# Wio Terminal Light-Sensor Gestures

[English](README.md) | [Japanese](README.ja.md)

## Overview

The collection sketch prints `WIO_LIGHT` readings at 40Hz/115200 baud. Deployment samples light readings into an Edge Impulse input frame and runs classification. Supply the inference library matching the header named in the deployment sketch; it is not included. Match training and deployment sampling conditions and test labeled gestures.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

## Development

### Hardware Development

#### Hardware and dependencies

Wio Terminal and a data-capable USB-C cable; this example uses onboard hardware and needs no external sensor wiring.

Dependencies: Exported Edge Impulse inference library.

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
