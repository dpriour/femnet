#define PRINCIPAL 0
#include "4c19.h"

void poidstri_hexa(int elem)

	{
	/*Calcul du poids agissant sur un triangle a maille hexagonale, et affecte au sommet.*/ 
	
  	int i;
  	double Pl,Pm,Pn;
  
  	/*Pl,Pm,Pn sont les poids des fils l, m, n du filet, au repos, dans l'eau. Ce sont des constantes par triangle.*/ 
  	
     	Pl = Surf_Hexa[elem].lo_repos*PI*Surf_Hexa[elem].diam_hydro_l*Surf_Hexa[elem].diam_hydro_l*Surf_Hexa[elem].rhosurface * G / 4.0;
      	Pm = Surf_Hexa[elem].mo_repos*PI*Surf_Hexa[elem].diam_hydro_m*Surf_Hexa[elem].diam_hydro_m*Surf_Hexa[elem].rhosurface * G / 4.0;
     	Pn = Surf_Hexa[elem].no_repos*PI*Surf_Hexa[elem].diam_hydro_n*Surf_Hexa[elem].diam_hydro_n*Surf_Hexa[elem].rhosurface * G / 4.0;
    
  	/*Pe est le vecteur qui contient les efforts dus au poids pour les trois sommets du triangle.*/
  	/*Initialisation de Pe a zero*/ 
  	  
    	for ( i = 1 ; i <= 9 ; i++ )
    		{ 
      		Pe[i] = 0.0;
    		}

  	/* 
  	Poids  selon l'axe Z pour le sommet 1 2 et 3 du triangle.
     	Surf_Hexa[elem].nb_cote_l_m_ou_n / 3.0 est le nombre de mailles selon l, m ou n, affecte au point 1 2 et 3.
     	*/
     	
     	Pe[3] = - (Pl + Pm + Pn) * (Surf_Hexa[elem].nb_cote_l_m_ou_n / 3.0);
     	Pe[6] = - (Pl + Pm + Pn) * (Surf_Hexa[elem].nb_cote_l_m_ou_n / 3.0);
     	Pe[9] = - (Pl + Pm + Pn) * (Surf_Hexa[elem].nb_cote_l_m_ou_n / 3.0);      
	}
