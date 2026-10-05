# Credential management

- Do not commit Wi-Fi credentials, API keys, or service-account keys. Leave personal credential files unchanged unless they are part of the user's request; never print their values in logs or reports.
- Keep Arduino credentials in `credentials.h` and provide a placeholder-only `credentials.h.example`. Follow the existing credential mechanism in each project.
- Configure cloud credentials through environment variables or local key files. Use placeholders in README examples and test data.
- Maintain exclusions in the root `.gitignore`. Do not ignore every `*.json` file, because shared configuration and sample files must remain trackable.
