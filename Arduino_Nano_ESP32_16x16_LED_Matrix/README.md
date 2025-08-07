# Arduino Nano ESP32 16x16 LED Matrix (In production)

## Overview

This project is an [Arduino_Uno_8x8_LED_Matrix](https://github.com/asamiile/diy-electronics/tree/main/Arduino_Uno_8x8_LED_Matrix) created with Arduino Nano ESP32. The LEDs used are 16x16.

You can see the LED animation pattern in the [Arduino Uno 8x8 LED Matrix - Behance](https://www.behance.net/gallery/229464473/Arduino-Uno-8x8-LED-Matrix).


### Bill of Materials

#### Control System

| Part Type                                     | Unit | Role/Notes                                   |     |
| --------------------------------------------- | ---- | -------------------------------------------- | --- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1    | Microcontroller.                             |     |
| [USB-C cable](https://amzn.to/407P2xg)        | 1    | For programming and powering the Nano ESP32. |     |


#### Input & Output

| Part Type                                                                                          | Unit | Role/Notes      |
| -------------------------------------------------------------------------------------------------- | ---- | --------------- |
| [WS2812B LED RGB 16x16](https://amzn.to/4ebZCcm) or [WS2812B LED RGB 8x8](https://amzn.to/44cSo3p) | 1    | Display device. |
| [Tact Switch](https://amzn.to/4l5lGrQ)                                                             | 1    | Input button.   |


#### Power System

| Part Type                                                      | Unit | Role/Notes                              |
| -------------------------------------------------------------- | ---- | --------------------------------------- |
| [External AC adapter 5V 4A or Higher](https://amzn.to/4neewTI) | 1    | Power supply for LEDs.                  |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)            | 1    | Connects the AC adapter to the circuit. |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ)     | 1    | To stabilize the power supply.          |


#### Electronics & Wiring

| Part Type                                      | Unit  | Role/Notes                                 |
| ---------------------------------------------- | ----- | ------------------------------------------ |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2) | 1     | For protecting the LED matrix's data line. |
| [Breadboard](https://amzn.to/40bMzlk)          | 1     | Circuit base for prototyping.              |
| [Jumper Wires](https://amzn.to/45voWYC)        | 1 set | To connect parts together.                 |


## Usage

### Hardware Development

<!-- -  Wire it according to [Seeed_Studio_XIAO_RP2040_16x16_LED_Matrix_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Seeed_Studio_XIAO_RP2040_16x16_LED_Matrix/diagrams/Seeed_Studio_XIAO_RP2040_16x16_LED_Matrix_bb.png) -->


#### Wiring List

- **Power Rails**
  - DC Jack (+) → Breadboard Positive **(+)** Rail
  - DC Jack (-) → Breadboard Negative **(-)** Rail
- **Power Stabilization**
  - 1000µF Capacitor is placed across the **+** and **-** power rails (Check for correct polarity: longer lead to +).
- **LED Matrix Power**
  - LED Matrix 5V wire → Breadboard **(+)** Rail
  - ED Matrix GND wire → Breadboard **(-)** Rail
- **Data Line**
  - Arduino Nano ESP32 **D6** → 330Ω Resistor → LED Matrix **DIN**
- **Input Switch**
  - Arduino Nano ESP32 **D2** → One leg of the Tactile Switch
  - Opposite leg of the Switch → An Arduino Nano ESP32 **GND** pin
- **Common Ground**
  - An Arduino Nano ESP32 **GND** pin → Breadboard Negative **(-)** Rail (This is essential for the circuit to work).


### Software Development

1. **Set up the IDE:**
   - Open the Arduino IDE.
   - Go to `Tools` > `Board` > `Boards Manager...`.
   - Search for "**Arduino ESP32 Boards**" and install the package by Arduino.
2. **Install Library:**
  - Install "**Adafruit NeoPixel by Adafruit**" from the `Tools` > `Manage Libraries...` menu.
3. **Modify the Sketch:**
    - Open the project [Arduino_Nano_ESP32_16x16_LED_Matrix.ino](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Nano_ESP32_16x16_LED_Matrix/sketch/Arduino_Nano_ESP32_16x16_LED_Matrix/Arduino_Nano_ESP32_16x16_LED_Matrix.ino) file.
4. **Connect & Upload:**
    - Connect the Arduino Nano ESP32 to your computer using a USB-C cable.
    - Select the correct COM port from the `Tools` menu and click the "Upload" button. (You may need to hold the BOOT button during upload).


### Test

1. Double-check all wiring to ensure it matches the diagram
2. Connect the external **5V power supply** to the DC jack.
3. The LED matrix will now initialize and display the first animation pattern.
4. Press the tactile switch to cycle through the display patterns.


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
