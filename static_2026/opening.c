#define PRINCIPAL 0
#include "4c19.h"

void orientation_netting()
	{
  	/*
	calculation of the orientation angle by panel relatively to the flow
	*/
	int elem,pa,ccase;
	double ps,angle_open1,angle_open,norm_n,norm_m;

  	double AlbX1,AlbX2,AlbX3,U1,V1,U2,V2,U3,V3,tmp,tmp4,tmp3,tmp2;
  	double nbmaille,nbmaille_aval,nbmaille_amont,param1,param2,tfuv[4],VV[4];
  	int zh,zi,zj,zl,zk;
	
	printf("calculation of the orientation angle by panel relatively to the flow\n");
	printf("Orientation_netting.nb_panel %d Orientation_netting.nb_tab %d\n",Orientation_netting.nb_panel,Orientation_netting.nb_tab);
   
   	/*VV orientation current*/
	VV[1] = cos(Courant.direction*PI/180.0);
	VV[2] = sin(Courant.direction*PI/180.0);
	VV[3] = 0.0;
	
	
	
	for (pa = 1 ; pa <= Orientation_netting.nb_panel ; pa++)
		{
		for (elem = 1 ; elem <= Orientation_netting.nb_tab ; elem++)
			{
			Orientation_netting.tab_mesh[pa][elem] = 0.0;
			Orientation_netting.tab_netting[pa][elem] = 0.0;
			Orientation_netting.tab_drag[pa][elem] = 0.0;
   			}
		}
	for (elem = 1 ; elem <= NOMBRE_SURFACES ; elem++)
		{
		for (pa=1;pa<=Orientation_netting.nb_panel;pa++)
			{
			if (Surface[elem].type == Orientation_netting.panel[pa])
				{
				Surface[elem].n[1] = Surface[elem].nx;	Surface[elem].n[2] = Surface[elem].ny;	Surface[elem].n[3] = Surface[elem].nz;
				Surface[elem].m[1] = Surface[elem].mx;	Surface[elem].m[2] = Surface[elem].my;	Surface[elem].m[3] = Surface[elem].mz;
				norm_n = sqrt(produit_scal(Surface[elem].n, Surface[elem].n));
				norm_m = sqrt(produit_scal(Surface[elem].m, Surface[elem].m));
				produit_vect3(Surface[elem].n, Surface[elem].m, Surface[elem].N);
				norm_n = sqrt(produit_scal(Surface[elem].N, Surface[elem].N));
				norm_m = 1/norm_n;
				produit_scal_vect(norm_m, Surface[elem].N, Surface[elem].N);
				//norm_n = sqrt(produit_scal(Surface[elem].N, Surface[elem].N));
				//norm_m = sqrt(produit_scal(VV, VV));
				//printf("elem %d norm %lf norm %lf\n",elem,norm_n,norm_m);
				
				
				ps = produit_scal(Surface[elem].N, VV);
				
							
				angle_open = 180.0  / PI * (acos(ps));
				if (angle_open >= 90.0) angle_open = 180.0 - angle_open;
				ccase = 1+(int) (angle_open / Orientation_netting.pas);
				Orientation_netting.tab_mesh[pa][ccase] = Orientation_netting.tab_mesh[pa][ccase] + Surface[elem].nb_cote_u_ou_v / 2.0;
				Orientation_netting.tab_netting[pa][ccase] = Orientation_netting.tab_netting[pa][ccase] + Surface[elem].nb_cote_u_ou_v * norm_n;
				Orientation_netting.tab_drag[pa][ccase] = Orientation_netting.tab_drag[pa][ccase] + Surface[elem].panel_drag;
				/*printf("elem %d angle_open %lf ccase %d\n",elem,angle_open,ccase);*/
				}
			}
		}
	}
	
	
	
	
	
	
