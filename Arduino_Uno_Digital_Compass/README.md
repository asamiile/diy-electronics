# Arduino Uno Digital Compass

## Overview

![]()


### Bill of Materials

#### Control System

| Part Type                                  | Unit | Role/Notes                       |
| ------------------------------------------ | ---- | -------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)     | 1    | Micro Controller.                |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1    | For writing programs to Arduino. |


#### Input & Output

| Part Type                                            | Unit | Role/Notes                     |
| ---------------------------------------------------- | ---- | ------------------------------ |
| [BNO055 9DOF Sensor Module](https://amzn.to/3U8l5tN) | 1    | Sensor that detects direction. |


#### Prototyping & Wiring

| Part Type                                               | Unit  | Role/Notes                                        |
| ------------------------------------------------------- | ----- | ------------------------------------------------- |
| [Breadboard](https://amzn.to/40bMzlk)   | 1     | Circuit base. (for prototype) |
| [Jumper Wires](https://amzn.to/45voWYC) | 1 set | Connecting parts together.    |


## Usage

### Hardware Development

-  Wire it according to [Arduino_Uno_Digital_Compass_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_Digital_Compass/diagrams/Arduino_Uno_Digital_Compass_bb.png)


#### Wiring List

<!-- - Common Cathode RGB LED
  - Longest leg of the LED (Common Cathode) → Arduino GND
  - Arduino D11 (PWM) → 220Ω Resistor  → Red (R) leg of LED
  - Arduino D10 (PWM) → 220Ω Resistor  → Blue (B) leg of LED
  - Arduino D9 (PWM) → 220Ω Resistor  → Green (G) leg of LED
- Tactile Switch (Push-button)
  - Arduino D2 → One leg of the Switch
  - Diagonally opposite leg of the Switch → Arduino GND
  - [Note] This circuit does not have an external pull-up resistor. You must use the Arduino's internal pull-up by setting pinMode(2, INPUT_PULLUP); in your sketch. -->

### Software Development

1. Set up the IDE: Open the Arduino IDE. Ensure your board is configured correctly under Tools > Board (select "Arduino Uno").
<!-- 2. Upload the Code: Copy and paste the complete code from the [Arduino_Uno_Digital_Compass.ino](Arduino_Uno_Digital_Compass/sketch/sketch_jul4a/Arduino_Uno_Digital_Compass/Arduino_Uno_Digital_Compass.ino) file into your sketch.
3. Connect & Upload: Connect your Arduino Uno to your PC with the USB cable and click the "Upload" button. -->


### Test

<!-- 1. After uploading the sketch, the RGB LED will be off.
2. Press the tactile switch once. The LED will turn pink.
3. Each subsequent press will cycle through the colors: Orange, Green, Blue, Purple, and then a smooth color-fading animation.
4. The next press will turn the LED off again, completing the cycle.
5. Confirm that all patterns are displayed correctly to complete the test. -->



## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
