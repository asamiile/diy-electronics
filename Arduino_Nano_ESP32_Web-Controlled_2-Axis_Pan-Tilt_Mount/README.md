# Arduino Nano ESP32 Web-Controlled 2-Axis Pan-Tilt Mount (In production)

## Overview

This project uses an Arduino Nano ESP32 to create a 2-axis pan-tilt platform that can be controlled remotely from a web browser. The Nano ESP32 connects to your Wi-Fi and hosts a web server with a simple interface, allowing you to control the pan and tilt servos in real-time from any device on the same network.

![]()


### Bill of Materials

#### Control System

| Part Type                                     | Unit | Role/Notes                                   |
| --------------------------------------------- | ---- | -------------------------------------------- |
| [Arduino Nano ESP32](https://amzn.to/452q2dH) | 1    | Microcontroller.                             |
| [USB-C Cable](https://amzn.to/4lU4bdZ)        | 1    | For programming and powering the Nano ESP32. |


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


## Usage

### Hardware Development

<!-- -  Wire it according to [Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount/diagrams/Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount_bb.png) -->


#### Wiring List

1. Power Setup
  - Connect the **DC Jack Adapter** to the breadboard's main power `(+)` and ground `(-)` rails.
  - Connect the **1000µF Capacitor** across the `+` and `-` rails (check polarity).
  - Connect both **Servos**' power wires `(Red)` to the + rail.
  - Connect both **Servos**' ground wires (Brown/Black) to the `-` rail.
2. Control Connections
  - Pan Servo Signal wire → Nano ESP32 Pin `GPIO 12`
  - Tilt Servo Signal wire → Nano ESP32 Pin `GPIO 13`
  - Nano ESP32 `GND` pin → Breadboard's Ground `(-)` Rail (This creates a common ground and is essential).


### Software Development

This project's software consists of two parts: the firmware that runs on the ESP32, and the web application that provides the control interface.

#### Firmware (ESP32 Sketch)

1. Environment Setup (One-time)
   - Install ESP32 Board Support:
      1. Go to `Tools > Board > Boards Manager...`.
      2. Search for `Arduino ESP32 Boards` and install the package by **Arduino**.
   - Install Required Library:
      1. In the Library Manager (`Tools > Manage Libraries...`), search for and install "**ESP32Servo**".
2. Credential Configuration 
   1. Locate the `credentials.h.example` file in the project directory.
   2. Open the file and replace `"YOUR_WIFI_SSID_HERE"` and `"YOUR_WIFI_PASSWORD_HERE"` with your actual Wi-Fi details.
   3. Rename the file from `credentials.h.example` to `credentials.h`.
3. Configure and Upload
   - Open the [ESP32-DevKitC_Web-Controlled_2-Axis_Pan-Tilt_Mount](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Nano_ESP32_Web-Controlled_2-Axis_Pan-Tilt_Mount/sketch/sketch_jul16a/sketch_jul16a.ino).
   - Go to `Tools > Board > Arduino ESP32` Boards and select "**Arduino Nano ESP32**".
   - Connect your Nano ESP32 to your computer with a USB-C cable, select the correct COM port, and click the "Upload" button.


#### Web Application (Control UI)

The control interface is a React web app hosted directly on the Nano ESP32. The final build files (HTML/CSS/JS) are uploaded to the ESP32's flash memory, which acts as a local web server. It provides the UI to any browser on the same Wi-Fi network and listens for API commands to move the servos.

The source code can be found here: []()

**Key Features**

- Pan & Tilt Sliders: For real-time control of each servo from 0-180 degrees.
- Center Button: Instantly returns both servos to their 90-degree position.
- Angle Display: Shows the current target angle for each servo.
- API: Sends commands to the ESP32 via simple HTTP GET requests (e.g., `/move?servo=pan&angle=120`).


### Test

1. After the upload is complete, keep the Nano ESP32 connected to your PC.
2. Connect the external 5V power supply to the DC jack. This will power the servos.
3. Open the **Arduino Serial Monitor** and set the baud rate to **115200**.
4. Press the **RESET** button on your Nano ESP32 board to restart it. The board will then connect to your Wi-Fi and print its IP address in the Serial Monitor.
5. On a smartphone or PC connected to the same Wi-Fi network, open a web browser and enter that IP address.
6. Use the controls on the webpage to confirm that the pan-tilt mechanism moves correctly.


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
