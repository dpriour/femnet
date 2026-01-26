h55599
s 00024/00000/00000
d D 1.1 95/10/17 12:21:34 molagnon 1 0
c date and time created 95/10/17 12:21:34 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

/*
 *  urdpnt = determination du point a 1/2 pixel le plus proche 
 *  mouture %I% du %G%
 */
void
urdpnt_ (float *Pxpnt, float *Pypnt, float *Pxpntu, float *Pypntu)
/* coordonnees du point donne */
/* coordonnees desarrondies   */

{
    int jxpnt, jypnt;

/* .... calcul des composantes du point .................*/

      jxpnt = (int) (xscl * (*Pxpnt)) + jxorg;
      jypnt = jyorg - (int) (yscl * (*Pypnt));

/* .... facteurs de correction ..............................*/

      *Pxpntu = ((float) (jxpnt - jxorg) + 0.5) / xscl ;
      *Pypntu = ((float) (jyorg - jypnt) + 0.5) / yscl ;
}
E 1
