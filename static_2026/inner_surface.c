#define PRINCIPAL 0
#include "4c19.h"

void inner_surface()
	{
  	/*calculation of the ellipsoidal inner surface of the catch
  	radial_radius is the radial radius of the ellipsoide
  	axial_radius is the axial radius of the ellipsoide
  	distance_front is the distance betwween the center of the ellipsoide and the front of the cod-end
	*/
   
  	double minx,maxx,surfacefr,volumefr,somme,angle,volume_ellipse;
  	double aa,bb,cc,v1,ve,amax,amin,Ecart,*rk,AA,BB,CC,AA_y,AA_z,AA_R,BB_y,BB_z,BB_R,CC_y,CC_z,CC_R,delta_y,delta_z,delta_R;
  	int zh,zi,zj,elem,symm,za,zb,zc,zd,ze,zf,taille;
  	double Ecart_0,AA_0,BB_0,CC_0,AA_1,BB_1,CC_1,delta_x,aa_y,aa_z,aa_R,bb_y,bb_z,bb_R,cc_y,cc_z,cc_R;
  	
	double **mat,*xmat,*cmat,*ff,*uu,*YY_vect,*ZZ_vect;
  	int zk,zl,n_ligne,p_colonne,nb_YY_ZZ,iter_nb;
  	
	/*valeurs arbitraires pour debuguer*/
	Prise.PR = Prise.volume * 4.0 / 3.0 * RHO;
	Prise.PE = 6.90;
	Prise.TA = 1.0;
	
	changement_variable_catch();
  	extrema_direction_courant(&minx,&maxx);


     	if (Prise.volume > Prise.seuil) 
      		{
		Prise.front_diameter = 0.0;
		Prise.radial_radius = 0.0;
		Prise.axial_radius = 0.0;
		Prise.distance_front = 0.0;
		Prise.nb_point = 0;
		Prise.perimeter_y =        (double *) Malloc_double(1 + Prise.nb_point);
		Prise.perimeter_z =        (double *) Malloc_double(1 + Prise.nb_point);
  		/*symmetry*/
		symm = recherche_symmetry();
		printf("symm: %d\n",symm);
  		perimeter2(Prise.front);
		/*for (zl = 1; zl<= Prise.nb_point; zl++)
			{
			printf("p   t = %d ",zl);	
			printf("%lf %lf \n",Prise.perimeter_y[zl],Prise.perimeter_z[zl]);			
			}*/

  		if (symm == 0)
  			{
  			/*aucune symmetrie*/
			/*approximation de Prise.Oz*/
  			somme = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	somme = somme + Prise.perimeter_z[za];
			Prise.Oz = somme / Prise.nb_point;
			/*approximation de Prise.Oy*/
  			somme = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	somme = somme + Prise.perimeter_y[za];
			Prise.Oy = somme / Prise.nb_point;
  			/*approximation du rayon du cercle*/
  			somme = 0.0;
  			for (za = 1; za <= Prise.nb_point; za++)	somme = somme + sqrt((Prise.perimeter_y[za]-Prise.Oy)*(Prise.perimeter_y[za]-Prise.Oy)+(Prise.perimeter_z[za]-Prise.Oz)*(Prise.perimeter_z[za]-Prise.Oz));
  			Prise.front_diameter = somme / Prise.nb_point;
			/*printf("Prise.Oy: %6.3lf Prise.Oz: %6.3lf Prise.front_diameter: %6.3lf  \n",Prise.Oy,Prise.Oz,Prise.front_diameter);*/

			/*allocation des rayons*/
			rk =        (double *) Malloc_double(1 + Prise.nb_point);
			
   		do
    			{
  		/*test_debut_symm_0
		delta_x = 0.000001;
		Ecart_0 = 0.0;
		for (zc = 1; zc <= 5; zc++)
  			{
  			if(zc == 2) Prise.Oy 			= Prise.Oy 		+ delta_x;
  			if(zc == 3) Prise.Oz 			= Prise.Oz 		+ delta_x;
  			if(zc == 4) Prise.front_diameter 	= Prise.front_diameter 	+ delta_x;
  			test_fin_symm_0*/
			/*calcul de Oy, Oz et du rayon par les moindre carres*/
			/*calcul des rayons*/
  			for (za = 1; za <= Prise.nb_point; za++)	rk[za] = sqrt((Prise.perimeter_y[za]-Prise.Oy)*(Prise.perimeter_y[za]-Prise.Oy)+(Prise.perimeter_z[za]-Prise.Oz)*(Prise.perimeter_z[za]-Prise.Oz));
			/*calcul de l'ecart Ecart en m^2*/
			Ecart = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	Ecart = Ecart + (rk[za]-Prise.front_diameter)*(rk[za]-Prise.front_diameter);
			/*derivees de Ecart relativement a Oz(BB) et R(CC) en m*/
			AA = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	AA = AA - 2.0 * (Prise.front_diameter-rk[za]) * (Prise.Oy-Prise.perimeter_y[za]) / rk[za];
			BB = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	BB = BB - 2.0 * (Prise.front_diameter-rk[za]) * (Prise.Oz-Prise.perimeter_z[za]) / rk[za];
			CC = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	CC = CC + 2.0 * (Prise.front_diameter-rk[za]);
			/*printf("AA: %6.3lf BB: %6.3lf CC: %6.3lf\n",AA,BB,CC);*/
			/*derivees de AA, BB et CC par rapport a z et R*/
			AA_y = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	AA_y = AA_y + 2.0 * ((Prise.perimeter_y[za]-Prise.Oy)*(Prise.perimeter_y[za]-Prise.Oy)*Prise.front_diameter-rk[za]*rk[za]*(Prise.front_diameter-rk[za])) / rk[za] / rk[za] / rk[za];
			AA_z = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	AA_z = AA_z + 2.0 * ((Prise.perimeter_y[za]-Prise.Oy)*(Prise.perimeter_z[za]-Prise.Oz)*Prise.front_diameter) / rk[za] / rk[za] / rk[za];
			AA_R = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	AA_R = AA_R + 2.0 * (Prise.perimeter_y[za]-Prise.Oy) / rk[za];
			BB_y = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	BB_y = BB_y + 2.0 * ((Prise.perimeter_y[za]-Prise.Oy)*(Prise.perimeter_z[za]-Prise.Oz)*Prise.front_diameter) / rk[za] / rk[za] / rk[za];
			BB_z = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	BB_z = BB_z + 2.0 * ((Prise.perimeter_z[za]-Prise.Oz)*(Prise.perimeter_z[za]-Prise.Oz)*Prise.front_diameter-rk[za]*rk[za]*(Prise.front_diameter-rk[za])) / rk[za] / rk[za] / rk[za];
			BB_R = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	BB_R = BB_R + 2.0 * (Prise.perimeter_z[za]-Prise.Oz) / rk[za];
			CC_y = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	CC_y = CC_y + 2.0 * (Prise.perimeter_y[za]-Prise.Oy) / rk[za];
			CC_z = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	CC_z = CC_z + 2.0 * (Prise.perimeter_z[za]-Prise.Oz) / rk[za];
			CC_R = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	CC_R = CC_R + 2.0;
			/*
			printf("AA_y: %6.3lf AA_z: %6.3lf AA_R: %6.3lf\n",AA_y,AA_z,AA_R);
			printf("BB_y: %6.3lf BB_z: %6.3lf BB_R: %6.3lf\n",BB_y,BB_z,BB_R);
			printf("CC_y: %6.3lf CC_z: %6.3lf CC_R: %6.3lf\n",CC_y,CC_z,CC_R);
			*/

			/*resolution du systeme lineaire*/
       			/*allocation de la matrice raideur mat*/
			n_ligne 	= 1+3;
       			p_colonne 	= n_ligne;
       	
       			xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
			mat = (double **) malloc (n_ligne * sizeof(double *));			if (mat	 == NULL){printf("mat	= NULL \n" );exit(0);}
  			cmat = xmat;
  			for (zk=0;zk<n_ligne;zk++)
  				{
  				mat[zk] = cmat;
  				cmat += p_colonne;
				}
  				
       			/*allocation des vecteurs deplacement uu et resultat ff dans le systeme lineaure mat*uu = ff*/
       			uu = (double *) malloc (p_colonne * sizeof(double));  	if (uu	== NULL){printf("uu	= NULL \n" );exit(0);}
       			ff = (double *) malloc (p_colonne * sizeof(double));  	if (ff	== NULL){printf("uu	= NULL \n" );exit(0);}

			/*affectation*/
			mat[1][1] = -AA_y;	mat[1][2] = -AA_z;	mat[1][3] = -AA_R;	
			mat[2][1] = -BB_y;	mat[2][2] = -BB_z;	mat[2][3] = -BB_R;	
			mat[3][1] = -CC_y;	mat[3][2] = -CC_z;	mat[3][3] = -CC_R;	
			ff[1] = AA;		ff[2] = BB;		ff[3] = CC;
			
			/*resolution du system mat*uu = ff  avec mat : matrice raideur carree, 
			ff vecteur contrainte connu et uu vecteur des inconnues*/
			solve_linear_system(3, mat, ff, uu);
			
			/*printf("delta_y: %9.4lf delta_z: %9.4lf delta_R: %9.4lf\n",delta_y,delta_z,delta_R);
			printf("uu	");imprvectreel(3, uu);*/
			
			delta_y = uu[1];	delta_z = uu[2];	delta_R = uu[3];		
			
			/*nouveau rayon et position selon z du centre*/
			Prise.Oy 		= Prise.Oy 		+ delta_y;
			Prise.Oz 		= Prise.Oz 		+ delta_z;
			Prise.front_diameter 	= Prise.front_diameter 	+ delta_R;
			/*printf("Prise.Oy: %6.3lf Prise.Oz: %6.3lf Prise.front_diameter: %6.3lf  \n",Prise.Oy,Prise.Oz,Prise.front_diameter);
			printf("AA: %9.6lf BB: %9.6lf CC: %9.6lf\n",AA,BB,CC);*/
  			/*test_debut_symm_0
  			if(zc == 1) 	
				{	
				Ecart_0 = Ecart;	AA_1 = AA;	BB_1 = BB;	CC_1 = CC;
				}
   			if(zc == 2) 
				{
				Prise.Oy 		= Prise.Oy 		- delta_x;
				AA_0 = (Ecart-Ecart_0) / delta_x;	aa_y = (AA-AA_1) / delta_x;	bb_y = (BB-BB_1) / delta_x;	cc_y = (CC-CC_1) / delta_x;
				}
   			if(zc == 3) 
				{
				Prise.Oz 		= Prise.Oz 		- delta_x;
				BB_0 = (Ecart-Ecart_0) / delta_x;	aa_z = (AA-AA_1) / delta_x;	bb_z = (BB-BB_1) / delta_x;	cc_z = (CC-CC_1) / delta_x;
				}
  			if(zc == 4) 
				{
				Prise.front_diameter 	= Prise.front_diameter 	- delta_x;
				CC_0 = (Ecart-Ecart_0) / delta_x;	aa_R = (AA-AA_1) / delta_x;	bb_R = (BB-BB_1) / delta_x;	cc_R = (CC-CC_1) / delta_x;
				}
			}
			printf("derivee:          AA  : %9.6lf BB  : %9.6lf CC  : %9.6lf\n",AA,BB,CC);
			printf("difference finie: AA_0: %9.6lf BB_0: %9.6lf CC_0: %9.6lf\n",AA_0,BB_0,CC_0);
			printf("derivee:          AA: %6.3lf %6.3lf %6.3lf    BB: %6.3lf %6.3lf %6.3lf    CC: %6.3lf %6.3lf %6.3lf\n",AA_y,AA_z,AA_R,BB_y,BB_z,BB_R,CC_y,CC_z,CC_R);
			printf("difference finie: aa: %6.3lf %6.3lf %6.3lf    bb: %6.3lf %6.3lf %6.3lf    cc: %6.3lf %6.3lf %6.3lf\n",aa_y,aa_z,aa_R,bb_y,bb_z,bb_R,cc_y,cc_z,cc_R);
  			test_fin_symm_0*/
    			}
    			while ((fabs(AA) > 0.0001)  || (fabs(BB) > 0.0001)  || (fabs(CC) > 0.0001)); /*AA, BB et CC en m doivent etre < a 0.1 mm*/
			
			
  			/*angle moyen du filet avec le courant au niveau du front*/
  			angle = mean_angle_2(Prise.front);
			printf("angle moyen : %6.3lf\n",angle);
			/*volume de l ellipsoide derriere le front*/
			volume_ellipse = 2.0 * Prise.volume - Prise.PR / RHO;
			printf("prise.volume: %6.3lf Prise.PR: %6.3lf volume_ellipse: %6.3lf\n",Prise.volume,Prise.PR,volume_ellipse);
			amax = Prise.diametre;
			amin = Prise.front_diameter;
			aa = (amin + amax) * 0.6;
			do
				{
				if (angle >= 0)
					{
					/*equation de la tangente au filet au niveau du front*/
					bb = aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter) / Prise.front_diameter / tan(angle);
					/*equation de l'ellipse au niveau du front*/
					cc = bb/aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter);
					/*volume de l'ellipse à l'amont du front*/
					v1 = - PI*aa*aa/bb/bb*(bb*bb*cc-cc*cc*cc/3.0-2.0*bb*bb*bb/3.0);
					/*volume de l'ellipsoid a l aval du front*/
					ve = 4.0/3.0*PI*aa*aa*bb - v1;
					}
				else
					{
					/*equation de la tangente au filet au niveau du front*/
					bb = - aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter) / Prise.front_diameter / tan(angle);
					/*equation de l'ellipse au niveau du front*/
					cc = bb/aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter);
					/*volume de l'ellipse à l'aval du front*/
					ve = - PI*aa*aa/bb/bb*(bb*bb*cc-cc*cc*cc/3.0-2.0*bb*bb*bb/3.0);
					}
				/*printf("aa: %6.3lf bb: %6.3lf cc: %6.3lf v1: %6.3lf ve: %6.3lf\n",aa,bb,cc,v1,ve);*/
				if (ve > volume_ellipse)
					{
					amax = aa;
					aa = (amin + amax) * 0.5;
					}
				else
					{
					amin = aa;
					aa = (amin + amax) * 0.5;
					}
				}
			while (fabs(ve - volume_ellipse) > Prise.seuil);
			Prise.radial_radius = aa;
			Prise.axial_radius = bb;
			if (angle >= 0.0)
				{
				Prise.distance_front = - cc;
				}
			else
				{
				Prise.distance_front =   cc;
				}
			Prise.Ox = Prise.front - Prise.distance_front;			
  			}
  		if (symm == 1)
  			{
  			/*symmetrie par rapport a l'axe x*/
			printf("Attention inner_surface pas fait pour symm: %d\n",symm);
			exit(0);
  			}
  		if (symm == 2)
  			{
  			/*symmetrie par rapport a l'axe y*/
  			if (fabs(Courant.direction) > 1.0)
  				{
				printf("Attention la direction du courant devrait etre egale à 0.0 pour respecter la symmetrie!\n");
				exit(0);
  				}
  			/*recherche du centre du cercle*/
  			for (za = 1; za <= NOMBRE_NOEUDS; za++)	if ( Noeud[za].symy == 1 )	Prise.Oy = Noeud[za].y;
			Prise.Ox = 0.0;
			Prise.Oz = 0.0;
			/*approximation de Prise.Oz*/
  			somme = 0.0;
  			for (za = 1; za <= Prise.nb_point; za++)	somme = somme + Prise.perimeter_z[za]-Prise.Oz;
			Prise.Oz = somme / Prise.nb_point;
			/*printf("Prise.Oz: %6.3lf\n",Prise.Oz);*/
  			/*approximation du rayon du cercle*/
  			somme = 0.0;
  			for (za = 1; za <= Prise.nb_point; za++)	somme = somme + sqrt((Prise.perimeter_y[za]-Prise.Oy)*(Prise.perimeter_y[za]-Prise.Oy)+(Prise.perimeter_z[za]-Prise.Oz)*(Prise.perimeter_z[za]-Prise.Oz));
  			Prise.front_diameter = somme / Prise.nb_point;
			/*printf("Prise.front_diameter: %6.3lf\n",Prise.front_diameter);*/
			
			/*allocation des rayons*/
			rk =        (double *) Malloc_double(1 + Prise.nb_point);
			
			
   		do
    			{
  		/*test_debut_symm_2
		delta_x = 0.000001;
  		Ecart_0 = 0.0;
		for (zc = 1; zc <= 4; zc++)
  			{
  			if(zc == 2) Prise.Oz 			= Prise.Oz 		+ delta_x;
  			if(zc == 3) Prise.front_diameter 	= Prise.front_diameter 	+ delta_x;
  			test_fin_symm_2*/
			/*calcul de Oz et du rayon par les moindre carres*/
			/*calcul des rayons*/
  			for (za = 1; za <= Prise.nb_point; za++)	rk[za] = sqrt((Prise.perimeter_y[za]-Prise.Oy)*(Prise.perimeter_y[za]-Prise.Oy)+(Prise.perimeter_z[za]-Prise.Oz)*(Prise.perimeter_z[za]-Prise.Oz));
			/*calcul de l'ecart Ecart en m^2*/
			Ecart = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	Ecart = Ecart + (rk[za]-Prise.front_diameter)*(rk[za]-Prise.front_diameter);
			/*derivees de Ecart relativement a Oz(BB) et R(CC) en m*/
			BB = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	BB = BB - 2.0 * (Prise.front_diameter-rk[za]) * (Prise.Oz-Prise.perimeter_z[za]) / rk[za];
			CC = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	CC = CC + 2.0 * (Prise.front_diameter-rk[za]);
			/*printf("BB: %6.3lf CC: %6.3lf\n",BB,CC);*/
			/*derivees de BB et CC par rapport a z et R*/
			BB_z = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	BB_z = BB_z + 2.0 * ((Prise.perimeter_z[za]-Prise.Oz)*(Prise.perimeter_z[za]-Prise.Oz)*Prise.front_diameter-rk[za]*rk[za]*(Prise.front_diameter-rk[za])) / rk[za] / rk[za] / rk[za];
			BB_R = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	BB_R = BB_R + 2.0 * (Prise.perimeter_z[za]-Prise.Oz) / rk[za];
			CC_z = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	CC_z = CC_z + 2.0 * (Prise.perimeter_z[za]-Prise.Oz) / rk[za];
			CC_R = 0.0;	for (za = 1; za <= Prise.nb_point; za++)	CC_R = CC_R + 2.0;
			/*printf("BB_z: %6.3lf BB_R: %6.3lf\n",BB_z,BB_R);		printf("CC_z: %6.3lf CC_R: %6.3lf\n",CC_z,CC_R);*/

			/*resolution du systeme lineaire*/
       			/*allocation de la matrice raideur mat*/
			n_ligne 	= 1+2;
       			p_colonne 	= n_ligne;
       	
       			xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
			mat = (double **) malloc (n_ligne * sizeof(double *));			if (mat	 == NULL){printf("mat	= NULL \n" );exit(0);}
  			cmat = xmat;
  			for (zk=0;zk<n_ligne;zk++)
  				{
  				mat[zk] = cmat;
  				cmat += p_colonne;
				}
  				
       			/*allocation des vecteurs deplacement uu et resultat ff dans le systeme lineaure mat*uu = ff*/
       			uu = (double *) malloc (p_colonne * sizeof(double));  	if (uu	== NULL){printf("uu	= NULL \n" );exit(0);}
       			ff = (double *) malloc (p_colonne * sizeof(double));  	if (ff	== NULL){printf("uu	= NULL \n" );exit(0);}

			/*affectation*/
			mat[1][1] = -BB_z;	mat[1][2] = -BB_R;	mat[2][1] = -CC_z;	mat[2][2] = -CC_R;
			ff[1] = BB;	ff[2] = CC;
			
			/*resolution du system mat*uu = ff  avec mat : matrice raideur carree, 
			ff vecteur contrainte connu et uu vecteur des inconnues*/
			solve_linear_system(2, mat, ff, uu);
			
			/*printf("delta_z: %9.4lf delta_R: %9.4lf\n",delta_z,delta_R);
			printf("uu	");imprvectreel(2, uu);*/
			
			delta_z = uu[1];	delta_R = uu[2];		
			
			/*nouveau rayon et position selon z du centre*/
			Prise.Oz = Prise.Oz + delta_z;
			Prise.front_diameter = Prise.front_diameter + delta_R;
			/*printf("Prise.Oz: %6.3lf Prise.front_diameter: %6.3lf  ",Prise.Oz,Prise.front_diameter);
			printf("BB: %9.6lf CC: %9.6lf\n",BB,CC);*/
  			/*test_debut_symm_2
  			if(zc == 1) 	
				{	
				Ecart_0 = Ecart;
				BB_1 = BB;
				CC_1 = CC;
				}
   			if(zc == 2) 
				{
				Prise.Oz 			= Prise.Oz 		- delta_x;
				BB_0 = (Ecart-Ecart_0) / delta_x;	bb_z = (BB-BB_1) / delta_x;	cc_z = (CC-CC_1) / delta_x;
				}
  			if(zc == 3) 
				{
				Prise.front_diameter 	= Prise.front_diameter 	- delta_x;
				CC_0 = (Ecart-Ecart_0) / delta_x;	bb_R = (BB-BB_1) / delta_x;	cc_R = (CC-CC_1) / delta_x;
				}
			}
			printf("derivee:          BB  : %9.6lf CC  : %9.6lf\n",BB,CC);
			printf("difference finie: BB_0: %9.6lf CC_0: %9.6lf\n",BB_0,CC_0);
			printf("derivee:          BB: %6.3lf %6.3lf    CC: %6.3lf %6.3lf\n",BB_z,BB_R,CC_z,CC_R);
			printf("difference finie: bb: %6.3lf %6.3lf    cc: %6.3lf %6.3lf\n",bb_z,bb_R,cc_z,cc_R);
  			test_fin_symm_2*/
    			}
    			while ((fabs(BB) > 0.0001)  || (fabs(CC) > 0.0001)); /*BB et CC en m doivent etre < a 0.1 mm*/
			
			
  			/*angle moyen du filet avec le courant au niveau du front*/
  			angle = mean_angle_2(Prise.front);
			printf("angle moyen: %6.3lf\n",angle);
			/*volume de l ellipsoide derriere le front*/
			volume_ellipse = 2.0 * Prise.volume - Prise.PR / RHO;
			printf("prise.volume: %6.3lf Prise.PR: %6.3lf volume_ellipse: %6.3lf\n",Prise.volume,Prise.PR,volume_ellipse);
			amax = Prise.diametre;
			amin = Prise.front_diameter;
			aa = (amin + amax) * 0.6;
			do
				{
				if (angle >= 0.0)
					{
					/*equation de la tangente au filet au niveau du front*/
					bb = aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter) / Prise.front_diameter / tan(angle);
					/*equation de l'ellipse au niveau du front*/
					cc = bb/aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter);
					/*volume de l'ellipse à l'amont du front*/
					v1 = - PI*aa*aa/bb/bb*(bb*bb*cc-cc*cc*cc/3.0-2.0*bb*bb*bb/3.0);
					/*volume de l'ellipsoid a l aval du front*/
					ve = 4.0/3.0*PI*aa*aa*bb - v1;
					}
				else
					{
					/*equation de la tangente au filet au niveau du front*/
					bb = - aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter) / Prise.front_diameter / tan(angle);
					/*equation de l'ellipse au niveau du front*/
					cc = bb/aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter);
					/*volume de l'ellipsoid a l aval du front*/
					ve = - PI*aa*aa/bb/bb*(bb*bb*cc-cc*cc*cc/3.0-2.0*bb*bb*bb/3.0);
					}
				/*printf("aa: %6.3lf bb: %6.3lf cc: %6.3lf v1: %6.3lf ve: %6.3lf\n",aa,bb,cc,v1,ve);*/
				if (ve > volume_ellipse)
					{
					amax = aa;
					aa = (amin + amax) * 0.5;
					}
				else
					{
					amin = aa;
					aa = (amin + amax) * 0.5;
					}
				}
			while (fabs(ve - volume_ellipse) > Prise.seuil);
			Prise.radial_radius = aa;
			Prise.axial_radius = bb;
			if (angle >= 0.0)
				{
				Prise.distance_front = - cc;
				}
			else
				{
				Prise.distance_front =   cc;
				}
			Prise.Ox = Prise.front - Prise.distance_front;
  			}
  		if (symm == 3)
  			{
  			/*symmetrie par rapport a l'axe z*/
			printf("Attention inner_surface pas fait pour symm: %d\n",symm);
			exit(0);
  			}
  		if (symm == 4)
  			{
  			/*symmetrie par rapport a y et z*/
  			if (fabs(Courant.direction) > 1.0)
  				{
				printf("Attention la direction du courant devrait etre egale à 0.0 pour respecter la symmetrie!\n");
				exit(0);
  				}
  			/*recherche du centre du cercle*/
  			for (za = 1; za <= NOMBRE_NOEUDS; za++)
  				{
 				if ( Noeud[za].symy == 1 )	Prise.Oy = Noeud[za].y;
 				if ( Noeud[za].symz == 1 )	Prise.Oz = Noeud[za].z;
				}
			Prise.Ox = 0.0;
  			/*calcul du rayon du cercle*/
  			somme = 0.0;
  			for (za = 1; za <= Prise.nb_point; za++)	somme = somme + sqrt((Prise.perimeter_y[za]-Prise.Oy)*(Prise.perimeter_y[za]-Prise.Oy)+(Prise.perimeter_z[za]-Prise.Oz)*(Prise.perimeter_z[za]-Prise.Oz));
  			Prise.front_diameter = somme / Prise.nb_point;
  			/*angle moyen du filet avec le courant au niveau du front*/
  			angle = mean_angle_2(Prise.front);
			printf("angle moyen: %6.3lf\n",angle);
			/*volume de l ellipsoide derriere le front*/
			volume_ellipse = 4.0 * Prise.volume - Prise.PR / RHO;
			printf("prise.volume: %6.3lf Prise.PR: %6.3lf volume_ellipse: %6.3lf\n",Prise.volume,Prise.PR,volume_ellipse);
			amax = Prise.diametre;
			amin = Prise.front_diameter;
			aa = (amin + amax) * 0.6;
			/*aa : demi axe radial, bb : demi axe axial, cc : decalage entre le centre de l ellipsoide et et le front
			ve volume derriere le front, volume_ellipse volume cible derrire le front
			si angle > 0 v1 est le volume de l'ellipse en amont du front
			si angle < 0 v1 est le volume de l'ellipse en aval  du front*/
			iter_nb	= 0;	
			do
				{
				iter_nb	= iter_nb + 1;	
				/*printf("iter_nb: %8d\n",iter_nb);*/
				if (angle >= 0.0)
					{
					/*equation de la tangente au filet au niveau du front*/
					bb = aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter) / Prise.front_diameter / tan(angle);
					/*equation de l'ellipse au niveau du front*/
					cc = bb/aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter);
					/*volume de l'ellipse à l'amont du front*/
					v1 = - PI*aa*aa/bb/bb*(bb*bb*cc-cc*cc*cc/3.0-2.0*bb*bb*bb/3.0);
					/*volume de l'ellipsoid a l aval du front*/
					ve = 4.0/3.0*PI*aa*aa*bb - v1;
					}
				else
					{
					/*equation de la tangente au filet au niveau du front*/
					bb = - aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter) / Prise.front_diameter / tan(angle);
					/*equation de l'ellipse au niveau du front*/
					cc = bb/aa * sqrt(aa*aa - Prise.front_diameter*Prise.front_diameter);
					/*volume de l'ellipse à l'aval du front*/
					ve = - PI*aa*aa/bb/bb*(bb*bb*cc-cc*cc*cc/3.0-2.0*bb*bb*bb/3.0);
					}
				if (ve > volume_ellipse)
					{
					amax = aa;
					aa = (amin + amax) * 0.5;
					}
				else
					{
					amin = aa;
					aa = (amin + amax) * 0.5;
					}
				}
			while ((fabs(ve - volume_ellipse) > Prise.seuil) && (iter_nb < 1000));
			Prise.axial_radius = bb;
			Prise.radial_radius = aa;
			if (angle >= 0.0)
				{
				Prise.distance_front = - cc;
				}
			else
				{
				Prise.distance_front =   cc;
				}
			Prise.Ox = Prise.front - Prise.distance_front;
			/*printf("aa: %6.3lf bb: %6.3lf cc: %6.3lf v1: %6.3lf ve: %6.3lf volume_ellipse: %6.3lf ",aa,bb,cc,v1,ve,volume_ellipse);
			printf("ecart: %6.3lf\n",(ve-volume_ellipse)/Prise.seuil);
			printf("Prise.front_diameter: %6.3lf\n",Prise.front_diameter);*/
			}
  		if (symm == 5)
  			{
  			/*symmetrie par rapport a Z et X*/
			printf("Attention inner_surface pas fait pour symm: %d\n",symm);
			exit(0);
  			}
  		if (symm == 6)
  			{
  			/*symmetrie par rapport a X et Y*/
			printf("Attention inner_surface pas fait pour symm: %d\n",symm);
			exit(0);
  			}
  		if (symm == 7)
  			{
  			/*symmetrie par rapport a X Y et Z*/
			printf("Attention inner_surface pas fait pour symm: %d\n",symm);
			exit(0);
  			}
  			
      		}
      	else
      		{
		Prise.radial_radius = 0.0;
		Prise.axial_radius = 0.0;
		Prise.distance_front = 0.0;
      		}
	printf("Prise.front: %6.3lf (m)\n",Prise.front);
	printf("toto inner surface: radial radius: %6.3lf axial radius: %6.3lf center to the front: %6.3lf (m)\n",Prise.radial_radius,Prise.axial_radius,Prise.distance_front);
	/*
	printf("nb point: %d\n",Prise.nb_point);
  	for (elem = 1; elem <= Prise.nb_point; elem++)	printf("y: %6.3lf z: %6.3lf (m)\n",Prise.perimeter_y[elem],Prise.perimeter_z[elem]);
	*/
	printf("Prise.Oy: %6.3lf (m) Prise.Oz: %6.3lf (m)\n",Prise.Oy,Prise.Oz);
	/*free*/
	if (rk						!= NULL)       	//free(rk);
	if (xmat					!= NULL)        //free(xmat);
	if (mat						!= NULL)        //free(mat);
	if (uu						!= NULL)        free(uu);
	if (ff						!= NULL)        free(ff);
	}
	
	
