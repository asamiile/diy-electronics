# TinyML with WioTerminal

[English](README.md) | [Japanese](README.ja.md)

## Overview

Wio Terminal TinyML examples cover audio scene recognition, accelerometer gestures, ultrasonic people counting, light-sensor gestures, and word detection. Model training/deployment requirements differ between examples.

## Bill of Materials

| Part | Quantity | Role / Notes |
| --- | --- | --- |
| Wio Terminal | 1 | Controller and sensor processing |
| Data-capable USB-C cable | 1 | Power and programming |

## Development

### Hardware Development

See Bill of Materials for the required hardware.

### Software Development

#### Environment and examples

Use the shared TinyML environment guide below for the original Conda, Python, FFmpeg, and Edge Impulse CLI setup. See the individual directories for collection and deployment sketches; trained model libraries must be supplied where required.

- [Audio scene recognition](Audio_scene_recognition_with_microphone/)
- [Accelerometer gestures](Classifying_hand_gestures_with_accelerometer/)
- [Ultrasonic people counting](People_counting_with_Ultrasonic_sensor/)
- [Light-sensor gestures](Recognizing_gestures_with_light_sensor/)
- [Word detection](Word_Detection/README.md)

### Test

Verify the behavior described in Overview and the development instructions. Compilation, execution, and physical hardware checks were not performed as part of this documentation update.

## References

### Common guides

- [Arduino development](../../../../docs/arduino-development.md)
- [TinyML environment](../../../../docs/tinyml-development.md)

- [TinyML with Wio Terminal](https://files.seeedstudio.com/wiki/Wio-Terminal-TinyML/TinyML_with_Wio_Terminal_Course_v1-3.pdf)
- [Wio Terminal Edge Impulse firmware](https://github.com/Seeed-Studio/Seeed_Arduino_edgeimpulse/releases/tag/1.4.0)

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiile" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
