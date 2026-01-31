/*
 * IR Learning Sketch for Arduino Nano ESP32 (Fixed for IRremote v4.x)
 *
 * Hardware:
 * - Arduino Nano ESP32
 * - Grove Shield for Arduino Nano
 * - Grove - Infrared Receiver (connected to Digital Pin D4)
 */

#include <Arduino.h>

// Important: Enable protocols to use (include all for learning purposes)
#define DECODE_NEC          // Many home appliances
#define DECODE_SONY
#define DECODE_PANASONIC
#define DECODE_KAISUIKYO
#define DECODE_JVC
#define DECODE_SAMSUNG
#define DECODE_LG
#define DECODE_DENON
#define DECODE_SHARP
#define DECODE_BOSEWAVE

#include <IRremote.hpp>

// Infrared Receiver Pin
#define IR_RECEIVER_PIN D4

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial connection
  delay(1000);

  Serial.println(F("================================="));
  Serial.println(F("IR Learning Sketch (v4 compatible)"));
  Serial.println(F("================================="));
  Serial.println(F("IR Receiver Pin: D4"));

  // Start receiving
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);

  Serial.println(F("Ready to receive IR signals..."));
  Serial.println(F("Point the remote and press a button."));
  Serial.println();
}

void loop() {
  // Check if IR signal was received
  if (IrReceiver.decode()) {

    Serial.println();
    Serial.println(F(">>> IR SIGNAL RECEIVED <<<"));

    // Display results using library standard functions
    IrReceiver.printIRResultShort(&Serial);

    // Also display raw data
    Serial.println(F("--- Raw Data (for simple code) ---"));
    IrReceiver.printIRResultRawFormatted(&Serial, true);

    Serial.println(F("---------------------------------"));
    Serial.println(F("Copy 'Protocol' and 'Command' (or 'Data') for your credentials.h"));

    // Reset to receive next signal
    IrReceiver.resume();
  }
}
