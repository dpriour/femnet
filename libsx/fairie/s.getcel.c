h39903
s 00020/00000/00000
d D 1.1 95/10/17 12:16:26 molagnon 1 0
c date and time created 95/10/17 12:16:26 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

void
getcel_ (float *Pwcel, float *Phcel, int *Pnpxlw, int *Pnpxlh)
                     
                     

/*
 *      getcel = taille d'une cellule elementaire 
 *      pour les niveaux de gris, en Unites utilisateur
 *                                et en pixels
 *      version %I% du %G%
 */

{
      *Pnpxlw = 1;
      *Pnpxlh = 1; 
      *Pwcel = (float) *Pnpxlw / xscl;     
      *Phcel = (float) *Pnpxlh / yscl;
}
E 1
