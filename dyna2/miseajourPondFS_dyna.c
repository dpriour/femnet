#define PRINCIPAL 0
#include "4c19.h"
static int ifdstk = 1;

//Pond: ponderation of drag force on extremities of the bar if these extremities are close to the free surface
//proportion of the cube inside water (>=0.0 and <=1.0)
//0.0 if not in the water
//1.0 if fully in water

void miseajourPondFS_dyna()
	{
  	int zi,zj;
  	double zz,zzh;

  	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
  		{
    		//calculation of pondFS in dynamic case
  		for (zj = 1 ; zj<= 2; zj++) 
  			{
	 		zz = wf[yb(zi,3*zj)];
	 		zzh = mh[yb(zi,3*zj)];
			if (zz-Element[zi].lcube/2.0> zzh)					  	
				{
				Element[zi].pondFS[zj] = 0.0;							
				//Pond : ponderation of drag force on extremity 1 of the bar if this extremity is close to the free surface
				}
			if((zz-Element[zi].lcube/2.0<=zzh) && (zz+Element[zi].lcube/2.0>=zzh))	
				{
				Element[zi].pondFS[zj] = (zzh-zz+Element[zi].lcube/2.0)/Element[zi].lcube;
				}
			if                                    (zz+Element[zi].lcube/2.0< zzh)		
				{
				Element[zi].pondFS[zj] = 1.0;
				}
			/*if (zi == 9)
				{
				printf("zi %4d zz %7.3lf mh %7.3lf lcube  %7.3lf pondFS %7.3lf \n",zi,zz,mh[yb(zi,3*zj)],Element[zi].lcube,Element[zi].pondFS[zj]);	
				}*/
 			}		
 		}

  	for (zi = 1 ; zi<= NOMBRE_SURFACES; zi++) 
  		{
    		//calculation of pondFS in dynamic case
  		for (zj = 1 ; zj<= 3; zj++) 
  			{
	 		zz = wf[yc(zi,3*zj)];
	 		zzh = mh[yb(zi,3*zj)];
			if (zz-Surface[zi].lcube/2.0> zzh)					  	Surface[zi].pondFS[zj] = 0.0;							//Pond : ponderation of drag force on extremity 1 of the bar if this extremity is close to the free surface
			if((zz-Surface[zi].lcube/2.0<=zzh) && (zz+Surface[zi].lcube/2.0>=zzh))	  	Surface[zi].pondFS[zj] = (zzh-zz+Surface[zi].lcube/2.0)/Surface[zi].lcube;
			if                                    (zz+Surface[zi].lcube/2.0< zzh)		Surface[zi].pondFS[zj] = 1.0;
			//printf("zi %4d zz %7.3lf mh %7.3lf lcube  %7.3lf pondFS %7.3lf \n",zi,zz,mh[yb(zi,3*zj)],Surface[zi].lcube,Surface[zi].pondFS[zj]);	
 			}		
 		}

	//exit(0);
	}

