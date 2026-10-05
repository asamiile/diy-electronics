// Include the Servo library to control the servo motor
#include <Servo.h>

// --- Pin Definitions ---
const int SERVO_PIN = 9;
const int POT_PIN   = A0;
const int RED_PIN   = 11;
const int GREEN_PIN = 10;
const int BLUE_PIN  = 5;

// Create a Servo object
Servo myServo;

void setup() {
  // Attach the servo object to its control pin
  myServo.attach(SERVO_PIN);
  
  // Set the RGB LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  // --- Servo Control ---
  // This part works as before.
  int potValue = analogRead(POT_PIN);
  int servoAngle = map(potValue, 0, 1023, 0, 180);
  myServo.write(servoAngle);

  // --- LED Color Transition: Orange-ish to Blue-ish ---
  // Map the servo angle (0-180) to the new RGB values.
  // At 0 degrees, color is #FF8122 (R:255, G:129, B:34)
  // At 180 degrees, color is #22B3FF (R:34, G:179, B:255)
  int redValue   = map(servoAngle, 0, 180, 255, 34);
  int greenValue = map(servoAngle, 0, 180, 129, 179);
  int blueValue  = map(servoAngle, 0, 180, 34,  255);
  
  // Set the LED to the calculated color at full brightness.
  setLedColor(redValue, greenValue, blueValue, 1.0);
  
  // Add a small delay for stability
  delay(15);
}

// Function to set the LED color with brightness control
void setLedColor(int r, int g, int b, float brightness) {
  // Constrain brightness to a 0.0 - 1.0 range for safety
  brightness = constrain(brightness, 0.0, 1.0);

  // Calculate the final color values by applying the brightness
  int final_r = r * brightness;
  int final_g = g * brightness;
  int final_b = b * brightness;

  // Write the final values to the LED pins
  analogWrite(RED_PIN, final_r);
  analogWrite(GREEN_PIN, final_g);
  analogWrite(BLUE_PIN, final_b);
}