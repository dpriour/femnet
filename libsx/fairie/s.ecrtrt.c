h58978
s 00032/00000/00000
d D 1.1 95/10/17 12:16:23 molagnon 1 0
c date and time created 95/10/17 12:16:23 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

void
ecrtrt_ (float *Pxpnt, float *Pypnt)
                     

/*
 *      ecrtrt = trace d'un trait 
 *      version %I% du %G%
 */
     
{
      int jxpnt1, jypnt1;
           
/* .... calcul des composantes de l extremite ............*/

      jxpnt1 = (int) (xscl * (*Pxpnt)) + jxorg;
      jypnt1 = jyorg - (int) (yscl * (*Pypnt));
      
/* .... trace ............................................*/

      if (jwdt0 <= 1) {
        zm_vct (PSimg, jxpnt0, jypnt0, jxpnt1, jypnt1, kclr0);
      } else {
        zm_vlr (PSimg, jxpnt0, jypnt0, jxpnt1, jypnt1, kclr0, jwdt0);
      }
                         
/* .... archivage de la position actuelle ................*/

      jxpnt0 = jxpnt1;
      jypnt0 = jypnt1;
}
E 1
