// 定数: ボタンを接続するピン番号
const int buttonPin = 2; // D2ピン

void setup() {
  // PCとの通信を開始 (通信速度: 9600 bps)
  Serial.begin(9600);
  
  // ボタンを接続するピンを入力モードに設定し、内部プルアップ抵抗を有効にする
  pinMode(buttonPin, INPUT_PULLUP);
  
  Serial.println("ボタンテストを開始します。ボタンを押してください。");
}

void loop() {
  // ボタンの状態を読み取る
  int buttonState = digitalRead(buttonPin);
  
  // もしボタンが押されていたら (INPUT_PULLUPなので、押されるとLOWになる)
  if (buttonState == LOW) {
    Serial.println("ボタンが押されました！");
    
    // 短いチャタリング（連続反応）防止のための待ち時間
    delay(200); 
  }
}