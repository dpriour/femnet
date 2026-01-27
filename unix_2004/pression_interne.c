#define PRINCIPAL 0
#include "4c19.h"

void pression_interne(int elem)
{
	/* 
	efforts wae d une nappe de filet, dus a la pression du courant, 
	dans le plan XOY.
	*/

  	double pression,A,B,C,p,S,force;
  	
  	/*pression constante des poissons sur le cul de chalut*/
  	pression = 0.5 * RHO * Courant.vitesse * Courant.vitesse;
  	/*pression variant lineairemt des poissons sur le cul de chalut*/
  
  	/*cotes A oppose au point 1 cotes B oppose au point 2 cotes C oppose au point 3*/
  	/*X1 ... Y3 sont definis dans rotation3.c*/
  	A = sqrt((X3-X2)*(X3-X2) + (Y3-Y2)*(Y3-Y2));
  	B = sqrt((X1-X3)*(X1-X3) + (Y1-Y3)*(Y1-Y3));
  	C = sqrt((X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1));
  
  	/*p : demi perimetre du triangle*/
  	p = (A + B + C)/2;

  	/*S : surface du triangle elem*/
  	S = sqrt(p*(p-A)*(p-B)*(p-C));
  	
  	/*force sur le triangle due a la pression sur la surface */
	force = pression * S;

   	/* Efforts arbitraires aux 3 noeuds, sommets du triangle.*/
  	wae[1] = 0.0;
  	wae[2] = 0.0;
  	wae[3] = - force / 3.0;
  	wae[4] = 0.0;
  	wae[5] = 0.0;
  	wae[6] = - force / 3.0;
  	wae[7] = 0.0;
  	wae[8] = 0.0;
  	wae[9] = - force / 3.0;

  	/* Effort elementaire place dans l'espace*/
  	base1( -betaa, 2, -alpha,  3,  9, wae);
}



