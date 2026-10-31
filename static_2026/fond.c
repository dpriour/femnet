#define PRINCIPAL 0
#include "4c19.h"

void fond()
{
	
  	int zi; 
 	double amplitude_effort_frottement;
 	
 	/*prise en compte des efforts et des raideurs dus au contact avec le fond
 	uniquement les efforts par noeds si ils sont sous la limite*/
 	
  	for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++) 
  	{
    		if ((whs[zi] == 1) && (wf[zi] < wh[zi]))
    		{                                             
      			/*printf("zi = %5d Bottom.raideur %lf wh %lf wf %lf FV %lf\n",zi,Bottom.raideur,wh[zi],wf[zi],(wh[zi] - wf[zi]) * Bottom.raideur);*/
      			wanoeud[zi]      += (wh[zi] - wf[zi]) * Bottom.raideur;
  			if (Structure.type_solver == 1)
			{
      				ze[zi][eca] +=                     Bottom.raideur;
    			}
			else if (Structure.type_solver == 2)
		      	{
				affectation_pardiso(Bottom.raideur, zi, zi);
		      	}	
    		}
    		if ((whs[zi] == -1) && (wf[zi] > wh[zi]))
    		{
      			wanoeud[zi]      += (wh[zi] - wf[zi]) * Bottom.raideur;
  			if (Structure.type_solver == 1)
			{
      				ze[zi][eca] +=                     Bottom.raideur;
    			}
			else if (Structure.type_solver == 2)
		      	{
				affectation_pardiso(Bottom.raideur, zi, zi);
		      	}	
    		}
  	}

  	/*uniquement pour le fond et le plafond horizontal pour l instant !!!!!!!!!!!!!!!*/
  	/*for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  		{
    		if ((whs[3*zi] == 1) && (wf[3*zi] < wh[3*zi]))
    			{*/    
    			/*fond*/                                         
      			/*wanoeud[3*zi]      += (wh[3*zi] - wf[3*zi]) * Bottom.raideur;
      			ze[3*zi][eca] +=                         Bottom.raideur;
    			}
    		if ((whs[3*zi] == -1) && (wf[3*zi] > wh[3*zi]))
    			{*/
    			/*plafond*/
      			/*wanoeud[3*zi]      += (wh[3*zi] - wf[3*zi]) * Bottom.raideur;
      			ze[3*zi][eca] +=                         Bottom.raideur;
    			}
  		}*/
  		
  	/*frottement des noeuds fixe sur le fond uniquement & si il y a du courant*/
  	if (Bottom.moving == 1)
	{
	  	for (zi = 1; zi<= NOMBRE_NOEUDS; zi++)
		{
	  		/*whs : sens des limites du deplacement en X ,Y et Z pour chaque noeud. */
	  
	    		if ((whs[3*zi] == 1) && (wf[3*zi] < wh[3*zi]) && (Courant.vitesse != 0.0))
	    			{
	 			/*Si on a un noeud sous le fond donc un effort wanoeud < 0 en zi et un sens des limites
	   			whs en zi = 1 alors le noeud en zi frotte sur le fond grace a l'effort < 0 dans le sens du courant*/ 
	   			amplitude_effort_frottement = Bottom.coef_frottement * (wh[3*zi] - wf[3*zi]) * Bottom.raideur;
	   			/*if ((Noeud[zi].type == 7) || (Noeud[zi].type == 8)) amplitude_effort_frottement = amplitude_effort_frottement * 0.1;*/
	   			wanoeud[3*zi-2] += amplitude_effort_frottement * cos(PI/180*Courant.direction);
	   			wanoeud[3*zi-1] += amplitude_effort_frottement * sin(PI/180*Courant.direction);
	   			Bottom.drag += amplitude_effort_frottement;
				//printf("amplitude_effort_frottement %lf \n",amplitude_effort_frottement);
	   			/*raideur liee a un deplacement vertical sur les efforts horizontaux 
	   			lies a la direction du courant*/
				if (Structure.type_solver == 1)
				{
	      				ze[3*zi-2][eca+2] += Bottom.raideur * Bottom.coef_frottement * cos(PI/180*Courant.direction);
		      			ze[3*zi-2][eca+1] += Bottom.raideur * Bottom.coef_frottement * sin(PI/180*Courant.direction);
    				}
				else if (Structure.type_solver == 2)
			      	{
					affectation_pardiso(Bottom.raideur * Bottom.coef_frottement * cos(PI/180*Courant.direction), 3*zi-2, 3*zi);
					affectation_pardiso(Bottom.raideur * Bottom.coef_frottement * sin(PI/180*Courant.direction), 3*zi-2, 3*zi-1);
			      	}
			}
		}
	}
}


