h44087
s 00107/00000/00000
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
#include <math.h>
#define   NCRCM           128

void
ecrcrc_ (float *Pxctr, float *Pyctr, float *Prcrc)
                             

/*
 *     ecrcrc : trace d'un cercle (vide)
 *     version %I% du %G%
 */
     
{
    int jxctr, jyctr, jrcrc;
    int jxpnt, jypnt;
    int jxccft [NCRCM+1], jyccft [NCRCM+1];
    int npnt, npnt2, npnt34, npnt4, npnt8, jpas;
    int ipnt;
    int kcol;

           
/* .... initialisation ............................*/

      if (kclr0 < 0) {
         kcol = 0;
      } else {
         kcol = kclr0;
      }

/* .... coordonnees, a l'echelle de l'ecran, du centre */

      jxctr = jxorg + (int) (xscl * (*Pxctr));
      jyctr = jyorg - (int) (yscl * (*Pyctr));

/* .... valeur entiere du rayon ...................*/
/* .... Attention, le rayon est donne suivant X ...*/

      jrcrc = ((int) (2.0 * xscl * (*Prcrc))) / 2;
      if (jrcrc <= 0) {
         zm_put (PSimg, jxctr, jyctr, kcol);
         return;
      }

/* .... discretisation ...................................*/
  
      npnt8 = (int) (0.707 * xscl * (*Prcrc));
      if (npnt8 <= 0) npnt8 = 1;
      npnt = 8 * npnt8;
      jpas = 1;
      while (npnt > NCRCM) {
          npnt8 /= 2;
          jpas *= 2;
          npnt = 8 * npnt8;
      }
      npnt4  = 2 * npnt8;
      npnt2  = 4 * npnt8;
      npnt34 = npnt2 + npnt4;

/* .... generation du cercle ............................*/

      jxccft [0] = jxctr;
      jyccft [0] = jyctr - jrcrc;
      jxccft [npnt4] = jxctr - jrcrc;
      jyccft [npnt4] = jyctr;
      jxccft [npnt2] = jxctr;
      jyccft [npnt2] = jyctr + jrcrc;
      jxccft [npnt34] = jxctr + jrcrc;
      jyccft [npnt34] = jyctr;
      for (ipnt = 1 ; ipnt < npnt8 ; ipnt ++) {
        jypnt = ipnt * jpas;
        jxpnt = (int) (sqrt ((double) (jrcrc * jrcrc - jypnt * jypnt)) + 0.5);
        jxccft [ipnt] = jxctr - jxpnt;
        jyccft [ipnt] = jyctr - jypnt;
        jxccft [npnt4 - ipnt] = jxctr - jypnt;
        jyccft [npnt4 - ipnt] = jyctr - jxpnt;
        jxccft [npnt4 + ipnt] = jxctr - jypnt;
        jyccft [npnt4 + ipnt] = jyctr + jxpnt;
        jxccft [npnt2 - ipnt] = jxctr - jxpnt;
        jyccft [npnt2 - ipnt] = jyctr + jypnt;
        jxccft [npnt2 + ipnt] = jxctr + jxpnt;
        jyccft [npnt2 + ipnt] = jyctr + jypnt;
        jxccft [npnt34 - ipnt] = jxctr + jypnt;
        jyccft [npnt34 - ipnt] = jyctr + jxpnt;
        jxccft [npnt34 + ipnt] = jxctr + jypnt;
        jyccft [npnt34 + ipnt] = jyctr - jxpnt;
        jxccft [npnt - ipnt] = jxctr + jxpnt;
        jyccft [npnt - ipnt] = jyctr - jypnt;
      }
      jypnt = npnt8 * jpas;
      jxpnt = (int) (sqrt ((double) (jrcrc * jrcrc - jypnt * jypnt)) + 0.5);
      jxccft [npnt8] = jxctr - jxpnt;
      jyccft [npnt8] = jyctr - jypnt;
      jxccft [npnt4 + npnt8] = jxctr - jypnt;
      jyccft [npnt4 + npnt8] = jyctr + jxpnt;
      jxccft [npnt2 + npnt8] = jxctr + jxpnt;
      jyccft [npnt2 + npnt8] = jyctr + jypnt;
      jxccft [npnt34 + npnt8] = jxctr + jypnt;
      jyccft [npnt34 + npnt8] = jyctr - jxpnt;

/* .... ecriture du cercle ............................*/

      for (ipnt = 1 ; ipnt <= npnt ; ipnt ++) {
         zm_vct (PSimg, jxccft [ipnt-1], jyccft [ipnt-1],
                        jxccft [ipnt], jyccft [ipnt], kcol) ;
      } 
}
E 1
