# Wio Terminal Weather Station

## Overview

This project transforms the Wio Terminal into a weather station. It measures ambient temperature and humidity using a Grove - DHT11 sensor and displays the data in real-time on the built-in LCD screen.

![](https://mir-s3-cdn-cf.behance.net/project_modules/max_3840_webp/76df73232223085.68984e3bc47f8.jpg)

### Features

- **Real-time Local Display**: Shows current temperature and humidity on the Wio Terminal's LCD screen
- **Simple Setup**: Easy-to-follow calibration with minimal configuration
- **Responsive UI**: Custom colors and fonts for improved readability
- **Battery Support**: Standalone operation via battery base (see Battery Power Requirements below)
- **Remote Monitoring**: Data publishing to Adafruit IO for cloud-based tracking

## Bill of Materials

| Part Type                                                                | Unit | Role/Notes                                                               |
| ------------------------------------------------------------------------ | ---- | ------------------------------------------------------------------------ |
| [Wio Terminal](https://amzn.to/4me4lxu)                                  | 1    | Main controller, display, and Wi-Fi module                               |
| [Grove - Temperature & Humidity Sensor (DHT11)](https://amzn.to/3Um4qmA) | 1    | Connected to any of the Grove ports (code uses D0)                       |
| USB Type-C Cable                                                         | 1    | For power and programming. Must be a data-sync cable                     |
| **Battery Base (Optional)**                                              | 1    | For standalone operation. See "Battery Power Requirements" section below |

## Setup Instructions

Please follow the reference guide below for the basic setup procedure.

- [Wio Terminal Getting Started Guide](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)

### Power Requirements & Battery Operation

**⚠️ Important - Display Shutdown Issue on Battery Power**

If the Wio Terminal's display goes black/blank after switching to battery power, check the following:

#### 1. **Battery Voltage Requirements**

- **Minimum Required**: 4.75V (USB standard)
- **Recommended**: 5.0V - 5.5V DC
- **Wio Terminal Power Consumption**: ~300-400mA (WiFi + Display running)
  - WiFi active: ~200-250mA
  - TFT LCD display: ~100-150mA
  - Sensor & MCU: ~50mA

**❌ Common Issues:**

- Battery voltage drops below 4.75V → TFT display shuts down (display still operating, but backlight off)
- Weak USB-C cable or loose connection → voltage drop at Wio Terminal
- Battery base capacity insufficient for sustained WiFi operation

#### 2. **Testing Battery Power**

```bash
# Use a multimeter to measure voltage:
# 1. Place probes on Battery Base USB-C connector (GND and +5V)
# 2. Record the voltage - should be 5.0V ± 0.3V

# Expected readings:
# USB power from PC: 5.0-5.2V → Display always ON ✅
# Battery base: 4.8-5.0V (full) → Display normally ON ✅
# Battery base: 4.5-4.7V (discharged) → Display may flicker or go black ⚠️
```

#### 3. **Improving Battery Stability**

**Option A: Use a High-Quality Battery Base**

- Recommended: Battery bases rated for ≥5000mAh capacity
- Ensure the USB-C output is regulated to stable 5V

**Option B: Add Power Stabilization**
Connect a 470µF - 1000µF electrolytic capacitor across the battery output (optional hardware mod):

```
Battery Base GND ─┤ ├─ Battery Base +5V
                  470µF
```

This smooths voltage ripple and helps TFT display stability.

**Option C: Check Firmware Behavior**
The updated code includes automatic display recovery every 5 seconds. If display goes black:

- Check Serial Monitor for error messages
- Verify WiFi connection status
- Battery voltage may be unstable

### 1. Hardware Setup

1. Connect the DHT11 sensor to one of the Grove ports (default: D0)
2. Connect Wio Terminal to your computer via USB Type-C cable

### 2. Software Setup

1. Install Arduino IDE and Wio Terminal board support
2. Install required libraries:
   - `DHT sensor library` by Adafruit
   - `Adafruit Unified Sensor` by Adafruit
3. Upload the sketch from the `sketch/` folder

### 3. Customize Display

The sketch includes color and font customization options. Modify these constants at the top of the sketch:

```cpp
#define TEMP_COLOR TFT_RED
#define HUMIDITY_COLOR TFT_BLUE
#define TEXT_SIZE 2
```

## Sketch Location

The sketch files are available in the `sketch/` directory.

## Cloud Integration (Optional)

For remote data monitoring and logging, refer to the [Adafruit IO Integration Guide](with_Adafruit_IO/README.md).

## Troubleshooting

### Display Goes Black When Using Battery Power

#### Symptoms

- Display works normally on USB power (PC connection)
- Display goes black/blank immediately after switching to battery power
- WiFi/sensor LED still blinks (device still running)

#### Root Cause Analysis

This is typically caused by **voltage instability** in the battery base:

| Issue                         | Voltage Impact   | Result                                        |
| ----------------------------- | ---------------- | --------------------------------------------- |
| Battery voltage too low       | <4.75V           | TFT backlight shuts down (no display)         |
| Weak/loose USB-C cable        | 4.5-4.7V         | Display flickers or goes black intermittently |
| Battery capacity insufficient | Drops under load | System resets or display blacks out           |
| Poor battery contact          | Fluctuates 3-5V  | Erratic display behavior                      |

#### Solution Steps

**Step 1: Verify Battery Output Voltage**

1. Get a digital multimeter (or USB voltage meter)
2. Measure voltage at battery base USB-C connector:
   ```
   RED probe → USB-C +5V pin
   BLACK probe → USB-C GND pin
   ```
3. Expected readings:
   - **No load**: 4.95-5.10V ✅ (Good)
   - **With Wio Terminal**: 4.75-4.95V ✅ (Acceptable)
   - **Below 4.70V** ❌ (Battery too weak)

**Step 2: Check USB-C Cable Quality**

- Use a proper data-sync USB Type-C cable
- Avoid cheap/charging-only cables (they may have poor contact resistance)
- Test with a different cable if available

**Step 3: Upgrade Battery Base** (if voltage is consistently low)

- Replace with a battery base rated ≥5000mAh
- Ensure output is regulated (stable 5V ± 0.3V)
- Avoid low-capacity power banks

**Step 4: Add Power Smoothing Capacitor** (Optional Hardware Mod)
If upgrading isn't possible, add a 470-1000µF capacitor to stabilize voltage:

```
[Battery Base Output]
        ↓
     +5V ─┬─→ [Wio Terminal]
         ┤
        C C 470-1000µF
        | |
       GND─┴─→ [Wio Terminal]
```

#### Firmware-Level Mitigation

The updated firmware includes:

- Auto display recovery every 5 seconds
- Graceful WiFi failure handling (non-blocking)
- Serial debug output for diagnosis

**Check Serial Monitor for detailed status:**

```bash
# Connect via Serial at 115200 baud
# Look for messages like:
# "Connected to WiFi. IP: 192.168.0.XX"
# "Attempting MQTT connection...connected"
```

If you see constant reconnection attempts, WiFi is unstable due to power fluctuations.

---

### Display Still Doesn't Show After Troubleshooting

1. **Force Reboot**: Press Wio Terminal power button
2. **Check DHT11 Sensor**: Disconnect and verify display initializes
3. **Serial Output**: Connect to PC to see initialization status
4. **Hardware Check**: Verify all Grove connectors are seated properly

## References

- [Wio Terminal Documentation](https://wiki.seeedstudio.com/Wio_Terminal_Intro/)
- [DHT11 Sensor Guide](https://www.adafruit.com/product/386)
- [Grove Sensor Documentation](https://wiki.seeedstudio.com/Grove_System/)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiii" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
