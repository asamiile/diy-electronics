# Arduino Nano 33 BLE Sense (In production)

## Overview

This project creates a simple digital compass using the built-in 9-axis IMU (Inertial Measurement Unit) of an Arduino Nano 33 BLE Sense. The onboard sensor combines an accelerometer, gyroscope, and magnetometer, allowing the board to calculate a stable heading (0-360 degrees). The result is displayed on the computer's Serial Monitor.

![]()


### Bill of Materials

#### Control System

| Part Type                                            | Unit | Role/Notes                                                                 |
| ---------------------------------------------------- | ---- | -------------------------------------------------------------------------- |
| [Arduino Nano 33 BLE Sense](https://amzn.to/3J0t7Te) | 1    | The microcontroller and 9-axis sensor are integrated on this single board. |
| [Micro USB Cable](https://amzn.to/4nmvlf5)           | 1    | For programming the board and supplying power from a PC.                   |


## Usage

### Hardware Development

#### Wiring List

No external wiring is required for the compass functionality, as the sensor is built directly into the Arduino board.


### Software Development

1. **Install Board Package**: 
   - In the Arduino IDE, go to `Tools` > `Board` > `Boards Manager...`.
   - Search for `Arduino Mbed OS Nano Boards` and install the package by Arduino.
2. **Install Library**:
   - Go to `Tools` > `Manage Libraries...`.
   - Search for `Arduino_LSM9DS1` and install the library by Arduino.
3. **Set up the IDE**:
   - Connect your board to your computer.
   - Go to `Tools` > `Board` and select "Arduino Nano 33 BLE Sense".
   - Go to `Tools` > `Port` and select the correct serial port.
4. Upload the Code:
- Copy the code from [Arduino_Nano_33_BLE_Sense_Digital_Compass.ino](Arduino_Nano_33_BLE_Sense_Digital_Compass/sketch/sketch_jul4a/Arduino_Nano_33_BLE_Sense_Digital_Compass/Arduino_Nano_33_BLE_Sense_Digital_Compass.ino) file into the sketch editor and click the "Upload" button.


### Test

1. After uploading the sketch, open the **Serial Monitor** by clicking the magnifying glass icon in the top-right corner of the Arduino IDE.
2. In the Serial Monitor window, set the baud rate to **9600** (or as specified in your sketch).
3. The Serial Monitor will display the heading in degrees.
4. Physically rotate the **Arduino board** and confirm that the heading value changes accordingly.


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
