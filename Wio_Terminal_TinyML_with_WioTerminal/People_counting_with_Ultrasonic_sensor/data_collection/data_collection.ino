#include "Ultrasonic.h"
#define INTERVAL_MS 50
Ultrasonic ultrasonic(0);

void setup() {
  Serial.begin(115200);
}

void loop() {
  static unsigned long last_interval_ms = 0;
  float distance;

  if (millis() > last_interval_ms + INTERVAL_MS) {
    last_interval_ms = millis();
    distance = ultrasonic.MeasureInCentimeters();
    if (distance < 200.0) {
      Serial.println(distance);
    }
    else
    Serial.println(-1);
  //Serial.print('\t');
  }
}
