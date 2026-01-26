h00265
s 00087/00000/00000
d D 1.1 95/10/17 12:16:20 molagnon 1 0
c date and time created 95/10/17 12:16:20 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
#define    NGRIM      (FCL_MAX - FCL_GRI)

void
chxclr_ (int *Pktbl)
           

/*
 *      chxclr = choix d'un segment de la table des couleurs
 *      version %I% du %G%   
 */
     
{
      switch (*Pktbl) {

/*  .... segment ardoise ............................. */
      default:
      case 0:
      case 1:
         iclrd = FCL_ARD + JPXLD;
         nclr  = NCLRM;
         break;

/*  .... segment arc-en-ciel fond blanc .............. */
      case 2:
         iclrd = FCL_RBW1 + JPXLD;
         nclr  = NCLRM;
         break;

/*  .... segment arc-en-ciel fond noir ............... */
      case 3:
         iclrd = FCL_RBW2 + JPXLD;
         nclr  = NCLRM;
         break;

/*  .... segment couleur utilisateur ................. */
      case 4:
         iclrd = FCL_USR + JPXLD;
         nclr  = NCLRM;
         break;

/*  .... segment gris utilisateur .................... */
      case 5:
         iclrd = FCL_GRI + JPXLD;
         nclr  = NGRIM;
         break;

/*  .... segment controle .................... */
      case 6:
         iclrd = 0;
         nclr  = 256;
         break;


/*  .... segment ardoise editable .................... */
      case 9:
         iclrd = FCL_ARD + FCL_EDT + JPXLD;
         nclr  = NCLRM;
         break;

/*  .... segment arc-en-ciel fond blanc editable ..... */
      case 10:
         iclrd = FCL_RBW1 + FCL_EDT + JPXLD;
         nclr  = NCLRM;
         break;

/*  .... segment arc-en-ciel fond noir editable ...... */
      case 11:
         iclrd = FCL_RBW2 + FCL_EDT + JPXLD;
         nclr  = NCLRM;
         break;

/*  .... segment couleur utilisateur editable ........ */
      case 12:
         iclrd = FCL_USR + FCL_EDT + JPXLD;
         nclr  = NCLRM;
         break;

/*  .... segment gris utilisateur editable ........... */
      case 13:
         iclrd = FCL_GRI + FCL_EDT + JPXLD;
         nclr  = NGRIM;
         break;

      }
      kclr0 = iclrd + nclr - 1;
}
E 1
