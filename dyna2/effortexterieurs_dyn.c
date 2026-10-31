#define PRINCIPAL 0
#include "4c19.h"

void effortexterieurs_dyn()
	{
	
  	/* prise en compte des efforts exterieurs agissant directement sur les noeuds*/
  	
  	int zi;
  	double drag_tmp[4],depl_tmp[4];
  	
    	/*printf("node_drag avant %lf\n",Structure.node_drag);*/
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++)
  		{ 
    		wanoeud[3*zi-2] += Noeud[zi].fextx;
    		wanoeud[3*zi-1] += Noeud[zi].fexty;
    		wanoeud[3*zi-0] += Noeud[zi].fextz;
		Structure.node_drag += Noeud[zi].fextx;
    		/*printf("zi %d  	fextx %lf node_drag %lf\n",zi,Noeud[zi].fextx,Structure.node_drag);*/
		drag_tmp[1] = Noeud[zi].fextx;		drag_tmp[2] = Noeud[zi].fexty;		drag_tmp[3] = Noeud[zi].fextz; 	//drag (N)
		depl_tmp[1] = wf[3*zi-2] - wf1[3*zi-2];	depl_tmp[2] = wf[3*zi-1] - wf1[3*zi-1];	depl_tmp[3] = wf[3*zi-0] - wf1[3*zi-0];	//deplacement (m)	
		Structure.node_energy -= produit_scal(drag_tmp,depl_tmp);
		Structure.node_power = Structure.node_energy/Pascalcul;
    		}
    	/*printf("node_drag apres %lf\n",Structure.node_drag);
    	exit(0);*/
	}


