h37153
s 00315/00000/00000
d D 1.1 95/10/17 12:16:28 molagnon 1 0
c date and time created 95/10/17 12:16:28 by molagnon
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
#include <sys/wait.h>
#include <sys/param.h>
#include "../include/faixvg.h"
#define    NGRIM      (FCL_MAX - FCL_GRI)
unsigned int jpxld, npxl;

/*
 *    inicms = initialisation de la colormap standard fairie  
 *    version  %I% du %G%
 */

void
inicms (void)
{
      int iclr, jrcn, iprc, ifxst;
      unsigned char jneb = 0;
      Display *Sdsp;
      Screen  *Sscr;
      Window   Hrcn;
      XStandardColormap Smapi; /* info sur map */
      Colormap Smapd;
      XColor   Sclr;
      int icel, ipxl, ncel, nmap;
      unsigned long jpxlf, jpxl1, jpxl2, rmult, gmult, bmult;
      unsigned long jpxlt [4096];

      if (ifcms == 0) {
/* .... niveaux d'identification ..................... */

      iclr = 0;
        Scmsft [iclr].red   = 1 ;
        Scmsft [iclr].green = 2 ;
        Scmsft [iclr].blue  = 3 ;
        iclr ++;
        Scmsft [iclr].red   = 4 ;
        Scmsft [iclr].green = 5 ;
        Scmsft [iclr].blue  = 6 ;
        iclr ++;

/* .... niveaux d'ardoise ........................ */

      iclr = FCL_ARD  + FCL_OFF;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green = 255 ;
        Scmsft [iclr].blue  = 255 ;
        iclr ++;
        Scmsft [iclr].red   = 191 ;
        Scmsft [iclr].green = 223 ;
        Scmsft [iclr].blue  = 255 ;
        iclr ++;
        Scmsft [iclr].red   = 159 ;
        Scmsft [iclr].green = 191 ;
        Scmsft [iclr].blue  = 223 ;
        iclr ++;
        Scmsft [iclr].red   = 127 ;
        Scmsft [iclr].green = 159 ;
        Scmsft [iclr].blue  = 191 ;
        iclr ++;
        Scmsft [iclr].red   =  95 ;
        Scmsft [iclr].green = 127 ;
        Scmsft [iclr].blue  = 159 ;
        iclr ++;
        Scmsft [iclr].red   =  63 ;
        Scmsft [iclr].green =  95 ;
        Scmsft [iclr].blue  = 127 ;
        iclr ++;
        Scmsft [iclr].red   = 31 ;
        Scmsft [iclr].green = 63 ;
        Scmsft [iclr].blue  = 95 ;
        iclr ++;
        Scmsft [iclr].red   =  0 ;
        Scmsft [iclr].green = 31 ;
        Scmsft [iclr].blue  = 63 ;

/* .... arc-en-ciel 1 ........................ */

      iclr = FCL_RBW1 + FCL_OFF;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green = 255 ;
        Scmsft [iclr].blue  = 255 ;
        iclr ++;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green =   0 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green = 191 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 191 ;
        Scmsft [iclr].green = 191 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green = 191 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 127 ;
        Scmsft [iclr].green = 127 ;
        Scmsft [iclr].blue  = 215 ;
        iclr ++;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green =   0 ;
        Scmsft [iclr].blue  = 255 ;
        iclr ++;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green =   0 ;
        Scmsft [iclr].blue  =   0 ;

/* .... arc-en-ciel 2 ........................ */

      iclr = FCL_RBW2 + FCL_OFF;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green =   0 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 127 ;
        Scmsft [iclr].green = 127 ;
        Scmsft [iclr].blue  = 255 ;
        iclr ++;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green = 127 ;
        Scmsft [iclr].blue  = 255 ;
        iclr ++;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green = 127 ;
        Scmsft [iclr].blue  = 127 ;
        iclr ++;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green = 255 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green = 255 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green = 127 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green = 255 ;
        Scmsft [iclr].blue  = 255 ;

/* .... on met la zone variable en arc-en-ciel 1 ................. */

        iclr = FCL_USR + FCL_OFF ;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green = 255 ;
        Scmsft [iclr].blue  = 255 ;
        iclr ++;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green =   0 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 255 ;
        Scmsft [iclr].green = 191 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 191 ;
        Scmsft [iclr].green = 191 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green = 191 ;
        Scmsft [iclr].blue  =   0 ;
        iclr ++;
        Scmsft [iclr].red   = 127 ;
        Scmsft [iclr].green = 127 ;
        Scmsft [iclr].blue  = 215 ;
        iclr ++;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green =   0 ;
        Scmsft [iclr].blue  = 255 ;
        iclr ++;
        Scmsft [iclr].red   =   0 ;
        Scmsft [iclr].green =   0 ;
        Scmsft [iclr].blue  =   0 ;

/* .... zone niveaux de gris ..................................... */

        for (iclr = FCL_GRI + FCL_OFF ;
             iclr < FCL_GRI + FCL_OFF + NGRIM;
             iclr ++) {
          jneb = (unsigned char) (((NGRIM - 
                 (iclr - FCL_GRI - FCL_OFF + 1)) * 256) / NGRIM);
          Scmsft [iclr].red   = jneb ;
          Scmsft [iclr].green = jneb ;
          Scmsft [iclr].blue  = jneb ;
        }

/* .... on duplique pour la zone editable ........................ */

        for (iclr =  FCL_ARD + FCL_OFF ;
             iclr <= FCL_GRI + FCL_OFF + NGRIM;
             iclr ++) {
           Scmsft [iclr + FCL_EDT].red   = Scmsft [iclr].red ;
           Scmsft [iclr + FCL_EDT].green = Scmsft [iclr].green ;
           Scmsft [iclr + FCL_EDT].blue  = Scmsft [iclr].blue ;
        }

/* .... on complete .............................................. */

        for (iclr = FCL_GRI + FCL_OFF + NGRIM + FCL_EDT;
             iclr < npxl;
             iclr ++) {
           Scmsft [iclr + FCL_EDT].red   = 0 ;
           Scmsft [iclr + FCL_EDT].green = 0 ;
           Scmsft [iclr + FCL_EDT].blue  = 0 ;
        }
      }
      ifcms = 1;
/* .... on fait dans un fils pour eviter les interactions avec Xview */

      iprc = fork ();
      if (iprc) return;

/* .... determiner display et root ............... */

      if (iprc) return;
      Sdsp = XOpenDisplay (NULL);
      if (Sdsp == NULL) {
         exit (1);
      }
      Sscr = XDefaultScreenOfDisplay (Sdsp);
      Hrcn = XRootWindowOfScreen (Sscr);

/* .... appel du serveur ......................... */

      XGrabServer(Sdsp);

      ncel = CellsOfScreen (Sscr);
      if (ncel < 4) {
         XUngrabServer (Sdsp);
         exit (1);
      }
    
/* .... chercher la table ....................... */

#ifdef X11R3
      ifxst = XGetStandardColormap (Sdsp, Hrcn, &Smapi, XA_RGB_DEFAULT_MAP);
#else
      ifxst = XGetRGBColormaps (Sdsp, Hrcn, &Smapi, &nmap, XA_RGB_DEFAULT_MAP);
#endif
      Smapd = DefaultColormapOfScreen (Sscr);
      jpxld = 30;
      if (ifxst != 0) {
         Sclr.pixel = jpxld;
         XQueryColor(Sdsp, Smapd, &Sclr);
         if ((Sclr.red   == 0) &&
             (Sclr.green == 257) &&
             (Sclr.blue  == 514)) {
                 Sclr.pixel = jpxld + 1;
                 XQueryColor(Sdsp, Smapd, &Sclr);
                 if ((Sclr.red   == 771) &&
                     (Sclr.green == 1028) &&
                     (Sclr.blue  == 1285)) {
                         XUngrabServer (Sdsp);
                         exit (0);
                 }
          }
      }

/* .... on libere les cellules hors de la gamme concernee ........ */
      jpxlf = 256;
      npxl  = 226;
      jrcn  = 256;
      rmult = jrcn * jrcn;
      gmult = jrcn;
      bmult = 1;

      while (ncel && 
	    !XAllocColorCells (Sdsp, Smapd, True, NULL, 0, jpxlt, ncel))
			ncel--;
      for (icel = 0; icel < ncel; icel ++) {
         if (jpxlt [icel] < jpxld || jpxlt [icel] > jpxlf) {
            XFreeColors (Sdsp, Smapd, &jpxlt [icel], 1, 0);
         }
      }

/* .... creation de la table des couleurs ........................ */

	for (ipxl = 0 ; ipxl < npxl ; ipxl ++) {
           Sclr.pixel = jpxld + ipxl;
           Sclr.red   = 255 * Scmsft [ipxl].red;
           Sclr.green = 255 * Scmsft [ipxl].green;
           Sclr.blue  = 255 * Scmsft [ipxl].blue;
           Sclr.flags = DoRed | DoGreen | DoBlue;
           XStoreColor (Sdsp, Smapd, &Sclr);
	}
        
        Smapi.colormap   = Smapd;
        Smapi.red_max    = jrcn - 1;
        Smapi.green_max  = jrcn - 1;
        Smapi.blue_max   = jrcn - 1;
        Smapi.red_mult   = rmult;
        Smapi.green_mult = gmult;
        Smapi.blue_mult  = bmult;
        Smapi.base_pixel = jpxld;

#ifdef X11R3
        XSetStandardColormap (Sdsp, Hrcn, &Smapi, XA_RGB_DEFAULT_MAP);
#else
        XSetRGBColormaps (Sdsp, Hrcn, nmap, &Smapi, XA_RGB_DEFAULT_MAP);
#endif
        XSetCloseDownMode (Sdsp, RetainPermanent);

      XUngrabServer (Sdsp);
      XCloseDisplay (Sdsp);
      exit (0);
}
E 1
