#include "batz.h"

/*int i;*/

void charger_initial()
	{
	int j,zi,no;

	/*int j,no,zi;*/

	/*fname = (char *) GetFile(NULL);*/
	strcpy(fname , (char *) GetFile("../data_2001"));
	//strcpy(fname , (char *) GetFile("../"));
	/*strcpy(fname , (char *) GetFile("/home/moi/hexa/data_2001"));*/

	if(fname[0])
		{
		/*printf(stdout,"%s\n",fname);*/
		printf("Fichier selectionne: %s\n" , fname);
		Flag_Fichier_final_charge = 1;
		}
	else
		{
		printf("fichier non trouve\n");
		return;
		}

	strcpy(fname1,fname);
	j=strlen(fname1);
	while ((fname1[j])!='.' && j>0) j--;
	if (fname1[j]=='.') fname1[j]=0;
	
	/* Lecture du fichier selectionne */	
	lectureDo3(fname1);
	lecture_don(fname1);
	printf("Passtockage charg init %f\n", Passtockage);

   	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
    		{
    		//printf("zi %4d type %4d \n",zi,Element[zi].type);
    		if (Element[zi].type > 0)
    			{
    			//this bar belongs to the cable Element[zi].type
       			Element[zi].lgrepos = (Element[zi].pro[2] - Element[zi].pro[1]) * TypeElement[Element[zi].type].lgrepos;
   			}
    		else
    			{
    			//this bar belongs to the panel panneau[-Element[zi].type].lgrepos
       			Element[zi].lgrepos = (Element[zi].pro[2] - Element[zi].pro[1]) * panneau[-Element[zi].type].longueur_repos;
    			}
      		}

	/*lecturesta(fname1);*/
    	/*initialisation des noeuds affiches********************************/
	for (no=1;no<=NOMBRE_NOEUDS;no++)
		{ 
  		Noeud[no].x = Noeud[no].inix;
  		Noeud[no].y = Noeud[no].iniy;
  		Noeud[no].z = Noeud[no].iniz;
		}
	/*printf("NOMBRE_NOEUDS: %d\n" , NOMBRE_NOEUDS);
	  for (zi=1;zi<=NOMBRE_NOEUDS;zi++)
	  	{
	    	printf("%lf %lf %lf \n",Noeud[zi].inix,Noeud[zi].iniy,Noeud[zi].iniz);
	    	printf("%lf %lf %lf \n",Noeud[zi].x,Noeud[zi].y,Noeud[zi].z);
	  	}*/
	nbtemps = 1;
	nb_animation = 1;
	step_animation = 1;
	no_eigenvalue = 1;
	scale_eigenvalue = 1.0;

	initialisation_nb_color();
	initialisation_nb_ufils();
	initialisation_nb_vfils();
	fils_contour_calculer();
	initialisation_nb_Ufils_hexa();
	initialisation_nb_Vfils_hexa();
	fils_contour_hexa();
	initialisation_color_side();
	initialisation_elongation();
	initialisation_couleur_tension_final();
	initialisation_couleur_triangle();
	initialisation_orientation_triangle();
    	printf("Avant prise en compte des symetries\n");
    	printf("NOMBRE_NOEUDS 		= %4d\n",NOMBRE_NOEUDS);
    	printf("NOMBRE_ELEMENTS 	= %4d\n",NOMBRE_ELEMENTS);
    	printf("NOMBRE_SURFACES 	= %4d\n",NOMBRE_SURFACES);
    	printf("NOMBRE_SUR_HEXA 	= %4d\n",NOMBRE_SURF_HEXA);
	if (Structure.visible_symmetry == 1)		recherche_symetrie();
    	printf("Apres prise en compte des symetries\n");
	initialisation_min_max();
	SetMenuItemChecked(w[103],0);
    	printf("min et max de x 	= %10.3f %10.3f\n",minx,maxx);
    	printf("min et max de y 	= %10.3f %10.3f\n",miny,maxy);
    	printf("min et max de z 	= %10.3f %10.3f\n",minz,maxz);

	initialisation_surface_front();
	initialisation_ps();
    	printf("NOMBRE_NOEUDS 		= %4d\n",NOMBRE_NOEUDS);
    	printf("NOMBRE_ELEMENTS 	= %4d\n",NOMBRE_ELEMENTS);
    	printf("NOMBRE_SURFACES 	= %4d\n",NOMBRE_SURFACES);
    	printf("NOMBRE_SUR_HEXA 	= %4d\n",NOMBRE_SURF_HEXA);
    	printf("elongationmin 		= %f\n",elongationmin);
    	printf("elongationmax 		= %f\n",elongationmax);
	FreeStandardColors();
	}


void charger_final()
	{
	int j,no,zi,elem, rrr,flag_dyn,pa;
	double Vn[4],Vm[4],norm_n,norm_m,scal,cos_gamma,sin_gamma,dn,dm,d_min,max_exit,min_exit,std_dev;
	double mean_exit;
	int nb_tri;
	if (Structure.graphic == 1)
		{		
		/*strcpy(newfic , (char *) GetFile("../data_2001"));*/
		strcpy(fname , (char *) GetFile("../data_2001"));
		//strcpy(fname , (char *) GetFile("../"));
		}
	if (Structure.graphic == 2)
		{
  		strcpy(fname,Structure.nomfichier1);
		}

	printf("Structure.graphic  %d ***********************************\n",Structure.graphic);
	
	/*fname = (char *) GetFile(NULL);*/
	/*strcpy(fname , (char *) GetFile("../data_2001"));*/
	/*strcpy(fname , (char *) GetFile("/home/langevin/perso/dpriour/texte/hexa2/data_2001"));*/

	if(fname[0])
		{
		/*printf(stdout,"%s\n",fname);*/
		printf("Fichier selectionne: %s\n" , fname);
		Flag_Fichier_final_charge = 1;
		}
	else
		{
		printf("fichier non trouve\n");
		return;
		}
	strcpy(fname1,fname);
	j=strlen(fname1);
	while ((fname1[j])!='.' && j>0) j--;
	if (fname1[j]=='.') fname1[j]=0;
	/* Lecture du fichier selectionne */	
	lecture_don(fname1);
	lectureDo3(fname1);
  	lecture_don(fname1);


    	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
    		{
      		//Element[zi].lgrepos = (Element[zi].pro[2] - Element[zi].pro[1]) * TypeElement[Element[zi].type].lgrepos;
		//printf("elem %d longueur : %lf \n",zi,Element[zi].lgrepos);
    		if (Element[zi].type > 0)
    			{
    			//this bar belongs to the cable Element[zi].type
       			Element[zi].lgrepos = (Element[zi].pro[2] - Element[zi].pro[1]) * TypeElement[Element[zi].type].lgrepos;
   			}
    		else
    			{
    			//this bar belongs to the panel panneau[-Element[zi].typ].lgrepos
       			Element[zi].lgrepos = (Element[zi].pro[2] - Element[zi].pro[1]) * panneau[-Element[zi].type].longueur_repos;
    			}
      		}
     		
     	
	lecturesta(fname1);
	mesure_defaut_discretisation();
	nbtemps = 0;
	initialisation_min_max();
	SetMenuItemChecked(w[103],0);

	flag_dyn = lecturedyn(fname1);
	
	/* initialisation parametre animation*/
	nb_animation = 1;
	//	ralenti_animation = 1.0;
	ralenti_animation = 1.0/(25*Passtockage);
	depart_anim_sec = Finstockage-Houle.periode;
	/* debut modifdp du 26 mars 2010*/
	if (depart_anim_sec < Debutstockage)	depart_anim_sec = Debutstockage;
	/* fin modifdp du 26 mars 2010*/
	fin_anim_sec = Finstockage;
	step_animation = 1;
	
	depart_anim = (1+ ((nbtemps-1) * ((depart_anim_sec - Debutstockage)/(Finstockage-Debutstockage))));
		
	fin_anim = (1+ ((nbtemps-1) * ((fin_anim_sec - Debutstockage)/(Finstockage-Debutstockage))));

	
    	/*initialisation des noeuds affiches********************************/
	for (no=1;no<=NOMBRE_NOEUDS;no++)
		{ 
  		Noeud[no].x = Noeud[no].inix;
  		Noeud[no].y = Noeud[no].iniy;
  		Noeud[no].z = Noeud[no].iniz;
		}
	//nbtemps = 1;
	nb_animation = 1;
	step_animation = 1;
	no_eigenvalue = 1;
	scale_eigenvalue = 1.0;
	
	printf("Avant initialisation_nb_color\n");
	initialisation_nb_color();
	printf("Après initialisation_nb_color\n");
	initialisation_nb_ufils();
	initialisation_nb_vfils();
	fils_contour_calculer();
	initialisation_nb_Ufils_hexa();
	initialisation_nb_Vfils_hexa();
	fils_contour_hexa();
	initialisation_color_side();
	initialisation_elongation();
	initialisation_couleur_tension_final();
	initialisation_couleur_triangle();
	initialisation_orientation_triangle();
   	printf("Avant prise en compte des symetries\n");
    	printf("NOMBRE_NOEUDS 		= %4d\n",NOMBRE_NOEUDS);
    	printf("NOMBRE_ELEMENTS 	= %4d\n",NOMBRE_ELEMENTS);
    	printf("NOMBRE_SURFACES 	= %4d\n",NOMBRE_SURFACES);
    	printf("NOMBRE_SUR_HEXA 	= %4d\n",NOMBRE_SURF_HEXA);
	if (Structure.visible_symmetry == 1)		recherche_symetrie();
    	printf("Apres prise en compte des symetries\n");
	initialisation_min_max();
    	printf("min et max de x 	= %10.3f %10.3f\n",minx,maxx);
    	printf("min et max de y 	= %10.3f %10.3f\n",miny,maxy);
    	printf("min et max de z 	= %10.3f %10.3f\n",minz,maxz);
	if (flag_dyn == 1) calcul_houle2();
	initialisation_surface_front();
	initialisation_ps();
    	printf("NOMBRE_NOEUDS 		= %4d\n",NOMBRE_NOEUDS);
    	printf("NOMBRE_ELEMENTS 	= %4d\n",NOMBRE_ELEMENTS);
    	printf("NOMBRE_SURFACES 	= %4d\n",NOMBRE_SURFACES);
    	printf("NOMBRE_SUR_HEXA 	= %4d\n",NOMBRE_SURF_HEXA);
    	printf("elongationmin 		= %f\n",elongationmin);
    	printf("elongationmax 		= %f\n",elongationmax);
  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
  		{
  		Surface[elem].flag_dessin_triangle = 0;
  		Surface[elem].flag_dessin = 0;
  		Surface[elem].flag_dessin_u = 0;
  		Surface[elem].flag_dessin_v = 0;
  		Surface[elem].flag_dessin_orientation_xy = 0;
  		}
  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
  		{
		Vn[1] = Surface[elem].nx;	Vn[2] = Surface[elem].ny;	Vn[3] = Surface[elem].nz; /*u twine vector*/
		Vm[1] = Surface[elem].mx;	Vm[2] = Surface[elem].my;	Vm[3] = Surface[elem].mz; /*v twine vector*/
		norm_n = sqrt(produit_scal_double(Vn,Vn));	
		norm_m = sqrt(produit_scal_double(Vm,Vm));	
		scal = produit_scal_double(Vn,Vm);
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
	for (pa=1;pa<=NbTypesurf;pa++)
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
		//printf("nb_tri %4d  ",nb_tri);
		//printf("mean_exit %8.3lf  ",panneau[pa].mean_exit_size);
		//printf("min_exit %8.3lf  ",panneau[pa].min_exit_size);
		//printf("panneau[%4d].max_exit_size = %8.3lf\n",pa,panneau[pa].max_exit_size);
		}
	for (pa=1;pa<=NbTypesurf;pa++)
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
	Ball.flag_dessin = 0;
	FreeStandardColors();
	}


