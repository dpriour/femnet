h15785
s 00053/00000/00000
d D 1.1 95/10/17 12:16:28 molagnon 1 0
c date and time created 95/10/17 12:16:28 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

/*
 *      inibtn = initialisation des boutons de la souris
 *      auteur = s.Louviaux R/D/I+
 *      version %I% du %G%
 */

void
inibtn_ (int *Pktblc, char *Pztblc, int ltblc)

                    /* code couleur (coloredit)               */
                    /* nom du fichier table des couleurs      */
            

{
  extern void inicoo_ (int *Pibtn);
  extern void iniedg_ (int *Pibtn, int *Pjgri1, int *Pjgri2);
  extern void iniedc_ (int *Pibtn);
  extern void chxclr_ (int *Pktbl);

  int ibtn;
  static int jgri1, jgri2;

/* ... d'abord la couleur (sinon pb au pointe) */

  ibtn = 3;
  switch (*Pktblc) {
  case 0:
    inineb_ ();
    break;
  case 1:
    chxclr_ (Pktblc);
    break;
  case 2:
    chxclr_ (Pktblc);
    break;
  case 3:
    chxclr_ (Pktblc);
    break;
  case 4:
    iniedc_ (&ibtn);
    break;
  case 5:
    iniedg_ (&ibtn, &jgri1, &jgri2);
    break;
  }

/* ... pointe de coordonnees .................. */

  ibtn = 1;
  inicoo_ (&ibtn);
}
E 1
