#define PRINCIPAL 0
#include "4c19.h"

void initialisation_pondFS()
	{
	//calculation of lcube for elements and triangles
  	int zi;
  	double zz;
 
  	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
  		{
    		//calculation of lcube in static case
		Element[zi].lcube = pow((Element[zi].lgrepos*PI*pow(Element[zi].diametrehydro,2)/8.0),(1.0/3.0));		//size of the cubique volume per node
 		}

  	for (zi = 1 ; zi<= NOMBRE_SURFACES; zi++) 
  		{
    		//calculation of lcube in static case
		Surface[zi].lcube = pow((Surface[zi].lgrepos*PI*pow(Surface[zi].diametrehydro,2)/6.0*Surface[zi].nb_cote_u_ou_v),(1.0/3.0));		//size of the cubique volume per node
 		}
	}

