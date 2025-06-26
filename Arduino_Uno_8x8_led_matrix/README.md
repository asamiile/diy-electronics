# Arduino Uno 8x8 LED Matrix

## Overview

- This project uses an Arduino UNO and an 8x8 WS2812B RGB LED matrix to display various art patterns and animations. You can switch between patterns using a tactile switch, enjoying effects such as rainbow, wave, ripple, and breathing. The project utilizes the Adafruit NeoPixel library and works with simple wiring and code. The vivid expressions of the LED matrix make it ideal for interior decoration or educational purposes.


### Bill of Materials

| Part Type                                                  | Num   | Role/Notes                         |     |
| ---------------------------------------------------------- | ----- | ---------------------------------- | --- |
| [Arduino UNO](https://amzn.to/44nRXEA)                     | 1     | Microcomputer                      |     |
| [8x8 RGB LED WS2812B](https://amzn.to/44cSo3p)             | 1     | display device                     |     |
| [Tact Switch](https://amzn.to/3T0gNUF)                     | 1     | Input button                       |     |
| [External AC adapter (5V)](https://amzn.to/4jZEIyu)        | 1     | Power supply for LEDs              |     |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)        | 1     | Connect the AC adapter to the breadboard |     |
| [USB cable (A-B)](https://amzn.to/407P2xg)                 | 1     | For writing programs to Arduino    |     |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2)             | 1     | For protecting the LED's data line |     |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ) | 1     | For power supply stabilization     | 
| [Breadboard](https://amzn.to/40bMzlk)                      | 1     | Circuit base (for prototype)       |     |
| [Jumper Wires](https://amzn.to/45voWYC)                    | 1 set | Connecting parts together          |     |

<!-- ## Requirement -->

## Usage

### Hardware Development

-  Wire it according to [Arduino_Uno_LED_8x8_led_matrix_art_breadboard.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_8x8_led_matrix/diagrams/Fritzing/Arduino_Uno_LED_8x8_led_matrix_art_bb.png)

### Software Development

1. Open the Arduino IDE.
2. Install "Adafruit NeoPixel by Adafruit" from the menu Tools > Manage Libraries.
3. Write the Arduino_Uno_LED_8x8_led_matrix_art.ino code to Arduino.

### Test

1. Upload the sketch to the Arduino and connect the power supply.
2. The LED matrix will initialize and display the first pattern.
3. Press the tactile switch to cycle through the display patterns in order.
4. Confirm that all patterns are displayed correctly to complete the test.


<!-- ## Features -->

<!-- ## Directory 

<!-- ## Reference -->


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
