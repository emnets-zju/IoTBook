#r "../bin/Microsoft.Azure.Devices.dll"
using System.Text;
using Microsoft.Azure.Devices;
static string connectionString = "HostName=IoTBook.azure-devices.net;SharedAccessKeyName=iothubowner;SharedAccessKey=WyWj4BMjrEGZlRkVtCFa628pUzZObisjVhpmsSufWiY=";
public async static Task SendCloudToDeviceMessageAsync(string msg)
{
    //创建cloud->device消息服务客户端
    ServiceClient serviceClient = ServiceClient.CreateFromConnectionString(connectionString);
    //创建消息对象实例，封装msg指令
    var commandMessage = new Message(Encoding.ASCII.GetBytes(msg));
    //服务客户端发送消息到设备LED
    await serviceClient.SendAsync("LED", commandMessage);	
}