const int redLED=2;
const int redLED=3;
const int redLED=4;
const int redLED=7;
void setup() {
  
 pinMode(redLED, OUTPUT);
 pinMode(yellowLED, OUTPUT);
   pinMode(greenLED, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
 
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Pedestrian button pressed! Red light.");
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    Serial.print("Time: "); Serial.println(millis());
    delay(8000); 
    } 
  else 
  {
   digitalWrite(redLED, HIGH); digitalWrite(yellowLED, LOW); digitalWrite(greenLED, LOW);
    Serial.println("State: RED"); Serial.println(millis());
    delay(5000);
    
   
    digitalWrite(redLED, LOW); digitalWrite(yellowLED, HIGH); digitalWrite(greenLED, LOW);
    Serial.println("State: YELLOW"); Serial.println(millis());
    delay(2000);
    
    
    digitalWrite(redLED, LOW); digitalWrite(yellowLED, LOW); digitalWrite(greenLED, HIGH);
    Serial.println("State: GREEN"); Serial.println(millis());
    delay(4000);
  }
}
