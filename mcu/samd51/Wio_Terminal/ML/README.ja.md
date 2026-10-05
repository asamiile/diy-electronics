# Wio Terminal の TinyML

[English](README.md) | [日本語](README.ja.md)

## 概要

Wio Terminal の TinyML サンプルとして、音声シーン認識、加速度によるジェスチャ、超音波による人数計測、照度によるジェスチャ、単語検出を収録しています。学習・デプロイの条件はサンプルごとに異なります。

## 部品表

| 部品 | 数量 | 用途・備考 |
| --- | --- | --- |
| Wio Terminal | 1 | 制御・センサー処理 |
| データ通信対応 USB-C ケーブル | 1 | 給電と書き込み |

## 開発

### ハードウェア開発

使用する部品は部品表を参照してください。

### ソフトウェア開発

#### 環境とサンプル

元の Conda、Python、FFmpeg、Edge Impulse CLI の準備手順は下の共通ガイドを参照してください。収集・デプロイ用スケッチは各ディレクトリにあります。学習済みモデルのライブラリが必要な場合は別途用意してください。

- [音声シーン認識](Audio_scene_recognition_with_microphone/)
- [加速度によるジェスチャ](Classifying_hand_gestures_with_accelerometer/)
- [超音波による人数計測](People_counting_with_Ultrasonic_sensor/)
- [照度によるジェスチャ](Recognizing_gestures_with_light_sensor/)
- [単語検出](Word_Detection/README.ja.md)

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)
- [TinyML 環境準備](../../../../docs/tinyml-development.ja.md)

- [TinyML with Wio Terminal](https://files.seeedstudio.com/wiki/Wio-Terminal-TinyML/TinyML_with_Wio_Terminal_Course_v1-3.pdf)
- [Wio Terminal Edge Impulse firmware](https://github.com/Seeed-Studio/Seeed_Arduino_edgeimpulse/releases/tag/1.4.0)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
