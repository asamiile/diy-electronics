# Arduino 開発手順

[English](arduino-development.md) | [日本語](arduino-development.ja.md)

## 開発環境の準備

[公式インストールガイド](https://arduino.github.io/arduino-cli/latest/installation/)に従って Arduino CLI を導入するか、Arduino IDE を使用します。VS Code ではリポジトリのルートを開くと共有エディタ設定が適用されます。

以下のコマンドは作品のディレクトリから実行します。各 README に記載されたボードパッケージとライブラリを導入してください。同じチップ系列でもボード名、ピン番号、FQBN は異なります。

```sh
arduino-cli core update-index
arduino-cli board list
arduino-cli board listall
arduino-cli core list
arduino-cli core install CORE_ID
arduino-cli lib list
arduino-cli lib install "LIBRARY_NAME"
```

追加のインデックス URL が必要なボードは、メーカーが案内する URL を CLI 設定へ登録してからコアを導入します。Arduino IDE では環境設定の追加ボードマネージャ URL、ボードマネージャ、ライブラリマネージャを使用します。

## ビルドと書き込み

`FQBN`、`SKETCH_DIRECTORY`、`PORT` を、作品のボード識別子、スケッチのディレクトリ、`board list` で確認した接続ポートに置き換えます。スケッチのディレクトリと主 `.ino` ファイルの名前は一致させます。

```sh
arduino-cli compile --fqbn FQBN SKETCH_DIRECTORY
arduino-cli upload -p PORT --fqbn FQBN SKETCH_DIRECTORY
arduino-cli monitor -p PORT --config baudrate=115200
```

通信速度はスケッチの設定に合わせます。Arduino IDE では対象ボードとポートを選択し、主スケッチを開いて書き込みます。失敗時は対象ボードのブートローダ手順を確認してください。

## 既存サンプルのファイル配置

一部の既存サンプルは、スケッチ名と異なるカテゴリのディレクトリに `.ino` を直接保存しています。Arduino CLI では、主スケッチと同名の一時ディレクトリを作り、`.ino` と必要な関連ファイルをコピーして、そのディレクトリをビルドします。Arduino IDE は開く際に同名のフォルダ作成を案内する場合があります。リポジトリ内のソース名は維持します。この準備だけでは不足するライブラリやモデルは追加されません。

## 実機テスト前の確認

作品固有の配線と電源条件に従い、極性と共通 GND を確認します。LED・モータの外部電源は、作品で指定された構成を維持してください。ビルド結果と実機テスト結果は分けて記録します。

## 参考資料

- [ビルドコマンド](https://arduino.github.io/arduino-cli/latest/commands/arduino-cli_compile/)
- [書き込みコマンド](https://arduino.github.io/arduino-cli/latest/commands/arduino-cli_upload/)
