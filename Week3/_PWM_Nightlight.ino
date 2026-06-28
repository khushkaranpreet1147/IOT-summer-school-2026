const int ledPin = 9;
const int buttonPin = 2;
int currentMode = 0; 

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("System Initialized: Mode 0 (Slow Breathing)");
}

void loop() {

}
