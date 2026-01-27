#define PRINCIPAL 0
#include "4c19.h"

void libere_memoire()
	{
	/* libere la memoire alloue par malloc */
	
  	int zi,pa;
	if (Structure.type_solver == 1)
	{
		if (xze		!= NULL)        free(xze);
		if (ze		!= NULL)        free(ze);
	}
	else if (Structure.type_solver == 2)
	{
/*		if (ka!= NULL)	free(ka);
		if (a!= NULL)	free(a);
		if (ja!= NULL)	free(ja);*/
		if (ia!= NULL)	free(ia);
		if (A!= NULL)	free(A);
		if (P!= NULL)	free(P);
	}

	if (xze_modif	!= NULL)        free(xze_modif);
	if (ze_modif	!= NULL)        free(ze_modif);

	if (xze_contact	!= NULL)        free(xze_contact);
	if (ze_contact	!= NULL)        free(ze_contact);
	
	/*
	if (xrang	!= NULL)        free(xrang);
	if (rang	!= NULL)        free(rang);
	*/

	if (Sortie_texte.noeud1_distance		!= NULL)       	free(Sortie_texte.noeud1_distance);
	if (Sortie_texte.noeud2_distance		!= NULL)        free(Sortie_texte.noeud2_distance);
	if (Sortie_texte.decimale_distance		!= NULL)        free(Sortie_texte.decimale_distance);
	if (Sortie_texte.comment_distance		!= NULL)        free(Sortie_texte.comment_distance);
	if (Sortie_texte.noeud_effort			!= NULL)        free(Sortie_texte.noeud_effort);
	if (Sortie_texte.axe_effort			!= NULL)        free(Sortie_texte.axe_effort);
	if (Sortie_texte.decimale_effort		!= NULL)        free(Sortie_texte.decimale_effort);
	if (Sortie_texte.comment_effort			!= NULL)        free(Sortie_texte.comment_effort);
	if (Sortie_texte.element_tension		!= NULL)        free(Sortie_texte.element_tension);
	if (Sortie_texte.element_extremite		!= NULL)        free(Sortie_texte.element_extremite);
	if (Sortie_texte.decimale_tension_element	!= NULL)        free(Sortie_texte.decimale_tension_element);
	if (Sortie_texte.comment_tension_element	!= NULL)        free(Sortie_texte.comment_tension_element);
	if (Sortie_texte.coulisse_tension		!= NULL)        free(Sortie_texte.coulisse_tension);
	if (Sortie_texte.coulisse_extremite		!= NULL)        free(Sortie_texte.coulisse_extremite);
	if (Sortie_texte.decimale_tension_coulisse  	!= NULL) 	free(Sortie_texte.decimale_tension_coulisse);
	if (Sortie_texte.comment_tension_coulisse	!= NULL)        free(Sortie_texte.comment_tension_coulisse);
	if (Sortie_texte.noeud_position			!= NULL)        free(Sortie_texte.noeud_position);
	if (Sortie_texte.axe_position			!= NULL)        free(Sortie_texte.axe_position);
	if (Sortie_texte.decimale_position		!= NULL)        free(Sortie_texte.decimale_position);
	if (Sortie_texte.comment_position		!= NULL)        free(Sortie_texte.comment_position);

	/*
	if (wa						!= NULL)        free(wa);
	if (wasurf					!= NULL)        free(wasurf);
	if (waemodif					!= NULL)        free(waemodif);
	if (waecontact					!= NULL)        free(waecontact);
	if (waelem					!= NULL)        free(waelem);
	if (wanoeud					!= NULL)        free(wanoeud);
	if (wf						!= NULL)        free(wf);
	if (wh						!= NULL)        free(wh);
	if (wv						!= NULL)        free(wv);
	if (mh						!= NULL)        free(mh);
	if (mvh						!= NULL)        free(mvh);
	if (mgh						!= NULL)        free(mgh);
	if (wf1						!= NULL)        free(wf1);
	if (wf2						!= NULL)        free(wf2);
	if (mvb						!= NULL)        free(mvb);
	if (mgb						!= NULL)        free(mgb);
	if (wfcodend					!= NULL)        free(wfcodend);

	if (fixation					!= NULL)        free(fixation);
	if (fixa					!= NULL)        free(fixa);
	if (whs						!= NULL)        free(whs);
	if (wl						!= NULL)        free(wl);
	*/

  	for (zi=1;zi<=NOMBRE_COULISSES;zi++)
  		{ 
		if (Coulisse[zi].noeud			!= NULL)        free(Coulisse[zi].noeud);
		if (Coulisse[zi].longueur		!= NULL)        free(Coulisse[zi].longueur);
		}
	for (pa=1;pa<=Structure.nb_winch;pa++)
		{
		if (Winch[pa].noeud					!= NULL)        free(Winch[pa].noeud);	
		if (Winch[pa].prop					!= NULL)        free(Winch[pa].prop);	
		if (Winch[pa].exit					!= NULL)        free(Winch[pa].exit);	
		if (Winch[pa].longueur					!= NULL)        free(Winch[pa].longueur);	
		}
	if (Ball.noeud							!= NULL)        free(Ball.noeud);	
	if (Ball.type							!= NULL)        free(Ball.type);	
	if (Ball.birth_time						!= NULL)        free(Ball.birth_time);	
	if (Ball.stiffness						!= NULL)        free(Ball.stiffness);	
	if (Ball.radius							!= NULL)        free(Ball.radius);	
	if (Orientation_netting.panel					!= NULL)        free(Orientation_netting.panel);
	if (Orientation_netting.tab_mesh				!= NULL)        free(Orientation_netting.tab_mesh);
	if (Orientation_netting.tab_netting				!= NULL)        free(Orientation_netting.tab_netting);
	if (Orientation_netting.tab_drag				!= NULL)        free(Orientation_netting.tab_drag);
	if (Opening_angle.panel						!= NULL)        free(Opening_angle.panel);
	if (Opening_angle.tab						!= NULL)        free(Opening_angle.tab);
	if (Opening_mesh.panel						!= NULL)        free(Opening_mesh.panel);
	if (Opening_mesh.tab						!= NULL)        free(Opening_mesh.tab);
	if (Opening_angle_stripe.panel					!= NULL)        free(Opening_angle_stripe.panel);
	if (Opening_angle_stripe.tab					!= NULL)        free(Opening_angle_stripe.tab);
	if (Prise.panel_meridian					!= NULL)        free(Prise.panel_meridian);
	if (Prise.panel_curvilinear					!= NULL)        free(Prise.panel_curvilinear);
	if (Prise.perimeter_y						!= NULL)        free(Prise.perimeter_y);
	if (Prise.perimeter_z						!= NULL)        free(Prise.perimeter_z);
	if (Prise.meridian_x						!= NULL)        free(Prise.meridian_x);
	if (Prise.meridian_r						!= NULL)        free(Prise.meridian_r);
	if (Prise.meridian_y						!= NULL)        free(Prise.meridian_y);
	if (Prise.meridian_z						!= NULL)        free(Prise.meridian_z);
	for (pa=1;pa<=Catch2_volume[Structure.nb_catch2_volume].nb_panel_catch2;pa++)
		{
		if (Catch2_volume[pa].panel_catch2			!= NULL)        free(Catch2_volume[pa].panel_catch2);
		}
	for (pa=1;pa<=Cage_volume[Structure.nb_cage_volume].nb_panel_catch2;pa++)
		{
		if (Cage_volume[pa].panel_catch2			!= NULL)        free(Cage_volume[pa].panel_catch2);
		if (Volume_cage[pa].panel_catch2			!= NULL)        free(Volume_cage[pa].panel_catch2);
		}
	for (pa = 1 ; pa <= Opening_mesh.nb_panel ; pa++)
		{
		if (Opening_mesh.tab[pa]				!= NULL)        free(Opening_mesh.tab[pa]);
		}
	if (Opening_mesh.tab						!= NULL)        free(Opening_mesh.tab);

	if (Opening_angle_stripe.fromx				!= NULL)        free(Opening_angle_stripe.fromx);
	if (Opening_angle_stripe.tox					!= NULL)        free(Opening_angle_stripe.tox);
	if (Opening_angle_stripe.tab					!= NULL)        free(Opening_angle_stripe.tab);
	}



