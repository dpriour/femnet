#define PRINCIPAL 0
#include "4c19.h"

double surface_triangle2(double XX1, double YY1, double ZZ1, double XX2, double YY2, double ZZ2, double XX3, double YY3, double ZZ3)
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
					
	//printf("X %lf  %lf  %lf Y %lf %lf %lf  Z %lf %lf %lf ",XX1,XX2,XX3,YY1,YY2,YY3,ZZ1,ZZ2,ZZ3);
	//printf("s %lf  %lf  %lf ",sx,sy,sz);
	//printf("surface  %lf \n",surface);
	
	
  	return surface;
  	}
	
double longueur_segment2(double XX1, double YY1, double ZZ1, double XX2, double YY2, double ZZ2)
	{
	double sx,sy,sz,longueur;
	/*
	calcul de la longueur du segment dont les coordonnes du sommet 1 (2) sont
	XX1, YY1 ZZ1, (XX2, YY2,ZZ2)
	*/
	  	     
  	longueur = sqrt((XX2-XX1)*(XX2-XX1)+(YY2-YY1)*(YY2-YY1)+(ZZ2-ZZ1)*(ZZ2-ZZ1));
  	return longueur;
  	}
	
double rayon_maxi()
	{
	/*
	definir le rayon maxi perpendiculairement a la direction du courant
	*/
	
  	int elem,selon_y,selon_z,premier,sommet,noeu;
  	double rayon,reperey,reperez,miny,maxy,minz,maxz;
  	
  	/*
  	on recherche les axes y et z de l objet
  	s ils existe : selon_y et selon_z sont = a 1 dans ce cas sinon = 0
  	*/
  	selon_y = 0;
  	selon_z = 0;
  	for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
  		{
		if ( Noeud[elem].symy == 1 )	
			{
			reperey = wfcodend[3*elem-1];
  			selon_y = 1;
			//printf("reperey = %11.3lf \n",reperey);
			}
		if ( Noeud[elem].symz == 1 )	
			{
			reperez = wfcodend[3*elem-0];
  			selon_z = 1;
			//printf("reperez = %11.3lf \n",reperez);
			}
		}

  	/*
  	on initialise le rayon maxi a 0.0
  	*/
  	rayon = 0.0;
	
  	if ((selon_y == 1) || (selon_z == 1))
  		{
  		for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
  			{
  			if (wfcodend[3*elem-2] >= Prise.front)
  				{
  				if ((fabs(wfcodend[3*elem-1] - reperey) > rayon) && (selon_y == 1))	rayon = fabs(wfcodend[3*elem-1] - reperey);
  				if ((fabs(wfcodend[3*elem-0] - reperez) > rayon) && (selon_z == 1)) 	rayon = fabs(wfcodend[3*elem-0] - reperez);
  				//printf("radius = %11.3lf \n",rayon);
  				}
			}
  		}
  	else
  		{
  		premier = 0; 
  		/*tant que premier = 0 c est que miny,maxy,minz,maxz ne sont pas initialises*/
  		for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  			{
  			for (sommet = 1; sommet<= 3; sommet++)
  				{
  				/*noeu = numero du sommet de la surface elem*/
  				noeu = Surface[elem].extremite[sommet];
  				if (wfcodend[3*noeu-2] >= Prise.front)
  					{
  					/*si noeu est derriere le front*/
  					if (premier == 0)
  						{
  						/*initialisation de miny,maxy,minz,maxz*/
  						miny = wfcodend[3*noeu-1];
  						maxy = wfcodend[3*noeu-1];
  						minz = wfcodend[3*noeu-0];
  						maxz = wfcodend[3*noeu-0];
  						premier = 1; 
  						}
  					else
  						{
  						if (wfcodend[3*noeu-1] > maxy)      maxy = wfcodend[3*noeu-1];
   						if (wfcodend[3*noeu-1] < miny)      miny = wfcodend[3*noeu-1];
  						if (wfcodend[3*noeu-0] > maxz)      maxz = wfcodend[3*noeu-0];
  						if (wfcodend[3*noeu-0] < minz)      minz = wfcodend[3*noeu-0];
  						}
  					}
  				}
			}
			/*printf("miny  = %lf  maxy  = %lf  minz  = %lf  maxz  = %lf   \n",miny,maxy,minz,maxz);*/
			if ((maxy - miny) > (maxz - minz))	rayon = (maxy - miny) / 2.0;
			else					rayon = (maxz - minz) / 2.0;
  		}
  	
  	
  	
	return rayon;
	}


void extrema_direction_x(double *minx,double *maxx)
	{
	/*
	definir le min et le max dans la direction des x
	*/
	
  	int elem,sommet,zh;
  	double XX1;
  	
  	/*
  	on initialise le minx et maxx avec la coordonnee x du sommet 1 du triangle a maille losange 1.
	Si on n'a pas de triangle a maille losange on prend le 1er triangle a maille hexagonale.  	
  	*/
	if (NOMBRE_SURFACES != 0)
		{ 
	  	zh = yc(1,1);
	  	}
	else
		{
		zh = yc_hexa(1,1);
		}
	*minx = wf[zh];
	*maxx = wf[zh];
	
  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
  		for (sommet = 1; sommet<= 3; sommet++)
  			{
  			/*numeros de la coordonnee selon x du sommets no sommet du triangle*/
  			zh = yc(elem,3*sommet-2);
  		
  			/*coordonnee selon x du sommets no sommet du triangle*/
  			XX1 = wf[zh  ];
  			if (*minx > XX1) *minx = XX1;
  			if (*maxx < XX1) *maxx = XX1;
  			}
  		}
  
  	for (elem = 1; elem<= NOMBRE_SURF_HEXA; elem++)
  		{
  		for (sommet = 1; sommet<= 3; sommet++)
  			{
  			/*numeros de la coordonnee selon x du sommets no sommet du triangle*/
  			zh = yc_hexa(elem,3*sommet-2);
  		
  			/*coordonnee selon x du sommets no sommet du triangle*/
  			XX1 = wf[zh  ];
  			if (*minx > XX1) *minx = XX1;
  			if (*maxx < XX1) *maxx = XX1;
  			}
  		}
	}
	
void extrema_direction_courant(double *minx,double *maxx)
	{
	/*
	definir le min et le max des x dans la direction du courant
	*/
	
  	int elem,sommet,zh;
  	double XX1;
  	
  	/*
  	on initialise le minx et maxx avec la coordonnee x du sommet 1 du triangle a maille losange 1.
	Si on n'a pas de triangle a maille losange on prend le 1er triangle a maille hexagonale.  	
  	*/
	if (NOMBRE_SURFACES != 0)
		{ 
	  	zh = yc(1,1);
	  	}
	else
		{
		zh = yc_hexa(1,1);
		}
	*minx = wfcodend[zh];
	*maxx = wfcodend[zh];
	
  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
  		for (sommet = 1; sommet<= 3; sommet++)
  			{
  			/*numeros de la coordonnee selon x du sommets no sommet du triangle*/
  			zh = yc(elem,3*sommet-2);
  		
  			/*coordonnee selon x du sommets no sommet du triangle*/
  			XX1 = wfcodend[zh  ];
  			if (*minx > XX1) *minx = XX1;
  			if (*maxx < XX1) *maxx = XX1;
  			}
  		}
  
  	for (elem = 1; elem<= NOMBRE_SURF_HEXA; elem++)
  		{
  		for (sommet = 1; sommet<= 3; sommet++)
  			{
  			/*numeros de la coordonnee selon x du sommets no sommet du triangle*/
  			zh = yc_hexa(elem,3*sommet-2);
  		
  			/*coordonnee selon x du sommets no sommet du triangle*/
  			XX1 = wfcodend[zh  ];
  			if (*minx > XX1) *minx = XX1;
  			if (*maxx < XX1) *maxx = XX1;
  			}
  		}
	}
	
void extrema_direction_courant_meridian(double *minx,double *maxx)
	{
	/*
	definir le min et le max des x dans la direction du courant pour les panneaux utilises par meridian
	*/
	
  	int elem,sommet,zh,pa,first;
  	double XX1;
  	
  	/*
  	on initialise le minx et maxx avec la coordonnee x du sommet 1 du triangle a maille losange 1.
	Si on n'a pas de triangle a maille losange on prend le 1er triangle a maille hexagonale.  	
  	*/
	first = 0;
	
  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
  		for (pa = 1; pa<= Prise.nb_panel_meridian; pa++)
  			{
  			if (Surface[elem].type == Prise.panel_meridian[pa])
  				{
  				for (sommet = 1; sommet<= 3; sommet++)
  					{
  					/*numeros de la coordonnee selon x du sommets no sommet du triangle*/
  					zh = yc(elem,3*sommet-2);
  					XX1 = wfcodend[zh  ];
  					if (first == 0)
  						{
						first = 1;
  						*minx = XX1;
  						*maxx = XX1;
  						}
  					else
  						{
  						/*coordonnee selon x du sommets no sommet du triangle*/
  						if (*minx > XX1) *minx = XX1;
  						if (*maxx < XX1) *maxx = XX1;
  						}
 		
  					}
  				}
  			}
  		}
	}
	
void extrema_direction_courant_curvilinear(double *minx,double *maxx)
	{
	/*
	definir le min et le max des x dans la direction du courant pour les panneaux utilises par curvilinear
	*/
	
  	int elem,sommet,zh,pa,first;
  	double XX1;
  	
  	/*
  	on initialise le minx et maxx avec la coordonnee x du sommet 1 du triangle a maille losange 1.
	Si on n'a pas de triangle a maille losange on prend le 1er triangle a maille hexagonale.  	
  	*/
	first = 0;
	
  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
  		for (pa = 1; pa<= Prise.nb_panel_curvilinear; pa++)
  			{
  			if (Surface[elem].type == Prise.panel_curvilinear[pa])
  				{
  				for (sommet = 1; sommet<= 3; sommet++)
  					{
  					/*numeros de la coordonnee selon x du sommets no sommet du triangle*/
  					zh = yc(elem,3*sommet-2);
  					if (first == 0)
  						{
						first = 1;
  						XX1 = wfcodend[zh  ];
  						*minx = XX1;
  						*maxx = XX1;
  						}
  					else
  						{
  						/*coordonnee selon x du sommets no sommet du triangle*/
  						XX1 = wfcodend[zh  ];
  						if (*minx > XX1) *minx = XX1;
  						if (*maxx < XX1) *maxx = XX1;
  						}
 		
  					}
  				}
  			}
  		}
	}
	
void changement_variable_catch()
	{
	/*
	changement de variables pour que x (wfcodend) soit parallele au courant et horizontal
	y perpendiculaire au courant et horizontal et z inchange cad vertical ascendant

	ATTENTION peu etre remplacer par changement_variable(0)
	*/
	
  	int elem;
  	
  	if (Prise.catch_gravity > 0.0)			/*in this case the codend is expected to be outside the water and affected by the gravity*/
  		{
	  	for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
	  		{
	  		wfcodend[3*elem-2] =  -wf[3*elem-0];
	  		wfcodend[3*elem-1] =   wf[3*elem-1];
	  		wfcodend[3*elem-0] =   wf[3*elem-2];
			}
  		}
  	else						/*in this case the codend is expected to be inside the water and affected by the current*/
  		{
	  	for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
	  		{
	  		wfcodend[3*elem-2] =   wf[3*elem-2] * cos(PI/180*Courant.direction) + wf[3*elem-1] * sin(PI/180*Courant.direction);
	  		wfcodend[3*elem-1] = - wf[3*elem-2] * sin(PI/180*Courant.direction) + wf[3*elem-1] * cos(PI/180*Courant.direction);
	  		wfcodend[3*elem-0] =   wf[3*elem-0];
			}
		}
	}		

void changement_variable(int direction)
	{
	/*
	changement de variables pour que x (wfcodend) soit parallele a x si direction = 1
	a y si direction = 2
	a z si direction = 3
	et au courant si direction = 0
	*/
	
  	int elem;
	double teta;
  	
  	if (direction == 0)
		{
		teta = PI/180*Courant.direction;
		for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
  			{
  			wfcodend[3*elem-2] =   wf[3*elem-2] * cos(teta) + wf[3*elem-1] * sin(teta);
  			wfcodend[3*elem-1] = - wf[3*elem-2] * sin(teta) + wf[3*elem-1] * cos(teta);
  			wfcodend[3*elem-0] =   wf[3*elem-0];
			}
		}
  	if (direction == 1)
		{
		for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
  			{
  			wfcodend[3*elem-2] =   wf[3*elem-2];
  			wfcodend[3*elem-1] =   wf[3*elem-1];
  			wfcodend[3*elem-0] =   wf[3*elem-0];
			}
		}
  	if (direction == 2)
		{
		for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
  			{
  			wfcodend[3*elem-2] =   wf[3*elem-1];
  			wfcodend[3*elem-1] =   wf[3*elem-0];
  			wfcodend[3*elem-0] =   wf[3*elem-2];
			}
		}
  	if (direction == 3)
		{
		for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
  			{
  			wfcodend[3*elem-2] = - wf[3*elem-0];
  			wfcodend[3*elem-1] =   wf[3*elem-2];
  			wfcodend[3*elem-0] =   wf[3*elem-1];
			}
		}
	}		

void changement_variable2(double theta)
	{
	/*
	changement de variables pour que x (wfcodend) soit parallele a theta de l'axe des x
	*/
	
  	int elem;
	theta = theta / 180 * PI;
	for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
		{
		wfcodend[3*elem-2] =   wf[3*elem-2] * cos(theta) + wf[3*elem-1] * sin(theta);
		wfcodend[3*elem-1] = - wf[3*elem-2] * sin(theta) + wf[3*elem-1] * cos(theta);
		wfcodend[3*elem-0] =   wf[3*elem-0];
		}
	}		

