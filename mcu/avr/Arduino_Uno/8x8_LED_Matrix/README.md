# Arduino Uno 8x8 LED Matrix

[English](README.md) | [Japanese](README.ja.md)

## Overview

An 8×8 WS2812B LED matrix with rainbow, ripple, bouncing-ball, ocean-wave, and breathing animations, cycled by a button.

### Gallery

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/6-BWVaQY8bo/hqdefault.jpg)](https://youtu.be/6-BWVaQY8bo?si=5ha3Cig4YXMKvDc2)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/e68a6a229464473.68652fef57f01.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/3cc74e229464473.68652fef5b1e3.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/204169229464473.68652fef54ef1.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/813954229464473.68652fef55609.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/7d1379229464473.68652fef57857.jpg)

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | ------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)     | 1    | Micro Controller.               |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1    | For writing programs to Arduino |

### Input & Output

| Part | Quantity | Role / Notes |
| ---------------------------------------------- | ---- | -------------- |
| [8x8 RGB LED WS2812B](https://amzn.to/44cSo3p) | 1    | display device |
| [Tact Switch](https://amzn.to/3T0gNUF)         | 1    | Input button   |

### Power System

| Part | Quantity | Role / Notes |
| ------------------------------------------------------------------------------------------------- | ---- | ---------------------------------------- |
| [Power Supply (5V, 2A+)](https://amzn.to/4jZEIyu) or [Mobile Power Bank](https://amzn.to/45jTQ5W) | 1    | Power supply for LEDs.                   |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)                                               | 1    | Connect the AC adapter to the breadboard |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ)                                        | 1    | For power supply stabilization           |

### Prototyping & Wiring

| Part | Quantity | Role / Notes |
| ---------------------------------------------- | ----- | ---------------------------------- |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2) | 1     | For protecting the LED's data line |
| [Breadboard](https://amzn.to/40bMzlk)          | 1     | Circuit base (for prototype)       |
| [Jumper Wires](https://amzn.to/45voWYC)        | 1 set | Connecting parts together          |

## Development

### Hardware Development

#### Wiring

- External 5V supply positive/GND → breadboard rails → matrix 5V/GND.
- 1000µF capacitor across the rails with correct polarity.
- Uno D6 → 330Ω resistor → matrix DIN.
- Uno D2 → switch → Uno GND.
- Join Uno GND to external supply GND.

See [the diagram](diagrams/Fritzing/Arduino_Uno_LED_8x8_led_matrix_art_bb.png).

### Software Development

#### Software and test

Use `Adafruit NeoPixel` and [the sketch](sketch/Arduino_Uno_8x8_led_matrix/Arduino_Uno_8x8_led_matrix.ino). Verify wiring before connecting external 5V power. Check the first animation and each button-selected pattern.

Related project: [Nano ESP32 16×16 matrix](../../../esp32/Arduino_Nano_ESP32/16x16_LED_Matrix/README.md).

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

[Arduino Uno 8x8 LED Matrix - Behance](https://www.behance.net/gallery/229464473/Arduino-Uno-8x8-LED-Matrix)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
