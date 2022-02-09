OBJ=myMinuit
CC=c++
ROOTCFLAGS=`root-config --cflags` -Wall -fPIC 

obj1=${OBJ}.o
obj2=${OBJ}Dict.o
DictCxx=${OBJ}Dict.cxx
HFile=${OBJ}.h
LinkDef=${OBJ}LinkDef.h
LIBO=lib${OBJ}.so


all: ${obj1} ${DictCxx} ${obj2} ${LIBO}
${obj1}: ${OBJ}.cxx
	${CC} -o $@ -c $^ ${ROOTCFLAGS}
${DictCxx}: ${HFile} ${LinkDef}
	rootcling -f $@ -c $^
${obj2}: ${DictCxx}
	${CC} -o $@ -c $^ ${ROOTCFLAGS}
${LIBO}:${obj1}  ${obj2}
	${CC} -shared -O2 -m64 $^ -o $@

.PHONY:all clean

clean:
	-rm -f *o *so ${DictCxx} *pcm
