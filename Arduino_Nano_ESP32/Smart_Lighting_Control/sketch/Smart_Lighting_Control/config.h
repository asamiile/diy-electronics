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
#define SCHEDULED_OFF_HOUR 23      // Hour (0-23)
#define SCHEDULED_OFF_MINUTE 30    // Minute (0-59)

// ============================================
// Light Sensor Thresholds (Illuminance)
// ============================================
// Illuminance thresholds detected by TSL2561 (lux units)
#define LIGHT_ON_THRESHOLD 50      // Minimum illuminance threshold to detect light ON
#define LIGHT_OFF_THRESHOLD 10     // Maximum illuminance threshold to detect light OFF

// ============================================
// System Configuration
// ============================================
#define DEBUG_MODE true            // Output debug information to serial monitor
#define RECONNECT_INTERVAL 30000   // WiFi reconnection attempt interval (milliseconds)
#define FEEDBACK_CHECK_DELAY 2000  // Wait time after IR transmission before verifying with light sensor (milliseconds)

// ============================================
// Pin Definitions
// ============================================
#define IR_EMITTER_PIN D2          // Grove - Infrared Emitter (Digital Pin D2)
#define IR_RECEIVER_PIN D4         // Grove - Infrared Receiver (Digital Pin D4)
#define TSL2561_SDA_PIN SDA        // Grove - Digital Light Sensor (I2C SDA)
#define TSL2561_SCL_PIN SCL        // Grove - Digital Light Sensor (I2C SCL)

#endif
