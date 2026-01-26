h23426
s 00083/00000/00000
d D 1.1 95/10/17 12:16:34 molagnon 1 0
c date and time created 95/10/17 12:16:34 by molagnon
e
u
U
f e 0
t
T
I 1
#include <fairas.h>
#include "../include/faixvg.h"
/*
 *    rstimg = restauration de l'image depuis un fichier
 *     version %I% du %G%
 */

int rstimg_ (char *Pzfil, int lzfil)
                    /* nom du fichier */
            

{
      int         ichr1, ichr2, lfilw;
      DIMFSTRING  (zfil,64); 
      FILE        *Pdfil;
      struct rasterfile entetras;
      int ilig, icol, ncol, nlig;
      BYTE *Pjimg;
      BYTE zbuft[3*LCMSF];
      extern char *fortoc (); 
      extern void lenchr_ ();
      extern void prtmsg_ ();
      extern void inistr_ ();

/* .... ouverture fichier ......................................*/
      
        lenchr_ (Pzfil, &ichr1, &ichr2, lzfil);
        ichr1 = ichr1 - 1;
        lfilw = ichr2 - ichr1;
        inistr (zfil, fortoc (Pzfil+ichr1, lfilw), 64);

        if (( Pdfil = fopen (zfil, "r")) == NULL ) {
	  int ktbl = 0;
	  int nblc = 1;
	  int klib = 23;
	  int ktrt = 0;
	  prtmsg_ (&ktbl, &nblc, &klib, &ktrt);
          printf (" %s\n", zfil);
          return (1);
	}


/* .... lecture dans le fichier ...............................*/

       (void) fread ((BYTE *) &entetras, sizeof(entetras), 1, Pdfil);
       if (entetras.ras_magic != RAS_MAGIC ) {
	  int ktbl = 0;
	  int nblc = 1;
	  int klib = 23;
	  int ktrt = 0;
	  prtmsg_ (&ktbl, &nblc, &klib, &ktrt);
          printf (" %s\n", zfil);
          fclose (Pdfil);
          return (2);
       }
       ncol = entetras.ras_width;
       nlig = entetras.ras_height;
       Pjimg = (BYTE *) PSimgw->d;
       if (entetras.ras_maptype != RMT_NONE ) {

         (void) fread ((BYTE *) zbuft, entetras.ras_maplength, 1, Pdfil);

         for (ilig = 0 ; ilig < nlig ; ilig ++) {
           (void) fread (Pjimg, ncol, 1, Pdfil);
           Pjimg += PSimgw->xv;
         }

       } else {
         for (ilig = 0 ; ilig < nlig ; ilig ++) {
           (void) fread (Pjimg, ncol / BYTBIT, 1, Pdfil);
           Pjimg += PSimgw->xv / BYTBIT;
         }
       }

/* .... expansion eventuelle .................................*/

        if (jgro > 1) {
           xpdpxr (PSimgw, PSimg, jprf, iclrb);
        }

        fclose (Pdfil);  
        return (0);
}
E 1
