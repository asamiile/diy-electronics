# Wio Terminal 音声シーン認識

[English](README.md) | [日本語](README.ja.md)

## 概要

デプロイ用スケッチはモデル窓を 4 分割してマイク入力を推論し、115200 baud で結果を表示します。エクスポートした `Audio_scene_recognition_with_microphone_inferencing.h` が必要です。前処理用の `converter.py` もあります。実行前に入出力設定を確認してください。モデル本体は未収録です。ラベル付きの音声シーンで入力と推論を検証します。

## 部品表

| 部品 | 数量 | 用途・備考 |
| --- | --- | --- |
| Wio Terminal | 1 | 制御・センサー処理 |
| データ通信対応 USB-C ケーブル | 1 | 給電と書き込み |

## 開発

### ハードウェア開発

#### ハードウェアと依存関係

Wio Terminal とデータ通信対応 USB-C ケーブルを使用します。内蔵ハードウェアを使うため、外部センサの配線は不要です。

依存関係：エクスポートした Edge Impulse 推論ライブラリ。

### ソフトウェア開発

#### ソースファイル

- [model_deployment.ino](model_deployment/model_deployment.ino)
- [converter.py](converter.py)

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
