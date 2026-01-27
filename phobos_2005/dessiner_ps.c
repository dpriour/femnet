#define PRINCIPAL 0
#include "phobos.h"

void dessiner()
	{
	int mode;
	ClearDrawArea();
	mode = GetMenuItemChecked(w[86]);       if (mode == 1) dessiner_defaut_discretisation();
	mode = GetMenuItemChecked(w[73]);	if (mode == 1) dessiner_contour_hexa();
	mode = GetMenuItemChecked(w[6]);	if (mode == 1) dessiner_contour_panneau();
	mode = GetMenuItemChecked(w[94]);	if (mode == 1) dessiner_contour_panel_cutting();
	mode = GetMenuItemChecked(w[9]);	if (mode == 1) dessiner_contour_element();
	mode = GetMenuItemChecked(w[87]);	if (mode == 1) dessiner_contour_winch();
	mode = GetMenuItemChecked(w[69]);	if (mode == 1) dessiner_contour_coulisse();
	mode = GetMenuItemChecked(w[89]);	if (mode == 1) dessiner_contour_balls();
	mode = GetMenuItemChecked(w[10]);	if (mode == 1) dessiner_liaison();
	mode = GetMenuItemChecked(w[100]);	if (mode == 1) dessiner_angle_flexion_cable();
	mode = GetMenuItemChecked(w[15]);	if (mode == 1) dessiner_lie();
	mode = GetMenuItemChecked(w[20]);	if (mode == 1) filet_interne_dessiner();
	mode = GetMenuItemChecked(w[32]);	if (mode == 1) orientation_uv_dessiner();
	mode = GetMenuItemChecked(w[33]);	if (mode == 1) orientation_UV_dessiner();
	mode = GetMenuItemChecked(w[34]);	if (mode == 1) orientation_xy_dessiner();
	mode = GetMenuItemChecked(w[19]);	if (mode == 1) filet_contour_dessiner();
	mode = GetMenuItemChecked(w[75]);	if (mode == 1) dessiner_axes();
	mode = GetMenuItemChecked(w[29]);	if (mode == 1) fils_contour_dessiner();
	mode = GetMenuItemChecked(w[95]);	if (mode == 1) internal_bar_dessiner();
	mode = GetMenuItemChecked(w[91]);	if (mode == 1) UV_Vectors_dessiner();
	mode = GetMenuItemChecked(w[90]);	if (mode == 1) axe_T90_dessiner();
	mode = GetMenuItemChecked(w[74]);	if (mode == 1) dessiner_numero_hexa();
	mode = GetMenuItemChecked(w[11]);	if (mode == 1) dessiner_numero_panneau();
	mode = GetMenuItemChecked(w[12]);	if (mode == 1) dessiner_numero_element();
	mode = GetMenuItemChecked(w[70]);	if (mode == 1) dessiner_numero_coulisse();
	mode = GetMenuItemChecked(w[8]);	if (mode == 1) dessiner_numero_barre();
	mode = GetMenuItemChecked(w[13]);	if (mode == 1) dessiner_order_liaison();
	mode = GetMenuItemChecked(w[103]);	if (mode == 1) dessiner_numero_liaison();
	mode = GetMenuItemChecked(w[85]);	if (mode == 1) dessiner_ordre_maillage();
	mode = GetMenuItemChecked(w[14]);	if (mode == 1) dessiner_numero_total();
	mode = GetMenuItemChecked(w[23]);	if (mode == 1) dessiner_numero_global();
	mode = GetMenuItemChecked(w[17]);	if (mode == 1) dessiner_numero_local();
	mode = GetMenuItemChecked(w[21]);	if (mode == 1) dessiner_numero_interieur();
	mode = GetMenuItemChecked(w[18]);	if (mode == 1) dessiner_numero_coin();
	mode = GetMenuItemChecked(w[24]);	if (mode == 1) dessiner_numerotation_type();
	
	mode = GetMenuItemChecked(w[48]);	if (mode == 1) dessiner_valeur_masse();
	mode = GetMenuItemChecked(w[49]);	if (mode == 1) dessiner_valeur_longueur();
	mode = GetMenuItemChecked(w[50]);	if (mode == 1) dessiner_valeur_cd();
	mode = GetMenuItemChecked(w[51]);	if (mode == 1) dessiner_valeur_effort_exterieur();
	mode = GetMenuItemChecked(w[52]);	if (mode == 1) dessiner_valeur_fixation();
	mode = GetMenuItemChecked(w[53]);	if (mode == 1) dessiner_valeur_limite();
	mode = GetMenuItemChecked(w[54]);	if (mode == 1) dessiner_valeur_sens_limite();
	mode = GetMenuItemChecked(w[55]);	if (mode == 1) dessiner_valeur_symetrie();
	mode = GetMenuItemChecked(w[61]);	if (mode == 1)  dessiner_nb_mailles();
	mode = GetMenuItemChecked(w[62]);	if (mode == 1)  dessiner_nb_cotes_mailles();
	mode = GetMenuItemChecked(w[63]);	if (mode == 1)  dessiner_longueur_cotes();
	mode = GetMenuItemChecked(w[93]);	if (mode == 1)  dessiner_panel_cutting();

	mode = GetMenuItemChecked(w[28]);	if (mode == 1) dessiner_numerotation_triangle_contour();
	mode = GetMenuItemChecked(w[37]);	if (mode == 1) dessiner_numerotation_triangle_interieur();
	mode = GetMenuItemChecked(w[39]);	if (mode == 1) dessiner_raideur_traction();
	mode = GetMenuItemChecked(w[40]);	if (mode == 1) dessiner_raideur_compression();
	mode = GetMenuItemChecked(w[76]);	if (mode == 1) dessiner_raideur_ouverture();
	mode = GetMenuItemChecked(w[41]);	if (mode == 1) dessiner_longueur_repos();
	mode = GetMenuItemChecked(w[96]);	if (mode == 1) dessiner_bar_length();
	mode = GetMenuItemChecked(w[42]);	if (mode == 1) dessiner_masse_volumique();
	mode = GetMenuItemChecked(w[43]);	if (mode == 1) dessiner_diametre();
	mode = GetMenuItemChecked(w[77]);	if (mode == 1) dessiner_largeur_noeud();
	mode = GetMenuItemChecked(w[44]);	if (mode == 1) dessiner_coefficient_cd();
	mode = GetMenuItemChecked(w[45]);	if (mode == 1) dessiner_coefficient_f();
	mode = GetMenuItemChecked(w[92]);	if (mode == 1) dessiner_panel_drag();
	mode = GetMenuItemChecked(w[46]);	if (mode == 1) dessiner_longueur_maillage();
	mode = GetMenuItemChecked(w[26]);	if (mode == 1) dessiner_type_maillage();
	mode = GetMenuItemChecked(w[64]);	if (mode == 1) dessiner_section_element();
	mode = GetMenuItemChecked(w[65]);	if (mode == 1) dessiner_volume_element();
	mode = GetMenuItemChecked(w[66]);	if (mode == 1) dessiner_masse_element();
	mode = GetMenuItemChecked(w[67]);	if (mode == 1) dessiner_masse_lineique();
	mode = GetMenuItemChecked(w[68]);	if (mode == 1) dessiner_flottabilite();
	mode = GetMenuItemChecked(w[99]);	if (mode == 1) dessiner_EI_flexion_cable();
	
	mode = GetMenuItemChecked(w[56]);	if (mode == 1) dessiner_courant();
	mode = GetMenuItemChecked(w[57]);	if (mode == 1) dessiner_Prise_volume();
	mode = GetMenuItemChecked(w[58]);	if (mode == 1) dessiner_frottement_fond();
	mode = GetMenuItemChecked(w[60]);	if (mode == 1) dessiner_surface_fils();
        mode = GetMenuItemChecked(w[81]);	if (mode == 1) dessiner_longueur_tendue();
        mode = GetMenuItemChecked(w[82]);       if (mode == 1) dessiner_tension();
	mode = GetMenuItemChecked(w[83]);       if (mode == 1) dessiner_numerotation_globale();
	mode = GetMenuItemChecked(w[84]);       if (mode == 1) dessiner_nrj();
	}

void dessiner_contour_hexa()
	{
	int pa,no,deb,fin;
	float x1,x2,y1,y2;
	
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	lecture_des();
	Color(RED);

	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{
		if (pan_hexa[pa].flag_dessin != 0)
			{
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			if (no != pan_hexa[pa].nb_noeud_contour) fin = pan_hexa[pa].noeud_contour[no+1];
			if (no == pan_hexa[pa].nb_noeud_contour) fin = pan_hexa[pa].noeud_contour[   1];
			x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
			x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
			y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);
			}
			}
		}
	}