int orientation_triangle(int zh,int zi,int zj)
	{
  	/*calculer l orientation du triangle 
  	si > 0 le volume compris entre ce triangle et le front s ajoute a la prise
  	si < 0 le volume compris entre ce triangle et le front se retranche de la prise
  	pour l orientation on calcule le produit vectoriel entre 12 et 13, 1 2 3 sont les sommets du triangle*/
  	
  	int orientation;
  	double nxx;
  	double y12,z12,y23,z23;
  	  	
  	/*variation de coordonnees entre les sommets*/
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
  	
int orientation_triangle_val(int zh,int zi,int zj)
	{
  	/*calculer l orientation du triangle 
  	si > 0 la valeur de ce triangle s ajoute a la valeur totale
  	si < 0 la valeur de ce triangle se retranche a la valeur totale
  	pour l orientation on calcule le produit vectoriel entre 12 et 13, 1 2 3 sont les sommets du triangle
  	zh, zi et zj sont les numéros des coordéées x des sommets du triangle*/
  	
  	int orientation;
  	double nxx;
  	double y12,z12,y23,z23;
  	  	
  	/*variation de coordonnees entre les sommets*/
  	y12 = wf[zi+1] - wf[zh+1];y23 = wf[zj+1] - wf[zi+1];
  	z12 = wf[zi+2] - wf[zh+2];z23 = wf[zj+2] - wf[zi+2];
  	
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
  	



















void surf_vol_elem(int zh,int zi,int zj,double frontx, double *surfacefront,double *volumefront)
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

  	/*ne traiter que les surfaces a l arriere ou en partie a l arriere du front*/
  	if ((XX1 >= frontx) || (XX2 >= frontx) || (XX3 >= frontx))
  		{
		sgn = orientation_triangle(zh, zi, zj);
  		
 		x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  		y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  		z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  			
  		/* surfaces totalement a l arriere  du front*/
  		if ((XX1 >= frontx) && (XX2 >= frontx) && (XX3 >= frontx))
  			{
			nb_pt_aval = nb_pt_aval + 3;
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, YY2, ZZ2, frontx, YY3, ZZ3);
  			volumetriangle = surfacetriangle * fabs((XX1 + XX2 + XX3) / 3.0 - frontx);
			/*printf("1 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
 		if ((XX1 < frontx) && (XX2 >= frontx) && (XX3 >= frontx))
  			{
			nb_pt_aval = nb_pt_aval + 2;
  			yinter1 = YY1 + y12 / x12 * (frontx - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontx - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontx - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontx - XX1);
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, YY2, ZZ2, frontx, YY3, ZZ3);
  			volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontx);
  			/*surface du triangle amont forme par 1 inter1 et inter2 : en amont du front a retranche de la surface totale*/
			surfacetriangleamont = surface_triangle2(frontx, YY1, ZZ1, frontx, yinter1, zinter1, frontx, yinter2, zinter2);
  			/*surface et volume en aval au front*/
    			surfacetriangle -=  surfacetriangleamont;
  			volumetriangle -=  (surfacetriangleamont * ((XX1 + frontx + frontx) / 3.0 - frontx));
			/*printf("2 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 >= frontx) && (XX2 < frontx) && (XX3 >= frontx))
  			{
			nb_pt_aval = nb_pt_aval + 2;
  			yinter1 = YY2 + y23 / x23 * (frontx - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontx - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontx - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontx - XX2);
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, YY2, ZZ2, frontx, YY3, ZZ3);
  			volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontx);
			surfacetriangleamont = surface_triangle2(frontx, yinter2, zinter2, frontx, YY2, ZZ2, frontx, yinter1, zinter1);
  			/*surface et volume en aval au front*/
  			surfacetriangle  -= surfacetriangleamont;
  			volumetriangle -= (surfacetriangleamont * ((frontx + XX2 + frontx) / 3.0 - frontx));
			/*printf("3 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 >= frontx) && (XX2 >= frontx) && (XX3 < frontx))
  			{
			nb_pt_aval = nb_pt_aval + 2;
  			yinter1 = YY3 + y31 / x31 * (frontx - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontx - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontx - XX3);
			zinter2 = ZZ3 + z23 / x23 * (frontx - XX3);
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, YY2, ZZ2, frontx, YY3, ZZ3);
  			/*surface totale du triangle*/
  			volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontx);
			surfacetriangleamont = surface_triangle2(frontx, yinter1, zinter1, frontx, yinter2, zinter2, frontx, YY3, ZZ3);
  			/*surface et volume en aval au front*/
  			surfacetriangle  -= surfacetriangleamont;
  			volumetriangle -= (surfacetriangleamont * ((frontx + frontx + XX3) / 3.0 - frontx));
			/*printf("4 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 1 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 >= frontx) && (XX2 < frontx) && (XX3 < frontx))
  			{
			nb_pt_aval = nb_pt_aval + 1;
  			yinter1 = YY1 + y12 / x12 * (frontx - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontx - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontx - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontx - XX1);
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, yinter1, zinter1, frontx, yinter2, zinter2);
  			volumetriangle = surfacetriangle * ((XX1 + frontx + frontx) / 3.0 - frontx);
			/*printf("5 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 2 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 < frontx) && (XX2 >= frontx) && (XX3 < frontx))
  			{
			nb_pt_aval = nb_pt_aval + 1;
  			yinter1 = YY2 + y23 / x23 * (frontx - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontx - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontx - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontx - XX2);
			surfacetriangle = surface_triangle2(frontx, yinter2, zinter2, frontx, YY2, ZZ2, frontx, yinter1, zinter1);
  			volumetriangle = surfacetriangle * ((frontx + XX2 + frontx) / 3.0 - frontx);
			/*printf("6 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 3 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 < frontx) && (XX2 < frontx) && (XX3 >= frontx))
  			{
			nb_pt_aval = nb_pt_aval + 1;
  			yinter1 = YY3 + y31 / x31 * (frontx - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontx - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontx - XX3);
  			zinter2 = ZZ3 + z23 / x23 * (frontx - XX3);
			surfacetriangle = surface_triangle2(frontx, yinter1, zinter1, frontx, yinter2, zinter2, frontx, YY3, ZZ3);
  			volumetriangle = surfacetriangle * ((frontx + frontx + XX3) / 3.0 - frontx);
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


void surf_vol_elem2(int zh,int zi,int zj,double frontx, double *surfacefront,double *volumefront,double *mean_height_surf)
	{
	/*calcul de la surface du front, du volume entre le front et le fond du filet et de sa hauteur moyenne
	pour une surface a maille losange ou hexagonale.*/
  	
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3,x12,y12,z12,x23,y23,z23,x31,y31,z31,surfacetriangle,volumetriangle;
  	double yinter1,zinter1,yinter2,zinter2,surfacetriangleamont,h_mean;
	int sgn;
	
	/*surfacetriangle = 0.0;
	volumetriangle = 0.0;
	sgn = 0;*/
	 	  		
	/*coordonnees du triangle*/
  	XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
  	YY1 = wfcodend[zh+1];	YY2 = wfcodend[zi+1];	YY3 = wfcodend[zj+1];
 	ZZ1 = wfcodend[zh+2];	ZZ2 = wfcodend[zi+2];	ZZ3 = wfcodend[zj+2];
 	h_mean = 0.0;

  	/*ne traiter que les surfaces a l arriere ou en partie a l arriere du front*/
  	if ((XX1 >= frontx) || (XX2 >= frontx) || (XX3 >= frontx))
  		{
		sgn = orientation_triangle(zh, zi, zj);
  		
 		x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  		y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  		z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  			
  		/* surfaces totalement a l arriere  du front*/
  		if ((XX1 >= frontx) && (XX2 >= frontx) && (XX3 >= frontx))
  			{
			nb_pt_aval = nb_pt_aval + 3;
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, YY2, ZZ2, frontx, YY3, ZZ3);
  			volumetriangle = surfacetriangle * fabs((XX1 + XX2 + XX3) / 3.0 - frontx);
  			h_mean = (ZZ1+ZZ2+ZZ3)/3.0;
			/*printf("1 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
 		if ((XX1 < frontx) && (XX2 >= frontx) && (XX3 >= frontx))
  			{
			nb_pt_aval = nb_pt_aval + 2;
  			yinter1 = YY1 + y12 / x12 * (frontx - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontx - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontx - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontx - XX1);
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, YY2, ZZ2, frontx, YY3, ZZ3);
  			volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontx);
  			/*surface du triangle amont forme par 1 inter1 et inter2 : en amont du front a retranche de la surface totale*/
			surfacetriangleamont = surface_triangle2(frontx, YY1, ZZ1, frontx, yinter1, zinter1, frontx, yinter2, zinter2);
  			/*surface et volume en aval au front*/
    			surfacetriangle -=  surfacetriangleamont;
  			volumetriangle -=  (surfacetriangleamont * ((XX1 + frontx + frontx) / 3.0 - frontx));
  			h_mean = ((ZZ1+ZZ2+ZZ3)/3.0*surfacetriangle-((ZZ1+zinter1+zinter2)/3.0*surfacetriangleamont))/(surfacetriangle-surfacetriangleamont);
  			/*h_mean weighted by the total surface and the amont surface*/
			/*printf("2 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 >= frontx) && (XX2 < frontx) && (XX3 >= frontx))
  			{
			nb_pt_aval = nb_pt_aval + 2;
  			yinter1 = YY2 + y23 / x23 * (frontx - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontx - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontx - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontx - XX2);
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, YY2, ZZ2, frontx, YY3, ZZ3);
  			volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontx);
			surfacetriangleamont = surface_triangle2(frontx, yinter2, zinter2, frontx, YY2, ZZ2, frontx, yinter1, zinter1);
  			/*surface et volume en aval au front*/
  			surfacetriangle  -= surfacetriangleamont;
  			volumetriangle -= (surfacetriangleamont * ((frontx + XX2 + frontx) / 3.0 - frontx));
  			h_mean = ((ZZ1+ZZ2+ZZ3)/3.0*surfacetriangle-((ZZ2+zinter1+zinter2)/3.0*surfacetriangleamont))/(surfacetriangle-surfacetriangleamont);
  			/*h_mean weighted by the total surface and the amont surface*/
			/*printf("3 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 >= frontx) && (XX2 >= frontx) && (XX3 < frontx))
  			{
			nb_pt_aval = nb_pt_aval + 2;
  			yinter1 = YY3 + y31 / x31 * (frontx - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontx - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontx - XX3);
			zinter2 = ZZ3 + z23 / x23 * (frontx - XX3);
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, YY2, ZZ2, frontx, YY3, ZZ3);
  			/*surface totale du triangle*/
  			volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontx);
			surfacetriangleamont = surface_triangle2(frontx, yinter1, zinter1, frontx, yinter2, zinter2, frontx, YY3, ZZ3);
  			/*surface et volume en aval au front*/
  			surfacetriangle  -= surfacetriangleamont;
  			volumetriangle -= (surfacetriangleamont * ((frontx + frontx + XX3) / 3.0 - frontx));
  			h_mean = ((ZZ1+ZZ2+ZZ3)/3.0*surfacetriangle-((ZZ3+zinter1+zinter2)/3.0*surfacetriangleamont))/(surfacetriangle-surfacetriangleamont);
  			/*h_mean weighted by the total surface and the amont surface*/
			/*printf("4 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 1 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 >= frontx) && (XX2 < frontx) && (XX3 < frontx))
  			{
			nb_pt_aval = nb_pt_aval + 1;
  			yinter1 = YY1 + y12 / x12 * (frontx - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontx - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontx - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontx - XX1);
			surfacetriangle = surface_triangle2(frontx, YY1, ZZ1, frontx, yinter1, zinter1, frontx, yinter2, zinter2);
  			volumetriangle = surfacetriangle * ((XX1 + frontx + frontx) / 3.0 - frontx);
  			h_mean = (ZZ1+zinter1+zinter2)/3.0;
			/*printf("5 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 2 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 < frontx) && (XX2 >= frontx) && (XX3 < frontx))
  			{
			nb_pt_aval = nb_pt_aval + 1;
  			yinter1 = YY2 + y23 / x23 * (frontx - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontx - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontx - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontx - XX2);
			surfacetriangle = surface_triangle2(frontx, yinter2, zinter2, frontx, YY2, ZZ2, frontx, yinter1, zinter1);
  			volumetriangle = surfacetriangle * ((frontx + XX2 + frontx) / 3.0 - frontx);
  			h_mean = (zinter1+ZZ2+zinter2)/3.0;
			/*printf("6 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/* surfaces partiellement a l arriere  du front : point 3 en aval du front
  		inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  		on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  		if ((XX1 < frontx) && (XX2 < frontx) && (XX3 >= frontx))
  			{
			nb_pt_aval = nb_pt_aval + 1;
  			yinter1 = YY3 + y31 / x31 * (frontx - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontx - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontx - XX3);
  			zinter2 = ZZ3 + z23 / x23 * (frontx - XX3);
			surfacetriangle = surface_triangle2(frontx, yinter1, zinter1, frontx, yinter2, zinter2, frontx, YY3, ZZ3);
  			volumetriangle = surfacetriangle * ((frontx + frontx + XX3) / 3.0 - frontx);
  			h_mean = (zinter1+zinter2+ZZ3)/3.0;
			/*printf("7 surfacetriangle = %12.6lf  \n",surfacetriangle);*/
  			}
  		/*ajout a la surface et au volume delimite par le front*/
  		*surfacefront += sgn * surfacetriangle;
  		*volumefront += sgn * volumetriangle;
  		*mean_height_surf += sgn * h_mean*surfacetriangle;
  		/*printf("signe = %6d  ",sgn);
  		printf("surfacetriangle = %12.6lf  ",surfacetriangle);
  		printf("volumetriangle = %12.6lf  \n",volumetriangle);
  		printf("surfacefront = %12.6lf  ",*surfacefront);
  		printf("volumefront = %12.6lf  \n",*volumefront);*/
  		}
	}


void surface_volume(double frontx, double *surfacefront,double *volumefront)
  	{

  	/*calcul de la surface du front et du volume entre le front et le fond du filet 
  	connaissant la position du front : frontx*/
  	
  	int elem,zh,zi,zj;
  	
	*volumefront = 0.0;
	*surfacefront = 0.0;
	nb_pt_aval = 0;
	
	//printf("frontx = %5.2lf ",frontx);
	//printf("volumefront = %5.2lf ",*volumefront);
	//printf("surfacefront = %5.2lf \n",*surfacefront);
  	for (elem = 1; elem <= NOMBRE_SURFACES; elem++)
  		{
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
		/*printf("elem = %4d surfacefront = %11.5lf  volumefront = %11.5lf\n",elem,*surfacefront,*volumefront);*/
  		surf_vol_elem(zh, zi, zj, frontx, surfacefront, volumefront);
		//printf("elem = %4d surfacefront = %11.5lf  volumefront = %11.5lf\n",elem,*surfacefront,*volumefront);/**/
		}
		
   	for (elem = 1; elem <= NOMBRE_SURF_HEXA; elem++)
  		{
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		zh = yc_hexa(elem,1);  zi = yc_hexa(elem,4);  zj = yc_hexa(elem,7);
  		surf_vol_elem(zh, zi, zj, frontx, surfacefront, volumefront);
		/*printf("elem = %4d surfacefront = %11.5lf  volumefront = %11.5lf\n",elem,*surfacefront,*volumefront);*/
		}
  	}
  	
  	
