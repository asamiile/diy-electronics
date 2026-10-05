# Wio Terminal 超音波による人数計測

[English](README.md) | [日本語](README.ja.md)

## 概要

データ収集と Edge Impulse デプロイ用のスケッチを収録しています。収集は `Ultrasonic(0)` を使い、50ms ごとに 115200 baud で距離を出力します。200cm 未満は距離、それ以外は `-1` です。デプロイにはエクスポートした `People_counting_with_Ultrasonic_sensor_inferencing.h` モデルライブラリと `Seeed_Arduino_FreeRTOS` が必要です。ラベル付きの例で距離と推論を検証してください。モデル本体は未収録です。

## 部品表

| 部品 | 数量 | 用途・備考 |
| --- | --- | --- |
| Wio Terminal | 1 | 制御・センサー処理 |
| データ通信対応 USB-C ケーブル | 1 | 給電と書き込み |
| 超音波センサー | 1 | 距離測定 |

## 開発

### ハードウェア開発

#### ハードウェアと依存関係

Wio Terminal、ピン 0 に対応するポートの Grove 超音波センサ、データ通信対応 USB-C ケーブル。

依存関係：`Ultrasonic.h`, `TFT_eSPI`, `Seeed_Arduino_FreeRTOS`, エクスポートした Edge Impulse モデル。

### ソフトウェア開発

#### ソースファイル

- [data_collection.ino](data_collection/data_collection.ino)
- [model_deployment.ino](model_deployment/model_deployment.ino)

Wio Terminal のボードパッケージを使用します。スケッチ名と一致するディレクトリ外にある既存ファイルは、ビルド前に共通ガイドの手順に従ってください。この説明はソースに基づくもので、今回の文書更新ではビルド・実機動作は未検証です。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../../docs/arduino-development.ja.md)
- [TinyML 環境準備](../../../../../docs/tinyml-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
