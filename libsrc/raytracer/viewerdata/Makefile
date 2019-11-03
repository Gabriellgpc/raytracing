BASEDIR	=	../../..

CC = g++
CXX = g++
CPPFLAGS = -Wall -O2 -I ${BASEDIR}/include
LDFLAGS = -L ${BASEDIR}/lib
LDLIBS = -lGL	-lGLU	-lGLUT -lutils

all:	test

test:	test.cpp viewerdata.o

viewerdata.o:	viewerdata.h viewerdata.cpp

clean:
	rm -f test
	rm -f viewerdata.o
