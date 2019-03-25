#r "Newtonsoft.Json"
#load "AnalyzeAudio.csx"
#load "ReadStream.csx"
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
#load "SendCloudToDeviceMessageAsync.csx"
#load "CompressAudio.csx"
#load "SaveToBlob.csx"

public static void Run(Stream myBlob, string name, ILogger log)
{
    //获取流的byte数组
    byte[] audio = ReadStream(myBlob);
    //分析语音，得到命令
    string audioInfo = AnalyzeAudio(audio);
    log.LogInformation(audioInfo);
    JObject jo = (JObject)JsonConvert.DeserializeObject(audioInfo);
    string command = jo["DisplayText"].ToString();

    //根据语音识别结果设置指令msg
    string msg = "";
    if (command == "Open.") msg = "open";
    else if (command == "Close.") msg = "close";
    else msg = "others";
    SendCloudToDeviceMessageAsync(msg).Wait();//向设备发送指令msg

    Stream compressStream = CompressAudio(myBlob); //压缩音频流
    //存储进“Command-***”容器
    //msg是根据语音识别结果设定的命令指令（open/close/others）
    log.LogInformation("上传文件到" + "command-" + msg);
    SaveToBlob(compressStream, name, "command-" + msg);
    
}
