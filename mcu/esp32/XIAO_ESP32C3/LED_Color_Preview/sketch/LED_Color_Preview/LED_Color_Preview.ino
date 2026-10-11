#include <Adafruit_NeoPixel.h>

#include "credentials.h"
#include "thingProperties.h"

// LED Stick data line (Shield D2/A2 port = GPIO4)
const int LED_PIN = D2;
const uint16_t LED_COUNT = 10;

// WS2813 Mini uses GRB order. Change this if colors are swapped
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Clamp to 0-255, then scale by brightness
uint8_t scaleByBrightness(int value) {
  const int level = constrain(brightness, 0, 255);
  return constrain(value, 0, 255) * level / 255;
}

// Apply the current RGB and brightness to all ten LEDs
void applyColor() {
  const uint32_t color = strip.Color(scaleByBrightness(red), scaleByBrightness(green), scaleByBrightness(blue));
  strip.fill(color);
  strip.show();
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  // Keep the LEDs off right after startup
  strip.begin();
  strip.clear();
  strip.show();

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
}

// Called when a Cloud variable changes
void onRedChange() {
  applyColor();
}

void onGreenChange() {
  applyColor();
}

void onBlueChange() {
  applyColor();
}

void onBrightnessChange() {
  applyColor();
}
