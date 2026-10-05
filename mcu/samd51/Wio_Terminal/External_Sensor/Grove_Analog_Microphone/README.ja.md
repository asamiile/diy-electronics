# Wio Terminal Grove アナログマイク

[English](README.md) | [日本語](README.ja.md)

## 概要

A0 のマイク入力を診断します。1 回に 128 サンプルを 5000µs 間隔（公称約 200Hz）で取得し、最小・最大・平均、ピーク間振幅、RMS を 115200 baud で表示します。振幅 20 未満は非常に小さい、100 未満は小さい、500 超は良好という表示です。静かな場合と音を出した場合を比べます。音声帯域の録音ではなく ADC の診断用です。

## 部品表

| 部品 | 数量 | 用途・備考 |
| --- | --- | --- |
| Wio Terminal | 1 | 制御・センサー処理 |
| データ通信対応 USB-C ケーブル | 1 | 給電と書き込み |
| Grove アナログマイク | 1 | 外部音声入力 |

## 開発

### ハードウェア開発

#### ハードウェアと依存関係

Wio Terminal、A0 に接続する Grove アナログマイク、データ通信対応 USB-C ケーブル。

依存関係：Arduino・Wio Terminal コア。

### ソフトウェア開発

#### ソースファイル

- [audio_test.ino](sketch/audio_test/audio_test.ino)

Wio Terminal のボードパッケージを使用します。スケッチ名と一致するディレクトリ外にある既存ファイルは、ビルド前に共通ガイドの手順に従ってください。この説明はソースに基づくもので、今回の文書更新ではビルド・実機動作は未検証です。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
