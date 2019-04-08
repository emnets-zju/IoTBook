TL_MQTT mqtt;  
// 设置MQTT参数  
int port = 1883;  
char serverName[]= "pk.iot-as-mqtt.cn-shanghai.aliyuncs.com";  
char clientName[] = "12345|securemode=3,signmethod=hmacsha1,timestamp=789|";  
char userName[] = "device&pk";  
char password[] = "FAFD82A3D602B37FB0FA8B7892F24A477F851A14";  
char propertyPostTopic[] = "/sys/pk/device/thing/event/property/post";  
    
unsigned int messageID = 0;    // 消息ID， 自增  
unsigned int deviceID = 0;        // deviceID，默认为0   
    
void setup() {  
    TL_Serial.begin(9600);  
    TL_WiFi.init();                        // 连接WiFi  
    bool wifi_conn = TL_WiFi.join("EmNets-301", "eagle402");  
    mqtt = TL_WiFi.fetchMQTT();          // 连接MQTT  
    int mqtt_conn = mqtt.connect(serverName, port, clientName, userName, password);     
}  
void loop() {  
    int motionState = TL_PIR.read();        // 读取传感器数据  
    char buf[150];  
    String payload = “{\”id\“:\”“;                  // 根据物模型，构造数据包  
    payload += messageID;  
    payload += "\"";  
    payload += ",\"version\":\"1.0\"";  
    payload += ",\"params\":{\"deviceID\":";  
    payload += deviceID;  
    payload += ",\"motionState\":";  
    payload += motionState;  
    payload += "},\"method\":\"thing.event.property.post\"}";  
    int payloadlength = payload.length();  
    payload.toCharArray( buf, 150 );  
    mqtt.publish(propertyPostTopic, buf, payloadlength);  // 数据包发送到指定Topic  
    messageID++;  
    TL_Serial.println(buf);  
    mqtt.yield(4000);  
}  