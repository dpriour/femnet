#
# Top level makefile for libsx and all the example code.
#
# Basically we just cd into each of the directories and build
# the stuff that's there.
#
# I know I've committed a major sin by not using imake to generate
# the makefiles, but I've never quite understood that beast and it seems
# overly complicated to me (but then again I never put tons of effort
# into understanding it).  If someone would like to explain it to me,
# I'd like that (or point to some simple to read documentation).
#
# Dominic Giamapolo
# dbg@sgi.com
# 
SHELL=/bin/sh
DIRS = src demo1 demo2 demo3 demo4 bezier frac freq creq multireq skel\
       xmore draw_demo

all : $(DIRS)

src::
	(cd src ; $(MAKE) )

demo1::
	(cd demo1 ; $(MAKE) )

demo2::
	(cd demo2 ; $(MAKE) )

demo3::
	(cd demo3 ; $(MAKE) )

demo4::
	(cd demo4 ; $(MAKE) )

bezier::
	(cd bezier ; $(MAKE) )

frac::
	(cd frac ; $(MAKE) )

freq::
	(cd freq ; $(MAKE) )

creq::
	(cd creq ; $(MAKE) )

multireq::
	(cd multireq ; $(MAKE) )

skel::
	(cd skel ; $(MAKE) )

xmore::
	(cd xmore ; $(MAKE) )

draw_demo::
	(cd draw_demo ; $(MAKE) )


clean :
	for dir in $(DIRS);  do               \
	   cd $$dir ; make clean ; cd ..;     \
	done;
