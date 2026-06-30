const int tempPin = A0;
const int redLED = 8;
const int greenLED = 9;

void setup() {
  
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);


  Serial.begin(9600);

   Serial.println("Timestamp,Temp_C,Temp_F,Humidity");
}

void loop() {

  
  int sensorValue = analogRead(tempPin);

  
  float voltage = sensorValue * (5.0 / 1023.0);

  float tempC = (voltage - 0.5) * 100.0;
  float tempF = (tempC * 9.0 / 5.0) + 32.0;
  
  int humidity = random(55, 86);

  
  Serial.print(millis());
  Serial.print(",");

  Serial.print(tempC, 1);
  Serial.print(",");

  Serial.print(tempF, 1);
  Serial.print(",");

  Serial.println(humidity);

  
  if (tempC > 35 || humidity > 80) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
  }

  
  delay(2000);
}
