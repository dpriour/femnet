#define PRINCIPAL 0
#include "4c19.h"

void extrema_direction_courant_catch2_volume(double *minx,double *maxx, int nc)
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
    	while (Surface[elem].type != Catch2_volume[nc].panel_catch2[1]) ;
    	
	/*printf("nc = %d   \n",nc);
	printf("Surface[%d].type = %d   \n",elem,Surface[elem].type);
	printf("Catch2_volume[%d].panel_catch2[1] = %d   \n",nc,Catch2_volume[nc].panel_catch2[1]);*/
	zh = yc(elem,1);
 	*minx = wfcodend[zh];
	*maxx = wfcodend[zh];
	
  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
		appartient = 0;
  		for (pa = 1; pa<= Catch2_volume[nc].nb_panel_catch2; pa++)
  			{
  			pan = Catch2_volume[nc].panel_catch2[pa];
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
  				if (*minx > XX1) *minx = XX1;
  				if (*maxx < XX1) *maxx = XX1;
  				}
  			}
  		}
	}
	
void surface_volume_catch2_volume(double frontx, double *surfacefront,double *volumefront, int nc)
  	{

  	/*calcul de la surface du front et du volume entre le front et le fond du filet 
  	connaissant la position du front : frontx pour le catch2_volume numero nc*/
  	
  	int elem,zh,zi,zj,appartient,pa,pan;
  	
	*volumefront = 0.0;
	*surfacefront = 0.0;
	nb_pt_aval = 0;
	
	/*printf("volumefront = %5.2lf ",*volumefront);
	printf("surfacefront = %5.2lf \n",*surfacefront);*/

  	for (elem = 1; elem <= NOMBRE_SURFACES; elem++)
  		{
		appartient = 0;
  		for (pa = 1; pa<= Catch2_volume[nc].nb_panel_catch2; pa++)
  			{
  			pan = Catch2_volume[nc].panel_catch2[pa];
  			if (Surface[elem].type == pan)	appartient = 1;
  			}
  			
  		if (appartient == 1)
  			{
  			/*numeros des coordonnees selon x des sommets du triangle*/
  			zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  			surf_vol_elem(zh, zi, zj, frontx, surfacefront, volumefront);
			/*printf("elem = %4d surfacefront = %11.5lf  volumefront = %11.5lf\n",elem,*surfacefront,*volumefront);*/
			}
		}
  	}
  	
  	
double nouveau_front2_catch2_volume(double frx, double mix, double max, int nc)
	{
	/*renvoie la position du front tel que volumefr soit = Catch2_volume[nc].volume +- Prise.seuil*/
	double infx, supx, surfacefr, volumefr;
	int compteur;
	
  	surface_volume_catch2_volume( frx,  &surfacefr, &volumefr, nc);
  	
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
		if(volumefr > Catch2_volume[nc].volume + Prise.seuil) 	infx = frx;
		if(volumefr < Catch2_volume[nc].volume - Prise.seuil) 	supx = frx;
		frx = (infx + supx) / 2.0;
		
  		surface_volume_catch2_volume( frx,  &surfacefr, &volumefr, nc);
  		
		if ( (frx <= mix) && (volumefr < Catch2_volume[nc].volume - Prise.seuil) ) 
			{
		 	frx = mix;
			}
		if ( (frx >= max) && (volumefr > Catch2_volume[nc].volume + Prise.seuil) ) 
			{
		 	frx = max;
			}
		/*printf(" compteur  = %4d ",compteur);
		printf(" surfacefr  = %11.5lf ",surfacefr);
		printf(" volumefr   = %11.5lf ",volumefr);
		printf(" infx  = %11.5lf ",infx);
		printf(" frx   = %11.5lf ",frx);
		printf(" supx  = %11.5lf \n",supx);*/
		}
	while((fabs(volumefr-Catch2_volume[nc].volume) >= Prise.seuil) && (frx > mix) && (frx < max) && (compteur < 100));
	if (compteur == 100 ) frx = max;
	return frx;
	}
	
