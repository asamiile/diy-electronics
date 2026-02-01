# Arduino Uno 8x8 LED Matrix

## Overview

- This project uses an Arduino UNO to control an 8x8 WS2812B LED matrix, displaying various animations like rainbow and ripple effects. A push button allows you to cycle through the patterns.

**Click to watch on YouTube**

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/6-BWVaQY8bo/hqdefault.jpg)](https://youtu.be/6-BWVaQY8bo?si=5ha3Cig4YXMKvDc2)


### LED Matrix glowing pattern

- Rainbow
![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/e68a6a229464473.68652fef57f01.jpg)

- Ripple
![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/3cc74e229464473.68652fef5b1e3.jpg)

- BouncingBall
![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/204169229464473.68652fef54ef1.jpg)

- OceanWave
![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/813954229464473.68652fef55609.jpg)

- Breathing
![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/7d1379229464473.68652fef57857.jpg)

[Here is](Arduino_Nano_ESP32_RGB_LED) a project with the same configuration created with Arduino Nano ESP32.

### Bill of Materials

#### Control System

| Part Type                                  | Unit | Role/Notes                      |
| ------------------------------------------ | ---- | ------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)     | 1    | Micro Controller.               |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1    | For writing programs to Arduino |


#### Input & Output

| Part Type                                      | Unit | Role/Notes     |
| ---------------------------------------------- | ---- | -------------- |
| [8x8 RGB LED WS2812B](https://amzn.to/44cSo3p) | 1    | display device |
| [Tact Switch](https://amzn.to/3T0gNUF)         | 1    | Input button   |


#### Power System

| Part Type                                                                                         | Unit | Role/Notes                               |
| ------------------------------------------------------------------------------------------------- | ---- | ---------------------------------------- |
| [Power Supply (5V, 2A+)](https://amzn.to/4jZEIyu) or [Mobile Power Bank](https://amzn.to/45jTQ5W) | 1    | Power supply for LEDs.                   |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)                                               | 1    | Connect the AC adapter to the breadboard |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ)                                        | 1    | For power supply stabilization           |


#### Prototyping & Wiring

| Part Type                                      | Unit  | Role/Notes                         |
| ---------------------------------------------- | ----- | ---------------------------------- |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2) | 1     | For protecting the LED's data line |
| [Breadboard](https://amzn.to/40bMzlk)          | 1     | Circuit base (for prototype)       |
| [Jumper Wires](https://amzn.to/45voWYC)        | 1 set | Connecting parts together          |


## Usage

### Hardware Development

-  Wire it according to [Arduino_Uno_LED_8x8_led_matrix_art_breadboard.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_8x8_LED_Matrix/diagrams/Fritzing/Arduino_Uno_LED_8x8_led_matrix_art_bb.png)


#### Wiring List

Before you apply power, carefully trace each connection with your finger and confirm that all of the following are correct.

- **Power Rails**
  - DC Jack (+) → Breadboard Positive (+) Rail
  - DC Jack (-) → Breadboard Negative (-) Rail
- **Power Stabilization**
  - 1000µF Capacitor is placed across the + and - power rails (Check for correct polarity: longer lead to +).
- **LED Matrix Power**
  - LED Matrix 5V wire → Breadboard (+) Rail
  - LED Matrix GND wire → Breadboard (-) Rail
- **Data Line**
  - Arduino D6 → 330Ω Resistor → LED Matrix DIN
- **Input Switch**
  - Arduino D2 → One leg of the Tactile Switch
  - Opposite leg of the Switch → An Arduino GND pin
- **Common Ground**
  - An Arduino GND pin → Breadboard Negative (-) Rail (This is essential for the circuit to work).


### Software Development

1. Open the Arduino IDE.
2. Install "Adafruit NeoPixel by Adafruit" from the menu Tools > Manage Libraries.
3. Open the project sketch file:  [Arduino_Uno_8x8_LED_Matrix.ino](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_8x8_LED_Matrix/sketch/Arduino_Uno_8x8_led_matrix/Arduino_Uno_8x8_led_matrix.ino)
4. Connect the Arduino to your computer using a USB cable (A-B) cable.
5. Select the correct COM port from the `Tools` menu and click the "Upload" button.


### Test

1. Double-check all wiring to ensure it matches the diagram.
2. Connect the external 5V power supply to the DC jack.
3. The LED matrix will now initialize and display the first animation pattern.
4. Press the tactile switch to cycle through the display patterns in order.
5. Confirm that all patterns are displayed correctly to complete the test.


## Author

[Asami.K](https://asami.tokyo/)

[Arduino Uno 8x8 LED Matrix - Behance](https://www.behance.net/gallery/229464473/Arduino-Uno-8x8-LED-Matrix)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
