#define PRINCIPAL 0
#include "4c19.h"

void sortie_texte_file(char *nomfichier)
	{
	/*ecrit dans le fichier *.sta les sorties texte*/
	
  	char   tonom[1000];
  	/*FILE   *file2;*/
	int pa,no,el,zi,int1,int2,int3;
	double surface_filtree;
	double dx,dy,dz,distance2,distance,longueur;
	
  	strcpy(tonom,nomfichier);
  	strcat(tonom,".sta");
  	/*printf(" \n");
  	printf("%s %s \n","file ",tonom);*/

  	file2 = fopen(tonom,"a");
  	for( pa = 1 ; pa <= Sortie_texte.nb_distance ; pa++ )
  		{
		no = 0;
		while ((Sortie_texte.comment_distance[pa].texte[no] !=':') && (no<155))
			{
			no++;
			fprintf(file2,"%c",Sortie_texte.comment_distance[pa].texte[no]);
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
  		if (int3 <= 0 ) fprintf(file2,"%12.0lf \n",distance);
  		if (int3 == 1 ) fprintf(file2,"%12.1lf \n",distance);
  		if (int3 == 2 ) fprintf(file2,"%12.2lf \n",distance);
  		if (int3 == 3 ) fprintf(file2,"%12.3lf \n",distance);
  		if (int3 == 4 ) fprintf(file2,"%12.4lf \n",distance);
  		if (int3 == 5 ) fprintf(file2,"%12.5lf \n",distance);
  		if (int3 == 6 ) fprintf(file2,"%12.6lf \n",distance);
  		if (int3 == 7 ) fprintf(file2,"%12.7lf \n",distance);
  		if (int3 == 8 ) fprintf(file2,"%12.8lf \n",distance);
  		if (int3 >= 9 ) fprintf(file2,"%12.9lf \n",distance);
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_effort ; pa++ )
  		{
		no = 0;
		while ((Sortie_texte.comment_effort[pa].texte[no] !=':') && (no<155))
			{
			no++;
			fprintf(file2,"%c",Sortie_texte.comment_effort[pa].texte[no]);
			}
  		int1 = Sortie_texte.noeud_effort[pa];
  		int2 = Sortie_texte.axe_effort[pa];
  		int3 = Sortie_texte.decimale_effort[pa];
  		if (int3 <= 0 ) fprintf(file2,"%12.0lf \n",wa[3*fixa[int1]-3+int2]);
  		if (int3 == 1 ) fprintf(file2,"%12.1lf \n",wa[3*fixa[int1]-3+int2]);
  		if (int3 == 2 ) fprintf(file2,"%12.2lf \n",wa[3*fixa[int1]-3+int2]);
  		if (int3 == 3 ) fprintf(file2,"%12.3lf \n",wa[3*fixa[int1]-3+int2]);
  		if (int3 == 4 ) fprintf(file2,"%12.4lf \n",wa[3*fixa[int1]-3+int2]);
  		if (int3 == 5 ) fprintf(file2,"%12.5lf \n",wa[3*fixa[int1]-3+int2]);
  		if (int3 == 6 ) fprintf(file2,"%12.6lf \n",wa[3*fixa[int1]-3+int2]);
  		if (int3 == 7 ) fprintf(file2,"%12.7lf \n",wa[3*fixa[int1]-3+int2]);
  		if (int3 == 8 ) fprintf(file2,"%12.8lf \n",wa[3*fixa[int1]-3+int2]);
  		if (int3 >= 9 ) fprintf(file2,"%12.9lf \n",wa[3*fixa[int1]-3+int2]);
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_tension_element ; pa++ )
  		{
  		for( zi = 1 ; zi <= NOMBRE_ELEMENTS ; zi++ )
  			{
  			if(Element[zi].type == Sortie_texte.element_tension[pa])
  				{
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
			fprintf(file2,"La sortie suivante ne peut pas etre faite : ");
			no = 0;
			while ((Sortie_texte.comment_tension_element[pa].texte[no] !=':') && (no<155))
				{
				no++;
				fprintf(file2,"%c",Sortie_texte.comment_tension_element[pa].texte[no]);
				}
			fprintf(file2,"\n");
  			}
  		else
  			{
			no = 0;
			while ((Sortie_texte.comment_tension_element[pa].texte[no] !=':') && (no<155))
				{
				no++;
				fprintf(file2,"%c",Sortie_texte.comment_tension_element[pa].texte[no]);
				}
			int1 = Sortie_texte.decimale_tension_element[pa];
  			if (int1 <= 0 ) fprintf(file2,"%12.0lf \n",Element[el].wt);
  			if (int1 == 1 ) fprintf(file2,"%12.1lf \n",Element[el].wt);
  			if (int1 == 2 ) fprintf(file2,"%12.2lf \n",Element[el].wt);
  			if (int1 == 3 ) fprintf(file2,"%12.3lf \n",Element[el].wt);
  			if (int1 == 4 ) fprintf(file2,"%12.4lf \n",Element[el].wt);
  			if (int1 == 5 ) fprintf(file2,"%12.5lf \n",Element[el].wt);
  			if (int1 == 6 ) fprintf(file2,"%12.6lf \n",Element[el].wt);
  			if (int1 == 7 ) fprintf(file2,"%12.7lf \n",Element[el].wt);
  			if (int1 == 8 ) fprintf(file2,"%12.8lf \n",Element[el].wt);
  			if (int1 >= 9 ) fprintf(file2,"%12.9lf \n",Element[el].wt);
			}
  		}
  		
  		
  	/*faire pout toutes (pa) les tensions de coulisses demandees*/
  	for( pa = 1 ; pa <= Sortie_texte.nb_tension_coulisse ; pa++ )
  		{
  		for( zi = 1 ; zi <= NOMBRE_COULISSES ; zi++ )
  			{
  			/*recherche du numero (zi) de la coulisse visee*/
  			if(zi == Sortie_texte.coulisse_tension[pa])
  				{
  				/*recherche du numero (el) de l extremite de coulisse ou est demandee la tension*/
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
  			/*dans ce cas ... ???*/
			fprintf(file2,"La sortie suivante ne peut pas etre faite : ");
			no = 0;
			while ((Sortie_texte.comment_tension_coulisse[pa].texte[no] !=':') && (no<155))
				{
				no++;
				fprintf(file2,"%c",Sortie_texte.comment_tension_coulisse[pa].texte[no]);
				}
			fprintf(file2,"\n");
  			}
  		else
  			{
			no = 0;
			while ((Sortie_texte.comment_tension_coulisse[pa].texte[no] !=':') && (no<155))
				{
				/*ecriture du commentaire*/
				no++;
				fprintf(file2,"%c",Sortie_texte.comment_tension_coulisse[pa].texte[no]);
				}
			int1 = Sortie_texte.decimale_tension_coulisse[pa];
  			if (int1 <= 0 ) fprintf(file2,"%12.0lf \n",Coulisse[el].wt);
  			if (int1 == 1 ) fprintf(file2,"%12.1lf \n",Coulisse[el].wt);
  			if (int1 == 2 ) fprintf(file2,"%12.2lf \n",Coulisse[el].wt);
  			if (int1 == 3 ) fprintf(file2,"%12.3lf \n",Coulisse[el].wt);
  			if (int1 == 4 ) fprintf(file2,"%12.4lf \n",Coulisse[el].wt);
  			if (int1 == 5 ) fprintf(file2,"%12.5lf \n",Coulisse[el].wt);
  			if (int1 == 6 ) fprintf(file2,"%12.6lf \n",Coulisse[el].wt);
  			if (int1 == 7 ) fprintf(file2,"%12.7lf \n",Coulisse[el].wt);
  			if (int1 == 8 ) fprintf(file2,"%12.8lf \n",Coulisse[el].wt);
  			if (int1 >= 9 ) fprintf(file2,"%12.9lf \n",Coulisse[el].wt);
			}
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_position ; pa++ )
  		{
		no = 0;
		while ((Sortie_texte.comment_position[pa].texte[no] !=':') && (no<155))
			{
			no++;
			fprintf(file2,"%c",Sortie_texte.comment_position[pa].texte[no]);
			}
  		int1 = Sortie_texte.noeud_position[pa];
  		int2 = Sortie_texte.axe_position[pa];
  		int3 = Sortie_texte.decimale_position[pa];
  		if (int3 <= 0 ) fprintf(file2,"%12.0lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 1 ) fprintf(file2,"%12.1lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 2 ) fprintf(file2,"%12.2lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 3 ) fprintf(file2,"%12.3lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 4 ) fprintf(file2,"%12.4lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 5 ) fprintf(file2,"%12.5lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 6 ) fprintf(file2,"%12.6lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 7 ) fprintf(file2,"%12.7lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 8 ) fprintf(file2,"%12.8lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 >= 9 ) fprintf(file2,"%12.9lf \n",wf[3*fixa[int1]-3+int2]);
  		}
  		
  	if(Sortie_texte.catch_drag == 1)
  		{
		fprintf(file2,"catch drag (N)				: %12.0lf \n",Prise.drag);
  		}
  		
  	if(Sortie_texte.effort_structure == 1)
  		{
  		effortstructur();
		fprintf(file2,"forces along X Y and Z axes (N)		: %12.6lf %12.6lf %12.6lf \n",wa[1],wa[2],wa[3]);
  		}
  		
  	if(Sortie_texte.diametre_prise == 1)
  		{
		fprintf(file2,"maximal catch diameter (m) 			: %12.3lf \n",Prise.diametre);
  		}
  		
  	if(Sortie_texte.epaisseur_prise == 1)
  		{
		fprintf(file2,"thickness of the catch (m) 			: %12.3lf \n",Prise.epaisseur);
  		}
  		
  	if(Sortie_texte.volume_capture == 1)
  		{
		fprintf(file2,"effective_volume of the catch (m3) 		: %12.4lf \n",Prise.volume_effectif);
  		}
  		
  	if(Sortie_texte.vitesse_courant == 1)
  		{
		fprintf(file2,"current amplitude (m/s)			: %12.3lf \n",Courant.vitesse);
  		}
  		
  	if(Sortie_texte.surface_filtree == 1)
  		{
  		surface_filtree = surf_filtree();
		fprintf(file2,"filtered surface (m2) 				: %12.2lf \n",surface_filtree);
  		}

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
			fprintf(file2,"%s",Sortie_texte.comment_longueur_cable[pa].texte);
			int1 = Sortie_texte.decimale_longueur_cable[pa];
  			if (int1 <= 0 ) fprintf(file2,"%12.0lf \n",longueur);
  			if (int1 == 1 ) fprintf(file2,"%12.1lf \n",longueur);
  			if (int1 == 2 ) fprintf(file2,"%12.2lf \n",longueur);
  			if (int1 == 3 ) fprintf(file2,"%12.3lf \n",longueur);
  			if (int1 == 4 ) fprintf(file2,"%12.4lf \n",longueur);
  			if (int1 == 5 ) fprintf(file2,"%12.5lf \n",longueur);
  			if (int1 == 6 ) fprintf(file2,"%12.6lf \n",longueur);
  			if (int1 == 7 ) fprintf(file2,"%12.7lf \n",longueur);
  			if (int1 == 8 ) fprintf(file2,"%12.8lf \n",longueur);
  			if (int1 >= 9 ) fprintf(file2,"%12.9lf \n",longueur);
		}

  	fclose(file2);
  	
	}
	
