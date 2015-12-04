
SRC := $(wildcard *.c)  $(wildcard sub/*.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
OUTPUT:= exe

all : $(OBJ)
	gcc  -o $(OUTPUT)  $^

%.o : %.c
	gcc -c $^  -o $@
.PHONY:clean 
# .PHONY==>it work,if there file clean existed
clean:
	rm -f $(OBJ)  $(OUTPUT) 
