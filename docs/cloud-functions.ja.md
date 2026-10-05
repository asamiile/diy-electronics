# Cloud Functions の共通手順

[English](cloud-functions.md) | [日本語](cloud-functions.ja.md)

## 準備

[Google Cloud CLI](https://cloud.google.com/sdk/docs/install)を導入し、使用するプロジェクトと、作品に必要な API・IAM 権限を準備します。コマンドはクラウド関数のディレクトリで実行します。

```sh
gcloud auth login
gcloud config set project YOUR_GCP_PROJECT_ID
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
```

Windows の PowerShell では `.venv\Scripts\Activate.ps1`、cmd では `.venv\Scripts\activate.bat` で環境を有効化します。ローカルから BigQuery に接続する場合はアプリケーションのデフォルト認証情報を設定します。作品のローカルテストモードでは BigQuery への書き込みを省略できます。

## ローカル実行

作品固有の環境変数を設定し、`ENTRY_POINT` を `main.py` の関数名に置き換えます。

```sh
functions-framework --target ENTRY_POINT --debug --port 8080
```

作品の README にあるサンプル JSON を `http://localhost:8080` に送ります。ローカルテストモードで書き込みを省略できるのは対応する関数だけです。Discord 関数は webhook を設定すると実際に通知を送信します。

## デプロイ

作品の README に記載されたデプロイ名、エントリーポイント、ランタイム、環境変数を使用し、以下のプレースホルダーを置き換えます。

```sh
gcloud functions deploy FUNCTION_NAME \
  --gen2 \
  --region asia-northeast1 \
  --runtime RUNTIME \
  --source . \
  --entry-point ENTRY_POINT \
  --trigger-http \
  --memory 256MB \
  --timeout 60s
```

既存の外部 webhook の例は公開 HTTP エンドポイントを使用するため、その構成では `--allow-unauthenticated` を追加します。認証付き呼び出しを使う場合は送信元も対応させてください。作品固有の環境変数またはシークレットを設定し、URL の形式を推測せず実際のトリガー URL を保存します。

## ログと webhook の確認

```sh
gcloud functions describe FUNCTION_NAME --gen2 --region asia-northeast1
gcloud functions logs read FUNCTION_NAME --gen2 --region asia-northeast1 --limit 50
```

Shiftr.io はデバイスのトピックを完全一致させ、POST・JSON・実際のトリガー URL を指定して webhook を有効化します。問題発生時はデバイスの送信、ブローカー・webhook の履歴、関数ログ、データベースのスキーマと権限の順に確認します。コードや設定の変更時は初回と同じデプロイ条件で更新してください。

## 参考資料

- [gcloud functions deploy](https://cloud.google.com/sdk/gcloud/reference/functions/deploy)
- [Python Functions Framework](https://github.com/GoogleCloudPlatform/functions-framework-python)
