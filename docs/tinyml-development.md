# Wio Terminal TinyML environment

[English](tinyml-development.md) | [日本語](tinyml-development.ja.md)

These commands preserve the environment used by the existing examples; they are not a guarantee of compatibility with every current package version.

```sh
conda create -n ml python=3.8
conda activate ml
pip install tensorflow
pip install librosa
conda install -c conda-forge ffmpeg
```

After installing and configuring the Edge Impulse CLI, use the data forwarder for data collection or the serial daemon to connect the device:

```sh
edge-impulse-data-forwarder
edge-impulse-daemon --clean
```

Choose the model and deployment library for the individual project. Follow the [Arduino development guide](arduino-development.md) for board setup and firmware upload.

- [TinyML with Wio Terminal course](https://files.seeedstudio.com/wiki/Wio-Terminal-TinyML/TinyML_with_Wio_Terminal_Course_v1-3.pdf)
- [Existing Edge Impulse firmware release](https://github.com/Seeed-Studio/Seeed_Arduino_edgeimpulse/releases/tag/1.4.0)
