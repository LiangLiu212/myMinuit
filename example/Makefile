OBJ=myMinuit
CC=g++
ROOTCFLAGS=`root-config --cflags` -Wall -fPIC  `root-config --libs` -lMinuit -lmyMinuit  -I /Users/liang/Documents/root/myMinuit -L /Users/liang/Documents/root/myMinuit/

obj1=${OBJ}.o
HFile=${OBJ}.h


all: main 
main: Ifit.C 
	${CC} -o $@  $^ ${ROOTCFLAGS}

.PHONY:all clean 

clean:
	-rm -f *o main

