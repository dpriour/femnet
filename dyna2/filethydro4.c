#include "4c19.h"

void filethydro4()
	{
	/*efforts de trainee hydrodynamique agissant sur les fils du filet en tenant
	compte de la proportion de la surface mouillee par rapport a la surface totale.
	tient compte de la ponderation liee a la surface libre*/
	  
	int zg,zh,zi,zj,zu,zv;
	double drag_tmp[4],depl_tmp[4];
	double ba[4],Vw[4],nt[4];
	double u1,u2,u3,v1,v2,v3,S,XX1,XX2,XX3,YY1,YY2,YY3,ZZ1,ZZ2,ZZ3,nx,ny,nz,mx,my,mz,delta_x;
	double FF[10],ff[10],KK[10][10];

	Structure.surface_energy = 0;
	  
	for (zg = 1 ; zg <= NOMBRE_SURFACES ; zg++)
		{
		/*calcul des efforts de trainée dans le courant en prenant en compte la vitesse des sommets de l élément triangulaire*/ 
		/*numero des coordonnees selon x des 2 extremites de cet element*/
		delta_x = 0.0001;	
		
		zh = yc(zg,1);
		zi = yc(zg,4);
		zj = yc(zg,7);
		
		/*
		if (zh == 193 )	printf("zg %5d\n",zg);
		if (zi == 193 )	printf("zg %5d\n",zg);
		if (zj == 193 )	printf("zg %5d\n",zg);
		*/

		
		u1 =   Surface[zg].lon[1] + Surface[zg].lon[2] - Surface[zg].lon[2] - Surface[zg].lon[1]; 
		u2 =   Surface[zg].lon[3] + Surface[zg].lon[4] - Surface[zg].lon[2] - Surface[zg].lon[1]; 
		u3 =   Surface[zg].lon[5] + Surface[zg].lon[6] - Surface[zg].lon[2] - Surface[zg].lon[1];  
		v1 = - Surface[zg].lon[1] + Surface[zg].lon[2] - Surface[zg].lon[2] + Surface[zg].lon[1];  
		v2 = - Surface[zg].lon[3] + Surface[zg].lon[4] - Surface[zg].lon[2] + Surface[zg].lon[1];  
		v3 = - Surface[zg].lon[5] + Surface[zg].lon[6] - Surface[zg].lon[2] + Surface[zg].lon[1]; 
		/* u1 : coordonnee du noeud 1 en nb de fils de direction u = 0.0*/
		/* u2 : coordonnee du noeud 2 en nb de fils de direction u.*/
		/* u3 : coordonnee du noeud 3 en nb de fils de direction u. */    
		/* v1 : coordonnee du noeud 1 en nb de fils de direction v = 0.0*/
		/* v2 : coordonnee du noeud 2 en nb de fils de direction v. */
		/* v3 : coordonnee du noeud 3 en nb de fils de direction v. */

		S = ((u2-u1)*(v3-v1) - (u3-u1)*(v2-v1));

		/* nx : Coordonnees selon x d'un cote de maille (selon u )*/
		/* ny : Coordonnees selon y d'un cote de maille (selon u )*/
		/* nz : Coordonnees selon z d'un cote de maille (selon u )*/
		/* mx : Coordonnees selon x d'un cote de maille (selon v )*/
		/* my : Coordonnees selon y d'un cote de maille (selon v )*/
		/* mz : Coordonnees selon z d'un cote de maille (selon v )*/
		
		XX1 = wf[zh+0];    	YY1 = wf[zh+1];    	ZZ1 = wf[zh+2];
		XX2 = wf[zi+0];    	YY2 = wf[zi+1];    	ZZ2 = wf[zi+2];
		XX3 = wf[zj+0];    	YY3 = wf[zj+1];    	ZZ3 = wf[zj+2];
		for (zu = 0 ; zu <= 10 ; zu++)
			{
			for (zv = 1 ; zv <= 9 ; zv++)
				{
				ff[zv] = 0.0;
				}
			
			if (zu == 1) XX1 += delta_x;
			if (zu == 2) YY1 += delta_x;
			if (zu == 3) ZZ1 += delta_x;
			if (zu == 4) XX2 += delta_x;
			if (zu == 5) YY2 += delta_x;
			if (zu == 6) ZZ2 += delta_x;
			if (zu == 7) XX3 += delta_x;
			if (zu == 8) YY3 += delta_x;
			if (zu == 9) ZZ3 += delta_x;
			      		
			nx =  (v3*(XX2-XX1) - v2*(XX3-XX1))/S;  	ny =  (v3*(YY2-YY1) - v2*(YY3-YY1))/S;  	nz =  (v3*(ZZ2-ZZ1) - v2*(ZZ3-ZZ1))/S;
			mx =  (u2*(XX3-XX1) - u3*(XX2-XX1))/S;  	my =  (u2*(YY3-YY1) - u3*(YY2-YY1))/S;  	mz =  (u2*(ZZ3-ZZ1) - u3*(ZZ2-ZZ1))/S;


			//zh extremite 1 //////////////////////////////////////////////////////
		     	Vw[1] = mvh[zh+0]-mvb[zh+0];		//water speed
		     	Vw[2] = mvh[zh+1]-mvb[zh+1];
		     	Vw[3] = mvh[zh+2]-mvb[zh+2];
			
			//fils u 
			//ba[1] = Surface[zg].nx;		//twine vector
			//ba[2] = Surface[zg].ny;
			//ba[3] = Surface[zg].nz;

			ba[1] = nx;		//twine vector
			ba[2] = ny;
			ba[3] = nz;
			
			basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
			//wasurf[yc(zg,1)] += nt[1] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			//wasurf[yc(zg,2)] += nt[2] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			//wasurf[yc(zg,3)] += nt[3] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			ff[1] += nt[1] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			ff[2] += nt[2] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			ff[3] += nt[3] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u

			if (zu == 0)
				{
				drag_tmp[1] = nt[1];
				drag_tmp[2] = nt[2];
				drag_tmp[3] = nt[3];
				}
		    		
			//fils v
			//ba[1] = Surface[zg].mx;
			//ba[2] = Surface[zg].my;
			//ba[3] = Surface[zg].mz;
			ba[1] = mx;
			ba[2] = my;
			ba[3] = mz;

			basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
			//wasurf[yc(zg,1)] += nt[1] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			//wasurf[yc(zg,2)] += nt[2] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			//wasurf[yc(zg,3)] += nt[3] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			ff[1] += nt[1] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			ff[2] += nt[2] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			ff[3] += nt[3] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			
			if (zu == 0)
				{
				drag_tmp[1] += nt[1];
				drag_tmp[2] += nt[2];
				drag_tmp[3] += nt[3];
			
				depl_tmp[1] = wf[yc(zg,1)] -  wf1[yc(zg,1)];	//deplacement (m) of first vertex	
				depl_tmp[2] = wf[yc(zg,2)] -  wf1[yc(zg,2)];	
				depl_tmp[3] = wf[yc(zg,3)] -  wf1[yc(zg,3)];	
				Structure.surface_energy -= produit_scal(drag_tmp,depl_tmp);
				}
				
			//zi extremite 2 //////////////////////////////////////////////////////
		     	Vw[1] = mvh[zi+0]-mvb[zi+0];
		     	Vw[2] = mvh[zi+1]-mvb[zi+1];
		     	Vw[3] = mvh[zi+2]-mvb[zi+2];		
			
			//fils u 
			//ba[1] = Surface[zg].nx;		//twine vector
			//ba[2] = Surface[zg].ny;
			//ba[3] = Surface[zg].nz;
			ba[1] = nx;		//twine vector
			ba[2] = ny;
			ba[3] = nz;
			
			basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
			//wasurf[yc(zg,4)] += nt[1] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			//wasurf[yc(zg,5)] += nt[2] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			//wasurf[yc(zg,6)] += nt[3] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			ff[4] += nt[1] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			ff[5] += nt[2] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			ff[6] += nt[3] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
				
			if (zu == 0)
				{
				drag_tmp[1] = nt[1];
				drag_tmp[2] = nt[2];
				drag_tmp[3] = nt[3];
				}
		    		
			//fils v
			//ba[1] = Surface[zg].mx;
			//ba[2] = Surface[zg].my;
			//ba[3] = Surface[zg].mz;
			ba[1] = mx;
			ba[2] = my;
			ba[3] = mz;

			basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
			//wasurf[yc(zg,4)] += nt[1] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			//wasurf[yc(zg,5)] += nt[2] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			//wasurf[yc(zg,6)] += nt[3] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			ff[4] += nt[1] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			ff[5] += nt[2] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			ff[6] += nt[3] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		 
			if (zu == 0)
				{
			 	drag_tmp[1] += nt[1];
				drag_tmp[2] += nt[2];
				drag_tmp[3] += nt[3];
				
				depl_tmp[1] = wf[yc(zg,4)] -  wf1[yc(zg,4)];	//deplacement (m) of second vertex	
				depl_tmp[2] = wf[yc(zg,5)] -  wf1[yc(zg,5)];	
				depl_tmp[3] = wf[yc(zg,6)] -  wf1[yc(zg,6)];	
				Structure.surface_energy -= produit_scal(drag_tmp,depl_tmp);
				}

		 
		 
		   	//zj extremite 3 //////////////////////////////////////////////////////
		     	Vw[1] = mvh[zj+0]-mvb[zj+0];
		     	Vw[2] = mvh[zj+1]-mvb[zj+1];
		     	Vw[3] = mvh[zj+2]-mvb[zj+2];		
			
			//fils u 
			//ba[1] = Surface[zg].nx;		//twine vector
			//ba[2] = Surface[zg].ny;
			//ba[3] = Surface[zg].nz;
			ba[1] = nx;		//twine vector
			ba[2] = ny;
			ba[3] = nz;
			
			basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
			//wasurf[yc(zg,7)] += nt[1] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			//wasurf[yc(zg,8)] += nt[2] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			//wasurf[yc(zg,9)] += nt[3] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			ff[7] += nt[1] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			ff[8] += nt[2] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
			ff[9] += nt[3] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
				
			if (zu == 0)
				{
				drag_tmp[1] = nt[1];
				drag_tmp[2] = nt[2];
				drag_tmp[3] = nt[3];
				}
		    		
			//fils v
			//ba[1] = Surface[zg].mx;
			//ba[2] = Surface[zg].my;
			//ba[3] = Surface[zg].mz;
			ba[1] = mx;
			ba[2] = my;
			ba[3] = mz;

			basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
			//wasurf[yc(zg,7)] += nt[1] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			//wasurf[yc(zg,8)] += nt[2] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			//wasurf[yc(zg,9)] += nt[3] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			ff[7] += nt[1] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			ff[8] += nt[2] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
			ff[9] += nt[3] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		 
			if (zu == 0)
				{
			 	drag_tmp[1] += nt[1];
				drag_tmp[2] += nt[2];
				drag_tmp[3] += nt[3];
				
				depl_tmp[1] = wf[yc(zg,7)] -  wf1[yc(zg,7)];	//deplacement (m) of second vertex	
				depl_tmp[2] = wf[yc(zg,8)] -  wf1[yc(zg,8)];	
				depl_tmp[3] = wf[yc(zg,9)] -  wf1[yc(zg,9)];	
				Structure.surface_energy -= produit_scal(drag_tmp,depl_tmp);
				
				Structure.surface_power = Structure.surface_energy/Pascalcul;
				for (zv = 1 ; zv <= 9 ; zv++)
					{
					FF[zv] = ff[zv];
					wasurf[yc(zg,zv)] += ff[zv];
					}
				}
			if (zu == 1) XX1 -= delta_x;
			if (zu == 2) YY1 -= delta_x;
			if (zu == 3) ZZ1 -= delta_x;
			if (zu == 4) XX2 -= delta_x;
			if (zu == 5) YY2 -= delta_x;
			if (zu == 6) ZZ2 -= delta_x;
			if (zu == 7) XX3 -= delta_x;
			if (zu == 8) YY3 -= delta_x;
			if (zu == 9) ZZ3 -= delta_x;
			for (zv = 1 ; zv <= 9 ; zv++)
				{
				KK[zu][zv] = (ff[zv] - FF[zv])/delta_x;
				}
				
			}
		
		/*
		if ((zh == 193) || (zi == 193) || (zj == 193))
			{
			printf("KK\n");
			for (zu = 1 ; zu <= 9 ; zu++)
				{
				for (zv = 1 ; zv <= 9 ; zv++)
					{
					printf("%7.3lf ",KK[zu][zv]);
					}
				printf("\n");
				}
			}
		*/
		}
	//exit(0);
	}

