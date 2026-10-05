# Monitoring から Discord への通知

[English](README.md) | [日本語](README.ja.md)

## 概要

HTTP 関数で Google Cloud Monitoring のインシデントを Discord へ転送します。クエリの `channel=critical` は `@everyone` を追加し、`warning` と既定値は通常形式を使います。すべてのレベルで同じ設定済み webhook URL を使用します。

## 部品表

このプロジェクトに専用の電子部品は不要です。必要なサービスと依存関係はソフトウェア開発を参照してください。

## 開発

### ハードウェア開発

専用のハードウェア設定はありません。

### ソフトウェア開発

#### 作品固有の設定

- デプロイ名・エントリーポイント：`notify_discord`、説明上のランタイム：`python312`。
- `DISCORD_WEBHOOK_URL` に通知先の Discord webhook を設定します。チャンネルの「連携サービス → ウェブフック」で作成し、URL は公開しません。
- 依存関係：[requirements.txt](requirements.txt)、実装：[main.py](main.py)。
- 関数：`notify_discord`、`get_discord_webhook_url`、`create_discord_message`、`send_to_discord`。

ローカル環境とデプロイは共通クラウドガイドを参照してください。webhook の環境変数または適切なシークレット連携をデプロイ設定へ追加します。既存の例は公開 HTTP 呼び出しを許可します。認証方式を変える場合は Monitoring 側の呼び出しも対応させます。

#### Monitoring 連携と問題の確認

関数のトリガー URL を使う Monitoring の webhook 通知チャンネルを作成します。緊急通知には `?channel=critical` を付け、アラートポリシーへ割り当てて Discord の受信を確認します。

設定不足時は環境変数・シークレットの存在を確認し、値は表示しません。認証エラー時は webhook が有効か確認し、再生成した場合は設定を更新します。タイムアウト時は接続と関数ログを確認します。コード、メモリ、タイムアウト、設定を変更する場合は共通のデプロイ手順で更新します。本番用のシークレット保管と呼び出し認証は別途設定が必要で、このソースだけでは構成されません。

### テスト

#### ローカル・デプロイ後のテスト

webhook を設定してから `notify_discord` を指定した Functions Framework を起動します。設定済みのローカルテストは実際にメッセージを送信します。この関数には `LOCAL_TEST_MODE` による送信省略はありません。webhook 未設定時は設定エラーを返します。

```sh
curl -X POST 'http://localhost:8080?channel=critical' \
  -H "Content-Type: application/json" \
  -d '{"incident":{"summary":"Test Alert","state":"OPEN","url":"https://console.cloud.google.com/"}}'
```

配信に成功すると `{"status":"success"}` が返ります。リモートテストではローカルのベース URL を実際のトリガー URL に置き換えます。緊急通知は `@everyone`、インシデント状態、要約、詳細 URL を含み、通常・警告通知はメンションを省略します。

## 参考資料

### 共通ガイド

- [Cloud Functions 共通手順](../../../docs/cloud-functions.ja.md)
- [認証情報の設定](../../../docs/credentials.ja.md)

- [Google Cloud Functions ドキュメント](https://cloud.google.com/functions/docs)
- [Google Cloud Monitoring webhook](https://cloud.google.com/monitoring/support/notification-options#webhooks)
- [Discord webhook 公式ドキュメント](https://discord.com/developers/docs/resources/webhook)
- [Weather Station Data Pipeline](../Weather_Station_Data_Pipeline) - BigQuery streaming
- [Wio Terminal Weather Station](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2) - Hardware integration

## 作者

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
