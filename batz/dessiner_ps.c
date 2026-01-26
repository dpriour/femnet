#include "batz.h"

void dessiner()
	{
	int pa,no,mode_u,mode_v,condition_draw_element,zi;
	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();
	
	if ((Flag_Fichier_final_charge == 1) || (Flag_Fichier_initial_charge == 1))
		{
		printf("avant lecture_des \n");/**/
		lecture_des(); /*lecture des ordres de dessin*/
		printf("apres lecture_des \n");/**/
		}

	ClearDrawArea();
	Color(WHITE);
	Move_to((float)0.0,(float)0.0);
	Line_to((float)1.0,(float)0.0);
	Line_to((float)1.0,(float)1.0);
	Line_to((float)0.0,(float)1.0);
	Line_to((float)0.0,(float)0.0);
	Surface_end();	/*faire un fond blanc */	

	mode_u = GetMenuItemChecked(w[11]);
	mode_v = GetMenuItemChecked(w[29]);
	if (((mode_u == 1) || (mode_v == 1)) && (Flag_Fichier_final_charge   == 1)) rotation_fils();
	/*printf("NOMBRE_SURFACES = %8d \n",NOMBRE_SURFACES);
	printf("NOMBRE_SURF_HEXA = %8d \n",NOMBRE_SURF_HEXA);
	printf("NOMBRE_ELEMENTS = %8d \n",NOMBRE_ELEMENTS);
	printf("NOMBRE_COULISSES = %8d \n",NOMBRE_COULISSES);
	printf("NOMBRE_WINCHS = %8d \n",NOMBRE_WINCHS);
	printf("Ball.nb = %8d \n",Ball.nb);
	printf("NOMBRE_NOEUDS = %8d \n",NOMBRE_NOEUDS);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES+NOMBRE_WINCHS+Ball.nb+NOMBRE_NOEUDS;no++)
		{ 
		pa = profondeur[no];
		if (pa == 0) printf("attention : pa = %8d no = %8d   \n",pa,no);
		if ((pa > 0) && (pa <= NOMBRE_SURFACES))
			{
			/*diamond netting*/
			pa = pa - 0;
			/*printf("pa = %8d panel %d color = %8d   \n",pa,Surface[pa].type,panneau[Surface[pa].type].flag_dessin);*/
			if (panneau[Surface[pa].type].flag_dessin != 0)
				{
				if (GetMenuItemChecked(w[16]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[80]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[10]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[11]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[29]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[20]) == 1) white_triangle_diamond(pa);
				/* debut modifdp du 4 mars 2010*/
				if (GetMenuItemChecked(w[94]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[102]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[95]) == 1) white_triangle_diamond(pa);
				/* fin modifdp du 4 mars 2010*/
				if (GetMenuItemChecked(w[21]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[22]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[23]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[84]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[25]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[27]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[56]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[56]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[57]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[72]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[59]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[61]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[62]) == 1) white_triangle_diamond(pa);	
				if (GetMenuItemChecked(w[73]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[63]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[64]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[85]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[83]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[86]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[58]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[82]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[60]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[65]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[66]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[67]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[68]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[69]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[28]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[33]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[32]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[35]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[38]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[41]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[44]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[47]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[50]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[53]) == 1) white_triangle_diamond(pa);
				if (GetMenuItemChecked(w[24]) == 1) white_triangle_diamond(pa);

				if (GetMenuItemChecked(w[16]) == 1) draw_orientation_xy_diamond(pa);
				if (GetMenuItemChecked(w[80]) == 1) draw_nb_mailles_diamond(pa);
				if (GetMenuItemChecked(w[11]) == 1) draw_fils_u(pa);
				if (GetMenuItemChecked(w[29]) == 1) draw_fils_v(pa);
				if (GetMenuItemChecked(w[10]) == 1) draw_contour_triangle_diamond(pa);
				if (GetMenuItemChecked(w[20]) == 1) draw_angle_fils(pa);
				/* debut modifdp du 4 mars 2010*/
				if (GetMenuItemChecked(w[94]) == 1) draw_solidity_ratio(pa);
				if (GetMenuItemChecked(w[102]) == 1) draw_max_exit_size(pa);
				if (GetMenuItemChecked(w[95]) == 1) draw_flow_orientation(pa);
				/* fin modifdp du 4 mars 2010*/
				if (GetMenuItemChecked(w[21]) == 1) draw_orientation_volume_diamond(pa);
				if (GetMenuItemChecked(w[22]) == 1) draw_volume_elementaire_diamond(pa);
				if (GetMenuItemChecked(w[23]) == 1) draw_surface_elementaire_diamond(pa);
				if (GetMenuItemChecked(w[84]) == 1) draw_defaut_discretisation_diamond(pa);
				if (GetMenuItemChecked(w[25]) == 1) draw_numero_element_diamond(pa);
				if (GetMenuItemChecked(w[27]) == 1) draw_type_element_diamond(pa);
				if (GetMenuItemChecked(w[56]) == 1) draw_raideur_traction_diamond(pa);
				if (GetMenuItemChecked(w[56]) == 1) draw_raideur_traction_diamond(pa);
				if (GetMenuItemChecked(w[57]) == 1) draw_raideur_compression_diamond(pa);
				if (GetMenuItemChecked(w[72]) == 1) draw_raideur_ouverture_diamond(pa);
				if (GetMenuItemChecked(w[59]) == 1) draw_longueur_repos_diamond(pa);
				if (GetMenuItemChecked(w[61]) == 1) draw_masse_volumique_diamond(pa);
				if (GetMenuItemChecked(w[62]) == 1) draw_diametre_diamond(pa);	
				if (GetMenuItemChecked(w[73]) == 1) draw_largeur_noeud_diamond(pa);
				if (GetMenuItemChecked(w[63]) == 1) draw_coefficient_cd_diamond(pa);
				if (GetMenuItemChecked(w[64]) == 1) draw_coefficient_f_diamond(pa);
				if (GetMenuItemChecked(w[83]) == 1) draw_deplacement_diamond(pa);
				if (GetMenuItemChecked(w[86]) == 1) draw_immersion_surface(pa);
				if (GetMenuItemChecked(w[58]) == 1) draw_tension_diamond(pa);
				if (GetMenuItemChecked(w[82]) == 1) draw_nrj_diamond(pa);
				if (GetMenuItemChecked(w[60]) == 1) draw_longueur_tendue_diamond(pa);
				if (GetMenuItemChecked(w[65]) == 1) draw_section_diamond(pa);
				if (GetMenuItemChecked(w[66]) == 1) draw_volume_diamond(pa);
				if (GetMenuItemChecked(w[67]) == 1) draw_masse_diamond(pa);
				if (GetMenuItemChecked(w[68]) == 1) draw_masse_lineique_diamond(pa);
				if (GetMenuItemChecked(w[69]) == 1) draw_flottabilite_diamond(pa);
				if (GetMenuItemChecked(w[28]) == 1) draw_type_noeud_diamond(pa);
				if (GetMenuItemChecked(w[33]) == 1) draw_numero_noeud_diamond(pa);
				if (GetMenuItemChecked(w[32]) == 1) draw_masse_noeud_diamond(pa);
				if (GetMenuItemChecked(w[35]) == 1) draw_longueur_noeud_diamond(pa);
				if (GetMenuItemChecked(w[38]) == 1) draw_cd_noeud_diamond(pa);
				if (GetMenuItemChecked(w[41]) == 1) draw_effort_noeud_diamond(pa);
				if (GetMenuItemChecked(w[44]) == 1) draw_limite_noeud_diamond(pa);
				if (GetMenuItemChecked(w[47]) == 1) draw_sens_limite_noeud_diamond(pa);
				if (GetMenuItemChecked(w[50]) == 1) draw_deplacement_noeud_diamond(pa);
				if (GetMenuItemChecked(w[53]) == 1) draw_symmetrie_noeud_diamond(pa);
				if (GetMenuItemChecked(w[24]) == 1) draw_profondeur_barycentre_diamond(pa,no);
				if (GetMenuItemChecked(w[85]) == 1) draw_trajectoire_surface(pa);
				}
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA))
			{
			/*hexagonal netting*/
			pa = pa - NOMBRE_SURFACES;
			if (TypeSurfHexa[Surf_Hexa[pa].type].flag_dessin != 0)
				{
				if (GetMenuItemChecked(w[16]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[80]) == 1) white_triangle_hexa(pa);/**/
				if (GetMenuItemChecked(w[10]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[11]) == 1 && GetMenuItemChecked(w[29]) == 0) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[29]) == 1 && GetMenuItemChecked(w[11]) == 0) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[11]) == 1 && GetMenuItemChecked(w[29]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[21]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[22]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[23]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[25]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[27]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[56]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[56]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[57]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[59]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[61]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[62]) == 1) white_triangle_hexa(pa);	
				if (GetMenuItemChecked(w[63]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[64]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[83]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[58]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[82]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[60]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[65]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[66]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[67]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[68]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[69]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[28]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[33]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[32]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[35]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[38]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[41]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[44]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[47]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[50]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[53]) == 1) white_triangle_hexa(pa);
				if (GetMenuItemChecked(w[24]) == 1) white_triangle_hexa(pa);

				if (GetMenuItemChecked(w[16]) == 1) draw_orientation_xy_hexa(pa);
				if (GetMenuItemChecked(w[80]) == 1) draw_nb_mailles_hexa(pa);/**/
				if (GetMenuItemChecked(w[10]) == 1) draw_contour_triangle_hexa(pa);
				if (GetMenuItemChecked(w[11]) == 1 && GetMenuItemChecked(w[29]) == 0) draw_fils_u_hexa(pa);
				if (GetMenuItemChecked(w[29]) == 1 && GetMenuItemChecked(w[11]) == 0) draw_fils_v_hexa(pa);
				if (GetMenuItemChecked(w[11]) == 1 && GetMenuItemChecked(w[29]) == 1) draw_fils_uv_hexa(pa);
				if (GetMenuItemChecked(w[21]) == 1) draw_orientation_volume_hexa(pa);
				if (GetMenuItemChecked(w[22]) == 1) draw_volume_elementaire_hexa(pa);
				if (GetMenuItemChecked(w[23]) == 1) draw_surface_elementaire_hexa(pa);
				if (GetMenuItemChecked(w[25]) == 1) draw_numero_element_hexa(pa);
				if (GetMenuItemChecked(w[27]) == 1) draw_type_element_hexa(pa);
				if (GetMenuItemChecked(w[56]) == 1) draw_raideur_traction_hexa(pa);
				if (GetMenuItemChecked(w[56]) == 1) draw_raideur_traction_hexa(pa);
				if (GetMenuItemChecked(w[57]) == 1) draw_raideur_compression_hexa(pa);
				if (GetMenuItemChecked(w[59]) == 1) draw_longueur_repos_hexa(pa);
				if (GetMenuItemChecked(w[61]) == 1) draw_masse_volumique_hexa(pa);
				if (GetMenuItemChecked(w[62]) == 1) draw_diametre_hexa(pa);	
				if (GetMenuItemChecked(w[63]) == 1) draw_coefficient_cd_hexa(pa);
				if (GetMenuItemChecked(w[64]) == 1) draw_coefficient_f_hexa(pa);
				if (GetMenuItemChecked(w[83]) == 1) draw_deplacement_hexa(pa);
				if (GetMenuItemChecked(w[58]) == 1) draw_tension_hexa(pa);
				if (GetMenuItemChecked(w[82]) == 1) draw_nrj_hexa(pa);
				if (GetMenuItemChecked(w[60]) == 1) draw_longueur_tendue_hexa(pa);
				if (GetMenuItemChecked(w[65]) == 1) draw_section_hexa(pa);
				if (GetMenuItemChecked(w[66]) == 1) draw_volume_hexa(pa);
				if (GetMenuItemChecked(w[67]) == 1) draw_masse_hexa(pa);
				if (GetMenuItemChecked(w[68]) == 1) draw_masse_lineique_hexa(pa);
				if (GetMenuItemChecked(w[69]) == 1) draw_flottabilite_hexa(pa);
				if (GetMenuItemChecked(w[28]) == 1) draw_type_noeud_hexa(pa);
				if (GetMenuItemChecked(w[33]) == 1) draw_numero_noeud_hexa(pa);
				if (GetMenuItemChecked(w[32]) == 1) draw_masse_noeud_hexa(pa);
				if (GetMenuItemChecked(w[35]) == 1) draw_longueur_noeud_hexa(pa);
				if (GetMenuItemChecked(w[38]) == 1) draw_cd_noeud_hexa(pa);
				if (GetMenuItemChecked(w[41]) == 1) draw_effort_noeud_hexa(pa);
				if (GetMenuItemChecked(w[44]) == 1) draw_limite_noeud_hexa(pa);
				if (GetMenuItemChecked(w[47]) == 1) draw_sens_limite_noeud_hexa(pa);
				if (GetMenuItemChecked(w[50]) == 1) draw_deplacement_noeud_hexa(pa);
				if (GetMenuItemChecked(w[53]) == 1) draw_symmetrie_noeud_hexa(pa);
				if (GetMenuItemChecked(w[24]) == 1) draw_profondeur_barycentre_hexa(pa,no);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS))
			{
			/*element*/
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			condition_draw_element = 0;		//not draw
			if(Element[pa].type > 0)
				{
				//the bar belongs to a cable
				if ((TypeElement[Element[pa].type].flag_dessin != 0) && (Element[pa].flag_dessin != 0))
					{	
					condition_draw_element = 1;	//draw
					}
				}
			else
				{
				//the bar belongs to a panel
				if (panneau[-Element[pa].type].flag_dessin != 0)
					{	
					condition_draw_element = 1;	//draw
					}
				}
			
			
			//printf("dessiner_ps pa %4d Element[pa].type %4d typeflag %4d flag %4d ",pa,Element[pa].type,TypeElement[Element[pa].type].flag_dessin,Element[pa].flag_dessin);
			//printf("no %4d pa %4d condition_draw_element %4d\n",no,pa,condition_draw_element);
			if (condition_draw_element == 1)
				{	
				if (GetMenuItemChecked(w[9]) == 1)  draw_contour_element3(pa);
				if (GetMenuItemChecked(w[25]) == 1) draw_numero_element_barre(pa);
				if (GetMenuItemChecked(w[27]) == 1) draw_type_element_barre(pa);
				if (GetMenuItemChecked(w[56]) == 1) draw_raideur_traction_barre(pa);
				if (GetMenuItemChecked(w[56]) == 1) draw_raideur_traction_barre(pa);
				if (GetMenuItemChecked(w[57]) == 1) draw_raideur_compression_barre(pa);
				if (GetMenuItemChecked(w[59]) == 1) draw_longueur_repos_barre(pa);
				if (GetMenuItemChecked(w[61]) == 1) draw_masse_volumique_barre(pa);
				if (GetMenuItemChecked(w[62]) == 1) draw_diametre_barre(pa);	
				if (GetMenuItemChecked(w[63]) == 1) draw_coefficient_cd_barre(pa);
				if (GetMenuItemChecked(w[64]) == 1) draw_coefficient_f_barre(pa);
				if (GetMenuItemChecked(w[83]) == 1) draw_deplacement_element(pa);
				if (GetMenuItemChecked(w[86]) == 1) draw_immersion_element(pa);
				if (GetMenuItemChecked(w[58]) == 1) draw_tension_element(pa);
				if (GetMenuItemChecked(w[82]) == 1) draw_nrj_element(pa);
				if (GetMenuItemChecked(w[60]) == 1) draw_longueur_tendue_element(pa);
				if (GetMenuItemChecked(w[65]) == 1) draw_section_element(pa);
				if (GetMenuItemChecked(w[66]) == 1) draw_volume_element(pa);
				if (GetMenuItemChecked(w[67]) == 1) draw_masse_element(pa);
				if (GetMenuItemChecked(w[68]) == 1) draw_masse_lineique_element(pa);
				if (GetMenuItemChecked(w[69]) == 1) draw_flottabilite_element(pa);
				if (GetMenuItemChecked(w[28]) == 1) draw_type_noeud_element(pa);
				if (GetMenuItemChecked(w[33]) == 1) draw_numero_noeud_element(pa);
				if (GetMenuItemChecked(w[32]) == 1) draw_masse_noeud_element(pa);
				if (GetMenuItemChecked(w[35]) == 1) draw_longueur_noeud_element(pa);
				if (GetMenuItemChecked(w[38]) == 1) draw_cd_noeud_element(pa);
				if (GetMenuItemChecked(w[41]) == 1) draw_effort_noeud_element(pa);
				if (GetMenuItemChecked(w[44]) == 1) draw_limite_noeud_element(pa);
				if (GetMenuItemChecked(w[47]) == 1) draw_sens_limite_noeud_element(pa);
				if (GetMenuItemChecked(w[50]) == 1) draw_deplacement_noeud_element(pa);
				if (GetMenuItemChecked(w[53]) == 1) draw_symmetrie_noeud_element(pa);
				if (GetMenuItemChecked(w[24]) == 1) draw_profondeur_barycentre_element(pa,no);
				if (GetMenuItemChecked(w[85]) == 1) draw_trajectoire_element(pa);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES))
			{
			/*coulisse*/
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			if (Coulisse[pa].flag_dessin != 0)
				{
				if (GetMenuItemChecked(w[70]) == 1) draw_contour_coulisse(pa);
				if (GetMenuItemChecked(w[25]) == 1) draw_numero_element_coulisse(pa);
				if (GetMenuItemChecked(w[27]) == 1) draw_type_element_coulisse(pa);
				if (GetMenuItemChecked(w[56]) == 1) draw_raideur_traction_coulisse(pa);
				if (GetMenuItemChecked(w[56]) == 1) draw_raideur_traction_coulisse(pa);
				if (GetMenuItemChecked(w[57]) == 1) draw_raideur_compression_coulisse(pa);
				if (GetMenuItemChecked(w[59]) == 1) draw_longueur_repos_coulisse(pa);
				if (GetMenuItemChecked(w[61]) == 1) draw_masse_volumique_coulisse(pa);
				if (GetMenuItemChecked(w[62]) == 1) draw_diametre_coulisse(pa);	
				if (GetMenuItemChecked(w[63]) == 1) draw_coefficient_cd_coulisse(pa);
				if (GetMenuItemChecked(w[64]) == 1) draw_coefficient_f_coulisse(pa);
				if (GetMenuItemChecked(w[83]) == 1) draw_deplacement_coulisse(pa);
				if (GetMenuItemChecked(w[58]) == 1) draw_tension_coulisse(pa);
				if (GetMenuItemChecked(w[82]) == 1) draw_nrj_coulisse(pa);
				if (GetMenuItemChecked(w[60]) == 1) draw_longueur_tendue_coulisse(pa);
				if (GetMenuItemChecked(w[65]) == 1) draw_section_coulisse(pa);
				if (GetMenuItemChecked(w[66]) == 1) draw_volume_coulisse(pa);
				if (GetMenuItemChecked(w[67]) == 1) draw_masse_coulisse(pa);
				if (GetMenuItemChecked(w[68]) == 1) draw_masse_lineique_coulisse(pa);
				if (GetMenuItemChecked(w[69]) == 1) draw_flottabilite_coulisse(pa);
				if (GetMenuItemChecked(w[28]) == 1) draw_type_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[33]) == 1) draw_numero_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[32]) == 1) draw_masse_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[35]) == 1) draw_longueur_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[38]) == 1) draw_cd_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[41]) == 1) draw_effort_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[44]) == 1) draw_limite_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[47]) == 1) draw_sens_limite_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[50]) == 1) draw_deplacement_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[53]) == 1) draw_symmetrie_noeud_coulisse(pa);
				if (GetMenuItemChecked(w[24]) == 1) draw_profondeur_barycentre_coulisse(pa,no);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS))
			{
			/*winch*/
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS - NOMBRE_COULISSES;
			if (Winch[pa].flag_dessin != 0)
				{
				if (GetMenuItemChecked(w[87]) == 1) draw_contour_winch(pa);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS + Ball.nb))
			{
			/*ball*/
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS - NOMBRE_COULISSES - NOMBRE_WINCHS;
			if (Ball.flag_dessin != 0)
				{
				if (GetMenuItemChecked(w[88]) == 1) draw_contour_ball(pa);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS + Ball.nb) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS + Ball.nb + NOMBRE_NOEUDS))
			{
			/*node*/
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS - NOMBRE_COULISSES - NOMBRE_WINCHS - Ball.nb;
			if (GetMenuItemChecked(w[90]) == 1) draw_contour_noeud(pa);
			if (GetMenuItemChecked(w[74]) == 1) draw_efforts_externes(pa);
			if (GetMenuItemChecked(w[97]) == 1) draw_eigen_values(pa);
			if (GetMenuItemChecked(w[24]) == 1) draw_profondeur_barycentre_noeud(pa,no);
			}
		}
	if (GetMenuItemChecked(w[14]) == 1) dessiner_surface_libre();
	if (GetMenuItemChecked(w[100]) == 1) dessiner_ballast_altitude();
	if (GetMenuItemChecked(w[101]) == 1) dessiner_cube_size();
	if (GetMenuItemChecked(w[15]) == 1) dessiner_surface_front();
	if (GetMenuItemChecked(w[17]) == 1) dessiner_axes();
	if (GetMenuItemChecked(w[93]) == 1) dessiner_repere();
	if (GetMenuItemChecked(w[18]) == 1) dessiner_quadrillage();
	if (GetMenuItemChecked(w[71]) == 1) dessiner_commentaire();
	}
	

