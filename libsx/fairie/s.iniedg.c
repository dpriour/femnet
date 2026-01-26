h45701
s 00382/00000/00000
d D 1.1 95/10/17 13:20:29 molagnon 1 0
c date and time created 95/10/17 13:20:29 by molagnon
e
u
U
f e 0
t
T
I 1
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdlib.h>
#include "../include/faixvg.h"
#define    FCL_DEB     (FCL_GRI + FCL_EDT + JPXLD)
#define    NGRIM       (FCL_MAX - FCL_GRI)
Canvas 	Hcedtg;
Canvas  Hwedtg;
Panel	Hpedtg;
Panel_item   Hsedtb, Hsedtn;
XImage *Pimad;
Window Hwind;
Screen  *Sscr;
XColor   Sclr;
Colormap Smapd;
static short jdgdt [1024];
int  jgri1, jgri2, jgrid, jgrif, kgrih, kgril, igri1, igri2;
int *Pjlev1, *Pjlev2;
int ifedg;

/*
 *      iniedg = initialisation de l'editeur de gris
 *      version  %I% du %G%
 */

void
iniedg_ (int *Pibtn, int *Pjgri1, int *Pjgri2)
/* bouton declenchant        */
/* niveau blanc initial      */
/* niveau noir initial       */

{
      extern void btnedg (Event *PSevn);
      extern void rpnedg (Canvas Hcnv, Xv_window Hwin, Rectlist *PSare);
      extern void setedg (Panel_item Hsedt, unsigned int jgrib, struct inputevent *PSinp);
      extern void finedg (void);
      extern void revedg (void);
      Panel_item Hbtn;
      Attr_avlist Satt;
      int jgri, idgd, kclr;
      int kgri;
      unsigned char *Pzdgd;

/* ..... a-t-on bien precedemment initialise en couleur ? .... */

      if (jprf != 8) {
        return;
      }
      if (ifcms == 0) {
        return;
      }

/* ..... flag et bouton ......................*/

      switch (*Pibtn) {
      case 1:             /* MS_LEFT */
        kactl  = FAI_EDG;
        kactdl = FAI_NONE;
        PFactl = btnedg;
        break;
      case 2:             /* MS_MIDDLE */
        kactm  = FAI_EDG;
        kactdm = FAI_NONE;
        PFactm = btnedg;
        break;
      default:
      case 3:             /* MS_RIGHT */
        kactr  = FAI_EDG;
        kactdr = FAI_NONE;
        PFactr = btnedg;
        break;
      }

/* ..... deja initialise ? ...................*/

      if (ifedg) {
         return;
      }
      ifedg = 1;
      Pjlev1 = Pjgri1;
      Pjlev2 = Pjgri2;

/* .... redefinition des couleurs utilisees ................... */   
        
       kclr = 13;
       chxclr_ (&kclr);
      
/* ..... construction du degrade de gris ......................*/

        Pzdgd = (unsigned char *) jdgdt;
        for (idgd = 0 ; idgd < 256 ; idgd ++) {
           kgri = (NGRIM * idgd) / 256 + FCL_GRI + FCL_EDT + JPXLD;
           *Pzdgd          = (unsigned char) kgri;
           *(Pzdgd + 256)  = (unsigned char) kgri;
           *(Pzdgd + 512)  = (unsigned char) kgri;
           *(Pzdgd + 768)  = (unsigned char) kgri;
           *(Pzdgd + 1024) = (unsigned char) kgri;
           *(Pzdgd + 1280) = (unsigned char) kgri;
           *(Pzdgd + 1536) = (unsigned char) kgri;
           *(Pzdgd + 1792) = (unsigned char) kgri;
           Pzdgd ++;
        }

        kgrih = 65025;
        kgril = 0;
        if (*Pjgri1 == *Pjgri2) {
           jgri1 = 0;
           if (*Pjgri2 == 0) {
              jgri2 = NGRIM - 1;
           } else {
              jgri2 = 2 * (*Pjgri2);
           }
        } else {
           jgri1 = *Pjgri1;
           jgri2 = *Pjgri2;
        }
        jgrid = jgri1;
        jgrif = jgri2;
        igri1 = 0;
        igri2 = NGRIM - 1;
                            
/*...... creation de la fenetre d'edition .........*/

        Hfedtg  = xv_create (XV_NULL, FRAME,
	       		  XV_LABEL, "grayedit",
	  		  WIN_X, 0,
			  WIN_Y, 0,
			  WIN_HEIGHT, LYFRMC,
		          WIN_WIDTH, LXFRMC,
			  0);
			  
        Hpedtg  = xv_create (Hfedtg, PANEL,
                                 WIN_ROW_GAP, 16,
	                         WIN_COLUMN_GAP, 32,
                                 0);

        Pimad   = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr),
                               DefaultDepth (Sdsp, Hscr),
                               ZPixmap, 0,
                               (unsigned char *) jdgdt,
                               256, 8, BitmapPad (Sdsp), 0);
                                 
