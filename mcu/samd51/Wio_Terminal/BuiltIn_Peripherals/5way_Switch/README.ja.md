# Wio Terminal 5 方向スイッチ

[English](README.md) | [日本語](README.ja.md)

## 概要

`WIO_5S_UP`、`WIO_5S_DOWN`、`WIO_5S_LEFT`、`WIO_5S_RIGHT`、`WIO_5S_PRESS` を LOW で有効な入力として読みます。対応する方向を LCD に描画し、1 秒の待機を行います。5 種類の入力を確認してください。ループ内でスプライトも転送するため、実際の表示結果は実機で確認が必要です。

## 部品表

| 部品 | 数量 | 用途・備考 |
| --- | --- | --- |
| Wio Terminal | 1 | 制御・センサー処理 |
| データ通信対応 USB-C ケーブル | 1 | 給電と書き込み |

## 開発

### ハードウェア開発

#### ハードウェアと依存関係

Wio Terminal とデータ通信対応 USB-C ケーブルを使用します。内蔵ハードウェアを使うため、外部センサの配線は不要です。

依存関係：`TFT_eSPI`.

### ソフトウェア開発

#### ソースファイル

- [Wio_Terminal_5way_Switch.ino](Wio_Terminal_5way_Switch.ino)

Wio Terminal のボードパッケージを使用します。スケッチ名と一致するディレクトリ外にある既存ファイルは、ビルド前に共通ガイドの手順に従ってください。この説明はソースに基づくもので、今回の文書更新ではビルド・実機動作は未検証です。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
