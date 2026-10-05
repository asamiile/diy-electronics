# XIAO ESP32C3 Sunrise and Sunset Alarms with Adafruit IO

[English](README.md) | [Japanese](README.ja.md)

## Overview

A planned sunrise/sunset alarm using XIAO ESP32C3 and a Grove Digital Light Sensor. Ambient light is used to detect dawn/dusk and send alerts to Adafruit IO, rather than relying on fixed alarm times.

## Bill of Materials

| Part | Quantity | Role / Notes |
| ------------------------------------------------------------------------------------------------------------ | ---- | --------------------------------------------------------------------------- |
| [XIAO ESP32C3](https://amzn.to/45T6bNg)                                                                      | 1    | The brain of the alarm. It will process sensor data and send notifications. |
| [Grove Digital Light Sensor](https://jp.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html) | 1    | Measures the ambient light to detect sunrise and sunset.                    |
| [Grove Shield for Seeeduino XIAO](https://amzn.to/479T6S5)                                                   | 1    | Replaces the breadboard and wires for a simple, reliable connection.        |
| [USB-C Cable](https://amzn.to/4lU4bdZ)                                                                       | 1    | For programming and powering the XIAO ESP32C3.                              |
| [Mobile Battery](https://amzn.to/45jTQ5W)                                                                    | 1    | Powers the device, allowing you to place it anywhere.                       |

## Development

### Hardware Development

#### Assembly plan and status

Solder the supplied headers to the XIAO, insert it into the Grove Shield, connect the light sensor through a Grove cable, and power it by USB-C/mobile battery. Confirm the sensor's required interface before selecting the Grove port. Firmware, dashboard details, and test results are not included.

### Software Development

See the shared guides in References for setup instructions.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)
- [Adafruit IO setup](../../../../docs/adafruit-io.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
