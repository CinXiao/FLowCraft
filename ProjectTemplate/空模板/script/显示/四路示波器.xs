chart1<<port1
chart2<<port2
chart3<<port3
chart4<<port4
按钮1被点击以后，清空图表1数据
IF button1
    GOTO:c
RETURN


c::
    CLEAR chart2
    CLEAR chart1
    CLEAR chart3
    CLEAR chart4