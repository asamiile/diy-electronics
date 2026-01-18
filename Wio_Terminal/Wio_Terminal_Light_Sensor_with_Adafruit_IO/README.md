# Wio Terminal Light Sensor with Adafruit IO

## Overview

- This project uses the Wio Terminal's built-in light sensor to function as an IoT ambient light monitor.

The device measures the surrounding light level in real-time and displays the value on its LCD screen. Simultaneously, it connects to Wi-Fi and publishes this data to an Adafruit IO feed, allowing the light level to be monitored remotely on a custom dashboard. For user convenience, Wi-Fi credentials are not hard-coded; instead, the `WiFiManager` library is used to create a configuration portal for easy setup.


- Adafruit IO Dashboads: 

[![Image from Gyazo](https://i.gyazo.com/c91afdeec80b07e40fff4aca7d88c4e0.png)](https://gyazo.com/c91afdeec80b07e40fff4aca7d88c4e0)


### Features


### Bill of Materials

| Part Type                                                                                                   | Unit | Role/Notes                                                                    |
| ----------------------------------------------------------------------------------------------------------- | ---- | ----------------------------------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu)                                                                     | 1    | Main controller, display, and Wi-Fi module.                                   |
| USB Type-C Cable                                                                                            | 1    | For power and programming. Must be a data-sync cable.                         |


## Usage

- **Step 1: Adafruit IO Setup**
  1. **Create a Feed**: Log in to your Adafruit IO account. Go to **Feeds** and create a new feed with the exact name `light-level`. This feed will store the brightness data from the Wio Terminal's built-in sensor.
-  **Step 2: Arduino Programming**
   1. **Install Libraries**: In your Arduino IDE, ensure you have the necessary libraries installed: `rpcWiFi`, `TFT_eSPI`, `Adafruit MQTT Library`, and `WiFiManager`.
   2. **Configure Credentials**: Create a `credentials.h` file in your sketch folder and add your Adafruit IO username and key.
   3. **Upload Code**: Upload the [Light_Sensor](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_Light_Sensor_with_Adafruit_IO/Light_Sensor) that is configured to use the **built-in light sensor** (WIO_LIGHT) to your Wio Terminal.
   4. **First-Time Wi-Fi Setup**: After uploading, connect to the "**AutoConnectAP**" Wi-Fi network with your phone or PC to configure the Wio Terminal to connect to your local Wi-Fi.
- **Step 3: Adafruit IO Dashboards Setup**
  1. **Create a Dashboard**: Go to **Dashboards** and create a new dashboard.
  2. **Add Blocks**: Click **New Block** and add blocks to visualize your data.
     - Gauge Block: Link this to your `light-level` feed to see the current brightness value.
  3. **Monitor Data**: Observe the data on your dashboard. 
     - **Note**: The built-in sensor is on the back of the Wio Terminal, so ensure it is not covered.


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
