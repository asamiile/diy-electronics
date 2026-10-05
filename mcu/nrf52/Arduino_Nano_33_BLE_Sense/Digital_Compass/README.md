# Arduino Nano 33 BLE Sense

[English](README.md) | [Japanese](README.ja.md)

## Overview

A digital compass using the Arduino Nano 33 BLE Sense's built-in 9-axis IMU. The accelerometer, gyroscope, and magnetometer support a heading display from 0–360° in Serial Monitor. The compass sketch is not included in this repository.

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| ---------------------------------------------------- | ---- | -------------------------------------------------------------------------- |
| [Arduino Nano 33 BLE Sense](https://amzn.to/3J0t7Te) | 1    | The microcontroller and 9-axis sensor are integrated on this single board. |
| [Micro USB Cable](https://amzn.to/4nmvlf5)           | 1    | For programming the board and supplying power from a PC.                   |

## Development

### Hardware Development

#### Hardware and software

No external sensor wiring is required. Use the Arduino Mbed OS Nano Boards package, select Arduino Nano 33 BLE Sense, and install `Arduino_LSM9DS1`. Obtain or implement `Arduino_Nano_33_BLE_Sense_Digital_Compass.ino` before uploading.

### Software Development

See the shared guides in References for setup instructions.

### Test

#### Test

Use 9600 baud, or the rate declared by the sketch. Rotate the board and confirm that the heading changes.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
