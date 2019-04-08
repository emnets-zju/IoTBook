const aliyunIot = require('aliyun-iot-device-sdk');  
const Gpio = require('pigpio').Gpio;  
const device_id = 0;  
const gpio_pir = new Gpio(18, {  
    mode: Gpio.INPUT,  
});  
    
// 创建设备实例  
const device = aliyunIot.device({  
    // 激活凭证 这里替换成你自己上一步申请到的激活凭证  
    productKey: ‘xxx',  
    deviceName: ‘xxx',  
    deviceSecret: ‘xxx'  
});  

// 读取传感器数值  
function getMotionState = function() {      
    return gpio_pir.digitalRead();   
}  
// 上传数据  
function postProps() {  
    device.postProps({  
        deviceID: device_id,  
        motionState: getMotionState()  
    });  
    console.log('post');  
}  
// 定义定时器，周期上传数据  
var myInterval = setInterval(postProps, 10000);  
    
device.on('connect', () => {  
    console.log('connect successfully');  
});  
