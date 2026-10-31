#include "batz.h"

/*lecture du fichier de resultat statique si il existe*/

int lecturesta(char *nomfichier)
	{
  	char tonom[100],c;
  	int tmp,tmp2,elem,pa;
  	double elongation,l,m,n,temp1,temp2,temp3,norm_temp;


  	strcpy(tonom,nomfichier);

  	strcat(tonom,".sta");
  	f1 = fopen(tonom,"r");
  	if (f1 == NULL) 
  		{
    		printf(" \n");
    		printf("%s %s %s \n","fichier ",tonom," n existe pas ");
    		fclose(f1);
    		return 0;
  		} 
  	else
  		{
    		printf(" \n");
    		printf("%s %s %s \n","fichier ",tonom," existe ");
  
    		/* lecture des nouvelles coordonnees des noeuds du maillage. */
    		for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    			{
      			fscanf(f1,"%d %lf %lf %lf",&tmp,&Noeud[elem].inix,&Noeud[elem].iniy,&Noeud[elem].iniz);
 			/*printf("elem %3d Noeud[elem].x %lf Noeud[elem].y %lf Noeud[elem].z %lf\n",elem,Noeud[elem].inix,Noeud[elem].iniy,Noeud[elem].iniz);*/
    			}
    		/* Lecture de la longueur tendue des bouts */
    		for (elem=1;elem<=NOMBRE_ELEMENTS;elem++)
    			{ 
      			fscanf(f1,"%lf",&elongation);
      			Element[elem].lgtendue = (elongation * Element[elem].lgrepos) +  Element[elem].lgrepos ;
      			if (elongation >= 0.0) Element[elem].wt = elongation * Element[elem].raideur_traction;
      			if (elongation <  0.0) Element[elem].wt = elongation * Element[elem].raideur_compression;
    			Element[elem].nrj= Element[elem].wt * (Element[elem].lgtendue - Element[elem].lgrepos)/2.0;
    			}
		/*printf("elem 3 longueur: %lf \n",Element[3].lgrepos);*/
   
    		/* Lecture de la longueur tendue des coulisses */
    		for (elem=1;elem<=NOMBRE_COULISSES;elem++)
    			{ 
      			fscanf(f1,"%lf",&elongation);
      			Coulisse[elem].lgtendue = (elongation * Coulisse[elem].lgrepos) +  Coulisse[elem].lgrepos ;
      			if (elongation >= 0.0) Coulisse[elem].wt = elongation * Coulisse[elem].raideur_traction;
      			if (elongation <  0.0) Coulisse[elem].wt = elongation * Coulisse[elem].raideur_compression;
    			Coulisse[elem].nrj= Coulisse[elem].wt * (Coulisse[elem].lgtendue - Coulisse[elem].lgrepos)/2.0;
    			}
    
  		/*lecture de la longueur des mailles selon u et v dans chaque triangle a l equilibre statique */
  		for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
  			{
      			fscanf(f1,"%lf",&Surface[elem].mx);
      			fscanf(f1,"%lf",&Surface[elem].my);
      			fscanf(f1,"%lf",&Surface[elem].mz);
      			fscanf(f1,"%lf",&Surface[elem].nx);
      			fscanf(f1,"%lf",&Surface[elem].ny);
      			fscanf(f1,"%lf",&Surface[elem].nz);
      			n = sqrt(Surface[elem].nx*Surface[elem].nx + Surface[elem].ny*Surface[elem].ny + Surface[elem].nz*Surface[elem].nz);
      			m = sqrt(Surface[elem].mx*Surface[elem].mx + Surface[elem].my*Surface[elem].my + Surface[elem].mz*Surface[elem].mz);
       		elongation = (n - Surface[elem].lgrepos) / Surface[elem].lgrepos;
      			if (elongation >= 0.0) Surface[elem].tension1 = elongation * Surface[elem].raideur_traction;
      			if (elongation <  0.0) Surface[elem].tension1 = elongation * Surface[elem].raideur_compression;
     			elongation = (m - Surface[elem].lgrepos) / Surface[elem].lgrepos;
      			if (elongation >= 0.0) Surface[elem].tension2 = elongation * Surface[elem].raideur_traction;
      			if (elongation <  0.0) Surface[elem].tension2 = elongation * Surface[elem].raideur_compression;
    			Surface[elem].nrj1= Surface[elem].tension1 * (n - Surface[elem].lgrepos)/2.0;
    			Surface[elem].nrj2= Surface[elem].tension2 * (m - Surface[elem].lgrepos)/2.0;
  			/*if (elem == 1)
				{
				printf("elem = %d  \n",elem);
				printf("m  = %19.15lf %19.15lf %19.15lf \n",Surface[elem].mx,Surface[elem].my,Surface[elem].mz);
				printf("n  = %19.15lf %19.15lf %19.15lf \n",Surface[elem].nx,Surface[elem].ny,Surface[elem].nz);
				printf("lgr  = %lf m  = %lf n  = %lf \n",Surface[elem].lgrepos,m,n);
				printf("t1  = %lf t2  = %lf \n",Surface[elem].tension1,Surface[elem].tension2);
				}*/
  			Surface[elem].nrj = Surface[elem].nrj1 + Surface[elem].nrj2;
    			temp1 = Surface[elem].ny*Surface[elem].mz - Surface[elem].nz*Surface[elem].my;
    			temp2 = Surface[elem].nz*Surface[elem].mx - Surface[elem].nx*Surface[elem].mz;
    			temp3 = Surface[elem].nx*Surface[elem].my - Surface[elem].ny*Surface[elem].mx;
    			norm_temp = sqrt(temp1*temp1 + temp2*temp2 + temp3*temp3);
			/*printf("elem = %d, temp1  = %f %f %f\n",elem,temp1,temp2,temp3);
			if (elem == 706) exit(0);*/
			if (norm_temp != 0.0)
				{
    				Surface[elem].Nx = temp1 / norm_temp;
    				Surface[elem].Ny = temp2 / norm_temp;
    				Surface[elem].Nz = temp3 / norm_temp;
				}
			else
				{
    				Surface[elem].Nx = 1.0;
    				Surface[elem].Ny = 0.0;
    				Surface[elem].Nz = 0.0;
				}
  			}
  		/*lecture des longueurs l, m et n des fils des mailles hexagonales dans chaque triangle a l equilibre statique */
  		for (elem = 1 ; elem<= NOMBRE_SURF_HEXA ; elem++) 
  			{
      			fscanf(f1,"%lf",&Surf_Hexa[elem].lx);
      			fscanf(f1,"%lf",&Surf_Hexa[elem].ly);
      			fscanf(f1,"%lf",&Surf_Hexa[elem].lz);
      			fscanf(f1,"%lf",&Surf_Hexa[elem].mx);
      			fscanf(f1,"%lf",&Surf_Hexa[elem].my);
      			fscanf(f1,"%lf",&Surf_Hexa[elem].mz);
      			fscanf(f1,"%lf",&Surf_Hexa[elem].nx);
      			fscanf(f1,"%lf",&Surf_Hexa[elem].ny);
      			fscanf(f1,"%lf",&Surf_Hexa[elem].nz);
      			l = sqrt(Surf_Hexa[elem].lx*Surf_Hexa[elem].lx + Surf_Hexa[elem].ly*Surf_Hexa[elem].ly + Surf_Hexa[elem].lz*Surf_Hexa[elem].lz);
      			m = sqrt(Surf_Hexa[elem].mx*Surf_Hexa[elem].mx + Surf_Hexa[elem].my*Surf_Hexa[elem].my + Surf_Hexa[elem].mz*Surf_Hexa[elem].mz);
      			n = sqrt(Surf_Hexa[elem].nx*Surf_Hexa[elem].nx + Surf_Hexa[elem].ny*Surf_Hexa[elem].ny + Surf_Hexa[elem].nz*Surf_Hexa[elem].nz);
      			elongation = (l - Surf_Hexa[elem].lo_repos) / Surf_Hexa[elem].lo_repos;
      			if (elongation >= 0.0) Surf_Hexa[elem].tension1 = elongation * Surf_Hexa[elem].raideur_traction_l;
      			if (elongation <  0.0) Surf_Hexa[elem].tension1 = elongation * Surf_Hexa[elem].raideur_compression_l;
      			elongation = (m - Surf_Hexa[elem].mo_repos) / Surf_Hexa[elem].mo_repos;
      			if (elongation >= 0.0) Surf_Hexa[elem].tension2 = elongation * Surf_Hexa[elem].raideur_traction_m;
      			if (elongation <  0.0) Surf_Hexa[elem].tension2 = elongation * Surf_Hexa[elem].raideur_compression_m;
      			elongation = (n - Surf_Hexa[elem].no_repos) / Surf_Hexa[elem].no_repos;
      			if (elongation >= 0.0) Surf_Hexa[elem].tension3 = elongation * Surf_Hexa[elem].raideur_traction_n;
      			if (elongation <  0.0) Surf_Hexa[elem].tension3 = elongation * Surf_Hexa[elem].raideur_compression_n;
    			Surf_Hexa[elem].nrj1= Surf_Hexa[elem].tension1 * (l - Surf_Hexa[elem].lo_repos)/2.0;
    			Surf_Hexa[elem].nrj2= Surf_Hexa[elem].tension2 * (m - Surf_Hexa[elem].mo_repos)/2.0;
    			Surf_Hexa[elem].nrj3= Surf_Hexa[elem].tension3 * (n - Surf_Hexa[elem].no_repos)/2.0;
    			Surf_Hexa[elem].nrj = Surf_Hexa[elem].nrj1 + Surf_Hexa[elem].nrj2 + Surf_Hexa[elem].nrj3;
  			}
  		/*lecture de la position du front */
  		fscanf(f1,"%lf",&frontx);
  		Prise.front = frontx;
      
    		/* lecture des derniers deplacements. */
    		/*for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    			{
      			fscanf(f1,"%d %lf %lf %lf",&tmp,&Noeud[elem].depx,&Noeud[elem].depy,&Noeud[elem].depz);
    			}*/

  		for( pa = 1 ; pa <= Sortie_texte.nb_distance ; pa++ )
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_distance[pa]);
			printf("Sortie_texte.valeur_distance[pa] %8.2lf \n",Sortie_texte.valeur_distance[pa]);
  			}
  		
  		for( pa = 1 ; pa <= Sortie_texte.nb_effort ; pa++ )
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_effort[pa]);
			printf("Sortie_texte.valeur_effort[pa] %8.2lf \n",Sortie_texte.valeur_effort[pa]);
  			}
  		
  		for( pa = 1 ; pa <= Sortie_texte.nb_tension_element ; pa++ )
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_tension[pa]);
			printf("Sortie_texte.valeur_tension[pa] %8.2lf \n",Sortie_texte.valeur_tension[pa]);
  			}
  		
  		for( pa = 1 ; pa <= Sortie_texte.nb_tension_coulisse ; pa++ )
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_tension_coulisse[pa]);
			printf("Sortie_texte.valeur_tension_coulisse[pa] %8.2lf \n",Sortie_texte.valeur_tension_coulisse[pa]);
  			}
 		
  		for( pa = 1 ; pa <= Sortie_texte.nb_position ; pa++ )
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_position[pa]);
			printf("Sortie_texte.valeur_position[pa] %8.2lf \n",Sortie_texte.valeur_position[pa]);
  			}
  		
  		if(Sortie_texte.bottom_drag == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_bottom_drag);
			printf("Sortie_texte.valeur_bottom_drag %8.2lf \n",Sortie_texte.valeur_bottom_drag);
  			}
  		
  		if(Sortie_texte.catch_drag == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_catch_drag);
			printf("Sortie_texte.valeur_catch_drag %8.2lf \n",Sortie_texte.valeur_catch_drag);
  			}
  		
  		if(Sortie_texte.element_drag == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_element_drag);
			printf("Sortie_texte.valeur_element_drag %8.2lf \n",Sortie_texte.valeur_element_drag);
  			}
  		
  		if(Sortie_texte.surface_drag == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_surface_drag);
			printf("Sortie_texte.valeur_surface_drag %8.2lf \n",Sortie_texte.valeur_surface_drag);
  			}
  		
  		if(Sortie_texte.node_drag == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_node_drag);
			printf("Sortie_texte.valeur_node_drag %8.2lf \n",Sortie_texte.valeur_node_drag);
  			}
  		
  		if(Sortie_texte.effort_structure == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf %lf %lf",&Sortie_texte.valeur_effort_structure[1],&Sortie_texte.valeur_effort_structure[2],&Sortie_texte.valeur_effort_structure[3]);
			printf("Sortie_texte.valeur_effort_structure %lf %lf %lf \n",Sortie_texte.valeur_effort_structure[1],Sortie_texte.valeur_effort_structure[2],Sortie_texte.valeur_effort_structure[3]);
  			}
  		
  		if(Sortie_texte.diametre_prise == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_diametre_prise);
  			}
  		
  		if(Sortie_texte.epaisseur_prise == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_epaisseur_prise);
  			}
  		
  		if(Sortie_texte.volume_capture == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_volume_capture);
  			}
  		
  		if(Sortie_texte.vitesse_courant == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_vitesse_courant);
			printf("Sortie_texte.valeur_vitesse_courant %8.2lf \n",Sortie_texte.valeur_vitesse_courant);
  			}
  		if(Sortie_texte.surface_filtree == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_surface_filtree);
  			}  	

  		for( pa = 1 ; pa <= Sortie_texte.nb_longueur_cable ; pa++ )
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Sortie_texte.valeur_longueur_cable[pa]);
			printf("Sortie_texte.valeur_longueur_cable[pa] %8.2lf \n",Sortie_texte.valeur_longueur_cable[pa]);
			}/**/

		printf("Sortie_texte.inner_surface %d \n",Sortie_texte.inner_surface);
		
  		/*lecture de la position de l ellipsoide de la surface interne de la prise*/ 
 		if(Sortie_texte.inner_surface == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%lf ",&Prise.radial_radius);
			fscanf(f1,"%lf ",&Prise.axial_radius);
			fscanf(f1,"%lf ",&Prise.distance_front);
			fscanf(f1,"%lf ",&Prise.Ox);
			fscanf(f1,"%lf ",&Prise.Oy);
			fscanf(f1,"%lf ",&Prise.Oz);
			printf("Prise.radial_radius %8.3lf ",Prise.radial_radius);
			printf("Prise.axial_radius %8.3lf ",Prise.axial_radius);
			printf("Prise.distance_front %8.3lf \n",Prise.distance_front);
  			Prise.front = Prise.Ox + Prise.distance_front;
  			frontx = Prise.front;
  			}
		/*printf("Sortie_texte.inner_surface_triangulation %d \n",Sortie_texte.inner_surface_triangulation);
		exit(0);*/
  			
  		/*lecture de la position de lellipsoide de la surface interne de la prise*/ 
 		if(Sortie_texte.inner_surface_triangulation == 1)
  			{
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%d ",&Prise.nb_noeuds);
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%d ",&Prise.nb_noeuds_contour);
			printf("Prise.nb_noeuds %8d Prise.nb_noeuds_contour %8d \n",Prise.nb_noeuds,Prise.nb_noeuds_contour);
			Prise.xx =        (double *) Malloc_double(1 + Prise.nb_noeuds);
			Prise.yy =        (double *) Malloc_double(1 + Prise.nb_noeuds);
			Prise.zz =        (double *) Malloc_double(1 + Prise.nb_noeuds);
  			Prise.xx_ini =    (double *) Malloc_double(1 + Prise.nb_noeuds);
			Prise.yy_ini =    (double *) Malloc_double(1 + Prise.nb_noeuds);
			Prise.zz_ini =    (double *) Malloc_double(1 + Prise.nb_noeuds);
  			for (elem = 1 ; elem<= Prise.nb_noeuds ; elem++) 
  				{
				fscanf(f1,"%lf ",&Prise.xx_ini[elem]);
				fscanf(f1,"%lf ",&Prise.yy_ini[elem]);
				fscanf(f1,"%lf ",&Prise.zz_ini[elem]);
				Prise.xx[elem] = Prise.xx_ini[elem];
				Prise.yy[elem] = Prise.yy_ini[elem];
				Prise.zz[elem] = Prise.zz_ini[elem];
  				}
 			do  c=fgetc(f1); while (c !=':');	
			fscanf(f1,"%d ",&Prise.nb_triangles);
			printf("Prise.nb_triangles %8d \n",Prise.nb_triangles);
			Prise.vertex_1 =        (int *) Malloc_int(1 + Prise.nb_triangles);
			Prise.vertex_2 =        (int *) Malloc_int(1 + Prise.nb_triangles);
			Prise.vertex_3 =        (int *) Malloc_int(1 + Prise.nb_triangles);
  			for (elem = 1 ; elem<= Prise.nb_triangles ; elem++) 
  				{
				fscanf(f1,"%d ",&tmp);
				fscanf(f1,"%d ",&Prise.vertex_1[elem]);
				fscanf(f1,"%d ",&Prise.vertex_2[elem]);
				fscanf(f1,"%d ",&Prise.vertex_3[elem]);
				/*printf("no %8d %8d %8d \n",Prise.vertex_1[elem],Prise.vertex_2[elem],Prise.vertex_3[elem]);*/
				}
  			}
	  	if(Sortie_texte.meridian == 1)
	  		{
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
	  		}
	 	if(Sortie_texte.meridian_X == 1)
	  		{
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
 			do  c=fgetc(f1); while (c !=':');	
	  		for( pa = 1 ; pa <= tmp ; pa++ )
	  			{
				fscanf(f1,"%lf ",&temp1);
				fscanf(f1,"%lf ",&temp1);
	  			}
	  		}
	  	if(Sortie_texte.meridian_Y == 1)
	  		{
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
 			do  c=fgetc(f1); while (c !=':');	
	  		for( pa = 1 ; pa <= tmp ; pa++ )
	  			{
				fscanf(f1,"%lf ",&temp1);
				fscanf(f1,"%lf ",&temp1);
	  			}
	  		}
		if(Sortie_texte.meridian_Z == 1)
	  		{
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
 			do  c=fgetc(f1); while (c !=':');	
	  		for( pa = 1 ; pa <= tmp ; pa++ )
	  			{
				fscanf(f1,"%lf ",&temp1);
				fscanf(f1,"%lf ",&temp1);
	  			}
	  		}
	 	if(Sortie_texte.curvilinear_codend_length == 1)
	  		{
	  		}
	 	if(Opening_angle.nb_panel > 0)
	  		{
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
	  		for( pa = 1 ; pa <= tmp ; pa++ )
	  			{
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp2);
				for (elem = 1 ; elem <= Opening_angle.nb_tab ; elem++)
					{
					fscanf(f1,"%lf ",&temp1);
					}
	  			}
	  		}
	   	if(Opening_mesh.nb_panel > 0)
	  		{
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
	  		for( pa = 1 ; pa <= tmp ; pa++ )
	  			{
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp2);
				for (elem = 1 ; elem <= Opening_angle.nb_tab ; elem++)
					{
					fscanf(f1,"%lf ",&temp1);
					}
	  			}
	  		}
	  	if(Opening_angle_stripe.nb_panel > 0)
	  		{
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
	  		for( pa = 1 ; pa <= tmp ; pa++ )
	  			{
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp2);
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
				for (elem = 1 ; elem <= Opening_angle_stripe.nb_tab ; elem++)
					{
					fscanf(f1,"%lf ",&temp1);
					}
	  			}
	  		}
	 	if (Prise.dir_mesh_front > 0)
	  		{
			if (Prise.dir_mesh_front == 1)
				{
 				do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
				}
			if (Prise.dir_mesh_front == 2)
				{
				do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
				}
	  		}
	 	if (Sortie_texte.panel_drag == 1)
	  		{
 			do  c=fgetc(f1); while (c !=':');	
 			////////////////////////////////////////////////21/10/23  	Structure.NbTypesurf	replaced by NbTypesurf
			for (pa=1;pa<=NbTypesurf;pa++)
				{
				fscanf(f1,"%d ",&tmp);
 				fscanf(f1,"%lf ",&temp1);				
 				}
 			}
		if (Sortie_texte.cable_drag == 1)
	  		{
 			do  c=fgetc(f1); while (c !=':');	  		
			for (pa=1;pa<=Structure.NbTypeelem;pa++)
				{
				fscanf(f1,"%d ",&tmp);
 				fscanf(f1,"%lf ",&temp1);				
				}
	  		}
		if (Structure.nb_value != 0)
	  		{
			for (pa = 1; pa<=Structure.nb_value ; pa++)
				{
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp2);
				do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
				do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
				do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
				do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
				}
			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
	  		}
		if (Structure.nb_recouvrement_x != 0)
	  		{
	  		}
		if (Structure.nb_vector_tension_bar != 0)
	  		{
	  		}
		if (Plan_cutting.nb_plan == 1)
	  		{
	 		do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
	 		do  c=fgetc(f1); while (c !=':');		  		
			for( pa = 1 ; pa <=  tmp; pa++ )
		  		{
				fscanf(f1,"%lf ",&temp1);
				fscanf(f1,"%lf ",&temp1);
				fscanf(f1,"%lf ",&temp1);
				fscanf(f1,"%lf ",&temp1);
		  		}
		 	}
		if (Structure.cut_plan_symmetry == 2)
	  		{	
	  		fscanf(f1,"%d ",&tmp);
	 		do  c=fgetc(f1); while (c !=':');	  		
			for (pa = 1; pa<= NOMBRE_SURFACES; pa++)
				{
				do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);	fscanf(f1,"%lf ",&temp1);	fscanf(f1,"%lf ",&temp1);
				do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);	fscanf(f1,"%lf ",&temp1);	fscanf(f1,"%lf ",&temp1);
				do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
				}
	 		}
		if(Orientation_netting.nb_panel > 0)
	  		{
	 		do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
			for (pa = 1 ; pa <= tmp ; pa++)
				{
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
				for (elem = 1 ; elem <= Orientation_netting.nb_tab ; elem++)
					{
					fscanf(f1,"%lf ",&temp1);
					}
				}
	 		do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
			for (pa = 1 ; pa <= tmp ; pa++)
				{
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
				for (elem = 1 ; elem <= Orientation_netting.nb_tab ; elem++)
					{
					fscanf(f1,"%lf ",&temp1);
					}
				}
	 		do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
			for (pa = 1 ; pa <= tmp ; pa++)
				{
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&tmp);
				for (elem = 1 ; elem <= Orientation_netting.nb_tab ; elem++)
					{
					fscanf(f1,"%lf ",&temp1);
					}
				}
	  		}
	  	if(Grid_drag.pas > 0.0)
	  		{
	  		}
	  	if (Foot_print.nb == -1)
	  		{
	  		}
		if (Structure.eigenvalues > 0)
	  		{
	 		do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%d ",&Structure.eigenvalues);
			//int n_jacobi_result;
			n_jacobi_result = 3*NOMBRE_NOEUDS;
			v_jacobi_result = matrix(1,(long) n_jacobi_result,1,(long) Structure.eigenvalues);
			v_jacobi_rotati = matrix(1,n_jacobi_result,1,Structure.eigenvalues);
			d_jacobi_result = vector(1,n_jacobi_result);			
			do  c=fgetc(f1); while (c !=':');
			for (pa=1;pa<=Structure.eigenvalues;pa++)
				{
				fscanf(f1,"%f ",&d_jacobi_result[pa]);
				//printf("%f   ",d_jacobi_result[pa]);
				}
			//printf("\n");
	 		do  c=fgetc(f1); while (c !=':');			
			for (pa=1;pa<=n_jacobi_result;pa++)
				{
				for (elem=1;elem<=Structure.eigenvalues;elem++)
					{
					fscanf(f1,"%f ",&v_jacobi_result[pa][elem]);
					v_jacobi_rotati[pa][elem] = v_jacobi_result[pa][elem]; //Used for rotation
					//printf("%f   ",v_jacobi_result[pa][elem]);
					}
				//printf("\n");
				}
	  		}
		if (Sortie_texte.triangle_drag == 1)
			{
	 		do  c=fgetc(f1); while (c !=':');
	  		for (pa = 1 ; pa<= NOMBRE_SURFACES ; pa++) 
				{
				fscanf(f1,"%d ",&tmp);
				fscanf(f1,"%lf ",&temp1);
				fscanf(f1,"%lf ",&temp1);
				}
			}
		if (Prise.angle_tensions > 0)
			{
	 		do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
	 		do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
	 		do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
			}
		if (Structure.ballast_altitude == 1)
			{
			printf("There is record a record of the ballasts altitude in sta file.\n");
			Structure.nb_ballast = 1;
			for (pa = 1; pa<=Structure.nb_ballast; pa++)
				{
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&temp1);
	 			do  c=fgetc(f1); while (c !=':');	fscanf(f1,"%lf ",&Ballast[pa].altitude);
				printf("There is record a record of the ballasts %d altitude in sta file. = %lf m\n",pa,Ballast[pa].altitude);
				/*initialisation of the free surface in the 1st ballast*/
				surface_ballast[1][1] = minx; surface_ballast[2][1] = miny; surface_ballast[3][1] = Ballast[pa].altitude;
				surface_ballast[1][2] = minx; surface_ballast[2][2] = maxy; surface_ballast[3][2] = Ballast[pa].altitude;
				surface_ballast[1][3] = maxx; surface_ballast[2][3] = maxy; surface_ballast[3][3] = Ballast[pa].altitude;
				surface_ballast[1][4] = maxx; surface_ballast[2][4] = miny; surface_ballast[3][4] = Ballast[pa].altitude;
				}
			}		
			
  			
		printf("end of lecturesta \n");

  		fclose(f1);
 		return 1;
 		}
	}	


