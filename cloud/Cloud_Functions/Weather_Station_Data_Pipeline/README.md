# Weather Station Data Pipeline

[English](README.md) | [Japanese](README.ja.md)

## Overview

Receive JSON from a Wio Terminal through a Shiftr.io webhook and insert temperature, humidity, and optional pressure into BigQuery. DHT11/v1 has no pressure reading; BME280/v2 supplies it.

## Bill of Materials

No dedicated electronic components are required. See Software Development for the required services and dependencies.

## Development

### Hardware Development

No dedicated hardware setup is required.

### Software Development

#### Project configuration

- Deployment name: `save-weather-data`; entry point: `save_weather_data`; documented runtime: `python312`.
- Dataset/table: `diy_electronics_iot.weather_data`.
- Device topic: `wio/json` (match the selected firmware).
- Dependencies: [requirements.txt](requirements.txt); implementation: [main.py](main.py).
- Hardware: [Weather Station v1](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v1/README.md) or [v2](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2/README.md).

Use the common cloud guide for environment preparation, deployment, logs, and webhook setup. Copy the deployed trigger URL into the webhook. The existing deployment pattern uses public HTTP invocation.

#### BigQuery schema

The function generates its own current UTC timestamp. Missing pressure is stored as null. The table must accept the `pressure` field even when the device uses DHT11.

```sql
CREATE SCHEMA IF NOT EXISTS `YOUR_GCP_PROJECT_ID.diy_electronics_iot`;
CREATE TABLE IF NOT EXISTS `YOUR_GCP_PROJECT_ID.diy_electronics_iot.weather_data` (
  timestamp TIMESTAMP NOT NULL,
  device_id STRING,
  temperature FLOAT64,
  humidity FLOAT64,
  pressure FLOAT64
)
PARTITION BY DATE(timestamp);
```

### Test

#### Local and deployed tests

After installing dependencies, run `python test_local.py`. This uses local test mode and does not insert rows into BigQuery. To run the HTTP server without database writes, set `LOCAL_TEST_MODE=true` before starting Functions Framework with `save_weather_data`.

```sh
curl -X POST http://localhost:8080 \
  -H "Content-Type: application/json" \
  -d '{"device_id":"wio_terminal","temperature":22.5,"humidity":55.0,"pressure":1013.2}'
```

Local test mode returns JSON with `status: success` and the transformed row. For a deployed test, replace the local URL with the actual trigger URL; a successful database write returns `Success` with HTTP 200.

```sql
SELECT timestamp, device_id, temperature, humidity, pressure
FROM `YOUR_GCP_PROJECT_ID.diy_electronics_iot.weather_data`
ORDER BY timestamp DESC
LIMIT 10;
```

## References

### Common guides

- [Cloud Functions workflow](../../../docs/cloud-functions.md)
- [Credentials](../../../docs/credentials.md)

- [Cloud Functions Documentation](https://cloud.google.com/functions/docs)
- [BigQuery Documentation](https://cloud.google.com/bigquery/docs)
- [Shiftr.io Documentation](https://www.shiftr.io/docs/)
- [MQTT Protocol Overview](https://mqtt.org/)
- [Wio Terminal Weather Station](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2)
- [Wio Terminal Weather Station](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2) - Hardware sketch and sensors

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
