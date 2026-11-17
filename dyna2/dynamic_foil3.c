#define PRINCIPAL 0
#include "4c19.h"

void dynamic_foil3()
	{
	/*calcul des efforts et des raideurs hydro du courant sur les foils*/
  	int zi,zj,ext1,ext2,typ_node;
  	double cube_vol,L_cube,immersion;
  	double D_force,L_force;
  	double vx,vy,vz,vH;
   	/*prise en compte de l imersion*/
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  		{
  		if (TypeNoeud[Noeud[zi].type].foil3_surface > 0.0)
  			{
  			vx = -mvb[3*zi-2]+mvh[3*zi-2];	//water speed along x at node zi
  			vy = -mvb[3*zi-1]+mvh[3*zi-1];	//water speed along y at node zi
  			vz = -mvb[3*zi-0]+mvh[3*zi-0];	//water speed along z at node zi
	 		//printf("mvb %9.4lf  %9.4lf  %9.4lf ",mvb[3*zi-2],mvb[3*zi-1],mvb[3*zi-0]);
  			vH = sqrt(vx*vx+vy*vy);
  			typ_node = Noeud[zi].type;
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
			D_force = 0.5 * RHO * TypeNoeud[typ_node].foil3_cd * TypeNoeud[typ_node].foil3_surface * vH * vH;   			
			L_force = 0.5 * RHO * TypeNoeud[typ_node].foil3_cl * TypeNoeud[typ_node].foil3_surface * vH * vH;   
			if ((0.0-wf[3*zi] <= L_cube) && (0.0+wf[3*zi] <= L_cube) && (vH>0.0))
				{
				//floating foil
     				immersion = 0.0 - wf[3*zi];
				wanoeud[3*zi-2] += immersion/L_cube * D_force * vx/vH;
	      			wanoeud[3*zi-1] += immersion/L_cube * D_force * vy/vH;
				wanoeud[3*zi-2] -= immersion/L_cube * L_force * vy/vH;
	      			wanoeud[3*zi-1] += immersion/L_cube * L_force * vx/vH;
				if (Structure.type_solver == 1)
					{
					affectation_ze_rang(3*zi-2, 3*zi-0,  1/L_cube * D_force * vx/vH);
					affectation_ze_rang(3*zi-1, 3*zi-0,  1/L_cube * D_force * vy/vH);
					affectation_ze_rang(3*zi-2, 3*zi-0, -1/L_cube * L_force * vy/vH);
					affectation_ze_rang(3*zi-1, 3*zi-0,  1/L_cube * L_force * vx/vH);
					}
				else if (Structure.type_solver == 2)
					{
					}
				Structure.node_drag += 0.0;		
				//printf("zi %d foil3_surface %5.2lfm2 L_cube %5.2lfm ",zi,TypeNoeud[typ_node].foil3_surface,L_cube);
	 			//printf("D_force %9.0lfN L_force %9.0lfN\n",D_force,L_force);
				}			
			if ((0.0-wf[3*zi] >= L_cube) && (vH>0.0))
				{
				//immersed foil
				wanoeud[3*zi-2] += D_force * vx/vH;
	      			wanoeud[3*zi-1] += D_force * vy/vH;
				wanoeud[3*zi-2] -= L_force * vy/vH;
	      			wanoeud[3*zi-1] += L_force * vx/vH;
				//printf("zi %d surf %5.2lfm2 L_cube %5.2lfm ",zi,TypeNoeud[typ_node].foil3_surface,L_cube);
	 			//printf("D_force %9.0lfN L_force %9.0lfN ",D_force,L_force);
	 			//printf("vx %9.4lf vy %9.4lf vH %9.4lf ",vx,vy,vH);
	 			//printf("wa %9.0lfN %9.0lfN\n",wanoeud[3*zi-2],wanoeud[3*zi-1]);
				}			
			if ((0.0+wf[3*zi] >= L_cube) && (vH>0.0))
				{
				//emerged foil
				}			
			}
   		}
	}

