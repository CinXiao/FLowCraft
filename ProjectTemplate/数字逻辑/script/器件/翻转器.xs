IF switchbutton1
    GOTO:flag

    port2=port1
    RETURN
flag::
    IF port1==0
        GOTO:f0
        GOTO:f1


f0::
   port2=1
    RETURN

f1::
   port2=0
    RETURN