s=""
IF button1
    s="1"
IF button2
    s="2"
IF button3
    s="3"
IF button4
    s="4"
IF button5
    s="5"
IF button6
    s="6"
IF button7
    s="7"
IF button8
    s="8"
IF button9
    s="9"
IF button10
    s="0"
IF button11
    s="+"
IF button12
    s="-"
IF button13
    s="*"
IF button14
    s="÷"
IF button15
    s="="
IF button16
    s="."

flag::
    port1=port1+s
    RETURN