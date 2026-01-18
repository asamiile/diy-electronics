#include "rpcWiFi.h" 
#include "DHT.h"
#include "TFT_eSPI.h"
#include "Free_Fonts.h"

#include "DNSServer.h"
#include "WebServer.h"
#include "WiFiManager.h" 

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include "credentials.h" // Adafruit IO credentials

// --- CONSTANTS AND CONFIGURATION ---

// Sensor Configuration
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Adafruit IO Connection Settings
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883              // use 8883 for SSL

// --- GLOBAL OBJECTS ---
TFT_eSPI tft; //initialize TFT LCD
TFT_eSprite spr = TFT_eSprite(&tft); //initialize sprite buffer

// Wi-Fi and MQTT Client Objects
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// MQTT Feeds for publishing data to Adafruit IO
// Format: <username>/feeds/<feedname>
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");

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
  // Increase the Wi-Fi setup portal wait time to 180 seconds (3 minutes)
  wifiManager.setConfigPortalTimeout(180);
  if (!wifiManager.autoConnect("AutoConnectAP")) {
    Serial.println("Failed to connect and hit timeout");
    tft.setFreeFont(FSS12);
    tft.fillScreen(TFT_MAGENTA);
    tft.drawString("Wi-Fi connection failed.", 40, 110);
    while (1);
  }

  Serial.print("Connected to WiFi. IP: ");
  Serial.println(WiFi.localIP());

  dht.begin();

  // Redraw the main UI now that a Wi-Fi connection is established.
  tft.fillScreen(TFT_BLACK);

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

void loop() {

  // Ensure we are connected to the MQTT broker before proceeding.
  MQTT_connect();

  // Read the latest sensor values.
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Publish the sensor readings to their respective Adafruit IO feeds.
  if (!temperature.publish(t, 2)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("Temperature sent!"));
  }

  if (!humidity.publish(h, 2)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("Humidity sent!"));
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
    // If we fail after all retries, return and let the main loop try again later.
    if (retries == 0) {
      Serial.println("MQTT connection failed. Will retry later.");
      return;
    }
  }

  Serial.println("MQTT Connected!");
}