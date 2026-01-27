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

### Upload Procedure

#### Step 1: Find Your Board's COM Port

```bash
arduino-cli board list
```

This command displays all connected boards with their serial ports and FQBN.

**Example output:**

```
Serial Port  Protocol  Type              Board Name             FQBN
COM8         serial    Serial Port (USB) Seeeduino Wio Terminal Seeeduino:samd:seeed_wio_terminal
```

#### Step 2: Prepare the Board (For Wio Terminal)

For **Wio Terminal**, put the board into bootloader mode:

1. **Double-click the Power Button** on the Wio Terminal quickly
2. The LED indicator may flash, indicating bootloader mode is active

**Note**: For other boards, check their specific bootloader activation method.

#### Step 3: Upload Using VS Code Task (Recommended)

1. Open a `.ino` file from your target project
2. Press `Ctrl+Shift+B` (or `Shift+Cmd+B` on macOS)
3. Select the **Upload task** for your board (e.g., "Arduino: Upload (Wio Terminal)")
4. When prompted, enter your board's COM port (e.g., `COM8`)
5. Wait for the upload to complete

**Success indicator:**

```
最大507904バイトのフラッシュメモリのうち、スケッチが122128バイト（24%）を使っています。
(Flash memory usage will be displayed)
```

#### Step 4: Upload Using Terminal (Alternative)

```bash
# Replace COM8 with your actual port and adjust the path as needed
arduino-cli upload -p COM8 --fqbn seeeduino:samd:seeed_wio_terminal <sketch_directory>

# Example for Wio Terminal Weather Station:
cd "D:\path\to\Wio_Terminal\Weather_Station\sketch\Weather_Station"
arduino-cli upload -p COM8 --fqbn seeeduino:samd:seeed_wio_terminal .
```

#### Step 5: Verify Upload Success

- Check the board's display or serial monitor for expected behavior
- Use Arduino IDE or PlatformIO's Serial Monitor to view debug output (if Serial.println() is used)
- Some boards will reboot automatically after upload

### Serial Monitor

#### Using Arduino CLI (Recommended)

Monitor serial output directly from the command line:

```bash
# Monitor serial output on a specific port (baud rate: 115200 by default)
arduino-cli monitor -p COM8

# With custom baud rate:
arduino-cli monitor -p COM8 --config baudrate=9600
```

**Example output:**

```
Connected to COM8
Temperature: 25.50 *C, Humidity: 55.30 %
Temperature sent!
Humidity sent!
Temperature: 25.52 *C, Humidity: 55.25 %
```

**To exit**: Press `Ctrl+C`

#### Using Arduino IDE

If you prefer a GUI:

1. Open Arduino IDE (install from [arduino.cc](https://www.arduino.cc/en/software) if needed)
2. Go to **Tools → Port** and select your board's COM port
3. Open **Tools → Serial Monitor** (or press `Ctrl+Shift+M`)
4. Set the baud rate to match your sketch (default: 115200)
5. View the serial output in real-time

#### Using VS Code + PlatformIO (Alternative)

1. Install the **PlatformIO IDE** extension for VS Code
2. Create/open a PlatformIO project
3. Use the **Serial Monitor** button in the PlatformIO toolbar
4. Select your port and baud rate

#### Common Baud Rates

| Baud Rate | Common Use                              |
| --------- | --------------------------------------- |
| 9600      | Classic Arduino                         |
| 115200    | **Default** (Wio Terminal, ESP32, etc.) |
| 230400    | High-speed boards                       |

**Note**: The baud rate in your sketch must match the Serial Monitor's baud rate. Check your `.ino` file for `Serial.begin()` configuration.

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
