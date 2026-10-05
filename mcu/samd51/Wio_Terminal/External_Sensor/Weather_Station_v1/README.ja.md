# Wio Terminal 気象ステーション v1

[English](README.md) | [日本語](README.ja.md)

## 概要

Wio Terminal と DHT11 で温度・湿度を測定し、LCD に表示するとともに Adafruit IO と Shiftr.io へ送信します。JSON 形式のテレメトリ、バッテリーベースによる動作、Wi-Fi・MQTT 再接続に対応します。

### 画像・動画

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/76df73232223085.68984e3bc47f8.jpg)

## 部品表

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------------------------ | ---- | ---------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu) | 1 | 制御部、ディスプレイ、Wi-Fi モジュール。 |
| [Grove - Temperature & Humidity Sensor (DHT11)](https://amzn.to/3Um4qmA) | 1 | Grove ポートに接続（コードでは D0）。 |
| USB Type-C ケーブル | 1 | 給電・書き込み用。データ通信対応ケーブルが必要。 |
| **バッテリーベース（任意）** | 1 | USB 電源なしで独立動作。 |

## 開発

### ハードウェア開発

#### ハードウェアとファームウェア

Grove DHT11 を D0 に接続し、データ通信対応 USB-C ケーブルを使用します。バッテリーベースは任意です。Wio Terminal のボードパッケージと `DHT sensor library`、`Adafruit Unified Sensor`、`PubSubClient`、`ArduinoJson` を使用します。

[認証情報サンプル](sketch/Weather_Station/credentials.h.example)から Wi-Fi、Adafruit IO のユーザー名・キー、Shiftr.io のキー・シークレットを設定し、[スケッチ](sketch/Weather_Station/Weather_Station.ino)を書き込みます。

### ソフトウェア開発

#### クラウド連携とテスト

`temperature`・`humidity` フィードは [Adafruit IO 連携](with_Adafruit_IO/README.ja.md)を参照してください。BigQuery 保存には[気象データパイプライン](../../../../../cloud/Cloud_Functions/Weather_Station_Data_Pipeline/README.ja.md)を使用します。センサの値、LCD 表示、両 MQTT 接続、フィード更新、保存された行を確認します。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../../docs/arduino-development.ja.md)
- [認証情報の設定](../../../../../docs/credentials.ja.md)
- [Adafruit IO の設定](../../../../../docs/adafruit-io.ja.md)
- [Cloud Functions 共通手順](../../../../../docs/cloud-functions.ja.md)

- [Wio Terminal ドキュメント](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
- [DHT11 Sensor ガイド](https://www.adafruit.com/product/386)
- [Adafruit IO ドキュメント](https://io.adafruit.com/api/docs/)
- [Shiftr.io ドキュメント](https://www.shiftr.io/docs/)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
