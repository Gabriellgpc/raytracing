BASEDIR	=	../..

CC = g++
CXX = g++
CPPFLAGS = -Wall -O2 -I ${BASEDIR}/include
LDLIBS = -llm

all:	test

test:	test.cpp utils.o

utils.o:	utils.h utils.cpp

libutils.a:	utils.o
	ar r $@ $?

install:	libutils.a
	-cp	-f	libutils.a	${BASEDIR}/lib
	-cp	-f	utils.h	${BASEDIR}/include

clean:
	rm -f test
	rm -f utils.o
