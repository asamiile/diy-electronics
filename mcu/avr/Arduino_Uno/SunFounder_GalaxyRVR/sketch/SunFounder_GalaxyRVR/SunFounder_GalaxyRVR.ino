#include <SoftPWM.h>
#include <Servo.h>
#include "SunFounder_AI_Camera.h"
#include "credentials.h"

// --- [State Management] ---
bool isAvoidanceMode = false; 
bool isFollowMode    = false; 
bool isLightOn       = true;  

// --- [Device Settings] ---
#define WIFI_MODE WIFI_MODE_AP 
#define SSID      AP_SSID 
#define PASSWORD  AP_PASSWORD 

#define NAME "GalaxyRVR"
#define TYPE "AiCamera"
#define PORT "8765"

AiCamera aiCam = AiCamera(NAME, TYPE);
Servo myServo;

// --- [Pin Definitions] ---
#define ULTRASONIC_PIN 10
#define IR_RIGHT 7
#define IR_LEFT 8
#define BATTERY_PIN A3

const int bluePin  = 11;
const int redPin   = 12;
const int greenPin = 13;

const int in1 = 2; 
const int in2 = 3; 
const int in3 = 4; 
const int in4 = 5; 

/* Calibration Offsets for RGB LEDs */
#define R_OFFSET 1.0
#define G_OFFSET 0.25
#define B_OFFSET 0.45

// --- [Setup] ---
void setup() {
  Serial.begin(115200);
  myServo.attach(6);
  myServo.write(90); // Center the camera tilt at start

  aiCam.begin(SSID, PASSWORD, WIFI_MODE, PORT);
  aiCam.setOnReceived(onReceive); 
  aiCam.setCommandTimeout(100);

  SoftPWMBegin();
  stopMove(); 

  pinMode(IR_RIGHT, INPUT);
  pinMode(IR_LEFT, INPUT);
  pinMode(BATTERY_PIN, INPUT);
}

void loop() {
  aiCam.loop(); // Maintenance of connection

  // Handle autonomous logic if toggled ON
  if (isAvoidanceMode) {
    avoidanceLogic();
  } 
  else if (isFollowMode) {
    followLogic();
  }
}

// --- [Event Handler] ---
void onReceive() {
  // 1. [RESTORED] Region D: Camera Tilt Slider Control
  int16_t sliderD = aiCam.getSlider(REGION_D);
  myServo.write(int(sliderD));

  // 2. Mode and Light Switches
  isAvoidanceMode = aiCam.getSwitch(REGION_E);
  isFollowMode    = aiCam.getSwitch(REGION_F);
  isLightOn       = aiCam.getSwitch(REGION_J);

  // 3. Manual Throttle (K and Q)
  int8_t throttle_L = aiCam.getThrottle(REGION_K);
  int8_t throttle_R = aiCam.getThrottle(REGION_Q);

  // Manual driving logic
  if (!isAvoidanceMode && !isFollowMode) {
    if (throttle_L == 0 && throttle_R == 0) {
      stopMove();
    } else {
      carSetMotors(throttle_L, throttle_R);
    }
  }

  // 4. Telemetry Update
  aiCam.sendDoc["N"] = digitalRead(IR_LEFT);
  aiCam.sendDoc["P"] = digitalRead(IR_RIGHT);
  aiCam.sendDoc["O"] = readSensorData();
  aiCam.sendDoc["BV"] = batteryGetVoltage();
}

// --- [RGB Control] ---
void setColor(int red, int green, int blue) {
  if (isLightOn) {
    SoftPWMSet(redPin, red * R_OFFSET);
    SoftPWMSet(greenPin, green * G_OFFSET);
    SoftPWMSet(bluePin, blue * B_OFFSET);
  } else {
    SoftPWMSet(redPin, 0);
    SoftPWMSet(greenPin, 0);
    SoftPWMSet(bluePin, 0);
  }
}

