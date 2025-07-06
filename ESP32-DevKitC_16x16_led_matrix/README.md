# ESP32-DevKitC 16x16 LED Matrix

## Overview

### Bill of Materials

| Part Type                                                  | Unit  | Role/Notes                                                                                   |
| ---------------------------------------------------------- | ----- | -------------------------------------------------------------------------------------------- |
| [ESP32-DevKitC](https://amzn.to/4jV1hnT)                   | 1     | Microcomputer                                                                                |
| [16x16 WS2812B LED Matrix Panel](https://amzn.to/4ebZCcm)  | 1     | display device                                                                               |
| [Tact Switch](https://amzn.to/4l5lGrQ)                     | 1     | Input button                                                                                 |
| [External AC adapter 5V 10A](https://amzn.to/4neewTI)      | 1     | Power supply for LEDs.                                                                       |
| [Logic Level Shifter](https://amzn.to/4eeDyhr)             | 1     | Converts ESP32's 3.3V data signal to the 5V level required by the LEDs for stable operation. |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)        | 1     | Connect the AC adapter to the breadboard                                                     |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2)             | 1     | For protecting the LED's data line                                                           |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ) | 1     | For power supply stabilization                                                               |
| [Breadboard](https://amzn.to/40bMzlk)                      | 1     | Circuit base (for prototype)                                                                 |
| [Jumper Wires](https://amzn.to/45voWYC)                    | 1 set | Connecting parts together                                                                    |


## Usage

### Hardware Development

-  Wire it according to [ESP32-DevKitC_16x16_LED_Matrix_bb.png](https://github.com/asamiile/diy-electronics/blob/main/ESP32-DevKitC_16x16_LED_Matrix/diagrams/ESP32-DevKitC_16x16_LED_Matrix_bb.png)


#### Wiring List

Before you apply power, carefully trace each connection with your finger and confirm that all of the following are correct.

- [ ] Safety First: The AC adapter and the USB cable are both disconnected.
- [ ] Capacitor Polarity: The electrolytic capacitor is straddling the power rails, with its longer lead (+) in the positive (+) rail and its shorter lead (-) in the negative (-) rail.
- [ ] External Power: The DC Jack Adapter is correctly wired to the breadboard's main positive (+) and negative (-) rails.
- [ ] LED Matrix Power: The thick 5V and GND wires from the LED matrix are connected securely to the main positive (+) and negative (-) rails.
- [ ] ESP32 Power: The ESP32's VIN (or 5V) pin is connected to the + rail, and a GND pin is connected to the - rail to establish a common ground.
- [ ] Logic Shifter Power:
  - HV is connected to the + rail (5V).
  - LV is connected to the ESP32's 3V3 pin.
  - Both GND pins on the shifter are connected to the - rail.
- [ ] Data Path:
  - ESP32 GPIO 23 (or your chosen data pin) → Logic Shifter LV1
  - Logic Shifter HV1 → 330Ω Resistor → LED Matrix DIN
- [ ] Switch Path:
  - ESP32 3V3 pin → One leg of the Tactile Switch
  - Opposite leg of the Switch → ESP32 GPIO 22 (or your chosen switch pin)
  - A 10kΩ pull-down resistor connects from GPIO 22's row to the - rail.


### Software Development


### Test


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
