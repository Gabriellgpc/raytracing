BASEDIR	=	.

CC = g++
CXX = g++
CPPFLAGS = -Wall -O2 -I . -fopenmp	-pg
LDFLAGS = -L ${BASEDIR}/lib
LDLIBS = -lGLU -lGL -lglut -lm	#-lutils -lraytrace

OBJS = raytrace.o    utils.o	viewerdata.o	world.o   object.o

all:	main

main:	main.cpp	${OBJS}

raytrace.o:	raytrace.cpp raytrace.h
viewerdata.o:	viewerdata.cpp viewerdata.h
object.o:	object.cpp object.h
world.o:	world.cpp world.h
utils.o:	utils.cpp utils.h

install:
	${MAKE}	clean
	cd libsrc	&& ${MAKE} clean
	cd libsrc	&& ${MAKE} install

clean:
	rm -rf main
	rm -f *.o

realclean:
	${MAKE}	clean
	cd libsrc	&& ${MAKE} clean
