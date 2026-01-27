#define PRINCIPAL 0
#include "4c19.h"
static int ifdstk = 1;

void miseajourPondFS()
	{
  	int zi,zj;
  	double zz;
		
  	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
  		{
    		//calculation of pondFS in static case. pondFS is between 0 and 1, 0 if not in water, 1 full in water
  		for (zj = 1 ; zj<= 2; zj++) 
  			{
	 		zz = wf[yb(zi,3*zj)];
			if (zz-Element[zi].lcube/2.0> 0.0)					  	Element[zi].pondFS[zj] = 0.0;							//Pond : ponderation of drag force on extremity 1 of the bar if this extremity is close to the free surface
			if((zz-Element[zi].lcube/2.0<=0.0) && (zz+Element[zi].lcube/2.0>=0.0))
				{
				if (Element[zi].lcube!= 0.0)
					{
					Element[zi].pondFS[zj] = (0.0-zz+Element[zi].lcube/2.0)/Element[zi].lcube;
					}
				else
					{
					Element[zi].pondFS[zj] = 1.0;
					}
				}
			if                                    (zz+Element[zi].lcube/2.0< 0.0)		Element[zi].pondFS[zj] = 1.0;
 			}		
 		}

  	for (zi = 1 ; zi<= NOMBRE_SURFACES; zi++) 
  		{
    		//calculation of pondFS in static case
  		for (zj = 1 ; zj<= 3; zj++) 
  			{
	 		zz = wf[yc(zi,3*zj)];
			if (zz-Surface[zi].lcube/2.0> 0.0)					  	Surface[zi].pondFS[zj] = 0.0;							//Pond : ponderation of drag force on extremity 1 of the bar if this extremity is close to the free surface
			if((zz-Surface[zi].lcube/2.0<=0.0) && (zz+Surface[zi].lcube/2.0>=0.0))	  	Surface[zi].pondFS[zj] = (0.0-zz+Surface[zi].lcube/2.0)/Surface[zi].lcube;
			if                                    (zz+Surface[zi].lcube/2.0< 0.0)		Surface[zi].pondFS[zj] = 1.0;
			//printf("zi %4d zz %7.3lf lcube  %7.3lf pondFS %7.3lf \n",zi,zz,Surface[zi].lcube,Surface[zi].pondFS[zj]);	
 			}		
 		}
	//exit(0);
	}

