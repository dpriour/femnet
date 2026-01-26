#include "4c19.h"

void inertie_noeud()
	{
  	/* 
  	effort et raideur d inertie sur chaque noeud : selon Gilbert, 
  	modifie le 5/8/96 pour que les efforts Ma(gammah - gamma) soient continus entre le flottant et l exonde 
  	grace au parametre sans dimension immer qui tend vers 0 lorsque immersion tend vers 0
  	effort = Ma(gammah - gamma) + rho V gammah - M gamma
  	raideur = + (M + Ma) / delt^2 
  	
  	ATTENTION la raideur liee a la variation de volume dans les cas flottant n est pas pris en compte
  	*/

  	int zi;
  	double immersion,volume,immer;

  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  		{
    		if (Noeud[zi].lonz >= 0.0)
    			{
      			/* flotteur  */
      			if (wf[3*zi] > mh[3*zi])
      				{
        			/*  exonde */
        			immersion = 0.0;
      				}
      			if ((wf[3*zi] <= mh[3*zi]) && (wf[3*zi] + Noeud[zi].lonz >= mh[3*zi]))
      				{
        			/*  flottant */
        			immersion = mh[3*zi] - wf[3*zi];
      				}
      			if (wf[3*zi] + Noeud[zi].lonz < mh[3*zi])
      				{
        			/*  inonde */
        			immersion = Noeud[zi].lonz;
      				}
    			}
    		if (Noeud[zi].lonz < 0.0) 
    			{
        		/* lest  */
      			if (wf[3*zi] + Noeud[zi].lonz > mh[3*zi])
      				{
        			/*  exonde */
        			immersion = 0.0;
      				}
      			if ((wf[3*zi] >= mh[3*zi]) && (wf[3*zi] + Noeud[zi].lonz <= mh[3*zi]))
      				{
        			/*  flottant */
        			immersion = - Noeud[zi].lonz - wf[3*zi] + mh[3*zi];
      				}
      			if (wf[3*zi] < mh[3*zi])
      				{
        			/*  inonde */
        			immersion = - Noeud[zi].lonz;
      				}
    			}
    		volume = immersion * Noeud[zi].lonx * Noeud[zi].lony;
    		if (Noeud[zi].lonz != 0.0) immer = pow((fabs(immersion/Noeud[zi].lonz)),0.4); else immer = 1.0;
    		wanoeud[3*zi-2] += Noeud[zi].majx * immer * (mgh[3*zi-2] - mgb[3*zi-2]) + RHO * volume * mgh[3*zi-2] - Noeud[zi].mx * mgb[3*zi-2];
    		wanoeud[3*zi-1] += Noeud[zi].majy * immer * (mgh[3*zi-1] - mgb[3*zi-1]) + RHO * volume * mgh[3*zi-1] - Noeud[zi].my * mgb[3*zi-1];
    		wanoeud[3*zi-0] += Noeud[zi].majz * immer * (mgh[3*zi-0] - mgb[3*zi-0]) + RHO * volume * mgh[3*zi-0] - Noeud[zi].mz * mgb[3*zi-0];



    		if (Structure.type_solver == 1)
		{
    			ze[3*zi-2][eca] += (Noeud[zi].majx * immer + Noeud[zi].mx) / Pascalcul / Pascalcul;
    			ze[3*zi-1][eca] += (Noeud[zi].majy * immer + Noeud[zi].my) / Pascalcul / Pascalcul;
    			ze[3*zi-0][eca] += (Noeud[zi].majz * immer + Noeud[zi].mz) / Pascalcul / Pascalcul;
	  	}
		else if (Structure.type_solver == 2)
		{
			//affectation_pardiso( (Noeud[zi].majx * immer + Noeud[zi].mx) / Pascalcul / Pascalcul, 3*zi-2, 3*zi-2);
			//affectation_pardiso( (Noeud[zi].majy * immer + Noeud[zi].my) / Pascalcul / Pascalcul, 3*zi-1, 3*zi-1);
			//affectation_pardiso( (Noeud[zi].majz * immer + Noeud[zi].mz) / Pascalcul / Pascalcul, 3*zi, 3*zi);
		}
    		/*printf("volume %lf immer %lf wanoeud = %lf %lf %lf \n",volume,immer,wanoeud[3*zi-2],wanoeud[3*zi-1],wanoeud[3*zi-0]);
    		printf("RHO %lf immer %lf mgb = %lf %lf %lf \n",RHO,immer,mgb[3*zi-2],mgb[3*zi-1],mgb[3*zi-0]);
    		printf("volume %lf immer %lf mgh = %lf %lf %lf \n",volume,immer,mgh[3*zi-2],mgh[3*zi-1],mgh[3*zi-0]);*/
  		}
	}
