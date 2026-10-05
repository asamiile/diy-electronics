# Arduino development

[English](arduino-development.md) | [日本語](arduino-development.ja.md)

## Prepare the environment

Install Arduino CLI using the [official installation guide](https://arduino.github.io/arduino-cli/latest/installation/), or use Arduino IDE. Open this repository's root folder in VS Code to load its shared editor settings.

Run commands below from the project directory. Install the board package and libraries specified by that project's README. Board names, pin numbering, and FQBNs differ even within the same chip family.

```sh
arduino-cli core update-index
arduino-cli board list
arduino-cli board listall
arduino-cli core list
arduino-cli core install CORE_ID
arduino-cli lib list
arduino-cli lib install "LIBRARY_NAME"
```

For a board package requiring an additional index URL, add the URL documented by its vendor to the CLI configuration before installing the core. In Arduino IDE, use Preferences → Additional Boards Manager URLs, Boards Manager, and Library Manager.

## Compile and upload

Replace `FQBN`, `SKETCH_DIRECTORY`, and `PORT` with the project's board identifier, sketch directory, and the connected port reported by `board list`. The sketch directory contains the main `.ino` file with the same name.

```sh
arduino-cli compile --fqbn FQBN SKETCH_DIRECTORY
arduino-cli upload -p PORT --fqbn FQBN SKETCH_DIRECTORY
arduino-cli monitor -p PORT --config baudrate=115200
```

Use the baud rate declared by the sketch. In Arduino IDE, select the target board and port, open the main sketch, and choose Upload. Verify board-specific bootloader instructions if upload fails.

## Legacy example files

Some existing examples store an `.ino` directly in a category directory whose name differs from the sketch. For Arduino CLI, copy the `.ino` and its required companion files into a temporary directory named after the main sketch, then compile that directory. Arduino IDE may offer to create the matching sketch folder when opening the file. Preserve repository source names; this preparation does not make the example's missing libraries or exported models available.

## Before hardware testing

Follow the project's wiring and power requirements, check polarity, and use the specified common ground. Keep external LED/motor power separate where the project requires it. Record compile results separately from physical hardware tests.

## References

- [Compile command](https://arduino.github.io/arduino-cli/latest/commands/arduino-cli_compile/)
- [Upload command](https://arduino.github.io/arduino-cli/latest/commands/arduino-cli_upload/)
