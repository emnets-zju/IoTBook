TL_MQTT mqtt;
int port = 12353;              // MQTT 端口号
char serverName[]= "tinylink.cn";            // MQTT Broker地址
char clientName[] = "78d3773a00f017238a5d989e8f0cd5d2be13f640";             // MQTT 设备名称
char topicName[] = "78d3773a00f017238a5d989e8f0cd5d2be13f640/event";           // MQTT Topic 名称
char userName[] = "Demos";              // MQTT设备ID
char password[] = "TinyLinkDemos";       // MQTT设备认证信息
const int SAMPLES_COUNT = 20, STR_MAX = 128;
int counter = 0;
float buffer[SAMPLES_COUNT]; 
char str_buffer[STR_MAX]; 

void readData() {
    TL_Accelerometer.read();       //获取加速度传感器X轴数据并记录
    buffer[counter] = TL_Accelerometer.data_x();
    counter++;
    TL_Buzzer.turnOff();
    if (counter >= 20) {
        counter = 0;
        float avg = 0, sum = 0, var = 0, diff = 0;
        for (int i = 0; i < SAMPLES_COUNT; i++) {       
            sum += buffer[i];     // 计算数据和
        }
        avg = sum / SAMPLES_COUNT;
        for (int i = 0; i < SAMPLES_COUNT; i++) {         
            diff = buffer[i] - avg;     
            var += diff * diff;// 计算方差
        }
        if (var > 1) {  // 发现节点被盗
            TL_LED.turnOn();
            TL_Buzzer.turnOn();
            sendMQTTMessage("\"Stolen\"");
            TL_Serial.println("Node is stolen.\nA notification is sent.");
        }
    }
}

int sendMQTTMessage(String msg) {   // 发布MQTT消息
    String data = String("{\"Ev\":") + msg + String("}");
    data.toCharArray(str_buffer, STR_MAX);
    TL_Serial.println("Publishes data:" + String(str_buffer));
    return mqtt.publish(topicName, str_buffer, strlen(str_buffer));
}

void setup() {
    TL_Serial.begin(9600);
    TL_Serial.println("Program starts");
    pinMode(2, OUTPUT);
    TL_WiFi.init();
    TL_WiFi.join("onelink","onelinktest");      // 连接WiFi
    TL_Serial.println("Joins WiFi");
    mqtt = TL_WiFi.fetchMQTT();
    mqtt.connect(serverName, port, clientName, userName, password); // 连接Broker
    TL_Serial.println("Connects MQTT");         // 连接MQTT
    sendMQTTMessage("\"Steady\"");
}

void loop() {
    readData();
    TL_Time.delayMillis(100);
}