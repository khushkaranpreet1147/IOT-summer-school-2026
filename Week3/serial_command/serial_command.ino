int blinkCounter = 0; 

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
    } else if (command.startsWith("BLINK_")) {
      int count = command.substring(6).toInt();
      if (count >= 1 && count <= 9) {
        for (int i = 0; i < count; i++) {
          digitalWrite(LED_BUILTIN, HIGH); delay(500);
          digitalWrite(LED_BUILTIN, LOW); delay(500);
        }
        blinkCounter += count; 
        Serial.print("Blinked "); Serial.print(count); Serial.println(" times");
      }
    } else if (command == "STATUS") {
      Serial.print("Total Blinks: "); Serial.println(blinkCounter);
      Serial.print("Current LED: "); Serial.println(digitalRead(LED_BUILTIN) ? "ON" : "OFF");
    } 
    
    else if (command == "RESET") {
      blinkCounter = 0;
      Serial.println("Blink counter reset to 0");
    } else {
      Serial.println("ERROR: Unknown command");
    }
  }
}

