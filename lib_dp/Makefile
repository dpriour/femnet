WHO = librairy_dp.o

OBJ1 = alloc.o 
# OBJ2 = src1.o src2.o src3.o
# OBJ3 = src1.o src2.o src3.o
USER = $(OBJ1)


COPTION= -O

CFLAGS = $(COPTION) -DASSERT

LIBS =  -Bstatic -lm -lsuntool -lsunwindow 

$(WHO): $(USER)
	ld -r -o librairy.o $(USER)
