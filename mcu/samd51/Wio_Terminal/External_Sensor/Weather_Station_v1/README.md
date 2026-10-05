# Wio Terminal Weather Station v1

[English](README.md) | [Japanese](README.ja.md)

## Overview

Wio Terminal measures DHT11 temperature/humidity, displays them on its LCD, and publishes to Adafruit IO and Shiftr.io. Features include JSON telemetry, battery-base operation, and Wi-Fi/MQTT reconnection.

### Gallery

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/76df73232223085.68984e3bc47f8.jpg)

## Bill of Materials

| Part | Quantity | Role / Notes |
| ------------------------------------------------------------------------ | ---- | ---------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu)                                  | 1    | Main controller, display, and Wi-Fi module           |
| [Grove - Temperature & Humidity Sensor (DHT11)](https://amzn.to/3Um4qmA) | 1    | Connected to any of the Grove ports (code uses D0)   |
| USB Type-C Cable                                                         | 1    | For power and programming. Must be a data-sync cable |
| **Battery Base (Optional)**                                              | 1    | For standalone operation without USB power           |

## Development

### Hardware Development

#### Hardware and firmware

Connect the Grove DHT11 to D0 and use a data-capable USB-C cable. The battery base is optional. Use the Wio Terminal board package and `DHT sensor library`, `Adafruit Unified Sensor`, `PubSubClient`, and `ArduinoJson`.

Configure Wi-Fi, Adafruit IO username/key, and Shiftr.io key/secret through the [credential example](sketch/Weather_Station/credentials.h.example), then upload [the sketch](sketch/Weather_Station/Weather_Station.ino).

### Software Development

#### Cloud integration and test

See [the Adafruit IO integration](with_Adafruit_IO/README.md) for the `temperature` and `humidity` feeds. For BigQuery logging, use [the weather pipeline](../../../../../cloud/Cloud_Functions/Weather_Station_Data_Pipeline/README.md). Confirm sensor readings, LCD display, both MQTT connections, feed updates, and stored rows.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../../docs/arduino-development.md)
- [Credentials](../../../../../docs/credentials.md)
- [Adafruit IO setup](../../../../../docs/adafruit-io.md)
- [Cloud Functions workflow](../../../../../docs/cloud-functions.md)

- [Wio Terminal Documentation](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
- [DHT11 Sensor Guide](https://www.adafruit.com/product/386)
- [Adafruit IO Documentation](https://io.adafruit.com/api/docs/)
- [Shiftr.io Documentation](https://www.shiftr.io/docs/)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
