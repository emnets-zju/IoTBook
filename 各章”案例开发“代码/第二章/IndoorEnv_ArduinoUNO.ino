#include "DHT.h"
DHT dht(2, DHT11);                   // DHT11的数据引脚连接开发板2号引脚
void setup() {                       // 程序初始化代码，执行一次
  Serial.begin(9600);                // 串口打印波特率为9600 Bd/s
  dht.begin();                       // 初始化DHT11模块
}
void loop() {  
  float h = dht.readHumidity();      // 读湿度数据
  float t = dht.readTemperature();   // 读温度数据
  Serial.print("Humidity: ");
  Serial.println(h);                 // 打印湿度
  Serial.print("Temperature: ");
  Serial.println(t);                 // 打印温度
  delay(3000);                       // 每间隔3秒打印一次环境数据
}