void dessiner2()
	{
	int mode,mode_u,mode_v;
	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();
	
	if ((Flag_Fichier_final_charge == 1) || (Flag_Fichier_initial_charge == 1))
		{
		lecture_des(); /*lecture des ordres de dessin*/
		}

	ClearDrawArea();
	Color(WHITE);
	Move_to((float)0.0,(float)0.0);
	Line_to((float)1.0,(float)0.0);
	Line_to((float)1.0,(float)1.0);
	Line_to((float)0.0,(float)1.0);
	Line_to((float)0.0,(float)0.0);
	/*Line_to((float)0.0,(float)0.0);*/
	Surface_end();	/*faire un fond blanc */

	mode = GetMenuItemChecked(w[80]);	if (mode == 1) dessiner_nb_mailles();
	mode = GetMenuItemChecked(w[9]);	if (mode == 1) dessiner_contour_element3();
	mode = GetMenuItemChecked(w[90]);	if (mode == 1) dessiner_contour_noeud();
	mode = GetMenuItemChecked(w[70]);	if (mode == 1) dessiner_contour_coulisse();
	mode = GetMenuItemChecked(w[87]);	if (mode == 1) dessiner_contour_winch();
	mode = GetMenuItemChecked(w[16]);	if (mode == 1) dessiner_orientation_xy_element();
	
	mode_u = GetMenuItemChecked(w[11]);
	mode_v = GetMenuItemChecked(w[29]);
	if ((mode_u == 1) && (mode_v == 0) && (Flag_Fichier_final_charge   == 1)) {rotation_fils(); dessiner_fils_u();}
	if ((mode_u == 0) && (mode_v == 1) && (Flag_Fichier_final_charge   == 1)) {rotation_fils(); dessiner_fils_v();}
	if ((mode_u == 1) && (mode_v == 1) && (Flag_Fichier_final_charge   == 1)) {rotation_fils(); dessiner_fils_uv();}
	if ((mode_u == 1) && (mode_v == 0) && (Flag_Fichier_initial_charge == 1)) {rotation_fils(); dessiner_fils_u_initial();}
	if ((mode_u == 0) && (mode_v == 1) && (Flag_Fichier_initial_charge == 1)) {rotation_fils(); dessiner_fils_v_initial();}
	if ((mode_u == 1) && (mode_v == 1) && (Flag_Fichier_initial_charge == 1)) {rotation_fils(); dessiner_fils_uv_initial();}
	
	mode = GetMenuItemChecked(w[10]);	if (mode == 1) dessiner_contour_triangle_element();
	mode = GetMenuItemChecked(w[88]);	if (mode == 1) dessiner_contour_ball();			/*fait*/
	mode = GetMenuItemChecked(w[14]);	if (mode == 1) dessiner_surface_libre();		/*fait*/
	mode = GetMenuItemChecked(w[100]);	if (mode == 1) dessiner_ballast_altitude();		/*fait*/
	mode = GetMenuItemChecked(w[101]);	if (mode == 1) dessiner_cube_size();			/*fait*/
	mode = GetMenuItemChecked(w[17]);	if (mode == 1) dessiner_axes();				/*fait*/
	mode = GetMenuItemChecked(w[18]);	if (mode == 1) dessiner_quadrillage();			/*fait*/
	mode = GetMenuItemChecked(w[20]);	if (mode == 1) dessiner_angle_fils();			/*fait*/
	mode = GetMenuItemChecked(w[21]);	if (mode == 1) dessiner_orientation_volume();		/*fait*/
	mode = GetMenuItemChecked(w[22]);	if (mode == 1) dessiner_volume_elementaire();		/*fait*/
	mode = GetMenuItemChecked(w[23]);	if (mode == 1) dessiner_surface_elementaire();		/*fait*/
	mode = GetMenuItemChecked(w[84]);	if (mode == 1) dessiner_defaut_discretisation();	/*fait*/
	mode = GetMenuItemChecked(w[24]);	if (mode == 1) dessiner_profondeur_barycentre();	/*fait*/
	mode = GetMenuItemChecked(w[25]);	if (mode == 1) dessiner_numero_element();		/*fait*/
	mode = GetMenuItemChecked(w[27]);	if (mode == 1) dessiner_type_element();			/*fait*/
	mode = GetMenuItemChecked(w[71]);	if (mode == 1) dessiner_commentaire();			/*fait*/
	mode = GetMenuItemChecked(w[74]);	if (mode == 1) dessiner_efforts_externes();		/*fait*/
	mode = GetMenuItemChecked(w[97]);	if (mode == 1) dessiner_eigen_values();			/*fait*/
	mode = GetMenuItemChecked(w[83]);	if (mode == 1) dessiner_deplacement();			/*fait*/
	mode = GetMenuItemChecked(w[86]);	if (mode == 1) dessiner_immersion();			/*fait*/
	mode = GetMenuItemChecked(w[56]);	if (mode == 1) dessiner_raideur_traction();		/*fait*/
	mode = GetMenuItemChecked(w[57]);	if (mode == 1) dessiner_raideur_compression();		/*fait*/
	mode = GetMenuItemChecked(w[72]);	if (mode == 1) dessiner_raideur_ouverture();		/*fait*/
	mode = GetMenuItemChecked(w[58]);	if (mode == 1) dessiner_tension();			/*fait*/
	mode = GetMenuItemChecked(w[82]);	if (mode == 1) dessiner_nrj();				/*fait*/
	mode = GetMenuItemChecked(w[59]);	if (mode == 1) dessiner_longueur_repos();		/*fait*/
	mode = GetMenuItemChecked(w[60]);	if (mode == 1) dessiner_longueur_tendue();		/*fait*/
	mode = GetMenuItemChecked(w[61]);	if (mode == 1) dessiner_masse_volumique();		/*fait*/
	mode = GetMenuItemChecked(w[62]);	if (mode == 1) dessiner_diametre();			/*fait*/
	mode = GetMenuItemChecked(w[73]);	if (mode == 1) dessiner_largeur_noeud();		/*fait*/
	mode = GetMenuItemChecked(w[63]);	if (mode == 1) dessiner_coefficient_cd();		/*fait*/
	mode = GetMenuItemChecked(w[64]);	if (mode == 1) dessiner_coefficient_f();		/*fait*/
	mode = GetMenuItemChecked(w[65]);	if (mode == 1) dessiner_section_element();		/*fait*/
	mode = GetMenuItemChecked(w[66]);	if (mode == 1) dessiner_volume_element();		/*fait*/
	mode = GetMenuItemChecked(w[67]);	if (mode == 1) dessiner_masse_element();		/*fait*/
	mode = GetMenuItemChecked(w[68]);	if (mode == 1) dessiner_masse_lineique();		/*fait*/
	mode = GetMenuItemChecked(w[69]);	if (mode == 1) dessiner_flottabilite();			/*fait*/
	
	
	mode = GetMenuItemChecked(w[15]);	if (mode == 1) dessiner_surface_front();
	mode = GetMenuItemChecked(w[28]);	if (mode == 1) dessiner_type_noeud();			/*fait*/
	mode = GetMenuItemChecked(w[33]);	if (mode == 1) dessiner_numero_noeud();			/*fait*/
	mode = GetMenuItemChecked(w[32]);	if (mode == 1) dessiner_masse_noeud();			/*fait*/
	mode = GetMenuItemChecked(w[35]);	if (mode == 1) dessiner_longueur_noeud();		/*fait*/
	mode = GetMenuItemChecked(w[38]);	if (mode == 1) dessiner_cd_noeud();			/*fait*/
	mode = GetMenuItemChecked(w[41]);	if (mode == 1) dessiner_effort_noeud();			/*fait*/
	mode = GetMenuItemChecked(w[44]);	if (mode == 1) dessiner_limite_noeud();			/*fait*/
	mode = GetMenuItemChecked(w[47]);	if (mode == 1) dessiner_sens_limite_noeud();		/*fait*/
	mode = GetMenuItemChecked(w[50]);	if (mode == 1) dessiner_deplacement_noeud();		/*fait*/
	mode = GetMenuItemChecked(w[53]);	if (mode == 1) dessiner_symmetrie_noeud();		/*fait*/
	
	
	if (Structure.graphic == 2)
		{
 		dessiner_fils_uv();
		}
	mode = GetMenuItemChecked(w[85]);	if (mode == 1) dessiner_trajectoire();			/*fait*/
	}
	

