# Wio Terminal Weather Station v2

[English](README.md) | [Japanese](README.ja.md)

## Overview

Weather Station v2 uses an I2C Grove BME280 to measure temperature, humidity, and pressure. The 320×240 LCD uses landscape rotation 3, three equal sections, and adaptive FMB18 text. It publishes to Adafruit IO and to BigQuery through Shiftr.io/Cloud Functions, with battery-base support and automatic Wi-Fi/MQTT reconnection.

## Bill of Materials

| Part | Quantity | Role / Notes |
| ------------------------------------------------------------ | ---- | ---------------------------------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu)                      | 1    | Main controller, display, and Wi-Fi module                                   |
| [Grove BME280 Environmental Sensor](https://amzn.to/4qcfIY1) | 1    | **NEW in v2**: Measures temperature, humidity, and barometric pressure (I2C) |
| USB Type-C Cable                                             | 1    | For power and programming. Must be a data-sync cable                         |
| **Battery Base (Optional)**                                  | 1    | For standalone operation without USB power                                   |

## Development

### Hardware Development

#### Hardware and firmware

Connect BME280 to the Wio Terminal I2C port (VCC 3.3V, GND, SCL, SDA). Use USB-C for data/power or the optional battery base.

Use `Seeed BME280`, `PubSubClient`, `ArduinoJson`, and the Wio-compatible `TFT_eSPI` configuration. Configure Wi-Fi, `AIO_USERNAME`, `AIO_KEY`, `SHIFTR_KEY`, and `SHIFTR_SECRET` in the credential example beside [the sketch](sketch/Weather_Station_v2/Weather_Station_v2.ino). After upload, use 115200 baud and check both MQTT connection messages.

### Software Development

#### Cloud integration

Adafruit IO uses `temperature` (°C), `humidity` (%RH), and `pressure` (hPa) feeds, documented with a 60-second update interval. Suggested gauge ranges are 15–30°C, 30–80%RH, and 950–1050 hPa; add 24-hour line charts if desired.

The BigQuery route is Wio Terminal → Shiftr.io topic `wio/json` → `save_weather_data` → `diy_electronics_iot.weather_data`. See [the weather pipeline](../../../../../cloud/Cloud_Functions/Weather_Station_Data_Pipeline/README.md) for the schema, including nullable `pressure`. [v1](../Weather_Station_v1/README.md) uses DHT11 without pressure measurement.

### Test

#### Test and analysis

Verify all three LCD sections, sensor readings, cloud feed updates, stored pressure values, and reconnection. The following query groups the current UTC date's samples by hour; it does not represent a rolling 24-hour window.

```sql
SELECT
  TIMESTAMP_TRUNC(timestamp, HOUR) AS hour,
  ROUND(AVG(temperature), 2) AS avg_temperature,
  ROUND(AVG(pressure), 1) AS avg_pressure,
  COUNT(*) AS sample_count
FROM `PROJECT_ID.diy_electronics_iot.weather_data`
WHERE DATE(timestamp) = CURRENT_DATE()
GROUP BY hour
ORDER BY hour DESC;
```

## References

### Common guides

- [Arduino development](../../../../../docs/arduino-development.md)
- [Credentials](../../../../../docs/credentials.md)
- [Adafruit IO setup](../../../../../docs/adafruit-io.md)
- [Cloud Functions workflow](../../../../../docs/cloud-functions.md)

- [Wio Terminal Documentation](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
- [BME280 Datasheet](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/)
- [Adafruit IO Documentation](https://io.adafruit.com/api/docs/)
- [Shiftr.io Documentation](https://www.shiftr.io/docs/)
- **[v1 Weather Station](../Weather_Station_v1/README.md)** - Original DHT11 version

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
