TARGET=main
CC=g++
OBJS=Ifit.o
ROOTCFLAGS=`root-config --cflags` -Wall -fPIC  `root-config --libs` -lMinuit -lblindMinuit \
	   -I /home/liang/data/software/myMinuit \
	   -L /home/liang/data/software/myMinuit
CFLAGS ="-march=broadwell -O3 -pipe"

.SUFFIXES   : .o .C
.SUFFIXES   : .o .cc
.SUFFIXES   : .o .cxx


.C.o : 
	${CC} $(FFLAGS) ${ROOTCFLAGS} -c $<

all: $(OBJS)
	${CC} ${ROOTCFLAGS} $(CFLAGS)  -o $(TARGET) $(OBJS)

.PHONY:all clean 

clean:
	-rm -f  main

