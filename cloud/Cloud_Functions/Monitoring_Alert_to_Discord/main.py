import functions_framework
import requests
import json
import os
from typing import Tuple

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


def create_discord_message(payload: dict, channel: str) -> dict:
    """
    Generate Discord message from Google Cloud Monitoring payload.

    Args:
        payload: JSON payload from Google Cloud Monitoring
        channel: Channel name

    Returns:
        JSON data to send to Discord Webhook ({"content": "..."})
    """
    try:
        # Extract incident information
        incident = payload.get('incident', {})
        summary = incident.get('summary', 'No summary available')
        state = incident.get('state', 'UNKNOWN').upper()
        url = incident.get('url', '')

        # Base message part
        message = f"**[{state}]** {summary}"

        # Make prominent for critical channel
        if channel == 'critical':
            message = f"⚠️ @everyone\n{message}"

        # Add URL if it exists
        if url:
            message += f"\n\nDetails: {url}"

        return {"content": message}

    except Exception as e:
        print(f"ERROR: Failed to create Discord message: {str(e)}")
        # Return generic message on error
        return {
            "content": f"⚠️ Alert notification received. Please check Cloud Monitoring for details.\nError: {str(e)}"
        }


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
