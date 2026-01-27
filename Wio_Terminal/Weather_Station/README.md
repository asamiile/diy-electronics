# Wio Terminal Weather Station

## Overview

This project transforms the Wio Terminal into a connected weather station. It measures ambient temperature and humidity using a Grove - DHT11 sensor and visualizes the data in two ways: locally on the built-in LCD screen and remotely on Adafruit IO and Shiftr.io.

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/76df73232223085.68984e3bc47f8.jpg)

**Cloud Dashboards:**

- [Adafruit IO Dashboard](https://io.adafruit.com/asamiinae/dashboards/weather-station)
- [Shiftr.io Dashboard](https://www.shiftr.io/)

### Features

- **Real-time Local Display**: Shows current temperature and humidity on the Wio Terminal's LCD screen
- **Dual Cloud Integration**: Publishes sensor data to both Adafruit IO and Shiftr.io via MQTT
- **JSON Format Support**: Sends data to Shiftr.io in JSON format for flexible data handling
- **Battery Support**: Standalone operation via battery base
- **Auto Reconnection**: Automatic WiFi and MQTT reconnection on connection loss

## Bill of Materials

| Part Type                                                                | Unit | Role/Notes                                           |
| ------------------------------------------------------------------------ | ---- | ---------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu)                                  | 1    | Main controller, display, and Wi-Fi module           |
| [Grove - Temperature & Humidity Sensor (DHT11)](https://amzn.to/3Um4qmA) | 1    | Connected to any of the Grove ports (code uses D0)   |
| USB Type-C Cable                                                         | 1    | For power and programming. Must be a data-sync cable |
| **Battery Base (Optional)**                                              | 1    | For standalone operation without USB power           |

## Setup Instructions

Please follow the reference guide below for the basic setup procedure:

- [Wio Terminal Getting Started Guide](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)

### 1. Hardware Setup

1. Connect the DHT11 sensor to one of the Grove ports (default: D0)
2. Connect Wio Terminal to your computer via USB Type-C cable

### 2. Software Setup

1. Install Arduino CLI or Arduino IDE
2. Install required libraries:
   - `DHT sensor library` by Adafruit
   - `Adafruit Unified Sensor` by Adafruit
   - `PubSubClient` by Nick O'Leary
   - `ArduinoJson` by Benoit Blanchon
3. Copy `credentials.h.example` to `credentials.h` and configure:
   - WiFi SSID and password
   - Adafruit IO username and API key
   - Shiftr.io key and secret
4. Upload the sketch from the `sketch/` folder

## Cloud Integration

For detailed setup and configuration of cloud services, refer to the following guides:

- **[Adafruit IO Integration](with_Adafruit_IO/README.md)** - Real-time dashboard and data logging
- **[Shiftr.io Integration](with_Shiftr_io/README.md)** - MQTT broker with JSON data format

## References

- [Wio Terminal Documentation](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
- [DHT11 Sensor Guide](https://www.adafruit.com/product/386)
- [Adafruit IO Documentation](https://io.adafruit.com/api/docs/)
- [Shiftr.io Documentation](https://www.shiftr.io/docs/)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
