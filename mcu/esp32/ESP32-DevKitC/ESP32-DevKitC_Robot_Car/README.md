# ESP32-DevKitC Robot Car

[English](README.md) | [Japanese](README.ja.md)

## Overview

A planned ESP32-DevKitC robot car with two DC motors, a TB6612FNG driver, and four AA batteries. Smartphone/PC control through a web app or Bluetooth is proposed.

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | ------------------------------------------ |
| [ESP32-DevKitC](https://amzn.to/4jV1hnT)   | 1    | Microcontroller; the "brain" of the robot. |
| [Micro USB cable](https://amzn.to/4nmvlf5) | 1    | To program the ESP32-DevKitC.              |

### Chassis & Mechanics

| Part | Quantity | Role / Notes |
| ------------------------------------------------------------ | ---- | ------------------------------------------------- |
| [Motor Smart Robot Car Chassis Kit](https://amzn.to/3Ggs4gN) | 1set | The body, wheels, and DC motors of the robot car. |

### Electronics & Power

| Part | Quantity | Role / Notes |
| -------------------------------------------------------- | ---- | ---------------------------------------------------- |
| [TB6612FNG Motor Driver Module](https://amzn.to/3I3CAbW) | 1    | Controls the two DC motors from the ESP32.           |
| AA Batteries (Alkaline)                                  | 4    | Power supply for the robot's motors and electronics. |

### Prototyping & Control

| Part | Quantity | Role / Notes |
| --------------------------------------- | ----- | ------------------------------------------------ |
| [Breadboard](https://amzn.to/40bMzlk)   | 1     | Circuit base for prototyping.                    |
| [Jumper Wires](https://amzn.to/45voWYC) | 1 set | For connecting all the components.               |
| Smartphone or PC                        | 1     | To control the robot via a web app or Bluetooth. |

## Development

### Hardware Development

#### Hardware and status

See [the wiring diagram](diagrams/ESP32-DevKitC_Robot_Car_bb.png). Firmware, control UI, and test results are not included. Confirm the final motor, battery, and driver ratings before assembly.

### Software Development

See the shared guides in References for setup instructions.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
