#pragma once
#include <WiFiUdp.h>
#include <IRremote.hpp>

// 気象表示・気象用MQTTクライアントは元のWeather Station v2をそのまま使う。
// このヘッダーには追加する照明機能のみをまとめる。
#if !defined(LIGHTING_SHIFTR_KEY) || !defined(LIGHTING_SHIFTR_SECRET)
#error "Set LIGHTING_SHIFTR_KEY and LIGHTING_SHIFTR_SECRET in credentials.h"
#endif
WiFiClient lightingSocket;
PubSubClient lightingMqttClient(lightingSocket);
uint32_t lightingReconnectTick = 0;
char lightingClientId[40];
WiFiUDP ntp;
bool timeValid = false, taskExecutedToday = false;
uint16_t lightLevel = 0;
uint32_t epoch = 0, clockTick = 0, ntpSent = 0, ntpAttempt = 0;
bool ntpPending = false, udpReady = false;
uint8_t ntpRequest[48] = {};
uint32_t activeDay = 0, lightSensorTick = 0, lightingPublishTick = 0;
uint8_t retryCount = 0;
enum class LightingPhase { Idle, Sampling, Feedback };
LightingPhase lightingPhase = LightingPhase::Idle;
uint32_t sampleTick = 0, sampleSum = 0, feedbackTick = 0;
uint8_t sampleCount = 0;
const char* lightingResult = "idle";

void receiveMessage(char* topic, byte* payload, unsigned int length) {
  // Nano側と同様に受信内容の確認のみ。MQTT経由のトグル操作は行わない。
  Serial.print("[MQTT RX] ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.write(payload, length);
  Serial.println();
}

void maintainLightingConnection(uint32_t now) {
  if (WiFi.status() != WL_CONNECTED) return;
  // 気象用とは独立して、30秒に1回だけ接続を試す。
  if (!lightingMqttClient.connected() && lightingPhase == LightingPhase::Idle &&
      now - lightingReconnectTick >= RECONNECT_INTERVAL) {
    lightingReconnectTick = now;
    if (lightingMqttClient.connect(lightingClientId, LIGHTING_SHIFTR_KEY, LIGHTING_SHIFTR_SECRET)) {
      Serial.println("[Lighting MQTT] connected");
      if (!lightingMqttClient.subscribe(LIGHTING_INPUT_TOPIC)) {
        Serial.println("[Lighting MQTT] subscribe failed");
      }
    } else {
      Serial.print("[Lighting MQTT] connection failed: ");
      Serial.println(lightingMqttClient.state());
    }
  }
  lightingMqttClient.loop();
}

void updateClock(uint32_t now) {
  // millis()の折り返しをまたいでも時刻を保持する。
  const uint32_t elapsed = now - clockTick;
  epoch += elapsed / 1000;
  clockTick += (elapsed / 1000) * 1000;
  if (WiFi.status() != WL_CONNECTED) {
    if (udpReady) { ntp.stop(); udpReady = false; ntpPending = false; }
    return;
  }
  if (!udpReady) udpReady = ntp.begin(2390);
  if (!udpReady) return;
  if (ntpPending) {
    const int packetSize = ntp.parsePacket();
    if (packetSize > 0) {
      uint8_t response[48];
      const int bytes = ntp.read(response, sizeof(response));
      const bool fromNtp = ntp.remotePort() == 123;
      ntp.clear();
      if (bytes == 48 && fromNtp && (response[0] & 7) == 4 &&
          (response[0] >> 6) != 3 && response[1] > 0 && response[1] < 16 &&
          memcmp(response + 24, ntpRequest + 40, 8) == 0) {
        const uint32_t seconds = (uint32_t(response[40]) << 24) |
            (uint32_t(response[41]) << 16) | (uint32_t(response[42]) << 8) | response[43];
        // 現在のNTP eraを対象。異常な古い応答を採用しない。
        if (seconds > 2208988800UL && seconds - 2208988800UL >= 1704067200UL) {
          epoch = seconds - 2208988800UL;
          clockTick = now;
          timeValid = true;
          ntpPending = false;
          Serial.println("[NTP] synchronized (UTC)");
        }
      }
    }
    if (now - ntpSent >= 3000) ntpPending = false;
  }
  const uint32_t interval = timeValid ? 3600000UL : 30000UL;
  if (!ntpPending && now - ntpAttempt >= interval) {
    ntpAttempt = now;
    memset(ntpRequest, 0, sizeof(ntpRequest));
    ntpRequest[0] = 0x23; // NTP v4 client
    // 応答のoriginate timestampと照合する識別子。
    for (uint8_t i = 40; i < 48; ++i) ntpRequest[i] = uint8_t(random(1, 256));
    if (ntp.beginPacket(NTP_SERVER, 123)) {
      ntp.write(ntpRequest, sizeof(ntpRequest));
      if (ntp.endPacket()) { ntpPending = true; ntpSent = now; }
    }
  }
}

void updateLighting(uint32_t now) {
  if (timeValid) {
    const uint32_t local = epoch + TIMEZONE_SECONDS;
    const uint32_t day = local / 86400;
    if (day != activeDay) { activeDay = day; taskExecutedToday = false; }
    const uint32_t minute = (local % 86400) / 60;
    if (ENABLE_SCHEDULED_IR && !taskExecutedToday && lightingPhase == LightingPhase::Idle &&
        minute == SCHEDULED_OFF_HOUR * 60UL + SCHEDULED_OFF_MINUTE) {
      // 同一日の繰り返しトグルを防ぐ。再起動するとこの状態は失われる。
      taskExecutedToday = true;
      lightingPhase = LightingPhase::Sampling;
      sampleSum = 0; sampleCount = 0;
      sampleTick = now - SCHEDULED_OFF_READ_INTERVAL;
    }
  }
  if (lightingPhase == LightingPhase::Sampling && now - sampleTick >= SCHEDULED_OFF_READ_INTERVAL) {
    sampleTick = now;
    sampleSum += analogRead(LIGHT_SENSOR_PIN);
    if (++sampleCount == SCHEDULED_OFF_READ_COUNT) {
      lightLevel = sampleSum / sampleCount;
      if (lightLevel >= SCHEDULED_OFF_THRESHOLD) {
        IrReceiver.stop();
        IrSender.sendRaw(rawDataON_OFF, RAW_DATA_LENGTH, 38);
        IrReceiver.start();
        feedbackTick = millis();
        lightingPhase = LightingPhase::Feedback;
        lightingResult = "sent";
      } else {
        lightingResult = "skipped (dark)";
        lightingPhase = LightingPhase::Idle;
      }
      Serial.print("[Lighting] "); Serial.println(lightingResult);
    }
  }
  if (lightingPhase == LightingPhase::Feedback && millis() - feedbackTick >= FEEDBACK_CHECK_DELAY) {
    lightLevel = analogRead(LIGHT_SENSOR_PIN);
    lightingResult = lightLevel < LIGHT_OFF_THRESHOLD ? "OFF verified" : "OFF not verified";
    Serial.print("[Lighting] "); Serial.println(lightingResult);
    // トグル式なので確認失敗時の自動再送はしない。
    lightingPhase = LightingPhase::Idle;
  }
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume(); // 受信は診断用。実際の消灯確認は照度を用いる。
  }
}

