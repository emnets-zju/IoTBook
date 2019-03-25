using System.Net.Http.Headers;

public static string AnalyzeAudio(byte[] audio) 
{
    var client = new HttpClient();
    // 连接uri在步骤6（1）中获取
    var uri = "https://southeastasia.stt.speech.microsoft.com/speech/recognition/conversation/cognitiveservices/v1?language=en-US";
    // 连接秘钥在步骤6（1）中获取
    client.DefaultRequestHeaders.Add("Ocp-Apim-Subscription-Key", "df5c164a42594cae83e338d7c596384e"); 
    HttpResponseMessage response;
    using (var content = new ByteArrayContent(audio)) 
    {
        content.Headers.ContentType = new MediaTypeHeaderValue("application/octet-stream");
        response = client.PostAsync(uri, content).Result;
        string audioInfo = response.Content.ReadAsStringAsync().Result;
        return audioInfo;
    }
}