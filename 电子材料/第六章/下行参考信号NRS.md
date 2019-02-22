# 下行参考信号NRS

在用于广播和下行传输信道（NPBCH/NPDCCH/NPDSCH）时，无论有没有数据传输，所有下行子帧（除了传输NPSS和NSSS的子帧之外）都要传输NRS。在三种不同部署方式下，NRS资源映射示意图如图6-1所示。

从NRS下行参考信号资源映射图中，可以看出：

- 不同的部署方式下，NRS资源映射其实是一样的，只是在带内部署方式下，多了LTE CRS（Cell-specific Reference Signal，小区专有参考信号）。
- NRS支持1个或2个天线端口，映射到一个slot的最后2个符号上（即第6和第7个符号上）。
- NRS资源映射的位置在时间上与LTE CRS错开，在频率上则与LTE CRS的频域位置相同。

<div align=center>
<img src=".\pics\pic1.png" width="50%">

图6-1 NRS资源映射示意图
</div>
