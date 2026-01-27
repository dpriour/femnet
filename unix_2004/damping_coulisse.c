#define PRINCIPAL 0
#include "4c19.h"

void damping_coulisse()
{
	/* 
	Calcul des raideurs additionnelles dues au deplacement virtuels des coulisses
	les coulisses sont dans un fluide virtuel Au cours des iterations les coulisses se deplacent
	et le fluide s y oppose ce qui donne une raideur additionnelle pour cela on introduit un
	pas de temps deltat qui correspond au temps d une iteration
	la raideur = effort / deltat
	effort = - 1/2 rho Cd D L vitesse
	vitesse = delta_deplacement / deltat
	soit
	raideur = - 1/2 1000 1 D L / deltat
	*/

  	int i, ii, j, jj,elem,segm,zl,zk,noeud1,noeud2;
  	double alpha3,beta2;
  	double vect[7];

  	if (deltat <= 0.0)
  	{
  		printf("deltat <= 0.0, modifier sa valeur dans param.txt \n");
  		deltat = 0.000001;
	}
		
  	for (elem = 1 ; elem<= NOMBRE_COULISSES ; elem++)
  	{
    		for (segm = 1 ; segm<= Coulisse[elem].nb_noeud + 1; segm++) 
    		{
    			if (segm == 1) noeud1 = Coulisse[elem].extremite[1];
    			if (segm != 1) noeud1 = Coulisse[elem].noeud[segm-1];
    			if (segm != Coulisse[elem].nb_noeud + 1) noeud2 = Coulisse[elem].noeud[segm];
    			if (segm == Coulisse[elem].nb_noeud + 1) noeud2 = Coulisse[elem].extremite[2];
    			vect[1] = wf[3*noeud1-2];
    			vect[4] = wf[3*noeud2-2];
    			vect[2] = wf[3*noeud1-1];
    			vect[5] = wf[3*noeud2-1];
    			vect[3] = wf[3*noeud1-0];
    			vect[6] = wf[3*noeud2-0];
    			
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
  			we[2][2] = +250.0 / deltat * Coulisse[elem].diametrehydro * Coulisse[elem].longueur[segm];
  			we[3][3] = +250.0 / deltat * Coulisse[elem].diametrehydro * Coulisse[elem].longueur[segm];
  			we[5][5] = +250.0 / deltat * Coulisse[elem].diametrehydro * Coulisse[elem].longueur[segm];
  			we[6][6] = +250.0 / deltat * Coulisse[elem].diametrehydro * Coulisse[elem].longueur[segm];
  		
  			/*printf("deltat = %lf \n",deltat);*/
  		
  			base9( -beta2, 2, -alpha3,  3,  9, we);
			if (Structure.type_solver == 1)
			{
				/* Mise a jour de la matrice de raideur globale  */
	
				ze[3*noeud1-2][eca+3*noeud1-2-3*noeud1+2] += we[1][1];
				ze[3*noeud1-2][eca+3*noeud1-1-3*noeud1+2] += we[1][2];
				ze[3*noeud1-2][eca+3*noeud1-0-3*noeud1+2] += we[1][3];
				ze[3*noeud1-2][eca+3*noeud2-2-3*noeud1+2] += we[1][4];
				ze[3*noeud1-2][eca+3*noeud2-1-3*noeud1+2] += we[1][5];
				ze[3*noeud1-2][eca+3*noeud2-0-3*noeud1+2] += we[1][6];
	
				ze[3*noeud1-1][eca+3*noeud1-2-3*noeud1+1] += we[2][1];
				ze[3*noeud1-1][eca+3*noeud1-1-3*noeud1+1] += we[2][2];
				ze[3*noeud1-1][eca+3*noeud1-0-3*noeud1+1] += we[2][3];
				ze[3*noeud1-1][eca+3*noeud2-2-3*noeud1+1] += we[2][4];
				ze[3*noeud1-1][eca+3*noeud2-1-3*noeud1+1] += we[2][5];
				ze[3*noeud1-1][eca+3*noeud2-0-3*noeud1+1] += we[2][6];
	
				ze[3*noeud1-0][eca+3*noeud1-2-3*noeud1+0] += we[3][1];
				ze[3*noeud1-0][eca+3*noeud1-1-3*noeud1+0] += we[3][2];
				ze[3*noeud1-0][eca+3*noeud1-0-3*noeud1+0] += we[3][3];
				ze[3*noeud1-0][eca+3*noeud2-2-3*noeud1+0] += we[3][4];
				ze[3*noeud1-0][eca+3*noeud2-1-3*noeud1+0] += we[3][5];
				ze[3*noeud1-0][eca+3*noeud2-0-3*noeud1+0] += we[3][6];
	
				ze[3*noeud2-2][eca+3*noeud1-2-3*noeud2+2] += we[4][1];
				ze[3*noeud2-2][eca+3*noeud1-1-3*noeud2+2] += we[4][2];
				ze[3*noeud2-2][eca+3*noeud1-0-3*noeud2+2] += we[4][3];
				ze[3*noeud2-2][eca+3*noeud2-2-3*noeud2+2] += we[4][4];
				ze[3*noeud2-2][eca+3*noeud2-1-3*noeud2+2] += we[4][5];
				ze[3*noeud2-2][eca+3*noeud2-0-3*noeud2+2] += we[4][6];
	
				ze[3*noeud2-1][eca+3*noeud1-2-3*noeud2+1] += we[5][1];
				ze[3*noeud2-1][eca+3*noeud1-1-3*noeud2+1] += we[5][2];
				ze[3*noeud2-1][eca+3*noeud1-0-3*noeud2+1] += we[5][3];
				ze[3*noeud2-1][eca+3*noeud2-2-3*noeud2+1] += we[5][4];
				ze[3*noeud2-1][eca+3*noeud2-1-3*noeud2+1] += we[5][5];
				ze[3*noeud2-1][eca+3*noeud2-0-3*noeud2+1] += we[5][6];
	
				ze[3*noeud2-0][eca+3*noeud1-2-3*noeud2+0] += we[6][1];
				ze[3*noeud2-0][eca+3*noeud1-1-3*noeud2+0] += we[6][2];
				ze[3*noeud2-0][eca+3*noeud1-0-3*noeud2+0] += we[6][3];
				ze[3*noeud2-0][eca+3*noeud2-2-3*noeud2+0] += we[6][4];
				ze[3*noeud2-0][eca+3*noeud2-1-3*noeud2+0] += we[6][5];
				ze[3*noeud2-0][eca+3*noeud2-0-3*noeud2+0] += we[6][6];
			}
			else if (Structure.type_solver == 2)
      		{
				for (i = 1; i<= 6; i++)
				{
					ii = new_coor(i, noeud1, noeud2, 0, 0);
					for (j=1;j<=6;j++)
					{
						jj = new_coor(j, noeud1, noeud2, 0, 0);
						affectation_pardiso(we[i][j], ii, jj);
					}
				}
      		}
		}
	}
}

