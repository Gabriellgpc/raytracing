BASEDIR	=	../..

CC = g++
CXX = g++
CPPFLAGS = -Wall -O2 -I ${BASEDIR}/include
LDFLAGS  = -O2 -L ${BASEDIR}/lib
LDLIBS   = -lGLU -lGL -lglut -llm	-lutils

all:	raytracer.a

libraytracer.a:	raytracer.o	object/object.o	viewerdata/viewerdata.o	world/world.o
	ar r $@ $?

object/object.o:
	cd object && ${MAKE}

viewerdata/viewerdata.o:
	cd viewerdata && ${MAKE}

world/world.o:
	cd world && ${MAKE}

raytracer.o:	raytracer.h	raytracer.cpp

install:	libraytracer.a
	-cp	-f	libraytracer.a	${BASEDIR}/lib
	-cp	-f	raytracer.h	${BASEDIR}/include

clean:
	rm -f test
	rm -f raytracer.a
	rm -f raytracer.o
	cd world      && ${MAKE} clean
	cd viewerdata && ${MAKE} clean
	cd object     && ${MAKE} clean
