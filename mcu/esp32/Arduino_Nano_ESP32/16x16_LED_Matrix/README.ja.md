# Arduino Nano ESP32 16x16 LED マトリクス

[English](README.md) | [日本語](README.ja.md)

## 概要

Arduino Uno の LED マトリクス作品を Arduino Nano ESP32 向けに構成したものです。16×16 の WS2812B ディスプレイを使用し、ボタンでアニメーションを切り替えます。[アニメーションの作例](https://www.behance.net/gallery/229464473/Arduino-Uno-8x8-LED-Matrix)。

## 部品表

### 制御系

| 部品 | 数量 | 用途・備考 |
| --------------------------------------------- | ---- | -------------------------------------------- | --- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1 | マイコン。 |  |
| [USB-C ケーブル](https://amzn.to/407P2xg) | 1 | Nano ESP32 の書き込み・給電用。 |  |

### 入出力

| 部品 | 数量 | 用途・備考 |
| -------------------------------------------------------------------------------------------------- | ---- | --------------- |
| [WS2812B LED RGB 16x16](https://amzn.to/4ebZCcm) または [WS2812B LED RGB 8x8](https://amzn.to/44cSo3p) | 1 | 表示用。 |
| [タクトスイッチ](https://amzn.to/4l5lGrQ) | 1 | 入力ボタン。 |

### 電源

| 部品 | 数量 | 用途・備考 |
| -------------------------------------------------------------- | ---- | --------------------------------------- |
| [External AC adapter 5V 4A または Higher](https://amzn.to/4neewTI) | 1 | LED 用電源。 |
| [DC ジャックアダプタ（メス）](https://amzn.to/3IdZI7k) | 1 | AC アダプタを回路に接続。 |
| [電解コンデンサ (1000µF)](https://amzn.to/45ZOWLQ) | 1 | 電源の安定化。 |

### 電子部品・配線

| 部品 | 数量 | 用途・備考 |
| ---------------------------------------------- | ----- | ------------------------------------------ |
| [抵抗 (300-500Ω)](https://amzn.to/4kMejW2) | 1 | LED マトリクスのデータ線保護。 |
| [ブレッドボード](https://amzn.to/40bMzlk) | 1 | 試作用の回路基板。 |
| [ジャンパワイヤ](https://amzn.to/45voWYC) | 1 組 | 部品間の接続用。 |

## 開発

### ハードウェア開発

#### 配線

- 外部 5V 電源：DC ジャックの正極・負極 → ブレッドボードの電源・GND レール → マトリクスの 5V・GND。
- レール間に極性を確認した 1000µF コンデンサを接続します。
- Nano D6 → 330Ω 抵抗 → マトリクス DIN。
- Nano D2 → タクトスイッチ → Nano GND。
- Nano GND と外部電源の GND を共通にします。

### ソフトウェア開発

#### ソフトウェア

Arduino ESP32 Boards と `Adafruit NeoPixel` を使用し、[スケッチ](sketch/Arduino_Nano_ESP32_16x16_LED_Matrix/Arduino_Nano_ESP32_16x16_LED_Matrix.ino)を開きます。別の ESP32 ボードのピン番号ではなく、Nano ESP32 のボード設定を使用してください。

### テスト

#### テスト

配線を確認して外部 5V 電源を接続し、最初のアニメーションが表示されることを確認します。スイッチを押して表示パターンを切り替えます。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
