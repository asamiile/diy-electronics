# Cloud Functions workflow

[English](cloud-functions.md) | [日本語](cloud-functions.ja.md)

## Preparation

Install the [Google Cloud CLI](https://cloud.google.com/sdk/docs/install), select a project, and prepare the APIs and IAM permissions required by the project. Run commands from the cloud function's directory.

```sh
gcloud auth login
gcloud config set project YOUR_GCP_PROJECT_ID
python3 -m venv .venv
source .venv/bin/activate
python -m pip install -r requirements.txt
```

On Windows, activate the environment with `.venv\Scripts\Activate.ps1` in PowerShell or `.venv\Scripts\activate.bat` in cmd. For local BigQuery access, configure application-default credentials; a project's local test mode can skip BigQuery writes.

## Local execution

Set project-specific environment variables first, then replace `ENTRY_POINT` with the function name in `main.py`.

```sh
functions-framework --target ENTRY_POINT --debug --port 8080
```

Send the project README's sample JSON to `http://localhost:8080`. Local test mode only bypasses writes where implemented; the Discord function can send actual notifications when its webhook is configured.

## Deployment

Use the deployment name, entry point, runtime, and environment variables from the project README. Replace the placeholders below.

```sh
gcloud functions deploy FUNCTION_NAME \
  --gen2 \
  --region asia-northeast1 \
  --runtime RUNTIME \
  --source . \
  --entry-point ENTRY_POINT \
  --trigger-http \
  --memory 256MB \
  --timeout 60s
```

The existing external webhook examples use public HTTP endpoints; add `--allow-unauthenticated` for that configuration. If using authenticated invocation, configure the caller accordingly. Supply project-specific environment variables or secrets during deployment. Save the actual trigger URL instead of constructing one from a presumed URL format.

## Logs and webhook checks

```sh
gcloud functions describe FUNCTION_NAME --gen2 --region asia-northeast1
gcloud functions logs read FUNCTION_NAME --gen2 --region asia-northeast1 --limit 50
```

For Shiftr.io, match the device topic exactly, select POST with JSON, use the deployed trigger URL, and enable the webhook. Trace failures from device publication through broker and webhook history, function logs, and database schema/permissions. Changing code or configuration requires updating the deployment; use the same deployment options as the initial deployment.

## References

- [gcloud functions deploy](https://cloud.google.com/sdk/gcloud/reference/functions/deploy)
- [Python Functions Framework](https://github.com/GoogleCloudPlatform/functions-framework-python)
