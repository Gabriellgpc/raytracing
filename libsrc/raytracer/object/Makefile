BASEDIR	=	../../..

CC = g++
CXX = g++
CPPFLAGS = -Wall -O2 -I ${BASEDIR}/include
LDFLAGS = -L ${BASEDIR}/lib
LDLIBS = -lutils

all:	test

test:	object.o

object.o:	object.h object.cpp

clean:
	rm -f test
	rm -f object.o
