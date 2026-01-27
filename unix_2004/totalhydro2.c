#define PRINCIPAL 0
#include "4c19.h"

void totalhydro2()
	{
	/* 
	calcul des efforts hydrodynamiques, c'est a dire effort de portance, et de trainee,
   	agissant sur les fils du filet.
	Assemblage des efforts de trainee et de portance elementaires,
	dans chaque triangle, affectes aux noeuds 
   	*/

  	double nbmaille,tfuv[4],V[4],u[4];
  	double bxx1,bxx2,bxx3,byy1,byy2,byy3,bzz1,bzz2,bzz3,bXX1,bYY1,bZZ1,bXX2,bYY2,bZZ2,bXX3,bYY3,bZZ3;
  	double ratio_mouille,surfacemouillee,surfacetotale;
  	int elem,zl,zk,pa;
	double **Kr,*xKr,*cKr,Kp[10][10],d_temp;

	/*allocation de la matrice raideur Kr*/
	xKr = (double *) malloc (10 * 10 * sizeof(double));  	if (xKr == NULL){printf("xKr	= NULL \n" );exit(0);}
	Kr = (double **) malloc (10 * sizeof(double *));	if (Kr	 == NULL){printf("Kr	= NULL \n" );exit(0);}
	cKr = xKr;
	for (zk=0;zk<10;zk++)
  		{
  		Kr[zk] = cKr;
  		cKr += 10;
		}


   	for (elem = 1 ; elem <= NOMBRE_SURFACES ; elem++)
   		{ 
  		/* Definition du vecteur courant grace au fichier .mdf */
  		pa = Surface[elem].type;	/*pannel*/
     		V[1] = Courant.vitesse*cos(Courant.direction*PI/180.0) * panneau[pa].current_reduction;
     		V[2] = Courant.vitesse*sin(Courant.direction*PI/180.0) * panneau[pa].current_reduction;
     		V[3] = 0.0                                             * panneau[pa].current_reduction;
     		bxx1 = wf[yc(elem,1)];	byy1 = wf[yc(elem,2)];	bzz1 = wf[yc(elem,3)];
     		bxx2 = wf[yc(elem,4)];	byy2 = wf[yc(elem,5)];	bzz2 = wf[yc(elem,6)];
     		bxx3 = wf[yc(elem,7)];	byy3 = wf[yc(elem,8)];	bzz3 = wf[yc(elem,9)];
     		
		if (bzz1 > 0.0 && bzz2 > 0.0 && bzz3 <= 0.0) 
			{
			ratio_mouille = 0.0;
			}
		else
 	  		{
			/* 
			Des que la cote d'un sommet d'un triangle est <=0, on calcule les efforts 
			hydrodynamiques exerces sur tous les fils de ce triangle...  
 			*/
 			
 			/*calcul de la proportion de surface mouillée*/
 			if (wf[yc(elem,3)] <= 0.0 && wf[yc(elem,6)] <= 0.0 && wf[yc(elem,9)] <= 0.0)
 				{
 				ratio_mouille = 1.0;
				}
 			if (bzz1 <= 0.0 && bzz2 > 0.0 && bzz3 > 0.0)
 				{
 				bXX2 = bxx1 - bzz1 / (bzz2-bzz1) * (bxx2-bxx1);	bYY2 = byy1 - bzz1 / (bzz2-bzz1) * (byy2-byy1);	bZZ2 = 0.0;
 				bXX3 = bxx1 - bzz1 / (bzz3-bzz1) * (bxx3-bxx1);	bYY3 = byy1 - bzz1 / (bzz3-bzz1) * (byy3-byy1);	bZZ3 = 0.0;
 				surfacemouillee = surface_triangle2(bxx1, byy1, bzz1, bXX2, bYY2, bZZ2, bXX3, bYY3, bZZ3);
				surfacetotale   = surface_triangle2(bxx1, byy1, bzz1, bxx2, byy2, bzz2, bxx3, byy3, bzz3);
 				if (surfacetotale != 0.0)	ratio_mouille =  (surfacetotale - surfacemouillee)/ surfacetotale;
 				else				ratio_mouille =  0.0;
				}
 			if (bzz1 > 0.0 && bzz2 <= 0.0 && bzz3 > 0.0)
 				{
 				bXX3 = bxx2 - bzz2 / (bzz3-bzz2) * (bxx3-bxx2);	bYY3 = byy2 - bzz2 / (bzz3-bzz2) * (byy3-byy2);	bZZ3 = 0.0;
 				bXX1 = bxx2 - bzz2 / (bzz1-bzz2) * (bxx1-bxx2);	bYY1 = byy2 - bzz2 / (bzz1-bzz2) * (byy1-byy2);	bZZ1 = 0.0;
 				surfacemouillee = surface_triangle2(bXX1, bYY1, bZZ1, bxx2, byy2, bzz2, bXX3, bYY3, bZZ3);
				surfacetotale   = surface_triangle2(bxx1, byy1, bzz1, bxx2, byy2, bzz2, bxx3, byy3, bzz3);
 				if (surfacetotale != 0.0)	ratio_mouille =  (surfacetotale - surfacemouillee)/ surfacetotale;
 				else				ratio_mouille =  0.0;
				}
 			if (bzz1 > 0.0 && bzz2 > 0.0 && bzz3 <= 0.0)
 				{
 				bXX1 = bxx3 - bzz3 / (bzz1-bzz3) * (bxx1-bxx3); 	bYY1 = byy3 - bzz3 / (bzz1-bzz3) * (byy1-byy3);	bZZ1 = 0.0;	    	
 				bXX2 = bxx3 - bzz3 / (bzz2-bzz3) * (bxx2-bxx3);	bYY2 = byy3 - bzz3 / (bzz2-bzz3) * (byy2-byy3);	bZZ2 = 0.0;
 				surfacemouillee = surface_triangle2(bXX1, bYY1, bZZ1, bXX2, bYY2, bZZ2, bxx3, byy3, bzz3);
				surfacetotale   = surface_triangle2(bxx1, byy1, bzz1, bxx2, byy2, bzz2, bxx3, byy3, bzz3);
 				if (surfacetotale != 0.0)	ratio_mouille =  (surfacetotale - surfacemouillee)/ surfacetotale;
 				else				ratio_mouille =  0.0;
				}
 			
 			if (bzz1 > 0.0 && bzz2 <= 0.0 && bzz3 <= 0.0)
 				{
 				bXX2 = bxx1 - bzz1 / (bzz2-bzz1) * (bxx2-bxx1);	bYY2 = byy1 - bzz1 / (bzz2-bzz1) * (byy2-byy1);	bZZ2 = 0.0;
 				bXX3 = bxx1 - bzz1 / (bzz3-bzz1) * (bxx3-bxx1);	bYY3 = byy1 - bzz1 / (bzz3-bzz1) * (byy3-byy1);	bZZ3 = 0.0;
 				surfacemouillee = surface_triangle2(bxx1, byy1, bzz1, bXX2, bYY2, bZZ2, bXX3, bYY3, bZZ3);
				surfacetotale   = surface_triangle2(bxx1, byy1, bzz1, bxx2, byy2, bzz2, bxx3, byy3, bzz3);
 				if (surfacetotale != 0.0)	ratio_mouille =  (surfacetotale - surfacemouillee)/ surfacetotale;
 				else				ratio_mouille =  0.0;
				}
 			if (bzz1 <= 0.0 && bzz2 > 0.0 && bzz3 <= 0.0)
 				{
 				bXX3 = bxx2 - bzz2 / (bzz3-bzz2) * (bxx3-bxx2);	bYY3 = byy2 - bzz2 / (bzz3-bzz2) * (byy3-byy2);	bZZ3 = 0.0;
 				bXX1 = bxx2 - bzz2 / (bzz1-bzz2) * (bxx1-bxx2);	bYY1 = byy2 - bzz2 / (bzz1-bzz2) * (byy1-byy2);	bZZ1 = 0.0;
 				surfacemouillee = surface_triangle2(bXX1, bYY1, bZZ1, bxx2, byy2, bzz2, bXX3, bYY3, bZZ3);
				surfacetotale   = surface_triangle2(bxx1, byy1, bzz1, bxx2, byy2, bzz2, bxx3, byy3, bzz3);
 				if (surfacetotale != 0.0)	ratio_mouille =  (surfacetotale - surfacemouillee)/ surfacetotale;
 				else				ratio_mouille =  0.0;
 				}
 			if (bzz1 <= 0.0 && bzz2 <= 0.0 && bzz3 > 0.0)
 				{
 				bXX1 = bxx3 - bzz3 / (bzz1-bzz3) * (bxx1-bxx3);	bYY1 = byy3 - bzz3 / (bzz1-bzz3) * (byy1-byy3);	bZZ1 = 0.0;
 				bXX2 = bxx3 - bzz3 / (bzz2-bzz3) * (bxx2-bxx3);	bYY2 = byy3 - bzz3 / (bzz2-bzz3) * (byy2-byy3);	bZZ2 = 0.0;
 				surfacemouillee = surface_triangle2(bXX1, bYY1, bZZ1, bXX2, bYY2, bZZ2, bxx3, byy3, bzz3);
				surfacetotale   = surface_triangle2(bxx1, byy1, bzz1, bxx2, byy2, bzz2, bxx3, byy3, bzz3);
 				if (surfacetotale != 0.0)	ratio_mouille =  (surfacetotale - surfacemouillee)/ surfacetotale;
 				else				ratio_mouille =  0.0;
				}
			}	
		/*printf("elem = %d  ratio_mouille  = %lf   \n",elem,ratio_mouille); */
		
		
		
		/* Efforts aux 3 noeuds, sommets du triangle.*/
		trainee_fil( elem, V, &tfuv[0]);
		//trainee_fil2( elem, V, tfuv);
		nbmaille = Surface[elem].nb_cote_u_ou_v;
		/* Efforts aux 3 noeuds, sommets du triangle .*/
		wae[1] = tfuv[1] / 3.0 * nbmaille * ratio_mouille;
		wae[2] = tfuv[2] / 3.0 * nbmaille * ratio_mouille;
		wae[3] = tfuv[3] / 3.0 * nbmaille * ratio_mouille;
		wae[4] = tfuv[1] / 3.0 * nbmaille * ratio_mouille;
		wae[5] = tfuv[2] / 3.0 * nbmaille * ratio_mouille;
		wae[6] = tfuv[3] / 3.0 * nbmaille * ratio_mouille;
		wae[7] = tfuv[1] / 3.0 * nbmaille * ratio_mouille;
		wae[8] = tfuv[2] / 3.0 * nbmaille * ratio_mouille;
		wae[9] = tfuv[3] / 3.0 * nbmaille * ratio_mouille;
		/* Mise a jour du vecteur effort global*/
		for ( zl = 1; zl <= 9; zl++ ) wasurf[yc(elem,zl)] += wae[zl];
		/*if ((nbiter >= 346) && (elem == 7))
			{
			printf("elem %4d tfuv %9.4lf %9.4lf %9.4lf nbmaille %9.4lf ratio %9.4lf bzz %9.4lf %9.4lf %9.4lf \n",elem,tfuv[1],tfuv[2],tfuv[3],nbmaille,ratio_mouille,bzz1,bzz2,bzz3);
			exit(0);
			}*/
		Structure.surface_drag = Structure.surface_drag             + tfuv[1] * nbmaille * ratio_mouille;
		/*
		d_temp = tfuv[1] * nbmaille * ratio_mouille;
		printf("elem %4d d_temp %9.4lf\n",elem,d_temp);
		*/
		if (Sortie_texte.panel_drag == 1)
				{
		    		panneau[pa].drag = panneau[pa].drag + tfuv[1] * nbmaille * ratio_mouille;
		    		Surface[elem].panel_drag = Surface[elem].panel_drag + tfuv[1] * nbmaille * ratio_mouille;
		    		Surface[elem].panel_dragxyz = Surface[elem].panel_dragxyz + sqrt(tfuv[1]*tfuv[1]+tfuv[2]*tfuv[2]+tfuv[3]*tfuv[3]) * nbmaille * ratio_mouille;
				/*printf("elem %4d pa %4d panel_drag %9.4lf\n",elem,pa,panneau[pa].drag);
				printf("elem %4d pa %4d panel_drag %9.4lf\n",elem,pa,panneau[pa].dragxyz);
				exit(0);*/
				}

   		}
   		
	/* partie reservee au filets a maille hexagonale.*/
   	for (elem = 1 ; elem <= NOMBRE_SURF_HEXA ; elem++)
   		{ 
	   	if(wf[yc_hexa(elem,3)] <= 0.0 ||   wf[yc_hexa(elem,6)] <= 0.0 || wf[yc_hexa(elem,9)] <= 0.0 )
 	  		{
			/* 
			Des que la cote d'un sommet d'un triangle est <=0, on calcule les efforts 
			hydrodynamiques exerces sur tous les fils de ce triangle...  
 			*/
 
    		 	eff_hexa1(elem);
     		 	for ( zl = 1 ; zl <= 9 ; zl++)
   		  		{
     		   		wasurf[yc_hexa(elem,zl)] += ET[zl];
      		   		wasurf[yc_hexa(elem,zl)] += EN[zl];
				/*if(yc_hexa(elem,zl) == (3 * fixa[418] - 2))
					{
					printf("elem = %d EN = %9.4lf%9.4lf%9.4lf%9.4lf%9.4lf%9.4lf%9.4lf%9.4lf%9.4lf\n",elem,EN[1],EN[2],EN[3],EN[4],EN[5],EN[6],EN[7],EN[8],EN[9]);
  					}*/
     		  		}
			Structure.surface_drag = Structure.surface_drag + ET[1] + EN[1] + ET[4] + EN[4] + ET[7] + EN[7];
   	  		}
   		}
   	/*free*/
	if (xKr						!= NULL)        free(xKr);
	if (Kr						!= NULL)        free(Kr);
	}

