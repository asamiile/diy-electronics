import functions_framework
from google.cloud import bigquery
import datetime
import os
import json

# BigQuery Configuration
DATASET_ID = 'diy_electronics_iot'
TABLE_ID = 'weather_data'

# Check if running in local development mode
LOCAL_TEST_MODE = os.getenv('LOCAL_TEST_MODE', 'false').lower() == 'true'

@functions_framework.http
def save_weather_data(request):
    """
    HTTP Cloud Function to save weather data to BigQuery.

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

        # Prepare row to insert
        row_to_insert = {
            "timestamp": datetime.datetime.now(datetime.timezone.utc).isoformat(),
            "device_id": request_json.get("device_id", "unknown_device"),
            "temperature": request_json.get("temperature"),
            "humidity": request_json.get("humidity")
        }

        # Local test mode: print and return without actual BigQuery insertion
        if LOCAL_TEST_MODE:
            print(f"[LOCAL TEST] Received data: {json.dumps(row_to_insert, indent=2)}")
            return json.dumps({"status": "success", "message": "Data received (test mode)", "data": row_to_insert}), 200

        # Production mode: insert into BigQuery
        client = bigquery.Client()

        # Get project ID (Cloud Functions automatically uses the project context)
        project_id = client.project
        table_id = f"{project_id}.{DATASET_ID}.{TABLE_ID}"

        print(f"Inserting data into {table_id}")
        table = client.get_table(table_id)

        errors = client.insert_rows_json(table, [row_to_insert])
        if errors == []:
            print(f"Successfully inserted row: {row_to_insert}")
            return 'Success', 200
        else:
            print(f"BigQuery Insert Errors: {errors}")
            return f'Error: {errors}', 500

    except Exception as e:
        print(f"Unexpected Error: {e}")
        import traceback
        traceback.print_exc()
        return f'Server Error: {e}', 500
