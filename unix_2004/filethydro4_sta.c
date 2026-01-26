#include "4c19.h"

void filethydro4_sta()

{

/*efforts de trainee hydrodynamique agissant sur les fils du filet en tenant
compte de la proportion de la surface mouillee par rapport a la surface totale.
prend en compte la ponderation liee a la surface libre*/
  
int typ,no1,no2,no3,elem;
double ba[4],Vw[4],nt[4],bu[4],bv[4],normal[4],tang1[4],tang2[4];
double mod,surface,XX1,XX2,XX3,YY1,YY2,YY3,ZZ1,ZZ2,ZZ3;
//printf("Structure.openfoam: %d\n",Structure.openfoam);
 
if ((Courant.vitesse != 0.0) && (Structure.openfoam <= 1))
	{
	for (elem = 1 ; elem <= NOMBRE_SURFACES ; elem++)
		{
		Vw[1] = Courant.vitesse*cos(Courant.direction*PI/180.0) * panneau[Surface[elem].type].current_reduction;
		Vw[2] = Courant.vitesse*sin(Courant.direction*PI/180.0) * panneau[Surface[elem].type].current_reduction;
		Vw[3] = 0.0                                             * panneau[Surface[elem].type].current_reduction;
		
		//extremites 1, 2 & 3 fils u
		ba[1] = Surface[elem].nx;
		ba[2] = Surface[elem].ny;
		ba[3] = Surface[elem].nz;
		if (produit_scal(ba,ba) == 0.0)
			{
			printf("filethydro4_sta\n");	
			printf("ba : ");	
			//exit(0);
			}
		basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
		wasurf[yc(elem,1)] += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,2)] += nt[2] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,3)] += nt[3] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*panel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}
		
		wasurf[yc(elem,4)] += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,5)] += nt[2] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,6)] += nt[3] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*panel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}
		
		wasurf[yc(elem,7)] += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,8)] += nt[2] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,9)] += nt[3] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*panel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}
		
		//extremite 1, 2 & 3 fils v
		ba[1] = Surface[elem].mx;
		ba[2] = Surface[elem].my;
		ba[3] = Surface[elem].mz;
		if (produit_scal(ba,ba) == 0.0)
			{
			printf("filethydro4_sta\n");	
			printf("ba : ");	
			//exit(0);
			}
		basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
		wasurf[yc(elem,1)] += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,2)] += nt[2] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,3)] += nt[3] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*pannel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}

		wasurf[yc(elem,4)] += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,5)] += nt[2] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,6)] += nt[3] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*pannel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}

		wasurf[yc(elem,7)] += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,8)] += nt[2] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,9)] += nt[3] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*pannel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}
		}
	}
if (Structure.openfoam == 2)
	{
	//water speed is given per node by *.spe file
	for (elem = 1 ; elem <= NOMBRE_SURFACES ; elem++)
		{
		no1 = (int) yc(elem,3)/3;	/*node number of vertex 1*/
		no2 = (int) yc(elem,6)/3;	/*node number of vertex 2*/
		no3 = (int) yc(elem,9)/3;	/*node number of vertex 3*/
		//extremites 1, 2 & 3 fils u
		ba[1] = Surface[elem].nx;
		ba[2] = Surface[elem].ny;
		ba[3] = Surface[elem].nz;
		if (produit_scal(ba,ba) == 0.0)
			{
			printf("filethydro4_sta\n");	
			printf("ba : ");	
			//exit(0);
			}
		//extremity 1, u twine
		Vw[1] = Noeud[no1].vx;
		Vw[2] = Noeud[no1].vy;
		Vw[3] = Noeud[no1].vz;
		basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
		wasurf[yc(elem,1)] += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,2)] += nt[2] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,3)] += nt[3] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*pannel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}
		
		//extremity 2, u twine
		Vw[1] = Noeud[no2].vx;
		Vw[2] = Noeud[no2].vy;
		Vw[3] = Noeud[no2].vz;
		basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
		wasurf[yc(elem,4)] += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,5)] += nt[2] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,6)] += nt[3] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*pannel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}
		
		//extremity 3, u twine
		Vw[1] = Noeud[no3].vx;
		Vw[2] = Noeud[no3].vy;
		Vw[3] = Noeud[no3].vz;
		basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
		wasurf[yc(elem,7)] += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,8)] += nt[2] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		wasurf[yc(elem,9)] += nt[3] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*pannel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}
		
		//extremite 1, 2 & 3 fils v
		ba[1] = Surface[elem].mx;
		ba[2] = Surface[elem].my;
		ba[3] = Surface[elem].mz;
		if (produit_scal(ba,ba) == 0.0)
			{
			printf("filethydro4_sta\n");	
			printf("ba : ");	
			//exit(0);
			}
		//extremity 1, v twine
		Vw[1] = Noeud[no1].vx;
		Vw[2] = Noeud[no1].vy;
		Vw[3] = Noeud[no1].vz;
		basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
		wasurf[yc(elem,1)] += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,2)] += nt[2] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,3)] += nt[3] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*pannel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}

		//extremity 2, v twine
		Vw[1] = Noeud[no2].vx;
		Vw[2] = Noeud[no2].vy;
		Vw[3] = Noeud[no2].vz;
		basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
		wasurf[yc(elem,4)] += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,5)] += nt[2] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,6)] += nt[3] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*pannel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}

		//extremity 3, v twine
		Vw[1] = Noeud[no3].vx;
		Vw[2] = Noeud[no3].vy;
		Vw[3] = Noeud[no3].vz;
		basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
		wasurf[yc(elem,7)] += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,8)] += nt[2] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		wasurf[yc(elem,9)] += nt[3] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
		Structure.surface_drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
		if (Sortie_texte.panel_drag == 1)
			{
		  	typ = Surface[elem].type;	/*pannel*/
		    	panneau[typ].drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
		    	Surface[elem].panel_drag += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;
			}
		}
	}
