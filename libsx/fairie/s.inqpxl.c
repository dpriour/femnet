h63395
s 00029/00000/00000
d D 1.1 95/10/17 12:16:32 molagnon 1 0
c date and time created 95/10/17 12:16:32 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

/*
 *      inqpxl = determination de la taille en pixel d un rectangle 
 *      version %I% du %G%
 */

void
inqpxl_ (float *dxpxl, float *dypxl, int *jxpxl, int *jypxl, float *xscl1, float *yscl1)
                         /* taille en mm du rectangle */
                         /* taille en pixel du rectangle */
                         /* facteurs de correction */
{
           
/* .... taille en pixel ....................................*/

      *jxpxl = (int) (xscl * (*dxpxl));
      if (*jxpxl < 1) *jxpxl = 1;
      *jypxl = (int) (yscl * (*dypxl));
      if (*jypxl < 1) *jypxl = 1;
           
/* .... facteurs de correction ..............................*/

      *xscl1 = ((float) *jxpxl) / (*dxpxl * xscl);
      *yscl1 = ((float) *jypxl) / (*dypxl * yscl);

} 
 

E 1
