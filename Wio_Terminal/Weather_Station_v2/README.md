# Wio Terminal Weather Station v2

## Overview

Weather Station v2 is an upgraded version of the original Weather Station, now featuring **atmospheric pressure measurement** using the Grove BME280 sensor. This project transforms the Wio Terminal into a comprehensive environmental monitoring station that measures temperature, humidity, and barometric pressure in real-time.

The data is visualized both locally on the Wio Terminal's LCD screen and remotely on cloud dashboards (Adafruit IO and BigQuery via Shiftr.io).

### Key Improvements over v1

| Feature               | v1 (DHT11)                | v2 (BME280)                               |
| --------------------- | ------------------------- | ----------------------------------------- |
| **Sensors**           | Temperature, Humidity     | Temperature, Humidity, **Pressure** ✨    |
| **Sensor Type**       | DHT11                     | BME280 (I2C)                              |
| **Cloud Storage**     | Adafruit IO only          | Adafruit IO + BigQuery                    |
| **UI Layout**         | Basic vertical (1 column) | **3-equal-section layout** ✨             |
| **Font Optimization** | Single size               | Adaptive FMB18 for readability ✨         |
| **Data Pipeline**     | Direct to Adafruit IO     | Shiftr.io → Cloud Functions → BigQuery ✨ |

### Features

- **Real-time Multi-Parameter Display**: Temperature, humidity, and **pressure** on LCD
- **Optimized UI**: 3-equal-section layout with balanced typography for 320×240 screen
- **Dual Cloud Integration**:
  - **Adafruit IO**: Real-time gauges and charts (temperature, humidity, pressure feeds)
  - **BigQuery**: Historical data storage via Shiftr.io webhook + Cloud Functions
- **Pressure Trend Monitoring**: Track barometric pressure changes for weather prediction
- **Battery Support**: Standalone operation via battery base
- **Auto Reconnection**: Automatic WiFi and MQTT reconnection

## Bill of Materials

