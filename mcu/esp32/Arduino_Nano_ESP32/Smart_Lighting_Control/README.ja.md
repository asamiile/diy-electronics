# Arduino Nano ESP32 照明の自動制御

[English](README.md) | [日本語](README.ja.md)

## 概要

NTP で日本標準時に同期し、指定時刻に赤外線で照明を制御します。Grove 照度センサによる結果確認、赤外線コードの学習、Wi-Fi 再接続、Adafruit IO と Shiftr.io への MQTT 送信に対応します。

## Wio Terminalへの統合

Chassis Battery付きWio Terminal 1台で気象観測と照明制御を行う場合は、[Wio Terminal統合版](../../../samd51/Wio_Terminal/External_Sensor/Weather_Station_v2_Smart_Lighting_Control/README.ja.md)を参照してください。Wio専用の配線・コード・変更する設定を記載しています。照度のしきい値はWioで再調整します。Nano用コードは単独構成向けに残しています。

## 部品表

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------------------------------------ | ---- | ----------------------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/4apayDa) | 1 | Wi-Fi 対応の制御用マイコン。 |
| [Grove Shield for Arduino Nano](https://amzn.to/49TrG40) | 1 | Grove センサ接続用の拡張シールド。 |
| [Grove - Infrared Emitter](https://amzn.to/4rt9Tqi) | 1 | 照明制御の赤外線を送信（デジタル D2）。 |
| [Grove - Infrared Receiver](https://jp.seeedstudio.com/Grove-Infrared-Receiver.html) | 1 | 学習用の赤外線を受信（デジタル D4）。 |
| [Grove - Light Sensor v1.2](https://amzn.to/4rsvrTV) | 1 | 動作結果の確認用に照度を測定（アナログ A0）。 |
| USB Type-C ケーブル | 1 | 給電・書き込み用。 |

## 開発

### ハードウェア開発

#### ハードウェアの接続

Grove Shield を取り付け、赤外線送信器を D2、受信器を D4、照度センサを A0（D6 と表示された Grove アナログポート）へ接続します。Nano の電源と書き込みには USB-C を使います。

### ソフトウェア開発

#### ファームウェアの設定

Arduino ESP32 Boards コアと `IRremote` を使用します。MQTT などの依存関係は実際のスケッチの include に従ってください。`sketch/Smart_Lighting_Control/` の認証情報サンプルをコピーし、Wi-Fi とサービスの認証情報を設定します。NTP、タイムゾーン、時刻、波形データ、しきい値は `config.h` で設定します。

`sketch/IR_Learning/IR_Learning.ino` を使い、115200 baud のシリアルモニタで照明リモコンの ON/OFF 信号を学習します。リモコンを受信器へ向け、出力された raw 配列全体を `rawDataON_OFF[]` へコピーします。`RAW_DATA_LENGTH` を確認し、`IR_Send_Test_Raw.ino` で検証します。`s` は 1 回送信、`c` は 5 回送信、`d` はデータ表示です。照度の読み取り値から部屋に合う `LIGHT_OFF_THRESHOLD` を決めます。元の説明の 25〜35 は調整開始時の目安で、共通のしきい値ではありません。

`SCHEDULED_OFF_HOUR` と `SCHEDULED_OFF_MINUTE` を設定して[主スケッチ](sketch/Smart_Lighting_Control/Smart_Lighting_Control.ino)を書き込みます。別の機器の信号取得には `IR_Receiver_Raw_Data_Test.ino`、NEC/Onkyo の送信テストには `IR_Send_Test.ino` を使います。各スケッチの役割は下表を参照してください。

#### クラウド連携と検証

Adafruit IO は照度を受信し、[照明データパイプライン](../../../../cloud/Cloud_Functions/Smart_Lighting_Control_Data_Pipeline/README.ja.md)は Shiftr.io 経由で選択されたテレメトリを BigQuery に保存します。別作品のトピックをコピーせず、`config.h` と webhook のトピックを照合してください。NTP 時刻、赤外線動作、照度フィードバック、予約制御、再接続をそれぞれ確認します。

#### 設定とスケッチの一覧

| 設定 | config.h の場所 | 変更内容 |
| --------------------- | ----------------------------------------------- | ------------------------------------------------------------------------------------------------------ |
| **波形データ** | `rawDataON_OFF[]` 配列 | 使用するリモコンの ON/OFF ボタンから学習したデータに置き換える。 |
| **データ長** | `RAW_DATA_LENGTH` マクロ | 自動計算されるが、取得したデータ長との一致を確認する。 |
| **照度しきい値** | `LIGHT_OFF_THRESHOLD` 定数 | `IR_Send_Test_Raw.ino` のシリアル出力を確認し、部屋の明るさに合わせて調整する。 |
| **予約時刻** | `SCHEDULED_OFF_HOUR` and `SCHEDULED_OFF_MINUTE` | 自動消灯する時刻を設定する。 |

| スケッチ名 | 用途 | 使用場面 |
| --------------------------------- | ----------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| **Smart_Lighting_Control.ino** | 主制御スケッチ | 予約時刻と照度フィードバックによる通常の照明制御。 |
| **IR_Send_Test_Raw.ino** | 波形送信テスト | 現在のリモコン信号を確認（s：1 回送信、c：5 回連続、d：データ表示）。 |
| **IR_Send_Test.ino** | プロトコル送信と受信結果確認 | NEC・Onkyo のコマンドをテストし、新しい赤外線機器への対応を確認。 |
| **IR_Receiver_Raw_Data_Test.ino** | 赤外線波形の取得 | リモコンを受信器へ向けてボタンを押し、波形を学習。 |
| **IR_Learning.ino** | 波形の自動取得例 | 取得した赤外線信号の解析・表示例。 |

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)
- [認証情報の設定](../../../../docs/credentials.ja.md)
- [Adafruit IO の設定](../../../../docs/adafruit-io.ja.md)
- [Cloud Functions 共通手順](../../../../docs/cloud-functions.ja.md)

- [Arduino Nano ESP32 ドキュメント](https://docs.arduino.cc/hardware/nano-esp32/)
- [Arduino WiFi ドキュメント](https://docs.arduino.cc/libraries/wifi/)
- [IRremote ライブラリのドキュメント](https://github.com/Arduino-IRremote/Arduino-IRremote)
- [Grove - Light Sensor v1.2](https://wiki.seeedstudio.com/Grove-Light-Sensor/)
- [NTP Time Synchronization](https://docs.arduino.cc/libraries/time/)

## 作者

[Your Name](https://your-portfolio.com/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
