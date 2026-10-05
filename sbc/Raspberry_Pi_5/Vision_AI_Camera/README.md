# Arduino Nano ESP32 Vision AI Camera

[English](README.md) | [Japanese](README.ja.md)

## Overview

An in-progress distributed camera system for indoor behavior/skeleton observations. Raspberry Pi 5 is the analysis/backend node and Arduino Nano ESP32 is the sensor/pan-tilt controller. The intended output is numeric metadata in BigQuery; video is not recorded.

## Bill of Materials

### SBC

| Part | Quantity | Role / Notes |
| ------------------------------ | ---- | --------------------------------------------------- |
| [Raspberry Pi 5 (16GB)](https://amzn.to/4sqqta4)       | 1    | Handles video analysis and object detection.        |

### MCU

| Part | Quantity | Role / Notes |
| ------------------------------------------------------------------------------------- | ---- | ------------------------------------------------------------------------ |
| [Arduino Nano ESP32](https://amzn.to/452q2dH)                                         | 1    | Controls sensors and the pan-tilt mount.                                              |
| [USB C Cable](https://amzn.to/4kmNVTn)                                                | 1    | For programming and powering the Nano ESP32.                             |
| [AC/DC Adapter (5V/4A)]()                                                             | 1    | Provides stable power from a wall outlet.                                |

### Camera

| Part | Quantity | Role / Notes |
| ------------------------------------------------------------------------------------- | ---- | ------------------------------------------------------------------------ |
| [Grove - Vision AI Module V2](https://amzn.to/41Mx9Vs)                                | 1    | Handles AI image recognition and camera control.                         |
| [OV5647-62 FOV Camera Module](https://amzn.to/41IEmWF)                                | 1    | Captures video. Connects directly to the Vision AI module.               |
| Grove Cable                                                                           |      | Should be included with your Grove - Vision AI Module V2.                |
| [Grove Shield for Arduino Nano](https://amzn.to/3UnUJnH)                              | 1    | Allows for easy, solder-free connection of the Grove sensor to the Nano. |
| [Pan Tilt Platform for Raspberry Pi & Nvidia Jetson Cameras](https://amzn.to/3OeokzX) | 1    | Provides motorized pan-tilt control for camera movement and positioning. |

## Development

### Hardware Development

#### Scope and hardware

Phase 1 prioritizes the Arduino-side eye: Vision AI Module V2 with OV5647-62 camera, B0283 pan/tilt servos through PCA9685, and Grove TSL2561 light sensing. Send detections and sensor data as JSON to the Pi using UDP/Wi-Fi or serial. Use external 5V/4A servo power and common GND.

Phase 2 receives metadata, adds MediaPipe Pose's 33-point skeleton and action labels, and posts to FastAPI (Motion Studio Backend) before BigQuery insertion. Speech Recognizer/ReSpeaker input is a future addition and is outside the initial scope.

### Software Development

#### Data and development plan

Keep `timestamp` in ISO 8601 with millisecond precision, `target_type` as `person`/`airplane`/`none`, `skeleton_3d` as 33 coordinate points (nullable for non-person targets), `action_label`, `environmental_data` with `lux` and nullable/omitted `voice_command`, and `servo_angles` with `pan`/`tilt`.

Assemble hardware, implement non-blocking Arduino detection/tracking/lighting acquisition, verify communication and exceptions, then validate Pi reception before adding analysis and backend integration. Align device IDs and timestamps when combining with [lighting data](../../../cloud/Cloud_Functions/Smart_Lighting_Control_Data_Pipeline/README.md).

Firmware and Pi receiver code are not included here. See [the project constraints](AGENTS.md) for the detailed phased plan.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
