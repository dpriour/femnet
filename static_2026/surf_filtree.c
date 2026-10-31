#define PRINCIPAL 0
#include "4c19.h"

double surf_filtree()
	{
  	/* 
  	calcul de la surface filtree par le filet
     	*/
   
  	double minx,maxx;
  	double volumefront,surfacefront;
  	
	changement_variable_catch();
  	extrema_direction_courant(&minx,&maxx);
  	surface_volume(minx, &surfacefront, &volumefront);
  	
  	/*
  	printf("surfacefront      (m2) : %12.2lf \n", surfacefront);
  	printf("volumefront       (m3) : %12.2lf \n", volumefront);
  	printf("minx               (m) : %12.2lf \n", minx);
  	printf("maxx               (m) : %12.2lf \n", maxx);
  	*/
  	
	return surfacefront;
	}

double surf_filtree_direction(int direction)
	{
  	/* 
  	calcul de la surface filtree par le filet calcule dans la direction
	selon x si direction = 1
	selon y si direction = 2
	selon z si direction = 3
	selon le courant si direction = 0
     	*/
   
  	double minx,maxx;
  	double volumefront,surfacefront;
  	
	changement_variable(direction);
  	surface_volume(0.0, &surfacefront, &volumefront);
  		
  	printf("surfacefront      (m2) : %12.2lf \n", surfacefront);
  	printf("volumefront       (m3) : %12.2lf \n", volumefront);
  		
	return surfacefront;
	}

