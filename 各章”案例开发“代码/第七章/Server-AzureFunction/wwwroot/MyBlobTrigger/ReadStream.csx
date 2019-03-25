public static byte[] ReadStream(Stream input)
{
    byte[] bytes = new byte[input.Length]; 
    input.Read(bytes, 0, bytes.Length); 
    // 设置当前流的位置为流的开始 
    input.Seek(0, SeekOrigin.Begin); 
    return bytes;
}