int Clip3(float *xx1,float *yy1,float *xx2,float *yy2)
	{
	double x01,y01,x02,y02;
	
	x01 = (double) *xx1;
	y01 = (double) *yy1;
	x02 = (double) *xx2;
	y02 = (double) *yy2;
	
	if ((x01>=0.0 && x01<=1.0) && (x02>=0.0 && x02<=1.0) && (y01>=0.0 && y01<=1.0) && (y02>=0.0 && y02<=1.0))
		{
		return 2;
		}

	if ((x01<0.0 && x02<0.0) || (x01>1.0 && x02>1.0) || (y01<0.0 && y02<0.0) || (y01>1.0 && y02>1.0) ) 
		{
		return 0;
		}

	if (x01<0.0)
		{
		if ((x02-x01) !=0.0)
			{
			y01 = y02 - (x02-0.0) * (y02-y01)/(x02-x01);
			}
		else
			{
			y01 = y02;	
			}
		x01=0.0;	
		}
	if ((x01<0.0 && x02<0.0) || (x01>1.0 && x02>1.0) || (y01<0.0 && y02<0.0) || (y01>1.0 && y02>1.0) ) 
		{
		return 0;
		}
	if (x02<0.0)
		{
		if ((x02-x01) !=0.0)
			{
			y02 = y02 - (x02-0.0) * (y02-y01)/(x02-x01);
			}
		else
			{
			y02 = y02;	
			}
		x02=0.0;	
		}
	if ((x01<0.0 && x02<0.0) || (x01>1.0 && x02>1.0) || (y01<0.0 && y02<0.0) || (y01>1.0 && y02>1.0) ) 
		{
		return 0;
		}
	if (x01>1.0)
		{
		if ((x02-x01) !=0.0)
			{
			y01 = y02 - (x02-1.0) * (y02-y01)/(x02-x01);
			}
		else
			{
			y01 = y02;	
			}
		x01=1.0;	
		}
	if ((x01<0.0 && x02<0.0) || (x01>1.0 && x02>1.0) || (y01<0.0 && y02<0.0) || (y01>1.0 && y02>1.0) ) 
		{
		return 0;
		}
	if (x02>1.0)
		{
		if ((x02-x01) !=0.0)
			{
			y02 = y02 - (x02-1.0) * (y02-y01)/(x02-x01);
			}
		else
			{
			y02 = y02;	
			}
		x02=1.0;	
		}

	if ((x01<0.0 && x02<0.0) || (x01>1.0 && x02>1.0) || (y01<0.0 && y02<0.0) || (y01>1.0 && y02>1.0) ) 
		{
		return 0;
		}
	if (y01<0.0)
		{
		if ((y02-y01) !=0.0)
			{
			x01 = x02 - (y02-0.0) * (x02-x01)/(y02-y01);
			}
		else
			{
			x01 = x02;	
			}
		y01=0.0;	
		}

	if ((x01<0.0 && x02<0.0) || (x01>1.0 && x02>1.0) || (y01<0.0 && y02<0.0) || (y01>1.0 && y02>1.0) ) 
		{
		return 0;
		}
	if (y02<0.0)
		{
		if ((y02-y01) !=0.0)
			{
			x02 = x02 - (y02-0.0) * (x02-x01)/(y02-y01);
			}
		else
			{
			x02 = x02;	
			}
		y02=0.0;	
		}

	if ((x01<0.0 && x02<0.0) || (x01>1.0 && x02>1.0) || (y01<0.0 && y02<0.0) || (y01>1.0 && y02>1.0) ) 
		{
		return 0;
		}
	if (y01>1.0)
		{
		if ((y02-y01) !=0.0)
			{
			x01 = x02 - (y02-1.0) * (x02-x01)/(y02-y01);
			}
		else
			{
			x01 = x02;	
			}
		y01=1.0;	
		}

	if ((x01<0.0 && x02<0.0) || (x01>1.0 && x02>1.0) || (y01<0.0 && y02<0.0) || (y01>1.0 && y02>1.0) ) 
		{
		return 0;
		}
	if (y02>1.0)
		{
		if ((y02-y01) !=0.0)
			{
			x02 = x02 - (y02-1.0) * (x02-x01)/(y02-y01);
			}
		else
			{
			x02 = x02;	
			}
		y02=1.0;	
		}

	if ((x01<0.0 && x02<0.0) || (x01>1.0 && x02>1.0) || (y01<0.0 && y02<0.0) || (y01>1.0 && y02>1.0) ) 
		{
		return 0;
		}

	*xx1 = (float) x01;
	*yy1 = (float) y01;
	*xx2 = (float) x02;
	*yy2 = (float) y02;
	return 2;
	}

