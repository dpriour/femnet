h51642
s 00038/00000/00000
d D 1.1 95/10/17 12:16:35 molagnon 1 0
c date and time created 95/10/17 12:16:35 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

setwdt_ (int *Pktrt)
           

/*
 *      setwdt = choix d une epaisseur de trait
 *        1 = tres fin
 *        2, 0 = trait normal
 *        3 = gras = guere epais (noter que ceci est tres fin)
 *        4 = tres epais 
 *      auteur : Ph. Morvan R/D/I+
 *      version %I% du %G%                                              
 */

{
      switch (*Pktrt) {
        case (1):
          jwdt0 = jwdt1;
          break;

        case (2):
          jwdt0 = jwdt2;
         break;

        case (3):
          jwdt0 = jwdt3;
          break;

        case (4):
          jwdt0 = jwdt4;
          break;

        default:
          jwdt0 = jwdt2;
          break;
      }
}
E 1
