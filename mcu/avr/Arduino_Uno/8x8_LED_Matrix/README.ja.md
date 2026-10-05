# Arduino Uno 8x8 LED マトリクス

[English](README.md) | [日本語](README.ja.md)

## 概要

8×8 の WS2812B LED マトリクスに、虹、波紋、跳ねるボール、海の波、呼吸アニメーションを表示します。ボタンでパターンを切り替えます。

### 画像・動画

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/6-BWVaQY8bo/hqdefault.jpg)](https://youtu.be/6-BWVaQY8bo?si=5ha3Cig4YXMKvDc2)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/e68a6a229464473.68652fef57f01.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/3cc74e229464473.68652fef5b1e3.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/204169229464473.68652fef54ef1.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/813954229464473.68652fef55609.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/7d1379229464473.68652fef57857.jpg)

## 部品表

### 制御系

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------ | ---- | ------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA) | 1 | マイコン。 |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1 | Arduino への書き込み用。 |

### 入出力

| 部品 | 数量 | 用途・備考 |
| ---------------------------------------------- | ---- | -------------- |
| [8x8 RGB LED WS2812B](https://amzn.to/44cSo3p) | 1 | 表示用。 |
| [タクトスイッチ](https://amzn.to/3T0gNUF) | 1 | 入力ボタン。 |

### 電源

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------------------------------------------------- | ---- | ---------------------------------------- |
| [電源 (5V, 2A+)](https://amzn.to/4jZEIyu) または [モバイルバッテリー](https://amzn.to/45jTQ5W) | 1 | LED 用電源。 |
| [DC ジャックアダプタ（メス）](https://amzn.to/3IdZI7k) | 1 | AC アダプタをブレッドボードに接続。 |
| [電解コンデンサ (1000µF)](https://amzn.to/45ZOWLQ) | 1 | 電源の安定化。 |

### 試作・配線

| 部品 | 数量 | 用途・備考 |
| ---------------------------------------------- | ----- | ---------------------------------- |
| [抵抗 (300-500Ω)](https://amzn.to/4kMejW2) | 1 | LED のデータ線保護。 |
| [ブレッドボード](https://amzn.to/40bMzlk) | 1 | 試作用の回路基板。 |
| [ジャンパワイヤ](https://amzn.to/45voWYC) | 1 組 | 部品間の接続用。 |

## 開発

### ハードウェア開発

#### 配線

- 外部 5V 電源の正極・GND → ブレッドボードのレール → マトリクスの 5V・GND。
- レール間に極性を確認した 1000µF コンデンサを接続します。
- Uno D6 → 330Ω 抵抗 → マトリクス DIN。
- Uno D2 → スイッチ → Uno GND。
- Uno GND と外部電源 GND を共通にします。

[回路図](diagrams/Fritzing/Arduino_Uno_LED_8x8_led_matrix_art_bb.png)を参照してください。

### ソフトウェア開発

#### ソフトウェアとテスト

`Adafruit NeoPixel` と[スケッチ](sketch/Arduino_Uno_8x8_led_matrix/Arduino_Uno_8x8_led_matrix.ino)を使用します。配線を確認してから外部 5V 電源を接続し、最初の表示とボタンで切り替える各パターンを確認します。

関連作品：[Nano ESP32 16×16 マトリクス](../../../esp32/Arduino_Nano_ESP32/16x16_LED_Matrix/README.ja.md)。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

[Arduino Uno 8x8 LED Matrix - Behance](https://www.behance.net/gallery/229464473/Arduino-Uno-8x8-LED-Matrix)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
