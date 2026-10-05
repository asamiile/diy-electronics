# SunFounder_GalaxyRVR

[English](README.md) | [日本語](README.ja.md)

## 概要

Arduino Uno R3 と ESP32 AI Camera を使うローバーです。手動走行、超音波による障害物回避、赤外線・超音波による追従、カメラのチルト、テレメトリに対応します。RGB 表示は前進が緑、後退が赤、旋回が黄、待機が青の呼吸アニメーションです。

## 部品表

| 部品 | 数量 | 用途・備考 |
| ---------------------------------------------------------------------- | ---- | ----------------------------------------------------- |
| [SunFounder GalaxyRVR](https://amzn.to/454yN6I) | 1 | Arduino Uno R3 と必要部品を含む。 |

## 開発

### ハードウェア開発

使用する部品は部品表を参照してください。

### ソフトウェア開発

#### 設定

`SunFounder AI Camera`、`SoftPWM`、`Servo` を使用し、[スケッチ](sketch/SunFounder_GalaxyRVR/SunFounder_GalaxyRVR.ino)を開きます。同じ場所の `credentials.h` に `STA_SSID` と `STA_PASSWORD` を設定し、STA モードでは 2.4GHz Wi-Fi を使います。

#### コントローラと検証

[SunFounder Controller](https://play.google.com/store/apps/details?id=com.sunfounder.sunfoundercontroller&hl=ja) を導入し、シリアルモニタに表示された IP アドレスへ接続して以下を割り当てます。

- Region D：カメラのチルトスライダ。
- Region E：障害物回避スイッチ。
- Region F：追従モードスイッチ。
- Region J：ライトの主スイッチ。
- Region K/Q：手動走行のスロットル。

SunFounder R3 ボードへ書き込み、手動・自動モード切り替え、障害物回避、追従距離、カメラ動作、電池電圧、センサ距離、LED 表示を確認します。

### テスト

概要と開発手順に記載された動作を確認してください。このドキュメント更新では、コンパイル・実行・実機検証は行っていません。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../docs/arduino-development.ja.md)
- [認証情報の設定](../../../../docs/credentials.ja.md)

- [SunFounder - Programming with Arduino IDE](https://docs.sunfounder.com/projects/galaxy-rvr/en/latest/programming_arduino.html)
- [GitHub - GalaxyRVR](https://github.com/sunfounder/galaxy-rvr/tree/main)
- [GitHub - SunFounder AI Camera Library for Arduino](https://github.com/sunfounder/SunFounder_AI_Camera/blob/main/README.md)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
