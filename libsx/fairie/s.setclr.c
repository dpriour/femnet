h36174
s 00022/00000/00000
d D 1.1 95/10/17 13:16:29 molagnon 1 0
c date and time created 95/10/17 13:16:29 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

/*
 *     setclr = positionnne la couleur courante
 *     version %I% du %G%
 */

void
setclr_ (int *Pkclr)
{
      register int kclrm;

      if (*Pkclr == -1) {
         kclr0 = iclrd;
      } else {
         kclr0 = iclrd + *Pkclr - 1;
         kclrm = iclrd + nclr - 1;
         if ((kclr0 > kclrm) || (kclr0 < iclrd)) {
           kclr0 = kclrm;
         }
      }
}
E 1
