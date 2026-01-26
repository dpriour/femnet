#define PRINCIPAL 0
#include "4c19.h"

void initialisation()
	{
  	int zi,zj,noeud1,noeud2,symm,panel;
  	double dx,dy,dz;
  	double lambda_min,lambda_max,lambda_ecart,lambda_mean;
  	double ff,ffprim,lambda,hlambda,aa,kk,dh;
  	  
  	/* wf : vecteur contenant les coordonnes finales des noeuds */
   	for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) 
  		{
    		wf[3*zi-2] = Noeud[zi].x;
    		wf[3*zi-1] = Noeud[zi].y;
    		wf[3*zi-0] = Noeud[zi].z;
    		//printf("noeud %4d %lf %lf %lf \n",zi,wf[3*zi-2],wf[3*zi-1],wf[3*zi-0]);
  		}
  	/*wl[i] = 99 si la coordonnee i du noeud est libre, 0 si elle est fixe */
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) 
  		{
    		wl[3*zi-2] = (int) 99 * (1-abs(Noeud[zi].fixx));
    		wl[3*zi-1] = (int) 99 * (1-abs(Noeud[zi].fixy));
   		wl[3*zi-0] = (int) 99 * (1-abs(Noeud[zi].fixz));
  		}
  	/* wh : maximum, limite des coordonnees */
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) 
  		{
    		wh[3*zi-2] = Noeud[zi].limx;
    		wh[3*zi-1] = Noeud[zi].limy;
    		wh[3*zi-0] = Noeud[zi].limz;
  		}
  	/* whs : sens des limites*/
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) 
  		{
    		whs[3*zi-2] = Noeud[zi].senx;
    		whs[3*zi-1] = Noeud[zi].seny;
    		whs[3*zi-0] = Noeud[zi].senz;
  		}
  	/* eca  : demi largeur des matrices raideurs*/
  	eca = DIM3;     

