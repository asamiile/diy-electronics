# Arduino Uno Digital Compass

## Overview

This project creates a simple digital compass using an Arduino Uno and a BNO055 9-axis orientation sensor. The BNO055 is a powerful sensor that combines an accelerometer, gyroscope, and magnetometer with an internal processor to provide tilt-compensated, absolute orientation. This allows it to output a stable and accurate heading (0-360 degrees), which is displayed on the computer's Serial Monitor.

![]()


### Bill of Materials

#### Control System

| Part Type                                  | Unit | Role/Notes                       |
| ------------------------------------------ | ---- | -------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)     | 1    | Micro Controller.                |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1    | For writing programs to Arduino. |


#### Input & Output

| Part Type                                            | Unit | Role/Notes                     |
| ---------------------------------------------------- | ---- | ------------------------------ |
| [BNO055 9DOF Sensor Module](https://amzn.to/3H3PAOx) | 1    | Sensor that detects direction. |


#### Prototyping & Wiring

| Part Type                                               | Unit  | Role/Notes                                        |
| ------------------------------------------------------- | ----- | ------------------------------------------------- |
| [Breadboard](https://amzn.to/40bMzlk)   | 1     | Circuit base. (for prototype) |
| [Jumper Wires](https://amzn.to/45voWYC) | 1 set | Connecting parts together.    |


## Usage

### Hardware Development

-  Wire it according to [Arduino_Uno_Digital_Compass_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_Digital_Compass/diagrams/Arduino_Uno_Digital_Compass_bb.png)


#### Wiring List

- **BNO055 Sensor to Arduino Uno**
  - VIN → 5V
  - GND → GND
  - SCL → A5
  - SDA → A4


### Software Development

1. Install Libraries: Before uploading, you need to install the required libraries.
   - In the Arduino IDE, go to `Tools` > `Manage Libraries...`.
   - Search for and install "Adafruit BNO055".
   - Search for and install "Adafruit Unified Sensor".
2. **Set up the IDE**: Open the Arduino IDE. Ensure your board is configured correctly under `Tools` > `Board` (select "Arduino Uno").
3. **Upload the Code**: Copy and paste the complete code from [Arduino_Uno_Digital_Compass.ino](Arduino_Uno_Digital_Compass/sketch/sketch_jul4a/Arduino_Uno_Digital_Compass/Arduino_Uno_Digital_Compass.ino)  file into the sketch editor.
4. **Connect & Upload**: Connect your Arduino Uno to your PC with the USB cable and click the "Upload" button.


### Test

1. After uploading the sketch, open the **Serial Monitor** by clicking the magnifying glass icon in the top-right corner of the Arduino IDE.
2. In the Serial Monitor window, set the baud rate to **9600**.
3. The current heading (azimuth) from the sensor will be printed in degrees.
4. Physically rotate the breadboard and sensor. Confirm that the heading value changes accordingly (e.g., pointing North should be close to 0 or 360 degrees).


## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
