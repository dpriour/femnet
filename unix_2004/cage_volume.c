#define PRINCIPAL 0
#include "4c19.h"

double surface_triangle2_cage(double XX1, double YY1, double ZZ1, double XX2, double YY2, double ZZ2, double XX3, double YY3, double ZZ3)
	{
	double sx,sy,sz,surface;
	/*
	calcul de la surface du triangle dont les coordonnes du sommet 1 (2&3) sont
	XX1, YY1 ZZ1, (XX2, YY2,ZZ2 & XX3, YY3,ZZ3) a l aide du produit vectoriel entre 12 et 13
	surface = 0.5 * |12^13|
	*/
	
	sx = (YY2-YY1) * (ZZ3-ZZ1) - (YY3-YY1) * (ZZ2-ZZ1);
	sy = (ZZ2-ZZ1) * (XX3-XX1) - (ZZ3-ZZ1) * (XX2-XX1);
	sz = (XX2-XX1) * (YY3-YY1) - (XX3-XX1) * (YY2-YY1);
  	     
  	surface = 0.5 * sqrt( (sx * sx) + (sy * sy) + (sz * sz) );
  	return surface;
  	}
	

int orientation_triangle_cage(int zh,int zi,int zj)
	{
  	/*calculer l orientation du triangle 
  	si > 0 le volume compris entre ce triangle et le front s ajoute a la prise
  	si < 0 le volume compris entre ce triangle et le front se retranche de la prise
  	pour l orientation on calcule le produit vectoriel entre 12 et 13, 1 2 3 sont les sommets du triangle*/
  	
  	int orientation;
  	double nxx;
  	double y12,z12,y23,z23;
  	  	
  	/*varaition de coordonnees entre les sommets*/
  	y12 = wfcodend[zi+1] - wfcodend[zh+1];y23 = wfcodend[zj+1] - wfcodend[zi+1];
  	z12 = wfcodend[zi+2] - wfcodend[zh+2];z23 = wfcodend[zj+2] - wfcodend[zi+2];
  	
  	/*vecteur normal au triangle*/
  	nxx = y12*z23 - z12*y23;

  	/*calcul du sens du triangle si > 0 volume ajoute et surface ajoute si < 0 retranche*/
  	if (fabs(nxx) != 0.0)
  		{
  		orientation = (int) (- nxx / fabs(nxx));
  		}
  	else
  		{
  		orientation = 1;
  		}
  	
  	return orientation;
  	}
  	



