#include "rpcWiFi.h"
#include "DHT.h"
#include "TFT_eSPI.h"
#include "Free_Fonts.h"

#include <PubSubClient.h>
#include "credentials.h"

// Sensor Configuration
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Adafruit IO Connection Settings
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883              // MQTT port

// --- GLOBAL OBJECTS ---
TFT_eSPI tft; //initialize TFT LCD
TFT_eSprite spr = TFT_eSprite(&tft); //initialize sprite buffer

// Wi-Fi and MQTT Client Objects
WiFiClient espClient;
PubSubClient client(espClient);

// --- FUNCTION PROTOTYPES ---
void MQTT_connect();
void drawDisplayUI();

void setup() {
  Serial.begin(115200);
  while (!Serial);
  delay(100);

  // Initialize the LCD and show a status message
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FSS12);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Connecting to Wi-Fi...", 50, 110);

  // LCD背光の安定化（バッテリー電源での不安定さを解決）
  delay(200);

  // credentials.hのSSID/パスワードを使用してWi-Fi接続
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // 接続待機（最大20秒）
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect to WiFi");
    Serial.printf("WiFi Status Code: %d\n", WiFi.status());
    tft.setFreeFont(FSS12);
    tft.fillScreen(TFT_MAGENTA);
    tft.drawString("Wi-Fi connection failed.", 40, 110);
    // バッテリー電源でも情報表示を保持するため、ループをスキップ
    // while (1); // コメントアウト - バッテリー動作時の対応
    delay(5000);
  } else {
    Serial.print("Connected to WiFi. IP: ");
    Serial.println(WiFi.localIP());
    Serial.printf("RSSI (Signal Strength): %d dBm\n", WiFi.RSSI());
    Serial.print("WiFi SSID: ");
    Serial.println(WIFI_SSID);
  }

  dht.begin();

  // Set up MQTT server
  client.setServer(AIO_SERVER, AIO_SERVERPORT);

  // Draw the initial UI
  drawDisplayUI();
}

void loop() {

  // バッテリー電源時の安定性向上：画面が消えた場合の自動復旧
  static unsigned long lastDisplayUpdate = 0;
  static unsigned long lastMQTTRetry = 0;
  static unsigned long lastWiFiCheck = 0;
  unsigned long now = millis();

  // 60秒ごとに画面表示を確認・復旧（バッテリー電源での背光リセット対策）
  if (now - lastDisplayUpdate > 60000) {
    lastDisplayUpdate = now;
    drawDisplayUI();
    Serial.println("[Display refresh] UI redrawn for battery stability");
  }

  // WiFi接続状態を常に監視（毎3秒確認）
  if (now - lastWiFiCheck > 3000) {
    lastWiFiCheck = now;
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WiFi Status] Connection lost! Attempting to reconnect...");
      Serial.printf("WiFi Status Code: %d\n", WiFi.status());
      WiFi.reconnect();  // WiFiの再接続を試行
      delay(500);
      if (WiFi.status() == WL_CONNECTED) {
        Serial.print("✓ WiFi reconnected. IP: ");
        Serial.println(WiFi.localIP());
        Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());
      } else {
        Serial.println("✗ WiFi reconnect failed. Will retry in next cycle.");
      }
    }
  }

  // MQTT接続試行（30秒ごと）
  if (now - lastMQTTRetry > 30000 || !client.connected()) {
    lastMQTTRetry = now;
    reconnect();
  }

  client.loop();

  // Read the latest sensor values.
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Publish the sensor readings to Adafruit IO feeds (only if MQTT is connected)
  String tempTopic = String(AIO_USERNAME) + "/feeds/temperature";
  String humidityTopic = String(AIO_USERNAME) + "/feeds/humidity";

  char tempStr[10];
  char humidityStr[10];
  dtostrf(t, 4, 2, tempStr);
  dtostrf(h, 4, 2, humidityStr);

  if (client.connected()) {
    if (client.publish(tempTopic.c_str(), tempStr)) {
      Serial.println(F("Temperature sent!"));
    } else {
      Serial.println(F("Temperature failed"));
    }

    if (client.publish(humidityTopic.c_str(), humidityStr)) {
      Serial.println(F("Humidity sent!"));
    } else {
      Serial.println(F("Humidity failed"));
    }
  } else {
    Serial.println("MQTT not connected - sensor data will not be sent to Adafruit IO");
    Serial.printf("Temperature: %.2f *C, Humidity: %.2f %% (local only)\n", t, h);
  }

  // Print the readings to the Serial Monitor for debugging purposes.
  Serial.printf("Temperature: %.2f *C, Humidity: %.2f %%\n", t, h);

  // Update the temperature value on the screen using a sprite.
  spr.createSprite(55, 40);
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(FMB24);
  spr.setTextColor(TFT_CYAN);
  spr.drawNumber((int)t, 0, 0);
  spr.pushSprite(200, 70);
  spr.deleteSprite();

  // Update the humidity value on the screen using a sprite.
  spr.createSprite(55, 40);
  spr.fillSprite(TFT_BLACK);
  spr.setFreeFont(FMB24);
  spr.setTextColor(TFT_CYAN);
  spr.drawNumber((int)h, 0, 0);
  spr.pushSprite(155, 170);
  spr.deleteSprite();

  // Wait before taking the next reading.
  delay(3000);

}

