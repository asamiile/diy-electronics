# XIAO ESP32C3 Adafruit IO 連携の日の出・日の入りアラーム

[English](README.md) | [日本語](README.ja.md)

## 概要

XIAO ESP32C3 と Grove Digital Light Sensor を使用する日の出・日の入りアラームの計画です。固定時刻ではなく周囲の明るさから夜明け・日暮れを検出し、Adafruit IO に通知することを想定しています。

## 部品表

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------------------------------------------------------------ | ---- | --------------------------------------------------------------------------- |
| [XIAO ESP32C3](https://amzn.to/45T6bNg) | 1 | センサ情報を処理し、通知を送るアラーム制御部。 |
| [Grove Digital Light Sensor](https://jp.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html) | 1 | 周囲の明るさを測定して日の出・日の入りを検出。 |
| [Grove Shield for Seeeduino XIAO](https://amzn.to/479T6S5) | 1 | ブレッドボードと配線を置き換え、接続を簡潔にする。 |
| [USB-C ケーブル](https://amzn.to/4lU4bdZ) | 1 | XIAO ESP32C3 の書き込み・給電用。 |
| [Mobile Battery](https://amzn.to/45jTQ5W) | 1 | デバイスに給電し、設置場所を選びやすくする。 |

## 開発

### ハードウェア開発

#### 組み立て計画と実装状況

付属ピンヘッダを XIAO にはんだ付けし、Grove Shield に装着します。照度センサを Grove ケーブルで接続し、USB-C・モバイルバッテリーで給電します。接続ポートを決める前にセンサの必要なインターフェースを確認してください。ファームウェア、ダッシュボードの詳細、テスト結果は未収録です。

### ソフトウェア開発

セットアップ手順は参考資料の共通ガイドを参照してください。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)
- [Adafruit IO の設定](../../../../docs/adafruit-io.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
