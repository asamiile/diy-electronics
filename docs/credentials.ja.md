# 認証情報の設定

[English](credentials.md) | [日本語](credentials.ja.md)

作品の `credentials.h.example` を同じスケッチディレクトリの `credentials.h` にコピーし、自分の Wi-Fi・サービス認証情報を設定します。サンプルは再利用できるテンプレートとして維持してください。

Arduino Cloud の Web エディターで書き込む作品は、代わりに `arduino_secrets.h` を使います。Web エディターが Secret タブの値からこのファイルを作るためです。リポジトリには値が空の `arduino_secrets.h` だけを置きます。Device ID・Secret Key・Wi-Fi の設定は Web エディターの Secret タブにだけ入力し、ローカルのファイルには書きません。Arduino Cloud を使っていても Arduino IDE で書き込む作品は、上記のとおり `credentials.h` を使います。

Wi-Fi 認証情報、API キー、デバイスの Secret Key、Discord webhook URL、`.env`、サービスアカウント鍵は Git に含めません。説明にはプレースホルダーを使います。クラウド側の認証情報は、作品で指定した環境変数やデプロイ時のシークレット設定で管理してください。

ローカル設定を追加する前に `.gitignore` を確認し、JSON 全体ではなく対象の認証ファイルを除外します。ピン設定、時刻、しきい値などのシステム設定は認証情報のサンプルではなく、作品の設定ファイルで管理します。
