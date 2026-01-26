h29811
s 00068/00000/00000
d D 1.1 95/10/17 12:16:22 molagnon 1 0
c date and time created 95/10/17 12:16:22 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
#define    NGRIM       (FCL_MAX - FCL_GRI)
#define    JPXLO       (FCL_GRI + FCL_EDT + JPXLD)

void
ecrimg_ (float *Pxpnt, float *Pypnt, long unsigned int *Pjimgt, int *Pnpntx, int *Pnpnty)
                /* abscisse coin bas gauche */
                /* ordonnee coin bas gauche */
                /* image en niveaux de 0 (noir) a 255 (blanc) */
                /* jimgt (npntx, npnty) (stockage FORTRAN)    */
                /* nombre de valeurs en x (colonnes)   */
                /* nombre de valeurs en y (lignes)     */
/*
 * ecrimg = trace d'une image
 * auteur : M.Olagnon       Ifremer
 * version %I% du %G%                                              
 */

{
      int jxpnt1, jypnt1, jxpnt2, jypnt2, lximg;
      int llig1, jypxl, ichr, ibit;
      BYTE *Pzchr;

/* .... calcul des composantes des coins ................*/

      jxpnt1 = (int) (xscl * (*Pxpnt)) + jxorg;
      jypnt2 = jyorg - (int) (yscl * (*Pypnt));
      jypnt1 = jypnt2 - *Pnpnty;
      jxpnt2 = jxpnt1 + *Pnpntx;
      jxpnt1 = BOUND (jxpnt1, 0, PSimg->x);
      jypnt1 = BOUND (jypnt1, 0, PSimg->y);
      jxpnt2 = BOUND (jxpnt2, 0, PSimg->x);
      jypnt2 = BOUND (jypnt2, 0, PSimg->y);
      lximg  = jxpnt2 - jxpnt1;

/* .... longueurs de lignes en octets (prise en compte du 
         filling)                       ..................*/

      llig1 = (PSimg->xv * PSimg->p) / BYTBIT;
      switch (jprf) {
         case (8):
          /* en couleur */
             for (jypxl = jypnt1; jypxl < jypnt2; jypxl++) {
                 Pzchr  = (BYTE *) PSimg->d + llig1 * jypxl + jxpnt1;
                 for (ichr = 0; ichr < lximg; ichr++) {
                   *Pzchr++ = (BYTE)
                              (((*Pjimgt++ * NGRIM) / 256) + JPXLO);
                 }
              }

          break;

          case (1):
           /* en N/B */
             for (jypxl = jypnt1; jypxl < jypnt2; jypxl++) {
                 Pzchr  = (BYTE *) PSimg->d + llig1 * jypxl + (jxpnt1 / BYTBIT);
                 for (ichr = 0; ichr < lximg; ichr += BYTBIT) {
                     register BYTE kclr = 0;
                     for (ibit = 0; ibit < BYTBIT; ibit ++) {
                        kclr = (kclr << 1) | (*Pjimgt++ > 127);
                     }
                     *Pzchr++ = kclr;
                 }
              }
            break;

       } /* end switch */
}
E 1
