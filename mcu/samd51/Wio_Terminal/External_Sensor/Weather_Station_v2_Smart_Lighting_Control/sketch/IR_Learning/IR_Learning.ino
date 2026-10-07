#include <Arduino.h>
#define RAW_BUFFER_LENGTH 300
#include <IRremote.hpp>

constexpr uint8_t RECEIVER_PIN = D4; // Chassis Grove D4/A4 (D5/A5)

void setup() {
  Serial.begin(115200);
  // バッテリー起動でも無期限に待たない。
  IrReceiver.begin(RECEIVER_PIN, DISABLE_LED_FEEDBACK);
}

void loop() {
  if (!IrReceiver.decode()) return;
  IrReceiver.printIRResultShort(&Serial);
  if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
    Serial.println("[IR] Buffer overflow: increase RAW_BUFFER_LENGTH");
  } else if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
    // 先頭の待機時間を除き、mark/space補正済みのus配列を出力する。
    IrReceiver.compensateAndPrintIRResultAsCArray(&Serial, true);
  }
  IrReceiver.resume();
}
