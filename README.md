# DIY Electronics

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Overview

These are a collection of DIY Electronics samples.

### Arduino UNO

- [Arduino Uno RGB LED](Arduino_Uno/Arduino_Uno_RGB_LED)
- [Arduino Uno 8x8 LED Matrix](Arduino_Uno/Arduino_Uno_8x8_LED_Matrix)
- [Arduino Uno Interactive Servo Light](Arduino_Uno/Arduino_Uno_Interactive_Servo_Light)

### Arduino Nano ESP32

- [Arduino Nano RGB LED](Arduino_Nano_ESP32/Arduino_Nano_ESP32_RGB_LED)

### Wio Terminal

#### Build In Sensor

- [TFT LCD](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_TFT_LCD)
- [Graphics](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_Graphics)
- [Line Charts](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_Line_Charts)
- [Histograms](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_Histograms)
- [Button](Wio_Terminal/Wio_Terminal_Build_In/Wio_Teaminal_Button)
- [5way Switch](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_5way_Switch)
- [Buzzer](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_Buzzer)
- [Buzzer Melody](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_Buzzer_Melody)
- [Mic](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_Mic)
- [Mic Graph](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_Mic_Graph)
- [Light Sensor](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_Light_Sensor)
- [Accelerometer](Wio_Terminal/Wio_Terminal_Build_In/Wio_Terminal_Accelerometer)

<!-- - [Wio Terminal Digital Tape Measure](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_Digital_Tape_Measure) -->
<!-- - [Wio Terminal Digital Compass](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_Digital_Compass) -->

#### IOT

- [Wifi BLE Scan](Wio_Terminal/Wio_Terminal_Wifi_BLE_Scan)
- [Weather Station with Adafruit IO](Wio_Terminal/Weather_Station_with_Adafruit_IO)
- [Light Sensor with Adafruit IO](Wio_Terminal/Wio_Terminal_Light_Sensor_with_Adafruit_IO)
<!-- - [GPS Tracker with Adafruit IO](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_GPS_Tracker_with_Adafruit_IO) -->

<!-- ### XIAO RP2040 -->

<!-- ### XIAO ESP32C3 -->

<!-- ### ESP32-DevKitC  -->

#### with Edge Impulse

- [Word Detection](Wio_Terminal/with_EdgeImpulse/Word_Detection)
- [Audio scene recognition with microphone](Wio_Terminal/with_EdgeImpulse/Audio_scene_recognition_with_microphone)
- [Classifying hand gestures with accelerometer](Wio_Terminal/with_EdgeImpulse/Classifying_hand_gestures_with_accelerometer)
- [People counting with Ultrasonic sensor](Wio_Terminal/with_EdgeImpulse/People_counting_with_Ultrasonic_sensor)
- [Recognizing gestures with light sensor](Wio_Terminal/with_EdgeImpulse/Recognizing_gestures_with_light_sensor)

#### SunFounder_GalaxyRVR

- [SunFounder_GalaxyRVR](SunFounder_GalaxyRVR)

## Development Environment Setup

### Arduino CLI Installation

This project uses **Arduino CLI** for building and uploading sketches.

#### macOS (Homebrew)

```bash
brew install arduino-cli
```

#### Windows (Winget)

```bash
winget install ArduinoSA.ArduinoCLI
```

#### Linux

```bash
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
```

### Installing Board Definitions

Install the board definitions for the boards used in this project:

```bash
# Wio Terminal (SAMD51)
arduino-cli core install Seeeduino:samd

# Arduino Nano ESP32
arduino-cli core install arduino:esp32

# XIAO RP2040
arduino-cli core install rp2040:rp2040

# Arduino Uno
arduino-cli core install arduino:avr
```

### Checking Connected Boards

```bash
arduino-cli board list
```

This command displays serial ports and board information.

### VS Code Configuration

To recognize `.ino` files as C++ and enable GitHub Copilot completions, the workspace file (`diy-electronics.code-workspace`) includes the following configuration:

```json
"files.associations": {
  "*.ino": "cpp"
}
```

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>

## Reference

- [Wio Terminal Guide](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
