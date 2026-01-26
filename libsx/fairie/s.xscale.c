h30870
s 00018/00000/00000
d D 1.1 95/10/17 12:19:23 molagnon 1 0
c date and time created 95/10/17 12:19:23 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

/*
 *      xscale = definition de facteurs d echelle 
 *      version %I% du %G%
 */
     
xscale_ (float *Pxscl, float *Pyscl)

{

/* .... echelle ....................................*/

      if (*Pxscl != 0.0 & *Pyscl != 0.0) {
        xscl = xscl * *Pxscl;     
        yscl = yscl * *Pyscl; 
      }
}
E 1
