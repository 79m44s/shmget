SRC = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRC) )  #将所有后缀为.c的字符串变为.o结尾

all:$(OBJS)

.PHONY:all
shmr.o:shmr.c
	gcc shmr.c -o shmr.o
shmw.o:shmw.c
	gcc shmw.c -o shmw.o
shmc.o:shmc.c
	gcc shmc.c -o shmc.o
	
.PHONY:clean
clean:
	-rm *.o

