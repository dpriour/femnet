#define PRINCIPAL 0
#include "4c19.h"

void allongement2(int elem)
	/* Calcul des raideurs elemtaires dues a la tension  dans les elements(ie les bouts) */
	{
  	double dx,dy,dz,rl,dr2,dr,lo;

	/* wf contient les coordonnees de noeuds. */
  	dx = wf[yb(elem,4)]-wf[yb(elem,1)];
  	dy = wf[yb(elem,5)]-wf[yb(elem,2)];
  	dz = wf[yb(elem,6)]-wf[yb(elem,3)];
  	dr2 = dx*dx + dy*dy + dz*dz;
  	if (dr2 < 0.01 * Element[elem].lgrepos * 0.01 * Element[elem].lgrepos)
  		{
    		dr2 = 0.01 * Element[elem].lgrepos * 0.01 * Element[elem].lgrepos;
  		}
  
	/* Longueur de la barre apres deformation */  
  	dr  = sqrt(dr2);		
  	Element[elem].lgtendue = dr;
  
  
	/* Longueur de la barre au repos, donnee dans le fichier .mdf*/  
  	lo = Element[elem].lgrepos; 
  	rl = Element[elem].raideur_effective / (dr2 * dr);
  
  	/* Calcul des raideurs elementaires, dans les commentaires raideur[1][1] est la derivee de Fx1 par rapport a x1
  						raideur[1][2] est la derivee de Fx1 par rapport a y1
 	ou Fx1 est la composante selon l'axe des X de l'effort du a la tension, a l'extremite 1 du bout
  	(x1,y1,z1) et (x2,y2,z2) sont les composantes des extremites 1 et 2 du bout.*/
  	wd[1] = rl/lo*(dr2*dr-dr2*lo+lo*dx*dx); /*raideur [1][1], et [4][4], -raideur [1][4],[4][1]*/
  	wd[4] = rl/lo*(dr2*dr-dr2*lo+lo*dy*dy); /*raideur [2][2], et [5][5], -raideur [5][2] et [2][5]*/
  	wd[6] = rl/lo*(dr2*dr-dr2*lo+lo*dz*dz); /*raideur [3][3], et [6][6], -raideur [6][3] et [3][6]*/
  	wd[2] = rl*dx*dy;                       /*raideur [1][2], [2][1], [5][4] et [4][5] , -raideur [5][1], [4][2], [2][4] et [1][5]*/
  	wd[3] = rl*dx*dz;                       /*raideur [1][3], [3][1], [6][4] et [4][6] , -raideur [6][1], [1][6], [4][3] et [3][4]*/
  	wd[5] = rl*dy*dz;                       /*raideur [2][3], [3][2], [6][5] et [5][6] , -raideur [6][2], [2][6], [5][3] et [3][5]*/
  	
 	/*
 	printf("Nodes \n");
   	printf("%8.2lf %8.2lf %8.2lf %8.2lf %8.2lf %8.2lf \n",wf[yb(elem,1)],wf[yb(elem,2)],wf[yb(elem,3)],wf[yb(elem,4)],wf[yb(elem,5)],wf[yb(elem,6)]);
 	printf("K %d\n",elem);
  	
  	printf("%8.2lf %8.2lf %8.2lf %8.2lf %8.2lf %8.2lf \n",wd[1],wd[2],wd[3],-wd[1],-wd[2],-wd[3]);
  	printf("%8.2lf %8.2lf %8.2lf %8.2lf %8.2lf %8.2lf \n",wd[2],wd[4],wd[5],-wd[2],-wd[4],-wd[5]);
  	printf("%8.2lf %8.2lf %8.2lf %8.2lf %8.2lf %8.2lf \n",wd[3],wd[5],wd[6],-wd[3],-wd[5],-wd[6]);
  	printf("%8.2lf %8.2lf %8.2lf %8.2lf %8.2lf %8.2lf \n",-wd[1],-wd[2],-wd[3],wd[1],wd[2],wd[3]);
  	printf("%8.2lf %8.2lf %8.2lf %8.2lf %8.2lf %8.2lf \n",-wd[2],-wd[4],-wd[5],wd[2],wd[4],wd[5]);
  	printf("%8.2lf %8.2lf %8.2lf %8.2lf %8.2lf %8.2lf \n",-wd[3],-wd[5],-wd[6],wd[3],wd[5],wd[6]);
  	*/
  	
	}