void dessiner_contour_panneau()
	{
	int pa,no,li,deb,fin,n1,n2,direction,tri;
	float xm,ym,xn,yn,x1,x2,x3,y1,y2,y3,limit,position,height,width,nbU,nbV,um,vm,u1,u2,u3,v1,v2,v3,ratio,space_height;
	char str[80],str_l[80],str_m[80],str_n[80],strU[80],strV[80],strt[80],strb[80],strn[80];
	double alpha,beta;
	
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	lecture_des();
	Color(BLUE);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		/*if (panneau[pa].flag_dessin != 0)*/
		if ((panneau[pa].flag_dessin != 0) && (plan.do_it != 1))
			{
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{ 
				deb = panneau[pa].noeud_contour[no];
				if (no != panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[no+1];
				if (no == panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[   1];
				/*x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
				y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
				x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
				y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
				Line(x1,y1,x2,y2);*/
				draw_segment_color(panneau[pa].flag_dessin, noeud[deb].x, noeud[deb].y, noeud[fin].x, noeud[fin].y);
				}
			}
		}
	if (plan.do_it == 1)
		{
		for (pa=1;pa<=Structure.NbTypesurf;pa++)
			{ 
			if (panneau[pa].flag_dessin != 0)
				{
				for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
					{ 
					deb = panneau[pa].noeud_contour[no];
					if (no != panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[no+1];
					if (no == panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[   1];
					if ((plan.direction == 3) && (Structure.orientation == 2))
						{
						/*
						printf("panneau %d coin %d      ",pa,no);
						printf("type de %d = %d et de %d = %d      ",deb,noeud[deb].type,fin,noeud[fin].type);
						printf("type de %d = %d et de %d = %d \n",deb,TypeNoeud[noeud[deb].type].symy,fin,TypeNoeud[noeud[fin].type].symy);
						*/
						
						if ((TypeNoeud[noeud[deb].type].symy  != 1) || (TypeNoeud[noeud[fin].type].symy  != 1))
							{
							draw_segment_color(panneau[pa].flag_dessin, noeud[deb].x, noeud[deb].y, noeud[fin].x, noeud[fin].y);
							}
						}
					}
				for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
					{ 
					deb = panneau[pa].noeud_contour[no];
					if (no != panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[no+1];
					if (no == panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[   1];
					if ((plan.direction == 3) && (Structure.orientation == 2))
						{
						if ((TypeNoeud[noeud[deb].type].symy  != 1) || (TypeNoeud[noeud[fin].type].symy  != 1))
							{
							draw_segment_color(panneau[pa].flag_dessin, 2.0*panneau[pa].symmetry_plan-noeud[deb].x, noeud[deb].y, 2.0*panneau[pa].symmetry_plan-noeud[fin].x, noeud[fin].y);
							}
						}
					}
				}
			}
		for (li=1;li<=plan.nb_line;li++)
			{ 
			pa = plan.panel[li];
			no = plan.corner[li];
			limit = plan.limit[li];
			deb = panneau[pa].noeud_contour[no];
			if ((plan.direction == 3) && (Structure.orientation == 2))		
			draw_segment_color(4, 2.0*panneau[pa].symmetry_plan-noeud[deb].x, noeud[deb].y, limit, noeud[deb].y);
			}
		for (li=1;li<=plan.nb_height;li++)
			{ 
			space_height = (float) (plan.maxx - plan.minx) / 20.0;
			//printf("space_height %lf\n",space_height);
			pa = plan.panelh[li];
			n1 = plan.corner1[li];
			n2 = plan.corner2[li];
			direction = plan.directionh[li];
			position = plan.position[li];
			deb = panneau[pa].noeud_contour[n1];
			fin = panneau[pa].noeud_contour[n2];

			if (direction == 1) height = fabs(noeud[deb].U - noeud[fin].U);
			if (direction == 2) height = fabs(noeud[deb].V - noeud[fin].V);

			if ((plan.direction == 3) && (Structure.orientation == 2))
				{
				if (floorf(height) == height) 	sprintf(str,"%5.0f",height);
				else 				sprintf(str,"%5.1f",height);
				x1  = (float) (position     - binx) / (baxx - binx);
				y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
				x1 += (float) (position     - binx) / (baxx - binx);
				y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
				x1 = (float) (x1 / 2.0);
				y1 = (float) (y1 / 2.0);
				Color(RED);
				Text(x1,y1,str);
				sprintf(str,"%5.0fmm",panneau[pa].longueur_repos*1000);
				x1  = (float) (position-2.0*space_height     - binx) / (baxx - binx);
				y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
				x1 += (float) (position-2.0*space_height     - binx) / (baxx - binx);
				y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
				x1 = (float) (x1 / 2.0);
				y1 = (float) (y1 / 2.0);
				Color(BLUE);
				Text(x1,y1,str);
				
				sprintf(str,"%3.0fmm",panneau[pa].diam_hydro*1000);
				x1  = (float) (position-3.0*space_height     - binx) / (baxx - binx);
				y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
				x1 += (float) (position-3.0*space_height     - binx) / (baxx - binx);
				y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
				x1 = (float) (x1 / 2.0);
				y1 = (float) (y1 / 2.0);
				Color(GREEN);
				Text(x1,y1,str);
				}
			}
		for (li=1;li<=plan.nb_width;li++)
			{ 
			Color(RED);
			pa = plan.panelw[li];
			n1 = plan.corner3[li];
			n2 = plan.corner4[li];
			direction = plan.directionw[li];
			deb = panneau[pa].noeud_contour[n1];
			fin = panneau[pa].noeud_contour[n2];

			if (direction == 1) width = fabs(noeud[deb].U - noeud[fin].U);
			if (direction == 2) width = fabs(noeud[deb].V - noeud[fin].V);

			if ((plan.direction == 3) && (Structure.orientation == 2))
				{
				if (floorf(width) == width) 	sprintf(str,"%-5.0f",width);
				else 				sprintf(str,"%-5.1f",width);
				x1  = (float) (noeud[deb].x 			- binx) / (baxx - binx);
				y1  = (float) (noeud[deb].y+plan.positionw[li] 	- biny) / (baxy - biny);
				x1 += (float) (noeud[fin].x 			- binx) / (baxx - binx);
				y1 += (float) (noeud[fin].y+plan.positionw[li] 	- biny) / (baxy - biny);
				x1 = (float) (x1 / 2.0);
				y1 = (float) (y1 / 2.0);
				/*printf("deb %d fin %d\n",deb,fin);
				printf("x %lf %lf\n",noeud[deb].x,noeud[fin].x);
				printf("y %lf %lf\n",noeud[deb].y,noeud[fin].y);
				printf("z %lf %lf\n",noeud[deb].z,noeud[fin].z);*/
				Text(x1,y1,str);
				}
			}
		for (li=1;li<=plan.nb_widths;li++)
			{ 
			//in case of symmetry
			Color(RED);
			pa = plan.panelws[li];
			n1 = plan.corner3s[li];
			n2 = plan.corner4s[li];
			direction = plan.directionws[li];
			deb = panneau[pa].noeud_contour[n1];
			fin = panneau[pa].noeud_contour[n2];

			if (direction == 1) width = fabs(noeud[deb].U - noeud[fin].U);
			if (direction == 2) width = fabs(noeud[deb].V - noeud[fin].V);

			if ((plan.direction == 3) && (Structure.orientation == 2))
				{
				if (floorf(width) == width) 	sprintf(str,"%5.0f",2.0*width);
				else 				sprintf(str,"%5.1f",2.0*width);
				x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1  = (float) (noeud[deb].y+plan.positionws[li] - biny) / (baxy - biny);
				x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 += (float) (noeud[fin].y+plan.positionws[li] - biny) / (baxy - biny);
				x1 = (float) (x1 / 2.0);
				y1 = (float) (y1 / 2.0);
				printf("deb %d fin %d\n",deb,fin);
				printf("x %lf %lf\n",noeud[deb].x,noeud[fin].x);
				printf("y %lf %lf\n",noeud[deb].y,noeud[fin].y);
				printf("z %lf %lf\n",noeud[deb].z,noeud[fin].z);/**/
				Text(x1,y1,str);
				}
			}
		for (li=1;li<=plan.nb_cut;li++)
			{ 
			Color(BLUE);
			pa = plan.panelc[li];
			no = plan.corner5[li];

			deb = panneau[pa].noeud_contour[no];
			if (no != panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[no+1];
			if (no == panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[1];
			nbU = fabs(noeud[deb].U - noeud[fin].U);
			nbV = fabs(noeud[deb].V - noeud[fin].V);
			ratio = fabs((noeud[deb].U - noeud[fin].U)/(noeud[deb].V - noeud[fin].V));

			sprintf(str,"%4.2f",ratio);
			x1 = (float) (0.5 * (noeud[deb].x + noeud[fin].x) - binx) / (baxx - binx);
			y1 = (float) (0.5 * (noeud[deb].y + noeud[fin].y) - biny) / (baxy - biny);
			
			Text(x1,y1,str);
			}
		if (plan.nb_cable >  0)
			{
			x1 = 	0.8;
			y1 =	1.0 - (float) (3/60.0);	
			sprintf(str,"cables");				
			Text(x1,y1,str);
			}
		for (li=1;li<=plan.nb_cable;li++)
			{ 
			Color(BLACK);
			pa = plan.cable[li];
			deb = element[pa].extremite[1];
			fin = element[pa].extremite[2];
			draw_segment_color(1, noeud[deb].x, noeud[deb].y, noeud[fin].x, noeud[fin].y);
			x1 = (float) (0.5 * (noeud[deb].x + noeud[fin].x) - binx) / (baxx - binx);
			y1 = (float) (0.5 * (noeud[deb].y + noeud[fin].y) - biny) / (baxy - biny);
			
			sprintf(str,"%d",li);				
			Text(x1,y1,str);
			
			x1 = 	0.8;
			y1 =	1.0 - (float) ((li+3)/60.0);	
			sprintf(str,"%d : %5.2f m %3.0f mm",li,element[pa].lgrepos,element[pa].diametrehydro*1000);				
			Text(x1,y1,str);
			printf("nb_cable %d %f %f\n",pa,element[pa].lgrepos,element[pa].diametrehydro);				

			}
		for (li=1;li<=plan.nb_cable_diameter;li++)
			{ 
			Color(BLACK);
			pa = plan.cabled[li];
			deb = element[pa].extremite[1];
			fin = element[pa].extremite[2];
			draw_segment_color(1, noeud[deb].x, noeud[deb].y, noeud[fin].x, noeud[fin].y);
			x1 = (float) (0.5 * (noeud[deb].x + noeud[fin].x) - binx) / (baxx - binx);
			y1 = (float) (0.5 * (noeud[deb].y + noeud[fin].y) - biny) / (baxy - biny);
			
			sprintf(str,"%d",li+plan.nb_cable);				
			Text(x1,y1,str);
			
			x1 = 	0.8;
			y1 =	1.0 - (float) ((li+plan.nb_cable+3)/60.0);	
			sprintf(str,"%d : %5.2f m %3.0f mm",li+plan.nb_cable,element[pa].lgrepos,plan.cable_diameter[li]*1000);				
			Text(x1,y1,str);
			printf("nb_cable_diameter %d %f %f\n",pa,element[pa].lgrepos,element[pa].diametrehydro);				

			}
		for (li=1;li<=plan.nb_cable_length;li++)
			{ 
			Color(BLACK);
			pa = plan.cablel[li];
			deb = element[pa].extremite[1];
			fin = element[pa].extremite[2];
			draw_segment_color(1, noeud[deb].x, noeud[deb].y, noeud[fin].x, noeud[fin].y);
			x1 = (float) (0.5 * (noeud[deb].x + noeud[fin].x) - binx) / (baxx - binx);
			y1 = (float) (0.5 * (noeud[deb].y + noeud[fin].y) - biny) / (baxy - biny);
			
			sprintf(str,"%d",li+plan.nb_cable+plan.nb_cable_diameter);				
			Text(x1,y1,str);
			
			x1 = 	0.8;
			y1 =	1.0 - (float) ((li+plan.nb_cable+plan.nb_cable_diameter+3)/60.0);	
			sprintf(str,"%d : %5.2f m %3.0f mm",li+plan.nb_cable+plan.nb_cable_diameter,plan.cable_length[li],element[pa].diametrehydro*1000);				
			Text(x1,y1,str);
			printf("nb_cable_length %d %f %f\n",pa,element[pa].lgrepos,element[pa].diametrehydro);				

			}
		for (li=1;li<=plan.nb_trait_UV;li++)
			{ 
			if ((GetMenuItemChecked(w[5])) == 0) filet_contour();
			Color(BLACK);
			pa = plan.panelt[li];
			um = plan.U1[li];	vm = plan.V1[li];
			tri = appartient_triangle_contour((double) um,(double) vm,pa);
			printf("pa %d UV %f %f tri %d\n",pa,um,vm,tri);
			
	    		u1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].U;	
	    		v1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].V;
	    		u2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].U;	
	    		v2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].V;
	    		u3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].U;	
	    		v3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].V;
			position_interieur_triangle((double) um,(double) vm,(double) u1,(double) v1,(double) u2,(double) v2,(double) u3,(double) v3, &alpha,&beta);
	    		x1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].x;	
	    		y1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].y;
	    		x2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].x;	
	    		y2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].y;
	    		x3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].x;	
	    		y3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].y;
			xm = x1 + alpha * (x2-x1) + beta * (x3-x1);
			ym = y1 + alpha * (y2-y1) + beta * (y3-y1);
			
			um = plan.U2[li];	vm = plan.V2[li];
			tri = appartient_triangle_contour((double) um,(double) vm,pa);
			printf("pa %d UV %f %f tri %d\n",pa,um,vm,tri);
			
	    		u1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].U;	
	    		v1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].V;
	    		u2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].U;	
	    		v2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].V;
	    		u3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].U;	
	    		v3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].V;
			position_interieur_triangle((double) um,(double) vm,(double) u1,(double) v1,(double) u2,(double) v2,(double) u3,(double) v3, &alpha,&beta);
	    		x1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].x;	
	    		y1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].y;
	    		x2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].x;	
	    		y2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].y;
	    		x3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].x;	
	    		y3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].y;
			xn = x1 + alpha * (x2-x1) + beta * (x3-x1);
			yn = y1 + alpha * (y2-y1) + beta * (y3-y1);
			draw_segment_color(1, xn, yn, xm, ym);
			}
		for (li=1;li<=plan.nb_trait_UV_symmetry;li++)
			{ 
			if ((GetMenuItemChecked(w[5])) == 0) filet_contour();
			Color(BLACK);
			pa = plan.panels[li];
			um = plan.R1[li];	vm = plan.S1[li];
			tri = appartient_triangle_contour((double) um,(double) vm,pa);
			printf("pa %d RS %f %f tri %d\n",pa,um,vm,tri);
			
	    		u1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].U;	
	    		v1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].V;
	    		u2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].U;	
	    		v2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].V;
	    		u3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].U;	
	    		v3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].V;
			position_interieur_triangle((double) um,(double) vm,(double) u1,(double) v1,(double) u2,(double) v2,(double) u3,(double) v3, &alpha,&beta);
	    		x1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].x;	
	    		y1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].y;
	    		x2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].x;	
	    		y2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].y;
	    		x3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].x;	
	    		y3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].y;
			xm = x1 + alpha * (x2-x1) + beta * (x3-x1);
			ym = y1 + alpha * (y2-y1) + beta * (y3-y1);
			
			um = plan.R2[li];	vm = plan.S2[li];
			tri = appartient_triangle_contour((double) um,(double) vm,pa);
			printf("pa %d UV %f %f tri %d\n",pa,um,vm,tri);
			
	    		u1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].U;	
	    		v1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].V;
	    		u2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].U;	
	    		v2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].V;
	    		u3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].U;	
	    		v3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].V;
			position_interieur_triangle((double) um,(double) vm,(double) u1,(double) v1,(double) u2,(double) v2,(double) u3,(double) v3, &alpha,&beta);
	    		x1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].x;	
	    		y1 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]]].y;
	    		x2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].x;	
	    		y2 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]]].y;
	    		x3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].x;	
	    		y3 = noeud[panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]]].y;
			xn = x1 + alpha * (x2-x1) + beta * (x3-x1);
			yn = y1 + alpha * (y2-y1) + beta * (y3-y1);
			draw_segment_color(1, xn, yn, xm, ym);
			draw_segment_color(1, 2.0*panneau[pa].symmetry_plan-xn, yn, 2.0*panneau[pa].symmetry_plan-xm, ym);
			}
		for (li=1;li<=plan.nb_indication;li++)
			{ 
			Color(RED);
			x1 = (float) (plan.X1[li] - binx) / (baxx - binx);
			y1 = (float) (plan.Y1[li] - biny) / (baxy - biny);
			
			sprintf(str,"%4.1f",plan.indication[li]);				
			Text(x1,y1,str);
			printf("xy1 %f %f indication %4.1f\n",x1,y1,plan.indication[li]);
			}
		}
	}

void dessiner_contour_panel_cutting()
	{
	int pa,no,deb,fin;
	float x1,x2,y1,y2;
	
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	lecture_des();
	Color(RED);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{ 
				deb = panneau[pa].noeud_contour[no];
				if (no != panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[no+1];
				if (no == panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[   1];
				x1 = ((REEL) noeud_seam[deb].x - binx) / (baxx - binx);
				y1 = ((REEL) noeud_seam[deb].y - biny) / (baxy - biny);
				x2 = ((REEL) noeud_seam[fin].x - binx) / (baxx - binx);
				y2 = ((REEL) noeud_seam[fin].y - biny) / (baxy - biny);
				Line(x1,y1,x2,y2);
				}
			}
		}
	}

void dessiner_contour_element()
	{
	int pa,deb,fin,elem,nb,zi,zj;
	float x1,x2,y1,y2,diam,x3,y3,pas_x,pas_y,x4,y4,x5,y5;
	
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	lecture_des();
	Color(RED);

	for (pa=1;pa<=Structure.nb_barre;pa++)
		{ 
		Color(GREEN);
		deb = barre[pa].noeud[1];
		fin = barre[pa].noeud[2];
		draw_segment_color(1, noeud[deb].x, noeud[deb].y, noeud[fin].x, noeud[fin].y);
		}
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		if (element[pa].flag_dessin != 0)
			{
			deb = element[pa].extremite[1];
			fin = element[pa].extremite[2];
			/*x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
			x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
			y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);*/
			draw_segment_color(element[pa].flag_dessin, noeud[deb].x, noeud[deb].y, noeud[fin].x, noeud[fin].y);
			}
		}
	for (pa=1;pa<=Structure.nb_sphere_element;pa++)
		{ 
		elem = Sphere_element.element[pa];
		if (element[elem].flag_dessin != 0)
			{
			nb = Sphere_element.nb[pa];
			diam = Sphere_element.diameter[pa];
			deb = element[elem].extremite[1];
			fin = element[elem].extremite[2];
			x1 = (REEL) noeud[deb].x;
			y1 = (REEL) noeud[deb].y;
			x2 = (REEL) noeud[fin].x;
			y2 = (REEL) noeud[fin].y;
			pas_x = (x2-x1) / 2 / nb;
			pas_y = (y2-y1) / 2 / nb;
			for (zi=1;zi<=nb;zi++)
				{
				x3 = x1 + pas_x + pas_x * (zi-1) * 2.0;
				y3 = y1 + pas_y + pas_y * (zi-1) * 2.0;
				for (zj=1;zj<=20;zj++)
					{
					x4 = x3 + diam / 2 * cos((zj -1)*2*PI/20);
					y4 = y3 + diam / 2 * sin((zj -1)*2*PI/20);
					x5 = x3 + diam / 2 * cos((zj -0)*2*PI/20);
					y5 = y3 + diam / 2 * sin((zj -0)*2*PI/20);
					draw_segment_color(element[pa].flag_dessin, x4,y4,x5,y5);
					}
				}
			}
		}
	}

void dessiner_contour_winch()
	{
	int pa,deb,fin;
	float x1,x2,y1,y2;
	
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	lecture_des();
	Color(GREEN);
	
	for (pa=1;pa<=Structure.nb_winch;pa++)
		{ 
		deb = winch[pa].extremite[1];
		fin = winch[pa].extremite[2];
		x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
		y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
		x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
		y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
		Line(x1,y1,x2,y2);
		}
	}

void dessiner_contour_coulisse()
	{
	int pa,deb,fin,zi,el;
	float x1,x2,y1,y2;
	
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	lecture_des();
	Color(BLACK);

	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		deb = coulisse[pa].extremite[1];
		fin = coulisse[pa].extremite[2];
		x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
		y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
		x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
		y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
		//printf("x1 ... y2 %f  %f  %f  %f\n", x1,y1,x2,y2);
		Line(x1,y1,x2,y2);
		}
	for (pa=1;pa<=Structure.nb_slider;pa++)
		{ 
		printf("pa %d\n", pa);
		for (zi=1;zi<=Slider[pa].nb_bar;zi++)
			{
			el = Slider[pa].barre[zi];
			printf("  zi %d ", zi);
			printf("  el %d  ", el);
			//exit(0);
			//element[el].slider = pa;	//this element is part of a slider
			//element[el].flag_dessin = 0;
			deb = element[el].extremite[1];
			fin = element[el].extremite[2];
			x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
			x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
			y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
			printf("x1 ... y2 %f  %f  %f  %f\n", x1,y1,x2,y2);
			Line(x1,y1,x2,y2);
			}
		}
	}

void dessiner_contour_balls()
	{
	int pa,no,deb,fin,nb_angle;
	float x1,x2,y1,y2,angle_ball_1,angle_ball_2;
	
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a dessiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	lecture_des();
	Color(RED);
	nb_angle = 10;	/*nb of segment in the contour of balls*/
	
	for (pa=1;pa<=Ball.nb;pa++)
		{ 
		deb = Ball.noeud[pa];
 		/*printf("pa %d deb %d\n",pa,deb);*/		
		for (no=1;no<=nb_angle;no++)
			{ 
			angle_ball_1 = (no-1) * (2.0 * PI / nb_angle);
			angle_ball_2 = (no+0) * (2.0 * PI / nb_angle);
			x1 = ((REEL) noeud[deb].x + Ball.radius[pa]*sin(angle_ball_1) - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y + Ball.radius[pa]*cos(angle_ball_1) - biny) / (baxy - biny);
			x2 = ((REEL) noeud[deb].x + Ball.radius[pa]*sin(angle_ball_2) - binx) / (baxx - binx);
			y2 = ((REEL) noeud[deb].y + Ball.radius[pa]*cos(angle_ball_2) - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);
			}
		}
	}

void dessiner_liaison()
	{
	int pa,deb,fin,co;
	float x1,x2,y1,y2,ox,oy,teta;
	//printf("Structure.link_distance %lf\n",Structure.link_distance);
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a dessiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	lecture_des();
	Color(RED);
	if (Structure.link_distance>=0.0)
		{
		ox = binx+(baxx-binx)*0.5;
		oy = biny+(baxy-biny)*0.5;
		//printf("ox %f oy %f\n",ox,oy);
		//printf("binx %f baxx %f biny %f baxy %f\n",binx,baxx,biny,baxy);
		for (pa=1;pa<=20;pa++)
			{ 
			teta = (REEL)PI/10*(pa-1);
			x1 = (REEL) (ox+Structure.link_distance/2.0*cos(teta));
			y1 = (REEL) (oy+Structure.link_distance/2.0*sin(teta));
			x1 = ((REEL) ox+Structure.link_distance/2.0*cos(teta) - binx) / (baxx - binx);
			y1 = ((REEL) oy+Structure.link_distance/2.0*sin(teta) - biny) / (baxy - biny);
			teta = (REEL)PI/10*(pa-0);
			x2 = (REEL) (ox+Structure.link_distance/2.0*cos(teta));
			y2 = (REEL) (oy+Structure.link_distance/2.0*sin(teta));
			x2 = ((REEL) ox+Structure.link_distance/2.0*cos(teta) - binx) / (baxx - binx);
			y2 = ((REEL) oy+Structure.link_distance/2.0*sin(teta) - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);
			//printf("teta %f x1 %f y1 %f x2 %f y2 %f\n",teta,x1,y1,x2,y2);
			}
		}
	Color(BLUE);
	

	for (pa=1;pa<=Structure.nb_liaison;pa++)
		{ 
		for (co=1;co<=Lien[pa].nb_liaison - 1;co++)
			{
			deb = Lien[pa].noeud[co];
			if (co != Lien[pa].nb_liaison) fin = Lien[pa].noeud[co+1];
			if (co == Lien[pa].nb_liaison) fin = Lien[pa].noeud[   1];
			x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
			x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
			y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);
			}
		}
	}

