#include <Adafruit_NeoPixel.h>

#define LED_PIN    6    // ArduinoのD6ピンに接続
#define LED_COUNT 256   // LEDの数 (16x16 = 256)

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();           // NeoPixelライブラリを初期化
  strip.show();            // すべてのLEDをオフの状態で初期化
  strip.setBrightness(50); // 明るさを設定 (最初は低めに設定すると安全です)
}

void loop() {
  // 最初のLED (0番目) を赤色で点灯させます
  strip.setPixelColor(0, strip.Color(255, 0, 0)); // R, G, B
  strip.show(); // LEDにデータを送信して点灯
  delay(1000); // 1秒待つ

  // 最初のLEDを消灯
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();
  delay(1000);
}