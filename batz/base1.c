#include "batz.h"
/*#include "4c19.h"*/

void base1(double angl1,int axeangl1,double angl2,int  axeangl2,int  nbcol,double *vect)

	/* 
	Changement de base du vecteur vect de dimension nbcol (nbcol <= 9)
  	Rotation de angl1 autour de l'axe axeangl1 puis rotation de angl2  autour de l'axe axeangl2.
  	Si axeangl = 1 : rotation autour de l axe des X
  	Si axeangl = 2 : rotation autour de l axe des Y
  	Si axeangl = 3 : rotation autour de l axe des Z
  	*/

	{
  	int zi,zj,zk;
  	double    Lamda[10][10], inter[10], rota[4][4], rotb[4][4], rotc[4][4];

  	/*premiere matrice de rotation*/
  	if (axeangl1 == 1)
  		{
    		rota[1][1] =   1.0;         rota[1][2] =   0.0;         rota[1][3] =   0.0;
    		rota[2][1] =   0.0;         rota[2][2] =   cos(angl1);  rota[2][3] =   sin(angl1);
    		rota[3][1] =   0.0;         rota[3][2] = - sin(angl1);  rota[3][3] =   cos(angl1);
  		}
  	if (axeangl1 == 2)
  		{
    		rota[1][1] =   cos(angl1);  rota[1][2] =   0.0;         rota[1][3] = - sin(angl1);
    		rota[2][1] =   0.0;         rota[2][2] =   1.0;         rota[2][3] =   0.0;
    		rota[3][1] =   sin(angl1);  rota[3][2] =   0.0;         rota[3][3] =   cos(angl1);
  		}
  	if (axeangl1 == 3)
  		{
    		rota[1][1] =   cos(angl1);  rota[1][2] =   sin(angl1);  rota[1][3] =   0.0;
    		rota[2][1] = - sin(angl1);  rota[2][2] =   cos(angl1);  rota[2][3] =   0.0;
    		rota[3][1] =   0.0;         rota[3][2] =   0.0;         rota[3][3] =   1.0;
  		}
  	/*seconde matrice de rotation*/
  	if (axeangl2 == 1)
  		{
    		rotb[1][1] =   1.0;         rotb[1][2] =   0.0;         rotb[1][3] =   0.0;
    		rotb[2][1] =   0.0;         rotb[2][2] =   cos(angl2);  rotb[2][3] =   sin(angl2);
    		rotb[3][1] =   0.0;         rotb[3][2] = - sin(angl2);  rotb[3][3] =   cos(angl2);
  		}
  	if (axeangl2 == 2)
  		{
    		rotb[1][1] =   cos(angl2);  rotb[1][2] =   0.0;         rotb[1][3] = - sin(angl2);
    		rotb[2][1] =   0.0;         rotb[2][2] =   1.0;         rotb[2][3] =   0.0;
    		rotb[3][1] =   sin(angl2);  rotb[3][2] =   0.0;         rotb[3][3] =   cos(angl2);
  		}
  	if (axeangl2 == 3)
  		{
    		rotb[1][1] =   cos(angl2);  rotb[1][2] =   sin(angl2);  rotb[1][3] =   0.0;
    		rotb[2][1] = - sin(angl2);  rotb[2][2] =   cos(angl2);  rotb[2][3] =   0.0;
    		rotb[3][1] =   0.0;         rotb[3][2] =   0.0;         rotb[3][3] =   1.0;
  		}
  
  	/*mise a zero de la matrice rotation elementaire*/
  	for (zi = 1 ; zi<= 3 ; zi++)
  		{
    		for (zj = 1 ; zj<= 3 ; zj++) 
    			{
      			rotc[zi][zj] = 0.0;
    			}
  		}

  	/*matrice rotation elementaire*/
  	for (zi = 1 ; zi<= 3 ; zi++)
  		{
    		for (zj = 1 ; zj<= 3 ; zj++) 
    			{
      			for (zk = 1 ; zk<= 3 ; zk++) 
      				{
        			rotc[zi][zj] += rotb[zk][zj] * rota[zi][zk];
      				}
    			}
  		}

  	/*mise a zero de la matrice rotation globale*/
  	for (zi = 1 ; zi<= nbcol ; zi++)
  		{
    		for (zj = 1 ; zj<= nbcol ; zj++) 
    			{
      			Lamda[zi][zj] = 0.0;
    			}
  		}

  	/*matrice rotation globale*/
  	for (zi = 1 ; zi<= nbcol/3 ; zi++)
  		{
    		for (zj = 1 ; zj<= 3 ; zj++) 
    			{
      			for (zk = 1 ; zk<= 3 ; zk++) 
      				{
        			Lamda[zj+3*zi-3][zk+3*zi-3] = rotc[zj][zk];
      				}
    			}
  		}

  	/*copie du vecteur vect dans inter*/
  	for (zi = 1 ; zi<= nbcol ; zi++)
  		{
    		inter[zi] = vect[zi];
  		}

  	/*mise a zero du vecteur vect */
  	for (zi = 1 ; zi<= nbcol ; zi++)
  		{
    		vect[zi] = 0.0;
  		}

  	/*changement de base de vect*/
  	for (zi = 1 ; zi<= nbcol ; zi++)
  		{
    		for (zj = 1 ; zj<= nbcol ; zj++) 
    			{
       			vect[zi] += inter[zj] * Lamda[zj][zi];
    			}
  		}
	}


