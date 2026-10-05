# Arduino Nano ESP32 Web 操作型 2 軸パン・チルト雲台

[English](README.md) | [日本語](README.ja.md)

## 概要

Arduino Nano ESP32 と 2 個の SG90 サーボを使用する、ブラウザ操作型の 2 軸パン・チルト雲台の計画です。記載されていたファームウェアと React 操作画面は、このリポジトリでは未実装です。スケッチファイルはプレースホルダーです。

## 部品表

### 制御系

| 部品 | 数量 | 用途・備考 |
| --------------------------------------------- | ---- | -------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1 | マイコン。 |
| [USB-C ケーブル](https://amzn.to/4lU4bdZ) | 1 | Nano ESP32 の書き込み・給電用。 |

### 機構・アクチュエータ

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------------- | ---- | ----------------------------------------------------- |
| [サーボモータ (SG90)](https://amzn.to/3TUevqn) | 2 | 水平のパン用と垂直のチルト用。 |
| [2-Axis Pan-Tilt Bracket Kit)](https://amzn.to/44J3H3s) | 1 | 2 個のサーボを取り付けるフレーム。 |

### 電源

| 部品 | 数量 | 用途・備考 |
| ---------------------------------------------------------- | ---- | ------------------------------------------------- |
| [AC アダプタ (5V 4A)](https://amzn.to/4lOymDh) | 1 | サーボ用の外部電源。 |
| [DC ジャックアダプタ（メス）](https://amzn.to/3IdZI7k) | 1 | AC アダプタ接続用ソケット。 |
| [電解コンデンサ (1000µF)](https://amzn.to/45ZOWLQ) | 1 | サーボ電源の安定化。 |

### 試作・配線

| 部品 | 数量 | 用途・備考 |
| ------------------------------------------------ | ----- | --------------------------------------------------- |
| [ブレッドボード](https://amzn.to/40bMzlk) | 1 | 試作用の回路基板。 |
| [ジャンパワイヤ](https://amzn.to/45voWYC) | 1 組 | 信号線の接続用。 |

## 開発

### ハードウェア開発

#### 配線計画

サーボには外部 5V/4A 電源を使い、電源レール間に 1000µF コンデンサを接続します。両サーボの電源線を正極、GND 線を GND に接続します。パン信号は GPIO12、チルト信号は GPIO13、Nano GND は外部電源 GND と共通にします。[回路図](diagrams/Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount_bb.png)を参照してください。

### ソフトウェア開発

#### ソフトウェア計画

Arduino ESP32 Boards と `ESP32Servo` を使用します。[スケッチのプレースホルダー](sketch/Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount/Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount.ino)と同じ場所に認証情報のサンプルがあります。

React 操作画面をボードのフラッシュメモリに配置する予定です。0〜180° のパン・チルトスライダ、90° に戻す中央ボタン、角度表示、`/move?servo=pan&angle=120` などのコマンドを想定しています。画面のソースとフラッシュへの配置手順は未収録です。

### テスト

#### 実装後のテスト計画

サーボ電源を接続し、115200 baud で確認します。ボードをリセットし、同じ Wi-Fi 上のブラウザから表示された IP アドレスを開き、両軸の動作を確認します。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)
- [認証情報の設定](../../../../docs/credentials.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
