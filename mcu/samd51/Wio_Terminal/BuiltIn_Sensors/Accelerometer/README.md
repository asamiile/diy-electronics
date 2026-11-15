# Wio Terminal Accelerometer

[English](README.md) | [Japanese](README.ja.md)

## Overview

Reads the built-in LIS3DHTR on `Wire1`, configured at 25Hz and ±2g. Plots X/Y/Z in magenta, green-yellow, and cyan with a 50-sample window, refreshing about every 50ms. Tilt the board and confirm the three traces respond. Serial is initialized at 115200 baud.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

## Development

### Hardware Development

#### Hardware and dependencies

Wio Terminal and a data-capable USB-C cable; this example uses onboard hardware and needs no external sensor wiring.

Dependencies: `LIS3DHTR.h` and `seeed_line_chart.h`.

### Software Development

#### Source files

- [Wio_Terminal_Accelerometer.ino](Wio_Terminal_Accelerometer.ino)

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