//////////////////////////////////////////////////////////////////////////////////////////////////////////
  	/*direction de la houle entre 0.0 et 360.0 degre*/
  	zi = Houle.direction / 360;
  	if (Houle.direction < 0.0) zi--;
  	Houle.direction = Houle.direction - zi * 360.0;
  	if (Houle.periode <= 0.0)
  		{
		printf("Attention : Houle.periode <= 0.0, modifie a 1.0 s \n");
  		Houle.periode = 1.0;
  		}
  	//k = 2 PI / Lambda
  	//C² = G/k tanh(k depth)
  	//lambda = c periode
  	//-> 0 = G periode² / 2 / PI * tanh(2 PI/Lamda depth) - lambda

	if(Houle.depth<0.0792*G*Houle.periode*Houle.periode) 
		{
		printf("Intermediate depth \n");
		//intermediate depth
		}
	else
		{
		printf("Deep waters \n");
		//deep waters
		}
	

	if (Structure.wave_model == 1)
		{
 		//Airy finite depth
	  	//calcul of lambda by Newton-Raphson with accuracy of  0.0001m/////////////////////////////////////////////
	  	lambda = G / 2.0 / PI * Houle.periode * Houle.periode;	//initial value
	  	do  
	  		{  
	  		ff= G*Houle.periode*Houle.periode/2.0/PI*tanh(2.0*PI*Houle.depth/lambda)-lambda;
	  		ffprim = -G*Houle.periode*Houle.periode*Houle.depth/lambda/lambda/cosh(2.0*PI*Houle.depth/lambda)/cosh(2.0*PI*Houle.depth/lambda)-1.0;
	  		hlambda=-ff/ffprim;
	  		lambda=lambda+hlambda;
	  		}
	  	while (fabs(ff)>0.0001);

	  	Houle.lambda = G / 2.0 / PI * Houle.periode * Houle.periode; 	//value for large depth
	  	printf("G/2/PI*T²                 	= %lf m\n",Houle.lambda);
	  	Houle.lambda = lambda;
	  	printf("lambda Airy finite depth  	= %lf m\n",Houle.lambda);
		}
	if (Structure.wave_model == 2)
		{
		//Stokes 2d order finite depth
	  	//calcul of lambda by Newton-Raphson with accuracy of  0.0001m/////////////////////////////////////////////
	  	lambda = G / 2.0 / PI * Houle.periode * Houle.periode;	//initial value
	  	do  
	  		{  
  			ff= G*Houle.periode*Houle.periode/2.0/PI*tanh(2.0*PI*Houle.depth/lambda)-lambda;
  			ffprim = -G*Houle.periode*Houle.periode*Houle.depth/lambda/lambda/cosh(2.0*PI*Houle.depth/lambda)/cosh(2.0*PI*Houle.depth/lambda)-1.0;
	  		hlambda=-ff/ffprim;
	  		lambda=lambda+hlambda;
	  		}
	  	while (fabs(ff)>0.0001);

	  	Houle.lambda = G / 2.0 / PI * Houle.periode * Houle.periode; 	//value for large depth
	  	printf("G/2/PI*T²                            		= %lf m\n",Houle.lambda);
	  	Houle.lambda = lambda;
	  	printf("lambda Stokes 2d order intermediate depth	= %lf m\n",Houle.lambda);		
		}
	if (Structure.wave_model == 3)
		{
		//Stokes 3d order infinite depth
	  	//calcul of lambda by Newton-Raphson with accuracy of  0.0001m/////////////////////////////////////////////
	  	lambda = G / 2.0 / PI * Houle.periode * Houle.periode;	//initial value
	  	do  
	  		{  
			ff=lambda/Houle.periode-(((2.0*PI*PI*(Houle.hauteur/2.0)*(Houle.hauteur/2.0))/lambda/lambda+1.0)*sqrt(lambda*G))/(sqrt(2.0)*sqrt(PI));
			ffprim = (sqrt(8.0*PI*PI*PI)*(Houle.hauteur/2.0)*(Houle.hauteur/2.0)*sqrt(lambda*G))/lambda/lambda/lambda-(((2.0*PI*PI*(Houle.hauteur/2.0)*(Houle.hauteur/2.0))/lambda/lambda+1.0)*G)/(sqrt(8.0*PI)*sqrt(lambda*G))+1.0/Houle.periode;
			hlambda=-ff/ffprim;
			lambda=lambda+hlambda;
	  		//printf("lambda  %lf m \n",lambda);		
	  		}
	  	while (fabs(ff)>0.0001);

	  	Houle.lambda = G / 2.0 / PI * Houle.periode * Houle.periode; 	//value for large depth
	  	printf("G/2/PI*T²                              	= %lf m\n",Houle.lambda);
	  	Houle.lambda = lambda;
	  	printf("lambda Stokes 3d order infinite depth  	= %lf m\n",Houle.lambda);
		Houle.k = 2*PI/Houle.lambda;
		kk = 2*PI/Houle.lambda;
		aa = Houle.hauteur/2;
	  	printf("crest to trough will be  %lf m\n",Houle.hauteur*(1+3.0/8.0*kk*kk*aa*aa));	
		//calcul de l amplitude aa pour obtenir une hauteur crete a creux de Houle.hauteur
	  	//printf("kk  = %lf m\n",kk);		
		do
			{
			ff=aa*aa*aa+8.0/3.0/kk/kk*aa-8.0*(Houle.hauteur/2.0)/3.0/kk/kk;
			ffprim=aa*aa*3+8.0/3.0/kk/kk;
			dh=-ff/ffprim;
			aa=aa+dh;
	  		//printf("ff  = %lf m\n",ff);		
			}
		while (fabs(ff)>0.0001);
	  	//printf("ff  = %lf m\n",fabs(ff));		
	  	printf("For a crest to trough of %lf m,\nuse a wave height of     %lf m\n",Houle.hauteur,2*aa);	
	  	//exit(0);	
		}
  	/*hauteur de houle par defaut a chaque noeud*/
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) mh[zi] = 0.0;
  	Houle.k     = 2.0 * PI / Houle.lambda;
  	Houle.omega = 2.0 * PI / Houle.periode;
