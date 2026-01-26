#define PRINCIPAL 0
#include "4c19.h"

	/*
	takes into account the forces due to an elastic sphere
	the centre of the sphere is Spheric_limit.x, Spheric_limit.y & Spheric_limit.z
	the radius is Spheric_limit.radius the stiffness in compression is Spheric_limit.kc
	and the stiffness in traction is Spheric_limit.kt;
	*/

void spheric_limit1()
	{
  	int i, ii, j, jj, zi,zu,zv,zw;
  	double dist,Sx,Sy,Sz,Srad,Sk,Mx,My,Mz;
  	double FSmod, FSdirx,FSdiry,FSdirz;
  	double delta_x,ff[4],ke[4][4],Ff[4],Ke[4][4];
  	
  	if (Spheric_limit.radius > 0.0)
  		{
	  	Sx = Spheric_limit.x;
	  	Sy = Spheric_limit.y;
	  	Sz = Spheric_limit.z;
	  	Srad = Spheric_limit.radius;
	  	
	  	/*printf("Spheric_limit.kt %lf  \n", Spheric_limit.kc);*/
	  	 
	  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
	  		{
	  		if (whs[3*zi] == 2)
	  			{
	  			/*printf("whs[3*zi] %5d zi %5d  ", whs[3*zi],zi);*/
	  			Mx = wf[3*zi-2];My = wf[3*zi-1];Mz = wf[3*zi-0];
	  			
	      			/*TEST_debut
				Mx = 0.1;	My = -0.2;	Mz = -9.75651;
	      			delta_x = -0.00001;
				for( zu = 0 ; zu <= 4 ; zu++ )
	      				{
	      				if (zu == 1) Mx = Mx + delta_x;
	      				if (zu == 2) My = My + delta_x;
	      				if (zu == 3) Mz = Mz + delta_x;
	      				TEST_fin*/
	      		
	  			dist = sqrt((Mx-Sx)*(Mx-Sx)+(My-Sy)*(My-Sy)+(Mz-Sz)*(Mz-Sz));
	  			if (dist > Srad) 	Sk = Spheric_limit.kt;
	  			else 			Sk = Spheric_limit.kc;
	  			Ff[1] = (Srad - dist) * (Mx-Sx) * Sk / dist / Srad;
	  			Ff[2] = (Srad - dist) * (My-Sy) * Sk / dist / Srad;
	  			Ff[3] = (Srad - dist) * (Mz-Sz) * Sk / dist / Srad;
				/*printf("zu %5d ",zu);
				printf("M %12.8lf %12.5lf %12.5lf   ",Mx,My,Mz);
				printf("dist %12.8lf   ",dist);
				printf("Ff = ");for (zv = 1 ;zv <= 3 ;zv++ )	
				printf("%12.5lf ",Ff[zv]);printf("\n");*/
	  			/*printf("M %lf %lf %lf dist %lf  ", Mx,My,Mz,dist);*/
	  			/*printf("FSdir %lf %lf %lf \n",FSdirx,FSdiry,FSdirz);*/
	  			Ke[1][1] = - Sk * (dist * (Srad-dist) - Srad * (Sx-Mx)*(Sx-Mx)  /dist) / dist / dist / Srad;
	  			Ke[2][2] = - Sk * (dist * (Srad-dist) - Srad * (Sy-My)*(Sy-My)  /dist) / dist / dist / Srad;
	  			Ke[3][3] = - Sk * (dist * (Srad-dist) - Srad * (Sz-Mz)*(Sz-Mz)  /dist) / dist / dist / Srad;
	  			Ke[1][2] = Sk * (Sy-My) * (Sx-Mx) / dist / dist / dist;
	  			Ke[2][1] = Sk * (Sy-My) * (Sx-Mx) / dist / dist / dist;
	  			Ke[1][3] = Sk * (Sz-Mz) * (Sx-Mx) / dist / dist / dist;
	  			Ke[3][1] = Sk * (Sz-Mz) * (Sx-Mx) / dist / dist / dist;
	  			Ke[2][3] = Sk * (Sz-Mz) * (Sy-My) / dist / dist / dist;
	  			Ke[3][2] = Sk * (Sz-Mz) * (Sy-My) / dist / dist / dist;
	  			
	      			/*TEST_debut
	      			if (zu == 0) for( zv = 1 ; zv <= 3 ; zv++ ) ff[zv] = Ff[zv] ;	
	      			if (zu == 1) Mx = Mx - delta_x;
	      			if (zu == 2) My = My - delta_x;
	      			if (zu == 3) Mz = Mz - delta_x;
	      		
	      			if ((zu > 0) && (zu < 4))
	      				for (zw = 1 ;zw <= 3 ;zw++ )	ke[zw][zu] = - (Ff[zw] - ff[zw]) / delta_x;
					
	      			if (zu == 4)
	      				{
					for (zw = 1 ;zw <= 3 ;zw++ )
						{
						printf("ke = ");	for (zv = 1 ;zv <= 3 ;zv++ )	printf("%12.0lf ",ke[zw][zv]);	printf(" \n");
						}
					for (zw = 1 ;zw <= 3 ;zw++ )
						{
						printf("Ke = ");	for (zv = 1 ;zv <= 3 ;zv++ )	printf("%12.0lf ",Ke[zw][zv]);	printf(" \n");
						}
	      				}
				}
				exit(0);
	      			TEST_fin*/
	      			wanoeud[3*zi-2]	+= Ff[1];
	      			wanoeud[3*zi-1]	+= Ff[2];
	      			wanoeud[3*zi-0]	+= Ff[3];
				if (Structure.type_solver == 1)
				{
	      				ze[3*zi-2][eca+0] += Ke[1][1];
	      				ze[3*zi-2][eca+1] += Ke[1][2];
	      				ze[3*zi-2][eca+2] += Ke[1][3];
	      				ze[3*zi-1][eca-1] += Ke[2][1];
	      				ze[3*zi-1][eca+0] += Ke[2][2];
	      				ze[3*zi-1][eca+1] += Ke[2][3];
	      				ze[3*zi-0][eca-2] += Ke[3][1];
	      				ze[3*zi-0][eca-1] += Ke[3][2];
	      				ze[3*zi-0][eca+0] += Ke[3][3];
				}
				else if (Structure.type_solver == 2)
				{
					affectation_pardiso(Ke[1][1], 3*zi-2, 3*zi-2);
					affectation_pardiso(Ke[1][2], 3*zi-2, 3*zi-1);
					affectation_pardiso(Ke[1][3], 3*zi-2, 3*zi);

					affectation_pardiso(Ke[2][1], 3*zi-1, 3*zi-2);
					affectation_pardiso(Ke[2][2], 3*zi-1, 3*zi-1);
					affectation_pardiso(Ke[2][3], 3*zi-1, 3*zi);

					affectation_pardiso(Ke[3][1], 3*zi, 3*zi-2);
					affectation_pardiso(Ke[3][2], 3*zi, 3*zi-1);
					affectation_pardiso(Ke[3][3], 3*zi, 3*zi);
	/*		  		for (i = 0; i< 3; i++)
		  			{
						ii = new_coor(i, zi, zi, 0, 0);
			  			for (j = 0; j< 3; j++)
		  				{
							jj = new_coor(j, zi, zi, 0, 0);
							affectation_pardiso(Ke[i+1][j+1], ii, jj);
						}
					}*/
				}
	  			/*printf("Ff %lf %lf %lf  \n", Ff[1],Ff[2],Ff[3]);*/
	       			}
			}
		}
	}
