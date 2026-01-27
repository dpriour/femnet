#include "4c19.h"

void ball_pesanteur()
	{
  	int zi,no;
  	double modulevitesse,immersion,demirhovit,immer,v2,Rho_ball,masse;
  	
	Rho_ball = 80.0;
	
  	/* pour chaque ball prendre en compte la pesanteur*/
   	for (zi = 1 ; zi<= Ball.nb; zi++) 
  		{
  		no = Ball.noeud[zi];
  		masse = 4.0/3.0*PI*Ball.radius[zi]*Ball.radius[zi]*Ball.radius[zi]*Rho_ball;
      		wanoeud[3*no-0] -= masse*G;
  		}
	}