//////////////////////////////////////////////////////////////////////////////////////////////////////

  	/*initialisation pour les elements :
    	de la longueur tendue
    	de wtfinal qui est > 0 en traction et < 0 en compression
    	du vecteur raideur =  module d'elasticite*section. */
  	if (lectsta == 0)  /* Cas ou aucun calcul n'a ete encore fait */
  		{
    		for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
    			{
    			if (Element[zi].netting2ropes_panel == 0)
    				{
	       			Element[zi].lgrepos = (Element[zi].pro[2] - Element[zi].pro[1]) * TypeElement[Element[zi].type].lgrepos;
	      			Element[zi].lgtendue = Element[zi].lgrepos;
	      			Element[zi].wtfinal = 1.0;
	      			Element[zi].raideur_effective = Element[zi].raideur_traction;
	   			}
    			else
    				{
	       			Element[zi].lgrepos = Element[zi].lgrepos;
	      			Element[zi].lgtendue = Element[zi].lgrepos;
	      			Element[zi].wtfinal = 1.0;
	      			Element[zi].raideur_effective = Element[zi].raideur_traction;
    				}
    				
     			}
  		}
  	if (lectsta == 1)  /* Cas ou un equilibre a deja ete calcule */
  		{
    		for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
    			{
      			Element[zi].lgrepos = (Element[zi].pro[2] - Element[zi].pro[1]) * TypeElement[Element[zi].type].lgrepos;
			if (Element[zi].netting2ropes_panel == 0)
				{
				Element[zi].lgrepos	= (Element[zi].pro[2] - Element[zi].pro[1]) * TypeElement[Element[zi].type].lgrepos;/**/
				}
			else
				{
				panel = Element[zi].netting2ropes_panel;
				Element[zi].lgrepos	= panneau[panel].longueur_repos * panneau[panel].netting_2_ropes_period / panneau[panel].netting_2_ropes_bar_nb;
				}
      			Element[zi].wtfinal = Element[zi].lgtendue - Element[zi].lgrepos;
      			if (Element[zi].wtfinal < 0.0 )
      				{
        			Element[zi].raideur_effective = Element[zi].raideur_compression;
      				}
      			else
      				{
        			Element[zi].raideur_effective = Element[zi].raideur_traction;         
      				}
    			}
  		}
 	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
  		{
    		if (Element[zi].extremite[1] > Element[zi].extremite[2])  
    		/* Element[zi].extremite[1] et Element[zi].extremite[2] sont les numeros des extremites des bouts*/
    			{
			zj = Element[zi].extremite[1];
			Element[zi].extremite[1] = Element[zi].extremite[2];
			Element[zi].extremite[2] = zj;
    			}
    		//calculation of the mass of the elements    		
    		Element[zi].mass = Element[zi].lgrepos * PI * Element[zi].diametrehydro * Element[zi].diametrehydro / 4.0 * Element[zi].rhoelement;
 		//printf("Element[%4d].lgrepos %lf \n",zi,Element[zi].lgrepos);
 		//printf("Element[%4d].diametrehydro %lf \n",zi,Element[zi].diametrehydro);
 		//printf("Element[%4d].rhoelement %lf \n",zi,Element[zi].rhoelement);
 		//printf("Element[%4d].mass %lf \n",zi,Element[zi].mass);
  		}


  	
    	/*
    	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
    		{
    		printf("Element[%2d].lgrepos = %lf\n",zi,Element[zi].lgrepos);
    		}
    	*/
  

  	/*initialisation des noeuds a l interieur ou exterieur pour les winchs*/
    	for (zi = 1 ; zi<= NOMBRE_WINCHS; zi++) 
    		{
    		Winch[zi].exit[1] = 0;					/*noeud a l interieur du treuil*/
    		for (zj = 2 ; zj<= Winch[zi].nb_barre + 1; zj++) 
    			{
    			Winch[zi].exit[zj] = 1;				/*noeud a l exterieur du treuil*/
    			}
    		}
    			
  	/*initialisation pour les coulisses :
    	de la longueur tendue, des longueurs entre les noeuds
    	de wtfinal qui est > 0 en traction et < 0 en compression
    	du vecteur raideur =  module d'elasticite*section. */

  	if (lectsta == 0)  /* Cas ou aucun calcul n'a ete encore fait */
  		{
    		for (zi = 1 ; zi<= NOMBRE_COULISSES; zi++) 
    			{
      			Coulisse[zi].wtfinal = 1.0;
      			Coulisse[zi].raideur_effective = Coulisse[zi].raideur_traction;
      			Coulisse[zi].lgtendue = 0.0;
    			for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    				{
    				noeud1 = Coulisse[zi].noeud[zj  ];
    				noeud2 = Coulisse[zi].noeud[zj+1];
    				dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    				dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    				dz = wf[3*noeud1-0]-wf[3*noeud2-2];
    				Coulisse[zi].longueur[zj] = sqrt(dx*dx + dy*dy + dz*dz);
    				Coulisse[zi].lgtendue += Coulisse[zi].longueur[zj];
    				}
    			}
  		}
  	if (lectsta == 1)  /* Cas ou un equilibre a deja ete calcule */
  		{
    		for (zi = 1 ; zi<= NOMBRE_COULISSES; zi++) 
    			{
      			Coulisse[zi].lgtendue = 0.0;
    			for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    				{
    				if (zj == 1) noeud1 = Coulisse[zi].extremite[1];
    				if (zj != 1) noeud1 = Coulisse[zi].noeud[zj-1];
    				if (zj != Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].noeud[zj];
    				if (zj == Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].extremite[2];
    				dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    				dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    				dz = wf[3*noeud1-0]-wf[3*noeud2-0];
    				Coulisse[zi].longueur[zj] = sqrt(dx*dx + dy*dy + dz*dz);
    				Coulisse[zi].lgtendue += Coulisse[zi].longueur[zj];
    				}
      			Coulisse[zi].wtfinal = Coulisse[zi].lgtendue - Coulisse[zi].lgrepos;
      			if (Coulisse[zi].wtfinal < 0.0 )
      				{
        			Coulisse[zi].raideur_effective = Coulisse[zi].raideur_compression;
      				}
      			else
      				{
        			Coulisse[zi].raideur_effective = Coulisse[zi].raideur_traction;         
      				}
    			}
  		}
  
  	
 	

  	/*initialisation du changement de numero des noeuds si ca n a pas
  	ete fait par largeurbande.c*/
  	if(largeur_matrice == 0)
  		{
    		for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) /*renumerotation par defaut*/
    			{
      			fixa    [zi] = zi;
      			fixation[zi] = zi;
      			Noeud[zi].new_numero = zi;
    			}
  		}
  		
  	/*initialisation de la relaxation de la raideur additionnellle*/
  	Numtemps_relax = 1.0;
  	
  	/*initialisation de la taille du volume de la prise*/
  	if (Prise.PR > Prise.seuil)
  		{
  		/*la prise est initialisee par le volume de poisson (cf input catch) et non par le volume derriere le front*/
		symm = recherche_symmetry();
  		if (symm == 0)
  			{
 			/*0 : pas de symmetrie*/
 			Prise.volume = Prise.volume / 1.0;
 			}
	 	if ((symm == 1) || (symm == 2) || (symm == 3))
 			{
 			/*1 plan de symmetrie*/
 			Prise.volume = Prise.volume / 2.0;
 			}
 		if ((symm == 4) || (symm == 5) || (symm == 6))
 			{
 			/*2 plans de symmetrie*/
 			Prise.volume = Prise.volume / 4.0;
 			}
 		if (symm == 7)
 			{
 			/*3 plans de symmetrie*/
 			Prise.volume = Prise.volume / 8.0;
 			}
		printf("symm %d Catch characteristics : volume selon les symmetries (m^3): %lf\n",symm,Prise.volume);
		}
	}

