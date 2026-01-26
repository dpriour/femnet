h21774
s 00214/00000/00000
d D 1.1 95/10/17 12:16:21 molagnon 1 0
c date and time created 95/10/17 12:16:21 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

void
ecrair_ (float *xpnt, float *ypnt, float *dthrx, float *dthry, int *kxsns, int *kysns)
                      /* coordonnes du point courant */
                      /* seuils de remplissage en x et y */
                      /* code sens de remplissage        */
 /* kxsns =>   */
 /* 0 = pas de remplissage en x  */
 /* 1 = remplissage en x de la courbe vers (l'axe des y + seuil en x) */
 /* 2 = remplissage en x de (l'axe des y + seuil en x) vers la courbe */
 /* kysns =>  inutilise */
 /* * = pas de remplissage en y  */
  
/*
        ecrair = noircissage d'une aire  
        l aire est definie par :
          en x : le seuil de remplissage en x
                 l abcisse du point objectif
          en y : le seuil de remplissage en y
                 le trait du point courant au point objectif            

        version %I% du %G%
        auteurs: S Louviaux R/D/I+, M Olagnon Ifremer
*/
 
{
    int kopr;
    int jxpnt1, jypnt1;
    int jxpnti, jypnti;
    int jxorgr, jyorgr;  
    int jxpntt[2], jypntt[2];  
    double vxpnt0, vypnt0;
    double vxpnt1, vypnt1;
    double vxpnti, vypnti;
    double vxorgr, vyorgr;  
    double vtmp;


/* .... coordonnees, a l'echelle de l'ecran, du point origine du remplissage */

      jxorgr = jxorg + (int) (xscl * (*dthrx));
      jyorgr = jyorg - (int) (yscl * (*dthry));
  
/* .... coordonnees, a l'echelle de l'ecran, du point courant .....*/

      jxpnt1 = jxorg + (int) (xscl * (*xpnt));
      jypnt1 = jyorg - (int) (yscl * (*ypnt));

      vxpnt0 = jxpnt0;
      vypnt0 = jypnt0;
      vxpnt1 = jxpnt1;
      vypnt1 = jypnt1;
      vxorgr = jxorgr;
      vyorgr = jyorgr;
  
  
/* .... traitement du code sens de remplissage en x ..............*/
  
      switch (*kxsns) {
  
      case 1: 
/* -------------------------------------------------------------- */
/* on noircit en x de la courbe vers l'axe des y + seuil en x     */
/* -------------------------------------------------------------- */
   
/* traitement des positions des points par rapport a la droite    */
/* representee par l'axe des y + seuil en x                       */
 
        if (jxpnt0 >= jxorgr && jxpnt1 >= jxorgr) {
          /* rien a noircir */
          break;
        }

        if (jypnt0 == jypnt1) {
          /* rien a noircir */
          break;
        }
  
        if (jxpnt0 < jxorgr && jxpnt1 < jxorgr) {
          /* noircissage du polygone */
          jxpntt [0] = jxpnt0;
          jypntt [0] = jypnt0;
          jxpntt [1] = jxpnt1;
          jypntt [1] = jypnt1;
          zm_rid (PSimg, jxorgr, jxpntt, jypntt, 2, kclr0);
          break;
        }
  
        if (jxpnt0 < jxorgr && jxpnt1 >= jxorgr) {
          /* calcul des coordonnees du point d'intersection */
          jxpnti = jxorgr;
          if (jxpnt1 != 0) {
            vtmp = ((vypnt0 * vxpnt1) - (vypnt1 * vxpnt0)) / (vxpnt1 - vxpnt0); 
            vypnti = vtmp + (vxorgr / vxpnt1) * (vypnt1 - vtmp);
            jypnti = (int) (vypnti + 0.5);
          }  
          else {
            vypnti = ((vypnt0 - vypnt1) / vxpnt0) * vxorgr + vypnt1;
            jypnti = (int) (vypnti + 0.5);
          }
          /* noircissage du triangle */
          jxpntt [0] = jxpnti;
          jypntt [0] = jypnti;
          jxpntt [1] = jxpnt0;
          jypntt [1] = jypnt0;
          zm_rid (PSimg, jxorgr, jxpntt, jypntt, 2, kclr0);
          break;
       } 
 
        if (jxpnt0 >= jxorgr && jxpnt1 < jxorgr) {
          /* calcul des coordonnees du point d'intersection */
          jxpnti = jxorgr;
          if (jxpnt1 != 0) {
            vtmp = ((vypnt0 * vxpnt1) - (vypnt1 * vxpnt0)) / (vxpnt1 - vxpnt0); 
            vypnti = vtmp + (vxorgr / vxpnt1) * (vypnt1 - vtmp);
            jypnti = (int) (vypnti + 0.5);
          }  
          else {
            vypnti = ((vypnt0 - vypnt1) / vxpnt0) * vxorgr + vypnt1;
            jypnti = (int) (vypnti + 0.5);
          }
          /* noircissage du triangle */
          jxpntt [0] = jxpnt1;
          jypntt [0] = jypnt1;
          jxpntt [1] = jxpnti;
          jypntt [1] = jypnti;
          zm_rid (PSimg, jxorgr, jxpntt, jypntt, 2, kclr0);
          break;
        } 
 
  
      case 2: 
/* -------------------------------------------------------------- */
/* on noircit en x, de l'axe des y + seuil en x vers la courbe    */ 
/* -------------------------------------------------------------- */
   
/* traitement des positions des points par rapport a la droite    */
/* representee par l'axe des y + seuil en x                       */
 
 
        if (jxpnt0 <= jxorgr && jxpnt1 <= jxorgr) {
          /* rien a noircir */
          break;
        }

        if (jypnt0 == jypnt1) {
          /* rien a noircir */
          break;
        }
  
        if (jxpnt0 > jxorgr && jxpnt1 > jxorgr
        ) {
          /* noircissage du polygone */
          /* noircissage du polygone */
          jxpntt [0] = jxpnt0;
          jypntt [0] = jypnt0;
          jxpntt [1] = jxpnt1;
          jypntt [1] = jypnt1;
          zm_rid (PSimg, jxorgr, jxpntt, jypntt, 2, kclr0);
          break;
        }
  
        if (jxpnt0 <= jxorgr && jxpnt1 > jxorgr) {
          /* calcul des coordonnees du point d'intersection */
          jxpnti = jxorgr;
          if (jxpnt1 != 0) {
            vtmp = ((vypnt0 * vxpnt1) - (vypnt1 * vxpnt0)) / (vxpnt1 - vxpnt0); 
            vypnti = vtmp + (vxorgr / vxpnt1) * (vypnt1 - vtmp);
            jypnti = (int) (vypnti + 0.5);
          }  
          else {
            vypnti = ((vypnt0 - vypnt1) / vxpnt0) * vxorgr + vypnt1;
            jypnti = (int) (vypnti + 0.5);
          }
          /* noircissage du triangle */
          jxpntt [0] = jxpnti;
          jypntt [0] = jypnti;
          jxpntt [1] = jxpnt1;
          jypntt [1] = jypnt1;
          zm_rid (PSimg, jxorgr, jxpntt, jypntt, 2, kclr0);
          break;
       } 
 
        if (jxpnt0 > jxorgr && jxpnt1 <= jxorgr) {
          /* calcul des coordonnees du point d'intersection */
          jxpnti = jxorgr;
          if (jxpnt1 != 0) {
            vtmp = ((vypnt0 * vxpnt1) - (vypnt1 * vxpnt0)) / (vxpnt1 - vxpnt0); 
            vypnti = vtmp + (vxorgr / vxpnt1) * (vypnt1 - vtmp);
            jypnti = (int) (vypnti + 0.5);
          }  
          else {
            vypnti = ((vypnt0 - vypnt1) / vxpnt0) * vxorgr + vypnt1;
            jypnti = (int) (vypnti + 0.5);
          }
          /* noircissage du triangle */
          jxpntt [0] = jxpnt0;
          jypntt [0] = jypnt0;
          jxpntt [1] = jxpnti;
          jypntt [1] = jypnti;
          zm_rid (PSimg, jxorgr, jxpntt, jypntt, 2, kclr0);
          break;
        }  
      default: 
        break;
      }
/* .... traitement du code sens de remplissage en y ..............*/
 
/* .... archivage de la position actuelle ................*/

      jxpnt0 = jxpnt1;
      jypnt0 = jypnt1;
} 
E 1