void opening_mesh()
	{
  	/*
	calculation of the opening mesh by panel
	*/
	
	int elem,pa,pan,ccase;
	double ps,mesh_open1,mesh_open,norm_n,norm_m;

  	double AlbX1,AlbX2,AlbX3,U1,V1,U2,V2,U3,V3,tmp,tmp4,tmp3,tmp2;
  	double nbmaille,nbmaille_aval,nbmaille_amont,param1,param2,tfuv[4],normal_vector[4],surface_mesh;
  	int zh,zi,zj,zl,zk;
	
	printf("calculation of the opening mesh by panel\n");
   
	Opening_mesh.nb_tab = 0;
	/*allocation de la matrice tab*/
	Opening_mesh.tab = (double **) malloc ((Opening_mesh.nb_panel+1) * sizeof(double *));	if (Opening_mesh.tab	 == NULL){printf("Opening_mesh.tab	= NULL \n" );exit(0);}
	for (pa = 1 ; pa <= Opening_mesh.nb_panel ; pa++)
		{
		Opening_mesh.tab[pa] = (double *) Malloc_double (Opening_mesh.nb_tab+1);	
		}

	if (Prise.volume > Prise.seuil) 
		{
  		changement_variable_catch();		/* met l axe des X dans le sens du courant et le plan Y0Z tel que Z soit vertical ascendant*/
  		for ( elem = 1 ; elem <= NOMBRE_SURFACES ; elem++ )
  			{
			nbmaille = nb_maille_devant( elem,Prise.front );

			for (pa=1;pa<=Opening_mesh.nb_panel;pa++)
				{
				if (Surface[elem].type == Opening_mesh.panel[pa])
					{
					Surface[elem].n[1] = Surface[elem].nx;	Surface[elem].n[2] = Surface[elem].ny;	Surface[elem].n[3] = Surface[elem].nz;
					Surface[elem].m[1] = Surface[elem].mx;	Surface[elem].m[2] = Surface[elem].my;	Surface[elem].m[3] = Surface[elem].mz;
					produit_vect3(Surface[elem].n, Surface[elem].m, normal_vector);
					surface_mesh = sqrt(produit_scal(normal_vector,normal_vector));
					ccase = 1 + (int) (surface_mesh / Opening_mesh.pas);
					/*printf("elem %d surface_mesh %lf Opening_mesh.pas %lf ccase %d ",elem,surface_mesh,Opening_mesh.pas,ccase);
					printf("n %lf %lf %lf m %lf %lf %lf\n",Surface[elem].nx,Surface[elem].ny,Surface[elem].nz,Surface[elem].mx,Surface[elem].my,Surface[elem].mz);
					printf("normal_vector %lf %lf %lf \n",normal_vector[1],normal_vector[2],normal_vector[3]);*/
					if (ccase > Opening_mesh.nb_tab)
						{
						Opening_mesh.nb_tab = ccase;
						for (pan=1;pan<=Opening_mesh.nb_panel;pan++)
							{
							Opening_mesh.tab[pan] = (double *) Realloc_double(Opening_mesh.tab[pan],Opening_mesh.nb_tab+1);
							}
						Opening_mesh.tab[pa][ccase] = Opening_mesh.tab[pa][ccase] + nbmaille / 2.0;
						}
					else
						{
						Opening_mesh.tab[pa][ccase] = Opening_mesh.tab[pa][ccase] + nbmaille / 2.0;
						}
					}
				}
  			}
	    	}
	else
	    	{
		for (elem = 1 ; elem <= NOMBRE_SURFACES ; elem++)
			{
			for (pa=1;pa<=Opening_mesh.nb_panel;pa++)
				{
				/*fscanf(fic,"%d",&Opening_mesh.panel[pa]);
				printf(" %d ",Opening_mesh.panel[pa]);*/
				if (Surface[elem].type == Opening_mesh.panel[pa])
					{
					nbmaille = Surface[elem].nb_cote_u_ou_v;
					Surface[elem].n[1] = Surface[elem].nx;	Surface[elem].n[2] = Surface[elem].ny;	Surface[elem].n[3] = Surface[elem].nz;
					Surface[elem].m[1] = Surface[elem].mx;	Surface[elem].m[2] = Surface[elem].my;	Surface[elem].m[3] = Surface[elem].mz;
					produit_vect3(Surface[elem].n, Surface[elem].m, normal_vector);
					surface_mesh = sqrt(produit_scal(normal_vector,normal_vector));
					ccase = 1 + (int) (surface_mesh / Opening_mesh.pas);
					/*printf("elem %d surface_mesh %lf Opening_mesh.pas %lf ccase %d \n",elem,surface_mesh,Opening_mesh.pas,ccase);*/
					if (ccase > Opening_mesh.nb_tab)
						{
						Opening_mesh.nb_tab = ccase;
						for (pan=1;pan<=Opening_mesh.nb_panel;pan++)
							{
							Opening_mesh.tab[pan] = (double *) Realloc_double(Opening_mesh.tab[pan],Opening_mesh.nb_tab+1);
							}
						Opening_mesh.tab[pa][ccase] = Opening_mesh.tab[pa][ccase] + nbmaille / 2.0;
						}
					else
						{
						Opening_mesh.tab[pa][ccase] = Opening_mesh.tab[pa][ccase] + nbmaille / 2.0;
						}
					}
				}
			}
	    	}
	}
	
	
	
	
	
	
