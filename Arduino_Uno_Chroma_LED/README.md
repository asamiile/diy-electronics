# Arduino Uno Chroma LED

## Overview

This project is a simple, interactive desk light created with an Arduino Uno and a single 5mm common cathode RGB LED. By pressing the tactile switch, you can cycle through the display modes in the following order:

- Pink
- Yellow
- Green
- Blue
- Purple
- Smooth color fade animation

![](https://mir-cdn.behance.net/v1/rendition/project_modules/max_3840_webp/6226e6229627251.6867e0d1bb8c7.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/ba3420229627251.6867e0d1bacc1.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/5d5c6a229627251.6867e0d1bb195.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/938d8b229627251.6867e0d1bc328.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/e95a45229627251.6867e0d1bc881.jpg)

*5 Color Changes* 

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/HZucglmYSCs/hqdefault.jpg)](https://youtu.be/HZucglmYSCs?si=rXBTJWtdmKFi_rcF)

*Smooth color fade animation*

[![YouTube Video Thumbnail](https://i.ytimg.com/vi/dp0oIES4NKo/hqdefault.jpg)](https://youtu.be/dp0oIES4NKo?si=npvw56pW3KhWuZMV)


This project is an excellent introduction to controlling RGB LEDs with PWM signals and handling button inputs on the Arduino. It's a perfect weekend project that results in a beautiful, minimalist mood lamp.


### Bill of Materials

#### Control System

| Part Type                                  | Unit | Role/Notes                       |
| ------------------------------------------ | ---- | -------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)     | 1    | Micro Controller.                |
| [USB cable (A-B)](https://amzn.to/407P2xg) | 1    | For writing programs to Arduino. |


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

-  Wire it according to [Arduino_Uno_Chroma_LED_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_Chroma_LED/diagrams/Arduino_Uno_Chroma_LED_bb.png)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/4fc92f229627251.6867e0d0b3b1b.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/fbf47c229627251.6867e0d0b35f8.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/eb167d229627251.6867e0d0b3081.jpg)


#### Wiring List

Please verify that each connection is wired as follows:

- Common Cathode RGB LED
  - Longest leg of the LED (Common Cathode) → Arduino GND
  - Arduino D11 (PWM) → Resistor → Red (R) leg of LED
  - Arduino D10 (PWM) → Resistor → Blue (B) leg of LED
  - Arduino D9 (PWM) → Resistor → Green (G) leg of LED
- Tactile Switch (Push-button)
  - Arduino D2 → One leg of the Switch
  - Diagonally opposite leg of the Switch → Arduino GND
  - [Note] This circuit does not have an external pull-up resistor. You must use the Arduino's internal pull-up by setting pinMode(2, INPUT_PULLUP); in your sketch.

### Software Development

1. Set up the IDE: Open the Arduino IDE. Ensure your board is configured correctly under Tools > Board (select "Arduino Uno").
2. Upload the Code: Copy and paste the complete code from the [Arduino_Uno_Chroma_LED.ino](Arduino_Uno_Chroma_LED/sketch/sketch_jul4a/Arduino_Uno_Chroma_LED/Arduino_Uno_Chroma_LED.ino) file into your sketch.
3. Connect & Upload: Connect your Arduino Uno to your PC with the USB cable and click the "Upload" button.


### Test

1. After uploading the sketch, the RGB LED will be off.
2. Press the tactile switch once. The LED will turn pink.
3. Each subsequent press will cycle through the colors: Orange, Green, Blue, Purple, and then a smooth color-fading animation.
4. The next press will turn the LED off again, completing the cycle.
5. Confirm that all patterns are displayed correctly to complete the test.


<!-- ## Final Assembly

This project can be moved from a breadboard prototype to a more permanent and polished product by soldering the components onto a universal prototyping board and designing a custom 3D-printed enclosure.


### 1. Soldering to a Prototyping Board

Once the circuit is confirmed to work on the breadboard, the next step is to create a permanent version by soldering. This makes the project durable and compact.

To create a compact and final product, the larger Arduino Uno used for prototyping is replaced with the much smaller Seeed Studio XIAO microcontroller. This allows the entire circuit to fit on a very small piece of prototyping board, making it ideal for a minimal desk lamp.

Below are the parts needed for this final, miniaturized version.

### Bill of Materials (for Final Assembly)

| Part Type                                               | Unit  | Role/Notes                                        |
| ------------------------------------------------------- | ----- | ------------------------------------------------- |
| [Seeed Studio XIAO RP2040](https://amzn.to/3TrkrHs)     | 1     | Micro Controller.                                    |
| [5mm Common Cathode RGB LED](https://amzn.to/4lmJuaE)   | 1     | Light source component.                           |
| [Tactile Switch (Push Button)](https://amzn.to/3T0gNUF) | 1     | Used for ON/OFF control and for switching colors. |
| [Resistor (220Ω)](https://amzn.to/4kMejW2)              | 3     | For protecting the LED's data line.               |
| [PCB](https://amzn.to/402bcRD)                          | 1     | Permanent circuit base for soldering.             |
| [Solid-core wire](https://amzn.to/44JYMR3)              | 1 set | For creating permanent connections on the PCB.    |
| [USB-C cable](https://amzn.to/407P2xg)                  | 1     | For programming and powering the XIAO.            |


### 2. 3D-Printed Enclosure
A custom case can be designed to house the circuit board, LED, and switch, turning it into a beautiful desk object.
- Material: Using a white or translucent filament is recommended, as it diffuses the light from the RGB LED, creating a soft, glowing effect.
- Design: The enclosure can be designed with an integrated holder to keep the LED perfectly straight. A small opening will be needed for the USB cable to connect to the microcontroller.
- Assembly: The final step is to place the soldered circuit board inside the 3D-printed case to complete your custom lamp. -->


## Author

[Asami.K](https://asami.tokyo/)

[Arduino Uno Chroma LED - Behance](https://www.behance.net/gallery/229627251/Arduino-Uno-Chroma-LED)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
