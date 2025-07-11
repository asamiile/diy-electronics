# Arduino Uno Interactive Servo Light

## Overview

This project lets you control the angle of a servo motor using a potentiometer knob. The RGB LED provides visual feedback by changing its color to correspond with the servo's position.

Turn the knob to sweep the servo arm through its range of motion, and watch the LED smoothly shift its color in response. Built on the Arduino Uno platform, this project is a fantastic introduction to using analog inputs and controlling servos. 


![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/6f8129230140209.68712daf1acd3.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/47518d230140209.68712daf1e3a0.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/81a14e230140209.68712daf1c780.jpg)


### At 0°, the color is pink.

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/cbb114230140209.687134623844c.jpg)


### At 90°, it's an intermediate purple.

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/3c0d8e230140209.687134623897d.jpg)


### At 180°, the color is light blue.

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_1200/14e02c230140209.6871346237c0b.jpg)


### Bill of Materials

| Part Type                                             | Unit  | Role/Notes                                                                 |
| ----------------------------------------------------- | ----- | -------------------------------------------------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)                | 1     | Microcomputer.                                                             |
| [Servo Motor (SG90)](https://amzn.to/3TUevqn)         | 1     | The main actuator that controls the angle. This is the part you purchased. |
| [Potentiometer (10kΩ)](https://amzn.to/4eCRh1R)       | 1     | Used as a knob to set the servo's angle.                                   |
| [5mm Common Cathode RGB LED](https://amzn.to/4lmJuaE) | 1     | Light source component.                                                    |
| [Resistor (220Ω)](https://amzn.to/4kMejW2)            | 3     | For protecting the LED's data line.                                        |
| [Breadboard](https://amzn.to/40bMzlk)                 | 1     | Circuit base. (for prototype)                                              |
| [Jumper Wires](https://amzn.to/45voWYC)               | 1 set | Connecting parts together.                                                 |
| [USB cable (A-B)](https://amzn.to/407P2xg)            | 1     | For writing programs to Arduino.                                           |

## Usage

### Hardware Development

-  Wire it according to [Arduino_Uno_Interactive_Servo_Light_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_Interactive_Servo_Light/diagrams/Arduino_Uno_Interactive_Servo_Light_bb.png)


#### Wiring List

- **Power Setup**
  - Arduino `5V` pin → Breadboard's Positive `(+)` Rail
  - Arduino `GND` pin → Breadboard's Negative `(-)` Rail
- **Servo Motor**
  - Signal wire (Orange/Yellow) → Arduino Pin `9`
  - Power wire (Red) → Breadboard's Positive `(+)` Rail
  - Ground wire (Brown/Black) → Breadboard's Negative `(-)` Rail
- **Potentiometer**
  - Center pin → Arduino Pin `A0`
  - One outer pin → Breadboard's Positive `(+)` Rail
  - Other outer pin → Breadboard's Negative `(-)` Rail
- **RGB LED (Common Cathode)**
  - Longest leg (Cathode) → Breadboard's Negative `(-)` Rail
  - Red leg → Resistor → Arduino Pin `11`
  - Green leg → Resistor → Arduino Pin `10`
  - Blue leg → Resistor → Arduino Pin `5`


### Software Development
1. Open the Arduino IDE.
2. The `<Servo.h>` library required for this project comes pre-installed.
3. Open the project sketch file and upload it to your Arduino Uno.


### Test

1. Connect the Arduino to your computer via USB to power the circuit.
2. Turn the potentiometer knob.
3. Confirm that the servo motor rotates smoothly and that the RGB LED changes color as you turn the knob.


## Author

[Asami.K](https://asami.tokyo/)

[Arduino Uno Chroma LED - Behance](https://www.behance.net/gallery/229627251/Arduino-Uno-Chroma-LED)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