void dessiner_angle_flexion_cable()
	{
	int pa,deb,fin,co;
	float x1,x2,y1,y2;
	char str[80];
	
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"Angle between cable (except 0)");

	lecture_des();
	Color(BLUE);

	for (pa=1;pa<=Structure.nb_lien;pa++)
		{
		if (Lien[pa].angle_link_flexion2 > 0.0)
			{
			sprintf(str,"%3.0lf",Lien[pa].angle_link_flexion2);
			for (co=1;co<=Lien[pa].nb_liaison;co++)
				{
				deb = Lien[pa].noeud[co];
				x1 = 0.0;
				y1 = 0.0;
				x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				}
			}
		}
	}

void dessiner_lie()
	{
	int pa,deb,fin,co;
	float x1,x2,y1,y2;
	
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	lecture_des();
	Color(YELLOW);

	for (pa=Structure.nb_liaison+1;pa<=Structure.nb_lien;pa++)
		{ 
		for (co=1;co<=Lien[pa].nb_liaison - 1;co++)
			{
			deb = Lien[pa].noeud[co];
			if (co != Lien[pa].nb_liaison) fin = Lien[pa].noeud[co+1];
			if (co == Lien[pa].nb_liaison) fin = Lien[pa].noeud[   1];
			x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
			x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
			y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);
			}
		}
	}

void dessiner_numero_hexa()
	{
	int pa,no,deb,col;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_hexa\n");
	SetColor(col);*/
	
	lecture_des();
	Color(RED);

	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		if (pan_hexa[pa].flag_dessin != 0)
			{
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%d",pa);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
			}
		}
	}

void dessiner_numero_panneau()
	{
	int pa,no,deb,col;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColorr(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	lecture_des();
	Color(RED);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%d",pa);
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{ 
				deb = panneau[pa].noeud_contour[no];
				x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
			y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
			Text(x1,y1,str);
			}
		}
	}

void dessiner_numero_element()
	{
	int pa,deb,fin,col;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(0,255,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_element\n");
	SetColor(col);*/
	
	lecture_des();
	Color(RED);

	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		if (element[pa].flag_dessin != 0)
			{
			sprintf(str,"%d",pa);
			deb = element[pa].extremite[1];
			fin = element[pa].extremite[2];
			x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
			x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
			y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
			x1 = (float) (x1 / 2.0);
			y1 = (float) (y1 / 2.0);
			Text(x1,y1,str);
			}
		}
	}

void dessiner_numero_coulisse()
	{
	int pa,col,deb,fin,zi,el;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(0,255,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_coulisse\n");
	SetColor(col);*/
	
	lecture_des();
	Color(RED);

	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		sprintf(str,"%d",pa);
		deb = coulisse[pa].extremite[1];
		fin = coulisse[pa].extremite[2];
		x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
		x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
		y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
		x1 = (float) (x1 / 2.0);
		y1 = (float) (y1 / 2.0);
		Text(x1,y1,str);
		}

	for (pa=1;pa<=Structure.nb_slider;pa++)
		{ 
		sprintf(str,"%d",pa);
		for (zi=1;zi<=Slider[pa].nb_bar;zi++)
			{
			el = Slider[pa].barre[zi];
			//element[el].slider = pa;	//this element is part of a slider
			//element[el].flag_dessin = 0;
			deb = element[el].extremite[1];
			fin = element[el].extremite[2];
			x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
			x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
			y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
			x1 = (float) (x1 / 2.0);
			y1 = (float) (y1 / 2.0);
			Text(x1,y1,str);
			}
		}
	}

void dessiner_numero_barre()
	{
	int pa,col,deb,fin;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(0,255,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_barre\n");
	SetColor(col);*/
	
	lecture_des();
	Color(RED);
	//printf("Structure.nb_barre %d\n", Structure.nb_barre);

	for (pa=1;pa<=Structure.nb_barre;pa++)
		{ 
		//printf("pa %d\n", pa);

		sprintf(str,"%d",pa);
		deb = barre[pa].noeud[1];
		fin = barre[pa].noeud[2];
		x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
		x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
		y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
		x1 = (float) (x1 / 2.0);
		y1 = (float) (y1 / 2.0);
		Text(x1,y1,str);
		}
	}

void dessiner_ordre_liaison()
	{
	int pa,col,deb,fin,co;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(0,0,255);
	if (col==-1) printf("Erreur de couleur dessiner_ordre_liaison\n");
	SetColor(col);*/
	/* printf(" nb_liaison  : %8d \n",Structure.nb_liaison); */
	
	lecture_des();
	Color(BLUE);

	for (pa=1;pa<=Structure.nb_lien;pa++)
		{
		sprintf(str,"%d",pa);
		for (co=1;co<=Lien[pa].nb_liaison;co++)
			{
			deb = Lien[pa].noeud[co];
			x1 = 0.0;
			y1 = 0.0;
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			}
		}
	}


void dessiner_numero_liaison()
	{
	int pa,col,deb,fin,co;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(0,0,255);
	if (col==-1) printf("Erreur de couleur dessiner_numero_liaison\n");
	SetColor(col);*/
	//printf(" nb_liaison  : %8d \n",Structure.nb_liaison); /**/
	
	lecture_des();
	Color(BLUE);

	for (pa=1;pa<=Structure.nb_lien;pa++)
		{
		//printf("pa %d nb_liaison  %8d \n",pa,Lien[pa].nb_liaison);
		sprintf(str,"%d",Lien[pa].nb_liaison);
		//sprintf(str,"%d",pa);
		for (co=1;co<=Lien[pa].nb_liaison;co++)
			{
			deb = Lien[pa].noeud[co];
			x1 = 0.0;
			y1 = 0.0;
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			}
		}
	}

void dessiner_order_liaison()
	{
	int pa,col,deb,fin,co;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(0,0,255);
	if (col==-1) printf("Erreur de couleur dessiner_order_liaison\n");
	SetColor(col);*/
	/* printf(" nb_liaison  : %8d \n",Structure.nb_liaison); */
	
	lecture_des();
	Color(BLUE);

	for (pa=1;pa<=Structure.nb_lien;pa++)
		{
		sprintf(str,"%d",pa);
		for (co=1;co<=Lien[pa].nb_liaison;co++)
			{
			deb = Lien[pa].noeud[co];
			x1 = 0.0;
			y1 = 0.0;
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			}
		}
	}


void dessiner_ordre_maillage()
	{
	int pa,col,deb,fin,co,ty,no;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,255);
	if (col==-1) printf("Erreur de couleur dessiner_numero_liaison\n");
	SetColor(col);*/
	/* printf(" nb_liaison  : %8d \n",Structure.nb_liaison); */
	

	for (ty=1;ty<=Structure.nb_ordre_objet;ty++)
		{ 
		sprintf(str,"%d",ty);
 	        if (ordre.type[ty] == 'e') 
 	        	{
			Color(RED);
			deb = element[ordre.indice[ty]].extremite[1];
			fin = element[ordre.indice[ty]].extremite[2];
			x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
			x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
			y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
			x1 = (float) (x1 / 2.0);
			y1 = (float) (y1 / 2.0);
			Text(x1,y1,str);
 	        	}
	        if (ordre.type[ty] == 'p') 
 	        	{
			Color(GREEN);
			x1 = 0.0;
			y1 = 0.0;
			for (no=1;no<=panneau[ordre.indice[ty]].nb_noeud_contour;no++)
				{ 
				deb = panneau[ordre.indice[ty]].noeud_contour[no];
				x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / panneau[ordre.indice[ty]].nb_noeud_contour);
			y1 = (float) (y1 / panneau[ordre.indice[ty]].nb_noeud_contour);
			Text(x1,y1,str);
 	        	}
 	        if (ordre.type[ty] == 'h') 
 	        	{
			Color(BLACK);
			x1 = 0.0;
			y1 = 0.0;
			for (no=1;no<=pan_hexa[ordre.indice[ty]].nb_noeud_contour;no++)
				{ 
				deb = pan_hexa[ordre.indice[ty]].noeud_contour[no];
				x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / pan_hexa[ordre.indice[ty]].nb_noeud_contour);
			y1 = (float) (y1 / pan_hexa[ordre.indice[ty]].nb_noeud_contour);
			Text(x1,y1,str);
 	        	}
		if (ordre.type[ty] == 'c') 
			{
			Color(BLACK);
			deb = coulisse[ordre.indice[ty]].extremite[1];
			fin = coulisse[ordre.indice[ty]].extremite[2];
			x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
			x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
			y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
			x1 = (float) (x1 / 2.0);
			y1 = (float) (y1 / 2.0);
			Text(x1,y1,str);
			}
		}
	}


void dessiner_numero_total()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_total\n");
	SetColor(col);*/
	
	Color(BLACK);

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		/*printf("pa %d x %f x %f\n",pa,noeud[pa].x,noeud[pa].y);*/
		sprintf(str,"%d",pa);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		}
	}

void dessiner_numerotation_type()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"node type");

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%d",noeud[pa].type);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		}
	}

void dessiner_valeur_masse()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"node mass (Kg)");

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].mx);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].my);
		Text(x1,y1-0.02,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].mz);
		Text(x1,y1-2*0.02,str);
		}
	}

void dessiner_valeur_longueur()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"node size (m)");

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].lonx);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].lony);
		Text(x1,y1-0.02,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].lonz);
		Text(x1,y1-2*0.02,str);
		}
	}

void dessiner_valeur_cd()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"node drag coefficient");

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].cdx);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].cdy);
		Text(x1,y1-0.02,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].cdz);
		Text(x1,y1-2*0.02,str);
		}
	}

void dessiner_valeur_effort_exterieur()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"node external forces (N)");

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].fextx);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].fexty);
		Text(x1,y1-0.02,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].fextz);
		Text(x1,y1-2*0.02,str);
		}
	}

void dessiner_valeur_fixation()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"node freedom: 0 = free, 1 = not free");

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%d",TypeNoeud[noeud[pa].type].fixx);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%d",TypeNoeud[noeud[pa].type].fixy);
		Text(x1,y1-0.02,str);
		sprintf(str,"%d",TypeNoeud[noeud[pa].type].fixz);
		Text(x1,y1-2*0.02,str);
		}
	}

void dessiner_valeur_limite()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"node limit (m)");

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].limx);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].limy);
		Text(x1,y1-0.02,str);
		sprintf(str,"%.3g",TypeNoeud[noeud[pa].type].limz);
		Text(x1,y1-2*0.02,str);
		}
	}

void dessiner_valeur_sens_limite()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	lecture_des();
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"limit sens : 1 = > limit and -1 = < limit");

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%d",TypeNoeud[noeud[pa].type].senx);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%d",TypeNoeud[noeud[pa].type].seny);
		Text(x1,y1-0.02,str);
		sprintf(str,"%d",TypeNoeud[noeud[pa].type].senz);
		Text(x1,y1-2*0.02,str);
		}
	}

void dessiner_valeur_symetrie()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	lecture_des();
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"node symmetry: 0 = no symmetry, 1 = symmetry");

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%d",TypeNoeud[noeud[pa].type].symx);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%d",TypeNoeud[noeud[pa].type].symy);
		Text(x1,y1-0.02,str);
		sprintf(str,"%d",TypeNoeud[noeud[pa].type].symz);
		Text(x1,y1-2*0.02,str);
		}
	}


