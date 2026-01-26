h12991
s 00035/00000/00000
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
 *       putgct = forcage du contexte graphique 
 *       version %I% du %G%
 */

void
putgct_ (float *Pxscl, float *Pyscl, float *Pxpnt, float *Pypnt, int *Pjwdt, int *Pkclr, int *Pkfnt, int *Pkalv, int *Pkalh)
{
      int kclrm;

/* ... facteurs d'echelle .................................... */
      xscl = *Pxscl;
      yscl = *Pyscl;

/* ... position courante ..................................... */
      jxpnt0 = jxorg + (int) (*Pxpnt * xscl);
      jypnt0 = jyorg - (int) (*Pypnt * yscl);

/* ... largeur courante ...................................... */
      jwdt0 = *Pjwdt;

/* ... couleur courante ...................................... */
      kclr0 = *Pkclr;

/* ... police courante ....................................... */
      if (*Pkfnt == 1)  PSfnt0 = PSfnt1;
      if (*Pkfnt == 2)  PSfnt0 = PSfnt2;
      if (*Pkfnt == 3)  PSfnt0 = PSfnt3;
      if (*Pkfnt == 4)  PSfnt0 = PSfnt4;

/* ... codes alignement ...................................... */
      kalv0 = *Pkalv;
      kalh0 = *Pkalh;
}
E 1