void surf_vol_elem_cage(int zh,int zi,int zj,double frontz, double *surfacefront,double *volumefront)
	{
	/*calcul de la surface du front et du volume entre le front et le fond du filet 
	pour une surface a maille losange ou hexagonale.*/
  	
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3,x12,y12,z12,x23,y23,z23,x31,y31,z31,surfacetriangle,volumetriangle;
  	double yinter1,zinter1,yinter2,zinter2,surfacetriangleamont;
	int sgn;
	
	/*surfacetriangle = 0.0;
	volumetriangle = 0.0;
	sgn = 0;*/
	 	  		
	/*coordonnees du triangle*/
  	XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
  	YY1 = wfcodend[zh+1];	YY2 = wfcodend[zi+1];	YY3 = wfcodend[zj+1];
 	ZZ1 = wfcodend[zh+2];	ZZ2 = wfcodend[zi+2];	ZZ3 = wfcodend[zj+2];

  	/*ne traiter que les surfaces sous ou en partie sous le front*/
  	if ((XX1 <= frontz) || (XX2 <= frontz) || (XX3 <= frontz))
  		{
		sgn = orientation_triangle_cage(zh, zi, zj);
  		
 		x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  		y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  		z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  			
  		/* surfaces totalement a l arriere  du front*/
  		if ((XX1 <= frontz) && (XX2 <= frontz) && (XX3 <= frontz))
  			{
			nb_pt_aval = nb_pt_aval + 3;
			surfacetriangle = surface_triangle2_cage(frontz, YY1, ZZ1, frontz, YY2, ZZ2, frontz, YY3, ZZ3);
  			volumetriangle = surfacetriangle * fabs((XX1 + XX2 + XX3) / 3.0 - frontz);
			/*printf("1 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
 		if ((XX1 > frontz) && (XX2 <= frontz) && (XX3 <= frontz))
  			{
			nb_pt_aval = nb_pt_aval + 2;
  			yinter1 = YY1 + y12 / x12 * (frontz - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontz - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontz - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontz - XX1);
			surfacetriangle = surface_triangle2_cage(frontz, YY1, ZZ1, frontz, YY2, ZZ2, frontz, YY3, ZZ3);
  			volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontz);
  			/*surface du triangle amont forme par 1 inter1 et inter2 : en amont du front a retranche de la surface totale*/
			surfacetriangleamont = surface_triangle2_cage(frontz, YY1, ZZ1, frontz, yinter1, zinter1, frontz, yinter2, zinter2);
  			/*surface et volume en aval au front*/
    			surfacetriangle -=  surfacetriangleamont;
  			volumetriangle -=  (surfacetriangleamont * ((XX1 + frontz + frontz) / 3.0 - frontz));
			/*printf("2 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 <= frontz) && (XX2 > frontz) && (XX3 <= frontz))
  			{
			nb_pt_aval = nb_pt_aval + 2;
  			yinter1 = YY2 + y23 / x23 * (frontz - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontz - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontz - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontz - XX2);
			surfacetriangle = surface_triangle2_cage(frontz, YY1, ZZ1, frontz, YY2, ZZ2, frontz, YY3, ZZ3);
  			volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontz);
			surfacetriangleamont = surface_triangle2_cage(frontz, yinter2, zinter2, frontz, YY2, ZZ2, frontz, yinter1, zinter1);
  			/*surface et volume en aval au front*/
  			surfacetriangle  -= surfacetriangleamont;
  			volumetriangle -= (surfacetriangleamont * ((frontz + XX2 + frontz) / 3.0 - frontz));
			/*printf("3 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 <= frontz) && (XX2 <= frontz) && (XX3 > frontz))
  			{
			nb_pt_aval = nb_pt_aval + 2;
  			yinter1 = YY3 + y31 / x31 * (frontz - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontz - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontz - XX3);
			zinter2 = ZZ3 + z23 / x23 * (frontz - XX3);
			surfacetriangle = surface_triangle2_cage(frontz, YY1, ZZ1, frontz, YY2, ZZ2, frontz, YY3, ZZ3);
  			/*surface totale du triangle*/
  			volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontz);
			surfacetriangleamont = surface_triangle2_cage(frontz, yinter1, zinter1, frontz, yinter2, zinter2, frontz, YY3, ZZ3);
  			/*surface et volume en aval au front*/
  			surfacetriangle  -= surfacetriangleamont;
  			volumetriangle -= (surfacetriangleamont * ((frontz + frontz + XX3) / 3.0 - frontz));
			/*printf("4 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 1 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 <= frontz) && (XX2 > frontz) && (XX3 > frontz))
  			{
			nb_pt_aval = nb_pt_aval + 1;
  			yinter1 = YY1 + y12 / x12 * (frontz - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontz - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontz - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontz - XX1);
			surfacetriangle = surface_triangle2_cage(frontz, YY1, ZZ1, frontz, yinter1, zinter1, frontz, yinter2, zinter2);
  			volumetriangle = surfacetriangle * ((XX1 + frontz + frontz) / 3.0 - frontz);
			/*printf("5 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 2 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 > frontz) && (XX2 <= frontz) && (XX3 > frontz))
  			{
			nb_pt_aval = nb_pt_aval + 1;
  			yinter1 = YY2 + y23 / x23 * (frontz - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontz - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontz - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontz - XX2);
			surfacetriangle = surface_triangle2_cage(frontz, yinter2, zinter2, frontz, YY2, ZZ2, frontz, yinter1, zinter1);
  			volumetriangle = surfacetriangle * ((frontz + XX2 + frontz) / 3.0 - frontz);
			/*printf("6 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 3 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 > frontz) && (XX2 > frontz) && (XX3 <= frontz))
  			{
			nb_pt_aval = nb_pt_aval + 1;
  			yinter1 = YY3 + y31 / x31 * (frontz - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontz - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontz - XX3);
  			zinter2 = ZZ3 + z23 / x23 * (frontz - XX3);
			surfacetriangle = surface_triangle2_cage(frontz, yinter1, zinter1, frontz, yinter2, zinter2, frontz, YY3, ZZ3);
  			volumetriangle = surfacetriangle * ((frontz + frontz + XX3) / 3.0 - frontz);
			/*printf("7 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/*ajout a la surface et au volume delimite par le front*/
  		*surfacefront += sgn * surfacetriangle;
  		*volumefront += sgn * volumetriangle;
  		/*printf("signe = %6d  ",sgn);
  		printf("surfacetriangle = %12.6lf  ",surfacetriangle);
  		printf("volumetriangle = %12.6lf  \n",volumetriangle);
  		printf("surfacefront = %12.6lf  ",*surfacefront);
  		printf("volumefront = %12.6lf  \n",*volumefront);*/
  		}
	}


