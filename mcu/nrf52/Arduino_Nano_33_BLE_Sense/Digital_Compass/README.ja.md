# Arduino Nano 33 BLE Sense

[English](README.md) | [日本語](README.ja.md)

## 概要

Arduino Nano 33 BLE Sense 内蔵の 9 軸 IMU を使うデジタルコンパスです。加速度・ジャイロ・磁気センサを使い、0〜360° の方位をシリアルモニタへ表示します。コンパス用スケッチはこのリポジトリには未収録です。

## 部品表

### 制御系

| 部品 | 数量 | 用途・備考 |
| ---------------------------------------------------- | ---- | -------------------------------------------------------------------------- |
| [Arduino Nano 33 BLE Sense](https://amzn.to/3J0t7Te) | 1 | マイコンと 9 軸センサを 1 枚のボードに搭載。 |
| [Micro USB ケーブル](https://amzn.to/4nmvlf5) | 1 | ボードへの書き込みと PC からの給電。 |

## 開発

### ハードウェア開発

#### ハードウェアとソフトウェア

外部センサの配線は不要です。Arduino Mbed OS Nano Boards パッケージを使用し、Arduino Nano 33 BLE Sense を選択して `Arduino_LSM9DS1` を導入します。書き込む前に `Arduino_Nano_33_BLE_Sense_Digital_Compass.ino` を用意または実装してください。

### ソフトウェア開発

セットアップ手順は参考資料の共通ガイドを参照してください。

### テスト

#### テスト

9600 baud、またはスケッチで指定した通信速度を使用します。ボードを回転させ、表示される方位が変化することを確認します。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)

## ライセンス

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## サポート

役に立った場合は、サポートをご検討ください:

[![BuyMeACoffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://buymeacoffee.com/asamiile)

## 作者

[Asami.K](https://asami.tokyo/)
