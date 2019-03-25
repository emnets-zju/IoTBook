package org.emnets.voicecontroller;

import android.util.Log;

import com.microsoft.azure.storage.CloudStorageAccount;
import com.microsoft.azure.storage.OperationContext;
import com.microsoft.azure.storage.StorageException;
import com.microsoft.azure.storage.blob.BlobContainerPublicAccessType;
import com.microsoft.azure.storage.blob.BlobRequestOptions;
import com.microsoft.azure.storage.blob.CloudBlobClient;
import com.microsoft.azure.storage.blob.CloudBlobContainer;
import com.microsoft.azure.storage.blob.CloudBlockBlob;
import com.microsoft.azure.storage.blob.ListBlobItem;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.channels.FileChannel;
import java.security.InvalidKeyException;

/**
 * Created by Administrator on 2019/1/6.
 */

public class AudioSender extends Thread {

    public String TAG = "AudioController";
    public static final String storageConnectionString =
            "DefaultEndpointsProtocol=https;" +
                    "AccountName=audioprocess973b;" +
                    "AccountKey=UvQFqC77bX6V5RG9uYx4G1NT+lfvd3oqIpsRmD2yok5ILksBLexaO3ZBAmvsKOgzP4F2f3oxaMFa1+WuXCQA1w==;" +
                    "EndpointSuffix=core.windows.net";
    private String tempFilePath = null;
    private File tempFile = null;

    public AudioSender(String oriFilePath) {
        tempFilePath = oriFilePath.substring(0, oriFilePath.length() - 4) + "-" + System.currentTimeMillis() + ".wav";
        copyFile(oriFilePath);
        tempFile = new File(tempFilePath);
    }

    private void copyFile(String oriFilePath) {
        FileChannel input = null;
        FileChannel output = null;

        try {
            input = new FileInputStream(oriFilePath).getChannel();
            output = new FileOutputStream(tempFilePath).getChannel();
            output.transferFrom(input, 0, input.size());
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (input != null) {
                    input.close();
                }
                if (output != null) {
                    output.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void run() {
        try {
            // 解析连接字符串并创建一个blob客户端与blob云端交互
            CloudStorageAccount storageAccount = CloudStorageAccount.parse(storageConnectionString);
            CloudBlobClient blobClient = storageAccount.createCloudBlobClient();

            // 从blob云端获取容器
            CloudBlobContainer container = blobClient.getContainerReference("audios");

            // 如果容器无法访问则创建它
            container.createIfNotExists(BlobContainerPublicAccessType.CONTAINER, new BlobRequestOptions(), new OperationContext());

            // 得到一个blob的引用
            CloudBlockBlob blob = container.getBlockBlobReference(tempFile.getName());

            // 将文件上传到blob
            Log.e(TAG, "上传文件");
            blob.uploadFromFile(tempFile.getAbsolutePath());

            // 列出容器中所有的内容
            for (ListBlobItem blobItem : container.listBlobs()) {
                Log.e(TAG, "blob的URI是: " + blobItem.getUri());
            }
        } catch (URISyntaxException e) {
            Log.e(TAG, e.getMessage());
        } catch (InvalidKeyException e) {
            Log.e(TAG, e.getMessage());
        } catch (StorageException e) {
            Log.e(TAG, e.getMessage());
        } catch (IOException e) {
            Log.e(TAG, e.getMessage());
        } finally {
            tempFile.delete();
        }
    }
}
