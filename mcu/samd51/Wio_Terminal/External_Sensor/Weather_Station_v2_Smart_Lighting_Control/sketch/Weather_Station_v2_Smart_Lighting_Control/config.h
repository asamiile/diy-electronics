#pragma once
#include <Arduino.h>

// ChassisのGroveポートを使用。括弧内は同じポートの第2信号。
constexpr uint8_t LIGHT_SENSOR_PIN = A0;       // Grove D0/A0 (D1/A1)
constexpr uint8_t IR_EMITTER_PIN = D2;         // Grove D2/A2 (D3/A3)
constexpr uint8_t IR_RECEIVER_PIN = D4;        // Grove D4/A4 (D5/A5)
constexpr uint16_t LIGHT_OFF_THRESHOLD = 32;   // 10-bit ADC値。実環境で調整。
constexpr uint16_t SCHEDULED_OFF_THRESHOLD = 80;
constexpr uint8_t SCHEDULED_OFF_READ_COUNT = 5;
constexpr uint32_t SCHEDULED_OFF_READ_INTERVAL = 100;
constexpr uint32_t FEEDBACK_CHECK_DELAY = 2000;
constexpr uint8_t SCHEDULED_OFF_HOUR = 23;
constexpr uint8_t SCHEDULED_OFF_MINUTE = 30;
constexpr int32_t TIMEZONE_SECONDS = 9 * 3600;
constexpr char NTP_SERVER[] = "pool.ntp.org";
constexpr uint32_t PUBLISH_INTERVAL = 60000;
constexpr uint32_t RECONNECT_INTERVAL = 30000;
// credentials.hの接続設定を優先し、未定義の場合だけ既定値を使う。
#ifndef AIO_SERVER
#define AIO_SERVER "io.adafruit.com"
#endif
#ifndef AIO_SERVERPORT
#define AIO_SERVERPORT 1883
#endif
#ifndef SHIFTR_SERVER
#define SHIFTR_SERVER "public.cloud.shiftr.io"
#endif
#ifndef SHIFTR_SERVERPORT
#define SHIFTR_SERVERPORT 1883
#endif
#ifndef LIGHTING_SHIFTR_SERVER
#define LIGHTING_SHIFTR_SERVER "lighting.cloud.shiftr.io"
#endif
#ifndef LIGHTING_SHIFTR_SERVERPORT
#define LIGHTING_SHIFTR_SERVERPORT 1883
#endif
constexpr char WEATHER_TOPIC[] = "wio/json";
constexpr char LIGHTING_TOPIC[] = "lighting/json";
constexpr char LIGHTING_INPUT_TOPIC[] = "lighting/json/in";

// 波形と設置位置を送信テストで確認した後にtrueへ変更する。
constexpr bool ENABLE_SCHEDULED_IR = false;

// 学習済みのON/OFFトグル波形。OFF専用命令ではない。
constexpr uint16_t rawDataON_OFF[] = {
  8950, 4500,
  550, 1650, 550, 550, 550, 1650, 550, 550,
  550, 1650, 550, 1650, 550, 1700, 500, 600,
  550, 550, 550, 1650, 550, 550, 550, 550,
  550, 1650, 550, 550, 550, 550, 550, 600,
  500, 1700, 550, 1650, 550, 1650, 550, 550,
  550, 550, 550, 550, 550, 550, 550, 550,
  550, 1700, 550, 1650, 550, 550, 550, 550,
  550, 550, 550, 550, 550, 600, 500, 550, 600
};
constexpr size_t RAW_DATA_LENGTH = sizeof(rawDataON_OFF) / sizeof(rawDataON_OFF[0]);
static_assert(SCHEDULED_OFF_HOUR < 24 && SCHEDULED_OFF_MINUTE < 60, "Invalid schedule");
static_assert(SCHEDULED_OFF_READ_COUNT > 0, "At least one light sample is required");
