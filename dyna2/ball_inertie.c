#include "4c19.h"

void ball_inertie()
	{
  	int zi,no;
  	double modulevitesse,immersion,demirhovit,immer,v2,Rho_ball,masse;
  	
	Rho_ball = 80.0;
	
  	/* pour chaque ball prendre en compte la pesanteur*/
   	for (zi = 1 ; zi<= Ball.nb; zi++) 
  		{
  		no = Ball.noeud[zi];
  		masse = 4.0/3.0*PI*Ball.radius[zi]*Ball.radius[zi]*Ball.radius[zi]*Rho_ball;
    		wanoeud[3*no-2] -= masse * mgb[3*no-2];
    		wanoeud[3*no-1] -= masse * mgb[3*no-1];
    		wanoeud[3*no-0] -= masse * mgb[3*no-0];
		/*printf("zi %4d no %4d masse %lf mgb %lf %lf %lf wa %lf %lf %lf wf %lf %lf %lf\n",zi,no,masse,mgb[3*no-2],mgb[3*no-1],mgb[3*no-0],wanoeud[3*no-2],wanoeud[3*no-1],wanoeud[3*no-0],wf[3*no-2],wf[3*no-1],wf[3*no-0]);*/
		if (Structure.type_solver == 1)
		{
  	  		ze[3*no-2][eca] += masse / Pascalcul / Pascalcul;
	    		ze[3*no-1][eca] += masse / Pascalcul / Pascalcul;
    			ze[3*no-0][eca] += masse / Pascalcul / Pascalcul;
		}
		else if (Structure.type_solver == 2)
		{

			//affectation_pardiso(masse / Pascalcul / Pascalcul, 3*no-2, 3*no-2);
			//affectation_pardiso(masse / Pascalcul / Pascalcul, 3*no-1, 3*no-1);
			//affectation_pardiso(masse / Pascalcul / Pascalcul, 3*no, 3*no);
		}
  	}
}


