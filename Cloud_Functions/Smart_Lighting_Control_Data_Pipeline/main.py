import functions_framework
from google.cloud import bigquery
import datetime
import os
import json

# BigQuery Configuration
DATASET_ID = 'diy_electronics_iot'
TABLE_ID = 'lighting_data'

# Check if running in local development mode
LOCAL_TEST_MODE = os.getenv('LOCAL_TEST_MODE', 'false').lower() == 'true'

@functions_framework.http
def save_lighting_data(request):
    """
    HTTP Cloud Function to save smart lighting control data to BigQuery.

    Receives JSON data from Shiftr.io Webhook:
    {
        "device_id": "arduino_nano_esp32",
        "timestamp": 1234567890,
        "lux": 2367,
        "light_state": "ON",
        "task_executed": false,
        "wifi_connected": true,
        "retry_count": 0
    }

    Args:
        request (flask.Request): The request object.

    Returns:
        Tuple[str, int]: Response message and HTTP status code.
    """
    try:
        # Parse JSON payload
        request_json = request.get_json(silent=True)
        if not request_json:
            return 'JSON payload required', 400

        # Extract data from request
        device_id = request_json.get("device_id", "unknown_device")
        light_level = request_json.get("lux", 0)
        status = request_json.get("light_state", "UNKNOWN")

        # Use timestamp from device if available, otherwise use current UTC time
        timestamp_unix = request_json.get("timestamp")
        if timestamp_unix:
            # Convert Unix timestamp to ISO 8601 format
            timestamp_utc = datetime.datetime.fromtimestamp(
                timestamp_unix,
                tz=datetime.timezone.utc
            ).isoformat()
        else:
            timestamp_utc = datetime.datetime.now(datetime.timezone.utc).isoformat()

        # Prepare row to insert into BigQuery
        row_to_insert = {
            "timestamp": timestamp_utc,
            "device_id": device_id,
            "light_level": light_level,
            "status": status
        }

        # Local test mode: print and return without actual BigQuery insertion
        if LOCAL_TEST_MODE:
            print(f"[LOCAL TEST] Received lighting data: {json.dumps(row_to_insert, indent=2)}")
            return json.dumps({
                "status": "success",
                "message": "Data received (test mode)",
                "data": row_to_insert
            }), 200

        # Production mode: insert into BigQuery
        client = bigquery.Client()

        # Get project ID (Cloud Functions automatically uses the project context)
        project_id = client.project
        table_id = f"{project_id}.{DATASET_ID}.{TABLE_ID}"

        print(f"Inserting lighting data into {table_id}")
        table = client.get_table(table_id)

        errors = client.insert_rows_json(table, [row_to_insert])
        if errors == []:
            print(f"Successfully inserted row: {row_to_insert}")
            return json.dumps({
                "status": "success",
                "message": "Data inserted successfully",
                "data": row_to_insert
            }), 200
        else:
            print(f"BigQuery Insert Errors: {errors}")
            return json.dumps({
                "status": "error",
                "message": f"BigQuery insert failed: {errors}"
            }), 500

    except Exception as e:
        print(f"Unexpected Error: {e}")
        import traceback
        traceback.print_exc()
        return json.dumps({
            "status": "error",
            "message": f"Server Error: {str(e)}"
        }), 500
