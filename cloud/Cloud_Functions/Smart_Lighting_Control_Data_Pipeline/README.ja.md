# 照明データパイプライン

[English](README.md) | [日本語](README.ja.md)

## 概要

Shiftr.io 経由で照明テレメトリを受信し、選択したフィールドを BigQuery に保存します。[Nano ESP32 側](../../../mcu/esp32/Arduino_Nano_ESP32/Smart_Lighting_Control/README.ja.md)は照度を Adafruit IO にも送信します。

## 部品表

このプロジェクトに専用の電子部品は不要です。必要なサービスと依存関係はソフトウェア開発を参照してください。

## 開発

### ハードウェア開発

専用のハードウェア設定はありません。

### ソフトウェア開発

#### 作品固有の設定

- デプロイ名・エントリーポイント：`save_lighting_data`、説明上のランタイム：`python311`。
- データセット・テーブル：`diy_electronics_iot.lighting_data`。
- 依存関係：[requirements.txt](requirements.txt)、実装：[main.py](main.py)。
- デバイスの `config.h` にある実際の `SHIFTR_TOPIC` と webhook を一致させます。気象作品の `wio/json` をそのままコピーしないでください。

環境準備、デプロイ、ログ、webhook 設定は共通のクラウドガイドを参照してください。既存の例は公開 HTTP エンドポイントを使用します。

#### データ変換とスキーマ

関数は `lux` を `light_level`、`light_state` を `status` に変換します。Unix の `timestamp` があれば UTC に変換し、なければ現在の UTC 時刻を使います。`device_id` の既定値は `unknown_device`、照度は 0、状態は `UNKNOWN` です。入力の `task_executed`、`wifi_connected`、`retry_count` は現在の関数では保存しません。

```sql
CREATE SCHEMA IF NOT EXISTS `YOUR_GCP_PROJECT_ID.diy_electronics_iot`;
CREATE TABLE IF NOT EXISTS `YOUR_GCP_PROJECT_ID.diy_electronics_iot.lighting_data` (
  timestamp TIMESTAMP NOT NULL,
  device_id STRING,
  light_level INTEGER,
  status STRING
)
PARTITION BY DATE(timestamp);
```

### テスト

#### ローカル・デプロイ後のテスト

書き込みを省略する場合は `LOCAL_TEST_MODE=true` を設定し、`save_lighting_data` を指定して Functions Framework を起動します。以下を送信します。

```sh
curl -X POST http://localhost:8080 \
  -H "Content-Type: application/json" \
  -d '{"device_id":"arduino_nano_esp32","timestamp":1769926200,"lux":2367,"light_state":"ON","task_executed":false,"wifi_connected":true,"retry_count":0}'
```

ローカルモードは `status: success`、`Data received (test mode)`、変換後の行を返します。実際の書き込みテストでは URL をデプロイ後のトリガー URL に置き換えます。成功すると `Data inserted successfully` が返ります。

```sql
SELECT timestamp, device_id, light_level, status
FROM `YOUR_GCP_PROJECT_ID.diy_electronics_iot.lighting_data`
ORDER BY timestamp DESC
LIMIT 10;
```

## 参考資料

### 共通ガイド

- [Cloud Functions 共通手順](../../../docs/cloud-functions.ja.md)
- [認証情報の設定](../../../docs/credentials.ja.md)
- [Adafruit IO の設定](../../../docs/adafruit-io.ja.md)

- [Cloud Functions ドキュメント](https://cloud.google.com/functions/docs)
- [BigQuery ドキュメント](https://cloud.google.com/bigquery/docs)
- [Shiftr.io ドキュメント](https://www.shiftr.io/docs/)
- [MQTT プロトコル概要](https://mqtt.org/)
- [Arduino Nano ESP32 Smart Lighting Control](../../../mcu/esp32/Arduino_Nano_ESP32/Smart_Lighting_Control)
- [Arduino Nano ESP32 Smart Lighting Control](../../../mcu/esp32/Arduino_Nano_ESP32/Smart_Lighting_Control) - Hardware sketch and sensors
- [Wio Terminal Weather Station](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2) - Similar IoT data pipeline example

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
