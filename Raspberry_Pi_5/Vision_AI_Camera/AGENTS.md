# AI Camera Production Module

## 1. Project Overview

このモジュールは、卒業制作のデータ収集を目的とした AI Camera の制作と制御を担当する。

- **目的**: 室内（人物の行動・骨格）および室外（飛行機・空）の観測とデータ化。
- **方針**: 映像は録画せず、解析された数値データ（座標、ラベル、照度）のみを収集し、BigQuery へ送信する。
- **設置環境**: リビング（窓際にカメラを設置）。

## 2. Hardware Stack

| パーツ名 | 役割 | 接続方式 |
| --- | --- | --- |
| Raspberry Pi 5 (16GB) | メイン処理（脳）、MediaPipe解析、GCP通信 | Wi-Fi |
| Arduino Nano ESP32 | サブ制御（目）、雲台制御、センサー集約 | USB/Wi-Fi (UDP) |
| Vision AI Module V2 | 物体検知（人・飛行機の一次判定） | I2C |
| OV5647-62 Camera | 映像入力 | Vision AI V2に接続 |
| Pan-Tilt Platform | 2軸サーボ（B0283）による自動追跡 | I2C (PCA9685) |

* Arduino Nano ESP32は以下を稼働中
  * [Smart_Lighting_Control](Arduino_Nano_ESP32/Smart_Lighting_Control/README.md)
  * [Smart_Lighting_Control_Data_Pipeline](Cloud_Functions/Smart_Lighting_Control_Data_Pipeline)

## 3. System Architecture & Data Flow

システムは「分散型構成」をとる。

### Phase 1: The Eye (Arduino Side)

- Vision AI Module V2 が物体（Person/Airplane）を検知。
- Arduino が Pan-Tilt サーボを動かし、ターゲットを中央に維持（トラッキング）。
- 照度センサーおよび音声コマンドの状態を取得。
- これらのメタデータを JSON 形式で Raspberry Pi 5 へ送信（UDP/Wi-Fi または Serial）。

### Phase 2: The Brain (Raspberry Pi Side)

- Arduino からのデータを受信。
- MediaPipe Pose を使用し、人物の 33 点の骨格座標（x, y, z）を抽出。
- 判定された行動ラベルと環境データを統合し、FastAPI（Motion Studio Backend）へ POST。
- 最終的に BigQuery へストリーミングインサート。

## 4. Data Specification (BigQuery Schema)

エージェントが生成するデータ構造は以下に従うこと。

| フィールド | 説明 |
| --- | --- |
| `timestamp` | ISO8601 形式の時刻 |
| `target_type` | `"person"` \| `"airplane"` \| `"none"` |
| `skeleton_3d` | 33 点の座標配列（JSON） |
| `action_label` | `"working"`, `"sitting"`, `"walking"`, など |
| `environmental_data` | `{ lux: number, voice_command: string }` |
| `servo_angles` | `{ pan: number, tilt: number }` |

## 5. Development Constraints & Rules

- **Non-Blocking**: Arduino/Python 共に、センサー待ちでループを止めない非ブロッキング処理を徹底すること。
- **Power Management**: サーボ駆動は外部電源(5V/4A)を前提とし、GND共通化の注意喚起をコードコメントに含めること。
- **Integration**: 既存の Smart_Lighting_Control データ（BigQuery）との結合を意識し、タイムスタンプの精度をミリ秒単位で保持すること。

## 6. Current Implementation Tasks

- Arduino Nano ESP32 から Raspberry Pi 5 へ UDP で検知データを飛ばすブリッジコードの作成。
- Pan-Tilt の追跡アルゴリズム（PID制御等）の実装。
- MediaPipe の解析負荷を Raspberry Pi 5 の 16GB メモリを活かして最適化。
