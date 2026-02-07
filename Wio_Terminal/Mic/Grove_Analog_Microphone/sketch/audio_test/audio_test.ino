/**
 * Audio Microphone Test Sketch for Wio Terminal
 * Purpose: Diagnose microphone ADC reading and sensitivity
 * Grove Analog Microphone connected to A0 port
 */

#define AUDIO_PIN A0
#define SAMPLE_COUNT 128
#define SAMPLE_DELAY_US 5000  // 5ms between samples (~200 Hz)

uint16_t audioSamples[SAMPLE_COUNT];

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(AUDIO_PIN, INPUT);

  Serial.println("\n=== AUDIO MICROPHONE TEST ===");
  Serial.println("Connected to A0 port");
  Serial.print("Sample count: ");
  Serial.print(SAMPLE_COUNT);
  Serial.print(" | Interval: ");
  Serial.print(SAMPLE_DELAY_US);
  Serial.println(" µs");
  Serial.println("===========================\n");
}

void loop() {
  // Collect samples
  for (uint16_t i = 0; i < SAMPLE_COUNT; i++) {
    audioSamples[i] = analogRead(AUDIO_PIN);
    delayMicroseconds(SAMPLE_DELAY_US);
  }

  // Analyze samples
  uint16_t minVal = audioSamples[0];
  uint16_t maxVal = audioSamples[0];
  uint32_t sum = 0;

  for (uint16_t i = 0; i < SAMPLE_COUNT; i++) {
    if (audioSamples[i] < minVal) minVal = audioSamples[i];
    if (audioSamples[i] > maxVal) maxVal = audioSamples[i];
    sum += audioSamples[i];
  }

  uint16_t mean = sum / SAMPLE_COUNT;
  uint16_t peakToPeak = maxVal - minVal;

  // Calculate RMS for reference
  uint64_t sumSquared = 0;
  for (uint16_t i = 0; i < SAMPLE_COUNT; i++) {
    int16_t diff = audioSamples[i] - mean;
    sumSquared += (uint32_t)diff * diff;
  }
  uint32_t variance = sumSquared / SAMPLE_COUNT;
  uint16_t rms = sqrt(variance);

  // Output results
  Serial.print("[TEST] Min: ");
  Serial.print(minVal);
  Serial.print(" | Max: ");
  Serial.print(maxVal);
  Serial.print(" | Mean: ");
  Serial.print(mean);
  Serial.print(" | Peak-to-Peak: ");
  Serial.print(peakToPeak);
  Serial.print(" | RMS: ");
  Serial.println(rms);

  // Recommendations
  if (peakToPeak < 20) {
    Serial.println("  ⚠️  WARNING: Very low signal amplitude. Check microphone connection.");
  } else if (peakToPeak < 100) {
    Serial.println("  ⚠️  Low signal. Increase volume or check sensitivity.");
  } else if (peakToPeak > 500) {
    Serial.println("  ✅ Good signal amplitude!");
  }

  delay(1000);  // Wait 1 second before next cycle
}