/*........ attributs reutilisables pour les tirettes ..................*/

	Satt = attr_create_list (
			XV_SHOW,	TRUE,
			XV_X,	   xv_col (Hpedtg, 0),
			PANEL_MIN_VALUE,	jgri1,
			PANEL_MAX_VALUE,	jgri2,
			PANEL_SLIDER_WIDTH,	256,
			PANEL_SHOW_RANGE,	TRUE,
			PANEL_SHOW_VALUE,	TRUE,
			PANEL_NOTIFY_LEVEL,	PANEL_ALL,
			0);
			
/* ....... tirettes ...................................................*/

	Hsedtb = xv_create (Hpedtg, PANEL_SLIDER,
			XV_Y,	   xv_row (Hpedtg, 0),
			ATTR_LIST,		Satt,
			PANEL_NOTIFY_PROC,	setedg,
			0);

	Hsedtn = xv_create (Hpedtg, PANEL_SLIDER,
			XV_Y,	   xv_row (Hpedtg, 1),
			ATTR_LIST,		Satt,
			PANEL_NOTIFY_PROC,	setedg,
			0);

/*........ boutons ...................................................*/

	Hbtn = xv_create (Hpedtg, PANEL_BUTTON,
	                XV_X,       xv_get (Hsedtb, XV_WIDTH) + 20,
			XV_Y,	    xv_row (Hpedtg, 0),
			PANEL_LABEL_STRING,    "Quit", 
			PANEL_NOTIFY_PROC,	finedg,
			0);
	Hbtn = xv_create (Hpedtg, PANEL_BUTTON,
	                XV_X,       xv_get (Hsedtb, XV_WIDTH) + 20,
			XV_Y,	    xv_row (Hpedtg, 1),
			PANEL_LABEL_STRING,    "Rev.", 
			PANEL_NOTIFY_PROC,	revedg,
			0);

	free (Satt);
	window_fit_height (Hpedtg);

/* ....... creation du canevas de dessin ...........................*/

	Hcedtg = xv_create (Hfedtg, CANVAS,
	                   XV_X,       0,
	                   XV_Y,       xv_get (Hpedtg, XV_HEIGHT),
	                   CANVAS_X_PAINT_WINDOW, TRUE,
                           CANVAS_REPAINT_PROC,  rpnedg,
	                   0);
        Hwedtg = canvas_paint_window (Hcedtg);
        Hwind = (Window) xv_get (Hwedtg, XV_XID);
        XSetWindowBackground (Sdsp, Hwind, (unsigned long) FCL_DEB);
        XClearWindow (Sdsp, Hwind);

/* ........ positionnement de la valeur initiale des tirettes ......*/

	xv_set (Hsedtb, PANEL_VALUE, jgri1, 0);
	xv_set (Hsedtn, PANEL_VALUE, jgri2, 0);
        
        Sscr = XDefaultScreenOfDisplay (Sdsp);
        Smapd = DefaultColormapOfScreen (Sscr);
        Sclr.pixel = JPXLD - 1;
        Sclr.red   = 255;
        Sclr.green = 255;
        Sclr.blue  = 255;
        Sclr.flags = DoRed | DoGreen | DoBlue;
        XStoreColor (Sdsp, Smapd, &Sclr);
}
void
btnedg (Event *PSevn) 
             

/* 
 * btnedg : affiche et gere l'editeur de gris
 */
{
      if (event_is_down (PSevn)) {
          if (Hfedtg != XV_NULL) {
            xv_set (Hfedtg, WIN_SHOW, TRUE, 0);

          }
      }
}

void
setedg (Panel_item Hsedt, unsigned int jgrib, struct inputevent *PSinp)
          		      
            		      
                 	       
/*
 * setedg = changement d'une borne du degrade
 */

