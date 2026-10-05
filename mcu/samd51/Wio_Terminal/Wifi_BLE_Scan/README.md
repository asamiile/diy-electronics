# Wio Terminal Wi-Fi and BLE Scan

[English](README.md) | [Japanese](README.ja.md)

## Overview

Repeatedly scans Wi-Fi networks and BLE advertisements, printing SSID, RSSI, Wi-Fi protection indicators, BLE device details, and device counts at 115200 baud. BLE scans last five seconds, followed by a one-second pause between loop cycles. Open Serial Monitor to pass the initial serial wait; no Wi-Fi credentials are required for scanning.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

## Development

### Hardware Development

#### Hardware and dependencies

Wio Terminal and a data-capable USB-C cable; this example uses onboard hardware and needs no external sensor wiring.

Dependencies: `rpcWiFi.h`, `rpcBLEDevice.h`, `BLEScan.h`, `BLEAdvertisedDevice.h`.

### Software Development

#### Source files

- [Wifi_BLE_Scan.ino](Wifi_BLE_Scan.ino)

Use the Wio Terminal board package. For legacy files stored outside a matching sketch directory, follow the shared guide before compiling. These instructions describe the source; compilation and physical behavior have not been verified in this documentation update.

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
