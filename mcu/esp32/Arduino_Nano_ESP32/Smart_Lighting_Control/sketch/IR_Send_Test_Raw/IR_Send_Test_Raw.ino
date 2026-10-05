/*
 * IR Send Test - Raw Data (Wave Form Copy)
 * Arduino Nano ESP32
 *
 * Purpose: Test sending the exact infrared waveform captured from physical remote
 *
 * 使い方:
 * 1. このスケッチをボードに書き込む
 * 2. シリアルモニタを開く (115200 baud)
 * 3. シリアルモニタに入力:
 *    - 's' : Send raw ON/OFF signal once
 *    - 'c' : Send 5 times continuously (test reliability)
 *    - 'h' : Show help menu
 * 4. 赤外線受信機（スマートフォンカメラ）で確認
 *    または、ライトがリモコンと同じように動作するか確認
 */

#include <Arduino.h>

// Define IR protocol before including IRremote
#define DECODE_NEC
#include <IRremote.hpp>

// ============================================
// Pin Definitions
// ============================================
#define IR_EMITTER_PIN D2   // Grove - Infrared Emitter (D2)
#define IR_RECEIVER_PIN D4  // Grove - Infrared Receiver (D4)

// ============================================
// Raw IR Data (Cloned from Physical Remote)
// ============================================
// This is the exact infrared waveform captured from the ceiling light remote's ON/OFF button
// Device: Iris Ohyama Ceiling Light (ACL-DGR remote)
// Protocol: Onkyo (as detected by IRremote)
// Captured: 2026-01-31
const uint16_t rawDataON_OFF[] PROGMEM = {
  8950, 4500,
  550, 1650, 550, 550, 550, 1650, 550, 550,
  550, 1650, 550, 1650, 550, 1700, 500, 600,
  550, 550, 550, 1650, 550, 550, 550, 550,
  550, 1650, 550, 550, 550, 550, 550, 600,
  500, 1700, 550, 1650, 550, 1650, 550, 550,
  550, 550, 550, 550, 550, 550, 550, 550,
  550, 1700, 550, 1650, 550, 550, 550, 550,
  550, 550, 550, 550, 550, 600, 500, 550,
  600
};
#define RAW_DATA_LENGTH (sizeof(rawDataON_OFF) / sizeof(rawDataON_OFF[0]))

// ============================================
// System State
// ============================================
unsigned long lastSendTime = 0;
const unsigned long MIN_SEND_INTERVAL = 500; // Minimum interval between sends (ms)

// ============================================
// Function Prototypes
// ============================================
void sendRawSignal();
void sendRawSignalContinuous(int count);
void printMenu();
void printRawData();

// ============================================
// Setup
// ============================================
void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial connection
  delay(500);

  Serial.println();
  Serial.println(F("========================================"));
  Serial.println(F("IR Send Test - Raw Data (Wave Form)"));
  Serial.println(F("Arduino Nano ESP32"));
  Serial.println(F("========================================\n"));

  // Initialize IR sender
  IrSender.begin(IR_EMITTER_PIN);

  Serial.println(F("IR Emitter initialized on pin D2"));
  Serial.println(F("IR Receiver on pin D4 for feedback\n"));

  Serial.println(F("Raw Data Information:"));
  Serial.print(F("  Data length: "));
  Serial.print(RAW_DATA_LENGTH);
  Serial.println(F(" timings"));
  Serial.println(F("  Frequency: 38 kHz (standard IR)"));
  Serial.println(F("  Source: Physical remote ON/OFF button\n"));

  printMenu();
}

// ============================================
// Main Loop
// ============================================
void loop() {
  // Check for serial input
  if (Serial.available() > 0) {
    char command = Serial.read();

    // Skip whitespace
    if (command == '\n' || command == '\r') {
      return;
    }

    Serial.println();
    Serial.print(F("Command: "));
    Serial.println(command);

    switch (command) {
      case 's':
      case 'S':
        sendRawSignal();
        break;

      case 'c':
      case 'C':
        sendRawSignalContinuous(5);
        break;

      case 'h':
      case 'H':
      case '?':
        printMenu();
        break;

      case 'd':
      case 'D':
        printRawData();
        break;

      default:
        Serial.println(F("Unknown command. Type 'h' for help."));
        break;
    }

    Serial.println();
  }
}

// ============================================
// IR Send Functions
// ============================================

void sendRawSignal() {
  // Safety: prevent sending too frequently
  if (millis() - lastSendTime < MIN_SEND_INTERVAL) {
    Serial.println(F("⚠ Wait before sending again"));
    return;
  }

  Serial.println(F("\n>>> Sending raw IR signal..."));

  // Send the exact waveform from the physical remote
  IrSender.sendRaw(rawDataON_OFF, RAW_DATA_LENGTH, 38);

  Serial.println(F("✓ Raw signal sent successfully!"));
  Serial.print(F("  - Waveform length: "));
  Serial.print(RAW_DATA_LENGTH);
  Serial.println(F(" timings"));
  Serial.println(F("  - Frequency: 38 kHz"));
  Serial.println(F("  - Duration: ~63 ms"));
  Serial.println(F("\n📝 Note: If light didn't respond, check:"));
  Serial.println(F("   1. IR receiver alignment with light"));
  Serial.println(F("   2. D2 pin LED blinking (check with phone camera)"));
  Serial.println(F("   3. Light's IR receiver sensitivity\n"));

  lastSendTime = millis();
}

void sendRawSignalContinuous(int count) {
  Serial.println();
  Serial.print(F(">>> Sending "));
  Serial.print(count);
  Serial.println(F(" continuous signals (reliability test)...\n"));

  for (int i = 1; i <= count; i++) {
    Serial.print(F("  ["));
    Serial.print(i);
    Serial.print(F("/"));
    Serial.print(count);
    Serial.print(F("] Sending... "));

    IrSender.sendRaw(rawDataON_OFF, RAW_DATA_LENGTH, 38);

    Serial.println(F("OK"));

    // Delay between sends (prevent receiver saturation)
    if (i < count) {
      delay(500);
    }
  }

  Serial.println(F("\n✓ All signals sent!"));
  Serial.println(F("  Expected behavior: Light should toggle ON/OFF"));
  Serial.println(F("  (Odd number = one state, Even number = opposite state)\n"));

  lastSendTime = millis();
}

// ============================================
// Utility Functions
// ============================================

void printMenu() {
  Serial.println(F("========================================"));
  Serial.println(F("Commands:"));
  Serial.println(F("  s - Send raw signal ONCE"));
  Serial.println(F("  c - Send raw signal 5 times (continuous)"));
  Serial.println(F("  d - Display raw data array"));
  Serial.println(F("  h - Show this help menu"));
  Serial.println(F("========================================\n"));
}

void printRawData() {
  Serial.println(F("Raw IR Data Array:"));
  Serial.println(F("const uint16_t rawDataON_OFF[] PROGMEM = {"));

  // Print data in a readable format
  for (uint16_t i = 0; i < RAW_DATA_LENGTH; i++) {
    if (i > 0) Serial.print(F(", "));

    // 10 values per line
    if (i > 0 && i % 10 == 0) {
      Serial.println();
    }

    // Read from PROGMEM
    uint16_t value = pgm_read_word(&rawDataON_OFF[i]);
    Serial.print(value);
  }

  Serial.println(F("\n};"));
  Serial.println();
}
