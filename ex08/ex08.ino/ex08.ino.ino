// ex09: 实时触摸传感器仪表盘（iPhone热点专用版）
#include <WiFi.h>
#include <WebServer.h>

// 替换成你iPhone热点的名称和密码
const char* ssid = "你的iPhone热点名称";
const char* password = "你的热点密码";

WebServer server(80);
const int touchPin = T0;  // D4引脚（a15孔）

const char* html = R"HTML(
<!DOCTYPE html>
<html>
<head>
    <title>实时传感器仪表盘</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {
            text-align: center;
            font-family: Arial;
            margin-top: 100px;
            background-color: #f0f0f0;
        }
        .dashboard {
            background-color: white;
            padding: 60px;
            border-radius: 20px;
            box-shadow: 0 0 20px rgba(0,0,0,0.1);
            display: inline-block;
        }
        .value {
            font-size: 96px;
            font-weight: bold;
            color: #2196F3;
            margin-top: 30px;
        }
        .label {
            font-size: 28px;
            color: #666;
        }
    </style>
</head>
<body>
    <div class="dashboard">
        <div class="label">触摸传感器数值</div>
        <div class="value" id="sensorValue">0</div>
    </div>

    <script>
        // 每100毫秒自动更新一次数值
        setInterval(function() {
            fetch('/get')
                .then(response => response.text())
                .then(value => {
                    document.getElementById('sensorValue').textContent = value;
                });
        }, 100);
    </script>
</body>
</html>
)HTML";

void handleRoot() {
    server.send(200, "text/html", html);
}

// 返回当前触摸传感器的数值
void handleGetSensorValue() {
    int touchValue = touchRead(touchPin);
    server.send(200, "text/plain", String(touchValue));
}

void setup() {
    Serial.begin(115200);

    Serial.println("正在连接iPhone热点...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi连接成功！");
    Serial.print("IP地址: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/get", handleGetSensorValue);
    server.begin();
    Serial.println("Web服务器已启动");
}

void loop() {
    server.handleClient();
}