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
本样例展示ICG模块中NMI功能。

说明：
本样例配置硬件NMI引脚下降沿触发中断，通过按键SW3输入信号，每检测到一个有效的下降
沿则切换一次LED_R的亮灭状态。

================================================================================
测试环境
================================================================================
测试用板:
---------------------
EV_M423_LQ64_V10

辅助工具:
---------------------
无

辅助软件:
---------------------
无

================================================================================
使用步骤
================================================================================
1）打开工程并参照mian()函数中的描述去修改hc32m423_icg.h文件中宏定义的值；
2）重新编译工程，启动IDE的下载程序功能，关闭IDE下载界面；
3）按下按键SW3，LED_R切换当前的亮灭状态。

================================================================================
注意
================================================================================
无

================================================================================
