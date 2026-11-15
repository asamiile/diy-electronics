# Wio Terminal Edge Impulse 単語検出

[English](README.md) | [日本語](README.ja.md)

## 概要

Edge Impulse を使用する、制作中の Wio Terminal 単語検出サンプルです。[デプロイ用スケッチ](sketch/Word_Detection/Word_Detection.ino)を収録しています。リンク先のチュートリアルでモデルを準備し、必要な推論ライブラリを用意してください。

## 部品表

| 部品 | 数量 | 用途・備考 |
| --- | --- | --- |
| Wio Terminal | 1 | 制御・センサー処理 |
| データ通信対応 USB-C ケーブル | 1 | 給電と書き込み |

## 開発

### ハードウェア開発

使用する部品は部品表を参照してください。

### ソフトウェア開発

#### 設定とテスト

環境の準備は共通の TinyML ガイド、書き込みは Arduino ガイドを参照してください。使用するモデルに合わせて、入力、推論結果、シリアル出力を確認します。

- [Edge Impulse 入門チュートリアル](https://wiki.seeedstudio.com/Getting_started_wizard/#getting-started-with-edge-impulse)

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../../docs/arduino-development.ja.md)
- [TinyML 環境準備](../../../../../docs/tinyml-development.ja.md)

## ライセンス

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## サポート

役に立った場合は、サポートをご検討ください:

[![BuyMeACoffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://buymeacoffee.com/asamiile)

## 作者

[Asami.K](https://asami.tokyo/)