void extrema_direction_courant_cage_volume(double *minz,double *maxz, int nc)
	{
	/*
	definir le min et le max des x dans la direction du courant pour le catch2_volume numero nc
	*/
	
  	int elem,pa,pan,sommet,zh,appartient;
  	double XX1;
  	
  	/*
  	on initialise le minx et maxx avec la coordonnee x du sommet 1 du premier triangle a maille 
  	losange appartenant au premier panneau pris en compte dans le catch2_volume numero nc
  	*/
  	elem = 0;
    	do
    		{
    		elem = elem + 1;
    		}
    	while (Surface[elem].type != Cage_volume[nc].panel_catch2[1]) ;
    	
	/*printf("nc = %d   \n",nc);
	printf("Surface[%d].type = %d   \n",elem,Surface[elem].type);
	printf("Cage_volume[%d].panel_catch2[1] = %d   \n",nc,Cage_volume[nc].panel_catch2[1]);*/
	zh = yc(elem,1);
 	*minz = wfcodend[zh];
	*maxz = wfcodend[zh];
	
  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
		appartient = 0;
  		for (pa = 1; pa<= Cage_volume[nc].nb_panel_catch2; pa++)
  			{
  			pan = Cage_volume[nc].panel_catch2[pa];
  			if (Surface[elem].type == pan)	appartient = 1;
  			}
  			
  		if (appartient == 1)
  			{
  			for (sommet = 1; sommet<= 3; sommet++)
  				{
  				/*numeros de la coordonnee selon x du sommets no sommet du triangle*/
  				zh = yc(elem,3*sommet-2);
  		
  				/*coordonnee selon x du sommets no sommet du triangle*/
  				XX1 = wfcodend[zh  ];
  				if (*minz > XX1) *minz = XX1;
  				if (*maxz < XX1) *maxz = XX1;
  				}
  			}
  		}
	}
	