void EffaceTriangle(int icolor, double dx1, double dy1, double dx2, double dy2, double dx3, double dy3)
	{
	/*efface dans la couleur icolor la surface du triangle sur l ecran
	les coordonnees des 3 sommets sont dx1,dx2 ...*/
	float xx1,xx2,xx3,yy1,yy2,yy3;
	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();
	
	xx1 = (REEL) (dx1 - binx) / (baxx - binx);
	xx2 = (REEL) (dx2 - binx) / (baxx - binx);
	xx3 = (REEL) (dx3 - binx) / (baxx - binx);
	yy1 = (REEL) (dy1 - biny) / (baxy - biny);
	yy2 = (REEL) (dy2 - biny) / (baxy - biny);
	yy3 = (REEL) (dy3 - biny) / (baxy - biny);
	
	Color(icolor);
	Move_to((float)xx1,(float)yy1);
	Line_to((float)xx2,(float)yy2);
	Line_to((float)xx3,(float)yy3);
	Line_to((float)xx1,(float)yy1);
	Surface_end();
	}

void EffaceQuadrangle(int icolor, double dx1, double dy1, double dx2, double dy2, double dx3, double dy3, double dx4, double dy4)
	{
	/*efface dans la couleur icolor la surface du triangle sur l ecran
	les coordonnees des 3 sommets sont dx1,dx2 ...*/
	float xx1,xx2,xx3,xx4,yy1,yy2,yy3,yy4;
	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();
	
	xx1 = (REEL) (dx1 - binx) / (baxx - binx);
	xx2 = (REEL) (dx2 - binx) / (baxx - binx);
	xx3 = (REEL) (dx3 - binx) / (baxx - binx);
	xx4 = (REEL) (dx4 - binx) / (baxx - binx);
	yy1 = (REEL) (dy1 - biny) / (baxy - biny);
	yy2 = (REEL) (dy2 - biny) / (baxy - biny);
	yy3 = (REEL) (dy3 - biny) / (baxy - biny);
	yy4 = (REEL) (dy4 - biny) / (baxy - biny);
	
	Color(icolor);
	Move_to((float)xx1,(float)yy1);
	Line_to((float)xx2,(float)yy2);
	Line_to((float)xx3,(float)yy3);
	Line_to((float)xx4,(float)yy4);
	Line_to((float)xx1,(float)yy1);
	Surface_end();
	}