void dessiner_nb_mailles()
	{
	int pa,no,col,deb;
	float x1,y1,xb,yb,dist,xp,yp,norm_1b;
	char str[80];
	
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	lecture_des();
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"U and V meshes number");
	dist =  (float) (0.0);

	/*for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%.3g",noeud[pa].U);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%.3g",noeud[pa].V);
		Text(x1,y1-0.02,str);
		}*/

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			xb = (float) (0.0);
			yb = (float) (0.0); 	/*barycentre position of the panel*/
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				deb = panneau[pa].noeud_contour[no];
				xb += (float) (noeud[deb].x - binx) / (baxx - binx);
				yb += (float) (noeud[deb].y - biny) / (baxy - biny);
				}
			xb = xb / panneau[pa].nb_noeud_contour;
			yb = yb / panneau[pa].nb_noeud_contour;
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				/*deb = panneau[pa].noeud_contour[no];
				sprintf(str,"%.3g",noeud[deb].U);
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				sprintf(str,"%.3g",noeud[deb].V);
				Text(x1,y1-0.02,str);*/
				deb = panneau[pa].noeud_contour[no];
				sprintf(str,"%.3g, %.3g",noeud[deb].U,noeud[deb].V);
				sprintf(str,"%5.1f, %5.1f",noeud[deb].U,noeud[deb].V);
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				norm_1b =  (float) fabs((xb-x1)*(xb-x1) + (yb-y1)*(yb-y1));
				xp = x1 + dist/norm_1b * (xb-x1);
				yp = y1 + dist/norm_1b * (yb-y1);
				Text(xp,yp,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			for (no=1;no<=panneau[pa].nb_noeud_cote;no++)
				{
				deb = panneau[pa].noeud_cote[no];
				sprintf(str,"%.3g",noeud[deb].U);
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				sprintf(str,"%.3g",noeud[deb].V);
				Text(x1,y1-0.02,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			for (no=1;no<=panneau[pa].nb_noeud_interieur;no++)
				{
				deb = panneau[pa].noeud_interieur[no];
				sprintf(str,"%.3g",noeud[deb].U);
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				sprintf(str,"%.3g",noeud[deb].V);
				Text(x1,y1-0.02,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{
			deb = pan_hexa[pa].noeud_contour[no];
			sprintf(str,"%.3g",noeud[deb].U);
			x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			sprintf(str,"%.3g",noeud[deb].V);
			Text(x1,y1-0.02,str);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no=1;no<=pan_hexa[pa].nb_noeud_cote;no++)
			{
			deb = pan_hexa[pa].noeud_cote[no];
			sprintf(str,"%.3g",noeud[deb].U);
			x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			sprintf(str,"%.3g",noeud[deb].V);
			Text(x1,y1-0.02,str);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no=1;no<=pan_hexa[pa].nb_noeud_interieur;no++)
			{
			deb = pan_hexa[pa].noeud_interieur[no];
			sprintf(str,"%.3g",noeud[deb].U);
			x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			sprintf(str,"%.3g",noeud[deb].V);
			Text(x1,y1-0.02,str);
			}
		}
	}


void dessiner_nb_cotes_mailles()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0); 	/*decalage de 0 puisque c est un noeud*/
	Text(x1,y1,"meshes number along u and v");

	/*for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%.3g",noeud[pa].u);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		sprintf(str,"%.3g",noeud[pa].v);
		Text(x1,y1-0.02,str);
		}*/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				deb = panneau[pa].noeud_contour[no];
				sprintf(str,"%.3g",noeud[deb].u);
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				sprintf(str,"%.3g",noeud[deb].v);
				Text(x1,y1-0.02,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			for (no=1;no<=panneau[pa].nb_noeud_cote;no++)
				{
				deb = panneau[pa].noeud_cote[no];
				sprintf(str,"%.3g",noeud[deb].u);
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				sprintf(str,"%.3g",noeud[deb].v);
				Text(x1,y1-0.02,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			for (no=1;no<=panneau[pa].nb_noeud_interieur;no++)
				{
				deb = panneau[pa].noeud_interieur[no];
				sprintf(str,"%.3g",noeud[deb].u);
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				sprintf(str,"%.3g",noeud[deb].v);
				Text(x1,y1-0.02,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{
			deb = pan_hexa[pa].noeud_contour[no];
			sprintf(str,"%.3g",noeud[deb].u);
			x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			sprintf(str,"%.3g",noeud[deb].v);
			Text(x1,y1-0.02,str);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no=1;no<=pan_hexa[pa].nb_noeud_cote;no++)
			{
			deb = pan_hexa[pa].noeud_cote[no];
			sprintf(str,"%.3g",noeud[deb].u);
			x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			sprintf(str,"%.3g",noeud[deb].v);
			Text(x1,y1-0.02,str);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no=1;no<=pan_hexa[pa].nb_noeud_interieur;no++)
			{
			deb = pan_hexa[pa].noeud_interieur[no];
			sprintf(str,"%.3g",noeud[deb].u);
			x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			sprintf(str,"%.3g",noeud[deb].v);
			Text(x1,y1-0.02,str);
			}
		}
	}

void dessiner_longueur_cotes()
	{
	int pa,no,deb,fin,col;
	float x1,y1,longueur,long_l,long_m,long_n,nbmax,nbU,nbV;
	char str[80],str_l[80],str_m[80],str_n[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 2.0 * 0.02); 	/*decalage de 2 puisque c est un cote*/
	Text(x1,y1,"stretched side length (m)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				deb = panneau[pa].noeud_contour[no];
				if (no != panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[no+1];
				if (no == panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[1];
				nbU = fabs(noeud[deb].U - noeud[fin].U);
				nbV = fabs(noeud[deb].V - noeud[fin].V);
				if (nbU > nbV) 	nbmax = nbU;
				else 		nbmax = nbV;
				longueur = nbmax * 2.0 *panneau[pa].longueur_repos; 
				sprintf(str,"%.3g",longueur);
				
				x1 = (float) (0.5 * (noeud[deb].x + noeud[fin].x) - binx) / (baxx - binx);
				y1 = (float) (0.5 * (noeud[deb].y + noeud[fin].y) - biny) / (baxy - biny);
				
				Text(x1,y1,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{
			deb = pan_hexa[pa].noeud_contour[no];
			if (no != pan_hexa[pa].nb_noeud_contour) fin = pan_hexa[pa].noeud_contour[no+1];
			if (no == pan_hexa[pa].nb_noeud_contour) fin = pan_hexa[pa].noeud_contour[1];
			nbU = fabs(noeud[deb].U - noeud[fin].U);
			nbV = fabs(noeud[deb].V - noeud[fin].V);
			if (nbU > nbV) 	nbmax = nbU;
			else 		nbmax = nbV;
			long_l = nbmax * 2.0 *pan_hexa[pa].lo_repos; 
			long_m = nbmax * 2.0 *pan_hexa[pa].mo_repos; 
			long_n = nbmax * 2.0 *pan_hexa[pa].no_repos; 
			sprintf(str_l,"%.3g",long_l);
			sprintf(str_m,"%.3g",long_m);
			sprintf(str_n,"%.3g",long_n);
			
			x1 = (float) (0.5 * (noeud[deb].x + noeud[fin].x) - binx) / (baxx - binx);
			y1 = (float) (0.5 * (noeud[deb].y + noeud[fin].y) - biny) / (baxy - biny);
			
			Text(x1,y1,str_l);
			Text(x1,y1+0.01,str_m);
			Text(x1,y1+0.02,str_n);
			}
		}
	}

void dessiner_panel_cutting()
	{
	int pa,no,deb,fin,col;
	float x1,y1,longueur,long_l,long_m,long_n,nbmax,nbU,nbV;
/* debut modifdp du 29 mars 2010*/
	char str[80],str_l[80],str_m[80],str_n[80],strU[80],strV[80],strt[80],strb[80],strn[80];
/* fin modifdp du 29 mars 2010*/
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_type\n");
	SetColor(col);*/
	
	Color(BLACK);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 2.0 * 0.02); 	/*decalage de 2 puisque c est un cote*/
	Text(x1,y1,"panel cutting");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if ((panneau[pa].flag_dessin != 0) && (panneau[pa].seam == 0.0))
			{
			Color(BLACK);
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				deb = panneau[pa].noeud_contour[no];
				if (no != panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[no+1];
				if (no == panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[1];
				nbU = fabs(noeud[deb].U - noeud[fin].U);
				nbV = fabs(noeud[deb].V - noeud[fin].V);

				if (nbU == 0) 		sprintf(str,"%.3g N",nbV);
				if (nbV == 0) 		sprintf(str,"%.3g T",nbU);
				if (nbU == nbV) 	sprintf(str,"%.3g AB",nbU);
				if ((nbU != 0) && (nbV != 0) && (nbU > nbV)) 	sprintf(str,"%.3g T %.3g B",nbU,nbV);
				if ((nbU != 0) && (nbV != 0) && (nbU < nbV)) 	sprintf(str,"%.3g N %.3g B",nbV,nbU);
/* debut modifdp du 29 mars 2010*/
							sprintf(strU,"%3.1f",nbU);
				if (nbU >= 10)		sprintf(strU,"%2.0f",nbU);
				if (nbU >= 100)		sprintf(strU,"%3.0f",nbU);
				if (nbU >= 1000)	sprintf(strU,"%4.0f",nbU);
				if (nbU >= 10000)	sprintf(strU,"%5.0f",nbU);
							sprintf(strV,"%3.1f",nbV);
				if (nbV >= 10)		sprintf(strV,"%2.0f",nbV);
				if (nbV >= 100)		sprintf(strV,"%3.0f",nbV);
				if (nbV >= 1000)	sprintf(strV,"%4.0f",nbV);
				if (nbV >= 10000)	sprintf(strV,"%5.0f",nbV);
				if (nbU == 0) 		sprintf(str,"%s N",strV);
				if (nbV == 0) 		sprintf(str,"%s T",strU);
				if (nbU == nbV) 	sprintf(str,"%s AB",strU);
				if ((nbU != 0) && (nbV != 0) && (nbU > nbV)) 	sprintf(str,"%s T %s B",strU,strV);
				if ((nbU != 0) && (nbV != 0) && (nbU < nbV)) 	sprintf(str,"%s N %s B",strV,strU);
/* fin modifdp du 29 mars 2010*/

/* debut modifdp du 31 mai 2010*/
				if (nbU > nbV)
					{
								sprintf(strb,"%3.1f",2.0*nbV);
					if (2.0*nbV >= 10)	sprintf(strb,"%2.0f",2.0*nbV);
					if (2.0*nbV >= 100)	sprintf(strb,"%3.0f",2.0*nbV);
					if (2.0*nbV >= 1000)	sprintf(strb,"%4.0f",2.0*nbV);
					if (2.0*nbV >= 10000)	sprintf(strb,"%5.0f",2.0*nbV);
								sprintf(strt,"%3.1f",nbU-nbV);
					if (nbU-nbV >= 10)	sprintf(strt,"%2.0f",nbU-nbV);
					if (nbU-nbV >= 100)	sprintf(strt,"%3.0f",nbU-nbV);
					if (nbU-nbV >= 1000)	sprintf(strt,"%4.0f",nbU-nbV);
					if (nbU-nbV >= 10000)	sprintf(strt,"%5.0f",nbU-nbV);
					sprintf(str,"%s T %s B",strt,strb);
					}
				if (nbU < nbV)
					{
								sprintf(strb,"%3.1f",2.0*nbU);
					if (2.0*nbU >= 10)	sprintf(strb,"%2.0f",2.0*nbU);
					if (2.0*nbU >= 100)	sprintf(strb,"%3.0f",2.0*nbU);
					if (2.0*nbU >= 1000)	sprintf(strb,"%4.0f",2.0*nbU);
					if (2.0*nbU >= 10000)	sprintf(strb,"%5.0f",2.0*nbU);
								sprintf(strn,"%3.1f",nbV-nbU);
					if (nbV-nbU >= 10)	sprintf(strn,"%2.0f",nbV-nbU);
					if (nbV-nbU >= 100)	sprintf(strn,"%3.0f",nbV-nbU);
					if (nbV-nbU >= 1000)	sprintf(strn,"%4.0f",nbV-nbU);
					if (nbV-nbU >= 10000)	sprintf(strn,"%5.0f",nbV-nbU);
					sprintf(str,"%s N %s B",strn,strb);
					}
				if (nbU == 0) 		sprintf(str,"%.3g N",nbV);
				if (nbV == 0) 		sprintf(str,"%.3g T",nbU);
				if (nbU == nbV) 	sprintf(str,"%.3g AB",nbU);
/* fin modifdp du 31 mai 2010*/

				
				x1 = (float) (0.5 * (noeud[deb].x + noeud[fin].x) - binx) / (baxx - binx);
				y1 = (float) (0.5 * (noeud[deb].y + noeud[fin].y) - biny) / (baxy - biny);
				
				Text(x1,y1,str);
				}
			}
		if ((panneau[pa].flag_dessin != 0) && (panneau[pa].seam != 0.0))
			{
			Color(RED);
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				deb = panneau[pa].noeud_contour[no];
				if (no != panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[no+1];
				if (no == panneau[pa].nb_noeud_contour) fin = panneau[pa].noeud_contour[1];
				nbU = fabs(noeud_seam[deb].U - noeud_seam[fin].U);
				nbV = fabs(noeud_seam[deb].V - noeud_seam[fin].V);

				if (nbU == 0) 		sprintf(str,"%.3g N",nbV);
				if (nbV == 0) 		sprintf(str,"%.3g T",nbU);
				if (nbU == nbV) 	sprintf(str,"%.3g AB",nbU);
				if ((nbU != 0) && (nbV != 0) && (nbU > nbV)) 	sprintf(str,"%.3g T %.3g B",nbU,nbV);
				if ((nbU != 0) && (nbV != 0) && (nbU < nbV)) 	sprintf(str,"%.3g N %.3g B",nbV,nbU);
				
				x1 = (float) (0.5 * (noeud_seam[deb].x + noeud_seam[fin].x) - binx) / (baxx - binx);
				y1 = (float) (0.5 * (noeud_seam[deb].y + noeud_seam[fin].y) - biny) / (baxy - biny);
				
				Text(x1,y1,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{
			deb = pan_hexa[pa].noeud_contour[no];
			if (no != pan_hexa[pa].nb_noeud_contour) fin = pan_hexa[pa].noeud_contour[no+1];
			if (no == pan_hexa[pa].nb_noeud_contour) fin = pan_hexa[pa].noeud_contour[1];
			nbU = fabs(noeud[deb].U - noeud[fin].U);
			nbV = fabs(noeud[deb].V - noeud[fin].V);
			if (nbU > nbV) 	nbmax = nbU;
			else 		nbmax = nbV;
			long_l = nbmax * 2.0 *pan_hexa[pa].lo_repos; 
			long_m = nbmax * 2.0 *pan_hexa[pa].mo_repos; 
			long_n = nbmax * 2.0 *pan_hexa[pa].no_repos; 
			sprintf(str_l,"%.3g",long_l);
			sprintf(str_m,"%.3g",long_m);
			sprintf(str_n,"%.3g",long_n);
			
			x1 = (float) (0.5 * (noeud[deb].x + noeud[fin].x) - binx) / (baxx - binx);
			y1 = (float) (0.5 * (noeud[deb].y + noeud[fin].y) - biny) / (baxy - biny);
			
			Text(x1,y1,str_l);
			Text(x1,y1+0.01,str_m);
			Text(x1,y1+0.02,str_n);
			}
		}
	}
	
void dessiner_numero_global()
	{
	int pa,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_global\n");
	SetColor(col);*/
	
	Color(BLACK);

	for (pa=1;pa<=Structure.nb_total;pa++)
		{ 
		sprintf(str,"%d",total2global[pa]);
		deb = pa;
		x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
		Text(x1,y1,str);
		}
	}

void dessiner_numero_local()
	{
	int pa,el,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_local\n");
	SetColor(col);*/
	
	Color(BLACK);

	for (el=1;el<=Structure.NbTypeelem;el++)
		{ 
		if (element[el].flag_maillage == 1)
			{
			for (no=1;no<=element[el].nb_barre - 1;no++)
				{
				sprintf(str,"%d",no);
				deb = element[el].noeud[no];
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_maillage == 1)
			{
			for (no=1;no<=panneau[pa].nb_noeud_cote;no++)
				{
				sprintf(str,"%d",no);
				deb = panneau[pa].noeud_cote[no];
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		if (pan_hexa[pa].flag_maillage == 1)
			{
			for (no=1;no<=pan_hexa[pa].nb_noeud_cote;no++)
				{
				sprintf(str,"%d",no);
				deb = pan_hexa[pa].noeud_cote[no];
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				}
			}
		}
	}

void dessiner_numero_interieur()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_interieur\n");
	SetColor(col);*/
	
	Color(RED);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			if (panneau[pa].flag_maillage == 1)
				{
				for (no=1;no<=panneau[pa].nb_noeud_interieur;no++)
					{
					sprintf(str,"%d",no);
					deb = panneau[pa].noeud_interieur[no];
					x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
					y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
					Text(x1,y1,str);
					}
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		if (pan_hexa[pa].flag_maillage == 1)
			{
			for (no=1;no<=pan_hexa[pa].nb_noeud_interieur;no++)
				{
				sprintf(str,"%d",no);
				deb = pan_hexa[pa].noeud_interieur[no];
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				}
			}
		}
	}

void dessiner_numero_coin()
	{
	int pa,el,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_coin\n");
	SetColor(col);*/
	
	Color(BLACK);
	for (el=1;el<=Structure.NbTypeelem;el++)
		{ 
		if (element[el].flag_dessin != 0)
			{
			for (no=1;no<=2;no++)
				{
				sprintf(str,"%d",no);
				deb = element[el].extremite[no];
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				}
			}
		}
	for (el=1;el<=Structure.nombreCoulisses;el++)
		{ 
		for (no=1;no<=2;no++)
			{
			sprintf(str,"%d",no);
			deb = coulisse[el].extremite[no];
			x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{
				sprintf(str,"%d",no);
				deb = panneau[pa].noeud_contour[no];
				x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
				Text(x1,y1,str);
				}
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{
			sprintf(str,"%d",no);
			deb = pan_hexa[pa].noeud_contour[no];
			x1 = (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 = (float) (noeud[deb].y - biny) / (baxy - biny);
			Text(x1,y1,str);
			}
		}
	}

void dessiner_raideur_traction()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80],str_l[80],str_m[80],str_n[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"raideur en traction (N)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].raideur_traction);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		sprintf(str_l,"%.3g",pan_hexa[pa].raideur_traction_l);
		sprintf(str_m,"%.3g",pan_hexa[pa].raideur_traction_m);
		sprintf(str_n,"%.3g",pan_hexa[pa].raideur_traction_n);
		Text(x1,y1     ,str_l);
		Text(x1,y1+0.01,str_m);
		Text(x1,y1+0.02,str_n);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",element[pa].raideur_traction);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",coulisse[pa].raideur_traction);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_raideur_compression()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80],str_l[80],str_m[80],str_n[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);

	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"raideur en compression (N)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].raideur_compression);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		sprintf(str_l,"%.3g",pan_hexa[pa].raideur_compression_l);
		sprintf(str_m,"%.3g",pan_hexa[pa].raideur_compression_m);
		sprintf(str_n,"%.3g",pan_hexa[pa].raideur_compression_n);
		Text(x1,y1     ,str_l);
		Text(x1,y1+0.01,str_m);
		Text(x1,y1+0.02,str_n);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",element[pa].raideur_compression);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",coulisse[pa].raideur_compression);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_raideur_ouverture()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);

	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"raideur a l ouverture des mailles (N.m/rad)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].raideur_ouverture);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	}

void dessiner_longueur_repos()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80],str_l[80],str_m[80],str_n[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"longueur au repos (m)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%.3g",panneau[pa].longueur_repos);
			for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
				{ 
				deb = panneau[pa].noeud_contour[no];
				x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
			y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
			Text(x1,y1,str);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		sprintf(str_l,"%.3g",pan_hexa[pa].lo_repos);
		sprintf(str_m,"%.3g",pan_hexa[pa].mo_repos);
		sprintf(str_n,"%.3g",pan_hexa[pa].no_repos);
		Text(x1,y1,str_l);
		Text(x1,y1+0.01,str_m);
		Text(x1,y1+0.02,str_n);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		if (element[pa].flag_dessin != 0)
			{
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%.3g",element[pa].lgrepos);
			for (no=1;no<=2;no++)
				{ 
				deb = element[pa].extremite[no];
				x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 2);
			y1 = (float) (y1 / 2);
			Text(x1,y1,str);
			}
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",coulisse[pa].lgrepos);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_bar_length()
	{
	int pa,col,deb,fin;
	float x1,y1;
	char str[80];
	
	/*col=GetRGBColor(0,255,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_barre\n");
	SetColor(col);*/
	
	lecture_des();
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"unstretched length bar (m)");


	for (pa=1;pa<=Structure.nb_barre;pa++)
		{ 
		sprintf(str,"%.3g",barre[pa].longueur_repos);
		deb = barre[pa].noeud[1];
		fin = barre[pa].noeud[2];
		x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
		x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
		y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
		x1 = (float) (x1 / 2.0);
		y1 = (float) (y1 / 2.0);
		Text(x1,y1,str);
		}
	}

void dessiner_masse_volumique()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"masse volumique (kg/m^3)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].rho);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",pan_hexa[pa].rho);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",element[pa].rhoelement);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",coulisse[pa].rhocoulisse);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_diametre()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80],str_l[80],str_m[80],str_n[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"diametre (m)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].diam_hydro);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		sprintf(str_l,"%.3g",pan_hexa[pa].diam_hydro_l);
		sprintf(str_m,"%.3g",pan_hexa[pa].diam_hydro_m);
		sprintf(str_n,"%.3g",pan_hexa[pa].diam_hydro_n);
		Text(x1,y1     ,str_l);
		Text(x1,y1+0.01,str_m);
		Text(x1,y1+0.02,str_n);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",element[pa].diametrehydro);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",coulisse[pa].diametrehydro);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_largeur_noeud()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"knots size (m)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].largeurnoeud);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	}

void dessiner_coefficient_cd()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"coefficient de frottement normal : cd");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].cdnormal);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",pan_hexa[pa].cdnormal);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",element[pa].cdnormal);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",coulisse[pa].cdnormal);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_coefficient_f()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"coefficient de frottement tangentiel : f");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].ftangent);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",pan_hexa[pa].ftangent);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",element[pa].ftangent);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",coulisse[pa].ftangent);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_panel_drag()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(BLUE);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"panel drag N");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].drag);
		sprintf(str,"%5.0lf",panneau[pa].drag);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",pan_hexa[pa].drag);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
		
	Color(BLACK);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",element[pa].ftangent);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		/*Text(x1,y1,str);*/
		}
		
	Color(RED);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",coulisse[pa].ftangent);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		/*Text(x1,y1,str);*/
		}
	}

