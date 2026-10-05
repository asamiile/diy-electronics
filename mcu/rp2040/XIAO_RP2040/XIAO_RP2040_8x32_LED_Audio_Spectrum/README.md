# XIAO RP2040 LED Audio Spectrum

[English](README.md) | [Japanese](README.ja.md)

## Overview

A planned XIAO RP2040 audio-spectrum display using a Grove microphone and an 8×32 WS2812B matrix.

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| --------------------------------------------------- | ---- | -------------------------------------- | --- |
| [XIAO RP2040](https://amzn.to/3TrkrHs) | 1    | Micro Controller.                      |     |
| [USB-C cable](https://amzn.to/407P2xg)              | 1    | For programming and powering the XIAO. |     |

### Input & Output

| Part | Quantity | Role / Notes |
| ---------------------------------------------------- | ---- | ------------------- | --- |
| [8x32 RGB LED WS2812B](https://amzn.to/4nlV9rJ)      | 1    | Display device      |     |
| [Microphone Module INMP441](https://amzn.to/3FUDMxC) | 1    | Audio Input sensor. |     |

### Power System

| Part | Quantity | Role / Notes |
| ---------------------------------------------------------- | ---- | --------------------------------------- | --- |
| [External AC adapter (5V10A)](https://amzn.to/4emi9mw)     | 1    | Main power supply for the LEDs.         |     |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)        | 1    | Connects the AC adapter to the circuit. |     |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ) | 1    | To stabilize the power supply.          |     |

### Prototyping & Wiring

| Part | Quantity | Role / Notes |
| ---------------------------------------------- | ----- | ------------------------------- | --- |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2) | 1     | To protect the LED's data line. |     |
| [Breadboard](https://amzn.to/40bMzlk)          | 1     | Circuit base for prototyping.   |     |
| [Jumper Wires](https://amzn.to/45voWYC)        | 1 set | To connect parts together.      |     |

## Development

### Hardware Development

See Bill of Materials for the required hardware.

### Software Development

#### Implementation status

The component plan and diagram files are included; wiring instructions, firmware, and test results are not. The diagram filenames begin with `ESP32-DevKitC`, so they must be reviewed for the XIAO RP2040 pin mapping before use. The proposed parts include an external 5V/2A+ supply, a level shifter, a 1000µF capacitor, and a data-line resistor.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
