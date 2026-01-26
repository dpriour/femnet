# Makefile pour Geometry Editor (GTK 3 version)

CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall
LIBS = `pkg-config --libs gtk+-3.0` -lm

OBJS = gtk3_main.o gtk3_drawing.o callbacks.o

all: gengis

gengis: $(OBJS)
	$(CC) -o gengis $(OBJS) $(LIBS)

gtk3_main.o: gtk3_main.c main.h callbacks.h gtk3_drawing.h
	$(CC) $(CFLAGS) -c gtk3_main.c

gtk3_drawing.o: gtk3_drawing.c gtk3_drawing.h
	$(CC) $(CFLAGS) -c gtk3_drawing.c

callbacks.o: callbacks.c main.h callbacks.h gtk3_drawing.h
	$(CC) $(CFLAGS) -c callbacks.c

clean:
	rm -f *.o gengis core

run: gengis
	./gengis
