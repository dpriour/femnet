#define PRINCIPAL 0
#include "4c19.h"

void poidstriang(int elem)

	{
	/* 
	Calcul du poids agissant sur un triangle a maille losange, et affecte au sommet. 
	*/

  	int i;
  	double P;
  
  	/* 
  	P est le poids d'une maille du filet, au repos, dans l'eau. C'est une constante par triangle. 
  	*/
     	
     	P = Surface[elem].lgrepos*PI*Surface[elem].diametrehydro*Surface[elem].diametrehydro*Surface[elem].rhosurface * G / 4.0;
     
  	/* 
  	Pe est le vecteur qui contient les efforts dus au poids pour les trois sommets du triangle 
  	*/ 
  
  	/* 
  	Initialisation de Pe a zero 
  	*/  
    	for ( i = 1 ; i <= 9 ; i++ )
    		{ 
      		Pe[i] = 0.0;
    		}

  	/* 
  	Poids  selon l'axe Z pour le sommet 1 2 et 3du triangle.
     	Surface[elem].nb_cote_u_ou_v / 3.0 est le nombre de mailles selon u (resp. selon v), affecte au point 1 2 et 3.
     	multiplie par 2 pour tenir compter des fils u et v
     	*/
     	
     	Pe[3] = - P*(2.0 * Surface[elem].nb_cote_u_ou_v / 3.0);
     	Pe[6] = - P*(2.0 * Surface[elem].nb_cote_u_ou_v / 3.0);
     	Pe[9] = - P*(2.0 * Surface[elem].nb_cote_u_ou_v / 3.0);      
	}
