h58489
s 00030/00000/00000
d D 1.1 95/10/17 12:16:19 molagnon 1 0
c date and time created 95/10/17 12:16:19 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvt.h"

/* 
 *   afftxt =  affiche d'un texte contenu dans un fichier dans une 
 *             fenetre tty.
 *   auteurs : M.Olagnon
 *             s.coudray ifremer/diti/som
 *   version 1.2 du 11/3/92
 */

afftxt_ (char *Pzfic, int llzfic)
{
        int	ichr1, ichr2;
	int	lztmp;

/* ... mise au format C de la chaine ........................*/

        lenchr_ (Pzfic, &ichr1, &ichr2, llzfic);
        lztmp = ichr2 - ichr1 + 1;
        inistr (Ztxtf, fortoc ((Pzfic + ichr1 - 1), lztmp), 128);

/* ... envoi du fichier dans la fenetre .....................*/

        xv_set (Stxtw, 
		TEXTSW_FILE,            Ztxtf,
		TEXTSW_INSERTION_POINT, TEXTSW_INFINITY,
		0);

	return (0);
}
E 1
