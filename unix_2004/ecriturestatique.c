#define PRINCIPAL 0
#include "4c19.h"

int ecriturestatique(char *nomfichier)
	{
  	char   tonom[1000];
  	FILE   *f3,*f4;
  	int    j,elem,pa,no,zi,zj,zk,el,int1,int2,int3,nb_recouv,nb_angles,zu,zv,no_cable,node,component;
  	double elongation,surface_filtree,amplitude,effort,min_x,min_y,min_z,max_x,max_y,max_z;
	double dx,dy,dz,distance2,distance,longueur;
	/* debut modifdp du 5 mars 2010*/
	double VECT[4],dir[4],Vn[4],Vm[4];	
	/* fin modifdp du 5 mars 2010*/	
	double UU[4],VV[4],NUU,NVV,ps,alpha;
	
	double miny, maxy, minz, maxz,yplus,ymoins,zplus,zmoins;    		
	double x1,x2,value,norm_n,norm_m,scal,cos_gamma,sin_gamma,dn,dm,min_exit,max_exit,mean_exit,std_dev;
	double y1,y2,y3,y4,y5,y6,y7,y8,y9,y10,y11,y12,y13,y14,y15,y16,y17,y18,y19,y20,y21,y22,y23,y24,y25,y26,y27,y28,y29,y30,y31,y32,y33,y34,y35,y36,y37,y38,y39,y40,y41,y42,y43,y44,y45,y46,y47,y48;
	double z1,z2,z3,z4,z5,z6,z7,z8,z9,z10,z11,z12,z13,z14,z15,z16,z17,z18,z19,z20,z21,z22,z23,z24,z25,z26,z27,z28,z29,z30,z31,z32,z33,z34,z35,z36,z37,z38,z39,z40,z41,z42,z43,z44,z45,z46,z47,z48;
	double *xmat,*cmat,surface_totale,surface_coupee,longueur_totale,longueur_coupee;
	int nby,nbz,n_ligne,p_colonne,zl,zc,nb_triangle_plus_y,nb_triangle_moin_y,nb_triangle_plus_z,nb_triangle_moin_z;
	int nb_segment_plus_y,nb_segment_moin_y,nb_segment_plus_z,nb_segment_moin_z,nb_tri;
	/*modified Breddermann 06.05.2021 */
    	double Sn1;
	//sta file/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  	strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0;
  	strcat(tonom,".sta");
  	printf(" \n");
  	printf("%s %s \n","file ",tonom);

  	f3 = fopen(tonom,"w");
  	/*ecriture des coordonnees a l equilibre statique dans le meme ordre que dans le fichier de donnees
  	en tenant compte de la renumerotation de largeurbande.c*/
	//printf("ball %17.9lf  %17.9lf  %17.9lf\n",wf[3*fixa[57]-2],wf[3*fixa[57]-1],wf[3*fixa[57]-2]);
  	for (elem = 1 ; elem<= NOMBRE_NOEUDS ; elem++) 
  		{
    		fprintf(f3,"  %5d",elem);
    		fprintf(f3,"  %17.9lf",wf[3*fixa[elem]-2]);
    		fprintf(f3,"  %17.9lf",wf[3*fixa[elem]-1]);
    		fprintf(f3,"  %17.9lf",wf[3*fixa[elem]-0]);
    		fprintf(f3,"\n");
  		}
 
  	/*ecriture de l elongation des elements a l equilibre statique */
  	for (elem = 1 ; elem<= NOMBRE_ELEMENTS ; elem++)
    		{
    		elongation = (Element[elem].lgtendue - Element[elem].lgrepos) / Element[elem].lgrepos;
    		fprintf(f3," %12.7lf \n",elongation);
    		}
  	fprintf(f3,"\n");

  	/*ecriture de l elongation des coulisses a l equilibre statique */
  	for (elem = 1 ; elem<= NOMBRE_COULISSES ; elem++)
    		{
    		elongation = (Coulisse[elem].lgtendue - Coulisse[elem].lgrepos) / Coulisse[elem].lgrepos;
    		fprintf(f3," %12.7lf \n",elongation);
    		}
  	fprintf(f3,"\n");

  	/*ecriture de la longueur des mailles des surfaces a l equilibre statique */
  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
  		{
    		fprintf(f3," %19.15lf ",Surface[elem].mx);
    		fprintf(f3," %19.15lf ",Surface[elem].my);
    		fprintf(f3," %19.15lf ",Surface[elem].mz);
    		fprintf(f3," %19.15lf ",Surface[elem].nx);
    		fprintf(f3," %19.15lf ",Surface[elem].ny);
    		fprintf(f3," %19.15lf ",Surface[elem].nz);
    		fprintf(f3,"\n");
  		}
  	fprintf(f3,"\n");

  	/*ecriture de la longueur des mailles pour les filets a mailles hexagonales a l equilibre statique */
  	for (elem = 1 ; elem<= NOMBRE_SURF_HEXA ; elem++) 
  		{
    		fprintf(f3," %9.5lf ",Surf_Hexa[elem].lx);
    		fprintf(f3," %9.5lf ",Surf_Hexa[elem].ly);
    		fprintf(f3," %9.5lf ",Surf_Hexa[elem].lz);
    		fprintf(f3," %9.5lf ",Surf_Hexa[elem].mx);
    		fprintf(f3," %9.5lf ",Surf_Hexa[elem].my);
    		fprintf(f3," %9.5lf ",Surf_Hexa[elem].mz);
    		fprintf(f3," %9.5lf ",Surf_Hexa[elem].nx);
    		fprintf(f3," %9.5lf ",Surf_Hexa[elem].ny);
    		fprintf(f3," %9.5lf ",Surf_Hexa[elem].nz);
    		fprintf(f3,"\n");
  		}
  	fprintf(f3,"\n");
  	/*writting of the position of the limit between 2 panels if exists*/

 	if(Prise.panels[1] != Prise.panels[2]	)
  		{
  		limit_panels();
		if(Prise.front < Prise.limit_panels)
			{
  			fprintf(f3," %12.3lf \n",Prise.front);
 			}
		else
			{
  			fprintf(f3," %12.3lf \n",Prise.limit_panels);
			}
  		}
	else
  		{
  		/*ecriture de la position du front */
	  	if (Prise.catch_gravity > 0.0)			/*in this case the codend is expected to be outside the water and affected by the gravity*/
	  		{
  			fprintf(f3," %12.3lf \n",-Prise.front);
  			}
  		else
  			{
  			fprintf(f3," %12.3lf \n",Prise.front);
  			}
  		}

  	for( pa = 1 ; pa <= Sortie_texte.nb_distance ; pa++ )
  		{
		no = 0;
		while ((Sortie_texte.comment_distance[pa].texte[no] !=':') && (no<155))
			{
			no++;
			fprintf(f3,"%c",Sortie_texte.comment_distance[pa].texte[no]);
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
  		if (int3 <= 0 ) fprintf(f3,"%12.0lf \n",distance);
  		if (int3 == 1 ) fprintf(f3,"%12.1lf \n",distance);
  		if (int3 == 2 ) fprintf(f3,"%12.2lf \n",distance);
  		if (int3 == 3 ) fprintf(f3,"%12.3lf \n",distance);
  		if (int3 == 4 ) fprintf(f3,"%12.4lf \n",distance);
  		if (int3 == 5 ) fprintf(f3,"%12.5lf \n",distance);
  		if (int3 == 6 ) fprintf(f3,"%12.6lf \n",distance);
  		if (int3 == 7 ) fprintf(f3,"%12.7lf \n",distance);
  		if (int3 == 8 ) fprintf(f3,"%12.8lf \n",distance);
  		if (int3 >= 9 ) fprintf(f3,"%12.9lf \n",distance);
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_effort ; pa++ )
  		{
		no = 0;
		while ((Sortie_texte.comment_effort[pa].texte[no] !=':') && (no<155))
			{
			no++;
			fprintf(f3,"%c",Sortie_texte.comment_effort[pa].texte[no]);
			}
  		int1 = Sortie_texte.noeud_effort[pa];
  		int2 = Sortie_texte.axe_effort[pa];
  		int3 = Sortie_texte.decimale_effort[pa];
  		effort = wasurf[3*fixa[int1]-3+int2] + waelem[3*fixa[int1]-3+int2] + wanoeud[3*fixa[int1]-3+int2];
  		if (int3 <= 0 ) fprintf(f3,"%12.0lf \n",effort);
  		if (int3 == 1 ) fprintf(f3,"%12.1lf \n",effort);
  		if (int3 == 2 ) fprintf(f3,"%12.2lf \n",effort);
  		if (int3 == 3 ) fprintf(f3,"%12.3lf \n",effort);
  		if (int3 == 4 ) fprintf(f3,"%12.4lf \n",effort);
  		if (int3 == 5 ) fprintf(f3,"%12.5lf \n",effort);
  		if (int3 == 6 ) fprintf(f3,"%12.6lf \n",effort);
  		if (int3 == 7 ) fprintf(f3,"%12.7lf \n",effort);
  		if (int3 == 8 ) fprintf(f3,"%12.8lf \n",effort);
  		if (int3 >= 9 ) fprintf(f3,"%12.9lf \n",effort);
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
			fprintf(f3,"La sortie suivante ne peut pas etre faite : ");
			no = 0;
			while ((Sortie_texte.comment_tension_element[pa].texte[no] !=':') && (no<155))
				{
				no++;
				fprintf(f3,"%c",Sortie_texte.comment_tension_element[pa].texte[no]);
				}
			fprintf(f3,"\n");
  			}
  		else
  			{
			no = 0;
			while ((Sortie_texte.comment_tension_element[pa].texte[no] !=':') && (no<155))
				{
				no++;
				fprintf(f3,"%c",Sortie_texte.comment_tension_element[pa].texte[no]);
				}
			int1 = Sortie_texte.decimale_tension_element[pa];
  			if (int1 <= 0 ) fprintf(f3,"%12.0lf \n",Element[el].wt);
  			if (int1 == 1 ) fprintf(f3,"%12.1lf \n",Element[el].wt);
  			if (int1 == 2 ) fprintf(f3,"%12.2lf \n",Element[el].wt);
  			if (int1 == 3 ) fprintf(f3,"%12.3lf \n",Element[el].wt);
  			if (int1 == 4 ) fprintf(f3,"%12.4lf \n",Element[el].wt);
  			if (int1 == 5 ) fprintf(f3,"%12.5lf \n",Element[el].wt);
  			if (int1 == 6 ) fprintf(f3,"%12.6lf \n",Element[el].wt);
  			if (int1 == 7 ) fprintf(f3,"%12.7lf \n",Element[el].wt);
  			if (int1 == 8 ) fprintf(f3,"%12.8lf \n",Element[el].wt);
  			if (int1 >= 9 ) fprintf(f3,"%12.9lf \n",Element[el].wt);
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
			fprintf(f3,"La sortie suivante ne peut pas etre faite : ");
			no = 0;
			while ((Sortie_texte.comment_tension_coulisse[pa].texte[no] !=':') && (no<155))
				{
				no++;
				fprintf(f3,"%c",Sortie_texte.comment_tension_coulisse[pa].texte[no]);
				}
			fprintf(f3,"\n");
  			}
  		else
  			{
			no = 0;
			while ((Sortie_texte.comment_tension_coulisse[pa].texte[no] !=':') && (no<155))
				{
				/*ecriture du commentaire*/
				no++;
				fprintf(f3,"%c",Sortie_texte.comment_tension_coulisse[pa].texte[no]);
				}
			int1 = Sortie_texte.decimale_tension_coulisse[pa];
  			if (int1 <= 0 ) fprintf(f3,"%12.0lf \n",Coulisse[el].wt);
  			if (int1 == 1 ) fprintf(f3,"%12.1lf \n",Coulisse[el].wt);
  			if (int1 == 2 ) fprintf(f3,"%12.2lf \n",Coulisse[el].wt);
  			if (int1 == 3 ) fprintf(f3,"%12.3lf \n",Coulisse[el].wt);
  			if (int1 == 4 ) fprintf(f3,"%12.4lf \n",Coulisse[el].wt);
  			if (int1 == 5 ) fprintf(f3,"%12.5lf \n",Coulisse[el].wt);
  			if (int1 == 6 ) fprintf(f3,"%12.6lf \n",Coulisse[el].wt);
  			if (int1 == 7 ) fprintf(f3,"%12.7lf \n",Coulisse[el].wt);
  			if (int1 == 8 ) fprintf(f3,"%12.8lf \n",Coulisse[el].wt);
  			if (int1 >= 9 ) fprintf(f3,"%12.9lf \n",Coulisse[el].wt);
			}
  		}
  		
  	for( pa = 1 ; pa <= Sortie_texte.nb_position ; pa++ )
  		{
		no = 0;
		while ((Sortie_texte.comment_position[pa].texte[no] !=':') && (no<155))
			{
			no++;
			fprintf(f3,"%c",Sortie_texte.comment_position[pa].texte[no]);
			}
  		int1 = Sortie_texte.noeud_position[pa];
  		int2 = Sortie_texte.axe_position[pa];
  		int3 = Sortie_texte.decimale_position[pa];
  		if (int3 <= 0 ) fprintf(f3,"%12.0lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 1 ) fprintf(f3,"%12.1lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 2 ) fprintf(f3,"%12.2lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 3 ) fprintf(f3,"%12.3lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 4 ) fprintf(f3,"%12.4lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 5 ) fprintf(f3,"%12.5lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 6 ) fprintf(f3,"%12.6lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 7 ) fprintf(f3,"%12.7lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 == 8 ) fprintf(f3,"%12.8lf \n",wf[3*fixa[int1]-3+int2]);
  		if (int3 >= 9 ) fprintf(f3,"%12.9lf \n",wf[3*fixa[int1]-3+int2]);
  		}
  		
  	if(Sortie_texte.bottom_drag == 1)
  		{
		fprintf(f3,"bottom drag (N)				: %12.0lf \n",Bottom.drag);
  		}
  		
  	if(Sortie_texte.catch_drag == 1)
  		{
		fprintf(f3,"catch drag (N)				: %12.0lf \n",Prise.drag);
  		}
  		
  	if(Sortie_texte.element_drag == 1)
  		{
		fprintf(f3,"element drag (N)				: %12.0lf \n",Structure.element_drag);
  		}
  		
  	if(Sortie_texte.surface_drag == 1)
  		{
		fprintf(f3,"surface drag (N)				: %12.0lf \n",Structure.surface_drag);
  		}
 		
  	if(Sortie_texte.node_drag == 1)
  		{
		fprintf(f3,"node drag (N)				: %12.0lf \n",Structure.node_drag);
  		}
	//printf("Sortie_texte.effort_structure %d:",Sortie_texte.effort_structure);  	exit(0);	
  	if(Sortie_texte.effort_structure == 1)
  		{
  		effortstructur();
		fprintf(f3,"forces along X Y and Z axes (N)		: %12.5lf %12.5lf %12.5lf \n",wa[1],wa[2],wa[3]);
		
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".efg");	
	  	f4 = fopen(tonom,"a");
	    	fprintf(f4,"static_forc:");
	     	for ( zi = 1 ; zi <= Structure.nb_fixed_components ; zi++ )
	     	{ 
	     		node = fixa[Structure.list_fixed_node[zi]];
	     		component = 3 * node + Structure.list_fixed_axe[zi] - 3;
			fprintf(f4," %10.2lf  ",wasurf[component] + waelem[component] + wanoeud[component]);
		}
		fprintf(f4,"\n");
		fclose(f4);
		
		
  		}
  		
  	if(Sortie_texte.diametre_prise == 1)
  		{
		if(Sortie_texte.meridian == 1)
  			{
  			meridian();
  			}
		fprintf(f3,"maximal catch diameter (m) 			: %12.3lf \n",Prise.diametre);
  		}
  		
  	if(Sortie_texte.epaisseur_prise == 1)
  		{
 		if(Prise.panels[1] != Prise.panels[2]	)
  			{
  			limit_panels();
			if(Prise.front < Prise.limit_panels)
				{
				fprintf(f3,"thickness of the catch (m) 			: %12.3lf \n",Prise.epaisseur);
 				}
			else
				{
				fprintf(f3,"thickness of the catch (m) 			: %12.3lf \n",Prise.front + Prise.epaisseur - Prise.limit_panels);
				}
  			}
		else
  			{
			fprintf(f3,"thickness of the catch (m) 			: %12.3lf \n",Prise.epaisseur);
  			}
    		}
  		
  	if(Sortie_texte.volume_capture == 1)
  		{
		fprintf(f3,"volume of the catch (m3) 			: %12.4lf \n",Prise.volume_effectif);
  		}
  		
  	if(Sortie_texte.vitesse_courant == 1)
  		{
		fprintf(f3,"current amplitude (m/s)			: %12.3lf \n",Courant.vitesse);
  		}
  		
  	if(Sortie_texte.surface_filtree == 1)
  		{
  		surface_filtree = surf_filtree();
		fprintf(f3,"filtered surface (m2) 				: %12.2lf \n",surface_filtree);
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
			fprintf(f3,"%s",Sortie_texte.comment_longueur_cable[pa].texte);
			int1 = Sortie_texte.decimale_longueur_cable[pa];
  			if (int1 <= 0 ) fprintf(f3,"%12.0lf \n",longueur);
  			if (int1 == 1 ) fprintf(f3,"%12.1lf \n",longueur);
  			if (int1 == 2 ) fprintf(f3,"%12.2lf \n",longueur);
  			if (int1 == 3 ) fprintf(f3,"%12.3lf \n",longueur);
  			if (int1 == 4 ) fprintf(f3,"%12.4lf \n",longueur);
  			if (int1 == 5 ) fprintf(f3,"%12.5lf \n",longueur);
  			if (int1 == 6 ) fprintf(f3,"%12.6lf \n",longueur);
  			if (int1 == 7 ) fprintf(f3,"%12.7lf \n",longueur);
  			if (int1 == 8 ) fprintf(f3,"%12.8lf \n",longueur);
  			if (int1 >= 9 ) fprintf(f3,"%12.9lf \n",longueur);
		}
		
  	/*ecriture de la position de lellipsoide de la surface interne de la prise */
 	if(Sortie_texte.inner_surface == 1)
  		{
  		inner_surface();
		fprintf(f3,"ellipsoide radial_radius, axial_radius, distance_front, Ox, Oy, Oz: %12.3lf %12.3lf %12.3lf %12.3lf %12.3lf %12.3lf \n",Prise.radial_radius,Prise.axial_radius,Prise.distance_front,Prise.Ox,Prise.Oy,Prise.Oz);
  		}
  	/*ecriture de la triangulation de l ellipsoide de la surface interne de la prise */
 	if(Sortie_texte.inner_surface_triangulation == 1)
  		{
  		if (Sortie_texte.inner_surface == 0)
  			{
  			printf("ca va pas etre possible*****************************\n ");
  			}
  		else
  			{
  			printf("ca va  etre possible*****************************\n ");
			fprintf(f3,"triangulation inner surface: nb of points %d \n",10);
  			}
  		}
  	/*ecriture de la meridian */
 	if(Sortie_texte.meridian == 1)
  		{
  		meridian();
		/*fprintf(f3,"meridian nb of points: %d \n",Prise.nb_point_meridian);*/
		fprintf(f3,"meridian: nb of points %d \n",Prise.nb_point_meridian);
		fprintf(f3,"           x            r: \n");
  		for( pa = 1 ; pa <= Prise.nb_point_meridian ; pa++ )
  			{
			fprintf(f3,"%12.6lf %12.6lf  \n",Prise.meridian_x[pa],Prise.meridian_r[pa]);
  			}
		fprintf(f3," \n");
  		}
  	/*ecriture de la meridian_x */
 	if(Sortie_texte.meridian_X == 1)
  		{
  		meridian_x();
		fprintf(f3,"meridian_x nb of points: %d \n",Prise.nb_point_meridian);
		fprintf(f3,"           y            z: \n");
  		for( pa = 1 ; pa <= Prise.nb_point_meridian ; pa++ )
  			{
			fprintf(f3,"%12.3lf %12.3lf  \n",Prise.meridian_y[pa],Prise.meridian_z[pa]);
  			}
		fprintf(f3," \n");
  		}
  	/*ecriture de la meridian_y */
 	if(Sortie_texte.meridian_Y == 1)
  		{
  		meridian_y();
		fprintf(f3,"meridian_y nb of points: %d \n",Prise.nb_point_meridian);
		fprintf(f3,"           z            x: \n");
  		for( pa = 1 ; pa <= Prise.nb_point_meridian ; pa++ )
  			{
			fprintf(f3,"%12.3lf %12.3lf  \n",Prise.meridian_z[pa],Prise.meridian_x[pa]);
  			}
		fprintf(f3," \n");
  		}
  	/*ecriture de la meridian_z */
 	if(Sortie_texte.meridian_Z == 1)
  		{
  		meridian_z();
		fprintf(f3,"meridian_z nb of points: %d \n",Prise.nb_point_meridian);
		fprintf(f3,"           x            y: \n");
  		for( pa = 1 ; pa <= Prise.nb_point_meridian ; pa++ )
  			{
			fprintf(f3,"%12.3lf %12.3lf  \n",Prise.meridian_x[pa],Prise.meridian_y[pa]);
  			}
		fprintf(f3," \n");
  		}
  	/*ecriture de la longueur curviligne du codend */
 	if(Sortie_texte.curvilinear_codend_length == 1)
  		{
  		meridian();
  		curvilinear();
  		}
  	if(Opening_angle.nb_panel > 0)
    		{
	      	opening();
	  	fprintf(f3,"Opening angle by panel, nb of panels: %d, angle step (deg): %lf \n",Opening_angle.nb_panel,Opening_angle.pas);
		for (pa = 1 ; pa <= Opening_angle.nb_panel ; pa++)
			{
	  		fprintf(f3,"panel: %d      ",Opening_angle.panel[pa]);
			for (elem = 1 ; elem <= Opening_angle.nb_tab ; elem++)
				{
	  			fprintf(f3," %lf",Opening_angle.tab[pa][elem]);
   				}
	  		fprintf(f3,"\n");
			} 		
    		}
  	if(Opening_mesh.nb_panel > 0)
    		{
	      	opening_mesh();
	  	fprintf(f3,"Opening mesh by panel, nb of panels: %d, mesh step (m^2): %lf, nb of class: %d\n",Opening_mesh.nb_panel,Opening_mesh.pas,Opening_mesh.nb_tab);
		for (pa = 1 ; pa <= Opening_mesh.nb_panel ; pa++)
			{
	  		fprintf(f3,"panel: %d      ",Opening_mesh.panel[pa]);
			for (elem = 1 ; elem <= Opening_mesh.nb_tab ; elem++)
				{
	  			fprintf(f3," %lf",Opening_mesh.tab[pa][elem]);
   				}
	  		fprintf(f3,"\n");
			} 		
    		}
  	if(Opening_angle_stripe.nb_panel > 0)
    		{
	      	opening_stripe();
	  	fprintf(f3,"Opening angle by stripe, nb of stripes: %d, angle step (deg): %lf \n",Opening_angle_stripe.nb_stripe,Opening_angle_stripe.pas);
		for (pa = 1 ; pa <= Opening_angle_stripe.nb_stripe ; pa++)
			{
	  		fprintf(f3,"stripe: %d  ",pa);
	  		fprintf(f3,"from(m): %10.3lf to(m): %10.3lf  ",Opening_angle_stripe.fromx[pa],Opening_angle_stripe.tox[pa]);
			for (elem = 1 ; elem <= Opening_angle_stripe.nb_tab ; elem++)
				{
	  			fprintf(f3," %10.0lf",Opening_angle_stripe.tab[pa][elem]);
   				}
	  		fprintf(f3,"\n");
			} 		
    		}
  	if (Prise.dir_mesh_front > 0)
  		{
		nb_mesh_front(Prise.front);
		if (Prise.dir_mesh_front == 1)
			{
			fprintf(f3,"Position of the front in U meshes: %lf \n",Prise.nb_mesh_front);
			}
		if (Prise.dir_mesh_front == 2)
			{
			fprintf(f3,"Position of the front in V meshes: %lf \n",Prise.nb_mesh_front);
			}
    		}
	if (Sortie_texte.panel_drag == 1)
		{
		fprintf(f3,"Drag of panels (N): \n");
		for (pa=1;pa<=Structure.NbTypesurf;pa++)
			{
			fprintf(f3,"%d		%lf\n",pa,panneau[pa].drag);
			}
		}
	if (Sortie_texte.cable_drag == 1)
		{
		fprintf(f3,"Drag of cables (N): \n");
		for (pa=1;pa<=Structure.NbTypeelem;pa++)
			{
			fprintf(f3,"%d		%lf\n",pa,TypeElement[pa].cable_drag);
			}
		}
	if (Structure.nb_value != 0)
		{
		/*
		int sens_lim_Y = -1;
		double lim_Y = 5.0;
		amplitude = value_calculation3(lim_Y,sens_lim_Y);
		*/
		amplitude = value_calculation2();
		for (zi = 1; zi<=Structure.nb_value ; zi++)
			{
			printf("value nb: %d",zi);
			printf("value: %lf at depth: %lf and value: %lf at depth: %lf\n",Value.value1[zi],Value.depth1[zi],Value.value2[zi],Value.depth2[zi]);
			fprintf(f3,"value nb: %d",zi);
			fprintf(f3,"value: %lf at depth: %lf and value: %lf at depth: %lf\n",Value.value1[zi],Value.depth1[zi],Value.value2[zi],Value.depth2[zi]);
			}
		printf("amplitude of value:	%lf \n",amplitude);
		fprintf(f3,"amplitude  of value:	%lf \n",amplitude);
		}
	if (Structure.nb_recouvrement_x != 0)
		{
		for (zi = 1; zi<=Structure.nb_recouvrement_x ; zi++)
			{
			printf("recouvrement_x nb: %4d",zi);
			printf("element1: %4d element2: %4d ",Recouvrement_x.element1[zi],Recouvrement_x.element2[zi]);
			int1 = Recouvrement_x.element1[zi];
			int2 = Recouvrement_x.element2[zi];
			nb_recouv =  recouvrement_x(int1,int2,&dx,&dy,&dz);
			Recouvrement_x.min[zi] = dx;
			Recouvrement_x.max[zi] = dy;
			Recouvrement_x.mean[zi] = dz;
			printf("nb_recouv: %4d min: %5.2lf max: %5.2lf mean: %5.2lf\n",nb_recouv,Recouvrement_x.min[zi],Recouvrement_x.max[zi],Recouvrement_x.mean[zi]);
			}
		}
	/* debut modifdp du 12 mars 2010*/	
	if (Structure.nb_vector_tension_bar != 0)
		{
		for (zi = 1; zi<=Structure.nb_vector_tension_bar ; zi++)
			{
			el = Vector_tension_bar.bar[zi];	/*bar number*/
			int1 = Element[el].extremite[1];
			int2 = Element[el].extremite[2];
			VECT[1] = wf[3*int2-2] - wf[3*int1-2];	/*x coordinate of the vector bar*/
			VECT[2] = wf[3*int2-1] - wf[3*int1-1];
			VECT[3] = wf[3*int2-0] - wf[3*int1-0];
			amplitude = sqrt(produit_scal(VECT,VECT));	/*length of the bar*/
			dir[1] = VECT[1] / amplitude;		/*x coordinate of the direction of the bar*/
			dir[2] = VECT[2] / amplitude;
			dir[3] = VECT[3] / amplitude;
			amplitude = Element[el].wt;
			VECT[1] = dir[1] * amplitude;
			VECT[2] = dir[2] * amplitude;
			VECT[3] = dir[3] * amplitude;
			printf("tension bar %d ",el);
			printf("vector tension %lf %lf %lf ",VECT[1],VECT[2],VECT[3]);
			printf("tension %lf ",amplitude);
			printf("vector direction %lf %lf %lf \n",dir[1],dir[2],dir[3]);
			}
		}
	/* fin modifdp du 12 mars 2010*/
	if (Plan_cutting.nb_plan == 1)
		{
		printf("plan_cutting  \n");
		fprintf(f3,"plan cutting, nb nodes:	%d \n",Plan_cutting.nb_nodes);
		fprintf(f3,"           x         y         z            alpha: \n");
  		for( pa = 1 ; pa <=  Plan_cutting.nb_nodes; pa++ )
  			{
			fprintf(f3,"%12.3lf %12.3lf  %12.3lf %12.3lf  \n",Plan_cutting.x[pa],Plan_cutting.y[pa],Plan_cutting.z[pa],Plan_cutting.alpha[pa]);
  			}
		fprintf(f3," \n");
		}
	if (Structure.cut_plan_symmetry == 2)
		{
		nb_angles = 0;				/*nb of intersections*/
		for (zi = 1; zi<= NOMBRE_SURFACES; zi++)
			{
			int1 = (int) yc(zi,3)/3;	/*node number of vertex 1*/
			int2 = (int) yc(zi,6)/3;
			int3 = (int) yc(zi,9)/3;
			if ((Noeud[int1].symy == 1) && (Noeud[int2].symy == 1))		nb_angles++;
			if ((Noeud[int2].symy == 1) && (Noeud[int3].symy == 1))		nb_angles++;
			if ((Noeud[int3].symy == 1) && (Noeud[int1].symy == 1))		nb_angles++;
			}
		fprintf(f3,"%d intersections with symmetry plan Y, the coordinates of 2 nodes (m) and the angle beween twines (radian) are:\n",nb_angles);
		for (zi = 1; zi<= NOMBRE_SURFACES; zi++)
			{
			int1 = (int) yc(zi,3)/3;	/*node number of vertex 1*/
			int2 = (int) yc(zi,6)/3;
			int3 = (int) yc(zi,9)/3;
			if ((Noeud[int1].symy == 1) && (Noeud[int2].symy == 1))
				{ 
				nb_angles++;			
				UU[1] = Surface[zi].nx;  	UU[2] = Surface[zi].ny;  	UU[3] = Surface[zi].nz;		/*U twine vector*/
  				VV[1] = Surface[zi].mx;  	VV[2] = Surface[zi].my;  	VV[3] = Surface[zi].mz;
  				NUU = sqrt(produit_scal(UU,UU));	NVV = sqrt(produit_scal(VV,VV));	ps = produit_scal(UU, VV);
				alpha = acos(ps/NUU/NVV);
				fprintf(f3,"node 1: %12.3lf %12.3lf  %12.3lf node 2: %12.3lf %12.3lf %12.3lf  ",wf[3*int1-2],wf[3*int1-1],wf[3*int1-0],wf[3*int2-2],wf[3*int2-1],wf[3*int2-0]);
				fprintf(f3,"angle: %12.3lf\n",alpha);
				}
			if ((Noeud[int2].symy == 1) && (Noeud[int3].symy == 1))
				{
				UU[1] = Surface[zi].nx;  	UU[2] = Surface[zi].ny;  	UU[3] = Surface[zi].nz;		/*U twine vector*/
  				VV[1] = Surface[zi].mx;  	VV[2] = Surface[zi].my;  	VV[3] = Surface[zi].mz;
  				NUU = sqrt(produit_scal(UU,UU));	NVV = sqrt(produit_scal(VV,VV));	ps = produit_scal(UU, VV);
				alpha = acos(ps/NUU/NVV);
				fprintf(f3,"node 1: %12.3lf %12.3lf  %12.3lf node 2: %12.3lf %12.3lf %12.3lf  ",wf[3*int2-2],wf[3*int2-1],wf[3*int2-0],wf[3*int3-2],wf[3*int3-1],wf[3*int3-0]);
				fprintf(f3,"angle: %12.3lf\n",alpha);
				}
			if ((Noeud[int3].symy == 1) && (Noeud[int1].symy == 1))
				{
				UU[1] = Surface[zi].nx;  	UU[2] = Surface[zi].ny;  	UU[3] = Surface[zi].nz;		/*U twine vector*/
  				VV[1] = Surface[zi].mx;  	VV[2] = Surface[zi].my;  	VV[3] = Surface[zi].mz;
  				NUU = sqrt(produit_scal(UU,UU));	NVV = sqrt(produit_scal(VV,VV));	ps = produit_scal(UU, VV);
				alpha = acos(ps/NUU/NVV);
				fprintf(f3,"node 1: %12.3lf %12.3lf  %12.3lf node 2: %12.3lf %12.3lf %12.3lf  ",wf[3*int3-2],wf[3*int3-1],wf[3*int3-0],wf[3*int1-2],wf[3*int1-1],wf[3*int1-0]);
				fprintf(f3,"angle: %12.3lf\n",alpha);
				}
			}
		}
  	if(Orientation_netting.nb_panel > 0)
    		{
	      	orientation_netting();
	  	fprintf(f3,"Mesh number by panel and by orientation of the normal of the netting relatively to the flow, nb of panels: %d, angle step (deg): %lf \n",Orientation_netting.nb_panel,Orientation_netting.pas);
		for (pa = 1 ; pa <= Orientation_netting.nb_panel ; pa++)
			{
	  		fprintf(f3,"panel: %d      ",Orientation_netting.panel[pa]);
			for (elem = 1 ; elem <= Orientation_netting.nb_tab ; elem++)
				{
	  			fprintf(f3," %lf",Orientation_netting.tab_mesh[pa][elem]);
   				}
	  		fprintf(f3,"\n");
			} 		
	  	fprintf(f3,"Netting surface (m^2) by panel and by orientation of the normal of the netting relatively to the flow, nb of panels: %d, angle step (deg): %lf \n",Orientation_netting.nb_panel,Orientation_netting.pas);
		for (pa = 1 ; pa <= Orientation_netting.nb_panel ; pa++)
			{
	  		fprintf(f3,"panel: %d      ",Orientation_netting.panel[pa]);
			for (elem = 1 ; elem <= Orientation_netting.nb_tab ; elem++)
				{
	  			fprintf(f3," %lf",Orientation_netting.tab_netting[pa][elem]);
   				}
	  		fprintf(f3,"\n");
			} 		
	  	fprintf(f3,"Drag (N) by panel and by orientation of the normal of the netting relatively to the flow, nb of panels: %d, angle step (deg): %lf \n",Orientation_netting.nb_panel,Orientation_netting.pas);
		for (pa = 1 ; pa <= Orientation_netting.nb_panel ; pa++)
			{
	  		fprintf(f3,"panel: %d      ",Orientation_netting.panel[pa]);
			for (elem = 1 ; elem <= Orientation_netting.nb_tab ; elem++)
				{
	  			fprintf(f3," %lf",Orientation_netting.tab_drag[pa][elem]);
   				}
	  		fprintf(f3,"\n");
			} 		
    		}
  	if(Grid_drag.pas > 0.0)
    		{
		
		printf("drag grid with a step of %lf m along y and z axis (N/m²)\n",Grid_drag.pas);
		miny = Noeud[1].y;	maxy = Noeud[1].y;
		minz = Noeud[1].z;	maxz = Noeud[1].z;
		for (zi = 1; zi<= NOMBRE_NOEUDS; zi++)
			{
			if (miny > Noeud[zi].y)	miny = Noeud[zi].y;
			if (maxy < Noeud[zi].y)	maxy = Noeud[zi].y;
			if (minz > Noeud[zi].z)	minz = Noeud[zi].z;
			if (maxz < Noeud[zi].z)	maxz = Noeud[zi].z;
			}
		nby = (int) ceil((maxy-miny)/Grid_drag.pas);
		nbz = (int) ceil((maxz-minz)/Grid_drag.pas);
		printf("miny = %lf; maxy = %lf; minz = %lf; maxz = %lf;\n",miny, maxy, minz, maxz);
		printf("nby = %d; nbz = %d;\n",nby,nbz);
	  	fprintf(f3,"Grid of drag along y and z (N/m^2)           \n");
	  	fprintf(f3,"miny: %lf m   minz: %lf m            \n",miny,minz);
	  	fprintf(f3,"nby: %d      nbz: %d      \n",nby,nbz);
	  	fprintf(f3,"step along y and z: %lf m   \n",Grid_drag.pas);
		
		/*debut allocation de la matrice Grid_drag.tab*/
		n_ligne 	= nby + 1;
		p_colonne 	= nbz + 1;
		xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
		Grid_drag.tab = (double **) malloc (n_ligne * sizeof(double *));	if (Grid_drag.tab == NULL){printf("Grid_drag.tab = NULL \n" );exit(0);}
		cmat = xmat;
		for (zi=0;zi<n_ligne;zi++)
			{
			Grid_drag.tab[zi] = cmat;
			cmat += p_colonne;
			}
		for (zl = 1; zl<= nby; zl++)
			{
			for (zc = 1; zc<= nbz; zc++)
				{
				Grid_drag.tab[zl][zc] = 0.0;
				}
			}
		/*fin allocation de la matrice Grid_drag.tab*/

		/******DEB NETTING*************************************************************/
		for (zi = 1; zi<= NOMBRE_SURFACES; zi++)
			{
			int1 = (int) yc(zi,3)/3;	/*node number of vertex 1*/
			int2 = (int) yc(zi,6)/3;
			int3 = (int) yc(zi,9)/3;
			//Noeud[int1].x
			y1 = Noeud[int1].y;	z1 = Noeud[int1].z;
			y2 = Noeud[int2].y;	z2 = Noeud[int2].z;
			y3 = Noeud[int3].y;	z3 = Noeud[int3].z;
			//printf("y1 = [ %lf  %lf  %lf]; z1 = [%lf %lf %lf]; ",y1,y2,y3,z1,z2,z3);	printf("y2 = [y1 y1(1)];    z2 = [z1 z1(1)];    plot2d(y2,z2,1)\n");			
			surface_totale = surface_triangle2(0.0, y1, z1, 0.0, y2, z2, 0.0, y3, z3);
			//printf("surface_totale %lf\n",surface_totale);
			
			
			for (zl = 1; zl<= nby; zl++)
				{
				for (zc = 1; zc<= nbz; zc++)
					{
					surface_coupee = 0.0;
					/**********************************************************************************/

					yplus = miny + (zl-1) * Grid_drag.pas; ymoins = yplus + Grid_drag.pas;
					zplus = minz + (zc-1) * Grid_drag.pas; zmoins = zplus + Grid_drag.pas;
				
					nb_triangle_plus_y =  cut_triangle_plus_y(yplus, y1, z1, y2, z2, y3, z3, &y4 ,&z4, &y5 ,&z5, &y6 ,&z6, &y7 ,&z7, &y8 ,&z8, &y9 ,&z9);
					if (nb_triangle_plus_y == 1)
						{
						//printf("y4 = [ %lf  %lf  %lf]; z4 = [%lf %lf %lf]; ",y4,y5,y6,z4,z5,z6);	printf("y5 = [y4 y4(1)];    z5 = [z4 z4(1)];    plot2d(y5,z5,4)\n");
						nb_triangle_plus_z =  cut_triangle_plus_z(zplus, y4, z4, y5, z5, y6, z6, &y10 ,&z10, &y11 ,&z11, &y12 ,&z12, &y13 ,&z13, &y14 ,&z14, &y15 ,&z15);
						if (nb_triangle_plus_z == 1)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						if (nb_triangle_plus_z == 2)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("nb_triangle %d\n",nb_triangle);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							//printf("y13 = [ %lf  %lf  %lf]; z13 = [%lf %lf %lf]; ",y13,y14,y15,z13,z14,z15);	printf("y14 = [y13 y13(1)];    z14 = [z13 z13(1)];    plot2d(y14,z14,6)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y13, z13, y14, z14, y15, z15, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("nb_triangle %d\n",nb_triangle);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						}
					if (nb_triangle_plus_y == 2)
						{
						//printf("y4 = [ %lf  %lf  %lf]; z4 = [%lf %lf %lf]; ",y4,y5,y6,z4,z5,z6);	printf("y5 = [y4 y4(1)];    z5 = [z4 z4(1)];    plot2d(y5,z5,4)\n");
						nb_triangle_plus_z =  cut_triangle_plus_z(zplus, y4, z4, y5, z5, y6, z6, &y10 ,&z10, &y11 ,&z11, &y12 ,&z12, &y13 ,&z13, &y14 ,&z14, &y15 ,&z15);
						if (nb_triangle_plus_z == 1)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("anb_triangle %d\n",nb_triangle);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						if (nb_triangle_plus_z == 2)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("anb_triangle %d\n",nb_triangle);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							//printf("y13 = [ %lf  %lf  %lf]; z13 = [%lf %lf %lf]; ",y13,y14,y15,z13,z14,z15);	printf("y14 = [y13 y13(1)];    z14 = [z13 z13(1)];    plot2d(y14,z14,6)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y13, z13, y14, z14, y15, z15, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("nb_triangle %d\n",nb_triangle);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						//printf("y7 = [ %lf  %lf  %lf]; z7 = [%lf %lf %lf]; ",y7,y8,y9,z7,z8,z9);	printf("y8 = [y7 y7(1)];    z8 = [z7 z7(1)];    plot2d(y8,z8,4)\n");
						nb_triangle_plus_z =  cut_triangle_plus_z(zplus, y7, z7, y8, z8, y9, z9, &y10 ,&z10, &y11 ,&z11, &y12 ,&z12, &y13 ,&z13, &y14 ,&z14, &y15 ,&z15);
						if (nb_triangle_plus_z == 1)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("anb_triangle %d\n",nb_triangle);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						if (nb_triangle_plus_z == 2)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("anb_triangle %d\n",nb_triangle);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							//printf("y13 = [ %lf  %lf  %lf]; z13 = [%lf %lf %lf]; ",y13,y14,y15,z13,z14,z15);	printf("y14 = [y13 y13(1)];    z14 = [z13 z13(1)];    plot2d(y14,z14,6)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y13, z13, y14, z14, y15, z15, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("nb_triangle %d\n",nb_triangle);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
							nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						}
					Grid_drag.tab[zl][zc] += surface_coupee/surface_totale*Surface[zi].panel_drag/Grid_drag.pas/Grid_drag.pas;
					//Grid_drag.tab[zl][zc] += surface_coupee;
					//printf("zl %d zc %d surface_coupee %lf\n",zl,zc,surface_coupee);
					/**********************************************************************************/
					}
				}
			}
		/******FIN NETTING*************************************************************/
		/******DEB DOOR*************************************************************/
			
			
		double drag_door;
		int typ_noeud;

		drag_door = 0.0;
		for (zu = 1; zu<= Grid_drag.nb_type_point; zu++)
			{
			typ_noeud = Grid_drag.type_point[zu];
			drag_door = drag_door + TypeNoeud[typ_noeud].fextx;
			}
			
		for (zi = 1; zi<= Grid_drag.nb_triangle; zi++)
			{
			int1 = fixa[Grid_drag.vertex[3*zi-2]];	/*node number of vertex 1*/
			int2 = fixa[Grid_drag.vertex[3*zi-1]];
			int3 = fixa[Grid_drag.vertex[3*zi-0]];
			//Noeud[int1].x
			y1 = Noeud[int1].y;	z1 = Noeud[int1].z;
			y2 = Noeud[int2].y;	z2 = Noeud[int2].z;
			y3 = Noeud[int3].y;	z3 = Noeud[int3].z;


			//printf("type noeuds = [ %d  %d  %d]\n ",Noeud[int1].type,Noeud[int2].type,Noeud[int3].type);
			//printf("y1 = [ %lf  %lf  %lf]; z1 = [%lf %lf %lf]; \n",y1,y2,y3,z1,z2,z3);
			//printf("y1 = [ %lf  %lf  %lf]; z1 = [%lf %lf %lf]; ",y1,y2,y3,z1,z2,z3);	printf("y2 = [y1 y1(1)];    z2 = [z1 z1(1)];    plot2d(y2,z2,1)\n");			
			surface_totale = surface_triangle2(0.0, y1, z1, 0.0, y2, z2, 0.0, y3, z3);
			//printf("surface_totale %lf\n",surface_totale);
			
			
			for (zl = 1; zl<= nby; zl++)
			//for (zl = 27; zl<= 27; zl++)
				{
				for (zc = 1; zc<= nbz; zc++)
				//for (zc = 1; zc<= 2; zc++)
					{
					surface_coupee = 0.0;
					/**********************************************************************************/

					yplus = miny + (zl-1) * Grid_drag.pas; ymoins = yplus + Grid_drag.pas;
					zplus = minz + (zc-1) * Grid_drag.pas; zmoins = zplus + Grid_drag.pas;
					//printf("yplus %lf  ymoins %lf  zplus %lf  zmoins %lf  \n",yplus,ymoins,zplus,zmoins);
				
					nb_triangle_plus_y =  cut_triangle_plus_y(yplus, y1, z1, y2, z2, y3, z3, &y4 ,&z4, &y5 ,&z5, &y6 ,&z6, &y7 ,&z7, &y8 ,&z8, &y9 ,&z9);
					if (nb_triangle_plus_y == 1)
						{
						//printf("y4 = [ %lf  %lf  %lf]; z4 = [%lf %lf %lf]; ",y4,y5,y6,z4,z5,z6);	printf("y5 = [y4 y4(1)];    z5 = [z4 z4(1)];    plot2d(y5,z5,4)\n");
						nb_triangle_plus_z =  cut_triangle_plus_z(zplus, y4, z4, y5, z5, y6, z6, &y10 ,&z10, &y11 ,&z11, &y12 ,&z12, &y13 ,&z13, &y14 ,&z14, &y15 ,&z15);
						if (nb_triangle_plus_z == 1)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						if (nb_triangle_plus_z == 2)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("nb_triangle_moin_y %d\n",nb_triangle_moin_y);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							//printf("y13 = [ %lf  %lf  %lf]; z13 = [%lf %lf %lf]; ",y13,y14,y15,z13,z14,z15);	printf("y14 = [y13 y13(1)];    z14 = [z13 z13(1)];    plot2d(y14,z14,6)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y13, z13, y14, z14, y15, z15, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("nb_triangle_moin_y %d\n",nb_triangle_moin_y);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						}
					if (nb_triangle_plus_y == 2)
						{
						//printf("y4 = [ %lf  %lf  %lf]; z4 = [%lf %lf %lf]; ",y4,y5,y6,z4,z5,z6);	printf("y5 = [y4 y4(1)];    z5 = [z4 z4(1)];    plot2d(y5,z5,4)\n");
						nb_triangle_plus_z =  cut_triangle_plus_z(zplus, y4, z4, y5, z5, y6, z6, &y10 ,&z10, &y11 ,&z11, &y12 ,&z12, &y13 ,&z13, &y14 ,&z14, &y15 ,&z15);
						if (nb_triangle_plus_z == 1)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("anb_triangle_moin_y %d\n",nb_triangle_moin_y);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						if (nb_triangle_plus_z == 2)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("anb_triangle_moin_y %d\n",nb_triangle_moin_y);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							//printf("y13 = [ %lf  %lf  %lf]; z13 = [%lf %lf %lf]; ",y13,y14,y15,z13,z14,z15);	printf("y14 = [y13 y13(1)];    z14 = [z13 z13(1)];    plot2d(y14,z14,6)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y13, z13, y14, z14, y15, z15, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("nb_triangle_moin_y %d\n",nb_triangle_moin_y);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						//printf("y7 = [ %lf  %lf  %lf]; z7 = [%lf %lf %lf]; ",y7,y8,y9,z7,z8,z9);	printf("y8 = [y7 y7(1)];    z8 = [z7 z7(1)];    plot2d(y8,z8,4)\n");
						nb_triangle_plus_z =  cut_triangle_plus_z(zplus, y7, z7, y8, z8, y9, z9, &y10 ,&z10, &y11 ,&z11, &y12 ,&z12, &y13 ,&z13, &y14 ,&z14, &y15 ,&z15);
						if (nb_triangle_plus_z == 1)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("anb_triangle_moin_y %d\n",nb_triangle_moin_y);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						if (nb_triangle_plus_z == 2)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y10, z10, y11, z11, y12, z12, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("anb_triangle_moin_y %d\n",nb_triangle_moin_y);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							//printf("y13 = [ %lf  %lf  %lf]; z13 = [%lf %lf %lf]; ",y13,y14,y15,z13,z14,z15);	printf("y14 = [y13 y13(1)];    z14 = [z13 z13(1)];    plot2d(y14,z14,6)\n");
							nb_triangle_moin_y =  cut_triangle_moin_y(ymoins, y13, z13, y14, z14, y15, z15, &y16 ,&z16, &y17 ,&z17, &y18 ,&z18, &y19 ,&z19, &y20 ,&z20, &y21 ,&z21);
							//printf("nb_triangle_moin_y %d\n",nb_triangle_moin_y);
							if (nb_triangle_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							if (nb_triangle_moin_y == 2)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y16, z16, y17, z17, y18, z18, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								//printf("y19 = [ %lf  %lf  %lf]; z19 = [%lf %lf %lf]; ",y19,y20,y21,z19,z20,z21);	printf("y20 = [y19 y19(1)];    z20 = [z19 z19(1)];    plot2d(y20,z20,7)\n");
								nb_triangle_moin_z =  cut_triangle_moin_z(zmoins, y19, z19, y20, z20, y21, z21, &y22 ,&z22, &y23 ,&z23, &y24 ,&z24, &y25 ,&z25, &y26 ,&z26, &y27 ,&z27);
								if (nb_triangle_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									}
								if (nb_triangle_moin_z == 2)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y22, z22, 0.0, y23, z23, 0.0, y24, z24);
									//printf("y25 = [ %lf  %lf  %lf]; z25 = [%lf %lf %lf]; ",y25,y26,y27,z25,z26,z27);		printf("y26 = [y25 y25(1)];    z26 = [z25 z25(1)];    plot2d(y26,z26,2)\n");
									surface_coupee = surface_coupee + surface_triangle2(0.0, y25, z25, 0.0, y26, z26, 0.0, y27, z27);
									}
								}
							}
						}
					Grid_drag.tab[zl][zc] += surface_coupee/surface_totale*(drag_door/Grid_drag.nb_triangle)/Grid_drag.pas/Grid_drag.pas;
					if (surface_coupee != 0.0)
						{
						//printf("zl %d zc %d surface_coupee %lf surface_totale %lf drag_door %lf drag_pas %lf tab %lf\n",zl,zc,surface_coupee,surface_totale,drag_door,Grid_drag.pas,Grid_drag.tab[zl][zc]);
						}
					//Grid_drag.tab[zl][zc] += surface_coupee/surface_totale*Surface[zi].panel_drag/Grid_drag.pas/Grid_drag.pas;
					//Grid_drag.tab[zl][zc] += surface_coupee;
					//printf("zl %d zc %d surface_coupee %lf\n",zl,zc,surface_coupee);
					/**********************************************************************************/
					}
				}
			}			
			
		/******FIN DOOR*************************************************************/
		/******DEB CABLE*************************************************************/
		for (zi = 1; zi<= NOMBRE_ELEMENTS; zi++)
			{
			int1 = (int) yb(zi,3)/3;	/*node number of extremity 1*/
			int2 = (int) yb(zi,6)/3;
			//Noeud[int1].x
			y1 = Noeud[int1].y;	z1 = Noeud[int1].z;
			y2 = Noeud[int2].y;	z2 = Noeud[int2].z;
			//printf("y1 = [ %lf  %lf]; z1 = [%lf %lf]; ",y1,y2,z1,z2);	printf("y2 = [y1 y1(1)];    z2 = [z1 z1(1)];    plot2d(y2,z2,1)\n");			
			longueur_totale = longueur_segment2(0.0, y1, z1, 0.0, y2, z2);
			//printf("longueur_totale %lf\n",longueur_totale);
			
			
			for (zl = 1; zl<= nby; zl++)
				{
				for (zc = 1; zc<= nbz; zc++)
					{
					longueur_coupee = 0.0;
					/**********************************************************************************/

					yplus = miny + (zl-1) * Grid_drag.pas; ymoins = yplus + Grid_drag.pas;
					zplus = minz + (zc-1) * Grid_drag.pas; zmoins = zplus + Grid_drag.pas;
				
					nb_segment_plus_y =  cut_segment_plus_y(yplus, y1, z1, y2, z2, &y4 ,&z4, &y5 ,&z5);
					if (nb_segment_plus_y == 1)
						{
						//printf("y4 = [ %lf  %lf  %lf]; z4 = [%lf %lf %lf]; ",y4,y5,y6,z4,z5,z6);	printf("y5 = [y4 y4(1)];    z5 = [z4 z4(1)];    plot2d(y5,z5,4)\n");
						nb_segment_plus_z =  cut_segment_plus_z(zplus, y4, z4, y5, z5, &y10 ,&z10, &y11 ,&z11);
						if (nb_segment_plus_z == 1)
							{
							//printf("y10 = [ %lf  %lf  %lf]; z10 = [%lf %lf %lf]; ",y10,y11,y12,z10,z11,z12);	printf("y11 = [y10 y10(1)];    z11 = [z10 z10(1)];    plot2d(y11,z11,5)\n");
							nb_segment_moin_y =  cut_segment_moin_y(ymoins, y10, z10, y11, z11, &y16 ,&z16, &y17 ,&z17);
							if (nb_segment_moin_y == 1)
								{
								//printf("y16 = [ %lf  %lf  %lf]; z16 = [%lf %lf %lf]; ",y16,y17,y18,z16,z17,z18);	printf("y17 = [y16 y16(1)];    z17 = [z16 z16(1)];    plot2d(y17,z17,7)\n");
								nb_segment_moin_z =  cut_segment_moin_z(zmoins, y16, z16, y17, z17, &y22 ,&z22, &y23 ,&z23);
								if (nb_segment_moin_z == 1)
									{
									//printf("y22 = [ %lf  %lf  %lf]; z22 = [%lf %lf %lf]; ",y22,y23,y24,z22,z23,z24);		printf("y23 = [y22 y22(1)];    z23 = [z22 z22(1)];    plot2d(y23,z23,1)\n");
									longueur_coupee = longueur_coupee + longueur_segment2(0.0, y22, z22, 0.0, y23, z23);
									}
								}
							}
						}
					Grid_drag.tab[zl][zc] += longueur_coupee/longueur_totale*Element[zi].cable_drag/Grid_drag.pas/Grid_drag.pas;
					if (longueur_coupee != 0.0)
						{
						//printf("zl %d zc %d longueur_coupee %lf\n",zl,zc,longueur_coupee);
						}
					/**********************************************************************************/
					}
				}
			}
		/******FIN CABLE*************************************************************/
			
			
			
	  	fprintf(f3,"tab:      \n");
		//printf("tab = [");
		for (zl = 1; zl<= nby; zl++)
			{
			for (zc = 1; zc<= nbz; zc++)
				{
				//printf(" %7.5lf",Grid_drag.tab[zl][zc]);
				}
			//printf("\n");
			}
		//printf("];\n");
		for (zl = 1; zl<= nby; zl++)
			{
			for (zc = 1; zc<= nbz; zc++)
				{
	  			fprintf(f3," %7.5lf",Grid_drag.tab[zl][zc]);
				}
	  		fprintf(f3,"\n");
			}
		for (zi = 1; zi<= NOMBRE_SURFACES; zi++)
			{
			//printf(" %7.0lf",Surface[zi].panel_drag);
			}
    		}
	if (Foot_print.nb == -1)
		{
		printf("foooot_print\n");
		Foot_print.nb = 0;
	  	for (elem = 1 ; elem<= NOMBRE_NOEUDS ; elem++) 
	  		{
			if ((whs[3*elem-0] == 1) && (wf[3*elem-0] < wh[3*elem-0]))
				{
				Foot_print.nb++;
				}
	  		}
		fprintf(f3,"Foot_print.nb:  %5d\n",Foot_print.nb);
		fprintf(f3,"y(m)	delta z(m):  \n");
	  	for (elem = 1 ; elem<= NOMBRE_NOEUDS ; elem++) 
	  		{
			if ((whs[3*elem-0] == 1) && (wf[3*elem-0] < wh[3*elem-0]))
				{
				Foot_print.nb++;
		    		fprintf(f3,"  %17.9lf",wf[3*elem-1]);
		    		fprintf(f3,"  %17.9lf",wh[3*elem-0]-wf[3*elem-0]);
				fprintf(f3,"\n");
				}
	  		}
		}
	if (Structure.eigenvalues > 0)
		{
		fprintf(f3,"Eigenvalues:  %5d\n",Structure.eigenvalues);
		float *d_jacobi_result,**v_jacobi_result;
		int n_jacobi_result;
		n_jacobi_result = 3*NOMBRE_NOEUDS;
		v_jacobi_result = matrix(1,n_jacobi_result,1,Structure.eigenvalues);
		d_jacobi_result = vector(1,n_jacobi_result);
  		symetrie2();
      		modification4();
      		jacobi_environ(d_jacobi_result,v_jacobi_result);
		fprintf(f3,"Eigen periods (s) :\n");
		for (zu=1;zu<=Structure.eigenvalues;zu++)
			{
			fprintf(f3,"%12.5f ",d_jacobi_result[zu]);
			}
		fprintf(f3,"\n");
		fprintf(f3,"Eigen vectors (m) :\n");
		for (zu=1;zu<=n_jacobi_result;zu++)
			{
			for (zv=1;zv<=Structure.eigenvalues;zv++)
				{
				fprintf(f3,"%12.5f ",v_jacobi_result[zu][zv]);
				}
			fprintf(f3,"\n");
			}
		}
	if (Sortie_texte.triangle_drag == 1)
		{
		fprintf(f3,"Drag of triangles (N) Hydrodynamic amplitude force of triangles (N): \n");
  		for (pa = 1 ; pa<= NOMBRE_SURFACES ; pa++) 
			{
			fprintf(f3,"%d		%lf	%lf\n",pa,Surface[pa].panel_drag,Surface[pa].panel_dragxyz);
			}
		}
	if (Prise.angle_tensions > 0)
		{
		fprintf(f3,"At the front of the catch. ");
		fprintf(f3,"angle between twines (deg.): %8.2lf ",Prise.angle_twines/(Prise.angle_tensions-1));
		fprintf(f3,"tension in twine u (N): %10.2lf ",Prise.tension_u/(Prise.angle_tensions-1));
		fprintf(f3,"tension in twine v (N): %10.2lf\n",Prise.tension_v/(Prise.angle_tensions-1));
		}
	if (Structure.ballast_altitude == 1)
		{
		printf("There is record a record of the ballasts altitude in sta file.\n");
		for (zi = 1; zi<=Structure.nb_ballast; zi++)
			{
			fprintf(f3,"ballast: %4d, altitude: %10.3lf (m)\n",zi,Ballast[zi].altitude);
			printf("ballast: %4d, altitude: %10.3lf (m)\n",zi,Ballast[zi].altitude);
			}
		}		
	if (Structure.total_mass != 0.0)
		{
	 	Structure.total_mass = 0.0;
	  	for (zi = 1 ; zi<= NOMBRE_ELEMENTS ; zi++) 
	  		{
	 		value = Element[zi].mass/ 2.0;
			//printf("value %lf \n",value);
 	 		//extremity 1
	 		x1 = (Structure.x_g*Structure.total_mass + wf[yb(zi,1)]*value) / (Structure.total_mass+value);
	 		y1 = (Structure.y_g*Structure.total_mass + wf[yb(zi,2)]*value) / (Structure.total_mass+value);
	 		z1 = (Structure.z_g*Structure.total_mass + wf[yb(zi,3)]*value) / (Structure.total_mass+value);
	 		Structure.total_mass += value;
	 		Structure.x_g = x1;
	 		Structure.y_g = y1;
	 		Structure.z_g = z1;
	 		//extremity 2
	 		x1 = (Structure.x_g*Structure.total_mass + wf[yb(zi,4)]*value) / (Structure.total_mass+value);
	 		y1 = (Structure.y_g*Structure.total_mass + wf[yb(zi,5)]*value) / (Structure.total_mass+value);
	 		z1 = (Structure.z_g*Structure.total_mass + wf[yb(zi,6)]*value) / (Structure.total_mass+value);
	 		Structure.total_mass += value;
	 		Structure.x_g = x1;
	 		Structure.y_g = y1;
	 		Structure.z_g = z1;
			}
		if (Structure.nb_ballast > 0)
			{
			for( zk = 1 ; zk <= NOMBRE_NOEUDS ; zk++ )
				{
				if (Noeud[zk].volume_ballast > 0.0)
					{
					value = Noeud[zk].volume_ballast * RHO;
					//printf("zk %4d volume_ballast %lf\n",zk,Noeud[int1].volume_ballast);
			 		x1 = (Structure.x_g*Structure.total_mass + wf[3*zk-2]*value) / (Structure.total_mass+value);
			 		y1 = (Structure.y_g*Structure.total_mass + wf[3*zk-1]*value) / (Structure.total_mass+value);
			 		z1 = (Structure.z_g*Structure.total_mass + wf[3*zk-0]*value) / (Structure.total_mass+value);
			 		Structure.total_mass += value;
			 		Structure.x_g = x1;
			 		Structure.y_g = y1;
			 		Structure.z_g = z1;
					}
				}
			}
			
		for (zi = 1 ; zi<= NOMBRE_ELEMENTS ; zi++) 
	  		{
			if (TypeElement[Element[zi].type].noeud_trainee == 1) //volume des barres reporté dans des cubes centrés sur les 2 extremités de la barre
				{
				//extremite 1
				value = Element[zi].lcube * Element[zi].lcube * Element[zi].lcube * Element[zi].pondFS[1];
		 		x1 = (Structure.x_p*Structure.total_volume_floatability + wf[yb(zi,1)]*value) / (Structure.total_volume_floatability+value);
		 		y1 = (Structure.y_p*Structure.total_volume_floatability + wf[yb(zi,2)]*value) / (Structure.total_volume_floatability+value);
		 		z1 = (Structure.z_p*Structure.total_volume_floatability + wf[yb(zi,3)]*value) / (Structure.total_volume_floatability+value);
		 		Structure.total_volume_floatability += value;
		 		Structure.x_p = x1;
		 		Structure.y_p = y1;
		 		Structure.z_p = z1;
				//extremite 2
				value = Element[zi].lcube * Element[zi].lcube * Element[zi].lcube * Element[zi].pondFS[2];
		 		x1 = (Structure.x_p*Structure.total_volume_floatability + wf[yb(zi,4)]*value) / (Structure.total_volume_floatability+value);
		 		y1 = (Structure.y_p*Structure.total_volume_floatability + wf[yb(zi,5)]*value) / (Structure.total_volume_floatability+value);
		 		z1 = (Structure.z_p*Structure.total_volume_floatability + wf[yb(zi,6)]*value) / (Structure.total_volume_floatability+value);
		 		Structure.total_volume_floatability += value;
		 		Structure.x_p = x1;
		 		Structure.y_p = y1;
		 		Structure.z_p = z1;
				}
			}
			
			
			
					
		printf("There is record a record of the total mass its center, the floatability and its center in sta file.\n");
		printf("total mass(kg)       : %lf xg(m): %lf yg(m): %lf zg(m): %lf\n",Structure.total_mass               ,Structure.x_g,Structure.y_g,Structure.z_g);
		printf("total floatability(m3): %lf xp(m): %lf yp(m): %lf zp(m): %lf\n",Structure.total_volume_floatability,Structure.x_p,Structure.y_p,Structure.z_p);
		fprintf(f3,"total mass(kg)       : %lf xg(m): %lf yg(m): %lf zg(m): %lf\n",Structure.total_mass               ,Structure.x_g,Structure.y_g,Structure.z_g);
		fprintf(f3,"total floatability(m3): %lf xp(m): %lf yp(m): %lf zp(m): %lf\n",Structure.total_volume_floatability,Structure.x_p,Structure.y_p,Structure.z_p);
		}
	if (Structure.netting_volume_calculation == 1)
		{
		double volumefront,surfacefront;
		surface_volume(Structure.front_netting_volume, &surfacefront, &volumefront);
		fprintf(f3,"surface front(m2): %lf  ",surfacefront);
		fprintf(f3,"netting_volume(m3): %lf \n",volumefront);
		printf("surfacefront             %lf  m²\n",surfacefront);
		printf("Structure.netting_volume %lf  m³\n",volumefront);
		}
  	fclose(f3);	//.sta