void perimeter2(double frontx)
	{
	/*calcul des points du perimetre du front pour cet element elem*/
  	
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3,x12,y12,z12,x23,y23,z23,x31,y31,z31,surfacetriangle,volumetriangle;
	int zh,zi,zj,elem;

  	for (elem = 1; elem <= NOMBRE_SURFACES; elem++)
  		{
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
		/*coordonnees du triangle*/
  		XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
  		YY1 = wfcodend[zh+1];	YY2 = wfcodend[zi+1];	YY3 = wfcodend[zj+1];
 		ZZ1 = wfcodend[zh+2];	ZZ2 = wfcodend[zi+2];	ZZ3 = wfcodend[zj+2];

  		/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
 		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 > frontx))
  			{
 			x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  			y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  			z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  		
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY1 + y12 / x12 * (frontx - XX1);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ1 + z12 / x12 * (frontx - XX1);
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY1 + y31 / x31 * (frontx - XX1);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ1 + z31 / x31 * (frontx - XX1);
  			}
  		/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
 			x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  			y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  			z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  		
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY2 + y23 / x23 * (frontx - XX2);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ2 + z23 / x23 * (frontx - XX2);
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY2 + y12 / x12 * (frontx - XX2);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ2 + z12 / x12 * (frontx - XX2);
  			}
  		/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 > frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
 			x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  			y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  			z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  		
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY3 + y31 / x31 * (frontx - XX3);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ3 + z31 / x31 * (frontx - XX3);
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY3 + y23 / x23 * (frontx - XX3);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
			Prise.perimeter_z[Prise.nb_point] = ZZ3 + z23 / x23 * (frontx - XX3);
  			}
  		/* surfaces partiellement a l arriere  du front : point 1 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 <= frontx))
  			{
 			x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  			y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  			z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  		
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY1 + y12 / x12 * (frontx - XX1);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ1 + z12 / x12 * (frontx - XX1);
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY1 + y31 / x31 * (frontx - XX1);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ1 + z31 / x31 * (frontx - XX1);
  			}
  		/* surfaces partiellement a l arriere  du front : point 2 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
 			x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  			y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  			z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  		
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY2 + y23 / x23 * (frontx - XX2);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ2 + z23 / x23 * (frontx - XX2);
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY2 + y12 / x12 * (frontx - XX2);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ2 + z12 / x12 * (frontx - XX2);
  			}
  		/* surfaces partiellement a l arriere  du front : point 3 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 <= frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
 			x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  			y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  			z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  		
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY3 + y31 / x31 * (frontx - XX3);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ3 + z31 / x31 * (frontx - XX3);
			Prise.nb_point = Prise.nb_point + 1;
			Prise.perimeter_y = (double *) Realloc_double(Prise.perimeter_y,1 + Prise.nb_point);
  			Prise.perimeter_y[Prise.nb_point] = YY3 + y23 / x23 * (frontx - XX3);
			Prise.perimeter_z = (double *) Realloc_double(Prise.perimeter_z,1 + Prise.nb_point);
  			Prise.perimeter_z[Prise.nb_point] = ZZ3 + z23 / x23 * (frontx - XX3);
  			}		
		}
	}

double mean_angle_2(double frt_x)
	{
	/*calcul de l'angle moyen du filet avec le courant au niveau du front en radian */
  	
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3,x12,y12,z12,x23,y23,z23,x31,y31,z31,surfacetriangle,volumetriangle,temp_acos;
  	double normal_vector[4],n_vector[4],m_vector[4],courant_vector[4],nn,mm,gamma,gamma_total,longueur,longueur_totale,prod;
	int zh,zi,zj,elem;
	
	/*direction du courant: vecteur norme*/
	courant_vector[1] = cos(Courant.direction*PI/180.0);
	courant_vector[2] = sin(Courant.direction*PI/180.0);
	courant_vector[3] = 0.0;
	gamma_total = 0.0;
	longueur_totale = 0.0;
	
  	for (elem = 1; elem <= NOMBRE_SURFACES; elem++)
  		{
 	 	/*numeros des coordonnees selon x des sommets du triangle*/
  		zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);

		/*coordonnees du triangle*/
  		XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
  		YY1 = wfcodend[zh+1];	YY2 = wfcodend[zi+1];	YY3 = wfcodend[zj+1];
 		ZZ1 = wfcodend[zh+2];	ZZ2 = wfcodend[zi+2];	ZZ3 = wfcodend[zj+2];

		longueur = 0.0;
		temp_acos = 0.0;
			
  		/* surfaces partiellement a l arriere  du front : point 1 en amont du front*/
 		if ((XX1 <= frt_x) && (XX2 > frt_x) && (XX3 > frt_x))
  			{
			n_vector[1] = Surface[elem].nx;	n_vector[2] = Surface[elem].ny;	n_vector[3] = Surface[elem].nz;
			m_vector[1] = Surface[elem].mx;	m_vector[2] = Surface[elem].my;	m_vector[3] = Surface[elem].mz;
  			nn = sqrt(produit_scal(n_vector, n_vector)); /*norme de n*/
  			mm = sqrt(produit_scal(m_vector, m_vector)); /*norme de m*/
			produit_vect3(n_vector, m_vector, normal_vector);
			x12 = frt_x;				x31 = frt_x;
			y12 = YY1 +(x12-XX1)/(XX2-XX1)*(YY2-YY1);	y31 = YY1 +(x31-XX1)/(XX3-XX1)*(YY3-YY1);
			z12 = ZZ1 +(x12-XX1)/(XX2-XX1)*(ZZ2-ZZ1);	z31 = ZZ1 +(x31-XX1)/(XX3-XX1)*(ZZ3-ZZ1);
			longueur = sqrt((x31-x12)*(x31-x12) + (y31-y12)*(y31-y12) + (z31-z12)*(z31-z12));
			temp_acos = PI / 2.0 - acos(produit_scal(normal_vector, courant_vector) / nn / mm);
			/*printf("a longueur: %6.3lf (m)\n",longueur);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 > frt_x) && (XX2 <= frt_x) && (XX3 > frt_x))
  			{
			n_vector[1] = Surface[elem].nx;	n_vector[2] = Surface[elem].ny;	n_vector[3] = Surface[elem].nz;
			m_vector[1] = Surface[elem].mx;	m_vector[2] = Surface[elem].my;	m_vector[3] = Surface[elem].mz;
  			nn = sqrt(produit_scal(n_vector, n_vector)); /*norme de n*/
  			mm = sqrt(produit_scal(m_vector, m_vector)); /*norme de m*/
			produit_vect3(n_vector, m_vector, normal_vector);
			x12 = frt_x;				x23 = frt_x;
			y12 = YY2 +(x12-XX2)/(XX1-XX2)*(YY1-YY2);	y23 = YY2 +(x23-XX2)/(XX3-XX2)*(YY3-YY2);
			z12 = ZZ2 +(x12-XX2)/(XX1-XX2)*(ZZ1-ZZ2);	z23 = ZZ2 +(x23-XX2)/(XX3-XX2)*(ZZ3-ZZ2);
			longueur = sqrt((x23-x12)*(x23-x12) + (y23-y12)*(y23-y12) + (z23-z12)*(z23-z12));
			temp_acos = PI / 2.0 - acos(produit_scal(normal_vector, courant_vector) / nn / mm);
			/*printf("b longueur: %6.3lf (m)\n",longueur);*/
			}
  		/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 > frt_x) && (XX2 > frt_x) && (XX3 <= frt_x))
  			{
			n_vector[1] = Surface[elem].nx;	n_vector[2] = Surface[elem].ny;	n_vector[3] = Surface[elem].nz;
			m_vector[1] = Surface[elem].mx;	m_vector[2] = Surface[elem].my;	m_vector[3] = Surface[elem].mz;
  			nn = sqrt(produit_scal(n_vector, n_vector)); /*norme de n*/
  			mm = sqrt(produit_scal(m_vector, m_vector)); /*norme de m*/
			produit_vect3(n_vector, m_vector, normal_vector);
			x31 = frt_x;				x23 = frt_x;
			y31 = YY3 +(x31-XX3)/(XX1-XX3)*(YY1-YY3);	y23 = YY3 +(x23-XX3)/(XX2-XX3)*(YY2-YY3);
			z31 = ZZ3 +(x31-XX3)/(XX1-XX3)*(ZZ1-ZZ3);	z23 = ZZ3 +(x23-XX3)/(XX2-XX3)*(ZZ2-ZZ3);
			longueur = sqrt((x31-x23)*(x31-x23) + (y31-y23)*(y31-y23) + (z31-z23)*(z31-z23));
			temp_acos = PI / 2.0 - acos(produit_scal(normal_vector, courant_vector) / nn / mm);
			/*printf("c longueur: %6.3lf (m)\n",longueur);*/
 			}
  		/* surfaces partiellement a l arriere  du front : point 1 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 > frt_x) && (XX2 <= frt_x) && (XX3 <= frt_x))
  			{
			n_vector[1] = Surface[elem].nx;	n_vector[2] = Surface[elem].ny;	n_vector[3] = Surface[elem].nz;
			m_vector[1] = Surface[elem].mx;	m_vector[2] = Surface[elem].my;	m_vector[3] = Surface[elem].mz;
  			nn = sqrt(produit_scal(n_vector, n_vector)); /*norme de n*/
  			mm = sqrt(produit_scal(m_vector, m_vector)); /*norme de m*/
			produit_vect3(n_vector, m_vector, normal_vector);
			x12 = frt_x;				x31 = frt_x;
			y12 = YY1 +(x12-XX1)/(XX2-XX1)*(YY2-YY1);	y31 = YY1 +(x31-XX1)/(XX3-XX1)*(YY3-YY1);
			z12 = ZZ1 +(x12-XX1)/(XX2-XX1)*(ZZ2-ZZ1);	z31 = ZZ1 +(x31-XX1)/(XX3-XX1)*(ZZ3-ZZ1);
			longueur = sqrt((x31-x12)*(x31-x12) + (y31-y12)*(y31-y12) + (z31-z12)*(z31-z12));
			temp_acos = PI / 2.0 - acos(produit_scal(normal_vector, courant_vector) / nn / mm);
			/*printf("d longueur: %6.3lf (m)\n",longueur);*/
 			}
  		/* surfaces partiellement a l arriere  du front : point 2 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 <= frt_x) && (XX2 > frt_x) && (XX3 <= frt_x))
  			{
			n_vector[1] = Surface[elem].nx;	n_vector[2] = Surface[elem].ny;	n_vector[3] = Surface[elem].nz;
			m_vector[1] = Surface[elem].mx;	m_vector[2] = Surface[elem].my;	m_vector[3] = Surface[elem].mz;
  			nn = sqrt(produit_scal(n_vector, n_vector)); /*norme de n*/
  			mm = sqrt(produit_scal(m_vector, m_vector)); /*norme de m*/
			produit_vect3(n_vector, m_vector, normal_vector);
			x12 = frt_x;				x23 = frt_x;
			y12 = YY2 +(x12-XX2)/(XX1-XX2)*(YY1-YY2);	y23 = YY2 +(x23-XX2)/(XX3-XX2)*(YY3-YY2);
			z12 = ZZ2 +(x12-XX2)/(XX1-XX2)*(ZZ1-ZZ2);	z23 = ZZ2 +(x23-XX2)/(XX3-XX2)*(ZZ3-ZZ2);
			longueur = sqrt((x23-x12)*(x23-x12) + (y23-y12)*(y23-y12) + (z23-z12)*(z23-z12));
			temp_acos = PI / 2.0 - acos(produit_scal(normal_vector, courant_vector) / nn / mm);
			/*printf("e longueur: %6.3lf (m)\n",longueur);*/
			}
  		/* surfaces partiellement a l arriere  du front : point 3 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 <= frt_x) && (XX2 <= frt_x) && (XX3 > frt_x))
  			{
			n_vector[1] = Surface[elem].nx;	n_vector[2] = Surface[elem].ny;	n_vector[3] = Surface[elem].nz;
			m_vector[1] = Surface[elem].mx;	m_vector[2] = Surface[elem].my;	m_vector[3] = Surface[elem].mz;
  			nn = sqrt(produit_scal(n_vector, n_vector)); /*norme de n*/
  			mm = sqrt(produit_scal(m_vector, m_vector)); /*norme de m*/
			produit_vect3(n_vector, m_vector, normal_vector);
			x31 = frt_x;				x23 = frt_x;
			y31 = YY3 +(x31-XX3)/(XX1-XX3)*(YY1-YY3);	y23 = YY3 +(x23-XX3)/(XX2-XX3)*(YY2-YY3);
			z31 = ZZ3 +(x31-XX3)/(XX1-XX3)*(ZZ1-ZZ3);	z23 = ZZ3 +(x23-XX3)/(XX2-XX3)*(ZZ2-ZZ3);
			longueur = sqrt((x31-x23)*(x31-x23) + (y31-y23)*(y31-y23) + (z31-z23)*(z31-z23));
			temp_acos = PI / 2.0 - acos(produit_scal(normal_vector, courant_vector) / nn / mm);
			/*printf("f longueur: %6.3lf (m)\n",longueur);*/
	  		}
		longueur_totale = longueur_totale + longueur;
		prod = temp_acos * longueur;
		/*gamma_total = gamma_total + temp_acos;*/
		gamma_total = gamma_total + prod;
		}
	/*angle moyen etre le filet et le courant*/
	/*gamma_total = gamma_total / nb_points * 2.0;*/
	gamma_total = gamma_total / longueur_totale;		
	printf("longueur_totale: %6.3lf (m)  ",longueur_totale);
	printf("gamma_total: %6.3lf (rad)\n",gamma_total);
	return gamma_total;
	}

