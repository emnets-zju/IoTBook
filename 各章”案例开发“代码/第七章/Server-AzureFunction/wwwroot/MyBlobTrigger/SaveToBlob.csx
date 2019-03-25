#r "Microsoft.WindowsAzure.Storage"

using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.Blob;
	
// 连接字符串在步骤4（1）获取
static string storageConnectionString = "DefaultEndpointsProtocol=https;AccountName=audioprocessappbc45;AccountKey=3NmfrpdD7FpEk8oA0lKy0Jh5oPo6WwrTsAKtTlfU3EA7//GgWJN1losLcMPP/YHvNmabQUuybvBcqLQOp3pVAg==;EndpointSuffix=core.windows.net";                      
	
public static void SaveToBlob(Stream myBlob, string name, string containnerName)
{
    // 解析连接字符串并创建一个blob客户端与blob云端交互
    CloudStorageAccount storageAccount = CloudStorageAccount.Parse(storageConnectionString);
    CloudBlobClient blobClient = storageAccount.CreateCloudBlobClient();
    // 从blob云端获取容器
    CloudBlobContainer container = blobClient.GetContainerReference(containnerName);
    // 如果容器无法访问则创建它
    container.CreateIfNotExistsAsync();
    // 得到一个blob的引用
    CloudBlockBlob blob = container.GetBlockBlobReference(name);
    // 将文件上传到blob
    blob.UploadFromStreamAsync(myBlob);
}