//sta file/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  	
//hyd file/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (Structure.hydro_forces == 1)
		{
		printf("Structure.hydro_forces = %d\n",Structure.hydro_forces);
	  	strcpy(tonom,nomfichier);
		j=strlen(tonom);
		while ((tonom[j])!='.' && j>0) j--;
		if (tonom[j]=='.') tonom[j]=0;
	  	strcat(tonom,".hyd");
	  	printf(" \n");
	  	printf("%s %s \n","file ",tonom);

	  	f3 = fopen(tonom,"w");
	  	/*ecriture des coordonnees a l equilibre statique dans le meme ordre que dans le fichier de donnees 
	  	ainsi que des efforts hydro aux noeuds*/
	  	for (elem = 1 ; elem<= NOMBRE_NOEUDS ; elem++) 
	  		{
	    		/*fprintf(f3,"  %5d",elem);*/
	    		fprintf(f3,"  %17.9lf",wf[3*fixa[elem]-2]);
	    		fprintf(f3,"  %17.9lf",wf[3*fixa[elem]-1]);
	    		fprintf(f3,"  %17.9lf",wf[3*fixa[elem]-0]);
	    		fprintf(f3,"  %10.3lf",Noeud[elem].fhx);
	    		fprintf(f3,"  %10.3lf",Noeud[elem].fhy);
	    		fprintf(f3,"  %10.3lf",Noeud[elem].fhz);
	    		fprintf(f3,"\n");
	  		}
	  	fclose(f3);	//.hyd
		}
