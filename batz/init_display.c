#include "batz.h"              /* where program specific stuff is defined */

void init_display(int argc, char **argv, MyProgram *me)
	{
  	char cvalue[4];
  	float coupe=0.5;
  	int width;
	/* debut modifdp du 4 mars 2010*/
	/*on est rendu a w[103] et on est limite a w[200] cf batz.h*/
	/* fin modifdp du 4 mars 2010*/
	if (OpenDisplay(argc, argv) == FALSE) return;
	w[0]  = MakeMenu("File");
	w[1]  = MakeMenuItem(w[0], "load_initial_file", 		charger_initial, 	me);		/*fait*/
	w[8]  = MakeMenuItem(w[0], "load_final_file",			charger_final, 		me);		/*fait*/
	//w[75] = MakeMenuItem(w[0], "portrait_mode", 			portrait, 		NULL);
	w[2]  = MakeMenuItem(w[0], "print", 				Genere_ps, 		NULL);
	w[30] = MakeMenuItem(w[0], "twines_period", 			edit, 			NULL);		/*idem*/
	w[96] = MakeMenuItem(w[0], "scale", 				edit_echelle, 		NULL);		/*idem*/
	w[76] = MakeMenuItem(w[0], "cut_depth", 			edit_coupe, 		NULL);
	/*w[78] = MakeMenuItem(w[0], "animation_slowing", 		edit_animation, 	NULL);*/
	w[79] = MakeMenuItem(w[0], "animation_parameters", 		edit_nb_animation, 	NULL);
	//w[98] = MakeMenuItem(w[0], "eigen_values_parameters", 		edit_eigenvalues, 	NULL);
	w[7]  = MakeMenuItem(w[0], "quit",				quitter, 		me);		/*idem*/

	w[3]   = MakeMenu("Visualisation");
	w[10]  = MakeMenuItem(w[3], "triangle_contour", 		Checked_dessiner_contour_triangle, 	me);	/*fait*/
	w[16]  = MakeMenuItem(w[3], "orientation_xy", 			Checked_dessiner_orientation_xy, 	me);
	w[9]   = MakeMenuItem(w[3], "cable/bar_contour", 		Checked_dessiner_contour_element, 	me);
	w[90]  = MakeMenuItem(w[3], "node_contour", 			Checked_dessiner_contour_noeud,		me);
	//w[70]  = MakeMenuItem(w[3], "coulisse_contour", 		Checked_dessiner_contour_coulisse, 	me);
	//w[87]  = MakeMenuItem(w[3], "winch_contour", 		Checked_dessiner_contour_winch, 	me);
	//w[88]  = MakeMenuItem(w[3], "ball_contour", 			Checked_dessiner_contour_ball, 		me);
	w[11]  = MakeMenuItem(w[3], "u_twines", 			Checked_dessiner_fils_u, 		me);
	w[29]  = MakeMenuItem(w[3], "v_twines", 			Checked_dessiner_fils_v, 		me);
	w[14]  = MakeMenuItem(w[3], "free_surface", 			Checked_dessiner_surface_libre, 	me);
	w[100]  = MakeMenuItem(w[3], "ballast_altitude", 		Checked_dessiner_ballast_altitude, 	me);
	w[101]  = MakeMenuItem(w[3], "cube_size", 			Checked_dessiner_cube_size, 		me);
	w[15]  = MakeMenuItem(w[3], "catch_front_surface", 		Checked_dessiner_surface_front, 	me);
	w[17]  = MakeMenuItem(w[3], "axes", 				Checked_dessiner_axes, 			me);
	w[93]  = MakeMenuItem(w[3], "repere", 				Checked_dessiner_repere, 		me);
	w[18]  = MakeMenuItem(w[3], "grid", 				Checked_dessiner_quadrillage, 		me);
	w[71]  = MakeMenuItem(w[3], "comment", 			Checked_commentaire, 			me);
	w[74]  = MakeMenuItem(w[3], "external_efforts",		Checked_efforts_externes, 		me);
	//w[97]  = MakeMenuItem(w[3], "eigen_values",			Checked_eigen_values, 			me);
	//w[83]  = MakeMenuItem(w[3], "displacement",			Checked_deplacement, 			me);
	w[85]  = MakeMenuItem(w[3], "trajectory",			Checked_trajectoire, 			me);
	w[86]  = MakeMenuItem(w[3], "immersion",			Checked_immersion, 			me);
	w[77]  = MakeMenuItem(w[3], "animation", 			Checked_animation, 			me);
	w[92]  = MakeMenuItem(w[3], "animation+video", 		Checked_animation_video, 		me);
	//w[104]  = MakeMenuItem(w[3], "animation_eigenvalue", 	Checked_animation_eigenvalue, 		me);
	w[103]  = MakeMenuItem(w[3], "symmetry/no symmetry", 	Checked_symmetry_no_symmetry, 		me);
	
	w[19] = MakeMenu("Element information");
	w[20] = MakeMenuItem(w[19], "twines_contact", 			Checked_angle_fils, 		me);
	/* debut modifdp du 4 mars 2010*/
	w[94] = MakeMenuItem(w[19], "solidity_ratio", 			Checked_solidity_ratio, 		me);
	w[102] = MakeMenuItem(w[19], "max_exit_size", 			Checked_max_exit_size, 		me);
	//w[95] = MakeMenuItem(w[19], "flow_orientation", 		Checked_flow_orientation, 		me);
	/* fin modifdp du 4 mars 2010*/
	/*w[21] = MakeMenuItem(w[19], "orientation_volume", 		Checked_orientation_volume, 	me);
	w[22] = MakeMenuItem(w[19], "volume_elementaire", 		Checked_volume_elementaire, 	me);
	w[23] = MakeMenuItem(w[19], "surface_elementaire", 		Checked_surface_elementaire, 	me);*/
	//w[84] = MakeMenuItem(w[19], "default_discretisation", 	Checked_defaut_discretisation, 	me);
	//w[24] = MakeMenuItem(w[19], "barycentre_depth", 		Checked_profondeur_barycentre, 	me);/**/
	w[25] = MakeMenuItem(w[19], "bar_number", 			Checked_numero_element, 	me);
	w[27] = MakeMenuItem(w[19], "cable_type", 			Checked_type_element, 		me);
	w[56] = MakeMenuItem(w[19], "traction_stiffness", 		Checked_raideur_traction, 	me);
	w[57] = MakeMenuItem(w[19],  "compression_stiffness", 		Checked_raideur_compression,	me);
	w[72] = MakeMenuItem(w[19],  "opening_stiffness",		Checked_raideur_ouverture,	me);
	w[58] = MakeMenuItem(w[19],  "tension", 			Checked_tension,		me);
	w[82] = MakeMenuItem(w[19],  "potential_energy", 		Checked_nrj,			me);
	w[59] = MakeMenuItem(w[19],  "unstretched_length", 		Checked_longueur_repos,		me);
	w[60] = MakeMenuItem(w[19],  "stretched_length", 		Checked_longueur_tendue,	me);
	w[61] = MakeMenuItem(w[19],  "density", 			Checked_masse_volumique,	me);
	w[62] = MakeMenuItem(w[19],  "diameter", 			Checked_diametre,		me);
	w[73] = MakeMenuItem(w[19],  "knot_size", 			Checked_largeur_noeud,		me);
	w[63] = MakeMenuItem(w[19],  "cd_coefficient", 		Checked_coefficient_cd,		me);
	w[64] = MakeMenuItem(w[19],  "f_coefficient", 			Checked_coefficient_f,		me);
	w[65] = MakeMenuItem(w[19],  "section", 			Checked_section_element,	me);
	w[66] = MakeMenuItem(w[19],  "volume", 			Checked_volume_element,		me);
	w[67] = MakeMenuItem(w[19],  "element_mass", 			Checked_masse_element,		me);
	w[68] = MakeMenuItem(w[19],  "linear_mass", 			Checked_masse_lineique,		me);
	//w[69] = MakeMenuItem(w[19],  "buoyancy", 			Checked_flottabilite,		me);
	
	w[31]  = MakeMenu("Node information");
	w[28] = MakeMenuItem(w[31], "type", 				Checked_type_noeud, 		me);
	w[33] = MakeMenuItem(w[31], "number", 				Checked_numero_noeud, 		me);
	w[32] = MakeMenuItem(w[31], "mass", 				Checked_masse_noeud, 		me);
	w[35] = MakeMenuItem(w[31], "length", 				Checked_longueur_noeud, 	me);
	w[38] = MakeMenuItem(w[31], "cd", 				Checked_cd_noeud, 		me);
	w[41] = MakeMenuItem(w[31], "external_force", 			Checked_effort_noeud, 		me);
	w[44] = MakeMenuItem(w[31], "limit", 				Checked_limite_noeud, 		me);
	w[47] = MakeMenuItem(w[31], "limit_orientation", 		Checked_sens_limite_noeud, 	me);
	w[50] = MakeMenuItem(w[31], "fixed/free", 			Checked_deplacement_noeud, 	me);
	w[53] = MakeMenuItem(w[31], "symmetry", 			Checked_symmetrie_noeud, 	me);
	w[80] = MakeMenuItem(w[31], "meshes_number", 			Checked_nb_mailles, 		me);
	
	w[4] = MakeDrawArea(X_SIZE, Y_SIZE, redisplay, me);
	SetButtonDownCB(w[4],  button_down);
	SetButtonUpCB  (w[4],  button_up);
	w[5] = MakeHorizScrollbar(X_SIZE, Rotation_Y, me);
	w[6] = MakeVertScrollbar(Y_SIZE, Rotation_X, me);
	w[81] = MakeVertScrollbar(Y_SIZE, edit_coupe2, me);
	w[89] = MakeVertScrollbar(Y_SIZE, edit_temps1, me);

          SetScrollbar(w[5] , (float) 0.0, (float) 360.0, (float) 1.0);
          SetScrollbar(w[6] , (float) 0.0, (float) 360.0, (float) 1.0);
          SetScrollbar(w[81], (float) 0.0, (float)   1.0, (float) 0.2);
          SetScrollbar(w[89], (float) 0.0, (float)   1.0, (float) 0.1);

  	width = 40;
  	sprintf(cvalue, "%d", 0);
  	w[12]  = MakeStringEntry(cvalue, width, Entry_Rotation_X, me);

  	sprintf(cvalue, "%d", 0);
  	w[13]  = MakeStringEntry(cvalue, width, Entry_Rotation_Y, me);

  	sprintf(cvalue, "%d", 0);
  	w[91]  = MakeStringEntry(cvalue, width, Entry_Temps, me);

  	SetWidgetPos(w[12], PLACE_RIGHT, w[4], PLACE_UNDER, w[6]);
  	SetWidgetPos(w[13], PLACE_UNDER, w[4], PLACE_RIGHT, w[5]);
  	SetWidgetPos(w[91], PLACE_RIGHT, w[12], PLACE_UNDER, w[6]);
  	SetWidgetPos(w[6 ], PLACE_RIGHT, w[4], NO_CARE, NULL); /* curs v 2 */
  	SetWidgetPos(w[81], PLACE_RIGHT, w[6], NO_CARE, NULL); /* curs v 2 */
  	SetWidgetPos(w[89], PLACE_RIGHT, w[81], NO_CARE, NULL); /* curs v 2 */
	SetWidgetPos(w[5 ], PLACE_UNDER, w[4], NO_CARE, NULL); /* curs h 1 */
	SetWidgetPos(w[4 ], PLACE_UNDER, w[0], NO_CARE, NULL);
	SetWidgetPos(w[3 ], PLACE_RIGHT, w[0], NO_CARE, NULL);
	SetWidgetPos(w[19], PLACE_RIGHT, w[3], NO_CARE, NULL);
	SetWidgetPos(w[31], PLACE_RIGHT, w[19], NO_CARE, NULL);

	ShowDisplay();
	GetStandardColors();
	}
	
void init_display_text(int argc, char **argv, MyProgram *me)
	{
  	char cvalue[4];
  	float coupe=0.5;
  	int width;
	
	if (OpenDisplay(argc, argv) == FALSE) return;
	
	w[0]  = MakeMenu("Fichier");
	w[4] = MakeDrawArea(X_SIZE, Y_SIZE, redisplay, me);
	SetWidgetPos(w[4 ], PLACE_UNDER, w[0], NO_CARE, NULL);

	ShowDisplay();
	GetStandardColors();
	}