int recherche_symmetry()
	{
  	/*
  	renvoie un entier:
  	0 : pas de symmetrie
  	1 : symmetrie selon X uniquement
  	2 : symmetrie selon Y uniquement
  	3 : symmetrie selon Z uniquement
  	4 : symmetrie selon Y et Z uniquement
  	5 : symmetrie selon Z et X uniquement
  	6 : symmetrie selon X et Y uniquement
  	7 : symmetrie selon X, Y et Z uniquement
	*/
   
  	int za,zx,zy,zz;
  	
  	zx = 0;		/*pas de symmetrie parrapport a X*/
  	zy = 0;		/*pas de symmetrie parrapport a Y*/
  	zz = 0;		/*pas de symmetrie parrapport a Z*/
  	for (za = 1; za <= NOMBRE_NOEUDS; za++)
  		{
 		if ( Noeud[za].symx == 1 )	zx = 1;
 		if ( Noeud[za].symy == 1 )	zy = 1;
 		if ( Noeud[za].symz == 1 )	zz = 1;
		}
	if ((zx == 0) && (zy == 0) && (zz == 0)) 	return 0;
	if ((zx == 1) && (zy == 0) && (zz == 0)) 	return 1;
	if ((zx == 0) && (zy == 1) && (zz == 0)) 	return 2;
	if ((zx == 0) && (zy == 0) && (zz == 1)) 	return 3;
	if ((zx == 0) && (zy == 1) && (zz == 1)) 	return 4;
	if ((zx == 1) && (zy == 0) && (zz == 1)) 	return 5;
	if ((zx == 0) && (zy == 1) && (zz == 1)) 	return 6;
	if ((zx == 1) && (zy == 1) && (zz == 1)) 	return 7;
	}
	
	
