#define PRINCIPAL 0
#include "4c19.h"

void traineecourant2()
	{
	/*calcul des efforts et des raideurs de trainee du courant sur les noeuds*/
  	int zi;
  	double modulevitesse,immersion;
  
  	/*prise en compte de l imersion*/
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  		{
    		modulevitesse = 0.5 * RHO * Courant.vitesse * Courant.vitesse;
    		if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] <= 0.0) && (wf[3*zi] + Noeud[zi].lonz >= 0.0))
    			{
      			/* flotteur flottant */
     			immersion = 0.0 - wf[3*zi];
      			wanoeud[3*zi-2] += immersion * Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse;
      			wanoeud[3*zi-1] += immersion * Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Courant.direction) * modulevitesse;
			if (Structure.type_solver == 1)
			{
      				//ze[3*zi-2][eca + 2] +=         Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse;
      				//ze[3*zi-1][eca + 1] +=         Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Courant.direction) * modulevitesse;
				affectation_ze_rang(3*zi-2, 3*zi-0, Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse);
				affectation_ze_rang(3*zi-1, 3*zi-0, Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Courant.direction) * modulevitesse);
			}
			else if (Structure.type_solver == 2)
			{
				affectation_pardiso(Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse, 3*zi-2, 3*zi);
				affectation_pardiso(Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Courant.direction) * modulevitesse, 3*zi-1, 3*zi);
			}
			Structure.node_drag = Structure.node_drag +  immersion * Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse;		
			}
    
    		if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] + Noeud[zi].lonz < 0.0))
    			{
      			/* flotteur inonde */
      			wanoeud[3*zi-2] += Noeud[zi].lonz* Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse;
      			wanoeud[3*zi-1] += Noeud[zi].lonz* Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Courant.direction) * modulevitesse;
			Structure.node_drag = Structure.node_drag + Noeud[zi].lonz* Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse;		
			/*printf("node drag %i %lf \n",zi,Noeud[zi].lonz* Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse);*/
    			}
    
    		if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] > 0.0))
    			{
      			/* flotteur exonde */
    			}
    		if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] >= 0.0) && (wf[3*zi] + Noeud[zi].lonz <= 0.0))
    			{
      			/* lest flottant */
      			immersion = - Noeud[zi].lonz - wf[3*zi] + 0.0;
     		 	wanoeud[3*zi-2] += immersion * Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse;
      			wanoeud[3*zi-1] += immersion * Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Courant.direction) * modulevitesse;
			if (Structure.type_solver == 1)
			{
      				//ze[3*zi-2][eca + 2] +=         Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse;
      				//ze[3*zi-1][eca + 1] +=         Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Courant.direction) * modulevitesse;
				affectation_ze_rang(3*zi-2, 3*zi-0, Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse);
				affectation_ze_rang(3*zi-1, 3*zi-0, Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Courant.direction) * modulevitesse);
			}
			else if (Structure.type_solver == 2)
			{
				affectation_pardiso(Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse, 3*zi-2, 3*zi);
				affectation_pardiso(Noeud[zi].cdy*Noeud[zi].lony * sin(PI/180*Courant.direction) * modulevitesse, 3*zi-1, 3*zi);
			}
			Structure.node_drag = Structure.node_drag + immersion * Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse;    			
			}
    		if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] < 0.0))
    			{
      			/* lest inonde */
      			wanoeud[3*zi-2] -= Noeud[zi].lonz* Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse;
      			wanoeud[3*zi-1] -= Noeud[zi].lonz* Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Courant.direction) * modulevitesse;
			Structure.node_drag = Structure.node_drag - Noeud[zi].lonz* Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Courant.direction) * modulevitesse; 
 			}
    		if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] + Noeud[zi].lonz > 0.0))
    			{
      			/* lest exonde */
    			}
  		}
	}

