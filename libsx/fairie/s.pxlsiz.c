h25748
s 00013/00000/00000
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
 *     pxlsiz = taille d un pixel en mm
 *     version %I% du %G%
 */

void
pxlsiz_ (float *Pdxpxl, float *Pdypxl)
{
      *Pdxpxl = (XWIN / (float) LXWIN);
      *Pdypxl = (YWIN / (float) LYWIN);
}
E 1
