# Wio Terminal Audio Scene Recognition

[English](README.md) | [Japanese](README.ja.md)

## Overview

The deployment sketch performs microphone inference with four slices per model window and prints results at 115200 baud. Supply the exported `Audio_scene_recognition_with_microphone_inferencing.h` library. The project also includes `converter.py` for preprocessing; inspect its input/output settings before running it. The model export is not included. Validate audio capture and predictions against labeled scenes.

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

- [model_deployment.ino](model_deployment/model_deployment.ino)
- [converter.py](converter.py)

Use the Wio Terminal board package. For legacy files stored outside a matching sketch directory, follow the shared guide before compiling. These instructions describe the source; compilation and physical behavior have not been verified in this documentation update.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../../docs/arduino-development.md)
- [TinyML environment](../../../../../docs/tinyml-development.md)

## License

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Support

If you find this helpful, consider supporting the work:

[![BuyMeACoffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://buymeacoffee.com/asamiile)

## Author

[Asami.K](https://asami.tokyo/)
