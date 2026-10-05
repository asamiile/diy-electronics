# Arduino Uno インタラクティブサーボライト

[English](README.md) | [日本語](README.ja.md)

## 概要

可変抵抗でサーボの角度を設定し、位置に合わせて RGB LED の色を変えます。0° はピンク、90° は紫、180° は水色です。

### 画像・動画

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/6f8129230140209.68712daf1acd3.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/47518d230140209.68712daf1e3a0.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/81a14e230140209.68712daf1c780.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/cbb114230140209.687134623844c.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/3c0d8e230140209.687134623897d.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/14e02c230140209.6871346237c0b.jpg)

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/JPDLfhR-mck/hqdefault.jpg)](https://youtu.be/JPDLfhR-mck?si=Nqr5AGdnBTtr3w_z)

## 部品表

### 制御系

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------ | ---- | -------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA) | 1 | マイコン。 |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1 | Arduino への書き込み用。 |

### 入力・アクチュエータ

| 部品 | 数量 | 用途・備考 |
| ----------------------------------------------------- | ---- | -------------------------------------------------------------------------- |
| [サーボモータ (SG90)](https://amzn.to/3TUevqn) | 1 | 角度を制御するアクチュエータ。 |
| [可変抵抗 (10kΩ)](https://amzn.to/4eCRh1R) | 1 | サーボ角度を設定するノブ。 |
| [5mm 共通カソード RGB LED](https://amzn.to/4lmJuaE) | 1 | 発光用部品。 |

### 試作・配線

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------ | ----- | ----------------------------------- |
| [抵抗 (220Ω)](https://amzn.to/4kMejW2) | 3 | LED のデータ線保護。 |
| [ブレッドボード](https://amzn.to/40bMzlk) | 1 | 試作用の回路基板。 |
| [ジャンパワイヤ](https://amzn.to/45voWYC) | 1 組 | 部品間の接続用。 |

## 開発

### ハードウェア開発

#### 配線

- Uno 5V・GND → ブレッドボードの電源・GND レール。
- サーボ信号 → D9、サーボ電源・GND → 対応するレール。
- 可変抵抗の中央端子 → A0、両端 → 5V と GND。
- 共通カソード RGB LED のカソード → GND、赤 → 抵抗 → D11、緑 → 抵抗 → D10、青 → 抵抗 → D5。

[回路図](diagrams/Arduino_Uno_Interactive_Servo_Light_bb.png)を参照してください。

### ソフトウェア開発

#### ソフトウェアとテスト

Arduino Uno 向けに `Servo` と[作品のスケッチ](sketch/Arduino_Uno_Interactive_Servo_Light/Arduino_Uno_Interactive_Servo_Light.ino)を使用します。給電して可変抵抗を回し、サーボが滑らかに動き、対応する色に変化することを確認します。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

[Arduino Uno Interactive Servo Light - Behance](https://www.behance.net/gallery/230140209/Arduino-Uno-Interactive-Servo-Light)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
