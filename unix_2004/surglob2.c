#define PRINCIPAL 0
#include "4c19.h"

void surglob2()
	{
	/* 
	Mise a jour du vecteur effort wasurf et de la matrice de raideur ze.
	Les efforts (wae) calcules ici sont dus a l'elasticite des fils de mailles hexagonales, 
	ainsi que la matrice de raideur (we) .
	*/
   	
   	int elem,zh,zi,zj,zl,zk,zm,zn,zf,zu,zv,maxilarg;
	double delta_x,WAE[10],WE[10][10];
	
  	nb_u_tension = 0;
  	nb_v_tension = 0;
  			
	for (elem = 1; elem<= NOMBRE_SURF_HEXA; elem++)
		{
		
		/*printf("elem = %d  ",elem);
		printf("NOMBRE_SURF_HEXA = %d\n",NOMBRE_SURF_HEXA);*/
		
    		/*numeros des coordonnees selon x des sommets du triangle*/
    		zh = yc_hexa(elem,1);  zi = yc_hexa(elem,4);  zj = yc_hexa(elem,7);
    		
      		/*TEST_debut
		delta_x = 0.000000000001;
		for( zu = 0 ; zu <= 10 ; zu++ )
      			{
			if (zu == 1) wf[zh+0] =wf[zh+0] + delta_x;
      			if (zu == 2) wf[zh+1] =wf[zh+1] + delta_x;
      			if (zu == 3) wf[zh+2] =wf[zh+2] + delta_x;
      			if (zu == 4) wf[zi+0] =wf[zi+0] + delta_x;
      			if (zu == 5) wf[zi+1] =wf[zi+1] + delta_x;
      			if (zu == 6) wf[zi+2] =wf[zi+2] + delta_x;
      			if (zu == 7) wf[zj+0] =wf[zj+0] + delta_x;
      			if (zu == 8) wf[zj+1] =wf[zj+1] + delta_x;
      			if (zu == 9) wf[zj+2] =wf[zj+2] + delta_x;
      			TEST_fin*/    		
    		
		rotation3(zh, zi, zj);
		etirement_hexa(elem);/**/	
/*if((zh == 49) || (zi == 49) || (zj == 49))
	{
	printf("elem %5d  ",elem);	
	printf("zh %5d  ",zh); printf("zi %5d  ",zi); printf("zj %5d  \n",zj);
	imprvectreel(9, wae);	
	}*/  		
      		/*TEST_debut
			printf("zu %5d  ",zu); printf("zh %5d  ",zh); printf("zi %5d  ",zi); printf("zj %5d  \n",zj);
			printf("wf %lf %lf %lf %lf %lf %lf %lf %lf %lf \n ",wf[zh+0],wf[zh+1],wf[zh+2],wf[zi+0],wf[zi+1],wf[zi+2],wf[zj+0],wf[zj+1],wf[zj+2]);
			printf("XZ %lf %lf %lf %lf %lf %lf \n",X1,X2,X3,Y1,Y2,Y3);
      			if (zu == 0)
      				{
				for (zl = 1; zl<= 9; zl++)	WAE[zl] = wae[zl];
      				}
      			if (zu == 1) wf[zh+0] =wf[zh+0] - delta_x;
      			if (zu == 2) wf[zh+1] =wf[zh+1] - delta_x;
      			if (zu == 3) wf[zh+2] =wf[zh+2] - delta_x;
      			if (zu == 4) wf[zi+0] =wf[zi+0] - delta_x;
      			if (zu == 5) wf[zi+1] =wf[zi+1] - delta_x;
      			if (zu == 6) wf[zi+2] =wf[zi+2] - delta_x;
      			if (zu == 7) wf[zj+0] =wf[zj+0] - delta_x;
      			if (zu == 8) wf[zj+1] =wf[zj+1] - delta_x;
      			if (zu == 9) wf[zj+2] =wf[zj+2] - delta_x;
      			if ((zu > 0) && (zu < 10))
      				{
				for (zm = 1 ;zm <= 9 ;zm++ )	WE[zm][zu] = - (wae[zm] - WAE[zm]) / delta_x;
      				}
      			if (zu == 10)
      				{		
				for (zm = 1 ;zm <= 9 ;zm++ )
					{
					printf("we = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%10.0lf ",we[zm][zv]);	printf(" \n");
					printf("WE = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%10.0lf ",WE[zm][zv]);	printf(" \n");
					}
      				exit(0);
      				}
      			}
      			TEST_fin*/    		

		if (Structure.type_solver == 1)
		{
			/* Mise a jour de la matrice de raideur globale*/
			for (zl = 1; zl<= 9; zl++)
			{
				for (zk = 1; zk<= 9; zk++) 
				{
					/* we est la matrice de raideur calculee dans etirement_hexa.
					La matrice globale est rangee differemment. Ce n'est plus une matrice
					bande. La diagonale est devenu la colonne eca de ze*/
					ze[yc_hexa(elem,zl)][eca+yc_hexa(elem,zk)-yc_hexa(elem,zl)] += we[zl][zk];
				}
			}
		}
		else if (Structure.type_solver == 2)
		{
			for (zl = 1; zl<= 9; zl++)
			{
				for (zk = 1; zk<= 9; zk++) 
				{
					affectation_pardiso(we[zl][zk], yc_hexa(elem,zl), yc_hexa(elem,zk));
				}
			}
		}
		/* Mise a jour du vecteur effort global*/
		for (zl = 1; zl<= 9; zl++)
			{
			wasurf[yc_hexa(elem,zl)] += wae[zl];
			}

		/* Calcul des bornes pour chaque ligne de la matrice de raideur globale*/
		for (zl = 1; zl<= 9; zl++)
			{
			for (zk = 1; zk<= 9; zk++)
				{
				/*borne basse de la raideur ze*/
				if (rang[1][yc_hexa(elem,zl)] < yc_hexa(elem,zk)) rang[1][yc_hexa(elem,zl)] = yc_hexa(elem,zk); 
				/*borne droite de la raideur ze*/
				if (rang[2][yc_hexa(elem,zl)] < yc_hexa(elem,zk)) rang[2][yc_hexa(elem,zl)] = yc_hexa(elem,zk); 
				/*borne haute de la raideur ze*/
				if (rang[3][yc_hexa(elem,zl)] > yc_hexa(elem,zk)) rang[3][yc_hexa(elem,zl)] = yc_hexa(elem,zk); 
				/*borne gauche de la raideur ze*/
				if (rang[4][yc_hexa(elem,zl)] > yc_hexa(elem,zk)) rang[4][yc_hexa(elem,zl)] = yc_hexa(elem,zk); 
				}
			}
		}
  	/*les fils l m n des mailles hexagonales ont ete calcules*/
  	Structure.lmn_calcules = 1;
	}
