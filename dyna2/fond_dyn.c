#define PRINCIPAL 0
#include "4c19.h"

void fond_dyn()
{
	
  	int zi; 
 	double amplitude_effort_frottement,modv,Vx,Vy,Vz,Vl;
 	double Fc,Bf,Bk,Fx,Fy,Fz;
 	
 	/*prise en compte des efforts et des raideurs dus au contact avec le fond*/
 	
 	for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++) 
	{
    		if ((whs[zi] == 1) && (wf[zi] < wh[zi]))
    		{                                             
      			/*printf("zi = %5d \n",zi);*/
      			wanoeud[zi]      += (wh[zi] - wf[zi]) * Bottom.raideur;
    			if (Structure.type_solver == 1)
			{
      				ze[zi][eca] += Bottom.raideur;
	  		}
			else if (Structure.type_solver == 2)
			{
				//affectation_pardiso(Bottom.raideur, zi, zi);
			}
    		}
    		if ((whs[zi] == -1) && (wf[zi] > wh[zi]))
    		{
      			wanoeud[zi]      += (wh[zi] - wf[zi]) * Bottom.raideur;

    			if (Structure.type_solver == 1)
			{
      				ze[zi][eca] += Bottom.raideur;
	  		}
			else if (Structure.type_solver == 2)
			{
				//affectation_pardiso( Bottom.raideur, zi, zi);
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
	   			whs en zi = 1 alors le noeud en zi frotte sur le fond grace a l'effort < 0
	   			dans le sens du courant*/ 
	   			amplitude_effort_frottement = Bottom.coef_frottement * (wh[3*zi] - wf[3*zi]) * Bottom.raideur;
	   			/*if ((Noeud[zi].type == 7) || (Noeud[zi].type == 8)) amplitude_effort_frottement = amplitude_effort_frottement * 0.1;*/
	   			wanoeud[3*zi-2] += amplitude_effort_frottement * cos(PI/180*Courant.direction);
	   			wanoeud[3*zi-1] += amplitude_effort_frottement * sin(PI/180*Courant.direction);
				//if (times > 2800.0) printf("Bottom.draga %lf ",Bottom.drag);
	   			Bottom.drag += amplitude_effort_frottement;
				//if (times > 2800.0) printf("Bottom.drag %lf \n",Bottom.drag);
	   			/*raideur liee a un deplacement vertical sur les efforts horizontaux 
	   			lies a la direction du courant*/

  	  			if (Structure.type_solver == 1)
				{
		      			ze[3*zi-2][eca+2] += Bottom.raideur * Bottom.coef_frottement * cos(PI/180*Courant.direction);
		      			ze[3*zi-2][eca+1] += Bottom.raideur * Bottom.coef_frottement * sin(PI/180*Courant.direction);
		  		}
				else if (Structure.type_solver == 2)
				{
					//affectation_pardiso( Bottom.raideur * Bottom.coef_frottement * cos(PI/180*Courant.direction), 3*zi-2, 3*zi);
					//affectation_pardiso( Bottom.raideur * Bottom.coef_frottement * sin(PI/180*Courant.direction), 3*zi-2, 3*zi+1);
				}
	      		}
	    	}
	}
 		
  	/*frottement des noeuds fixe sur le fond uniquement & si il y a vitesse des noeuds relativement au fond*/
	Vl = 0.005; /*speed limit over which there is a constant wearing, otherwise the wearing is proportionnal to the node speed modv*/
	Bf = Bottom.coef_frottement;
	Bk = Bottom.raideur;

	for (zi = 1; zi<= NOMBRE_NOEUDS; zi++)
  	{
  		/*whs : sens des limites du deplacement en X ,Y et Z pour chaque noeud. */
    		if ((whs[3*zi] == 1) && (wf[3*zi] < wh[3*zi])) /*node in contact with the bottom*/
    		{
	  		Vx = mvb[3*zi-2]; 		Vy = mvb[3*zi-1];  		Vz = mvb[3*zi-0];
	  		modv = sqrt(Vx*Vx + Vy*Vy + Vz*Vz);
	  		Fc = Bk * (wh[3*zi] - wf[3*zi]);
	  		
	  		if (modv > Vl)
	  		{
	  			Fx = - Fc * Bf * Vx / modv;
	  			Fy = - Fc * Bf * Vy / modv;
	  			Fz = - Fc * Bf * Vz / modv;
	   			wanoeud[3*zi-2] += Fx;
	   			wanoeud[3*zi-1] += Fy;
	   			wanoeud[3*zi-0] += Fz;
				//if (times > 2800.0) printf("Bottom.dragb %lf ",Bottom.drag);
	   			Bottom.drag += Fc * Bf;
				//if (times > 2800.0) printf("Bottom.drag %lf \n",Bottom.drag);
	   			Bottom.energy +=  Fc * Bf * sqrt(Vx*Vx + Vy*Vy + Vz*Vz) * Pascalcul;
	   			Bottom.power =  Bottom.energy/Pascalcul;

 	   			if (Structure.type_solver == 1)
				{
		   			ze[3*zi-2][eca+0] -= Bf*Fc/modv/modv/Pascalcul*(Vx*Vx/modv-modv);
	   				ze[3*zi-2][eca+1] -= Bf*Fc/modv/modv/Pascalcul*(Vx*Vy/modv);
	   				ze[3*zi-2][eca+2] -= Bf*Fc/modv/modv/Pascalcul*(Vx*Vz/modv)+ Bf*Bk /modv * Vx;

	   				ze[3*zi-1][eca-1] -= Bf*Fc/modv/modv/Pascalcul*(Vx*Vy/modv);
	   				ze[3*zi-1][eca+0] -= Bf*Fc/modv/modv/Pascalcul*(Vy*Vy/modv-modv);
	   				ze[3*zi-1][eca+1] -= Bf*Fc/modv/modv/Pascalcul*(Vy*Vz/modv)+ Bf*Bk /modv * Vy;

	   				ze[3*zi-0][eca-2] -= Bf*Fc/modv/modv/Pascalcul*(Vx*Vz/modv);
	   				ze[3*zi-0][eca-1] -= Bf*Fc/modv/modv/Pascalcul*(Vy*Vz/modv);
	   				ze[3*zi-0][eca-0] -= Bf*Fc/modv/modv/Pascalcul*(Vz*Vz/modv-modv)+ Bf*Bk /modv * Vz;
		  		}
				else if (Structure.type_solver == 2)
				{
					//affectation_pardiso( - Bf*Fc/modv/modv/Pascalcul*(Vx*Vx/modv-modv), 3*zi-2, 3*zi-2);
					//affectation_pardiso( - Bf*Fc/modv/modv/Pascalcul*(Vx*Vy/modv), 3*zi-2, 3*zi-1);
					//affectation_pardiso( - Bf*Fc/modv/modv/Pascalcul*(Vx*Vz/modv)+ Bf*Bk /modv * Vx, 3*zi-2, 3*zi);

					//affectation_pardiso( - Bf*Fc/modv/modv/Pascalcul*(Vx*Vy/modv), 3*zi-1, 3*zi-2);
					//affectation_pardiso( - Bf*Fc/modv/modv/Pascalcul*(Vy*Vy/modv-modv), 3*zi-1, 3*zi-1);
					//affectation_pardiso( - Bf*Fc/modv/modv/Pascalcul*(Vy*Vz/modv)+ Bf*Bk /modv * Vy, 3*zi-1, 3*zi);

					//affectation_pardiso( - Bf*Fc/modv/modv/Pascalcul*(Vx*Vz/modv), 3*zi, 3*zi-2);
					//affectation_pardiso( - Bf*Fc/modv/modv/Pascalcul*(Vy*Vz/modv), 3*zi, 3*zi-1);
					//affectation_pardiso( - Bf*Fc/modv/modv/Pascalcul*(Vz*Vz/modv-modv)+ Bf*Bk /modv * Vz, 3*zi, 3*zi);

				}
	      		}
	  		if ((modv > 0) && (modv <= Vl))
	  		{ 
	  			Fx = - Fc * Bf * Vx / Vl;
	  			Fy = - Fc * Bf * Vy / Vl;
	  			Fz = - Fc * Bf * Vz / Vl;
	   			wanoeud[3*zi-2] += Fx;
	   			wanoeud[3*zi-1] += Fy;
	   			wanoeud[3*zi-0] += Fz;
				//if (times > 2800.0) printf("Bottom.dragc %lf ",Bottom.drag);
	   			Bottom.drag += Fc * Bf * modv/Vl;
				//if (times > 2800.0) printf("Bottom.drag %lf \n",Bottom.drag);
 	   			if (Structure.type_solver == 1)
				{
	   				ze[3*zi-2][eca+0] += Bf/Vl*Fc/Pascalcul;
	   				ze[3*zi-2][eca+1] += 0.0;
	   				ze[3*zi-2][eca+2] += -Bf/Vl*Bk*Vx;

	   				ze[3*zi-1][eca-1] += 0.0;
	   				ze[3*zi-1][eca+0] += Bf/Vl*Fc/Pascalcul;
	   				ze[3*zi-1][eca+1] += -Bf/Vl*Bk*Vy;

	   				ze[3*zi-0][eca-2] += 0.0;
	   				ze[3*zi-0][eca-1] += 0.0;
	   				ze[3*zi-0][eca-0] += Bf/Vl*Fc/Pascalcul	-Bf/Vl*Bk*Vz;
				}
				else if (Structure.type_solver == 2)
				{
					//affectation_pardiso( Bf/Vl*Fc/Pascalcul , 3*zi-2, 3*zi-2);
					//affectation_pardiso( 0.0, 3*zi-2, 3*zi-1);
					//affectation_pardiso( -Bf/Vl*Bk*Vx, 3*zi-2, 3*zi);

					//affectation_pardiso(0.0, 3*zi-1, 3*zi-2);
					//affectation_pardiso(Bf/Vl*Fc/Pascalcul, 3*zi-1, 3*zi-1);
					//affectation_pardiso(-Bf/Vl*Bk*Vy, 3*zi-1, 3*zi);

					//affectation_pardiso(Bf/Vl*Fc/Pascalcul, 3*zi, 3*zi-2);
					//affectation_pardiso(0.0, 3*zi, 3*zi-1);
					//affectation_pardiso(-Bf/Vl*Bk*Vx, 3*zi, 3*zi);
				}
	      		}
      		}
    	}
}


