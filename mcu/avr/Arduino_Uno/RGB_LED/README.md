# Arduino Uno RGB LED

[English](README.md) | [Japanese](README.ja.md)

## Overview

An interactive desk light with a common-cathode RGB LED and a tactile switch. The modes include pink, yellow/orange, green, blue, purple, and a smooth color-fade animation, returning to off after the cycle. Use the sketch as the source of truth for the actual color values.

### Gallery

![](https://mir-cdn.behance.net/v1/rendition/project_modules/max_3840_webp/6226e6229627251.6867e0d1bb8c7.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/ba3420229627251.6867e0d1bacc1.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/5d5c6a229627251.6867e0d1bb195.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/938d8b229627251.6867e0d1bc328.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/e95a45229627251.6867e0d1bc881.jpg)

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/HZucglmYSCs/hqdefault.jpg)](https://youtu.be/HZucglmYSCs?si=rXBTJWtdmKFi_rcF)

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/dp0oIES4NKo/hqdefault.jpg)](https://youtu.be/dp0oIES4NKo?si=npvw56pW3KhWuZMV)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/4fc92f229627251.6867e0d0b3b1b.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/fbf47c229627251.6867e0d0b35f8.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/eb167d229627251.6867e0d0b3081.jpg)

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | -------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)     | 1    | Micro Controller.                |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1    | For writing programs to Arduino. |

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

- Common cathode → Uno GND.
- D11 (PWM) → 220Ω → red; D10 (PWM) → 220Ω → blue; D9 (PWM) → 220Ω → green.
- D2 → switch → GND. Use `pinMode(2, INPUT_PULLUP)`; no external pull-up is shown.

See [the wiring diagram](diagrams/Arduino_Uno_RGB_LED_bb.png).

### Software Development

#### Software and test

Upload [the sketch](sketch/Arduino_Uno_RGB_LED/Arduino_Uno_RGB_LED.ino) to Arduino Uno. Initially the LED is off. Press the button to cycle all colors and the fade animation, then return to off.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

[Arduino Uno Chroma LED - Behance](https://www.behance.net/gallery/229627251/Arduino-Uno-Chroma-LED)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
