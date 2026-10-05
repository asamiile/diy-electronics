# XIAO RP2040 16x16 LED Matrix

[English](README.md) | [Japanese](README.ja.md)

## Overview

A 16×16 (256-pixel) WS2812B matrix with button-selected animations, external 5V/10A power, and a 3.3V-to-5V logic level shifter. An 8×8 matrix requires changing `LED_COUNT` from 256 to 64.

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| --------------------------------------------------- | ---- | -------------------------------------- | --- |
| [XIAO RP2040](https://amzn.to/3TrkrHs) | 1    | Micro Controller.                      |     |
| [USB-C cable](https://amzn.to/407P2xg)              | 1    | For programming and powering the XIAO. |     |

### Input & Output

| Part | Quantity | Role / Notes |
| -------------------------------------------------------------------------------------------------- | ---- | --------------- |
| [WS2812B LED RGB 16x16](https://amzn.to/4ebZCcm) or [WS2812B LED RGB 8x8](https://amzn.to/44cSo3p) | 1    | Display device. |
| [Tact Switch](https://amzn.to/4l5lGrQ)                                                             | 1    | Input button.   |

### Power System

| Part | Quantity | Role / Notes |
| ---------------------------------------------------------- | ---- | --------------------------------------- |
| [External AC adapter 5V 10A](https://amzn.to/4neewTI)      | 1    | Power supply for LEDs.                  |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)        | 1    | Connects the AC adapter to the circuit. |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ) | 1    | To stabilize the power supply.          |

### Electronics & Wiring

| Part | Quantity | Role / Notes |
| ---------------------------------------------- | ----- | ----------------------------------- |
| [Logic Level Shifter](https://amzn.to/4eeDyhr) | 1     | To convert the data signal voltage. |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2) | 1     | To protect the LED's data line.     |
| [Breadboard](https://amzn.to/40bMzlk)          | 1     | Circuit base for prototyping.       |
| [Jumper Wires](https://amzn.to/45voWYC)        | 1 set | To connect parts together.          |

## Development

### Hardware Development

#### Wiring

- Supply positive/GND → power/GND rails, matrix power, and a polarized 1000µF capacitor.
- XIAO 5V/GND → the corresponding rails.
- Shifter HV → 5V, LV → XIAO 3V3, and both GND pins → common GND.
- XIAO D6 → LVx; HVx → 330Ω → matrix DIN.
- XIAO D2 → switch → GND; enable its internal pull-up in the sketch.

See [the wiring diagram](diagrams/XIAO_RP2040_16x16_LED_Matrix_bb.png).

### Software Development

#### Software and test

Use Earle F. Philhower's RP2040 core, select XIAO RP2040, and install `Adafruit NeoPixel`. The core's board index is `https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json`. Upload [the sketch](sketch/XIAO_RP2040_16x16_LED_Matrix/XIAO_RP2040_16x16_LED_Matrix.ino), check power/GND wiring, and verify all patterns with the button. Enclosure design is not yet documented.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
