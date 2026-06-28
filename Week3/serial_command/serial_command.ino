void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("System Ready. Waiting for commands...");
}

void loop() {
  
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();

    if (command == "LED_ON") {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("LED is ON");
    } else if (command == "LED_OFF") {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("LED is OFF");
    }
  }
}
}

