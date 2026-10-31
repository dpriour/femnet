#include "4c19.h"

void estime_position()
	{
  	int zi;
  	double mvbz,mvbm;
  	
  	/* 
  	une fois connu la position wf, la vitesse mvb et l acceleration on calcule une estimation de la
  	position au temps t + Pascalcul
  	La vitesse a t est mvb, la vitesse a t + Pascalcul est     mvb + Pascalcul * mgb     , appele mvbz
  	la vitesse entre t et t + Pascalcul peut etre estime comme la moyenne de mvb et mvbz, appele mvbm
  	dans ces conditions l estime de position a t + Pascalcul est wf + Pascalcul * mvbm
  	*/
	/*printf("  %17.9lf",mgb[3*fixa[2]-2]);  		
	printf("  %17.9lf",mvb[3*fixa[2]-2]);  		
	printf("  %17.9lf",wf[3*fixa[2]-2]);*/
   	for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS; zi++) 
  		{
  		if (wl[zi] != 0)
  			{
  			wf[zi] += (Pascalcul * (   mvb[zi] + ((Pascalcul * mgb[zi])/ 2.0)   ) ) ;
  			}
		}/**/
	/*printf("  %17.9lf\n",wf[3*fixa[2]-2]);*/
	}

