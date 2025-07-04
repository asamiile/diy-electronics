# Arduino Uno Chroma LED

## Overview

- This project is a simple, interactive desk light created with an Arduino Uno and a single 5mm common cathode RGB LED. By pressing the tactile switch, you can cycle through six preset colors (Pink, Orange, Green, Blue, Purple) and a smoothly transitioning color fade animation. This project is an excellent introduction to controlling RGB LEDs with PWM signals and handling button inputs on the Arduino. It's a perfect weekend project that results in a beautiful, minimalist mood lamp.

![](https://mir-cdn.behance.net/v1/rendition/project_modules/max_3840_webp/6226e6229627251.6867e0d1bb8c7.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/938d8b229627251.6867e0d1bc328.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/5d5c6a229627251.6867e0d1bb195.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/ba3420229627251.6867e0d1bacc1.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/9ed5b2229627251.6867e0d1bbdcc.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/3a3079229627251.6867e0d1ba49c.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/e95a45229627251.6867e0d1bc881.jpg)


### Bill of Materials

| Part Type                                               | Unit  | Role/Notes                                        |
| ------------------------------------------------------- | ----- | ------------------------------------------------- |
| [Arduino UNO](https://amzn.to/44nRXEA)                  | 1     | Microcomputer.                                    |
| [5mm Common Cathode RGB LED](https://amzn.to/4lmJuaE)   | 1     | Light source component.                           |
| [Tactile Switch (Push Button)](https://amzn.to/3T0gNUF) | 1     | Used for ON/OFF control and for switching colors. |
| [Resistor (220Ω)](https://amzn.to/4kMejW2)              | 3     | For protecting the LED's data line.               |
| [Breadboard](https://amzn.to/40bMzlk)                   | 1     | Circuit base. (for prototype)                     |
| [Jumper Wires](https://amzn.to/45voWYC)                 | 1 set | Connecting parts together.                        |
| [USB cable (A-B)](https://amzn.to/407P2xg)              | 1     | For writing programs to Arduino.                  |

## Usage

### Hardware Development

-  Wire it according to [Arduino_Uno_Chroma_LED_bb.png](https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_Chroma_LED/diagrams/Arduino_Uno_Chroma_LED_bb.png)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/4fc92f229627251.6867e0d0b3b1b.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/fbf47c229627251.6867e0d0b35f8.jpg)

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/eb167d229627251.6867e0d0b3081.jpg)


### Software Development

1. Set up the IDE: Open the Arduino IDE. Ensure your board is configured correctly under Tools > Board (select "Arduino Uno").
2. Upload the Code: Copy and paste the complete code from the [https://github.com/asamiile/diy-electronics/blob/main/Arduino_Uno_Chroma_LED/Arduino_Uno_Chroma_LED.ino](Arduino_Uno_Chroma_LED/sketch/sketch_jul4a/Arduino_Uno_Chroma_LED/Arduino_Uno_Chroma_LED.ino) file into your sketch.
3. Connect & Upload: Connect your Arduino Uno to your PC with the USB cable and click the "Upload" button.


### Test

1. After uploading the sketch, the RGB LED will be off.
2. Press the tactile switch once. The LED will turn pink.
3. Each subsequent press will cycle through the colors: Orange, Green, Blue, Purple, and then a smooth color-fading animation.
4. The next press will turn the LED off again, completing the cycle.
5. Confirm that all patterns are displayed correctly to complete the test.


## Author

[Asami.K](https://asami.tokyo/)

[Arduino Uno Chroma LED - Behance](https://www.behance.net/gallery/229627251/Arduino-Uno-Chroma-LED)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
