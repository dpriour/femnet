#define PRINCIPAL 0
#include "4c19.h"

/*void effortstructur();
double surf_filtree();*/

void sortie_texte_ecran()
	{
	/*display on screen text output*/
	
	int pa,no,el,zi,int1,int2,int3;
	double surface_filtree,effort,volume_x,volume_y,volume_z,volume_0;
	double dx,dy,dz,distance2,distance,longueur,energie;
	  	
  	for( pa = 1 ; pa <= Sortie_texte.nb_distance ; pa++ )
  		{
		no = 0;
		while ((Sortie_texte.comment_distance[pa].texte[no] !=':') && (no<155))
			{
			no++;
			printf("%c",Sortie_texte.comment_distance[pa].texte[no]);
			}
		int1 = Sortie_texte.noeud1_distance[pa];
		int2 = Sortie_texte.noeud2_distance[pa];
		int3 = Sortie_texte.decimale_distance[pa];
		
		dx = wf[3*fixa[int2]-2] - wf[3*fixa[int1]-2];
		dy = wf[3*fixa[int2]-1] - wf[3*fixa[int1]-1];
		dz = wf[3*fixa[int2]-0] - wf[3*fixa[int1]-0];
		distance2 = dx*dx + dy*dy + dz*dz;
		if (distance2 >= 0.0) 
			{
			distance = sqrt (distance2);
			}
		else
			{
			distance = 0.0;
			}
  		if (int3 <= 0 ) printf("%12.0lf \n",distance);
  		if (int3 == 1 ) printf("%12.1lf \n",distance);
  		if (int3 == 2 ) printf("%12.2lf \n",distance);
  		if (int3 == 3 ) printf("%12.3lf \n",distance);
  		if (int3 == 4 ) printf("%12.4lf \n",distance);
  		if (int3 == 5 ) printf("%12.5lf \n",distance);
  		if (int3 == 6 ) printf("%12.6lf \n",distance);
  		if (int3 == 7 ) printf("%12.7lf \n",distance);
  		if (int3 == 8 ) printf("%12.8lf \n",distance);
  		if (int3 >= 9 ) printf("%12.9lf \n",distance);
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_effort ; pa++ )
  		{
		no = 0;
		while ((Sortie_texte.comment_effort[pa].texte[no] !=':') && (no<155))
			{
			no++;
			printf("%c",Sortie_texte.comment_effort[pa].texte[no]);
			}
  		int1 = Sortie_texte.noeud_effort[pa];
  		int2 = Sortie_texte.axe_effort[pa];
  		int3 = Sortie_texte.decimale_effort[pa];
  		effort = wasurf[3*fixa[int1]-3+int2] + waelem[3*fixa[int1]-3+int2] + wanoeud[3*fixa[int1]-3+int2];
  		//effort = waelem[3*fixa[int1]-3+int2];
  		if (int3 <= 0 ) printf("%12.0lf \n",effort);
  		if (int3 == 1 ) printf("%12.1lf \n",effort);
  		if (int3 == 2 ) printf("%12.2lf \n",effort);
  		if (int3 == 3 ) printf("%12.3lf \n",effort);
  		if (int3 == 4 ) printf("%12.4lf \n",effort);
  		if (int3 == 5 ) printf("%12.5lf \n",effort);
  		if (int3 == 6 ) printf("%12.6lf \n",effort);
  		if (int3 == 7 ) printf("%12.7lf \n",effort);
  		if (int3 == 8 ) printf("%12.8lf \n",effort);
  		if (int3 >= 9 ) printf("%12.9lf \n",effort);
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_tension_element ; pa++ )
  		{
		/*printf("element : %d  ",Sortie_texte.element_tension[pa]);
		printf("noeud : %d\n",Sortie_texte.element_extremite[pa]);*/
  		for( zi = 1 ; zi <= NOMBRE_ELEMENTS ; zi++ )
  			{
  			if(Element[zi].type == Sortie_texte.element_tension[pa])
  				{
  				/*printf("elem %5d extremites  %5d %5d ",zi,Element[zi].extremite[1],Element[zi].extremite[2]);
  				printf("type %5d ",Element[zi].type);
  				printf("fixa %5d \n",fixa[Sortie_texte.element_extremite[pa]]);*/
  				if(Element[zi].extremite[1] == fixa[Sortie_texte.element_extremite[pa]])
  					{
  					el = zi;
  					break;
  					}
  				if(Element[zi].extremite[2] == fixa[Sortie_texte.element_extremite[pa]])
  					{
  					el = zi;
  					break;
  					}
  				}
  			}
  		if ((el < 1) || (el > NOMBRE_ELEMENTS))
  			{
			printf("La sortie suivante ne peut pas etre faite : %4d",el);
			no = 0;
			while ((Sortie_texte.comment_tension_element[pa].texte[no] !=':') && (no<155))
				{
				no++;
				printf("%c",Sortie_texte.comment_tension_element[pa].texte[no]);
				}
			printf("\n");
  			}
  		else
  			{
			no = 0;
			while ((Sortie_texte.comment_tension_element[pa].texte[no] !=':') && (no<155))
				{
				no++;
				printf("%c",Sortie_texte.comment_tension_element[pa].texte[no]);
				}
			int1 = Sortie_texte.decimale_tension_element[pa];
			
  			if (int1 <= 0 ) printf("%12.0lf \n",Element[el].wt);
  			if (int1 == 1 ) printf("%12.1lf \n",Element[el].wt);
  			if (int1 == 2 ) printf("%12.2lf \n",Element[el].wt);
  			if (int1 == 3 ) printf("%12.3lf \n",Element[el].wt);
  			if (int1 == 4 ) printf("%12.4lf \n",Element[el].wt);
  			if (int1 == 5 ) printf("%12.5lf \n",Element[el].wt);
  			if (int1 == 6 ) printf("%12.6lf \n",Element[el].wt);
  			if (int1 == 7 ) printf("%12.7lf \n",Element[el].wt);
  			if (int1 == 8 ) printf("%12.8lf \n",Element[el].wt);
  			if (int1 >= 9 ) printf("%12.9lf \n",Element[el].wt);
			}
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_tension_coulisse ; pa++ )
  		{
  		for( zi = 1 ; zi <= NOMBRE_COULISSES ; zi++ )
  			{
  			if(zi == Sortie_texte.coulisse_tension[pa])
  				{
  				if(Coulisse[zi].extremite[1] == fixa[Sortie_texte.coulisse_extremite[pa]])
  					{
  					el = zi;
  					break;
  					}
  				if(Coulisse[zi].extremite[2] == fixa[Sortie_texte.coulisse_extremite[pa]])
  					{
  					el = zi;
  					break;
  					}
  				}
  			}
  		if ((el < 1) || (el > NOMBRE_COULISSES))
  			{
			printf("La sortie suivante ne peut pas etre faite : %4d",el);
			no = 0;
			while ((Sortie_texte.comment_tension_coulisse[pa].texte[no] !=':') && (no<155))
				{
				no++;
				printf("%c",Sortie_texte.comment_tension_coulisse[pa].texte[no]);
				}
			printf("\n");
  			}
  		else
  			{
			no = 0;
			while ((Sortie_texte.comment_tension_coulisse[pa].texte[no] !=':') && (no<155))
				{
				no++;
				printf("%c",Sortie_texte.comment_tension_coulisse[pa].texte[no]);
				}
			int1 = Sortie_texte.decimale_tension_coulisse[pa];
  			if (int1 <= 0 ) printf("%12.0lf \n",Coulisse[el].wt);
  			if (int1 == 1 ) printf("%12.1lf \n",Coulisse[el].wt);
  			if (int1 == 2 ) printf("%12.2lf \n",Coulisse[el].wt);
  			if (int1 == 3 ) printf("%12.3lf \n",Coulisse[el].wt);
  			if (int1 == 4 ) printf("%12.4lf \n",Coulisse[el].wt);
  			if (int1 == 5 ) printf("%12.5lf \n",Coulisse[el].wt);
  			if (int1 == 6 ) printf("%12.6lf \n",Coulisse[el].wt);
  			if (int1 == 7 ) printf("%12.7lf \n",Coulisse[el].wt);
  			if (int1 == 8 ) printf("%12.8lf \n",Coulisse[el].wt);
  			if (int1 >= 9 ) printf("%12.9lf \n",Coulisse[el].wt);
			}
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_position ; pa++ )
  		{
		no = 0;
		while ((Sortie_texte.comment_position[pa].texte[no] !=':') && (no<155))
			{
			no++;
			printf("%c",Sortie_texte.comment_position[pa].texte[no]);
			}
  		int1 = Sortie_texte.noeud_position[pa];
  		int2 = Sortie_texte.axe_position[pa];
  		int3 = Sortie_texte.decimale_position[pa];
  		if (int3 <= 0 ) printf("%12.0lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 1 ) printf("%12.1lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 2 ) printf("%12.2lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 3 ) printf("%12.3lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 4 ) printf("%12.4lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 5 ) printf("%12.5lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 6 ) printf("%12.6lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 7 ) printf("%12.7lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 8 ) printf("%12.8lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 >= 9 ) printf("%12.9lf \n",wf[3*fixa[int1]-3+int2]);
  		}
  		




  	if(Sortie_texte.bottom_drag == 1)
  		{
  		if (Bottom.drag >= 100.0)							printf("bottom drag along X (N)					: %8.0lf \n",Bottom.drag);
  		if ((Bottom.drag < 100.0) && (Bottom.drag >= 10.0))				printf("bottom drag along X (N)					: %9.1lf \n",Bottom.drag);
  		if ((Bottom.drag < 10.0) && (Bottom.drag >= 1.0))				printf("bottom drag along X (N)					: %10.2lf \n",Bottom.drag);
  		if ((Bottom.drag < 1.0) && (Bottom.drag >= 0.1))				printf("bottom drag along X (N)					: %11.3lf \n",Bottom.drag);
  		if (Bottom.drag < 0.1)								printf("bottom drag along X (N)					: %12.4lf \n",Bottom.drag);
  		}
  		
  	if(Sortie_texte.catch_drag == 1)
  		{
  		if (Prise.drag >= 100.0)							printf("catch drag along X (N)					: %8.0lf \n",Prise.drag);
  		if ((Prise.drag < 100.0) && (Prise.drag >= 10.0))				printf("catch drag along X (N)					: %9.1lf \n",Prise.drag);
  		if ((Prise.drag < 10.0) && (Prise.drag >= 1.0))				printf("catch drag along X (N)					: %10.2lf \n",Prise.drag);
  		if ((Prise.drag < 1.0) && (Prise.drag >= 0.1))					printf("catch drag along X (N)					: %11.3lf \n",Prise.drag);
  		if (Prise.drag < 0.1)								printf("catch drag along X (N)					: %12.4lf \n",Prise.drag);
  		}
  		
  	if(Sortie_texte.element_drag == 1)
  		{
  		if (Structure.element_drag >= 100.0)						printf("element drag along X (N)				: %8.0lf \n",Structure.element_drag);
  		if ((Structure.element_drag < 100.0) && (Structure.element_drag >= 10.0))	printf("element drag along X (N)				: %9.1lf \n",Structure.element_drag);
  		if ((Structure.element_drag < 10.0) && (Structure.element_drag >= 1.0))	printf("element drag along X (N)				: %10.2lf \n",Structure.element_drag);
  		if ((Structure.element_drag < 1.0) && (Structure.element_drag >= 0.1))	printf("element drag along X (N)				: %11.3lf \n",Structure.element_drag);
  		if (Structure.element_drag < 0.1)						printf("element drag along X (N)				: %12.4lf \n",Structure.element_drag);
  		}
  		
  	if(Sortie_texte.surface_drag == 1)
  		{
  		if (Structure.surface_drag >= 100.0)						printf("surface drag along X (N)				: %8.0lf \n",Structure.surface_drag);
  		if ((Structure.surface_drag < 100.0) && (Structure.surface_drag >= 10.0))	printf("surface drag along X (N)				: %9.1lf \n",Structure.surface_drag);
  		if ((Structure.surface_drag < 10.0) && (Structure.surface_drag >= 1.0))	printf("surface drag along X (N)				: %10.2lf \n",Structure.surface_drag);
  		if ((Structure.surface_drag < 1.0) && (Structure.surface_drag >= 0.1))	printf("surface drag along X (N)				: %11.3lf \n",Structure.surface_drag);
  		if (Structure.surface_drag < 0.1)						printf("surface drag along X (N)				: %12.4lf \n",Structure.surface_drag);
  		}
  		
  	if(Sortie_texte.node_drag == 1)
  		{
  		if (Structure.node_drag >= 100.0)						printf("node drag along X (N)					: %8.0lf \n",Structure.node_drag);
  		if ((Structure.node_drag < 100.0) && (Structure.node_drag >= 10.0))		printf("node drag along X (N)					: %9.1lf \n",Structure.node_drag);
  		if ((Structure.node_drag < 10.0) && (Structure.node_drag >= 1.0))		printf("node drag along X (N)					: %10.2lf \n",Structure.node_drag);
  		if ((Structure.node_drag < 1.0) && (Structure.node_drag >= 0.1))		printf("node drag along X (N)					: %11.3lf \n",Structure.node_drag);
  		if (Structure.node_drag < 0.1)							printf("node drag along X (N)					: %12.4lf \n",Structure.node_drag);
  		}
  		
  	effortstructur();
  	/*Structure.total_drag = wa[1];*/
/* debut modifdp du 18 mars 2010*/
  	Structure.total_drag = Bottom.drag + Prise.drag + Structure.element_drag + Structure.surface_drag + Structure.node_drag;
    	/*printf("Bottom.drag %lf\n",Bottom.drag);
    	printf("Prise.drag %lf\n",Prise.drag);
    	printf("Structure.element_drag %lf\n",Structure.element_drag);
    	printf("Structure.surface_drag %lf\n",Structure.surface_drag);
    	printf("Structure.node_drag %lf\n",Structure.node_drag);
    	printf("Structure.total_drag %lf\n",Structure.total_drag);
    	exit(0);*/
/* fin modifdp du 18 mars 2010*/

  	if((Sortie_texte.bottom_drag == 1) || (Sortie_texte.catch_drag == 1) || (Sortie_texte.element_drag == 1) || (Sortie_texte.surface_drag == 1) || (Sortie_texte.node_drag == 1))
  		{
  		if (Structure.total_drag >= 100.0)					printf("total drag along X (N)				: %8.0lf \n",Structure.total_drag);
  		if ((Structure.total_drag < 100.0) && (Structure.total_drag >= 10.0))	printf("total drag along X (N)				: %9.1lf \n",Structure.total_drag);
  		if ((Structure.total_drag < 10.0) && (Structure.total_drag >= 1.0))		printf("total drag along X (N)				: %10.2lf \n",Structure.total_drag);
  		if ((Structure.total_drag < 1.0) && (Structure.total_drag >= 0.1))		printf("total drag along X (N)				: %11.3lf \n",Structure.total_drag);
  		if (Structure.total_drag < 0.1)						printf("total drag along X (N)				: %12.4lf \n",Structure.total_drag);
		/*printf("effort sur la structure selon X Y et Z (N)	: %12.2lf %12.2lf %12.2lf \n",wa[1],wa[2],wa[3]);*/
		printf("forces on the structure along X Y and Z (N)	: %12.0lf %12.0lf %12.0lf \n",wa[1],wa[2],wa[3]);
  		}
  		
  	if(Sortie_texte.diametre_prise == 1)
  		{ 
		/*printf("diametre de la prise (m) 			: %12.3lf \n",Prise.diametre);*/
		printf("maximal diameter of the catch (m) 		: %12.3lf \n",Prise.diametre);
  		}
  		
  	if(Sortie_texte.epaisseur_prise == 1)
  		{
		/*printf("epaisseur de la prise (m) 			: %12.3lf \n",Prise.epaisseur);*/
		printf("thickness of the catch  (m) 			: %15.7lf \n",Prise.epaisseur);
  		}
  		
  	if(Sortie_texte.volume_capture == 1)
  		{
		/*printf("volume de la capture (m3) 			: %12.3lf \n",Prise.volume);*/
		printf("effective volume of the catch (m3) 		: %15.7lf \n",Prise.volume_effectif);
  		}
  		
  	if(Sortie_texte.vitesse_courant == 1)
  		{
		/*printf("vitesse du courant (m/s)			: %12.3lf \n",Courant.vitesse);*/
		printf("current amplitude (m/s)				: %12.3lf \n",Courant.vitesse);
  		}
  		
  	if(Sortie_texte.surface_filtree == 1)
  		{
  		surface_filtree = surf_filtree();
		/*printf("surface filtree (m2) 				: %12.2lf \n",surface_filtree);*/
		printf("filtered surface (m2) 				: %12.2lf \n",surface_filtree);
  		}  		

	/**********************************************************************/
	double_temp = 0.0;
	/**********************************************************************/
  	for( pa = 1 ; pa <= Sortie_texte.nb_longueur_cable ; pa++ )
  		{
		longueur = 0.0;
  		for( zi = 1 ; zi <= NOMBRE_ELEMENTS ; zi++ )
  			{
  			if(Element[zi].type == Sortie_texte.element_longueur_cable[pa])
  				{
  				longueur = longueur + Element[zi].lgtendue;
  				}
  			}
			/**********************************************************************/
			double_temp = double_temp + longueur;
			/**********************************************************************/
			printf("%s",Sortie_texte.comment_longueur_cable[pa].texte);
			int1 = Sortie_texte.decimale_longueur_cable[pa];
  			if (int1 <= 0 ) printf("%12.0lf \n",longueur);
  			if (int1 == 1 ) printf("%12.1lf \n",longueur);
  			if (int1 == 2 ) printf("%12.2lf \n",longueur);
  			if (int1 == 3 ) printf("%12.3lf \n",longueur);
  			if (int1 == 4 ) printf("%12.4lf \n",longueur);
  			if (int1 == 5 ) printf("%12.5lf \n",longueur);
  			if (int1 == 6 ) printf("%12.6lf \n",longueur);
  			if (int1 == 7 ) printf("%12.7lf \n",longueur);
  			if (int1 == 8 ) printf("%12.8lf \n",longueur);
  			if (int1 >= 9 ) printf("%12.9lf \n",longueur);
		}

  	for( pa = 1 ; pa <= Sortie_texte.nb_energie_elong_diamond ; pa++ )
  		{
		energie = 0.0;
  		for( zi = 1 ; zi <= NOMBRE_SURFACES ; zi++ )
  			{
  			if( Surface[zi].type == Sortie_texte.panneau_energie_elong[pa])
  				{
  				energie = energie + Surface[zi].energy_elastique;
  				}
  			}
			printf("%s",Sortie_texte.comment_energie_elong_diamond[pa].texte);
			int1 = Sortie_texte.decimale_energie_elong[pa];
  			if (int1 <= 0 ) printf("%12.0lf \n",energie);
  			if (int1 == 1 ) printf("%12.1lf \n",energie);
  			if (int1 == 2 ) printf("%12.2lf \n",energie);
  			if (int1 == 3 ) printf("%12.3lf \n",energie);
  			if (int1 == 4 ) printf("%12.4lf \n",energie);
  			if (int1 == 5 ) printf("%12.5lf \n",energie);
  			if (int1 == 6 ) printf("%12.6lf \n",energie);
  			if (int1 == 7 ) printf("%12.7lf \n",energie);
  			if (int1 == 8 ) printf("%12.8lf \n",energie);
  			if (int1 >= 9 ) printf("%12.9lf \n",energie);
		}

  	for( pa = 1 ; pa <= Sortie_texte.nb_energie_fold_diamond ; pa++ )
  		{
		energie = 0.0;
  		for( zi = 1 ; zi <= NOMBRE_SURFACES ; zi++ )
  			{
  			if( Surface[zi].type == Sortie_texte.panneau_energie_fold[pa])
  				{
  				energie = energie + Surface[zi].energy_pliage;
  				}
  			}
			printf("%s",Sortie_texte.comment_energie_fold_diamond[pa].texte);
			int1 = Sortie_texte.decimale_energie_fold[pa];
  			if (int1 <= 0 ) printf("%12.0lf \n",energie);
  			if (int1 == 1 ) printf("%12.1lf \n",energie);
  			if (int1 == 2 ) printf("%12.2lf \n",energie);
  			if (int1 == 3 ) printf("%12.3lf \n",energie);
  			if (int1 == 4 ) printf("%12.4lf \n",energie);
  			if (int1 == 5 ) printf("%12.5lf \n",energie);
  			if (int1 == 6 ) printf("%12.6lf \n",energie);
  			if (int1 == 7 ) printf("%12.7lf \n",energie);
  			if (int1 == 8 ) printf("%12.8lf \n",energie);
  			if (int1 >= 9 ) printf("%12.9lf \n",energie);
		}

  	for( pa = 1 ; pa <= Sortie_texte.nb_energie_open_diamond ; pa++ )
  		{
		energie = 0.0;
  		for( zi = 1 ; zi <= NOMBRE_SURFACES ; zi++ )
  			{
  			if( Surface[zi].type == Sortie_texte.panneau_energie_open[pa])
  				{
  				energie = energie + Surface[zi].energy_ouverture;
				}
  			}
			printf("%s",Sortie_texte.comment_energie_open_diamond[pa].texte);
			int1 = Sortie_texte.decimale_energie_open[pa];
  			if (int1 <= 0 ) printf("%12.0lf \n",energie);
  			if (int1 == 1 ) printf("%12.1lf \n",energie);
  			if (int1 == 2 ) printf("%12.2lf \n",energie);
  			if (int1 == 3 ) printf("%12.3lf \n",energie);
  			if (int1 == 4 ) printf("%12.4lf \n",energie);
  			if (int1 == 5 ) printf("%12.5lf \n",energie);
  			if (int1 == 6 ) printf("%12.6lf \n",energie);
  			if (int1 == 7 ) printf("%12.7lf \n",energie);
  			if (int1 == 8 ) printf("%12.8lf \n",energie);
  			if (int1 >= 9 ) printf("%12.9lf \n",energie);
		}

  	for( pa = 1 ; pa <= Sortie_texte.nb_energie_contact_diamond ; pa++ )
  		{
		energie = 0.0;
  		for( zi = 1 ; zi <= NOMBRE_SURFACES ; zi++ )
  			{
  			if( Surface[zi].type == Sortie_texte.panneau_energie_contact[pa])
  				{
  				energie = energie + Surface[zi].energy_contact;
				}
  			}
			printf("%s",Sortie_texte.comment_energie_contact_diamond[pa].texte);
			int1 = Sortie_texte.decimale_energie_contact[pa];
  			if (int1 <= 0 ) printf("%12.0lf \n",energie);
  			if (int1 == 1 ) printf("%12.1lf \n",energie);
  			if (int1 == 2 ) printf("%12.2lf \n",energie);
  			if (int1 == 3 ) printf("%12.3lf \n",energie);
  			if (int1 == 4 ) printf("%12.4lf \n",energie);
  			if (int1 == 5 ) printf("%12.5lf \n",energie);
  			if (int1 == 6 ) printf("%12.6lf \n",energie);
  			if (int1 == 7 ) printf("%12.7lf \n",energie);
  			if (int1 == 8 ) printf("%12.8lf \n",energie);
  			if (int1 >= 9 ) printf("%12.9lf \n",energie);
		}

  	if(Sortie_texte.volume_x == 1)
  		{
		/*printf("volume selon x (m3) 				: %12.2lf \n",volume_x);*/
		printf("volume along x (m3) 				: %12.2lf \n",volume_x);
  		}  		

  	if(Sortie_texte.volume_y == 1)
  		{
		/*printf("volume selon y (m3) 				: %12.2lf \n",volume_y);*/
		printf("volume along y (m3) 				: %12.2lf \n",volume_y);
  		}  		

  	if(Sortie_texte.volume_z == 1)
  		{
		/*printf("volume selon z (m3) 				: %12.2lf \n",volume_z);*/
		surface_filtree = surf_filtree_direction(3);
		printf("volume along z (m3) 				: %12.2lf \n",volume_z);
  		}  		

  	if(Sortie_texte.volume_0 == 1)
  		{
		/*printf("volume selon le courant (m3) 			: %12.2lf \n",volume_0);*/
		printf("volume along the current (m3) 			: %12.2lf \n",volume_0);
  		}  		

  	if(Sortie_texte.inner_surface == 1)
  		{
		inner_surface();
		printf("ellipsoidal inner surface: radial radius: %6.3lf axial radius: %6.3lf center to the front: %6.3lf (m)\n",Prise.radial_radius,Prise.axial_radius,Prise.distance_front);
  		}  		
	if (Sortie_texte.panel_drag == 1)
		{
		printf("Drag of panels (N): \n");
		for (pa=1;pa<=Structure.NbTypesurf;pa++)
			{
			printf("%d : %6.0lf\n",pa,panneau[pa].drag);
			}
		}
	if (Sortie_texte.cable_drag == 1)
		{
		printf("Drag of cables (N): \n");
		for (pa=1;pa<=Structure.NbTypeelem;pa++)
			{
			printf("%d : %6.0lf\n",pa,TypeElement[pa].cable_drag);
			}
		}
	}
	