void dessiner_longueur_maillage()
	{
	int pa,no,col,deb;
	float x1,y1,pas_mail;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"longueur des maillages (m)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].pas_maillage);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",pan_hexa[pa].pas_maillage);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		pas_mail = (float) (element[pa].lgrepos / element[pa].nb_barre);
		sprintf(str,"%.3g",pas_mail);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		pas_mail = (float) (coulisse[pa].lgrepos / (coulisse[pa].nb_noeud+1));
		sprintf(str,"%.3g",pas_mail);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_type_maillage()
	{
	int pa,no,col,deb;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"type de maillage des panneaux");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%d",panneau[pa].type_maillage);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%d",pan_hexa[pa].type_maillage);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	}

void dessiner_section_element()
	{
	int pa,no,col,deb;
	float x1,y1,section;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"cable/twine section (m^2)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		section = PI * panneau[pa].diam_hydro * panneau[pa].diam_hydro / 4.0 ;
		sprintf(str,"%.3g",section);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		section = PI * element[pa].diametrehydro * element[pa].diametrehydro / 4.0 ;
		sprintf(str,"%.3g",section);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		section = PI * coulisse[pa].diametrehydro * coulisse[pa].diametrehydro / 4.0 ;
		sprintf(str,"%.3g",section);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_volume_element()
	{
	int pa,no,col,deb;
	float x1,y1,volume;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"bar/twine volume (m^3)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		volume = PI * panneau[pa].diam_hydro * panneau[pa].diam_hydro / 4.0  * panneau[pa].longueur_repos ;
		sprintf(str,"%.3g",volume);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		volume = 0.0;
		volume += PI * pan_hexa[pa].diam_hydro_l * pan_hexa[pa].diam_hydro_l / 4.0 * pan_hexa[pa].lo_repos;
		volume += PI * pan_hexa[pa].diam_hydro_m * pan_hexa[pa].diam_hydro_m / 4.0 * pan_hexa[pa].mo_repos;
		volume += PI * pan_hexa[pa].diam_hydro_n * pan_hexa[pa].diam_hydro_n / 4.0 * pan_hexa[pa].no_repos;
		sprintf(str,"%.3g",volume);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		volume = PI * element[pa].diametrehydro * element[pa].diametrehydro / 4.0  * element[pa].lgrepos ;
		sprintf(str,"%.3g",volume);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		volume = PI * coulisse[pa].diametrehydro * coulisse[pa].diametrehydro / 4.0  * coulisse[pa].lgrepos ;
		sprintf(str,"%.3g",volume);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_masse_element()
	{
	int pa,no,col,deb;
	float x1,y1,masse,mass_surf,mass_hexa,mass_elem,mass_coul,mass_node,mass_total;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);

	mass_surf = 0.0;
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		masse = PI * panneau[pa].diam_hydro * panneau[pa].diam_hydro / 4.0 * panneau[pa].rho  * panneau[pa].longueur_repos;
		mass_surf += masse;
		sprintf(str,"%.3g",masse);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	mass_hexa = 0.0;
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		masse = 0.0;
		masse += PI * pan_hexa[pa].diam_hydro_l * pan_hexa[pa].diam_hydro_l / 4.0 * pan_hexa[pa].rho  * pan_hexa[pa].lo_repos;
		masse += PI * pan_hexa[pa].diam_hydro_m * pan_hexa[pa].diam_hydro_m / 4.0 * pan_hexa[pa].rho  * pan_hexa[pa].mo_repos;
		masse += PI * pan_hexa[pa].diam_hydro_n * pan_hexa[pa].diam_hydro_n / 4.0 * pan_hexa[pa].rho  * pan_hexa[pa].no_repos;
		mass_hexa += masse;
		sprintf(str,"%.3g",masse);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
		
	Color(BLUE);	
	mass_elem = 0.0;
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		masse = PI * element[pa].diametrehydro * element[pa].diametrehydro / 4.0 * element[pa].rhoelement  * element[pa].lgrepos;
		mass_elem += masse;
		sprintf(str,"%.3g",masse);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	mass_coul = 0.0;
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		masse = PI * coulisse[pa].diametrehydro * coulisse[pa].diametrehydro / 4.0 * coulisse[pa].rhocoulisse  * coulisse[pa].lgrepos;
		mass_coul += masse;
		sprintf(str,"%.3g",masse);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	mass_node = 0.0;
  	for (pa = 1 ; pa<=Structure.nb_global  ; pa++) 
  		{
		mass_node += TypeNoeud[noeud_global[pa].type].mz;
  		}
		
	mass_total = mass_surf + mass_hexa + mass_elem + mass_coul + mass_node;
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	//Text(x1,y1,"twine mass (kg) surf %lf hexa %lf elem %lf node %lf total %lf",mass_surf,mass_hexa,mass_elem,mass_node,mass_total);

	sprintf(str,"%.3g",mass_surf);	Text(x1+0.0,y1+5*0.02,"mass surf : ");	Text(x1+0.1,y1+5*0.02,str);
	sprintf(str,"%.3g",mass_elem);	Text(x1+0.2,y1+5*0.02,"mass elem : ");	Text(x1+0.3,y1+5*0.02,str);
	sprintf(str,"%.3g",mass_node);	Text(x1+0.4,y1+5*0.02,"mass node : ");	Text(x1+0.5,y1+5*0.02,str);
	sprintf(str,"%.3g",mass_total);	Text(x1+0.6,y1+5*0.02,"mass total : ");	Text(x1+0.7,y1+5*0.02,str);

	}

void dessiner_masse_lineique()
	{
	int pa,no,col,deb;
	float x1,y1,masse;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"lineic mass (kg/m)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		masse = PI * panneau[pa].diam_hydro * panneau[pa].diam_hydro / 4.0 * panneau[pa].rho ;
		sprintf(str,"%.3g",masse);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		masse = PI * element[pa].diametrehydro * element[pa].diametrehydro / 4.0 * element[pa].rhoelement ;
		sprintf(str,"%.3g",masse);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		masse = PI * coulisse[pa].diametrehydro * coulisse[pa].diametrehydro / 4.0 * coulisse[pa].rhocoulisse ;
		sprintf(str,"%.3g",masse);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_flottabilite()
	{
	int pa,no,col,deb;
	float x1,y1,flotab;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"floatability in water (kg)");

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		flotab = PI * panneau[pa].diam_hydro * panneau[pa].diam_hydro * panneau[pa].longueur_repos / 4.0 * RHO;
		sprintf(str,"%.3g",flotab);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		flotab = 0.0;
		flotab += PI * pan_hexa[pa].diam_hydro_l * pan_hexa[pa].diam_hydro_l * pan_hexa[pa].lo_repos / 4.0 *(RHO) ;
		flotab += PI * pan_hexa[pa].diam_hydro_m * pan_hexa[pa].diam_hydro_m * pan_hexa[pa].mo_repos / 4.0 *(RHO) ;
		flotab += PI * pan_hexa[pa].diam_hydro_n * pan_hexa[pa].diam_hydro_n * pan_hexa[pa].no_repos / 4.0 *(RHO) ;
		sprintf(str,"%.3g",flotab);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		flotab = PI * element[pa].diametrehydro * element[pa].diametrehydro * element[pa].lgrepos / 4.0 * (RHO) ;
		sprintf(str,"%.3g",flotab);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		flotab = PI * coulisse[pa].diametrehydro * coulisse[pa].diametrehydro * coulisse[pa].lgrepos / 4.0 * (RHO) ;
		sprintf(str,"%.3g",flotab);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}

void dessiner_EI_flexion_cable()
	{
	int pa,no,col,deb;
	float x1,y1,flotab;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	x1 = (float) (0.0);
	y1 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x1,y1,"EI flexion cable (N m2)");

		
	Color(RED);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		flotab = TypeElement[pa].EI_flexion;
		if (flotab > 0.0)
			{
			sprintf(str,"%.3g",flotab);
			for (no=1;no<=2;no++)
				{ 
				deb = element[pa].extremite[no];
				x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 2);
			y1 = (float) (y1 / 2);
			Text(x1,y1,str);
			}
		}
	}

void dessiner_courant()
	{
	float x1,y1,temp;
	char str[80];
	
	Color(BLUE);
	x1 = (float) (0.0);
	y1 = (float) (0.0);
	temp = (float) (Courant.vitesse/1852.0*3600.0);
	sprintf(str,"%.3g",temp);
	Text(x1,y1+1*0.02,"current speed (knot) : ");
	Text(x1+0.3,y1+1*0.02,str);
	temp = (float) (Courant.direction);
	sprintf(str,"%.3g",temp);
	Text(x1,y1+2*0.02,"current direction (degre) : ");
	Text(x1+0.3,y1+2*0.02,str);
	}

void dessiner_Prise_volume()
	{
	float x1,y1,temp;
	char str[80];
	
	Color(BLUE);
	x1 = (float) (0.0);
	y1 = (float) (0.0);
	
	temp = (float) (Prise.volume);
	sprintf(str,"%.3g",temp);
	Text(x1,y1+3*0.02,"catch volume (m^3): ");
	Text(x1+0.3,y1+3*0.02,str);
	
	temp = (float) (Prise.seuil);
	sprintf(str,"%.3g",temp);
	Text(x1,y1+4*0.02,"catch accuracy (m^3): ");
	Text(x1+0.3,y1+4*0.02,str);
	
	temp = (float) (Prise.cd);
	sprintf(str,"%.3g",temp);
	Text(x1,y1+5*0.02,"catch drag coef.: ");
	Text(x1+0.3,y1+5*0.02,str);
	}

void dessiner_frottement_fond()
	{
	float x1,y1,temp;
	char str[80];
	
	Color(BLUE);
	x1 = (float) (0.0);
	y1 = (float) (0.0);
	
	temp = (float) (Bottom.coef_frottement);
	sprintf(str,"%.3g",temp);
	Text(x1,y1+6*0.02,"bottom drag coef.: ");
	Text(x1+0.3,y1+6*0.02,str);
	
	temp = (float) (Bottom.raideur);
	sprintf(str,"%.3g",temp);
	Text(x1,y1+7*0.02,"bottom stiffness (N/m): ");
	Text(x1+0.3,y1+7*0.02,str);
	}

void dessiner_surface_fils()
	{
	float x1,y1,temp,flotab;
	char str[80];
	int pa,no,col,deb;
	
	
	lecture_des();
	Color(BLUE);
	x1 = (float) (0.0);
	y1 = (float) (0.0);
	
	temp = (float) (Structure.surface_fils);
	sprintf(str,"%.3g",temp);
	Text (x1,y1+8*0.02,"twines surface (m^2) : ");
	Text(x1+0.3,y1+8*0.02,str);
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur dessiner_numero_panneau\n");
	SetColor(col);*/
	
	Color(RED);
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",panneau[pa].surf_fils);
		//sprintf(str,"%.3g",panneau[pa].surf_fils/2.0/panneau[pa].longueur_repos/panneau[pa].diam_hydro);
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / panneau[pa].nb_noeud_contour);
		y1 = (float) (y1 / panneau[pa].nb_noeud_contour);
		Text(x1,y1,str);
		//printf("Twine surface of panel %4d = %.3g m^2\n",pa,panneau[pa].surf_fils);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		sprintf(str,"%.3g",pan_hexa[pa].surf_fils);
		for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
			{ 
			deb = pan_hexa[pa].noeud_contour[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / pan_hexa[pa].nb_noeud_contour);
		y1 = (float) (y1 / pan_hexa[pa].nb_noeud_contour);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.NbTypeelem;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		flotab = element[pa].diametrehydro * element[pa].lgrepos;
		sprintf(str,"%.3g",flotab);
		for (no=1;no<=2;no++)
			{ 
			deb = element[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
		
	Color(BLUE);
	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		x1 = 0.0;
		y1 = 0.0;
		flotab = coulisse[pa].diametrehydro * coulisse[pa].lgrepos;
		sprintf(str,"%.3g",flotab);
		for (no=1;no<=2;no++)
			{ 
			deb = coulisse[pa].extremite[no];
			x1 += (float) (noeud[deb].x - binx) / (baxx - binx);
			y1 += (float) (noeud[deb].y - biny) / (baxy - biny);
			}
		x1 = (float) (x1 / 2);
		y1 = (float) (y1 / 2);
		Text(x1,y1,str);
		}
	}


void filet_interne_dessiner()
	{
	/*defini les triangles poses sur le contour, 
	calcule les coordonnees en nb de mailles des sommets des triangles, 
	calcule */
	int pa,col;
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur filet_interne_dessiner\n");
	SetColor(col);*/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			dessiner_filet_interne(pa);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		dessiner_filet_interne(pa);
		}
	}

void internal_bar_dessiner()
	{
	int pa,col,deb,fin;
	float x1,y1,x2,y2;
	char str[80];
	
	lecture_des();
	Color(RED);

	for (pa=1;pa<=Structure.nb_barre;pa++)
		{ 
		deb = barre[pa].noeud[1];
		fin = barre[pa].noeud[2];
		x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
		y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
		x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
		y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
		Line(x1,y1,x2,y2);
		}
	}

void orientation_uv_dessiner()
	{
	/*defini les triangles poses sur le contour, 
	calcule les coordonnees en nb de mailles des sommets des triangles, 
	calcule */
	int pa,col;

	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur filet_interne_dessiner\n");
	SetColor(col);*/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		dessiner_orientation_uv(pa);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		dessiner_orientation_uv(pa);
		}
	}

void orientation_UV_dessiner()
	{
	/*defini les triangles poses sur le contour, 
	calcule les coordonnees en nb de mailles des sommets des triangles, 
	calcule */
	int pa,col;

	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur filet_interne_dessiner\n");
	SetColor(col);*/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		dessiner_orientation_UV(pa);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		dessiner_orientation_UV(pa);
		}
	}

void orientation_xy_dessiner()
	{
	/*defini les triangles poses sur le contour, 
	calcule les coordonnees en nb de mailles des sommets des triangles, 
	calcule */
	int pa,col;
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur filet_interne_dessiner\n");
	SetColor(col);*/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		dessiner_orientation_xy(pa);
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		dessiner_orientation_xy(pa);
		}
	}

	
