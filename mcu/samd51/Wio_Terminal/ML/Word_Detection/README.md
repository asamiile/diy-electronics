# Wio Terminal Edge Impulse Word Detection

[English](README.md) | [Japanese](README.ja.md)

## Overview

An in-progress Wio Terminal word-detection example using Edge Impulse. The [deployment sketch](sketch/Word_Detection/Word_Detection.ino) is included; follow the linked tutorial for model preparation and supply its required inference library.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

## Development

### Hardware Development

See Bill of Materials for the required hardware.

### Software Development

#### Setup and test

Use the shared TinyML guide for environment setup and the Arduino guide for upload. Verify model input, inference output, and serial behavior against the model you deploy.

- [Edge Impulse getting-started tutorial](https://wiki.seeedstudio.com/Getting_started_wizard/#getting-started-with-edge-impulse)

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