// --- [Motor Logic] ---
void carSetMotors(int8_t power_L, int8_t power_R) {
  // Left side motors
  if (power_L >= 0) {
    SoftPWMSet(in1, map(power_L, 0, 100, 0, 255));
    SoftPWMSet(in2, 0);
  } else {
    SoftPWMSet(in1, 0);
    SoftPWMSet(in2, map(power_L, 0, -100, 0, 255));
  }

  // Right side motors
  if (power_R >= 0) {
    SoftPWMSet(in3, 0);
    SoftPWMSet(in4, map(power_R, 0, 100, 0, 255));
  } else {
    SoftPWMSet(in3, map(power_R, 0, -100, 0, 255));
    SoftPWMSet(in4, 0);
  }

  // Directional Color Logic
  if (power_L > 0 && power_R > 0) setColor(0, 255, 0);   // Green
  else if (power_L < 0 && power_R < 0) setColor(255, 0, 0);   // Red
  else if (power_L != power_R) setColor(255, 255, 0); // Yellow
}

void stopMove() {
  SoftPWMSet(in1, 0); SoftPWMSet(in2, 0);
  SoftPWMSet(in3, 0); SoftPWMSet(in4, 0);

  if (isLightOn) {
    // Fading effect for stopping
    for (int a = 0; a < 2; a++) {
      for (int i = 0; i < 255; i++) {
        setColor(i, 0, 255 - i);
        delay(5);
      }
      for (int i = 255; i > 0; i--) {
        setColor(i, 0, 255 - i);
        delay(5);
      }
    }
  } else {
    setColor(0, 0, 0);
  }
}

// --- [Helper Movement Functions for Autonomous Mode] ---
void moveForward(int speed) {
  SoftPWMSet(in1, speed); SoftPWMSet(in2, 0);
  SoftPWMSet(in3, 0);     SoftPWMSet(in4, speed);
  setColor(0, 255, 0);
}

void moveBackward(int speed) {
  SoftPWMSet(in1, 0);     SoftPWMSet(in2, speed);
  SoftPWMSet(in3, speed); SoftPWMSet(in4, 0);
  setColor(255, 0, 0);
}

void turnLeft(int speed) {
  SoftPWMSet(in1, 0);     SoftPWMSet(in2, speed);
  SoftPWMSet(in3, 0);     SoftPWMSet(in4, speed);
  setColor(255, 255, 0);
}

void turnRight(int speed) {
  SoftPWMSet(in1, speed); SoftPWMSet(in2, 0);
  SoftPWMSet(in3, speed); SoftPWMSet(in4, 0);
  setColor(255, 255, 0);
}

void backLeft(int speed) {
  SoftPWMSet(in1, 0);     SoftPWMSet(in2, 0);
  SoftPWMSet(in3, speed); SoftPWMSet(in4, 0);
  setColor(255, 165, 0);
}

// --- [Autonomous Mode Definitions] ---
void avoidanceLogic() {
  float distance = readSensorData();
  if (distance > 50) moveForward(200);
  else if (distance < 15 && distance > 1) {
    moveBackward(200);
    delay(500); 
    backLeft(150);
    delay(1000); 
  } else moveForward(150);
}

void followLogic() {
  float distance = readSensorData();
  int rightValue = digitalRead(IR_RIGHT);
  int leftValue = digitalRead(IR_LEFT);
  if (distance > 5 && distance < 30) moveForward(150);
  else if (rightValue == 0 && leftValue == 1) turnRight(150);
  else if (rightValue == 1 && leftValue == 0) turnLeft(150);
  else stopMove();
}

// --- [Sensor Helpers] ---
float readSensorData() {
  delay(4);
  pinMode(ULTRASONIC_PIN, OUTPUT);
  digitalWrite(ULTRASONIC_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC_PIN, LOW);
  pinMode(ULTRASONIC_PIN, INPUT);
  float duration = pulseIn(ULTRASONIC_PIN, HIGH, 30000); 
  return duration * 0.034 / 2;
}

float batteryGetVoltage() {
  int adcValue = analogRead(BATTERY_PIN);
  float adcVoltage = adcValue / 1023.0 * 5 * 2;
  return int(adcVoltage * 100) / 100.0;
}
