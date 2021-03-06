﻿================================================================================
                                样例使用说明
================================================================================
版本历史
日期        版本    负责人     IAR     MDK     GCC     描述
2020-09-15  1.0     CDT        7.70    5.16    8.3.1   first version
================================================================================
平台说明
================================================================================
GCC工程，由Eclipse IDE外挂GNU-ARM Toolchain，再结合pyOCD GDB Server实现工程的编译、
链接和调试。在用Eclipse导入工程后，请将xxxx_PyOCDDebug中pyocd-gdbserver和SVD文件
设置为正确的路径；请将xxxx_PyOCDDownload中pyocd设置为正确的路径。注意，这些路径不
能包含非英文字符。

================================================================================
功能描述
================================================================================
本例程以ADC的序列A和DAM单元的通道0为例，实现了通过DMA读取ADC数据。例程实现原理：Pa4的下
降沿触发ADC的序列A扫描，序列A扫描结束后，产生事件“EVT_ADC_EOCA”，该事件触发DMA的通道0
从指定的ADC数据寄存器地址（源地址）读取指定长度的数据到指定的目标地址，如此重复。

说明：
本例程中，DAM的块大小（block size）必须覆盖从最小通道编号到最大通道编号的所有同道，因为
DMA每读取一个数据后，数据指针加1，指向下一个需要读取的数据地址。程中选用的ADC通道为ADC_CH2、
ADC_CH3和ADC_CH5，那么DMA的块大小须设置为不小于4，同样地，用于保存ADC数据的数组的大小，
也应不小于4。

================================================================================
测试环境
================================================================================
测试用板:
---------------------
EV_M423_LQ64_V10

辅助工具:
---------------------
USB转串口工具

辅助软件:
---------------------
串口调试助手软件（115200bps，8N1）

================================================================================
使用步骤
================================================================================
1）如果需要用在上位机观察ADC值，请将USB转串口工具正确地与开发板上的UART3端口连接；如果
   不需要，请忽略此步骤；
2）打开工程并重新编译；
3）启动IDE的下载和调试功能；
4）全速运行程序或在需要的位置设置断点；
5）在PE7上制造一个下降沿，触发序列A扫描。

================================================================================
注意
================================================================================
无

================================================================================
