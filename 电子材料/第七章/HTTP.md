# HTTP报文格式

## 1. 请求报文格式

HTTP的请求报文格式如图1所示，图2是对应格式的示例报文。请求报文由请求行、首部行和实体三部分组成，需要注意HTTP报文中的所有行都必须以“\r\n”（回车和换行）结尾。

<div align=center>
<img src=".\pics\http-1.png" width="50%">

图1 HTTP请求报文格式
</div>

①请求行：请求行包括请求方法、URL和HTTP版本。HTTP常用的请求方法见表1；URL（Uniform Resource Locator）是统一资源定位符，用来表示从因特网上得到资源的位置和访问这些资源的方法；HTTP版本目前可选HTTP/1.0或HTTP/1.1。例如图2中的示例，HTTP请求方法为POST，URL为http://tinylink.emnets.org/index.php，HTTP的版本为HTTP/1.1。

②首部行：首部行是控制字段，HTTP中长短连接、缓存和文本格式等都可以通过首部行来设置。例如图2中的示例，首部行设置请求为长连接（设置TCP层为长连接），设置请求的服务器主机地址为10.214.149.119。

③实体部分：HTTP请求报文的实体部分可携带数据内容，POST请求可能会将数据内容（如果本次请求携带内容的话）放入实体部分，GET请求的实体一般为空。

```
POST http://tinylink.emnets.org/index.php HTTP/1.1 \r\n
Connection:keep-alive \r\n
Host:10.214.149.119 \r\n
\r\n
-----------------------------178337587380872764801987301
Content-Disposition: form-data; name="upload"; filename="test.cpp"
…
```

图2 HTTP请求报文示例

表1 部分HTTP请求方法

| 请求方法 | 含义                                               |
|----------|----------------------------------------------------|
| GET      | 读取一个Web页面                                    |
| POST     | 当提交表单时需要用到POST，需要上传附加数据到服务器 |
| DELETE   | 请求服务器删除指定的页面                           |

## 2. 应答报文格式

HTTP的应答报文格式如图3所示，图4是对应格式的示例报文。应答报文由状态行、首部行和实体三部分组成，需要注意HTTP报文中的所有行都必须以“\r\n”（回车和换行）结尾。

①状态行：状态行包括HTTP版本、状态码和短语。HTTP版本目前可选HTTP/1.0或HTTP/1.1；HTTP的请求返回状态码见表2；HTTP短语对应一个状态码。例如图7-4中的示例，HTTP的版本为HTTP/1.1，HTTP状态码为200，对应的短语是OK，代表返回成功。

②首部行：首部行是控制字段，HTTP中长短连接、缓存和文本格式等都可以通过首部行来设置。例如图4中的示例，首部行设置请求为长连接（设置TCP层为长连接），“no-store, no-cache”设置缓存方式为对比缓存，意味着如果请求资源ID在浏览器数据库中存在，则直接使用本地缓存。

③实体部分：HTTP应答报文的实体部分携带返回的数据内容，可以是HTML文本，也可以是JSON。例如图4中的示例就是携带了一个HTML页面。

<div align=center>
<img src=".\pics\http-2.png" width="50%">

图3 HTTP应答报文格式
</div>

```
HTTP/1.1 200 OK \r\n
Cache-Control:no-store, no-cache \r\n
Connection:Keep-Alive \r\n
\r\n
<html lang="zh-CN" xmlns="http://www.w3.org/1999/xhtml">
…
```

图4 HTTP应答报文示例

表2 HTTP请求返回状态码

| 状态码 | 含义                                               |
|----------|----------------------------------------------------|
| 1xx      | 通知消息，如请求已收到或正在处理                                   |
| 2xx     | 成功 |
| 3xx   | 重定向，浏览器如要完成请求还需进一步行动                          |
| 4xx   | 浏览器请求错误，例如页面不存在或请求语法不正确                          |
| 5xx   | 服务器差错，服务器失效                          |

