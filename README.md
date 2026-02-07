# DIY Electronics

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Overview

These are a collection of DIY Electronics samples.

### Arduino UNO

- [RGB LED](Arduino_Uno/RGB_LED)
- [8x8 LED Matrix](Arduino_Uno/8x8_LED_Matrix)
- [Interactive Servo Light](Arduino_Uno/Interactive_Servo_Light)

### Arduino Nano ESP32

- [RGB LED](Arduino_Nano_ESP32/RGB_LED)

#### IoT with Adafruit IO & BigQuery

- [Smart Lighting Control](Arduino_Nano_ESP32/Smart_Lighting_Control)

<!-- ### XIAO RP2040 -->

<!-- ### XIAO ESP32C3 -->

<!-- ### ESP32-DevKitC  -->

### Wio Terminal

#### Built-In Peripherals

- [Button](Wio_Terminal/BuiltIn_Peripherals/Button)
- [5way Switch](Wio_Terminal/BuiltIn_Peripherals/5way_Switch)
- [Buzzer](Wio_Terminal/BuiltIn_Peripherals/Buzzer)
- [Buzzer Melody](Wio_Terminal/BuiltIn_Peripherals/Buzzer_Melody)
- [TFT LCD](Wio_Terminal/BuiltIn_Peripherals/TFT_LCD)
- [Graphics](Wio_Terminal/BuiltIn_Peripherals/Graphics)
- [Line Charts](Wio_Terminal/BuiltIn_Peripherals/Line_Charts)
- [Histograms](Wio_Terminal/BuiltIn_Peripherals/Histograms)

#### Built-In Sensors

- [Mic](Wio_Terminal/BuiltIn_Sensors/Mic)
- [Mic Graph](Wio_Terminal/BuiltIn_Sensors/Mic_Graph)
- [Light Sensor](Wio_Terminal/BuiltIn_Sensors/Light_Sensor)
- [Accelerometer](Wio_Terminal/BuiltIn_Sensors/Accelerometer)

<!-- - [Wio Terminal Digital Tape Measure](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_Digital_Tape_Measure) -->
<!-- - [Wio Terminal Digital Compass](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_Digital_Compass) -->

##### With Adafruit IO

- [Light Sensor](Wio_Terminal\BuiltIn_Sensors\Light_Sensor_With_AdafruitIO)

#### External Sensor

- [Grove - Analog Microphone (MEMS)](Wio_Terminal\External_Sensor\Grove_Analog_Microphone)

##### with Adafruit IO & BigQuery

- [Weather Station v1](Wio_Terminal\External_Sensor\Weather_Station_v1)
- [Weather_Station_v2](Wio_Terminal\External_Sensor\Weather_Station_v2)

#### IOT

- [Wifi BLE Scan](Wio_Terminal/Wifi_BLE_Scan)

