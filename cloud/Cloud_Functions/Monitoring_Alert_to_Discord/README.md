# Monitoring Alert to Discord

[English](README.md) | [Japanese](README.ja.md)

## Overview

An HTTP function forwards Google Cloud Monitoring incidents to Discord. Query parameter `channel=critical` adds `@everyone`; `warning` and the default use standard formatting. All levels use the same configured webhook URL.

## Bill of Materials

No dedicated electronic components are required. See Software Development for the required services and dependencies.

## Development

### Hardware Development

No dedicated hardware setup is required.

### Software Development

#### Project configuration

- Deployment name/entry point: `notify_discord`; documented runtime: `python312`.
- Set `DISCORD_WEBHOOK_URL` to the target Discord webhook. Create it in the channel's Integrations → Webhooks settings; keep the URL private.
- Dependencies: [requirements.txt](requirements.txt); implementation: [main.py](main.py).
- Functions: `notify_discord`, `get_discord_webhook_url`, `create_discord_message`, and `send_to_discord`.

Use the common cloud guide for local environment and deployment. Add the webhook environment variable or an appropriate secret binding to the deployment configuration. The existing example allows public HTTP invocation. Authentication changes require a compatible Monitoring caller.

#### Monitoring integration and troubleshooting

Create a Monitoring webhook notification channel pointing to the function's trigger URL, add `?channel=critical` for critical alerts, and assign the channel to an alert policy. Confirm Discord receives the notification.

For missing configuration, check whether the environment variable/secret is present without printing its value. For authorization failures, verify the webhook exists and is valid; update it if regenerated. For timeouts, inspect service connectivity and the function's logs. Redeploy with the shared deployment procedure when changing code, memory, timeout, or configuration. Production secret storage and caller authentication must be configured explicitly; they are not implemented by this source alone.

### Test

#### Local and deployed tests

Configure the webhook before starting Functions Framework with `notify_discord`. A configured local test sends a real message; this function has no `LOCAL_TEST_MODE` bypass. Without a webhook, it returns a configuration error.

```sh
curl -X POST 'http://localhost:8080?channel=critical' \
  -H "Content-Type: application/json" \
  -d '{"incident":{"summary":"Test Alert","state":"OPEN","url":"https://console.cloud.google.com/"}}'
```

Successful delivery returns `{"status":"success"}`. Replace the local base URL with the actual deployed trigger URL for a remote test. Critical messages contain `@everyone`, incident state, summary, and the details URL; warning/default messages omit the mention.

## References

### Common guides

- [Cloud Functions workflow](../../../docs/cloud-functions.md)
- [Credentials](../../../docs/credentials.md)

- [Google Cloud Functions Documentation](https://cloud.google.com/functions/docs)
- [Google Cloud Monitoring Webhook](https://cloud.google.com/monitoring/support/notification-options#webhooks)
- [Discord Webhook Official Documentation](https://discord.com/developers/docs/resources/webhook)
- [Weather Station Data Pipeline](../Weather_Station_Data_Pipeline) - BigQuery streaming
- [Wio Terminal Weather Station](../../../mcu/samd51/Wio_Terminal/External_Sensor/Weather_Station_v2) - Hardware integration

## Author

[Asami.K](https://asami.tokyo/)

<a href="https://www.buymeacoffee.com/asamiei" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Buy Me A Coffee" style="height: 60px !important;width: 217px !important;" ></a>
