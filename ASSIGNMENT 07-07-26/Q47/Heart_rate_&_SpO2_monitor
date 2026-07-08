#include <Arduino.h>

#define LDR_PIN 34
#define LED_PIN 14

const int numReadings = 5;
int readings[numReadings];
int indexR = 0;
int total = 0;
int average = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  for (int i = 0; i < numReadings; i++) readings[i] = 0;
}

void loop() {

  int sensorValue = analogRead(LDR_PIN);

  // smoothing
  total -= readings[indexR];
  readings[indexR] = sensorValue;
  total += readings[indexR];
  indexR = (indexR + 1) % numReadings;
  average = total / numReadings;

  // WIDE mapping (fix)
  int heartRate = map(average, 0, 4095, 40, 140);
  int spo2 = map(average, 0, 4095, 88, 100);

  // ALERT logic (unchanged)
  bool alert = (heartRate < 50 || heartRate > 120 || spo2 < 94);

  digitalWrite(LED_PIN, alert ? HIGH : LOW);

  // DEBUG
Serial.println("--------------------------");
Serial.print("Heart Rate : ");
Serial.print(heartRate);
Serial.println(" bpm");

Serial.print("SpO2 : ");
Serial.print(spo2);
Serial.println(" %");

Serial.print("Alert : ");
Serial.println(alert ? "YES" : "NO");
Serial.println("--------------------------");
delay(2000);
}
