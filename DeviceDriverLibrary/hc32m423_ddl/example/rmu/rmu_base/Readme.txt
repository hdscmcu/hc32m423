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


功能描述
================================================================================
1）读取复位信息，并通过串口发送；
2）制造一些可通过软件实现的复位,本样例实现了看门狗复位、外部高速振荡器异常停振
   复位、软件复位和LVD复位的样例。

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
串口调试助手(115200bps,8N1)

================================================================================
使用步骤
================================================================================
1）打开工程。
2）在main.c文件中修改对TEST_RESET_MODE的宏定义选择测试的复位功能，并重新编译；
3）下载程序到目标板，用串口调试助手波特率设置为115200，查看复位信息。
4）串口显示“Press SW1 to config reset condition .”时，短按按键SW1使能当前测试复位
   功能。
5）根据串口调试信息查看本次复位情况。


================================================================================
注意
================================================================================


================================================================================
