#define PRINCIPAL 0
#include "4c19.h"

void chaineeff3()
	{
	/*traite l effet du fond sur les noeuds*/
	
  	int zi;
  	double amplitude_effort_frottement;
  	
  	/*blocage des noeuds pour la premiere iteration
  	ils seront liberes ulterieurement si les efforts le permettemt*/
    	if ( nbiter == 1 )
    		{
  		for (zi = 1; zi<= 3*NOMBRE_NOEUDS; zi++)
  			{
  			/*whs : sens des limites du deplacement en X ,Y et Z pour chaque noeud. */
    			//if ( whs[zi]!=0 )
    			if ((whs[zi]==1) ||  (whs[zi]==-1))
    				{
         			/*wl[zi] = 0;*/
    				}
    			}
    		}
    		
  	/*liberation des noeuds de leur limite*/
  	for (zi = 1; zi<= 3*NOMBRE_NOEUDS; zi++)
  		{
  		/*whs : sens des limites du deplacement en X ,Y et Z pour chaque noeud. */
  
    		//if ( (whs[zi]!=0) && (wl[zi]==0) )
    		if ( (whs[zi]==1) || (whs[zi]==-10) )
    			{
	    		if (wl[zi]==0)
	    			{
	      			if ( ( wa[zi] > 0.0 ) && ( whs[zi] == 1) )
	      				{  
	 
	 				/*wl[zi] = 99 si la coordonnee zi du noeud est libre, 0 si elle est fixe */
	 				/*Si on a un noeud fixe en zi, un effort wa > 0 en zi et un sens des limites
	   				whs en zi = 1 alors le noeud en zi peut decoller vers le haut grace a l'effort >0
	   				donc le noeud en zi devient libre*/ 
	   
		 			wl[zi] = 99;
	      				}
	      			if ( ( wa[zi] < 0.0 ) && ( whs[zi] == -1) )
	      				{  
					/*Si on a un noeud fixe en zi, un effort wa < 0 en zi et un sens des limites
	   				whs en zi = -1 alors le noeud en zi peut decoller vers le bas grace a l'effort < 0
	   				donc le noeud en zi devient libre*/    
	      
					wl[zi] = 99;
	      				}
	    			}
	    		}
    		}
    		
  	/*frottement des noeuds fixe sur le fond uniquement & si il y a du courant*/
  	for (zi = 1; zi<= NOMBRE_NOEUDS; zi++)
  		{
  		/*whs : sens des limites du deplacement en X ,Y et Z pour chaque noeud. */
  
    		if ( (whs[3*zi]==1) || (whs[3*zi]==-1) )
    			{
	    		if ((wl[3*zi]==0) && (Courant.vitesse != 0.0) )
	    			{
	       			/*printf("zi %5d ", zi);
	       			printf("whs[3*zi] %5d ", whs[3*zi]);
	       			printf("wl[3*zi] %5d ", wl[3*zi]);
	       			printf("wa[3*zi] %15.4lf \n", wa[3*zi]);*/
	      			if ( ( wa[3*zi] < 0.0 ) && ( whs[3*zi] == 1) )
	      				{  
	 
	 				/*wl[zi] = 99 si la coordonnee zi du noeud est libre, 0 si elle est fixe */
	 				/*Si on a un noeud fixe en zi, un effort wa < 0 en zi et un sens des limites
	   				whs en zi = 1 alors le noeud en zi frotte sur la limite grace a l'effort < 0
	   				dans le sens du courant*/ 
	   				/*amplitude_effort_frottement = Bottom.coef_frottement * fabs(wa[3*zi]);
	   				wa[3*zi-2] += amplitude_effort_frottement * cos(PI/180*Courant.direction);
	   				wa[3*zi-1] += amplitude_effort_frottement * sin(PI/180*Courant.direction);*/
	      				}
	      			if ( ( wa[3*zi] > 0.0 ) && ( whs[3*zi] == -1) )
	      				{  
					/*Si on a un noeud fixe en zi, un effort wa < 0 en zi et un sens des limites
	   				whs en zi = -1 alors le noeud en zi peut decoller vers le bas grace a l'effort < 0
	   				donc le noeud en zi devient libre*/    
	   				/*amplitude_effort_frottement = Bottom.coef_frottement * fabs(wa[3*zi]);
	   				wa[3*zi-2] += amplitude_effort_frottement * cos(PI/180*Courant.direction);
	   				wa[3*zi-1] += amplitude_effort_frottement * sin(PI/180*Courant.direction);*/
	      				}
	    			}
	    		}
    		}
	}