void solve_linear_system(int nb_row, double **stiff, double *contr, double *result)
	{
	/*resolution of the system stiff * result = contr  with 
	stiff : squarre matrix of stiffness, 
	contr : known vector of constraint and 
	result : unknown vector of results
	solve_linear_system(3, stiff, contr, result);*/
	
	int zd,ze,zf;
	
 	/*printf("stiff	\n");
  	for (zd=1;zd<=nb_row;zd++)
  		{
  		for (ze=1;ze<=nb_row;ze++)	printf("%6.3lf  ",stiff[zd][ze]);
  		printf("\n");
  		}
	printf("contr	");imprvectreel(nb_row, contr);*/
	/*triangulation*/
	for (zd = 1; zd <= nb_row-1; zd++)
  		{
		for (ze = zd+1; ze <= nb_row; ze++)
  			{
			for (zf = zd+1; zf <= nb_row; zf++)
  				{
  				stiff[ze][zf] = stiff[ze][zf] - stiff[zd][zf] * stiff[ze][zd] / stiff[zd][zd];
  				}
  			contr[ze] = contr[ze] - contr[zd] * stiff[ze][zd] / stiff[zd][zd];
 			stiff[ze][zd] = 0.0;
  			}
  		}
 	/*printf("stiff	\n");
  	for (zd=1;zd<=nb_row;zd++)
  		{
  		for (ze=1;ze<=nb_row;ze++)	printf("%6.3lf  ",stiff[zd][ze]);
  		printf("\n");
  		}
	printf("contr	");imprvectreel(nb_row, contr);*/
	/*remonte*/
	for (zd = nb_row; zd >= 2; zd--)
  		{
  		result[zd] = contr[zd] / stiff[zd][zd];
		for (ze = zd-1; ze >= 1; ze--)
  			{
  			contr[ze] = contr[ze] - stiff[ze][zd] * result[zd];
  			}
  		}
  	result[1] = contr[1] / stiff[1][1];
	/*printf("result	");imprvectreel(nb_row, result);*/
	}
	

