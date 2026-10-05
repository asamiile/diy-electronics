# Directory policy

## Classification

- `sbc/<board>/<project>/`: applications and system projects for computers such as Raspberry Pi.
- `mcu/<chip-family>/<board>/<project>/`: microcontroller firmware, diagrams, and board-specific instructions.
- `cloud/<runtime>/<project>/`: cloud processes connected to hardware projects.
- `docs/`: shared repository documentation.

Separate SBC and MCU by their execution/development environments. Group MCU projects by chip family before board brand, while retaining board directories because pins, peripherals, cores, FQBNs, and libraries differ. Using Arduino tools alone does not determine a project's location.

## Adding and updating projects

1. Place the project under its existing category/family/board; add a directory for a genuinely new family or board.
2. Create English `README.md` and Japanese `README.ja.md`, with optional `sketch/`, `diagrams/`, and `docs/`. Document the board, wiring, dependencies, and build procedure. Link repeated setup to the shared guides.
3. Keep the main Arduino `.ino` filename aligned with its parent sketch directory. Preserve existing sketch and diagram names when reorganizing projects.
4. For multi-device projects, use the primary board running the directory's code and link the counterpart projects. GalaxyRVR is under Uno for its control sketch; Vision AI Camera is under Pi for its system documentation.
5. Update both root project indexes and relative links. When moving projects, check README, `AGENTS.md`, and build paths.
6. Keep credentials in the existing ignored local files.

Add cross-board shared code only when needed. Existing `BuiltIn_Peripherals`, `BuiltIn_Sensors`, `External_Sensor`, `ML`, and project names are retained.

## Migration table

Update fixed paths in personal scripts and open editor files to the new locations. In VS Code, open the repository root to use `.vscode/settings.json`.

| Old path | New path |
| --- | --- |
| `Arduino_Nano_ESP32/` | [`mcu/esp32/Arduino_Nano_ESP32/`](../../mcu/esp32/Arduino_Nano_ESP32) |
| `XIAO_ESP32C3/` | [`mcu/esp32/XIAO_ESP32C3/`](../../mcu/esp32/XIAO_ESP32C3) |
| `ESP32-DevKitC/` | [`mcu/esp32/ESP32-DevKitC/`](../../mcu/esp32/ESP32-DevKitC) |
| `Arduino_Uno/` | [`mcu/avr/Arduino_Uno/`](../../mcu/avr/Arduino_Uno) |
| `Arduino_Nano_33_BLE_Sense/` | [`mcu/nrf52/Arduino_Nano_33_BLE_Sense/`](../../mcu/nrf52/Arduino_Nano_33_BLE_Sense) |
| `XIAO_RP2040/` | [`mcu/rp2040/XIAO_RP2040/`](../../mcu/rp2040/XIAO_RP2040) |
| `Wio_Terminal/` | [`mcu/samd51/Wio_Terminal/`](../../mcu/samd51/Wio_Terminal) |
| `Raspberry_Pi_5/` | [`sbc/Raspberry_Pi_5/`](../../sbc/Raspberry_Pi_5) |
| `Cloud_Functions/` | [`cloud/Cloud_Functions/`](../../cloud/Cloud_Functions) |
| `Rotating_Turntable/` | [`mcu/esp32/Arduino_Nano_ESP32/Rotating_Turntable/`](../../mcu/esp32/Arduino_Nano_ESP32/Rotating_Turntable) |
| `SunFounder_GalaxyRVR/` | [`mcu/avr/Arduino_Uno/SunFounder_GalaxyRVR/`](../../mcu/avr/Arduino_Uno/SunFounder_GalaxyRVR) |
