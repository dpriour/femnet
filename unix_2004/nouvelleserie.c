#define PRINCIPAL 0
#include "4c19.h"

void nouvelleserie()

	{
	/* Definition de la nouvelle serie des noeuds, suite a la renumerotation */
  	int zi,zj;
  	TLARGE1 listeinter;
  
  	for (zi = 1; zi <= NOMBRE_NOEUDS; zi++) listeinter[zi] = zi;
  	for (zi = 1; zi <= NOMBRE_NOEUDS-1; zi++) 
  		{
    		for (zj = zi; zj <= NOMBRE_NOEUDS; zj++)
    			{
      			/* 
      			fixation Noeud[].new_numero contient les numeros des noeuds dans leur ordre d'apparition. 
      			*/
     			/*if (listeinter[zj]  == Noeud[zi].new_numero)*/
      			if (listeinter[zj]  == fixation[zi])
      				{
        			echangenoeuds(zi,zj);
        			listeinter[zj] = listeinter[zi];
        			/*listeinter[zi] = Noeud[zi].new_numero;*/
        			listeinter[zi] = fixation[zi];
      				}
    			}
  		}
	}



