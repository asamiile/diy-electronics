# Arduino Nano ESP32 RGB LED

[English](README.md) | [日本語](README.ja.md)

## 概要

Arduino Uno の RGB 卓上ライトを Arduino Nano ESP32 向けに構成し、タクトスイッチと Arduino IoT Cloud の両方で操作します。[発光の作例](https://www.behance.net/gallery/229627251/Arduino-Uno-Chroma-LED)。

### 画像・動画

![](https://mir-s3-cdn-cf.behance.net/project_modules/fs_webp/032252232222857.68984c6f142d3.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/hd_webp/1095e9232222857.68984c6f139e4.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/fs_webp/5c3228232222857.68984c6f148b3.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/fs_webp/3b2910232222857.68984c6f150ae.jpg)

[![Image from Gyazo](https://i.gyazo.com/1ab5feb8a2e3802c23280b4c67604f26.png)](https://gyazo.com/1ab5feb8a2e3802c23280b4c67604f26)

[![Image from Gyazo](https://i.gyazo.com/5e2e5a0bee07afac0b680496551c4410.png)](https://gyazo.com/5e2e5a0bee07afac0b680496551c4410)

[![Image from Gyazo](https://i.gyazo.com/94192f1e5d906190a007f4fb6ecdc9c7.png)](https://gyazo.com/94192f1e5d906190a007f4fb6ecdc9c7)

## 部品表

### 制御系

| 部品 | 数量 | 用途・備考 |
| --------------------------------------------- | ---- | -------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1 | マイコン。 |
| [USB-C ケーブル](https://amzn.to/4lU4bdZ) | 1 | Nano ESP32 の書き込み・給電用。 |

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

- 共通カソード RGB LED：カソード → GND、赤 → 220Ω → D2、緑 → 220Ω → D3、青 → 220Ω → D4。
- スイッチ：D5 → スイッチ → GND。

### ソフトウェア開発

#### Arduino Cloud の設定

Nano ESP32 を登録して Thing を作成し、2.4GHz Wi-Fi を設定します。`colorMode` を Integer Number・Read & Write の変数として追加します。生成されたデバイス設定を維持しながら、Thing のスケッチを[作品のスケッチ](sketch/Arduino_Nano_ESP32_RGB_LED/Arduino_Nano_ESP32_RGB_LED.ino)に置き換えます。

ダッシュボードに `colorMode` と連携する Stepper を追加し、範囲を 0〜6 に設定します。必要に応じて Value 表示も追加します。書き込みに失敗した場合はボードのブートローダ手順を確認してください。元の手順ではリセットを 2 回、その後 1 回押します。

### テスト

#### テスト

オンラインになった後、Mode 0 では LED が消灯します。Mode 1 はピンクで、以後の変更で色が切り替わります。実物のスイッチ操作がダッシュボードへ反映され、ダッシュボード操作が LED へ反映されることを確認します。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)
- [認証情報の設定](../../../../docs/credentials.ja.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
