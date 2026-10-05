# Credentials

[English](credentials.md) | [日本語](credentials.ja.md)

Copy the project's `credentials.h.example` to `credentials.h` in the same sketch directory, then enter your own Wi-Fi and service credentials. Preserve the example file as a reusable template. Arduino Cloud projects may use generated device secrets instead; follow their project instructions.

Keep personal Wi-Fi credentials, API keys, device secret keys, Discord webhook URLs, `.env` files, and service-account keys out of Git. Use placeholders in documentation. Configure cloud credentials through the project's environment variables or deployment secret configuration.

Check `.gitignore` before adding new local configuration. Exclude specific secret files rather than all JSON files. System settings such as pin assignments, schedules, and thresholds belong in the project's configuration, not in credential examples.
