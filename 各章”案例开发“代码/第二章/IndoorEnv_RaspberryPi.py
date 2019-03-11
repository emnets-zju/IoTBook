import grovepi
import math
import time
sensor = 2                                        # DHT11数据接口和开发板2号引脚连接
blue = 0
while True:
  try:
    [temp,humidity] = grovepi.dht(sensor,blue)    # 读取温湿度
    if math.isnan(temp)==False and math.isnan(humidity)==False:
      print("temperature = %.02f C\nhumidity =%.02f%%"%(temp, humidity))
      time.sleep(3)                               # 每间隔3秒打印一次环境数据
  except IOError:
    print ("Error")
