# Wio Terminal Buttons

[English](README.md) | [Japanese](README.ja.md)

## Overview

Reads the three active-low buttons `WIO_KEY_A`, `WIO_KEY_B`, and `WIO_KEY_C`, drawing the selected button name on the LCD. The loop uses one-second delays and also pushes a sprite buffer. Check each input and actual LCD output independently. The source filename retains its original `Wio_Teaminal` spelling.

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

- [Wio_Teaminal_Button.ino](Wio_Teaminal_Button.ino)

Use the Wio Terminal board package. For legacy files stored outside a matching sketch directory, follow the shared guide before compiling. These instructions describe the source; compilation and physical behavior have not been verified in this documentation update.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
