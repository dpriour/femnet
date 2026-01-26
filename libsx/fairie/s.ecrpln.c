h38041
s 00025/00000/00000
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
ecrpln_ (int *Pnpnt, float *Pxpnt, float *Pypnt)
           
                     

/*
 *      ecrpln = trace d une polyline 
 *      version %I% du %G%
 */
     
{
    int ipnt;

/* .... initialisation ............................*/

     movpnt_ (Pxpnt, Pypnt);

/* .... trace ............................................*/

      for (ipnt = 1; ipnt < *Pnpnt; ipnt++) {
        ecrtrt_ (++Pxpnt, ++Pypnt);
      }
}
E 1