void dessiner_filet_interne(int no_pa)
	{
	int no_triangle,no_tri_hexa,cote,deb,fin;
	float x1,x2,y1,y2;
	
	lecture_des();
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	//Color(BLACK);
	if (panneau[no_pa].flag_dessin == 1) Color(BLACK);
	if (panneau[no_pa].flag_dessin == 2) Color(BLUE);
	if (panneau[no_pa].flag_dessin == 3) Color(RED);
	if (panneau[no_pa].flag_dessin == 4) Color(GREEN);
	if (panneau[no_pa].flag_dessin == 5) Color(YELLOW);

	for (no_triangle=1;no_triangle<=panneau[no_pa].nb_triangle_interieur;no_triangle++)
		{ 
		for (cote=1;cote<=3;cote++)
			{ 
			/*numerotation totale des extremites des cotes du triangle*/
			deb = panneau[no_pa].triangle_interieur[no_triangle][cote];
			if (cote <  3) fin = panneau[no_pa].triangle_interieur[no_triangle][cote+1];
			if (cote == 3) fin = panneau[no_pa].triangle_interieur[no_triangle][1     ];
			/*numerotation totale des extremites des cotes du triangle*/
			x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
			x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
			y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);
			}
		}
	for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[no_pa].nb_tri_hexa_interieur;no_tri_hexa++)
		{ 
		for (cote=1;cote<=3;cote++)
			{ 
			/*numerotation totale des extremites des cotes du tri_hexa*/
			deb = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][cote];
			if (cote <  3) fin = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][cote+1];
			if (cote == 3) fin = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][1     ];
			/*numerotation totale des extremites des cotes du tri_hexa*/
			x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
			x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
			y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);
			}
		}
	}
	
void dessiner_orientation_uv(int no_pa)
	{
	int no_triangle,no_tri_hexa,sommet1,sommet2,sommet3;
	float u1,u2,u3,v1,v2,v3,orientation;
	
	lecture_des();
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	if (panneau[no_pa].flag_dessin == 1) Color(BLACK);
	if (panneau[no_pa].flag_dessin == 2) Color(BLUE);
	if (panneau[no_pa].flag_dessin == 3) Color(RED);
	if (panneau[no_pa].flag_dessin == 4) Color(GREEN);
	if (panneau[no_pa].flag_dessin == 5) Color(YELLOW);
	if (panneau[no_pa].flag_dessin == 6) Color(YELLOW);
	if (panneau[no_pa].flag_dessin == 7) Color(YELLOW);
	if (panneau[no_pa].flag_dessin == 8) Color(YELLOW);
	if (panneau[no_pa].flag_dessin == 9) Color(YELLOW);
	if (panneau[no_pa].flag_dessin == 10) Color(YELLOW);
	Color(BLUE);
	
	for (no_triangle=1;no_triangle<=panneau[no_pa].nb_triangle_interieur;no_triangle++)
		{ 
		sommet1 = panneau[no_pa].triangle_interieur[no_triangle][1];
		sommet2 = panneau[no_pa].triangle_interieur[no_triangle][2];
		sommet3 = panneau[no_pa].triangle_interieur[no_triangle][3];
		u1 = noeud[sommet1].u;
		u2 = noeud[sommet2].u;
		u3 = noeud[sommet3].u;
		v1 = noeud[sommet1].v;
		v2 = noeud[sommet2].v;
		v3 = noeud[sommet3].v;
		/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du triangle*/
		orientation = (u2-u1)*(v3-v1) - (u3-u1)*(v2-v1);
		
		if (orientation < 0.0)
			{
			//Color(BLUE);
			Move_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet2].x - binx) / (baxx - binx),((REEL) noeud[sommet2].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet3].x - binx) / (baxx - binx),((REEL) noeud[sommet3].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
			Surface_end();
			}
		}
	for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[no_pa].nb_tri_hexa_interieur;no_tri_hexa++)
		{ 
		sommet1 = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][1];
		sommet2 = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][2];
		sommet3 = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][3];
		u1 = noeud[sommet1].u;
		u2 = noeud[sommet2].u;
		u3 = noeud[sommet3].u;
		v1 = noeud[sommet1].v;
		v2 = noeud[sommet2].v;
		v3 = noeud[sommet3].v;
		/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du tri_hexa*/
		orientation = (u2-u1)*(v3-v1) - (u3-u1)*(v2-v1);
		
		if (orientation < 0.0)
			{
			Color(BLUE);
			Move_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet2].x - binx) / (baxx - binx),((REEL) noeud[sommet2].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet3].x - binx) / (baxx - binx),((REEL) noeud[sommet3].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
			Surface_end();
			}
		}
	}
	
void dessiner_orientation_UV(int no_pa)
	{
	int no_triangle,no_tri_hexa,sommet1,sommet2,sommet3;
	float u1,u2,u3,v1,v2,v3,orientation;
	
	lecture_des();
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	Color(BLUE);

	for (no_triangle=1;no_triangle<=panneau[no_pa].nb_triangle_interieur;no_triangle++)
		{ 
		sommet1 = panneau[no_pa].triangle_interieur[no_triangle][1];
		sommet2 = panneau[no_pa].triangle_interieur[no_triangle][2];
		sommet3 = panneau[no_pa].triangle_interieur[no_triangle][3];
		u1 = noeud[sommet1].U;
		u2 = noeud[sommet2].U;
		u3 = noeud[sommet3].U;
		v1 = noeud[sommet1].V;
		v2 = noeud[sommet2].V;
		v3 = noeud[sommet3].V;
		/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du triangle*/
		orientation = (u2-u1)*(v3-v1) - (u3-u1)*(v2-v1);
		
		if (orientation < 0.0)
			{
			Color(BLUE);
			Move_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet2].x - binx) / (baxx - binx),((REEL) noeud[sommet2].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet3].x - binx) / (baxx - binx),((REEL) noeud[sommet3].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
			Surface_end();
			}
		}
	for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[no_pa].nb_tri_hexa_interieur;no_tri_hexa++)
		{ 
		sommet1 = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][1];
		sommet2 = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][2];
		sommet3 = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][3];
		u1 = noeud[sommet1].U;
		u2 = noeud[sommet2].U;
		u3 = noeud[sommet3].U;
		v1 = noeud[sommet1].V;
		v2 = noeud[sommet2].V;
		v3 = noeud[sommet3].V;
		/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du tri_hexa*/
		orientation = (u2-u1)*(v3-v1) - (u3-u1)*(v2-v1);
		
		if (orientation < 0.0)
			{
			Color(BLUE);
			Move_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet2].x - binx) / (baxx - binx),((REEL) noeud[sommet2].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet3].x - binx) / (baxx - binx),((REEL) noeud[sommet3].y - biny) / (baxy - biny));
			Line_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
			Surface_end();
			}
		}
	}
	
void dessiner_orientation_xy(int no_pa)
	{
	int no_triangle,no_tri_hexa,sommet1,sommet2,sommet3;
	float u1,u2,u3,v1,v2,v3,orientation,x1,y1;
	
	lecture_des();
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	x1 = (float) (0.0);
	y1 = (float) (0.0);	
	Text (x1,y1+8*0.02,"Grey : inside, White : outside");

	Color(BLUE);
	gris_interne = ColorRGB(150,150,150);

	for (no_triangle=1;no_triangle<=panneau[no_pa].nb_triangle_interieur;no_triangle++)
		{ 
		sommet1 = panneau[no_pa].triangle_interieur[no_triangle][1];
		sommet2 = panneau[no_pa].triangle_interieur[no_triangle][2];
		sommet3 = panneau[no_pa].triangle_interieur[no_triangle][3];
		u1 = noeud[sommet1].x;
		u2 = noeud[sommet2].x;
		u3 = noeud[sommet3].x;
		v1 = noeud[sommet1].y;
		v2 = noeud[sommet2].y;
		v3 = noeud[sommet3].y;
		/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du triangle*/
		orientation = (u2-u1)*(v3-v1) - (u3-u1)*(v2-v1);
		
		if (orientation < 0.0)		Color(gris_interne);
		else				Color(WHITE);
		Move_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
		Line_to(((REEL) noeud[sommet2].x - binx) / (baxx - binx),((REEL) noeud[sommet2].y - biny) / (baxy - biny));
		Line_to(((REEL) noeud[sommet3].x - binx) / (baxx - binx),((REEL) noeud[sommet3].y - biny) / (baxy - biny));
		Line_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
		Surface_end();
		
		}
	for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[no_pa].nb_tri_hexa_interieur;no_tri_hexa++)
		{ 
		sommet1 = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][1];
		sommet2 = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][2];
		sommet3 = pan_hexa[no_pa].tri_hexa_interieur[no_tri_hexa][3];
		u1 = noeud[sommet1].x;
		u2 = noeud[sommet2].x;
		u3 = noeud[sommet3].x;
		v1 = noeud[sommet1].y;
		v2 = noeud[sommet2].y;
		v3 = noeud[sommet3].y;
		/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du tri_hexa*/
		orientation = (u2-u1)*(v3-v1) - (u3-u1)*(v2-v1);
		
		if (orientation < 0.0)		Color(BLUE);
		else				Color(GREEN);
		Move_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
		Line_to(((REEL) noeud[sommet2].x - binx) / (baxx - binx),((REEL) noeud[sommet2].y - biny) / (baxy - biny));
		Line_to(((REEL) noeud[sommet3].x - binx) / (baxx - binx),((REEL) noeud[sommet3].y - biny) / (baxy - biny));
		Line_to(((REEL) noeud[sommet1].x - binx) / (baxx - binx),((REEL) noeud[sommet1].y - biny) / (baxy - biny));
		Surface_end();
		}
	}
	
void filet_contour_dessiner()
	{
	/*dessine les triangles poses sur le contour,  */
	int pa,col;
	
	lecture_des();
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur filet_contour_dessiner\n");
	SetColor(col);*/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_dessin != 0)
			{
			dessiner_filet_contour(pa);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		dessiner_filet_contour_hexa(pa);
		}
	}

void fils_contour_dessiner()
	{
	/*dessine les fils poses sur le contour,  */
	int col;

	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur fils_contour_dessiner\n");
	SetColor(col);*/
	dessiner_fils_contour();
	}

	
void UV_Vectors_dessiner()
	{
	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur UV_Vectors_dessiner\n");
	SetColor(col);*/
	int no_triangle,no_pa,no_tri_hexa,no,cote,deb,fin,deb_total,fin_total,z1,z2,z3;
	float x1,x2,y1,y2,x_barycentre,y_barycentre,vect_x,vect_y,vect_z,nx,ny,nz,mx,my,mz;
	float speed_ball,p1u,p2u,p3u,p0u,p1v,p2v,p3v,p0v,p1x,p2x,p3x,p0x,p1y,p2y,p3y,p0y,p1z,p2z,p3z,p0z;
	float surface,norme,alpha,beta,U2X,U2Y,U2Z,V2X,V2Y,V2Z,u1,u2,u3,v1,v2,v3,S,XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3;
	char str[80];
	
	lecture_des();
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	for (no_pa=1;no_pa<=Structure.NbTypesurf;no_pa++)
		{ 
		nx = 0.0;	ny = 0.0;	nz = 0.0;
		mx = 0.0;	my = 0.0;	mz = 0.0;
		for (no_triangle=1;no_triangle<=panneau[no_pa].nb_triangle_contour;no_triangle++)
			{ 
			deb = panneau[no_pa].triangle_contour[no_triangle][1];	z1 = panneau[no_pa].noeud_contour[deb];
			deb = panneau[no_pa].triangle_contour[no_triangle][2];	z2 = panneau[no_pa].noeud_contour[deb];
			deb = panneau[no_pa].triangle_contour[no_triangle][3];	z3 = panneau[no_pa].noeud_contour[deb];
			
			/*u1 =    noeud[z1].U / periode_fils + noeud[z1].V / periode_fils; 
			u2 =    noeud[z2].U / periode_fils + noeud[z2].V / periode_fils; 
			u3 =    noeud[z3].U / periode_fils + noeud[z3].V / periode_fils; 
			v1 =  - noeud[z1].U / periode_fils + noeud[z1].V / periode_fils; 
			v2 =  - noeud[z2].U / periode_fils + noeud[z2].V / periode_fils; 
			v3 =  - noeud[z3].U / periode_fils + noeud[z3].V / periode_fils;*/

			u1 =  noeud[z1].U / periode_fils; 	u2 =  noeud[z2].U / periode_fils; 	u3 =  noeud[z3].U / periode_fils; 
			v1 =  noeud[z1].V / periode_fils; 	v2 =  noeud[z2].V / periode_fils; 	v3 =  noeud[z3].V / periode_fils; 

			S = ((u2-u1)*(v3-v1) - (u3-u1)*(v2-v1));
			if( S == 0.0 ) 
				{
				printf("WARNING: the U V coordinates of contour triangle %d of panel %d are such that the surface in mesh is ZERO!\n", no_triangle,no_pa);
				/*exit(0);*/
				}
			else
				{			
				XX1 = noeud[z1].x;	XX2 = noeud[z2].x;	XX3 = noeud[z3].x;
				YY1 = noeud[z1].y;	YY2 = noeud[z2].y;	YY3 = noeud[z3].y;
				ZZ1 = noeud[z1].z;	ZZ2 = noeud[z2].z;	ZZ3 = noeud[z3].z;
				nx +=  ((v3-v1)*(XX2-XX1) - (v2-v1)*(XX3-XX1))/S;  	ny +=  ((v3-v1)*(YY2-YY1) - (v2-v1)*(YY3-YY1))/S;  	nz +=  ((v3-v1)*(ZZ2-ZZ1) - (v2-v1)*(ZZ3-ZZ1))/S;
				mx +=  ((u2-u1)*(XX3-XX1) - (u3-u1)*(XX2-XX1))/S;  	my +=  ((u2-u1)*(YY3-YY1) - (u3-u1)*(YY2-YY1))/S;  	mz +=  ((u2-u1)*(ZZ3-ZZ1) - (u3-u1)*(ZZ2-ZZ1))/S;
				}
			/*
			printf("panel %d trangle %d n %f %f %f m %f %f %f S %f\n",no_pa,no_triangle,nx,ny,nz,mx,my,mz,S); 
			printf("z1 %d z2 %d z3 %d\n",z1,z2,z3); 
			printf("U %f %f %f V %f %f %f\n",noeud[z1].U,noeud[z2].U,noeud[z3].U,noeud[z1].V,noeud[z2].V,noeud[z3].V); 
			printf("u %f %f %f v %f %f %f\n",u1,u2,u3,v1,v2,v3); 
			printf("XX %f %f %f YY %f %f %f ZZ %f %f %f\n",XX1,XX2,XX3,YY1,YY2,YY3,ZZ1,ZZ2,ZZ3);
			*/				
			}
		nx = nx / panneau[no_pa].nb_triangle_contour;
		ny = ny / panneau[no_pa].nb_triangle_contour;
		nz = nz / panneau[no_pa].nb_triangle_contour;
		mx = mx / panneau[no_pa].nb_triangle_contour;
		my = my / panneau[no_pa].nb_triangle_contour;
		mz = mz / panneau[no_pa].nb_triangle_contour;
			
		x_barycentre = 0.0;	y_barycentre = 0.0;
		for (no=1;no<=panneau[no_pa].nb_noeud_contour;no++)
			{ 
			deb = panneau[no_pa].noeud_contour[no];
			x_barycentre += noeud[deb].x;	y_barycentre += noeud[deb].y;
			}			
		x_barycentre = x_barycentre / panneau[no_pa].nb_noeud_contour;
		y_barycentre = y_barycentre / panneau[no_pa].nb_noeud_contour;
		
		x1 = ((REEL) x_barycentre - binx) / (baxx - binx);
		y1 = ((REEL) y_barycentre - biny) / (baxy - biny);
		x2 = ((REEL) x_barycentre + nx - binx) / (baxx - binx);
		y2 = ((REEL) y_barycentre + ny - biny) / (baxy - biny);
		Color(RED);
		Line(x1,y1,x2,y2);
		x2 = ((REEL) x_barycentre + mx - binx) / (baxx - binx);
		y2 = ((REEL) y_barycentre + my - biny) / (baxy - biny);
		Color(GREEN);
		Line(x1,y1,x2,y2);
		if (Structure.orientation == 1)
			{
			printf("input uniform_meshing3 %d 1     %f %f %f     %f %f %f\n",no_pa,nz / periode_fils,nx / periode_fils,ny / periode_fils,mz / periode_fils,mx / periode_fils,my / periode_fils);
			}
		if (Structure.orientation == 2)
			{
			printf("input uniform_meshing3 %d 1     %f %f %f     %f %f %f\n",no_pa,ny / periode_fils,nz / periode_fils,nx / periode_fils,my / periode_fils,mz / periode_fils,mx / periode_fils);
			}
		if (Structure.orientation == 3)
			{
			printf("input uniform_meshing3 %d 1     %f %f %f     %f %f %f\n",no_pa,nx / periode_fils,ny / periode_fils,nz / periode_fils,mx / periode_fils,my / periode_fils,mz / periode_fils);
			}
		}
		Color(BLACK);
		x1 = 0.0;	y1 = 0.0;
		sprintf(str,"RED U, GREEN V");
		Text(x1,y1,str);
	}
	
