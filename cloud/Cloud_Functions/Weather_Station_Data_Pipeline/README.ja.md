# 気象データパイプライン

[English](README.md) | [日本語](README.ja.md)

## 概要

Wio Terminal から Shiftr.io の webhook 経由で JSON を受信し、温度・湿度・任意の気圧を BigQuery に保存します。DHT11・v1 には気圧がなく、BME280・v2 は気圧を送信します。

## 部品表

このプロジェクトに専用の電子部品は不要です。必要なサービスと依存関係はソフトウェア開発を参照してください。

## 開発

### ハードウェア開発

専用のハードウェア設定はありません。

### ソフトウェア開発

#### 作品固有の設定

- デプロイ名：`save-weather-data`、エントリーポイント：`save_weather_data`、説明上のランタイム：`python312`。
- データセット・テーブル：`diy_electronics_iot.weather_data`。
- デバイストピック：`wio/json`（対象ファームウェアと一致させます）。
- 依存関係：[requirements.txt](requirements.txt)、実装：[main.py](main.py)。
- ハードウェア：[気象ステーション v1](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v1/README.ja.md) または [v2](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2/README.ja.md)。

環境準備、デプロイ、ログ、webhook 設定は共通のクラウドガイドを参照してください。デプロイ時の実際のトリガー URL を webhook に設定します。既存のデプロイ例は公開 HTTP 呼び出しを使用します。

#### BigQuery スキーマ

関数が現在の UTC 時刻を生成します。気圧がない場合は NULL を保存します。DHT11 の場合も、テーブルは `pressure` フィールドを受け入れる必要があります。

```sql
CREATE SCHEMA IF NOT EXISTS `YOUR_GCP_PROJECT_ID.diy_electronics_iot`;
CREATE TABLE IF NOT EXISTS `YOUR_GCP_PROJECT_ID.diy_electronics_iot.weather_data` (
  timestamp TIMESTAMP NOT NULL,
  device_id STRING,
  temperature FLOAT64,
  humidity FLOAT64,
  pressure FLOAT64
)
PARTITION BY DATE(timestamp);
```

### テスト

#### ローカル・デプロイ後のテスト

依存関係の導入後、`python test_local.py` を実行します。ローカルテストモードを使用し、BigQuery には書き込みません。HTTP サーバで書き込みを省略する場合は `LOCAL_TEST_MODE=true` を設定して、`save_weather_data` を指定した Functions Framework を起動します。

```sh
curl -X POST http://localhost:8080 \
  -H "Content-Type: application/json" \
  -d '{"device_id":"wio_terminal","temperature":22.5,"humidity":55.0,"pressure":1013.2}'
```

ローカルテストモードは `status: success` と変換後の行を含む JSON を返します。デプロイ後はローカル URL を実際のトリガー URL に置き換えます。データベース書き込みに成功すると HTTP 200 と `Success` が返ります。

```sql
SELECT timestamp, device_id, temperature, humidity, pressure
FROM `YOUR_GCP_PROJECT_ID.diy_electronics_iot.weather_data`
ORDER BY timestamp DESC
LIMIT 10;
```

## 参考資料

### 共通ガイド

- [Cloud Functions 共通手順](../../../docs/cloud-functions.ja.md)
- [認証情報の設定](../../../docs/credentials.ja.md)

- [Cloud Functions ドキュメント](https://cloud.google.com/functions/docs)
- [BigQuery ドキュメント](https://cloud.google.com/bigquery/docs)
- [Shiftr.io ドキュメント](https://www.shiftr.io/docs/)
- [MQTT プロトコル概要](https://mqtt.org/)
- [Wio Terminal Weather Station](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2)
- [Wio Terminal Weather Station](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2) - Hardware sketch and sensors

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