void opening()
	{
  	/*
	calculation of the opening angle by panel
	*/
	
	int elem,pa,ccase;
	double ps,angle_open1,angle_open,norm_n,norm_m;

  	double AlbX1,AlbX2,AlbX3,U1,V1,U2,V2,U3,V3,tmp,tmp4,tmp3,tmp2;
  	double nbmaille,nbmaille_aval,nbmaille_amont,param1,param2,tfuv[4];
  	int zh,zi,zj,zl,zk;
	
	printf("calculation of the opening angle by panel\n");
   
	for (pa = 1 ; pa <= Opening_angle.nb_panel ; pa++)
		{
		for (elem = 1 ; elem <= Opening_angle.nb_tab ; elem++)
			{
			Opening_angle.tab[pa][elem] = 0.0;
   			}
		}

	if (Prise.volume > Prise.seuil) 
		{
  		changement_variable_catch();		/* met l axe des X dans le sens du courant et le plan Y0Z tel que Z soit vertical ascendant*/
  		for ( elem = 1 ; elem <= NOMBRE_SURFACES ; elem++ )
  			{
			nbmaille = nb_maille_devant( elem,Prise.front );

			for (pa=1;pa<=Opening_angle.nb_panel;pa++)
				{
				if (Surface[elem].type == Opening_angle.panel[pa])
					{
					Surface[elem].n[1] = Surface[elem].nx;	Surface[elem].n[2] = Surface[elem].ny;	Surface[elem].n[3] = Surface[elem].nz;
					Surface[elem].m[1] = Surface[elem].mx;	Surface[elem].m[2] = Surface[elem].my;	Surface[elem].m[3] = Surface[elem].mz;
					ps = produit_scal(Surface[elem].n, Surface[elem].m);
					norm_n = sqrt(produit_scal(Surface[elem].n, Surface[elem].n));
					norm_m = sqrt(produit_scal(Surface[elem].m, Surface[elem].m));
					angle_open = 180.0  / PI * (acos(ps/norm_n/norm_m));
					if (angle_open >= 90.0) angle_open = 180.0 - angle_open;
					ccase = (int) (angle_open / Opening_angle.pas);
					Opening_angle.tab[pa][ccase] = Opening_angle.tab[pa][ccase] + nbmaille / 2.0;
					}
				}
  			}
	    	}
	else
	    	{
		for (elem = 1 ; elem <= NOMBRE_SURFACES ; elem++)
			{
			for (pa=1;pa<=Opening_angle.nb_panel;pa++)
				{
				/*fscanf(fic,"%d",&Opening_angle.panel[pa]);
				printf(" %d ",Opening_angle.panel[pa]);*/
				if (Surface[elem].type == Opening_angle.panel[pa])
					{
					Surface[elem].n[1] = Surface[elem].nx;	Surface[elem].n[2] = Surface[elem].ny;	Surface[elem].n[3] = Surface[elem].nz;
					Surface[elem].m[1] = Surface[elem].mx;	Surface[elem].m[2] = Surface[elem].my;	Surface[elem].m[3] = Surface[elem].mz;
					ps = produit_scal(Surface[elem].n, Surface[elem].m);
					norm_n = sqrt(produit_scal(Surface[elem].n, Surface[elem].n));
					norm_m = sqrt(produit_scal(Surface[elem].m, Surface[elem].m));
					angle_open = 180.0  / PI * (acos(ps/norm_n/norm_m));
					if (angle_open >= 90.0) angle_open = 180.0 - angle_open;
					ccase = (int) (angle_open / Opening_angle.pas);
					Opening_angle.tab[pa][ccase] = Opening_angle.tab[pa][ccase] + Surface[elem].nb_cote_u_ou_v / 2.0;
					}
				}
			}
	    	}
	/*for (pa = 1 ; pa <= Opening_angle.nb_panel ; pa++)
		{
		printf("panel %d  \n",Opening_angle.panel[pa]);
		for (elem = 1 ; elem <= Opening_angle.nb_tab ; elem++)
			{
			printf(" %lf  ",Opening_angle.tab[pa][elem]);
   			}
		printf("\n");
		}*/
   		
	}
	
	
	
	
	
	
