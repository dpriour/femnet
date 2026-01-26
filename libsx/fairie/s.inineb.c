h06032
s 00075/00000/00000
d D 1.1 95/10/17 13:18:12 molagnon 1 0
c date and time created 95/10/17 13:18:12 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"

/*
 *     inineb =  forcage noir et blanc
 *     version %I% du %G%
 */
void
inineb_ (void)
{
      extern void rpncnv (Canvas Scnv, Xv_window Swin, Rectlist *PSare);
      Screen *Sscr;
      int lximg;

      switch (jprf) {

/* .... avant inigra (rien a faire) ..................................*/
 
      case 0:
        jprf = 1;
        break;

/* .... on y est deja (rien a faire) .................................*/
 
      case 1:
        break;

/* .... on etait en couleur ..........................................*/
 
      default:
      case 8:
        jprf = 1;
        nclr = 2;
      
/* .... recreation de l'image memoire ou l'on va dessiner ......*/

        xv_destroy (Hwimg);
        zm_del     (PSimg);
        xv_destroy (Hcimg);
        ifcms = 0;
      
       
/* .... redefinition de l'image de travail .....................*/

        PSimg = zm_cre (lxwin, lywin, jprf);
        PSimgw = PSimg;             
       
/* .... recreation du canevas de dessin ................*/

        Hcimg = xv_create (Hfimg, CANVAS,
                               CANVAS_AUTO_SHRINK,   FALSE,
                               CANVAS_REPAINT_PROC, rpncnv,
                               CANVAS_X_PAINT_WINDOW, TRUE,
                               0);

        Hwimg = canvas_paint_window (Hcimg);
        Sdsp  = (Display *) xv_get (Hwimg, XV_DISPLAY);
        Hwin  = (Window) xv_get (Hwimg, XV_XID);
        Sscr  = XDefaultScreenOfDisplay (Sdsp);
        lximg = PSimgw->x;
        Sgc = XCreateGC (Sdsp, Hwin, 0, NULL);
        Hscr = DefaultScreen (Sdsp);
        Pima = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr),
                            jprf,
                            ZPixmap, 0,
                            (BYTE *) PSimgw->d,
                            lximg, lywin, BitmapPad (Sdsp), lximg);
       
/* .... initialisation du fond .................................... */ 

        zm_set (PSimg, 0, 0, lxwin, lywin, 0);

        kclr0 = 1; 
        break;
      }
}
E 1
