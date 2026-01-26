h44921
s 00297/00000/00000
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
#define LXCOO   128
#define LYCOO    40

Zonmem *PScoo;
XImage *Pimac;
int ifcoo;
WORD jcoot [LXCOO * LYCOO / WRDBYT];
DIMFSTRING (Zlig1, LPOS);    
DIMFSTRING (Zlig2, LPOS + 4); /* ne doit pas depasser LXCOO pixels */
int jxbox, jybox;
int jxloc, jyloc;
double 	dxloc, dyloc;
int	kbox;
                          
void
inicoo_ (int *Pibtn)
                   /* bouton declenchant                   */

/*
 *      inicoo = initialisation du pointe de coordonnees
 *      version %I% du %G%
 */
     
{
      extern void btncoo (Event *PSevn);
      extern void suicoo (Event *PSevn);

/* ..... flag et bouton ......................*/

      switch (*Pibtn) {
      default:
      case 1:             /* MS_LEFT */
        kactl = FAI_COO;
        kactdl = FAI_COO;
        PFactl = btncoo;
        PFactdl = suicoo;
        break;
      case 2:             /* MS_MIDDLE */
        kactm = FAI_COO;
        kactdm = FAI_COO;
        PFactm = btncoo;
        PFactdm = suicoo;
        break;
      case 3:             /* MS_RIGHT */
        kactr = FAI_COO;
        kactdr = FAI_COO;
        PFactr = btncoo;
        PFactdr = suicoo;
        break;
      }

/* ..... deja initialise ? ...................*/

      if (ifcoo) {
         return;
      }
      ifcoo = 1;

/* ..... creation de l image contenant les coordonnees ..........*/

      PScoo = zm_bld (LXCOO, LYCOO, jprf, (BYTE *) jcoot);
      if (jprf == jprfe) {
           Pimac = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr), jprf,
                                 ZPixmap, 0,
                                 (BYTE *) jcoot,
                                 LXCOO, LYCOO, BitmapPad (Sdsp), 0);
      } else {
           Pimac = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr), jprf,
                                 XYBitmap, 0,
                                 (BYTE *) jcoot,
                                 LXCOO, LYCOO, BitmapPad (Sdsp), 0);
           Pimac->byte_order = MSBFirst;
           Pimac->bitmap_bit_order = MSBFirst;
      }
}
void btncoo (Event *PSevn) 
             

/* 
 * btncoo : trace une boite contenant les coordonnees
 *
 */
{
      int i, j, k;
      unsigned char *Pdat;

      if (event_is_down (PSevn)) {
          jxloc = (int) event_x (PSevn);
          jyloc = (int) event_y (PSevn);
          if (jxloc < 0 || jxloc > lxwin) return;
          if (jyloc < 0 || jyloc > lywin) return;
          
/* .... recuperation des coordonnees ................ */

          dxloc = (double) (jxloc * jgro - jxorg) / xscl;
          dyloc = (double) (jyorg - jyloc * jgro) / yscl;

/* .... stockage de la zone  qu on va effacer ................ */

          if (jxloc + LXCOO > lxwin) {
            jxbox = jxloc - LXCOO;
            kbox = 1;
          } else  {
            jxbox = jxloc;
            kbox = 0;
          }
          
          if (jyloc + LYCOO > lywin) {
            jybox = jyloc - LYCOO;
            kbox = kbox + 10;
          } else  {
            jybox = jyloc;
          }

/* .... preparation de la boite qu'on va afficher ............ */

          zm_set (PScoo, 0, 0, LXCOO, LYCOO, 1);
          zm_set (PScoo, 0, 0, LXCOO, LYCOO, 0);
                  
          switch (kbox) {

 /* .... point au coin sup gauche  ................*/
          case 0:
             zm_vct (PScoo, 0, 0, LXCOO - 1, 0, 1);
             zm_vct (PScoo, 0, 0, 0, LYCOO - 1, 1);
             break;
                   
 /* .... point au coin inf gauche  ................*/
          case 10:
             zm_vct (PScoo, LXCOO - 1, LYCOO - 1, 0, LYCOO - 1, 1);
             zm_vct (PScoo, 0, LYCOO - 1, 0, 0, 1);
             break;
               
  /* .... point au coin sup droit ................*/
          case 1:
             zm_vct (PScoo, 0, 0, LXCOO - 1, 0, 1);
             zm_vct (PScoo, LXCOO - 1, 0, LXCOO - 1, LYCOO - 1, 1);
             break;
          
  /* .... point au coin inf droit ................*/
          case 11:
             zm_vct (PScoo, LXCOO - 1, 0, LXCOO - 1, LYCOO - 1, 1);
             zm_vct (PScoo, LXCOO - 1, LYCOO - 1, 0, LYCOO - 1, 1);
             break;
          }
 /* .... affichage du texte ................ */

          inistr (Zlig1, NULL, LPOS);
 	  chxfmt_ (&dxloc, Zlig1, LPOS);
          inistr (Zlig2, "x = ", LPOS + 4);
 	  catstr (Zlig2, Zlig1);
 	  zm_txt (PScoo, 8, (LYCOO / 2 - 5), Zlig2, strlen(Zlig2), 
 	          PSfntc, 1);
                   
	  chxfmt_ (&dyloc, Zlig1, LPOS);
 	  cpystr  (Zlig2, "y = ");
 	  catstr (Zlig2, Zlig1);
 	  zm_txt (PScoo, 8, (LYCOO - 7), Zlig2, strlen(Zlig2), 
 	          PSfntc, 1);

 /* .... affichage de la boite ................ */

          XPutImage (Sdsp, Hwin, Sgc, Pimac,    0,     0,
                                            jxbox, jybox,
                                            LXCOO,  LYCOO);
        }
 
 
/* .... desaffichage ..................................*/

        if (event_is_up (PSevn)) {
            XPutImage (Sdsp, Hwin, Sgc, Pima, jxbox, jybox,
                                              jxbox, jybox,
                                              LXCOO, LYCOO);
        }
}
void
suicoo (Event *PSevn) 
             

