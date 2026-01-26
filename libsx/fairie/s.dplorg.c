h37233
s 00021/00000/00000
d D 1.1 95/10/17 12:16:21 molagnon 1 0
c date and time created 95/10/17 12:16:21 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

void
dplorg_ (float *Pxorg, float *Pyorg)
                     

/*
 *       dplorg  = deplacement de l origine 
 *       version %I% du %G%
 */

{
      int lxorg, lyorg;

/* .... calcul des composantes et archivage ............*/

      lxorg = (int) (xscl * (*Pxorg));
      lyorg = (int) (yscl * (*Pyorg));
      jxorg = jxorg + lxorg;
      jyorg = jyorg - lyorg;
} 
E 1
