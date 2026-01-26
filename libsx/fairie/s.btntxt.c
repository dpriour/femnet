h44392
s 00072/00000/00000
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
 =======================================================================

     btntxt_ = initialisation des boutons de la souris pour la fenetre
               texte 
                   
     parametres =
	variables globales :
	Stxtwxt = 
	Stxtw = 
	
     appels =
	evntxt = traitement des evenements ( passee par adresse)

     generiques =
	txt = texte

	P   = pointeur
	S   = structure

     auteur = s.coudray		ifremer/diti/som
     version 1.1 du 2/27/91
 
 =======================================================================
*/


btntxt_ (void)
{	
extern void evntxt (Textsw Stxtw, Event *PSevn);


	/*... test si fenetre existe .................................*/

	if ( Sfrmt == NULL) {
	  return;
	}

	/*... conduite a tenir en cas d'evenement.....................*/

	xv_set (Stxtw, WIN_CONSUME_EVENTS,
		WIN_MOUSE_BUTTONS,
		WIN_UP_EVENTS,
		WIN_LEFT_KEYS,
		0,
		WIN_EVENT_PROC, evntxt, 
		0);
        
	/*... fin .................................*/
}


void evntxt (Textsw Stxtw, Event *PSevn)
{

	/* .... fonctions ................ */
 
	if (event_is_key_left (PSevn) && event_is_up (PSevn)) {
          if (event_id (PSevn) == KEY_LEFT (7)) {
            xv_set (Sfrmt, FRAME_CLOSED, TRUE, 0);
          }
          if (event_id (PSevn) == KEY_LEFT (5)) {
            xv_set (Sfrmt, WIN_SHOW, TRUE, 0);
          }
          if (event_id (PSevn) == KEY_LEFT (1)) {
            xv_destroy_safe (Sfrmt);
          }
        } 
 
}
E 1
