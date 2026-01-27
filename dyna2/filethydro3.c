#include "4c19.h"

void filethydro3()

{

/*efforts de trainee hydrodynamique agissant sur les fils du filet en tenant
compte de la proportion de la surface mouillee par rapport a la surface totale.
tient compte de la ponderation liee a la surface libre*/
  
int zg,zh,zi,zj;
double drag_tmp[4],depl_tmp[4];
double ba[4],Vw[4],nt[4];

Structure.surface_energy = 0;
  
for (zg = 1 ; zg <= NOMBRE_SURFACES ; zg++)
	{
	/*calcul des efforts de trainée dans le courant en prenant en compte la vitesse des sommets de l élément triangulaire*/ 
	/*numero des coordonnees selon x des 2 extremites de cet element*/
	zh = yc(zg,1);
	zi = yc(zg,4);
	zj = yc(zg,7);
	
	//zh extremite 1 //////////////////////////////////////////////////////
     	Vw[1] = mvh[zh+0]-mvb[zh+0];		//water speed
     	Vw[2] = mvh[zh+1]-mvb[zh+1];
     	Vw[3] = mvh[zh+2]-mvb[zh+2];
	
	//fils u 
	ba[1] = Surface[zg].nx;		//twine vector
	ba[2] = Surface[zg].ny;
	ba[3] = Surface[zg].nz;

	//printf("fil35 ba %5.2lf %5.2lf %5.2lf Vw  %5.2lf %5.2lf %5.2lf\n",ba[1],ba[2],ba[3],Vw[1],Vw[2],Vw[3]);
	
	basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
	wasurf[yc(zg,1)] += nt[1] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(zg,2)] += nt[2] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(zg,3)] += nt[3] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u

	drag_tmp[1] = nt[1];
	drag_tmp[2] = nt[2];
	drag_tmp[3] = nt[3];
    		
	//fils v
	ba[1] = Surface[zg].mx;
	ba[2] = Surface[zg].my;
	ba[3] = Surface[zg].mz;

	//printf("fil51 ba %5.2lf %5.2lf %5.2lf Vw  %5.2lf %5.2lf %5.2lf\n",ba[1],ba[2],ba[3],Vw[1],Vw[2],Vw[3]);
	basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
	wasurf[yc(zg,1)] += nt[1] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	wasurf[yc(zg,2)] += nt[2] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	wasurf[yc(zg,3)] += nt[3] * Surface[zg].pondFS[1] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v

	drag_tmp[1] += nt[1];
	drag_tmp[2] += nt[2];
	drag_tmp[3] += nt[3];
	
	depl_tmp[1] = wf[yc(zg,1)] -  wf1[yc(zg,1)];	//deplacement (m) of first vertex	
	depl_tmp[2] = wf[yc(zg,2)] -  wf1[yc(zg,2)];	
	depl_tmp[3] = wf[yc(zg,3)] -  wf1[yc(zg,3)];	
	Structure.surface_energy -= produit_scal(drag_tmp,depl_tmp);
		
	//zi extremite 2 //////////////////////////////////////////////////////
     	Vw[1] = mvh[zi+0]-mvb[zi+0];
     	Vw[2] = mvh[zi+1]-mvb[zi+1];
     	Vw[3] = mvh[zi+2]-mvb[zi+2];		
	
	//fils u 
	ba[1] = Surface[zg].nx;		//twine vector
	ba[2] = Surface[zg].ny;
	ba[3] = Surface[zg].nz;
	
	//printf("fil76 ba %5.2lf %5.2lf %5.2lf Vw  %5.2lf %5.2lf %5.2lf\n",ba[1],ba[2],ba[3],Vw[1],Vw[2],Vw[3]);
	basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
	wasurf[yc(zg,4)] += nt[1] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(zg,5)] += nt[2] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(zg,6)] += nt[3] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		
	drag_tmp[1] = nt[1];
	drag_tmp[2] = nt[2];
	drag_tmp[3] = nt[3];
    		
	//fils v
	ba[1] = Surface[zg].mx;
	ba[2] = Surface[zg].my;
	ba[3] = Surface[zg].mz;

	//printf("fil91 ba %5.2lf %5.2lf %5.2lf Vw  %5.2lf %5.2lf %5.2lf\n",ba[1],ba[2],ba[3],Vw[1],Vw[2],Vw[3]);
	basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
	wasurf[yc(zg,4)] += nt[1] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	wasurf[yc(zg,5)] += nt[2] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	wasurf[yc(zg,6)] += nt[3] * Surface[zg].pondFS[2] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
 
 	drag_tmp[1] += nt[1];
	drag_tmp[2] += nt[2];
	drag_tmp[3] += nt[3];
	
	depl_tmp[1] = wf[yc(zg,4)] -  wf1[yc(zg,4)];	//deplacement (m) of second vertex	
	depl_tmp[2] = wf[yc(zg,5)] -  wf1[yc(zg,5)];	
	depl_tmp[3] = wf[yc(zg,6)] -  wf1[yc(zg,6)];	
	Structure.surface_energy -= produit_scal(drag_tmp,depl_tmp);

 
 
   	//zj extremite 3 //////////////////////////////////////////////////////
     	Vw[1] = mvh[zj+0]-mvb[zj+0];
     	Vw[2] = mvh[zj+1]-mvb[zj+1];
     	Vw[3] = mvh[zj+2]-mvb[zj+2];		
	
	//fils u 
	ba[1] = Surface[zg].nx;		//twine vector
	ba[2] = Surface[zg].ny;
	ba[3] = Surface[zg].nz;
	
	//printf("fil118 ba %5.2lf %5.2lf %5.2lf Vw  %5.2lf %5.2lf %5.2lf\n",ba[1],ba[2],ba[3],Vw[1],Vw[2],Vw[3]);
	basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
	wasurf[yc(zg,7)] += nt[1] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(zg,8)] += nt[2] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
	wasurf[yc(zg,9)] += nt[3] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils u
		
	drag_tmp[1] = nt[1];
	drag_tmp[2] = nt[2];
	drag_tmp[3] = nt[3];
    		
	//fils v
	ba[1] = Surface[zg].mx;
	ba[2] = Surface[zg].my;
	ba[3] = Surface[zg].mz;

	//printf("fil133 ba %5.2lf %5.2lf %5.2lf Vw  %5.2lf %5.2lf %5.2lf\n",ba[1],ba[2],ba[3],Vw[1],Vw[2],Vw[3]);
	basic_bar_drag1(Surface[zg].diametrehydro, Surface[zg].lgrepos, Surface[zg].cdnormal, Surface[zg].ftangent, ba, Vw, nt);	//nt trainee (drag + lift) sur un seul fils u
	wasurf[yc(zg,7)] += nt[1] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	wasurf[yc(zg,8)] += nt[2] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
	wasurf[yc(zg,9)] += nt[3] * Surface[zg].pondFS[3] * Surface[zg].nb_cote_u_ou_v / 3.0;		//1/3 de la trainee de tous les fils v
 
 	drag_tmp[1] += nt[1];
	drag_tmp[2] += nt[2];
	drag_tmp[3] += nt[3];
	
	depl_tmp[1] = wf[yc(zg,7)] -  wf1[yc(zg,7)];	//deplacement (m) of second vertex	
	depl_tmp[2] = wf[yc(zg,8)] -  wf1[yc(zg,8)];	
	depl_tmp[3] = wf[yc(zg,9)] -  wf1[yc(zg,9)];	
	Structure.surface_energy -= produit_scal(drag_tmp,depl_tmp);
		
	Structure.surface_power = Structure.surface_energy/Pascalcul;
	}
}