//hyd file/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//tmp file/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (Structure.delta_h1 == 1)
		{
		printf("There is calculation of the total height of the structure.\n");
	  	strcpy(tonom,nomfichier);
		j=strlen(tonom);
		while ((tonom[j])!='.' && j>0) j--;
		if (tonom[j]=='.') tonom[j]=0;
	  	strcat(tonom,".tmp");
	  	printf(" \n");
	  	printf("%s %s \n","file ",tonom);
	  	//strcpy(tonom,"output");
	  	printf(" \n");
	  	printf("%s %s \n","file ",tonom);

	  	f3 = fopen(tonom,"w");
	  	/*write heigth of the structure*/
	  	Structure.delta_h2;
	  	for (zu = 1 ; zu<= NOMBRE_NOEUDS-1 ; zu++) 
	  		{
		  	for (zv = zu+1 ; zv<= NOMBRE_NOEUDS ; zv++) 
		  		{
		  		if (fabs(wf[3*zu]-wf[3*zv]) > Structure.delta_h2)
		  			{
		  			Structure.delta_h2 = fabs(wf[3*zu]-wf[3*zv]);
		  			}
		  		}
	  		}
	    	//fprintf(f3,"  %12.6lf\n",Structure.delta_h2);
		for (zi = 1; zi<= NOMBRE_ELEMENTS; zi++)
			{
			if (TypeElement[Element[zi].type].constant_tension == 0) 
				{	
				int1 = (int) yb(zi,3)/3;	int2 = (int) yb(zi,6)/3;	/*node number of extremity 1*/
		
				//x1 = wf[3*fixa[int1]-2];	y1 = wf[3*fixa[int1]-1];	z1 = wf[3*fixa[int1]-0];
				//x2 = wf[3*fixa[int2]-2];	y2 = wf[3*fixa[int2]-1];	z2 = wf[3*fixa[int2]-0];
				
			    	//printf("x  %12.6lf  %12.6lf  ",x1,x2);
			    	//printf("y  %12.6lf  %12.6lf  ",y1,y2);
			    	//printf("z  %12.6lf  %12.6lf\n",z1,z2);
			    	
				x1 = Noeud[int1].x;	y1 = Noeud[int1].y;	z1 = Noeud[int1].z;
				x2 = Noeud[int2].x;	y2 = Noeud[int2].y;	z2 = Noeud[int2].z;

			    	//printf("x  %12.6lf  %12.6lf  ",x1,x2);
			    	//printf("y  %12.6lf  %12.6lf  ",y1,y2);
			    	//printf("z  %12.6lf  %12.6lf\n",z1,z2);
	    	
				min_x = x1;	max_x = x1;	
				min_y = y1;	max_y = y1;	
				min_z = z1;	max_z = z1;
				}
			}
	    	//printf("max_x  %12.6lf  %12.6lf\n",max_x,min_x);
	    	//printf("max_y  %12.6lf  %12.6lf\n",max_y,min_y);
	    	//printf("max_z  %12.6lf  %12.6lf\n",max_z,min_z);
		for (zi = 1; zi<= NOMBRE_ELEMENTS; zi++)
			{
			if (TypeElement[Element[zi].type].constant_tension == 0) 
				{
				int1 = (int) yb(zi,3)/3;	int2 = (int) yb(zi,6)/3;	/*node number of extremity 1 & 2*/
		
				x1 = Noeud[int1].x;	y1 = Noeud[int1].y;	z1 = Noeud[int1].z;
				x2 = Noeud[int2].x;	y2 = Noeud[int2].y;	z2 = Noeud[int2].z;

				if (x1 < min_x) min_x = x1;	if (y1 < min_y) min_y = y1;	if (z1 < min_z) min_z = z1;
				if (x1 > max_x) max_x = x1;	if (y1 > max_y) max_y = y1;	if (z1 > max_z) max_z = z1;
				if (x2 < min_x) min_x = x2;	if (y2 < min_y) min_y = y2;	if (z2 < min_z) min_z = z2;
				if (x2 > max_x) max_x = x2;	if (y2 > max_y) max_y = y2;	if (z2 > max_z) max_z = z2;
				}
			}
		
	    	//fprintf(f3,"max_x  %12.6lf  %12.6lf  \n",max_x,min_x);
	    	//fprintf(f3,"max_y  %12.6lf  %12.6lf  \n",max_y,min_y);
	    	//fprintf(f3,"max_z  %12.6lf  %12.6lf  \n",max_z,min_z);
		fprintf(f3,"Hx:  %12.8lf  \n",max_x-min_x);
	    	fprintf(f3,"Hy:  %12.8lf  \n",max_y-min_y);
	    	fprintf(f3,"Hz:  %12.8lf  \n",max_z-min_z);
	  	fclose(f3);	//.tmp
		}
		
	if (Structure.Delta_h_v == 1)
		{
		printf("There is calculation of 2 distances on the structure.\n");
	  	strcpy(tonom,nomfichier);
		j=strlen(tonom);
		while ((tonom[j])!='.' && j>0) j--;
		if (tonom[j]=='.') tonom[j]=0;
	  	strcat(tonom,".tmp");
	  	printf(" \n");
	  	printf("%s %s \n","file ",tonom);

	  	f3 = fopen(tonom,"w");
	  	/*write heigth of the structure*/

		dx = wf[3*fixa[Structure.Delta_h2]-2] - wf[3*fixa[Structure.Delta_h1]-2];
		dy = wf[3*fixa[Structure.Delta_h2]-1] - wf[3*fixa[Structure.Delta_h1]-1];
		dz = wf[3*fixa[Structure.Delta_h2]-0] - wf[3*fixa[Structure.Delta_h1]-0];
		distance = sqrt (dx*dx + dy*dy + dz*dz);
		fprintf(f3,"distance 1:  %12.8lf  \n",distance);
		
		dx = wf[3*fixa[Structure.Delta_h4]-2] - wf[3*fixa[Structure.Delta_h3]-2];
		dy = wf[3*fixa[Structure.Delta_h4]-1] - wf[3*fixa[Structure.Delta_h3]-1];
		dz = wf[3*fixa[Structure.Delta_h4]-0] - wf[3*fixa[Structure.Delta_h3]-0];
		distance = sqrt (dx*dx + dy*dy + dz*dz);
		fprintf(f3,"distance 2:  %12.8lf  \n",distance);
	  	fclose(f3);	//.tmp
		}
