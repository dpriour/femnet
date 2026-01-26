h33608
s 00016/00000/00000
d D 1.1 95/10/17 12:16:33 molagnon 1 0
c date and time created 95/10/17 12:16:33 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

/*
 *      movpnt = deplacement de la position actuelle 
 *      version %I% du %G%
 */

void
movpnt_ (float *Pxpnt, float *Pypnt)
                     

/* .... calcul des composantes et archivage ............*/
{
      jxpnt0 = (int) (xscl * (*Pxpnt)) + jxorg;
      jypnt0 = jyorg - (int) (yscl * (*Pypnt));
}
E 1
