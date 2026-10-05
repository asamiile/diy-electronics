# Wio Terminal デジタルコンパス

[English](README.md) | [日本語](README.ja.md)

## 概要

Wio Terminal と外付けの 9 軸加速度・ジャイロ・磁気センサを使うデジタルコンパスの計画です。

## 部品表

| 部品 | 数量 | 用途・備考 |
| -------------------------------------------------------------------------------------------------------- | ---- | --------------------------------------------------------------------------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu) | 1 | 制御部、ディスプレイ、Wi-Fi モジュール。 |
| [Grove - IMU 9DOF (ICM20600+AK09918)](https://www.seeedstudio.com/Grove-IMU-9DOF-ICM20600-AK09918.html) | 1 | 3 軸加速度、3 軸ジャイロ、3 軸磁気センサで動き・方位を測定。 |
| USB Type-C ケーブル | 1 | 給電・書き込み用。データ通信対応ケーブルが必要。 |

## 開発

### ハードウェア開発

使用する部品は部品表を参照してください。

### ソフトウェア開発

#### 実装状況

部品表には `Grove IMU 9DOF (ICM20600+AK09918)` とデータ通信対応の USB-C ケーブルを記載しています。ファームウェア、接続の詳細、テスト結果は未収録です。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
