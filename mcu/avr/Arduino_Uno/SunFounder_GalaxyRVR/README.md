# SunFounder_GalaxyRVR

[English](README.md) | [Japanese](README.ja.md)

## Overview

An Arduino Uno R3 rover with an ESP32 AI Camera, supporting manual driving, ultrasonic obstacle avoidance, IR/ultrasonic target following, camera tilt, and telemetry. RGB feedback shows forward in green, reverse in red, turns in yellow, and idle as breathing blue.

## Bill of Materials

| Part | Quantity | Role / Notes |
| ---------------------------------------------------------------------- | ---- | ----------------------------------------------------- |
| [SunFounder GalaxyRVR](https://amzn.to/454yN6I)                                | 1    | Includes Arduino Uno R3, and All Parts.           |

## Development

### Hardware Development

See Bill of Materials for the required hardware.

### Software Development

#### Configuration

Use `SunFounder AI Camera`, `SoftPWM`, and `Servo`. Open [the sketch](sketch/SunFounder_GalaxyRVR/SunFounder_GalaxyRVR.ino). Configure `STA_SSID` and `STA_PASSWORD` in its neighboring `credentials.h`, using 2.4GHz Wi-Fi for STA mode.

#### Controller and verification

Install [SunFounder Controller](https://play.google.com/store/apps/details?id=com.sunfounder.sunfoundercontroller&hl=en), connect to the IP address reported in Serial Monitor, and assign:

- Region D: camera-tilt slider.
- Region E: obstacle-avoidance switch.
- Region F: following-mode switch.
- Region J: light master switch.
- Region K/Q: manual-drive throttle.

Upload to the SunFounder R3 board and verify manual/autonomous mode changes, obstacle handling, following distance, camera movement, battery telemetry, sensor distance, and LED feedback.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)
- [Credentials](../../../../docs/credentials.md)

- [SunFounder - Programming with Arduino IDE](https://docs.sunfounder.com/projects/galaxy-rvr/en/latest/programming_arduino.html)
- [GitHub - GalaxyRVR](https://github.com/sunfounder/galaxy-rvr/tree/main)
- [GitHub - SunFounder AI Camera Library for Arduino](https://github.com/sunfounder/SunFounder_AI_Camera/blob/main/README.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
