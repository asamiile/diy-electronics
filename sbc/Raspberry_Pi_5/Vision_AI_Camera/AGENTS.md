# Indoor Occupancy Data Collection Camera

## Scope

- Follow the MVP and data contract in [README.md](README.md); maintain its Japanese counterpart.
- Observe indoor zones and store numeric observation metadata in the cloud for later SQL analysis and visualization.
- Required primary hardware: Raspberry Pi 5 (16GB), Grove Vision AI Module V2, OV5647-62 camera, and pan-tilt platform.
- Implement one fixed zone first, then two-zone patrol: `work_area` near the camera and `door_area` at the far end of a long room. Install the camera in the near corner facing inward. The Pi coordinates observation, mount control, persistence, and cloud delivery.
- Use a versioned rectangular ROI for each view; count only threshold-qualified person detections whose box centers lie inside the ROI. Match image coordinate systems and treat invalid ROI configuration as unknown.
- Do not claim depth separation or exhaustive entry/exit counting: foreground occlusion and sequential observation can cause missed detections. Validate placement and ROIs on hardware.
- Dashboard application development, Nano ESP32 firmware, environmental sensors, person tracking, skeleton/action analysis, and audio are outside the current MVP.
- Do not store images, video, or audio. Do not identify individuals.

## Hardware and execution

- Verify the exact mount controller, power requirements, signal voltages, and Vision AI-to-Pi transport before implementing wiring-dependent code.
- Do not assume the previous PCA9685/B0283 setup or an Arduino bridge is required.
- Use suitable external servo power and follow the controller's ground requirements.
- Use bounded, non-blocking sensor/network waits. Determine safe movement limits on hardware.
- Recorded mount angles are commands, not measured positions.

## Data and cloud

- Preserve UTC timestamps with millisecond precision, configuration/model/schema versions, and stable event IDs across retries.
- Follow README definitions for occupied, empty, unknown, sample aggregation, and null values.
- Persist pending observations across outages/restarts. Acknowledge delivery only after persistence and implement explicit deduplication; do not assume the database enforces event-ID uniqueness.
- Store versioned zone configurations alongside observation records.
- Treat missing observations and failed inference separately from empty observations. Do not sum zone counts into room population.
- The ingestion API and BigQuery are planned; runtime, authentication, queue limits, and retention implementation remain to be selected.
- Keep credentials out of code and examples.
- Report specification, local checks, deployment, and physical verification separately.
