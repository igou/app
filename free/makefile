CC := arm-linux-gcc
DIR := Source demo
DIR := $(strip $(DIR))
SRC := $(foreach n,$(DIR),$(wildcard $(n)/*.c))
OBJ := $(patsubst %.c,%.o,$(SRC))
INC := Source/include  demo/ARM9_AT91SAM9XE_IAR  \
demo/common/drivers/Atmel/at91lib/boards/at91sam9xe-ek \
Source/portable/GCC/ARM_CM3
INCLUDE := $(foreach n,$(INC),-I$(n))
.PHONY : all clean
all: $(OBJ)
	echo "================================="
	echo "$(SRC)"
	echo "$(INCLUDE)"
	echo "================================="
	$(CC) -o $@ $^
%.o:%.c
	$(CC) -c -march=armv5  $^ -o $@  $(INCLUDE)
clean:
	rm -rf $(OBJ)