void surface_volume2(double frontx, double *surfacefront,double *volumefront,double *front_height)
  	{

  	/*calcul de la surface du front et du volume entre le front et le fond du filet 
  	connaissant la position du front : frontx*/
  	
  	int elem,zh,zi,zj;
  	double volumefront_height;
  	
	*volumefront = 0.0;
	*surfacefront = 0.0;
	volumefront_height = 0.0;	//sum of height by surface for triangle behind the front
	nb_pt_aval = 0;
	
	/*printf("volumefront = %5.2lf ",*volumefront);
	printf("surfacefront = %5.2lf \n",*surfacefront);*/

  	for (elem = 1; elem <= NOMBRE_SURFACES; elem++)
  		{
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
		/*printf("elem = %4d surfacefront = %11.5lf  volumefront = %11.5lf\n",elem,*surfacefront,*volumefront);*/
  		//surf_vol_elem(zh, zi, zj, frontx, surfacefront, volumefront);
  		surf_vol_elem2(zh, zi, zj, frontx, surfacefront, volumefront, &volumefront_height);
		/*printf("elem = %4d surfacefront = %11.5lf  volumefront = %11.5lf\n",elem,*surfacefront,*volumefront);*/
		}
	*front_height = volumefront_height / *surfacefront; //mean height of the front
		
   	for (elem = 1; elem <= NOMBRE_SURF_HEXA; elem++)
  		{
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		zh = yc_hexa(elem,1);  zi = yc_hexa(elem,4);  zj = yc_hexa(elem,7);
  		surf_vol_elem(zh, zi, zj, frontx, surfacefront, volumefront);
		/*printf("elem = %4d surfacefront = %11.5lf  volumefront = %11.5lf\n",elem,*surfacefront,*volumefront);*/
		}
  	}
  	
  	
double nouveau_front2(double frx, double mix, double max)
	{
	/*renvoie la position du front tel que volumefr soit = Prise.volume +- Prise.seuil*/
	double infx, supx, surfacefr, volumefr;
	int compteur;
	
  	surface_volume( frx,  &surfacefr, &volumefr);
  	
	infx = mix;
	supx = max;
	compteur = 0;
	/*printf(" surfacefr  = %11.5lf ",surfacefr);
	printf(" volumefr   = %11.5lf ",volumefr);
	printf(" infx  = %11.5lf ",infx);
	printf(" frx   = %11.5lf ",frx);
	printf(" supx  = %11.5lf \n",supx);*/
	
	do
		{
		compteur += 1;
		if(volumefr > Prise.volume + Prise.seuil) 	infx = frx;
		if(volumefr < Prise.volume - Prise.seuil) 	supx = frx;
		frx = (infx + supx) / 2.0;
		
  		surface_volume( frx,  &surfacefr, &volumefr);
  		
		if ( (frx <= mix) && (volumefr < Prise.volume - Prise.seuil) ) 
			{
		 	frx = mix;
			}
		if ( (frx >= max) && (volumefr > Prise.volume + Prise.seuil) ) 
			{
		 	frx = max;
			}
     	/*if (nbiter == 25)
     		{
		printf(" compteur  = %4d ",compteur);
		printf(" surfacefr  = %11.5lf ",surfacefr);
		printf(" volumefr   = %11.5lf ",volumefr);
		printf(" infx  = %11.5lf ",infx);
		printf(" frx   = %11.5lf ",frx);
		printf(" supx  = %11.5lf \n",supx);
		}*/
		}
	while((fabs(volumefr-Prise.volume) >= Prise.seuil) && (frx > mix) && (frx < max) && (compteur < 100));
	/*while((fabs(volumefr-Prise.volume) >= Prise.seuil) && (frx > mix) && (frx < max) && (fabs((supx-infx)*surfacefr) >= Prise.seuil));*/
	if (compteur ==100 ) frx = max;
	return frx;
	}
	
void pres_pris_elem2(int elem, double pression, double frontx)
	{
	/*Calcul des efforts de pression (wae) du poisson pour un element triangulaire
	  a maille losange  elem.*/
	  
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3,x12,y12,z12,x23,y23,z23,x31,y31,z31,surfacetriangle;
  	double yinter1,zinter1,yinter2,zinter2,surfacetriangleamont,surfacetriangleaval;
  	double angle3,angle2,force,cosa;
  	int zh,zi,zj;
	
	/*zh zi et zj sont les coordonnees x des 3 sommets du triangle de filet losange*/
  	zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  	
  	/*coordonnees du triangle*/
  	XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
  	YY1 = wfcodend[zh+1];	YY2 = wfcodend[zi+1];	YY3 = wfcodend[zj+1];
  	ZZ1 = wfcodend[zh+2];	ZZ2 = wfcodend[zi+2];	ZZ3 = wfcodend[zj+2];
 
  	if (Surface[elem].tarp == 1)
  		{
		rotation4(zh, zi, zj, &angle3, &angle2);
			  			
  		x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  		y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  		z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  			
		surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);

		force = pression * surfacetriangle;
  		//printf("pression = %5.2lf \n",pression);/**/

		wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
		wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
		wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;
		//exit(0);
   		}/**/
  	/*ne traiter que les surfaces a l arriere ou en partie a l arriere du front*/
  	/* surfaces totalement a l arriere  du front*/
  	if ((Surface[elem].tarp == 0) && ((XX1 > frontx) || (XX2 > frontx) || (XX3 > frontx)))
  		{
		rotation4(zh, zi, zj, &angle3, &angle2);
		/*la normale au triangle est verticale ascendante*/
		/*printf("angle3 = %5.2lf ",angle3);	printf("angle2 = %5.2lf \n",angle2);*/
			  			
  		x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  		y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  		z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  			
  		/* surfaces totalement a l arriere  du front*/
  		if ((XX1 > frontx) && (XX2 > frontx) && (XX3 > frontx))
  			{
			surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
  			/*printf("s_totale = %5.2lf ",surfacetriangle);*/
  
  			/*force sur le triangle due a la pression sur la surface */
			force = pression * surfacetriangle;
  			//printf("pression = %5.2lf \n",pression);/**/
			//exit(0);

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;
  			
   			}
  		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 > frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
  			yinter1 = YY1 + y12 / x12 * (frontx - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontx - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontx - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontx - XX1);
			surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
      				
  			/*force sur le triangle totale due a la pression sur la surface */
			force = pression * surfacetriangle;

   			/* Efforts  aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;

			surfacetriangleamont = surface_triangle2(XX1, YY1, ZZ1, frontx, yinter1, zinter1, frontx, yinter2, zinter2);
  			/*force sur le triangle amont due a la - pression sur la surface amont*/
			force = - pression * surfacetriangleamont;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] += - force + force / 3.0 * ((XX1-frontx)/(XX1-XX2)) + force / 3.0 * ((XX1-frontx)/(XX1-XX3));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] += - force / 3.0 * ((XX1-frontx)/(XX1-XX2));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] += - force / 3.0 * ((XX1-frontx)/(XX1-XX3));
  			if (Prise.angle_tensions > 0)
  				{
  				cosa = 	produit_scal(Surface[elem].n,Surface[elem].m)/Surface[elem].lg_tendue1/Surface[elem].lg_tendue2;
  				if (cosa < -1) cosa = -1.0;
  				if (cosa >  1) cosa =  1.0;
  				Prise.angle_twines = Prise.angle_twines + acos(cosa)*180.0/PI;
				Prise.tension_u = Prise.tension_u + Surface[elem].tension1;
				Prise.tension_v = Prise.tension_v + Surface[elem].tension2;	
				Prise.angle_tensions++;		//nb of surfaces + 1
				//printf("elem %4d ",elem);
				//printf("n %lf %lf %lf ",Surface[elem].n[1],Surface[elem].n[2],Surface[elem].n[3]);
				//printf("m %lf %lf %lf ",Surface[elem].m[1],Surface[elem].m[2],Surface[elem].m[3]);
				//printf("cosa %lf ",cosa);
				//printf("angle_twines %8.2lf ",acos(cosa)*180.0/PI);
				//printf("tension_u %8.2lf ",Surface[elem].tension1);
				//printf("tension_v %8.2lf ",Surface[elem].tension2);
				//printf("angle_tensions %5d \n",Prise.angle_tensions);
  				}
    			}
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)*/
  			yinter1 = YY2 + y23 / x23 * (frontx - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontx - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontx - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontx - XX2);
			surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
     				
  			/*force sur le triangle totale due a la pression sur la surface */
			force = pression * surfacetriangle;

   			/* Efforts  aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;

			surfacetriangleamont = surface_triangle2(frontx, yinter2, zinter2, XX2, YY2, ZZ2, frontx, yinter1, zinter1);
  			/*force sur le triangle amont due a la - pression sur la surface amont*/
			force = - pression * surfacetriangleamont;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] += - force / 3.0 * ((XX2-frontx)/(XX2-XX1));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] += - force + force / 3.0 * ((XX2-frontx)/(XX2-XX1)) + force / 3.0 * ((XX2-frontx)/(XX2-XX3));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] += - force / 3.0 * ((XX2-frontx)/(XX2-XX3));
  			if (Prise.angle_tensions > 0)
  				{
  				cosa = 	produit_scal(Surface[elem].n,Surface[elem].m)/Surface[elem].lg_tendue1/Surface[elem].lg_tendue2;
  				if (cosa < -1) cosa = -1.0;
  				if (cosa >  1) cosa =  1.0;
  				Prise.angle_twines = Prise.angle_twines + acos(cosa)*180.0/PI;
				Prise.tension_u = Prise.tension_u + Surface[elem].tension1;
				Prise.tension_v = Prise.tension_v + Surface[elem].tension2;	
				Prise.angle_tensions++;
				//printf("angle_twines %8.2lf ",acos(cosa)*180.0/PI);
				//printf("tension_u %8.2lf ",Surface[elem].tension1);
				//printf("tension_v %8.2lf ",Surface[elem].tension2);
				//printf("angle_tensions %5d \n",Prise.angle_tensions);
  				}
   			}
  		if ((XX1 > frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23)*/
  			yinter1 = YY3 + y31 / x31 * (frontx - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontx - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontx - XX3);
  			zinter2 = ZZ3 + z23 / x23 * (frontx - XX3);
			surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
     				
  			/*force sur le triangle totale due a la pression sur la surface */
			force = pression * surfacetriangle;

   			/* Efforts  aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;

			surfacetriangleamont = surface_triangle2(frontx, yinter1, zinter1, frontx, yinter2, zinter2, XX3, YY3, ZZ3);
  			/*force sur le triangle amont due a la - pression sur la surface amont*/
			force = - pression * surfacetriangleamont;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] += - force / 3.0 * ((XX3-frontx)/(XX3-XX1));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] += - force / 3.0 * ((XX3-frontx)/(XX3-XX2));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] += - force + force / 3.0 * ((XX3-frontx)/(XX3-XX1)) + force / 3.0 * ((XX3-frontx)/(XX3-XX2));
  			if (Prise.angle_tensions > 0)
  				{
  				cosa = 	(produit_scal(Surface[elem].n,Surface[elem].m))/Surface[elem].lg_tendue1/Surface[elem].lg_tendue2;
  				if (cosa < -1) cosa = -1.0;
  				if (cosa >  1) cosa =  1.0;
  				Prise.angle_twines = Prise.angle_twines + acos(cosa)*180.0/PI;
				Prise.tension_u = Prise.tension_u + Surface[elem].tension1;
				Prise.tension_v = Prise.tension_v + Surface[elem].tension2;	
				Prise.angle_tensions++;
				//printf("angle_twines %8.2lf ",acos(cosa)*180.0/PI);
				//printf("tension_u %8.2lf ",Surface[elem].tension1);
				//printf("tension_v %8.2lf ",Surface[elem].tension2);
				//printf("angle_tensions %5d \n",Prise.angle_tensions);
  				}
    			}
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 <= frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 1 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
  			yinter1 = YY1 + y12 / x12 * (frontx - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontx - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontx - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontx - XX1);
			surfacetriangleaval = surface_triangle2(XX1, YY1, ZZ1, frontx, yinter1, zinter1, frontx, yinter2, zinter2);
    				
  			/*force sur le triangle due a la pression sur la surface */
			force = pression * surfacetriangleaval;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force + force / 3.0 * ((XX1-frontx)/(XX1-XX2)) + force / 3.0 * ((XX1-frontx)/(XX1-XX3));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0 * ((XX1-frontx)/(XX1-XX2));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0 * ((XX1-frontx)/(XX1-XX3));
  			if (Prise.angle_tensions > 0)
  				{
  				cosa = 	produit_scal(Surface[elem].n,Surface[elem].m)/Surface[elem].lg_tendue1/Surface[elem].lg_tendue2;
  				if (cosa < -1) cosa = -1.0;
  				if (cosa >  1) cosa =  1.0;
  				Prise.angle_twines = Prise.angle_twines + acos(cosa)*180.0/PI;
				Prise.tension_u = Prise.tension_u + Surface[elem].tension1;
				Prise.tension_v = Prise.tension_v + Surface[elem].tension2;	
				Prise.angle_tensions++;
				//printf("angle_twines %8.2lf ",acos(cosa)*180.0/PI);
				//printf("tension_u %8.2lf ",Surface[elem].tension1);
				//printf("tension_v %8.2lf ",Surface[elem].tension2);
				//printf("angle_tensions %5d \n",Prise.angle_tensions);
  				}
    			}
  		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 2 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)*/
  			yinter1 = YY2 + y23 / x23 * (frontx - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontx - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontx - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontx - XX2);
			surfacetriangleaval = surface_triangle2(frontx, yinter2, zinter2, XX2, YY2, ZZ2, frontx, yinter1, zinter1);
    				
  			/*force sur le triangle due a la pression sur la surface */
			force = pression * surfacetriangleaval;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0 * ((XX2-frontx)/(XX2-XX1));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force + force / 3.0 * ((XX2-frontx)/(XX2-XX1)) + force / 3.0 * ((XX2-frontx)/(XX2-XX3));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0 * ((XX2-frontx)/(XX2-XX3));
  			if (Prise.angle_tensions > 0)
  				{
  				cosa = 	produit_scal(Surface[elem].n,Surface[elem].m)/Surface[elem].lg_tendue1/Surface[elem].lg_tendue2;
  				if (cosa < -1) cosa = -1.0;
  				if (cosa >  1) cosa =  1.0;
  				Prise.angle_twines = Prise.angle_twines + acos(cosa)*180.0/PI;
				Prise.tension_u = Prise.tension_u + Surface[elem].tension1;
				Prise.tension_v = Prise.tension_v + Surface[elem].tension2;	
				Prise.angle_tensions++;
				//printf("angle_twines %8.2lf ",acos(cosa)*180.0/PI);
				//printf("tension_u %8.2lf ",Surface[elem].tension1);
				//printf("tension_v %8.2lf ",Surface[elem].tension2);
				//printf("angle_tensions %5d \n",Prise.angle_tensions);
  				}
    			}
  		if ((XX1 <= frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 3 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23)*/
  			yinter1 = YY3 + y31 / x31 * (frontx - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontx - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontx - XX3);
  			zinter2 = ZZ3 + z23 / x23 * (frontx - XX3);
			surfacetriangleaval = surface_triangle2(frontx, yinter1, zinter1, frontx, yinter2, zinter2, XX3, YY3, ZZ3);
    				
  			/*force sur le triangle due a la pression sur la surface */
			force = pression * surfacetriangleaval;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0 * ((XX3-frontx)/(XX3-XX1));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0 * ((XX3-frontx)/(XX3-XX2));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force + force / 3.0 * ((XX3-frontx)/(XX3-XX1)) + force / 3.0 * ((XX3-frontx)/(XX3-XX2));
  			if (Prise.angle_tensions > 0)
  				{
  				cosa = 	produit_scal(Surface[elem].n,Surface[elem].m)/Surface[elem].lg_tendue1/Surface[elem].lg_tendue2;
  				if (cosa < -1) cosa = -1.0;
  				if (cosa >  1) cosa =  1.0;
  				Prise.angle_twines = Prise.angle_twines + acos(cosa)*180.0/PI;
				Prise.tension_u = Prise.tension_u + Surface[elem].tension1;
				Prise.tension_v = Prise.tension_v + Surface[elem].tension2;	
				Prise.angle_tensions++;
				//printf("angle_twines %8.2lf ",acos(cosa)*180.0/PI);
				//printf("tension_u %8.2lf ",Surface[elem].tension1);
				//printf("tension_v %8.2lf ",Surface[elem].tension2);
				//printf("angle_tensions %5d \n",Prise.angle_tensions);
  				}
    			}
		}
	/* Effort elementaire place dans l'espace*/
	base1( -(angle2), 2, -(angle3),  3,  9, wae);
	}
	
	
