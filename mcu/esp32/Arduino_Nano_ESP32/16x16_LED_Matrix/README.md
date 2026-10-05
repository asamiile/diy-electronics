# Arduino Nano ESP32 16x16 LED Matrix

[English](README.md) | [Japanese](README.ja.md)

## Overview

An Arduino Nano ESP32 version of the Arduino Uno LED matrix project, using a 16×16 WS2812B display and a button to cycle animations. [Animation examples](https://www.behance.net/gallery/229464473/Arduino-Uno-8x8-LED-Matrix).

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| --------------------------------------------- | ---- | -------------------------------------------- | --- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1    | Microcontroller.                             |     |
| [USB-C cable](https://amzn.to/407P2xg)        | 1    | For programming and powering the Nano ESP32. |     |

### Input & Output

| Part | Quantity | Role / Notes |
| -------------------------------------------------------------------------------------------------- | ---- | --------------- |
| [WS2812B LED RGB 16x16](https://amzn.to/4ebZCcm) or [WS2812B LED RGB 8x8](https://amzn.to/44cSo3p) | 1    | Display device. |
| [Tact Switch](https://amzn.to/4l5lGrQ)                                                             | 1    | Input button.   |

### Power System

| Part | Quantity | Role / Notes |
| -------------------------------------------------------------- | ---- | --------------------------------------- |
| [External AC adapter 5V 4A or Higher](https://amzn.to/4neewTI) | 1    | Power supply for LEDs.                  |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)            | 1    | Connects the AC adapter to the circuit. |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ)     | 1    | To stabilize the power supply.          |

### Electronics & Wiring

| Part | Quantity | Role / Notes |
| ---------------------------------------------- | ----- | ------------------------------------------ |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2) | 1     | For protecting the LED matrix's data line. |
| [Breadboard](https://amzn.to/40bMzlk)          | 1     | Circuit base for prototyping.              |
| [Jumper Wires](https://amzn.to/45voWYC)        | 1 set | To connect parts together.                 |

## Development

### Hardware Development

#### Wiring

- External 5V supply: DC jack positive/negative → breadboard positive/GND rails → matrix 5V/GND.
- Place a 1000µF capacitor across the rails with the correct polarity.
- Nano D6 → 330Ω resistor → matrix DIN.
- Nano D2 → tactile switch → Nano GND.
- Join Nano GND to the external supply GND.

### Software Development

#### Software

Use Arduino ESP32 Boards and `Adafruit NeoPixel`. Open [the sketch](sketch/Arduino_Nano_ESP32_16x16_LED_Matrix/Arduino_Nano_ESP32_16x16_LED_Matrix.ino). Use the Nano ESP32's board configuration, not another ESP32 board's pin numbering.

### Test

#### Test

Check wiring, apply the external 5V supply, and confirm the first animation appears. Press the switch to cycle patterns.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
