#define PRINCIPAL 0
#include "4c19.h"

double effortmax()
	{
	/*calcul de l'effort maximal de toutes les coordonnees*/
  	int zi,zj;
  	double R;

  	zj = 1;
  	R = 0.0;
  	for (zi = 1; zi<= 3*NOMBRE_NOEUDS; zi++)
  		{
    		if (fabs(wa[zi])>fabs(R)) 
    			{ 
      			R = wa[zi]; 
  			zj = zi;
    			}
    		}
    	
     	//printf("zj %5d effortmax %lf   ",zj,R);
   	/*if (nbiter > 144)
    		{
    		printf("zj %5d effortmax %lf   ",zj,R);
    		}
    	*/
  	return R;
	}


