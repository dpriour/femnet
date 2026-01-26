h00541
s 00071/00000/00000
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
ecrpxl_ (int *Pjxpnt, int *Pjypnt, int *Plxpnt, int *Plypnt, int *Pkgrs)
                        /* point de trace  */
                       /* taille du trace */
                       /* niveau de gris de 0 a 255 */

/*
 *      ecrpxl = ecriture d un pave avec niveaux de gris 
 *      version %I% du %G%
 */
     
{
    int jxpnt, jypnt;
    int lxpnt, lypnt;
    int kclr,  kclrv;
    int jlvl;

/* .... calcul des composantes du point ............*/
/* .... correction due a  l orientation negative des y ......*/

     lxpnt = *Plxpnt;
     lypnt = - *Plypnt;
     jxpnt = jxorg + *Pjxpnt;
     jypnt = jyorg - *Pjypnt;

/* .... determination du point superieur gauche ............*/

     if (lxpnt < 0) {
       lxpnt = - lxpnt;
       jxpnt = jxpnt - lxpnt;
     }

     if (lypnt < 0) {
       lypnt = - lypnt;
       jypnt = jypnt - lypnt;
     }

/* .... trace en monochrome .......................... */
  
      if (nclr <= 2)  {

        kclr = (int) ((*Pkgrs * 2) / 256);
        if (kclr > 0)  {
          zm_set (PSimg, jxpnt, jypnt, lxpnt, lypnt, 1);
        } else {
          zm_set (PSimg, jxpnt, jypnt, lxpnt, lypnt, 0);
        }
        return;
      }
         
        
/* .... trace en couleur ..........................
   .... le nombre de couleurs est limite a nclr -2 car :
   .... 0        = couleur du fond
   .... nclr - 1 = couleur du texte
   ....................................................... */
      
      jlvl = (256 + nclr - 1) / nclr;
      kclr = *Pkgrs / jlvl;
      if (kclr < 0) kclr = 0;
      if (kclr >= (nclr - 1)) kclr = nclr - 2;

      if (kclr > 0) {
        kclrv = iclrd + kclr;
        zm_set (PSimg, jxpnt, jypnt, lxpnt, lypnt, kclrv);
      } else {
        zm_set (PSimg, jxpnt, jypnt, lxpnt, lypnt, iclrd);
      }
}
E 1
