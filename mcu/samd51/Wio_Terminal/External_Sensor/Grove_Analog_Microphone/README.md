# Wio Terminal Grove Analog Microphone

[English](README.md) | [Japanese](README.ja.md)

## Overview

Diagnoses raw microphone input on A0. Each batch contains 128 samples with 5000µs delay (about 200Hz nominal), reporting min/max/mean, peak-to-peak, and RMS at 115200 baud. It flags peak-to-peak below 20 as very low, below 100 as low, and above 500 as good. Compare quiet/sound conditions; this is an ADC diagnostic, not audio-band recording.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |
| Grove analog microphone | 1 | External audio input |

## Development

### Hardware Development

#### Hardware and dependencies

Wio Terminal, Grove analog microphone connected to A0, and a data-capable USB-C cable.

Dependencies: Arduino/Wio Terminal core.

### Software Development

#### Source files

- [audio_test.ino](sketch/audio_test/audio_test.ino)

Use the Wio Terminal board package. For legacy files stored outside a matching sketch directory, follow the shared guide before compiling. These instructions describe the source; compilation and physical behavior have not been verified in this documentation update.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