//tmp file/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  	
//cuv file/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (Structure.curvature == 1)
		{
		printf("There is calculation of the curvature of the elements.\n");
	  	for (elem = 1 ; elem<= NOMBRE_NOEUDS ; elem++) 
	  		{
	  		Noeud[elem].curvature = -1.0;
	  		Noeud[elem].curvature_nb = 0;
	  		}
///////////////////////////////
//		pliage_barre_pardiso2();/**/	// flexion de barres avec angle au repos nul 			
		pliage_barre_pardiso2_3();/**/	// flexion de barres avec angle au repos nul 			
///////////////////////////////
		pliage_barre_pardiso4();/**/	// flexion de barres avec angle au repos non nul
	  	strcpy(tonom,nomfichier);
		j=strlen(tonom);
		while ((tonom[j])!='.' && j>0) j--;
		if (tonom[j]=='.') tonom[j]=0;
	  	strcat(tonom,".cuv");
	  	printf("%s %s \n","file ",tonom);

	  	/*ecriture des courbures a chaque noeud*/
	  	f3 = fopen(tonom,"w");
	    	fprintf(f3,"NOMBRE_NOEUDS =  %5d\n",NOMBRE_NOEUDS);
	    	fprintf(f3,"   node          curvature nb_nodes\n");
	  	for (elem = 1 ; elem<= NOMBRE_NOEUDS ; elem++) 
	  		{
	    		fprintf(f3,"  %5d",elem);
	    		fprintf(f3,"  %17.9lf",Noeud[elem].curvature);
	    		fprintf(f3,"  %5d",Noeud[elem].curvature_nb);
	    		fprintf(f3,"\n");
	  		}
	  	fclose(f3);	//.cuv
		}
	//cuv file/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//

            
	if (Structure.paraview == 1)
		{
		/////  paraview output /////////////////////////////////////////////////////////////////////////////////////////////////
		//
		///********************************************************************
		//vtk file elements /rig ////////////////////////////////////////////////////////////////////////////////////
		//last modified K. Breddermann 27.04.2022
		strcpy(tonom,nomfichier);
		j=strlen(tonom);
		while ((tonom[j])!='.' && j>0) j--;
		if (tonom[j]=='.') tonom[j]=0;
		strcat(tonom,"_rig.vtk");
		printf(" \n");
		//printf("%s %s \n","fichier ",tonom);

		f3 = fopen(tonom,"w");
		if (f3 < 0)
			{   
			printf("\n");
			printf("Could not open the file %s.\n",tonom);
			}
		fprintf(f3,"# vtk DataFile Version 2.0\n");
		fprintf(f3,"rig or elements\n");
		fprintf(f3,"ASCII\n");
		fprintf(f3,"\n");
		fprintf(f3,"DATASET UNSTRUCTURED_GRID\n");
		fprintf(f3,"POINTS %d float\n", NOMBRE_ELEMENTS*2);
		for (j = 1 ; j<= NOMBRE_ELEMENTS ; j++)
			{
			fprintf(f3,"%.7E  %.7E  %.7E\n",wf[3*Element[j].extremite[1]-2], wf[3*Element[j].extremite[1]-1], wf[3*Element[j].extremite[1]-0]);
			fprintf(f3,"%.7E  %.7E  %.7E\n",wf[3*Element[j].extremite[2]-2], wf[3*Element[j].extremite[2]-1], wf[3*Element[j].extremite[2]-0]);
			}
		fprintf(f3,"\n");    
		fprintf(f3,"CELLS %d %d\n", NOMBRE_ELEMENTS, 3*NOMBRE_ELEMENTS);
		zi=1;    
		for (j = 1 ; j<= NOMBRE_ELEMENTS ; j++)
			{
			fprintf(f3,"%d %d %d\n", 2, zi-1, zi);
			zi=zi+2;
			}
		fprintf(f3,"\n");    
		fprintf(f3,"CELL_TYPES %d\n", NOMBRE_ELEMENTS);
		for (j = 1 ; j<= NOMBRE_ELEMENTS ; j++)
			{
			fprintf(f3,"3\n");
			}
		fprintf(f3,"\n");
		fprintf(f3,"CELL_DATA %d\n", NOMBRE_ELEMENTS);
		fprintf(f3,"SCALARS rig_tension_in_N float 1\n");
		fprintf(f3,"LOOKUP_TABLE default\n");
		for (j = 1 ; j<= NOMBRE_ELEMENTS ; j++)
			{
			if (TypeElement[Element[j].type].constant_tension == 0)
				{
				fprintf(f3,"%8.2e\n",Element[j].wt);				//usual bar
				}
			else
				{
				if (Element[pa].wt < TypeElement[Element[j].type].tension_constant)
					{
					fprintf(f3,"%8.2e\n",Element[j].wt);				//usual bar
					}
				else
					{
					fprintf(f3,"%8.2e\n",TypeElement[Element[j].type].tension_constant);		//bar at constant tension
					}
				}        
			}
		fprintf(f3,"SCALARS element_no float 1\n");
		fprintf(f3,"LOOKUP_TABLE default\n");
		for (j = 1 ; j<= NOMBRE_ELEMENTS ; j++)
			{
			fprintf(f3,"%d\n", Element[j].type);
			}

		fclose(f3);
            
		printf("rig vtk-file %s written\n",tonom);
		//vtk file elements/rig ////////////////////////////////////////////////////////////////////////////////////
		
		
		//vtk file surfaces/body ///////////////////////////////////////////////////////////////////////////////////////////////////////
		//last modified K. Breddermann 27.04.2022
		strcpy(tonom,nomfichier);
		j=strlen(tonom);
		while ((tonom[j])!='.' && j>0) j--;
		if (tonom[j]=='.') tonom[j]=0;
		strcat(tonom,"_body.vtk");
		printf(" \n");
		//printf("%s %s \n","fichier ",tonom);

		f3 = fopen(tonom,"w");
		if (f3 < 0)
			{   
			printf("\n");
			printf("Could not open the file %s.\n",tonom);
			}
		fprintf(f3,"# vtk DataFile Version 2.0\n");
		fprintf(f3,"trawl body or surfaces\n");
		fprintf(f3,"ASCII\n");
		fprintf(f3,"\n");
		fprintf(f3,"DATASET UNSTRUCTURED_GRID\n");
		fprintf(f3,"POINTS %d float\n", NOMBRE_NOEUDS);
		for (j = 1 ; j<= NOMBRE_NOEUDS ; j++)
			{            
			fprintf(f3,"%.7E  %.7E  %.7E\n",wf[3*fixa[j]-2], wf[3*fixa[j]-1], wf[3*fixa[j]-0]);        
			}
		fprintf(f3,"\n");    
		fprintf(f3,"CELLS %d %d\n", NOMBRE_SURFACES, 4*NOMBRE_SURFACES);   
		for (j = 1 ; j<= NOMBRE_SURFACES ; j++)
			{
			fprintf(f3,"%d %d %d %d\n", 3, fixation[Surface[j].extremite[1]]-1, fixation[Surface[j].extremite[2]]-1, fixation[Surface[j].extremite[3]]-1);
			}
		//vtk point numbers start with 0, therefore fixation[Surface[j].extremite[1]]-1 
		fprintf(f3,"\n");    
		fprintf(f3,"CELL_TYPES %d\n", NOMBRE_SURFACES);
		for (j = 1 ; j<= NOMBRE_SURFACES ; j++)
			{
			fprintf(f3,"5\n");
			}
		fprintf(f3,"\n");
		fprintf(f3,"CELL_DATA %d\n", NOMBRE_SURFACES);
		fprintf(f3,"SCALARS u_tension_in_N double 1\n");
		fprintf(f3,"LOOKUP_TABLE default\n");
		for (j = 1 ; j<= NOMBRE_SURFACES ; j++)
			{
			fprintf(f3,"%g\n", Surface[j].tension1);
			}
		fprintf(f3,"SCALARS v_tension_in_N double 1\n");
		fprintf(f3,"LOOKUP_TABLE default\n");
		for (j = 1 ; j<= NOMBRE_SURFACES ; j++)
			{
			fprintf(f3,"%g\n", Surface[j].tension2);
			}
		fprintf(f3,"SCALARS panel_no int 1\n");
		fprintf(f3,"LOOKUP_TABLE default\n");
		for (j = 1 ; j<= NOMBRE_SURFACES ; j++)
			{
			fprintf(f3,"%d\n", Surface[j].type);
			}
		fprintf(f3,"SCALARS tri_element_no int \n");
		fprintf(f3,"LOOKUP_TABLE default\n");
		for (j = 1 ; j<= NOMBRE_SURFACES ; j++)
			{
			fprintf(f3,"%d\n", j);
			}
		fprintf(f3,"SCALARS solidity_diamond float 1\n");
		fprintf(f3,"LOOKUP_TABLE default\n");
		for (j = 1 ; j<= NOMBRE_SURFACES ; j++)
			{
			Sn1 = Solidity_diamond(j);
			fprintf(f3,"%4.2f\n", Sn1);
			}

		fclose(f3);
		printf("body vtk-file %s written\n",tonom);
		//****************************************************************************************/
		//for (j = 1 ; j<= NOMBRE_SURFACES+NOMBRE_ELEMENTS ; j++)
		//      {
		//      printf("%d %g\n", j, Surface[j].tension1);
		//      }

		//vtk file surfaces/body///////////////////////////////////////////////////////////////////////////////////
		}

	///// OpenFOAM output /////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (Structure.openfoam == 1)
		{
		//write stuff for openfoam, speed file dont exist, pressure file dont exist
		//stlOF();
		//meshOF();
		//porousCellSetOF();
		//porousBaffleOF();
		}
	if (Structure.openfoam == 2)
		{
		//write stuff for openfoam, speed file exists, pressure file dont exist
		//stlOF();
		//meshOF();
		//porousCellSetOF();
		//porousBaffleOF();
		}
	if (Structure.openfoam == 3)
		{
		//write stuff for openfoam, speed file dont exist, pressure file exists
		}
	if (Structure.exit_size_diamond_panel == 1)
		{
		printf("min max mean and std dev of exit_size are calculated per diamond panel\n");
	  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	  		{
			Vn[1] = Surface[elem].nx;	Vn[2] = Surface[elem].ny;	Vn[3] = Surface[elem].nz; /*u twine vector*/
			Vm[1] = Surface[elem].mx;	Vm[2] = Surface[elem].my;	Vm[3] = Surface[elem].mz; /*v twine vector*/
			norm_n = sqrt(produit_scal(Vn,Vn));	
			norm_m = sqrt(produit_scal(Vm,Vm));	
			scal = produit_scal(Vn,Vm);
			cos_gamma = scal/norm_n/norm_m;
			if (cos_gamma >  1.0) cos_gamma =  1.0;
			if (cos_gamma < -1.0) cos_gamma = -1.0;
			sin_gamma = sqrt(1.0 - cos_gamma*cos_gamma);
			dn = norm_m*sin_gamma;
			dm = norm_n*sin_gamma;
			if (dn <= dm) Surface[elem].max_exit_size = dn;
			if (dm <= dn) Surface[elem].max_exit_size = dm;
			//printf("Vn %lf %lf %lf\n",Vn[1],Vn[2],Vn[3]);
			//printf("Vm %lf %lf %lf\n",Vm[1],Vm[2],Vm[3]);
			//printf("scal %lf norm %lf %lf Surface[%3d].max_exit_size = %8.3lf \n",scal,norm_n,norm_m,elem,Surface[elem].max_exit_size);
			if (elem == 1) 
				{
				min_exit_diameter = Surface[elem].max_exit_size;
				max_exit_diameter = Surface[elem].max_exit_size;
				}
			if (min_exit_diameter > Surface[elem].max_exit_size) min_exit_diameter = Surface[elem].max_exit_size;
			if (max_exit_diameter < Surface[elem].max_exit_size) max_exit_diameter = Surface[elem].max_exit_size;
	  		}
		for (pa=1;pa<=Structure.NbTypesurf;pa++)
			{
			mean_exit = 0.0;
			nb_tri = 0;
		  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
		  		{
		  		if(Surface[elem].type == pa)
			  		{
			  		nb_tri++;
			  		if (nb_tri == 1)
			  			{
			  			min_exit = Surface[elem].max_exit_size;
			  			max_exit = Surface[elem].max_exit_size;
			  			}
			  		mean_exit+= Surface[elem].max_exit_size;
			  		if (min_exit > Surface[elem].max_exit_size) min_exit = Surface[elem].max_exit_size;
			  		if (max_exit < Surface[elem].max_exit_size) max_exit = Surface[elem].max_exit_size;
			  		}
		  		}
		  	panneau[pa].mean_exit_size = mean_exit/nb_tri;
		  	panneau[pa].min_exit_size  = min_exit;
		  	panneau[pa].max_exit_size  = max_exit;
			printf("nb_tri %4d  ",nb_tri);
			printf("mean_exit %8.3lf  ",panneau[pa].mean_exit_size);
			printf("min_exit %8.3lf  ",panneau[pa].min_exit_size);
			printf("panneau[%4d].max_exit_size = %8.3lf\n",pa,panneau[pa].max_exit_size);
			}
		for (pa=1;pa<=Structure.NbTypesurf;pa++)
			{
			std_dev = 0.0;
			nb_tri = 0;
		  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
		  		{
		  		if(Surface[elem].type == pa)
			  		{
			  		nb_tri++;
			  		std_dev+= (Surface[elem].max_exit_size - panneau[pa].mean_exit_size) * (Surface[elem].max_exit_size - panneau[pa].mean_exit_size);
			  		}
		  		}
		  	panneau[pa].std_dev_exit_size = sqrt(std_dev/nb_tri);
			//printf("panneau[%4d].std_dev_exit_size = %8.3lf\n",pa,panneau[pa].std_dev_exit_size);
			}
		for (pa=1;pa<=Structure.NbTypesurf;pa++)
			{
			printf("panel %4d  ",pa);
			printf("mean_exit %8.3lf  ",panneau[pa].mean_exit_size);
			printf("min_exit %8.3lf  ",panneau[pa].min_exit_size);
			printf("max_exit_size = %8.3lf  ",panneau[pa].max_exit_size);
			printf("std_dev_exit_size = %8.3lf\n",panneau[pa].std_dev_exit_size);
			}
		}
	}
	

