#include "4c19.h"

void output_pressure(char *nomfichier)

{

/*efforts de trainee hydrodynamique agissant sur les fils du filet en tenant
compte de la proportion de la surface mouillee par rapport a la surface totale.
prend en compte la ponderation liee a la surface libre*/
  
int elem;
double bu[4],bv[4],Vw[4],nt[4],normal[4],tang1[4],tang2[4],hydro_force[4];
double mod,value,surface,XX1,XX2,XX3,YY1,YY2,YY3,ZZ1,ZZ2,ZZ3;
FILE   *file2;
char tonom[996];
 
strcpy(tonom,nomfichier);
strcat(tonom,".pre");	
file2 = fopen(tonom,"a");
for (elem = 1 ; elem <= NOMBRE_SURFACES ; elem++)
	{
	Vw[1] = Courant.vitesse*cos(Courant.direction*PI/180.0) * panneau[Surface[elem].type].current_reduction;
	Vw[2] = Courant.vitesse*sin(Courant.direction*PI/180.0) * panneau[Surface[elem].type].current_reduction;
	Vw[3] = 0.0                                             * panneau[Surface[elem].type].current_reduction;
	hydro_force[1] = 0.0;	hydro_force[2] = 0.0;	hydro_force[3] = 0.0;
	
	//extremites 1, 2 & 3 fils u
	bu[1] = Surface[elem].nx;	bu[2] = Surface[elem].ny;	bu[3] = Surface[elem].nz;
	if (produit_scal(bu,bu) == 0.0)
		{
		printf("filethydro4_sta\n");	
		printf("bu NULL\n");	
		}
	basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, bu, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
	hydro_force[1] += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	hydro_force[2] += nt[2] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	hydro_force[3] += nt[3] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	
	hydro_force[1] += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	hydro_force[2] += nt[2] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	hydro_force[3] += nt[3] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	
	hydro_force[1] += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	hydro_force[2] += nt[2] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	hydro_force[3] += nt[3] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	
	//extremite 1, 2 & 3 fils v
	bv[1] = Surface[elem].mx;	bv[2] = Surface[elem].my;	bv[3] = Surface[elem].mz;
	if (produit_scal(bv,bv) == 0.0)
		{
		printf("filethydro4_sta\n");	
		printf("bv NULL\n");	
		}
	basic_bar_drag1(Surface[elem].diametrehydro, Surface[elem].lgrepos, Surface[elem].cdnormal, Surface[elem].ftangent, bv, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
	hydro_force[1] += nt[1] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	hydro_force[2] += nt[2] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	hydro_force[3] += nt[3] * Surface[elem].pondFS[1] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v

	hydro_force[1] += nt[1] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	hydro_force[2] += nt[2] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	hydro_force[3] += nt[3] * Surface[elem].pondFS[2] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v

	hydro_force[1] += nt[1] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	hydro_force[2] += nt[2] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	hydro_force[3] += nt[3] * Surface[elem].pondFS[3] * Surface[elem].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
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
	printf("bu:");		imprvectreel1(3, 3, bu);
	printf("bv:");		imprvectreel1(3, 3, bv);
	printf("normal:");	imprvectreel1(3, 3, normal);
	printf("tang1:");	imprvectreel1(3, 3, tang1);
	printf("tang2:");	imprvectreel1(3, 3, tang2);
	printf("surface (m2) %lf ",surface);
	printf("FXYZ (N):");		imprvectreel1(3, 3, hydro_force);
	*/

	if (surface > 0.0)
		{
		value = produit_scal(hydro_force,normal);	value = value/surface;		fprintf(file2,"%lg ",value);
		//printf("normal value (Pa) %lf ",value);
		value = produit_scal(hydro_force,tang1); 	value = value/surface;		fprintf(file2,"%lg ",value);
		//printf("t1 value (Pa) %lf ",value);
		value = produit_scal(hydro_force,tang2); 	value = value/surface;		fprintf(file2,"%lg\n",value);
		//printf("t2 value (Pa) %lf\n",value);
		}
	else
		{
		value = 0.0;
		}
	}
fclose(file2);
}

