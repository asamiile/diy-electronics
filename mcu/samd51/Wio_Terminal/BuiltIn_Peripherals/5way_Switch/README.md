# Wio Terminal 5-Way Switch

[English](README.md) | [Japanese](README.ja.md)

## Overview

Reads `WIO_5S_UP`, `WIO_5S_DOWN`, `WIO_5S_LEFT`, `WIO_5S_RIGHT`, and `WIO_5S_PRESS` as active-low inputs. The code draws the corresponding direction on the LCD, with one-second delays. Verify all five input states; display behavior must be checked on hardware because the loop also pushes a sprite buffer.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

## Development

### Hardware Development

#### Hardware and dependencies

Wio Terminal and a data-capable USB-C cable; this example uses onboard hardware and needs no external sensor wiring.

Dependencies: `TFT_eSPI`.

### Software Development

#### Source files

- [Wio_Terminal_5way_Switch.ino](Wio_Terminal_5way_Switch.ino)

Use the Wio Terminal board package. For legacy files stored outside a matching sketch directory, follow the shared guide before compiling. These instructions describe the source; compilation and physical behavior have not been verified in this documentation update.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../../docs/arduino-development.md)

## License

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Support

If you find this helpful, consider supporting the work:

[![BuyMeACoffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://buymeacoffee.com/asamiile)

## Author

[Asami.K](https://asami.tokyo/)
