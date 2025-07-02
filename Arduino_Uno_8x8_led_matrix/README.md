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

<!-- ## Requirement -->

## Usage

### Hardware Development

-  Wire it according to [Arduino_Uno_LED_8x8_led_matrix_art_breadboard.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_8x8_led_matrix/diagrams/Fritzing/Arduino_Uno_LED_8x8_led_matrix_art_bb.png)

[![Image from Gyazo](https://i.gyazo.com/d4c205e1af4648523a3a9dd021e60e1f.png)](https://gyazo.com/d4c205e1af4648523a3a9dd021e60e1f)

#### [Important] Before You Begin Assembly

For safety, please make sure both the Arduino's USB cable and the AC adapter are unplugged from your PC and the wall outlet until all wiring is complete.

#### Step 1: Place Components on the Breadboard

First, place the main components onto the breadboard.

1. **Tactile Switch**: Insert the tactile switch firmly into the breadboard, ensuring it straddles the center channel.
2. **Resistor (330Ω)**: Insert the resistor into an empty area of the breadboard (e.g., across rows 9 and 13 as shown in your Fritzing diagram).
3. **Electrolytic Capacitor (1000µF)**: Place the capacitor so it straddles the power rails of the breadboard.
   - [IMPORTANT NOTE] The longer lead (positive, +) must be plugged into the positive `(+)` rail (the column with the red line).
    - The shorter lead (negative, -) must be plugged into the negative `(-)` rail (the column with the blue line).

#### Step 2: Wire the External Power

Connect the power from your AC adapter to the breadboard.

1. Connect a red jumper wire from the positive `(+)` terminal of the **DC Jack Adapter** to the positive `(+)` rail of the breadboard.
2. Connect a black jumper wire from the negative `(-)` terminal of the **DC Jack Adapter** to the negative `(-)` rail of the breadboard.

#### Step 3: Wire the LED Matrix

Next, connect the LED matrix.

1. Insert the thick red power wire from the LED matrix into an empty hole on the positive `(+)` rail of the breadboard.
2. Insert the thick white/black `GND` wire from the LED matrix into an empty hole on the negative `(-)` rail of the breadboard.
3. Connect the data line (`DIN`) from the matrix's 3-pin connector (the green wire) to the same row as one leg of the resistor.
4. Connect the `GND` line from the 3-pin connector (the white wire) to the negative `(-)` rail of the breadboard.

#### Step 4: Connect to the Arduino

Finally, connect all components to the Arduino Uno.

1. LED Data Line: Connect a jumper wire (e.g., green) from the other leg of the resistor to the Arduino `D6` pin.
2. Tactile Switch:
Connect a jumper wire (e.g., yellow) from one leg of the switch to the Arduino `D2` pin.
    - Connect a black jumper wire from the diagonally opposite leg of the switch to an Arduino GND pin (e.g., the one next to D13).
3. Common Ground (Most Important):
    - Connect a black jumper wire from another Arduino GND pin (e.g., one in the POWER header) to the negative `(-)` rail of the breadboard.

#### Final Checklist

After you finish wiring, please trace each connection with your finger and verify that all of the following are correct.

- [ ] External Power → Breadboard Power Rails (`+` and `-`)
- [ ] Capacitor → Straddling the power rails (Check polarity!)
- [ ] LED Power Wires → Breadboard Power Rails (`+` and `-`)
- [ ] Arduino `D6` → Resistor → LED `DIN`
- [ ] Arduino `D2` → Switch Leg 1
- [ ] Switch Leg 2 → Arduino `GND`
- [ ] Another Arduino `GND` → **Breadboard Negative Rail (Common Ground)**


### Software Development

1. Open the Arduino IDE.
2. Install "Adafruit NeoPixel by Adafruit" from the menu Tools > Manage Libraries.
3. Write the [Arduino_Uno_8x8_led_matrix.ino](Arduino_Uno_8x8_led_matrix/sketch/Arduino_Uno_8x8_led_matrix/Arduino_Uno_8x8_led_matrix.ino) code to Arduino.

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
