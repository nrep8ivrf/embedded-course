// ex06: 警车双闪（单板载LED完美模拟版）
const int ledPin = 2;  // 板载蓝色LED

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // 模拟"红灯"快闪3次
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(80);   // 快闪间隔
    digitalWrite(ledPin, LOW);
    delay(80);
  }
  
  // 短暂停顿
  delay(150);
  
  // 模拟"蓝灯"慢闪3次
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(250);  // 慢闪间隔
    digitalWrite(ledPin, LOW);
    delay(250);
  }
  
  // 循环前停顿
  delay(300);
}