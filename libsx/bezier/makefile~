#
#
include ../libsx_defs

LOCAL_LIBS = -lm

# the object files which the program depends on
OBJS       = main.o callbacks.o bezier.o gfx.o

bez : $(OBJS)
	$(CC) -o bez $(OBJS) $(LIBS) $(LOCAL_LIBS)


# main.o depends on main.c (of course) and main.h and callbacks.h
main.o : main.c main.h callbacks.h gfx.h

callbacks.o : gfx.h callbacks.c main.h

gfx.o : gfx.c gfx.h


clean :
	rm -f *.o *~ core bez
