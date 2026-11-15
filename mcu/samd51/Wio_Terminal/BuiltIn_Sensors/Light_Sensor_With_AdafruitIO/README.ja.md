# Wio Terminal Adafruit IO 連携の照度センサ

[English](README.md) | [日本語](README.ja.md)

## 概要

Wio Terminal 内蔵の照度センサ（`WIO_LIGHT`）を読み取り、LCD に表示して Adafruit IO へ送信します。背面にあるセンサを覆わないようにしてください。

### 画像・動画

[![Image from Gyazo](https://i.gyazo.com/c91afdeec80b07e40fff4aca7d88c4e0.png)](https://gyazo.com/c91afdeec80b07e40fff4aca7d88c4e0)

## 部品表

| 部品 | 数量 | 用途・備考 |
| ----------------------------------------------------------------------------------------------------------- | ---- | ----------------------------------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu) | 1 | 制御部、ディスプレイ、Wi-Fi モジュール。 |
| USB Type-C ケーブル | 1 | 給電・書き込み用。データ通信対応ケーブルが必要。 |

## 開発

### ハードウェア開発

使用する部品は部品表を参照してください。

### ソフトウェア開発

#### 設定

`rpcWiFi`、`TFT_eSPI`、`Adafruit MQTT Library` と、[スケッチ](Light_Sensor/Light_Sensor.ino)に必要な依存関係を用意します。`light-level` フィードと、それに接続するゲージを作成します。認証情報は `Light_Sensor/` のサンプルを設定します。

元の説明では WiFiManager の `AutoConnectAP` 設定ポータルを想定しています。ポータルを使う前に対象スケッチの Wi-Fi 接続実装を確認し、実装に合う方法で設定してください。

### テスト

#### テスト

周囲の明るさを変え、LCD とダッシュボードが更新されることを確認します。シリアル出力で MQTT・Wi-Fi 接続を確認します。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../../docs/arduino-development.ja.md)
- [認証情報の設定](../../../../../docs/credentials.ja.md)
- [Adafruit IO の設定](../../../../../docs/adafruit-io.ja.md)

## ライセンス

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## サポート

役に立った場合は、サポートをご検討ください:

[![BuyMeACoffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://buymeacoffee.com/asamiile)

## 作者

[Asami.K](https://asami.tokyo/)
