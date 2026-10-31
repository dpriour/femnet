#define PRINCIPAL 0
#include "4c19.h"

void transnoeud()
	{
	/*
	On ajoute une "raideur fictive" sur les termes diagonaux de la matrice,
	de sorte qu'elle ne soit jamais singuliere. Ce terme provient du
	parametre lu dans param.txt
	*/
	
	int    elem,zi,zj,zimini,zjmini,nb_inf;
	double rai,mini;
	
	if (Structure.type_solver == 1)
	{
		//nb_inf = 0;
		for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
		{
			
			ze[3*elem-2][eca] += Numtemps;
			ze[3*elem-1][eca] += Numtemps;
			ze[3*elem-0][eca] += Numtemps;
			
			/*
			if (ze[3*elem-2][eca] < Numtemps)	
				{
				ze[3*elem-2][eca] = Numtemps;
				nb_inf++;
				}
			if (ze[3*elem-1][eca] < Numtemps)	
				{
				ze[3*elem-1][eca] = Numtemps;
				nb_inf++;
				}
			if (ze[3*elem-0][eca] < Numtemps)	
				{
				ze[3*elem-0][eca] = Numtemps;
				nb_inf++;
				}
			*/
		}
		//Structure.ratio_num_temp = (double) nb_inf/3/NOMBRE_NOEUDS;
	/*for (zi = 1; zi<= 3*NOMBRE_NOEUDS; zi++)
		{
		for (zj = rang[4][zi]; zj<= rang[2][zi]; zj++)
			{
			ze[zi][eca-zi+zj] += Numtemps;
			}
		}*/
	}
	else if (Structure.type_solver == 2)
	{
		for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
		{
			//affectation_pardiso(Numtemps, 3*elem-2, 3*elem-2);
			//affectation_pardiso(Numtemps, 3*elem-1, 3*elem-1);
			//affectation_pardiso(Numtemps, 3*elem, 3*elem);
		}
	}
}

