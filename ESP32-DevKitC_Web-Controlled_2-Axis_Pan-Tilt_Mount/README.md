# ESP32-DevKitC Web-Controlled 2-Axis Pan-Tilt Mount

## Overview




![]()


### Bill of Materials

#### Control System

| Part Type                                  | Unit | Role/Notes                              |
| ------------------------------------------ | ---- | --------------------------------------- |
| [ESP32-DevKitC](https://amzn.to/4jV1hnT)   | 1    | Microcontroller.                        |
| [Micro-USB Cable](https://amzn.to/44ZoEZa) | 1    | For programming and powering the ESP32. |


#### Mechanics & Actuators

| Part Type                                               | Unit | Role/Notes                                            |
| ------------------------------------------------------- | ---- | ----------------------------------------------------- |
| [Servo Motor (SG90)](https://amzn.to/3TUevqn)           | 2    | One for pan (horizontal) and one for tilt (vertical). |
| [2-Axis Pan-Tilt Bracket Kit)](https://amzn.to/44J3H3s) | 1    | The mechanical frame for mounting the two servos.     |


#### Power System

| Part Type                                                  | Unit | Role/Notes                                        |
| ---------------------------------------------------------- | ---- | ------------------------------------------------- |
| [AC Adapter (5V 4A)](https://amzn.to/4lOymDh)              | 1    | A dedicated external power supply for the servos. |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)        | 1    | Socket to connect the AC adapter to the circuit.  |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ) | 1    | To stabilize the servo power supply.              |


#### Prototyping & Wiring

| Part Type                                        | Unit  | Role/Notes                                          |
| ------------------------------------------------ | ----- | --------------------------------------------------- |
| [Breadboard](https://amzn.to/40bMzlk)            | 1     | Circuit base for prototyping.                       |
| [Jumper Wires](https://amzn.to/45voWYC)          | 1 set | For connecting signal lines.                        |
| [Silicone Wire (18AWG)](https://amzn.to/4lMv2sr) | 1     | Thick wire for high-current servo power (5V & GND). |


## Usage

### Hardware Development

<!-- -  Wire it according to [Arduino_Uno_Interactive_Servo_Light_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_Interactive_Servo_Light/diagrams/Arduino_Uno_Interactive_Servo_Light_bb.png) -->


#### Wiring List

<!-- - **Power Setup**
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
  - Blue leg → Resistor → Arduino Pin `5` -->


### Software Development

<!-- 1. Open the Arduino IDE.
2. The `<Servo.h>` library required for this project comes pre-installed.
3. Open the project sketch file and upload it to your Arduino Uno. -->


### Test

<!-- 1. Connect the Arduino to your computer via USB to power the circuit.
2. Turn the potentiometer knob.
3. Confirm that the servo motor rotates smoothly and that the RGB LED changes color as you turn the knob. -->


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
