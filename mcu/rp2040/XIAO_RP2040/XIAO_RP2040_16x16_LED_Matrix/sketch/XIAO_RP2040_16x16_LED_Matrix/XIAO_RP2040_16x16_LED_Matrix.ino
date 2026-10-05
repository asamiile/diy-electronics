// Required Library
#include <Adafruit_NeoPixel.h>

// --- Constants (Pin and Matrix Configuration) ---
const int LED_PIN = 6;       // The pin connected to the logic shifter for the LED data
const int BUTTON_PIN = 2;    // The pin connected to the push button
const int LED_COUNT = 256;   // Total number of LEDs (16x16 = 256)

// Create a NeoPixel object
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- Global Variables ---
int testMode = 0; // Stores the current test pattern
const int totalModes = 4; // Total number of test patterns

// For button debouncing
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = HIGH;

void setup() {
  // Initialize NeoPixels
  pixels.begin();
  pixels.setBrightness(40); // Set a safe, low brightness for testing (max 255)
  pixels.show(); // Turn all pixels off

  // Initialize the button pin with an internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Debug
  Serial.println("Setup finished. Starting loop...");
}

void loop() {
  // 1. Check if the button has been pressed
  handleButton();

  // 2. Display the current test pattern
  runTestPattern();
}

// Function to detect a button press and cycle through modes
void handleButton() {
  int reading = digitalRead(BUTTON_PIN);

  // If the button state has changed, reset the debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // After the debounce delay, if the button is pressed (LOW), change the mode
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW) {
      testMode = (testMode + 1) % totalModes; // Cycle to the next mode (0, 1, 2, 3)

      // Debug
      Serial.print("Button pressed! New mode: ");
      Serial.println(testMode);

      delay(200); // Wait a moment to prevent multiple rapid presses
    }
  }
  lastButtonState = reading;
}

// Function to call the correct pattern based on the current mode
void runTestPattern() {
  switch (testMode) {
    case 0:
      colorWipe(pixels.Color(255, 0, 0)); // Red
      break;
    case 1:
      colorWipe(pixels.Color(0, 255, 0)); // Green
      break;
    case 2:
      colorWipe(pixels.Color(0, 0, 255)); // Blue
      break;
    case 3:
      rainbowCycle(); // Rainbow
      break;
  }
}

// --- Test Pattern Functions ---

// Fills the screen with a single color
void colorWipe(uint32_t color) {
  pixels.fill(color);
  pixels.show();
}

// Displays a smoothly cycling rainbow pattern
void rainbowCycle() {
  static uint16_t j = 0;
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
  }
  pixels.show();
  j++;
  if (j >= 256 * 5) { // Cycle through the rainbow 5 times
    j = 0;
  }
  delay(10); // Adjust animation speed
}

// Helper function to generate rainbow colors
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}