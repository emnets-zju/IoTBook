

# 三星SmartThings

## 1 简介

**定义：** SmartThings成立于 2012 年，专注于制造智能家居设备。最初它仅仅是创始人Alex Hawkinson在众筹平台kickStarter上发起的一个项目。2014年SmartThings被三星公司收购，如今已经发展成为综合性一站式的智能家居平台。SmartThings可以通过统一的控制中心和官方app集中管理各种品牌和不同平台的物联网设备。除此之外，SmartThings允许第三方开发者在平台上创建自定义智能家居设备或应用。开发者可以根据不同的设备连接方式需求，灵活地使用平台支持的各类设备集成技术。SmartThings旨在所有物联网设备之间实现智能交互，从而推动物联网&quot;万物互联&quot;的发展。

<table><tr><td bgcolor=#dddddd>
<p align="center"><b>扩展阅读</b></p>
<p> 
SmartThings的起因是一次损失达$80,000的家庭事故。创始人Alex Hawkinson有一套建在山上的房子。2011年2月他和家人冬旅回来发现房子被水浸泡坏了，原因是停水的时候管道冻裂了，来水的时候水从墙体渗出，损坏了房子。他在外出期间对此一无所知，认为如果早早得知管道破裂，就可以安排勤杂工去修复它，这样就能避免损失。于是他开始寻找一种就算自己不在家也能监管房子的办法，他发现市场上竟然一款消费级传感器也没有，装一套专业传感设备又太贵。为了可以简单方便地监测自己家里的情况，他和他的团队用了几个月的时间做出来一个简易的传感工程机。后来，他们想和其他公司合作开发连接设备，这时候他们发现市场上没有以互联网为平台、利用云端和应用连接家居的连接设备。于是他们产生了一个更大的想法：为社区类发明和产品提供平台，SmartThings平台也就应运而生了。
</p>
</td></tr></table>

SmartThings还为开发者提供了一个项目交流分享的社区：SmartThings Community。在这个社区里，开发者可以分享他们自定义完成的设备、应用和服务，或者浏览其他社区人员创建的优秀项目。社区中还提供了许多交流论坛，包括设备论坛，服务论坛，项目论坛，移动应用论坛等。这些论坛可以使开发者们学习、分享和提升SmartThings物联网开发经验。

**基本框架：** SmartThings平台的整体架构如图1所示，主要包含：

<div align=center>
<img src=".\pics\pic1.png" width="80%">

图1 SmartThings平台架构
</div>

- 智能物联网设备：包含第三方厂商设备，三星设备以及各类独立的物联网设备。SmartThings平台为设备接入云端提供了三种连接方式，包括设备-SmartThings云连接，设备-第三方云-SmartThings云连接以及设备-控制中心- SmartThings云连接。开发者可以根据需求实现设备连接SmartThings云的方式；
- 服务（Service或SmartAPP）：用户自定义的服务程序，旨在SmartThings平台和物联网设备间建立连接得以控制和获取设备的状态，或辅助实现第三方云和SmartThings云的通信；
- SmartThings API：SmartThings平台提供的用于集成、控制、管理物联网设备和自定义服务的接口；
- SmartThings云：在物联网设备、服务和SmartThings app之间建立连接，实现数据交换的平台；
- SmartThings app：SmartThings平台为用户提供了一个官方的SmartThings app，用以集中管理各种物联网设备和服务；
- 开发者工作区（Developer Workspace）：平台提供的向SmartThings云中添加物联网设备和自定义服务的开发者工具。

**开发者工作区：** SmartThings平台为开发者提供了两种类型的开发工作区：一种是易于使用的图形化的网页控制台（Web Console），另一种是SmartThings SDK。

网页控制台是SmartThings平台提供的一个基于网页操作的集成开发环境。它支持设备、服务的图形化集成，并提供了设备插件（Plugin）模拟器和虚拟设备功能，使开发者能够用虚拟的移动应用界面和物联网设备测试其开发的服务或应用。网页控制台上还提供了消息日志（Logger），允许开发者跟踪和查询物联网设备的历史活动，方便用户的开发调试。

SmartThings SDK提供了类似于网页控制台的功能，支持设备和服务的集成。此SDK依附于Atom编辑器（GitHub上的开源项目）的IDE，并额外提供了一个命令行接口。和网页控制器一样，此SDK也提供了设备插件模拟器和虚拟设备功能。

**官方认证的物联网设备：** 截止2018年底，SmartThings官方支持且已认证的物联网设备共304款，涉及48个厂商，包括三星、亚马逊、谷歌等知名公司。SmartThings认证的设备涉及到十余种类别，详细分类如表1所示。


