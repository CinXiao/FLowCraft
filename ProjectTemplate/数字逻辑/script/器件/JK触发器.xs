IF switchbutton1
    GOTO:s
    GOTO:fd
RETURN

fd::
    IF switchbutton2
       GOTO:s
RETURN


s::
IF switchbutton1&&switchbutton2
    GOTO:JK11
IF switchbutton1
    GOTO:JK10
IF switchbutton2
    GOTO:JK01
RETURN


JK11::
  IF port1==1
        port2=0
   IF port1==0
        port2=1       
    RETURN

JK10::
        port2=1       
    RETURN

JK01::
    port2=0    
   RETURN
