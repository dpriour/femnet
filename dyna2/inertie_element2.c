#include "4c19.h"

void inertie_element2()
	{
  	/* 
  	effort et raideur d inertie sur chaque element
  	effort = Ma(gammah - gamma) + rho V gammah - M gamma
  	Ma = K rho V 
  	avec K = 1 dans le cas de cylindres
  	raideur = + (M + Ma) / delt^2 
  	
  	ATTENTION la repartition des masses et du volume n est pas correctement faite dans le cas du flottant
  	de meme la raideur liee a la variation de volume V dans les cas fottant n est pas pris en compte
  	
  	on tient compte ici de l'imersion liée à la houle
  	*/

  	int zi,no1,no2,no3,no4,no5,no6;
  	double immersion,volume,immer,f,lmouillee,dx,dy,dz,d1,d2,d3,d4,d5,d6,C,M,Ma,V,Ma1,Ma2,V1,V2;
  	double lonx,lony,lonz;

   	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
	{
    		no1 = yb(zi,1); 	/*numero de la coordonnee selon x de l extremite  1 de l element*/
    		no2 = yb(zi,2); 	/*numero de la coordonnee selon y de l extremite  1 de l element*/
    		no3 = yb(zi,3); 	/*numero de la coordonnee selon z de l extremite  1 de l element*/
    		no4 = yb(zi,4); 	/*numero de la coordonnee selon x de l extremite  2 de l element*/
    		no5 = yb(zi,5); 	/*numero de la coordonnee selon y de l extremite  2 de l element*/
    		no6 = yb(zi,6); 	/*numero de la coordonnee selon z de l extremite  2 de l element*/

		V = Element[zi].lgrepos * PI * Element[zi].diametrehydro * Element[zi].diametrehydro / 4.0 / 2.0;	//1/2 volume de l element a chaque extremite				
      		//M = V * Element[zi].rhoelement; 									//1/2 masse  de l element a chaque extremite				  		
 		M = Element[zi].mass/2.0;
      		
		lonx = pow(V,1.0/3.0);	//cote selon x du cube de volume V
		lony = lonx; 		//cote selon y du cube de volume V
		lonz = V/(lonx*lonx);	//cote selon z du cube de volume V
      		
		// flotteur exonde extremite 1 & 2
		if (wf[no3] - lonz/2.0 > mh[no3])					V1 = 0.0;	//volume inonde extremite 1
		if (wf[no6] - lonz/2.0 > mh[no6])					V2 = 0.0;	//volume inonde extremite 2
		// flotteur flottant extremite 1 & 2
		if ((wf[no3] - lonz/2.0 <= mh[no3]) && (wf[no3] + lonz/2.0 >= mh[no3]))	V1 = fabs(lonx * lony * (mh[no3] - wf[no3] + lonz/2.0));
		if ((wf[no6] - lonz/2.0 <= mh[no6]) && (wf[no6] + lonz/2.0 >= mh[no6]))	V2 = fabs(lonx * lony * (mh[no6] - wf[no6] + lonz/2.0));
		// flotteur inonde  extremite 1 & 2
		if ((wf[no3] + lonz/2.0 < mh[no3]))					V1 = V;
		if ((wf[no6] + lonz/2.0 < mh[no6]))					V2 = V;
		
		//Ma1 = V1 * Element[zi].rhoelement;	/*a modifier lorsque le cm sera connu*/
		//Ma2 = V2 * Element[zi].rhoelement;	/*a modifier lorsque le cm sera connu*/
		Ma1 = V1 * RHO;	/*a modifier lorsque le cm sera connu*/
		Ma2 = V2 * RHO;	/*a modifier lorsque le cm sera connu*/
      		  		
    		waelem[no1] += Ma1 * (mgh[no1] - mgb[no1]) + RHO * V1 * mgh[no1] - M * mgb[no1];
    		waelem[no2] += Ma1 * (mgh[no2] - mgb[no2]) + RHO * V1 * mgh[no2] - M * mgb[no2];
    		waelem[no3] += Ma1 * (mgh[no3] - mgb[no3]) + RHO * V1 * mgh[no3] - M * mgb[no3];
    		waelem[no4] += Ma2 * (mgh[no4] - mgb[no4]) + RHO * V2 * mgh[no4] - M * mgb[no4];
    		waelem[no5] += Ma2 * (mgh[no5] - mgb[no5]) + RHO * V2 * mgh[no5] - M * mgb[no5];
    		waelem[no6] += Ma2 * (mgh[no6] - mgb[no6]) + RHO * V2 * mgh[no6] - M * mgb[no6];
      		  		
    		/*waelem[no1] +=  - M * mgb[no1];
    		waelem[no2] +=  - M * mgb[no2];
    		waelem[no3] +=  - M * mgb[no3];
    		waelem[no4] +=  - M * mgb[no4];
    		waelem[no5] +=  - M * mgb[no5];
    		waelem[no6] +=  - M * mgb[no6];*/
    		
		//printf("zi %4d V %lf M %lf Ma1 %lf mgh %lf %lf %lf wa %lf %lf %lf \n",zi,V,M,Ma1,mgh[no1],mgh[no2],mgh[no3],waelem[no1],waelem[no2],waelem[no3]);

		if (Structure.type_solver == 1)
		{
	    		ze[no1][eca] += (Ma1 + M) / Pascalcul / Pascalcul;
	    		ze[no2][eca] += (Ma1 + M) / Pascalcul / Pascalcul;
	    		ze[no3][eca] += (Ma1 + M) / Pascalcul / Pascalcul;
	    		ze[no4][eca] += (Ma2 + M) / Pascalcul / Pascalcul;
	    		ze[no5][eca] += (Ma2 + M) / Pascalcul / Pascalcul;
	    		ze[no6][eca] += (Ma2 + M) / Pascalcul / Pascalcul;
		}
		else if (Structure.type_solver == 2)
		{
			//affectation_pardiso((Ma + M) / Pascalcul / Pascalcul, no1, no1);
			//affectation_pardiso((Ma + M) / Pascalcul / Pascalcul, no2, no2);
			//affectation_pardiso((Ma + M) / Pascalcul / Pascalcul, no3, no3);
			//affectation_pardiso((Ma + M) / Pascalcul / Pascalcul, no4, no4);
			//affectation_pardiso((Ma + M) / Pascalcul / Pascalcul, no5, no5);
			//affectation_pardiso((Ma + M) / Pascalcul / Pascalcul, no6, no6);
		}
	}
}
