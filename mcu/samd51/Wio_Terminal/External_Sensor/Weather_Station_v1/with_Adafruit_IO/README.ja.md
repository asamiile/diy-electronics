# Wio Terminal Weather Station with Adafruit IO

[English](README.md) | [日本語](README.ja.md)

## 概要

DHT11 気象ステーション v1 の Adafruit IO 連携です。温度・湿度を送信し、ゲージ・グラフで可視化します。必要に応じて通知連携を追加します。自動再接続や Wi-Fi 設定ポータルの有無は、使用するファームウェアによります。

### 画像・動画

[![Image from Gyazo](https://i.gyazo.com/2f3f2dd6637c2fdf2869a831bb386971.png)](https://gyazo.com/2f3f2dd6637c2fdf2869a831bb386971)

## 部品表

| 部品 | 数量 | 用途・備考 |
| --- | --- | --- |
| Wio Terminal | 1 | 制御・センサー処理 |
| データ通信対応 USB-C ケーブル | 1 | 給電と書き込み |

センサーと配線は、参考資料の元の Weather Station プロジェクトを参照してください。

## 開発

### ハードウェア開発

使用する部品は部品表を参照してください。

### ソフトウェア開発

#### 作品固有の設定

D0 のセンサ配線と実際のスケッチは[親プロジェクト](../README.ja.md)を参照してください。`temperature` と `humidity` フィード、および各フィードのゲージを作成し、認証情報サンプルで `AIO_USERNAME` と `AIO_KEY` を設定します。必要ライブラリは親 README に記載しています。

以前の説明には WiFiManager と Discord 通知がありましたが、Adafruit IO のダッシュボード作成だけでは追加されません。対象スケッチを確認し、通知連携は別途設定してください。

### テスト

#### 検証

親プロジェクトのファームウェアを書き込み、Wi-Fi・MQTT 接続と、両フィード・ゲージの更新を確認します。

## 参考資料

### 共通ガイド

- [Arduino 開発手順](../../../../../../docs/arduino-development.ja.md)
- [Adafruit IO の設定](../../../../../../docs/adafruit-io.ja.md)

- [Adafruit IO ドキュメント](https://io.adafruit.com/api/docs/)
- [MQTT プロトコル概要](https://mqtt.org/)
- [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library)
- [WiFiManager by tzapu](https://github.com/tzapu/WiFiManager)

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiii" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