void opening_stripe()
	{
  	/*
	calculation of the opening angle by stripe
	*/
	
	int elem,pa,ccase,stri;
	double ps,angle_open1,angle_open,norm_n,norm_m;
	double *xmat,*cmat;
  	int n_ligne,p_colonne;

  	double AlbX1,AlbX2,AlbX3,U1,V1,U2,V2,U3,V3,tmp,tmp4,tmp3,tmp2,minx,maxx;
  	double nbmaille,nbmaille_aval,nbmaille_amont,param1,param2,tfuv[4];
  	int zh,zi,zj,zl,zk;
	
	printf("calculation of the opening angle by stripe\n");
   
	if (Prise.volume > Prise.seuil) 
		{
  		changement_variable_catch();		/* met l axe des X dans le sens du courant et le plan Y0Z tel que Z soit vertical ascendant*/
		extrema_direction_courant(&minx,&maxx);
		maxx = Prise.front;		
		}
  	else
  		{
		extrema_direction_x(&minx,&maxx);
  		}
  		
  	/*define the nb of stripes*/
  	Opening_angle_stripe.nb_stripe = 1 + (int) (maxx-minx) / Opening_angle_stripe.stripe_step;
	printf("minx %lf  ",minx);	printf("maxx %lf  ",maxx);
	printf("Opening_angle_stripe.nb_stripe %d  \n",Opening_angle_stripe.nb_stripe);
  	Opening_angle_stripe.fromx =	(double *) Malloc_double(1 + Opening_angle_stripe.nb_stripe);
  	Opening_angle_stripe.tox =	(double *) Malloc_double(1 + Opening_angle_stripe.nb_stripe);

       	/*allocation de la matrice tab*/
	n_ligne 	= Opening_angle_stripe.nb_stripe + 1;
       	p_colonne 	= Opening_angle_stripe.nb_tab + 1;     
       	xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
	Opening_angle_stripe.tab = (double **) malloc (n_ligne * sizeof(double *));	if (Opening_angle_stripe.tab	 == NULL){printf("Opening_angle_stripe.tab	= NULL \n" );exit(0);}
  	cmat = xmat;
  	for (zk=0;zk<n_ligne;zk++)
  		{
  		Opening_angle_stripe.tab[zk] = cmat;
  		cmat += p_colonne;
		}	
	
	/*mise a zero du tableau par stripe et par pas d angle*/
	for (pa = 1 ; pa <= Opening_angle_stripe.nb_stripe ; pa++)
		{
		for (elem = 1 ; elem <= Opening_angle_stripe.nb_tab ; elem++)
			{
			Opening_angle_stripe.tab[pa][elem] = 0.0;
   			}
		}
	

	/*calculation of opening by stripe*/
	for (stri = 1 ; stri <= Opening_angle_stripe.nb_stripe ; stri++)
		{
		if (stri == 1)
			{
			Opening_angle_stripe.fromx[stri] = maxx; 		
			Opening_angle_stripe.tox[stri] = maxx - Opening_angle_stripe.stripe_step;		
			}
		else
			{
			Opening_angle_stripe.fromx[stri] = Opening_angle_stripe.fromx[stri-1] - Opening_angle_stripe.stripe_step; 		
			Opening_angle_stripe.tox[stri]   = Opening_angle_stripe.tox[stri-1]   - Opening_angle_stripe.stripe_step; 		
			}
		if (Opening_angle_stripe.tox[stri] < minx) Opening_angle_stripe.tox[stri] = minx;
		for ( elem = 1 ; elem <= NOMBRE_SURFACES ; elem++ )
  			{
			for (pa=1;pa<=Opening_angle_stripe.nb_panel;pa++)
				{
				if (Surface[elem].type == Opening_angle_stripe.panel[pa])
					{
					if (Prise.volume > Prise.seuil) 
						{
						nbmaille = nb_maille_devant( elem, Opening_angle_stripe.fromx[stri] );
						}
					else
						{
						/*nbmaille = Surface[elem].nb_cote_u_ou_v;*/
						nbmaille = nb_maille_devant( elem, Opening_angle_stripe.fromx[stri] );
						}
					Surface[elem].n[1] = Surface[elem].nx;	Surface[elem].n[2] = Surface[elem].ny;	Surface[elem].n[3] = Surface[elem].nz;
					Surface[elem].m[1] = Surface[elem].mx;	Surface[elem].m[2] = Surface[elem].my;	Surface[elem].m[3] = Surface[elem].mz;
					ps = produit_scal(Surface[elem].n, Surface[elem].m);
					norm_n = sqrt(produit_scal(Surface[elem].n, Surface[elem].n));
					norm_m = sqrt(produit_scal(Surface[elem].m, Surface[elem].m));
					angle_open = 180.0  / PI * (acos(ps/norm_n/norm_m));
					if (angle_open >= 90.0) angle_open = 180.0 - angle_open;
					ccase = (int) (angle_open / Opening_angle_stripe.pas);
					Opening_angle_stripe.tab[stri][ccase] = Opening_angle_stripe.tab[stri][ccase] + nbmaille / 2.0;
					/*if (stri==1)
						{
					printf("elem %5d panel %5d stri %5d case %5d op %18.0lf nbmaille %10.5lf  \n",elem,Surface[elem].type,stri,ccase,Opening_angle_stripe.tab[stri][ccase],nbmaille);
						}*/
					}
				}
			}
		}

	/*up to now the nb of meshes is calculated from fromx to minx, so to calculate from fromx to tox we remove frome a stripe the next one*/
	for (stri = 1 ; stri <= Opening_angle_stripe.nb_stripe - 1 ; stri++)
		{
		for (elem = 1 ; elem <= Opening_angle_stripe.nb_tab ; elem++)
			{
			Opening_angle_stripe.tab[stri][elem] = Opening_angle_stripe.tab[stri][elem] - Opening_angle_stripe.tab[stri+1][elem];
			}
		}
		
	/*writting results on screen*/
	/*for (stri = 1 ; stri <= Opening_angle_stripe.nb_stripe ; stri++)
		{
		printf("stripe %d  ",stri);
		printf("fromx %lf  ",Opening_angle_stripe.fromx[stri]);
		printf("tox %lf  \n",Opening_angle_stripe.tox[stri]);
		for (elem = 1 ; elem <= Opening_angle_stripe.nb_tab ; elem++)
			{
			printf(" %lf  ",Opening_angle_stripe.tab[stri][elem]);
   			}
		printf("\n");
		}*/
	/*free*/
	if (xmat						!= NULL)        free(xmat);
	}
	
