# Arduino Nano ESP32 Smart Lighting Control

[English](README.md) | [Japanese](README.ja.md)

## Overview

Scheduled infrared lighting control using NTP-synchronized Japan Standard Time, with Grove light-sensor feedback, IR-code learning, Wi-Fi reconnection, and dual MQTT publication to Adafruit IO and Shiftr.io.

## Bill of Materials

| Part | Quantity | Role / Notes |
| ------------------------------------------------------------------------------------ | ---- | ----------------------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/4apayDa)                                        | 1    | Main controller with WiFi connectivity                      |
| [Grove Shield for Arduino Nano](https://amzn.to/49TrG40)                             | 1    | Expansion shield for easy Grove sensor connection           |
| [Grove - Infrared Emitter](https://amzn.to/4rt9Tqi)                                  | 1    | Sends IR signals to control lights (D2 digital)             |
| [Grove - Infrared Receiver](https://jp.seeedstudio.com/Grove-Infrared-Receiver.html) | 1    | Receives IR signals for learning (D4 digital)               |
| [Grove - Light Sensor v1.2](https://amzn.to/4rsvrTV)                                 | 1    | Measures light levels for feedback verification (A0 analog) |
| USB Type-C Cable                                                                     | 1    | For power and programming                                   |

## Development

### Hardware Development

#### Hardware setup

Attach the Grove Shield. Connect the IR emitter to D2, IR receiver to D4, and light sensor to A0 (Grove analog port labeled D6). Power/program the Nano through USB-C.

### Software Development

#### Firmware configuration

Use the Arduino ESP32 Boards core and `IRremote`; follow the actual sketch includes for MQTT and other dependencies. Copy the credential example in `sketch/Smart_Lighting_Control/` and configure Wi-Fi and service credentials. NTP, timezone, scheduling, waveform data, and thresholds are configured in `config.h`.

Learn the lighting remote's ON/OFF signal with `sketch/IR_Learning/IR_Learning.ino`, using Serial Monitor at 115200 baud. Point the remote at the receiver and copy the complete raw array into `rawDataON_OFF[]`. Verify `RAW_DATA_LENGTH` and test with `IR_Send_Test_Raw.ino`: `s` sends once, `c` sends five times, and `d` displays data. Adjust `LIGHT_OFF_THRESHOLD` for the room using sensor readings; the original guide suggested 25–35 as a starting range, not a universal threshold.

Set `SCHEDULED_OFF_HOUR` and `SCHEDULED_OFF_MINUTE`, then upload [the main sketch](sketch/Smart_Lighting_Control/Smart_Lighting_Control.ino). Use `IR_Receiver_Raw_Data_Test.ino` to capture other devices and `IR_Send_Test.ino` for NEC/Onkyo transmission tests. Their paths and roles are listed below.

#### Cloud integration and verification

Adafruit IO receives light readings; [the lighting pipeline](../../../../cloud/Cloud_Functions/Smart_Lighting_Control_Data_Pipeline/README.md) stores selected telemetry in BigQuery through Shiftr.io. Check the actual topic in `config.h` against the webhook rather than copying a topic from another project. Verify NTP time, IR operation, sensor feedback, scheduled switching, and reconnection independently.

#### Configuration reference

| Setting               | Location in config.h                            | What to Change                                                                                         |
| --------------------- | ----------------------------------------------- | ------------------------------------------------------------------------------------------------------ |
| **Raw Waveform Data** | `rawDataON_OFF[]` array                         | Replace with the raw data learned from YOUR remote's ON/OFF button                                     |
| **Raw Data Length**   | `RAW_DATA_LENGTH` macro                         | Automatically calculated, but verify it matches your captured data length                              |
| **Light Threshold**   | `LIGHT_OFF_THRESHOLD` constant                  | Adjust based on your room's lighting conditions (test with `IR_Send_Test_Raw.ino`, read serial output) |
| **Scheduled Time**    | `SCHEDULED_OFF_HOUR` and `SCHEDULED_OFF_MINUTE` | Set the time you want lights to turn off automatically                                                 |

| Sketch Name                       | Purpose                                         | Use Case                                                                                                                 |
| --------------------------------- | ----------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| **Smart_Lighting_Control.ino**    | Main production sketch                          | Normal operation - controls lights based on schedule and light sensor feedback                                           |
| **IR_Send_Test_Raw.ino**          | Raw waveform transmission test                  | Verify that IR signals from current remote work correctly (commands: 's'=send once, 'c'=5x continuous, 'd'=display data) |
| **IR_Send_Test.ino**              | Protocol-based IR sender with receiver feedback | Test NEC/Onkyo protocol commands, useful for adding support for new IR devices                                           |
| **IR_Receiver_Raw_Data_Test.ino** | Capture raw IR waveforms                        | Learn raw data from new remote controls (point remote at receiver and press button)                                      |
| **IR_Learning.ino**               | Automated raw data extraction reference         | Reference implementation for parsing and displaying captured IR signals                                                  |

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)
- [Credentials](../../../../docs/credentials.md)
- [Adafruit IO setup](../../../../docs/adafruit-io.md)
- [Cloud Functions workflow](../../../../docs/cloud-functions.md)

- [Arduino Nano ESP32 Documentation](https://docs.arduino.cc/hardware/nano-esp32/)
- [Arduino WiFi Documentation](https://docs.arduino.cc/libraries/wifi/)
- [IRremote Library Documentation](https://github.com/Arduino-IRremote/Arduino-IRremote)
- [Grove - Light Sensor v1.2](https://wiki.seeedstudio.com/Grove-Light-Sensor/)
- [NTP Time Synchronization](https://docs.arduino.cc/libraries/time/)

## Author

[Your Name](https://your-portfolio.com/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
