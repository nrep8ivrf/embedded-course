// ex07: Web网页无极调光器
#include <WiFi.h>
#include <WebServer.h>

// 替换成你自己的WiFi名称和密码
const char* ssid = "你的WiFi名称";
const char* password = "你的WiFi密码";

WebServer server(80);
const int ledPin = 2;  // LED接D2引脚
const int pwmChannel = 0;
const int pwmFreq = 5000;
const int pwmResolution = 8;

// 网页HTML代码
const char* html = R"HTML(
<!DOCTYPE html>
<html>
<head>
    <title>ESP32无极调光器</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body { text-align: center; font-family: Arial; margin-top: 50px; }
        .slider { width: 80%; height: 30px; }
        .value { font-size: 32px; margin-top: 30px; color: #2196F3; }
    </style>
</head>
<body>
    <h1>LED亮度调节</h1>
    <input type="range" min="0" max="255" value="0" class="slider" id="brightnessSlider">
    <div class="value">亮度: <span id="brightnessValue">0</span></div>

    <script>
        const slider = document.getElementById('brightnessSlider');
        const valueDisplay = document.getElementById('brightnessValue');
        
        // 监听滑动条变化
        slider.addEventListener('input', function() {
            const brightness = this.value;
            valueDisplay.textContent = brightness;
            // 发送请求给ESP32
            fetch(`/set?brightness=${brightness}`);
        });
    </script>
</body>
</html>
)HTML";

// 处理根目录请求，返回网页
void handleRoot() {
    server.send(200, "text/html", html);
}

// 处理亮度设置请求
void handleSetBrightness() {
    if (server.hasArg("brightness")) {
        int brightness = server.arg("brightness").toInt();
        brightness = constrain(brightness, 0, 255);  // 限制在0-255之间
        ledcWrite(pwmChannel, brightness);
        server.send(200, "text/plain", "OK");
    } else {
        server.send(400, "text/plain", "Bad Request");
    }
}

void setup() {
    Serial.begin(115200);
    
    // 初始化PWM
    ledcSetup(pwmChannel, pwmFreq, pwmResolution);
    ledcAttachPin(ledPin, pwmChannel);
    ledcWrite(pwmChannel, 0);  // 初始亮度0
    
    // 连接WiFi
    Serial.println("正在连接WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi连接成功！");
    Serial.print("IP地址: ");
    Serial.println(WiFi.localIP());
    
    // 注册网页路由
    server.on("/", handleRoot);
    server.on("/set", handleSetBrightness);
    server.begin();
    Serial.println("Web服务器已启动");
}

void loop() {
    server.handleClient();  // 处理客户端请求
}