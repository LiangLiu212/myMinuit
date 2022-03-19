OBJ=blindMinuit
CC=g++
ROOTCFLAGS=`root-config --cflags` -Wall -fPIC  `root-config --libs` -lMinuit

obj1=${OBJ}.o
HFile=${OBJ}.h


all: main ${obj1}
main: main.cxx ${obj1}
	${CC} -o $@  $^ ${ROOTCFLAGS}
${obj1}: ${OBJ}.cxx
	${CC} -o $@ -c $^ ${ROOTCFLAGS}

.PHONY:all clean 

clean:
	-rm -f *o main

