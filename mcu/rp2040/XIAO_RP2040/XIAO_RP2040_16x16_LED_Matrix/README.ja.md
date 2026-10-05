# XIAO RP2040 16x16 LED マトリクス

[English](README.md) | [日本語](README.ja.md)

## 概要

16×16（256 ピクセル）の WS2812B マトリクスで、ボタンによりアニメーションを切り替えます。外部 5V/10A 電源と、3.3V から 5V へのロジックレベル変換を使用します。8×8 を使う場合は `LED_COUNT` を 256 から 64 に変更します。

## 部品表

### 制御系

| 部品 | 数量 | 用途・備考 |
| --------------------------------------------------- | ---- | -------------------------------------- | --- |
| [XIAO RP2040](https://amzn.to/3TrkrHs) | 1 | マイコン。 |  |
| [USB-C ケーブル](https://amzn.to/407P2xg) | 1 | XIAO の書き込み・給電用。 |  |

### 入出力

| 部品 | 数量 | 用途・備考 |
| -------------------------------------------------------------------------------------------------- | ---- | --------------- |
| [WS2812B LED RGB 16x16](https://amzn.to/4ebZCcm) または [WS2812B LED RGB 8x8](https://amzn.to/44cSo3p) | 1 | 表示用。 |
| [タクトスイッチ](https://amzn.to/4l5lGrQ) | 1 | 入力ボタン。 |

### 電源

| 部品 | 数量 | 用途・備考 |
| ---------------------------------------------------------- | ---- | --------------------------------------- |
| [External AC adapter 5V 10A](https://amzn.to/4neewTI) | 1 | LED 用電源。 |
| [DC ジャックアダプタ（メス）](https://amzn.to/3IdZI7k) | 1 | AC アダプタを回路に接続。 |
| [電解コンデンサ (1000µF)](https://amzn.to/45ZOWLQ) | 1 | 電源の安定化。 |

### 電子部品・配線

| 部品 | 数量 | 用途・備考 |
| ---------------------------------------------- | ----- | ----------------------------------- |
| [ロジックレベル変換器](https://amzn.to/4eeDyhr) | 1 | 信号電圧のレベル変換。 |
| [抵抗 (300-500Ω)](https://amzn.to/4kMejW2) | 1 | LED のデータ線保護。 |
| [ブレッドボード](https://amzn.to/40bMzlk) | 1 | 試作用の回路基板。 |
| [ジャンパワイヤ](https://amzn.to/45voWYC) | 1 組 | 部品間の接続用。 |

## 開発

### ハードウェア開発

#### 配線

- 電源の正極・GND → 電源・GND レール、マトリクス電源、極性を確認した 1000µF コンデンサ。
- XIAO 5V・GND → 対応するレール。
- レベル変換器 HV → 5V、LV → XIAO 3V3、両 GND → 共通 GND。
- XIAO D6 → LVx、HVx → 330Ω → マトリクス DIN。
- XIAO D2 → スイッチ → GND。スケッチで内部プルアップを有効にします。

[回路図](diagrams/XIAO_RP2040_16x16_LED_Matrix_bb.png)を参照してください。

### ソフトウェア開発

#### ソフトウェアとテスト

Earle F. Philhower の RP2040 コアで XIAO RP2040 を選択し、`Adafruit NeoPixel` を導入します。ボードのインデックス URL は `https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json` です。[スケッチ](sketch/XIAO_RP2040_16x16_LED_Matrix/XIAO_RP2040_16x16_LED_Matrix.ino)を書き込み、電源・GND の配線とボタンで切り替える全パターンを確認します。ケース設計の説明は未収録です。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