void surface_volume_cage_volume(double frontz, double *surfacefront,double *volumefront, int nc)
  	{

  	/*calcul de la surface du front et du volume entre le front et le fond du filet 
  	connaissant la position du front : frontz pour le catch2_volume numero nc*/
  	
  	int elem,zh,zi,zj,appartient,pa,pan;
  	
	*volumefront = 0.0;
	*surfacefront = 0.0;
	nb_pt_aval = 0;
	
	/*printf("volumefront = %5.2lf ",*volumefront);
	printf("surfacefront = %5.2lf \n",*surfacefront);*/

  	for (elem = 1; elem <= NOMBRE_SURFACES; elem++)
  		{
		appartient = 0;
  		for (pa = 1; pa<= Cage_volume[nc].nb_panel_catch2; pa++)
  			{
  			pan = Cage_volume[nc].panel_catch2[pa];
  			if (Surface[elem].type == pan)	appartient = 1;
  			}
  			
  		if (appartient == 1)
  			{
  			/*numeros des coordonnees selon x des sommets du triangle*/
  			zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  			surf_vol_elem_cage(zh, zi, zj, frontz, surfacefront, volumefront);
			/*printf("elem = %4d surfacefront = %11.5lf  volumefront = %11.5lf\n",elem,*surfacefront,*volumefront);*/
			}
		}
  	}


void surface_cage_volume_volume(double frontz, double *surfacefront,double *volumefront, int nc)
  	{

  	/*calcul de la surface du front et du volume entre le front et le fond du filet 
  	connaissant la position du front : frontz pour le catch2_volume numero nc*/
  	
  	int elem,zh,zi,zj,appartient,pa,pan;
  	
	*volumefront = 0.0;
	*surfacefront = 0.0;
	nb_pt_aval = 0;
	
	/*printf("volumefront = %5.2lf ",*volumefront);
	printf("surfacefront = %5.2lf \n",*surfacefront);*/

  	for (elem = 1; elem <= NOMBRE_SURFACES; elem++)
  		{
		appartient = 0;
  		for (pa = 1; pa<= Volume_cage[nc].nb_panel_catch2; pa++)
  			{
  			pan = Volume_cage[nc].panel_catch2[pa];
  			if (Surface[elem].type == pan)	appartient = 1;
  			}
  			
  		if (appartient == 1)
  			{
  			/*numeros des coordonnees selon x des sommets du triangle*/
  			zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  			surf_vol_elem_cage(zh, zi, zj, frontz, surfacefront, volumefront);
			/*printf("elem = %4d surfacefront = %11.5lf  volumefront = %11.5lf\n",elem,*surfacefront,*volumefront);*/
			}
		}
  	}
  	
	

float* cage_volume()
	{
	int nc,pa,elem;
  	double minz,maxz,surfacefr,volumefr;
	
	float* volumefr2 = NULL;	
	volumefr2 = malloc((Structure.nb_cage_volume+1) * sizeof(float));
	
	/*changement_variable_catch();*/
  	for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
  		{
  		wfcodend[3*elem-2] = wf[3*elem];
  		wfcodend[3*elem-1] = wf[3*elem-2];
  		wfcodend[3*elem-0] = wf[3*elem-1];
		}
	
  	for (nc = 1; nc<= Structure.nb_cage_volume; nc++)
  		{
  		extrema_direction_courant_cage_volume(&minz,&maxz,nc);
		
		/*definir le front de la prise dans la direction du courant*/
		surface_volume_cage_volume( maxz,  &surfacefr, &volumefr, nc);
		volumefr2[nc] = volumefr;
  		}
	return volumefr2;
	}


float* volume_cage()
	{
	int nc,pa,elem;
  	double minz,maxz,surfacefr,volumefr;
	
	float* volumefr1 = NULL;	
	volumefr1 = malloc((Structure.nb_cage_volume+1) * sizeof(float));
	if (volumefr1 == NULL)
	{
		printf("volumefr1 = NULL\n");
		exit(1);
	}
	
	/*changement_variable_catch();*/
  	for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
  		{
  		wfcodend[3*elem-2] = wf[3*elem];
  		wfcodend[3*elem-1] = wf[3*elem-2];
  		wfcodend[3*elem-0] = wf[3*elem-1];
		}
	
  	for (nc = 1; nc<= Structure.nb_cage_volume; nc++)
  		{
		maxz=0;
		
		/*definir le front de la prise dans la direction du courant*/
		surface_cage_volume_volume( maxz,  &surfacefr, &volumefr, nc);
		volumefr1[nc] = volumefr;
  		}
	return volumefr1;
	}