<!-- - [GPS Tracker with Adafruit IO](https://github.com/asamiile/diy-electronics/tree/main/Wio_Terminal_GPS_Tracker_with_Adafruit_IO) -->

#### ML

##### with Edge Impulse

- [Word Detection](Wio_Terminal/ML/Word_Detection)
- [Audio scene recognition with microphone](Wio_Terminal/ML/Audio_scene_recognition_with_microphone)
- [Classifying hand gestures with accelerometer](Wio_Terminal/ML/Classifying_hand_gestures_with_accelerometer)
- [People counting with Ultrasonic sensor](Wio_Terminal/ML/People_counting_with_Ultrasonic_sensor)
- [Recognizing gestures with light sensor](Wio_Terminal/ML/Recognizing_gestures_with_light_sensor)

### SunFounder_GalaxyRVR

- [SunFounder_GalaxyRVR](SunFounder_GalaxyRVR)

## Building in VS Code

The workspace is configured for Arduino development using Arduino CLI. See [Arduino CLI official documentation](https://arduino.github.io/arduino-cli/) for detailed setup.

### Environment Setup

#### 1. Install Arduino CLI

```bash
# macOS (via Homebrew)
brew install arduino-cli

# Windows (via Chocolatey)
choco install arduino-cli

# Or download from https://arduino.github.io/arduino-cli/
```

#### 2. Install Board Support

```bash
# Wio Terminal (SAMD51)
arduino-cli core install Seeeduino:samd

# Arduino Nano ESP32
arduino-cli core install arduino:esp32

# XIAO RP2040
arduino-cli core install rp2040:rp2040

# Arduino Uno
arduino-cli core install arduino:avr
```

### Build and Upload

#### Detect Connected Boards

```bash
arduino-cli board list
```

#### Compile

```bash
# Wio Terminal
arduino-cli compile --fqbn seeeduino:samd:seeed_wio_terminal <sketch_directory>

# Arduino Nano ESP32
arduino-cli compile --fqbn arduino:esp32:nano_nora <sketch_directory>

# XIAO RP2040
arduino-cli compile --fqbn rp2040:rp2040:generic <sketch_directory>
```

#### Upload

```bash
# Wio Terminal (replace COM8 with your port)
arduino-cli upload -p COM8 --fqbn seeeduino:samd:seeed_wio_terminal <sketch_directory>

# Arduino Nano ESP32
arduino-cli upload -p COM8 --fqbn arduino:esp32:nano_nora <sketch_directory>

# XIAO RP2040
arduino-cli upload -p COM8 --fqbn rp2040:rp2040:generic <sketch_directory>
```

#### Serial Monitor

```bash
# Monitor serial output at 115200 baud (default)
arduino-cli monitor -p COM8

# With custom baud rate
arduino-cli monitor -p COM8 --config baudrate=115200
```

Press `Ctrl+C` to exit the monitor.

## Google Cloud Setup

Some projects integrate with Google Cloud services (BigQuery, Cloud Functions) for data logging and processing. This section covers the gcloud CLI setup and common deployment patterns.

### Prerequisites

Install the Google Cloud CLI (gcloud):

```bash
# macOS (via Homebrew)
brew install google-cloud-sdk

# Windows (via Chocolatey)
choco install google-cloud-cli

# Or download from https://cloud.google.com/sdk/docs/install
```

### Initial Configuration

```bash
# Authenticate with Google Cloud
gcloud auth login

# Set your GCP project (replace with your actual project ID)
gcloud config set project YOUR_GCP_PROJECT_ID

# Verify configuration
gcloud config list
```

### Deploy to Cloud Functions

Example: Deploying a weather data processor to Cloud Functions

```bash
# Navigate to the Cloud Functions directory
cd <project-path>/Cloud_Functions/Weather_Station_Data_Pipeline

# Deploy (first time or update existing)
gcloud functions deploy save_weather_data \
  --gen2 \
  --region=asia-northeast1 \
  --runtime=python311 \
  --source=. \
  --entry-point=save_weather_data \
  --trigger-http \
  --allow-unauthenticated
```

### Local Testing

Test Cloud Functions locally before deployment:

```bash
# Install the Functions Framework
pip install functions-framework google-cloud-bigquery

# Start local server
cd <project-path>/Cloud_Functions
functions-framework --target=save_weather_data --debug

# In another terminal, test the function
curl -X POST http://localhost:8080 \
  -H "Content-Type: application/json" \
  -d '{"device_id": "wio_terminal", "temperature": 22.5, "humidity": 55.0}'
```

### BigQuery Setup

Create the dataset and table for storing sensor data:

```sql
-- Create dataset
CREATE SCHEMA IF NOT EXISTS `PROJECT_ID.diy_electronics_iot`
  OPTIONS(
    description="IoT data from DIY electronics projects",
    location="asia-northeast1"
  );

-- Create table
CREATE TABLE IF NOT EXISTS `PROJECT_ID.diy_electronics_iot.weather_data` (
  timestamp TIMESTAMP NOT NULL,
  device_id STRING,
  temperature FLOAT64,
  humidity FLOAT64,
  pressure FLOAT64
)
PARTITION BY DATE(timestamp)
OPTIONS(
  description="Weather station sensor data",
  partition_expiration_ms=7776000000
);
```

### Troubleshooting Cloud Functions

```bash
# View function details
gcloud functions describe save-weather-data --gen2 --region=asia-northeast1

# View deployment logs
gcloud functions logs read save-weather-data --gen2 --region=asia-northeast1 --limit 50

# Delete function
gcloud functions delete save-weather-data --gen2 --region=asia-northeast1
```

### Useful gcloud Commands

```bash
# List all deployed functions
gcloud functions list --gen2

# Get function URL
gcloud functions describe save-weather-data --gen2 --region=asia-northeast1 --format="value(serviceConfig.uri)"

# Update function
gcloud functions deploy save-weather-data --update-env-vars VAR_NAME=value

# View quotas and usage
gcloud compute project-info describe --project YOUR_GCP_PROJECT_ID
```

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>

## Reference

- [Wio Terminal Guide](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
