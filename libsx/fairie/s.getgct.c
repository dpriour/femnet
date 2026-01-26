h13851
s 00033/00000/00000
d D 1.1 95/10/17 12:16:27 molagnon 1 0
c date and time created 95/10/17 12:16:27 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
/*
 *      getgct = obtention du contexte graphique 
 *      version %I% du %G%                                              
 */

void
getgct_ (float *Pxscl, float *Pyscl, float *Pxpnt, float *Pypnt, int *Pjwdt, int *Pkclr, int *Pkfnt, int *Pkalv, int *Pkalh)
{
/* ... facteurs d'echelle .................................... */
      *Pxscl = xscl;
      *Pyscl = yscl;

/* ... position courante ..................................... */
      *Pxpnt = (float) (jxpnt0 - jxorg) / xscl;
      *Pypnt = (float) (jyorg - jypnt0) / yscl;

/* ... largeur courante ...................................... */
      *Pjwdt = jwdt0;

/* ... couleur courante ...................................... */
      *Pkclr = kclr0;

/* ... police courante ....................................... */
      if (PSfnt0 == PSfnt1)  *Pkfnt = 1;
      if (PSfnt0 == PSfnt2)  *Pkfnt = 2;
      if (PSfnt0 == PSfnt3)  *Pkfnt = 3;
      if (PSfnt0 == PSfnt4)  *Pkfnt = 4;

/* ... codes alignement ...................................... */
      *Pkalv = kalv0;
      *Pkalh = kalh0;
}
E 1
