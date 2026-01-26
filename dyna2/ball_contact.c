#include "4c19.h"

void ball_contact()
	{
  	int zi,zj,z1,z2,no[7],zc,zd,zu;
  	double dist,vp[7],r1,r2,rad1,rad2,sti1,sti2,denom,eff,veff[7],vv,uu;
  	double x1_x2p[7],y1_y2p[7],z1_z2p[7],x2_x1p[7],y2_y1p[7],z2_z1p[7];
  	double tmpa[7],tmpb[7],tmpc[7],tmpd[7],tmpe[7],vvp[7],uup[7],distp[7];
  	double f1xp[7],f1yp[7],f1zp[7],f2xp[7],f2yp[7],f2zp[7];
  	double F1xp[7],F1yp[7],F1zp[7],F2xp[7],F2yp[7],F2zp[7],delta_x,Veff[7];
  	double X2_x1,Y2_y1,Z2_z1,X1_x2,Y1_y2,Z1_z2,Dist;
  	double X1_x2p[7],Y1_y2p[7],Z1_z2p[7],X2_x1p[7],Y2_y1p[7],Z2_z1p[7],Distp[7];
  	
  	/* pour chaque ball prendre en compte le contact avec les autres*/
   	for (zi = 1 ; zi<= Ball.nb-1; zi++) 
  		{
  		z1 = Ball.noeud[zi];
		vp[1] = wf [3*z1-2];	vp[2] = wf [3*z1-1];	vp[3] = wf [3*z1-0];
   		for (zj = zi+1 ; zj<= Ball.nb; zj++) 
  			{
  			z2 = Ball.noeud[zj];
			vp[4] = wf [3*z2-2];	vp[5] = wf [3*z2-1];	vp[6] = wf [3*z2-0];
      			/*TEST_debut
			delta_x = 0.0000001;
			for( zu = 0 ; zu <= 6 ; zu++ )
      				{
      				if (zu == 1) vp[ 1] = vp[ 1] + delta_x;
      				if (zu == 2) vp[ 2] = vp[ 2] + delta_x;
      				if (zu == 3) vp[ 3] = vp[ 3] + delta_x;
      				if (zu == 4) vp[ 4] = vp[ 4] + delta_x;
      				if (zu == 5) vp[ 5] = vp[ 5] + delta_x;
      				if (zu == 6) vp[ 6] = vp[ 6] + delta_x;
      			TEST_fin*/
			dist = sqrt((vp[4]-vp[1])*(vp[4]-vp[1])+(vp[5]-vp[2])*(vp[5]-vp[2])+(vp[6]-vp[3])*(vp[6]-vp[3]));
      				
			if ((dist < (Ball.radius[zi]+Ball.radius[zj])) && (times >= Ball.birth_time[zi]) && (times >= Ball.birth_time[zj]))
				{
				/*contact*/
				rad1 = Ball.radius[zi];		rad2 = Ball.radius[zj];
				sti1 = Ball.stiffness[zi];	sti2 = Ball.stiffness[zj];
				denom = sti2*rad1+sti1*rad2;
				r1 = (rad1*rad2*(sti1-sti2)+dist*sti2*rad1)/denom;
				r2 = (rad2*rad1*(sti2-sti1)+dist*sti1*rad2)/denom;
				eff = sti1*sti2*(rad1+rad2-dist)/denom;
				veff[1] = eff * (vp[1]-vp[4])/dist;
				veff[2] = eff * (vp[2]-vp[5])/dist;
				veff[3] = eff * (vp[3]-vp[6])/dist;
				veff[4] = eff * (vp[4]-vp[1])/dist;
				veff[5] = eff * (vp[5]-vp[2])/dist;
				veff[6] = eff * (vp[6]-vp[3])/dist;
				
				wanoeud[3*z1-2] += veff[1];	wanoeud[3*z1-1] += veff[2];	wanoeud[3*z1-0] += veff[3];
		      		wanoeud[3*z2-2] += veff[4];	wanoeud[3*z2-1] += veff[5];	wanoeud[3*z2-0] += veff[6];
		      			
				x1_x2p[1] =  1.0;	x1_x2p[2] =  0.0;	x1_x2p[3] =  0.0;
				x1_x2p[4] = -1.0;	x1_x2p[5] =  0.0;	x1_x2p[6] =  0.0;
				y1_y2p[1] =  0.0;	y1_y2p[2] =  1.0;	y1_y2p[3] =  0.0;
				y1_y2p[4] =  0.0;	y1_y2p[5] = -1.0;	y1_y2p[6] =  0.0;
				z1_z2p[1] =  0.0;	z1_z2p[2] =  0.0;	z1_z2p[3] =  1.0;
				z1_z2p[4] =  0.0;	z1_z2p[5] =  0.0;	z1_z2p[6] = -1.0;
				x2_x1p[1] = -1.0;	x2_x1p[2] =  0.0;	x2_x1p[3] =  0.0;
				x2_x1p[4] =  1.0;	x2_x1p[5] =  0.0;	x2_x1p[6] =  0.0;
				y2_y1p[1] =  0.0;	y2_y1p[2] = -1.0;	y2_y1p[3] =  0.0;
				y2_y1p[4] =  0.0;	y2_y1p[5] =  1.0;	y2_y1p[6] =  0.0;
				z2_z1p[1] =  0.0;	z2_z1p[2] =  0.0;	z2_z1p[3] = -1.0;
				z2_z1p[4] =  0.0;	z2_z1p[5] =  0.0;	z2_z1p[6] =  1.0;
				
				/*derivative of dist*/
				produit_scal_vect_6(vp[4]-vp[1], x2_x1p, tmpa);
				produit_scal_vect_6(vp[5]-vp[2], y2_y1p, tmpb);
				produit_scal_vect_6(vp[6]-vp[3], z2_z1p, tmpc);
				add_vect_6(tmpa, tmpb, tmpd);
				add_vect_6(tmpd, tmpc, tmpe);
				produit_scal_vect_6(1.0/dist, tmpe, distp);
				
				/*tous les efforts sont de la forme uu/vv leur derivees sont donc de la
				la forme (up*vv-uu*vp)/vv/vv
				vv est identique pour tous les efforts on le calcul qu'une fois
				ainsi que sa derivee*/
				vv = dist*denom/(sti1*sti2);
				/*derivative of vv*/
				produit_scal_vect_6(denom/(sti1*sti2)  ,  distp, vvp);
					
				/*derivative of f1x*/
				uu = (rad1+rad2-dist)*(vp[1]-vp[4]);
				/*derivative of uu*/
				produit_scal_vect_6(rad1+rad2-dist	, x1_x2p	, tmpa);
				produit_scal_vect_6(-vp[1]+vp[4]	, distp		, tmpb);
				add_vect_6(tmpa, tmpb, uup);
				/*derivative of f1x = (uup*vv-uu*vvp) / vv2*/
				produit_scal_vect_6( vv, uup, tmpa);	produit_scal_vect_6(-uu, vvp, tmpb);
				add_vect_6(tmpa, tmpb, tmpc);		produit_scal_vect_6(1.0/vv/vv, tmpc, f1xp);
					
				/*derivative of f1y*/
				uu = (rad1+rad2-dist)*(vp[2]-vp[5]);
				/*derivative of uu*/
				produit_scal_vect_6(rad1+rad2-dist	, y1_y2p	, tmpa);
				produit_scal_vect_6(-vp[2]+vp[5]	, distp		, tmpb);
				add_vect_6(tmpa, tmpb, uup);
				/*derivative of f1y = (uup*vv-uu*vvp) / vv2*/
				produit_scal_vect_6( vv, uup, tmpa);	produit_scal_vect_6(-uu, vvp, tmpb);
				add_vect_6(tmpa, tmpb, tmpc);		produit_scal_vect_6(1.0/vv/vv, tmpc, f1yp);
					
				/*derivative of f1z*/
				uu = (rad1+rad2-dist)*(vp[3]-vp[6]);
				/*derivative of uu*/
				produit_scal_vect_6(rad1+rad2-dist	, z1_z2p	, tmpa);
				produit_scal_vect_6(-vp[3]+vp[6]	, distp		, tmpb);
				add_vect_6(tmpa, tmpb, uup);
				/*derivative of f1z = (uup*vv-uu*vvp) / vv2*/
				produit_scal_vect_6( vv, uup, tmpa);	produit_scal_vect_6(-uu, vvp, tmpb);
				add_vect_6(tmpa, tmpb, tmpc);		produit_scal_vect_6(1.0/vv/vv, tmpc, f1zp);
					
				/*derivative of f2x*/
				uu = (rad1+rad2-dist)*(vp[4]-vp[1]);
				/*derivative of uu*/
				produit_scal_vect_6(rad1+rad2-dist	, x2_x1p	, tmpa);
				produit_scal_vect_6(-vp[4]+vp[1]	, distp		, tmpb);
				add_vect_6(tmpa, tmpb, uup);
				/*derivative of f2x = (uup*vv-uu*vvp) / vv2*/
				produit_scal_vect_6( vv, uup, tmpa);	produit_scal_vect_6(-uu, vvp, tmpb);
				add_vect_6(tmpa, tmpb, tmpc);		produit_scal_vect_6(1.0/vv/vv, tmpc, f2xp);
					
				/*derivative of f2y*/
				uu = (rad1+rad2-dist)*(vp[5]-vp[2]);
				/*derivative of uu*/
				produit_scal_vect_6(rad1+rad2-dist	, y2_y1p	, tmpa);
				produit_scal_vect_6(-vp[5]+vp[2]	, distp		, tmpb);
				add_vect_6(tmpa, tmpb, uup);
				/*derivative of f2y = (uup*vv-uu*vvp) / vv2*/
				produit_scal_vect_6( vv, uup, tmpa);	produit_scal_vect_6(-uu, vvp, tmpb);
				add_vect_6(tmpa, tmpb, tmpc);		produit_scal_vect_6(1.0/vv/vv, tmpc, f2yp);
					
				/*derivative of f2z*/
				uu = (rad1+rad2-dist)*(vp[6]-vp[3]);
				/*derivative of uu*/
				produit_scal_vect_6(rad1+rad2-dist	, z2_z1p	, tmpa);
				produit_scal_vect_6(-vp[6]+vp[3]	, distp		, tmpb);
				add_vect_6(tmpa, tmpb, uup);
				/*derivative of f2z = (uup*vv-uu*vvp) / vv2*/
				produit_scal_vect_6( vv, uup, tmpa);	produit_scal_vect_6(-uu, vvp, tmpb);
				add_vect_6(tmpa, tmpb, tmpc);		produit_scal_vect_6(1.0/vv/vv, tmpc, f2zp);
					
				no[ 1] = 3*z1-2;	no[ 2] = 3*z1-1;	no[ 3] = 3*z1-0;
				no[ 4] = 3*z2-2;	no[ 5] = 3*z2-1;	no[ 6] = 3*z2-0;

				if (Structure.type_solver == 1)
				{				
   					for (zc = 1 ; zc<= 6; zc++) 
  					{
						ze[3*z1-2][eca-(3*z1-2)+no[zc]] -= f1xp[zc];
						ze[3*z1-1][eca-(3*z1-1)+no[zc]] -= f1yp[zc];
						ze[3*z1-0][eca-(3*z1-0)+no[zc]] -= f1zp[zc];
						ze[3*z2-2][eca-(3*z2-2)+no[zc]] -= f2xp[zc];
						ze[3*z2-1][eca-(3*z2-1)+no[zc]] -= f2yp[zc];
						ze[3*z2-0][eca-(3*z2-0)+no[zc]] -= f2zp[zc];
					}
				}
				else if (Structure.type_solver == 2)
				{
			   		for (zc = 1 ; zc<= 6; zc++) 
  					{
						//affectation_pardiso(-f1xp[zc], 3*z1-2, no[zc]);
						//affectation_pardiso(-f1yp[zc], 3*z1-1, no[zc]);
						//affectation_pardiso(-f1zp[zc], 3*z1-0, no[zc]);

						//affectation_pardiso(-f2xp[zc], 3*z2-2, no[zc]);
						//affectation_pardiso(-f2yp[zc], 3*z2-1, no[zc]);
						//affectation_pardiso(-f2zp[zc], 3*z2-0, no[zc]);
					}
				}

   				for (zc = 1 ; zc<= 6; zc++) 
  					{
   					for (zd = 1 ; zd<= 6; zd++) 
  						{
  						if (rang[1][no[zc]] < no[zd])	rang[1][no[zc]] = no[zd];
  						if (rang[2][no[zc]] < no[zd])	rang[2][no[zc]] = no[zd];
  						if (rang[3][no[zc]] > no[zd])	rang[3][no[zc]] = no[zd];
  						if (rang[4][no[zc]] > no[zd])	rang[4][no[zc]] = no[zd];
  						}
  					}
				}
      			/*TEST_debut
      				if (zu == 0)
      					{
					Veff[1] = veff[1];	Veff[2] = veff[2];	Veff[3] = veff[3];
					Veff[4] = veff[4];	Veff[5] = veff[5];	Veff[6] = veff[6];
					X2_x1 = vp[4]-vp[1];	Y2_y1 = vp[5]-vp[2];	Z2_z1 = vp[6]-vp[3];
					X1_x2 = vp[1]-vp[4];	Y1_y2 = vp[2]-vp[5];	Z1_z2 = vp[3]-vp[6];
					Dist = dist;
					}
				if ((zu > 0) && (zu < 7)) 
					{
					F1xp[zu]	= (veff[1] - Veff[1]) 		/ delta_x;
					F1yp[zu]	= (veff[2] - Veff[2]) 		/ delta_x;
					F1zp[zu]	= (veff[3] - Veff[3]) 		/ delta_x;
					F2xp[zu]	= (veff[4] - Veff[4]) 		/ delta_x;
					F2yp[zu]	= (veff[5] - Veff[5]) 		/ delta_x;
					F2zp[zu]	= (veff[6] - Veff[6]) 		/ delta_x;
					X2_x1p[zu]	= ((vp[4]-vp[1]) - X2_x1) 	/ delta_x;
					Y2_y1p[zu]	= ((vp[5]-vp[2]) - Y2_y1) 	/ delta_x;
					Z2_z1p[zu]	= ((vp[6]-vp[3]) - Z2_z1) 	/ delta_x;
					X1_x2p[zu]	= ((vp[1]-vp[4]) - X1_x2) 	/ delta_x;
					Y1_y2p[zu]	= ((vp[2]-vp[5]) - Y1_y2) 	/ delta_x;
					Z1_z2p[zu]	= ((vp[3]-vp[6]) - Z1_z2) 	/ delta_x;
					Distp[zu]	= (dist - Dist) 		/ delta_x;
					}
      				if (zu == 1) vp[ 1] = vp[ 1] - delta_x;
      				if (zu == 2) vp[ 2] = vp[ 2] - delta_x;
      				if (zu == 3) vp[ 3] = vp[ 3] - delta_x;
      				if (zu == 4) vp[ 4] = vp[ 4] - delta_x;
      				if (zu == 5) vp[ 5] = vp[ 5] - delta_x;
      				if (zu == 6) vp[ 6] = vp[ 6] - delta_x;
      				printf("zu = %4d  ",zu);	printf("dist %lf ",dist);	printf("veff =");	imprvectreel(6, veff);
				}
			printf("x2_x1p =");	imprvectreel(6, x2_x1p);	printf("X2_x1p =");	imprvectreel(6, X2_x1p);
			printf("y2_y1p =");	imprvectreel(6, y2_y1p);	printf("Y2_y1p =");	imprvectreel(6, Y2_y1p);
			printf("z2_z1p =");	imprvectreel(6, z2_z1p);	printf("Z2_z1p =");	imprvectreel(6, Z2_z1p);
			printf("x1_x2p =");	imprvectreel(6, x1_x2p);	printf("X1_x2p =");	imprvectreel(6, X1_x2p);
			printf("y1_y2p =");	imprvectreel(6, y1_y2p);	printf("Y1_y2p =");	imprvectreel(6, Y1_y2p);
			printf("z1_z2p =");	imprvectreel(6, z1_z2p);	printf("Z1_z2p =");	imprvectreel(6, Z1_z2p);
			printf("f1xp =");	imprvectreel(6, f1xp);		printf("F1xp =");	imprvectreel(6, F1xp);
			printf("f1yp =");	imprvectreel(6, f1yp);		printf("F1yp =");	imprvectreel(6, F1yp);
			printf("f1zp =");	imprvectreel(6, f1zp);		printf("F1zp =");	imprvectreel(6, F1zp);
			printf("f2xp =");	imprvectreel(6, f2xp);		printf("F2xp =");	imprvectreel(6, F2xp);
			printf("f2yp =");	imprvectreel(6, f2yp);		printf("F2yp =");	imprvectreel(6, F2yp);
			printf("f2zp =");	imprvectreel(6, f2zp);		printf("F2zp =");	imprvectreel(6, F2zp);
			printf("distp =");	imprvectreel(6, distp);		printf("Distp =");	imprvectreel(6, Distp);
			exit(0);
      			TEST_fin*/
      			}
  		}
	}



