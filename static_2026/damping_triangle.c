#define PRINCIPAL 0
#include "4c19.h"

void damping_triangle()
{
	/* 
	Calcul des raideurs additionnelles dues au deplacement virtuels des triangles(ie les filets 
	a mailles losange et maille hexagonale)
	les triangles sont dans un fluide virtuel> Au cours des iterations les triangles se deplacent
	et le fluide s y oppose ce qui donne une raideur additionnelle pour cela on introduit un
	pas de temps deltat qui correspond au temps d une iteration
	la raideur = effort / deltat
	effort = - 1/2 rho Cd D L vitesse
	vitesse = delta_deplacement / deltat
	soit
	raideur = - 1/2 1000 1 D L / deltat
	*/

  	int elem,zh,zi,zj,zl,zk;
  	double surface_moyenne;

  	if (deltat <= 0.0)
	{
  		printf("deltat <= 0.0, modifier sa valeur dans param.txt \n");
  		deltat = 0.000001;
	}
		
	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
	{
    		/*numeros des coordonnees selon x des sommets du triangle*/
    		zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
    		/*rotation3 donne X1 Y1 X2 Y2 x3 et Y3 coordonees du triangle dans le plan XoY*/
		rotation3(zh, zi, zj);
		
		for (zl = 1; zl<= 9; zl++)
		{
			for (zk = 1; zk<= 9; zk++) 
			{
				/* mise a zero de la matrice we */
				we[zl][zk] = 0.0;
			}
		}
		
		we[3][3] = +666.7 / deltat * Surface[elem].nb_cote_u_ou_v * Surface[elem].diametrehydro * Surface[elem].lgrepos;
		we[6][6] = +666.7 / deltat * Surface[elem].nb_cote_u_ou_v * Surface[elem].diametrehydro * Surface[elem].lgrepos;
		we[9][9] = +666.7 / deltat * Surface[elem].nb_cote_u_ou_v * Surface[elem].diametrehydro * Surface[elem].lgrepos;
		
  		/* Matrice elementaire placee dans l'espace*/
  		base9( -betaa, 2, -alpha,  3,  9, we);
		
		/*if (elem == 226)
			{
			imprmatreel3( 1, 9, 1,  9,  we, 10);
			}*/

		if (Structure.type_solver == 1)
		{
			/* Mise a jour de la matrice de raideur globale*/
			for (zl = 1; zl<= 9; zl++)
			{
				for (zk = 1; zk<= 9; zk++) 
				{
					/* we est la matrice de raideur calculee dans etirement5.
					La matrice globale est rangee differemment. Ce n'est plus une matrice
					bande. La diagonale est devenu la colonne eca de ze*/
					ze[yc(elem,zl)][eca+yc(elem,zk)-yc(elem,zl)] += we[zl][zk];
				}
			}
		}
		else if (Structure.type_solver == 2)
      	{
			for (zl = 1; zl<= 9; zl++)
			{
				for (zk = 1; zk<= 9; zk++) 
				{
					affectation_pardiso(we[zl][zk], yc(elem,zl), yc(elem,zk));
				}
			}
      	}	
	}
		
	for (elem = 1; elem<= NOMBRE_SURF_HEXA; elem++)
	{
    		/*numeros des coordonnees selon x des sommets du triangle*/
    		zh = yc_hexa(elem,1);  zi = yc_hexa(elem,4);  zj = yc_hexa(elem,7);
    		/*rotation3 donne X1 Y1 X2 Y2 x3 et Y3 coordonees du triangle dans le plan XoY*/
		rotation3(zh, zi, zj);
		
		for (zl = 1; zl<= 9; zl++)
		{
			for (zk = 1; zk<= 9; zk++) 
			{
				/* mise a zero de la matrice we */
				we[zl][zk] = 0.0;
			}
		}
		
		surface_moyenne = ( Surf_Hexa[elem].lo_repos * Surf_Hexa[elem].diam_hydro_l 
				  + Surf_Hexa[elem].mo_repos * Surf_Hexa[elem].diam_hydro_m
				  + Surf_Hexa[elem].no_repos * Surf_Hexa[elem].diam_hydro_n ) / 3.0;
		
		we[3][3] = +1000.0 / deltat * Surf_Hexa[elem].nb_cote_l_m_ou_n * surface_moyenne;
		we[6][6] = +1000.0 / deltat * Surf_Hexa[elem].nb_cote_l_m_ou_n * surface_moyenne;
		we[9][9] = +1000.0 / deltat * Surf_Hexa[elem].nb_cote_l_m_ou_n * surface_moyenne;
		
  		/* Matrice elementaire placee dans l'espace*/
  		base9( -betaa, 2, -alpha,  3,  9, we);
		
		if (Structure.type_solver == 1)
		{
			/* Mise a jour de la matrice de raideur globale*/
			for (zl = 1; zl<= 9; zl++)
			{
				for (zk = 1; zk<= 9; zk++) 
				{
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
	}
}

