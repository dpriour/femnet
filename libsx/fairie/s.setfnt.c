h35107
s 00031/00000/00000
d D 1.1 95/10/17 13:15:06 molagnon 1 0
c date and time created 95/10/17 13:15:06 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

/*
 *     setfnt = choix d une police 
 *     version %I% du %G%
 */

void
setfnt_ (int *Pkfnt)
{
      switch (*Pkfnt) {

        case (1):
          PSfnt0 = PSfnt1;
          break;

        case (2):
          PSfnt0 = PSfnt2;
         break;

        case (3):
          PSfnt0 = PSfnt3;
          break;

        case (4):
        default:
          PSfnt0 = PSfnt4;
          break;

      }
}
E 1
