#define PRINCIPAL 0
#include "4c19.h"

void damping_element()
{
	/* 
	Calcul des raideurs additionnelles dues au deplacement virtuels des elements(ie les bouts)
	les element sont dans un fluide virtuel> Au cours des iterations les elements se deplacent
	et le fluide s y oppose ce qui donne une raideur additionnelle pour cela on introduit un
	pas de temps deltat qui correspond au temps d une iteration
	la raideur = effort / deltat
	effort = - 1/2 rho Cd D L vitesse
	vitesse = delta_deplacement / deltat
	soit
	raideur = - 1/2 1000 1 D L / deltat
	*/

  	int elem,zl,zk;
  	double alpha3,beta2;
  	double vect[7];

  	if (deltat <= 0.0)
  	{
  		printf("deltat <= 0.0, modifier sa valeur dans param.txt \n");
  		deltat = 0.000001;
	}
		
  	for (elem = 1; elem<= NOMBRE_ELEMENTS; elem++)
  	{
    		
  		/*printf("elem %d \n",elem);*/
  		
    		vect[1] = wf[yb(elem,1)  ];
    		vect[2] = wf[yb(elem,1)+1];
    		vect[3] = wf[yb(elem,1)+2];
    		vect[4] = wf[yb(elem,4)  ];
    		vect[5] = wf[yb(elem,4)+1];
    		vect[6] = wf[yb(elem,4)+2];
    		
  		/* alpha3 = angle de rotation de l element autour de l'axe OZ, de telle sorte que 
  		l element soit dans le plan XOZ. */ 
   
  		if (vect[4] != vect[1]) 	alpha3 =   atan((vect[5]-vect[2])/(vect[4]-vect[1]));
  		else				alpha3 =   0.0;
  		
		base1( alpha3, 3, 0.0,  1,  6, vect);

  		/* beta2 = angle de rotation de l element autour de l'axe OY, de telle sorte que 
  		l element soit parallele a OX. */ 
   
  		if (vect[4] != vect[1]) 	beta2 =   atan((vect[6]-vect[3])/(vect[4]-vect[1]));
  		else				beta2 =   0.0;
  		
		/*base1( beta2, 2, 0.0,  1,  6, vect);*/

  		for (zl = 1; zl<= 6; zl++)
  		{
  			for (zk = 1; zk<= 6; zk++)
  			{
  				we[zl][zk] = 0.0;
  			}
  		}
  		we[2][2] = +250.0 / deltat * Element[elem].diametrehydro * Element[elem].lgrepos;
  		we[3][3] = +250.0 / deltat * Element[elem].diametrehydro * Element[elem].lgrepos;
  		we[5][5] = +250.0 / deltat * Element[elem].diametrehydro * Element[elem].lgrepos;
  		we[6][6] = +250.0 / deltat * Element[elem].diametrehydro * Element[elem].lgrepos;
  		
  		/*printf("deltat = %lf \n",deltat);*/
  		
  		base9( -beta2, 2, -alpha3,  3,  9, we);

		if (Structure.type_solver == 1)
		{
			/* Mise a jour de la matrice de raideur globale  */
			for (zl = 1; zl<= 6; zl++)
			{
				for (zk = 1; zk<= 6; zk++) 
				{
					/* we est la matrice de raideur damping.
					La matrice globale est rangee differemment. Ce n'est plus une matrice
					bande. La diagonale est devenu la colonne eca de ze*/
					ze[yb(elem,zl)][eca+yb(elem,zk)-yb(elem,zl)] += we[zl][zk];
				}
			}
		}
		else if (Structure.type_solver == 2)
      	{
			for (zl = 1; zl<= 6; zl++)
			{
				for (zk = 1; zk<= 6; zk++) 
				{
					affectation_pardiso(we[zl][zk], yb(elem,zl), yb(elem,zk));
				}
			}
      	}
	}
}

