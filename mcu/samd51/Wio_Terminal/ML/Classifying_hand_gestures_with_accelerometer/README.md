# Wio Terminal Accelerometer Hand Gestures

[English](README.md) | [Japanese](README.ja.md)

## Overview

The deployment example in `model_training/` uses the built-in LIS3DHTR, takes three-axis samples at the model-defined interval, and runs Edge Impulse inference. Supply `Classifying_hand_gestures_with_accelerometer_inferencing.h`; the exported model and training dataset are not included. Check accelerometer initialization and compare known gestures with predictions at 115200 baud.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

## Development

### Hardware Development

#### Hardware and dependencies

Wio Terminal and a data-capable USB-C cable; this example uses onboard hardware and needs no external sensor wiring.

Dependencies: `LIS3DHTR.h`, `TFT_eSPI`, exported Edge Impulse model.

### Software Development

#### Source files

- [model_deployment.ino](model_training/model_deployment.ino)

Use the Wio Terminal board package. For legacy files stored outside a matching sketch directory, follow the shared guide before compiling. These instructions describe the source; compilation and physical behavior have not been verified in this documentation update.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../../docs/arduino-development.md)
- [TinyML environment](../../../../../docs/tinyml-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
