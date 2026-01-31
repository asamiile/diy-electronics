/*
 * Smart Lighting Control - Main Program
 * Arduino Nano ESP32
 *
 * Features:
 * - WiFi connection and NTP time synchronization (JST)
 * - Scheduled IR signal transmission at specified time
 * - Light sensor feedback verification
 * - Automatic retry on send failure
 * - Non-blocking operation using millis()
 */

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>

// Important: Define IR protocols before including IRremote
#define DECODE_NEC
#include <IRremote.hpp>

// Include configuration files
#include "credentials.h"
#include "config.h"

// ============================================
// System State Variables
// ============================================

// WiFi and NTP
unsigned long lastNTPSyncTime = 0;
const unsigned long NTP_SYNC_INTERVAL = 3600000; // Sync every hour (ms)

// Scheduled task
unsigned long lastTaskExecutionTime = 0;
bool taskExecutedToday = false;

// Sensor measurements
uint16_t currentLux = 0;
unsigned long lastSensorReadTime = 0;

// IR sending state
unsigned long lastIRSendTime = 0;
bool waitingForFeedback = false;
int retryCount = 0;
const int MAX_RETRIES = 3;

// ============================================
// Setup
// ============================================

void setup() {
  // Initialize Serial
  Serial.begin(115200);
  while (!Serial); // Wait for serial connection
  delay(1000);

  Serial.println();
  Serial.println(F("================================="));
  Serial.println(F("Smart Lighting Control"));
  Serial.println(F("Arduino Nano ESP32"));
  Serial.println(F("================================="));
  Serial.println();

  // Initialize pins
  initializePins();

  // Initialize WiFi
  initializeWiFi();

  // Synchronize time from NTP
  syncNTPTime();

  // Initialize light sensor (TSL2561)
  initializeLightSensor();

  // Initialize IR sender
  IrSender.begin(IR_EMITTER_PIN);

  Serial.println(F("System initialized successfully."));
  Serial.println(F("Waiting for scheduled time..."));
  Serial.println();
}

// ============================================
// Main Loop
// ============================================

void loop() {
  // Non-blocking operations

  // Check and refresh NTP time periodically
  if (millis() - lastNTPSyncTime > NTP_SYNC_INTERVAL) {
    syncNTPTime();
  }

  // Read sensor periodically
  if (millis() - lastSensorReadTime > 60000) { // Read every 60 seconds (for BigQuery logging)
    readLightSensor();
    lastSensorReadTime = millis();
  }

  // Check for scheduled task execution
  checkScheduledTask();

  // Handle IR feedback verification
  if (waitingForFeedback) {
    handleFeedbackVerification();
  }

  // Print status periodically
  static unsigned long lastStatusPrint = 0;
  if (millis() - lastStatusPrint > 10000) { // Print every 10 seconds
    printSystemStatus();
    lastStatusPrint = millis();
  }

  delay(100); // Small delay to prevent watchdog timeout
}

// ============================================
// WiFi Initialization
// ============================================

void initializeWiFi() {
  Serial.println(F("Connecting to WiFi..."));
  Serial.print(F("SSID: "));
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int attempts = 0;
  const int MAX_ATTEMPTS = 20;

  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPTS) {
    delay(500);
    Serial.print(F("."));
    attempts++;
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("WiFi connected successfully."));
    Serial.print(F("IP Address: "));
    Serial.println(WiFi.localIP());
  } else {
    Serial.println(F("WiFi connection failed. Retrying..."));
  }
}

// ============================================
// NTP Time Synchronization
// ============================================

void syncNTPTime() {
  Serial.println(F("Syncing time from NTP server..."));

  // Set timezone and sync time
  configTzTime("JST-9", NTP_SERVER, NTP_SERVER_JP);

  // Wait for time to be set
  time_t now = time(nullptr);
  int attempts = 0;
  while (now < 24 * 3600 && attempts < 30) {
    delay(500);
    Serial.print(F("."));
    now = time(nullptr);
    attempts++;
  }

  Serial.println();

  if (now > 24 * 3600) {
    struct tm* timeinfo = localtime(&now);
    Serial.print(F("Current JST: "));
    Serial.println(asctime(timeinfo));
    lastNTPSyncTime = millis();
  } else {
    Serial.println(F("NTP sync failed."));
  }
}

// ============================================
// Pin Initialization
// ============================================

void initializePins() {
  pinMode(IR_EMITTER_PIN, OUTPUT);
  digitalWrite(IR_EMITTER_PIN, LOW);
}

// ============================================
// Light Sensor Initialization
// ============================================

void initializeLightSensor() {
  Serial.println(F("Initializing Grove - Light Sensor..."));

  // Configure analog pin for reading
  pinMode(LIGHT_SENSOR_PIN, INPUT);

  // Take initial reading to stabilize
  delay(100);
  analogRead(LIGHT_SENSOR_PIN);

  Serial.println(F("✓ Light Sensor initialized successfully"));
}

// ============================================
// Light Sensor Reading
// ============================================

void readLightSensor() {
  // Read current light level using Grove - Light Sensor
  // Raw value: 0-4095 (12-bit ADC)
  // Higher value = brighter light

  int rawValue = analogRead(LIGHT_SENSOR_PIN);

  // For display purposes, convert to 10-bit equivalent (0-1023)
  currentLux = rawValue / 4;
}

