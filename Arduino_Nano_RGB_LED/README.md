# Arduino Nano RGB LED

## Overview

This project is an [Arduino Uno RGB LED](https://github.com/asamiile/diy-electronics/tree/main/Arduino_Uno_RGB_LED) repurposed for an Arduino Nano ESP32.

You can see the LED light in the [Arduino Uno Chroma LED - Behance](https://www.behance.net/gallery/229627251/Arduino-Uno-Chroma-LED).


### Bill of Materials

#### Control System

| Part Type                                     | Unit | Role/Notes                                   |
| --------------------------------------------- | ---- | -------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1    | Microcontroller.                             |
| [USB-C Cable](https://amzn.to/4lU4bdZ)        | 1    | For programming and powering the Nano ESP32. |


#### Input & Output

| Part Type                                               | Unit | Role/Notes                                        |
| ------------------------------------------------------- | ---- | ------------------------------------------------- |
| [5mm Common Cathode RGB LED](https://amzn.to/4lmJuaE)   | 1    | Light source component.                           |
| [Tactile Switch (Push Button)](https://amzn.to/3T0gNUF) | 1    | Used for ON/OFF control and for switching colors. |


#### Prototyping & Wiring

| Part Type                                               | Unit  | Role/Notes                                        |
| ------------------------------------------------------- | ----- | ------------------------------------------------- |

| [Resistor (220Ω)](https://amzn.to/4kMejW2) | 3     | For protecting the LED's data line. |
| [Breadboard](https://amzn.to/40bMzlk)      | 1     | Circuit base. (for prototype)       |
| [Jumper Wires](https://amzn.to/45voWYC)    | 1 set | Connecting parts together.          |


## Usage

### Hardware Development

![](https://lightroom.adobe.com/v2c/catalogs/ed2e01a539b04942967b87bf621ffa54/assets/b8db24c849a64bb18d8dd6fd5660a455/revisions/c071297ff20249fc9b3ba093a697bede/renditions/5b248209ceab8b479a5bee75af28089c)

![](https://lightroom.adobe.com/v2c/catalogs/ed2e01a539b04942967b87bf621ffa54/assets/bca19d1e416744b98cee6658e6d6800a/revisions/548504f3b69b0c2330a2fb2fab47af73/renditions/e4896d7690edf4af243964254276df1e)

![](https://lightroom.adobe.com/v2c/catalogs/ed2e01a539b04942967b87bf621ffa54/assets/bb6fd70ff4054056b0f6f719df701b3e/revisions/8801239ee9d04482a4760a18e419a3b3/renditions/b28d76ebb304b27770fa8d02a13d0b9d)

![](https://lightroom.adobe.com/v2c/catalogs/ed2e01a539b04942967b87bf621ffa54/assets/e9131d3305154917a7ae84aa82cad378/revisions/4c1754ba6b8542449073e73987967987/renditions/3f735415ab7ce87328a2d3573b487371)


#### Wiring List

Please verify that each connection is wired as follows:

- **Common Cathode RGB LED**
  - Longest leg of the LED (Common Cathode) → Arduino **GND**
  - Red (R) leg of LED → 220Ω Resistor → Arduino **D2**
  - Green (G) leg of LED → 220Ω Resistor → Arduino **D3**
  - Blue (B) leg of LED → 220Ω Resistor → Arduino **D4**
- **Tactile Switch (Push-button)**
  - One leg of the Switch → Arduino **D5**
  - Diagonally opposite leg of the Switch → Arduino **GND**


### Software Development

This project uses the Arduino IoT Cloud.

1. **Set up the Cloud Thing**
   - Go to [Arduino IoT Cloud](https://cloud.arduino.cc/) and log in.
   - Go to the **Things** section and create a new Thing.
   - Select your Arduino Nano ESP32.
     - If you haven't registered your device yet, follow the steps in [this article](https://docs.arduino.cc/tutorials/nano-esp32/cloud-setup/).
     - Enter your 2.4GHz Wi-Fi credentials (SSID and Password). 
      Note: This project was tested using a 2.4GHz smartphone hotspot.
   - Add a new Cloud Variable with the following settings:
     - Name: `colorMode`
     - Type: `Integer Number`
     - Permission: `Read & Write`
    [![Image from Gyazo](https://i.gyazo.com/1ab5feb8a2e3802c23280b4c67604f26.png)](https://gyazo.com/1ab5feb8a2e3802c23280b4c67604f26)
2. **Upload the Code**
   - Go to the **Sketch** tab of your Thing.
   - A template sketch will be automatically generated. Delete the contents and replace it with the complete code from [Arduino_Nano_RGB_LED.ino](https://github.com/asamiile/diy-electronics/tree/main/Arduino_Nano_RGB_LED/sketch/Arduino_Nano_RGB_LED/Arduino_Nano_RGB_LED.ino) file.
    [![Image from Gyazo](https://i.gyazo.com/5e2e5a0bee07afac0b680496551c4410.png)](https://gyazo.com/5e2e5a0bee07afac0b680496551c4410)
   - Click the **Upload** button to flash the sketch to your board. If the update fails, enter **bootloader mode** and try uploading again using the following steps:
     - Press the reset button twice (the board's LED will flash multiple colors).
     - Press the reset button once (the board's LED will flash green).


### Test

1. **Set up the Dashboard** 
   - Go to the **Dashboards** section in Arduino Cloud.
   - Create a new dashboard.
   - Enter **Edit mode**.
   - Click **Add** and select the **Stepper** widget. In the widget's settings, link it to the `colorMode` variable. Set the Min Value to `0` and the Max Value to `6`.
   - (Optional) Add a **Value** widget and link it to the same `colorMode` variable to display the current mode number.
   - Exit Edit mode.
    [![Image from Gyazo](https://i.gyazo.com/94192f1e5d906190a007f4fb6ecdc9c7.png)](https://gyazo.com/94192f1e5d906190a007f4fb6ecdc9c7)
2. **Verify Operation** 
   - After the board is powered on and its status is **Online**, the LED should be off (Mode 0).
   - **Dashboard Control**: Click the "**+**" button on the Stepper widget. The physical LED should turn pink (Mode 1). Each subsequent click will cycle through the colors.
   - **Physical Control**: Press the tactile switch on your breadboard. The LED should cycle to the next color mode.
   - **Synchronization**: Confirm that when you press the physical button, the **Value/Stepper widget on the dashboard updates in real-time**, and vice-versa. This completes the test.


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
