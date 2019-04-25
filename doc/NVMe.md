***Directive***

**CMD**    

    DTYPE field 
        00h (Directives not in use) Field not us
        01h (Streams)        ;Spec 1.3，I/O command中只有write才支持directive
        02h – 0Fh Reserved

    Directive Specific (DSPEC) field includes additional information for the 
        associated I/O command 

**identify**

    Optional Admin Command Support (OACS) field Identify Controller data structure
    1,Return Parameters operation of the Identify Directive (Directive Receive)
    2,Enable operation of the Identify Directive （Directive Send）

**stream**