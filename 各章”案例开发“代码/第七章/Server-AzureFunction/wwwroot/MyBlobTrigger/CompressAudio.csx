#r "../bin/NAudio.dll"
using System;
using System.IO;
using NAudio;
using NAudio.Wave;
public static Stream CompressAudio(Stream myBlob)
{
    //读取音频流
    var reader = new WaveFileReader(myBlob);
    //设置压缩后的wav格式：采样频率8k，采样位数为8，单声道
    var newFormat = new WaveFormat(8000, 8, 1);
    //压缩音频流，存储在到WaveStream对象实例
    WaveStream waveStream = new WaveFormatConversionStream(newFormat, reader);
    //创建输出的Stream对象，并分配足够的内存空间
    Stream outputStream = new MemoryStream((int)waveStream.Length * 4);
    //将压缩后的音频流写入到outputStream中
    WaveFileWriter.WriteWavFileToStream(outputStream, waveStream);
    outputStream.Seek(0, SeekOrigin.Begin);
    return outputStream;
}