if (Structure.openfoam == 3)
	{
	//pressure is given for each triagular element by *.pre file
	for (elem = 1 ; elem <= NOMBRE_SURFACES ; elem++)
		{
		
		bu[1] = Surface[elem].nx;	bu[2] = Surface[elem].ny;	bu[3] = Surface[elem].nz;
		bv[1] = Surface[elem].mx;	bv[2] = Surface[elem].my;	bv[3] = Surface[elem].mz;
		produit_vect3(bv, bu, normal);
		mod = sqrt(produit_scal(normal, normal));
		produit_scal_vect(1/mod, normal, normal);
		mod = sqrt(produit_scal(bu, bu));
		produit_scal_vect(1/mod, bu, tang1);
		produit_vect3(normal, tang1, tang2);
		
	   	XX1 = wf[yc(elem,1)];	YY1 = wf[yc(elem,2)];	ZZ1 = wf[yc(elem,3)];
		XX2 = wf[yc(elem,4)];	YY2 = wf[yc(elem,5)];	ZZ2 = wf[yc(elem,6)];
		XX3 = wf[yc(elem,7)];	YY3 = wf[yc(elem,8)];	ZZ3 = wf[yc(elem,9)];
		surface = surface_triangle2(XX1, YY1, ZZ1, XX2, YY2, ZZ2, XX3, YY3, ZZ3);
	
		/*
		printf("pression n %lf t1 %lf t2 %lf\n",Surface[elem].pressure_n,Surface[elem].pressure_t1,Surface[elem].pressure_t2);
		printf("bu:");		imprvectreel1(3, 3, bu);
		printf("bv:");		imprvectreel1(3, 3, bv);
		printf("normal:");	imprvectreel1(3, 3, normal);
		printf("tang1:");	imprvectreel1(3, 3, tang1);
		printf("tang2:");	imprvectreel1(3, 3, tang2);
		printf("pression (Pa) n %lf t1 %lf t2 %lf\n",Surface[elem].pressure_n,Surface[elem].pressure_t1,Surface[elem].pressure_t2);
		printf("surface (m2) %lf\n",surface);
		printf("FX (N) %lf  ",surface * (normal[1] * Surface[elem].pressure_n + tang1[1] * Surface[elem].pressure_t1 + tang2[1] * Surface[elem].pressure_t2));
		printf("FY (N) %lf  ",surface * (normal[2] * Surface[elem].pressure_n + tang1[2] * Surface[elem].pressure_t1 + tang2[2] * Surface[elem].pressure_t2));
		printf("FZ (N) %lf \n",surface * (normal[3] * Surface[elem].pressure_n + tang1[3] * Surface[elem].pressure_t1 + tang2[3] * Surface[elem].pressure_t2));
		*/
		
		//forces along X on the 3 vertex
		wasurf[yc(elem,1)] += surface * (normal[1] * Surface[elem].pressure_n + tang1[1] * Surface[elem].pressure_t1 + tang2[1] * Surface[elem].pressure_t2)/3.0;
		wasurf[yc(elem,4)] += surface * (normal[1] * Surface[elem].pressure_n + tang1[1] * Surface[elem].pressure_t1 + tang2[1] * Surface[elem].pressure_t2)/3.0;
		wasurf[yc(elem,7)] += surface * (normal[1] * Surface[elem].pressure_n + tang1[1] * Surface[elem].pressure_t1 + tang2[1] * Surface[elem].pressure_t2)/3.0;
		//forces along Y on the 3 vertex
		wasurf[yc(elem,2)] += surface * (normal[2] * Surface[elem].pressure_n + tang1[2] * Surface[elem].pressure_t1 + tang2[2] * Surface[elem].pressure_t2)/3.0;
		wasurf[yc(elem,5)] += surface * (normal[2] * Surface[elem].pressure_n + tang1[2] * Surface[elem].pressure_t1 + tang2[2] * Surface[elem].pressure_t2)/3.0;
		wasurf[yc(elem,8)] += surface * (normal[2] * Surface[elem].pressure_n + tang1[2] * Surface[elem].pressure_t1 + tang2[2] * Surface[elem].pressure_t2)/3.0;
		//forces along Z on the 3 vertex
		wasurf[yc(elem,3)] += surface * (normal[3] * Surface[elem].pressure_n + tang1[3] * Surface[elem].pressure_t1 + tang2[3] * Surface[elem].pressure_t2)/3.0;
		wasurf[yc(elem,6)] += surface * (normal[3] * Surface[elem].pressure_n + tang1[3] * Surface[elem].pressure_t1 + tang2[3] * Surface[elem].pressure_t2)/3.0;
		wasurf[yc(elem,9)] += surface * (normal[3] * Surface[elem].pressure_n + tang1[3] * Surface[elem].pressure_t1 + tang2[3] * Surface[elem].pressure_t2)/3.0;
		}
	//exit(0);
		
	}
}

