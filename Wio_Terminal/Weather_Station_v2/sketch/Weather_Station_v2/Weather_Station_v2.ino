// filepath: Wio_Terminal/Weather_Station_v2/sketch/Weather_Station_v2/Weather_Station_v2.ino
#include "rpcWiFi.h"
#include <Wire.h>
#include "Seeed_BME280.h"
#include "TFT_eSPI.h"
#include "Free_Fonts.h"

#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "credentials.h"

// Sensor Configuration (BME280 - I2C接続)
BME280 bme280;

// Adafruit IO Connection Settings
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883              // MQTT port
#define MQTT_PUBLISH_INTERVAL 60000       // Send data every 60 seconds (balance between battery efficiency and precision)

// Shiftr.io Connection Settings
#define SHIFTR_SERVER   "public.cloud.shiftr.io"
#define SHIFTR_SERVERPORT 1883            // MQTT port
#define SHIFTR_TOPIC    "wio/json"        // Topic for JSON data

// --- GLOBAL OBJECTS ---
TFT_eSPI tft; //initialize TFT LCD
TFT_eSprite spr = TFT_eSprite(&tft); //initialize sprite buffer

// Wi-Fi and MQTT Client Objects
WiFiClient espClient;
PubSubClient client(espClient);

// Shiftr.io MQTT Client Objects
WiFiClient shiftrClient;
PubSubClient shiftrMqttClient(shiftrClient);

// --- FUNCTION PROTOTYPES ---
void reconnect();
void reconnectShiftr();
void sendJsonToShiftr(float temperature, float humidity, float pressure);
void drawDisplayUI();

void setup() {
  Serial.begin(115200);
  // Serial wait with timeout (avoid infinite loop on battery power where serial is not available)
  unsigned long serialWaitStart = millis();
  while (!Serial && millis() - serialWaitStart < 3000) {
    delay(10);
  }
  delay(100);

  // Initialize the LCD and show a status message
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  tft.setFreeFont(FSS12);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Connecting to Wi-Fi...", 50, 110);

  // Power stabilization wait (avoid instability during battery power switching)
  // Allow sufficient time to avoid current surge when switching from USB to battery
  delay(1000);

  // WiFi module initialization wait (Important: allow sufficient time after TFT initialization)
  Serial.println("\n[WiFi] Initializing WiFi module...");
  delay(500);

  // Connect to Wi-Fi using SSID/password from credentials.h
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Wait for connection (max 20 seconds)
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 40) {  // 40 attempts * 500ms = 20 seconds
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
    // Skip loop to keep information displayed even on battery power
    // while (1); // Commented out - for battery operation
    delay(5000);
  } else {
    Serial.print("Connected to WiFi. IP: ");
    Serial.println(WiFi.localIP());
    Serial.printf("RSSI (Signal Strength): %d dBm\n", WiFi.RSSI());
    Serial.print("WiFi SSID: ");
    Serial.println(WIFI_SSID);
  }

  // BME280初期化 (I2C接続)
  Serial.println("[INIT] Initializing BME280 sensor...");
  if (!bme280.init()) {
    Serial.println("[ERROR] BME280 initialization failed!");
    tft.fillScreen(TFT_RED);
    tft.drawString("BME280 Init Failed", 50, 110);
    delay(3000);
  } else {
    Serial.println("[INIT] BME280 sensor initialized successfully");
  }

  // Set up Adafruit IO MQTT server
  client.setServer(AIO_SERVER, AIO_SERVERPORT);

  // Set up Shiftr.io MQTT server
  shiftrMqttClient.setServer(SHIFTR_SERVER, SHIFTR_SERVERPORT);

  // Draw the initial UI
  drawDisplayUI();

  Serial.println("[SETUP] Device ready");
}

