const int ledPin = 2;
const int touchPin = T0;
bool ledState = LOW;
int lastTouchState = 0;
const int debounceTime = 200;
unsigned long lastDebounceTime = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);
}

void loop() {
  int touchValue = touchRead(touchPin);
  int currentTouchState = (touchValue < 30) ? 1 : 0;

  if (currentTouchState == 1 && lastTouchState == 0) {
    if (millis() - lastDebounceTime > debounceTime) {
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
      lastDebounceTime = millis();
    }
  }
  lastTouchState = currentTouchState;
}