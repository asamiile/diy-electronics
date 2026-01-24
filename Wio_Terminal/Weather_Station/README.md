# Wio Terminal Weather Station

## Overview

This project transforms the Wio Terminal into a weather station. It measures ambient temperature and humidity using a Grove - DHT11 sensor and displays the data in real-time on the built-in LCD screen.

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/76df73232223085.68984e3bc47f8.jpg)

### Features

- **Real-time Local Display**: Shows current temperature and humidity on the Wio Terminal's LCD screen
- **Simple Setup**: Easy-to-follow calibration with minimal configuration
- **Responsive UI**: Custom colors and fonts for improved readability

### Bill of Materials

| Part Type | Unit | Role/Notes |
| --- | --- | --- |
| [Wio Terminal](https://amzn.to/4me4lxu) | 1 | Main controller, display, and Wi-Fi module |
| [Grove - Temperature & Humidity Sensor (DHT11)](https://amzn.to/3Um4qmA) | 1 | Connected to any of the Grove ports (code uses D0) |
| USB Type-C Cable | 1 | For power and programming. Must be a data-sync cable |

## Setup Instructions

Please follow the reference guide below for the basic setup procedure.

- [Wio Terminal Getting Started Guide](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)

### 1. Hardware Setup

1. Connect the DHT11 sensor to one of the Grove ports (default: D0)
2. Connect Wio Terminal to your computer via USB Type-C cable

### 2. Software Setup

1. Install Arduino IDE and Wio Terminal board support
2. Install required libraries:
   - `DHT sensor library` by Adafruit
   - `Adafruit Unified Sensor` by Adafruit
3. Upload the sketch from the `sketch/` folder

### 3. Customize Display

The sketch includes color and font customization options. Modify these constants at the top of the sketch:

```cpp
#define TEMP_COLOR TFT_RED
#define HUMIDITY_COLOR TFT_BLUE
#define TEXT_SIZE 2
```

## Sketch Location

The sketch files are available in the `sketch/` directory.

## Cloud Integration (Optional)

For remote data monitoring and logging, refer to the [Adafruit IO Integration Guide](with_Adafruit_IO/README.md).

## References

- [Wio Terminal Documentation](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
- [DHT11 Sensor Guide](https://www.adafruit.com/product/386)
- [Grove Sensor Documentation](https://wiki.seeedstudio.com/Grove_System/)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiii" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
