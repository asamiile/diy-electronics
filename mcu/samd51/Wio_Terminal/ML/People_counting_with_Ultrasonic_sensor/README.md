# Wio Terminal Ultrasonic People Counting

[English](README.md) | [Japanese](README.ja.md)

## Overview

Includes collection and Edge Impulse deployment sketches. Collection uses `Ultrasonic(0)` and reports distance every 50ms at 115200 baud; distances below 200cm are printed, otherwise `-1`. Supply the exported `People_counting_with_Ultrasonic_sensor_inferencing.h` model library and `Seeed_Arduino_FreeRTOS` for deployment. Validate sensor readings and predictions using labeled examples; the exported model is not included.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |
| Ultrasonic sensor | 1 | Distance measurement |

## Development

### Hardware Development

#### Hardware and dependencies

Wio Terminal, Grove ultrasonic sensor on the port corresponding to pin 0, and a data-capable USB-C cable.

Dependencies: `Ultrasonic.h`, `TFT_eSPI`, `Seeed_Arduino_FreeRTOS`, exported Edge Impulse model.

### Software Development

#### Source files

- [data_collection.ino](data_collection/data_collection.ino)
- [model_deployment.ino](model_deployment/model_deployment.ino)

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
