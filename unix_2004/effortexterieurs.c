#define PRINCIPAL 0
#include "4c19.h"

void effortexterieurs()
	{
	
  	/* prise en compte des efforts exterieurs agissant directement sur les noeuds*/
  	
  	int zi;
  	
    	/*printf("node_drag avant %lf\n",Structure.node_drag);*/
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++)
  		{ 
    		wanoeud[3*zi-2] += Noeud[zi].fextx;
    		wanoeud[3*zi-1] += Noeud[zi].fexty;
    		wanoeud[3*zi-0] += Noeud[zi].fextz;
		//Structure.node_drag += Noeud[zi].fextx;
    		/*printf("zi %d  	fextx %lf node_drag %lf\n",zi,Noeud[zi].fextx,Structure.node_drag);*/
    		}
    	/*printf("node_drag apres %lf\n",Structure.node_drag);
    	exit(0);*/
	}


