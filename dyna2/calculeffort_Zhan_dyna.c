#include "4c19.h"	
	
void calculeffort_zhan_dyna()

{

/*efforts de trainee hydrodynamique agissant sur les fils du filet en tenant
compte de la proportion de la surface mouillee par rapport a la surface totale.
prend en compte la ponderation liee a la surface libre*/
  
int zi,zj,zk,zl;
double ba[4],Vw[4],nt[4];
  
for (zi = 1 ; zi <= NOMBRE_SURFACES ; zi++)
	{
	/*numero des coordonnees selon x des 2 extremites de cet element*/
	zj = yc(zi,1);
	zk = yc(zi,4);
	zl = yc(zi,7);

	//zh extremite 1 //////////////////////////////////////////////////////
     	Vw[1] = mvh[zj+0]-mvb[zj+0];		//water speed
     	Vw[2] = mvh[zj+1]-mvb[zj+1];
     	Vw[3] = mvh[zj+2]-mvb[zj+2];
	//twine u
	ba[1] = Surface[zi].nx;
	ba[2] = Surface[zi].ny;
	ba[3] = Surface[zi].nz;
	calculeffort_Zhan(zi,Vw,ba);
	//twine v
	ba[1] = Surface[zi].mx;
	ba[2] = Surface[zi].my;
	ba[3] = Surface[zi].mz;
	calculeffort_Zhan(zi,Vw,ba);

	//zh extremite 2 //////////////////////////////////////////////////////
     	Vw[1] = mvh[zk+0]-mvb[zk+0];		//water speed
     	Vw[2] = mvh[zk+1]-mvb[zk+1];
     	Vw[3] = mvh[zk+2]-mvb[zk+2];
	//twine u
	ba[1] = Surface[zi].nx;
	ba[2] = Surface[zi].ny;
	ba[3] = Surface[zi].nz;
	calculeffort_Zhan(zi,Vw,ba);
	//twine v
	ba[1] = Surface[zi].mx;
	ba[2] = Surface[zi].my;
	ba[3] = Surface[zi].mz;
	calculeffort_Zhan(zi,Vw,ba);

	//zh extremite 3 //////////////////////////////////////////////////////
     	Vw[1] = mvh[zl+0]-mvb[zl+0];		//water speed
     	Vw[2] = mvh[zl+1]-mvb[zl+1];
     	Vw[3] = mvh[zl+2]-mvb[zl+2];
	//twine u
	ba[1] = Surface[zi].nx;
	ba[2] = Surface[zi].ny;
	ba[3] = Surface[zi].nz;
	calculeffort_Zhan(zi,Vw,ba);
	//twine v
	ba[1] = Surface[zi].mx;
	ba[2] = Surface[zi].my;
	ba[3] = Surface[zi].mz;
	calculeffort_Zhan(zi,Vw,ba);
	}
}
	

