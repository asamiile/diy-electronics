/*
  Smart Lighting Control - Arduino Nano ESP32

  Features:
  - Grove Light Sensor (analog A0) for brightness detection
  - Scheduled OFF at 23:30 (with brightness check)
  - IR remote control (Grove Infrared Emitter D2, Receiver D4)
  - Dual MQTT publishing (Shiftr.io + Adafruit IO)
  - WiFi with NTP time sync (JST)
  - Feedback verification via IR receiver

  Author: DIY Electronics
  Date: 2025
*/

#include "config.h"
#include "credentials.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <time.h>
#include <IRremote.hpp>

// ===== PIN DEFINITIONS =====
// ピン番号は config.h で定義されているため、ここでは直接数値を使用

// ===== MQTT CLIENT OBJECTS =====
WiFiClient shiftrClient;
PubSubClient shiftrMqtt(shiftrClient);

WiFiClient adafruitClient;
PubSubClient adafruitMqtt(adafruitClient);

// ===== STATE VARIABLES =====
uint16_t currentLux = 0;
bool lastKnownState = false;  // true = light ON, false = light OFF
unsigned long lastSensorReadTime = 0;
unsigned long lastShiftrPublishTime = 0;
unsigned long lastAdafruitPublishTime = 0;
unsigned long lastIRFeedbackCheckTime = 0;
bool taskExecutedToday = false;
uint8_t wifiRetryCount = 0;

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n\n=== Smart Lighting Control (Arduino Nano ESP32) ===");

  // Initialize hardware
  initializePins();
  initializeLightSensor();

  // WiFi and time sync
  initializeWiFi();
  syncNTPTime();

  // Configure MQTT servers
  shiftrMqtt.setServer(SHIFTR_SERVER, SHIFTR_PORT);
  shiftrMqtt.setCallback(shiftrCallback);

  adafruitMqtt.setServer(ADAFRUIT_SERVER, ADAFRUIT_PORT);
  adafruitMqtt.setCallback(adafruitCallback);

  // Reconnect MQTT
  reconnectShiftrMQTT();
  reconnectAdafruitMQTT();

  // IR emitter setup
  IrSender.begin(2, ENABLE_LED_FEEDBACK);  // D2 (GPIO 2)
  Serial.println("[SETUP] IR emitter initialized");

  // IR receiver setup
  IrReceiver.begin(4, ENABLE_LED_FEEDBACK);  // D4 (GPIO 4)

  printSystemStatus();
}

// ===== MAIN LOOP =====
void loop() {
  // Maintain WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    initializeWiFi();
  }

  // Maintain MQTT connections
  if (!shiftrMqtt.connected()) {
    reconnectShiftrMQTT();
  }
  shiftrMqtt.loop();

  if (!adafruitMqtt.connected()) {
    reconnectAdafruitMQTT();
  }
  adafruitMqtt.loop();

  // Sensor reading (every 60 seconds)
  if (millis() - lastSensorReadTime > 60000) {
    readLightSensor();
    lastSensorReadTime = millis();
  }

  // Check scheduled task (every minute)
  static unsigned long lastCheckTime = 0;
  if (millis() - lastCheckTime > 60000) {
    checkScheduledTask();
    lastCheckTime = millis();
  }

  // Publish to Shiftr.io (every 60 seconds)
  if (millis() - lastShiftrPublishTime > 60000) {
    if (shiftrMqtt.connected()) {
      publishToShiftr();
      lastShiftrPublishTime = millis();
    }
  }

  // Publish to Adafruit IO (every 60 seconds)
  if (millis() - lastAdafruitPublishTime > 60000) {
    if (adafruitMqtt.connected()) {
      publishToAdafruit();
      lastAdafruitPublishTime = millis();
    }
  }

  // IR feedback check (if light control was executed)
  if (millis() - lastIRFeedbackCheckTime > 5000) {
    handleFeedbackVerification();
    lastIRFeedbackCheckTime = millis();
  }

  delay(100);  // Non-blocking delay
}

// ===== INITIALIZATION FUNCTIONS =====
void initializePins() {
  pinMode(A0, INPUT);       // Light sensor
  pinMode(2, OUTPUT);       // IR emitter (D2)
  pinMode(4, INPUT);        // IR receiver (D4)
  Serial.println("[INIT] Pins configured");
}

void initializeLightSensor() {
  // Read once to initialize
  currentLux = analogRead(A0);
  Serial.print("[INIT] Light Sensor initialized. Initial value: ");
  Serial.println(currentLux);
}

void initializeWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    return;  // Already connected
  }

  Serial.print("[WiFi] Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  uint8_t attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("[WiFi] Connected! IP: ");
    Serial.println(WiFi.localIP());
    wifiRetryCount = 0;
  } else {
    Serial.println("[WiFi] Connection failed");
    wifiRetryCount++;
  }
}

void syncNTPTime() {
  Serial.println("[NTP] Syncing time...");
  configTime(9 * 3600, 0, "ntp.nict.jp", "time.google.com");  // JST (UTC+9)

  time_t now = time(nullptr);
  uint8_t attempts = 0;
  while (now < 24 * 3600 && attempts < 20) {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
    attempts++;
  }
  Serial.println();

  if (now > 24 * 3600) {
    Serial.print("[NTP] Time synced: ");
    Serial.println(ctime(&now));
  } else {
    Serial.println("[NTP] Failed to sync time");
  }
}

// ===== SENSOR READING =====
void readLightSensor() {
  currentLux = analogRead(A0);
  Serial.print("[SENSOR] Lux: ");
  Serial.print(currentLux);
  Serial.print(" | Light State: ");
  Serial.println(currentLux >= LIGHT_OFF_THRESHOLD ? "ON" : "OFF");
}

