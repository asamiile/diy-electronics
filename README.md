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

<!-- ### XIAO RP2040 -->

<!-- ### XIAO ESP32C3 -->

<!-- ### ESP32-DevKitC  -->

### Wio Terminal

#### Built-In Peripherals

- [Button](Wio_Terminal/BuiltIn_Peripherals/Button)
- [5way Switch](Wio_Terminal/BuiltIn_Peripherals/5way_Switch)
- [Buzzer](Wio_Terminal/BuiltIn_Peripherals/Buzzer)
- [Buzzer Melody](Wio_Terminal/BuiltIn_Peripherals/Buzzer_Melody)
- [TFT LCD](Wio_Terminal/BuiltIn_Peripherals/TFT_LCD)
- [Graphics](Wio_Terminal/BuiltIn_Peripherals/Graphics)
- [Line Charts](Wio_Terminal/BuiltIn_Peripherals/Line_Charts)
- [Histograms](Wio_Terminal/BuiltIn_Peripherals/Histograms)

#### Built-In Sensors

- [Mic](Wio_Terminal/BuiltIn_Sensors/Mic)
- [Mic Graph](Wio_Terminal/BuiltIn_Sensors/Mic_Graph)
- [Light Sensor](Wio_Terminal/BuiltIn_Sensors/Light_Sensor)
- [Accelerometer](Wio_Terminal/BuiltIn_Sensors/Accelerometer)

<!-- - [Wio Terminal Digital Tape Measure](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_Digital_Tape_Measure) -->
<!-- - [Wio Terminal Digital Compass](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_Digital_Compass) -->

#### IOT

- [Wifi BLE Scan](Wio_Terminal/Wifi_BLE_Scan)

#### IOT with Adafruit IO

- [Wio Terminal Weather Station](Wio_Terminal/Weather_Station/)
- [Weather Station with Adafruit IO](Wio_Terminal/Weather_Station/with_Adafruit_IO)
- [Light Sensor with Adafruit IO](Wio_Terminal/Light_Sensor)

<!-- - [GPS Tracker with Adafruit IO](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_GPS_Tracker_with_Adafruit_IO) -->

#### ML with Edge Impulse

- [Word Detection](Wio_Terminal/ML/Word_Detection)
- [Audio scene recognition with microphone](Wio_Terminal/ML/Audio_scene_recognition_with_microphone)
- [Classifying hand gestures with accelerometer](Wio_Terminal/ML/Classifying_hand_gestures_with_accelerometer)
- [People counting with Ultrasonic sensor](Wio_Terminal/ML/People_counting_with_Ultrasonic_sensor)
- [Recognizing gestures with light sensor](Wio_Terminal/ML/Recognizing_gestures_with_light_sensor)

#### SunFounder_GalaxyRVR

- [SunFounder_GalaxyRVR](SunFounder_GalaxyRVR)

## Building in VS Code

The workspace includes pre-configured build tasks for compiling and uploading sketches. Open any `.ino` file and use the built-in task runner.

### Install Arduino CLI

- [Arduino CLI official documentation](https://arduino.github.io/arduino-cli/).

### VS Code Configuration

The workspace file (`diy-electronics.code-workspace`) includes configuration to recognize `.ino` files as C++ and enable GitHub Copilot completions:

```json
"files.associations": {
  "*.ino": "cpp"
}
```

### Install Board Support

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

### Available Tasks

| Task                                    | Purpose                                  |
| --------------------------------------- | ---------------------------------------- |
| `Arduino: Compile (Wio Terminal)`       | Compile for Wio Terminal (SAMD51)        |
| `Arduino: Compile (Arduino Nano ESP32)` | Compile for Arduino Nano ESP32           |
| `Arduino: Compile (XIAO RP2040)`        | Compile for XIAO RP2040                  |
| `Arduino: Upload (Wio Terminal)`        | Compile & upload to Wio Terminal         |
| `Arduino: Upload (Arduino Nano ESP32)`  | Compile & upload to Arduino Nano ESP32   |
| `Arduino: List Connected Boards`        | Detect connected boards and serial ports |

### Running Tasks

1. **Open a `.ino` file** in VS Code
2. **Run a task**: `Ctrl+Shift+B` (macOS: `Shift+Cmd+B`) to show the build task menu
3. **Select a task** from the list (e.g., "Arduino: Compile (Wio Terminal)")
4. For upload tasks, enter the **COM port** when prompted (e.g., `COM7` on Windows, `/dev/ttyUSB0` on Linux)

### Find Your Board's COM Port

```bash
arduino-cli board list
```

This command displays all connected boards with their serial ports and FQBN (Fully Qualified Board Name).

### Frequently Used Commands

Alternatively, you can use Arduino CLI directly from the terminal:

```bash
# Compile a sketch
arduino-cli compile --fqbn seeeduino:samd:seeed_wio_terminal <sketch_directory>

# Upload to a board (replace COM7 with your port)
arduino-cli upload -p COM7 --fqbn seeeduino:samd:seeed_wio_terminal <sketch_directory>

# Install a library
arduino-cli lib install "DHT sensor library"

# List installed libraries
arduino-cli lib list
```

For detailed Arduino CLI usage, see the [Arduino CLI Getting Started guide](https://arduino.github.io/arduino-cli/latest/getting-started/).

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>

## Reference

- [Wio Terminal Guide](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
