CC := arm-linux-gcc
SRC := $(wildcard Source/*.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
INC := Source/include 
INCC:= demo/ARM9_AT91SAM9XE_IAR
INCCC:=demo/Common/drivers/Atmel/at91lib/boards/at91sam9xe-ek
INC1 := Source/portable/GCC/ARM_CM3
.PHONY : all clean
all: $(OBJ)
	$(CC) -o $@ $^
%.o:%.c
	$(CC) -c $^ -o $@ -I$(INC) -I$(INCC) -I$(INCCC) -I$(INC1)
clean:
	rm -rf $(OBJ)
