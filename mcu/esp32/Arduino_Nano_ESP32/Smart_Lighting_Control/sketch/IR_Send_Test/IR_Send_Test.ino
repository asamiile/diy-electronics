/*
 * IR Send & Receive Test - Integrated IR Test with Grove Modules
 *
 * Purpose: Test IR sending (D2) and receiving (D4) with actual ceiling light remote codes
 * No WiFi, no NTP, no scheduling - just simple IR transmission and reception
 *
 * Hardware:
 * - Arduino Nano ESP32
 * - Grove IR Emitter (D2)
 * - Grove IR Receiver (D4)
 * - Built-in LED or external LED on D1 for feedback
 */

#include <Arduino.h>
#include <IRremote.hpp>

// Pin Configuration
#define IR_EMITTER_PIN D2
#define IR_RECEIVER_PIN D4
#define FEEDBACK_LED_PIN D1

// IR Code - Ceiling Light (NEC Protocol)
#define IR_ADDRESS 0x1275
#define IR_COMMAND_TOGGLE 0x207   // ON/OFF toggle
#define IR_COMMAND_BRIGHTNESS_UP 0x208
#define IR_COMMAND_BRIGHTNESS_DOWN 0x206
#define IR_COMMAND_NIGHT_LIGHT 0x203
#define IR_COMMAND_FULL_BRIGHT 0x202

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println(F("\n=== IR Send & Receive Test ==="));
  Serial.println(F("Testing Grove IR Emitter (D2) and Receiver (D4)"));
  Serial.println(F("Ceiling Light Remote Codes (NEC Protocol)"));
  Serial.println(F(""));
  Serial.println(F("Commands:"));
  Serial.println(F("  '0' - Send Light Toggle (ON/OFF)"));
  Serial.println(F("  '8' - Send Brightness UP"));
  Serial.println(F("  '9' - Send Brightness DOWN"));
  Serial.println(F("  '3' - Send Night Light"));
  Serial.println(F("  '2' - Send Full Bright"));
  Serial.println(F("  'c' - Send CH Setting + Toggle (TEST)"));
  Serial.println(F("  'r' - Show received signals"));
  Serial.println(F("  '?'  - Show help"));
  Serial.println(F(""));

  // Initialize pins
  pinMode(FEEDBACK_LED_PIN, OUTPUT);
  digitalWrite(FEEDBACK_LED_PIN, LOW);

  // Initialize IR Emitter
  // IrSender.begin(pin) or IrSender.begin(pin, enableFeedback, feedbackPin)
  IrSender.begin(IR_EMITTER_PIN);  // D2 = IR Emitter output
  Serial.println(F("IR Emitter initialized on D2"));

  // Feedback LED on D1
  digitalWrite(FEEDBACK_LED_PIN, LOW);

  // Initialize IR Receiver
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);
  Serial.println(F("IR Receiver initialized on pin D4"));

  Serial.println(F(""));
  Serial.println(F("Ready for commands..."));
  Serial.println(F(""));
}

void loop() {
  // Check for IR signal received on D4
  if (IrReceiver.decode()) {
    Serial.println(F("\n>>> IR Signal Received on D4! <<<"));
    Serial.print(F("Protocol: NEC"));
    Serial.print(F(", Address: 0x"));
    Serial.print(IrReceiver.decodedIRData.address, HEX);
    Serial.print(F(", Command: 0x"));
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    // Resume receiver
    IrReceiver.resume();
  }

  // Check for serial input
  if (Serial.available() > 0) {
    char cmd = Serial.read();

    switch (cmd) {
      case '0': {
        Serial.println(F("\n>>> Sending Light TOGGLE (ON/OFF)..."));
        IrSender.sendNEC(IR_ADDRESS, IR_COMMAND_TOGGLE, 1);
        Serial.println(F("✓ IR signal sent"));
        blinkLED();
        break;
      }

      case '8': {
        Serial.println(F("\n>>> Sending Brightness UP..."));
        IrSender.sendNEC(IR_ADDRESS, IR_COMMAND_BRIGHTNESS_UP, 1);
        Serial.println(F("✓ IR signal sent"));
        blinkLED();
        break;
      }

      case '9': {
        Serial.println(F("\n>>> Sending Brightness DOWN..."));
        IrSender.sendNEC(IR_ADDRESS, IR_COMMAND_BRIGHTNESS_DOWN, 1);
        Serial.println(F("✓ IR signal sent"));
        blinkLED();
        break;
      }

      case '3': {
        Serial.println(F("\n>>> Sending Night Light..."));
        IrSender.sendNEC(IR_ADDRESS, IR_COMMAND_NIGHT_LIGHT, 1);
        Serial.println(F("✓ IR signal sent"));
        blinkLED();
        break;
      }

      case '2': {
        Serial.println(F("\n>>> Sending Full Bright..."));
        IrSender.sendNEC(IR_ADDRESS, IR_COMMAND_FULL_BRIGHT, 1);
        Serial.println(F("✓ IR signal sent"));
        blinkLED();
        break;
      }

      case 'c': {
        Serial.println(F("\n>>> Sending CH Set + Light TOGGLE..."));
        Serial.println(F("Step 1: CH Setting (0x205)..."));
        IrSender.sendNEC(IR_ADDRESS, 0x205, 1);  // CH setting
        Serial.println(F("✓ CH setting sent"));
        blinkLED();

        delay(100);  // Wait for processing

        Serial.println(F("Step 2: Light Toggle (0x207)..."));
        IrSender.sendNEC(IR_ADDRESS, IR_COMMAND_TOGGLE, 1);
        Serial.println(F("✓ Light toggle sent"));
        blinkLED();

        Serial.println(F("\nIf light toggles, CH setup is working!"));
        break;
      }

      case 'r': {
        Serial.println(F("\n--- Received Signal Information ---"));
        Serial.println(F("If a signal was received, it appears above."));
        Serial.println(F("Point your remote at D4 and press a button."));
        break;
      }

      case '?': {
        Serial.println(F("\n=== IR Send & Receive Test Commands ==="));
        Serial.println(F("  '0' - Send Light Toggle (ON/OFF)"));
        Serial.println(F("  '8' - Send Brightness UP"));
        Serial.println(F("  '9' - Send Brightness DOWN"));
        Serial.println(F("  '3' - Send Night Light"));
        Serial.println(F("  '2' - Send Full Bright"));
        Serial.println(F("  'r' - Show received signals"));
        Serial.println(F("  '?'  - Show help"));
        Serial.println(F(""));
        break;
      }

      default: {
        if (cmd >= 32 && cmd <= 126) { // Printable character
          Serial.print(F("\n? Unknown command: "));
          Serial.print(cmd);
          Serial.println(F(" (type '?' for help)"));
        }
        break;
      }
    }

    delay(50);
  }

  delay(50);
}

void blinkLED() {
  digitalWrite(FEEDBACK_LED_PIN, HIGH);
  delay(100);
  digitalWrite(FEEDBACK_LED_PIN, LOW);
  delay(100);
  digitalWrite(FEEDBACK_LED_PIN, HIGH);
  delay(100);
  digitalWrite(FEEDBACK_LED_PIN, LOW);
}