void pres_pris_elem3(int elem, double pression, double frontx)
	{
	/*Calcul des efforts de pression (wae) du poisson pour un element triangulaire
	  a maille losange  elem.*/
	  
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3,x12,y12,z12,x23,y23,z23,x31,y31,z31,surfacetriangle;
  	double yinter1,zinter1,yinter2,zinter2,surfacetriangleamont,surfacetriangleaval;
  	double angle3,angle2,force;
  	double xA,xB,xC,yA,yB,yC,zA,zB,zC,xP,xQ,yP,yQ,zP,zQ,N[4];
  	double FAx,FAy,FAz,FPx,FPy,FPz,FQx,FQy,FQz;
  	int zh,zi,zj,zu,zv,zw,zl,zk;
	double AA[4],BB[4],CC[4],FA[4], FB[4], FC[4],Fzh[4],Fzi[4],Fzj[4];
	double delta_x,ff[10],WE[10][10],Xb,Xc,Fr,Yb,Yc,Zb,Zc,Yr,Zr,Xb2,Xb3,Xc2,Xc3,Fr2,Fr3;
	double **Kr,*xKr,*cKr,Kp[10][10];

	/*allocation de la matrice raideur Kr*/
	xKr = (double *) malloc (10 * 10 * sizeof(double));  	if (xKr == NULL){printf("xKr	= NULL \n" );exit(0);}
	Kr = (double **) malloc (10 * sizeof(double *));	if (Kr	 == NULL){printf("Kr	= NULL \n" );exit(0);}
	cKr = xKr;
	for (zk=0;zk<10;zk++)
  		{
  		Kr[zk] = cKr;
  		cKr += 10;
		}
	/*elem = 60;*/
	/*zh zi et zj sont les coordonnees x des 3 sommets du triangle de filet losange*/
  	zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  	
  	/*mise a zero du vecteur effort wae et de la matrice raideur Kr*/
    	for (zl = 1; zl<= 9; zl++) wae[zl] = 0.0;
	for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kr[zl][zk] = 0.0;
	for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = 0.0;
  	/*coordonnees du triangle*/
  	XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
  	YY1 = wfcodend[zh+1];	YY2 = wfcodend[zi+1];	YY3 = wfcodend[zj+1];
  	ZZ1 = wfcodend[zh+2];	ZZ2 = wfcodend[zi+2];	ZZ3 = wfcodend[zj+2];

      			/*TEST_debut3
			delta_x = 0.00001;
			for( zu = 0 ; zu <= 10 ; zu++ )
      				{
      				if (zu == 1) XX1 =XX1 + delta_x;
      				if (zu == 2) YY1 =YY1 + delta_x;
      				if (zu == 3) ZZ1 =ZZ1 + delta_x;
      				if (zu == 4) XX2 =XX2 + delta_x;
      				if (zu == 5) YY2 =YY2 + delta_x;
      				if (zu == 6) ZZ2 =ZZ2 + delta_x;
      				if (zu == 7) XX3 =XX3 + delta_x;
      				if (zu == 8) YY3 =YY3 + delta_x;
      				if (zu == 9) ZZ3 =ZZ3 + delta_x;
      				TEST_fin3*/
  	/*ne traiter que les surfaces a l arriere ou en partie a l arriere du front*/
  	/* surfaces totalement a l arriere  du front*/
  	if ((Surface[elem].tarp == 0) && ((XX1 > frontx) || (XX2 > frontx) || (XX3 > frontx)))
  		{
  		x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  		y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  		z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  			
  		/* surfaces totalement a l arriere  du front*/
  		if ((XX1 > frontx) && (XX2 > frontx) && (XX3 > frontx))
  			{
			/*printf("elem1 : %d \n",elem);
			exit(0);*/
			AA[1] = XX1;		AA[2] = YY1;		AA[3] = ZZ1;
			BB[1] = XX2;		BB[2] = YY2;		BB[3] = ZZ2;
			CC[1] = XX3;		CC[2] = YY3;		CC[3] = ZZ3;
			pression_totale(AA,BB,CC,pression,FA,FB,FC,Kr);
			wae[1] = FA[1];		wae[2] = FA[2];		wae[3] = FA[3];
			wae[4] = FB[1];		wae[5] = FB[2];		wae[6] = FB[3];
			wae[7] = FC[1];		wae[8] = FC[2];		wae[9] = FC[3];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl][zk];/**/
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];/**/
   			}
  		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 > frontx))
  			{
			/*printf("elem2 : %d \n",elem);
			exit(0);*/
			AA[1] = XX1;		AA[2] = YY1;		AA[3] = ZZ1;
			BB[1] = XX2;		BB[2] = YY2;		BB[3] = ZZ2;
			CC[1] = XX3;		CC[2] = YY3;		CC[3] = ZZ3;
			pression_totale(AA,BB,CC,pression,FA,FB,FC,Kr);
			wae[1] = FA[1];		wae[2] = FA[2];		wae[3] = FA[3];
			wae[4] = FB[1];		wae[5] = FB[2];		wae[6] = FB[3];
			wae[7] = FC[1];		wae[8] = FC[2];		wae[9] = FC[3];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl][zk];/**/
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];
			pression_partielle2(AA,BB,CC,-pression,frontx,FA,FB,FC,Kr);
			wae[1] += FA[1];	wae[2] += FA[2];	wae[3] += FA[3];
			wae[4] += FB[1];	wae[5] += FB[2];	wae[6] += FB[3];
			wae[7] += FC[1];	wae[8] += FC[2];	wae[9] += FC[3];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] += Kr[zl][zk];/**/
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];
    			}
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
			/*printf("elem3 : %d \n",elem);
			exit(0);*/
			AA[1] = XX2;		AA[2] = YY2;		AA[3] = ZZ2;
			BB[1] = XX3;		BB[2] = YY3;		BB[3] = ZZ3;
			CC[1] = XX1;		CC[2] = YY1;		CC[3] = ZZ1;
			pression_totale(AA,BB,CC,pression,FA,FB,FC,Kr);
			wae[4] = FA[1];		wae[5] = FA[2];		wae[6] = FA[3];
			wae[7] = FB[1];		wae[8] = FB[2];		wae[9] = FB[3];
			wae[1] = FC[1];		wae[2] = FC[2];		wae[3] = FC[3];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl][zk];/**/
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];/**/
			pression_partielle2(AA,BB,CC,-pression,frontx,FA,FB,FC,Kr);
			wae[4] += FA[1];	wae[5] += FA[2];	wae[6] += FA[3];
			wae[7] += FB[1];	wae[8] += FB[2];	wae[9] += FB[3];
			wae[1] += FC[1];	wae[2] += FC[2];	wae[3] += FC[3];
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];/**/
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] += Kr[zl][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kr[zl][zk] = Kp[zl][zk];
			for (zl = 1; zl<= 3; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl+6][zk];
			for (zl = 4; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl-3][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kr[zl][zk] = Kp[zl][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 3; zk++)	Kp[zl][zk] = Kr[zl][zk+6];
			for (zl = 1; zl<= 9; zl++)	for (zk = 4; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl][zk-3];/**/
   			}
  		if ((XX1 > frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
			/*printf("elem4 : %d \n",elem);
			exit(0);*/
			AA[1] = XX3;		AA[2] = YY3;		AA[3] = ZZ3;
			BB[1] = XX1;		BB[2] = YY1;		BB[3] = ZZ1;
			CC[1] = XX2;		CC[2] = YY2;		CC[3] = ZZ2;
			pression_totale(AA,BB,CC,pression,FA,FB,FC,Kr);
			wae[7] = FA[1];		wae[8] = FA[2];		wae[9] = FA[3];
			wae[1] = FB[1];		wae[2] = FB[2];		wae[3] = FB[3];
			wae[4] = FC[1];		wae[5] = FC[2];		wae[6] = FC[3];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl][zk];/**/
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];/**/
			pression_partielle2(AA,BB,CC,-pression,frontx,FA,FB,FC,Kr);
			wae[7] += FA[1];	wae[8] += FA[2];	wae[9] += FA[3];
			wae[1] += FB[1];	wae[2] += FB[2];	wae[3] += FB[3];
			wae[4] += FC[1];	wae[5] += FC[2];	wae[6] += FC[3];
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];/**/
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] += Kr[zl][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kr[zl][zk] = Kp[zl][zk];
			for (zl = 1; zl<= 6; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl+3][zk];
			for (zl = 7; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl-6][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kr[zl][zk] = Kp[zl][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 6; zk++)	Kp[zl][zk] = Kr[zl][zk+3];
			for (zl = 1; zl<= 9; zl++)	for (zk = 7; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl][zk-6];/**/
    			}
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 <= frontx))
  			{
			/*printf("elem5 : %d \n",elem);
			exit(0);*/
			AA[1] = XX1;	AA[2] = YY1;	AA[3] = ZZ1;
			BB[1] = XX2;	BB[2] = YY2;	BB[3] = ZZ2;
			CC[1] = XX3;	CC[2] = YY3;	CC[3] = ZZ3;
			pression_partielle2(AA,BB,CC,pression,frontx,FA,FB,FC,Kr);
			wae[1] = FA[1];	wae[2] = FA[2];	wae[3] = FA[3];
			wae[4] = FB[1];	wae[5] = FB[2];	wae[6] = FB[3];
			wae[7] = FC[1];	wae[8] = FC[2];	wae[9] = FC[3];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl][zk];/**/
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];/**/
    			}
  		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
			/*printf("elem6 : %d \n",elem);
			exit(0);*/
			AA[1] = XX2;	AA[2] = YY2;	AA[3] = ZZ2;
			BB[1] = XX3;	BB[2] = YY3;	BB[3] = ZZ3;
			CC[1] = XX1;	CC[2] = YY1;	CC[3] = ZZ1;
			pression_partielle2(AA,BB,CC,pression,frontx,FA,FB,FC,Kr);
			wae[4] = FA[1];	wae[5] = FA[2];	wae[6] = FA[3];
			wae[7] = FB[1];	wae[8] = FB[2];	wae[9] = FB[3];
			wae[1] = FC[1];	wae[2] = FC[2];	wae[3] = FC[3];
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];/**/
			for (zl = 1; zl<= 3; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl+6][zk];
			for (zl = 4; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl-3][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kr[zl][zk] = Kp[zl][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 3; zk++)	Kp[zl][zk] = Kr[zl][zk+6];
			for (zl = 1; zl<= 9; zl++)	for (zk = 4; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl][zk-3];/**/
    			}
  		if ((XX1 <= frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
			/*printf("elem7 : %d \n",elem);
			exit(0);*/
			AA[1] = XX3;	AA[2] = YY3;	AA[3] = ZZ3;
			BB[1] = XX1;	BB[2] = YY1;	BB[3] = ZZ1;
			CC[1] = XX2;	CC[2] = YY2;	CC[3] = ZZ2;
			pression_partielle2(AA,BB,CC,pression,frontx,FA,FB,FC,Kr);
			wae[7] = FA[1];	wae[8] = FA[2];	wae[9] = FA[3];
			wae[1] = FB[1];	wae[2] = FB[2];	wae[3] = FB[3];
			wae[4] = FC[1];	wae[5] = FC[2];	wae[6] = FC[3];
			Prise.drag = Prise.drag + FA[1] + FB[1] + FC[1];/**/
			for (zl = 1; zl<= 6; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl+3][zk];
			for (zl = 7; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl-6][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 9; zk++)	Kr[zl][zk] = Kp[zl][zk];
			for (zl = 1; zl<= 9; zl++)	for (zk = 1; zk<= 6; zk++)	Kp[zl][zk] = Kr[zl][zk+3];
			for (zl = 1; zl<= 9; zl++)	for (zk = 7; zk<= 9; zk++)	Kp[zl][zk] = Kr[zl][zk-6];/**/
    			}
		}
			
      				/*TEST_debut3
      				if (zu == 0)
      					{
					for (zv = 1 ;zv <= 9 ;zv++ )	ff[zv] = wae[zv];
      					}
      				if (zu == 1) XX1 =XX1 - delta_x;
      				if (zu == 2) YY1 =YY1 - delta_x;
      				if (zu == 3) ZZ1 =ZZ1 - delta_x;
      				if (zu == 4) XX2 =XX2 - delta_x;
      				if (zu == 5) YY2 =YY2 - delta_x;
      				if (zu == 6) ZZ2 =ZZ2 - delta_x;
      				if (zu == 7) XX3 =XX3 - delta_x;
      				if (zu == 8) YY3 =YY3 - delta_x;
      				if (zu == 9) ZZ3 =ZZ3 - delta_x;
      		
      				if ((zu > 0) && (zu < 10))
      					{
					for (zv = 1 ;zv <= 9 ;zv++ )	WE[zv][zu] = - (wae[zv] - ff[zv]) / delta_x;
      					}
      				if (zu == 10)
      					{
					printf("elem : %d zh : %d zi : %d zj : %d\n",elem,zh,zi,zj);
					for (zv = 1 ;zv <= 9 ;zv++ )
						{
						printf("we = ");	for (zw = 1 ;zw <= 9 ;zw++ )	printf("%12.5lf ",Kp[zv][zw]);	printf(" \n");
						printf("WE = ");	for (zw = 1 ;zw <= 9 ;zw++ )	printf("%12.5lf ",WE[zv][zw]);	printf(" \n");
						}
      					}
				}
				exit(0);
      				TEST_fin3*/
	/* Mise a jour du vecteur effort global*/
    	for (zl = 1; zl<= 9; zl++) wasurf[yc(elem,zl)] += wae[zl];

	/* Mise a jour de la matrice de raideur globale*/
	if (Structure.type_solver == 1)
	{
		for (zl = 1; zl<= 9; zl++)
			{
			for (zk = 1; zk<= 9; zk++) 
				{
				/* we est la matrice de raideur calculee dans etirement4.
				La matrice globale est rangee differemment. Ce n'est plus une matrice
				bande. La diagonale est devenu la colonne eca de ze*/
				ze[yc(elem,zl)][eca+yc(elem,zk)-yc(elem,zl)] += Kp[zl][zk];/**/
				}
			}
	}
	else if (Structure.type_solver == 2)
	{
		for (zl = 1; zl<= 9; zl++)
		{
		for (zk = 1; zk<= 9; zk++) 
			{
				affectation_pardiso(Kp[zl][zk], yc(elem,zl), yc(elem,zk));
			}
		}
	}

	/*free xKr Kr*/
	if (xKr		!= NULL)        free(xKr);
	if (Kr		!= NULL)        free(Kr);
	}

