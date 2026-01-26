h05262
s 00304/00000/00000
d D 1.1 95/10/17 12:16:29 molagnon 1 0
c date and time created 95/10/17 12:16:29 by molagnon
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
#define    FCL_DEB     (FCL_USR + FCL_EDT + JPXLD)
Canvas  Hwedtc;
Canvas 	Hcedtc;
Panel	Hpedtc;
Panel_item	Hsedt1, Hsedt2, Hsedt3;
XImage *Pimab;
Zonmem *PSblk;
Window Hwinb;
Screen  *Sscr;
XColor   Sclr;
Colormap Smapd;
int   lxblk;
WORD jblkt [LXCAR * LYCAR / WRDBYT];
int iclr0;

void
iniedc_ (int *Pibtn)
/* bouton declenchant */

/*
 *       iniedc = initialisation de l'editeur de couleurs  
 *       version %I% du %G%
 */
     
{
	extern void rpnedc (Canvas Scnv, Xv_window Swin, Rectlist *PSare);
        extern void getedc ();
        extern void setedc ();
        extern void finedc ();
        extern void btnedc (Event *PSevn);
	
        Panel_item Hbtn;
        Panel_item Hchx;
        Attr_avlist Satt;
        int lxwinc, lywinc;
        int kclr;

/* ..... a-t-on bien precedemment initialise en couleur ? .... */

        if (jprf != 8) {
           return;
        }
        if (ifcms == 0) {
           return;
        }

/* ..... flag et bouton ......................*/

        switch (*Pibtn) {
        case 1:
          ibedtc = MS_LEFT;
          kactl  = FAI_EDC;
          PFactl = btnedc;
          PFactdl = btnedc;
          break;
        case 2:
          ibedtc = MS_MIDDLE;
          kactm  = FAI_EDC;
          PFactm = btnedc;
          PFactdm = btnedc;
          break;
        default:
        case 3:
          ibedtc = MS_RIGHT;
          kactr  = FAI_EDC;
          PFactr = btnedc;
          PFactdr = btnedc;
          break;
        }

/* ..... deja initialise ? ...................*/

        if (ifedc) {
           return;
        }
        ifedc = 1;

/* .... redefinition des couleurs utilisees ................... */   
        
        kclr = 12;
        chxclr_ (&kclr);

/*...... creation de la fenetre d'edition .........*/
	
        lxwinc = (NCLRM - 1) * (LXCAR + LXCAR_GAP) + LXCAR_GAP;
        lywinc = LYFRMC + (2 * LYCAR_GAP) + LYCAR;
	
        Hfedtc  = xv_create (XV_NULL, FRAME,
	       		  XV_LABEL, "coloredit",
	  		  WIN_X, 0,
			  WIN_Y, 0,
			  WIN_HEIGHT, lywinc,
		          WIN_WIDTH, lxwinc,
			  0);
			  
        Hpedtc  = xv_create (Hfedtc, PANEL,
                                 WIN_ROW_GAP, 64,
                                 0);

/*........ attributs reutilisables pour les tirettes ..................*/

	Satt = attr_create_list (
			XV_SHOW,	TRUE,
			PANEL_MIN_VALUE,	0,
			PANEL_MAX_VALUE,	255,
			PANEL_SLIDER_WIDTH,	lxwinc - 200,
			PANEL_SHOW_RANGE,	TRUE,
			PANEL_SHOW_VALUE,	TRUE,
			PANEL_NOTIFY_LEVEL,	PANEL_ALL,
			0);
			
/*........ bouton ...................................................*/

	Hbtn = xv_create (Hpedtc, PANEL_BUTTON,
			PANEL_LABEL_STRING,    "Quit", 
			PANEL_NOTIFY_PROC,	finedc,
			0);

/*........ choice ...................................................*/

	Hchx = xv_create (Hpedtc, PANEL_CHOICE,
			PANEL_LABEL_STRING,	" Couleur n0 ------>",
			PANEL_CHOICE_STRINGS,	"0","1","2","3","4",
						"5","6","text", 0,
			PANEL_NOTIFY_PROC,	getedc,
			0);

        xv_set (Hpedtc, 
                PANEL_LAYOUT, PANEL_VERTICAL,
                0);

/* ....... tirettes ...................................................*/

	Hsedt1 = xv_create (Hpedtc, PANEL_SLIDER,
			ATTR_LIST,		Satt,
			PANEL_LABEL_STRING,	" rouge:",
			PANEL_NOTIFY_PROC,	setedc,
			0);

	Hsedt2 = xv_create (Hpedtc, PANEL_SLIDER,
			ATTR_LIST,		Satt,
			PANEL_LABEL_STRING,	" vert   :",
			PANEL_NOTIFY_PROC,	setedc,
			0);

	Hsedt3 = xv_create (Hpedtc, PANEL_SLIDER,
			ATTR_LIST,		Satt,
			PANEL_LABEL_STRING,	" bleu  :",
			PANEL_NOTIFY_PROC,	setedc,
			0);

	free (Satt);
	window_fit_height (Hpedtc);

/* ....... creation du canevas de dessin ...........................*/

        PSblk = zm_bld (LXCAR, LYCAR, DefaultDepth (Sdsp, Hscr), (BYTE *)jblkt);

        lxblk = PSblk->x;
        Pimab = XCreateImage (Sdsp, DefaultVisual (Sdsp, Hscr),
                             DefaultDepth (Sdsp, Hscr),
                             ZPixmap, 0,
                             (BYTE *) jblkt,
                             lxblk, LYLPE, BitmapPad (Sdsp), 0);

	Hcedtc = xv_create (Hfedtc, CANVAS,
	                   XV_X,       0,
	                   XV_Y,       xv_get (Hpedtc, XV_HEIGHT),
	                   CANVAS_X_PAINT_WINDOW, TRUE,
                           CANVAS_REPAINT_PROC, rpnedc,
	                   0);
        Hwedtc = canvas_paint_window (Hcedtc);
        Hwinb = (Window) xv_get (Hwedtc, XV_XID);
        XSetWindowBackground (Sdsp, Hwinb, (unsigned long) FCL_DEB);
        XClearWindow (Sdsp, Hwinb);
	                   
/* ........ positionnement de la valeur initiale des tirettes .......
   ........ = couleur du fond ......................................*/

        Sscr = XDefaultScreenOfDisplay (Sdsp);
        Smapd = DefaultColormapOfScreen (Sscr);

        Sclr.pixel = FCL_DEB;
        XQueryColor (Sdsp, Smapd, &Sclr);
	xv_set (Hsedt1, PANEL_VALUE, Sclr.red / 255, 0);
	xv_set (Hsedt2, PANEL_VALUE, Sclr.green / 255, 0);
	xv_set (Hsedt3, PANEL_VALUE, Sclr.blue / 255, 0);

        Sclr.pixel = JPXLD - 1;
        Sclr.red   = 510;
        Sclr.green = 510;
        Sclr.blue  = 510;
        Sclr.flags = DoRed | DoGreen | DoBlue;
        XStoreColor (Sdsp, Smapd, &Sclr);
}
void btnedc (Event *PSevn) 
             

