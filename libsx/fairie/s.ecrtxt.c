h63311
s 00084/00000/00000
d D 1.1 95/10/17 12:16:24 molagnon 1 0
c date and time created 95/10/17 12:16:24 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

void
ecrtxt_ (float *Pxpnt, float *Pypnt, char *ztxtt, int ltxt)
                     
             
         

/*
 *      ecrtxt = ecriture d un texte 
 *      version %I% du %G%
 */
     
{
           
      int jxpnt1, jypnt1;
      int jxchr, jychr;
      int ltxtt;
           
/* .... calcul des composantes de l extremite ................*/

      jxpnt1 = (int) (xscl * (*Pxpnt)) + jxorg;
      jypnt1 = jyorg - (int) (yscl * (*Pypnt));
      
/* .... taille sans blancs .................................*/

      for (ltxtt = ltxt ; ltxtt > 0 ; ltxtt--) {
         if (ztxtt[ltxtt-1] != ' ' && ztxtt[ltxtt-1] != '\0') break;
      }

/* .... taille des caracteres .................................*/

      jxchr = PSfnt0->x;
      jychr = PSfnt0->y;
            
/* .... correction due a l'alignement .........................*/

      switch (kalh0) {

        case (1):    /* a gauche */
          break;

        case (2):    /* centre */
          jxpnt1 = jxpnt1 - (ltxtt * jxchr) / 2;
          break;

        case (3):    /* a droite */
          jxpnt1 = jxpnt1 - ltxtt * jxchr;
          break;

        default:    /* normal */
          break;
        }

      switch (kalv0) {

        case (1):    /* en haut */
          jypnt1 = jypnt1 + jychr;
          break;

        case (3):    /* au milieu */
          jypnt1 = jypnt1 + (jychr / 2) - 3;
          break;

        case (5):    /* en bas */
          jypnt1 = jypnt1 - 3;
          break;

        default:    /* normal */
          break;
        }

/* .... alignement pour tenir compte du grossissement eventuel ..*/

      if (jgro > 1) {
        jxpnt1 = (jxpnt1 / jgro) * jgro;
        jypnt1 = (jypnt1 / jgro) * jgro;
      }

/* .... trace ................................................*/

      zm_txt (PSimg, jxpnt1, jypnt1, ztxtt, ltxtt, PSfnt0, kclr0);

}
E 1