void pression_partielle(double AA[4], double BB[4], double CC[4], double pression, double frontx, double *FA, double *FB, double *FC)
	{
	/*calcul des efforts de pressions sur un triangle de sommets AA,BB,CC
	la pression est pression
	le sommet AA est derrierre le frontx
	les efforts sur les sommets sont placés dans FA, FB, FC*/
	
  	double xP,xQ,yP,yQ,zP,zQ,N[4];
  	double FAx,FAy,FAz,FPx,FPy,FPz,FQx,FQy,FQz;
  	
  	/*coordonnees des points P Q du front et des cotes AB et AC*/
	xP = frontx;
	yP = AA[2]+(BB[2]-AA[2])*(frontx-AA[1])/(BB[1]-AA[1]);
	zP = AA[3]+(BB[3]-AA[3])*(frontx-AA[1])/(BB[1]-AA[1]);
	xQ = frontx;
	yQ = AA[2]+(CC[2]-AA[2])*(frontx-AA[1])/(CC[1]-AA[1]);
	zQ = AA[3]+(CC[3]-AA[3])*(frontx-AA[1])/(CC[1]-AA[1]);
  	/*printf("P = %7.3lf %7.3lf %7.3lf ",xP,yP,zP);
  	printf("Q = %7.3lf %7.3lf %7.3lf \n",xQ,yQ,zQ);*/
	
 	/*vecteur normal au triangle dont la norme est le double de la surFace du triangle APQ*/
	N[1] = (BB[2]-AA[2])*(frontx-AA[1])*(frontx-AA[1])/(BB[1]-AA[1])*(CC[3]-AA[3])/(CC[1]-AA[1])-(BB[3]-AA[3])*(frontx-AA[1])*(frontx-AA[1])/(BB[1]-AA[1])*(CC[2]-AA[2])/(CC[1]-AA[1]);
	N[2] = (BB[3]-AA[3])*(frontx-AA[1])*(frontx-AA[1])/(BB[1]-AA[1])-(frontx-AA[1])*(frontx-AA[1])*(CC[3]-AA[3])/(CC[1]-AA[1]);
	N[3] = (frontx-AA[1])*(frontx-AA[1])*(CC[2]-AA[2])/(CC[1]-AA[1])-(BB[2]-AA[2])*(frontx-AA[1])*(frontx-AA[1])/(BB[1]-AA[1]);
  	/*printf("N = %7.3lf %7.3lf %7.3lf \n",N[1],N[2],N[3]);*/
	
	/*forces sur le triangle APQ*/
	FAx = -pression/6.0*N[1];
	FPx = -pression/6.0*N[1];
	FQx = -pression/6.0*N[1];
	FAy = -pression/6.0*N[2];
	FPy = -pression/6.0*N[2];
	FQy = -pression/6.0*N[2];
	FAz = -pression/6.0*N[3];
	FPz = -pression/6.0*N[3];
	FQz = -pression/6.0*N[3];
  	/*printf("FA = %7.3lf %7.3lf %7.3lf ",FAx,FAy,FAz);
  	printf("FP = %7.3lf %7.3lf %7.3lf ",FPx,FPy,FPz);
  	printf("FQ = %7.3lf %7.3lf %7.3lf \n",FQx,FQy,FQz);*/
	
	/*forces sur le triangle ABC apres avoir reparti les efforts precedents*/
	FA[1] = FAx + FPx - FPx*(frontx-AA[1])/(BB[1]-AA[1]) + FQx - FQx*(frontx-AA[1])/(CC[1]-AA[1]);
	FA[2] = FAy + FPy - FPy*(frontx-AA[1])/(BB[1]-AA[1]) + FQy - FQy*(frontx-AA[1])/(CC[1]-AA[1]);
	FA[3] = FAz + FPz - FPz*(frontx-AA[1])/(BB[1]-AA[1]) + FQz - FQz*(frontx-AA[1])/(CC[1]-AA[1]);
	FB[1] = FPx*(frontx-AA[1])/(BB[1]-AA[1]);
	FB[2] = FPy*(frontx-AA[1])/(BB[1]-AA[1]);
	FB[3] = FPz*(frontx-AA[1])/(BB[1]-AA[1]);
	FC[1] = FQx*(frontx-AA[1])/(CC[1]-AA[1]);
	FC[2] = FQy*(frontx-AA[1])/(CC[1]-AA[1]);
	FC[3] = FQz*(frontx-AA[1])/(CC[1]-AA[1]);
	}

