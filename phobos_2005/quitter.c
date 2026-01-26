#define PRINCIPAL 0
#include "phobos.h"

void quitter(Widget w, void *data)
	{
	int pa;
	if (flag_ps == TRUE)
		{
		}
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
  		if ( panneau[pa].noeud_interieur	!= NULL) 	free(panneau[pa].noeud_interieur);
  		if ( panneau[pa].noeud_contour 		!= NULL) 	free(panneau[pa].noeud_contour);
  		if ( panneau[pa].suivant_contour 	!= NULL) 	free(panneau[pa].suivant_contour);
  		if ( panneau[pa].noeud_cote 		!= NULL) 	free(panneau[pa].noeud_cote);
  		if ( panneau[pa].prop_cote 		!= NULL) 	free(panneau[pa].prop_cote);
  		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{
  		if ( pan_hexa[pa].noeud_interieur	!= NULL) 	free(pan_hexa[pa].noeud_interieur);
  		if ( pan_hexa[pa].noeud_contour 	!= NULL) 	free(pan_hexa[pa].noeud_contour);
  		if ( pan_hexa[pa].suivant_contour 	!= NULL) 	free(pan_hexa[pa].suivant_contour);
  		if ( pan_hexa[pa].noeud_cote 		!= NULL) 	free(pan_hexa[pa].noeud_cote);
  		if ( pan_hexa[pa].prop_cote 		!= NULL) 	free(pan_hexa[pa].prop_cote);
  		}
	for (pa=1;pa<=Structure.nb_lien;pa++)
		{
  		if ( Lien[pa].type			!= NULL) 	free(Lien[pa].type);
  		if ( Lien[pa].structure			!= NULL) 	free(Lien[pa].structure);
  		if ( Lien[pa].extremite			!= NULL) 	free(Lien[pa].extremite);
  		if ( Lien[pa].noeud			!= NULL) 	free(Lien[pa].noeud);
  		}
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{
  		if ( element[pa].noeud			!= NULL) 	free(element[pa].noeud);
  		if ( element[pa].barre			!= NULL) 	free(element[pa].barre);
  		if ( element[pa].prop			!= NULL) 	free(element[pa].prop);
  		}
	exit(0);
	}

