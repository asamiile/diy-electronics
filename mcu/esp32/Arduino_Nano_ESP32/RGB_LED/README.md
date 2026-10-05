# Arduino Nano ESP32 RGB LED

[English](README.md) | [Japanese](README.ja.md)

## Overview

An Arduino Nano ESP32 adaptation of the Arduino Uno RGB desk light, controlled by both a tactile switch and Arduino IoT Cloud. [Lighting examples](https://www.behance.net/gallery/229627251/Arduino-Uno-Chroma-LED).

### Gallery

![](https://mir-s3-cdn-cf.behance.net/project_modules/fs_webp/032252232222857.68984c6f142d3.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/hd_webp/1095e9232222857.68984c6f139e4.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/fs_webp/5c3228232222857.68984c6f148b3.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/fs_webp/3b2910232222857.68984c6f150ae.jpg)

[![Image from Gyazo](https://i.gyazo.com/1ab5feb8a2e3802c23280b4c67604f26.png)](https://gyazo.com/1ab5feb8a2e3802c23280b4c67604f26)

[![Image from Gyazo](https://i.gyazo.com/5e2e5a0bee07afac0b680496551c4410.png)](https://gyazo.com/5e2e5a0bee07afac0b680496551c4410)

[![Image from Gyazo](https://i.gyazo.com/94192f1e5d906190a007f4fb6ecdc9c7.png)](https://gyazo.com/94192f1e5d906190a007f4fb6ecdc9c7)

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| --------------------------------------------- | ---- | -------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1    | Microcontroller.                             |
| [USB-C Cable](https://amzn.to/4lU4bdZ)        | 1    | For programming and powering the Nano ESP32. |

### Input & Output

| Part | Quantity | Role / Notes |
| ------------------------------------------------------- | ---- | ------------------------------------------------- |
| [5mm Common Cathode RGB LED](https://amzn.to/4lmJuaE)   | 1    | Light source component.                           |
| [Tactile Switch (Push Button)](https://amzn.to/3T0gNUF) | 1    | Used for ON/OFF control and for switching colors. |

### Prototyping & Wiring

| Part | Quantity | Role / Notes |
| ------------------------------------------------------- | ----- | ------------------------------------------------- |
| [Resistor (220Ω)](https://amzn.to/4kMejW2) | 3     | For protecting the LED's data line. |
| [Breadboard](https://amzn.to/40bMzlk)      | 1     | Circuit base. (for prototype)       |
| [Jumper Wires](https://amzn.to/45voWYC)    | 1 set | Connecting parts together.          |

## Development

### Hardware Development

#### Wiring

- Common-cathode RGB LED: cathode → GND; red → 220Ω → D2; green → 220Ω → D3; blue → 220Ω → D4.
- Switch: D5 → switch → GND.

### Software Development

#### Arduino Cloud configuration

Register the Nano ESP32, create a Thing, and configure 2.4GHz Wi-Fi. Add `colorMode` as an Integer Number variable with Read & Write permissions. Replace the generated Thing sketch with [this sketch](sketch/Arduino_Nano_ESP32_RGB_LED/Arduino_Nano_ESP32_RGB_LED.ino), preserving the generated device configuration.

Create a dashboard Stepper linked to `colorMode`, with a range of 0–6. Optionally add a Value widget. If upload fails, follow the board's bootloader procedure; the original procedure uses two reset presses followed by one reset press.

### Test

#### Test

Once online, Mode 0 leaves the LED off. Incrementing to Mode 1 turns it pink; subsequent changes cycle colors. Check that pressing the physical switch updates the dashboard and dashboard changes update the LED.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)
- [Credentials](../../../../docs/credentials.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
