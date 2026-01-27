#define PRINCIPAL 0
#include "4c19.h"

void pesanteurSurface()
	/* Pesanteur des fils */
	{
  	int elem,zl;
  
	/* prise en compte des surfaces a maille losange.*/
  	for (elem = 1 ; elem <= NOMBRE_SURFACES ; elem++)
  		{
   	 	poidstriang(elem);
    
 		/* Mise a jour du vecteur effort global */
  	 	for ( zl = 1 ; zl <= 9 ; zl++ )
  	 		{ 
    	 		wasurf[yc(elem,zl)] += Pe[zl];
   	 		}
   		}
  	
	/* prise en compte des surfaces a maille hexagonale.*/
  	for (elem = 1 ; elem <= NOMBRE_SURF_HEXA ; elem++)
  		{
   	 	poidstri_hexa(elem);
    
 		/* Mise a jour du vecteur effort global */
 		/*on affecte le poids du triangle de preference aux noeuds mobiles*/
    		if ((wl[yc_hexa(elem,3)]!=99) || (wl[yc_hexa(elem,6)]!=99) || (wl[yc_hexa(elem,9)]!=99))
    			{
    			if((wl[yc_hexa(elem,3)]!=99) && (wl[yc_hexa(elem,6)]!=99) && (wl[yc_hexa(elem,9)]==99))
    				{
  	 			wasurf[yc_hexa(elem,9)] += 3.0 * Pe[9];
    				}
    			if((wl[yc_hexa(elem,3)]!=99) && (wl[yc_hexa(elem,6)]==99) && (wl[yc_hexa(elem,9)]!=99))
    				{
  	 			wasurf[yc_hexa(elem,6)] += 3.0 * Pe[6];
    				}
    			if((wl[yc_hexa(elem,3)]==99) && (wl[yc_hexa(elem,6)]!=99) && (wl[yc_hexa(elem,9)]!=99))
    				{
  	 			wasurf[yc_hexa(elem,3)] += 3.0 * Pe[3];
    				}
    			if((wl[yc_hexa(elem,3)]!=99) && (wl[yc_hexa(elem,6)]==99) && (wl[yc_hexa(elem,9)]==99))
    				{
  	 			wasurf[yc_hexa(elem,6)] += 1.5 * Pe[6];
  	 			wasurf[yc_hexa(elem,9)] += 1.5 * Pe[9];
    				}
    			if((wl[yc_hexa(elem,3)]==99) && (wl[yc_hexa(elem,6)]!=99) && (wl[yc_hexa(elem,9)]==99))
    				{
  	 			wasurf[yc_hexa(elem,3)] += 1.5 * Pe[3];
  	 			wasurf[yc_hexa(elem,9)] += 1.5 * Pe[9];
    				}
    			if((wl[yc_hexa(elem,3)]==99) && (wl[yc_hexa(elem,6)]==99) && (wl[yc_hexa(elem,9)]!=99))
    				{
  	 			wasurf[yc_hexa(elem,3)] += 1.5 * Pe[3];
  	 			wasurf[yc_hexa(elem,6)] += 1.5 * Pe[6];
    				}
    			if((wl[yc_hexa(elem,3)]!=99) && (wl[yc_hexa(elem,6)]!=99) && (wl[yc_hexa(elem,9)]!=99))
    				{
    				/*ici les 3 noeuds sont fixes aussi le poids n a t il pas d effet, malgre tout
    				par souci d uniformisation on affecte le poids*/
  	 			wasurf[yc_hexa(elem,3)] += Pe[3];
  	 			wasurf[yc_hexa(elem,6)] += Pe[6];
  	 			wasurf[yc_hexa(elem,9)] += Pe[9];
    				}
    			}
    		else
    			{
  	 		wasurf[yc_hexa(elem,3)] += Pe[3];
  	 		wasurf[yc_hexa(elem,6)] += Pe[6];
  	 		wasurf[yc_hexa(elem,9)] += Pe[9];
    			}
  	 	
  	 	
  	 	/*
  	 	for ( zl = 1 ; zl <= 9 ; zl++ )
  	 		{
    	 		wasurf[yc_hexa(elem,zl)] += Pe[zl];
   	 		}
   	 	*/
   		}
	}
