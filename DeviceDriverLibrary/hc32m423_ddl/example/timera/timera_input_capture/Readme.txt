================================================================================
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
本样例展示Timera捕获功能。

说明：
本样例设置Timera为锯齿波、向上计数模式，Timera单元4的通道1、2开启捕获下降沿输入
及外部中断事件(SW1按键触发)功能，通道1捕获到P92输入下降沿则切换LED_R的状态，通
道2捕获到P93输入下降沿则切换LED_G的状态；SW1按下则同时切换LED_R和LED_G的状态。

================================================================================
测试环境
================================================================================
测试用板:
---------------------
EV_M423_LQ64_V10

辅助工具:
---------------------
杜邦线

辅助软件:
---------------------
无

================================================================================
使用步骤
================================================================================
1）打开工程并重新编译；
2）启动IDE的下载程序功能，关闭IDE下载界面；
3）通过跳线将引脚P92引脚拉低，则切换LED_R的状态；将P93引脚拉低，切换LED_G的状态；
4）按下SW1按键则同时切换LED_R、LED_G状态。

================================================================================
注意
================================================================================
无

================================================================================
