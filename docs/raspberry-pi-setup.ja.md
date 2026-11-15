# Raspberry Pi 5 初期セットアップガイド

[English](raspberry-pi-setup.md) | [日本語](raspberry-pi-setup.ja.md)

Raspberry Pi 5でこのプロジェクトの環境を構築するための初期セットアップ手順です。

## 必要なツール

### OS書き込み用ツール

| 部品・環境                                         | 数量            | 用途・備考                                                              |
| -------------------------------------------------- | --------------- | ----------------------------------------------------------------------- |
| microSDカード（32〜128GB）                         | 1               | OS・プログラム・未送信JSONの保存。                                       |
| USB microSDカードリーダー                          | 1               | 開発PCでOSを書き込むために使用。PCに対応スロットがあれば不要。           |
| Raspberry Pi Imager                               | 1個             | OSイメージをmicroSDカードに書き込むツール。PC用フリーソフト。            |

### 初期設定用ツール（オプション）

| 部品・環境                                         | 数量            | 用途・備考                                                              |
| -------------------------------------------------- | --------------- | ----------------------------------------------------------------------- |
| micro-HDMI → HDMIケーブル                          | 1（必要時）     | ローカル設定・障害調査用。初期設定からSSHで運用できれば不要。           |
| モニター                                           | 1（必要時）     | 初期セットアップ時の画面表示用。SSHで運用できれば不要。                 |
| USBキーボード                                      | 1（必要時）     | 初期セットアップ時の入力用。SSHで運用できれば不要。                     |

### ネットワーク環境

| 部品・環境                                         | 数量            | 用途・備考                                                              |
| -------------------------------------------------- | --------------- | ----------------------------------------------------------------------- |
| Wi-Fiルーターとインターネット接続                  | 1環境           | Pi内蔵Wi-Fiで送信できれば、追加Wi-Fiアダプターは不要。                  |
| LANケーブル（Cat 5e以上）                          | 1（有線利用時） | 設置場所のWi-Fiが不安定な場合に使用。                                   |

## セットアップ手順

### 1. OSイメージの書き込み

1. **Raspberry Pi Imager をダウンロード**
   - [公式ページ](https://www.raspberrypi.com/software/) からダウンロード
   - Windows / macOS / Linux 対応

2. **microSDカードをPCに接続**
   - USB microSDカードリーダーを使用、またはPC内蔵スロットに挿入

3. **Imager を起動して以下を選択**
   - **Raspberry Pi Device**: Raspberry Pi 5
   - **Operating System**: Raspberry Pi OS (64-bit)
   - **Storage**: 認識されたmicroSDカード
   - ⚙️ 詳細設定で以下を設定することを推奨:
     - ホスト名、ユーザー名、パスワード
     - Wi-Fi SSID とパスワード
     - タイムゾーン（Asia/Tokyo）
     - SSH有効化

4. **書き込み実行**
   - 「書き込み」をクリック
   - 完了までお待ちください（5〜10分程度）

### 2. Raspberry Pi 5への起動

1. **microSDカードをPi 5に挿入**
   - ケースを開けてスロットに奥までしっかり挿し込む

2. **電源接続**
   - [Raspberry Pi 27W USB-C Power Supply](https://www.raspberrypi.com/products/27w-power-supply/) を接続
   - Pi本体のLEDが点灯・点滅を開始

3. **起動待機**
   - 初回起動は1〜2分かかる場合があります
   - LEDの点滅が安定したら、セットアップ完了

### 3. ネットワーク接続の確認

**Wi-Fi接続（推奨）**
- Imager で事前設定した場合は自動接続
- 未設定の場合は、ディスプレイ・キーボードで手動設定、またはSSH接続後に `sudo raspi-config` で設定

**有線接続（オプション）**
- LANケーブルをRaspberry Pi 5のRJ45ポートに接続
- DHCP自動割り当てで接続（ルーター設定による）

### 4. SSH接続による運用（推奨）

ディスプレイなしでリモート管理する場合：

```bash
# Pi 5へのSSH接続（ホスト名はImagerで設定した名前に置き換え）
ssh pi@<hostname>.local
# または
ssh pi@<raspberry-pi-ip-address>

# パスワード入力（Imagerで設定したパスワード）
```

## トラブルシューティング

| 問題 | 確認項目・対処方法 |
| ---- | ---- |
| OSが書き込めない | microSDカードが正常か確認。別のPCで試す。カードリーダーの接触確認。 |
| Pi が起動しない | microSDカード挿入の向き・奥まで確認。電源ケーブル確認。LEDの点灯確認。 |
| Wi-Fi接続できない | SSID・パスワード確認。`sudo raspi-config` で再設定。近距離での接続試行。 |
| SSH接続できない | ホスト名とIPアドレス確認。ファイアウォール設定確認。ルーター設定確認。 |

## 関連資料

- [Raspberry Piの公式ドキュメント](https://www.raspberrypi.com/documentation/computers/getting-started.html)
- [SSH での接続ガイド](https://www.raspberrypi.com/documentation/computers/remote-access.html#ssh)
- [Raspberry Pi Imager ガイド](https://www.raspberrypi.com/documentation/computers/getting-started.html#using-raspberry-pi-imager)