<div style="text-align:center">
<table style="margin:auto">
<caption>表1 SmartThings官方认证设备分类</caption>
<tr>
<th>类别</th>
<th>控制中心</th>
<th>集成平台</th>
<th>语音助手</th>
<th>灯&开关</th>
<th>插座</th>
<th>传感器</th>
<th>摄像头&门铃</th>
<th>门锁</th>
<th>温度调节装置</th>
<th>音响</th>
<th>其它</th>
</tr>
<tr>
<td>数量</td>
<td>9</td>
<td>8</td>
<td>8</td>
<td>105</td>
<td>39</td>
<td>43</td>
<td>11</td>
<td>40</td>
<td>9</td>
<td>14</td>
<td>18</td>
</tr>

</table>
</div>



## 2 关键特性

SmartThings采用基于设备模型的设备开发方式，提供了三种设备集成方式，支持大多数物联网设备与SmartThings云的连接。在服务开发方面，SmartThings采用基于生命周期的服务开发方式，每个周期阶段的分工明确，最大程度上保证了自定义服务与SmartThings平台的兼容性。在移动应用开发方面，SmartThings支持插件式移动应用开发。用户可以按需添加或删除物联网设备对应的插件。在三端应用集成与简化方面， SmartThings采取了基于设备档案的集成方案。

在本节中，我们将详细介绍SmartThings平台最具特点的关键特性，即其三种设备集成方式、基于生命周期的服务开发方式和插件式移动应用开发。

**(1)设备集成方式**

SmartThings为物联网设备提供了三种与SmartThings云连接的方式：设备-SmartThings云连接，设备-第三方云-SmartThings云连接以及设备-控制中心- SmartThings云连接。设备开发者在完成设备开发之后，还需要根据选择的连接方式添加SmartThings要求的额外配置，实现设备与云端的集成。由于SmartThings使用较为传统的设备开发方案，并且需要满足SmartThings平台的各项开发要求，其设备开发和集成步骤均较为复杂。下面我们将详细介绍SmartThings支持的三种设备连接方式：


<div align=center>
<img src=".\pics\pic1.png" width="80%">

图2 设备-SmartThings云连接的设备集成方案
</div>

若要使用设备-SmartThings云连接的集成方案（如图2），设备开发者需要预先申请安全认证，如X.509证书或ED25519公钥（一种常用的椭圆曲线签名方案），并将其存放在设备中。如果申请的是X.509证书，开发者需要存放X.509 证书的通用唯一识别码UUID。如果是ED25519公钥，开发者可以用SmartThings提供的API将其转换为设备签名。设备开发者还需要提供符合SmartThings要求的设备接口，并向SmartThings云提供一个URL用以接收和发送设备上的数据和命令。设备需要支持CoAP协议以实现与SmartThings云的通讯。除此之外，设备开发者还需要自主提供与SmartThings app配对的方案。SmartThings支持设备通过SmartThings云直接进行配对。对于成熟的第三方设备设计厂商，SmartThings还提供了基于遥控按钮和设备按钮的配对方案。用户可以通过厂商额外提供的遥控按钮或嵌入设备的匹配按钮，实现同一WiFi网络中的物联网设备和SmartThings app的配对。

<div align=center>
<img src=".\pics\pic1.png" width="80%">

图3 设备-第三方云-SmartThings云连接的设备集成方案
</div>

若要使用设备-第三方云-SmartThings云连接的集成方案（如图3），设备开发者需要自己实现一个连接器（Connector）服务完成云-云之间的通信和命令的解析，使设备能间接地与SmartThings云通信。下面用LIFX智能灯作为例子简单说明设备-第三方云- SmartThings云连接集成的工作流程：1.终端用户在app中点击打开LIFX智能灯的按钮。2. SmartThings云接收此开灯事件，生成携带第三方OAuth访问令牌的命令[11]，并发送到连接器服务。3. 连接器服务解析此命令，生成设备支持的&quot;on&quot;命令并将其传输到第三方的LIFX云。4. LIFX云发送&quot;on&quot;命令到LIFX智能灯将其开启。5. 智能灯的状态通过连接器返回SmartThings云，用户的SmartThings app界面得到更新，显示灯已打开。

<div align=center>
<img src=".\pics\pic1.png" width="80%">

图4 设备-控制中心- SmartThings云连接的设备集成方案
</div>

若要使用设备-控制中心- SmartThings云连接的集成方案（如图4），设备开发者需要在设备中嵌入ZigBee或Z-Wave通信协议，同时也需要自主开发SmartThings要求的设备接口，以及与控制中心配对的方案。在该模式下，物联网设备会先通过ZigBee或Z-Wave协议与控制中心连接，再由控制中心通过WiFi或以太网与SmartThings云进行通信。目前SmartThings支持的控制中心包括官方的SmartThings hub和三星的Samsung Connect Home hub系列控制中心。