void drag_normal_twine(double VV[4], double uu[4], int elem, double *FN, double **KN)
	{
	double sin_teta_2,norm_u_2,norm_V_2,ps,Vn[4],WW[4],n[4],E;
	
	
	norm_u_2 = uu[1]*uu[1] + uu[2]*uu[2] + uu[3]*uu[3];	/*norme au carre du fil uu*/
	norm_V_2 = VV[1]*VV[1] + VV[2]*VV[2] + VV[3]*VV[3];	/*norme au carre du fil uu*/
	Vn[1] = VV[1] / sqrt(norm_V_2);				/*vecteur courant norme*/
	Vn[2] = VV[2] / sqrt(norm_V_2);
	Vn[3] = VV[3] / sqrt(norm_V_2);
	ps = produit_scal(Vn, uu);				/*produit scalaire entre le courant VV et le fil uu*/
	sin_teta_2 = 1 - ps*ps/norm_u_2;			/*sin (teta) au carre, teta = angle entre VV et uu*/
	WW[1] = Vn[2]*uu[3]-Vn[3]*uu[2];			/*W est le produit vectoriel de VV^uu*/
	WW[2] = Vn[3]*uu[1]-Vn[1]*uu[3];
	WW[3] = Vn[1]*uu[2]-Vn[2]*uu[1];
	n[1] = uu[2]*WW[3]-uu[3]*WW[2];				/*n est le produit vectoriel de uu^WW*/
	n[2] = uu[3]*WW[1]-uu[1]*WW[3];				/*n est la direction de l effort normal*/
	n[3] = uu[1]*WW[2]-uu[2]*WW[1];
	E = 1.0/6.0 * RHO * Surface[elem].cdnormal * Surface[elem].diametrehydro* Surface[elem].lgrepos * norm_V_2;
	
	FN[1] = E * sin_teta_2 * n[1] / norm_u_2;
	FN[2] = E * sin_teta_2 * n[2] / norm_u_2;
	FN[3] = E * sin_teta_2 * n[3] / norm_u_2;
	FN[4] = E * sin_teta_2 * n[1] / norm_u_2;
	FN[5] = E * sin_teta_2 * n[2] / norm_u_2;
	FN[6] = E * sin_teta_2 * n[3] / norm_u_2;
	FN[7] = E * sin_teta_2 * n[1] / norm_u_2;
	FN[8] = E * sin_teta_2 * n[2] / norm_u_2;
	FN[9] = E * sin_teta_2 * n[3] / norm_u_2;
	}

void drag_tangent_twine(double VV[4], double uu[4], int elem, double *FT, double **KT)
	{
	}
