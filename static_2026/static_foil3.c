#define PRINCIPAL 0
#include "4c19.h"

void static_foil3()
	{
	/*calcul des efforts et des raideurs hydro du courant sur les foils*/
  	int zi,zj,ext1,ext2,typ_node;
  	double cube_vol,L_cube,modulevitesse,immersion;
  	double D_force,L_force;
   	/*prise en compte de l imersion*/
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  		{
  		if (TypeNoeud[Noeud[zi].type].foil3_surface > 0.0)
  			{
  			typ_node = Noeud[zi].type;
     			modulevitesse = 0.5 * RHO * Courant.vitesse * Courant.vitesse;
 			cube_vol = 0.0;
			for (zj = 1 ; zj<= NOMBRE_ELEMENTS ; zj++) 
			  	{
		    		ext1 = (int) yb(zj,3)/3;	//node extremity 1
		    		ext2 = (int) yb(zj,6)/3;	//node extremity 2
		    		if ((ext1 == zi) || (ext2 == zi))
		    			{
					cube_vol += Element[zj].lcube * Element[zj].lcube * Element[zj].lcube;	    			
					//printf("zj %d Noeud[%d].type %d foil3_surface %lf cube_vol %lf\n",zj,zi,typ_node,TypeNoeud[typ_node].foil3_surface,cube_vol);
					}
			  	}
			L_cube = pow((cube_vol),(1.0/3.0));
			D_force = TypeNoeud[typ_node].foil3_cd * TypeNoeud[typ_node].foil3_surface * modulevitesse;   			
			L_force = TypeNoeud[typ_node].foil3_cl * TypeNoeud[typ_node].foil3_surface * modulevitesse;   
			if ((0.0-wf[3*zi] <= L_cube) && (0.0+wf[3*zi] <= L_cube))
				{
				//floating foil
     				immersion = 0.0 - wf[3*zi];
				wanoeud[3*zi-2] += immersion/L_cube * D_force * cos(PI/180*Courant.direction);
	      			wanoeud[3*zi-1] += immersion/L_cube * D_force * sin(PI/180*Courant.direction);
				wanoeud[3*zi-2] -= immersion/L_cube * L_force * sin(PI/180*Courant.direction);
	      			wanoeud[3*zi-1] += immersion/L_cube * L_force * cos(PI/180*Courant.direction);
				if (Structure.type_solver == 1)
					{
					affectation_ze_rang(3*zi-2, 3*zi-0,  1/L_cube * D_force * cos(PI/180*Courant.direction));
					affectation_ze_rang(3*zi-1, 3*zi-0,  1/L_cube * D_force * sin(PI/180*Courant.direction));
					affectation_ze_rang(3*zi-2, 3*zi-0, -1/L_cube * L_force * sin(PI/180*Courant.direction));
					affectation_ze_rang(3*zi-1, 3*zi-0,  1/L_cube * L_force * cos(PI/180*Courant.direction));
					}
				else if (Structure.type_solver == 2)
					{
					}
				Structure.node_drag += 0.0;		
				//printf("zi %d foil3_surface %5.2lfm2 L_cube %5.2lfm ",zi,TypeNoeud[typ_node].foil3_surface,L_cube);
	 			//printf("D_force %9.0lfN L_force %9.0lfN\n",D_force,L_force);
				}			
			if (0.0-wf[3*zi] >= L_cube)
				{
				//immersed foil
     				immersion = 0.0 - wf[3*zi];
				wanoeud[3*zi-2] += D_force * cos(PI/180*Courant.direction);
	      			wanoeud[3*zi-1] += D_force * sin(PI/180*Courant.direction);
				wanoeud[3*zi-2] -= L_force * sin(PI/180*Courant.direction);
	      			wanoeud[3*zi-1] += L_force * cos(PI/180*Courant.direction);
				//printf("zi %d surf %5.2lfm2 L_cube %5.2lfm ",zi,TypeNoeud[typ_node].foil3_surface,L_cube);
	 			//printf("D_force %9.0lfN L_force %9.0lfN ",D_force,L_force);
	 			//printf("wa %9.0lfN %9.0lfN\n",wanoeud[3*zi-2],wanoeud[3*zi-1]);
				}			
			if (0.0+wf[3*zi] >= L_cube)
				{
				//emerged foil
				}			
			}
   		}
	}

