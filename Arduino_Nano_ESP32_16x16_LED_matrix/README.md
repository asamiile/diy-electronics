# Arduino Nano ESP32 16x16 LED Matrix (In production)

## Overview

This project uses an Arduino Nano ESP32 to control a 16x16 (256 pixels) WS2812B LED matrix, displaying various animations that can be cycled with a push button. A dedicated 5V 10A external power supply is used to handle the high current demand of the LEDs. A logic level shifter ensures stable data transmission from the 3.3V Nano ESP32 to the 5V LED matrix.

**Note**: This project can also be built with an 8x8 (64 pixels) LED matrix. If you use an 8x8 matrix, you will need to change the LED_COUNT variable in the code from 256 to 64.


<!-- **Click to watch on YouTube**

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/6-BWVaQY8bo/hqdefault.jpg)](https://youtu.be/6-BWVaQY8bo?si=5ha3Cig4YXMKvDc2) -->


### Bill of Materials

#### Control System

| Part Type                                     | Unit | Role/Notes                             |     |
| --------------------------------------------- | ---- | -------------------------------------- | --- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1    | Microcontroller.                       |     |
| [USB-C cable](https://amzn.to/407P2xg)        | 1    | For programming and powering the Nano. |     |


#### Input & Output

| Part Type                                                                                          | Unit | Role/Notes      |
| -------------------------------------------------------------------------------------------------- | ---- | --------------- |
| [WS2812B LED RGB 16x16](https://amzn.to/4ebZCcm) or [WS2812B LED RGB 8x8](https://amzn.to/44cSo3p) | 1    | Display device. |
| [Tact Switch](https://amzn.to/4l5lGrQ)                                                             | 1    | Input button.   |


#### Power System

| Part Type                                                  | Unit | Role/Notes                              |
| ---------------------------------------------------------- | ---- | --------------------------------------- |
| [External AC adapter 5V 10A](https://amzn.to/4neewTI)      | 1    | Power supply for LEDs.                  |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)        | 1    | Connects the AC adapter to the circuit. |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ) | 1    | To stabilize the power supply.          |


#### Electronics & Wiring

| Part Type                                      | Unit  | Role/Notes                          |
| ---------------------------------------------- | ----- | ----------------------------------- |
| [Logic Level Shifter](https://amzn.to/4eeDyhr) | 1     | To convert the data signal voltage. |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2) | 1     | To protect the LED's data line.     |
| [Breadboard](https://amzn.to/40bMzlk)          | 1     | Circuit base for prototyping.       |
| [Jumper Wires](https://amzn.to/45voWYC)        | 1 set | To connect parts together.          |


## Usage

### Hardware Development

-  Wire it according to [Seeed_Studio_XIAO_RP2040_16x16_LED_Matrix_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Seeed_Studio_XIAO_RP2040_16x16_LED_Matrix/diagrams/Seeed_Studio_XIAO_RP2040_16x16_LED_Matrix_bb.png)


#### Wiring List

- **Main Power Setup**
  - DC Jack Adapter `(+)` → 5V Power Rail `(+)`
  - DC Jack Adapter `(-)` → Ground Rail `(-)`
  - 1000µF Capacitor `(+)` → 5V Power Rail `(+)`
  - 1000µF Capacitor `(-)` → Ground Rail `(-)`
  - LED Matrix Power `(+)` → 5V Power Rail `(+)`
  - LED Matrix Power `(-)` → Ground Rail `(-)`
- **Nano ESP32 & Logic Shifter Power**
  - Nano ESP32 `VUSB` pin → 5V Power Rail `(+)`
  - Nano ESP32 `GND` pin → Ground Rail `(-)`
  - Logic Shifter `HV` pin → 5V Power Rail `(+)`
  - Logic Shifter `LV` pin → Nano ESP32 `3V3` pin
  - Logic Shifter `GND` pins (both) → Ground Rail `(-)`
- **Data Path**
  - Nano ESP32 pin `D6` → Logic Shifter low-voltage input `LVx`
  - Logic Shifter high-voltage output `HVx` → **330Ω Resistor**
  - Other side of Resistor → LED Matrix `DIN` (Data In)
- **Switch Connection**
  - Nano ESP32 pin `D2` → One leg of the Tactile Switch
  - Other leg of Switch → Ground Rail `(-)`
  - (Note: The code must use the **XIAO's** internal pull-up for this pin.)


### Software Development

1. Set Up Arduino IDE for ESP32
   1. Go to `Tools` > `Board` > `Boards Manager...`.
   2. Search for "**Arduino ESP32 Boards**" and install the package by Arduino.
2.  Install Required Library
    1.  In the IDE, go to `Tools` > `Manage Libraries...`.
    2.  Search for "**Adafruit NeoPixel**" and install the library.
3.  Upload the Sketch
    1. Open the project [sketch file](https://github.com/asamiile/diy-electronics/blob/main/SArduino_Nano_ESP32_16x16_LED_matrix/sketch/sketch_jul20a/sketch_jul20a.ino).
    2. Go to `Tools` > `Board` > `Arduino ESP32 Boards` and select "**Arduino Nano ESP32**".
    3. Connect the Arduino Nano ESP32 to your computer using a USB-C cable.
    4. Select the correct COM port from the `Tools` menu and click the "Upload" button.


### Test

1. Double-check all wiring, especially power and ground connections.
2. Plug in the 5V 10A AC adapter to power the LEDs.
3. The LED matrix should light up with the first animation pattern.
4. Press the tactile switch to confirm that the patterns cycle correctly.



## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
