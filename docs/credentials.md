# Credentials

[English](credentials.md) | [日本語](credentials.ja.md)

Copy the project's `credentials.h.example` to `credentials.h` in the same sketch directory, then enter your own Wi-Fi and service credentials. Preserve the example file as a reusable template.

Projects uploaded from the Arduino Cloud web editor use `arduino_secrets.h` instead, because the web editor generates it from the Secret tab. The repository contains only an `arduino_secrets.h` with empty values. Enter your Device ID, Secret Key, and Wi-Fi settings only in the web editor's Secret tab, never in the local file. Projects that use Arduino Cloud but upload from the Arduino IDE use `credentials.h`, as above.

Keep personal Wi-Fi credentials, API keys, device secret keys, Discord webhook URLs, `.env` files, and service-account keys out of Git. Use placeholders in documentation. Configure cloud credentials through the project's environment variables or deployment secret configuration.

Check `.gitignore` before adding new local configuration. Exclude specific secret files rather than all JSON files. System settings such as pin assignments, schedules, and thresholds belong in the project's configuration, not in credential examples.