double nb_maille_devant(int eleme, double planx)
	{
	/*renvoi le nb de maille de l element eleme devant le planx*/
	double nbmaill,AlbX1,AlbX2,AlbX3,U1,V1,U2,V2,U3,V3,param1,param2,nbmaill_aval;
	int zh,zi,zj;
	
	
	
	
  	nbmaill = 0.0;
	/*numeros des coordonnees selon x des sommets du triangle*/
  	zh = yc(eleme,1);  zi = yc(eleme,4);  zj = yc(eleme,7);
  	/*
  	coordonnees cartesiennes et filaires du triangle
  	*/
  	AlbX1 = wfcodend[zh  ];	AlbX2 = wfcodend[zi  ];	AlbX3 = wfcodend[zj  ];
  	U1 = Surface[eleme].lon[1] ; V1 = Surface[eleme].lon[2] ;
  	U2 = Surface[eleme].lon[3] ; V2 = Surface[eleme].lon[4] ;
  	U3 = Surface[eleme].lon[5] ; V3 = Surface[eleme].lon[6] ;
   	/*ne traiter que les surfaces en partie sous la surface libre*/
  	if ((AlbX1 < planx) || (AlbX2 < planx) || (AlbX3 < planx))
  		{
  		if ((AlbX1 <= planx) && (AlbX2 <= planx) && (AlbX3 <= planx))
  			{
			nbmaill = Surface[eleme].nb_cote_u_ou_v;
    			}
		else if ((AlbX1 >= planx) && (AlbX2 < planx) && (AlbX3 < planx))
  			{
  			/*surfaces partiellement a l avant  du front : point 1 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
			/* Nombre de maille par point du triangle de sommets 1, inter1 et inter2. */
			nbmaill = Surface[eleme].nb_cote_u_ou_v;
			param1 = (AlbX1-planx) / (AlbX1-AlbX2) ; param2 = (AlbX1-planx) / (AlbX1-AlbX3) ;
			nbmaill_aval = fabs( ( (1 - param1) * U1 + param1 * U2 - U1) * ((1 - param2) * V1 + param2 * V3 - V1)
	      	            		    - ( (1 - param1) * V1 + param1 * V2 - V1) * ((1 - param2) * U1 + param2 * U3 - U1) );
			nbmaill = nbmaill - nbmaill_aval;
    			}
		else if ((AlbX1 < planx) && (AlbX2 >= planx) && (AlbX3 < planx))
  			{
  			/* surfaces partiellement a l avant  du front : point 2 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  			on calcule le volume en amont que l on retranche au volume dy cylindre de section triangulaire*/
			/* Nombre de maille du triangle de sommets 2, inter1 et inter2. */
			nbmaill = Surface[eleme].nb_cote_u_ou_v;
			param1 = (AlbX2-planx) / (AlbX2-AlbX3) ; param2 = (AlbX2-planx) / (AlbX2-AlbX1) ;
			nbmaill_aval = fabs( ( (1 - param1) * U2 + param1 * U3 - U2) * ( (1 - param2) * V2 + param2 * V1 - V2)
	       	       	  	       	    - ( (1 - param1) * V2 + param1 * V3 - V2) * ( (1 - param2) * U2 + param2 * U1 - U2) );
    			nbmaill = nbmaill - nbmaill_aval;
    			}
		else if ((AlbX1 < planx) && (AlbX2 < planx) && (AlbX3 >= planx))
  			{
  			/* surfaces partiellement a l avant du front : point 3 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23) */
			/* Nombre de maille du triangle de sommets 3, inter1 et inter2. */
			nbmaill = Surface[eleme].nb_cote_u_ou_v;
			param1 = (AlbX3-planx) / (AlbX3-AlbX1) ;    param2 = (AlbX3-planx) / (AlbX3-AlbX2) ;
			nbmaill_aval = fabs( ( (1 - param1) * U3 + param1 * U1 - U3) * ( (1 -param2) * V3 + param2 * V2 - V3)
	                  		    - ( (1 - param1) * V3 + param1 * V1 - V3) * ( (1 -param2) * U3 + param2 * U2 - U3) );
    			nbmaill = nbmaill - nbmaill_aval;
    			}
		else if ((AlbX1 < planx) && (AlbX2 >= planx) && (AlbX3 >= planx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
   			/* Nombre de mailles contenues dans le triangle amont de sommets1, inter1 et inter2.*/
   			param1 = (AlbX1-planx) / (AlbX1-AlbX2) ;    param2 = (AlbX1-planx) / (AlbX1-AlbX3) ;
			nbmaill = fabs( ( (1 - param1) * U1 + param1 * U2 - U1) * ( (1 - param2) * V1 + param2 * V3 - V1)
		                       - ( (1 - param1) * V1 + param1 * V2 - V1) * ( (1 - param2) * U1 + param2 * U3 - U1) );
    			}
    	
		else if ((AlbX1 >= planx) && (AlbX2 < planx) && (AlbX3 >= planx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12) */
   			/* Nombre de mailles contenues dans le triangle de sommets 2, inter1 et inter2. */
			param1 = (AlbX2-planx) / (AlbX2-AlbX3) ;    param2 = (AlbX2-planx) / (AlbX2-AlbX1) ;
			nbmaill = fabs( ( (1 - param1) * U2 + param1 * U3 - U2) * ( (1 - param2) * V2 + param2 * V1 - V2)
		                       - ( (1 - param1) * V2 + param1 * V3 - V2) * ( (1 - param2) * U2 + param2 * U1 - U2) );
    			}
		else if ((AlbX1 >= planx) && (AlbX2 >= planx) && (AlbX3 < planx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23) */
   			/* Nombre de mailles contenues dans le triangle de sommets 3, inter1 et inter2. */
			param1 = (AlbX3-planx) / (AlbX3-AlbX1) ;    param2 = (AlbX3-planx) / (AlbX3-AlbX2) ;
			nbmaill = fabs( ( (1 - param1) * U3 + param1 * U1 - U3) * ( (1 - param2) * V3 + param2 * V2 - V3)
				       - ( (1 - param1) * V3 + param1 * V1 - V3) * ( (1 - param2) * U3 + param2 * U2 - U3) );
    			}
    		}
  	return nbmaill;
	}