**(2)基于生命周期的服务开发**

本节我们将详细介绍SmartThings平台要求开发者在自定义服务中实现的生命周期（Lifecycle），以及平台允许服务创建的订阅事件和调度事件。最后我们将简单介绍SmartThings支持的服务开发形式。

**①服务生命周期**

SmartThings平台要求服务开发者在服务中实现各个生命周期阶段（Lifecycle Phase）请求的处理程序。当服务被注册到SmartThings平台后，便会开始它的生命周期直至此服务被卸载。服务的生命周期需要包括7个生命周期阶段：PING（服务存在访问请求），CONFIGURATION（服务相关配置信息请求），INSTALL（服务安装请求），UPDATE（服务更新请求），EVENT（服务响应触发事件请求），OAUTH\_CALLBACK（服务访问第三方云请求），UNINSTALL（服务卸载请求）。服务在各个生命周期阶段均会被SmartThings云调用。反之，服务也可以调用SmartThings 平台的RESTful API发送和接收数据或命令[11]。SmartThings平台在服务的每个生命周期阶段向其发送一个POST请求，请求主体会包含某一生命周期阶段标识和依赖于此生命周期阶段的相关数据。服务要求能够解析并响应此请求。服务响应使用传统HTTP响应代码：2XX表示成功，4XX表示请求的输入错误，5XX表示SmartThings平台上的故障。服务的生命周期工作流程及每个生命周期阶段内SmartThings平台的请求内容如图5所示。


<div align=center>
<img src=".\pics\pic1.png" width="80%">

图5 服务的生命周期工作流程
</div>

- PING生命周期阶段：发生在服务在平台上注册后。在此阶段，SmartThings平台发送包含服务识别号的请求验证服务的存在性和完整性。服务需要返回一个200状态和包含服务识别号的pingData字段表示响应成功。
- CONFIGURATION生命周期阶段：发生在服务安装期间。在此阶段，SmartThings平台请求查询该服务的基本配置信息，以及需要访问的设备及其权限。其中还分为两个子阶段：INITIALIZE子阶段和PAGE子阶段。SmartThings平台在INITIALIZE子阶段请求查询服务对应的移动应用的初始化页面的配置信息，在PAGE子阶段请求查询移动应用中后续每个页面的配置信息，有多个页面则需多次查询。服务需要在各个子阶段返回其配置信息和需要的设备访问权限。
- INSTALL生命周期阶段：发生在服务安装完成时。在此阶段，SmartThings平台向服务发送移动应用的相关信息和访问令牌，以及授权的设备信息及相应权限。服务需要返回一个200状态和一个空的installData字段表示响应成功。服务在此阶段还可以在响应中向SmartThings平台请求添加事件订阅和事件调度。
- UPDATE生命周期阶段：发生在终端用户需要更新已经安装的服务的配置时。在此阶段，SmartThings平台向服务发送所有更新的和之前的设备信息及授权权限。如：如果要将服务监测的设备号从74aac3bb变为64aac3bb，需要在请求的config和previousConfig字段中分别添加&quot;deviceId&quot;：&quot;64aac3bb&quot;和&quot;deviceId&quot;：&quot;74aac3bb&quot;。服务需要返回一个200状态和一个空的updateData字段表示响应成功。服务在此阶段还可以请求更新已添加的事件订阅和事件调度。
- UNINSTALL生命周期阶段：发生在服务被终端用户卸载时。在此阶段，服务接收到平台请求后需要处理所有的清理任务。同时SmartThings平台会删除与此服务相关的事件订阅和事件调度。服务需要返回一个200状态和一个空的uninstallData字段表示响应成功。
- OAUTH\_CALLBACK生命周期阶段：发生在第三方云响应服务的OAuth认证请求时。在此阶段，SmartThings平台向服务发送一个包含第三方OAuth系统提供的授权码和访问令牌的URL。服务可以从中提取所需的令牌，使其有权访问第三方系统。服务需要返回一个200状态和一个空的oAuthCallbackData字段表示响应成功。
- EVENT生命周期阶段：发生订阅或调度事件被触发时。在此阶段，SmartThings平台向服务发送触发的订阅事件或调度事件的详细信息。如果是订阅事件，会声明响应的事件为设备事件（DEVICE\_EVENT）或功能事件（CAPABILITY\_EVENT）；如果是调度事件，会声明响应的事件为计时器事件（TIMER\_EVENT）。服务中需要包含处理这些事件的回调函数，并返回一个200状态和一个空的event字段表示响应成功。

