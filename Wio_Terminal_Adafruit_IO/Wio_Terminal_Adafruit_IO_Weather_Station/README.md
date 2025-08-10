# Wio Terminal Adafruit IO Weather Station

## Overview

- This project transforms the Wio Terminal into a connected weather station. It measures ambient temperature and humidity using a Grove - DHT11 sensor and visualizes the data in two ways: locally on the built-in LCD screen and remotely on an Adafruit IO dashboard.

![](https://lightroom.adobe.com/v2c/catalogs/ed2e01a539b04942967b87bf621ffa54/assets/294f9f11830c4129b0251f46e46a78b9/revisions/bf4c861ac19f4574a86f0b4264dbb407/renditions/be709306d144d6fb8234c250f2e8deca)


- Adafruit IO Dashboads: [Weather Station](https://io.adafruit.com/asamiile/dashboards/weather-station)

[![Image from Gyazo](https://i.gyazo.com/2f3f2dd6637c2fdf2869a831bb386971.png)](https://gyazo.com/2f3f2dd6637c2fdf2869a831bb386971)


### Features
- Real-time Display: Displays current temperature and humidity on the Wio Terminal's screen.
- IoT Cloud Integration: Publishes sensor data to Adafruit IO via the MQTT protocol for remote monitoring and data logging.
- User-Friendly Setup: Utilizes the WiFiManager library to create a configuration portal, allowing you to set up Wi-Fi credentials through a web browser without hard-coding them into the sketch.


### Bill of Materials

| Part Type                                                              | Unit | Role/Notes                                            |
| ---------------------------------------------------------------------- | ---- | ----------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu)                                | 1    | Main controller, display, and Wi-Fi module.           |
| [Grove - Temperature&Humidity Sensor (DHT11)](https://amzn.to/3Um4qmA) | 1    | Connected to any of the Grove ports (code uses D0).   |
| USB Type-C Cable                                                       | 1    | For power and programming. Must be a data-sync cable. |


## Usage

Please follow the reference guide below for the basic setup procedure.

- [Build an ML Model in 5 Minutes and Deploy in the Wio Terminal Powered by Edge Impulse](https://wiki.seeedstudio.com/Getting_started_wizard/#getting-started-with-edge-impulse)

The sketch with color and font customization for this project is available at the following link:

- [Weather_Station](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_Adafruit_IO/Wio_Terminal_Adafruit_IO_Weather_Station/Weather_Station)


### Setting Up Discord Notifications (Optional)

- **Create a Discord Webhook**
  - In your Discord server, go to **Server Settings** > **Integrations** > **Webhooks**. Create a new webhook for your desired channel and copy the Webhook URL.
- **Create an Adafruit IO Action**
  - In Adafruit IO, create a new Reactive Action. Configure the trigger and webhook action as shown in the image below, using the JSON provided.
    [![Image from Gyazo](https://i.gyazo.com/6f92135d9cde9b7498e314a76d25807f.png)](https://gyazo.com/6f92135d9cde9b7498e314a76d25807f)
    POST Body for Webhook:
    ```
    {
    "content": "🚨 High Temperature Alert!",
    "embeds": [{
        "title": "🌡️ Overtemperature notification",
        "description": "The temperature has exceeded the 30°C threshold.",
        "color": 16734296
    }]
    }
    ```


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
