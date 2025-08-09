#include "arduino_secrets.h"
#include "thingProperties.h"

// --- Constants for Pins ---
const int RED_PIN    = 2;
const int GREEN_PIN  = 3;
const int BLUE_PIN   = 4; 
const int BUTTON_PIN = 5;

// --- Global Variables ---
const int totalModes = 7; // 0:Off, 1-5:Static Colors, 6:Fade

// For button debouncing
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(115200);
  delay(1500); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Pin setup
  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Set initial color based on the Cloud variable's default value
  updateColor();
}

void loop() {
  ArduinoCloud.update();
  
  // Check the physical button's state
  handleButton();

  // If in fade mode, keep updating the color
  if (colorMode == 6) {
    colorFade();
  }
}

/*
  Function called when the 'colorMode' cloud variable changes
*/
void onColorModeChange() {
  Serial.print("Mode changed via Cloud to: ");
  Serial.println(colorMode);
  updateColor();
}

// Function to check for a physical button press
void handleButton() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) { // Button was pressed
        Serial.println("Button Pressed!");
        // Update the 'colorMode' cloud variable
        colorMode = (colorMode + 1) % totalModes;

        updateColor();
      }
    }
  }
  lastButtonState = reading;
}

// Function to set the LED color based on the current colorMode
void updateColor() {
  if (colorMode != 6) { // If not in fade mode
    switch (colorMode) {
      case 0: setColor(0, 0, 0); break;       // Off
      case 1: setColor(255, 152, 152); break; // Pink
      case 2: setColor(255, 159, 0); break;   // Orange
      case 3: setColor(52, 255, 186); break;  // Green
      case 4: setColor(80, 108, 255); break;  // Blue
      case 5: setColor(179, 55, 145); break;  // Purple
    }
  }
}

// --- Color-setting helper functions ---
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN,   red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN,  blue);
}

void colorFade() {
  unsigned long time = millis();
  int redVal   = (sin(time / 2000.0) * 127) + 128;
  int greenVal = (sin(time / 2000.0 + 2) * 127) + 128;
  int blueVal  = (sin(time / 2000.0 + 4) * 127) + 128;
  setColor(redVal, greenVal, blueVal);
  delay(10); 
}