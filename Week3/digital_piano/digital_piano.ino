const int btnDo = 2;
const int btnRe = 3;
const int btnMi = 4;
const int btnFa = 5;
const int buzzerPin = 8;

void setup() {
  pinMode(btnDo, INPUT_PULLUP);
  pinMode(btnRe, INPUT_PULLUP);
  pinMode(btnMi, INPUT_PULLUP);
  pinMode(btnFa, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  
  if (digitalRead(btnDo) == LOW) {
    tone(buzzerPin, 262); // Do
  } else if (digitalRead(btnRe) == LOW) {
    tone(buzzerPin, 294); // Re
  } else if (digitalRead(btnMi) == LOW) {
    tone(buzzerPin, 330); // Mi
  } else if (digitalRead(btnFa) == LOW) {
    tone(buzzerPin, 349); // Fa
  } else {
    noTone(buzzerPin);
  }
}
  
  