**②事件订阅**

SmartThings平台要求连接的物联网设备在状态发生变化时能够上传其状态（此功能需要设备开发者自主开发）。当SmartThings云检测到状态变化后，便会在云端创建一个事件。服务可以在授权的设备上为指定的事件创建订阅（Subscription）。订阅的事件被触发时，服务将收到一个来自平台的POST请求，其中会包含触发事件的相关信息。服务需要根据此请求在EVENT阶段作出响应。例如，当服务订阅家里的智能冰箱门打开事件后，一旦用户在某一时刻打开了冰箱门，服务便会收到此状态变化的通知。

SmartThings提供了两种类型的订阅：设备订阅（Device subscription）和功能订阅（Capability subscription）。设备订阅指服务可以在用户选定的已授权的设备上创建的订阅。设备订阅指定订阅类型为DEVICE，并且需要在服务的JSON请求体中包含一个&quot;device&quot;对象声明订阅的设备的基本信息和具体事件，如：订阅客厅的灯打开事件。设备订阅的事件被触发后，SmartThings平台会向服务发送一个&quot;DEVICE\_EVENT&quot;的事件类型，其中包含订阅事件的详细信息。功能订阅指的是用户授权对所有设备订阅指定的事件。功能订阅指定订阅类型为CAPABILITY，并且需要在服务的JSON请求体中包含一个&quot;capability&quot;对象声明订阅的功能描述，如：订阅家里所有的灯打开事件，任意一盏灯打开都会向服务发送通知。功能订阅的事件被触发后，SmartThings平台会向服务发送一个&quot;CAPABILITY\_EVENT&quot;的事件类型及事件详细信息。

**③事件调度**

服务还可以在授权的设备上为指定的事件创建调度（Scheduling），使事件可以在指定时间或周期性地执行。与订阅类似，在调度事件触发（调度时间到达）后SmartThings平台会向服务发送一个包含调度信息的POST请求，并在其中声明触发的事件类型为&quot;TIMER\_EVENT&quot;。

SmartThings支持两种类型的调度：一次调度和周期性调度。一次调度指在指定的日期和时间执行一次调度事件，如：调度客厅灯在明天早上八点开启。一次调度的时间设置是从1970年1月1日UTC（Unix时间）开始计算的毫秒数。周期性调度会根据设定的Cron表达式周期性地执行事件，如：调度客厅灯在每天早上八点开启。SmartThings支持的Cron表达式用5或6个字段（年字段可选）表示时间。&quot;秒&quot;字段在SmartThings中省略，SmartThings平台会随机选取某一秒触发事件。具体Cron表达式设置方案参考表2。其中&quot;?&quot;字符：表示不确定的值，用于日和周字段是因为这两字段可能会相互冲突。例如想在每月的20日触发调度，那么需要在周字段设置问号；&quot;\*&quot;字符：表示匹配该域的任意值；&quot;,&quot;字符：同时指定多个值；&quot;-&quot;字符：指定一个值的范围；&quot;/&quot;字符：指定一个值的增加幅度。n/m表示从n开始，每次增加m；&quot;L&quot;字符：用在&quot;日&quot;字段表示一个月中的最后一天，用在&quot;周&quot;字段表示该月最后一个星期X。如6L在&quot;周&quot;字段表示最后的周五（一周从周日开始，1代表周日，7代表周六）；&quot;W&quot;字符：指定离给定日期最近的工作日(周一到周五)；&quot;C&quot;：字符：指定日期的后一天。 5C在日字段表示当月第六天，在&quot;周&quot;字段表示周五；&quot;#&quot;字符：表示该月第几个周X。6#3表示该月第3个周五。上述例子中灯在每天早上八点开启对应的Cron表达式为&quot;0 8 \* \* ? \*&quot;。下面再结合上述特殊字符给出一些Cron表达式的例子方便开发者理解：

- 0 2 1 \* ? \*：表示每月的1日的凌晨2点
- 0 10,14,16 \* \* ?：每天上午10点，下午2点，4点
- 0/30 9-17 \* \* ?：朝九晚五工作时间内每30分钟
- 15 10 ? 6L 2016-2018：表示16-18年的每个月的最后一个星期五上午10:15
- 15 10 C \* ?：第二天上午10:15
- 15 10 ? \* 6#3：每月的第三个星期五上午10:15
- 15 10 15W \* ?：离每月15日最近的工作日的上午10:15
- 15 10 LW \* ?：每月最后一个工作日的上午10:15

