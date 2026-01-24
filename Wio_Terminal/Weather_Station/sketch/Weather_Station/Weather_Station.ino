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
    tft.setFreeFont(FSS12);
    tft.fillScreen(TFT_MAGENTA);
    tft.drawString("Wi-Fi connection failed.", 40, 110);
    while (1);
  }

  Serial.print("Connected to WiFi. IP: ");
  Serial.println(WiFi.localIP());

  dht.begin();

  // Set up MQTT server
  client.setServer(AIO_SERVER, AIO_SERVERPORT);

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
  reconnect();

  client.loop();

  // Read the latest sensor values.
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Publish the sensor readings to Adafruit IO feeds
  String tempTopic = String(AIO_USERNAME) + "/feeds/temperature";
  String humidityTopic = String(AIO_USERNAME) + "/feeds/humidity";

  char tempStr[10];
  char humidityStr[10];
  dtostrf(t, 4, 2, tempStr);
  dtostrf(h, 4, 2, humidityStr);

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
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "WioTerminal-";
    clientId += String(random(0xffff), HEX);

    // Attempt to connect with Adafruit IO username and API key as password
    if (client.connect(clientId.c_str(), AIO_USERNAME, AIO_KEY)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
