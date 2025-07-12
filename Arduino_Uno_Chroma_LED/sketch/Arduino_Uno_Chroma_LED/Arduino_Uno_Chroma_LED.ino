/*
 * Project: Arduino Uno Chroma LED
 * Author: Asami.K
 *
 * Description:
 * A simple, interactive desk light using a single RGB LED.
 * A push button cycles through different colors and a smooth fade animation.
 *
 * Hardware:
 * - Arduino Uno
 * - 5mm Common Cathode RGB LED
 * - Tactile Push Button
 * - 3x 220 Ohm Resistors
 *
 * Connections:
 * - RGB LED Red Pin   -> 220Ω Resistor -> Arduino Pin ~9
 * - RGB LED Green Pin -> 220Ω Resistor -> Arduino Pin ~10
 * - RGB LED Blue Pin  -> 220Ω Resistor -> Arduino Pin ~11
 * - RGB LED GND Pin   -> Arduino GND
 * - Button Pin 1      -> Arduino Pin D2
 * - Button Pin 2      -> Arduino GND
 */

// --- Constants for Pins ---
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;
const int BUTTON_PIN = 2;

// --- Global Variables ---
int colorMode = 0;          // Stores the current color mode
const int totalModes = 7;   // Total number of modes 

// For button debouncing
int buttonState;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;


void setup() {
  // Set the LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Set the button pin as an input with an internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Start serial communication for debugging
  Serial.begin(9600);
}


void loop() {
  // 1. Check for button presses
  handleButton();

  // 2. Display the color based on the current mode
  updateColor();
}


// Checks for a button press and cycles through the color modes
void handleButton() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) { // Button was pressed
        colorMode = (colorMode + 1) % totalModes; // Cycle to the next mode
        Serial.print("Mode changed to: ");
        Serial.println(colorMode);
      }
    }
  }
  lastButtonState = reading;
}


// Calls the appropriate function to set the LED color based on the current mode
void updateColor() {
  switch (colorMode) {
    case 0:
      setColor(0, 0, 0); // Off
      break;
    case 1:
      setColor(255, 152, 152); // Pink
      break;
    case 2:
      setColor(255, 159, 0); // Orange
      break;
    case 3:
      setColor(52, 255, 186); // Green
      break;
    case 4:
      setColor(80, 108, 255); // Blue
      break;
    case 5:
      setColor(179, 55, 145); // Purple
      break;
    case 6:
      colorFade(); // Smooth color fade
      break;
  }
}


// --- Color-setting helper functions ---

// A simple function to set a specific R, G, B color
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}


// A function to create a smooth, slow color-fading animation
void colorFade() {
  // Use millis() and sine waves to smoothly cycle through colors
  unsigned long time = millis();
  
  int redVal   = (sin(time / 2000.0) * 127) + 128;
  int greenVal = (sin(time / 2000.0 + 2) * 127) + 128; // Phase shift
  int blueVal  = (sin(time / 2000.0 + 4) * 127) + 128; // Phase shift
  
  setColor(redVal, greenVal, blueVal);
  delay(10); // Small delay for the animation
}