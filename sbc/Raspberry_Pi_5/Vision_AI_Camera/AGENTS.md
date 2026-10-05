# AI Camera Production Module

## 1. Project overview

This module covers building and controlling the AI Camera used to collect graduation-project data.

- **Purpose:** observe indoor behavior and skeletons and convert them to numeric data.
- **Policy:** do not record video. Collect only analyzed numeric metadata (coordinates, labels, and illuminance) and send it to BigQuery.
- **Installation:** the living room, with the camera near the window.

### Current implementation scope

- **Prioritize Phase 1:** implement only the Arduino Nano ESP32 "eye" first: Vision AI, pan/tilt, environmental sensing, and JSON transmission to the Pi.
- **Speech recognition is not implemented:** Grove Speech Recognizer and ReSpeaker 2-Mics Pi HAT are available but excluded from the initial release. Revisit them after the Pi and data pipeline stabilize.

## 2. Hardware stack

| Component | Role | Connection |
| --- | --- | --- |
| Raspberry Pi 5 (16GB) | Main processing, MediaPipe analysis, and GCP communication | Wi-Fi |
| Arduino Nano ESP32 | Eye controller, pan/tilt control, and sensor aggregation | USB / Wi-Fi (UDP) |
| Vision AI Module V2 | Initial person/airplane detection | I2C |
| OV5647-62 Camera | Image input | Connected to Vision AI V2 |
| Pan-Tilt Platform | Automatic tracking using two B0283 servos | I2C (PCA9685) |
| Grove TSL2561 | Ambient illuminance in lux | I2C |

### Future audio components (not started)

| Component | Notes |
| --- | --- |
| Grove Speech Recognizer | Arduino side; outside the initial scope |
| ReSpeaker 2-Mics Pi HAT | Raspberry Pi side; outside the initial scope |

Related Arduino/data projects:

- [Smart Lighting Control](../../../mcu/esp32/Arduino_Nano_ESP32/Smart_Lighting_Control/README.md)
- [Smart Lighting Control Data Pipeline](../../../cloud/Cloud_Functions/Smart_Lighting_Control_Data_Pipeline/README.md)

## 3. System architecture and data flow

The system uses a distributed architecture.

### Phase 1: The Eye (Arduino side) — current priority

- Detect objects (Person/Airplane) with Vision AI Module V2.
- Move pan/tilt servos to keep the target centered.
- Read Grove TSL2561 illuminance.
- Send metadata as JSON to Raspberry Pi 5 over UDP/Wi-Fi or serial.

### Phase 2: The Brain (Raspberry Pi side) — after the eye

- Receive Arduino data.
- Extract 33 skeleton coordinates (x, y, z) using MediaPipe Pose.
- Combine action labels with environmental data and POST to FastAPI (Motion Studio Backend).
- Stream the resulting records into BigQuery.

## 4. Development sequence

Stabilize each step before advancing to the next.

1. **Build the AI Camera:** assemble the camera, Vision AI Module V2, pan/tilt platform, Grove TSL2561, wiring, and power. Use external servo power and a common GND.
2. **Implement Arduino firmware:** object detection, pan/tilt control, illuminance acquisition, and JSON creation/transmission to Raspberry Pi 5 over UDP/Wi-Fi or serial.
3. **Test behavior:** tracking, communication continuity, and non-blocking exception handling.
4. **Validate Pi reception:** inspect packet format and rate in logs or local output.
5. **Phase 2 analysis:** add skeleton coordinates and action labels using MediaPipe Pose or equivalent, matching the schema in section 5.
6. **Phase 2 backend integration:** POST to FastAPI (Motion Studio Backend); establish schema and error handling.
7. **Build and test BigQuery delivery:** prepare the dataset, table, schema, and service-account authentication; test streaming or batch writes.
8. **Optional data integration:** align device IDs and millisecond timestamps when combining with Smart Lighting Control data.

## 5. Data specification (BigQuery schema)

Generated records must follow this structure.

| Field | Description |
| --- | --- |
| `timestamp` | ISO 8601 timestamp |
| `target_type` | `"person"` / `"airplane"` / `"none"` |
| `skeleton_3d` | JSON array of 33 coordinate points; nullable when the target is not a person |
| `action_label` | Labels such as `"working"`, `"sitting"`, and `"walking"`; mainly used from Phase 2 |
| `environmental_data` | `{ lux: number \| null, voice_command: string \| null }`; keep `voice_command` null or omitted for now |
| `servo_angles` | `{ pan: number, tilt: number }` |

## 6. Development constraints

- **Non-blocking:** Arduino and Python must not stop their main loops while waiting for sensors.
- **Power:** use external 5V/4A servo power. Include common-GND guidance in code comments.
- **Integration:** preserve millisecond timestamp precision for joining with existing Smart Lighting Control data in BigQuery.

## 7. Current implementation tasks

### Phase 1 (priority)

- Implement the Arduino Nano ESP32 UDP bridge for detection and illuminance/sensor status.
- Implement pan/tilt tracking, using PID control or a suitable alternative.

### Phase 2 (after Phase 1 stabilizes)

- Optimize MediaPipe workloads for Raspberry Pi 5 with 16GB RAM.
- Design and implement audio input (Grove/ReSpeaker) and `voice_command`.
