# XIAO RP2040 LED Audio Spectrum (In production)

## Overview

- 


### Bill of Materials

#### Control System
| Part Type                                           | Unit | Role/Notes                             |     |
| --------------------------------------------------- | ---- | -------------------------------------- | --- |
| [XIAO RP2040](https://amzn.to/3TrkrHs) | 1    | Micro Controller.                      |     |
| [USB-C cable](https://amzn.to/407P2xg)              | 1    | For programming and powering the XIAO. |     |


#### Input & Output

| Part Type                                            | Unit | Role/Notes          |     |
| ---------------------------------------------------- | ---- | ------------------- | --- |
| [8x32 RGB LED WS2812B](https://amzn.to/4nlV9rJ)      | 1    | Display device      |     |
| [Microphone Module INMP441](https://amzn.to/3FUDMxC) | 1    | Audio Input sensor. |     |


#### Power System

| Part Type                                                  | Unit | Role/Notes                              |     |
| ---------------------------------------------------------- | ---- | --------------------------------------- | --- |
| [External AC adapter (5V10A)](https://amzn.to/4emi9mw)     | 1    | Main power supply for the LEDs.         |     |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)        | 1    | Connects the AC adapter to the circuit. |     |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ) | 1    | To stabilize the power supply.          |     |


#### Prototyping & Wiring

| Part Type                                      | Unit  | Role/Notes                      |     |
| ---------------------------------------------- | ----- | ------------------------------- | --- |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2) | 1     | To protect the LED's data line. |     |
| [Breadboard](https://amzn.to/40bMzlk)          | 1     | Circuit base for prototyping.   |     |
| [Jumper Wires](https://amzn.to/45voWYC)        | 1 set | To connect parts together.      |     |


## Usage


### Hardware Development

<!-- -  Wire it according to [Arduino_Uno_LED_8x8_led_matrix_art_breadboard.png](https://github.com/asamiile/diy-electronics/blob/main/ESP32-DevKitC_8x32_Led_Audio_Spectrum/diagrams/ESP32-DevKitC_8x32_Led_Audio_Spectrum_bb.png) -->


<!-- #### Step 1: Place Components on the Breadboard

First, place the main components onto the breadboard.

1. **ESP32-DevKitC**: Insert the ESP32-DevKitC firmly into the breadboard, ensuring it straddles the center channel.
2. **I2S Microphone Module**: Place the microphone module on the breadboard near the ESP32.
3. **Resistor (300-500Ω)**: Insert the resistor into an empty area on the breadboard.
4. **Electrolytic Capacitor (1000µF)**: Place the capacitor so it straddles the power rails of the breadboard.
    - **[IMPORTANT NOTE]** The **longer lead (positive, +)** must be plugged into the **positive (+)** rail (the column with the red line).
    - The **shorter lead (negative, -)** must be plugged into the **negative (-)** rail (the column with the blue line).

#### Step 2: Wire the External Power

Connect the power from your AC adapter to the breadboard.

1. Connect a **red** jumper wire from the positive `(+)` terminal of the **DC Jack Adapter** to the **positive (+)** rail of the breadboard.
2. Connect a **black** jumper wire from the negative `(-)` terminal of the **DC Jack Adapter** to the **negative (-)** rail of the breadboard.


#### Step 3: Wire the LED Matrix

Next, connect the 8x32 LED matrix.

1. Connect the dedicated `5V` power wire from the LED matrix to the positive **(+)** rail of the breadboard.
2. Connect the dedicated `GND` wire from the LED matrix to the **negative (-)** rail of the breadboard.
3. Connect the `DIN` (Data In) wire from the matrix's 3-pin connector to the same row as one leg of the **resistor**.

#### Step 4: Wire the I2S Microphone

Connect the microphone module to the ESP32.

1. Connect the `VDD` pin of the microphone to the `3V3` pin on the ESP32 (using a red wire).
2. Connect the `GND` pin of the microphone to a `GND` pin on the ESP32 (using a black wire).
3. Connect the `L/R` pin of the microphone to the same `GND` pin on the ESP32 (using a black wire).
4. Connect the `SD` pin of the microphone to `GPIO 34` on the ESP32.
5. Connect the `WS` pin of the microphone to `GPIO 25` on the ESP32.
6. Connect the `SCK` pin of the microphone to `GPIO 26` on the ESP32.

#### Step 5: Final Connections

Finally, connect the remaining components to the ESP32 to complete the circuit.

1. **LED Data Line**: Connect a jumper wire from the *other leg of the resistor* to the `GPIO 13` pin on the ESP32.
2. **Common Ground (Most Important)**: Connect a wire from another `GND` pin on the ESP32 to the **negative (-)** rail of the breadboard.

#### Final Checklist
After you finish wiring, please trace each connection with your finger and verify that all of the following are correct.

- [ ] External Power & Capacitor → Breadboard Power Rails (`+` and `-`, check polarity)
- [ ] LED Power/GND → Breadboard Power Rails (`+` and `-`)
- [ ] I2S Mic Power → ESP32 `3V3`/`GND`
- [ ] ESP32 `GPIO 13` → Resistor → LED `DIN`
- [ ] I2S Mic `SD`/`WS`/`SCK` → ESP32 `GPIO 34`/`25`/`26`
- [ ] ESP32 `GND` → **Breadboard Negative Rail (Common Ground)** -->


### Software Development

<!-- 1. Open the Arduino IDE.
2. Install "Adafruit NeoPixel by Adafruit" from the menu Tools > Manage Libraries.
3. Write the Arduino_Uno_LED_8x8_led_matrix_art.ino code to Arduino. -->

### Test

<!-- 1. Upload the sketch to the Arduino and connect the power supply.
2. The LED matrix will initialize and display the first pattern.
3. Press the tactile switch to cycle through the display patterns in order.
4. Confirm that all patterns are displayed correctly to complete the test. -->



## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
