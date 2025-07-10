# Arduino Uno 8x8 LED Matrix

## Overview

- This project uses an Arduino UNO and an 8x8 WS2812B RGB LED matrix to display various art patterns and animations. You can switch between patterns using a tactile switch, enjoying effects such as rainbow, wave, ripple, and breathing. The project utilizes the Adafruit NeoPixel library and works with simple wiring and code. The vivid expressions of the LED matrix make it ideal for interior decoration or educational purposes.

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/2bd1c8229464473.68652fef58605.jpg)


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


### Bill of Materials

| Part Type                                                                  | Unit  | Role/Notes                               |
| -------------------------------------------------------------------------- | ----- | ---------------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)                                     | 1     | Microcomputer                            |
| [8x8 RGB LED WS2812B](https://amzn.to/44cSo3p)                             | 1     | display device                           |
| [Tact Switch](https://amzn.to/3T0gNUF)                                     | 1     | Input button                             |
| [Power Supply (5V, 2A+)](https://amzn.to/4jZEIyu) or [Mobile Power Bank](https://amzn.to/449XEpG) | 1     | Power supply for LEDs.                   |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)                        | 1     | Connect the AC adapter to the breadboard |
| [USB cable (A-B)](https://amzn.to/407P2xg)                                 | 1     | For writing programs to Arduino          |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2)                             | 1     | For protecting the LED's data line       |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ)                 | 1     | For power supply stabilization           |
| [Breadboard](https://amzn.to/40bMzlk)                                      | 1     | Circuit base (for prototype)             |
| [Jumper Wires](https://amzn.to/45voWYC)                                    | 1 set | Connecting parts together                |
|                                                                            |       |                                          |


## Usage

### Hardware Development

-  Wire it according to [Arduino_Uno_LED_8x8_led_matrix_art_breadboard.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_8x8_led_matrix/diagrams/Fritzing/Arduino_Uno_LED_8x8_led_matrix_art_bb.png)


#### Wiring List

Before you apply power, carefully trace each connection with your finger and confirm that all of the following are correct.

- Power Rails:
  - DC Jack (+) → Breadboard Positive (+) Rail
  - DC Jack (-) → Breadboard Negative (-) Rail
- Power Stabilization:
  - 1000µF Capacitor is placed across the + and - power rails (Check for correct polarity: longer lead to +).
- LED Matrix Power:
  - LED Matrix 5V wire → Breadboard (+) Rail
  - LED Matrix GND wire → Breadboard (-) Rail
- Data Line:
  - Arduino D6 → 330Ω Resistor → LED Matrix DIN
- Input Switch:
  - Arduino D2 → One leg of the Tactile Switch
  - Opposite leg of the Switch → An Arduino GND pin
- Common Ground:
  - An Arduino GND pin → Breadboard Negative (-) Rail (This is essential for the circuit to work).


### Software Development

1. Open the Arduino IDE.
2. Install "Adafruit NeoPixel by Adafruit" from the menu Tools > Manage Libraries.
3. Write the [Arduino_Uno_8x8_led_matrix.ino](Arduino_Uno_8x8_led_matrix/sketch/Arduino_Uno_8x8_led_matrix/Arduino_Uno_8x8_led_matrix.ino) code to Arduino.

### Test

1. Upload the sketch to the Arduino and connect the power supply.
2. The LED matrix will initialize and display the first pattern.
3. Press the tactile switch to cycle through the display patterns in order.
4. Confirm that all patterns are displayed correctly to complete the test.


## Final Assembly

### 1. Soldering to a Prototyping Board

Make your breadboard circuit permanent by soldering it onto a PCB (Printed Circuit Board). For safety, please work in a well-ventilated area.

### Bill of Materials (for Final Assembly)

| Part Type                                                                                         | Unit  | Role/Notes                                   |
| ------------------------------------------------------------------------------------------------- | ----- | -------------------------------------------- |
| [Seeed Studio XIAO RP2040](https://amzn.to/3TrkrHs)                                               | 1     | Micro Controller.                            |
| [8x8 RGB LED WS2812B](https://amzn.to/44cSo3p)                                                    | 1     | display device                               |
| [JST SM 3-Pin Connector](https://amzn.to/3GCiy7N)                                                 | 1 set | To easily connect/disconnect the LED matrix. |
| [Tactile Switch](https://amzn.to/4nHuvd1)                                                         | 1     | Input button                                 |
| [Power Supply (5V, 2A+)](https://amzn.to/4jZEIyu) or [Mobile Power Bank](https://amzn.to/449XEpG) | 1     | Power supply for LEDs.                       |
| [Logic Level Shifter](https://amzn.to/4eeDyhr)                                                    | 1     | To convert the data signal voltage.          |
| [PCB Mount DC Power Jack (5.5x2.1mm)](https://amzn.to/4kuBPG4)                                    | 1     | For soldering directly onto the PCB.         |
| [USB cable (A-B)](https://amzn.to/407P2xg)                                                        | 1     | For writing programs to Arduino              |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2)                                                    | 1     | To protect the LED's data line.              |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ)                                        | 1     | To stabilize the power supply.               |
| [Prototyping PCB](https://amzn.to/4lpHRJu)                                                        | 1     | Circuit base for soldering.                  |
| [Hook-up Wire](https://amzn.to/45XlDK0)                                                           | 1 set | To connect the components.                   |


### 2. 3D-Printed Enclosure



## Author

[Asami.K](https://asami.tokyo/)

[Arduino Uno 8x8 LED Matrix - Behance](https://www.behance.net/gallery/229464473/Arduino-Uno-8x8-LED-Matrix)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