void TraceSegment(int icolor, double dx1, double dy1, double dx2, double dy2)
	{
	/*trace le segment dx1,dy1 a dx2 dy2 dans la couleur icolor */
	float xx1,xx2,yy1,yy2;
	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();
	
	xx1 = (REEL) (dx1 - binx) / (baxx - binx);
	xx2 = (REEL) (dx2 - binx) / (baxx - binx);
	yy1 = (REEL) (dy1 - biny) / (baxy - biny);
	yy2 = (REEL) (dy2 - biny) / (baxy - biny);
	/*
	0 : invisible
	1 : black
	2 : blue
	3 : red
	4 : green
	5 : yellow
	6 : cyan
	7 : purple
	8 : light blue
	9 : orange
	10 : light purple
	*/
	Color(icolor);
	if (icolor == 1 )	Color(BLACK);
	if (icolor == 2 )	Color(BLUE);
	if (icolor == 3 )	Color(RED);
	if (icolor == 4 )	Color(GREEN);
	if (icolor == 5 )	Color(YELLOW);
	Move_to((float)xx1,(float)yy1);
	Line_to((float)xx2,(float)yy2);
	Line_end();
	}
	
void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y)
	{
	/*ecrit le texte chaine en dx et dy, avec un decalage selon y de decalage_y
	selon la couleur icolor*/
	float xx1,yy1;
	
	xx1 = (REEL) (dx - binx) / (baxx - binx);
	yy1 = (REEL) (dy - biny) / (baxy - biny);
	Color(icolor);
    	Text(xx1,yy1+(float)decalage_y,chaine);
	}
