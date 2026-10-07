import functions_framework
import requests
import json
import os
from datetime import datetime, timezone, timedelta

@functions_framework.http
def notify_discord(request):
    """
    Receives Webhook notifications from Google Cloud Monitoring and sends
    notifications to Discord based on the channel specified in the query parameter.
    Uses a single Discord Webhook URL configured via DISCORD_WEBHOOK_URL environment variable.

    Query Parameters:
        channel: 'critical', 'warning', or other (affects message formatting)

    Request Body:
        JSON payload from Google Cloud Monitoring
        (includes incident.summary, incident.state, incident.url)
    """
    try:
        # Get channel from query parameter
        channel = request.args.get('channel', default='default').lower()

        # Determine Discord Webhook URL based on channel
        discord_url = get_discord_webhook_url(channel)

        if not discord_url:
            error_msg = f"Discord Webhook URL not configured for channel: {channel}"
            print(f"ERROR: {error_msg}")
            return {"error": error_msg}, 400

        # Extract incident information from request body
        payload = request.get_json()
        if not payload:
            error_msg = "Request body is not JSON"
            print(f"ERROR: {error_msg}")
            return {"error": error_msg}, 400

        # Create Discord message
        discord_message = create_discord_message(payload, channel)

        # Send to Discord
        response = send_to_discord(discord_url, discord_message)

        if response.status_code in [200, 204]:
            print(f"Successfully sent notification to Discord ({channel} channel)")
            return {"status": "success"}, 200
        else:
            error_msg = f"Discord API returned status {response.status_code}: {response.text}"
            print(f"ERROR: {error_msg}")
            return {"error": error_msg}, response.status_code

    except json.JSONDecodeError as e:
        error_msg = f"Failed to parse JSON request body: {str(e)}"
        print(f"ERROR: {error_msg}")
        return {"error": error_msg}, 400
    except Exception as e:
        error_msg = f"Unexpected error: {str(e)}"
        print(f"ERROR: {error_msg}")
        return {"error": error_msg}, 500


def get_discord_webhook_url(channel: str) -> str:
    """
    Get Discord Webhook URL from environment variable.

    Args:
        channel: Channel name (for message formatting only)

    Returns:
        Discord Webhook URL, or empty string if not configured
    """
    return os.getenv('DISCORD_WEBHOOK_URL', '')


def format_incident_time(value) -> str:
    """MonitoringのUnix時刻を日本時間で表示する。"""
    try:
        return datetime.fromtimestamp(float(value), timezone(timedelta(hours=9))).strftime('%Y/%m/%d %H:%M:%S JST')
    except (TypeError, ValueError, OverflowError, OSError):
        return 'Unknown'


def create_discord_message(payload: dict, channel: str) -> dict:
    """気象・照明の停止通知を英語にし、他のポリシーは概要を保持する。"""
    incident = payload.get('incident') or {}
    state = str(incident.get('state', 'UNKNOWN')).upper()
    summary = incident.get('summary') or 'No summary available'
    service = (incident.get('resource') or {}).get('labels', {}).get('service_name')
    policy = incident.get('policy_name', '')
    routes = {
        'save-weather-data': ('weather-station', 'Weather'),
        'save-lighting-data': ('lighting', 'Lighting'),
    }
    # リソースラベルを優先し、既存ポリシー名でも対象を識別する。
    if not service:
        service = {
            'weather-station - Data delivery outage': 'save-weather-data',
            'lighting - Data delivery outage': 'save-lighting-data',
            'Wio Terminal outage alert': 'save-weather-data',
            'Arduino Nano ESP32 outage alert': 'save-lighting-data',
        }.get(policy)
    if service in routes and state in ('OPEN', 'CLOSED'):
        route, label = routes[service]
        closed = state == 'CLOSED'
        title = f"✅ Data delivery alert cleared: {route}" if closed else f"⚠️ Data delivery stopped: {route}"
        description = f"The {label.lower()} data delivery alert has closed." if closed else f"No requests for {label.lower()} data have been received for 10 minutes."
        timestamp = format_incident_time(incident.get('ended_at' if closed else 'started_at'))
        time_label = 'Closed at' if closed else 'Detected at'
        message = f"**{title}**\n\n{description}\n\nTarget: Wio Terminal / {service}\n{time_label}: {timestamp}"
        if not closed:
            message += '\n\nCheck:\n- Wio Terminal power and Wi-Fi\n- Shiftr connection and webhook\n- Cloud Run logs'
        else:
            message += '\n\nThe monitoring incident has closed. Verify that BigQuery data storage has resumed separately.'
    else:
        message = f"**[{state}]** {summary}"
    if channel == 'critical':
        message = '@everyone\n' + message
    if incident.get('url'):
        message += f"\n\nDetails: {incident['url']}"
    return {'content': message}


def send_to_discord(webhook_url: str, message: dict) -> requests.Response:
    """
    Send notification to Discord Webhook.

    Args:
        webhook_url: Discord Webhook URL
        message: Message to send ({"content": "..."})

    Returns:
        requests.Response object
    """
    headers = {"Content-Type": "application/json"}

    try:
        response = requests.post(
            webhook_url,
            json=message,
            headers=headers,
            timeout=10
        )
        return response
    except requests.exceptions.Timeout:
        print("ERROR: Request to Discord Webhook timed out")
        raise
    except requests.exceptions.RequestException as e:
        print(f"ERROR: Failed to send request to Discord Webhook: {str(e)}")
        raise
