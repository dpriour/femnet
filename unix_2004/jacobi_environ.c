#define PRINCIPAL 0
#include "4c19.h"

void jacobi_environ(float *d_jacobi_result, float **v_jacobi_result)
	{
	float **a_jacobi,*d_jacobi,**v_jacobi,*masse_jacobi,p_jacobi,max_non_symm[11],val_non_symm;
	int n_jacobi,nrot_jacobi,zu,zv,zw,zx,zy,zz,max_non_symm_zu[11],max_non_symm_zv[11],val_non_symm_zu,val_non_symm_zv;
	n_jacobi = 3*NOMBRE_NOEUDS;
	a_jacobi = matrix(1,n_jacobi,1,n_jacobi);
	v_jacobi = matrix(1,n_jacobi,1,n_jacobi);
	d_jacobi = vector(1,n_jacobi);
	masse_jacobi = vector(1,n_jacobi);
	/*zeroing*/
	for (zu=1;zu<=n_jacobi;zu++)
		{
		masse_jacobi[zu] = 0.0;
		}
	for (zu=1;zu<=n_jacobi;zu++)
		{
		for (zv=1;zv<=n_jacobi;zv++)
			{
			a_jacobi[zu][zv] = 0.0;
			}
		}
	for (zu=1;zu<=10;zu++)
		{
		max_non_symm[zu] = 0.0;
		max_non_symm_zu[zu] = 0;
		max_non_symm_zv[zu] = 0;
		}
	/*mass vector*/
	for (zu = 1 ; zu<= NOMBRE_NOEUDS ; zu++) 
		{
		masse_jacobi[3*zu-2] += Noeud[zu].mx;
		masse_jacobi[3*zu-1] += Noeud[zu].my;
		masse_jacobi[3*zu-0] += Noeud[zu].mz;
		}
  	for (zu = 1 ; zu<= NOMBRE_ELEMENTS ; zu++) 
  		{
    		masse_jacobi[yb(zu,1)] += Element[zu].mass / 2.0;
    		masse_jacobi[yb(zu,2)] += Element[zu].mass / 2.0;
    		masse_jacobi[yb(zu,3)] += Element[zu].mass / 2.0;
    		masse_jacobi[yb(zu,4)] += Element[zu].mass / 2.0;
    		masse_jacobi[yb(zu,5)] += Element[zu].mass / 2.0;
    		masse_jacobi[yb(zu,6)] += Element[zu].mass / 2.0;
		}
  	for (zu = 1 ; zu <= NOMBRE_SURFACES ; zu++)
  		{
	     	masse_jacobi[yc(zu,1)] += Surface[zu].lgrepos*PI*Surface[zu].diametrehydro*Surface[zu].diametrehydro*Surface[zu].rhosurface / 4.0 * 2.0 * Surface[zu].nb_cote_u_ou_v / 3.0;
	     	masse_jacobi[yc(zu,2)] += Surface[zu].lgrepos*PI*Surface[zu].diametrehydro*Surface[zu].diametrehydro*Surface[zu].rhosurface / 4.0 * 2.0 * Surface[zu].nb_cote_u_ou_v / 3.0;
	     	masse_jacobi[yc(zu,3)] += Surface[zu].lgrepos*PI*Surface[zu].diametrehydro*Surface[zu].diametrehydro*Surface[zu].rhosurface / 4.0 * 2.0 * Surface[zu].nb_cote_u_ou_v / 3.0;
	     	masse_jacobi[yc(zu,4)] += Surface[zu].lgrepos*PI*Surface[zu].diametrehydro*Surface[zu].diametrehydro*Surface[zu].rhosurface / 4.0 * 2.0 * Surface[zu].nb_cote_u_ou_v / 3.0;
	     	masse_jacobi[yc(zu,5)] += Surface[zu].lgrepos*PI*Surface[zu].diametrehydro*Surface[zu].diametrehydro*Surface[zu].rhosurface / 4.0 * 2.0 * Surface[zu].nb_cote_u_ou_v / 3.0;
	     	masse_jacobi[yc(zu,6)] += Surface[zu].lgrepos*PI*Surface[zu].diametrehydro*Surface[zu].diametrehydro*Surface[zu].rhosurface / 4.0 * 2.0 * Surface[zu].nb_cote_u_ou_v / 3.0;
	     	masse_jacobi[yc(zu,7)] += Surface[zu].lgrepos*PI*Surface[zu].diametrehydro*Surface[zu].diametrehydro*Surface[zu].rhosurface / 4.0 * 2.0 * Surface[zu].nb_cote_u_ou_v / 3.0;
	     	masse_jacobi[yc(zu,8)] += Surface[zu].lgrepos*PI*Surface[zu].diametrehydro*Surface[zu].diametrehydro*Surface[zu].rhosurface / 4.0 * 2.0 * Surface[zu].nb_cote_u_ou_v / 3.0;
	     	masse_jacobi[yc(zu,9)] += Surface[zu].lgrepos*PI*Surface[zu].diametrehydro*Surface[zu].diametrehydro*Surface[zu].rhosurface / 4.0 * 2.0 * Surface[zu].nb_cote_u_ou_v / 3.0;
  		}
	//printf("ze global elements finis (stiffness matrix)\n");
	for( zu = 1 ; zu <= 12 ; zu++ )
		{
		for( zw = eca-9 ; zw <= eca+9 ; zw++ )
			{
			//printf("%9.0lf",ze[zu][zw]);
			}
		//printf("\n");
		}
	
	for( zu = 1 ; zu <= n_jacobi ; zu++ )
		{
		for( zv = 1 ; zv <= n_jacobi ; zv++ )
			{
			a_jacobi[zu][zv] = (float) (ze[zu][eca-zu+zv] / sqrt(masse_jacobi[zu]*masse_jacobi[zv]));
			/*if ((zu == 124) && (zv == 112))
				{
				printf("zu: %8d ", zu);
				printf("zv: %8d ", zv);
				printf("ze: %8.4lf ", ze[zu][eca-zu+zv]);
				printf("mass zu: %8.4lf ", masse_jacobi[zu]);
				printf("mass zv: %8.4lf\n", masse_jacobi[zv]);
				}
			if ((zu == 112) && (zv == 124))
				{
				printf("zu: %8d ", zu);
				printf("zv: %8d ", zv);
				printf("ze: %8.4lf ", ze[zu][eca-zu+zv]);
				printf("mass zu: %8.4lf ", masse_jacobi[zu]);
				printf("mass zv: %8.4lf\n", masse_jacobi[zv]);
				}*/
			}
		}
		
	/*print if the matrix is not symmetric*/
	printf("beginning of verification of non symmetry of stiffness matrix for eigen values: 10 max dy-symmetric ratio are calculated:\n");
	for( zu = 1 ; zu <= 10 ; zu++ )
		{
		max_non_symm[zu] = 0.0;
		}
	for( zu = 1 ; zu <= n_jacobi-1 ; zu++ )
		{
		for( zv = zu+1 ; zv <= n_jacobi ; zv++ )
			{
			if(a_jacobi[zu][zv] != a_jacobi[zv][zu])
				{
				if (fabsf(a_jacobi[zu][zv]) > fabsf(a_jacobi[zv][zu]))
					{
					val_non_symm = fabsf((a_jacobi[zu][zv]-a_jacobi[zv][zu])/a_jacobi[zu][zv]);
					val_non_symm_zu = zu;
					val_non_symm_zv = zv;
					//printf("zu %4d zv%4d (a_jacobi[zu][zv] - a_jacobi[zv][zu])/a_jacobi[zu][zv] %9.3lf \n",zu,zv,(a_jacobi[zu][zv]-a_jacobi[zv][zu])/a_jacobi[zu][zv]);
					}
				else
					{
					val_non_symm = fabsf((a_jacobi[zu][zv]-a_jacobi[zv][zu])/a_jacobi[zv][zu]);
					val_non_symm_zu = zv;
					val_non_symm_zv = zu;
					//printf("zu %4d zv%4d (a_jacobi[zv][zu] - a_jacobi[zu][zv])/a_jacobi[zv][zu] %9.3lf \n",zu,zv,(a_jacobi[zv][zu]-a_jacobi[zu][zv])/a_jacobi[zv][zu]);
					}
				zx = 11;
				for (zw = 10; zw >= 1; zw--)				
					{
					if(val_non_symm > max_non_symm[zw])
						{
						zx = zw;
						}
					}
				if (zx < 11)
					{
					for (zw = 10; zw >= zx+1; zw--)				
						{
						max_non_symm[zw] = max_non_symm[zw-1];
						}
					max_non_symm[zx] = val_non_symm;
					max_non_symm_zu[zx] = val_non_symm_zu;
					max_non_symm_zv[zx] = val_non_symm_zv;
					//printf("val %8.4f zx %2d  max  ", val_non_symm,zx);
					for( zw = 1 ; zw <= 10 ; zw++ )
						{
						//printf("%8.4f ", max_non_symm[zw]);
						}
					//printf("\n");
					}
				
				}
			}
		}
	for( zu = 1 ; zu <= 10 ; zu++ )
		{
		printf("ratio: %8.4f ", max_non_symm[zu]);
		//printf("zu: %4d ", max_non_symm_zu[zu]);
		//printf("zv: %4d ", max_non_symm_zv[zu]);
		printf("ze(zu,zv): %10.0lf ", ze[max_non_symm_zu[zu]][eca-max_non_symm_zu[zu]+max_non_symm_zv[zu]]);
		printf("ze(zv,zu): %10.0lf ", ze[max_non_symm_zv[zu]][eca-max_non_symm_zv[zu]+max_non_symm_zu[zu]]);
		printf("mass zu: %4.0lf ", masse_jacobi[zu]);
		printf("mass zv: %4.0lf\n", masse_jacobi[zv]);
		}
	printf("end        of verification of non symmetry of stiffness matrix for eigen values\n");
	/*printf*/
	/*printf("mass\n");
	for (zu=1;zu<=n_jacobi;zu++)
		{
		printf("%8.4f ", masse_jacobi[zu]);
		}
	printf("\n");*/
	/*printf("stiffness/sqrt(mass^2)\n");
	for (zu=1;zu<=n_jacobi;zu++)
		{
		for (zv=1;zv<=n_jacobi;zv++)
			{
			printf("%12.0f ", a_jacobi[zu][zv]);
			}
		printf("\n");
		}*/
	jacobi(a_jacobi, n_jacobi, d_jacobi, v_jacobi, &nrot_jacobi);
	
	/*printf("lamda\n");
	for (zu=1;zu<=n_jacobi;zu++)
		{
		printf("%8.4f ", d_jacobi[zu]);
		}
	printf("\n");*/
	/*replace eigenvalues by eigen periods*/
	for (zu=1;zu<=n_jacobi;zu++) 
		{
		if (d_jacobi[zu] > 0)
			{
			d_jacobi[zu]=2.0*PI/sqrt(d_jacobi[zu]);
			}
		}
	/*printf("periods\n");
	for (zu=1;zu<=n_jacobi;zu++)
		{
		printf("%8.4f ", d_jacobi[zu]);
		}
	printf("\n");*/
		
	/*to remove eigenvectors corresponding to fixed node, the eigen periods is set to zero*/
	for (zv=1;zv<=n_jacobi;zv++)
		{
		for (zu=1;zu<=n_jacobi;zu++)
			{
			if (v_jacobi[zu][zv] == 1.0)
				{
				if (wl[zu] != 99)
					{
					d_jacobi[zv] = 0.0;
					//printf("zu %3d zv %3d ", zu,zv);
					//printf("v_jacobi %9.5f ", v_jacobi[zu][zv]);
					//printf("wl %9.5f \n", wl[zu]);
					}
				}
			}
		}
		
		
	/*sorting the eigen periods*/	
	for (zu=1;zu<n_jacobi;zu++) 
		{
		p_jacobi=d_jacobi[zw=zu];
		for (zv=zu+1;zv<=n_jacobi;zv++)
			if (d_jacobi[zv] >= p_jacobi) p_jacobi=d_jacobi[zw=zv];
		if (zw != zu) 
			{
			d_jacobi[zw]=d_jacobi[zu];
			d_jacobi[zu]=p_jacobi;
			for (zv=1;zv<=n_jacobi;zv++) 
				{
				p_jacobi=v_jacobi[zv][zu];
				v_jacobi[zv][zu]=v_jacobi[zv][zw];
				v_jacobi[zv][zw]=p_jacobi;
				}
			}
		}
		
	/*in case there are too numerous eigen periods asked*/
	if (Structure.eigenvalues>n_jacobi)Structure.eigenvalues=n_jacobi;
	
	
	//printf("eigen periods (s)\n");
	for (zu=1;zu<=Structure.eigenvalues;zu++)
		{
		//printf("%12.5f ", d_jacobi[zu]);
		d_jacobi_result[zu] = d_jacobi[zu];
		}
	//printf("\n");
	//printf("eigenvectors (m)\n");
	for (zu=1;zu<=n_jacobi;zu++)
		{
		zw = (int) floor((zu+2)/3);			/*node number*/
		zx = 3*zw - zu;					/*ecart*/
		zz = fixation[zw];
		zy = 3*fixation[zw]-zx;				/*DOF as defined in phobos or don file*/
		//printf("zu %4d zw %4d zx %4d zy %4d zz %4d ", zu,zw,zx,zy,zz);
		for (zv=1;zv<=Structure.eigenvalues;zv++)
			{
			//printf("%9.5f ", v_jacobi[zu][zv]);
			v_jacobi_result[zy][zv] = v_jacobi[zu][zv];
			}
		//printf("\n");
		}
	}
	