void pression_partielle2(double AA[4], double BB[4], double CC[4], double pression, double frontx, double *FA, double *FB, double *FC, double **Kp)
	{
	/*calcul des efforts de pressions sur un triangle de sommets AA,BB,CC
	la pression est pression
	le sommet AA est derrierre le frontx
	les efforts sur les sommets sont placés dans FA, FB, FC*/
	
  	double xP,xQ,yP,yQ,zP,zQ,N[4];
  	double FAx,FAy,FAz,FPx,FPy,FPz,FQx,FQy,FQz;
  	double Xb,Xc,Fr,Yb,Yc,Zb,Zc,Yr,Zr,Xb2,Xb3,Xc2,Xc3,Fr2,Fr3;
  		
  	/*coordonnees des points P Q du front et des cotes AB et AC*/
	xP = frontx;
	yP = AA[2]+(BB[2]-AA[2])*(frontx-AA[1])/(BB[1]-AA[1]);
	zP = AA[3]+(BB[3]-AA[3])*(frontx-AA[1])/(BB[1]-AA[1]);
	xQ = frontx;
	yQ = AA[2]+(CC[2]-AA[2])*(frontx-AA[1])/(CC[1]-AA[1]);
	zQ = AA[3]+(CC[3]-AA[3])*(frontx-AA[1])/(CC[1]-AA[1]);
  	/*printf("P = %7.3lf %7.3lf %7.3lf ",xP,yP,zP);
  	printf("Q = %7.3lf %7.3lf %7.3lf \n",xQ,yQ,zQ);*/
	
 	/*vecteur normal au triangle dont la norme est le double de la surFace du triangle APQ*/
	N[1] = (BB[2]-AA[2])*(frontx-AA[1])*(frontx-AA[1])/(BB[1]-AA[1])*(CC[3]-AA[3])/(CC[1]-AA[1])-(BB[3]-AA[3])*(frontx-AA[1])*(frontx-AA[1])/(BB[1]-AA[1])*(CC[2]-AA[2])/(CC[1]-AA[1]);
	N[2] = (BB[3]-AA[3])*(frontx-AA[1])*(frontx-AA[1])/(BB[1]-AA[1])-(frontx-AA[1])*(frontx-AA[1])*(CC[3]-AA[3])/(CC[1]-AA[1]);
	N[3] = (frontx-AA[1])*(frontx-AA[1])*(CC[2]-AA[2])/(CC[1]-AA[1])-(BB[2]-AA[2])*(frontx-AA[1])*(frontx-AA[1])/(BB[1]-AA[1]);
  	/*printf("N = %7.3lf %7.3lf %7.3lf \n",N[1],N[2],N[3]);*/
	
	/*forces sur le triangle APQ*/
	FAx = -pression/6.0*N[1];
	FPx = -pression/6.0*N[1];
	FQx = -pression/6.0*N[1];
	FAy = -pression/6.0*N[2];
	FPy = -pression/6.0*N[2];
	FQy = -pression/6.0*N[2];
	FAz = -pression/6.0*N[3];
	FPz = -pression/6.0*N[3];
	FQz = -pression/6.0*N[3];
  	/*printf("FA = %7.3lf %7.3lf %7.3lf ",FAx,FAy,FAz);
  	printf("FP = %7.3lf %7.3lf %7.3lf ",FPx,FPy,FPz);
  	printf("FQ = %7.3lf %7.3lf %7.3lf \n",FQx,FQy,FQz);*/
	
	/*forces sur le triangle ABC apres avoir reparti les efforts precedents*/
	FA[1] = FAx + FPx - FPx*(frontx-AA[1])/(BB[1]-AA[1]) + FQx - FQx*(frontx-AA[1])/(CC[1]-AA[1]);
	FA[2] = FAy + FPy - FPy*(frontx-AA[1])/(BB[1]-AA[1]) + FQy - FQy*(frontx-AA[1])/(CC[1]-AA[1]);
	FA[3] = FAz + FPz - FPz*(frontx-AA[1])/(BB[1]-AA[1]) + FQz - FQz*(frontx-AA[1])/(CC[1]-AA[1]);
	FB[1] = FPx*(frontx-AA[1])/(BB[1]-AA[1]);
	FB[2] = FPy*(frontx-AA[1])/(BB[1]-AA[1]);
	FB[3] = FPz*(frontx-AA[1])/(BB[1]-AA[1]);
	FC[1] = FQx*(frontx-AA[1])/(CC[1]-AA[1]);
	FC[2] = FQy*(frontx-AA[1])/(CC[1]-AA[1]);
	FC[3] = FQz*(frontx-AA[1])/(CC[1]-AA[1]);
	Xb = BB[1]-AA[1];
	Xc = CC[1]-AA[1];
	Fr = frontx-AA[1];
	Yb = BB[2]-AA[2];
	Yc = CC[2]-AA[2];
	Zb = BB[3]-AA[3];
	Zc = CC[3]-AA[3];
	Yr = Yb*Fr/Xb*Zc/Xc;
	Zr = Zb*Fr/Xb*Yc/Xc;
	Xb2 = Xb*Xb;
	Xb3 = Xb*Xb2;
	Xc2 = Xc*Xc;
	Xc3 = Xc*Xc2;
	Fr2 = Fr*Fr;
	Fr3 = Fr*Fr2;

	Kp[1][1] = -pression/6.0*(6.0*Xb3*Xc3*Yr-6.0*Xb3*Xc3*Zr-5.0*Xb2*Xc3*Yr*Fr-5.0*Xb3*Xc2*Yr*Fr+3.0*Xb*Xc2*Zb*Fr2*Yc+6.0*Xb3*Xc2*Zr*Fr+Fr2*Xc3*Yr*Xb+2.0*Fr2*Xc2*Yr*Xb2+3.0*Fr*Xc3*Zr*Xb2-Fr3*Xc2*Zb*Yc-Fr2*Xc2*Zr*Xb2-Fr2*Xb*Xc2*Yb*Zc+Fr3*Xc2*Yb*Zc-Fr2*Xc3*Zr*Xb+Fr2*Xb3*Xc*Yr-Fr3*Xb*Xc*Zb*Yc-2.0*Fr2*Xb3*Xc*Zr-Fr2*Xb2*Xc*Yb*Zc+Fr3*Xb2*Yb*Zc)/Xb3/Xc3;
	Kp[1][2] = pression/6.0*Fr2*(-Zc+Zb)*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc2;
	Kp[1][3] = -pression/6.0*Fr2*(Yb-Yc)*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc2;
	Kp[1][4] = -pression/6.0*Fr2*(Yb*Zc-Zb*Yc)*(3.0*Xb*Xc-2.0*Fr*Xc-Fr*Xb)/Xb3/Xc2;
	Kp[1][5] = pression/6.0*Fr2*Zc*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc2;
	Kp[1][6] = -pression/6.0*Fr2*Yc*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc2;
	Kp[1][7] = -pression/6.0*Fr2*(Yb*Zc-Zb*Yc)*(3.0*Xb*Xc-Fr*Xc-2.0*Fr*Xb)/Xb2/Xc3;
	Kp[1][8] = -pression/6.0*Zb*Fr2*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc2;
	Kp[1][9] = pression/6.0*Yb*Fr2*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc2;
	Kp[2][1] = pression/6.0*Fr*(-6.0*Xb2*Xc3*Zb+6.0*Xb*Xc3*Zb*Fr+6.0*Xb3*Xc2*Zc-6.0*Xb3*Xc*Fr*Zc-2.0*Fr2*Xc3*Zb-3.0*Fr*Xc2*Zc*Xb2+Fr2*Xc*Zc*Xb2+Fr2*Xc2*Zc*Xb+3.0*Fr*Xb2*Zb*Xc2-Fr2*Xb*Zb*Xc2+2.0*Fr2*Xb3*Zc-Fr2*Xb2*Zb*Xc)/Xb3/Xc3;
	Kp[2][2] = 0.0;
	Kp[2][3] = pression/6.0*Fr2*(-Xc+Xb)*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc2;
	Kp[2][4] = -pression/6.0*Fr2*(3.0*Zb*Xb*Xc-2.0*Zb*Fr*Xc+Fr*Zc*Xb-Zb*Fr*Xb)/Xb3/Xc;
	Kp[2][5] = 0.0;
	Kp[2][6] = pression/6.0*Fr2*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc;
	Kp[2][7] = pression/6.0*Fr2*(3.0*Zc*Xb*Xc-Fr*Zc*Xc-2.0*Fr*Zc*Xb+Zb*Fr*Xc)/Xb/Xc3;
	Kp[2][8] = 0.0;
	Kp[2][9] = -pression/6.0*Fr2*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb/Xc2;
	Kp[3][1] = -pression/6.0*Fr*(6.0*Xb3*Xc2*Yc-6.0*Xb3*Xc*Fr*Yc-6.0*Xb2*Xc3*Yb+6.0*Xb*Xc3*Yb*Fr-3.0*Fr*Xc2*Yc*Xb2+Fr2*Xc*Yc*Xb2-2.0*Fr2*Xc3*Yb+Fr2*Xc2*Yc*Xb+2.0*Fr2*Xb3*Yc+3.0*Fr*Xb2*Yb*Xc2-Fr2*Xb*Yb*Xc2-Fr2*Xb2*Yb*Xc)/Xb3/Xc3;
	Kp[3][2] = -pression/6.0*Fr2*(-Xc+Xb)*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc2;
	Kp[3][3] = 0.0;
	Kp[3][4] = pression/6.0*Fr2*(3.0*Yb*Xb*Xc-2.0*Yb*Fr*Xc+Fr*Yc*Xb-Yb*Fr*Xb)/Xb3/Xc;
	Kp[3][5] = -pression/6.0*Fr2*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb2/Xc;
	Kp[3][6] = 0.0;
	Kp[3][7] = -pression/6.0*Fr2*(3.0*Yc*Xb*Xc-Xc*Fr*Yc-2.0*Fr*Yc*Xb+Yb*Fr*Xc)/Xb/Xc3;
	Kp[3][8] = pression/6.0*Fr2*(3.0*Xb*Xc-Fr*Xc-Fr*Xb)/Xb/Xc2;
	Kp[3][9] = 0.0;
	Kp[4][1] = -pression/6.0*Fr2*(3.0*Yb*Zc*Xb*Xc-2.0*Yb*Fr*Zc*Xc-Yb*Fr*Zc*Xb-3.0*Zb*Yc*Xb*Xc+2.0*Zb*Fr*Yc*Xc+Zb*Fr*Yc*Xb)/Xb3/Xc2;
	Kp[4][2] = pression/6.0*Fr3*(-Zc+Zb)/Xb2/Xc;
	Kp[4][3] = -pression/6.0*Fr3*(Yb-Yc)/Xb2/Xc;
	Kp[4][4] = -pression/3.0*Fr3*(Yb*Zc-Zb*Yc)/Xb3/Xc;
	Kp[4][5] = pression/6.0*Fr3/Xb2*Zc/Xc;
	Kp[4][6] = -pression/6.0*Fr3/Xb2*Yc/Xc;
	Kp[4][7] = -pression/6.0*Fr3*(Yb*Zc-Zb*Yc)/Xb2/Xc2;
	Kp[4][8] = -pression/6.0*Zb*Fr3/Xb2/Xc;
	Kp[4][9] = pression/6.0*Yb*Fr3/Xb2/Xc;
	Kp[5][1] = pression/6.0*Fr2*(-3.0*Zb*Xb*Xc2+2.0*Zb*Fr*Xc2+3.0*Zc*Xb2*Xc-Fr*Zc*Xb2-Fr*Xc*Zc*Xb)/Xb3/Xc2;
	Kp[5][2] = 0.0;
	Kp[5][3] = pression/6.0*Fr3*(-Xc+Xb)/Xb2/Xc;
	Kp[5][4] = pression/6.0*Fr3*(-2.0*Zb*Xc+Zc*Xb)/Xb3/Xc;
	Kp[5][5] = 0.0;
	Kp[5][6] = pression/6.0*Fr3/Xb2;
	Kp[5][7] = pression/6.0*Fr3/Xb*Zc/Xc2;
	Kp[5][8] = 0.0;
	Kp[5][9] = -pression/6.0*Fr3/Xb/Xc;
	Kp[6][1] = -pression/6.0*Fr2*(3.0*Yc*Xb2*Xc-Fr*Yc*Xb2-3.0*Yb*Xb*Xc2+2.0*Yb*Fr*Xc2-Fr*Xc*Yc*Xb)/Xb3/Xc2;
	Kp[6][2] = -pression/6.0*Fr3*(-Xc+Xb)/Xb2/Xc;
	Kp[6][3] = 0.0;
	Kp[6][4] = -pression/6.0*Fr3*(-2.0*Yb*Xc+Yc*Xb)/Xb3/Xc;
	Kp[6][5] = -pression/6.0*Fr3/Xb2;
	Kp[6][6] = 0.0;
	Kp[6][7] = -pression/6.0*Fr3*Yc/Xc2/Xb;
	Kp[6][8] = pression/6.0*Fr3/Xb/Xc;
	Kp[6][9] = 0.0;
	Kp[7][1] = -pression/6.0*Fr2*(3.0*Yb*Zc*Xb*Xc-Yb*Fr*Zc*Xc-2.0*Yb*Fr*Zc*Xb-3.0*Zb*Yc*Xb*Xc+Zb*Fr*Yc*Xc+2.0*Zb*Fr*Yc*Xb)/Xb2/Xc3;
	Kp[7][2] = pression/6.0*Fr3*(-Zc+Zb)/Xb/Xc2;
	Kp[7][3] = -pression/6.0*Fr3*(Yb-Yc)/Xb/Xc2;
	Kp[7][4] = -pression/6.0*Fr3*(Yb*Zc-Zb*Yc)/Xb2/Xc2;
	Kp[7][5] = pression/6.0*Fr3/Xb*Zc/Xc2;
	Kp[7][6] = -pression/6.0*Fr3*Yc/Xc2/Xb;
	Kp[7][7] = -pression/3.0*Fr3*(Yb*Zc-Zb*Yc)/Xb/Xc3;
	Kp[7][8] = -pression/6.0*Zb*Fr3/Xb/Xc2;
	Kp[7][9] = pression/6.0*Yb*Fr3/Xb/Xc2;
	Kp[8][1] = pression/6.0*Fr2*(-3.0*Zb*Xb*Xc2+Zb*Fr*Xc2+3.0*Zc*Xb2*Xc-2.0*Fr*Zc*Xb2+Fr*Xb*Zb*Xc)/Xb2/Xc3;
	Kp[8][2] = 0.0;
	Kp[8][3] = pression/6.0*Fr3*(-Xc+Xb)/Xb/Xc2;
	Kp[8][4] = -pression/6.0*Zb*Fr3/Xb2/Xc;
	Kp[8][5] = 0.0;
	Kp[8][6] = pression/6.0*Fr3/Xb/Xc;
	Kp[8][7] = pression/6.0*Fr3*(2*Zc*Xb-Zb*Xc)/Xb/Xc3;
	Kp[8][8] = 0.0;
	Kp[8][9] = -pression/6.0*Fr3/Xc2;
	Kp[9][1] = -pression/6.0*Fr2*(3.0*Yc*Xb2*Xc-2.0*Fr*Yc*Xb2-3.0*Yb*Xb*Xc2+Yb*Fr*Xc2+Fr*Xb*Yb*Xc)/Xb2/Xc3;
	Kp[9][2] = -pression/6.0*Fr3*(-Xc+Xb)/Xb/Xc2;
	Kp[9][3] = 0.0;
	Kp[9][4] = pression/6.0*Yb*Fr3/Xb2/Xc;
	Kp[9][5] = -pression/6.0*Fr3/Xb/Xc;
	Kp[9][6] = 0.0;
	Kp[9][7] = -pression/6.0*Fr3*(2*Yc*Xb-Yb*Xc)/Xb/Xc3;
	Kp[9][8] = pression/6.0*Fr3/Xc2;
	Kp[9][9] = 0.0;
	}

void pression_totale(double AA[4], double BB[4], double CC[4], double pression, double *FA, double *FB, double *FC, double **Kr)
	{
	/*calcul des efforts de pressions sur un triangle de sommets AA,BB,CC
	les sommets AA BB et CC sont derriere le frontx
	les efforts sur les sommets sont placés dans FA, FB, FC et la raideur dans Kp*/
	
	/*efforts aux 3 sommets AA BB et CC*/
	FA[1] = - pression / 6.0*((BB[2]-AA[2])*(CC[3]-AA[3])-(BB[3]-AA[3])*(CC[2]-AA[2]));
	FA[2] = - pression / 6.0*((BB[3]-AA[3])*(CC[1]-AA[1])-(BB[1]-AA[1])*(CC[3]-AA[3]));
	FA[3] = - pression / 6.0*((BB[1]-AA[1])*(CC[2]-AA[2])-(BB[2]-AA[2])*(CC[1]-AA[1]));
	FB[1] = - pression / 6.0*((BB[2]-AA[2])*(CC[3]-AA[3])-(BB[3]-AA[3])*(CC[2]-AA[2]));
	FB[2] = - pression / 6.0*((BB[3]-AA[3])*(CC[1]-AA[1])-(BB[1]-AA[1])*(CC[3]-AA[3]));
	FB[3] = - pression / 6.0*((BB[1]-AA[1])*(CC[2]-AA[2])-(BB[2]-AA[2])*(CC[1]-AA[1]));
	FC[1] = - pression / 6.0*((BB[2]-AA[2])*(CC[3]-AA[3])-(BB[3]-AA[3])*(CC[2]-AA[2]));
	FC[2] = - pression / 6.0*((BB[3]-AA[3])*(CC[1]-AA[1])-(BB[1]-AA[1])*(CC[3]-AA[3]));
	FC[3] = - pression / 6.0*((BB[1]-AA[1])*(CC[2]-AA[2])-(BB[2]-AA[2])*(CC[1]-AA[1]));
	/* matrice raideur Kr*/
	Kr[1][1] = 0;	Kr[1][2] = pression/6.0*(BB[3]-CC[3]);	Kr[1][3] = pression/6.0*(CC[2]-BB[2]);	Kr[1][4] = 0;	Kr[1][5] = pression/6.0*(CC[3]-AA[3]);	Kr[1][6] = pression/6.0*(AA[2]-CC[2]);	Kr[1][7] = 0;	Kr[1][8] = pression/6.0*(AA[3]-BB[3]);	Kr[1][9] = pression/6.0*(BB[2]-AA[2]);
	Kr[2][1] = pression/6.0*(CC[3]-BB[3]);	Kr[2][2] = 0;	Kr[2][3] = pression/6.0*(BB[1]-CC[1]);	Kr[2][4] = pression/6.0*(AA[3]-CC[3]);	Kr[2][5] = 0;	Kr[2][6] = pression/6.0*(CC[1]-AA[1]);	Kr[2][7] = pression/6.0*(BB[3]-AA[3]);	Kr[2][8] = 0;	Kr[2][9] = pression/6.0*(AA[1]-BB[1]);
	Kr[3][1] = pression/6.0*(BB[2]-CC[2]);	Kr[3][2] = pression/6.0*(-BB[1]+CC[1]);	Kr[3][3] = 0;	Kr[3][4] = pression/6.0*(CC[2]-AA[2]);	Kr[3][5] = pression/6.0*(AA[1]-CC[1]);	Kr[3][6] = 0;	Kr[3][7] = pression/6.0*(AA[2]-BB[2]);	Kr[3][8] = pression/6.0*(BB[1]-AA[1]);	Kr[3][9] = 0;
	Kr[4][1] = 0;	Kr[4][2] = pression/6.0*(BB[3]-CC[3]);	Kr[4][3] = pression/6.0*(CC[2]-BB[2]);	Kr[4][4] = 0;	Kr[4][5] = pression/6.0*(CC[3]-AA[3]);	Kr[4][6] = pression/6.0*(AA[2]-CC[2]);	Kr[4][7] = 0;	Kr[4][8] = pression/6.0*(AA[3]-BB[3]);	Kr[4][9] = pression/6.0*(BB[2]-AA[2]);
	Kr[5][1] = pression/6.0*(CC[3]-BB[3]);	Kr[5][2] = 0;	Kr[5][3] = pression/6.0*(BB[1]-CC[1]);	Kr[5][4] = pression/6.0*(AA[3]-CC[3]);	Kr[5][5] = 0;	Kr[5][6] = pression/6.0*(CC[1]-AA[1]);	Kr[5][7] = pression/6.0*(BB[3]-AA[3]);	Kr[5][8] = 0;	Kr[5][9] = pression/6.0*(AA[1]-BB[1]);
	Kr[6][1] = pression/6.0*(BB[2]-CC[2]);	Kr[6][2] = pression/6.0*(-BB[1]+CC[1]);	Kr[6][3] = 0;	Kr[6][4] = pression/6.0*(CC[2]-AA[2]);	Kr[6][5] = pression/6.0*(AA[1]-CC[1]);	Kr[6][6] = 0;	Kr[6][7] = pression/6.0*(AA[2]-BB[2]);	Kr[6][8] = pression/6.0*(BB[1]-AA[1]);	Kr[6][9] = 0;
	Kr[7][1] = 0;	Kr[7][2] = pression/6.0*(BB[3]-CC[3]);	Kr[7][3] = pression/6.0*(CC[2]-BB[2]);	Kr[7][4] = 0;	Kr[7][5] = pression/6.0*(CC[3]-AA[3]);	Kr[7][6] = pression/6.0*(AA[2]-CC[2]);	Kr[7][7] = 0;	Kr[7][8] = pression/6.0*(AA[3]-BB[3]);	Kr[7][9] = pression/6.0*(BB[2]-AA[2]);
	Kr[8][1] = pression/6.0*(CC[3]-BB[3]);	Kr[8][2] = 0;	Kr[8][3] = pression/6.0*(BB[1]-CC[1]);	Kr[8][4] = pression/6.0*(AA[3]-CC[3]);	Kr[8][5] = 0;	Kr[8][6] = pression/6.0*(CC[1]-AA[1]);	Kr[8][7] = pression/6.0*(BB[3]-AA[3]);	Kr[8][8] = 0;	Kr[8][9] = pression/6.0*(AA[1]-BB[1]);
	Kr[9][1] = pression/6.0*(BB[2]-CC[2]);	Kr[9][2] = pression/6.0*(-BB[1]+CC[1]);	Kr[9][3] = 0;	Kr[9][4] = pression/6.0*(CC[2]-AA[2]);	Kr[9][5] = pression/6.0*(AA[1]-CC[1]);	Kr[9][6] = 0;	Kr[9][7] = pression/6.0*(AA[2]-BB[2]);	Kr[9][8] = pression/6.0*(BB[1]-AA[1]);	Kr[9][9] = 0;
	}

