# Smart Lighting Control Data Pipeline

[English](README.md) | [Japanese](README.ja.md)

## Overview

Receive lighting telemetry through Shiftr.io and store selected fields in BigQuery. The [Nano ESP32 device](../../../mcu/esp32/Arduino_Nano_ESP32/Smart_Lighting_Control/README.md) also publishes light values to Adafruit IO.

## Bill of Materials

No dedicated electronic components are required. See Software Development for the required services and dependencies.

## Development

### Hardware Development

No dedicated hardware setup is required.

### Software Development

#### Project configuration

- Deployment name/entry point: `save_lighting_data`; documented runtime: `python311`.
- Dataset/table: `diy_electronics_iot.lighting_data`.
- Dependencies: [requirements.txt](requirements.txt); implementation: [main.py](main.py).
- Read the actual `SHIFTR_TOPIC` in the device's `config.h` and match the webhook. Do not copy `wio/json` from the weather project.

Use the common cloud guide for environment preparation, deployment, logs, and webhook setup. The existing example uses a public HTTP endpoint.

#### Data mapping and schema

The function maps `lux` → `light_level` and `light_state` → `status`. A supplied Unix `timestamp` is converted to UTC; without it, the function uses the current UTC time. Missing `device_id` defaults to `unknown_device`, missing lux to 0, and missing state to `UNKNOWN`. Input fields `task_executed`, `wifi_connected`, and `retry_count` are not stored by the current function.

```sql
CREATE SCHEMA IF NOT EXISTS `YOUR_GCP_PROJECT_ID.diy_electronics_iot`;
CREATE TABLE IF NOT EXISTS `YOUR_GCP_PROJECT_ID.diy_electronics_iot.lighting_data` (
  timestamp TIMESTAMP NOT NULL,
  device_id STRING,
  light_level INTEGER,
  status STRING
)
PARTITION BY DATE(timestamp);
```

### Test

#### Local and deployed tests

Set `LOCAL_TEST_MODE=true` before starting Functions Framework with `save_lighting_data` to skip database writes. Submit:

```sh
curl -X POST http://localhost:8080 \
  -H "Content-Type: application/json" \
  -d '{"device_id":"arduino_nano_esp32","timestamp":1769926200,"lux":2367,"light_state":"ON","task_executed":false,"wifi_connected":true,"retry_count":0}'
```

Local mode returns `status: success`, `Data received (test mode)`, and the transformed row. Replace the URL with the deployed trigger URL to test a real write; success returns `Data inserted successfully`.

```sql
SELECT timestamp, device_id, light_level, status
FROM `YOUR_GCP_PROJECT_ID.diy_electronics_iot.lighting_data`
ORDER BY timestamp DESC
LIMIT 10;
```

## References

### Common guides

- [Cloud Functions workflow](../../../docs/cloud-functions.md)
- [Credentials](../../../docs/credentials.md)
- [Adafruit IO setup](../../../docs/adafruit-io.md)

- [Cloud Functions Documentation](https://cloud.google.com/functions/docs)
- [BigQuery Documentation](https://cloud.google.com/bigquery/docs)
- [Shiftr.io Documentation](https://www.shiftr.io/docs/)
- [MQTT Protocol Overview](https://mqtt.org/)
- [Arduino Nano ESP32 Smart Lighting Control](../../../mcu/esp32/Arduino_Nano_ESP32/Smart_Lighting_Control)
- [Arduino Nano ESP32 Smart Lighting Control](../../../mcu/esp32/Arduino_Nano_ESP32/Smart_Lighting_Control) - Hardware sketch and sensors
- [Wio Terminal Weather Station](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2) - Similar IoT data pipeline example

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
