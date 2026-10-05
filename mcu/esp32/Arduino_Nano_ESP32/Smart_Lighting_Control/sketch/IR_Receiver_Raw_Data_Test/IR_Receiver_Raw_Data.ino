/*
 * IR Receiver Test - Raw Data Display Version
 *
 * Purpose: Capture and display raw IR signal data from remote control
 * This helps identify the exact signal sent by Iris Ohyama ACL-DGR remote
 *
 * Hardware:
 * - Arduino Nano ESP32
 * - Grove IR Receiver (D4)
 */

#include <Arduino.h>
#include <IRremote.hpp>

#define IR_RECEIVER_PIN D4

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("\n=== IR Receiver - Raw Data Display ==="));
  Serial.println(F("Point ACL-DGR remote at D4 and press buttons"));
  Serial.println(F(""));

  // Initialize IR receiver
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);
  Serial.println(F("IR Receiver initialized on pin D4"));
  Serial.println(F(""));
  Serial.println(F("Waiting for signals..."));
  Serial.println(F(""));
}

void loop() {
  // Check if we received an IR signal
  if (IrReceiver.decode()) {
    Serial.println(F("\n=== IR Signal Received ==="));

    // Decoded data
    Serial.print(F("Protocol: "));
    Serial.println(IrReceiver.decodedIRData.protocol);

    Serial.print(F("Address: 0x"));
    Serial.print(IrReceiver.decodedIRData.address, HEX);
    Serial.print(F(" (Decimal: "));
    Serial.print(IrReceiver.decodedIRData.address);
    Serial.println(F(")"));

    Serial.print(F("Command: 0x"));
    Serial.print(IrReceiver.decodedIRData.command, HEX);
    Serial.print(F(" (Decimal: "));
    Serial.print(IrReceiver.decodedIRData.command);
    Serial.println(F(")"));

    Serial.print(F("Repeat: "));
    Serial.println(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT ? "YES" : "NO");

    Serial.print(F("Bits: "));
    Serial.println(IrReceiver.decodedIRData.numberOfBits);

    Serial.println(F(""));

    // Print summary
    Serial.println(F("--- Summary ---"));
    Serial.print(F("Full command (Hex): 0x"));
    Serial.print(IrReceiver.decodedIRData.address, HEX);
    Serial.print(IrReceiver.decodedIRData.command, HEX);
    Serial.println();

    // Continue receiving
    IrReceiver.resume();
  }

  delay(50);
}
