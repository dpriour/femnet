#include "4c19.h"

void inertie_surface2()
{
  	/* 
  	effort et raideur d inertie sur chaque surface de filet a maille losange
  	effort = Ma(gammah - gamma) + rho V gammah - M gamma
  	Ma = K rho V 
  	avec K = 1 dans le cas de cylindres
  	raideur = + (M + Ma) / delt^2 
  	
  	ATTENTION la repartition des masses et du volume n est pas correctement faite dans le cas du flottant
  	de meme la raideur liee a la variation de volume V dans les cas fottant n est pas pris en compte
  	*/

  	int zh,zi,zj,no1,no2,no3,no4,no5,no6,no7,no8,no9,elem;
  	double immersion,volume,immer,f,lmouillee,dx,dy,dz,d1,d2,d3,d4,d5,d6,C,M,Ma,V;
  	double lonx,lony,lonz,V1,V2,V3, Ma1,Ma2,Ma3;

  	for (elem = 1 ; elem<= NOMBRE_SURFACES ; elem++) 
	{
    		no1 = yc(elem,1); 	/*numero de la coordonnee selon x de l sommet  1 du triangle*/
    		no2 = yc(elem,2); 	/*numero de la coordonnee selon y de l sommet  1 du triangle*/
    		no3 = yc(elem,3); 	/*numero de la coordonnee selon z de l sommet  1 du triangle*/
    		no4 = yc(elem,4); 	/*numero de la coordonnee selon x de l sommet  2 du triangle*/
    		no5 = yc(elem,5); 	/*numero de la coordonnee selon y de l sommet  2 du triangle*/
    		no6 = yc(elem,6); 	/*numero de la coordonnee selon z de l sommet  2 du triangle*/
    		no7 = yc(elem,7); 	/*numero de la coordonnee selon z de l sommet  3 du triangle*/
    		no8 = yc(elem,8); 	/*numero de la coordonnee selon z de l sommet  3 du triangle*/
    		no9 = yc(elem,9); 	/*numero de la coordonnee selon z de l sommet  3 du triangle*/

      		V = PI * Surface[elem].diametrehydro * Surface[elem].diametrehydro / 4.0 * Surface[elem].lgrepos * 2.0 * Surface[elem].nb_cote_u_ou_v / 3.0;	//1/3 volume du triangle a chaque sommet
      		M = V * Surface[elem].rhosurface; 														//1/3 masse  du triangle a chaque sommet				  		
      		
		lonx = pow(V,1.0/3.0);	//cote selon x du cube de volume V
		lony = lonx; 		//cote selon y du cube de volume V
		lonz = V/(lonx*lonx);	//cote selon z du cube de volume V
      		
		// flotteur exonde sommet 1, 2 & 3
		if (wf[no3] - lonz/2.0 > mh[no3])					V1 = 0.0;	//volume inonde sommet 1
		if (wf[no6] - lonz/2.0 > mh[no6])					V2 = 0.0;	//volume inonde sommet 2
		if (wf[no9] - lonz/2.0 > mh[no9])					V3 = 0.0;	//volume inonde sommet 3
		// flotteur flottant sommet 1, 2 & 3
		if ((wf[no3] - lonz/2.0 <= mh[no3]) && (wf[no3] + lonz/2.0 >= mh[no3]))	V1 = fabs(lonx * lony * (mh[no3] - wf[no3] + lonz/2.0));
		if ((wf[no6] - lonz/2.0 <= mh[no6]) && (wf[no6] + lonz/2.0 >= mh[no6]))	V2 = fabs(lonx * lony * (mh[no6] - wf[no6] + lonz/2.0));
		if ((wf[no9] - lonz/2.0 <= mh[no9]) && (wf[no9] + lonz/2.0 >= mh[no9]))	V3 = fabs(lonx * lony * (mh[no9] - wf[no9] + lonz/2.0));
		// flotteur inonde  sommet 1, 2 & 3
		if ((wf[no3] + lonz/2.0 < mh[no3]))					V1 = V;
		if ((wf[no6] + lonz/2.0 < mh[no6]))					V2 = V;
		if ((wf[no9] + lonz/2.0 < mh[no9]))					V3 = V;
		
		//Ma1 = V1 * Surface[elem].rhosurface;	/*a modifier lorsque le cm sera connu*/
		//Ma2 = V2 * Surface[elem].rhosurface;	/*a modifier lorsque le cm sera connu*/
		//Ma3 = V3 * Surface[elem].rhosurface;	/*a modifier lorsque le cm sera connu*/
		Ma1 = V1 * RHO;	/*a modifier lorsque le cm sera connu*/
		Ma2 = V2 * RHO;	/*a modifier lorsque le cm sera connu*/
		Ma3 = V3 * RHO;	/*a modifier lorsque le cm sera connu*/
      		  		
    		wasurf[no1] += Ma1 * (mgh[no1] - mgb[no1]) + RHO * V1 * mgh[no1] - M * mgb[no1];
    		wasurf[no2] += Ma1 * (mgh[no2] - mgb[no2]) + RHO * V1 * mgh[no2] - M * mgb[no2];
    		wasurf[no3] += Ma1 * (mgh[no3] - mgb[no3]) + RHO * V1 * mgh[no3] - M * mgb[no3];
    		wasurf[no4] += Ma2 * (mgh[no4] - mgb[no4]) + RHO * V2 * mgh[no4] - M * mgb[no4];
    		wasurf[no5] += Ma2 * (mgh[no5] - mgb[no5]) + RHO * V2 * mgh[no5] - M * mgb[no5];
    		wasurf[no6] += Ma2 * (mgh[no6] - mgb[no6]) + RHO * V2 * mgh[no6] - M * mgb[no6];
    		wasurf[no7] += Ma3 * (mgh[no7] - mgb[no7]) + RHO * V3 * mgh[no7] - M * mgb[no7];
    		wasurf[no8] += Ma3 * (mgh[no8] - mgb[no8]) + RHO * V3 * mgh[no8] - M * mgb[no8];
    		wasurf[no9] += Ma3 * (mgh[no9] - mgb[no9]) + RHO * V3 * mgh[no9] - M * mgb[no9];
      		  		   		
		//printf("elem %4d M %lf mgb %lf %lf %lf wa %lf %lf %lf \n",elem,M,mgb[no1],mgb[no2],mgb[no3],waelem[no1],waelem[no2],waelem[no3]);

		if (Structure.type_solver == 1)
		{
	    		ze[no1][eca] += (Ma1 + M) / Pascalcul / Pascalcul;
	    		ze[no2][eca] += (Ma1 + M) / Pascalcul / Pascalcul;
	    		ze[no3][eca] += (Ma1 + M) / Pascalcul / Pascalcul;
	    		ze[no4][eca] += (Ma2 + M) / Pascalcul / Pascalcul;
	    		ze[no5][eca] += (Ma2 + M) / Pascalcul / Pascalcul;
	    		ze[no6][eca] += (Ma2 + M) / Pascalcul / Pascalcul;
	    		ze[no7][eca] += (Ma3 + M) / Pascalcul / Pascalcul;
	    		ze[no8][eca] += (Ma3 + M) / Pascalcul / Pascalcul;
	    		ze[no9][eca] += (Ma3 + M) / Pascalcul / Pascalcul;
		}
		else if (Structure.type_solver == 2)
		{
			//affectation_pardiso((Ma + M) / Pascalcul / Pascalcul, no1, no1);
		}

	}
	for (elem = 1; elem<= NOMBRE_SURF_HEXA; elem++)
	{
    		no1 = yc_hexa(elem,1); 	/*numero de la coordonnee selon x de l sommet  1 du triangle*/
    		no2 = yc_hexa(elem,2); 	/*numero de la coordonnee selon y de l sommet  1 du triangle*/
    		no3 = yc_hexa(elem,3); 	/*numero de la coordonnee selon z de l sommet  1 du triangle*/
    		no4 = yc_hexa(elem,4); 	/*numero de la coordonnee selon x de l sommet  2 du triangle*/
    		no5 = yc_hexa(elem,5); 	/*numero de la coordonnee selon y de l sommet  2 du triangle*/
    		no6 = yc_hexa(elem,6); 	/*numero de la coordonnee selon z de l sommet  2 du triangle*/
    		no7 = yc_hexa(elem,7); 	/*numero de la coordonnee selon z de l sommet  3 du triangle*/
    		no8 = yc_hexa(elem,8); 	/*numero de la coordonnee selon z de l sommet  3 du triangle*/
    		no9 = yc_hexa(elem,9); 	/*numero de la coordonnee selon z de l sommet  3 du triangle*/

      		V  = PI * Surf_Hexa[elem].diam_hydro_l * Surf_Hexa[elem].diam_hydro_l * Surf_Hexa[elem].lo_repos / 4.0 * Surf_Hexa[elem].nb_cote_l_m_ou_n / 3.0;
      		V += PI * Surf_Hexa[elem].diam_hydro_m * Surf_Hexa[elem].diam_hydro_m * Surf_Hexa[elem].mo_repos / 4.0 * Surf_Hexa[elem].nb_cote_l_m_ou_n / 3.0;
      		V += PI * Surf_Hexa[elem].diam_hydro_n * Surf_Hexa[elem].diam_hydro_n * Surf_Hexa[elem].no_repos / 4.0 * Surf_Hexa[elem].nb_cote_l_m_ou_n / 3.0;
      		M = V * Surf_Hexa[elem].rhosurface; 														//1/3 masse  du triangle a chaque sommet				  		
      		
		lonx = pow(V,1.0/3.0);	//cote selon x du cube de volume V
		lony = lonx; 		//cote selon y du cube de volume V
		lonz = V/(lonx*lonx);	//cote selon z du cube de volume V
      		
		// flotteur exonde sommet 1, 2 & 3
		if (wf[no3] - lonz/2.0 > mh[no3])					V1 = 0.0;	//volume inonde sommet 1
		if (wf[no6] - lonz/2.0 > mh[no6])					V2 = 0.0;	//volume inonde sommet 2
		if (wf[no9] - lonz/2.0 > mh[no9])					V3 = 0.0;	//volume inonde sommet 3
		// flotteur flottant sommet 1, 2 & 3
		if ((wf[no3] - lonz/2.0 <= mh[no3]) && (wf[no3] + lonz/2.0 >= mh[no3]))	V1 = fabs(lonx * lony * (mh[no3] - wf[no3] + lonz/2.0));
		if ((wf[no6] - lonz/2.0 <= mh[no6]) && (wf[no6] + lonz/2.0 >= mh[no6]))	V2 = fabs(lonx * lony * (mh[no6] - wf[no6] + lonz/2.0));
		if ((wf[no9] - lonz/2.0 <= mh[no9]) && (wf[no9] + lonz/2.0 >= mh[no9]))	V3 = fabs(lonx * lony * (mh[no9] - wf[no9] + lonz/2.0));
		// flotteur inonde  sommet 1, 2 & 3
		if ((wf[no3] + lonz/2.0 < mh[no3]))					V1 = V;
		if ((wf[no6] + lonz/2.0 < mh[no6]))					V2 = V;
		if ((wf[no9] + lonz/2.0 < mh[no9]))					V3 = V;
		
		Ma1 = V1 * Surf_Hexa[elem].rhosurface;	/*a modifier lorsque le cm sera connu*/
		Ma2 = V2 * Surf_Hexa[elem].rhosurface;	/*a modifier lorsque le cm sera connu*/
		Ma3 = V3 * Surf_Hexa[elem].rhosurface;	/*a modifier lorsque le cm sera connu*/
      		  		
    		wasurf[no1] += Ma1 * (mgh[no1] - mgb[no1]) + RHO * V1 * mgh[no1] - M * mgb[no1];
    		wasurf[no2] += Ma1 * (mgh[no2] - mgb[no2]) + RHO * V1 * mgh[no2] - M * mgb[no2];
    		wasurf[no3] += Ma1 * (mgh[no3] - mgb[no3]) + RHO * V1 * mgh[no3] - M * mgb[no3];
    		wasurf[no4] += Ma2 * (mgh[no4] - mgb[no4]) + RHO * V2 * mgh[no4] - M * mgb[no4];
    		wasurf[no5] += Ma2 * (mgh[no5] - mgb[no5]) + RHO * V2 * mgh[no5] - M * mgb[no5];
    		wasurf[no6] += Ma2 * (mgh[no6] - mgb[no6]) + RHO * V2 * mgh[no6] - M * mgb[no6];
    		wasurf[no7] += Ma3 * (mgh[no7] - mgb[no7]) + RHO * V3 * mgh[no7] - M * mgb[no7];
    		wasurf[no8] += Ma3 * (mgh[no8] - mgb[no8]) + RHO * V3 * mgh[no8] - M * mgb[no8];
    		wasurf[no9] += Ma3 * (mgh[no9] - mgb[no9]) + RHO * V3 * mgh[no9] - M * mgb[no9];
      		  		   		
		//printf("elem %4d M %lf mgb %lf %lf %lf wa %lf %lf %lf \n",elem,M,mgb[no1],mgb[no2],mgb[no3],waelem[no1],waelem[no2],waelem[no3]);

		if (Structure.type_solver == 1)
		{
	    		ze[no1][eca] += (Ma1 + M) / Pascalcul / Pascalcul;
	    		ze[no2][eca] += (Ma1 + M) / Pascalcul / Pascalcul;
	    		ze[no3][eca] += (Ma1 + M) / Pascalcul / Pascalcul;
	    		ze[no4][eca] += (Ma2 + M) / Pascalcul / Pascalcul;
	    		ze[no5][eca] += (Ma2 + M) / Pascalcul / Pascalcul;
	    		ze[no6][eca] += (Ma2 + M) / Pascalcul / Pascalcul;
	    		ze[no7][eca] += (Ma3 + M) / Pascalcul / Pascalcul;
	    		ze[no8][eca] += (Ma3 + M) / Pascalcul / Pascalcul;
	    		ze[no9][eca] += (Ma3 + M) / Pascalcul / Pascalcul;
		}
		else if (Structure.type_solver == 2)
		{
			//affectation_pardiso((Ma + M) / Pascalcul / Pascalcul, no1, no1);
		}

	}
}