/* 
 * suicoo : deplace une boite contenant les coordonnees
 *
 */
{
      int jxboxp, jyboxp;
      int jxbox1, jybox1, lxbox1, lybox1;
      int jxbox2, jybox2;

      if (event_id (PSevn) == LOC_DRAG) {
          jxloc = (int) event_x (PSevn);
          jyloc = (int) event_y (PSevn);
          jxboxp = jxbox;
          jyboxp = jybox;

          if (jxloc < 0 || jxloc > lxwin) return;
          if (jyloc < 0 || jyloc > lywin) return;
          
/* .... recuperation des coordonnees ................ */

          dxloc = (double) (jxloc * jgro - jxorg) / xscl;
          dyloc = (double) (jyorg - jyloc * jgro) / yscl;
        
/* .... stockage de la zone  qu on va effacer ................ */

          if (jxloc + LXCOO > lxwin) {
            jxbox = jxloc - LXCOO;
            kbox = 1;
          } else  {
            jxbox = jxloc;
            kbox = 0;
          }
          
          if (jyloc + LYCOO > lywin) {
            jybox = jyloc - LYCOO;
            kbox = kbox + 10;
          } else  {
            jybox = jyloc;
          }
          
/* .... desaffichage ..................................*/

          if (jxbox != jxboxp) {
            jxbox1 = jxbox + LXCOO;
            jxbox2 = jxboxp + LXCOO;
            jxbox1 = (jxboxp > jxbox && jxboxp < jxbox1)? jxbox1 : jxboxp;
            lxbox1 = jxbox2 - jxbox1;
            lxbox1 = (jxbox2 > jxbox && jxbox2 < jxbox + LXCOO)? jxbox - jxbox1 : lxbox1;
            XPutImage (Sdsp, Hwin, Sgc, Pima, jxbox1, jyboxp,
                                              jxbox1, jyboxp,
                                              lxbox1,  LYCOO);
          }

          if (jybox != jyboxp) {
            jybox1 = jybox + LYCOO;
            jybox2 = jyboxp + LYCOO;
            jybox1 = (jyboxp > jybox && jyboxp < jybox1)? jybox1 : jyboxp;
            lybox1 = jybox2 - jybox1;
            lybox1 = (jybox2 > jybox && jybox2 < jybox + LYCOO)? jybox - jybox1 : lybox1;
            XPutImage (Sdsp, Hwin, Sgc, Pima, jxboxp, jybox1,
                                              jxboxp, jybox1,
                                              LXCOO,  lybox1);
          }
/* .... preparation de la boite qu'on va afficher ............ */

          zm_set (PScoo, 0, 0, LXCOO, LYCOO, 0);

          switch (kbox) {

 /* .... point au coin sup gauche  ................*/
          case 0:
             zm_vct (PScoo, 0, 0, LXCOO - 1, 0, 1);
             zm_vct (PScoo, 0, LYCOO - 1, 0, 0, 1);
             break;
                   
 /* .... point au coin inf gauche  ................*/
          case 10:
             zm_vct (PScoo, LXCOO - 1, LYCOO - 1, 0, LYCOO - 1, 1);
             zm_vct (PScoo, 0, LYCOO - 1, 0, 0, 1);
             break;
               
  /* .... point au coin sup droit ................*/
          case 1:
             zm_vct (PScoo, 0, 0, LXCOO - 1, 0, 1);
             zm_vct (PScoo, LXCOO - 1, 0, LXCOO - 1, LYCOO - 1, 1);
             break;
          
  /* .... point au coin inf droit ................*/
          case 11:
             zm_vct (PScoo, LXCOO - 1, 0, LXCOO - 1, LYCOO - 1, 1);
             zm_vct (PScoo, LXCOO - 1, LYCOO - 1, 0, LYCOO - 1, 1);
             break;
          }
          
 /* .... affichage du texte ................ */

          inistr (Zlig1, NULL, LPOS);
 	  chxfmt_ (&dxloc, Zlig1, LPOS);
          inistr (Zlig2, "x = ", LPOS + 4);
 	  catstr (Zlig2, Zlig1);
 	  zm_txt (PScoo, 8, (LYCOO / 2 - 5), Zlig2, strlen(Zlig2), 
 	          PSfntc, 1);
                   
 	  chxfmt_ (&dyloc, Zlig1, LPOS);
 	  cpystr  (Zlig2, "y = ");
 	  catstr (Zlig2, Zlig1);
 	  zm_txt (PScoo, 8, (LYCOO - 7), Zlig2, strlen(Zlig2), 
 	          PSfntc, 1);

 /* .... affichage de la boite ................ */
 
          XPutImage (Sdsp, Hwin, Sgc, Pimac,    0,     0,
                                            jxbox, jybox,
                                            LXCOO,  LYCOO);
     }
}
E 1
