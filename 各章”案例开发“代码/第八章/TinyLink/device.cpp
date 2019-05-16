/*第一部分*/
REQUIRE("Raspberry pi");  
/*以树莓派为开发板*/  
TL_MQTT mqtt;   //声明MQTT客户端

/*MQTT Broker参数*/  
int port = xxxxx;  
char serverName[] = "xxxxxx";  
char clientName [] = "xxxxx";  
char pubTopic[] = "xxxxx";  
char subTopic[] = "xxxxx";  
char userName[] = "xxxxx";  
char passWord[] = "xxxxx";  
int Time = 0;  
int Count = 0;  
char buf[100];// MQTT消息缓存
 
/*第二部分*/
/*MQTT下行回调函数,根据消息内容点亮或者熄灭LED*/  
void messageArrived(MQTT::MessageData& md){   
    MQTT::Message &message = md.message;  
    char res[20];  
    strncpy(res, (char*)message.payload, 19);  
    if(strncmp(res, "LED_TURNON", strlen("LED_TURNON")) == 0){  
            TL_LED.turnOn();  
            delay(500);  
    }  
    else if(strncmp(res, "LED_TURNOFF", strlen("LED_TURNOFF")) == 0){  
            TL_LED.turnOff();  
            delay(500);  
    }  
}  

/*第三部分*/
/*初始化WiFi并建立连接并实例化MQTT客户端*/  
void setup(){  
    TL_WiFi.init();  
    TL_WiFi.join("SSID","Password");  
    mqtt = TL_WiFi.fetchMQTT();  
    mqtt.connect(serverName, port, clientName, userName,passWord);// MQTT客户端连接MQTT Broker   
    mqtt.subscribe(subTopic, messageArrived, 0);// 注册回调函数  
}  

/*第四部分*/
void loop(){            //主循环计时30秒，检测到人移动次数达到10次则判定座位上有人  
	Time++;   
    if(TL_PIR.read())   //红外PIR检测  
        Count++;        //检测到周围有人移动，计数加1     
    if(Time==30){  
        if(Count>=10){ 
            String data = "{\"pir\":1}";     //检测到人移动次数达到10，PIR节点置位1  
            data.toCharArray( buf,100 );  
        }
        else{
            String data = "{\"pir\":0}";     //检测到人移动次数达到10，PIR节点置位1  
            data.toCharArray( buf,100 );  
        }  
        mqtt.publish(pubTopic, buf, strlen(buf));   //MQTT客户端向Topic发布消息  
        Time= 0;
        Count= 0;  
    }  
    mqtt.yield(1000);   //等待mqtt下行消息 
}  