void reconnect() {
  // WiFi接続を再確認
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\n[MQTT] WiFi not connected. Attempting WiFi reconnect...");
    WiFi.reconnect();
    delay(1000);

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[MQTT] ERROR: WiFi reconnect failed. Cannot reach Adafruit IO.");
      Serial.printf("WiFi Status: %d\n", WiFi.status());
      Serial.println("Waiting 30 seconds before next MQTT attempt...");
      return;
    } else {
      Serial.print("[MQTT] WiFi restored. IP: ");
      Serial.println(WiFi.localIP());
      Serial.printf("RSSI: %d dBm\n", WiFi.RSSI());
    }
  }

  // WiFi接続確認後、MQTT接続を試行
  int attempt = 0;
  while (!client.connected() && attempt < 5) {
    attempt++;
    Serial.print("\n[Attempt ");
    Serial.print(attempt);
    Serial.print("/5] Attempting MQTT connection to ");
    Serial.print(AIO_SERVER);
    Serial.print(":");
    Serial.println(AIO_SERVERPORT);

    // Create a random client ID
    String clientId = "WioTerminal-";
    clientId += String(random(0xffff), HEX);

    Serial.printf("Client ID: %s\n", clientId.c_str());
    Serial.printf("Username: %s\n", AIO_USERNAME);
    Serial.println("Connecting...");

    // Attempt to connect with Adafruit IO username and API key as password
    if (client.connect(clientId.c_str(), AIO_USERNAME, AIO_KEY)) {
      Serial.println("✓ MQTT connected successfully!");
      break;
    } else {
      Serial.print("✗ MQTT connection failed. Error code: ");
      int state = client.state();
      Serial.println(state);

      // エラーコードの詳細説明
      switch(state) {
        case -4: Serial.println("  → MQTT_CONNECTION_TIMEOUT"); break;
        case -3: Serial.println("  → MQTT_CONNECTION_LOST"); break;
        case -2: Serial.println("  → MQTT_CONNECT_FAILED (Network issue or server unreachable)"); break;
        case -1: Serial.println("  → MQTT_DISCONNECTED"); break;
        case 1: Serial.println("  → MQTT_CONNECT_BAD_PROTOCOL"); break;
        case 2: Serial.println("  → MQTT_CONNECT_BAD_CLIENT_ID"); break;
        case 3: Serial.println("  → MQTT_CONNECT_UNAVAILABLE"); break;
        case 4: Serial.println("  → MQTT_CONNECT_BAD_CREDENTIALS (Check AIO_USERNAME and AIO_KEY)"); break;
        case 5: Serial.println("  → MQTT_CONNECT_UNAUTHORIZED"); break;
        default: Serial.println("  → Unknown error"); break;
      }

      Serial.print("Retry in 5 seconds...\n");
      delay(5000);
    }
  }

  if (!client.connected()) {
    Serial.println("\nWARNING: Could not connect to MQTT after 5 attempts.");
    Serial.println("Continuing with sensor reading anyway (offline mode)...");
  }
}

// ============================================
// UI Display Function
// ============================================
// Draws all static UI elements (header, labels, units, divider line)
void drawDisplayUI() {
  // Clear the screen
  tft.fillScreen(TFT_BLACK);
  delay(50);  // Wait for screen clear to complete

  // Draw the header
  tft.fillRect(0, 0, 320, 50, TFT_CYAN);
  tft.setFreeFont(FMB12);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("WEATHER STATION", 40, 15);

  // Draw the static labels
  tft.setFreeFont(FM12);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Temperature:", 10, 75);
  tft.drawString("Humidity:", 10, 175);

  // Draw the units
  tft.setFreeFont(FSSB9);
  tft.setTextColor(TFT_CYAN);
  tft.drawString("C", 260, 70);
  tft.drawString("%RH", 215, 170);

  // Draw the divider line
  tft.drawFastHLine(0, 140, 320, TFT_CYAN);
}