/* 
 * btnedc : affiche et gere l'editeur de couleurs
 */
{
      if (event_id (PSevn) == LOC_DRAG) {
          return;
      }
      if (event_is_down (PSevn)) {
          if (Hfedtc != XV_NULL) {
            xv_set (Hfedtc, WIN_SHOW, TRUE, 0);
          }
      }
}

void
getedc (Panel_item Hsedt, unsigned int iclr, struct inputevent *PSinp)
{
/*
 *      getedc = choix de la couleur a editer
 */

        Sclr.pixel = FCL_DEB + iclr;
        XQueryColor (Sdsp, Smapd, &Sclr);
	xv_set (Hsedt1, PANEL_VALUE, Sclr.red / 255, 0);
	xv_set (Hsedt2, PANEL_VALUE, Sclr.green / 255, 0);
	xv_set (Hsedt3, PANEL_VALUE, Sclr.blue / 255, 0);
	iclr0 = iclr;
}

void
setedc (Panel_item Hsedt, unsigned int jclr, struct inputevent *PSinp)
{
/*
 *      setedc = definition de la couleur editee
 */

	if (Hsedt == Hsedt1) {
           Sclr.red   = 255 * jclr;
           Scmsft [iclr0 + FCL_EDT + FCL_USR].red   = jclr ;
	}
	if (Hsedt == Hsedt2) {
           Sclr.green = 255 * jclr;
           Scmsft [iclr0 + FCL_EDT + FCL_USR].green = jclr ;
	}
	if (Hsedt == Hsedt3) {
           Sclr.blue  = 255 * jclr;
           Scmsft [iclr0 + FCL_EDT + FCL_USR].blue  = jclr ;
	}

/*....... chargement de la couleur dans la table ....*/

        Sclr.pixel = FCL_DEB + iclr0;
        Sclr.flags = DoRed | DoGreen | DoBlue;
        XStoreColor (Sdsp, Smapd, &Sclr);
}
         


void
finedc (void) 

/*
 *	 finedc = fin d'edition des couleurs
 */
{
	xv_set (Hfedtc, WIN_SHOW, FALSE, 0);
}

void
rpnedc (Canvas Scnv, Xv_window Swin, Rectlist *PSare)
{
      int jxchr, jychr, iclr, jxclr, jyclr, jxclrt, jyclrt, kclrt;
      char	zclrt[3];

/* ... dessin de la palette
 *  ... remarque: on ne dessine pas avec la couleur 0 qui est le fond
 * ............. la palette est au maximum de 8 lignes x 16 colonnes
 * ............. un carre de la palette est donne par LXCAR x LYCAR
 */

	kclrt = FCL_DEB + NCLRM - 1;
        jxchr = PSfnt3->x;
        jychr = PSfnt3->y;

	for (iclr = 1 ; iclr < NCLRM ; iclr++) {
	   jxclr = (iclr - 1) * (LXCAR + LXCAR_GAP) + LXCAR_GAP / 2;
	   jyclr = LYCAR_GAP;
	   zm_set (PSblk, 0, 0, LXCAR, LYCAR, (FCL_DEB + iclr));

	   sprintf (zclrt, "%02d", iclr);
           zm_txt (PSblk,
                   (LXCAR / 2) - (jxchr / 2), (LYCAR / 2) + (jychr / 4),
                   zclrt, 2, PSfnt3, kclrt);

           XPutImage (Sdsp, Hwinb, Sgc, Pimab,    0,     0,
                                              jxclr, jyclr,
                                              LXCAR, LYCAR);

	}
}

E 1
