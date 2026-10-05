# Wio Terminal 気象ステーション v2

[English](README.md) | [日本語](README.ja.md)

## 概要

気象ステーション v2 は I2C 接続の Grove BME280 で温度・湿度・気圧を測定します。320×240 の LCD は横向きの回転設定 3、均等な 3 分割、読みやすさに合わせた FMB18 表示を使用します。Adafruit IO と、Shiftr.io・Cloud Functions 経由の BigQuery に送信し、バッテリーベースと Wi-Fi・MQTT 自動再接続に対応します。

## 部品表

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------------ | ---- | ---------------------------------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu) | 1 | 制御部、ディスプレイ、Wi-Fi モジュール。 |
| [Grove BME280 Environmental Sensor](https://amzn.to/4qcfIY1) | 1 | **v2 で追加**：温度・湿度・気圧を測定（I2C）。 |
| USB Type-C ケーブル | 1 | 給電・書き込み用。データ通信対応ケーブルが必要。 |
| **バッテリーベース（任意）** | 1 | USB 電源なしで独立動作。 |

## 開発

### ハードウェア開発

#### ハードウェアとファームウェア

BME280 を Wio Terminal の I2C ポート（VCC 3.3V、GND、SCL、SDA）へ接続します。データ通信・給電には USB-C、独立動作には任意のバッテリーベースを使います。

`Seeed BME280`、`PubSubClient`、`ArduinoJson` と Wio 対応の `TFT_eSPI` 設定を使用します。[スケッチ](sketch/Weather_Station_v2/Weather_Station_v2.ino)と同じ場所の認証情報サンプルで Wi-Fi、`AIO_USERNAME`、`AIO_KEY`、`SHIFTR_KEY`、`SHIFTR_SECRET` を設定します。書き込み後は 115200 baud で両 MQTT 接続のメッセージを確認します。

### ソフトウェア開発

#### クラウド連携

Adafruit IO は `temperature`（°C）、`humidity`（%RH）、`pressure`（hPa）を使用し、説明上の更新間隔は 60 秒です。ゲージの目安は 15〜30°C、30〜80%RH、950〜1050 hPa です。必要に応じて 24 時間の折れ線グラフを追加します。

BigQuery への経路は Wio Terminal → Shiftr.io の `wio/json` → `save_weather_data` → `diy_electronics_iot.weather_data` です。NULL を許容する `pressure` を含むスキーマは[気象データパイプライン](../../../../../cloud/Cloud_Functions/Weather_Station_Data_Pipeline/README.ja.md)を参照してください。[v1](../Weather_Station_v1/README.ja.md) は DHT11 を使用し、気圧は測定しません。

### テスト

#### テストと分析

LCD の 3 領域、センサ値、フィード更新、保存された気圧、再接続を確認します。以下は UTC の当日データを時間単位で集計するクエリで、直近 24 時間の移動窓ではありません。

```sql
SELECT
  TIMESTAMP_TRUNC(timestamp, HOUR) AS hour,
  ROUND(AVG(temperature), 2) AS avg_temperature,
  ROUND(AVG(pressure), 1) AS avg_pressure,
  COUNT(*) AS sample_count
FROM `PROJECT_ID.diy_electronics_iot.weather_data`
WHERE DATE(timestamp) = CURRENT_DATE()
GROUP BY hour
ORDER BY hour DESC;
```

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../../docs/arduino-development.ja.md)
- [認証情報の設定](../../../../../docs/credentials.ja.md)
- [Adafruit IO の設定](../../../../../docs/adafruit-io.ja.md)
- [Cloud Functions 共通手順](../../../../../docs/cloud-functions.ja.md)

- [Wio Terminal ドキュメント](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
- [BME280 データシート](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/)
- [Adafruit IO ドキュメント](https://io.adafruit.com/api/docs/)
- [Shiftr.io ドキュメント](https://www.shiftr.io/docs/)
- **[v1 Weather Station](../Weather_Station_v1/README.ja.md)** - Original DHT11 version

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