void axe_T90_dessiner()
	{
	/*dessine les axes T90 poses sur le contour,  */
	int col;

	/*col=GetRGBColor(255,0,0);
	if (col==-1) printf("Erreur de couleur fils_contour_dessiner\n");
	SetColor(col);*/
	dessiner_axe_T90();
	}

	
void dessiner_filet_contour_hexa(int no_pa)
	{
	int no_triangle,no_tri_hexa,cote,deb,fin,deb_total,fin_total;
	float x1,x2,y1,y2;
	
	lecture_des();
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a dessiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	Color(GREEN);

	for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[no_pa].nb_tri_hexa_contour;no_tri_hexa++)
		{ 
		for (cote=1;cote<=3;cote++)
			{ 
			/*numerotation locale des extremites des cotes du tri_hexa*/
			deb =                pan_hexa[no_pa].tri_hexa_contour[no_tri_hexa][cote  ];
			if (cote <  3) fin = pan_hexa[no_pa].tri_hexa_contour[no_tri_hexa][cote+1];
			if (cote == 3) fin = pan_hexa[no_pa].tri_hexa_contour[no_tri_hexa][1     ];
			/*numerotation totale des extremites des cotes du tri_hexa*/
			deb_total = pan_hexa[no_pa].noeud_contour[deb];
			fin_total = pan_hexa[no_pa].noeud_contour[fin];
			deb = deb_total;
			fin = fin_total;
			x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
			x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
			y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);
			}
		}
	}
	
void dessiner_filet_contour(int no_pa)
	{
	int no_triangle,no_tri_hexa,cote,deb,fin,deb_total,fin_total;
	float x1,x2,y1,y2;
	
	lecture_des();
	/*x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	Color(BLUE);

	for (no_triangle=1;no_triangle<=panneau[no_pa].nb_triangle_contour;no_triangle++)
		{ 
		for (cote=1;cote<=3;cote++)
			{ 
			/*numerotation locale des extremites des cotes du triangle*/
			deb =                panneau[no_pa].triangle_contour[no_triangle][cote  ];
			if (cote <  3) fin = panneau[no_pa].triangle_contour[no_triangle][cote+1];
			if (cote == 3) fin = panneau[no_pa].triangle_contour[no_triangle][1     ];
			/*numerotation totale des extremites des cotes du triangle*/
			deb_total = panneau[no_pa].noeud_contour[deb];
			fin_total = panneau[no_pa].noeud_contour[fin];
			deb = deb_total;
			fin = fin_total;
			x1 = ((REEL) noeud[deb].x - binx) / (baxx - binx);
			y1 = ((REEL) noeud[deb].y - biny) / (baxy - biny);
			x2 = ((REEL) noeud[fin].x - binx) / (baxx - binx);
			y2 = ((REEL) noeud[fin].y - biny) / (baxy - biny);
			Line(x1,y1,x2,y2);
			}
		}
	}
	
void dessiner_fils_contour()
	{
	int no_triangle,no_tri_hexa,cote,deb,fin,deb_total,fin_total,no_pa;
	int pre,sec,tro,um,vm,minu,maxu,minv,maxv,inside,inside1,inside2,int_temp;
	float x1,x2,x3,y1,y2,y3,xd,yd;
	float a1,a2,b1,b2,ru,rv;
	float u1,u2,u3,v1,v2,v3,xm,ym,alpha,beta,denom,vect_ux,vect_vx,vect_uy,vect_vy;
	int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
	void trace_fil_hexa(float a1, float b1, float a2, float b2, float x1, float y1, float x2, float y2, float x3, float y3);
	
	lecture_des();
	initialisation_nb_fils();
	fils_contour_calculer();
	
	/*
	x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?
	*/
	
	Color(BLUE);
	//gris_interne = ColorRGB(150,150,150);
	//Color(gris_interne);
	Color(ColorRGB(150,150,150));

	for (deb=1;deb<=Structure.nb_fils;deb++)
		{ 
		x1 = ((REEL) h1x[deb] - binx) / (baxx - binx);
		y1 = ((REEL) h1y[deb] - biny) / (baxy - biny);
		x2 = ((REEL) h2x[deb] - binx) / (baxx - binx);
		y2 = ((REEL) h2y[deb] - biny) / (baxy - biny);
		Line(x1,y1,x2,y2);
		}
	
	/*
	x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?
	*/
	
	Color(BLUE);

	for (no_pa=1;no_pa<=Structure.NbTypesurf_hexa;no_pa++)
		{ 
		/*printf("no_pa = %d  \n",no_pa);*/
	for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[no_pa].nb_tri_hexa_contour;no_tri_hexa++)
		{ 
		
		int_temp = pan_hexa[no_pa].tri_hexa_contour[no_tri_hexa][1];	pre = pan_hexa[no_pa].noeud_contour[int_temp];
		int_temp = pan_hexa[no_pa].tri_hexa_contour[no_tri_hexa][2];	sec = pan_hexa[no_pa].noeud_contour[int_temp];
		int_temp = pan_hexa[no_pa].tri_hexa_contour[no_tri_hexa][3];	tro = pan_hexa[no_pa].noeud_contour[int_temp];
		
		/*printf("pre= %d, sec = %d, tro = %d  ",pre,sec,tro);*/
		
		u1 = (float) noeud[pre].U / periode_fils;	v1 = (float) noeud[pre].V / periode_fils;
		u2 = (float) noeud[sec].U / periode_fils;	v2 = (float) noeud[sec].V / periode_fils;
		u3 = (float) noeud[tro].U / periode_fils;	v3 = (float) noeud[tro].V / periode_fils;
		x1 = noeud[pre].x;	y1 = noeud[pre].y;
		x2 = noeud[sec].x;	y2 = noeud[sec].y;
		x3 = noeud[tro].x;	y3 = noeud[tro].y;
		
		/*
		printf("u1= %f,v1 = %f  ",u1,v1);
		printf("u2= %f,v2 = %f  ",u2,v2);
		printf("u3= %f,v3 = %f\n",u3,v3);
		
		printf("x1= %f,y1 = %f  ",x1,y1);
		printf("x2= %f,y2 = %f  ",x2,y2);
		printf("x3= %f,y3 = %f\n",x3,y3);
		*/
		
		
	       	denom = (u3-u1)*(v2-v1) - (u2-u1)*(v3-v1);
		/*
	        printf(" * noeud_panneau * denom = %f\n",denom); 
		*/
	       	/* precautions en cas de denominateur nul*/
	       	if (fabs(denom) <= 0.00001)
	               	{  
	               	} 
	       	/*calcul des vecteur elementaires cartesiens de cote de maille vect_u et vect_v*/
	       	
	       	ru = u1+1.0;
	       	rv = v1+0.0;
	       	
		/*
		printf("ru= %f,rv = %f\n",ru,rv);
		*/
		
	     	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
	     	beta  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;
	     	
		/*
	        printf("alpha= %f, beta= %f\n",alpha,beta);
		*/
	       	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
	       	vect_ux = alpha * ( x2 - x1 )+ beta * ( x3 - x1 );
	       	vect_uy = alpha * ( y2 - y1 )+ beta * ( y3 - y1 );

	       	ru = u1+0.0;
	       	rv = v1+1.0;
	       	
	     	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
	     	beta  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;
	     	
		/*
	        printf("alpha= %f, beta= %f\n",alpha,beta);
		*/
	       	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
	       	vect_vx = alpha * ( x2 - x1 )+ beta * ( x3 - x1 );
	       	vect_vy = alpha * ( y2 - y1 )+ beta * ( y3 - y1 );

	       	
		/*
	        printf("vect_ux= %f, vect_uy= %f\n",vect_ux,vect_uy);
	        printf("vect_vx= %f, vect_vy= %f\n",vect_vx,vect_vy);
		*/
	        
		minu = (int) floor(u1);		maxu = (int) ceil(u1);
		minv = (int) floor(v1);		maxv = (int) ceil(v1);
		if (minu>u2) minu = (int) floor(u2);  if (maxu<u2) maxu = (int) ceil(u2);
		if (minu>u3) minu = (int) floor(u3);  if (maxu<u3) maxu = (int) ceil(u3);
		if (minv>v2) minv = (int) floor(v2);  if (maxv<v2) maxv = (int) ceil(v2);
		if (minv>v3) minv = (int) floor(v3);  if (maxv<v3) maxv = (int) ceil(v3);
		
		/*
		printf("minu   : %8d ,maxu  :  %8d \n",minu,maxu);
		printf("minv   : %8d ,maxv  :  %8d \n",minv,maxv);
		*/
			
		for (um=minu;um<=maxu;um++)
			{ 
			for (vm=minv;vm<=maxv;vm++)
				{
				/*printf("um   : %8d ,vm  :  %8d ",um,vm);*/
	       			/* determination des coefficients alpha et beta definis tels que 1m = alpha*12 + beta*13 */
	     			alpha =   ( (vm-v1)*(u3-u1) - (um-u1)*(v3-v1) ) / denom;
	     			beta  =   ( (um-u1)*(v2-v1) - (vm-v1)*(u2-u1) ) / denom;
	         		/*printf("alpha= %f,beta = %f ",alpha,beta);*/
	       		       
	       			/* determination des coordonnees cartesiennes de l origine de la maille proche d une position d equilibre */
	       			xm = alpha * ( x2 - x1 )+ beta * ( x3 - x1 ) + x1;
	       			ym = alpha * ( y2 - y1 )+ beta * ( y3 - y1 ) + y1;
	         		/*printf("xm= %f,ym = %f\n",xm,ym);*/
	         		
	         		/*trace des 6 fils a l interieur d une maille*/
				/*
				Line(((REEL) xm-0.08-binx) / (baxx-binx),((REEL) ym-biny) / (baxy-biny),((REEL) xm+0.08-binx) / (baxx-binx),((REEL) ym-biny) / (baxy-biny));
				Line(((REEL) xm-binx) / (baxx-binx),((REEL) ym-0.08-biny) / (baxy-biny),((REEL) xm-binx) / (baxx-binx),((REEL) ym+0.08-biny) / (baxy-biny));
	         		*/
	         		
				/*
				*/
				a1 = xm;
				b1 = ym;
				a2 = xm +vect_ux;
				b2 = ym +vect_uy;
				/*
	         		printf("a1= %f,b1 = %f\n",a1,b1);
	         		printf("a2= %f,b2 = %f\n",a2,b2);
	         		printf("x1= %f,y1 = %f\n",x1,y1);
	         		printf("x2= %f,y2 = %f\n",x2,y2);
	         		printf("x3= %f,y3 = %f\n",x3,y3);
				trace_fil_hexa( a1,  b1,  a2,  b2,  x1,  y1,  x2,  y2,  x3,  y3);
				
				
				a2 = xm +vect_vx;
				b2 = ym +vect_vy;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x1,  y1,  x2,  y2,  x3,  y3);
				*/
				
				a1 = xm +vect_ux*1.0/6.0 +vect_vx*1.0/2.0;
				b1 = ym +vect_uy*1.0/6.0 +vect_vy*1.0/2.0;
				a2 = xm +vect_ux*0.0/6.0 +vect_vx*0.0/2.0;
				b2 = ym +vect_uy*0.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x1,  y1,  x2,  y2,  x3,  y3);
				a2 = xm +vect_ux*0.0/6.0 +vect_vx*2.0/2.0;
				b2 = ym +vect_uy*0.0/6.0 +vect_vy*2.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x1,  y1,  x2,  y2,  x3,  y3);
				a2 = xm +vect_ux*3.0/6.0 +vect_vx*1.0/2.0;
				b2 = ym +vect_uy*3.0/6.0 +vect_vy*1.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x1,  y1,  x2,  y2,  x3,  y3);
				a1 = xm +vect_ux*4.0/6.0 +vect_vx*2.0/2.0;
				b1 = ym +vect_uy*4.0/6.0 +vect_vy*2.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x1,  y1,  x2,  y2,  x3,  y3);
				a1 = xm +vect_ux*4.0/6.0 +vect_vx*0.0/2.0;
				b1 = ym +vect_uy*4.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x1,  y1,  x2,  y2,  x3,  y3);
				a2 = xm +vect_ux*6.0/6.0 +vect_vx*0.0/2.0;
				b2 = ym +vect_uy*6.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x1,  y1,  x2,  y2,  x3,  y3);
				/*
				*/
				}
			}
		}
		}
	}
	
void dessiner_UV_Vectors()
	{
	int no_triangle,no_tri_hexa,cote,deb,fin,deb_total,fin_total,no_pa;
	int pre,sec,tro,um,vm,minu,maxu,minv,maxv,inside,inside1,inside2,int_temp;
	float x1,x2,x3,y1,y2,y3,xd,yd;
	float a1,a2,b1,b2,ru,rv;
	float u1,u2,u3,v1,v2,v3,xm,ym,alpha,beta,denom,vect_ux,vect_vx,vect_uy,vect_vy;
	int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
	void trace_fil_hexa(float a1, float b1, float a2, float b2, float x1, float y1, float x2, float y2, float x3, float y3);
	
	lecture_des();
	initialisation_nb_fils();
	fils_contour_calculer();
	
	/*
	x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?
	*/
	
	Color(BLUE);

	for (deb=1;deb<=Structure.nb_fils;deb++)
		{ 
		x1 = ((REEL) h1x[deb] - binx) / (baxx - binx);
		y1 = ((REEL) h1y[deb] - biny) / (baxy - biny);
		x2 = ((REEL) h2x[deb] - binx) / (baxx - binx);
		y2 = ((REEL) h2y[deb] - biny) / (baxy - biny);
		Line(x1,y1,x2,y2);
		}
	}
	
void dessiner_axe_T90()
	{
	int no_triangle,no_tri_hexa,cote,deb,fin,deb_total,fin_total,no_pa;
	int pre,sec,tro,um,vm,minu,maxu,minv,maxv,inside,inside1,inside2,int_temp;
	float x1,x2,x3,y1,y2,y3,xd,yd;
	float a1,a2,b1,b2,ru,rv;
	float u1,u2,u3,v1,v2,v3,xm,ym,alpha,beta,denom,vect_ux,vect_vx,vect_uy,vect_vy;
	int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
	void trace_fil_hexa(float a1, float b1, float a2, float b2, float x1, float y1, float x2, float y2, float x3, float y3);
	
	lecture_des();
	/*
	x1,x2,y1,y2 sont les coordonnees des extremites de segment a desssiner.
	x1,x2,y1,y2 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?
	*/
	
	Color(GREEN);

	for (deb=1;deb<=Structure.T90_nb_fils;deb++)
		{ 
		x1 = ((REEL) g1x[deb] - binx) / (baxx - binx);
		y1 = ((REEL) g1y[deb] - biny) / (baxy - biny);
		x2 = ((REEL) g2x[deb] - binx) / (baxx - binx);
		y2 = ((REEL) g2y[deb] - biny) / (baxy - biny);
		Line(x1,y1,x2,y2);
		}
	}
	
