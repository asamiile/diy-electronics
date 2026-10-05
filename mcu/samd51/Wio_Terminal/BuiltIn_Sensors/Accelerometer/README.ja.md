# Wio Terminal 加速度センサ

[English](README.md) | [日本語](README.ja.md)

## 概要

内蔵 LIS3DHTR を `Wire1` で読み、25Hz・±2g に設定します。X・Y・Z をマゼンタ、黄緑、水色で表示し、50 サンプルを保持して約 50ms ごとに更新します。ボードを傾けて 3 本の線の変化を確認します。シリアルは 115200 baud で初期化します。

## 部品表

| 部品 | 数量 | 用途・備考 |
| --- | --- | --- |
| Wio Terminal | 1 | 制御・センサー処理 |
| データ通信対応 USB-C ケーブル | 1 | 給電と書き込み |

## 開発

### ハードウェア開発

#### ハードウェアと依存関係

Wio Terminal とデータ通信対応 USB-C ケーブルを使用します。内蔵ハードウェアを使うため、外部センサの配線は不要です。

依存関係：`LIS3DHTR.h` と `seeed_line_chart.h`。

### ソフトウェア開発

#### ソースファイル

- [Wio_Terminal_Accelerometer.ino](Wio_Terminal_Accelerometer.ino)

Wio Terminal のボードパッケージを使用します。スケッチ名と一致するディレクトリ外にある既存ファイルは、ビルド前に共通ガイドの手順に従ってください。この説明はソースに基づくもので、今回の文書更新ではビルド・実機動作は未検証です。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
