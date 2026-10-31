#define PRINCIPAL 0
#include "4c19.h"

void base9(double angl1,int axeangl1,double angl2,int  axeangl2,int  nbcol,double (*mat)[10])

/* Changement de base de la matrice mat de dimension nbcol*nbcol.
   nbcol doit etre egal a 9.
   rotation de angl1 autour de l'axe axeangl1 puis
   rotation de angl2  autour de l'axe axeangl2
   si axeteta = 1 : autour de l axe des X
   si axeteta = 2 : autour de l axe des Y
   si axeteta = 3 : autour de l axe des Z*/

{
  int zi,zj,zk;
  double    Lamda[10][10], inter[10][10], rota[4][4], rotb[4][4], rotc[4][4];

		/*for ( zi = 1 ; zi <= nbcol ; zi++)
  			{    			
  			for ( zj = 1 ; zj <= nbcol ; zj++)
				{
				printf("mat[%1d][%1d] =%7.3lf ",zi,zj,mat[zi][zj]);
  				}
  			printf(" \n");	
  			}*/
  /*printf("angle1 = %10.5lf\n",angl1);
  printf("angle2 = %10.5lf\n",angl2);*/
 
  /*premiere matrice rotation*/
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
  
  /*seconde matrice rotation*/
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

  
  
  /*mise a zero de la matrice inter */
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    for (zj = 1 ; zj<= nbcol ; zj++) 
    {
       inter[zi][zj] = 0.0;
    }
  }

  /*premiere multiplication par Lamda*/
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    for (zj = 1 ; zj<= nbcol ; zj++) 
    {
      for (zk = 1 ; zk<= nbcol ; zk++) 
      {
        inter[zi][zj] += mat[zi][zk] * Lamda[zk][zj];
      }
    }
  }

  /*copie de Lamda dans mat*/
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    for (zj = 1 ; zj<= nbcol ; zj++)   mat[zi][zj] = Lamda[zi][zj];
  }

  /*transposee de Lamda dans Lamda*/
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    for (zj = 1 ; zj<= nbcol ; zj++) 
    {
       Lamda[zi][zj] = mat[zj][zi];
    }
  }


  /*mise a zero de la matrice mat */
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    for (zj = 1 ; zj<= nbcol ; zj++) 
    {
       mat[zi][zj] = 0.0;
    }
  }

  /*seconde multiplication par Lamda transpose*/
  for (zi = 1 ; zi<= nbcol ; zi++)
  {
    for (zj = 1 ; zj<= nbcol ; zj++) 
    {
      for (zk = 1 ; zk<= nbcol ; zk++) 
      {
        mat[zi][zj] += Lamda[zi][zk] * inter[zk][zj];
      }
   }
  }
}
