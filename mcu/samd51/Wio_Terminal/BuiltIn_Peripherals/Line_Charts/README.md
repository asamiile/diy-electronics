# Wio Terminal Line Charts

[English](README.md) | [Japanese](README.ja.md)

## Overview

Displays random values on a rolling line chart, retaining up to 50 samples and updating about every 50ms. This is synthetic chart data, not sensor measurements. Confirm the chart updates and its oldest sample is removed once the window fills.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

## Development

### Hardware Development

#### Hardware and dependencies

Wio Terminal and a data-capable USB-C cable; this example uses onboard hardware and needs no external sensor wiring.

Dependencies: `seeed_line_chart.h` / Wio-compatible chart library.

### Software Development

#### Source files

- [Wio_Terminal_Line_Charts.ino](Wio_Terminal_Line_Charts.ino)

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