// ===== SCHEDULED TASK =====
void checkScheduledTask() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);

  int currentHour = timeinfo->tm_hour;
  int currentMinute = timeinfo->tm_min;

  // Check if it's 23:30 and light is ON
  if (currentHour == SCHEDULED_OFF_HOUR &&
      currentMinute == SCHEDULED_OFF_MINUTE &&
      !taskExecutedToday) {

    // Only send OFF if light is currently bright (ON)
    if (currentLux >= LIGHT_OFF_THRESHOLD) {
      Serial.println("[TASK] Executing scheduled OFF at 23:30");
      sendLightOffSignal();
      taskExecutedToday = true;
    } else {
      Serial.println("[TASK] Light already OFF, skipping send");
      taskExecutedToday = true;
    }
  }

  // Reset flag at midnight
  if (currentHour == 0 && currentMinute == 0) {
    taskExecutedToday = false;
    Serial.println("[TASK] Daily flag reset");
  }
}

// ===== IR CONTROL =====
void sendLightOffSignal() {
  // Send raw IR waveform for OFF command
  Serial.println("[IR] Sending OFF signal (raw waveform)...");

  IrSender.sendRaw(rawDataON_OFF, RAW_DATA_LENGTH, 38);

  delay(500);
  Serial.println("[IR] OFF signal sent");
}

void handleFeedbackVerification() {
  if (IrReceiver.decode()) {
    Serial.print("[IR_RX] Decoded: ");
    Serial.print(IrReceiver.decodedIRData.protocol);
    Serial.print(" | Address: ");
    Serial.print(IrReceiver.decodedIRData.address, HEX);
    Serial.print(" | Command: ");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    IrReceiver.resume();
  }
}

// ===== MQTT CONNECTION =====
void reconnectShiftrMQTT() {
  if (shiftrMqtt.connected()) {
    return;
  }

  Serial.print("[MQTT-Shiftr] Connecting...");

  // Generate random client ID (like Weather_Station pattern)
  String clientId = "Arduino-Nano-ESP32-";
  clientId += String(random(0xffff), HEX);

  // Username and password for Shiftr.io
  if (shiftrMqtt.connect(clientId.c_str(), SHIFTR_USERNAME, SHIFTR_PASSWORD)) {
    Serial.println(" SUCCESS");
    shiftrMqtt.subscribe(SHIFTR_SUBSCRIBE_TOPIC);
  } else {
    Serial.print(" FAILED (");
    Serial.print(shiftrMqtt.state());
    Serial.println(")");
  }
}

void reconnectAdafruitMQTT() {
  if (adafruitMqtt.connected()) {
    return;
  }

  Serial.print("[MQTT-Adafruit] Connecting...");

  // Generate random client ID (like Weather_Station pattern)
  String clientId = "Arduino-Nano-ESP32-";
  clientId += String(random(0xffff), HEX);

  // Username and key for Adafruit IO
  if (adafruitMqtt.connect(clientId.c_str(), AIO_USERNAME, AIO_KEY)) {
    Serial.println(" SUCCESS");
  } else {
    Serial.print(" FAILED (");
    Serial.print(adafruitMqtt.state());
    Serial.println(")");
  }
}

// ===== MQTT PUBLISH =====
void publishToShiftr() {
  if (!shiftrMqtt.connected()) {
    return;
  }

  DynamicJsonDocument doc(256);
  doc["device_id"] = DEVICE_ID;  // Add device identifier for BigQuery
  doc["timestamp"] = time(nullptr);
  doc["lux"] = currentLux;
  doc["light_state"] = currentLux >= LIGHT_OFF_THRESHOLD ? "ON" : "OFF";
  doc["task_executed"] = taskExecutedToday;
  doc["wifi_connected"] = WiFi.status() == WL_CONNECTED;
  doc["retry_count"] = wifiRetryCount;

  String payload;
  serializeJson(doc, payload);

  if (shiftrMqtt.publish(SHIFTR_TOPIC, payload.c_str())) {
    Serial.print("[MQTT-Shiftr] Published: ");
    Serial.println(payload);
  } else {
    Serial.println("[MQTT-Shiftr] Publish failed");
  }
}

void publishToAdafruit() {
  if (!adafruitMqtt.connected()) {
    return;
  }

  String feedPath = String(AIO_USERNAME) + "/feeds/lighting";
  String luxValue = String(currentLux);

  if (adafruitMqtt.publish(feedPath.c_str(), luxValue.c_str())) {
    Serial.print("[MQTT-Adafruit] Published Lux: ");
    Serial.println(luxValue);
  } else {
    Serial.println("[MQTT-Adafruit] Publish failed");
  }
}

// ===== MQTT CALLBACKS =====
void shiftrCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("[MQTT-Shiftr] Message on ");
  Serial.print(topic);
  Serial.print(": ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void adafruitCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("[MQTT-Adafruit] Message on ");
  Serial.print(topic);
  Serial.print(": ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// ===== STATUS PRINTING =====
void printSystemStatus() {
  Serial.println("\n========== SYSTEM STATUS ==========");
  Serial.print("WiFi Status: ");
  Serial.println(WiFi.status() == WL_CONNECTED ? "CONNECTED" : "DISCONNECTED");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  }

  Serial.print("Shiftr MQTT: ");
  Serial.println(shiftrMqtt.connected() ? "CONNECTED" : "DISCONNECTED");

  Serial.print("Adafruit MQTT: ");
  Serial.println(adafruitMqtt.connected() ? "CONNECTED" : "DISCONNECTED");

  Serial.print("Current Lux: ");
  Serial.println(currentLux);

  time_t now = time(nullptr);
  Serial.print("Current Time (JST): ");
  Serial.println(ctime(&now));

  Serial.println("=====================================\n");
}
