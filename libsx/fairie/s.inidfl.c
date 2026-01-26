h06338
s 00229/00000/00000
d D 1.1 95/10/17 12:16:29 molagnon 1 0
c date and time created 95/10/17 12:16:29 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
#include <thread.h>
#define LXDECM  256

thread_t Twin;
int lxdec, lydec;
int ifdfl;
int lxmem;
Zonmem *PSmem, *PSvis;

void
inidfl_ (int *Pibtn, float *Pxdec)
/*
 *      inidfl = initialisation du defilement 
 *      version %I% du %G%
 */

{
      extern void btndfl (Event *PSevn);
      extern void affgra_ (void);
      int lxdecm;

      if (ifaff > 1) {
         return;
      }

/* ..... flag et bouton ......................*/

      switch (*Pibtn) {
      case 1:             /* MS_LEFT */
        kactl  = FAI_DFL;
        kactdl = FAI_NONE;
        PFactl = btndfl;
        break;
      default:
      case 2:             /* MS_MIDDLE */
        kactm  = FAI_DFL;
        kactdm = FAI_NONE;
        PFactm = btndfl;
        break;
      case 3:             /* MS_RIGHT */
        kactr  = FAI_DFL;
        kactdr = FAI_NONE;
        PFactr = btndfl;
        break;
      }
      
/* ..... deja initialise ? ...................*/

      if (ifdfl) {
         return;
      }
      ifdfl = 1;

/* .... definition de l'image en memoire ..................*/

      lxdec = (int) (*Pxdec * xscl) / jgro;
      if (lxwin / 6 < LXDECM) {
         lxdecm = LXDECM;
      } else {
         lxdecm = lxwin / 6;
      }
      if (lxdec > lxdecm) lxdec = lxdecm;
      if (lxdec < 1) lxdec = 1;
      *Pxdec = (float) (jgro * lxdec) / xscl;
      lxmem = lxwin + 3 * lxdec;
      if (jprf == 1) {
          lxmem = WRDBIT * ((lxmem + WRDBIT - 1) / WRDBIT);
      } else {
          lxmem = WRDBYT * ((lxmem + WRDBYT - 1) / WRDBYT);
      }
      PSmem = zm_cre (jgro * lxmem, jgro * lywin, jprf);
      zm_set (PSmem, 0, 0, jgro * lxmem, jgro * lywin, iclrb);

      PSvis = zm_bld (jgro * lxwin, jgro * lywin, jprf, PSmem->d);
      PSvis->xv = PSmem->xv;

/* .... recuperation du dessin existant ..................*/

      zm_cpy (PSmem, 0, 0, jgro * lxwin, jgro * lywin, PSimg, 0, 0);

      if (jgro == 1) {
         int lximg;
         PSimgw = zm_bld (lxwin, lywin, jprf, PSmem->d);
         PSimgw->xv = PSmem->xv;
         Pima->data = NULL;
         XDestroyImage (Pima);
         if (jprf == jprfe) {
            lximg = PSmem->x;
            Pima = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr),
                                 jprf,
                                 ZPixmap, 0,
                                 (BYTE *) PSmem->d,
                                 lximg, lywin, BitmapPad (Sdsp), 0);
         } else {
            lximg = PSmem->x;
            Pima = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr),
                                 jprf,
                                 XYBitmap, 0,
                                 (BYTE *) PSmem->d,
                                 lximg, lywin, BitmapPad (Sdsp), 0);
            Pima->byte_order = MSBFirst;
            Pima->bitmap_bit_order = MSBFirst;
         }
      } else {
          zm_del (PSimg);
      }
      PSimg = PSmem;
}
void
btndfl (Event *PSevn)
             

/* 
 * btndfl : action defilement
 *
 */
{
      int jpxl;
      if (ifaff != 1) {
          return;
      }
 
      if (event_is_down (PSevn)) {

/* .... decalage ..............................................*/

          zm_cpy (PSimg, jgro * lxdec, 0,
                         jgro * (lxmem - lxdec), jgro * lywin, 
                  PSimg, 0, 0);

/* .... effacement ..............................................*/

          zm_set (PSimg, jgro * (lxmem - lxdec), 0,
                         jgro * lxdec, jgro * lywin, iclrb);

/* .... construction eventuelle de l'image .....................*/

          if (jgro > 1) {
             rdcpxr (PSvis, PSimgw, jprf, iclrb);
          }

          XPutImage (Sdsp, Hwin, Sgc, Pima, 0,0,0,0,lxwin,lywin);

/* .... decalage de l origine ................................. */

          jxorg -= lxdec * jgro;

      }
 
 /* .... cede la main quand on relache ........................ */
 
      if (event_is_up (PSevn)) {
          int jxmou, jymou;
          jxmou = (int) event_x (PSevn);
          jymou = (int) event_y (PSevn);
          jxmou -= lxdec;
          xv_set (Hfimg, WIN_MOUSE_XY, jxmou, jymou, NULL);
          (void) thr_setprio (thr_self (), MINPRIO);
          (void) thr_yield ();
      }
}
void
attdfl_ (int *Pibtn, int *Pifrfr)
/* bouton declenchant le defilement */
/* indicateur demandant de rafraichir AVANT */
/*
 * attdfl = arrete le programme jusqu'a defilement
 */
{
        extern void inidfl_ (int *Pibtn, float *Pxdec);
        extern void trtevn (Canvas Scnv, Event *PSevn);
        extern void affgra_ (void);
        static int ifdeb = 0;
  
        if (ifaff > 1) {
           return;
        }

        if (ifdfl == 0) {
           float xdec;

           xdec = (float) ((jgro * lxwin) / 16) / xscl;
           inidfl_ (Pibtn, &xdec);
        }

/* .... lancement eventuel du multithread ............... */
        if (ifaff == 0) {
            affgra_ ();
        } else {

/* .... affichage du dessin en l'etat ................*/

            if ((*Pifrfr != 0) || (ifdeb == 0)) {

/* .... construction eventuelle de l'image .....................*/

               if (jgro > 1) {
                  rdcpxr (PSvis, PSimgw, jprf, iclrb);
               }
  
/* .... affichage de l'image .................................. */

               XPutImage (Sdsp, Hwin, Sgc, Pima, 0,0,0,0,lxwin,lywin);
            }
        }

/* .... on autorise les evenements ............................*/

        if (ifdeb == 0) {
          ifdeb = 1;
          xv_set (Hwimg, WIN_CONSUME_EVENTS,
                             WIN_UP_EVENTS,
                             LOC_DRAG,
                             LOC_WINEXIT,
                             WIN_LEFT_KEYS,
                             WIN_ASCII_EVENTS, 
                             0,
                         WIN_EVENT_PROC, trtevn, 
                         0);
        }

/* .... on passe la main a la fenetre ..............*/

        (void) thr_setprio (thr_self (), (MAXPRIO / 2));
        (void) thr_setprio (Twin, MAXPRIO);
        (void) thr_yield ();
        (void) thr_setprio (thr_self (), MAXPRIO);
}
E 1
