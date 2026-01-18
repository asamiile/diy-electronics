# TinyML with WioTerminal

## Usage

1. Create a new virtual environment

```
conda create -n ml python=3.8
```

2. Activate the virtual environment

```
conda activate ml
```

3. Install Packages.

```
pip install tensorflow
pip install librosa
conda install -c conda-forge ffmpeg
```

4. Edge Impulse CLI

- Data forwarde

```
edge-impulse-data-forwarder
```

- Serial daemon

```
edge-impulse-daemon --clean
```


### Notebook

- [weather_prediction_final.ipynb](https://colab.research.google.com/drive/1gkT_LavFmRMy5RRUNolobtM4OkoFcb15?usp=sharing)

## Reference

- [TinyML with Wio Terminal](https://files.seeedstudio.com/wiki/Wio-Terminal-TinyML/TinyML_with_Wio_Terminal_Course_v1-3.pdf)
- [Wio Terminal Edge Impulse firmware](https://github.com/Seeed-Studio/Seeed_Arduino_edgeimpulse/releases/tag/1.4.0)
