BASEDIR	=	../../..

CC = g++
CXX = g++
CPPFLAGS = -Wall -O2 -I ${BASEDIR}/include
LDFLAGS = -L ${BASEDIR}/lib
LDLIBS = -lGL	-lGLU -lutils

all:	test

test:	test.cpp world.o

world.o:	world.h world.cpp

clean:
	rm -f test
	rm -f world.o
