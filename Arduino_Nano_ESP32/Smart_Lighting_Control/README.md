# Arduino Nano ESP32 Smart Lighting Control

## Overview

This project transforms the Arduino Nano ESP32 into an automated lighting control system. It retrieves the precise Japan Standard Time (JST) from an NTP server and sends infrared signals to control ceiling lights at scheduled times. The system includes a feedback loop using a digital light sensor (TSL2561) to verify successful light control, and supports learning IR codes from existing remote controls.

### Features

- **Scheduled Auto Off**: Retrieves accurate JST time from NTP server and sends lights OFF signal at specified times
- **Feedback Loop Verification**: Measures ambient light levels with Grove - Digital Light Sensor (TSL2561) to confirm successful light control
- **IR Code Learning**: Supports learning and recording infrared signals from existing home automation remote controls
- **WiFi Connectivity**: Automatic WiFi reconnection on connection loss
- **Flexible Scheduling**: Customizable schedule for automatic lighting control

## Bill of Materials

| Part Type                                                                            | Unit | Role/Notes                                            |
| ------------------------------------------------------------------------------------ | ---- | ----------------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/4apayDa)                                        | 1    | Main controller with WiFi connectivity                |
| [Grove Shield for Arduino Nano](https://amzn.to/49TrG40)                             | 1    | Expansion shield for easy Grove sensor connection     |
| [Grove - Infrared Emitter](https://amzn.to/4rt9Tqi)                                  | 1    | Sends IR signals to control lights (D2 digital)       |
| [Grove - Infrared Receiver](https://jp.seeedstudio.com/Grove-Infrared-Receiver.html) | 1    | Receives IR signals for learning (D4 digital)         |
| [Grove - Digital Light Sensor (TSL2561)](https://amzn.to/4atF123)                    | 1    | Measures light levels for feedback verification (I2C) |
| USB Type-C Cable                                                                     | 1    | For power and programming                             |

## Software Setup

### 1. Arduino IDE Configuration

Install Arduino IDE or use Arduino CLI following the [official guide](https://docs.arduino.cc/software/ide/).

### 2. Board Configuration

Install the ESP32 board package for Arduino Nano ESP32:

```bash
arduino-cli core install arduino:esp32
```

### 3. Required Libraries

Install the following libraries:

- **WiFi** (ESP32 built-in)
- **Time** (ESP32 built-in)
- **IRremote** (by Armin Joachimsmeyer) - For infrared transmission and reception
- **Grove_Digital_Light_Sensor_TSL2561** (by Seeed Studio) - For ambient light measurement

Install via Arduino IDE or CLI:

```bash
arduino-cli lib install "IRremote"
arduino-cli lib install "Grove - Digital Light Sensor TSL2561"
```

### 4. Hardware Setup

1. Connect the Grove Shield to Arduino Nano ESP32
2. Connect Grove - Infrared Emitter to **D2** (Digital port)
3. Connect Grove - Infrared Receiver to **D4** (Digital port)
4. Connect Grove - Digital Light Sensor (TSL2561) to **I2C** port
5. Connect Arduino Nano ESP32 via USB Type-C cable

### 5. Credentials Configuration

1. Copy `credentials.h.example` to `credentials.h`
2. Configure the following personal information:
   - WiFi SSID (2.4 GHz network)
   - WiFi password
   - IR OFF code (learned from IR_Learning sketch)

**Note:** System settings such as NTP server, timezone, and scheduling are configured in `config.h` (not in credentials.h).

### 6. IR Code Learning

1. Load the `IR_Learning.ino` sketch (if available)
2. Upload to Arduino Nano ESP32
3. Open the Serial Monitor (115200 baud)
4. Point your lighting remote's OFF button at the infrared receiver
5. Press the button and note the displayed raw data or protocol code
6. Copy the learned code to the `OFF_SIGNAL` constant in the main sketch

### 7. Upload Main Sketch

1. Open `SmartLightingControl.ino` from the `sketch/` folder
2. Select the board: **Arduino Nano ESP32** (Tools → Board)
3. Compile and upload to the device

## References

- [Arduino Nano ESP32 Documentation](https://docs.arduino.cc/hardware/nano-esp32/)
- [Arduino WiFi Documentation](https://docs.arduino.cc/libraries/wifi/)
- [IRremote Library Documentation](https://github.com/Arduino-IRremote/Arduino-IRremote)
- [Grove - Digital Light Sensor (TSL2561)](https://wiki.seeedstudio.com/Grove-Digital_Light_Sensor/)
- [NTP Time Synchronization](https://docs.arduino.cc/libraries/time/)

## Author

[Your Name](https://your-portfolio.com/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
