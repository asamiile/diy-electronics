# Wio Terminal Buzzer Melody

[English](README.md) | [Japanese](README.ja.md)

## Overview

Plays the programmed `ccggaagffeeddc` note sequence on `WIO_BUZZER`, using the `beats` array and `tempo=300`. The melody repeats in the main loop. Verify pitch sequence, note lengths, and rests.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

## Development

### Hardware Development

#### Hardware and dependencies

Wio Terminal and a data-capable USB-C cable; this example uses onboard hardware and needs no external sensor wiring.

Dependencies: Arduino/Wio Terminal core.

### Software Development

#### Source files

- [Wio_Terminal_Buzzer_Melody.ino](Wio_Terminal_Buzzer_Melody.ino)

Use the Wio Terminal board package. For legacy files stored outside a matching sketch directory, follow the shared guide before compiling. These instructions describe the source; compilation and physical behavior have not been verified in this documentation update.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
