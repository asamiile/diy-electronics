# Wio Terminal Digital Compass

[English](README.md) | [Japanese](README.ja.md)

## Overview

A planned digital compass using Wio Terminal and an external 9-axis accelerometer/gyroscope/magnetometer.

## Bill of Materials

| Part | Quantity | Role / Notes |
| -------------------------------------------------------------------------------------------------------- | ---- | --------------------------------------------------------------------------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu)                                                                  | 1    | Main controller, display, and Wi-Fi module.                                                                           |
| [Grove - IMU 9DOF (ICM20600+AK09918)](https://www.seeedstudio.com/Grove-IMU-9DOF-ICM20600-AK09918.html) | 1    | Measures motion and orientation on 9 axes: 3-axis accelerometer, 3-axis gyroscope, and 3-axis magnetometer (compass). |
| USB Type-C Cable                                                                                         | 1    | For power and programming. Must be a data-sync cable.                                                                 |

## Development

### Hardware Development

See Bill of Materials for the required hardware.

### Software Development

#### Implementation status

The component list specifies `Grove IMU 9DOF (ICM20600+AK09918)` and a data-capable USB-C cable. Firmware, connection details, and test results are not included.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