void calcul_houle2()
	{
	/* debut modifdp du 17 mars 2010*/
	/*wave surface is represented by segments which are parrallel to the crests, along minx, maxx, miny and maxy
	the segments are such that the first extremity is Houle.X[2*i-1], Houle.Y[2*i-1], Houle.Z[2*i-1], and the second is Houle.X[2*i-0], Houle.Y[2*i-0], Houle.Z[2*i-0]*/
	double xp,yp,Xp,Yp,lX,lY,ll,dist_diagonale,distw,distc;
	double Xs,Ys,Xs1,Ys1,Xs2,Ys2,Xs3,Ys3,Xs4,Ys4;
	float vect_1[4],vect_2[4],vect_3[4];
	int zk,pa,nb_cretes,zi;
  	int n_ligne,p_colonne;
	int temp;
	int nb_div=50;
	double angle_houle = Houle.direction *PI/180;
	if (Houle.lambda <= 0.0)
		{
		Houle.lambda = G / 2.0 / PI * Houle.periode * Houle.periode;	
		}
	distc = Houle.lambda/nb_div;			/*crests distance*/
	vect_2[1] =  cos(angle_houle);	vect_2[2] = sin(angle_houle);	vect_2[3] = 0.0; /*wave direction vector*/
	vect_3[1] = -sin(angle_houle);	vect_3[2] = cos(angle_houle);	vect_3[3] = 0.0; /*crest direction vector: normal to the wave direction*/
	if (angle_houle == 0.0)
		{
		vect_1[1] = maxx-minx;		vect_1[2] = maxy-miny;		vect_1[3] = 0.0; /*diagonal vector*/
		}
	if ((angle_houle > 0.0) && (angle_houle < PI/2.0))
		{
		vect_1[1] = maxx-minx;		vect_1[2] = maxy-miny;		vect_1[3] = 0.0; /*diagonal vector*/
		}
	if (angle_houle == PI/2.0)
		{
		vect_1[1] = maxx-minx;		vect_1[2] = maxy-miny;		vect_1[3] = 0.0; /*diagonal vector*/
		}
	if ((angle_houle > PI/2.0) && (angle_houle < PI))
		{
		vect_1[1] = minx-maxx;		vect_1[2] = maxy-miny;		vect_1[3] = 0.0; /*diagonal vector*/
		}
	if (angle_houle == PI)
		{
		vect_1[1] = minx-maxx;		vect_1[2] = maxy-miny;		vect_1[3] = 0.0; /*diagonal vector*/
		}
	if ((angle_houle > PI) && (angle_houle < 3.0*PI/2.0))
		{
		vect_1[1] = minx-maxx;		vect_1[2] = miny-maxy;		vect_1[3] = 0.0; /*diagonal vector*/
		}
	if (angle_houle == 3.0*PI/2.0)
		{
		vect_1[1] = minx-maxx;		vect_1[2] = miny-maxy;		vect_1[3] = 0.0; /*diagonal vector*/
		}
	if ((angle_houle > 3.0*PI/2.0) && (angle_houle < 2.0*PI))
		{
		vect_1[1] = maxx-minx;		vect_1[2] = miny-maxy;		vect_1[3] = 0.0; /*diagonal vector*/
		}
	dist_diagonale =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
	nb_cretes = (int) (dist_diagonale/distc);
	if (nb_cretes<5) 
		{
		distc = dist_diagonale/5.0;
		nb_cretes = (int) (dist_diagonale/distc);
		}
	printf("dist_diagonale %8.2f distc %8.2f nb_cretes %8d \n",dist_diagonale,distc,nb_cretes);
	printf("Houle.lambda %8.2f nb_div %8d \n",Houle.lambda,nb_div);
	/*******************************************************/
	/*double** Houle.X = NULL;  Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs */
	int dim1,dim2,i,j;

	/* debut modifdp du 4 mars 2010*/
	dim1=10*(nb_cretes+1); /* Attribuer juste pour réaliser mon test */
	/* fin modifdp du 4 mars 2010*/
	dim2=nbtemps;
	printf("dim1,dim2 %d %d\n",dim1,dim2);

	Houle.X = malloc (sizeof(double*)*dim1); /* On commence par déclarer un tableau de pointeurs ayant pour dimension la largeur de la matrice */
	Houle.Y = malloc (sizeof(double*)*dim1); /* On commence par déclarer un tableau de pointeurs ayant pour dimension la largeur de la matrice */
	Houle.Z = malloc (sizeof(double*)*dim1); /* On commence par déclarer un tableau de pointeurs ayant pour dimension la largeur de la matrice */
	Houle.U = malloc (sizeof(double*)*dim1); /* On commence par déclarer un tableau de pointeurs ayant pour dimension la largeur de la matrice */
	Houle.V = malloc (sizeof(double*)*dim1); /* On commence par déclarer un tableau de pointeurs ayant pour dimension la largeur de la matrice */
	Houle.W = malloc (sizeof(double*)*dim1); /* On commence par déclarer un tableau de pointeurs ayant pour dimension la largeur de la matrice */

	for (i=0;i<dim1;i++)
		{
		Houle.X[i] = malloc (sizeof(double)*dim2); /*Puis pour chaque ligne, on attribue un nombre de colonne*/
		Houle.Y[i] = malloc (sizeof(double)*dim2); /*Puis pour chaque ligne, on attribue un nombre de colonne*/
		Houle.Z[i] = malloc (sizeof(double)*dim2); /*Puis pour chaque ligne, on attribue un nombre de colonne*/
		Houle.U[i] = malloc (sizeof(double)*dim2); /*Puis pour chaque ligne, on attribue un nombre de colonne*/
		Houle.V[i] = malloc (sizeof(double)*dim2); /*Puis pour chaque ligne, on attribue un nombre de colonne*/
		Houle.W[i] = malloc (sizeof(double)*dim2); /*Puis pour chaque ligne, on attribue un nombre de colonne*/
		}
	/**************** essai de remplissage du tableau *********************/
	/*
	for (i=0;i<dim1;i++)
		{
		for (j=0;j<dim2;j++)
			{		
			Houle.X[i][j] = (i+j)/3.0;
			}
		}
	*/
	/****************** puis à la fin de l'utilisation du tableau ********************/
	/*
	for (i=0;i<dim1;i++)
	{

		free (Houle.X[i]); 
		free (Houle.Y[i]); 
		free (Houle.Z[i]); 
		free (Houle.U[i]); 
		free (Houle.V[i]); 
		free (Houle.W[i]); 
	}
	free (Houle.X);
	free (Houle.Y);
	free (Houle.Z);
	free (Houle.U);
	free (Houle.V);
	free (Houle.W);
	*/
	/******************************************************************/
	zi = 0;
	printf("nb_cretes %d nbtemps %d angle_houle %lf\n",nb_cretes,nbtemps,angle_houle);
	for (pa=1;pa<=nbtemps;pa++)
		{
		zi = 0;
		//printf("temps  %lf\n",temps[pa]);
		//printf("periode  %lf\n",Houle.periode);
		//printf("hauteur  %lf\n",Houle.hauteur);
		if (temps[pa] < Houle.periode)  	
			{
			Houle.hh1 = Houle.hauteur * temps[pa] / Houle.periode;
			}
		else 					
			{
			Houle.hh1 = Houle.hauteur;
			}
		if (angle_houle == 0.0)	/***************************************************************/
			{
			for (zk=0;zk<=nb_cretes+1;zk++)
				{
				/*lignes parallèles aux cretes*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++; 
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=miny;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=maxy;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*contour à miny*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=miny;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				/*printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=miny;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*contour à maxy*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=maxy;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				/*printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=maxy;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			}
		if ((angle_houle > 0.0) && (angle_houle < PI/2.0))	/***************************************************************/
			{
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*crests*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				zi++;
				Ys = miny;			/*premier point sur miny*/
				ll = (Ys-Yp) / vect_3[2]; 	/*longueur du vecteur reliant le point de la crete XpYp au point sur le bord Ys*/
				Xs = Xp + ll * vect_3[1];	/*absice du point sur le bord*/
				if (Xs > maxx)
					{
					Xs = maxx;
					ll = (Xs-Xp) / vect_3[1];
					Ys = Yp + ll * vect_3[2];
					}
				Houle.X[zi][pa]=Xs;
				Houle.Y[zi][pa]=Ys;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("azi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				zi++;				
				Xs = minx;			/*deuxième point sur minx a priori*/
				ll = (Xs-Xp) / vect_3[1];	/*longueur du vecteur reliant le point de la crete XpYp au point sur le bord Xs*/
				Ys = Yp + ll * vect_3[2];	/*ordonnee du point sur le bord*/
				if (Ys > maxy)
					{
					Ys = maxy;
					ll = (Ys-Yp) / vect_3[2];
					Xs = Xp + ll * vect_3[1];
					}
				
				Houle.X[zi][pa]=Xs;
				Houle.Y[zi][pa]=Ys;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("bzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along miny*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Ys1 = miny;
				ll = (Ys1-Yp) / vect_3[2];
				Xs1 = Xp + ll * vect_3[1];
				if (Xs1 <= maxx)
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("czi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					Xp = minx + (zk+1) * distc *cos(angle_houle);
					Yp = miny + (zk+1) * distc *sin(angle_houle);
					zi++;
					Ys2 = miny;
					ll = (Ys2-Yp) / vect_3[2];
					Xs2 = Xp + ll * vect_3[1];
					if (Xs2 <= maxx)
						{
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("dzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					else
						{
						Xs2 = maxx;
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("ezi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along maxx*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs1 = maxx;
				ll = (Xs1-Xp) / vect_3[1];
				Ys1 = Yp + ll * vect_3[2];
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs2 = maxx;
				ll = (Xs2-Xp) / vect_3[1];
				Ys2 = Yp + ll * vect_3[2];
				if ((Ys1<=miny) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*first point on the corner maxx miny*/
					Ys1 = miny;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("fzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("gzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*two point between the corners maxx miny & maxx maxy*/
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("hzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("izi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2>maxy))
					{
					/*last point on the corner maxx maxy*/
					Ys2 = maxy;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("jzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("kzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along minx*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs1 = minx;
				ll = (Xs1-Xp) / vect_3[1];
				Ys1 = Yp + ll * vect_3[2];
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs2 = minx;
				ll = (Xs2-Xp) / vect_3[1];
				Ys2 = Yp + ll * vect_3[2];
				if ((Ys1<=miny) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*first point on the corner minx miny*/
					Ys1 = miny;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("fzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("gzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*two point between the corners minx miny & minx maxy*/
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("hzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("izi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2>maxy))
					{
					/*last point on the corner minx maxy*/
					Ys2 = maxy;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("jzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("kzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				}
				
				
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along maxy*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Ys1 = maxy;
				ll = (Ys1-Yp) / vect_3[2];
				Xs1 = Xp + ll * vect_3[1];
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				Ys2 = maxy;
				ll = (Ys2-Yp) / vect_3[2];
				Xs2 = Xp + ll * vect_3[1];

				if ((Xs1<=minx) && (Xs2>minx) && (Xs2<=maxx))
					{
					/*first point on the corner minx maxy*/
					Xs1 = minx;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				if ((Xs1>minx) && (Xs1<=maxx) && (Xs2>minx) && (Xs2<=maxx))
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				if ((Xs1>minx) && (Xs1<=maxx) && (Xs2>maxx))
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					Xs2 = maxx;
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				}

			}
		if (angle_houle == PI/2.0)	/***************************************************************/
			{
			for (zk=0;zk<=nb_cretes+1;zk++)
				{
				/*lignes parallèles aux cretes*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++; 
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=minx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=maxx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*contour à minx*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=minx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				/*printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=minx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*contour à maxx*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=maxx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				/*printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=maxx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			}
		if ((angle_houle > PI/2.0) && (angle_houle < PI))/***************************************************************/
			{
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*crests*/
				/*point à zk cretes de l'origine maxx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				zi++;
				Ys = miny;			/*premier point sur miny*/
				ll = (Ys-Yp) / vect_3[2]; 	/*longueur du vecteur reliant le point de la crete XpYp au point sur le bord Ys*/
				Xs = Xp + ll * vect_3[1];	/*absice du point sur le bord*/
				if (Xs < minx)
					{
					Xs = minx;
					ll = (Xs-Xp) / vect_3[1];
					Ys = Yp + ll * vect_3[2];
					}
				Houle.X[zi][pa]=Xs;
				Houle.Y[zi][pa]=Ys;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("azi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				zi++;				
				Xs = maxx;			/*deuxième point sur maxx a priori*/
				ll = (Xs-Xp) / vect_3[1];	/*longueur du vecteur reliant le point de la crete XpYp au point sur le bord Xs*/
				Ys = Yp + ll * vect_3[2];	/*ordonnee du point sur le bord*/
				if (Ys > maxy)
					{
					Ys = maxy;
					ll = (Ys-Yp) / vect_3[2];
					Xs = Xp + ll * vect_3[1];
					}
				Houle.X[zi][pa]=Xs;
				Houle.Y[zi][pa]=Ys;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("bzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along miny*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Ys1 = miny;
				ll = (Ys1-Yp) / vect_3[2];
				Xs1 = Xp + ll * vect_3[1];
				if (Xs1 >= minx)
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("czi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					Xp = maxx + (zk+1) * distc *cos(angle_houle);
					Yp = miny + (zk+1) * distc *sin(angle_houle);
					zi++;
					Ys2 = miny;
					ll = (Ys2-Yp) / vect_3[2];
					Xs2 = Xp + ll * vect_3[1];
					if (Xs2 >= minx)
						{
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("dzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					else
						{
						Xs2 = minx;
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("ezi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along maxx*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs1 = maxx;
				ll = (Xs1-Xp) / vect_3[1];
				Ys1 = Yp + ll * vect_3[2];
				if (Ys1 <= maxy)
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("czi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					Xp = maxx + (zk+1) * distc *cos(angle_houle);
					Yp = miny + (zk+1) * distc *sin(angle_houle);
					zi++;
					Xs2 = maxx;
					ll = (Xs2-Xp) / vect_3[1];
					Ys2 = Yp + ll * vect_3[2];
					if (Ys2 <= maxy)
						{
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("dzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					else
						{
						Ys2 = maxy;
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("ezi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along maxy*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Ys1 = maxy;
				ll = (Ys1-Yp) / vect_3[2];
				Xs1 = Xp + ll * vect_3[1];
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				Ys2 = maxy;
				ll = (Ys2-Yp) / vect_3[2];
				Xs2 = Xp + ll * vect_3[1];

				if ((Xs1>maxx) && (Xs2>minx) && (Xs2<=maxx))
					{
					/*first point on the corner minx maxy*/
					Xs1 = maxx;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				if ((Xs1>minx) && (Xs1<=maxx) && (Xs2>minx) && (Xs2<=maxx))
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				if ((Xs1>minx) && (Xs1<=maxx) && (Xs2<=minx))
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					Xs2 = minx;
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along minx*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs1 = minx;
				ll = (Xs1-Xp) / vect_3[1];
				Ys1 = Yp + ll * vect_3[2];
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs2 = minx;
				ll = (Xs2-Xp) / vect_3[1];
				Ys2 = Yp + ll * vect_3[2];
				if ((Ys1<=miny) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*first point on the corner maxx miny*/
					Ys1 = miny;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("fzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("gzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*two point between the corners maxx miny & maxx maxy*/
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("hzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("izi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2>maxy))
					{
					/*last point on the corner maxx maxy*/
					Ys2 = maxy;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("jzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("kzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				}
			}
		if (angle_houle == PI)/***************************************************************/
			{
			for (zk=0;zk<=nb_cretes+1;zk++)
				{
				/*lignes parallèles aux cretes*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++; 
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=miny;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=maxy;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*contour à miny*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=miny;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				/*printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=miny;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*contour à maxy*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = miny + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=maxy;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				/*printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + (zk+1) * distc *cos(angle_houle);
				Yp = miny + (zk+1) * distc *sin(angle_houle);
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=Xp;
				Houle.Y[zi][pa]=maxy;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			}
		if ((angle_houle > PI) && (angle_houle < 3.0*PI/2.0))/***************************************************************/
			{
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*crests*/
				/*point à zk cretes de l'origine maxx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				zi++;
				Ys = maxy;			/*premier point sur maxy*/
				ll = (Ys-Yp) / vect_3[2]; 	/*longueur du vecteur reliant le point de la crete XpYp au point sur le bord Ys*/
				Xs = Xp + ll * vect_3[1];	/*absice du point sur le bord*/
				if (Xs < minx)
					{
					Xs = minx;
					ll = (Xs-Xp) / vect_3[1];
					Ys = Yp + ll * vect_3[2];
					}
				Houle.X[zi][pa]=Xs;
				Houle.Y[zi][pa]=Ys;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("azi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				zi++;				
				Xs = maxx;			/*deuxième point sur maxx a priori*/
				ll = (Xs-Xp) / vect_3[1];	/*longueur du vecteur reliant le point de la crete XpYp au point sur le bord Xs*/
				Ys = Yp + ll * vect_3[2];	/*ordonnee du point sur le bord*/
				if (Ys < miny)
					{
					Ys = miny;
					ll = (Ys-Yp) / vect_3[2];
					Xs = Xp + ll * vect_3[1];
					}
				Houle.X[zi][pa]=Xs;
				Houle.Y[zi][pa]=Ys;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("bzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along maxy*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Ys1 = maxy;
				ll = (Ys1-Yp) / vect_3[2];
				Xs1 = Xp + ll * vect_3[1];
				if (Xs1 > minx)
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("czi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					Xp = maxx + (zk+1) * distc *cos(angle_houle);
					Yp = maxy + (zk+1) * distc *sin(angle_houle);
					zi++;
					Ys2 = maxy;
					ll = (Ys2-Yp) / vect_3[2];
					Xs2 = Xp + ll * vect_3[1];
					if (Xs2 > minx)
						{
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("dzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					else
						{
						Xs2 = minx;
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("ezi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along minx*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs1 = minx;
				ll = (Xs1-Xp) / vect_3[1];
				Ys1 = Yp + ll * vect_3[2];
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + (zk+1) * distc *cos(angle_houle);
				Yp = maxy + (zk+1) * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs2 = minx;
				ll = (Xs2-Xp) / vect_3[1];
				Ys2 = Yp + ll * vect_3[2];
				if ((Ys1>maxy) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*first point on the corner minx maxy*/
					Ys1 = maxy;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("fzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("gzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*two point between the corners maxx miny & maxx maxy*/
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("hzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("izi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2<=miny))
					{
					/*last point on the corner minx miny*/
					Ys2 = miny;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("jzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("kzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along maxx*/
				/*point à zk cretes de l'origine maxx maxy dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs1 = maxx;
				ll = (Xs1-Xp) / vect_3[1];
				Ys1 = Yp + ll * vect_3[2];
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + (zk+1) * distc *cos(angle_houle);
				Yp = maxy + (zk+1) * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs2 = maxx;
				ll = (Xs2-Xp) / vect_3[1];
				Ys2 = Yp + ll * vect_3[2];
				if ((Ys1>maxy) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*first point on the corner minx miny*/
					Ys1 = maxy;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("fzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("gzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*two point between the corners minx miny & minx maxy*/
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("hzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("izi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2<=miny))
					{
					/*last point on the corner maxx miny*/
					Ys2 = miny;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("jzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("kzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along miny*/
				/*point à zk cretes de l'origine maxx maxy dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Ys1 = miny;
				ll = (Ys1-Yp) / vect_3[2];
				Xs1 = Xp + ll * vect_3[1];
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + (zk+1) * distc *cos(angle_houle);
				Yp = maxy + (zk+1) * distc *sin(angle_houle);
				Ys2 = miny;
				ll = (Ys2-Yp) / vect_3[2];
				Xs2 = Xp + ll * vect_3[1];

				if ((Xs1>maxx) && (Xs2>minx) && (Xs2<=maxx))
					{
					/*first point on the corner minx maxy*/
					Xs1 = maxx;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				if ((Xs1>minx) && (Xs1<=maxx) && (Xs2>minx) && (Xs2<=maxx))
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				if ((Xs1>minx) && (Xs1<=maxx) && (Xs2<=minx))
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					Xs2 = minx;
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				}
			}
		if (angle_houle == 3.0*PI/2.0)/***************************************************************/
			{
			for (zk=0;zk<=nb_cretes+1;zk++)
				{
				/*lignes parallèles aux cretes*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++; 
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=minx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=maxx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*contour à minx*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=minx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				/*printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + (zk+1) * distc *cos(angle_houle);
				Yp = maxy + (zk+1) * distc *sin(angle_houle);
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=minx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*contour à maxx*/
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
			
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=maxx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				/*printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = maxx + (zk+1) * distc *cos(angle_houle);
				Yp = maxy + (zk+1) * distc *sin(angle_houle);
				zi++;
				if (zi >dim1)
					{
					printf("zi %d > dim1 %d\n",zi,dim1);/**/
					exit(0);
					}
				Houle.X[zi][pa]=maxx;
				Houle.Y[zi][pa]=Yp;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("zi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			}
		if ((angle_houle > 3.0*PI/2.0) && (angle_houle < 2.0*PI))/***************************************************************/
			{
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*crests*/
				/*point à zk cretes de l'origine minx maxy dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				zi++;
				Ys = maxy;			/*premier point sur maxy*/
				ll = (Ys-Yp) / vect_3[2]; 	/*longueur du vecteur reliant le point de la crete XpYp au point sur le bord Ys*/
				Xs = Xp + ll * vect_3[1];	/*absice du point sur le bord*/
				if (Xs > maxx)
					{
					Xs = maxx;
					ll = (Xs-Xp) / vect_3[1];
					Ys = Yp + ll * vect_3[2];
					}
				Houle.X[zi][pa]=Xs;
				Houle.Y[zi][pa]=Ys;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("azi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				zi++;				
				Xs = minx;			/*deuxième point sur maxx a priori*/
				ll = (Xs-Xp) / vect_3[1];	/*longueur du vecteur reliant le point de la crete XpYp au point sur le bord Xs*/
				Ys = Yp + ll * vect_3[2];	/*ordonnee du point sur le bord*/
				if (Ys < miny)
					{
					Ys = miny;
					ll = (Ys-Yp) / vect_3[2];
					Xs = Xp + ll * vect_3[1];
					}
				Houle.X[zi][pa]=Xs;
				Houle.Y[zi][pa]=Ys;
				vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
				distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
				//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

				/*if (pa == 1) printf("bzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along maxy*/
				/*point à zk cretes de l'origine minx maxy dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Ys1 = maxy;
				ll = (Ys1-Yp) / vect_3[2];
				Xs1 = Xp + ll * vect_3[1];
				if (Xs1 < maxx)
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("czi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					Xp = minx + (zk+1) * distc *cos(angle_houle);
					Yp = maxy + (zk+1) * distc *sin(angle_houle);
					zi++;
					Ys2 = maxy;
					ll = (Ys2-Yp) / vect_3[2];
					Xs2 = Xp + ll * vect_3[1];
					if (Xs2 < maxx)
						{
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("dzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					else
						{
						Xs2 = maxx;
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("ezi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along minx*/
				/*point à zk cretes de l'origine minx maxy dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs1 = minx;
				ll = (Xs1-Xp) / vect_3[1];
				Ys1 = Yp + ll * vect_3[2];
				if (Ys1 > miny)
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("czi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					Xp = minx + (zk+1) * distc *cos(angle_houle);
					Yp = maxy + (zk+1) * distc *sin(angle_houle);
					zi++;
					Xs2 = minx;
					ll = (Xs2-Xp) / vect_3[1];
					Ys2 = Yp + ll * vect_3[2];
					if (Ys2 > miny)
						{
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("dzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					else
						{
						Ys2 = miny;
						Houle.X[zi][pa]=Xs2;
						Houle.Y[zi][pa]=Ys2;
						vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
						distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
						//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

						/*if (pa == 1) printf("ezi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
						}
					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along miny*/
				/*point à zk cretes de l'origine minx maxy dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Ys1 = miny;
				ll = (Ys1-Yp) / vect_3[2];
				Xs1 = Xp + ll * vect_3[1];
				
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + (zk+1) * distc *cos(angle_houle);
				Yp = maxy + (zk+1) * distc *sin(angle_houle);
				Ys2 = miny;
				ll = (Ys2-Yp) / vect_3[2];
				Xs2 = Xp + ll * vect_3[1];

				if ((Xs1<=minx) && (Xs2>minx) && (Xs2<=maxx))
					{
					/*first point on the corner minx min y*/
					Xs1 = minx;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				if ((Xs1>minx) && (Xs1<=maxx) && (Xs2>minx) && (Xs2<=maxx))
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				if ((Xs1>minx) && (Xs1<=maxx) && (Xs2>maxx))
					{
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					Xs2 = maxx;
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					}
				}
			for (zk=0;zk<=nb_cretes;zk++)
				{
				/*along maxx*/
				/*point à zk cretes de l'origine minx maxy dans la direction de la houle*/
				Xp = minx + zk * distc *cos(angle_houle);
				Yp = maxy + zk * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs1 = maxx;
				ll = (Xs1-Xp) / vect_3[1];
				Ys1 = Yp + ll * vect_3[2];
				/*point à zk cretes de l'origine minx miny dans la direction de la houle*/
				Xp = minx + (zk+1) * distc *cos(angle_houle);
				Yp = maxy + (zk+1) * distc *sin(angle_houle);
				/*printf("zk %d minxy %lf %lf distc %lf ah %lf Xp %lf Yp %lf\n",zk,minx,miny,distc,angle_houle,Xp,Yp);*/
				Xs2 = maxx;
				ll = (Xs2-Xp) / vect_3[1];
				Ys2 = Yp + ll * vect_3[2];
				if ((Ys1>maxy) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*first point on the corner maxx miny*/
					Ys1 = maxy;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("fzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("gzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2>miny) && (Ys2<=maxy))
					{
					/*two point between the corners maxx miny & maxx maxy*/
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("hzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("izi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				if ((Ys1>miny) && (Ys1<=maxy) && (Ys2<=miny))
					{
					/*last point on the corner maxx maxy*/
					Ys2 = miny;
					zi++;
					Houle.X[zi][pa]=Xs1;
					Houle.Y[zi][pa]=Ys1;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("jzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					zi++;
					Houle.X[zi][pa]=Xs2;
					Houle.Y[zi][pa]=Ys2;
					vect_1[1] = Houle.X[zi][pa];		vect_1[2] = Houle.Y[zi][pa];		vect_1[3] = 0.0;
					distw =  produit_scal(vect_1, vect_2);	/*distance between origin and the point along wave direction*/
					//Houle.Z[zi][pa] =   Houle.hh1/2  * sin(2.0*PI*(temps[pa]/Houle.periode - distw/Houle.lambda));
				if (Structure.wave_model == 1) Houle.Z[zi][pa] = Houle.hh1/2.0 * cos(Houle.k*distw-Houle.omega*temps[pa]);
				if (Structure.wave_model == 2) Houle.Z[zi][pa] = Houle.hh1/2.0*((Houle.hh1/2*Houle.k*(3.0-pow(tanh(Houle.depth*Houle.k),2.0))*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/(4.0*pow(tanh(Houle.depth*Houle.k),3.0))+cos(Houle.k*distw-Houle.omega*temps[pa]));
				if (Structure.wave_model == 3) Houle.Z[zi][pa] = (Houle.hh1/2.0)*((3.0*(Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k*cos(3.0*(Houle.k*distw-Houle.omega*temps[pa])))/8.0+((Houle.hh1/2.0)*Houle.k*cos(2.0*(Houle.k*distw-Houle.omega*temps[pa])))/2.0+(1.0-((Houle.hh1/2.0)*(Houle.hh1/2.0)*Houle.k*Houle.k)/16.0)*cos(Houle.k*distw-Houle.omega*temps[pa]));

					/*if (pa == 1) printf("kzi %d distw %lf X %lf Y %lf Z %lf\n",zi,distw,Houle.X[zi][pa],Houle.Y[zi][pa],Houle.Z[zi][pa]);*/
					}
				}
			}
		Houle.nb_point=zi;
		}
		
	/*rotation de la surface libre en dynamique */
	if (nbtemps > 1)
		{
		for (pa=1;pa<=nbtemps;pa++)
			{ 
			for (zi=1;zi<=Houle.nb_point;zi++)
				{
  				Houle.U[zi][pa] = Houle.X[zi][pa];	Houle.V[zi][pa] = Houle.Y[zi][pa];	Houle.W[zi][pa] = Houle.Z[zi][pa];
				}
			}
		}
		
		
	/* fin modifdp du 17 mars 2010*/
	}

void initialisation_min_max()
	{
	int no,tp;
	
   	/*initialisation des noeuds affiches********************************/
	for (no=1;no<=NOMBRE_NOEUDS;no++)
		{ 
  		Noeud[no].x = Noeud[no].inix;
  		Noeud[no].y = Noeud[no].iniy;
  		Noeud[no].z = Noeud[no].iniz;
		}
	/*initialisation des min et des max*********************************************/
	minx = (REEL) Noeud[1].x;	maxx = (REEL) Noeud[1].x +1.0;
	miny = (REEL) Noeud[1].y;	maxy = (REEL) Noeud[1].y +1.0;
	minz = (REEL) Noeud[1].z;	maxz = (REEL) Noeud[1].z +1.0;
   	
   	/*printf(" min et max de x 	= %10.3f %10.3f\n",minx,maxx);
    	printf(" min et max de y 	= %10.3f %10.3f\n",miny,maxy);
    	printf(" min et max de z 	= %10.3f %10.3f\n",minz,maxz);
    	printf("NOMBRE_NOEUDS = %d\n",NOMBRE_NOEUDS);*/
    	
	for (no=1;no<=NOMBRE_NOEUDS;no++)
		{
		if((REEL) Noeud[no].x < minx) minx = (REEL) Noeud[no].x;
		if((REEL) Noeud[no].x > maxx) maxx = (REEL) Noeud[no].x;
		if((REEL) Noeud[no].y < miny) miny = (REEL) Noeud[no].y;
		if((REEL) Noeud[no].y > maxy) maxy = (REEL) Noeud[no].y;
		if((REEL) Noeud[no].z < minz) minz = (REEL) Noeud[no].z;
		if((REEL) Noeud[no].z > maxz) maxz = (REEL) Noeud[no].z;
		}
	if (nbtemps > 1)
		{
		for (no=1;no<=NOMBRE_NOEUDS;no++)
			{
			for (tp=1;tp<=nbtemps;tp++)
				{
				if((REEL) Noeud[no].dx[tp] < minx) minx = (REEL) Noeud[no].dx[tp];
				if((REEL) Noeud[no].dx[tp] > maxx) maxx = (REEL) Noeud[no].dx[tp];
				if((REEL) Noeud[no].dy[tp] < miny) miny = (REEL) Noeud[no].dy[tp];
				if((REEL) Noeud[no].dy[tp] > maxy) maxy = (REEL) Noeud[no].dy[tp];
				if((REEL) Noeud[no].dz[tp] < minz) minz = (REEL) Noeud[no].dz[tp];
				if((REEL) Noeud[no].dz[tp] > maxz) maxz = (REEL) Noeud[no].dz[tp];
				}
			}
		}
	if (fabsf(maxx - minx) >= fabsf(maxy - miny) && fabsf(maxx - minx) >= fabsf(maxz - minz) ) ecartmax = fabsf(maxx - minx);
	if (fabsf(maxy - miny) >= fabsf(maxz - minz) && fabsf(maxy - miny) >= fabsf(maxx - minx) ) ecartmax = fabsf(maxy - miny);
	if (fabsf(maxz - minz) >= fabsf(maxx - minx) && fabsf(maxz - minz) >= fabsf(maxy - miny) ) ecartmax = fabsf(maxz - minz);

	/* debut modifdp du 16 mars 2010*/
	if (fabsf(maxx - minx) < ecartmax/3.0)
		{
		/*maxx and minx are too close*/
		maxx = (maxx + minx)/2.0 + ecartmax/6.0;
		minx = (maxx + minx)/2.0 - ecartmax/6.0;
		}
	if (fabsf(maxy - miny) < ecartmax/3.0)
		{
		/*maxy and miny are too close*/
		maxy = (maxy + miny)/2.0 + ecartmax/6.0;
		miny = (maxy + miny)/2.0 - ecartmax/6.0;
		}
	if (fabsf(maxz - minz) < ecartmax/3.0)
		{
		/*maxz and minz are too close*/
		maxz = (maxz + minz)/2.0 + ecartmax/6.0;
		minz = (maxz + minz)/2.0 - ecartmax/6.0;
		}
	/* fin modifdp du 16 mars 2010*/
		

   	/*printf(" min et max de x 	= %10.3f %10.3f\n",minx,maxx);
    	printf(" min et max de y 	= %10.3f %10.3f\n",miny,maxy);
    	printf(" min et max de z 	= %10.3f %10.3f\n",minz,maxz);
    	printf("ecartmax 		= %f\n",ecartmax);
    	printf("max - min de x 	= %10.3f \n",fabsf(maxx - minx));
     	printf("max - min de y 	= %10.3f \n",fabsf(maxy - miny));
   	printf("max - min de z 	= %10.3f \n",fabsf(maxz - minz));*/
	
	/*initialisation du repere d axes x y et z*/
	repere[1][1] = minx; 			repere[2][1] = miny; 			repere[3][1] = minz;
	repere[1][2] = minx+ecartmax/5.0; 	repere[2][2] = miny; 			repere[3][2] = minz;
	repere[1][3] = minx; 			repere[2][3] = miny+ecartmax/5.0; 	repere[3][3] = minz;
	repere[1][4] = minx; 			repere[2][4] = miny; 			repere[3][4] = minz+ecartmax/5.0;
	
	repere[1][1] = 0.0; 			repere[2][1] = 0.0; 			repere[3][1] = 0.0;
	repere[1][2] = 0.0+ecartmax/5.0; 	repere[2][2] = 0.0; 			repere[3][2] = 0.0;
	repere[1][3] = 0.0; 			repere[2][3] = 0.0+ecartmax/5.0; 	repere[3][3] = 0.0;
	repere[1][4] = 0.0; 			repere[2][4] = 0.0; 			repere[3][4] = 0.0+ecartmax/5.0;
	
	/*initialisation de la surface libre*/
	surface_libre[1][1] = minx; surface_libre[2][1] = miny; surface_libre[3][1] = 0.0;
	surface_libre[1][2] = minx; surface_libre[2][2] = maxy; surface_libre[3][2] = 0.0;
	surface_libre[1][3] = maxx; surface_libre[2][3] = maxy; surface_libre[3][3] = 0.0;
	surface_libre[1][4] = maxx; surface_libre[2][4] = miny; surface_libre[3][4] = 0.0;
	
	/*initialisation de la surface du fond*/
	surface_fond[1][1] = minx; surface_fond[2][1] = miny; surface_fond[3][1] = -Houle.depth;
	surface_fond[1][2] = minx; surface_fond[2][2] = maxy; surface_fond[3][2] = -Houle.depth;
	surface_fond[1][3] = maxx; surface_fond[2][3] = maxy; surface_fond[3][3] = -Houle.depth;
	surface_fond[1][4] = maxx; surface_fond[2][4] = miny; surface_fond[3][4] = -Houle.depth;
	
    	/*printf("depth %10.3f \n",Houle.depth);
    	printf("surface_fond %10.3f \n",surface_fond[3][1]);
    	printf("surface_fond %10.3f \n",surface_fond[3][2]);
    	printf("surface_fond %10.3f \n",surface_fond[3][3]);
    	printf("surface_fond %10.3f \n",surface_fond[3][4]);
    	exit(0);*/
	
	
	/*initialisation de la volume value*/
	if (Structure.nb_value == 1)
		{
		volume_value[1][1] = minx;	volume_value_dessine[1][1] = minx;
		volume_value[1][2] = maxx;	volume_value_dessine[1][2] = maxx;
		volume_value[1][3] = maxx;	volume_value_dessine[1][3] = maxx;
		volume_value[1][4] = minx;	volume_value_dessine[1][4] = minx;
		volume_value[1][5] = minx;	volume_value_dessine[1][5] = minx;
		volume_value[1][6] = maxx;	volume_value_dessine[1][6] = maxx;
		volume_value[1][7] = maxx;	volume_value_dessine[1][7] = maxx;
		volume_value[1][8] = minx;	volume_value_dessine[1][8] = minx;
		volume_value[2][1] = miny;	volume_value_dessine[2][1] = miny;
		volume_value[2][2] = miny;	volume_value_dessine[2][2] = miny;
		volume_value[2][3] = maxy;	volume_value_dessine[2][3] = maxy;
		volume_value[2][4] = maxy;	volume_value_dessine[2][4] = maxy;
		volume_value[2][5] = miny;	volume_value_dessine[2][5] = miny;
		volume_value[2][6] = miny;	volume_value_dessine[2][6] = miny;
		volume_value[2][7] = maxy;	volume_value_dessine[2][7] = maxy;
		volume_value[2][8] = maxy;	volume_value_dessine[2][8] = maxy;
		volume_value[3][1] = Value.depth1[Structure.nb_value];	volume_value_dessine[3][1] = Value.depth1[Structure.nb_value];
		volume_value[3][2] = Value.depth1[Structure.nb_value];	volume_value_dessine[3][2] = Value.depth1[Structure.nb_value];
		volume_value[3][3] = Value.depth1[Structure.nb_value];	volume_value_dessine[3][3] = Value.depth1[Structure.nb_value];
		volume_value[3][4] = Value.depth1[Structure.nb_value];	volume_value_dessine[3][4] = Value.depth1[Structure.nb_value];
		volume_value[3][5] = Value.depth2[Structure.nb_value];	volume_value_dessine[3][5] = Value.depth2[Structure.nb_value];
		volume_value[3][6] = Value.depth2[Structure.nb_value];	volume_value_dessine[3][6] = Value.depth2[Structure.nb_value];
		volume_value[3][7] = Value.depth2[Structure.nb_value];	volume_value_dessine[3][7] = Value.depth2[Structure.nb_value];
		volume_value[3][8] = Value.depth2[Structure.nb_value];	volume_value_dessine[3][8] = Value.depth2[Structure.nb_value];
		}
	if (Structure.nb_value > 1)
		{
		if (volume_value[3][1] > Value.depth1[Structure.nb_value]) volume_value[3][1] = Value.depth1[Structure.nb_value];	if (volume_value_dessine[3][1] > Value.depth1[Structure.nb_value]) volume_value_dessine[3][1] = Value.depth1[Structure.nb_value];
		if (volume_value[3][2] > Value.depth1[Structure.nb_value]) volume_value[3][2] = Value.depth1[Structure.nb_value];	if (volume_value_dessine[3][2] > Value.depth1[Structure.nb_value]) volume_value_dessine[3][2] = Value.depth1[Structure.nb_value];
		if (volume_value[3][3] > Value.depth1[Structure.nb_value]) volume_value[3][3] = Value.depth1[Structure.nb_value];	if (volume_value_dessine[3][3] > Value.depth1[Structure.nb_value]) volume_value_dessine[3][3] = Value.depth1[Structure.nb_value];
		if (volume_value[3][4] > Value.depth1[Structure.nb_value]) volume_value[3][4] = Value.depth1[Structure.nb_value];	if (volume_value_dessine[3][4] > Value.depth1[Structure.nb_value]) volume_value_dessine[3][4] = Value.depth1[Structure.nb_value];
		if (volume_value[3][5] < Value.depth2[Structure.nb_value]) volume_value[3][5] = Value.depth2[Structure.nb_value];	if (volume_value_dessine[3][5] < Value.depth2[Structure.nb_value]) volume_value_dessine[3][5] = Value.depth2[Structure.nb_value];
		if (volume_value[3][6] < Value.depth2[Structure.nb_value]) volume_value[3][6] = Value.depth2[Structure.nb_value];	if (volume_value_dessine[3][6] < Value.depth2[Structure.nb_value]) volume_value_dessine[3][6] = Value.depth2[Structure.nb_value];
		if (volume_value[3][7] < Value.depth2[Structure.nb_value]) volume_value[3][7] = Value.depth2[Structure.nb_value];	if (volume_value_dessine[3][7] < Value.depth2[Structure.nb_value]) volume_value_dessine[3][7] = Value.depth2[Structure.nb_value];
		if (volume_value[3][8] < Value.depth2[Structure.nb_value]) volume_value[3][8] = Value.depth2[Structure.nb_value];	if (volume_value_dessine[3][8] < Value.depth2[Structure.nb_value]) volume_value_dessine[3][8] = Value.depth2[Structure.nb_value];
		}
	/*initialisation de la surface du front*/
	/*
	surface_front[1][1] = frontx; surface_front[2][1] = miny; surface_front[3][1] = minz;
	surface_front[1][2] = frontx; surface_front[2][2] = maxy; surface_front[3][2] = minz;
	surface_front[1][3] = frontx; surface_front[2][3] = maxy; surface_front[3][3] = maxz;
	surface_front[1][4] = frontx; surface_front[2][4] = miny; surface_front[3][4] = maxz;
	*/
	
	/*initialisation de la limite de trace sans zoom*/
	ccartmax = ecartmax;
	cinx = minx;
	ciny = miny;
	cinz = minz;
	caxx = maxx;
	caxy = maxy;
	caxz = maxz;
	
	/*mise a l echelle*/
	if (((caxx - cinx)*RESOLUTION_Y_FEN)>((caxy - ciny)*RESOLUTION_X_FEN))
		{
		caxy = ciny + (caxx - cinx) * RESOLUTION_Y_FEN / RESOLUTION_X_FEN;
		}
	else
		{
		caxx = cinx + (caxy - ciny) * RESOLUTION_X_FEN / RESOLUTION_Y_FEN;
		}
		
	/*initialisation de la limite de trace avec zoom*/
	binx = cinx - marge * (caxx - cinx);
	biny = ciny - marge * (caxy - ciny);
	baxx = caxx + marge * (caxx - cinx);
	baxy = caxy + marge * (caxy - ciny);
	/*if (baxx - binx == 0.0) { printf("baxx - binx = 0.0   \n"); exit(0); }*/
	if (baxx - binx == 0.0) baxx = binx + 1.0;
	/*if (baxy - biny == 0.0) { printf("baxx - binx = 0.0   \n"); exit(0); }*/
	if (baxy - biny == 0.0) baxy = biny + 1.0;
	
	/*
	printf("RESOLUTION_X_FEN et RESOLUTION_Y_FEN = %f %f\n",RESOLUTION_X_FEN,RESOLUTION_Y_FEN);
	printf("cinx et caxx = %f %f\n",cinx,caxx);
	printf("ciny et caxy = %f %f\n",ciny,caxy);
	printf("binx et baxx = %f %f\n",binx,baxx);
	printf("biny et baxy = %f %f\n",biny,baxy);
	*/
		
	/*initialisation de la profondeur de coupe***************************/
	profondeur_coupe = 1.0;
    	profondeur_coupe_float = cinz + profondeur_coupe * (caxz-cinz);
	
    	/*initialisation des angles de rotation********************************/
    	angle_x = 0.0;
    	angle_y = 0.0;
    	angle_z = 0.0;
    	
 	/*recuperation de la backgroundcolor*/
	backgroundcolor = GetBgColor(w[4]);
	for(no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES+NOMBRE_WINCHS+Ball.nb+NOMBRE_NOEUDS;no++)
		{
		profondeur[no] = no;
		}

  	tri();
	}
	
void initialisation_surface_front()
	{
  	int elem,sommet1,sommet2,sommet3,compteur,coin,nb_teta;
  	double coordx1,coordx2,coordx3,coordy1,coordy2,coordy3,coordz1,coordz2,coordz3;
  	double mminy,mmaxy,mminz,mmaxz,teta,gamma,xx,yy,zz;
  	
  	/*printf("initialisation_surface_front \n"); */

	changement_variable_catch();
  	compteur = 0;
	/*printf("frontx %8.2f \n",frontx); 
	printf("mminy %8.2f mmaxy %8.2f \n",mminy,mmaxy); 
	printf("mminz %8.2f mmaxz %8.2f \n",mminz,mmaxz);*/
  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
  		sommet1 = Surface[elem].extremite[1];
  		sommet2 = Surface[elem].extremite[2];
  		sommet3 = Surface[elem].extremite[3];
  		coordx1 = wfcodend[3*sommet1-2];	coordy1 = wfcodend[3*sommet1-1];	coordz1 = wfcodend[3*sommet1-0];
  		coordx2 = wfcodend[3*sommet2-2];	coordy2 = wfcodend[3*sommet2-1];	coordz2 = wfcodend[3*sommet2-0];
  		coordx3 = wfcodend[3*sommet3-2];	coordy3 = wfcodend[3*sommet3-1];	coordz3 = wfcodend[3*sommet3-0];
  		if (((coordx1<=frontx) && (coordx2>=frontx)) || ((coordx1>=frontx) && (coordx2<=frontx)))
  			{
  			compteur++;
  			if (compteur == 1)
  				{
				mminy= coordy1; mminz = coordz1;
				mmaxy= coordy1; mmaxz = coordz1;
  				}
  			if (coordy1 < mminy)	mminy = coordy1;
  			if (coordy2 < mminy)	mminy = coordy2;
  			if (coordy1 > mmaxy)	mmaxy = coordy1;
   			if (coordy2 > mmaxy)	mmaxy = coordy2;
  			if (coordz1 < mminz)	mminz = coordz1;
  			if (coordz2 < mminz)	mminz = coordz2;
  			if (coordz1 > mmaxz)	mmaxz = coordz1;
   			if (coordz2 > mmaxz)	mmaxz = coordz2;
 			}
  		if (((coordx1<=frontx) && (coordx3>=frontx)) || ((coordx1>=frontx) && (coordx3<=frontx)))
  			{
  			compteur++;
  			if (compteur == 1)
  				{
				/*printf("compteur 2 %8d \n",compteur); */
				mminy= coordy1; mminz = coordz1;
				mmaxy= coordy1; mmaxz = coordz1;
  				}
  			if (coordy1 < mminy)	mminy = coordy1;
  			if (coordy3 < mminy)	mminy = coordy3;
  			if (coordy1 > mmaxy)	mmaxy = coordy1;
   			if (coordy3 > mmaxy)	mmaxy = coordy3;
  			if (coordz1 < mminz)	mminz = coordz1;
  			if (coordz3 < mminz)	mminz = coordz3;
  			if (coordz1 > mmaxz)	mmaxz = coordz1;
   			if (coordz3 > mmaxz)	mmaxz = coordz3;
   			/*
			printf("mminy 2 %8.2f mmaxy %8.2f \n",mminy,mmaxy); 
			printf("coordy1 %8.2f ordy3 %8.2f \n",coordy1,coordy3); 
			*/
 			}
  		if (((coordx2<=frontx) && (coordx3>=frontx)) || ((coordx2>=frontx) && (coordx3<=frontx)))
  			{
  			compteur++;
  			if (compteur == 1)
  				{
				/*printf("compteur 2 %8d \n",compteur); */
				mminy= coordy2; mminz = coordz2;
				mmaxy= coordy2; mmaxz = coordz2;
  				}
  			if (coordy2 < mminy)	mminy = coordy2;
  			if (coordy3 < mminy)	mminy = coordy3;
  			if (coordy2 > mmaxy)	mmaxy = coordy2;
   			if (coordy3 > mmaxy)	mmaxy = coordy3;
  			if (coordz2 < mminz)	mminz = coordz2;
  			if (coordz3 < mminz)	mminz = coordz3;
  			if (coordz2 > mmaxz)	mmaxz = coordz2;
   			if (coordz3 > mmaxz)	mmaxz = coordz3;
			
			/*
			printf("mminy 2 %8.2f mmaxy %8.2f \n",mminy,mmaxy); 
			printf("coordy2 %8.2f ordy3 %8.2f \n",coordy2,coordy3); 
			*/
 			}
		}
  	
  	for (elem = 1; elem<= NOMBRE_SURF_HEXA; elem++)
  		{
  		sommet1 = Surf_Hexa[elem].extremite[1];
  		sommet2 = Surf_Hexa[elem].extremite[2];
  		sommet3 = Surf_Hexa[elem].extremite[3];
  		coordx1 = wfcodend[3*sommet1-2];	coordy1 = wfcodend[3*sommet1-1];	coordz1 = wfcodend[3*sommet1-0];
  		coordx2 = wfcodend[3*sommet2-2];	coordy2 = wfcodend[3*sommet2-1];	coordz2 = wfcodend[3*sommet2-0];
  		coordx3 = wfcodend[3*sommet3-2];	coordy3 = wfcodend[3*sommet3-1];	coordz3 = wfcodend[3*sommet3-0];
  		if (((coordx1<=frontx) && (coordx2>=frontx)) || ((coordx1>=frontx) && (coordx2<=frontx)))
  			{
  			compteur++;
  			if (compteur == 1)
  				{
				mminy= coordy1; mminz = coordz1;
				mmaxy= coordy1; mmaxz = coordz1;
  				}
  			if (coordy1 < mminy)	mminy = coordy1;
  			if (coordy2 < mminy)	mminy = coordy2;
  			if (coordy1 > mmaxy)	mmaxy = coordy1;
   			if (coordy2 > mmaxy)	mmaxy = coordy2;
  			if (coordz1 < mminz)	mminz = coordz1;
  			if (coordz2 < mminz)	mminz = coordz2;
  			if (coordz1 > mmaxz)	mmaxz = coordz1;
   			if (coordz2 > mmaxz)	mmaxz = coordz2;
 			}
  		if (((coordx1<=frontx) && (coordx3>=frontx)) || ((coordx1>=frontx) && (coordx3<=frontx)))
  			{
  			compteur++;
  			if (compteur == 1)
  				{
				/*printf("compteur 2 %8d \n",compteur); */
				mminy= coordy1; mminz = coordz1;
				mmaxy= coordy1; mmaxz = coordz1;
  				}
  			if (coordy1 < mminy)	mminy = coordy1;
  			if (coordy3 < mminy)	mminy = coordy3;
  			if (coordy1 > mmaxy)	mmaxy = coordy1;
   			if (coordy3 > mmaxy)	mmaxy = coordy3;
  			if (coordz1 < mminz)	mminz = coordz1;
  			if (coordz3 < mminz)	mminz = coordz3;
  			if (coordz1 > mmaxz)	mmaxz = coordz1;
   			if (coordz3 > mmaxz)	mmaxz = coordz3;
   			/*
			printf("mminy 2 %8.2f mmaxy %8.2f \n",mminy,mmaxy); 
			printf("coordy1 %8.2f ordy3 %8.2f \n",coordy1,coordy3); 
			*/
 			}
  		if (((coordx2<=frontx) && (coordx3>=frontx)) || ((coordx2>=frontx) && (coordx3<=frontx)))
  			{
  			compteur++;
  			if (compteur == 1)
  				{
				/*printf("compteur 2 %8d \n",compteur); */
				mminy= coordy2; mminz = coordz2;
				mmaxy= coordy2; mmaxz = coordz2;
  				}
  			if (coordy2 < mminy)	mminy = coordy2;
  			if (coordy3 < mminy)	mminy = coordy3;
  			if (coordy2 > mmaxy)	mmaxy = coordy2;
   			if (coordy3 > mmaxy)	mmaxy = coordy3;
  			if (coordz2 < mminz)	mminz = coordz2;
  			if (coordz3 < mminz)	mminz = coordz3;
  			if (coordz2 > mmaxz)	mmaxz = coordz2;
   			if (coordz3 > mmaxz)	mmaxz = coordz3;
			
			/*
			printf("mminy 2 %8.2f mmaxy %8.2f \n",mminy,mmaxy); 
			printf("coordy2 %8.2f ordy3 %8.2f \n",coordy2,coordy3); 
			*/
 			}
		}

  	if (Prise.catch_gravity > 0.0)			/*in this case the codend is expected to be outside the water and affected by the gravity*/
  		{
	  	surface_front[1][1] =  (float) mmaxz;
	  	surface_front[2][1] =  (float) mminy;
	  	surface_front[3][1] =  (float) frontx;
	  	surface_front[1][2] =  (float) mmaxz;
	  	surface_front[2][2] =  (float) mmaxy;
	  	surface_front[3][2] =  (float) frontx;
	  	surface_front[1][3] =  (float) mminz;
	  	surface_front[2][3] =  (float) mmaxy;
	  	surface_front[3][3] =  (float) frontx;
	  	surface_front[1][4] =  (float) mminz;
	  	surface_front[2][4] =  (float) mminy;
	  	surface_front[3][4] =  (float) frontx;
  		}
  	else						/*in this case the codend is expected to be inside the water and affected by the current*/
  		{
	  	surface_front[1][1] =  (float) (frontx * cos(PI/180.0*Courant.direction) - mminy * sin(PI/180.0*Courant.direction));
	  	surface_front[2][1] =  (float) (frontx * sin(PI/180.0*Courant.direction) + mminy * cos(PI/180.0*Courant.direction));
	  	surface_front[3][1] =  (float) mminz;
	  	surface_front[1][2] =  (float) (frontx * cos(PI/180.0*Courant.direction) - mminy * sin(PI/180.0*Courant.direction));
	  	surface_front[2][2] =  (float) (frontx * sin(PI/180.0*Courant.direction) + mminy * cos(PI/180.0*Courant.direction));
	  	surface_front[3][2] =  (float) mmaxz;
	  	surface_front[1][3] =  (float) (frontx * cos(PI/180.0*Courant.direction) - mmaxy * sin(PI/180.0*Courant.direction));
	  	surface_front[2][3] =  (float) (frontx * sin(PI/180.0*Courant.direction) + mmaxy * cos(PI/180.0*Courant.direction));
	  	surface_front[3][3] =  (float) mmaxz;
	  	surface_front[1][4] =  (float) (frontx * cos(PI/180.0*Courant.direction) - mmaxy * sin(PI/180.0*Courant.direction));
	  	surface_front[2][4] =  (float) (frontx * sin(PI/180.0*Courant.direction) + mmaxy * cos(PI/180.0*Courant.direction));
	  	surface_front[3][4] =  (float) mminz;
  		}
	
	/*
	printf("compteur %8d \n",compteur); 
	printf("frontx %8.2f \n",frontx); 
	printf("mminy %8.2f mmaxy %8.2f \n",mminy,mmaxy); 
	printf("mminz %8.2f mmaxz %8.2f \n",mminz,mmaxz); 
  	for (elem = 1; elem<= 4; elem++)
  		{
		printf("surface_front "); 
		printf(" %8.2f  %8.2f  %8.2f \n",surface_front[1][elem],surface_front[2][elem],surface_front[3][elem]); 
  		}
  	*/
  	
  	for (elem = 1; elem<= 4; elem++)
  		{
  		for (coin = 1; coin<= 3; coin++)
  			{
  			surface_front_dessine[coin][elem] = surface_front[coin][elem];
  			}
  		}
  		
  	/*initialisation de la surface interne de la prise*/
  	nb_teta = 20;						/*nb de points sur l'ellipse*/
  	gamma = acos(Prise.distance_front/Prise.axial_radius);	/*angle du front*/
	/*printf("ellipse: Prise.axial_radius %8.3lf Prise.radial_radius %8.3lf Prise.distance_front %8.3lf \n",Prise.axial_radius,Prise.radial_radius,Prise.distance_front);*/
  	for (elem = 0; elem<= nb_teta; elem++)
  		{
  		teta = -gamma + elem * 2*gamma/nb_teta;
  		surface_inner[1][elem] = Prise.Ox + Prise.axial_radius * cos(teta);
  		surface_inner[2][elem] = Prise.Oy;
  		surface_inner[3][elem] = Prise.Oz + Prise.radial_radius * sin(teta);
		surface_inner_dessine[1][elem] = surface_inner[1][elem];		
		surface_inner_dessine[2][elem] = surface_inner[2][elem];		
		surface_inner_dessine[3][elem] = surface_inner[3][elem];		
		/*printf("ellipse: elem %4d teta %8.3lf xx %8.3lf yy %8.3lf \n",elem,teta,surface_inner[1][elem],surface_inner[3][elem]);*/
		}
	}
	
void changement_variable_catch()
	{
	/*
	changement de variables pour que x (wfcodend) soit parallele au courant et horizontal
	y perpendiculaire au courant et horizontal et z inchange cad vertical ascendant
	*/
	
  	int elem;

	/*printf("Courant.direction %8.2f \n",Courant.direction); */
  	
  	if (Prise.catch_gravity > 0.0)			/*in this case the codend is expected to be outside the water and affected by the gravity*/
  		{
	  	for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
	  		{
	  		wfcodend[3*elem-2] =   Noeud[elem].iniz;
	  		wfcodend[3*elem-1] =   Noeud[elem].iniy;
	  		wfcodend[3*elem-0] =   Noeud[elem].inix;
			}
  		}
  	else						/*in this case the codend is expected to be inside the water and affected by the current*/
  		{
	  	for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
	  		{
	  		wfcodend[3*elem-2] =   Noeud[elem].inix * cos(PI/180.0*Courant.direction) + Noeud[elem].iniy * sin(PI/180.0*Courant.direction);
	  		wfcodend[3*elem-1] = - Noeud[elem].iniy * sin(PI/180.0*Courant.direction) + Noeud[elem].iniy * cos(PI/180.0*Courant.direction);
	  		wfcodend[3*elem-0] =   Noeud[elem].iniz;
			}
		}
	}
			
void initialisation_color_side()
	{
	int no,el,sommet1,sommet2,sommet3,extremite1,extremite2,co;
	/*double Relaxation,min_energy,max_energy,min_tension,max_tension,min_stress,max_stress;*/
	
	initialisation_nb_color();
	
	min_tension1 = Surface[1].tension1;								max_tension1 = Surface[1].tension1;	
	min_tension2 = Surface[1].tension2;								max_tension2 = Surface[1].tension2;	
	min_energy = Surface[1].nrj;									max_energy = Surface[1].nrj;	
	min_stress1 = Surface[1].tension1/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0);	max_stress1 = Surface[1].tension1/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0);	
	min_stress2 = Surface[1].tension1/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0);	max_stress2 = Surface[1].tension1/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0);	
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{
		if (min_tension1 > Surface[no].tension1)								min_tension1 = Surface[no].tension1;
		if (max_tension1 < Surface[no].tension1)								max_tension1 = Surface[no].tension1;
		if (min_tension2 > Surface[no].tension2)								min_tension2 = Surface[no].tension2;
		if (max_tension2 < Surface[no].tension2)								max_tension2 = Surface[no].tension2;
		if (min_energy > Surface[no].nrj)									min_energy = Surface[no].nrj;
		if (max_energy < Surface[no].nrj)									max_energy = Surface[no].nrj;
		if (min_stress1 > Surface[no].tension1/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0))	min_stress1 = Surface[no].tension1/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0);
		if (max_stress1 < Surface[no].tension1/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0))	max_stress1 = Surface[no].tension1/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0);
		if (min_stress2 > Surface[no].tension2/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0))	min_stress2 = Surface[no].tension2/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0);
		if (max_stress2 < Surface[no].tension2/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0))	max_stress2 = Surface[no].tension2/(PI*Surface[1].diametrehydro*Surface[1].diametrehydro/4.0);
		}
	if (max_tension1 == min_tension1) max_tension1 = min_tension1 + 1.0;
	if (max_tension2 == min_tension2) max_tension2 = min_tension2 + 1.0;

	for (no=1;no<=NOMBRE_SURFACES;no++)
		{
		co = (int) ((Surface[no].tension1-min_tension1)/(max_tension1-min_tension1) * nb_col);
		Surface[no].color_side[1]  = colo[co];
		co = (int) ((Surface[no].tension2-min_tension2)/(max_tension2-min_tension2) * nb_col);
		Surface[no].color_side[2]  = colo[co];
		//printf("no %4d tension1 %8.2lf min %8.2lf max %8.2lf co %5d colo %10d  ",no,Surface[no].tension1,min_tension1,max_tension1,co,colo[co]); /**/
		//printf("no %4d tension2 %8.2lf min %8.2lf max %8.2lf co %5d colo %10d\n",no,Surface[no].tension2,min_tension2,max_tension2,co,colo[co]); /**/
		}

	/* La demarche est la meme pour les surfaces a maille hexagonale.*/
	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{
		sommet1 = Surf_Hexa[no].extremite[1];
		sommet2 = Surf_Hexa[no].extremite[2];
		sommet3 = Surf_Hexa[no].extremite[3];
		Surf_Hexa[no].color_side[1]  = GREEN;
		Surf_Hexa[no].color_side[2]  = GREEN;
		Surf_Hexa[no].color_side[3]  = GREEN;
		}
	for (el=1;el<=NOMBRE_ELEMENTS;el++)
		{
		extremite1 = Element[el].extremite[1];
		extremite2 = Element[el].extremite[2];
		}
	}

void initialisation_nb_color()
	{
	int no,rr,gg,bb;
	
	flag_plain_color = FALSE;
	nb_col = 50;
	if (colo != NULL)        free(colo);
	colo = (int *) Malloc_int(1 + nb_col);
	
	for (no=0;no<=nb_col;no++)
		{
		rr = (int) (255*no/nb_col);
		gg = (int) (0);
		/* debut modifdp du 4 mars 2010*/
		bb = (int) (255-rr);
		/* fin modifdp du 17 mars 2010*/
		colo[no] = ColorRGB(rr,gg,bb);
		//printf("no %4d rr %5d gg %5d bb %5d colo %10d\n",no,rr,gg,bb,colo[no]);/**/
		}
	}
	
void initialisation_nb_ufils()
	{
	int no;
	
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{
		Surface[no].nb_ufils = 0; 
		Surface[no].g1_ux = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		Surface[no].g1_uy = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		Surface[no].g1_uz = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		Surface[no].g2_ux = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		Surface[no].g2_uy = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		Surface[no].g2_uz = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		Surface[no].f1_ux = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		Surface[no].f1_uy = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		Surface[no].f2_ux = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		Surface[no].f2_uy = 	(float *) Malloc_float(1 + Surface[no].nb_ufils);
		}
	}
	
void initialisation_nb_vfils()
	{
	int no;
	
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{
		Surface[no].nb_vfils = 0; 
		Surface[no].g1_vx = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		Surface[no].g1_vy = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		Surface[no].g1_vz = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		Surface[no].g2_vx = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		Surface[no].g2_vy = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		Surface[no].g2_vz = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		Surface[no].f1_vx = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		Surface[no].f1_vy = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		Surface[no].f2_vx = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		Surface[no].f2_vy = 	(float *) Malloc_float(1 + Surface[no].nb_vfils);
		}
	}
	
void initialisation_nb_Ufils_hexa()
	{
	int no;
	
	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{
		Surf_Hexa[no].nb_Ufils = 0; 
		Surf_Hexa[no].g1_Ux = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		Surf_Hexa[no].g1_Uy = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		Surf_Hexa[no].g1_Uz = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		Surf_Hexa[no].g2_Ux = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		Surf_Hexa[no].g2_Uy = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		Surf_Hexa[no].g2_Uz = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		Surf_Hexa[no].f1_Ux = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		Surf_Hexa[no].f1_Uy = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		Surf_Hexa[no].f2_Ux = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		Surf_Hexa[no].f2_Uy = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Ufils);
		}
	}
	
void initialisation_nb_Vfils_hexa()
	{
	int no;
	
	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{
		Surf_Hexa[no].nb_Vfils = 0; 
		Surf_Hexa[no].g1_Vx = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		Surf_Hexa[no].g1_Vy = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		Surf_Hexa[no].g1_Vz = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		Surf_Hexa[no].g2_Vx = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		Surf_Hexa[no].g2_Vy = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		Surf_Hexa[no].g2_Vz = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		Surf_Hexa[no].f1_Vx = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		Surf_Hexa[no].f1_Vy = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		Surf_Hexa[no].f2_Vx = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		Surf_Hexa[no].f2_Vy = 	(float *) Malloc_float(1 + Surf_Hexa[no].nb_Vfils);
		}
	}
	
void ajout_symetrique(double decalx, double decaly, double decalz, int signx, int signy, int signz )
	{
	int no,no_su,fils,pa;
	
  	if (2 * NOMBRE_NOEUDS > DIM1)
  		{
    		printf("%s %d \n","Attention : DIM1 dans filwin.h est trop petit, l augmenter jusqu a",6*NOMBRE_NOEUDS+1);
    		exit(0);
  		}
  	if (2 * NOMBRE_ELEMENTS > DIM2)
  		{
    		printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",2*NOMBRE_ELEMENTS+1);
    		exit(0);
  		}
  	if (2 * NOMBRE_SURFACES > DIM2)
  		{
    		printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",2*NOMBRE_SURFACES+1);
    		exit(0);
  		}
  	if (2 * NOMBRE_SURF_HEXA > DIM2)
  		{
    		printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",2*NOMBRE_SURF_HEXA+1);
    		exit(0);
  		}
	for (no=1;no<=NOMBRE_NOEUDS;no++)
		{
		Noeud[no+NOMBRE_NOEUDS].inix 	= 2.0 * decalx + signx * Noeud[no].inix;
		Noeud[no+NOMBRE_NOEUDS].iniy 	= 2.0 * decaly + signy * Noeud[no].iniy;
		Noeud[no+NOMBRE_NOEUDS].iniz 	= 2.0 * decalz + signz * Noeud[no].iniz;

		Noeud[no+NOMBRE_NOEUDS].type 	= Noeud[no].type;
		Noeud[no+NOMBRE_NOEUDS].x 	= Noeud[no].x;
		Noeud[no+NOMBRE_NOEUDS].y 	= Noeud[no].y;
		Noeud[no+NOMBRE_NOEUDS].z 	= Noeud[no].z;
		Noeud[no+NOMBRE_NOEUDS].mx 	= Noeud[no].mx;
		Noeud[no+NOMBRE_NOEUDS].my 	= Noeud[no].my;
		Noeud[no+NOMBRE_NOEUDS].mz 	= Noeud[no].mz;
		Noeud[no+NOMBRE_NOEUDS].majx 	= Noeud[no].majx;
		Noeud[no+NOMBRE_NOEUDS].majy 	= Noeud[no].majy;
		Noeud[no+NOMBRE_NOEUDS].majz 	= Noeud[no].majz;
		Noeud[no+NOMBRE_NOEUDS].sx 	= Noeud[no].sx;
		Noeud[no+NOMBRE_NOEUDS].sy 	= Noeud[no].sy;
		Noeud[no+NOMBRE_NOEUDS].sz 	= Noeud[no].sz;
		Noeud[no+NOMBRE_NOEUDS].cdx 	= Noeud[no].cdx;
		Noeud[no+NOMBRE_NOEUDS].cdy 	= Noeud[no].cdy;
		Noeud[no+NOMBRE_NOEUDS].cdz 	= Noeud[no].cdz;
		Noeud[no+NOMBRE_NOEUDS].fx 	= signx * Noeud[no].fx;
		Noeud[no+NOMBRE_NOEUDS].fy 	= signy * Noeud[no].fy;
		Noeud[no+NOMBRE_NOEUDS].fz 	= signz * Noeud[no].fz;
		Noeud[no+NOMBRE_NOEUDS].depx 	= signx * Noeud[no].depx;
		Noeud[no+NOMBRE_NOEUDS].depy 	= signy * Noeud[no].depy;
		Noeud[no+NOMBRE_NOEUDS].depz 	= signz * Noeud[no].depz;
		Noeud[no+NOMBRE_NOEUDS].fxcal 	= Noeud[no].fxcal;
		Noeud[no+NOMBRE_NOEUDS].fycal 	= Noeud[no].fycal;
		Noeud[no+NOMBRE_NOEUDS].fzcal 	= Noeud[no].fzcal;
		Noeud[no+NOMBRE_NOEUDS].fmx 	= Noeud[no].fmx;
		Noeud[no+NOMBRE_NOEUDS].fmy 	= Noeud[no].fmy;
		Noeud[no+NOMBRE_NOEUDS].fmz 	= Noeud[no].fmz;
		Noeud[no+NOMBRE_NOEUDS].limx 	= Noeud[no].limx;
		Noeud[no+NOMBRE_NOEUDS].limy 	= Noeud[no].limy;
		Noeud[no+NOMBRE_NOEUDS].limz 	= Noeud[no].limz;
		Noeud[no+NOMBRE_NOEUDS].fixx 	= Noeud[no].fixx;
		Noeud[no+NOMBRE_NOEUDS].fixy 	= Noeud[no].fixy;
		Noeud[no+NOMBRE_NOEUDS].fixz 	= Noeud[no].fixz;
		Noeud[no+NOMBRE_NOEUDS].symx 	= Noeud[no].symx;
		Noeud[no+NOMBRE_NOEUDS].symy 	= Noeud[no].symy;
		Noeud[no+NOMBRE_NOEUDS].symz 	= Noeud[no].symz;
		//printf("nbtemps = %8d  \n",nbtemps);
		if (nbtemps > 1)
			{
			Noeud[no+NOMBRE_NOEUDS].dx =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].dx,1 + nbtemps);
			Noeud[no+NOMBRE_NOEUDS].dy =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].dy,1 + nbtemps);
			Noeud[no+NOMBRE_NOEUDS].dz =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].dz,1 + nbtemps);
			Noeud[no+NOMBRE_NOEUDS].ex =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].ex,1 + nbtemps);
			Noeud[no+NOMBRE_NOEUDS].ey =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].ey,1 + nbtemps);
			Noeud[no+NOMBRE_NOEUDS].ez =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].ez,1 + nbtemps);
			Noeud[no+NOMBRE_NOEUDS].hz =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].hz,1 + nbtemps);
			Noeud[no+NOMBRE_NOEUDS].gx =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].gx,1 + nbtemps);
			Noeud[no+NOMBRE_NOEUDS].gy =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].gy,1 + nbtemps);
			Noeud[no+NOMBRE_NOEUDS].gz =        (double *) Realloc_double(Noeud[no+NOMBRE_NOEUDS].gz,1 + nbtemps);
			for (pa=1;pa<=nbtemps;pa++)
				{ 
  				Noeud[no+NOMBRE_NOEUDS].dx[pa] = 2.0 * decalx + signx * Noeud[no].dx[pa];
   				Noeud[no+NOMBRE_NOEUDS].dy[pa] = 2.0 * decaly + signy * Noeud[no].dy[pa];
  				Noeud[no+NOMBRE_NOEUDS].dz[pa] = 2.0 * decalz + signz * Noeud[no].dz[pa];
  				Noeud[no+NOMBRE_NOEUDS].ex[pa] = 2.0 * decalx + signx * Noeud[no].ex[pa];
  				Noeud[no+NOMBRE_NOEUDS].ey[pa] = 2.0 * decaly + signy * Noeud[no].ey[pa];
  				Noeud[no+NOMBRE_NOEUDS].ez[pa] = 2.0 * decalz + signz * Noeud[no].ez[pa];
  				Noeud[no+NOMBRE_NOEUDS].hz[pa] = 2.0 * decalz + signz * Noeud[no].hz[pa];
  				Noeud[no+NOMBRE_NOEUDS].gx[pa] = 2.0 * decalx + signx * Noeud[no].gx[pa];
  				Noeud[no+NOMBRE_NOEUDS].gy[pa] = 2.0 * decaly + signy * Noeud[no].gy[pa];
  				Noeud[no+NOMBRE_NOEUDS].gz[pa] = 2.0 * decalz + signz * Noeud[no].gz[pa];
				//printf("pa = %8d no = %8d NOMBRE_NOEUDS = %8d \n",pa,no,NOMBRE_NOEUDS);
				}
			}
		}
	for (no=1;no<=NOMBRE_ELEMENTS;no++)
		{
		Element[no+NOMBRE_ELEMENTS].extremite[1] 			= Element[no].extremite[1] + NOMBRE_NOEUDS;
		Element[no+NOMBRE_ELEMENTS].extremite[2] 			= Element[no].extremite[2] + NOMBRE_NOEUDS;
		Element[no+NOMBRE_ELEMENTS].pro[1] 			= Element[no].pro[1];
		Element[no+NOMBRE_ELEMENTS].pro[2] 			= Element[no].pro[2];
		Element[no+NOMBRE_ELEMENTS].type 			= Element[no].type;
		Element[no+NOMBRE_ELEMENTS].lgrepos 			= Element[no].lgrepos;
		Element[no+NOMBRE_ELEMENTS].lgtendue 			= Element[no].lgtendue;
		Element[no+NOMBRE_ELEMENTS].raideur_traction 		= Element[no].raideur_traction;
		Element[no+NOMBRE_ELEMENTS].raideur_compression 	= Element[no].raideur_compression;
		Element[no+NOMBRE_ELEMENTS].wt 				= Element[no].wt;
		Element[no+NOMBRE_ELEMENTS].nrj 			= Element[no].nrj;
		Element[no+NOMBRE_ELEMENTS].diametrehydro 		= Element[no].diametrehydro;
		Element[no+NOMBRE_ELEMENTS].rhoelement 			= Element[no].rhoelement;
		Element[no+NOMBRE_ELEMENTS].cdnormal 			= Element[no].cdnormal;
		Element[no+NOMBRE_ELEMENTS].ftangent 			= Element[no].ftangent;
		Element[no+NOMBRE_ELEMENTS].color 			= Element[no].color;
		}
  	NOMBRE_ELEMENTS = 2 * NOMBRE_ELEMENTS;
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{
		no_su = no+NOMBRE_SURFACES;
		Surface[no_su].extremite[1] 			= Surface[no].extremite[1] + NOMBRE_NOEUDS;
		Surface[no_su].extremite[2] 			= Surface[no].extremite[2] + NOMBRE_NOEUDS;
		Surface[no_su].extremite[3] 			= Surface[no].extremite[3] + NOMBRE_NOEUDS;
		Surface[no_su].nx 			= Surface[no].nx;
		Surface[no_su].ny 			= Surface[no].ny;
		Surface[no_su].nz 			= Surface[no].nz;
		Surface[no_su].mx 			= Surface[no].mx;
		Surface[no_su].my 			= Surface[no].my;
		Surface[no_su].mz 			= Surface[no].mz;
		Surface[no_su].defaut_disc 		= Surface[no].defaut_disc;
		Surface[no_su].lgrepos 			= Surface[no].lgrepos;
		Surface[no_su].nb_ufils 		= Surface[no].nb_ufils;		/*non inversion des fils u et v pour une continuite*/
		Surface[no_su].nb_vfils 		= Surface[no].nb_vfils;		/*au plan de symetrie*/
		Surface[no_su].color_u 			= Surface[no].color_u;		
		Surface[no_su].color_v 			= Surface[no].color_v;		
		Surface[no_su].type 			= Surface[no].type;
		Surface[no_su].color_side[1] 		= Surface[no].color_side[1];
		Surface[no_su].color_side[2] 		= Surface[no].color_side[2];
		Surface[no_su].color_side[3] 		= Surface[no].color_side[3];
		Surface[no_su].lon[1] 			= Surface[no].lon[1];		/*non inversion des fils u et v pour une continuite*/
		Surface[no_su].lon[2] 			= Surface[no].lon[2];		/*au plan de symetrie*/
		Surface[no_su].lon[3] 			= Surface[no].lon[3];
		Surface[no_su].lon[4] 			= Surface[no].lon[4];
		Surface[no_su].lon[5] 			= Surface[no].lon[5];
		Surface[no_su].lon[6] 			= Surface[no].lon[6];
		Surface[no_su].raideur_traction 	= Surface[no].raideur_traction;
		Surface[no_su].raideur_compression 	= Surface[no].raideur_compression;
		Surface[no_su].raideur_ouverture 	= Surface[no].raideur_ouverture;
		Surface[no_su].tension1 		= Surface[no].tension1;
		Surface[no_su].tension2 		= Surface[no].tension2;
		Surface[no_su].nrj1 			= Surface[no].nrj1;
		Surface[no_su].nrj2 			= Surface[no].nrj2;
		Surface[no_su].nrj 			= Surface[no].nrj;
		Surface[no_su].lgrepos 			= Surface[no].lgrepos;
		Surface[no_su].diametrehydro 		= Surface[no].diametrehydro;
		Surface[no_su].largeurnoeud 		= Surface[no].largeurnoeud;
		Surface[no_su].rhosurface 		= Surface[no].rhosurface;
		Surface[no_su].cdnormal 		= Surface[no].cdnormal;
		Surface[no_su].ftangent 		= Surface[no].ftangent;
		Surface[no_su].tarp 		        = Surface[no].tarp;
		Surface[no_su].orientation 		= -Surface[no].orientation;	/*pour regler la symetie interne/externe*/
		
		
		
		Surface[no_su].g1_ux = 	(float *) Realloc_float(Surface[no_su].g1_ux,1 + Surface[no_su].nb_ufils);
		Surface[no_su].g1_uy = 	(float *) Realloc_float(Surface[no_su].g1_uy,1 + Surface[no_su].nb_ufils);
		Surface[no_su].g1_uz = 	(float *) Realloc_float(Surface[no_su].g1_uz,1 + Surface[no_su].nb_ufils);
		Surface[no_su].g2_ux = 	(float *) Realloc_float(Surface[no_su].g2_ux,1 + Surface[no_su].nb_ufils);
		Surface[no_su].g2_uy = 	(float *) Realloc_float(Surface[no_su].g2_uy,1 + Surface[no_su].nb_ufils);
		Surface[no_su].g2_uz = 	(float *) Realloc_float(Surface[no_su].g2_uz,1 + Surface[no_su].nb_ufils);
		Surface[no_su].f1_ux = 	(float *) Realloc_float(Surface[no_su].f1_ux,1 + Surface[no_su].nb_ufils);
		Surface[no_su].f1_uy = 	(float *) Realloc_float(Surface[no_su].f1_uy,1 + Surface[no_su].nb_ufils);
		Surface[no_su].f2_ux = 	(float *) Realloc_float(Surface[no_su].f2_ux,1 + Surface[no_su].nb_ufils);
		Surface[no_su].f2_uy = 	(float *) Realloc_float(Surface[no_su].f2_uy,1 + Surface[no_su].nb_ufils);

		/*non intervention des fils u et v pour une continuite au plan de symetrie*/
		for (fils=1;fils<=Surface[no_su].nb_ufils;fils++)
			{
			Surface[no_su].g1_ux[fils] = 2 * decalx + signx * Surface[no].g1_ux[fils];
			Surface[no_su].g1_uy[fils] = 2 * decaly + signy * Surface[no].g1_uy[fils];
			Surface[no_su].g1_uz[fils] = 2 * decalz + signz * Surface[no].g1_uz[fils];
			Surface[no_su].g2_ux[fils] = 2 * decalx + signx * Surface[no].g2_ux[fils];
			Surface[no_su].g2_uy[fils] = 2 * decaly + signy * Surface[no].g2_uy[fils];
			Surface[no_su].g2_uz[fils] = 2 * decalz + signz * Surface[no].g2_uz[fils];
			}
		
		Surface[no_su].g1_vx = 	(float *) Realloc_float(Surface[no_su].g1_vx,1 + Surface[no_su].nb_vfils);
		Surface[no_su].g1_vy = 	(float *) Realloc_float(Surface[no_su].g1_vy,1 + Surface[no_su].nb_vfils);
		Surface[no_su].g1_vz = 	(float *) Realloc_float(Surface[no_su].g1_vz,1 + Surface[no_su].nb_vfils);
		Surface[no_su].g2_vx = 	(float *) Realloc_float(Surface[no_su].g2_vx,1 + Surface[no_su].nb_vfils);
		Surface[no_su].g2_vy = 	(float *) Realloc_float(Surface[no_su].g2_vy,1 + Surface[no_su].nb_vfils);
		Surface[no_su].g2_vz = 	(float *) Realloc_float(Surface[no_su].g2_vz,1 + Surface[no_su].nb_vfils);
		Surface[no_su].f1_vx = 	(float *) Realloc_float(Surface[no_su].f1_vx,1 + Surface[no_su].nb_vfils);
		Surface[no_su].f1_vy = 	(float *) Realloc_float(Surface[no_su].f1_vy,1 + Surface[no_su].nb_vfils);
		Surface[no_su].f2_vx = 	(float *) Realloc_float(Surface[no_su].f2_vx,1 + Surface[no_su].nb_vfils);
		Surface[no_su].f2_vy = 	(float *) Realloc_float(Surface[no_su].f2_vy,1 + Surface[no_su].nb_vfils);

		/*non inversion des fils u et v pour une continuite au plan de symetrie*/
		for (fils=1;fils<=Surface[no_su].nb_vfils;fils++)
			{
			Surface[no_su].g1_vx[fils] = 2 * decalx + signx * Surface[no].g1_vx[fils];
			Surface[no_su].g1_vy[fils] = 2 * decaly + signy * Surface[no].g1_vy[fils];
			Surface[no_su].g1_vz[fils] = 2 * decalz + signz * Surface[no].g1_vz[fils];
			Surface[no_su].g2_vx[fils] = 2 * decalx + signx * Surface[no].g2_vx[fils];
			Surface[no_su].g2_vy[fils] = 2 * decaly + signy * Surface[no].g2_vy[fils];
			Surface[no_su].g2_vz[fils] = 2 * decalz + signz * Surface[no].g2_vz[fils];
			}
		}
		
	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{
		no_su = no+NOMBRE_SURF_HEXA;
		Surf_Hexa[no_su].extremite[1] 		= Surf_Hexa[no].extremite[1] + NOMBRE_NOEUDS;
		Surf_Hexa[no_su].extremite[2] 		= Surf_Hexa[no].extremite[2] + NOMBRE_NOEUDS;
		Surf_Hexa[no_su].extremite[3] 		= Surf_Hexa[no].extremite[3] + NOMBRE_NOEUDS;
		Surf_Hexa[no_su].lx 			= Surf_Hexa[no].lx;
		Surf_Hexa[no_su].ly 			= Surf_Hexa[no].ly;
		Surf_Hexa[no_su].lz 			= Surf_Hexa[no].lz;
		Surf_Hexa[no_su].mx 			= Surf_Hexa[no].mx;
		Surf_Hexa[no_su].my 			= Surf_Hexa[no].my;
		Surf_Hexa[no_su].mz 			= Surf_Hexa[no].mz;
		Surf_Hexa[no_su].nx 			= Surf_Hexa[no].nx;
		Surf_Hexa[no_su].ny 			= Surf_Hexa[no].ny;
		Surf_Hexa[no_su].nz 			= Surf_Hexa[no].nz;
		Surf_Hexa[no_su].lo_repos 		= Surf_Hexa[no].lo_repos;
		Surf_Hexa[no_su].mo_repos 		= Surf_Hexa[no].mo_repos;
		Surf_Hexa[no_su].no_repos 		= Surf_Hexa[no].no_repos;
		Surf_Hexa[no_su].nb_Ufils 		= Surf_Hexa[no].nb_Ufils;		/*non inversion des fils u et v pour une continuite*/
		Surf_Hexa[no_su].nb_Vfils 		= Surf_Hexa[no].nb_Vfils;		/*au plan de symetrie*/
		Surf_Hexa[no_su].color_l 		= Surf_Hexa[no].color_l;		
		Surf_Hexa[no_su].color_m 		= Surf_Hexa[no].color_m;		
		Surf_Hexa[no_su].color_n 		= Surf_Hexa[no].color_n;		
		Surf_Hexa[no_su].type 			= Surf_Hexa[no].type;
		Surf_Hexa[no_su].color_side[1] 		= Surf_Hexa[no].color_side[1];
		Surf_Hexa[no_su].color_side[2] 		= Surf_Hexa[no].color_side[2];
		Surf_Hexa[no_su].color_side[3] 		= Surf_Hexa[no].color_side[3];
		Surf_Hexa[no_su].lon[1] 		= Surf_Hexa[no].lon[1];		/*non inversion des fils u et v pour une continuite*/
		Surf_Hexa[no_su].lon[2] 		= Surf_Hexa[no].lon[2];		/*au plan de symetrie*/
		Surf_Hexa[no_su].lon[3] 		= Surf_Hexa[no].lon[3];
		Surf_Hexa[no_su].lon[4] 		= Surf_Hexa[no].lon[4];
		Surf_Hexa[no_su].lon[5] 		= Surf_Hexa[no].lon[5];
		Surf_Hexa[no_su].lon[6] 		= Surf_Hexa[no].lon[6];
		Surf_Hexa[no_su].raideur_traction_l 	= Surf_Hexa[no].raideur_traction_l;
		Surf_Hexa[no_su].raideur_traction_m 	= Surf_Hexa[no].raideur_traction_m;
		Surf_Hexa[no_su].raideur_traction_n 	= Surf_Hexa[no].raideur_traction_n;
		Surf_Hexa[no_su].raideur_compression_l 	= Surf_Hexa[no].raideur_compression_l;
		Surf_Hexa[no_su].raideur_compression_m 	= Surf_Hexa[no].raideur_compression_m;
		Surf_Hexa[no_su].raideur_compression_n 	= Surf_Hexa[no].raideur_compression_n;
		Surf_Hexa[no_su].tension1 		= Surf_Hexa[no].tension1;
		Surf_Hexa[no_su].tension2 		= Surf_Hexa[no].tension2;
		Surf_Hexa[no_su].tension3 		= Surf_Hexa[no].tension3;
		Surf_Hexa[no_su].nrj1 			= Surf_Hexa[no].nrj1;
		Surf_Hexa[no_su].nrj2 			= Surf_Hexa[no].nrj2;
		Surf_Hexa[no_su].nrj3 			= Surf_Hexa[no].nrj3;
		Surf_Hexa[no_su].nrj 			= Surf_Hexa[no].nrj;
		Surf_Hexa[no_su].diam_hydro_l 		= Surf_Hexa[no].diam_hydro_l;
		Surf_Hexa[no_su].diam_hydro_m 		= Surf_Hexa[no].diam_hydro_m;
		Surf_Hexa[no_su].diam_hydro_n 		= Surf_Hexa[no].diam_hydro_n;
		Surf_Hexa[no_su].rhosurface 		= Surf_Hexa[no].rhosurface;
		Surf_Hexa[no_su].cdnormal 		= Surf_Hexa[no].cdnormal;
		Surf_Hexa[no_su].ftangent 		= Surf_Hexa[no].ftangent;
		Surf_Hexa[no_su].orientation 		= -Surf_Hexa[no].orientation;	/*pour regler la symetie interne/externe*/
		
		Surf_Hexa[no_su].g1_Ux = 	(float *) Realloc_float(Surf_Hexa[no_su].g1_Ux,1 + Surf_Hexa[no_su].nb_Ufils);
		Surf_Hexa[no_su].g1_Uy = 	(float *) Realloc_float(Surf_Hexa[no_su].g1_Uy,1 + Surf_Hexa[no_su].nb_Ufils);
		Surf_Hexa[no_su].g1_Uz = 	(float *) Realloc_float(Surf_Hexa[no_su].g1_Uz,1 + Surf_Hexa[no_su].nb_Ufils);
		Surf_Hexa[no_su].g2_Ux = 	(float *) Realloc_float(Surf_Hexa[no_su].g2_Ux,1 + Surf_Hexa[no_su].nb_Ufils);
		Surf_Hexa[no_su].g2_Uy = 	(float *) Realloc_float(Surf_Hexa[no_su].g2_Uy,1 + Surf_Hexa[no_su].nb_Ufils);
		Surf_Hexa[no_su].g2_Uz = 	(float *) Realloc_float(Surf_Hexa[no_su].g2_Uz,1 + Surf_Hexa[no_su].nb_Ufils);
		Surf_Hexa[no_su].f1_Ux = 	(float *) Realloc_float(Surf_Hexa[no_su].f1_Ux,1 + Surf_Hexa[no_su].nb_Ufils);
		Surf_Hexa[no_su].f1_Uy = 	(float *) Realloc_float(Surf_Hexa[no_su].f1_Uy,1 + Surf_Hexa[no_su].nb_Ufils);
		Surf_Hexa[no_su].f2_Ux = 	(float *) Realloc_float(Surf_Hexa[no_su].f2_Ux,1 + Surf_Hexa[no_su].nb_Ufils);
		Surf_Hexa[no_su].f2_Uy = 	(float *) Realloc_float(Surf_Hexa[no_su].f2_Uy,1 + Surf_Hexa[no_su].nb_Ufils);

		
		/*intervention des fils u et v pour une continuite au plan de symetrie*/
		for (fils=1;fils<=Surf_Hexa[no_su].nb_Ufils;fils++)
			{
			Surf_Hexa[no_su].g1_Ux[fils] = 2 * decalx + signx * Surf_Hexa[no].g1_Ux[fils];
			Surf_Hexa[no_su].g1_Uy[fils] = 2 * decaly + signy * Surf_Hexa[no].g1_Uy[fils];
			Surf_Hexa[no_su].g1_Uz[fils] = 2 * decalz + signz * Surf_Hexa[no].g1_Uz[fils];
			Surf_Hexa[no_su].g2_Ux[fils] = 2 * decalx + signx * Surf_Hexa[no].g2_Ux[fils];
			Surf_Hexa[no_su].g2_Uy[fils] = 2 * decaly + signy * Surf_Hexa[no].g2_Uy[fils];
			Surf_Hexa[no_su].g2_Uz[fils] = 2 * decalz + signz * Surf_Hexa[no].g2_Uz[fils];
			}
		
		Surf_Hexa[no_su].g1_Vx = 	(float *) Realloc_float(Surf_Hexa[no_su].g1_Vx,1 + Surf_Hexa[no_su].nb_Vfils);
		Surf_Hexa[no_su].g1_Vy = 	(float *) Realloc_float(Surf_Hexa[no_su].g1_Vy,1 + Surf_Hexa[no_su].nb_Vfils);
		Surf_Hexa[no_su].g1_Vz = 	(float *) Realloc_float(Surf_Hexa[no_su].g1_Vz,1 + Surf_Hexa[no_su].nb_Vfils);
		Surf_Hexa[no_su].g2_Vx = 	(float *) Realloc_float(Surf_Hexa[no_su].g2_Vx,1 + Surf_Hexa[no_su].nb_Vfils);
		Surf_Hexa[no_su].g2_Vy = 	(float *) Realloc_float(Surf_Hexa[no_su].g2_Vy,1 + Surf_Hexa[no_su].nb_Vfils);
		Surf_Hexa[no_su].g2_Vz = 	(float *) Realloc_float(Surf_Hexa[no_su].g2_Vz,1 + Surf_Hexa[no_su].nb_Vfils);
		Surf_Hexa[no_su].f1_Vx = 	(float *) Realloc_float(Surf_Hexa[no_su].f1_Vx,1 + Surf_Hexa[no_su].nb_Vfils);
		Surf_Hexa[no_su].f1_Vy = 	(float *) Realloc_float(Surf_Hexa[no_su].f1_Vy,1 + Surf_Hexa[no_su].nb_Vfils);
		Surf_Hexa[no_su].f2_Vx = 	(float *) Realloc_float(Surf_Hexa[no_su].f2_Vx,1 + Surf_Hexa[no_su].nb_Vfils);
		Surf_Hexa[no_su].f2_Vy = 	(float *) Realloc_float(Surf_Hexa[no_su].f2_Vy,1 + Surf_Hexa[no_su].nb_Vfils);

		/*non inversion des fils u et v pour une continuite au plan de symetrie*/
		for (fils=1;fils<=Surf_Hexa[no_su].nb_Vfils;fils++)
			{
			Surf_Hexa[no_su].g1_Vx[fils] = 2 * decalx + signx * Surf_Hexa[no].g1_Vx[fils];
			Surf_Hexa[no_su].g1_Vy[fils] = 2 * decaly + signy * Surf_Hexa[no].g1_Vy[fils];
			Surf_Hexa[no_su].g1_Vz[fils] = 2 * decalz + signz * Surf_Hexa[no].g1_Vz[fils];
			Surf_Hexa[no_su].g2_Vx[fils] = 2 * decalx + signx * Surf_Hexa[no].g2_Vx[fils];
			Surf_Hexa[no_su].g2_Vy[fils] = 2 * decaly + signy * Surf_Hexa[no].g2_Vy[fils];
			Surf_Hexa[no_su].g2_Vz[fils] = 2 * decalz + signz * Surf_Hexa[no].g2_Vz[fils];
			}
		}
		
		
  	NOMBRE_SURFACES  = 2 * NOMBRE_SURFACES;
  	NOMBRE_SURF_HEXA = 2 * NOMBRE_SURF_HEXA;
	NOMBRE_NOEUDS    = 2 * NOMBRE_NOEUDS;
	}
	
void recherche_symetrie()
	{
	int no,symx,symy,symz,fils;
	
	/*recherche de point de symetrie*********************/
	symx = 0;	
	symy = 0;	
	symz = 0;	
	Structure.symetry = 0;  	
	for (no=1;no<=NOMBRE_NOEUDS;no++)
  		{
  		if (TypeNoeud[Noeud[no].type].symx != 0) symx = no;
  		if (TypeNoeud[Noeud[no].type].symy != 0) symy = no;
  		if (TypeNoeud[Noeud[no].type].symz != 0) symz = no;
  		}
  		
  	if (symx != 0) Structure.symetry = Structure.symetry + 1; 
  	if (symy != 0) Structure.symetry = Structure.symetry + 2; 
  	if (symz != 0) Structure.symetry = Structure.symetry + 4;
  	
    	printf("symx 	= %5d  ",symx);
    	printf("symy 	= %5d  ",symy);
    	printf("symz 	= %5d  ",symz);
  	
    	printf("Structure.symetry = %5d  \n",Structure.symetry);
  		
  	if (symx != 0) ajout_symetrique((double) Noeud[symx].x,                    0.0,                    0.0, -1, 1, 1);
  	if (symy != 0) ajout_symetrique(                   0.0, (double) Noeud[symy].y,                    0.0,  1,-1, 1);
  	if (symz != 0) ajout_symetrique(                   0.0,                    0.0, (double) Noeud[symz].z,  1, 1,-1);
  	/*
  	*/
  	
	for (no=1;no<=NOMBRE_NOEUDS;no++)
		{
		Noeud[no].x = Noeud[no].inix;
		Noeud[no].y = Noeud[no].iniy;
		Noeud[no].z = Noeud[no].iniz;
		}
		
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{
		for (fils=1;fils<=Surface[no].nb_ufils;fils++)
			{
			Surface[no].f1_ux[fils] = Surface[no].g1_ux[fils];
			Surface[no].f1_uy[fils] = Surface[no].g1_uy[fils];
			Surface[no].f2_ux[fils] = Surface[no].g2_ux[fils];
			Surface[no].f2_uy[fils] = Surface[no].g2_uy[fils];
			}
		}
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{
		for (fils=1;fils<=Surface[no].nb_vfils;fils++)
			{
			Surface[no].f1_vx[fils] = Surface[no].g1_vx[fils];
			Surface[no].f1_vy[fils] = Surface[no].g1_vy[fils];
			Surface[no].f2_vx[fils] = Surface[no].g2_vx[fils];
			Surface[no].f2_vy[fils] = Surface[no].g2_vy[fils];
			}
		}
	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{
		for (fils=1;fils<=Surf_Hexa[no].nb_Ufils;fils++)
			{
			Surf_Hexa[no].f1_Ux[fils] = Surf_Hexa[no].g1_Ux[fils];
			Surf_Hexa[no].f1_Uy[fils] = Surf_Hexa[no].g1_Uy[fils];
			Surf_Hexa[no].f2_Ux[fils] = Surf_Hexa[no].g2_Ux[fils];
			Surf_Hexa[no].f2_Uy[fils] = Surf_Hexa[no].g2_Uy[fils];
			}
		}
	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{
		for (fils=1;fils<=Surf_Hexa[no].nb_Vfils;fils++)
			{
			Surf_Hexa[no].f1_Vx[fils] = Surf_Hexa[no].g1_Vx[fils];
			Surf_Hexa[no].f1_Vy[fils] = Surf_Hexa[no].g1_Vy[fils];
			Surf_Hexa[no].f2_Vx[fils] = Surf_Hexa[no].g2_Vx[fils];
			Surf_Hexa[no].f2_Vy[fils] = Surf_Hexa[no].g2_Vy[fils];
			}
		}
	}
	
	
void portrait()
	{

	if (mode_portrait == FALSE) 
		{
		mode_portrait = TRUE ;
		SetMenuItemChecked(w[75],1);
		}
	else 
		{
		mode_portrait = FALSE;
		SetMenuItemChecked(w[75],0);
		}
	}


void Genere_ps()
	{
	flag_ps = TRUE;
	flag_plain_color = TRUE;
	ClearDrawArea();
	/*strcpy(nom_fichier,GetStringEntry(w_main[1]));*/
	strcpy(nom_fichier,fname1);
	/*Retrace_fenetre();*/
    	printf("fname1 = %s \n",fname1);/**/
	/*mode_portrait = FALSE;*/
	Chk_ps_open();
	dessiner();
	Chk_ps_close();
	flag_ps = FALSE;
	flag_plain_color = FALSE;
	/*printf("convert -density 300 %s.ps %s.jpg \n",fname1,fname1);
	system("convert -density 300 %s.ps s.jpg \n",fname1);*/
	/*system("convert -density 300 ../data_2001/optim/gloria/LM_2_12_s_043_p_02_n_03_X.ps ../data_2001/optim/gloria/LM_2_12_s_043_p_02_n_03_Xa.jpg");*/
	/*system("convert < command.txt");	*/
	/*system("rm *.ps");*/
	}


void initialisation_ps()
	{
	flag_ps  = FALSE; 	/* sortie a l'ecran seulement */
	fic_ps = NULL; 		/* Fichier PostSript non ouvert */
	hauteur_police_ps = 9;
	largeur_police_ps = 6;
	hauteur_police_ps = 7;
	largeur_police_ps = 7;
	mode_portrait = TRUE;
	epaisseur_trait_ps = 0.5;
	flag_delta_carac = FALSE;
	flag_ortho_norm = TRUE;	/*sortie papier postscript a l echelle*/

	axe_x1 = RESOLUTION_X*0.1;
	axe_y1 = RESOLUTION_Y*0.3;
	axe_x2 = RESOLUTION_X*0.9;
	axe_y2 = RESOLUTION_Y*0.9;
	}
	
	
void initialisation_elongation()
	{
	int no,no_mini,no_maxi;
	float rapport;
	
	elongationmin = 1.0; 	/*rapport mini de la longueur tendue a la longueur au repos*/
	elongationmax = 1.0; 	/*rapport maxi de la longueur tendue a la longueur au repos*/
    	/*initialisation des elongations extremes********************************/
	for (no=1;no<=NOMBRE_ELEMENTS;no++)
		{ 
		/*printf("no  %8d     \n",no);*/
/**********************************************************************************************************************************************/
/**********************************************************************************************************************************************/

/**********************************************************************************************************************************************/
		if (Element[no].lgrepos <= 0.0) 
			{ 
			printf("l element %4d a une longueur <= 0 : lgrepos = %8.3f   \n",no,Element[no].lgrepos); exit(0); 
			}
		rapport = (float) Element[no].lgtendue / Element[no].lgrepos;
		if (rapport < elongationmin) elongationmin = rapport;
		if (rapport > elongationmax) elongationmax = rapport;
		}
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{ 
		rapport = (float) sqrt(Surface[no].nx*Surface[no].nx + Surface[no].ny*Surface[no].ny + Surface[no].nz*Surface[no].nz);
		if (Surface[no].lgrepos <= 0.0) { printf("Surface_2 = %8d lgrepos = %8f   \n",no,Surface[no].lgrepos); exit(0); }
		rapport = (float) rapport / Surface[no].lgrepos;
		if (rapport < elongationmin) { elongationmin = rapport; no_mini = no; }
		if (rapport > elongationmax) { elongationmax = rapport; no_maxi = no; }
		
		rapport = (float) sqrt(Surface[no].mx*Surface[no].mx + Surface[no].my*Surface[no].my + Surface[no].mz*Surface[no].mz);
		if (Surface[no].lgrepos <= 0.0) { printf("Surface_3 = %8d lgrepos = %8f   \n",no,Surface[no].lgrepos); exit(0); }
		rapport = (float) rapport / Surface[no].lgrepos;
		if (rapport < elongationmin) { elongationmin = rapport; no_mini = no; }
		if (rapport > elongationmax) { elongationmax = rapport; no_maxi = no; }
		}
	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{ 
		rapport = (float) sqrt(Surf_Hexa[no].lx*Surf_Hexa[no].lx + Surf_Hexa[no].ly*Surf_Hexa[no].ly + Surf_Hexa[no].lz*Surf_Hexa[no].lz);
		if (Surf_Hexa[no].lo_repos <= 0.0) { printf("Surf_Hexa_1 = %8d lo_repos = %8f   \n",no,Surf_Hexa[no].lo_repos); exit(0); }
		rapport = (float) rapport / Surf_Hexa[no].lo_repos;
		if (rapport < elongationmin) { elongationmin = rapport; no_mini = no; }
		if (rapport > elongationmax) { elongationmax = rapport; no_maxi = no; }
		
		rapport = (float) sqrt(Surf_Hexa[no].mx*Surf_Hexa[no].mx + Surf_Hexa[no].my*Surf_Hexa[no].my + Surf_Hexa[no].mz*Surf_Hexa[no].mz);
		if (Surf_Hexa[no].mo_repos <= 0.0) { printf("Surf_Hexa_2 = %8d mo_repos = %8f   \n",no,Surf_Hexa[no].mo_repos); exit(0); }
		rapport = (float) rapport / Surf_Hexa[no].mo_repos;
		if (rapport < elongationmin) { elongationmin = rapport; no_mini = no; }
		if (rapport > elongationmax) { elongationmax = rapport; no_maxi = no; }
		
		rapport = (float) sqrt(Surf_Hexa[no].nx*Surf_Hexa[no].nx + Surf_Hexa[no].ny*Surf_Hexa[no].ny + Surf_Hexa[no].nz*Surf_Hexa[no].nz);
		if (Surf_Hexa[no].no_repos <= 0.0) { printf("Surf_Hexa_3 = %8d no_repos = %8f   \n",no,Surf_Hexa[no].no_repos); exit(0); }
		rapport = (float) rapport / Surf_Hexa[no].no_repos;
		if (rapport < elongationmin) { elongationmin = rapport; no_mini = no; }
		if (rapport > elongationmax) { elongationmax = rapport; no_maxi = no; }
		
		/*printf("Surf_Hexa[no].lx = %lf  ",Surf_Hexa[no].lx);
		printf("Surf_Hexa[no].ly = %lf  ",Surf_Hexa[no].ly);
		printf("Surf_Hexa[no].lz = %lf\n",Surf_Hexa[no].lz);
		printf("Surf_Hexa[no].mx = %lf  ",Surf_Hexa[no].mx);
		printf("Surf_Hexa[no].my = %lf  ",Surf_Hexa[no].my);
		printf("Surf_Hexa[no].mz = %lf\n",Surf_Hexa[no].mz);
		printf("Surf_Hexa[no].nx = %lf  ",Surf_Hexa[no].nx);
		printf("Surf_Hexa[no].ny = %lf  ",Surf_Hexa[no].ny);
		printf("Surf_Hexa[no].nz = %lf\n",Surf_Hexa[no].nz);
		exit(0);*/
		}
	/*tous les fils detendus sont mis en bleu*/
	/*if (elongationmin < 1.0) elongationmin = 1.0;*/
	/*printf("no_mini  %8d no_maxi = %8d \n",no_mini,no_maxi);*/
	}
	
	
	
	
void initialisation_couleur_tension_final()
	{
	int no,rouge,vert,bleu;
	float rapport;
	
    	/*initialisation des couleurs des fils et des elements********************************/
	for (no=1;no<=NOMBRE_ELEMENTS;no++)
		{ 
		/*couleur des fils u*/
		rapport = (float) Element[no].lgtendue;
		if (Element[no].lgrepos <= 0.0) { printf("%8d %8f   ",no,Element[no].lgrepos); exit(0); }
		rapport = (float) rapport / Element[no].lgrepos;
		/*tous les fils detendus sont mis en bleu*/
		if (rapport < 1.0) rapport = 1.0;
		if ((rapport < elongationmin) || (rapport > elongationmax)) 
			{ 
			printf("rapport < elongationmin || (rapport > elongationmax %8d %8f   ",no,rapport); 
			exit(0); 
			}
		if (elongationmax-elongationmin != 0.0)
			{
			rouge = (int) (255.0 * (rapport-elongationmin) / (elongationmax-elongationmin));
			}
		else
			{
			rouge = 0;
			}
		if ((rouge < 0) || (rouge > 255)) 
			{ 
			printf("%8d %8d   ",no,rouge); 
			exit(0); 
			}
		vert  = 0;
		bleu  = 255 - rouge;
		/*printf("rouge %8d  vert %8d  bleu %8d   \n",rouge,vert,bleu); */
		/*Element[no].color = ColorRGB(rouge,vert,bleu);*/
		}
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{ 
		/*couleur des fils u*/
		rapport = (float) sqrt(Surface[no].nx*Surface[no].nx + Surface[no].ny*Surface[no].ny + Surface[no].nz*Surface[no].nz);
		if (Surface[no].lgrepos <= 0.0) { printf("%8d %8f   ",no,Surface[no].lgrepos); exit(0); }
		rapport = (float) rapport / Surface[no].lgrepos;
		/*tous les fils detendus sont mis en bleu*/
		if (rapport < 1.0) rapport = 1.0;
		if ((rapport < elongationmin) || (rapport > elongationmax)) 
			{ 
			printf("rapport < elongationmin || (rapport > elongationmax %8d %8f   ",no,rapport); 
			exit(0); 
			}
		if (elongationmax-elongationmin != 0.0)
			{
			rouge = (int) (255.0 * (rapport-elongationmin) / (elongationmax-elongationmin));
			}
		else
			{
			rouge = 0;
			}
		if ((rouge < 0) || (rouge > 255)) 
			{ 
			printf("%8d %8d   ",no,rouge); 
			exit(0); 
			}
		vert  = 0;
		bleu  = 255 - rouge;
		/*printf("%8d %8d %8d ",rouge,vert,bleu);*/ 
		/*Surface[no].color_u = ColorRGB(rouge,vert,bleu);*/
		Surface[no].color_u = 0;/**/
		
		/*couleur des fils v*/
		rapport = (float) sqrt(Surface[no].mx*Surface[no].mx + Surface[no].my*Surface[no].my + Surface[no].mz*Surface[no].mz);
		if (Surface[no].lgrepos <= 0.0) { printf("%8d %8f   ",no,Surface[no].lgrepos); exit(0); }
		rapport = (float) rapport / Surface[no].lgrepos;
		/*tous les fils detendus sont mis en bleu*/
		if (rapport < 1.0) rapport = 1.0;
		if ((rapport < elongationmin) || (rapport > elongationmax)) 
			{ 
			printf("rapport < elongationmin || (rapport > elongationmax %8d %8f   ",no,rapport); 
			exit(0); 
			}
		if (elongationmax-elongationmin != 0.0)
			{
			rouge = (int) (255.0 * (rapport-elongationmin) / (elongationmax-elongationmin));
			}
		else
			{
			rouge = 0;
			}
		if ((rouge < 0) || (rouge > 255)) 
			{ 
			printf("%8d %8d   ",no,rouge); 
			exit(0); 
			}
		vert  = 0;
		bleu  = 255 - rouge;
		/*printf("%8d %8d %8d \n",rouge,vert,bleu);*/ 
		/*Surface[no].color_v = ColorRGB(rouge,vert,bleu);*/
		Surface[no].color_v = 0;/**/
		}
		
	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{ 
		/*couleur des fils l*/
		rapport = (float) sqrt(Surf_Hexa[no].lx*Surf_Hexa[no].lx + Surf_Hexa[no].ly*Surf_Hexa[no].ly + Surf_Hexa[no].lz*Surf_Hexa[no].lz);
		if (Surf_Hexa[no].lo_repos <= 0.0) { printf("%8d %8f   ",no,Surf_Hexa[no].lo_repos); exit(0); }
		rapport = (float) rapport / Surf_Hexa[no].lo_repos;
		/*tous les fils detendus sont mis en bleu*/
		if (rapport < 1.0) rapport = 1.0;
		if ((rapport < elongationmin) || (rapport > elongationmax)) 
			{ 
			printf("rapport < elongationmin || (rapport > elongationmax %8d %8f   ",no,rapport); 
			exit(0); 
			}
		if (elongationmax-elongationmin != 0.0)
			{
			rouge = (int) (255.0 * (rapport-elongationmin) / (elongationmax-elongationmin));
			}
		else
			{
			rouge = 0;
			}
		if ((rouge < 0) || (rouge > 255)) 
			{ 
			printf("%8d %8d   ",no,rouge); 
			exit(0); 
			}
		vert  = 0;
		bleu  = 255 - rouge;
		/*Surf_Hexa[no].color_l = ColorRGB(rouge,vert,bleu);*/
		
		/*couleur des fils m*/
		rapport = (float) sqrt(Surf_Hexa[no].mx*Surf_Hexa[no].mx + Surf_Hexa[no].my*Surf_Hexa[no].my + Surf_Hexa[no].mz*Surf_Hexa[no].mz);
		if (Surf_Hexa[no].mo_repos <= 0.0) { printf("%8d %8f   ",no,Surf_Hexa[no].mo_repos); exit(0); }
		rapport = (float) rapport / Surf_Hexa[no].mo_repos;
		/*tous les fils detendus sont mis en bleu*/
		if (rapport < 1.0) rapport = 1.0;
		if ((rapport < elongationmin) || (rapport > elongationmax)) 
			{ 
			printf("rapport < elongationmin || (rapport > elongationmax %8d %8f   ",no,rapport); 
			exit(0); 
			}
		if (elongationmax-elongationmin != 0.0)
			{
			rouge = (int) (255.0 * (rapport-elongationmin) / (elongationmax-elongationmin));
			}
		else
			{
			rouge = 0;
			}
		if ((rouge < 0) || (rouge > 255)) 
			{ 
			printf("%8d %8d   ",no,rouge); 
			exit(0); 
			}
		vert  = 0;
		bleu  = 255 - rouge;
		/*Surf_Hexa[no].color_m = ColorRGB(rouge,vert,bleu);*/
		
		/*couleur des fils n*/
		rapport = (float) sqrt(Surf_Hexa[no].nx*Surf_Hexa[no].nx + Surf_Hexa[no].ny*Surf_Hexa[no].ny + Surf_Hexa[no].nz*Surf_Hexa[no].nz);
		if (Surf_Hexa[no].no_repos <= 0.0) { printf("%8d %8f   ",no,Surf_Hexa[no].no_repos); exit(0); }
		rapport = (float) rapport / Surf_Hexa[no].no_repos;
		/*tous les fils detendus sont mis en bleu*/
		if (rapport < 1.0) rapport = 1.0;
		if ((rapport < elongationmin) || (rapport > elongationmax)) 
			{ 
			printf("rapport < elongationmin || (rapport > elongationmax %8d %8f   ",no,rapport); 
			exit(0); 
			}
		if (elongationmax-elongationmin != 0.0)
			{
			rouge = (int) (255.0 * (rapport-elongationmin) / (elongationmax-elongationmin));
			}
		else
			{
			rouge = 0;
			}
		if ((rouge < 0) || (rouge > 255)) 
			{ 
			printf("%8d %8d   ",no,rouge); 
			exit(0); 
			}
		vert  = 0;
		bleu  = 255 - rouge;
		/*Surf_Hexa[no].color_n = ColorRGB(rouge,vert,bleu);*/
		}
	}
	
	
void initialisation_couleur_tension_initial()
	{
	int no,rouge,vert,bleu;

	
    	/*initialisation des couleurs des fils et des elements********************************/
	for (no=1;no<=NOMBRE_ELEMENTS;no++)
		{ 
		/*couleur des fils u*/
		rouge = 0;
		vert  = 0;
		bleu  = 255 - rouge;
		/*Element[no].color = ColorRGB(rouge,vert,bleu);*/
		}
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{ 
		/*couleur des fils u*/
		rouge = 0;
		vert  = 0;
		bleu  = 255 - rouge;
		/*Surface[no].color_u = ColorRGB(rouge,vert,bleu);*/
		
		/*couleur des fils v*/
		rouge = 0;
		vert  = 0;
		bleu  = 255 - rouge;
		/*Surface[no].color_v = ColorRGB(rouge,vert,bleu);*/
		}

	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{ 
		/*couleur des fils l*/
		rouge = 0;
		vert  = 0;
		bleu  = 255 - rouge;
		/*Surf_Hexa[no].color_l = ColorRGB(rouge,vert,bleu);*/
		
		/*couleur des fils m*/
		rouge = 0;
		vert  = 0;
		bleu  = 255 - rouge;
		/*Surf_Hexa[no].color_m = ColorRGB(rouge,vert,bleu);*/

		/*couleur des fils n*/
		rouge = 0;
		vert  = 0;
		bleu  = 255 - rouge;
		/*Surf_Hexa[no].color_n = ColorRGB(rouge,vert,bleu);*/
		}
	}
			
	
void initialisation_couleur_triangle()
	{
	/*
	defini les couleurs des faces internes et externes des triangles
	*/
	gris_interne = ColorRGB(255,255,255);
	gris_externe = ColorRGB(255,255,255);
	gris_interne = ColorRGB(150,150,150);
	gris_externe = ColorRGB(255,255,255);
	
	}
	
	
void initialisation_orientation_triangle()
	{
	int no;

	
    	/*
    	initialisation de l orientation des triangles de tel sorte que le gris interne 
    	soit toujours a l interieur des triangle. C est pourquoi les triangles symetriques 
    	auront une orientation de -1
    	*/
	for (no=1;no<=NOMBRE_SURFACES;no++)
		{ 
		Surface[no].orientation = 1;
		}
	for (no=1;no<=NOMBRE_SURF_HEXA;no++)
		{ 
		Surf_Hexa[no].orientation = 1;
		}
	}
			
	
int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3)
	{
	double  S, S_ref ;
	int inside;
	double surface_triangle(double x1, double y1, double x2, double y2, double x3, double y3);

	/*
	printf(" ");
	printf("um   : %8.2lf ,vm  :  %8.2lf ",um,vm);
	RECHERCHE SI LE NOEUD M DE COORDONNEES FILAIRE um ET vm EST A L INTERIEUR DU CONTOUR  DU triangle 1 2 3 
	de coordonnees u1,v1, u2,v2, u3,v3
	SI A L INTERIEUR DU CONTOUR RETURN = 1
	SI A L EXTERIEUR DU CONTOUR RETURN = 0
	*/

	/*S_REF = SURFACE DU TRIANGLE u1,v1, u2,v2, u3,v3*/
	S_ref = surface_triangle( u1, v1, u2, v2, u3, v3);
	/*S = somme des 3 SURFACEs des TRIANGLEs 12M 13M 23M*/
	S = 0.0;
	S    += surface_triangle( u1, v1, u2, v2, um, vm);
	S    += surface_triangle( u2, v2, u3, v3, um, vm);
	S    += surface_triangle( u3, v3, u1, v1, um, vm);
	/*printf("S_ref   : %8.2lf , S :  %8.2lf \n",S_ref,S);*/
	if ((S > 0.999 * S_ref) && (S < 1.001 * S_ref))
		{
		/*LE NOEUD M EST A L INTERIEUR DU triangle*/
		inside = 1;
		}
	else
		{
		/*LE NOEUD M EST A L exterieur DU triangle*/
		inside = 0;
		}
	return(inside);
	}
	
int segment_secant2(double a1, double b1, double a2, double b2, double x1, double yy1, double x2, double y2)
	{
	double  S, S_ref ;
	int secant;
	double surface_triangle(double x1, double y1, double x2, double y2, double x3, double y3);

	/*
	RECHERCHE SI LE segment a1,b1 a a2,b2 coupe le segment x1,yy1 a x2,y2
	SI les segments sont secants RETURN = 1
	SI non RETURN = 0
	*/

	/*S_REF = somme des SURFACEs du TRIANGLE a1,b1, x1,yy1, x2,y2 et du triangle a2,b2, x1,yy1, x2,y2*/
	/*S     = somme des SURFACEs du TRIANGLE x1,yy1, a1,b1, a2,b2 et du triangle x2,y2, a1,b1, a2,b2*/
	
	S_ref 	= 0.0;
	S_ref  += surface_triangle( a1, b1, x1, yy1, x2, y2);
	S_ref  += surface_triangle( a2, b2, x1, yy1, x2, y2);
	S 	= 0.0;
	S      += surface_triangle( x1, yy1, a1, b1, a2, b2);
	S      += surface_triangle( x2, y2, a1, b1, a2, b2);
	
	/*printf("a1   : %8.2f , b1 :  %8.2f a2   : %8.2f , b2 :  %8.2f \n",a1,b1,a2,b2);
	printf("x1   : %8.2f , yy1 :  %8.2f x2   : %8.2f , y2 :  %8.2f \n",x1,yy1,x2,y2);
	printf("S_ref   : %8.2f , S :  %8.2f \n",S_ref,S);
	printf("S_ref   : %8.2f , S :  %8.2f \n",S_ref,S);*/
	
	if ((S > 0.999 * S_ref) && (S < 1.001 * S_ref))
		{
		/*les segments sont secants*/
		secant = 1;
		}
	else
		{
		/*les segments ne sont pas secants*/
		secant = 0;
		}
	/*printf("secant   : %d d \n",secant);*/
	return(secant);
	}
	
int segment_secant(double a1, double b1, double a2, double b2, double x1, double yy1, double x2, double y2)
	{
	/*
	RECHERCHE SI LE segment a1,b1 a a2,b2 coupe le segment x1,yy1 a x2,y2
	SI les segments sont secants RETURN = 1
	SI non RETURN = 0
	*/
  	int secant;
  	double xx,yy,denom;
	secant = 0;
	
  	
	xx = a1;
	yy = b1;
	
	/*
	cf maple /home/alre/maple/hexagone/secant.map
	denom = (b2-b1) * (x2-x1) - (a2-a1) * (y2-y1) 
	xx et yy sont les coordonnee du point d intercection des 2 droite passant par les 2 segments
	xx =  (-x1*a1*b2-a2*x1*y2+a2*y1*x2+a1*x1*y2-a1*y1*x2+x2*a1*b2-x2*b1*a2+x1*b1*a2)/denom 
	yy =   (b1*a2*y1-b1*a2*y2-b2*x1*y2+b2*y1*x2+b1*x1*y2-b1*y1*x2+b2*a1*y2-b2*a1*y1)/denom
	*/

	denom = (b2-b1) * (x2-x1) - (a2-a1) * (y2-yy1);
	/*printf("denom   : %15.8lf \n",denom);*/
	if (denom != 0.0)
		{
		/*c a d le prod vect des 2 segments n est pas nul*/
		xx =  (-x1*a1*b2-a2*x1*y2+a2*yy1*x2+a1*x1*y2-a1*yy1*x2+x2*a1*b2-x2*b1*a2+x1*b1*a2)/denom;
		yy =   (b1*a2*yy1-b1*a2*y2-b2*x1*y2+b2*yy1*x2+b1*x1*y2-b1*yy1*x2+b2*a1*y2-b2*a1*yy1)/denom;
		/*printf("xx   : %8.2lf , yy :  %8.2lf  \n",xx,yy);*/
		secant =1;
		if (a1 != a2)
			{
			/*printf("a1 != a2 \n");
			printf("xx-a1   : %8.2lf , xx-a2 :  %8.2lf  \n",xx-a1,xx-a2);*/
			
			if (((xx>a1) && (xx>a2)) || ((xx<a1) && (xx<a2)) || ((xx>x1) && (xx>x2)) || ((xx<x1) && (xx<x2)))
				{
				/*printf(" secant devrait =0\n");*/
				secant =0;
				}
			}
		else
			{
			if (((yy>b1) && (yy>b2)) || ((yy<b1) && (yy<b2)) || ((yy>yy1) && (yy>y2)) || ((yy<yy1) && (yy<y2)))
				secant =0;
			}
		}
	else
		{
		if (((a2-a1)==0.0) && ((b2-b1)==0.0))
			{
			secant =0;
			}
		else
			{
			if (((x2-x1)==0.0) && ((y2-yy1)==0.0))
				{
				secant =0;
				}
			else
				{
				/*les 2 segments sont parralelles*/
				secant =0;
				}
			}
		}
	
	
	/*printf("a1   : %8.2lf , b1 :  %8.2lf a2   : %8.2lf , b2 :  %8.2lf \n",a1,b1,a2,b2);
	printf("x1   : %8.2lf , yy1 :  %8.2lf x2   : %8.2lf , y2 :  %8.2lf \n",x1,yy1,x2,y2);
	printf("secant : %8d, xx   : %8.2lf , yy :  %8.2lf  , denom :  %8.2lf  \n",secant,xx,yy,denom);*/
	
	
	return(secant);
	}
	
void intersection_segment(double a1, double b1, double a2, double b2, double x1, double yy1, double x2, double y2, double *x,double *y)
  	{
  	/*calcul le point d intersection x y de 2 segments a1,b1 a a2,b2 et de x1,yy1 a x2,y2*/
  	

  	
	*x = a1;
	*y = b1;
	
	if (b2 != b1)
		{
		if ((a2-a1)*(y2-yy1) != (b2-b1)*(x2-x1))
			{
			*y = (b1*(a2-a1)/(b2-b1)*(y2-yy1) - yy1*(x2-x1) - (a1-x1)*(y2-yy1)) / ((a2-a1)/(b2-b1)*(y2-yy1) - (x2-x1));
			*x = a1 + (a2-a1)/(b2-b1) * (*y-b1);
			}
		else
			{
			/*pas sur du tout : A VERIFIER*/
			*x = a1;
			*y = b1;
			}
		}
	else
		{
		*y = b1;
		if (y2 != yy1)
			{
			*x = x1 +(x2-x1)/(y2-yy1)*(*y-yy1);
			}
		else
			{
			/*pas sur du tout : A VERIFIER*/
			*x = a1;
			}
		}
	
  	}
  	

void mesure_defaut_discretisation()
	{
	int ni,nj,nk,ng,nb,no,pa,voisin;
	int sommet1,sommet2,sommet3,som1,som2,som3;
	double defaut,defa[4],min_defa,nol,mol,nil,mil,defaut_max,defaut_mean;
	
	for (ni=1;ni<=NOMBRE_SURFACES;ni++)
		{
		nj = 0;		/*numero du premier   triangle voisin de ni*/
		nk = 0;		/*numero du second    triangle voisin de ni*/
		ng = 0;		/*numero du troisieme triangle voisin de ni*/
		nb = 0;		/*nb de triangles voisin de ni*/
		defaut = 0.0;	/*mesure de defaut de discretisation du triangle ni*/
 		sommet1 = Surface[ni].extremite[1];
  		sommet2 = Surface[ni].extremite[2];
  		sommet3 = Surface[ni].extremite[3];
  		/*longueurs tendues des fils u rt v*/
  		nil = sqrt(Surface[ni].nx*Surface[ni].nx + Surface[ni].ny*Surface[ni].ny + Surface[ni].nz*Surface[ni].nz);
  		mil = sqrt(Surface[ni].mx*Surface[ni].mx + Surface[ni].my*Surface[ni].my + Surface[ni].mz*Surface[ni].mz);
		for (no=1;no<=NOMBRE_SURFACES;no++)
			{
			if ((Surface[no].type == Surface[ni].type) && (no != ni))
				{
 				som1 = Surface[no].extremite[1];
  				som2 = Surface[no].extremite[2];
  				som3 = Surface[no].extremite[3];
  				voisin = 0;
  				if ((sommet1 == som1) && (sommet2 == som2)) voisin = 1;
  				if ((sommet1 == som1) && (sommet2 == som3)) voisin = 1;
  				if ((sommet1 == som1) && (sommet3 == som2)) voisin = 1;
  				if ((sommet1 == som1) && (sommet3 == som3)) voisin = 1;
  				if ((sommet1 == som2) && (sommet2 == som1)) voisin = 1;
  				if ((sommet1 == som2) && (sommet2 == som3)) voisin = 1;
  				if ((sommet1 == som2) && (sommet3 == som1)) voisin = 1;
  				if ((sommet1 == som2) && (sommet3 == som3)) voisin = 1;
  				if ((sommet1 == som3) && (sommet2 == som1)) voisin = 1;
  				if ((sommet1 == som3) && (sommet2 == som2)) voisin = 1;
  				if ((sommet1 == som3) && (sommet3 == som1)) voisin = 1;
  				if ((sommet1 == som3) && (sommet3 == som2)) voisin = 1;
  				if ((sommet2 == som1) && (sommet3 == som2)) voisin = 1;
  				if ((sommet2 == som1) && (sommet3 == som3)) voisin = 1;
   				if ((sommet2 == som2) && (sommet3 == som1)) voisin = 1;
  				if ((sommet2 == som2) && (sommet3 == som3)) voisin = 1;
   				if ((sommet2 == som3) && (sommet3 == som1)) voisin = 1;
  				if ((sommet2 == som3) && (sommet3 == som2)) voisin = 1;
				if (voisin == 1)
  					{
  					nb = nb + 1;
  					/*
  					defa[nb] = Surface[no].Nx*Surface[ni].Nx + Surface[no].Ny*Surface[ni].Ny + Surface[no].Nz*Surface[ni].Nz;
  					*/
  					/*longueurs tendues des fils u rt v*/
  					nol = sqrt(Surface[no].nx*Surface[no].nx + Surface[no].ny*Surface[no].ny + Surface[no].nz*Surface[no].nz);
  					mol = sqrt(Surface[no].mx*Surface[no].mx + Surface[no].my*Surface[no].my + Surface[no].mz*Surface[no].mz);
					defa[nb] = ((Surface[no].nx*Surface[ni].nx + Surface[no].ny*Surface[ni].ny + Surface[no].nz*Surface[ni].nz) / nol / nil
						 +  (Surface[no].mx*Surface[ni].mx + Surface[no].my*Surface[ni].my + Surface[no].mz*Surface[ni].mz) /mol /mil) 
						 / 2.0;
					}
				}
			}
 		if (nb > 1) 
 			{
 			min_defa = 1.0;
			for (no=1;no<=nb;no++)
				{
				/*recherche du voisin avec le defaut le plus eleve*/
				if (defa[no] < min_defa) min_defa = defa[no];
				}
			/*elimination du defaut le plus eleve*/
 			Surface[ni].defaut_disc = - min_defa;
			for (no=1;no<=nb;no++)
				{
 				Surface[ni].defaut_disc = Surface[ni].defaut_disc + defa[no];
				}
 			Surface[ni].defaut_disc = Surface[ni].defaut_disc / (nb - 1);
 			}
 		else
 			{
 			Surface[ni].defaut_disc = 1.0;
 			}
		}
	/*ecriture des defaut par panneaux*/
	for (no=1;no<=NbTypesurf;no++)
		{
		if (panneau[no].netting_2_ropes_period == 0)
			{
			defaut_max = 1.0;	/*mesure de defaut max  de discretisation du panneau no*/
			defaut_mean = 0.0;	/*mesure de defaut mean de discretisation du panneau no*/
			nb = 0;			/*nb surfaces dans le panneau*/
			for (ni=1;ni<=NOMBRE_SURFACES;ni++)
				{
				if (Surface[ni].type == no)
					{
					nb++;
					if (Surface[ni].defaut_disc < defaut_max) defaut_max = Surface[ni].defaut_disc;
					defaut_mean = defaut_mean + Surface[ni].defaut_disc;
					}
				}
			defaut_mean = defaut_mean / nb;
			printf("panneau = %5d  defaut max = %lf defaut mean = %lf\n",no,defaut_max,defaut_mean);
			}
		}
	}

void produit_vect(float xx1, float yy1, float zz1, float xx2, float yy2, float zz2, float *xx3, float *yy3, float *zz3)
	{
	*xx3 = yy1*zz2 - zz1*yy2;
	*yy3 = zz1*xx2 - xx1*zz2;
	*zz3 = xx1*yy2 - yy1*xx2;
	}


void produit_vect2(float vect_1[4], float vect_2[4], float *xx3, float *yy3, float *zz3)
	{
	*xx3 = vect_1[2]*vect_2[3] - vect_1[3]*vect_2[2];
	*yy3 = vect_1[3]*vect_2[1] - vect_1[1]*vect_2[3];
	*zz3 = vect_1[1]*vect_2[2] - vect_1[2]*vect_2[1];
	}


void produit_vect3(float vect_1[4], float vect_2[4], float *vect_3)
	{
	vect_3[1] = vect_1[2]*vect_2[3] - vect_1[3]*vect_2[2];
	vect_3[2] = vect_1[3]*vect_2[1] - vect_1[1]*vect_2[3];
	vect_3[3] = vect_1[1]*vect_2[2] - vect_1[2]*vect_2[1];
	}

void produit_vect3_double(double vect_1[4], double vect_2[4], double *vect_3)
	{
	vect_3[1] = vect_1[2]*vect_2[3] - vect_1[3]*vect_2[2];
	vect_3[2] = vect_1[3]*vect_2[1] - vect_1[1]*vect_2[3];
	vect_3[3] = vect_1[1]*vect_2[2] - vect_1[2]*vect_2[1];
	}

void add_vect(float vect_1[4], float vect_2[4], float *vect_3)
	{
	vect_3[1] = vect_1[1] + vect_2[1];
	vect_3[2] = vect_1[2] + vect_2[2];
	vect_3[3] = vect_1[3] + vect_2[3];
	}

void sou_vect(float vect_1[4], float vect_2[4], float *vect_3)
	{
	vect_3[1] = vect_1[1] - vect_2[1];
	vect_3[2] = vect_1[2] - vect_2[2];
	vect_3[3] = vect_1[3] - vect_2[3];
	}

void add_vect_6(float vect_1[4], float vect_2[4], float *vect_3)
	{
	int zi;
   	for (zi = 1 ; zi<= 6; zi++) 
  		{
		vect_3[zi] = vect_1[zi] + vect_2[zi];
		}
	}

void add_vect_12(float vect_1[4], float vect_2[4], float *vect_3)
	{
	int zi;
   	for (zi = 1 ; zi<= 12; zi++) 
  		{
		vect_3[zi] = vect_1[zi] + vect_2[zi];
		}
	}

void produit_scal_vect(float scal, float vect_1[4], float *vect_2)
	{
	vect_2[1] = vect_1[1]*scal;
	vect_2[2] = vect_1[2]*scal;
	vect_2[3] = vect_1[3]*scal;
	}

void produit_scal_vect_double(double scal, double vect_1[4], double *vect_2)
	{
	vect_2[1] = vect_1[1]*scal;
	vect_2[2] = vect_1[2]*scal;
	vect_2[3] = vect_1[3]*scal;
	}

void produit_scal_vect_2(float scal1, float vect_1[4], float scal2, float vect_2[4], float *vect_3)
	{
	vect_3[1] = vect_1[1]*scal1 + vect_2[1]*scal2;
	vect_3[2] = vect_1[2]*scal1 + vect_2[2]*scal2;
	vect_3[3] = vect_1[3]*scal1 + vect_2[3]*scal2;
	}

void produit_scal_vect_2_double(double scal1, double vect_1[4], double scal2, double vect_2[4], double *vect_3)
	{
	vect_3[1] = vect_1[1]*scal1 + vect_2[1]*scal2;
	vect_3[2] = vect_1[2]*scal1 + vect_2[2]*scal2;
	vect_3[3] = vect_1[3]*scal1 + vect_2[3]*scal2;
	}

void produit_scal_vect_12(float scal, float vect_1[13], float *vect_2)
	{
	int zi;
   	for (zi = 1 ; zi<= 12; zi++) 
  		{
		vect_2[zi] = vect_1[zi]*scal;
		}
	}

void produit_scal_vect_6(float scal, float vect_1[13], float *vect_2)
	{
	int zi;
   	for (zi = 1 ; zi<= 6; zi++) 
  		{
		vect_2[zi] = vect_1[zi]*scal;
		}
	}

float produit_scal(float vect_1[4], float vect_2[4])
	{
	float prod_scal;
	
	prod_scal = vect_1[1]*vect_2[1] + vect_1[2]*vect_2[2] + vect_1[3]*vect_2[3];
	return prod_scal;
	}

double produit_scal_double(double vect_1[4], double vect_2[4])
	{
	double prod_scal;
	
	prod_scal = vect_1[1]*vect_2[1] + vect_1[2]*vect_2[2] + vect_1[3]*vect_2[3];
	return prod_scal;
	}
	
