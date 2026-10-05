#!/usr/bin/env python3
"""
Local test script for save_weather_data function
"""

import os
import sys
import json

# Set test mode environment variable
os.environ['LOCAL_TEST_MODE'] = 'true'

# Add current directory to path
sys.path.insert(0, os.path.dirname(__file__))

from main import save_weather_data
from unittest.mock import Mock

# Create mock request
mock_request = Mock()
mock_request.get_json.return_value = {
    "device_id": "wio_terminal",
    "temperature": 22.5,
    "humidity": 55.0
}

print("=" * 60)
print("LOCAL TEST: Calling save_weather_data()")
print("=" * 60)

# Call function
response, status_code = save_weather_data(mock_request)

print(f"\nStatus Code: {status_code}")
print(f"Response:\n{response}")

if status_code == 200:
    print("\n✅ TEST PASSED: Function executed successfully in test mode!")
else:
    print(f"\n❌ TEST FAILED: Unexpected status code {status_code}")

print("=" * 60)
