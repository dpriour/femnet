h36717
s 00114/00000/00000
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
#include <faixvg.h>
#define  LTABCOU (LCMSF-(JPXLD-FCL_OFF))

int
savimg_ (char *Pzfil, int lzfil)
                    /* nom du fichier                       */
            
/*
 *  savimg = sauvegarde de l'image dans un fichier raster
 *  version %I% du %G%
 */
{
      int         ichr1, ichr2, lfilw;
      int         ilig, ncol;
      DIMFSTRING  (zfil,64); 
      FILE        *Pdfil;
      BYTE        *Pjimg;
      struct rasterfile entetras;
      extern char *fortoc (); 
      extern void lenchr_ ();
      extern void inistr_ ();
      extern void prtmsg_ ();

/* .... ouverture fichier ......................................*/
      
        lenchr_ (Pzfil, &ichr1, &ichr2, lzfil);
        ichr1 = ichr1 - 1;
        lfilw = ichr2 - ichr1;
        inistr (zfil, fortoc (Pzfil+ichr1, lfilw), 64);

        if (( Pdfil = fopen (zfil, "w")) == NULL ) {
	  int ktbl = 0;
	  int nblc = 1;
	  int klib = 23;
	  int ktrt = 0;
	  prtmsg_ ( &ktbl, &nblc, &klib, &ktrt);
          printf ( " %s\n", zfil);
          return (1);
	}

/* .... reduction eventuelle .................................*/

        if (jgro > 1) {
           rdcpxr (PSimg, PSimgw, jprf, iclrb);
        }

/* .... header .................................................*/
      
        entetras.ras_magic = RAS_MAGIC;
        entetras.ras_width = PSimgw->x;
        entetras.ras_height = PSimgw->y;
        entetras.ras_depth = PSimgw->p;
        entetras.ras_length = (PSimgw->x / BYTBIT) * PSimgw->x;
        entetras.ras_type = RT_STANDARD;
        if (jprf > 1) {
           entetras.ras_maptype   = RMT_EQUAL_RGB;
           entetras.ras_maplength = 3 * LTABCOU;
        } else {
           entetras.ras_maptype   = RMT_NONE;
           entetras.ras_maplength = 0;
        }
       (void) fwrite ((BYTE *) &entetras, sizeof(entetras), 1, Pdfil);

/* .... Couleur .................................*/

        if (jprf > 1) {
	   BYTE jredt [LCMSF];  
	   BYTE jgrnt [LCMSF]; 
	   BYTE jblut [LCMSF]; 
	   int iclr;
	
/* ........... table des couleurs .............*/

                      
	   for (iclr = 0; iclr < JPXLD - FCL_OFF; iclr++) {
             jredt [iclr] = (BYTE) 0;
             jgrnt [iclr] = (BYTE) 0;
             jblut [iclr] = (BYTE) 0;
           }
	   for (iclr = JPXLD - FCL_OFF; iclr < LCMSF; iclr++) {
             jredt [iclr] = (BYTE) Scmsft [iclr-(JPXLD-FCL_OFF)].red;
             jgrnt [iclr] = (BYTE) Scmsft [iclr-(JPXLD-FCL_OFF)].green;
             jblut [iclr] = (BYTE) Scmsft [iclr-(JPXLD-FCL_OFF)].blue;
           }
           (void) fwrite (jredt, LTABCOU, 1, Pdfil);
           (void) fwrite (jgrnt, LTABCOU, 1, Pdfil);
           (void) fwrite (jblut, LTABCOU, 1, Pdfil);

/* .... ecriture de la bitmap .............................*/

           Pjimg = (BYTE *) PSimgw->d;
           for (ilig = 0 ; ilig < PSimgw->y ; ilig ++) {
              (void) fwrite (Pjimg, PSimgw->x, 1, Pdfil);
              Pjimg += PSimgw->xv;
           }

/* ....Noir et Blanc ......................................*/

       } else {

/* .... ecriture de la bitmap .............................*/

           Pjimg = (BYTE *) PSimgw->d;
           ncol  = (PSimgw->x + BYTBIT - 1) / BYTBIT;
           for (ilig = 0 ; ilig < PSimgw->y ; ilig ++) {
              (void) fwrite (Pjimg, ncol, 1, Pdfil);
              Pjimg += PSimgw->xv / BYTBIT;
           }
       }
;
        fclose (Pdfil);  
        return (0);
}
E 1
