# Indoor Zone Occupancy Data Collection Camera

[English](README.md) | [Japanese](README.ja.md)

## Overview

Observe people in the near work area and far door area of a long room, and retain metadata in the cloud for later analysis and visualization. Do not store images or video. This project is at the specification stage; implementation code is not included.

### MVP

- Start with one fixed zone to verify detection and cloud delivery, then patrol two registered zones.
- After the mount stops, collect multiple samples and classify each observation as occupied, empty, or unknown.
- Send one JSON record per observation from the Pi over authenticated HTTPS to an ingestion API and store it in BigQuery.
- Persist pending records on the Pi during outages; replay them after recovery with the same `event_id` and deduplicate at storage.
- Completion means records can be queried by period and zone using SQL and consumed later by visualization tools.

Dashboard application development, personal identification, person tracking, pose/action analysis, speech recognition, and temperature/humidity/illuminance measurements are outside the MVP. Counts represent the observed view, not total room occupancy or individual dwell histories.

## Bill of Materials

The six specified products are **confirmed**. Other rows distinguish required additions, included items to check, conditional items, and optional tools. The initial proposal uses microSD boot and USB serial communication with Vision AI V2.

### Control

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | ------------------------------- |
| [Raspberry Pi 5 (16GB)](https://amzn.to/4sqqta4) | 1 | **Confirmed**. Patrol, result aggregation, local queue, and cloud delivery. |
| [Grove - Vision AI Module V2](https://amzn.to/41Mx9Vs) | 1 | **Confirmed**. Person inference; verify result retrieval over USB during implementation. |
| microSD card (32–64GB, Class 10 / UHS-I; A2 candidate) | 1 | **Required addition** for microSD boot. OS, program, and pending JSON storage. Capacity is a project proposal. |
| USB microSD reader | 1 if needed | **Conditional**. OS imaging on the development PC; unnecessary with a compatible built-in slot. |

### Input / Output

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | ------------------------------- |
| [OV5647-62 FOV Camera Module for Raspberry Pi](https://amzn.to/41IEmWF) | 1 | **Confirmed**. Connect to Vision AI V2, not directly to the Pi CSI port in this architecture. |
| [Pan Tilt Platform for Raspberry Pi & Nvidia Jetson Cameras](https://amzn.to/3OeokzX) | 1 kit | **Confirmed**. Moves between zones; check the actual model number. |
| Mount servos, controller, assembly screws | 1 set | **Check included items**. The identically named Arducam B0283 includes two servos, an I2C controller, brackets, and screws; normally no separate purchase for B0283. Verify Pi 5 control. |

### Power

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | ------------------------------- |
| [Raspberry Pi 27W USB-C Power Supply](https://www.raspberrypi.com/products/27w-power-supply/) | 1 | **Confirmed**. Pi power; use a version suitable for Japanese mains outlets. |
| External mount supply and voltage regulation if needed | 1 circuit, depending on configuration | **Conditional**. Consider separate servo power to avoid startup disturbances. Determine voltage/current/connectors from the actual manual. B0283 lists servo operation at 3.6–4.8V and controller operation at 3–5V; do not assume direct 5V servo power is suitable. |
| Power terminal block / connector | 1 set with external power | **Conditional**. Match polarity, current capacity, and controller connections. |

Selecting the Pi's 27W supply does not settle mount power. For external power, follow controller instructions for common ground and do not inadvertently join the positive external supply and Pi 5V rail.

### Prototyping / Wiring

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | ------------------------------- |
| USB-A to USB-C data cable | 1 | **Required addition** for proposed USB communication. Pi USB-A to Vision AI USB-C; not charge-only. Start with 0.5–1m as a candidate and allow movement slack. |
| Camera FFC cable | 1 | **Check included items**. OV5647-62 to Vision AI V2. A standard 15-pin, 1mm-pitch cable is a candidate; verify connectors, contact orientation, and length against hardware before buying. A Pi 5 22-pin adapter is unnecessary for this connection. |
| Female-to-female jumper wires | Normally 4 | **Check included items**. Pi to I2C mount controller; B0283 includes four. Extend/replace only if case routing requires it. SDA, SCL, power, and GND; follow controller power instructions. |
| GPIO extension / low-profile connector | 1 if needed | **Conditional**. Avoid case/controller interference; check pin mapping, height, and cable exit. |
| Camera mounting spacers, screws / adapter plate | 1 set if needed | **Conditional**. Use if the Seeed camera's mounting holes/dimensions do not match the bracket. Select screw diameter/length on hardware. |
| Cable clips / ties | Several | **Required addition**. Provide strain relief and avoid tension during pan/tilt movement. |

Do not assume a breadboard, additional PCA9685, additional servos, Grove Shield, or Nano ESP32 is needed. If switching Vision AI communication to I2C, add the appropriate Grove adapter wiring and verify power/signal voltages.

### Case / Installation

| Part | Quantity | Role / Notes |
| ------------------------------------------ | ---- | ------------------------------- |
| [Raspberry Pi Case for Raspberry Pi 5](https://www.raspberrypi.com/products/raspberry-pi-5-case/) | 1 | **Confirmed**. Official case includes a cooling fan; no additional fan in the initial purchase list. |
| Mount base / shelf mounting hardware | 1 set | **Required addition**. Prevent movement of the installation; match mount holes and mounting surface. |
| Vision AI V2 fasteners / insulating spacers | 1 set | **Required addition**. Secure the exposed board and prevent metal contact. Proposed placement is near the Pi, with only the camera on the moving mount. |

Check case GPIO access, fan clearance, and controller placement. Leave sufficient FFC slack and verify no folding, snagging, or disconnection across the intended movement range.

### Network / Setup

| Part / environment | Quantity | Role / Notes |
| ------------------------------------------ | ---- | ------------------------------- |
| Wi-Fi router and Internet access | 1 environment | **Required environment**. No additional Wi-Fi adapter if onboard Wi-Fi works at the installation. |
| Ethernet cable (Cat 5e or higher) | 1 for wired use | **Conditional**. Use if Wi-Fi is unreliable. |
| Micro-HDMI to HDMI cable, monitor, USB keyboard | 1 each if needed | **Optional**. Local setup/troubleshooting; unnecessary if configured for SSH from the start. |

Prepare a microSD card, USB data cable, mounting base, board fasteners, and cable clips first. Check existing/included readers, FFC, and jumper wires; choose mount power and camera mounting adapters after hardware inspection.

## Development

### Hardware Development

#### Installation and observation zones

Fix the camera in the near corner of a long room (bottom left below), facing toward the far end. Split observations into the near work area and far door area.

```text
             Far end
┌────────────────────┐
│       Door         │
│                    │
│     Door area      │
│     door_area      │
│                    │
│     Work area      │
│     work_area      │
│    Desk / chair    │
│ Camera ↗           │
└────────────────────┘
             Near end
```

Mount on a shelf or wall at a height selected by checking seated people and people at the door. The proposed work view tilts downward and the door view faces farther into the room. Height, angles, and effective detection distances require hardware validation; they are not guaranteed constants.

| Zone ID | Target | View and region |
| --- | --- | --- |
| `work_area` | Near desk/chair | View containing seated people at close range; ROI covers the desk/chair area. |
| `door_area` | Far doorway | Far-facing view; ROI covers where people stand in front of the door. |

Alternate between two views: move → stop/settle → observe → classify/store. Views are not simultaneous. Brief door passages may be missed; use the door observations for usage trends, not exhaustive entry/exit counts.

#### ROI classification

Define a rectangular region of interest (ROI) for each view. Count a person only when the detection meets the confidence threshold and its bounding-box center lies inside the ROI, including its boundary. Sample/count/confidence aggregation uses only those detections. Missing or invalid ROI configuration produces `unknown` with `error_code: invalid_roi`.

Store `x_min`, `y_min`, `x_max`, and `y_max` normalized to image width/height in the same coordinate system as detection boxes, with the origin at the top left. Align coordinates after any model resizing/cropping before applying the rule. ROI changes update `config_version` and cloud configuration history.

An ROI is an image region, not a depth measurement. A nearby person overlapping the door ROI, or people/furniture obscuring the far area, can prevent correct separation. Adjust height, view directions, and ROIs.

During installation, check seated people being cropped out, furniture occlusion, far-person detection, day/night and backlighting, out-of-zone detections, and cable movement clearance. Document conditions that cannot be corrected as operational limitations.

Determine safe mount limits on hardware. Recorded angles are commands, not measured positions.

| Source | Destination | Checks |
| --- | --- | --- |
| OV5647-62 | Vision AI V2 | Camera cable orientation and connection. |
| Vision AI V2 | Raspberry Pi 5 | Transport, supported library, signal voltage; determine on hardware. |
| Raspberry Pi 5 | Mount controller | Control interface, pins, servo supply; determine on hardware. |

Do not power servos directly from Pi GPIO. Follow the chosen controller's requirements for external power and signal-ground connections.

### Software Development

#### Architecture and implementation sequence

```text
OV5647-62 → Vision AI V2 → Raspberry Pi 5
                            ├─ Patrol control and observation classification
                            ├─ Persistent pending-record queue
                            └─ HTTPS → Ingestion API → BigQuery
                                                       └─ SQL / visualization when needed
```

An ingestion API and BigQuery are planned. Select the API runtime, authentication, and table names during implementation. Pi OS, Python/library versions, model support, and performance are unverified. See [credential management](../../../docs/credentials.md) and the [Cloud Functions guide](../../../docs/cloud-functions.md) for shared authentication/deployment procedures.

1. Verify person detection and Pi result retrieval for one fixed zone.
2. Implement JSON generation, local persistence, and API-to-BigQuery delivery.
3. Verify mount control, then add two-zone patrol and sample aggregation.
4. Verify outages, restarts, retries, deduplication, and SQL retrieval.

#### Observation and classification

These settings are initial proposals. Tune on hardware and version every configuration change.

| Item | Initial proposal |
| --- | --- |
| Patrol | Two zones in registered order; target approximately 30 seconds between observations of each zone. |
| Settling | Wait one second after stopping; exclude images captured during movement. |
| Samples | Five per observation. |
| Detection threshold | Model confidence at least 0.7. |
| Classification | With five valid samples, at least three positives means `occupied`; otherwise `empty`. Fewer than five valid samples means `unknown`. |
| Time | Observation start in UTC with millisecond precision; verify clock synchronization before observing. |
| Waiting | Apply sensor/network timeouts so waits cannot halt patrol indefinitely. |

`empty` means the observation did not meet the occupied criterion; it does not guarantee physical absence. For `occupied`, `person_count` is the median count across positive valid samples (the lower middle value for even sample counts). `confidence` is the highest person confidence across those samples.

#### Stored data

Retain observation-level records before aggregation. Compute estimated use time through SQL when needed. The following examples are illustrative, not measurements.

| Field | Type / meaning |
| --- | --- |
| `event_id` | STRING. Unique observation ID, unchanged on retries. |
| `device_id` | STRING. Device identifier. |
| `observed_at` | TIMESTAMP. Observation start, UTC with millisecond precision. |
| `zone_id` | STRING. Zone identifier. |
| `occupancy_status` | STRING. `occupied` / `empty` / `unknown`. |
| `person_count` | INTEGER. Representative count; 0 for empty, null for unknown. |
| `confidence` | FLOAT. Representative confidence; null for empty/unknown. |
| `valid_sample_count` | INTEGER. Valid sample count. |
| `positive_sample_count` | INTEGER. Samples detecting a person above the threshold. |
| `pan_deg` / `tilt_deg` | FLOAT. Commanded mount angles. |
| `model_version` | STRING. Identifies the model and label mapping. |
| `config_version` | STRING. Zone and observation configuration version. |
| `schema_version` | INTEGER. Payload schema version. |
| `error_code` | STRING / null. Reason for unknown status; null when successful. |
| `received_at` | TIMESTAMP. Added by the cloud receiver. |

Example payloads show occupied, empty, and unknown due to an inference timeout. The API adds `received_at`.

```json
[
  {
    "event_id": "room-camera-01-20261007T103000123Z-work_area",
    "device_id": "room-camera-01",
    "observed_at": "2026-10-07T10:30:00.123Z",
    "zone_id": "work_area",
    "occupancy_status": "occupied",
    "person_count": 1,
    "confidence": 0.91,
    "valid_sample_count": 5,
    "positive_sample_count": 4,
    "pan_deg": 90,
    "tilt_deg": 75,
    "model_version": "person-detector-v1",
    "config_version": "zones-v1",
    "schema_version": 1,
    "error_code": null
  },
  {
    "event_id": "room-camera-01-20261007T103010123Z-door_area",
    "device_id": "room-camera-01",
    "observed_at": "2026-10-07T10:30:10.123Z",
    "zone_id": "door_area",
    "occupancy_status": "empty",
    "person_count": 0,
    "confidence": null,
    "valid_sample_count": 5,
    "positive_sample_count": 0,
    "pan_deg": 45,
    "tilt_deg": 75,
    "model_version": "person-detector-v1",
    "config_version": "zones-v1",
    "schema_version": 1,
    "error_code": null
  },
  {
    "event_id": "room-camera-01-20261007T103020123Z-door_area",
    "device_id": "room-camera-01",
    "observed_at": "2026-10-07T10:30:20.123Z",
    "zone_id": "door_area",
    "occupancy_status": "unknown",
    "person_count": null,
    "confidence": null,
    "valid_sample_count": 0,
    "positive_sample_count": 0,
    "pan_deg": 45,
    "tilt_deg": 75,
    "model_version": "person-detector-v1",
    "config_version": "zones-v1",
    "schema_version": 1,
    "error_code": "inference_timeout"
  }
]
```

Store zone configuration history separately in the cloud and join observations using device ID and configuration version. These angles are examples, not validated safe positions.

```json
{
  "device_id": "room-camera-01",
  "config_version": "zones-v1",
  "effective_from": "2026-10-07T10:00:00.000Z",
  "target_zone_interval_sec": 30,
  "settle_time_sec": 1,
  "samples_per_observation": 5,
  "confidence_threshold": 0.7,
  "positive_samples_required": 3,
  "zones": [
    {
      "zone_id": "work_area",
      "zone_name": "Work area",
      "pan_deg": 90,
      "tilt_deg": 75,
      "roi": {
        "x_min": 0.1,
        "y_min": 0.2,
        "x_max": 0.9,
        "y_max": 0.95
      }
    },
    {
      "zone_id": "door_area",
      "zone_name": "Door area",
      "pan_deg": 45,
      "tilt_deg": 75,
      "roi": {
        "x_min": 0.35,
        "y_min": 0.15,
        "x_max": 0.65,
        "y_max": 0.85
      }
    }
  ]
}
```

ROI coordinates above are illustrative placeholders. Calibrate against each installed view and verify that bounding-box center classification separates the zones.

#### Later analysis

- Plan date partitioning on `observed_at` and clustering on `device_id` / `zone_id`.
- Detection rate is occupied observations divided by classifiable observations. Exclude unknown; return null if no classifiable records exist.
- Dwell time is an estimate from patrol observations. Use midpoints between adjacent valid observations as state boundaries; exclude unknown intervals and gaps exceeding twice the configured target interval.
- Periods without records, such as a stopped Pi, are missing observations; do not fill them as empty.
- Do not sum counts from zones observed at different times into a room population.
- Proposed retention: observation records for 90 days, daily aggregates for one year. Select aggregate generation/storage during implementation.
- Define local queue limits and retry policy during implementation, log capacity failures, and mark records delivered only after confirmed persistence.

### Test

This is a specification update only. Implementation, cloud deployment, and hardware verification have not been performed. MVP acceptance criteria:

| Item | Acceptance criterion | Status |
| --- | --- | --- |
| Patrol | Repeatedly observe two zones within safe movement limits. | Not performed |
| Classification | Distinguish occupied, empty, and inference failure; exclude movement images. | Not performed |
| Installation / ROI | Detect seated people and people at the door, exclude out-of-ROI detections, and document occlusion/light/distance limits. | Not performed |
| Persistence | Store one record per observation and configuration history in the cloud. | Not performed |
| Recovery | Replay pending records after outages/restarts without duplicates in query results. | Not performed |
| Data use | Query by period/zone and identify unknown and missing observations. | Not performed |
| Stored content | Do not store images/video/audio or embed credentials in code. | Not performed |

## References

- [Arducam B0283 package contents and power specifications](https://www.arducam.com/blog/product/arducam-pan-tilt-platform-for-raspberry-pi-camera-2-dof-bracket-kit-with-digital-servos-and-ptz-control-broad-b0283/)
- [Raspberry Pi storage and setup](https://www.raspberrypi.com/documentation/computers/getting-started.html)
- [Parts inventory](https://docs.google.com/spreadsheets/d/1ZrbcD6XS5Xo5qeRy-CnxoPaLbTnPlHFerhubvc88T8E/edit?gid=941591219#gid=941591219)
- [Credential management](../../../docs/credentials.md)
- [Cloud Functions guide](../../../docs/cloud-functions.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