{
        int igri, igri0;
        int kgri;
        extern void chgcms ();
        
/*....... recalcul du degrade ...........................*/
	if (Hsedt == Hsedtb) {
	  if (jgrib <= jgri2) {
	     igri0 = ((jgri1 -jgrid) * NGRIM) / (jgrif - jgrid + 1);
	     igri1 = ((jgrib -jgrid) * NGRIM) / (jgrif - jgrid + 1);
	     igri2 = ((jgri2 -jgrid) * NGRIM) / (jgrif - jgrid + 1);
	     jgri1 = jgrib;
             for (igri = igri2 ; igri > igri1 ; igri--) {
                kgri = (kgrih * (igri2 - igri) + kgril * (igri - igri1))
                         / (igri2 - igri1);
                Sclr.pixel = igri + FCL_DEB;
                Sclr.red   = kgri;
                Sclr.green = kgri;
                Sclr.blue  = kgri;
                Sclr.flags = DoRed | DoGreen | DoBlue;
                XStoreColor (Sdsp, Smapd, &Sclr);
             }
             for (igri = igri1 ; igri >= igri0 ; igri--) {
                kgri = kgrih;
                Sclr.pixel = igri + FCL_DEB;
                Sclr.red   = kgri;
                Sclr.green = kgri;
                Sclr.blue  = kgri;
                Sclr.flags = DoRed | DoGreen | DoBlue;
                XStoreColor (Sdsp, Smapd, &Sclr);
             }
          } else {
             xv_set (Hsedtb, PANEL_VALUE, jgri2, 0);
          }
	}
	
	if (Hsedt == Hsedtn) {
	  if (jgrib >= jgri1) {
	     igri0 = ((jgri2 -jgrid) * NGRIM) / (jgrif - jgrid + 1);
	     igri1 = ((jgri1 -jgrid) * NGRIM) / (jgrif - jgrid + 1);
	     igri2 = ((jgrib -jgrid) * NGRIM) / (jgrif - jgrid + 1);
	     jgri2 = jgrib;
             for (igri = igri0 ; igri > igri2 ; igri--) {
                kgri = kgril;
                Sclr.pixel = igri + FCL_DEB;
                Sclr.red   = kgri;
                Sclr.green = kgri;
                Sclr.blue  = kgri;
                Sclr.flags = DoRed | DoGreen | DoBlue;
                XStoreColor (Sdsp, Smapd, &Sclr);
             }
             for (igri = igri2 ; igri > igri1 ; igri--) {
                kgri = (kgrih * (igri2 - igri) + kgril * (igri - igri1))
                       / (igri2 - igri1);
                Sclr.pixel = igri + FCL_DEB;
                Sclr.red   = kgri;
                Sclr.green = kgri;
                Sclr.blue  = kgri;
                Sclr.flags = DoRed | DoGreen | DoBlue;
                XStoreColor (Sdsp, Smapd, &Sclr);
             }
          } else {
             xv_set (Hsedtn, PANEL_VALUE, jgri1, 0);
          }
	}
	
}
         
void
revedg (void) 

/*
 * revedg = reverse video
 */
{
        int igri, kgri0;
        int kgri;

/*....... recalcul du degrade ...........................*/

        kgri0 = kgril;
        kgril = kgrih;
        kgrih = kgri0;

        for (igri = NGRIM - 1 ; igri > igri2 ; igri--) {
           kgri = kgril;
           Sclr.pixel = igri + FCL_DEB;
           Sclr.red   = kgri;
           Sclr.green = kgri;
           Sclr.blue  = kgri;
           Sclr.flags = DoRed | DoGreen | DoBlue;
           XStoreColor (Sdsp, Smapd, &Sclr);
        }
        for (igri = igri2 ; igri > igri1 ; igri--) {
           kgri = (kgril * (igri - igri1) + kgrih * (igri2 - igri)) / 
                                 (igri2 - igri1);
           Sclr.pixel = igri + FCL_DEB;
           Sclr.red   = kgri;
           Sclr.green = kgri;
           Sclr.blue  = kgri;
           Sclr.flags = DoRed | DoGreen | DoBlue;
           XStoreColor (Sdsp, Smapd, &Sclr);
        }
        for (igri = igri1 ; igri >= 0 ; igri--) {
           kgri = kgrih;
           Sclr.pixel = igri + FCL_DEB;
           Sclr.red   = kgri;
           Sclr.green = kgri;
           Sclr.blue  = kgri;
           Sclr.flags = DoRed | DoGreen | DoBlue;
           XStoreColor (Sdsp, Smapd, &Sclr);
        }
        
}

void
finedg (void) 

/*
 * finedg = fin d'edition des couleurs
 */

{
	xv_set (Hfedtg, WIN_SHOW, FALSE, 0);
	*Pjlev1 = jgri1;
	*Pjlev2 = jgri2;
}

void
rpnedg (Canvas Hcnv, Xv_window Hwin, Rectlist *PSare)
/*
 * rpnedg = repeinture de l'editeur de gris
 */

{

/* ... dessin de la palette ........................................*/

        XPutImage (Sdsp, Hwind, Sgc, Pimad,    0,     0,
                                              68,    24,
                                             256,     8);
}
E 1