void pression_prise2_catch2_volume(double frontx,int nc)
	{
	
  	/*
  	calcul des efforts de pression du poisson en aval de frontx
  	attention c est pas du tout affine : verifie les efforts aux 3 sommets, 
  	et calculer les efforts si un ou 2 sommets est en amont
  	du frontx
  	*/
  	double pression;
  	int elem,zh,zi,zj,zl,pa,pan,appartient;
  	
  	
  	/*pression constante des poissons sur le cul de chalut*/
  	pression = Prise.cd * 0.5 * RHO * Courant.vitesse * Courant.vitesse ;

  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
		appartient = 0;
  		for (pa = 1; pa<= Catch2_volume[nc].nb_panel_catch2; pa++)
  			{
  			pan = Catch2_volume[nc].panel_catch2[pa];
  			if (Surface[elem].type == pan)	appartient = 1;
  			}
  			
  		if (appartient == 1)
  			{
  			/*numeros des coordonnees selon x des sommets du triangle*/
  			/*pression = pression_statique( elem,  frontx);*/
    			for (zl = 1; zl<= 9; zl++) wae[zl] = 0.0;
  			zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  			pres_pris_elem3(elem, pression, frontx);
    			}
  		} 
  	}
		

void catch2_volume()
	{
	int nc,pa,elem;
  	double minx,maxx,surfacefr,volumefr;
	
	/*changement_variable_catch();*/
  	for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
  		{
  		wfcodend[3*elem-2] = wf[3*elem-2];
  		wfcodend[3*elem-1] = wf[3*elem-1];
  		wfcodend[3*elem-0] = wf[3*elem-0];
		}
	
  	for (nc = 1; nc<= Structure.nb_catch2_volume; nc++)
  		{
		/*printf("nc = %d   \n",nc);*/
  		extrema_direction_courant_catch2_volume(&minx,&maxx,nc);
		/*printf("minx  = %11.5lf ",minx);
		printf("maxx  = %11.5lf \n",maxx);
		printf("Catch2_volume Structure.nb_catch2_volume = %d  ",Structure.nb_catch2_volume);
		printf("Volumea %lf  ",Catch2_volume[nc].volume);
		printf("nb panels %d  ",Catch2_volume[nc].nb_panel_catch2);
		printf("panels :");
		for (pa=1;pa<=Catch2_volume[nc].nb_panel_catch2;pa++)
			{
			printf(" %d",Catch2_volume[nc].panel_catch2[pa]);
			}
		printf("\n");*/
		
		/*definir le front de la prise dans la direction du courant*/
		surface_volume_catch2_volume( minx,  &surfacefr, &volumefr, nc);	
		/*printf("volumefr  = %11.5lf ",volumefr);
		printf("Volumeb %lf  \n",Catch2_volume[nc].volume);*/
  		if (volumefr < Catch2_volume[nc].volume - Prise.seuil)
  			{
  			/*ici le volume est trop faible donc le front = minx*/
  			Catch2_volume[nc].front = minx;
			/*printf("Volumec %lf  \n",Catch2_volume[nc].volume);*/
  			}
  		else
  			{
  			if ((Catch2_volume[nc].front >= maxx) || (Catch2_volume[nc].front <= minx))
				{
				Catch2_volume[nc].front = (minx + maxx) / 2.0;
				}
			Catch2_volume[nc].front = nouveau_front2_catch2_volume(Catch2_volume[nc].front, minx,	maxx, nc);
			/*printf("Volumed %lf  \n",Catch2_volume[nc].volume);*/
  			}
  		/*calcul des efforts de pression du poisson en aval de Catch2_volume[nc].front*/
		printf("front  = %11.5lf ",Catch2_volume[nc].front);
		printf("volumefr  = %11.5lf ",volumefr);
		printf("Volumee  = %11.5lf \n",Catch2_volume[nc].volume);/**/
		pression_prise2_catch2_volume(Catch2_volume[nc].front,nc);
  		}
	}
