# AI Camera Production Module

## 1. Project Overview

このモジュールは、卒業制作のデータ収集を目的とした AI Camera の制作と制御を担当する。

- **目的**: 室内（人物の行動・骨格）の観測とデータ化。
- **方針**: 映像は録画せず、解析された数値データ（座標、ラベル、照度）のみを収集し、BigQuery へ送信する。
- **設置環境**: リビング（窓際にカメラを設置）。

### 実装スコープ（当面）

- **Phase 1 を優先**: Arduino Nano ESP32 側の **「目」**（Vision AI・Pan-Tilt・環境センサ・Pi への JSON 送信）のみをまず実装する。
- **音声認識は未実装**: Grove Speech Recognizer / ReSpeaker 2-Mics Pi HAT は保持しているが、**初期リリースでは入れない**（Pi 側やデータパイプラインが固まった段階で追加を検討）。

## 2. Hardware Stack

| パーツ名 | 役割 | 接続方式 |
| --- | --- | --- |
| Raspberry Pi 5 (16GB) | メイン処理（脳）、MediaPipe解析、GCP通信 | Wi-Fi |
| Arduino Nano ESP32 | サブ制御（目）、雲台制御、センサー集約 | USB/Wi-Fi (UDP) |
| Vision AI Module V2 | 物体検知（人・飛行機の一次判定） | I2C |
| OV5647-62 Camera | 映像入力 | Vision AI V2に接続 |
| Pan-Tilt Platform | 2軸サーボ（B0283）による自動追跡 | I2C (PCA9685) |
| Grove TSL2561 | 環境照度（lux） | I2C |

### 将来追加（音声・未着手）

| パーツ名 | 備考 |
| --- | --- |
| Grove - Speech Recognizer | Arduino 側。初期スコープ外。 |
| ReSpeaker 2-Mics Pi HAT | Raspberry Pi 側。初期スコープ外。 |

* Arduino Nano ESP32 は以下と連携中（リポジトリ内参照）
  * [Smart_Lighting_Control](../../Arduino_Nano_ESP32/Smart_Lighting_Control/README.md)
  * [Smart_Lighting_Control_Data_Pipeline](../../Cloud_Functions/Smart_Lighting_Control_Data_Pipeline/README.md)

## 3. System Architecture & Data Flow

システムは「分散型構成」をとる。

### Phase 1: The Eye (Arduino Side) — 当面ここまで

- Vision AI Module V2 が物体（Person/Airplane）を検知。
- Arduino が Pan-Tilt サーボを動かし、ターゲットを中央に維持（トラッキング）。
- 照度センサー（Grove TSL2561）の値を取得。
- 上記メタデータを JSON 形式で Raspberry Pi 5 へ送信（UDP/Wi-Fi または Serial）。

### Phase 2: The Brain (Raspberry Pi Side) — 目の次

- Arduino からのデータを受信。
- MediaPipe Pose を使用し、人物の 33 点の骨格座標（x, y, z）を抽出。
- 判定された行動ラベルと環境データを統合し、FastAPI（Motion Studio Backend）へ POST。
- 最終的に BigQuery へストリーミングインサート。

## 4. 開発手順

次の順序で進める。各ステップが安定してから次へ移す。

1. **AI Camera の構築**: カメラ・Vision AI Module V2・Pan-Tilt・照度センサ（Grove TSL2561）・配線・電源を組み立てる。サーボ駆動は外部電源を前提とし、GND を共通化する。
2. **Arduino での実装**: 物体検知・Pan-Tilt 制御・照度取得・Raspberry Pi 5 向け JSON の生成と送信（UDP / Wi-Fi または Serial）を実装する。
3. **動作テスト**: トラッキング、通信の継続性、例外時の挙動（非ブロッキング）を確認する。
4. **Raspberry Pi での受信検証**: 受信側でパケットを受け取り、ログまたはローカル出力でペイロード形式・レートを確認する。
5. **Phase 2 — 解析**: MediaPipe Pose 等で骨格座標・行動ラベルを付与し、セクション 5 のデータ仕様に沿ったレコード形に整える。
6. **Phase 2 — バックエンド連携**: FastAPI（Motion Studio Backend）へ POST し、スキーマとエラーハンドリングを確定する。
7. **BigQuery の構築と送信**: データセット・テーブル・スキーマ・認証（サービスアカウント等）を用意し、ストリーミングインサートまたはバッチで書き込みテストまで行う。
8. **既存データとの統合（任意）**: Smart_Lighting_Control 系データと結合する場合は、デバイス ID 等のキーとタイムスタンプ（ミリ秒精度）を揃える。

## 5. Data Specification (BigQuery Schema)

エージェントが生成するデータ構造は以下に従うこと。

| フィールド | 説明 |
| --- | --- |
| `timestamp` | ISO8601 形式の時刻 |
| `target_type` | `"person"` \| `"airplane"` \| `"none"` |
| `skeleton_3d` | 33 点の座標配列（JSON）。`target_type` が `"person"` でない場合は `null` 可。 |
| `action_label` | `"working"`, `"sitting"`, `"walking"`, など。Phase 2 以降で主に使用。 |
| `environmental_data` | `{ lux: number \| null, voice_command: string \| null }`。当面は `voice_command` を常に `null`（または省略）でよい。 |
| `servo_angles` | `{ pan: number, tilt: number }` |

## 6. Development Constraints & Rules

- **Non-Blocking**: Arduino/Python 共に、センサー待ちでループを止めない非ブロッキング処理を徹底すること。
- **Power Management**: サーボ駆動は外部電源(5V/4A)を前提とし、GND共通化の注意喚起をコードコメントに含めること。
- **Integration**: 既存の Smart_Lighting_Control データ（BigQuery）との結合を意識し、タイムスタンプの精度をミリ秒単位で保持すること。

## 7. Current Implementation Tasks

### Phase 1（優先）

- Arduino Nano ESP32 から Raspberry Pi 5 へ UDP で検知・照度センサー状態を送るブリッジコードの作成。
- Pan-Tilt の追跡アルゴリズム（PID制御等）の実装。

### Phase 2（目が安定してから）

- MediaPipe の解析負荷を Raspberry Pi 5 の 16GB メモリを活かして最適化。
- 音声入力（Grove / ReSpeaker）と `voice_command` の設計・実装。
