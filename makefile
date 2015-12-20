# single file 
Q :=@
PWD := $(shell pwd)
#PROJ := pipe  thread key input sort
PROJ := $(shell find $(PWD) -name "*.c")
PROJ := $(patsubst $(PWD)/%.c,%,$(PROJ))
APP := exe
OBJ := $(foreach n,$(PROJ),$(n).o)
OUT := output
.PHONY : all clean
all:$(OBJ) $(PROJ) 

pipe: pipe.o
	gcc -o $@ $@.o
thread: thread.o
	gcc -o $@ $@.o -lpthread
key: key.o
	gcc -o $@ $@.o
input:input.o
	gcc -o $@ $@.o
sort : sort.o
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
