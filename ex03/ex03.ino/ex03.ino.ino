const int ledPin = 2;
const int shortBlink = 200;
const int longBlink = 600;
const int gap = 200;
const int sosGap = 2000;

int sequence[] = {shortBlink, gap, shortBlink, gap, shortBlink, gap*2,
                  longBlink, gap, longBlink, gap, longBlink, gap*2,
                  shortBlink, gap, shortBlink, gap, shortBlink, sosGap};
int sequenceLength = sizeof(sequence)/sizeof(sequence[0]);
int currentStep = 0;
unsigned long previousMillis = 0;
bool ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= sequence[currentStep]) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
    currentStep++;
    if (currentStep >= sequenceLength) currentStep = 0;
  }
}