void publishLighting() {
  if (client.connected()) {
    char topic[128], value[16];
    const int size = snprintf(topic, sizeof(topic), "%s/feeds/lighting", AIO_USERNAME);
    snprintf(value, sizeof(value), "%u", lightLevel);
    if (size > 0 && size < int(sizeof(topic)) && !client.publish(topic, value)) {
      Serial.println("[Lighting] Adafruit IO publish failed");
    }
  }
  if (!lightingMqttClient.connected()) {
    Serial.println("[Lighting MQTT] disconnected: JSON not sent");
    return;
  }
  char payload[384];
  StaticJsonDocument<384> doc;
  doc["device_id"] = "wio_terminal_lighting";
  if (timeValid) doc["timestamp"] = epoch; // 未同期ならCloud Functionsの受信時刻を使う。
  doc["lux"] = lightLevel; // スキーマ互換名。物理的なluxではなくADC値。
  doc["light_state"] = lightLevel >= LIGHT_OFF_THRESHOLD ? "ON" : "OFF";
  doc["task_executed"] = taskExecutedToday;
  doc["wifi_connected"] = WiFi.status() == WL_CONNECTED;
  doc["retry_count"] = retryCount;
  serializeJson(doc, payload, sizeof(payload));
  if (lightingMqttClient.publish(LIGHTING_TOPIC, payload)) {
    Serial.println("[Lighting MQTT] lighting/json published");
  } else Serial.println("[Lighting MQTT] publish failed");
}

void setupLighting() {
  analogReadResolution(10);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  IrSender.begin(IR_EMITTER_PIN);
  IrReceiver.begin(IR_RECEIVER_PIN, DISABLE_LED_FEEDBACK);
  lightingMqttClient.setServer(LIGHTING_SHIFTR_SERVER, LIGHTING_SHIFTR_SERVERPORT);
  lightingMqttClient.setCallback(receiveMessage);
  lightingMqttClient.setSocketTimeout(1);
  if (!lightingMqttClient.setBufferSize(512)) Serial.println("[Lighting] MQTT buffer allocation failed");
  snprintf(lightingClientId, sizeof(lightingClientId), "WioTerminal-Lighting-%04lx", (unsigned long)random(0xffff));
  const uint32_t now = millis();
  clockTick = lightSensorTick = lightingPublishTick = now;
  lightingReconnectTick = now - RECONNECT_INTERVAL;
  ntpAttempt = now - 30000;
  lightLevel = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("[Lighting] ADC: "); Serial.println(lightLevel);
}

void loopLighting() {
  uint32_t now = millis();
  updateClock(now);
  now = millis();
  updateLighting(now);
  if (!ENABLE_SCHEDULED_IR && Serial.available() && Serial.read() == 's' &&
      lightingPhase == LightingPhase::Idle) {
    IrReceiver.stop();
    IrSender.sendRaw(rawDataON_OFF, RAW_DATA_LENGTH, 38);
    IrReceiver.start();
    feedbackTick = millis();
    lightingResult = "manual toggle sent";
    Serial.print("[Lighting] "); Serial.println(lightingResult);
    lightingPhase = LightingPhase::Feedback;
  }
  now = millis();
  maintainLightingConnection(now);
  now = millis();
  if (now - lightSensorTick >= 1000 && lightingPhase == LightingPhase::Idle) {
    lightSensorTick = now;
    lightLevel = analogRead(LIGHT_SENSOR_PIN);
    Serial.print("[Lighting] ADC: "); Serial.print(lightLevel);
    Serial.print(" | state: ");
    Serial.println(lightLevel >= LIGHT_OFF_THRESHOLD ? "ON" : "OFF");
  }
  if (now - lightingPublishTick >= PUBLISH_INTERVAL) {
    lightingPublishTick = now;
    publishLighting();
  }
}
