# ESP32-DevKitC Web-Controlled 2-Axis Pan-Tilt Mount

[English](README.md) | [Japanese](README.ja.md)

## Overview

A planned ESP32-DevKitC web-controlled pan/tilt mount using two SG90 servos, a bracket, an external 5V/4A supply, and a 1000µF capacitor.

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | --------------------------------------- |
| [ESP32-DevKitC](https://amzn.to/4jV1hnT)   | 1    | Microcontroller.                        |
| [Micro-USB Cable](https://amzn.to/44ZoEZa) | 1    | For programming and powering the ESP32. |

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
| [Silicone Wire (18AWG)](https://amzn.to/4lMv2sr) | 1     | Thick wire for high-current servo power (5V & GND). |

## Development

### Hardware Development

See Bill of Materials for the required hardware.

### Software Development

#### Implementation status

Only the component plan is included. Firmware, board-specific signal pins, web UI, and tested wiring are not provided. Determine the DevKitC pin assignments and servo power wiring before building; do not use the unrelated Arduino Uno wiring previously present as commented template text.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
