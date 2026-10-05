# Wio Terminal 照度によるジェスチャ

[English](README.md) | [日本語](README.ja.md)

## 概要

収集用スケッチは `WIO_LIGHT` を 40Hz・115200 baud で出力します。デプロイ用スケッチは照度の読み取り値を Edge Impulse の入力フレームへ格納して分類します。コードが参照するヘッダに対応する推論ライブラリが必要ですが、ここには未収録です。学習時と実行時のサンプリング条件を合わせ、ラベル付きジェスチャで検証してください。

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