void pres_pris_elem2_hexa(int elem, double pression, double frontx)
	{
	/*Calcul des efforts de pression (wae) du poisson pour un element triangulaire
	  a maille hexagonale elem.*/
	  
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3,x12,y12,z12,x23,y23,z23,x31,y31,z31,surfacetriangle;
  	double yinter1,zinter1,yinter2,zinter2,surfacetriangleamont,surfacetriangleaval;
  	double angle3,angle2,force;
  	int zh,zi,zj;
	
	/*zh zi et zj sont les coordonnees x des 3 sommets du triangle de filet hexagonal*/
  	zh = yc_hexa(elem,1);  zi = yc_hexa(elem,4);  zj = yc_hexa(elem,7);
  	
  	/*coordonnees du triangle*/
  	XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
  	YY1 = wfcodend[zh+1];	YY2 = wfcodend[zi+1];	YY3 = wfcodend[zj+1];
  	ZZ1 = wfcodend[zh+2];	ZZ2 = wfcodend[zi+2];	ZZ3 = wfcodend[zj+2];

	if (Surf_Hexa[elem].tarp == 1)
  		{
		rotation4(zh, zi, zj, &angle3, &angle2);
		/*la normale au triangle est verticale ascendante*/
		/*printf("angle3 = %5.2lf ",angle3);	printf("angle2 = %5.2lf \n",angle2);*/
			  			
  		x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  		y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  		z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
		surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
		force = pression * surfacetriangle;
  		/*printf("force = %5.2lf \n",force);*/

   		/* Efforts aux 3 noeuds, sommets du triangle.*/
  		wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
  		wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
  		wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;
  		
    		/* Effort elementaire place dans l'espace*/
  		base1( -(angle2), 2, -(angle3),  3,  9, wae);
  		}
 
  	/*ne traiter que les surfaces a l arriere ou en partie a l arriere du front*/
  	/* surfaces totalement a l arriere  du front*/
  	if ((Surf_Hexa[elem].tarp == 0) && ((XX1 > frontx) || (XX2 > frontx) || (XX3 > frontx)))
  		{
		rotation4(zh, zi, zj, &angle3, &angle2);
		/*la normale au triangle est verticale ascendante*/
		/*printf("angle3 = %5.2lf ",angle3);	printf("angle2 = %5.2lf \n",angle2);*/
			  			
  		x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  		y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  		z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  			
  		/* surfaces totalement a l arriere  du front*/
  		if ((XX1 > frontx) && (XX2 > frontx) && (XX3 > frontx))
  			{
			surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
  			/*printf("s_totale = %5.2lf ",surfacetriangle);*/
  
  			/*force sur le triangle due a la pression sur la surface */
			force = pression * surfacetriangle;
  			/*printf("force = %5.2lf \n",force);*/

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;
   			}
  		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 > frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
  			yinter1 = YY1 + y12 / x12 * (frontx - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontx - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontx - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontx - XX1);
			surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
      				
  			/*force sur le triangle totale due a la pression sur la surface */
			force = pression * surfacetriangle;

   			/* Efforts  aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;

			surfacetriangleamont = surface_triangle2(XX1, YY1, ZZ1, frontx, yinter1, zinter1, frontx, yinter2, zinter2);
  			/*force sur le triangle amont due a la - pression sur la surface amont*/
			force = - pression * surfacetriangleamont;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] += - force + force / 3.0 * ((XX1-frontx)/(XX1-XX2)) + force / 3.0 * ((XX1-frontx)/(XX1-XX3));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] += - force / 3.0 * ((XX1-frontx)/(XX1-XX2));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] += - force / 3.0 * ((XX1-frontx)/(XX1-XX3));
    			}
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)*/
  			yinter1 = YY2 + y23 / x23 * (frontx - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontx - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontx - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontx - XX2);
			surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
     				
  			/*force sur le triangle totale due a la pression sur la surface */
			force = pression * surfacetriangle;

   			/* Efforts  aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;

			surfacetriangleamont = surface_triangle2(frontx, yinter2, zinter2, XX2, YY2, ZZ2, frontx, yinter1, zinter1);
  			/*force sur le triangle amont due a la - pression sur la surface amont*/
			force = - pression * surfacetriangleamont;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] += - force / 3.0 * ((XX2-frontx)/(XX2-XX1));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] += - force + force / 3.0 * ((XX2-frontx)/(XX2-XX1)) + force / 3.0 * ((XX2-frontx)/(XX2-XX3));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] += - force / 3.0 * ((XX2-frontx)/(XX2-XX3));
   			}
  		if ((XX1 > frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23)*/
  			yinter1 = YY3 + y31 / x31 * (frontx - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontx - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontx - XX3);
  			zinter2 = ZZ3 + z23 / x23 * (frontx - XX3);
			surfacetriangle = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
     				
  			/*force sur le triangle totale due a la pression sur la surface */
			force = pression * surfacetriangle;

   			/* Efforts  aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0;
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0;
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0;

			surfacetriangleamont = surface_triangle2(frontx, yinter1, zinter1, frontx, yinter2, zinter2, XX3, YY3, ZZ3);
  			/*force sur le triangle amont due a la - pression sur la surface amont*/
			force = - pression * surfacetriangleamont;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] += - force / 3.0 * ((XX3-frontx)/(XX3-XX1));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] += - force / 3.0 * ((XX3-frontx)/(XX3-XX2));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] += - force + force / 3.0 * ((XX3-frontx)/(XX3-XX1)) + force / 3.0 * ((XX3-frontx)/(XX3-XX2));
    			}
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 <= frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 1 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
  			yinter1 = YY1 + y12 / x12 * (frontx - XX1);
  			zinter1 = ZZ1 + z12 / x12 * (frontx - XX1);
  			yinter2 = YY1 + y31 / x31 * (frontx - XX1);
  			zinter2 = ZZ1 + z31 / x31 * (frontx - XX1);
			surfacetriangleaval = surface_triangle2(XX1, YY1, ZZ1, frontx, yinter1, zinter1, frontx, yinter2, zinter2);
    				
  			/*force sur le triangle due a la pression sur la surface */
			force = pression * surfacetriangleaval;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force + force / 3.0 * ((XX1-frontx)/(XX1-XX2)) + force / 3.0 * ((XX1-frontx)/(XX1-XX3));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0 * ((XX1-frontx)/(XX1-XX2));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0 * ((XX1-frontx)/(XX1-XX3));
    			}
  		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 2 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)*/
  			yinter1 = YY2 + y23 / x23 * (frontx - XX2);
  			zinter1 = ZZ2 + z23 / x23 * (frontx - XX2);
  			yinter2 = YY2 + y12 / x12 * (frontx - XX2);
  			zinter2 = ZZ2 + z12 / x12 * (frontx - XX2);
			surfacetriangleaval = surface_triangle2(frontx, yinter2, zinter2, XX2, YY2, ZZ2, frontx, yinter1, zinter1);
    				
  			/*force sur le triangle due a la pression sur la surface */
			force = pression * surfacetriangleaval;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0 * ((XX2-frontx)/(XX2-XX1));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force + force / 3.0 * ((XX2-frontx)/(XX2-XX1)) + force / 3.0 * ((XX2-frontx)/(XX2-XX3));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force / 3.0 * ((XX2-frontx)/(XX2-XX3));
    			}
  		if ((XX1 <= frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
  			/* surfaces partiellement a l arriere  du front : point 3 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23)*/
  			yinter1 = YY3 + y31 / x31 * (frontx - XX3);
  			zinter1 = ZZ3 + z31 / x31 * (frontx - XX3);
  			yinter2 = YY3 + y23 / x23 * (frontx - XX3);
  			zinter2 = ZZ3 + z23 / x23 * (frontx - XX3);
			surfacetriangleaval = surface_triangle2(frontx, yinter1, zinter1, frontx, yinter2, zinter2, XX3, YY3, ZZ3);
    				
  			/*force sur le triangle due a la pression sur la surface */
			force = pression * surfacetriangleaval;

   			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = 0.0;	wae[2] = 0.0;	wae[3] = - force / 3.0 * ((XX3-frontx)/(XX3-XX1));
  			wae[4] = 0.0;	wae[5] = 0.0;	wae[6] = - force / 3.0 * ((XX3-frontx)/(XX3-XX2));
  			wae[7] = 0.0;	wae[8] = 0.0;	wae[9] = - force + force / 3.0 * ((XX3-frontx)/(XX3-XX1)) + force / 3.0 * ((XX3-frontx)/(XX3-XX2));
    			}
    		/* Effort elementaire place dans l'espace*/
  		base1( -(angle2), 2, -(angle3),  3,  9, wae);
		}
	}
	
double pression_statique(int elem, double frontx)
	{
	/*renvoie une pression statique rho g h avec h distance au front
	a utiliser avec barry1.don comparer le resultat avec barry2 ou la pression est dynamique*/
	
  	double pression,XX1,XX2,XX3;
  	int zh,zi,zj;
  	
  	zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
	
  	XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
 
  	/*ne traiter que les surfaces a l arriere ou en partie a l arriere du front*/
  	/* surfaces totalement a l arriere  du front*/
  	if ((XX1 > frontx) || (XX2 > frontx) || (XX3 > frontx))
  		{
  		if ((XX1 >  frontx) && (XX2 >  frontx) && (XX3 >  frontx))	pression = RHO * G * ((XX1   +XX2   +XX3   )/3.0 - frontx);
  		if ((XX1 <= frontx) && (XX2 >  frontx) && (XX3 >  frontx))	pression = RHO * G * ((frontx+XX2   +XX3   )/3.0 - frontx);
  		if ((XX1 >  frontx) && (XX2 <= frontx) && (XX3 >  frontx))	pression = RHO * G * ((XX1   +frontx+XX3   )/3.0 - frontx);
  		if ((XX1 >  frontx) && (XX2 >  frontx) && (XX3 <= frontx))	pression = RHO * G * ((XX1   +XX2   +frontx)/3.0 - frontx);
  		if ((XX1 >  frontx) && (XX2 <= frontx) && (XX3 <= frontx))	pression = RHO * G * ((XX1   +frontx+frontx)/3.0 - frontx);
  		if ((XX1 <= frontx) && (XX2 >  frontx) && (XX3 <= frontx))	pression = RHO * G * ((frontx+XX2   +frontx)/3.0 - frontx);
  		if ((XX1 <= frontx) && (XX2 <= frontx) && (XX3 >  frontx))	pression = RHO * G * ((frontx+frontx+XX3   )/3.0 - frontx);
    		}
  	return pression;
	}

	
