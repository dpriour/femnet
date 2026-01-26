h07425
s 00050/00000/00000
d D 1.1 95/10/17 12:16:25 molagnon 1 0
c date and time created 95/10/17 12:16:25 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvt.h"
#include <signal.h>

/* 
 =======================================================================

     fintxt.c =  fin d'affichage d'une fenetre de texte 
                   
     parametres =
	variables globales:
	Stxtw	= structure fenetre textsw

     appels =

     generiques =
	frm = frame
	txt = texte

	P   = pointeur
	S   = structure
	g   = variable globale
        tg  = tableau en variable globale

     auteur = s.coudray		ifremer/diti/som
     version 1.2 du 2/27/91
 
 =======================================================================
*/

fintxt_ (void)
{
	fclose (stdin) ;

	/*.......... attente d'un quit ...............................*/


        xv_set (Spnlc, 
			WIN_SHOW, 	TRUE,
			0);

        xv_set (Stxtw, 
			TEXTSW_READ_ONLY, 1,
			WIN_SHOW, 	TRUE,
			0);

        signal (SIGALRM, SIG_IGN);
	window_main_loop (Sfrmt);
        signal (SIGALRM, SIG_DFL);
	return (0);
}
E 1
