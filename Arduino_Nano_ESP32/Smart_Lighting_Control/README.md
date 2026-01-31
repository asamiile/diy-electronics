# Arduino Nano ESP32 Smart Lighting Control

## Overview

This project transforms the Arduino Nano ESP32 into an automated lighting control system. It retrieves the precise Japan Standard Time (JST) from an NTP server and sends infrared signals to control ceiling lights at scheduled times. The system includes a feedback loop using a light sensor (Grove - Light Sensor) to verify successful light control, and supports learning IR codes from existing remote controls.

### Features

- **Scheduled Auto Off**: Retrieves accurate JST time from NTP server and sends lights OFF signal at specified times
- **Feedback Loop Verification**: Measures ambient light levels with Grove - Light Sensor to confirm successful light control
- **IR Code Learning**: Supports learning and recording infrared signals from existing home automation remote controls
- **WiFi Connectivity**: Automatic WiFi reconnection on connection loss
- **Flexible Scheduling**: Customizable schedule for automatic lighting control

## Bill of Materials

| Part Type                                                                            | Unit | Role/Notes                                                  |
| ------------------------------------------------------------------------------------ | ---- | ----------------------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/4apayDa)                                        | 1    | Main controller with WiFi connectivity                      |
| [Grove Shield for Arduino Nano](https://amzn.to/49TrG40)                             | 1    | Expansion shield for easy Grove sensor connection           |
| [Grove - Infrared Emitter](https://amzn.to/4rt9Tqi)                                  | 1    | Sends IR signals to control lights (D2 digital)             |
| [Grove - Infrared Receiver](https://jp.seeedstudio.com/Grove-Infrared-Receiver.html) | 1    | Receives IR signals for learning (D4 digital)               |
| [Grove - Light Sensor v1.2](https://amzn.to/4rsvrTV)                                 | 1    | Measures light levels for feedback verification (A0 analog) |
| USB Type-C Cable                                                                     | 1    | For power and programming                                   |

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

Install via Arduino IDE or CLI:

```bash
arduino-cli lib install "IRremote"
```

### 4. Hardware Setup

1. Connect the Grove Shield to Arduino Nano ESP32
2. Connect Grove - Infrared Emitter to **D2** (Digital port)
3. Connect Grove - Infrared Receiver to **D4** (Digital port)
4. Connect Grove - Light Sensor to **A0** (Analog port, D6)
5. Connect Arduino Nano ESP32 via USB Type-C cable

### 5. Credentials Configuration

1. Copy `credentials.h.example` to `credentials.h`
2. Configure the following personal information:
   - WiFi SSID (2.4 GHz network)
   - WiFi password
   - IR OFF code (learned from IR_Learning sketch)

**Note:** System settings such as NTP server, timezone, and scheduling are configured in `config.h` (not in credentials.h).

### 6. IR Code Learning and Configuration

#### Learning IR Signals from Your Remote

1. Load the `IR_Learning.ino` sketch from the test sketches folder
2. Upload to Arduino Nano ESP32
3. Open the Serial Monitor (115200 baud)
4. Point your lighting remote's OFF button at the infrared receiver
5. Press the button once and wait for the raw data array to be displayed
6. Copy the entire raw data array from the serial output

#### Configuring for Different Light Fixtures

**Important:** The following settings in `config.h` must be customized for your specific lighting fixture:

| Setting               | Location in config.h                            | What to Change                                                                                         |
| --------------------- | ----------------------------------------------- | ------------------------------------------------------------------------------------------------------ |
| **Raw Waveform Data** | `rawDataON_OFF[]` array                         | Replace with the raw data learned from YOUR remote's ON/OFF button                                     |
| **Raw Data Length**   | `RAW_DATA_LENGTH` macro                         | Automatically calculated, but verify it matches your captured data length                              |
| **Light Threshold**   | `LIGHT_OFF_THRESHOLD` constant                  | Adjust based on your room's lighting conditions (test with `IR_Send_Test_Raw.ino`, read serial output) |
| **Scheduled Time**    | `SCHEDULED_OFF_HOUR` and `SCHEDULED_OFF_MINUTE` | Set the time you want lights to turn off automatically                                                 |

**Step-by-step:**

1. Learn your remote using `IR_Learning.ino` (steps above)
2. Open `config.h` in the main sketch folder
3. Replace the `rawDataON_OFF[]` array with your learned data
4. Test with `IR_Send_Test_Raw.ino` (send 's' to test one signal, 'c' for 5 continuous)
5. Verify light turns ON/OFF correctly
6. Run `IR_Send_Test_Raw.ino` for a few seconds, note the light sensor readings (shown in serial monitor)
7. Adjust `LIGHT_OFF_THRESHOLD` if needed (typically 25-35 for most environments)
8. Upload `SmartLightingControl.ino` to deploy

### 7. Test Sketches

This project includes several test sketches to help with development and troubleshooting:

| Sketch Name                       | Purpose                                         | Use Case                                                                                                                 |
| --------------------------------- | ----------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| **Smart_Lighting_Control.ino**    | Main production sketch                          | Normal operation - controls lights based on schedule and light sensor feedback                                           |
| **IR_Send_Test_Raw.ino**          | Raw waveform transmission test                  | Verify that IR signals from current remote work correctly (commands: 's'=send once, 'c'=5x continuous, 'd'=display data) |
| **IR_Send_Test.ino**              | Protocol-based IR sender with receiver feedback | Test NEC/Onkyo protocol commands, useful for adding support for new IR devices                                           |
| **IR_Receiver_Raw_Data_Test.ino** | Capture raw IR waveforms                        | Learn raw data from new remote controls (point remote at receiver and press button)                                      |
| **IR_Learning.ino**               | Automated raw data extraction reference         | Reference implementation for parsing and displaying captured IR signals                                                  |

**Recommended Workflow:**

1. Start with **Smart_Lighting_Control.ino** for daily operation
2. Use **IR_Send_Test_Raw.ino** to verify current remote control works
3. If adding a new IR device: Use **IR_Receiver_Raw_Data_Test.ino** to capture, then **IR_Send_Test.ino** to test sending

### 8. Upload Main Sketch

#### Using Arduino IDE (GUI)

1. Open `SmartLightingControl.ino` from the `sketch/` folder
2. Select the board: **Arduino Nano ESP32** (Tools → Board)
3. Compile and upload to the device

#### Using Arduino CLI (Command Line)

**Step 1: List connected boards**

```bash
arduino-cli board list
```

Note the COM port (e.g., `COM9`) for your Arduino Nano ESP32.

**Step 2: Compile the sketch**

```bash
arduino-cli compile --fqbn arduino:esp32:nano_nora D:\Share\Develop\diy-electronics\Arduino_Nano_ESP32\Smart_Lighting_Control\sketch\Smart_Lighting_Control
```

**Step 3: Upload to the board**

```bash
arduino-cli upload -p COM9 --fqbn arduino:esp32:nano_nora D:\Share\Develop\diy-electronics\Arduino_Nano_ESP32\Smart_Lighting_Control\sketch\Smart_Lighting_Control
```

Replace `COM9` with your actual COM port from Step 1.

**Step 4: Monitor serial output**

```bash
arduino-cli monitor -p COM9 -c baudrate=115200
```

## References

- [Arduino Nano ESP32 Documentation](https://docs.arduino.cc/hardware/nano-esp32/)
- [Arduino WiFi Documentation](https://docs.arduino.cc/libraries/wifi/)
- [IRremote Library Documentation](https://github.com/Arduino-IRremote/Arduino-IRremote)
- [Grove - Light Sensor v1.2](https://wiki.seeedstudio.com/Grove-Light-Sensor/)
- [NTP Time Synchronization](https://docs.arduino.cc/libraries/time/)

## Author

[Your Name](https://your-portfolio.com/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