void trace_fil_hexa(float a1, float b1, float a2, float b2, float x1, float y1, float x2, float y2, float x3, float y3)
	{
	/*a1,b1 a a2,b2 est le fil a trace dans le triangle de sommets x1,y1 x2,y2 x3,y3*/
	int inside1,inside2,secant;
	double xx,yy;
	int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
	int segment_secant(double a1, double b1, double a2, double b2, double x1, double y1, double x2, double y2);
	void intersection_segment(double a1, double b1, double a2, double b2, double x1, double y1, double x2, double y2, double *x,double *y);
	
	inside1 = appartient_triangle4((double) a1, (double) b1, (double) x1, (double) y1, (double) x2, (double) y2, (double) x3, (double) y3);
	inside2 = appartient_triangle4((double) a2, (double) b2, (double) x1, (double) y1, (double) x2, (double) y2, (double) x3, (double) y3);
	if ((inside1 == 1) && (inside2 == 1))
		{
		/*ici les 2 extremites a1,b1 et a2,b2 du fil sont dans le triangle 1 2 3, on peut le trace*/
		Line(((REEL) a1-binx) / (baxx-binx),((REEL) b1-biny) / (baxy-biny),((REEL) a2-binx) / (baxx-binx),((REEL) b2-biny) / (baxy-biny));
		}
	/*ici l extremite a1,b1 est dans le triangle 1 2 3 et a2,b2 est a l exterieur*/
	if ((inside1 == 1) && (inside2 != 1))
		{
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x1, (double) y1, (double) x2, (double) y2);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x1, (double) y1, (double) x2, (double) y2, &xx, &yy);
			Line(((REEL) a1-binx) / (baxx-binx),((REEL) b1-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
			}
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x2, (double) y2, (double) x3, (double) y3);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x2, (double) y2, (double) x3, (double) y3, &xx, &yy);
			Line(((REEL) a1-binx) / (baxx-binx),((REEL) b1-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
			}
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x3, (double) y3, (double) x1, (double) y1);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x3, (double) y3, (double) x1, (double) y1, &xx, &yy);
			Line(((REEL) a1-binx) / (baxx-binx),((REEL) b1-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
			}
		}
	if ((inside1 != 1) && (inside2 == 1))
		{
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x1, (double) y1, (double) x2, (double) y2);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x1, (double) y1, (double) x2, (double) y2, &xx, &yy);
			Line(((REEL) a2-binx) / (baxx-binx),((REEL) b2-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
			}
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x2, (double) y2, (double) x3, (double) y3);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x2, (double) y2, (double) x3, (double) y3, &xx, &yy);
			Line(((REEL) a2-binx) / (baxx-binx),((REEL) b2-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
			}
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x3, (double) y3, (double) x1, (double) y1);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x3, (double) y3, (double) x1, (double) y1, &xx, &yy);
			Line(((REEL) a2-binx) / (baxx-binx),((REEL) b2-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
			}
		}
	}
	
void dessiner_numerotation_triangle_contour()
	{
	int pa,col,deb,deb_total,no_triangle,no_tri_hexa,cote;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,255,255);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_triangle_contour\n");
	SetColor(col);*/
	
	Color(BLACK);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		for (no_triangle=1;no_triangle<=panneau[pa].nb_triangle_contour;no_triangle++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%d",no_triangle);
			for (cote=1;cote<=3;cote++)
				{ 
				deb = panneau[pa].triangle_contour[no_triangle][cote  ];
				deb_total = panneau[pa].noeud_contour[deb];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			/* printf(" xo  : %8d , yo :  %8d \n",xo,yo);  */
			Text(x1,y1,str);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[pa].nb_tri_hexa_contour;no_tri_hexa++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%d",no_tri_hexa);
			for (cote=1;cote<=3;cote++)
				{ 
				deb = pan_hexa[pa].tri_hexa_contour[no_tri_hexa][cote  ];
				deb_total = pan_hexa[pa].noeud_contour[deb];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			/* printf(" xo  : %8d , yo :  %8d \n",xo,yo);  */
			Text(x1,y1,str);
			}
		}
	}

void dessiner_numerotation_triangle_interieur()
	{
	int pa,col,deb_total,no_triangle,no_tri_hexa,cote;
	float x1,y1;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,255,255);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_triangle_interieur\n");
	SetColor(col);*/
	
	Color(BLUE);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		for (no_triangle=1;no_triangle<=panneau[pa].nb_triangle_interieur;no_triangle++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%d",no_triangle);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = panneau[pa].triangle_interieur[no_triangle][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			/* printf(" xo  : %8d , yo :  %8d \n",xo,yo);  */
			Text(x1,y1,str);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[pa].nb_tri_hexa_interieur;no_tri_hexa++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%d",no_tri_hexa);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = pan_hexa[pa].tri_hexa_interieur[no_tri_hexa][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			/* printf(" xo  : %8d , yo :  %8d \n",xo,yo);  */
			Text(x1,y1,str);
			}
		}
	}


/*************************************************************************************************************/
void dessiner_tension()
	{	
	int i,pa,col,deb_total,no_triangle,no_tri_hexa,cote,no,deb,fin;
	float x1,y1,x2,y2,x3,y3;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(1,254,254);
	if (col==-1) printf("Erreur de couleur dessiner_tension\n");
	SetColor(col);*/
	
	Color(RED);
	x3 = (float) (0.0);
	y3 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x3,y3,"tension (N)");

	Color(BLUE);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
	for (no_triangle=1;no_triangle<=panneau[pa].nb_triangle_interieur;no_triangle++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surface[panneau[pa].numero_triangle[no_triangle]].tension1);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = panneau[pa].triangle_interieur[no_triangle][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			Text(x1,y1,str);

			
			x2 = 0.0;
			y2 = 0.0;
			sprintf(str,"%lf",surface[panneau[pa].numero_triangle[no_triangle]].tension2);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = panneau[pa].triangle_interieur[no_triangle][cote  ];
				x2 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y2 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x2 = (float) (x2 / 3.0);
			y2 = (float) (y2 / 3.0 - 1.0 * 0.02);
			Text(x2,y2,str);
			}
		}
		
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[pa].nb_tri_hexa_interieur;no_tri_hexa++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surf_hexa[no_tri_hexa].tension1);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = pan_hexa[pa].tri_hexa_interieur[no_tri_hexa][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			Text(x1,y1+0.00,str);
			
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surf_hexa[no_tri_hexa].tension2);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = pan_hexa[pa].tri_hexa_interieur[no_tri_hexa][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0 - 1.0 * 0.02);
			Text(x1,y1+0.02,str);
			
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surf_hexa[no_tri_hexa].tension3);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = pan_hexa[pa].tri_hexa_interieur[no_tri_hexa][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0 - 2.0 * 0.02);
			Text(x1,y1+0.04,str);
			
			}
		}


	Color(RED);
			
	for (pa=1;pa<=Structure.nb_barre;pa++)
		{ 
		sprintf(str,"%lf",barre[pa].tension);
		deb = barre[pa].noeud[1];
		fin = barre[pa].noeud[2];
		x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
		x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
		y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
		x1 = (float) (x1 / 2.0);
		y1 = (float) (y1 / 2.0);
		Text(x1,y1,str);
		}
		
		
		
	Color(BLUE);
	

	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		sprintf(str,"%lf",coulisse[pa].wt);		
		deb = coulisse[pa].extremite[1];
		fin = coulisse[pa].extremite[2];
		x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
		x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
		y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
		x1 = (float) (x1 / 2.0);
		y1 = (float) (y1 / 2.0);
		Text(x1,y1,str);
		}
		
		
		
	}

	
/*******************************************************************************************************************************************************************************************************/
void dessiner_longueur_tendue()
	{
	int i,pa,col,deb_total,no_triangle,no_tri_hexa,cote,no,deb,fin;
	float x1,y1,x2,y2,x3,y3;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,255,255);
	if (col==-1) printf("Erreur de couleur dessiner_longueur_tendue\n");
	SetColor(col);*/	
	
	Color(RED);
	x3 = (float) (0.0);
	y3 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x3,y3,"longueur_tendue (m)");

	
	Color(BLUE);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
	for (no_triangle=1;no_triangle<=panneau[pa].nb_triangle_interieur;no_triangle++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surface[panneau[pa].numero_triangle[no_triangle]].lg_tendue1);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = panneau[pa].triangle_interieur[no_triangle][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0 + 1.0 * 0.02);
			Text(x1,y1,str);

			
			x2 = 0.0;
			y2 = 0.0;
			sprintf(str,"%lf",surface[panneau[pa].numero_triangle[no_triangle]].lg_tendue2);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = panneau[pa].triangle_interieur[no_triangle][cote  ];
				x2 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y2 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x2 = (float) (x2 / 3.0);
			y2 = (float) (y2 / 3.0);
			Text(x2,y2,str);
			}
		}
		
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[pa].nb_tri_hexa_interieur;no_tri_hexa++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surf_hexa[no_tri_hexa].lg_tendue1);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = pan_hexa[pa].tri_hexa_interieur[no_tri_hexa][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			Text(x1,y1+0.00,str);
			
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surf_hexa[no_tri_hexa].lg_tendue2);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = pan_hexa[pa].tri_hexa_interieur[no_tri_hexa][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			Text(x1,y1+0.02,str);
			
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surf_hexa[no_tri_hexa].lg_tendue3);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = pan_hexa[pa].tri_hexa_interieur[no_tri_hexa][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			Text(x1,y1+0.04,str);
			
			}
		}

		
	Color(RED);
			
	for (pa=1;pa<=Structure.nb_barre;pa++)
		{ 
		sprintf(str,"%lf",barre[pa].longueur_tendue);
		deb = barre[pa].noeud[1];
		fin = barre[pa].noeud[2];
		x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
		x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
		y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
		x1 = (float) (x1 / 2.0);
		y1 = (float) (y1 / 2.0);
		Text(x1,y1,str);
		}
		
        Color(BLUE);
        
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{
		sprintf(str,"%lf",coulisse[pa].lgtendue);
		deb = coulisse[pa].extremite[1];
		fin = coulisse[pa].extremite[2];
		x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
		x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
		y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
		x1 = (float) (x1 / 2.0);
		y1 = (float) (y1 / 2.0);
		Text(x1,y1,str);
		}

	


		
       
	}
/****************************************************************************************************************/
void dessiner_numerotation_globale()
	{
	int i,pa,col,deb_total,no_triangle,no_tri_hexa,cote;
	float x1,y1,x3,y3;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,255,255);
	if (col==-1) printf("Erreur de couleur dessiner_numerotation_globale\n");
	SetColor(col);*/
	
	Color(RED);
	x3 = (float) (0.0);
	y3 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x3,y3,"numerotation_globale");

	Color(BLUE);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		for (no_triangle=1;no_triangle<=panneau[pa].nb_triangle_interieur;no_triangle++)
			{ 
			x1 = 0.0;
			y1 = 0.0;                                    
			sprintf(str,"%d",panneau[pa].numero_triangle[no_triangle]);       
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = panneau[pa].triangle_interieur[no_triangle][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			/* printf(" xo  : %8d , yo :  %8d \n",xo,yo);  */
			Text(x1,y1,str);
			}
		}
			
	}
/****************************************************************************************************************/
void dessiner_nrj()
	{
	int i,pa,col,deb_total,no_triangle,no_tri_hexa,cote,no,deb,fin;
	float x1,y1,x3,y3;
	char str[80];
	
	lecture_des();
	/*col=GetRGBColor(0,255,255);
	if (col==-1) printf("Erreur de couleur dessiner_nrj\n");
	SetColor(col);*/
	
	Color(RED);
	x3 = (float) (0.0);
	y3 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
	Text(x3,y3,"energie potentielle (J) par cable ou fils elementaires");

	Color(BLUE);
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		for (no_triangle=1;no_triangle<=panneau[pa].nb_triangle_interieur;no_triangle++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surface[panneau[pa].numero_triangle[no_triangle]].nrj);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = panneau[pa].triangle_interieur[no_triangle][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			Text(x1,y1,str);
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		for (no_tri_hexa=1;no_tri_hexa<=pan_hexa[pa].nb_tri_hexa_interieur;no_tri_hexa++)
			{ 
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%lf",surf_hexa[no_tri_hexa].nrj);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = pan_hexa[pa].tri_hexa_interieur[no_tri_hexa][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			Text(x1,y1+0.00,str);
			}
		}

	Color(RED);
			
	for (pa=1;pa<=Structure.nb_barre;pa++)
		{ 
		sprintf(str,"%lf",barre[pa].nrj);
		deb = barre[pa].noeud[1];
		fin = barre[pa].noeud[2];
		x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
		x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
		y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
		x1 = (float) (x1 / 2.0);
		y1 = (float) (y1 / 2.0);
		Text(x1,y1,str);
		}
		
	Color(BLUE);	
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		sprintf(str,"%lf",coulisse[pa].nrj);
		deb = coulisse[pa].extremite[1];
		fin = coulisse[pa].extremite[2];
		x1  = (float) (noeud[deb].x - binx) / (baxx - binx);
		y1  = (float) (noeud[deb].y - biny) / (baxy - biny);
		x1 += (float) (noeud[fin].x - binx) / (baxx - binx);
		y1 += (float) (noeud[fin].y - biny) / (baxy - biny);
		x1 = (float) (x1 / 2.0);
		y1 = (float) (y1 / 2.0);
		Text(x1,y1,str);
		}

	

			
	}
/****************************************************************************************************************/
void dessiner_defaut_discretisation()
	{
	int i,pa,col,deb_total,no_triangle,no_tri_hexa,cote,no,deb,fin,panneau_min;
	int sommet1,sommet2,sommet3,icolor,rapport_blue,rapport_red;
	float x1,y1,x3,y3,defaut_max,defaut_min;
	float xx1,xx2,xx3,yy1,yy2,yy3;
	char str[80];
	
	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();

	lecture_des();
	/*col=GetRGBColor(0,255,255);
	if (col==-1) printf("Erreur de couleur dessiner_defaut_discretisation\n");
	SetColor(col);*/
	
	panneau_min = 1;
	defaut_max = -1.0;
	defaut_min =  1.0;
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		for (no_triangle=1;no_triangle<=panneau[pa].nb_triangle_interieur;no_triangle++)
			{
			if (surface[panneau[pa].numero_triangle[no_triangle]].defaut_disc > defaut_max) 
				{
				defaut_max = surface[panneau[pa].numero_triangle[no_triangle]].defaut_disc;
				}
			if (surface[panneau[pa].numero_triangle[no_triangle]].defaut_disc < defaut_min) 
				{
				defaut_min = surface[panneau[pa].numero_triangle[no_triangle]].defaut_disc;
				panneau_min = pa;
				}
			}
		}
	/*printf("defaut_min = %f defaut_max = %f\n", defaut_min, defaut_max);*/

	Color(RED);
	x3 = (float) (0.0);
	y3 = (float) (0.0 + 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/
    	sprintf(str,"defaut de discretisation max = %5.2lf dans panneau %5d",defaut_min,panneau_min);
	Text(x3,y3,str);

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		for (no_triangle=1;no_triangle<=panneau[pa].nb_triangle_interieur;no_triangle++)
			{
			sommet1 = panneau[pa].triangle_interieur[no_triangle][1];
			sommet2 = panneau[pa].triangle_interieur[no_triangle][2];
			sommet3 = panneau[pa].triangle_interieur[no_triangle][3];
			xx1 = (float) (noeud[sommet1].x - binx) / (baxx - binx);
			xx2 = (float) (noeud[sommet2].x - binx) / (baxx - binx);
			xx3 = (float) (noeud[sommet3].x - binx) / (baxx - binx);
			yy1 = (float) (noeud[sommet1].y - biny) / (baxy - biny);
			yy2 = (float) (noeud[sommet2].y - biny) / (baxy - biny);
			yy3 = (float) (noeud[sommet3].y - biny) / (baxy - biny);
			if (defaut_max != defaut_min)
				{
				rapport_blue = (int) 255.0 * (surface[panneau[pa].numero_triangle[no_triangle]].defaut_disc-defaut_min) / (defaut_max-defaut_min);
				}
			else
				{
				rapport_blue = 124;
				}
			rapport_red = 255 - rapport_blue;
			/*col=GetRGBColor(rapport_red,0,rapport_blue);
			if (col==-1) printf("Erreur de couleur dessiner_defaut_discretisation\n");
			SetColor(col);
			Move_to((float)xx1,(float)yy1);
			Line_to((float)xx2,(float)yy2);
			Line_to((float)xx3,(float)yy3);
			Line_to((float)xx1,(float)yy1);
			Surface_end();*/
			x1 = 0.0;
			y1 = 0.0;
			sprintf(str,"%9.6lf",surface[panneau[pa].numero_triangle[no_triangle]].defaut_disc);
			for (cote=1;cote<=3;cote++)
				{ 
				deb_total = panneau[pa].triangle_interieur[no_triangle][cote  ];
				x1 += (float) (noeud[deb_total].x - binx) / (baxx - binx);
				y1 += (float) (noeud[deb_total].y - biny) / (baxy - biny);
				}
			x1 = (float) (x1 / 3.0);
			y1 = (float) (y1 / 3.0);
			Text(x1,y1,str);
			}
		}
	}
	



/****************************************************************************************************************/
void draw_segment_color(int color, double x1m, double y1m, double x2m, double y2m)
	{
	if (color == 1) TraceSegment( BLACK, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 2) TraceSegment(  BLUE, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 3) TraceSegment(   RED, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 4) TraceSegment( GREEN, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 5) TraceSegment(YELLOW, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 6) TraceSegment( WHITE, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
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
	
	Color(icolor);
	Move_to((float)xx1,(float)yy1);
	Line_to((float)xx2,(float)yy2);
	Line_end();
	}
	

