#define PRINCIPAL 0
#include "phobos.h"              /* where program specific stuff is defined */

void init_display(int argc, char **argv, MyProgram *me)
	{
	/*on est rendu a w[103] et on est limite a w[200] cf phobos.h*/
	
	if (OpenDisplay(argc, argv) == FALSE) return;

	w[0]  = MakeMenu("File");
	w[1]  = MakeMenuItem(w[0], "load_don_file",		charger_phobos, me);
	w[5]  = MakeMenuItem(w[0], "triangle_contour",		filet_contour, me);
	w[72] = MakeMenuItem(w[0], "meshing",			maillage, me);
	w[27] = MakeMenuItem(w[0], "internal_triangle",		filet_interne, me);
	w[2]  = MakeMenuItem(w[0], "global_numbering",		numerotation_globale, me);
	w[88] = MakeMenuItem(w[0], "balls",			numerotation_balls, me);
	w[59] = MakeMenuItem(w[0], "twines_surface",		nb_maille_total, me);
	w[22] = MakeMenuItem(w[0], "create_mdg_file",		creer_fichier_phobos, me);
	w[98] = MakeMenuItem(w[0], "load_mdg&sta_files",	charger_mdgsta, me);
	w[97] = MakeMenuItem(w[0], "create_sta_file ",		creer_fichier_sta, me);
	w[80] = MakeMenuItem(w[0], "read_mdgsta_files",		lire_fichier_mdgsta,me);
	w[30] = MakeMenuItem(w[0], "print", 			Genere_ps, 	NULL);
	//w[101] = MakeMenuItem(w[0], "add link", 		add_link, me);
	w[7]  = MakeMenuItem(w[0], "quit",			quitter, me);

	w[3]  = MakeMenu("Visualisation");
	w[73] = MakeMenuItem(w[3], "contour_hexa", 		Checked_dessiner_contour_hexa, me);
	w[6]  = MakeMenuItem(w[3], "contour_diamond", 		Checked_dessiner_contour_panneau, me);
	//w[94] = MakeMenuItem(w[3], "contour_panel_cutting", 	Checked_dessiner_contour_panel_cutting, me);
	w[9]  = MakeMenuItem(w[3], "contour_cable_bar", 	Checked_dessiner_contour_element, me);
	//w[87] = MakeMenuItem(w[3], "contour_winch", 		Checked_dessiner_contour_winch, me);
	//w[69] = MakeMenuItem(w[3], "contour_coulisse", 	Checked_dessiner_contour_coulisse, me);
	//w[89] = MakeMenuItem(w[3], "contour_balls", 		Checked_dessiner_contour_balls, me);
	w[10] = MakeMenuItem(w[3], "initial_link", 		Checked_dessiner_liaison, me);
	w[15] = MakeMenuItem(w[3], "calculted_link", 		Checked_dessiner_lie, me);
	w[19] = MakeMenuItem(w[3], "triangle_contour", 		Checked_filet_contour, me);
	w[20] = MakeMenuItem(w[3], "internal_triangle", 	Checked_filet_interne, me);
	w[95] = MakeMenuItem(w[3], "internal_bar", 		Checked_internal_bar, me);
	//w[32] = MakeMenuItem(w[3], "orientation_uv", 		Checked_orientation_uv, me);
	//w[33] = MakeMenuItem(w[3], "orientation_UV", 		Checked_orientation_UV, me);
	w[34] = MakeMenuItem(w[3], "orientation_xy", 		Checked_orientation_xy, me);
	w[29] = MakeMenuItem(w[3], "twines_contour", 		Checked_fils_contour, me);
	//w[90] = MakeMenuItem(w[3], "T90_axe", 		Checked_axe_T90, me);
	w[91] = MakeMenuItem(w[3], "UV_Vectors", 		Checked_UV_Vectors, me);
	w[36] = MakeMenuItem(w[3], "twines_period", 		edit, 	NULL);
	w[75] = MakeMenuItem(w[3], "axes", 			Checked_dessiner_axes, me);

	w[16]  = MakeMenu("Display");
	w[74]  = MakeMenuItem(w[16], "hexa_panel_number", 	Checked_numerotation_hexa, me);
	w[11]  = MakeMenuItem(w[16], "diamond_panel_number", 	Checked_numerotation_panneau, me);
	w[12]  = MakeMenuItem(w[16], "cable_number",		Checked_numerotation_element, me);
	//w[70]  = MakeMenuItem(w[16], "coulisse_number", 	Checked_numerotation_coulisse, me);
	w[8]   = MakeMenuItem(w[16], "bar_number", 		Checked_numerotation_barre, me);
	w[13]  = MakeMenuItem(w[16], "link_order", 		Checked_order_liaison, me);
	w[103]  = MakeMenuItem(w[16], "link_number", 		Checked_numerotation_liaison, me);
	w[85]  = MakeMenuItem(w[16], "meshing_order", 		Checked_ordre_maillage, me);
	w[28]  = MakeMenuItem(w[16], "triangle_contour_number", Checked_numerotation_triangle_contour, me);
	w[37]  = MakeMenuItem(w[16], "intern_triangle_number", 	Checked_numerotation_triangle_interieur, me);
	w[83]  = MakeMenuItem(w[16], "global_intern_triangle", 	Checked_numerotation_globale, me);
	w[56]  = MakeMenuItem(w[16], "current", 		Checked_courant, me);
	w[57]  = MakeMenuItem(w[16], "catch", 			Checked_prise, me);
	w[58]  = MakeMenuItem(w[16], "bottom_drag", 		Checked_frottement_fond, me);
	w[60]  = MakeMenuItem(w[16], "twine_surface",  		Checked_surface_fils, me);

	w[38]  = MakeMenu("Element information");
	w[39]  = MakeMenuItem(w[38], "traction_stiffness", 	Checked_raideur_traction, me);
	w[40]  = MakeMenuItem(w[38], "compression_stiffness", 	Checked_raideur_compression, me);
	w[76]  = MakeMenuItem(w[38], "opening_stiffness", 	Checked_raideur_ouverture, me);
	w[41]  = MakeMenuItem(w[38], "unstretched_length", 	Checked_longueur_repos, me);
	w[81]  = MakeMenuItem(w[38], "stretched_length", 	Checked_longueur_tendue, me);
	w[96]  = MakeMenuItem(w[38], "bar_length", 		Checked_bar_length, me);
	w[82]  = MakeMenuItem(w[38], "tension", 		Checked_tension, me);
	w[84]  = MakeMenuItem(w[38], "potential_energy", 	Checked_nrj, me);
	//w[86]  = MakeMenuItem(w[38], "discretisation_default", 	Checked_defaut_discretisation, me);
	w[42]  = MakeMenuItem(w[38], "density", 		Checked_masse_volumique, me);
	w[43]  = MakeMenuItem(w[38], "diameter", 		Checked_diametre, me);
	w[77]  = MakeMenuItem(w[38], "knot_size", 		Checked_largeur_noeud, me);
	w[44]  = MakeMenuItem(w[38], "cd_coefficient", 		Checked_coefficient_cd, me);
	w[45]  = MakeMenuItem(w[38], "f_coefficient", 		Checked_coefficient_f, me);
	//w[92]  = MakeMenuItem(w[38], "drag_panel", 		Checked_panel_drag, me);
	w[46]  = MakeMenuItem(w[38], "meshing_length", 		Checked_longueur_maillage, me);
	//w[26]  = MakeMenuItem(w[38], "meshing_type", 		Checked_type_maillage, me);
	w[64]  = MakeMenuItem(w[38], "section", 		Checked_section_element, me);
	w[65]  = MakeMenuItem(w[38], "volume", 			Checked_volume_element, me);
	w[66]  = MakeMenuItem(w[38], "mass", 			Checked_masse_element, me);
	w[67]  = MakeMenuItem(w[38], "linear_mass", 		Checked_masse_lineique, me);
	w[68]  = MakeMenuItem(w[38], "buoyancy", 		Checked_flottabilite, me);
	w[99]  = MakeMenuItem(w[38], "EI_flexion_cable", 	Checked_EI_flexion_cable, me);
	w[100] = MakeMenuItem(w[38], "angle_flexion_cable", 	Checked_angle_flexion_cable, me);

	w[47]  = MakeMenu("Node information");
	w[14]  = MakeMenuItem(w[47], "node_total", 		Checked_numerotation_total, me);
	w[23]  = MakeMenuItem(w[47], "node_global", 		Checked_numerotation_global, me);
	//w[17]  = MakeMenuItem(w[47], "node_local", 		Checked_numerotation_local, me);
	w[18]  = MakeMenuItem(w[47], "node_corner", 		Checked_numerotation_coin, me);
	//w[21]  = MakeMenuItem(w[47], "node_internal", 	Checked_numerotation_interieur, me);
	w[24]  = MakeMenuItem(w[47], "node_type", 		Checked_numerotation_type, me);
	w[48]  = MakeMenuItem(w[47], "mass", 			Checked_valeur_masse, me);
	w[49]  = MakeMenuItem(w[47], "length", 			Checked_valeur_longueur, me);
	w[50]  = MakeMenuItem(w[47], "drag_coefficient", 	Checked_valeur_cd, me);
	w[51]  = MakeMenuItem(w[47], "external_force", 		Checked_valeur_effort_exterieur, me);
	w[52]  = MakeMenuItem(w[47], "fixed / free", 		Checked_valeur_fixation, me);
	w[53]  = MakeMenuItem(w[47], "limit", 			Checked_valeur_limite, me);
	w[54]  = MakeMenuItem(w[47], "limit_orientation", 	Checked_valeur_sens_limite, me);
	w[55]  = MakeMenuItem(w[47], "symetry", 		Checked_valeur_symetrie, me);
	w[61]  = MakeMenuItem(w[47], "mesh_nb", 		Checked_nb_mailles, me);
	w[62]  = MakeMenuItem(w[47], "mesh_side_nb", 		Checked_nb_cotes_mailles, me);
	w[63]  = MakeMenuItem(w[47], "side_length", 		Checked_longueur_cotes, me);
	//w[93]  = MakeMenuItem(w[47], "panel_cutting", 	Checked_panel_cutting, me);
	
	w[4] = MakeDrawArea(X_SIZE, Y_SIZE, redisplay, me);
	SetButtonDownCB(w[4],  button_down);
	SetButtonUpCB(w[4],    button_up);

	
	SetWidgetPos(w[4 ], PLACE_UNDER, w[0], NO_CARE, NULL);
	SetWidgetPos(w[3 ], PLACE_RIGHT, w[0], NO_CARE, NULL);
	SetWidgetPos(w[16], PLACE_RIGHT, w[3], NO_CARE, NULL);
	SetWidgetPos(w[38], PLACE_RIGHT, w[16], NO_CARE, NULL);
	SetWidgetPos(w[47], PLACE_RIGHT, w[38], NO_CARE, NULL);
	ShowDisplay();
	GetStandardColors();
	}

