# Seeed Studio XIAO RP2040 8x8 LED Matrix

## Overview

- This project takes the [Arduino_Uno_8x8_LED_Matrix](https://github.com/asamiile/diy-electronics/tree/main/Arduino_Uno_8x8_led_matrix) prototype and refines it into a compact, permanent product built around the powerful Seeed Studio XIAO RP2040. It features several animation patterns that can be cycled with a push button.

![]()


### LED Matrix glowing pattern

- Rainbow
- Ripple
- BouncingBall
- OceanWave
- Breathing

### Bill of Materials

#### Control System

| Part Type                                           | Unit | Role/Notes                             |
| --------------------------------------------------- | ---- | -------------------------------------- |
| [Seeed Studio XIAO RP2040](https://amzn.to/3TrkrHs) | 1    | Micro Controller.                      |
| [USB-C cable](https://amzn.to/407P2xg)              | 1    | For programming and powering the XIAO. |


#### Input & Output

| Part Type                                      | Unit | Role/Notes     |
| ---------------------------------------------- | ---- | -------------- |
| [8x8 RGB LED WS2812B](https://amzn.to/44cSo3p) | 1    | display device |
| [Tactile Switch](https://amzn.to/4nHuvd1)      | 1    | Input button   |


#### Power System

| Part Type                                                                                         | Unit | Role/Notes                     |
| ------------------------------------------------------------------------------------------------- | ---- | ------------------------------ |
| [Power Supply (5V, 2A+)](https://amzn.to/4jZEIyu) or [Mobile Power Bank](https://amzn.to/449XEpG) | 1    | Power supply for LEDs.         |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)                                               |      |                                |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ)                                        | 1    | To stabilize the power supply. |

#### Electronics & Wiring

| Part Type                                         | Unit  | Role/Notes                                   |
| ------------------------------------------------- | ----- | -------------------------------------------- |
| [Logic Level Shifter](https://amzn.to/4eeDyhr)    | 1     | To convert the data signal voltage.          |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2)    | 1     | To protect the LED's data line.              |
| [JST SM 3-Pin Connector](https://amzn.to/3GCiy7N) | 1 set | To easily connect/disconnect the LED matrix. |
1     | Connect the AC adapter to the breadboard     |
| [Prototyping PCB](https://amzn.to/4lpHRJu)                                                        | 1     | Circuit base for soldering.                  |
| [Hook-up Wire](https://amzn.to/45XlDK0)                                                           | 1 set | To connect the components.                   |



## Usage

### Hardware Development

-  Wire it according to [Seeed_Studio_XIAO_RP2040_8x8_LED_Matrix_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Seeed_Studio_XIAO_RP2040_8x8_LED_Matrix/diagrams/Seeed_Studio_XIAO_RP2040_8x8_LED_Matrix_bb.png)


#### Wiring List

Before you apply power, carefully trace each connection with your finger and confirm that all of the following are correct.

- **Main Power Input**
  - External 5V Power Supply `(+)` → DC Jack `(+)`
  - External 5V Power Supply `(-)` → DC Jack `(-)`
  - Output from DC Jack `(+)` → 5V Power Rail on the PCB
  - Output from DC Jack `(-)` → GND Rail on the PCB
- **Powering the Components**
  - Capacitor `(+)` → 5V Power Rail
  - Capacitor `(-)` → GND Rail
  - XIAO RP2040 `5V` pin → 5V Power Rail
  - XIAO RP2040 `GND` pin → GND Rail
  - Logic Level Shifter `HV` pin → 5V Power Rail
  - Logic Level Shifter `GND` pin → GND Rail
  - JST Connector (for LED) `5V` pin → 5V Power Rail
  - JST Connector (for LED) `GND` pin → GND Rail
- **Signal Connections**
  - Logic Level Shifter `LV` pin → XIAO RP2040 `3V3` pin
  - XIAO RP2040 pin `D6` → Logic Level Shifter's input `LVx`
  - Logic Level Shifter's output `HVx` → Resistor (300-500Ω) → JST Connector's data pin
  - XIAO RP2040 pin `D2` → One leg of the Switch
  - Other leg of the Switch → **GND Rail**
  - (Note: The code already sets `pinMode(BUTTON_PIN, INPUT_PULLUP);` correctly.)


### Software Development

#### 1. Set Up Arduino IDE for RP2040

First, you need to teach the Arduino IDE how to talk to your XIAO RP2040.

1. Open Arduino IDE and go to `File` > `Preferences`.
2.  In the "Additional Board Manager URLs" field, paste the following URL:
  ```
  https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
  ```
3. Go to `Tools` > `Board` > `Boards Manager...`, search for "rp2040", and install the "Raspberry Pi Pico/RP2040" package.

#### 2. Install Required Library

1. In the IDE menu, go to `Tools` > `Manage Libraries....`
2. Search for "**Adafruit NeoPixel**" and install the library by Adafruit.

#### 3. Upload the Sketch
1. Go to `Tools` > `Board` and select "**Seeed Studio XIAO RP2040**" from the list.
2. Connect your XIAO RP2040 to your computer with a USB-C cable.
3. Open the project sketch (`.ino` file).
4. Verify that the pin numbers defined at the top of the code (`LED_PIN`, `BUTTON_PIN`) match your physical wiring.
5. Click the "Upload" button.

### Test
1. Connect the 5V power supply to the DC jack.
2. The LED matrix will light up and display the first animation pattern.
3. Press the tactile switch to cycle through the different patterns.
4. Confirm that all patterns display correctly.

### 3D-Printed Enclosure
<!-- Create a custom case with a 3D printer to protect the electronics and give your project a polished look.

Using CAD software (like Tinkercad), design an enclosure based on the exact measurements of your finished PCB. The design must include:
* **Cutouts** for the 8x8 LED matrix, USB port, DC power jack, and switch.
* **Mounting posts** to secure the PCB in place.

It's recommended to print a small test piece to check the fit of the ports before starting the final print. Once printed, secure the board inside the enclosure with screws to complete the project. -->


## Author

[Asami.K](https://asami.tokyo/)

[Arduino Uno 8x8 LED Matrix - Behance](https://www.behance.net/gallery/229464473/Arduino-Uno-8x8-LED-Matrix)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