void checkScheduledTask() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);

  int currentHour = timeinfo->tm_hour;
  int currentMinute = timeinfo->tm_min;
  int currentSecond = timeinfo->tm_sec;

  // Check if scheduled time has arrived (23:30)
  if (currentHour == SCHEDULED_OFF_HOUR &&
      currentMinute == SCHEDULED_OFF_MINUTE &&
      currentSecond >= 0 && currentSecond < 2) { // Allow 2-second window

    if (!taskExecutedToday && !waitingForFeedback) {
      Serial.println();
      Serial.println(F(">>> Scheduled OFF time reached (23:30) <<<"));

      // Check light sensor status before sending OFF command
      Serial.print(F("Current Light Level: "));
      Serial.print(currentLux);
      Serial.println(F(" (10-bit)"));

      if (currentLux >= LIGHT_OFF_THRESHOLD) {
        // Light is ON (bright) - send OFF command
        Serial.println(F("✓ Light is ON - Sending OFF command..."));
        sendLightOffSignal();
      } else {
        // Light is already OFF (dark) - do nothing
        Serial.println(F("⊘ Light is already OFF - No action needed"));
      }

      lastTaskExecutionTime = millis();
      taskExecutedToday = true;
    }
  }

  // Reset flag at end of day (23:59)
  if (currentHour == 23 && currentMinute == 59) {
    taskExecutedToday = false;
  }
}

// ============================================
// IR Signal Transmission
// ============================================

void sendLightOffSignal() {
  Serial.println(F("Sending IR OFF signal (raw waveform)..."));

  // Send the exact infrared waveform captured from the physical remote
  // This ensures complete compatibility with the ceiling light's receiver
  // by transmitting the raw IR signal at 38 kHz (standard IR frequency)
  IrSender.sendRaw(rawDataON_OFF, RAW_DATA_LENGTH, 38);

  Serial.println(F("Raw IR signal transmitted:"));
  Serial.print(F("  Data length: "));
  Serial.print(RAW_DATA_LENGTH);
  Serial.println(F(" timings"));
  Serial.println(F("  Frequency: 38 kHz"));
  Serial.println(F("  Status: Sent successfully"));

  lastIRSendTime = millis();
  waitingForFeedback = true;
  retryCount = 0;
}

// ============================================
// Feedback Verification
// ============================================

void handleFeedbackVerification() {
  unsigned long timeSinceIRSend = millis() - lastIRSendTime;

  // Wait FEEDBACK_CHECK_DELAY milliseconds after sending
  if (timeSinceIRSend >= FEEDBACK_CHECK_DELAY) {
    Serial.println(F("Checking light sensor for feedback..."));
    readLightSensor();

    // currentLux contains raw value / 4 (10-bit equivalent)
    // Need to get actual raw value for comparison
    int rawValue = analogRead(LIGHT_SENSOR_PIN);

    Serial.print(F("Current light level (raw): "));
    Serial.print(rawValue);
    Serial.print(F(" (10-bit equiv: "));
    Serial.print(currentLux);
    Serial.println(F(")"));

    // Check if light is off (raw value below threshold)
    if (rawValue < LIGHT_OFF_THRESHOLD) {
      Serial.println(F("✓ Light OFF confirmed. Task successful."));
      waitingForFeedback = false;
      retryCount = 0;
    }
    // Light still on - attempt retry
    else if (retryCount < MAX_RETRIES) {
      retryCount++;
      Serial.print(F("✗ Light still ON. Retry #"));
      Serial.println(retryCount);
      sendLightOffSignal();
    }
    // Max retries exceeded
    else {
      Serial.println(F("✗ Light OFF failed after maximum retries."));
      waitingForFeedback = false;
      retryCount = 0;
    }
  }
}

// ============================================
// System Status Output
// ============================================

void printSystemStatus() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);

  Serial.println();
  Serial.println(F("--- System Status ---"));
  Serial.print(F("Time (JST): "));
  Serial.print(timeinfo->tm_hour);
  Serial.print(F(":"));
  if (timeinfo->tm_min < 10) Serial.print(F("0"));
  Serial.print(timeinfo->tm_min);
  Serial.print(F(":"));
  if (timeinfo->tm_sec < 10) Serial.print(F("0"));
  Serial.println(timeinfo->tm_sec);

  Serial.print(F("WiFi Status: "));
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(F("Connected"));
  } else {
    Serial.println(F("Disconnected"));
  }

  Serial.print(F("Light Level: "));
  Serial.print(currentLux);
  Serial.println(F(" (10-bit)"));

  Serial.print(F("Task Status: "));
  if (taskExecutedToday) {
    Serial.println(F("Executed today"));
  } else {
    Serial.println(F("Pending"));
  }

  if (waitingForFeedback) {
    Serial.print(F("Feedback Status: Waiting (Retry "));
    Serial.print(retryCount);
    Serial.print(F("/"));
    Serial.print(MAX_RETRIES);
    Serial.println(F(")"));
  }

  Serial.println(F("--------------------"));
  Serial.println();
}
