#include "4c19.h"

void actualiser_deplacement_balls()
	{
  	int zi;
  	/* pour chaque ball mettre le deplacement  bloque si t < birth_time et mettre a ball.type si t >= birth_time*/
   	for (zi = 1 ; zi<= Ball.nb; zi++) 
  		{
  		if (times < Ball.birth_time[zi])
  			{ 
			wl[3*Ball.noeud[zi]-2] = 0; 
			wl[3*Ball.noeud[zi]-1] = 0; 
			wl[3*Ball.noeud[zi]-0] = 0; 
  			}
  		else
  			{
    			wl[3*Ball.noeud[zi]-2] = (int) 99 * (1-Noeud[Ball.noeud[zi]].fixx);
    			wl[3*Ball.noeud[zi]-1] = (int) 99 * (1-Noeud[Ball.noeud[zi]].fixy);
   			wl[3*Ball.noeud[zi]-0] = (int) 99 * (1-Noeud[Ball.noeud[zi]].fixz);
  			}
		/*printf("times %lf ball %d noeud %5d ",times,zi,Ball.noeud[zi]);
		printf("wl %5d %5d %5d \n",wl[3*Ball.noeud[zi]-2],wl[3*Ball.noeud[zi]-1],wl[3*Ball.noeud[zi]-0]);*/
  		}
	/*imprvectint(33,wl);*/
	}

