# Wio Terminal Light Sensor with Adafruit IO

[English](README.md) | [Japanese](README.ja.md)

## Overview

Read Wio Terminal's built-in ambient light sensor (`WIO_LIGHT`), display its value on the LCD, and publish it to Adafruit IO. Keep the sensor on the back of the device uncovered.

### Gallery

[![Image from Gyazo](https://i.gyazo.com/c91afdeec80b07e40fff4aca7d88c4e0.png)](https://gyazo.com/c91afdeec80b07e40fff4aca7d88c4e0)

## Bill of Materials

| Part | Quantity | Role / Notes |
| ----------------------------------------------------------------------------------------------------------- | ---- | ----------------------------------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu)                                                                     | 1    | Main controller, display, and Wi-Fi module.                                   |
| USB Type-C Cable                                                                                            | 1    | For power and programming. Must be a data-sync cable.                         |

## Development

### Hardware Development

See Bill of Materials for the required hardware.

### Software Development

#### Configuration

Use `rpcWiFi`, `TFT_eSPI`, `Adafruit MQTT Library`, and the dependencies required by [the sketch](Light_Sensor/Light_Sensor.ino). Create the `light-level` feed and a dashboard gauge linked to it. Configure the credential example in `Light_Sensor/`.

The original guide describes a WiFiManager setup portal named `AutoConnectAP`. Check the selected sketch's actual Wi-Fi setup before using a portal; configure the connection according to its implementation.

### Test

#### Test

Confirm the LCD and dashboard update when ambient light changes. Check MQTT/Wi-Fi connection in serial output.

## References

### Common guides

- [Arduino development](../../../../../docs/arduino-development.md)
- [Credentials](../../../../../docs/credentials.md)
- [Adafruit IO setup](../../../../../docs/adafruit-io.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
