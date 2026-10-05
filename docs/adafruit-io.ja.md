# Adafruit IO の設定

[English](adafruit-io.md) | [日本語](adafruit-io.ja.md)

[Adafruit IO](https://io.adafruit.com/) のアカウントを作成し、ユーザー名と AIO Key を取得して、作品の[認証情報の手順](credentials.ja.md)に従って設定します。

作品の README に記載された名前でフィードを作成します。各フィードにゲージや折れ線グラフを接続し、作品の単位と表示範囲を設定します。設定済みのスケッチを書き込み、シリアル出力で Wi-Fi・MQTT の接続を確認して、フィードの時刻とダッシュボードの値が更新されることを確認します。

`AutoConnectAP` などの設定ポータルは作品固有の機能です。対象スケッチが実装している場合だけ使用してください。Arduino Cloud / Arduino IoT Remote の設定は Adafruit IO と分けて扱います。

- [Adafruit IO API ドキュメント](https://io.adafruit.com/api/docs/)
