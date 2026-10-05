#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// NTP Server Settings (Time Synchronization)
// ============================================
#define NTP_SERVER "pool.ntp.org"
#define NTP_SERVER_JP "ntp.jst.mfeed.ad.jp"
#define TIMEZONE_OFFSET 9  // JST (UTC+9)
#define DAYLIGHT_OFFSET 0  // No daylight saving time in Japan

// ============================================
// Scheduled Lighting Control
// ============================================
// Set the time to turn off lights (24-hour format)
#define SCHEDULED_OFF_HOUR 23      // Hour (0-23) - PRODUCTION: 23:30
#define SCHEDULED_OFF_MINUTE 30    // Minute (0-59) - PRODUCTION: 23:30 (daily)

// ============================================
// Light Sensor Configuration (Grove - Light Sensor)
// ============================================
// CdS phototransistor (GL5528) connected to analog pin A0 (D6 port)
// Threshold calibrated for user's environment:
// - Light OFF (dark): 0-40 (10-bit equiv)
// - Light ON (normal): 121+ (10-bit equiv)
#define LIGHT_SENSOR_PIN A0              // Analog input pin
#define LIGHT_OFF_THRESHOLD 32           // 10-bit equivalent: Light below this = OFF (regular sensor reading)
#define LIGHT_ON_THRESHOLD 150           // Reserved for future use
#define SCHEDULED_OFF_THRESHOLD 80       // Threshold for scheduled OFF at 23:30 (requires multiple readings)
#define SCHEDULED_OFF_READ_COUNT 5       // Number of consecutive readings for scheduled OFF check
#define SCHEDULED_OFF_READ_INTERVAL 100  // Interval between readings (milliseconds)

// ============================================
// System Configuration
// ============================================
#define DEBUG_MODE true            // Output debug information to serial monitor
#define RECONNECT_INTERVAL 30000   // WiFi reconnection attempt interval (milliseconds)
#define FEEDBACK_CHECK_DELAY 2000  // Wait time after IR transmission before verifying with light sensor (milliseconds)

// ============================================
// IR Control Configuration (NEC Protocol)
// ============================================
// Ceiling Light Specifications:
// Protocol: NEC
// Address: 0x1275 (from remote learning)
#define IR_ADDRESS 0x1275         // NEC address for ceiling light
#define IR_COMMAND_TOGGLE 0x207   // ON/OFF toggle command
#define IR_COMMAND_BRIGHTNESS_UP 0x208
#define IR_COMMAND_BRIGHTNESS_DOWN 0x206
#define IR_COMMAND_NIGHT_LIGHT 0x203
#define IR_COMMAND_FULL_BRIGHT 0x202

// ============================================
// Raw IR Data (Cloned from Physical Remote)
// ============================================
// This is the exact infrared waveform captured from the physical remote's ON/OFF button
// Format: Mark duration (LED on), Space duration (LED off), ...
// Device: Arduino Nano ESP32
// Learning sketch: IR_Learning.ino
// Captured: 2026-01-31
const uint16_t rawDataON_OFF[] PROGMEM = {
  8950, 4500,
  550, 1650, 550, 550, 550, 1650, 550, 550,
  550, 1650, 550, 1650, 550, 1700, 500, 600,
  550, 550, 550, 1650, 550, 550, 550, 550,
  550, 1650, 550, 550, 550, 550, 550, 600,
  500, 1700, 550, 1650, 550, 1650, 550, 550,
  550, 550, 550, 550, 550, 550, 550, 550,
  550, 1700, 550, 1650, 550, 550, 550, 550,
  550, 550, 550, 550, 550, 600, 500, 550,
  600
};
#define RAW_DATA_LENGTH (sizeof(rawDataON_OFF) / sizeof(rawDataON_OFF[0]))

// ============================================
// Shiftr.io MQTT Configuration
// ============================================
#define SHIFTR_SERVER "public.cloud.shiftr.io"
#define SHIFTR_PORT 1883
#define SHIFTR_TOPIC "lighting/json"
#define DEVICE_ID "arduino_nano_esp32"         // Device identifier for BigQuery
// Credentials from credentials.h
#define SHIFTR_USERNAME SHIFTR_KEY      // From credentials.h
#define SHIFTR_PASSWORD SHIFTR_SECRET   // From credentials.h
#define SHIFTR_SUBSCRIBE_TOPIC "lighting/json/in"

// ============================================
// Adafruit IO MQTT Configuration
// ============================================
#define ADAFRUIT_SERVER "io.adafruit.com"
#define ADAFRUIT_PORT 1883
#define MQTT_PUBLISH_INTERVAL 60000            // Send data every 60 seconds

// ============================================
// Pin Definitions
// ============================================
#define IR_EMITTER_PIN 2           // D2 (GPIO 2)
#define IR_RECEIVER_PIN 4          // D4 (GPIO 4)

#endif
