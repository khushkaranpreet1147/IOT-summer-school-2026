#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); 

const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;

void setup() {
  
  Serial.begin(9600);
  
  BTSerial.begin(9600); 
  
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  

  allOff();
  Serial.println("Bluetooth Controller Ready. Pair your device.");
}

void loop() {
  
  if (BTSerial.available() > 0) {
    char command = BTSerial.read();
    Serial.print("Received Command: ");
    Serial.println(command);

    switch (command) {
      case 'R':
        digitalWrite(redPin, HIGH);
        break;
      case 'G':
        digitalWrite(greenPin, HIGH);
        break;
      case 'B':
        digitalWrite(bluePin, HIGH);
        break;
      case 'X':
        allOff();
        break;
      case 'F':
        flashLEDs();
        break;
      default:
        
        break;
    }
  }
}

void allOff() {
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
}

void flashLEDs() {
  allOff();
  for (int i = 0; i < 5; i++) {
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
    delay(300);
    allOff();
    delay(300);
  }
}
