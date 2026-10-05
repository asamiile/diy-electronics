# Arduino Uno Interactive Servo Light

[English](README.md) | [Japanese](README.ja.md)

## Overview

A potentiometer controls a servo angle while an RGB LED changes color with its position: pink at 0°, purple at 90°, and light blue at 180°.

### Gallery

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/6f8129230140209.68712daf1acd3.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/47518d230140209.68712daf1e3a0.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/81a14e230140209.68712daf1c780.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/cbb114230140209.687134623844c.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/3c0d8e230140209.687134623897d.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/14e02c230140209.6871346237c0b.jpg)

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/JPDLfhR-mck/hqdefault.jpg)](https://youtu.be/JPDLfhR-mck?si=Nqr5AGdnBTtr3w_z)

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | -------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)     | 1    | Micro Controller.                |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1    | For writing programs to Arduino. |

### Input & Actuators

| Part | Quantity | Role / Notes |
| ----------------------------------------------------- | ---- | -------------------------------------------------------------------------- |
| [Servo Motor (SG90)](https://amzn.to/3TUevqn)         | 1    | The main actuator that controls the angle. This is the part you purchased. |
| [Potentiometer (10kΩ)](https://amzn.to/4eCRh1R)       | 1    | Used as a knob to set the servo's angle.                                   |
| [5mm Common Cathode RGB LED](https://amzn.to/4lmJuaE) | 1    | Light source component.                                                    |

### Prototyping & Wiring

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ----- | ----------------------------------- |
| [Resistor (220Ω)](https://amzn.to/4kMejW2) | 3     | For protecting the LED's data line. |
| [Breadboard](https://amzn.to/40bMzlk)      | 1     | Circuit base. (for prototype)       |
| [Jumper Wires](https://amzn.to/45voWYC)    | 1 set | Connecting parts together.          |

## Development

### Hardware Development

#### Wiring

- Uno 5V/GND → breadboard positive/GND rails.
- Servo signal → D9; servo power/GND → the corresponding rails.
- Potentiometer center → A0; outer pins → 5V and GND.
- Common-cathode RGB LED cathode → GND; red → resistor → D11; green → resistor → D10; blue → resistor → D5.

See [the wiring diagram](diagrams/Arduino_Uno_Interactive_Servo_Light_bb.png).

### Software Development

#### Software and test

Use `Servo` and [the project sketch](sketch/Arduino_Uno_Interactive_Servo_Light/Arduino_Uno_Interactive_Servo_Light.ino) for Arduino Uno. Power the circuit and turn the potentiometer: confirm smooth servo motion and matching color changes.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

[Arduino Uno Interactive Servo Light - Behance](https://www.behance.net/gallery/230140209/Arduino-Uno-Interactive-Servo-Light)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
