#define PRINCIPAL 0
#include "4c19.h"

void traineevent1()
{
	/*calcul des efforts et des raideurs de trainee du vent sur les noeuds*/
  	int zi;
  	double modulevitesse,tirant_air;
  	
  	/*Vent.vitesse = 0.0;
  	Vent.direction = 270.0;*/


  	/*prise en compte du tirant d air*/
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
	{
    		modulevitesse = 0.5 * RHO_AIR * Vent.vitesse * Vent.vitesse;
    		if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] <= 0.0) && (wf[3*zi] + Noeud[zi].lonz >= 0.0))
		{
      			/* flotteur flottant */
     			tirant_air = wf[3*zi] + Noeud[zi].lonz - 0,0;
      			wanoeud[3*zi-2] += tirant_air * Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Vent.direction) * modulevitesse;
      			wanoeud[3*zi-1] += tirant_air * Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Vent.direction) * modulevitesse;
			if (Structure.type_solver == 1)
			{
      				ze[3*zi-2][eca + 2] -=         Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Vent.direction) * modulevitesse;
      				ze[3*zi-1][eca + 1] -=         Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Vent.direction) * modulevitesse;
			}
			else if (Structure.type_solver == 2)
			{
				affectation_pardiso(-Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Vent.direction) * modulevitesse, 3*zi-2, 3*zi);
				affectation_pardiso(-Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Vent.direction) * modulevitesse, 3*zi-1, 3*zi);
			}
		}
    
    		if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] + Noeud[zi].lonz < 0.0))
		{
      			/* flotteur inonde */
		}
    
    		if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] > 0.0))
		{
      			/* flotteur exonde */
      			wanoeud[3*zi-2] += Noeud[zi].lonz* Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Vent.direction) * modulevitesse;
      			wanoeud[3*zi-1] += Noeud[zi].lonz* Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Vent.direction) * modulevitesse;
		}
    		if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] >= 0.0) && (wf[3*zi] + Noeud[zi].lonz <= 0.0))
		{
      			/* lest flottant */
      			tirant_air = wf[3*zi] - 0.0;
     		 	wanoeud[3*zi-2] += tirant_air * Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Vent.direction) * modulevitesse;
      			wanoeud[3*zi-1] += tirant_air * Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Vent.direction) * modulevitesse;
			if (Structure.type_solver == 1)
			{
      				ze[3*zi-2][eca + 2] -=         Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Vent.direction) * modulevitesse;
      				ze[3*zi-1][eca + 1] -=         Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Vent.direction) * modulevitesse;
			}
			else if (Structure.type_solver == 2)
			{
				affectation_pardiso(-Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Vent.direction) * modulevitesse, 3*zi-2, 3*zi);
				affectation_pardiso(-Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Vent.direction) * modulevitesse, 3*zi-1, 3*zi);
			}
		}
    		if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] < 0.0))
		{
      			/* lest inonde */
		}
    		if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] + Noeud[zi].lonz > 0.0))
		{
      			/* lest exonde */
      			wanoeud[3*zi-2] -= Noeud[zi].lonz* Noeud[zi].cdx*Noeud[zi].lony * cos(PI/180*Vent.direction) * modulevitesse;
      			wanoeud[3*zi-1] -= Noeud[zi].lonz* Noeud[zi].cdy*Noeud[zi].lonx * sin(PI/180*Vent.direction) * modulevitesse;
		}
	}
}

