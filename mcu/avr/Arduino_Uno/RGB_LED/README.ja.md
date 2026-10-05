# Arduino Uno RGB LED

[English](README.md) | [日本語](README.ja.md)

## 概要

共通カソード RGB LED とタクトスイッチを使う卓上ライトです。ピンク、黄・オレンジ、緑、青、紫、滑らかな色変化を順に表示し、一巡すると消灯します。実際の色の値はスケッチを基準にしてください。

### 画像・動画

![](https://mir-cdn.behance.net/v1/rendition/project_modules/max_3840_webp/6226e6229627251.6867e0d1bb8c7.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/ba3420229627251.6867e0d1bacc1.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/5d5c6a229627251.6867e0d1bb195.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/938d8b229627251.6867e0d1bc328.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/e95a45229627251.6867e0d1bc881.jpg)

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/HZucglmYSCs/hqdefault.jpg)](https://youtu.be/HZucglmYSCs?si=rXBTJWtdmKFi_rcF)

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/dp0oIES4NKo/hqdefault.jpg)](https://youtu.be/dp0oIES4NKo?si=npvw56pW3KhWuZMV)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/4fc92f229627251.6867e0d0b3b1b.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/fbf47c229627251.6867e0d0b35f8.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/eb167d229627251.6867e0d0b3081.jpg)

## 部品表

### 制御系

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------ | ---- | -------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA) | 1 | マイコン。 |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1 | Arduino への書き込み用。 |

### 入出力

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------- | ---- | ------------------------------------------------- |
| [5mm 共通カソード RGB LED](https://amzn.to/4lmJuaE) | 1 | 発光用部品。 |
| [タクトスイッチ (Push Button)](https://amzn.to/3T0gNUF) | 1 | 点灯・消灯と色切り替え。 |

### 試作・配線

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------- | ----- | ------------------------------------------------- |
| [抵抗 (220Ω)](https://amzn.to/4kMejW2) | 3 | LED のデータ線保護。 |
| [ブレッドボード](https://amzn.to/40bMzlk) | 1 | 試作用の回路基板。 |
| [ジャンパワイヤ](https://amzn.to/45voWYC) | 1 組 | 部品間の接続用。 |

## 開発

### ハードウェア開発

#### 配線

- 共通カソード → Uno GND。
- D11（PWM）→ 220Ω → 赤、D10（PWM）→ 220Ω → 青、D9（PWM）→ 220Ω → 緑。
- D2 → スイッチ → GND。外付けプルアップは示していないため、`pinMode(2, INPUT_PULLUP)` を使用します。

[回路図](diagrams/Arduino_Uno_RGB_LED_bb.png)を参照してください。

### ソフトウェア開発

#### ソフトウェアとテスト

[スケッチ](sketch/Arduino_Uno_RGB_LED/Arduino_Uno_RGB_LED.ino)を Arduino Uno に書き込みます。初期状態は消灯です。ボタンを押して各色と色変化アニメーションを表示し、最後に消灯へ戻ることを確認します。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

[Arduino Uno Chroma LED - Behance](https://www.behance.net/gallery/229627251/Arduino-Uno-Chroma-LED)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