void pression_prise2(double frontx)
	{
	
  	/*
  	calcul des efforts de pression du poisson en aval de frontx
  	attention c est pas du tout affine : verifie les efforts aux 3 sommets, 
  	et calculer les efforts si un ou 2 sommets est en amont
  	du frontx
  	*/
  	double pression,modVV,ZZ1,vitesseM,directionM,VV[4];
  	int elem,zh,zi,zj,zl;
  	
  	
  	/*pression constante des poissons sur le cul de chalut*/
  	pression = Prise.cd * 0.5 * RHO * Courant.vitesse * Courant.vitesse ;

  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
		if (Prise.catch_gravity > 0.0) 
			{
		  	/*pression hydrostatique sur le cul de chalut*/
  			zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
		  	pression = G * Prise.catch_gravity * ((wfcodend[zh]+wfcodend[zi]+wfcodend[zj])/3.0 - frontx);
			/*printf("frontx %lf wf %lf %lf %lf pression %lf\n",frontx,wfcodend[zh],wfcodend[zi],wfcodend[zj],pression);*/
			}
		else
			{
		  	/*pression non constante des poissons sur le cul de chalut*/
			modVV = Courant.vitesse;
			if (Courant.nb_courant != 0)
				{
				// the pressure is calculated by triangle : not good see pression_prise3
				zh = yc(elem,1);	zi = yc(elem,4);	zj = yc(elem,7);
				ZZ1 = (wf[zh+2] + wf[zi+2] + wf[zj+2]) /3.0;			/*mean depth of the triangular element*/
				for (zl = 1 ;zl <= Courant.nb_courant ;zl++ )
					{
					if (((ZZ1-Courant.depth1[zl])*(ZZ1-Courant.depth2[zl])) <= 0.0)
						{
						vitesseM   = Courant.courant1[zl]   +(ZZ1-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.courant2[zl]  -Courant.courant1[zl]);
						directionM = Courant.direction1[zl] +(ZZ1-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.direction2[zl]-Courant.direction1[zl]);
						VV[1] = vitesseM*cos(directionM*PI/180.0) * panneau[Surface[elem].type].current_reduction;
						VV[2] = vitesseM*sin(directionM*PI/180.0) * panneau[Surface[elem].type].current_reduction;
						VV[3] = 0.0                               * panneau[Surface[elem].type].current_reduction;
						modVV = vitesseM;
						/*printf("Courant.nb_courant %d \n",Courant.nb_courant);
						printf("h mean %lf \n",ZZ1);
						printf("vitesseM %lf directionM %lf \n",vitesseM,directionM);*/
						}
					}
		
				}
		  	//pression = Prise.cd * 0.5 * RHO * Courant.vitesse * Courant.vitesse ;
		  	pression = Prise.cd * 0.5 * RHO * modVV * modVV ;
			}
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		/*pression = pression_statique( elem,  frontx);*/
    		for (zl = 1; zl<= 9; zl++) wae[zl] = 0.0;
  		zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  		pres_pris_elem2(elem, pression, frontx);
		/* Mise a jour du vecteur effort global*/
    		for (zl = 1; zl<= 9; zl++) wasurf[yc(elem,zl)] += wae[zl];
		Prise.drag = Prise.drag + wae[1] + wae[4] + wae[7];
  		} 

  	for (elem = 1; elem<= NOMBRE_SURF_HEXA; elem++)
  		{
  		/*numeros des coordonnees selon x des sommets du triangle*/
    		for (zl = 1; zl<= 9; zl++) wae[zl] = 0.0;
  		zh = yc_hexa(elem,1);  zi = yc_hexa(elem,4);  zj = yc_hexa(elem,7);
  		pres_pris_elem2_hexa(elem, pression, frontx);
		/* Mise a jour du vecteur effort global*/
    		for (zl = 1; zl<= 9; zl++) wasurf[yc_hexa(elem,zl)] += wae[zl];		
    		Prise.drag = Prise.drag + wae[1] + wae[4] + wae[7];
  		} 
  	}
		

void pression_prise3(double frontx,double front_height)
	{
	
  	/*
  	calcul des efforts de pression du poisson en aval de frontx
  	attention c est pas du tout affine : verifie les efforts aux 3 sommets, 
  	et calculer les efforts si un ou 2 sommets est en amont
  	du frontx
  	*/
  	double pression,modVV,vitesseM,directionM,VV[4];
  	int elem,zh,zi,zj,zl;
  	
  	
  	/*pression constante des poissons sur le cul de chalut*/
  	pression = Prise.cd * 0.5 * RHO * Courant.vitesse * Courant.vitesse ;

  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
		if (Prise.catch_gravity > 0.0) 
			{
		  	/*pression hydrostatique sur le cul de chalut*/
  			zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
		  	pression = G * Prise.catch_gravity * ((wfcodend[zh]+wfcodend[zi]+wfcodend[zj])/3.0 - frontx);
			/*printf("frontx %lf wf %lf %lf %lf pression %lf\n",frontx,wfcodend[zh],wfcodend[zi],wfcodend[zj],pression);*/
			}
		else
			{
		  	/*pression constante des poissons sur le cul de chalut*/
			modVV = Courant.vitesse;
			if (Courant.nb_courant != 0)
				{
				// the pressure is constant and calculated with the mean height of the cod-end
				for (zl = 1 ;zl <= Courant.nb_courant ;zl++ )
					{
					if (((front_height-Courant.depth1[zl])*(front_height-Courant.depth2[zl])) <= 0.0)
						{
						vitesseM   = Courant.courant1[zl]   +(front_height-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.courant2[zl]  -Courant.courant1[zl]);
						directionM = Courant.direction1[zl] +(front_height-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.direction2[zl]-Courant.direction1[zl]);
						VV[1] = vitesseM*cos(directionM*PI/180.0) * panneau[Surface[elem].type].current_reduction;
						VV[2] = vitesseM*sin(directionM*PI/180.0) * panneau[Surface[elem].type].current_reduction;
						VV[3] = 0.0                               * panneau[Surface[elem].type].current_reduction;
						modVV = vitesseM;
						/*printf("Courant.nb_courant %d ",Courant.nb_courant);
						printf("h mean %lf ",front_height);
						printf("vitesseM %lf directionM %lf \n",vitesseM,directionM);*/
						}
					}
		
				}
		  	//pression = Prise.cd * 0.5 * RHO * Courant.vitesse * Courant.vitesse ;
		  	pression = Prise.cd * 0.5 * RHO * modVV * modVV ;
			}
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		/*pression = pression_statique( elem,  frontx);*/
    		for (zl = 1; zl<= 9; zl++) wae[zl] = 0.0;
  		zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  		pres_pris_elem2(elem, pression, frontx);
		/* Mise a jour du vecteur effort global*/
    		for (zl = 1; zl<= 9; zl++) wasurf[yc(elem,zl)] += wae[zl];
		Prise.drag = Prise.drag + wae[1] + wae[4] + wae[7];
		//printf("elem %4d: ",elem);
		//imprvectreel1(9, 0, wae);
  		} 

  	for (elem = 1; elem<= NOMBRE_SURF_HEXA; elem++)
  		{
  		/*numeros des coordonnees selon x des sommets du triangle*/
    		for (zl = 1; zl<= 9; zl++) wae[zl] = 0.0;
  		zh = yc_hexa(elem,1);  zi = yc_hexa(elem,4);  zj = yc_hexa(elem,7);
  		pres_pris_elem2_hexa(elem, pression, frontx);
		/* Mise a jour du vecteur effort global*/
    		for (zl = 1; zl<= 9; zl++) wasurf[yc_hexa(elem,zl)] += wae[zl];		
    		Prise.drag = Prise.drag + wae[1] + wae[4] + wae[7];
  		} 
  	}
		

void mesh_front(int elem, double frontx, int *zn, double *nb)
	{
	/*Calcul de la position du front en nb de maille dans l element elem
	zn = 1 si le front coupe l element elem et nb et le nb de maille
	ou est le frony*/
	  
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3,x12,y12,z12,x23,y23,z23,x31,y31,z31,surfacetriangle;
  	double yinter1,zinter1,yinter2,zinter2,surfacetriangleamont,surfacetriangleaval;
  	double angle3,angle2,force,uv1,uv2,uv3,nb1,nb2;
  	int zh,zi,zj;
	
	/*zh zi et zj sont les coordonnees x des 3 sommets du triangle de filet losange*/
  	zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  	
  	/*coordonnees du triangle*/
  	XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
  	YY1 = wfcodend[zh+1];	YY2 = wfcodend[zi+1];	YY3 = wfcodend[zj+1];
  	ZZ1 = wfcodend[zh+2];	ZZ2 = wfcodend[zi+2];	ZZ3 = wfcodend[zj+2];
  	
	if (Prise.dir_mesh_front == 1)
		{
		uv1 =   Surface[elem].lon[1]; 
  		uv2 =   Surface[elem].lon[3]; 
  		uv3 =   Surface[elem].lon[5];
  		}
  	else
  		{
  		uv1 =   Surface[elem].lon[2];  
  		uv2 =   Surface[elem].lon[4];  
  		uv3 =   Surface[elem].lon[6];
  		}
  		
  	*zn = 0;
  	*nb = 0.0;
  		

  	/*ne traiter que les surfaces a l arriere ou en partie a l arriere du front*/
  	/* surfaces totalement a l arriere  du front*/
  	if ((Surface[elem].tarp == 0) && ((XX1 > frontx) || (XX2 > frontx) || (XX3 > frontx)))
  		{
		rotation4(zh, zi, zj, &angle3, &angle2);
		/*la normale au triangle est verticale ascendante*/
		/*printf("angle3 = %5.2lf ",angle3);	printf("angle2 = %5.2lf \n",angle2);*/
			  			
  		x12 = XX2 - XX1;x23 = XX3 - XX2;x31 = XX1 - XX3;
  		y12 = YY2 - YY1;y23 = YY3 - YY2;y31 = YY1 - YY3;
  		z12 = ZZ2 - ZZ1;z23 = ZZ3 - ZZ2;z31 = ZZ1 - ZZ3;
  			
  		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 > frontx))
  			{
  			*zn = 1;
  			/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
  			nb1 = uv1 + (uv2-uv1) / (XX2 - XX1) * (frontx - XX1);
  			nb2 = uv1 + (uv3-uv1) / (XX3 - XX1) * (frontx - XX1);
  			*nb = (nb1 + nb2) / 2.0;
 			/*printf("elem %5d zn %5d nb1 %10.2lf nb2 %10.2lf nb %10.2lf \n",elem,*zn,nb1,nb2,*nb);
 			exit(0);*/
    			}
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
  			*zn = 1;
  			/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)*/
  			nb1 = uv2 + (uv1-uv2) / (XX1 - XX2) * (frontx - XX2);
  			nb2 = uv2 + (uv3-uv2) / (XX3 - XX2) * (frontx - XX2);
  			*nb = (nb1 + nb2) / 2.0;
   			}
  		if ((XX1 > frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
  			*zn = 1;
  			/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23)*/
  			nb1 = uv3 + (uv1-uv3) / (XX1 - XX3) * (frontx - XX3);
  			nb2 = uv3 + (uv2-uv3) / (XX2 - XX3) * (frontx - XX3);
  			*nb = (nb1 + nb2) / 2.0;
    			}
  		if ((XX1 > frontx) && (XX2 <= frontx) && (XX3 <= frontx))
  			{
  			*zn = 1;
  			/* surfaces partiellement a l arriere  du front : point 1 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)*/
  			nb1 = uv1 + (uv2-uv1) / (XX2 - XX1) * (frontx - XX1);
  			nb2 = uv1 + (uv3-uv1) / (XX3 - XX1) * (frontx - XX1);
  			*nb = (nb1 + nb2) / 2.0;
    			}
  		if ((XX1 <= frontx) && (XX2 > frontx) && (XX3 <= frontx))
  			{
  			*zn = 1;
  			/* surfaces partiellement a l arriere  du front : point 2 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)*/
  			nb1 = uv2 + (uv1-uv2) / (XX1 - XX2) * (frontx - XX2);
  			nb2 = uv2 + (uv3-uv2) / (XX3 - XX2) * (frontx - XX2);
  			*nb = (nb1 + nb2) / 2.0;
    			}
  		if ((XX1 <= frontx) && (XX2 <= frontx) && (XX3 > frontx))
  			{
  			*zn = 1;
  			/* surfaces partiellement a l arriere  du front : point 3 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23)*/
  			nb1 = uv3 + (uv1-uv3) / (XX1 - XX3) * (frontx - XX3);
  			nb2 = uv3 + (uv2-uv3) / (XX2 - XX3) * (frontx - XX3);
  			*nb = (nb1 + nb2) / 2.0;
    			}
		}
	}

void nb_mesh_front(double frontx)
	{
	
  	/*
  	calculation of the position of the front in nb of meshes
  	*/
  	double nb_total,nb;
  	int elem,l,zn_total,zn;
  	
  	if (Prise.dir_mesh_front > 0)
  		{
  		nb_total = 0.0;
	  	zn_total = 0;
  		for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  			{
  			zn = 0;
  			/*renvoie la position du front en nb de mailles*/
  			mesh_front(elem, frontx,&zn,&nb);
  			if (zn > 0)
  				{
  				zn_total = zn_total + zn;
  				nb_total = nb_total + nb;
 				/*printf("elem %5d zn %5d zn_total %5d nb %10.2lf nb_total %10.2lf \n",elem,zn,zn_total,nb,nb_total);*/
  				}
  			}
  		Prise.nb_mesh_front = nb_total / zn_total;
 		printf("zn_total %5d Prise.nb_mesh_front %10.2lf \n",zn_total,Prise.nb_mesh_front);
  		} 
    	}
		

void catch_hexa()
	{
  	/*Mise a jour du vecteur effort wasurf .
     	Les efforts (wae) calcules ici sont dus a la pression interne 
     	au triangles de filet due a la
     	vitesse du courant, 
     	ainsi que la matrice de raideur (we) .*/
   
  	double minx,maxx,surfacefr,volumefr,front_height;

	changement_variable_catch();			//x_codend : coordinates along the current or gravity
  	extrema_direction_courant(&minx,&maxx);	//obtention of minx and maxx the extremas of the netting along the x_codend
	/*printf("minx  = %11.5lf ",minx);
	printf("maxx  = %11.5lf \n",maxx);*/

	/*definir le front de la prise dans la direction du courant or gravity*/	
	//surface_volume( minx,  &surfacefr, &volumefr);	
	surface_volume2( minx,  &surfacefr, &volumefr, &front_height);	
	/*front surface and volume between front netting bottom using front position : minx, and mean height of the front*/
  	if (volumefr < Prise.volume - Prise.seuil)
  		{
  		Prise.front = minx;
  		}
  	else
  		{
  		if ((Prise.front >= maxx) || (Prise.front <= minx))
			{
			Prise.front = (minx + maxx) / 2.0;
			}
		Prise.front = nouveau_front2(Prise.front, minx,	maxx); 
		/*front position such volumefr = Prise.volume +- Prise.seuil*/
  		}
	//printf("Prise.front  = %11.8lf ",Prise.front);
	/*************************************************************************************************************/
	//Prise.front  = 333.36881410;
	/*Prise.front = maxx - 0.89;*/
	/*************************************************************************************************************/
	
  	/*calcul des efforts de pression du poisson en aval de Prise.front*/
	//pression_prise2(Prise.front);
	pression_prise3(Prise.front,front_height);  
	/*calculation of forces du to pressure of fish behind Prise.front. The pressure is calculated with current and if current is not
	uniform on height the mean height of the front is used (front_height)*/
	Prise.diametre = 2.0 * rayon_maxi();
	Prise.epaisseur = maxx-Prise.front;
	surface_volume( Prise.front,  &surfacefr, &Prise.volume_effectif);
	/*calcul de la surface du front et du volume entre le front et le fond du filet 
  	connaissant la position du front : frontx*/

	//printf("front_height  = %9.3lf ",front_height);
	//printf("Prise front = %9.3lf ",Prise.front);
	//printf("volume_effectif  = %9.3lf ",Prise.volume_effectif);
	//printf("diametre  = %9.3lf ",Prise.diametre);
	//printf("epaisseur  = %9.3lf ",Prise.epaisseur);
	//exit(0);
	}
