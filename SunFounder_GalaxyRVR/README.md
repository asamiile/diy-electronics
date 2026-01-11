# SunFounder_GalaxyRVR

## Overview

- SunFounder_GalaxyRVR is an Arduino-based Mars Rover exploration project. Powered by an Arduino Uno R3 and an ESP32-based AI Camera, this rover supports both manual remote control and autonomous driving modes.
- This project focuses on integrating real-time telemetry, sensor-based autonomy, and interactive visual feedback, developed with a front-end engineer's perspective on state management and event-driven logic.


### Features
- **Hybrid Control System**: Toggle between manual RC mode and autonomous exploration modes via a mobile app.
- **Autonomous Obstacle Avoidance**: Utilizes ultrasonic sensors to detect barriers, executing escape maneuvers (reverse and turn) when paths are blocked.
- **Target Following Mode**: Uses IR sensors and ultrasonic ranging to maintain a set distance from a moving object.
- **Camera Tilt Control**: Real-time camera gimbal adjustment via a slider widget (Region D).
- **Interactive RGB Feedback**: Dynamic LED state indicators (Forward: Green, Backward: Red, Turning: Yellow, Idle: Breathing Blue).
- **Real-time Telemetry**: Monitoring of battery voltage and sensor distance data through the SunFounder Controller app.


### Bill of Materials

| Part Type                                                              | Unit | Role/Notes                                            |
| ---------------------------------------------------------------------- | ---- | ----------------------------------------------------- |
| [SunFounder GalaxyRVR](https://amzn.to/454yN6I)                                | 1    | Includes Arduino Uno R3, and All Parts.           |


## Usage

### 1. Preparation

- Install [Arduino IDE](https://www.arduino.cc/en/software/).
- Install required libraries via Library Manager:
  - `SunFounder AI Camera`
  - `SoftPWM`
  - `Servo`

### 2. Configuration

- Create a `credentials.h` file in the same directory as the sketch.
- For **STA Mode**, define your Wi-Fi credentials:

```C++
#define STA_SSID "Your_2.4GHz_WiFi_Name"
#define STA_PASSWORD "Your_Password"
```


### 3. Controller App Setup

- Install the [SunFounder Controller](https://play.google.com/store/apps/details?id=com.sunfounder.sunfoundercontroller&hl=ja) app on your tablet or smartphone.
- Connect to the rover's IP address (displayed on the Arduino Serial Monitor).
- Assign the following widgets:
  - **Region D**: Slider (Camera Tilt)
  - **Region E**: Switch (Obstacle Avoidance Mode)
  - **Region F**: Switch (Follow Mode)
  - **Region J**: Switch (Light Master Control)
  - **Region K/Q**: Throttle (Manual Driving)


### 4. Deployment
Compile and upload the code to your SunFounder R3 Board.


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>

## Reference

- [SunFounder - Programming with Arduino IDE](https://docs.sunfounder.com/projects/galaxy-rvr/en/latest/programming_arduino.html)
- [GitHub - GalaxyRVR](https://github.com/sunfounder/galaxy-rvr/tree/main)
- [GitHub - SunFounder AI Camera Library for Arduino](https://github.com/sunfounder/SunFounder_AI_Camera/blob/main/README.md)

