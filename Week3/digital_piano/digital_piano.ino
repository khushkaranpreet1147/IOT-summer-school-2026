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
  
 void loop() {
  int pressedCount = 0;
  if (digitalRead(btnDo) == LOW) pressedCount++;
  if (digitalRead(btnRe) == LOW) pressedCount++;
  if (digitalRead(btnMi) == LOW) pressedCount++;
  if (digitalRead(btnFa) == LOW) pressedCount++;

  if (pressedCount >= 2) {
    tone(buzzerPin, 392); // Sol (Chord Substitute)
  } else if (digitalRead(btnDo) == LOW) {
    tone(buzzerPin, 262);
  } else if (digitalRead(btnRe) == LOW) {
    tone(buzzerPin, 294);
  } else if (digitalRead(btnMi) == LOW) {
    tone(buzzerPin, 330);
  } else if (digitalRead(btnFa) == LOW) {
    tone(buzzerPin, 349);
  } else {
    noTone(buzzerPin);
  }
}
  
  
