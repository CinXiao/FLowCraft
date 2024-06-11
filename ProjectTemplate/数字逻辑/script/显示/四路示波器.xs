
InsertValue(chart1,port1)
InsertValue(chart2,port2)
InsertValue(chart3,port3)
InsertValue(chart4,port4)
按钮1被点击以后，清空图表1数据
IF button1
    GOTO:c
RETURN


c::
    Clear(chart2,chart1,chart3,chart4)