# XIAO ESP32C3 LED Color Preview

[English](README.md) | [Japanese](README.ja.md)

## Overview

Preview physical LED color and brightness against 3DCG lighting using a Grove RGB LED Stick and Arduino IoT Remote. All ten WS2813 Mini LEDs show the same color. This is a planned build: the control sketch is not included and the proposed wiring has not been tested.

## Bill of Materials

### Control System

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| [XIAO ESP32C3 PRE-SOLDERED](https://link.amazon/B0c237jnG) | 1 | Main controller with WiFi; headers pre-soldered |
| [Seeed Studio XIAO Grove Shield](https://jp.seeedstudio.com/Grove-Shield-for-Seeeduino-XIAO-p-4621.html) | 1 | Grove connection interface |

### Input & Output

| Part | Quantity | Role / Notes |
| ---------------------------------------------- | ---- | -------------- |
| [Grove RGB LED Stick 104020131](https://jp.seeedstudio.com/Grove-RGB-LED-Stick-10-WS2813-Mini.html) | 1 | Ten WS2813 Mini LEDs; Grove cable included |

### Power System

| Part | Quantity | Role / Notes |
| ------------------------------------------------------------------------------------------------- | ---- | ---------------------------------------- |
| [Power Supply (5V, 2A+)](https://amzn.to/4jZEIyu) or [Mobile Power Bank](https://amzn.to/45jTQ5W) | 1    | Power supply for LEDs.                   |
| [Grove Screw Terminal](https://link.amazon/B022xHEM0) | 2 | Separate Shield-side and LED-side wiring without cutting cables |
| [DC jack adapter (female)](https://amzn.to/3IdZI7k)                                               | 1    | Connect the AC adapter to the breadboard |
| [Logic Level Shifter](https://amzn.to/4eeDyhr) | 1     | To convert the data signal voltage. |
| [Electrolytic Capacitor (1000µF)](https://amzn.to/45ZOWLQ)                                        | 1    | For power supply stabilization           |

### Prototyping & Wiring

| Part | Quantity | Role / Notes |
| ---------------------------------------------- | ----- | ---------------------------------- |
| [Breadboard](https://amzn.to/40bMzlk)          | 1     | Circuit base (for prototype)       |
| [Jumper Wires](https://amzn.to/45voWYC)        | 1 set | Connecting parts together; 22AWG solid wire recommended. Grove Screw Terminal accepts 20–30AWG. |
| [Resistor (300-500Ω)](https://amzn.to/4kMejW2) | 1     | For protecting the LED's data line |
| [USB-C Cable](https://amzn.to/4lU4bdZ)        | 1    | For programming and powering . |

## Development

### Hardware Development

#### Breadboard diagram

![Breadboard wiring diagram](diagrams/LED_Color_Preview.png)

Fritzing source: [LED_Color_Preview.fzz](diagrams/LED_Color_Preview.fzz)

The diagram's notes are in Japanese.

#### Wiring steps

> [!IMPORTANT]
> Keep the USB-C cable and the external 5V supply unplugged while wiring.

Wire colors follow the diagram (yellow: signal, orange: 3.3V, red: 5V, black: GND, white: Grove cable).

1. **Mount XIAO ESP32C3 on the Grove Shield**
   - Check the orientation against the Shield's silkscreen.
2. **Connect XIAO ESP32C3 to the LED**
   - Use Grove cables to connect the Shield's D2/A2 port ([pinout](https://jp.seeedstudio.com/Grove-Shield-for-Seeeduino-XIAO-p-4621.html)) to Grove Screw Terminal 1, and the LED Stick to Grove Screw Terminal 2 ([Grove Screw Terminal schematic](https://files.seeedstudio.com/wiki/Grove-Screw_Terminal/res/Grove-Screw_Terminal_v1.0.zip)).
   - Before connecting the orange wire, connect only XIAO ESP32C3 and the Shield to USB-C and measure about 3.3V between Grove Screw Terminal 1 VCC and GND with a multimeter. If it reads 5V, do not connect it; that can damage XIAO ESP32C3. Unplug USB-C after measuring.
   - Connect the yellow and orange wires and the 330Ω resistor as shown in the diagram. Only channel 1 (LV1/HV1) of the level shifter is used.
3. **Connect the power**
   - Connect the red and black wires and the 1000µF capacitor as shown in the diagram.
   - Insert the capacitor's striped lead into the − rail.
4. **Check before powering on**
   - No short between the + and − rails (check with a multimeter).
   - The external supply is 5V (do not use 9V or 12V).
   - Screw terminals are tight and no bare wires touch each other. Do not force thick wire (such as 18AWG) into Grove terminals.
5. **Power on**
   - Plug in the external 5V supply, then USB-C. Disconnect in reverse order.

#### Current and optional protection

All ten LEDs at full-brightness white draw only about 0.5A, so a fuse is not required; to add one as short-circuit protection, place the following parts between the DC jack + and the + rail.

- [Littelfuse 0287001.PXCN](https://www.marutsu.co.jp/pc/i/2563488/) (1A, DC32V, ATO)
- [FHAC0002ZXJ holder](https://www.marutsu.co.jp/pc/i/15761797/)

### Software Development

#### Development steps

> [!NOTE]
> Internet access and an Arduino Cloud plan that allows four variables are required.

1. **Prepare the board and libraries**
   - In the Arduino IDE Boards Manager, install `esp32 by Espressif Systems` and select `XIAO_ESP32C3`.
   - In the Library Manager, install `ArduinoIoTCloud` and `Adafruit_NeoPixel`. `WiFi` is included in the board package.
   - Attach the Wi-Fi antenna to XIAO ESP32C3.
2. **Register the device in Arduino Cloud**
   - In Devices, register XIAO ESP32C3 as a third-party ESP32 device.
   - Save the Device ID and Secret Key shown. Do not commit them to Git.
3. **Create a Thing**
   - Create a Thing, associate the device from step 2, and set the 2.4GHz Wi-Fi SSID and password.
   - Add these Integer Number, Read & Write variables: `red`, `green`, `blue`, `brightness`
4. **Upload the sketch**
   - The sketch has not been written yet. It should behave as follows:
     - Ten LEDs on D2 (GPIO4). The Nano pin mapping is not used.
     - LEDs are off at startup.
     - RGB and brightness are stored separately, and variable changes are applied to all ten LEDs.
   - Add it to the Thing's sketch and upload it to XIAO ESP32C3. See [Arduino development](../../../../docs/arduino-development.md) for upload instructions.
   - Confirm that the device shows as online in Arduino Cloud.
5. **Create the dashboard**
   - Add four Sliders with a 0–255 range, linked to `red`, `green`, `blue`, and `brightness`.
   - Open the dashboard in Arduino IoT Remote on iOS or Android.
6. **Check the color order**
   - At low brightness, show red, green, and blue one at a time and confirm each matches. If the colors differ, fix the color order (RGB, GRB, etc.) in the sketch.

### Test

#### Planned tests

Test red, green, blue, and white at low brightness, app control, and brightness 0. Measure current, voltage, and temperature at the intended maximum brightness; verify behavior after power cycling and Wi-Fi reconnection.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)
- [Credentials](../../../../docs/credentials.md)

- [XIAO ESP32C3 Documentation and Pinout](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/)
- [Grove Shield for XIAO](https://wiki.seeedstudio.com/Grove-Shield-for-Seeeduino-XIAO-embedded-battery-management-chip/)
- [Grove RGB LED Stick Specifications and Pinout](https://wiki.seeedstudio.com/Grove-RGB_LED_Stick-10-WS2813_Mini/)
- [Arduino Cloud / IoT Remote](https://cloud.arduino.cc/how-it-works/)
- [Grove-to-Jumper Conversion Cable](https://jp.seeedstudio.com/Grove-4-pin-Female-Jumper-to-Grove-4-pin-Conversion-Cable-5-PCs-per-PAck.html)
- [Grove Screw Terminal](https://wiki.seeedstudio.com/Grove-Screw_Terminal/)
- [Grove Screw Terminal schematic (Eagle/PDF)](https://files.seeedstudio.com/wiki/Grove-Screw_Terminal/res/Grove-Screw_Terminal_v1.0.zip)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
