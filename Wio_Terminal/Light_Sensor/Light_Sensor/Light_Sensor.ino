#include "rpcWiFi.h"
#include "TFT_eSPI.h"
#include "Free_Fonts.h"

#include "DNSServer.h"
#include "WebServer.h"
#include "WiFiManager.h"

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "credentials.h"

// --- CONSTANTS AND CONFIGURATION ---

// Sensor Configuration
#define LIGHT_SENSOR_PIN WIO_LIGHT

// Adafruit IO Connection Settings
// IMPORTANT: Replace these with your Adafruit IO username and key!
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883

// --- GLOBAL OBJECTS ---

// TFT LCD and Sprite (buffer for partial screen updates)
TFT_eSPI tft;
TFT_eSprite spr = TFT_eSprite(&tft);

// Wi-Fi and MQTT Client Objects
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// MQTT Feed for publishing data to Adafruit IO
// The path follows the format: &lt;username&gt;/feeds/&lt;feedname&gt;
Adafruit_MQTT_Publish lightLevel = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light-level");

// --- FUNCTION PROTOTYPES ---
void MQTT_connect();

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

  // Use WiFiManager to handle the connection.
  // If no credentials are saved, it starts an Access Point named "AutoConnectAP".
  WiFiManager wifiManager;
  wifiManager.setConfigPortalTimeout(180);
  if (!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("Failed to connect and hit timeout");
    tft.fillScreen(TFT_MAGENTA);
    tft.drawString("Wi-Fi connection failed.", 40, 110);
    while (1); // Halt execution if Wi-Fi is essential for operation.
  }

  Serial.print("Connected to WiFi. IP: ");
  Serial.println(WiFi.localIP());

  // Redraw the main UI now that a Wi-Fi connection is established.
  tft.fillScreen(TFT_BLACK);

  // Draw the header
  tft.fillRect(0, 0, 320, 50, TFT_PURPLE);
  tft.setFreeFont(FSB9);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("SUNRISE & SUNSET ALARM", 30, 20);

  // Draw the static label
  tft.setFreeFont(FSS12);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("Light Level:", 30, 140);
}

void loop() {

  // Maintain connection to the MQTT broker.
  MQTT_connect();

  // Read the latest value from the light sensor.
  int lightValue = analogRead(LIGHT_SENSOR_PIN);

  // Publish the sensor reading to the Adafruit IO feed.
  if (!lightLevel.publish((int32_t)lightValue)) {
    Serial.println(F("Failed to publish light level."));
  } else {
    Serial.println(F("Light level sent!"));
  }

  // Print the reading to the Serial Monitor for debugging purposes.
  Serial.printf("Light Level: %dn", lightValue);

  // Update the light level value on the screen using a sprite.
  spr.createSprite(120, 50);
  spr.fillSprite(TFT_BLACK); // Erase the old value.
  spr.setFreeFont(FMB24);
  spr.setTextColor(TFT_GREENYELLOW);
  spr.drawNumber(lightValue, 0, 0);
  spr.pushSprite(170, 125);
  spr.deleteSprite();

  // Wait before taking the next reading.
  delay(10000); // Send data every 10 seconds

}

// --- FUNCTION PROTOTYPES ---
void MQTT_connect() {
  int8_t ret;

  // If already connected, do nothing and exit the function.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT… ");

  uint8_t retries = 3;

  // Loop until connected, with a limited number of retries.
  // The connect() function will return 0 for a successful connection.
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds…");
    mqtt.disconnect();
    delay(5000);
    retries--;
    if (retries == 0) {
      // If we fail after all retries, return and let the main loop try again later.
      Serial.println("MQTT connection failed. Will retry later.");
      return;
    }
  }

  Serial.println("MQTT Connected!");
}