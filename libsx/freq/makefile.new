#
#
include ../libsx_defs

FREQ_OBJS  = freq.o dirlist.o
OBJS       = main.o libfreq.a

all : libfreq.a freq


libfreq.a : $(FREQ_OBJS)
	rm -f libfreq.a
	ar rc libfreq.a $(FREQ_OBJS)
	$(RANLIB) libfreq.a


freq : $(OBJS) 
	$(CC) -o $@ $(OBJS) $(LIBS)


main.o : main.c libsx.h freq.h

freq.o : freq.c

dirlist.o : dirlist.c

clean:
	rm -f *.o *~ core freq libfreq.a
