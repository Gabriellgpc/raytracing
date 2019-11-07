BASEDIR	=	.

CC = g++
CXX = g++
CPPFLAGS = -Wall -O2 -I .
LDFLAGS = -L ${BASEDIR}/lib
LDLIBS = -lGLU -lGL -lglut -lm	-fopenmp#-lutils -lraytrace

all:	main

main:	main.cpp    raytrace.cpp    utils.cpp	viewerdata.cpp	world.cpp   object.cpp	raytrace.h  utils.h viewerdata.h	world.h   object.h

install:
	${MAKE}	clean
	cd libsrc	&& ${MAKE} clean
	cd libsrc	&& ${MAKE} install

clean:
	rm -rf main

realclean:
	${MAKE}	clean
	cd libsrc	&& ${MAKE} clean
