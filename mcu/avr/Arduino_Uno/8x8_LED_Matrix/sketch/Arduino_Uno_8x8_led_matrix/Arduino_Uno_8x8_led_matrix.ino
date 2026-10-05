// Include required library
#include <Adafruit_NeoPixel.h>

// --- Constants ---
const int BUTTON_PIN = 2;      // Pin connected to the tactile switch
const int LED_PIN = 6;         // Pin connected to the LED matrix's data input (DIN)
const int LED_COUNT = 64;      // Total number of LEDs (8x8 = 64)

// Create NeoPixel object
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- Global Variables ---
int patternMode = 0;              // Stores the current display pattern (0: Off, 1: Red, 2: Rainbow)
const int totalPatterns = 6;      // Total number of patterns

// --- Ball Variables ---
float ballX = 3;
float ballY = 3;
float speedX = 0.3;
float speedY = 0.2;

// For button debouncing
int buttonState;
int lastButtonState = HIGH; 
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pixels.begin();
  pixels.setBrightness(50); // Limit brightness
  pixels.show(); // Initialize all LEDs to 'off'
}

void loop() {
  // 1. Check the button state
  handleButton();

  // 2. Update the LED pattern according to the current pattern mode
  updatePattern();
}

// Function to check if the button is pressed and change the pattern mode
void handleButton() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) { // if the button was just pressed
        patternMode = (patternMode + 1) % totalPatterns; // Cycle to the next pattern
        Serial.print("Pattern changed to: ");
        Serial.println(patternMode);
      }
    }
  }
  lastButtonState = reading;
}

// Function to draw the current pattern
void updatePattern() {
  switch (patternMode) {
    case 0: // Pattern 0: Off
      patternOff();
      break;
    case 1: // Pattern 2: Rainbow Animation
      patternRainbow();
      break;
    case 2: 
      patternRipple();
      break;      
    case 3:
      patternBouncingBall();
      break;
    case 4:
      patternOceanWave();
      break;
    case 5:
      patternBreathing();
      break;
  }
}

// --- Pattern-Specific Drawing Functions ---

void patternOff() {
  pixels.clear();
  pixels.show();
  delay(10); // Short delay to prevent loop from running too fast
}

void patternRainbow() {
  // Draw one frame of the rainbow animation
  static uint16_t j = 0; // Variable to store the position of the animation
  for (int i = 0; i < pixels.numPixels(); i++) {
    pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
  }
  pixels.show();
  j++; // Increment position for the next frame
  if (j >= 256) {
    j = 0;
  }
  delay(20); // Adjusts animation speed
}

// Ripple pattern
void patternRipple() {
  float rippleSpeed = 0.2;
  float rippleFrequency = 0.3;
  
  // Use millis() to make the wave change over time, creating an animation.
  float timeValue = millis() * rippleSpeed / 100.0;

  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      // Calculate the distance of each pixel from the center of the matrix.
      float distance = sqrt(pow(x - 3.5, 2) + pow(y - 3.5, 2));
      
      // Calculate brightness using a sine wave.
      // Brightness oscillates smoothly based on distance and time, creating the wave effect.
      uint8_t brightness = (uint8_t)(128 + 127 * sin(distance * rippleFrequency - timeValue));
      
      // Convert the (x, y) coordinate to a single pixel index for the NeoPixel library.
      int pixelIndex = x + y * 8;
      
      // Set the pixel to a white color with the calculated brightness.
      pixels.setPixelColor(pixelIndex, pixels.Color(brightness, brightness, brightness));
    }
  }
  pixels.show();
}

// Bouncing Ball
void patternBouncingBall() {
  // Clear the screen for the next frame
  pixels.clear();

  // Update the ball's position based on its current velocity
  ballX += speedX;
  ballY += speedY;

  // Reverse velocity if the ball hits a wall
  if (ballX >= 7.0 || ballX <= 0.0) {
    speedX *= -1;
  }
  if (ballY >= 7.0 || ballY <= 0.0) {
    speedY *= -1;
  }

  // Draw the pixel at the ball's new position
  pixels.setPixelColor((int)ballY * 8 + (int)ballX, pixels.Color(0, 191, 255));
  pixels.show();
  delay(30); // Adjusts the speed of the movement
}

// Gentle waves
void patternOceanWave() {
  float time = millis() / 2000.0; // 時間の経過

  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      // sin波で波の高さを計算
      float wave = sin(x * 0.8 + time);
      
      if (wave > 0.5) { // 波の山の部分
        pixels.setPixelColor(y * 8 + x, pixels.Color(100, 200, 255)); // 明るい水色
      } else { // 波の谷の部分
        pixels.setPixelColor(y * 8 + x, pixels.Color(0, 80, 150));   // 暗い青
      }
    }
  }
  pixels.show();
  delay(30);
}

// Slow breathing
void patternBreathing() {
  // 6秒かけて明るさが変化するsin波
  float breath = (sin(millis() / 2000.0) + 1.0) / 2.0; // 0.0 ~ 1.0の範囲に
  
  int brightness = (int)(breath * 80); // 明るさを0〜80の範囲で変化
  pixels.setBrightness(brightness);
  
  pixels.fill(pixels.Color(40, 0, 180)); // 画面を深い紫色で満たす
  pixels.show();
  delay(30);
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