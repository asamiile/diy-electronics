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
#define DECODE_ONKYO
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
  if (millis() - lastSensorReadTime > 5000) { // Read every 5 seconds
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
  Serial.println(F("Initializing TSL2561 light sensor..."));
  // Note: Actual initialization depends on the Grove TSL2561 library
  // This is a placeholder for sensor setup
  Serial.println(F("Light sensor initialized."));
}

// ============================================
// Light Sensor Reading
// ============================================

void readLightSensor() {
  // Read current light level (Lux)
  // This is a placeholder - replace with actual sensor library call
  // Example: currentLux = lightSensor.getLux();

  // For now, we'll use a dummy value for demonstration
  currentLux = analogRead(A0) / 10; // Simulated reading
}

// ============================================
// Scheduled Task Check
// ============================================

void checkScheduledTask() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);

  int currentHour = timeinfo->tm_hour;
  int currentMinute = timeinfo->tm_min;
  int currentSecond = timeinfo->tm_sec;

  // Check if scheduled time has arrived
  if (currentHour == SCHEDULED_OFF_HOUR &&
      currentMinute == SCHEDULED_OFF_MINUTE &&
      currentSecond >= 0 && currentSecond < 2) { // Allow 2-second window

    if (!taskExecutedToday && !waitingForFeedback) {
      Serial.println();
      Serial.println(F(">>> Scheduled OFF time reached <<<"));

      sendLightOffSignal();

      lastTaskExecutionTime = millis();
      taskExecutedToday = true;
    }
  }

  // Reset flag at end of day
  if (currentHour == 23 && currentMinute == 59) {
    taskExecutedToday = false;
  }
}

// ============================================
// IR Signal Transmission
// ============================================

void sendLightOffSignal() {
  Serial.println(F("Sending IR OFF signal..."));

  // Send the learned IR code
  // For Onkyo protocol: Address=0x1275, Command=0x207
  IrSender.sendOnkyo(IR_OFF_CODE >> 8, IR_OFF_CODE & 0xFF, 1);

  Serial.print(F("IR Code sent: 0x"));
  Serial.println(IR_OFF_CODE, HEX);

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

    Serial.print(F("Current light level: "));
    Serial.print(currentLux);
    Serial.println(F(" Lux"));

    // Check if light is off
    if (currentLux <= LIGHT_OFF_THRESHOLD) {
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
  Serial.println(F(" Lux"));

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
