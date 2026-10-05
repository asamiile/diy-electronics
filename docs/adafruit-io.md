# Adafruit IO setup

[English](adafruit-io.md) | [日本語](adafruit-io.ja.md)

Create an [Adafruit IO](https://io.adafruit.com/) account, obtain its username and AIO key, and configure them using the project's [credential instructions](credentials.md).

Create the exact feed names listed in the project README. Build a dashboard with gauges or line charts linked to those feeds, using the project's units and ranges. Upload the configured firmware, confirm Wi-Fi and MQTT connection in serial output, and check that feed timestamps and dashboard values update.

A configuration portal such as `AutoConnectAP` is project-specific; use it only when the selected sketch implements it. Keep Arduino Cloud / Arduino IoT Remote setup separate from Adafruit IO.

- [Adafruit IO API documentation](https://io.adafruit.com/api/docs/)
