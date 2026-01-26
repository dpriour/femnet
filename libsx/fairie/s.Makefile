h54084
s 00002/00000/00041
d D 1.2 95/10/17 14:06:23 molagnon 2 1
c problemes ansi avec includes xview
e
s 00041/00000/00000
d D 1.1 95/10/17 12:16:44 molagnon 1 0
c date and time created 95/10/17 12:16:44 by molagnon
e
u
U
f e 0
t
T
I 1
#                    ---------------------
#                    ! MAKEFILE de libxv!
#                    ---------------------
#                    version %I% du %G%
#
include ../config.env
include ../config.mk
#
I 2
#
CC = gcc
E 2
# _________________________________________________________
#
all       : $(INCXVW) \
            $(LINKXV) \
            $(BIBXVW)
#
$(BIBXVG) : $(BIBXVG)($(OBJGRA))
$(BIBXVT) : $(BIBXVT)($(OBJTXT)) 
#
#
.PRECIOUS : $(BIBXVW)
#
#
#
$(INCXVW) :
	cd ../include ; $(MAKE) $(INCXVW)
#
$(LINKXV) :
	ln -s ../lib/$@
#
#
clean : 
	sccs clean
	$(RM) $(BIBXVW) $(LINKXV)
	$(RM) ,*
	$(RM) *%
#
#
#
install : 
	sccs clean
	$(RM) ,*
	$(RM) *%
E 1