| Part Type                                                    | Unit | Role/Notes                                                                   |
| ------------------------------------------------------------ | ---- | ---------------------------------------------------------------------------- |
| [Wio Terminal](https://amzn.to/4me4lxu)                      | 1    | Main controller, display, and Wi-Fi module                                   |
| [Grove BME280 Environmental Sensor](https://amzn.to/4qcfIY1) | 1    | **NEW in v2**: Measures temperature, humidity, and barometric pressure (I2C) |
| USB Type-C Cable                                             | 1    | For power and programming. Must be a data-sync cable                         |
| **Battery Base (Optional)**                                  | 1    | For standalone operation without USB power                                   |

**Note:** v1 used a DHT11 sensor. The BME280 is superior for pressure measurement accuracy and stability.

## Hardware Setup

1. **Connect BME280 Sensor to I2C Port:**
   - Insert the Grove BME280 into one of the I2C connectors on the Wio Terminal (usually labeled I2C or I2C1)
   - The sensor will communicate via I2C protocol (SCL/SDA pins)

2. **Power Connection:**
   - USB Type-C cable for programming and power during development
   - Optional: Battery base for standalone operation

3. **Wio Terminal Orientation:**
   - Rotate to landscape (3) for better display of 3-parameter layout

**Wiring Diagram:**

```
Wio Terminal I2C Port ←→ Grove BME280
  ├─ VCC (3.3V)
  ├─ GND
  ├─ SCL (I2C Clock)
  └─ SDA (I2C Data)
```

## Software Setup

See [Wio Terminal Getting Started Guide](https://wiki.seeedstudio.com/Wio_Terminal_Intro/) for basic setup.

### 1. Install Dependencies

#### Via Arduino IDE GUI

- Tools → Manage Libraries
  - Search and install: `Seeed_BME280`
  - Search and install: `PubSubClient` by Nick O'Leary
  - Search and install: `ArduinoJson` by Benoit Blanchon
  - Search and install: `TFT_eSPI` by Bodmer (usually pre-installed)

#### Via Arduino CLI

```bash
arduino-cli lib install "Seeed BME280"
arduino-cli lib install "PubSubClient"
arduino-cli lib install "ArduinoJson"
```

### 2. Configure Credentials

1. Copy `credentials.h.example` to `credentials.h`:

   ```bash
   cp sketch/Weather_Station_v2/credentials.h.example sketch/Weather_Station_v2/credentials.h
   ```

2. Edit `credentials.h` with your settings:

   ```cpp
   // WiFi Configuration
   #define WIFI_SSID "YOUR_SSID"
   #define WIFI_PASSWORD "YOUR_PASSWORD"

   // Adafruit IO Configuration
   #define AIO_USERNAME "your_username"
   #define AIO_KEY "your_api_key"

   // Shiftr.io Configuration
   #define SHIFTR_KEY "your_shiftr_key"
   #define SHIFTR_SECRET "your_shiftr_secret"
   ```

### 3. Compile and Upload

**Using Arduino IDE:**

- File → Open → `sketch/Weather_Station_v2/Weather_Station_v2.ino`
- Tools → Board → Wio Terminal
- Sketch → Upload

**Using Arduino CLI:**

```bash
arduino-cli compile --fqbn seeeduino:samd:seeed_wio_terminal sketch/Weather_Station_v2
arduino-cli upload -p COM8 --fqbn seeeduino:samd:seeed_wio_terminal sketch/Weather_Station_v2
```

### 4. Verify Serial Output

```bash
# Monitor at 115200 baud
arduino-cli monitor -p COM8 --config baudrate=115200
```

Expected output:

```
[WiFi] Initializing WiFi module...
Connected to WiFi. IP: 192.168.0.xx
[Attempt 1/5] Attempting MQTT connection to io.adafruit.com:1883
✓ Adafruit IO MQTT connected successfully!
[Shiftr.io Attempt 1/3] Connecting to public.cloud.shiftr.io:1883
✓ Shiftr.io MQTT connected successfully!
```

## Cloud Integration

### Adafruit IO Dashboard

Weather Station v2 publishes to three separate feeds on Adafruit IO:

| Feed Name     | Data Type   | Update Interval |
| ------------- | ----------- | --------------- |
| `temperature` | Float (°C)  | 60 seconds      |
| `humidity`    | Float (%RH) | 60 seconds      |
| `pressure`    | Float (hPa) | 60 seconds      |

**Dashboard Setup:**

1. Create three blocks in Adafruit IO dashboard:
   - **Temperature Gauge**: Range 15-30°C
   - **Humidity Gauge**: Range 30-80%RH
   - **Pressure Gauge**: Range 950-1050 hPa
   - **Line Charts**: 24-hour history for each parameter

2. Access dashboard at: https://io.adafruit.com/{YOUR_USERNAME}/dashboards

### BigQuery Data Pipeline

Weather data is logged to BigQuery for long-term storage and analysis via the Shiftr.io → Cloud Functions → BigQuery pipeline.

**Data Flow:**

```
Wio Terminal (MQTT)
  ↓ Shiftr.io (wio/json topic)
  ↓ Webhook (Cloud Functions)
  ↓ Cloud Functions (save_weather_data)
  ↓ BigQuery (weather_data table)
```

**BigQuery Table Schema:**

```sql
CREATE TABLE IF NOT EXISTS `PROJECT_ID.diy_electronics_iot.weather_data` (
  timestamp TIMESTAMP NOT NULL,
  device_id STRING,
  temperature FLOAT64,
  humidity FLOAT64,
  pressure FLOAT64
)
PARTITION BY DATE(timestamp)
```

For detailed setup instructions, see:

- **[Weather Station Data Pipeline](../../../Cloud_Functions/Weather_Station_Data_Pipeline/README.md)**
- **[Google Cloud Setup](../../../README.md#google-cloud-setup)** in root README

**Query Example:**

```sql
-- Average temperature and pressure over last 24 hours
SELECT
  TIMESTAMP_TRUNC(timestamp, HOUR) AS hour,
  ROUND(AVG(temperature), 2) AS avg_temperature,
  ROUND(AVG(pressure), 1) AS avg_pressure,
  COUNT(*) AS sample_count
FROM `PROJECT_ID.diy_electronics_iot.weather_data`
WHERE DATE(timestamp) = CURRENT_DATE()
GROUP BY hour
ORDER BY hour DESC
```

## References

- [Wio Terminal Documentation](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
- [BME280 Datasheet](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/)
- [Adafruit IO Documentation](https://io.adafruit.com/api/docs/)
- [Shiftr.io Documentation](https://www.shiftr.io/docs/)
- **[v1 Weather Station](../Weather_Station_v1/README.md)** - Original DHT11 version

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