void loop() {

  // Track loop execution count and timestamp (for debugging)
  static unsigned long lastDebugPrint = 0;
  unsigned long now = millis();

  if (now - lastDebugPrint > 60000) {  // Print loop status every 60 seconds
    Serial.printf("[LOOP] Device alive - uptime: %lu sec\n", now / 1000);
    lastDebugPrint = now;
  }

  // Improve stability on battery power: auto recovery if screen goes black
  static unsigned long lastMQTTRetry = 0;
  static unsigned long lastWiFiCheck = 0;
  static unsigned long lastSensorRead = 0;

  // Always maintain MQTT keep-alive (execute every loop)
  // Timeout protection: WDT will reset if client.loop() blocks for too long
  client.loop();

  // Shiftr.io MQTT keep-alive
  shiftrMqttClient.loop();

  // Constantly monitor WiFi connection status (check every 3 seconds)
  if (now - lastWiFiCheck > 3000) {
    lastWiFiCheck = now;
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("[WiFi Status] Connection lost! Attempting to reconnect...");
      Serial.printf("WiFi Status Code: %d\n", WiFi.status());
      WiFi.reconnect();  // Attempt WiFi reconnection
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

  // MQTT connection attempt (every 30 seconds or when connection is lost)
  if (now - lastMQTTRetry > 30000 || !client.connected()) {
    lastMQTTRetry = now;
    reconnect();
    reconnectShiftr();  // Also try to connect to Shiftr.io
  }

  // Read and send sensor data (every 60 seconds)
  if (now - lastSensorRead > MQTT_PUBLISH_INTERVAL) {
    lastSensorRead = now;

    // Read the latest sensor values from BME280
    float t = bme280.getTemperature();
    float h = bme280.getHumidity();
    float p = bme280.getPressure() / 100.0;  // Convert Pa to hPa

    // Publish the sensor readings to Adafruit IO feeds (only if MQTT is connected)
    String tempTopic = String(AIO_USERNAME) + "/feeds/temperature";
    String humidityTopic = String(AIO_USERNAME) + "/feeds/humidity";
    String pressureTopic = String(AIO_USERNAME) + "/feeds/pressure";

    char tempStr[10];
    char humidityStr[10];
    char pressureStr[10];
    dtostrf(t, 4, 2, tempStr);
    dtostrf(h, 4, 2, humidityStr);
    dtostrf(p, 5, 2, pressureStr);

    if (client.connected()) {
      if (client.publish(tempTopic.c_str(), tempStr)) {
        Serial.println(F("✓ Temperature sent!"));
      } else {
        Serial.println(F("✗ Temperature failed"));
      }

      if (client.publish(humidityTopic.c_str(), humidityStr)) {
        Serial.println(F("✓ Humidity sent!"));
      } else {
        Serial.println(F("✗ Humidity failed"));
      }

      if (client.publish(pressureTopic.c_str(), pressureStr)) {
        Serial.println(F("✓ Pressure sent!"));
      } else {
        Serial.println(F("✗ Pressure failed"));
      }
    } else {
      Serial.println("✗ MQTT not connected - sensor data will not be sent to Adafruit IO");
      Serial.printf("Temperature: %.2f *C, Humidity: %.2f %%, Pressure: %.2f hPa (local only)\n", t, h, p);
    }

    // Print the readings to the Serial Monitor for debugging purposes.
    Serial.printf("Sensor readings: Temperature: %.2f *C, Humidity: %.2f %%, Pressure: %.2f hPa\n", t, h, p);

    // Send data to Shiftr.io as JSON
    sendJsonToShiftr(t, h, p);

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
    spr.pushSprite(200, 120);
    spr.deleteSprite();

    // Update the pressure value on the screen using a sprite.
    spr.createSprite(70, 40);
    spr.fillSprite(TFT_BLACK);
    spr.setFreeFont(FMB24);
    spr.setTextColor(TFT_CYAN);
    spr.drawNumber((int)p, 0, 0);
    spr.pushSprite(195, 170);
    spr.deleteSprite();
  } // End of sensor read block

  // Non-blocking delay (always maintain MQTT keep-alive)
  delay(100);  // Short delay to maintain other microcontroller functions

}

// ============================================
// UI Display Function
// ============================================
// Draws all static UI elements (header, labels, units, divider line)
void drawDisplayUI() {
  // Clear the screen
  Serial.println("[UI] Attempting to initialize TFT display...");
  tft.fillScreen(TFT_BLACK);
  delay(50);  // Wait for screen clear to complete
  Serial.println("[UI] Display cleared successfully");

  // Draw the header
  tft.fillRect(0, 0, 320, 50, TFT_CYAN);
  tft.setFreeFont(FMB12);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("WEATHER STATION V2", 30, 15);

  // Draw the static labels
  tft.setFreeFont(FM12);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Temperature:", 10, 75);
  tft.drawString("Humidity:", 10, 125);
  tft.drawString("Pressure:", 10, 175);

  // Draw the units
  tft.setFreeFont(FSSB9);
  tft.setTextColor(TFT_CYAN);
  tft.drawString("C", 260, 70);
  tft.drawString("%RH", 275, 120);
  tft.drawString("hPa", 270, 170);

  // Draw divider lines
  tft.drawFastHLine(0, 105, 320, TFT_CYAN);
  tft.drawFastHLine(0, 155, 320, TFT_CYAN);

  Serial.println("[UI] Display UI initialized successfully");
}

// ============================================
// Adafruit IO MQTT Connection Function
// ============================================
void reconnect() {
  // Re-check WiFi connection
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

  // Attempt MQTT connection after confirming WiFi connection
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

      // Detailed explanation of error codes
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
// Shiftr.io MQTT Connection Function
// ============================================
void reconnectShiftr() {
  // Re-check WiFi connection
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("[Shiftr.io] WiFi not connected. Skipping Shiftr.io connection.");
    return;
  }

  // Attempt Shiftr.io MQTT connection
  int attempt = 0;
  while (!shiftrMqttClient.connected() && attempt < 3) {
    attempt++;

    // Shorten retry interval to reduce current consumption on battery power
    Serial.print("\n[Shiftr.io Attempt ");
    Serial.print(attempt);
    Serial.print("/3] Connecting to ");
    Serial.print(SHIFTR_SERVER);
    Serial.print(":");
    Serial.println(SHIFTR_SERVERPORT);

    // Create a random client ID
    String clientId = "WioTerminal-Shiftr-";
    clientId += String(random(0xffff), HEX);

    Serial.printf("Client ID: %s\n", clientId.c_str());
    Serial.printf("Username (Key): %s\n", SHIFTR_KEY);

    // Attempt to connect with Shiftr.io credentials
    if (shiftrMqttClient.connect(clientId.c_str(), SHIFTR_KEY, SHIFTR_SECRET)) {
      Serial.println("✓ Shiftr.io MQTT connected successfully!");
      break;
    } else {
      Serial.print("✗ Shiftr.io connection failed. Error code: ");
      int state = shiftrMqttClient.state();
      Serial.println(state);

      switch(state) {
        case -4: Serial.println("  → MQTT_CONNECTION_TIMEOUT"); break;
        case -3: Serial.println("  → MQTT_CONNECTION_LOST"); break;
        case -2: Serial.println("  → MQTT_CONNECT_FAILED"); break;
        case -1: Serial.println("  → MQTT_DISCONNECTED"); break;
        case 1: Serial.println("  → MQTT_CONNECT_BAD_PROTOCOL"); break;
        case 2: Serial.println("  → MQTT_CONNECT_BAD_CLIENT_ID"); break;
        case 3: Serial.println("  → MQTT_CONNECT_UNAVAILABLE"); break;
        case 4: Serial.println("  → MQTT_CONNECT_BAD_CREDENTIALS (Check SHIFTR_KEY and SHIFTR_SECRET)"); break;
        case 5: Serial.println("  → MQTT_CONNECT_UNAUTHORIZED"); break;
        default: Serial.println("  → Unknown error"); break;
      }

      if (attempt < 3) {
        // Battery power load reduction: adjust retry interval
        Serial.println("  Retrying in 1 second...");
        delay(1000);
      }
    }
  }

  if (!shiftrMqttClient.connected()) {
    Serial.println("[Shiftr.io] WARNING: Could not connect to Shiftr.io after 3 attempts.");
  }
}

// ============================================
// Send JSON Data to Shiftr.io
// ============================================
void sendJsonToShiftr(float temperature, float humidity, float pressure) {
  // Check Shiftr.io connection; reconnect if necessary
  if (!shiftrMqttClient.connected()) {
    Serial.println("[Shiftr.io] Not connected. Attempting reconnection...");
    reconnectShiftr();
  }

  // Only send if connected
  if (shiftrMqttClient.connected()) {
    // Create JSON document using ArduinoJson
    StaticJsonDocument<256> jsonDoc;
    jsonDoc["device_id"] = "wio_terminal";
    jsonDoc["temperature"] = temperature;
    jsonDoc["humidity"] = humidity;
    jsonDoc["pressure"] = pressure;

    // Serialize JSON to string
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Publish to Shiftr.io topic
    if (shiftrMqttClient.publish(SHIFTR_TOPIC, jsonString.c_str())) {
      Serial.println("[Shiftr.io] ✓ JSON data sent successfully!");
      Serial.print("  Topic: ");
      Serial.println(SHIFTR_TOPIC);
      Serial.print("  Payload: ");
      Serial.println(jsonString);
    } else {
      Serial.println("[Shiftr.io] ✗ Failed to publish JSON data");
    }
  } else {
    Serial.println("[Shiftr.io] ✗ Not connected - JSON data will not be sent");
  }
}
