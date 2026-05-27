// ex02: 用millis()实现LED 1Hz闪烁（亮1秒，灭1秒）
const int ledPin = 2;         // LED接GPIO2
bool ledState = LOW;          // LED初始状态
unsigned long previousMillis = 0;  // 上一次状态改变的时间
const long interval = 1000;   // 闪烁间隔1000ms=1秒

void setup() {
  pinMode(ledPin, OUTPUT);    // 设置引脚为输出模式
}

void loop() {
  unsigned long currentMillis = millis(); // 获取当前运行时间

  // 当时间差超过间隔时，翻转LED状态
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // 更新上一次时间
    ledState = !ledState;            // 翻转状态
    digitalWrite(ledPin, ledState);  // 写入引脚
  }
}