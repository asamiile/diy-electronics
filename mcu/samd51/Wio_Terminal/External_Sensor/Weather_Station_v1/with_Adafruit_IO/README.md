# Wio Terminal Weather Station with Adafruit IO

[English](README.md) | [Japanese](README.ja.md)

## Overview

Adafruit IO integration for the DHT11 Weather Station v1: publish temperature/humidity, visualize gauges/charts, and optionally connect notifications. Device auto-reconnection and any Wi-Fi setup portal depend on the selected firmware.

### Gallery

[![Image from Gyazo](https://i.gyazo.com/2f3f2dd6637c2fdf2869a831bb386971.png)](https://gyazo.com/2f3f2dd6637c2fdf2869a831bb386971)

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

For sensors and wiring, see the original Weather Station project linked in References.

## Development

### Hardware Development

See Bill of Materials for the required hardware.

### Software Development

#### Project configuration

Follow [the parent project](../README.md) for D0 sensor wiring and the actual sketch. Create `temperature` and `humidity` feeds and one gauge per feed; configure `AIO_USERNAME` and `AIO_KEY` through the credential example. Required libraries are listed in the parent README.

The previous guide mentioned WiFiManager and Discord-triggered notifications; those are not automatically provided by creating an Adafruit IO dashboard. Check the chosen sketch and separately configure any notification integration.

### Test

#### Verification

Upload the parent project's firmware, confirm Wi-Fi/MQTT connection, and check that both feed values and dashboard gauges update.

## References

### Common guides

- [Arduino development](../../../../../../docs/arduino-development.md)
- [Adafruit IO setup](../../../../../../docs/adafruit-io.md)

- [Adafruit IO Documentation](https://io.adafruit.com/api/docs/)
- [MQTT Protocol Overview](https://mqtt.org/)
- [Adafruit MQTT Library](https://github.com/adafruit/Adafruit_MQTT_Library)
- [WiFiManager by tzapu](https://github.com/tzapu/WiFiManager)

## License

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Support

If you find this helpful, consider supporting the work:

[![BuyMeACoffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://buymeacoffee.com/asamiile)

## Author

[Asami.K](https://asami.tokyo/)
