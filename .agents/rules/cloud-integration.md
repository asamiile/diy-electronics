# MQTT and cloud integration

- Read the target project's README and source to identify its broker, topic, payload, and destination. Keep Adafruit IO and Shiftr.io / Cloud Functions configurations distinct.
- For Shiftr.io, match the device's publication topic to the webhook Topic exactly. Check the destination URL, `application/json`, and enabled status.
- Trace delivery failures through device publication logs, broker reception history, webhook request history, Cloud Functions logs, and BigQuery schema and permissions.
- When changing existing topics, payloads, or device IDs, update both publishers and consumers consistently.

See the READMEs of the individual [Cloud Functions projects](../../cloud/Cloud_Functions/) for detailed setup and execution instructions.
