# Arduino Nano ESP32 Vision AI カメラ

[English](README.md) | [日本語](README.ja.md)

## 概要

室内の行動・骨格を観測する、制作中の分散型カメラシステムです。Raspberry Pi 5 は解析とバックエンド連携、Arduino Nano ESP32 はセンサ集約と雲台制御を担当します。映像は録画せず、数値メタデータを BigQuery に保存する計画です。

## 部品表

### SBC

| 部品 | 数量 | 用途・備考 |
| ------------------------------ | ---- | --------------------------------------------------- |
| [Raspberry Pi 5 (16GB)](https://amzn.to/4sqqta4) | 1 | 映像解析と物体検知。 |

### MCU

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------------------------------------- | ---- | ------------------------------------------------------------------------ |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1 | センサとパン・チルト雲台を制御。 |
| [USB-C ケーブル](https://amzn.to/4kmNVTn) | 1 | Nano ESP32 の書き込み・給電用。 |
| [AC/DC Adapter (5V/4A)]() | 1 | コンセントから安定した電源を供給。 |

### カメラ

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------------------------------------- | ---- | ------------------------------------------------------------------------ |
| [Grove - Vision AI Module V2](https://amzn.to/41Mx9Vs) | 1 | AI 画像認識とカメラ制御。 |
| [OV5647-62 FOV Camera Module](https://amzn.to/41IEmWF) | 1 | 映像を入力。Vision AI モジュールに直接接続。 |
| Grove Cable |  | Grove Vision AI Module V2 に付属する想定。 |
| [Grove Shield for Arduino Nano](https://amzn.to/3UnUJnH) | 1 | Grove センサを Nano にはんだ付けなしで接続。 |
| [Pan Tilt Platform for Raspberry Pi & Nvidia Jetson Cameras](https://amzn.to/3OeokzX) | 1 | モータでカメラのパン・チルトを制御。 |

## 開発

### ハードウェア開発

#### スコープとハードウェア

Phase 1 は Arduino 側の「目」を優先します。OV5647-62 カメラを接続した Vision AI Module V2、PCA9685 経由の B0283 パン・チルトサーボ、Grove TSL2561 照度センサを使用します。検知結果とセンサ情報を JSON で Pi へ送信します。通信は UDP・Wi-Fi またはシリアルです。サーボは外部 5V/4A 電源を使用し、GND を共通にします。

Phase 2 では受信したメタデータに MediaPipe Pose の 33 点骨格と行動ラベルを付け、FastAPI（Motion Studio Backend）へ POST してから BigQuery へ保存します。Speech Recognizer・ReSpeaker による音声入力は将来追加で、初期スコープ外です。

### ソフトウェア開発

#### データと開発計画

`timestamp` はミリ秒精度の ISO 8601、`target_type` は `person`・`airplane`・`none`、`skeleton_3d` は 33 点の座標（人物以外では NULL 可）とします。`action_label`、`lux` と NULL または省略可能な `voice_command` を持つ `environmental_data`、`pan`・`tilt` を持つ `servo_angles` を含めます。

ハードウェアを組み立て、非ブロッキングの検知・追跡・照度取得を実装し、通信と例外処理を確認します。Pi の受信検証後に解析とバックエンド連携へ進みます。[照明データ](../../../cloud/Cloud_Functions/Smart_Lighting_Control_Data_Pipeline/README.ja.md)と統合する場合はデバイス ID と時刻を揃えます。

ここにはファームウェアと Pi 受信コードは未収録です。段階的な計画の詳細は[作品の制約](AGENTS.md)を参照してください。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
