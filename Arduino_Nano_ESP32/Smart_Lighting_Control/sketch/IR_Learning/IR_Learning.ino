/*
 * IR Learning Sketch - Capture raw IR signals for cloning
 * Purpose: Record physical remote's infrared pattern and output as copyable raw data
 *
 * 使い方:
 * 1. IDE: Tools > Upload Speed を「115200」に設定
 * 2. この sketch をアップロード
 * 3. Tools > Serial Monitor を開く (ボーレート 115200)
 * 4. リモコンのボタンをIRレシーバー（D4）に向けて短く1回だけ押す
 * 5. シリアルモニタに rawData 配列が出力される
 * 6. その配列をコピーして SmartLightingControl.ino にペースト
 *
 * Hardware:
 * - Arduino Nano ESP32
 * - Grove Infrared Receiver on Pin D4
 * - Baud Rate: 115200
 */

#include <Arduino.h>

// Protocol decoders - enable all to capture any remote
#define DECODE_NEC
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

// IR Receiver Pin
#define IR_RECEIVER_PIN D4

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial connection
  delay(500);

  Serial.println(F("\n========================================"));
  Serial.println(F("  IR Learning - Raw Data Capture v2.0"));
  Serial.println(F("========================================\n"));

  // Initialize IR receiver
  IrReceiver.begin(IR_RECEIVER_PIN, ENABLE_LED_FEEDBACK);

  Serial.println(F("IR Receiver: D4 (115200 baud)"));
  Serial.println(F("Ready to learn from remote!\n"));
  Serial.println(F("Instructions:"));
  Serial.println(F("1. Point remote at receiver (D4)"));
  Serial.println(F("2. Press button ONCE (short press, ~0.5 second)"));
  Serial.println(F("3. Raw data array will be printed"));
  Serial.println(F("4. Copy the array to SmartLightingControl.ino\n"));
  Serial.println(F("========================================\n"));
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.println(F("\n>>> RAW IR DATA CAPTURED <<<\n"));

    // Display decoded info first
    Serial.print(F("Protocol: "));
    Serial.println(getProtocolString(IrReceiver.decodedIRData.protocol));

    Serial.print(F("Address: 0x"));
    Serial.println(IrReceiver.decodedIRData.address, HEX);

    Serial.print(F("Command: 0x"));
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    Serial.print(F("Bits: "));
    Serial.println(IrReceiver.decodedIRData.numberOfBits);

    // ===== CRITICAL: Extract and output raw data in array format =====
    Serial.println(F("\n// ===== COPY THIS RAW DATA ARRAY ====="));
    Serial.println(F("uint16_t rawData[] = {"));

    // IRremote v4.5.0 stores raw timing data in the internal buffer
    // Use printIRResultRawFormatted which outputs: +8950,-4450 + 550,-1700 ...
    // We'll capture this and convert to array format

    Serial.println(F("// Raw data from IR signal:"));
    IrReceiver.printIRResultRawFormatted(&Serial, true);

    Serial.println(F("};"));
    Serial.println(F("// ===== END OF RAW DATA =====\n"));
    Serial.println(F("// NOTE: If the above shows +XXXX,-YYYY format, manually convert to:"));
    Serial.println(F("// uint16_t rawData[] = { XXXX, YYYY, ... };  (remove signs, use absolute values)\n"));

    Serial.println(F("\n========================================"));
    Serial.println(F("Ready for next signal...\n"));

    // Resume for next signal
    IrReceiver.resume();
  }
}
