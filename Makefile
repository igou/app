# single file 
Q :=@
source := $(wildcard *.c)  $(wildcard sub/*.c)
OBJ := $(patsubst %.c,%.o,$(source))
#code += sub
PROJ :=  pipe thread key input
APP := exe

OUT := output
.PHONY : all clean
all:$(OBJ) $(PROJ) install
pipe:
	gcc -o $@ $@.o
thread:
	gcc -o $@ $@.o -lpthread
key:
	gcc -o $@ $@.o
input:
	gcc -o $@ $@.o

%.o : %.c
	gcc -c $^ -o $@ 
install:
ifeq ($(OUT),$(wildcard $(OUT))) #ifeq ()  note:ifeq后面要有空格
	$(Q)echo "------file$(OUT) exist"
	$(Q)mv $(PROJ) $(OUT)
else
	$(Q)echo "------file $(OUT) NOT exist"
	$(Q)mkdir $(OUT)
	$(Q)mv $(PROJ) $(OUT)
endif
#.c.o:
#	gcc -c $<  # xx.o depend on xx.c文件在同一个目录下
clean:
	#rm -rf $(OUT)/$(PROJ) 
	rm -rf $(OUT)
	rm -rf $(OBJ)
