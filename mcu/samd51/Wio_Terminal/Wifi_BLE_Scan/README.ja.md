# Wio Terminal Wi-Fi・BLE 検出

[English](README.md) | [日本語](README.ja.md)

## 概要

Wi-Fi ネットワークと BLE 広告を繰り返し検出し、SSID、RSSI、Wi-Fi の保護状態、BLE デバイス情報、件数を 115200 baud で表示します。BLE 検出は 5 秒間で、ループ間に 1 秒待機します。起動時の待機を解除するためシリアルモニタを開きます。スキャンに Wi-Fi 認証情報は不要です。

## 部品表

| 部品 | 数量 | 用途・備考 |
| --- | --- | --- |
| Wio Terminal | 1 | 制御・センサー処理 |
| データ通信対応 USB-C ケーブル | 1 | 給電と書き込み |

## 開発

### ハードウェア開発

#### ハードウェアと依存関係

Wio Terminal とデータ通信対応 USB-C ケーブルを使用します。内蔵ハードウェアを使うため、外部センサの配線は不要です。

依存関係：`rpcWiFi.h`, `rpcBLEDevice.h`, `BLEScan.h`, `BLEAdvertisedDevice.h`.

### ソフトウェア開発

#### ソースファイル

- [Wifi_BLE_Scan.ino](Wifi_BLE_Scan.ino)

Wio Terminal のボードパッケージを使用します。スケッチ名と一致するディレクトリ外にある既存ファイルは、ビルド前に共通ガイドの手順に従ってください。この説明はソースに基づくもので、今回の文書更新ではビルド・実機動作は未検証です。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
