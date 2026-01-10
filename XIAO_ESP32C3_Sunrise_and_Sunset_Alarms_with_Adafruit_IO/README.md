# XIAO ESP32C3 Sunrise and Sunset Alarms with Adafruit IO (In production)

## Overview

- This project is a smart alarm that detects local sunrise and sunset times by measuring ambient light levels with a Grove Digital Light Sensor. The XIAO ESP32C3 processes this data and sends real-time alerts to a custom Adafruit IO dashboard. It's a weather-adaptive alternative to fixed-time alarms, all housed in a compact form factor thanks to the Seeed Studio XIAO ecosystem.

![]()


- Adafruit IO Dashboads: []()

[![Image from Gyazo]()]()


### Features


### Bill of Materials

| Part Type                                                                                                    | Unit | Role/Notes                                                                  |
| ------------------------------------------------------------------------------------------------------------ | ---- | --------------------------------------------------------------------------- |
| [XIAO ESP32C3](https://amzn.to/45T6bNg)                                                                      | 1    | The brain of the alarm. It will process sensor data and send notifications. |
| [Grove Digital Light Sensor](https://jp.seeedstudio.com/Grove-Light-Sensor-v1-2-LS06-S-phototransistor.html) | 1    | Measures the ambient light to detect sunrise and sunset.                    |
| [Grove Shield for Seeeduino XIAO](https://amzn.to/479T6S5)                                                   | 1    | Replaces the breadboard and wires for a simple, reliable connection.        |
| [USB-C Cable](https://amzn.to/4lU4bdZ)                                                                       | 1    | For programming and powering the XIAO ESP32C3.                              |
| [Mobile Battery](https://amzn.to/45jTQ5W)                                                                    | 1    | Powers the device, allowing you to place it anywhere.                       |


## Assembly Steps

### Hardware Development

1. Solder the pin headers that come with the XIAO ESP32C3 onto the board.
2. Plug the XIAO ESP32C3 into the Grove Shield.
3. Use the Grove Cable to connect the Grove Digital Light Sensor to one of the Grove ports on the shield.
4. Connect the USB Type-C Cable to the XIAO ESP32C3 and the Mobile Battery.

- []()

### Software Development


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
