# Arduino Nano ESP32 Web-Controlled 2-Axis Pan-Tilt Mount

[English](README.md) | [Japanese](README.ja.md)

## Overview

A planned browser-controlled two-axis pan/tilt mount using Arduino Nano ESP32 and two SG90 servos. The documented firmware and React control UI are not implemented in this repository; the sketch file is a placeholder.

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| --------------------------------------------- | ---- | -------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1    | Microcontroller.                             |
| [USB-C Cable](https://amzn.to/4lU4bdZ)        | 1    | For programming and powering the Nano ESP32. |

### Mechanics & Actuators

| Part | Quantity | Role / Notes |
| ------------------------------------------------------- | ---- | ----------------------------------------------------- |
| [Servo Motor (SG90)](https://amzn.to/3TUevqn)           | 2    | One for pan (horizontal) and one for tilt (vertical). |
| [2-Axis Pan-Tilt Bracket Kit)](https://amzn.to/44J3H3s) | 1    | The mechanical frame for mounting the two servos.     |

### Power System

| Part | Quantity | Role / Notes |
| ---------------------------------------------------------- | ---- | ------------------------------------------------- |
| [AC Adapter (5V 4A)](https://amzn.to/4lOymDh)              | 1    | A dedicated external power supply for the servos. |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)        | 1    | Socket to connect the AC adapter to the circuit.  |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ) | 1    | To stabilize the servo power supply.              |

### Prototyping & Wiring

| Part | Quantity | Role / Notes |
| ------------------------------------------------ | ----- | --------------------------------------------------- |
| [Breadboard](https://amzn.to/40bMzlk)            | 1     | Circuit base for prototyping.                       |
| [Jumper Wires](https://amzn.to/45voWYC)          | 1 set | For connecting signal lines.                        |

## Development

### Hardware Development

#### Wiring plan

Use the external 5V/4A servo supply and a 1000µF capacitor across the power rails. Connect both servo power wires to the positive rail and their ground wires to GND. Pan signal uses GPIO12, tilt signal uses GPIO13, and Nano GND joins the external GND. See [the diagram](diagrams/Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount_bb.png).

### Software Development

#### Software plan

Use Arduino ESP32 Boards and `ESP32Servo`. The [sketch placeholder](sketch/Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount/Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount.ino) has a neighboring credential example.

The planned React UI is hosted in the board's flash memory: pan/tilt sliders from 0–180°, a center button at 90°, angle display, and commands such as `/move?servo=pan&angle=120`. UI source and flash-upload instructions are not yet included.

### Test

#### Planned test

After implementation, connect servo power, monitor at 115200 baud, reset the board, and open the reported IP address from a browser on the same Wi-Fi network. Confirm both axes respond.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)
- [Credentials](../../../../docs/credentials.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
