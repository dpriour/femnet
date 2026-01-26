#define PRINCIPAL 0
#include "4c19.h"

double mouvementmax()
	{
	/*calcul du deplacement maximal de toutes les coordonnees des noeuds*/
  	int zi,zj;
  	double R;

  	R = 0.0;
  	for (zi = 1; zi<= 3*NOMBRE_NOEUDS; zi++)
    		{ 
    		if (fabs(wv[zi]) > fabs(R)) 
    			{ 
      			R = wv[zi]; 
  			zj = zi;
    			}
    		}
    	/*if (nbiter > 1)
    		{
    		printf("zj mouvmax = %5d \n",zj);
    		}*/
  	return R;
	}