<div style="text-align:center">
<table style="margin:auto">
<caption>表2 SmartThings平台支持的Cron表达式结构</caption>
<tr>
<th>字段名</th>
<th>可取值</th>
<th>允许特殊字符</th>
</tr>
<tr>
<td>分</td>
<td>0-59</td>
<td>, - * /</td>
</tr>
<tr>
<td>时</td>
<td>0-23</td>
<td>, - * /</td>
</tr>
<tr>
<td>日</td>
<td>1-31</td>
<td>, - * ? / L W C</td>
</tr>
<tr>
<td>月</td>
<td>1-12 or JAN-DEC</td>
<td>, - * /</td>
</tr>
<tr>
<td>周</td>
<td>1-7 or SUN-SAT</td>
<td>, - * ? / L C #</td>
</tr>
<tr>
<td>年（可选字段）</td>
<td>empty, 1970-2099</td>
<td>, - * /</td>
</tr>
</table>
</div>

**④服务开发形式**

SmartThings支持两种形式的服务开发：WebHook形式和AWS Lambda函数形式。这两种形式的服务均需要开发者设计回调函数接收并分析来自SmartThings平台的HTTP POST请求。WebHook对应一个公网可以访问的HTTPS URL。服务开发者在此URL对应的服务器上保存服务代码（即事件触发后对应的自定义回调函数，能接收并处理来自SmartThings平台的HTTP POST请求）。基于WebHook形式的服务具有很高的自主性，SmartThings支持用任何语言和工具开发其服务代码。AWS Lambda函数也可以被用来开发SmartThings服务，它是亚马逊提供的一项计算服务，可使用户无需预配置或管理服务器即可部署、运行自定义回调函数。基于AWS Lambda函数的服务形式要求开发者先在AWS平台上部署已实现的回调函数，然后在AWS上授予SmartThings平台许可来执行该Lambda函数。随后开发者需要在AWS控制台的Lambda函数页面中，为此Lambda函数创建一个亚马逊资源名（Amazon Resource Names，ARN），并在SmartThings开发者工作区中填入上述ARN完成Lambda函数形式的服务注册。以上两种形式的服务均需要自定义回调函数接收并分析来自SmartThings平台的HTTP POST请求。

**(3)插件式移动应用开发**

SmartThings为不断增长的物联网设备提供了一套中央控制方案。具体来说，为了能不断添加新的物联网设备并且无需更新软件，SmartThings移动应用使用插件架构。用户可以在官方提供的SmartThings app主界面的基础上，根据匹配的物联网设备下载或添加设备插件。

插件是一个使用HTML、CSS、JavaScript和JSON设计的网页应用程序，并被打包成一个PPK（Plugin Package）文件嵌入SmartThings app中。在插件中开发者需要定义设备的移动应用界面及一些设备相关的交互行为。对于某一设备，用户既可以使用SmartThings平台提供的默认插件，也可以根据需求使用JavaScript API自己设计插件。图6展示了SmartThings插件平台（Plugin Platform）的软件框架。SmartThings app中固定了app的逻辑层、内核和初始的用户界面层，并提供了一个可修改的插件平台。用户可以在此插件平台上从官方的插件商店中下载和更新插件，也可以删除某一个设备对应的插件。这种增量式架构允许SmartThings app的原始空间占用保持在很小的范围内，而且即使在app编译和发布之后还能得到进一步扩展。例如：如果用户买了一个智能灯，那么他只需要去插件商店寻找合适的灯泡插件并下载下来，便可以将此智能灯集成到他的SmartThings app中了。


<div align=center>
<img src=".\pics\pic1.png" width="80%">

图6 SmartThings插件平台的软件框架
</div>

SmartThings app是用户管理和控制物联网设备的直接途径。基于插件的移动应用工作流程如图8-7所示：

<div align=center>
<img src=".\pics\pic1.png" width="80%">

图7 基于插件的移动应用工作流程
</div>

- **步骤1：** 开发者为物联网设备创建插件。该插件既可以是SmartThings平台提供的默认插件，也可以是开发者根据需求自己设计的插件。
- **步骤2：** 用户激活一个新设备。用户在SmartThings app中与附近的新物联网设备配对。
- **步骤3：** SmartThings app下载插件。如果SmartThings app检测到该物联网设备对应的插件还没有预加载或预装，那么它就会从云端的插件商店下载对应插件。
- **步骤4：** 用户控制设备。当插件安装好后，用户可以监视该物联网设备的状态，并可以通过插件向设备发送控制命令。
- **步骤5：** 设备响应命令。在物联网设备上都应有一个应用程序（设备开发者提供）用以处理来自插件的用户命令，并返回状态通知。

