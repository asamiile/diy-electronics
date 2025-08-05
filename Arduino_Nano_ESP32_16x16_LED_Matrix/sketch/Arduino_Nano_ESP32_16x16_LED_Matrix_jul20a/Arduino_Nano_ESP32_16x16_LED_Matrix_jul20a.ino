#include <Adafruit_NeoPixel.h>

// --- Pin Definitions ---
const int LED_PIN    = 6; // LEDマトリクスのDINピン
const int BUTTON_PIN = 2; // タクトスイッチのピン

// --- Matrix Settings ---
const int LED_COUNT = 256; // 16x16 = 256個のLED

// NeoPixelオブジェクトを作成
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- State Variables ---
bool isMatrixOn = false;      // LEDが点灯しているかどうかの状態を保存 (最初はOFF)
bool lastButtonState = HIGH;  // 前回のボタンの状態を保存

void setup() {
// デバッグ用にシリアル通信を開始
Serial.begin(115200);

// ボタンピンを内部プルアップ付き入力モードに設定
pinMode(BUTTON_PIN, INPUT_PULLUP);

// NeoPixelライブラリを初期化
strip.begin();
strip.setBrightness(40); // 明るさを設定 (最初は低めが安全です)
strip.clear();           // 全てのLEDを消灯
strip.show();            // マトリクスに反映
}

void loop() {
// 現在のボタンの状態を読み取る
bool currentButtonState = digitalRead(BUTTON_PIN);

// ボタンが「押された瞬間」（前回HIGH -> 今回LOW）を検出
if (lastButtonState == HIGH && currentButtonState == LOW) {
  // isMatrixOnの状態を反転させる (true -> false, false -> true)
isMatrixOn = !isMatrixOn;
delay(50); // 簡単なチャタリング防止

// 新しい状態に基づいてマトリクスを更新
if (isMatrixOn) {
// もしONにするなら、マトリクスを白色で塗りつぶす
Serial.println("Matrix ON");
strip.fill(strip.Color(150, 150, 150)); // 明るすぎない白
} else {
// もしOFFにするなら、マトリクスを消灯する
Serial.println("Matrix OFF");
strip.clear();
}

// 変更をマトリクスに反映させる
strip.show();
}

// 今回のボタンの状態を「前回の状態」として保存する
lastButtonState = currentButtonState;
}