BASEDIR	=	.

CC = g++
CXX = g++
CPPFLAGS = -Wall -O2 -I ${BASEDIR}/include
LDFLAGS = -O2 -L ${BASEDIR}/lib
LDLIBS = -lGLU -lGL -lglut -llm	-lraytracer	-lutils

all:	main

main:	main.cpp

install:
	${MAKE}	clean
	cd libsrc	&& ${MAKE} clean
	cd libsrc	&& ${MAKE} install

clean:
	rm -rf main

realclean:
	${MAKE}	clean
	cd libsrc	&& ${MAKE} clean
