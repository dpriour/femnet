#define PRINCIPAL 0
#include "4c19.h"

double effortsum()
	{
	/* Calcul de l effort moyen sur toutes les coordonnees des noeuds*/
  	int zi;
  	double R;

  	R = 0.0;
  	for (zi = 1; zi<= 3*NOMBRE_NOEUDS; zi++)
  		{
    		R += fabs(wa[zi]);
  		}
  	R = R / 3.0 / (double) NOMBRE_NOEUDS;

  	return R;
	}


