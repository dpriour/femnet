h21853
s 00044/00000/00000
d D 1.1 95/10/17 12:16:20 molagnon 1 0
c date and time created 95/10/17 12:16:20 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
#include <xview/icon_load.h>

void                        
chgicn_ (char *Pzficn, char *Pzlicn, int lficn, int llicn)
                /* nom du fichier de l'icone      */
                /* libelle de l'icone    	  */
            
            

/*
 *      chgicn = chargement d'une icone utilisateur
 *      auteur = s.coudray   ifremer/dit/som
 *      version %I% du %G%                                              
 */
     
{ 
	char	zerr [256];	/* buffer message d'erreur */
	char	zficw [64];	/* buffer nom du fichier */
	int	kerr;
        int     ichr1, ichr2, lficnw;

	extern char *fortoc (); 
	extern void lenchr_ (); 

/* ... chargement du fichier icone dans Sicn .....*/

        lenchr_ (Pzficn, &ichr1, &ichr2, lficn);
        ichr1 = ichr1 - 1;
        lficnw = ichr2 - ichr1;
        strcpy (zficw, fortoc (Pzficn+ichr1, lficnw));
	kerr = icon_load (Sicn, zficw, zerr);

	if (kerr == 0) {
          lenchr_ (Pzlicn, &ichr1, &ichr2, llicn);
	  if ((ichr2 - ichr1) != 0) {
            icon_set (Sicn, XV_LABEL, fortoc (Pzlicn, llicn), 0);
	  }
    	  xv_set (Hfimg, FRAME_ICON, Sicn, 0);
	}

}

	
E 1
