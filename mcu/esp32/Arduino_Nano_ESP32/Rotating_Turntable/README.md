# Arduino Nano ESP32 Rotating Turntable

[English](README.md) | [Japanese](README.ja.md)

## Overview

A planned rotating platform controlled by Arduino Nano ESP32 and a TB6612FNG motor driver. A 10kΩ potentiometer sets speed and a tactile switch changes direction. The proposed geared DC motor is approximately 30–60 RPM.

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| --------------------------------------------- | ---- | ---------------------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1    | The "brain" that controls the motor's speed and direction. |
| [USB-C Cable](https://amzn.to/4lU4bdZ)        | 1    | For programming and powering the Nano ESP32.               |

### Input & Output

| Part | Quantity | Role / Notes |
| ------------------------------------------------ | ---- | --------------------------------------------- |
| [Potentiometer (10kΩ)	](https://amzn.to/4eCRh1R) | 1    | A knob to adjust the rotation speed.          |
| [Tactile Switch	](https://amzn.to/4l5lGrQ)       | 1    | A button to change the direction of rotation. |

### Drivetrain

| Part | Quantity | Role / Notes |
| ----------------------------------------------------- | ---- | ------------------------------------------------------ |
| [Geared DC Motor)	]()                                 | 1    | The motor that rotates the platform (e.g., 30-60 RPM). |
| [Motor Driver (TB6612FNG)		](https://amzn.to/3I3CAbW) | 1    | Allows the Nano ESP32 to control the motor.            |

### Mechanical Parts

| Part | Quantity | Role / Notes |
| ----------------------- | ----- | ------------------------------------------------- |
| [Lazy Susan Bearing)]() | 1     | Ensures the platform spins smoothly.              |
| [Circular Plates]()     | 2     | For the base and the top rotating platform.       |
| [Motor Mount Bracket]() | 1     | To securely attach the motor to the base.         |
| [Shaft Coupler]()       | 1     | To connect the motor's shaft to the top platform. |
| [Screws and Spacers]()  | 1 set | For assembling all the parts.                     |

### Power System

| Part | Quantity | Role / Notes |
| ---------------------------------- | ---- | ------------------------------------------------------------------------------- |
| [AC Adapter (9V or 12V)]()         | 1    | A dedicated power supply for the motor. Must match your chosen motor's voltage. |
| [DC Jack](https://amzn.to/3IdZI7k) | 1    | The socket to connect the AC adapter to the circuit.                            |

### Electronics & Wiring

| Part | Quantity | Role / Notes |
| --------------------------------------- | ----- | ----------------------------------- |
| [Breadboard](https://amzn.to/40bMzlk)   | 1     | For assembling the control circuit. |
| [Jumper Wires](https://amzn.to/45voWYC) | 1 set | To connect the components.          |

## Development

### Hardware Development

See Bill of Materials for the required hardware.

### Software Development

#### Implementation status

The bill of materials is a planning draft. Wiring, firmware, and test results are not included. Match the proposed 9V or 12V motor supply to the selected motor; the mechanical design uses a bearing, two plates, a motor bracket, and a shaft coupler.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
