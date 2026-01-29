# Wio Terminal Weather Station - Cloud Functions Pipeline

## Overview

Wio Terminal weather data integrated with **Shiftr.io MQTT broker** and **Google Cloud Functions** for real-time data streaming to **BigQuery**. Measures temperature and humidity using a Grove - DHT11 sensor.

**Key Features:**

- Real-time MQTT publishing to Shiftr.io
- Automatic webhook forwarding to Cloud Functions
- Streaming data insertion into BigQuery for analytics
- Scalable serverless architecture

## Architecture

```mermaid
graph LR
    A[Wio Terminal] -->|MQTT Publish<br>Topic: wio/json| B(Shiftr.io)
    B -->|Webhook POST<br>JSON Payload| C[Cloud Functions]
    C -->|Streaming Insert| D[(BigQuery)]

    style A fill:#f9f,stroke:#333,stroke-width:2px
    style B fill:#bbf,stroke:#333,stroke-width:2px
    style C fill:#aff,stroke:#333,stroke-width:2px
    style D fill:#faa,stroke:#333,stroke-width:2px
```

**Data Flow:**

1. **Wio Terminal** reads DHT11 sensor (temperature, humidity)
2. **MQTT** transmits JSON via WiFi to Shiftr.io
3. **Shiftr.io** forwards data via webhook to Cloud Functions
4. **Cloud Functions** validates and inserts data into BigQuery
5. **BigQuery** stores time-series data for analytics

## Prerequisites

### Hardware Setup

For hardware setup and assembly instructions, see [parent README](../README.md#hardware-setup).

### Software Prerequisites

- Wio Terminal with Arduino IDE setup (see [parent README](../README.md#software-setup))
- Google Cloud Project with BigQuery enabled
- Shiftr.io account (free tier: https://shiftr.io)
- Required libraries: `PubSubClient`, `ArduinoJson`

## Setup Instructions

### 1. Shiftr.io Setup

1. Create an account at [Shiftr.io](https://www.shiftr.io/)
2. Create a new MQTT instance (namespace):
   - Click "New Instance" or similar option
   - Enter a name (e.g., `wio-weather-station`)
3. Copy your instance credentials:
   - **Instance Name/Key**: Your unique identifier (case-sensitive)
   - **API Token/Secret**: Authentication credential

### 2. Arduino Sketch Configuration

Ensure you have installed the required libraries:

- `PubSubClient` by Nick O'Leary
- `ArduinoJson` by Benoit Blanchon
- `DHT` sensor library by Adafruit
- `Adafruit_Sensor` by Adafruit

For Arduino IDE setup and library installation details, see [parent README](../README.md#software-setup).

Update the sketch with your Shiftr.io credentials in `credentials.h`:

```cpp
#define SHIFTR_KEY "your_instance_name"       // Your Shiftr.io instance name (case-sensitive)
#define SHIFTR_SECRET "your_api_token"        // Your Shiftr.io API token
```

### 3. BigQuery Setup

Create dataset and table (run in Google Cloud Console):

```sql
CREATE SCHEMA IF NOT EXISTS diy_electronics_iot
  OPTIONS(description="IoT data from DIY projects");

CREATE TABLE IF NOT EXISTS diy_electronics_iot.weather_data (
  timestamp TIMESTAMP NOT NULL,
  device_id STRING,
  temperature FLOAT64,
  humidity FLOAT64
)
PARTITION BY DATE(timestamp);
```

### 4. Cloud Functions Deployment

#### Local Testing (Optional)

Test the Cloud Function locally before deployment:

```bash
# Install Functions Framework
pip install functions-framework google-cloud-bigquery

# Navigate to gcp directory
cd gcp

# Start local server
functions-framework --target=save_weather_data --debug
```

Test with curl in another terminal:

```bash
curl -X POST http://localhost:8080 \
  -H "Content-Type: application/json" \
  -d '{"device_id": "wio_terminal", "temperature": 22.5, "humidity": 55.0}'
```

Expected output: `Success`

#### Deploy to Google Cloud

For gcloud CLI setup and detailed deployment instructions, see [Google Cloud Setup](../../../../README.md#google-cloud-setup) in the root README.

Quick deployment:

```bash
cd gcp

gcloud functions deploy save-weather-data \
  --gen2 \
  --region=asia-northeast1 \
  --runtime=python310 \
  --source=. \
  --entry-point=save_weather_data \
  --trigger-http \
  --allow-unauthenticated
```

Copy the deployed function URL (will be shown at end of deployment).

### 5. Shiftr.io Webhook Configuration

1. Log in to Shiftr.io dashboard
2. Go to **Webhooks** section
3. Create new webhook:
   - **Topic**: `wio/json`
   - **URL**: Paste your Cloud Functions URL
   - **Method**: POST
   - **Format**: JSON

### 6. Upload & Configure

1. Upload the sketch to Wio Terminal
2. The device will connect to WiFi and start publishing data to Shiftr.io
3. Data will be automatically forwarded to BigQuery via Cloud Functions

## References

- [Wio Terminal Documentation](https://wiki.seeedstudio.com/Wio_Terminal_Getting_Started/)
- [Shiftr.io MQTT Broker](https://shiftr.io)
- [Shiftr.io Documentation](https://www.shiftr.io/docs/)
- [Google Cloud Functions](https://cloud.google.com/functions)
- [BigQuery Documentation](https://cloud.google.com/bigquery/docs)
- [MQTT Protocol Overview](https://mqtt.org/)
- [PubSubClient Library](https://github.com/knolleary/pubsub_client)
- [ArduinoJson Library](https://github.com/bblanchon/ArduinoJson)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
