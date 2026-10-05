# Wio Terminal TinyML の環境準備

[English](tinyml-development.md) | [日本語](tinyml-development.ja.md)

以下は既存サンプルで使用していた環境を維持するためのコマンドです。現在のすべてのパッケージとの互換性を保証するものではありません。

```sh
conda create -n ml python=3.8
conda activate ml
pip install tensorflow
pip install librosa
conda install -c conda-forge ffmpeg
```

Edge Impulse CLI を導入・設定した後、データ収集にはデータフォワーダ、デバイスの接続にはシリアルデーモンを使います。

```sh
edge-impulse-data-forwarder
edge-impulse-daemon --clean
```

モデルとデプロイ用ライブラリは作品ごとに選択します。ボード設定とファームウェアの書き込みは [Arduino 開発手順](arduino-development.ja.md)を参照してください。

- [TinyML with Wio Terminal 講座](https://files.seeedstudio.com/wiki/Wio-Terminal-TinyML/TinyML_with_Wio_Terminal_Course_v1-3.pdf)
- [既存の Edge Impulse ファームウェア](https://github.com/Seeed-Studio/Seeed_Arduino_edgeimpulse/releases/tag/1.4.0)
