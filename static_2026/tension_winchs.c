#define PRINCIPAL 0
#include "4c19.h"

void tension_winchs()
{
	/* Calcul des efforts en chaque noeud issus de la tension des winch*/
  	int zh,zi,zg,zj,noeud1,noeud2;
  	double dx,dy,dz,l_zero,tension_w,raideur_effective,dr,dr2,rl,longu,long3;

  	/*prise en compte de la tension dans les winch*/
  	for (zg = 1 ; zg<= NOMBRE_WINCHS ; zg++)
  	{
    		for (zj = Winch[zg].nb_barre  ; zj>= 2; zj--) 
    			{
    			if ((Winch[zg].exit[zj+1] == 1) && (Winch[zg].exit[zj  ] == 1))
    				{
    				noeud1 = Winch[zg].noeud[zj+1];
    				noeud2 = Winch[zg].noeud[zj  ];
    				/*l_zero : longueur au repos de chaque barre*/
				l_zero = fabs(Winch[zg].prop[zj+1]-Winch[zg].prop[zj  ]) * Winch[zg].longueur_repos;
    				dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    				dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    				dz = wf[3*noeud1-0]-wf[3*noeud2-0];
  				dr2 = dx*dx + dy*dy + dz*dz;
  				dr  = sqrt(dr2);		
    				Winch[zg].longueur[zj] = dr;
    				if (dr > l_zero)	raideur_effective = Winch[zg].raideur_traction;
    				else			raideur_effective = Winch[zg].raideur_compression;
    				tension_w = (dr - l_zero) / l_zero * raideur_effective;
    				waelem[3*noeud1-2] -= dx/dr*tension_w;
    				waelem[3*noeud1-1] -= dy/dr*tension_w;
    				waelem[3*noeud1-0] -= dz/dr*tension_w;
    				waelem[3*noeud2-2] += dx/dr*tension_w;
    				waelem[3*noeud2-1] += dy/dr*tension_w;
				waelem[3*noeud2-0] += dz/dr*tension_w;
    				/*
				printf("noeuds %3d %3d ",noeud1,noeud2);
    				printf("l %6.3lf l_zero %6.3lf raideur %6.3lf ",Winch[zg].longueur[zj],l_zero,raideur_effective);
    				printf("tension dans la barre %3d = %6.3lf\n",zj,tension_w);
    				*/
				/*imprvectreel(36, waelem);*/
  				rl = raideur_effective / Winch[zg].longueur[zj] / Winch[zg].longueur[zj] / Winch[zg].longueur[zj];
  
  				/* Calcul des raideurs elementaires, dans les commentaires raideur[1][1] est la derivee de Fx1 par rapport a x1
  						raideur[1][2] est la derivee de Fx1 par rapport a y1
 				ou Fx1 est la composante selon l'axe des X de l'effort du a la tension, a l'extremite 1 du bout
  				(x1,y1,z1) et (x2,y2,z2) sont les composantes des extremites 1 et 2 du bout.*/
  				wd[1] = rl/l_zero*(dr2*dr-dr2*l_zero+l_zero*dx*dx); /*raideur [1][1], et [4][4], -raideur [1][4],[4][1]*/
  				wd[4] = rl/l_zero*(dr2*dr-dr2*l_zero+l_zero*dy*dy); /*raideur [2][2], et [5][5], -raideur [5][2] et [2][5]*/
  				wd[6] = rl/l_zero*(dr2*dr-dr2*l_zero+l_zero*dz*dz); /*raideur [3][3], et [6][6], -raideur [6][3] et [3][6]*/
  				wd[2] = rl*dx*dy;                       /*raideur [1][2], [2][1], [5][4] et [4][5] , -raideur [5][1], [4][2], [2][4] et [1][5]*/
  				wd[3] = rl*dx*dz;                       /*raideur [1][3], [3][1], [6][4] et [4][6] , -raideur [6][1], [1][6], [4][3] et [3][4]*/
  				wd[5] = rl*dy*dz;                       /*raideur [2][3], [3][2], [6][5] et [5][6] , -raideur [6][2], [2][6], [5][3] et [3][5]*/
  				
				zh = 3*noeud1-2;
				zi = 3*noeud2-2;
				
				if (Structure.type_solver == 1)
				{
					ze[zh  ][eca  ] += wd[1];    	ze[zh  ][eca+1] += wd[2];    	ze[zh  ][eca+2] += wd[3];
					ze[zh+1][eca-1] += wd[2];    	ze[zh+1][eca  ] += wd[4];    	ze[zh+1][eca+1] += wd[5];
					ze[zh+2][eca-2] += wd[3];    	ze[zh+2][eca-1] += wd[5];    	ze[zh+2][eca  ] += wd[6];
	
					ze[zi  ][eca  ] += wd[1];    	ze[zi  ][eca+1] += wd[2];    	ze[zi  ][eca+2] += wd[3];
					ze[zi+1][eca-1] += wd[2];    	ze[zi+1][eca  ] += wd[4];    	ze[zi+1][eca+1] += wd[5];
					ze[zi+2][eca-2] += wd[3];    	ze[zi+2][eca-1] += wd[5];    	ze[zi+2][eca  ] += wd[6];

					ze[zh  ][eca+zi-zh  ] -= wd[1];	ze[zh  ][eca+zi-zh+1] -= wd[2];	ze[zh  ][eca+zi-zh+2] -= wd[3];
					ze[zh+1][eca+zi-zh-1] -= wd[2];	ze[zh+1][eca+zi-zh  ] -= wd[4];	ze[zh+1][eca+zi-zh+1] -= wd[5];
					ze[zh+2][eca+zi-zh-2] -= wd[3];	ze[zh+2][eca+zi-zh-1] -= wd[5];	ze[zh+2][eca+zi-zh  ] -= wd[6];

					ze[zi  ][eca-zi+zh  ] -= wd[1];	ze[zi  ][eca-zi+zh+1] -= wd[2];	ze[zi  ][eca-zi+zh+2] -= wd[3];
					ze[zi+1][eca-zi+zh-1] -= wd[2];	ze[zi+1][eca-zi+zh  ] -= wd[4];	ze[zi+1][eca-zi+zh+1] -= wd[5];
					ze[zi+2][eca-zi+zh-2] -= wd[3];	ze[zi+2][eca-zi+zh-1] -= wd[5];	ze[zi+2][eca-zi+zh  ] -= wd[6];

					if (rang[1][zh  ] < zi+2) rang[1][zh  ] = zi+2; 
					if (rang[1][zh+1] < zi+2) rang[1][zh+1] = zi+2; 
					if (rang[1][zh+2] < zi+2) rang[1][zh+2] = zi+2; 

					if (rang[2][zh  ] < zi+2) rang[2][zh  ] = zi+2; 
					if (rang[2][zh+1] < zi+2) rang[2][zh+1] = zi+2; 
					if (rang[2][zh+2] < zi+2) rang[2][zh+2] = zi+2;

					if (rang[3][zh  ] > zh  ) rang[3][zh  ] = zh  ; 
					if (rang[3][zh+1] > zh  ) rang[3][zh+1] = zh  ; 
					if (rang[3][zh+2] > zh  ) rang[3][zh+2] = zh  ; 

					if (rang[4][zh  ] > zh  ) rang[4][zh  ] = zh  ; 
					if (rang[4][zh+1] > zh  ) rang[4][zh+1] = zh  ; 
					if (rang[4][zh+2] > zh  ) rang[4][zh+2] = zh  ;

					if (rang[1][zi  ] < zi+2) rang[1][zi  ] = zi+2; 
					if (rang[1][zi+1] < zi+2) rang[1][zi+1] = zi+2; 
					if (rang[1][zi+2] < zi+2) rang[1][zi+2] = zi+2; 

					if (rang[2][zi  ] < zi+2) rang[2][zi  ] = zi+2; 
					if (rang[2][zi+1] < zi+2) rang[2][zi+1] = zi+2; 
					if (rang[2][zi+2] < zi+2) rang[2][zi+2] = zi+2;

					if (rang[3][zi  ] > zh  ) rang[3][zi  ] = zh  ; 
					if (rang[3][zi+1] > zh  ) rang[3][zi+1] = zh  ; 
					if (rang[3][zi+2] > zh  ) rang[3][zi+2] = zh  ; 

					if (rang[4][zi  ] > zh  ) rang[4][zi  ] = zh  ; 
					if (rang[4][zi+1] > zh  ) rang[4][zi+1] = zh  ; 
					if (rang[4][zi+2] > zh  ) rang[4][zi+2] = zh  ;
				}
				else if (Structure.type_solver == 2)
			      	{
					affectation_pardiso(wd[1], zh, zh);	affectation_pardiso(wd[2], zh, zh+1);	affectation_pardiso(wd[3], zh, zh+2);
					affectation_pardiso(wd[2], zh+1, zh);	affectation_pardiso(wd[4], zh+1, zh+1);	affectation_pardiso(wd[5], zh+1, zh+2);
					affectation_pardiso(wd[3], zh+2, zh);	affectation_pardiso(wd[5], zh+2, zh+1);	affectation_pardiso(wd[6], zh+2, zh+2);

					affectation_pardiso(wd[1], zi, zi);	affectation_pardiso(wd[2], zi, zi+1);	affectation_pardiso(wd[3], zi, zi+2);
					affectation_pardiso(wd[2], zi+1, zi);	affectation_pardiso(wd[4], zi+1, zi+1);	affectation_pardiso(wd[5], zi+1, zi+2);
					affectation_pardiso(wd[3], zi+2, zi);	affectation_pardiso(wd[5], zi+2, zi+1);	affectation_pardiso(wd[6], zi+2, zi+2);

					affectation_pardiso(-wd[1], zh, zi);	affectation_pardiso(-wd[2], zh, zi+1);	 affectation_pardiso(-wd[3], zh, zi+2);
					affectation_pardiso(-wd[2], zh+1, zi);	affectation_pardiso(-wd[4], zh+1, zi+1); affectation_pardiso(-wd[5], zh+1, zi+2);
					affectation_pardiso(-wd[3], zh+2, zi);	affectation_pardiso(-wd[5], zh+2, zi+1); affectation_pardiso(-wd[6], zh+2, zi+2);

					affectation_pardiso(-wd[1], zi, zh);	affectation_pardiso(-wd[2], zi, zh+1);	 affectation_pardiso(-wd[3], zi, zh+2);
					affectation_pardiso(-wd[2], zi+1, zh);	affectation_pardiso(-wd[4], zi+1, zh+1); affectation_pardiso(-wd[5], zi+1, zh+2);
					affectation_pardiso(-wd[3], zi+2, zh);	affectation_pardiso(-wd[5], zi+2, zh+1); affectation_pardiso(-wd[6], zi+2, zh+2);

					if (rang[1][zh  ] < zi+2) rang[1][zh  ] = zi+2; 
					if (rang[1][zh+1] < zi+2) rang[1][zh+1] = zi+2; 
					if (rang[1][zh+2] < zi+2) rang[1][zh+2] = zi+2; 

					if (rang[2][zh  ] < zi+2) rang[2][zh  ] = zi+2; 
					if (rang[2][zh+1] < zi+2) rang[2][zh+1] = zi+2; 
					if (rang[2][zh+2] < zi+2) rang[2][zh+2] = zi+2;

					if (rang[3][zh  ] > zh  ) rang[3][zh  ] = zh  ; 
					if (rang[3][zh+1] > zh  ) rang[3][zh+1] = zh  ; 
					if (rang[3][zh+2] > zh  ) rang[3][zh+2] = zh  ; 

					if (rang[4][zh  ] > zh  ) rang[4][zh  ] = zh  ; 
					if (rang[4][zh+1] > zh  ) rang[4][zh+1] = zh  ; 
					if (rang[4][zh+2] > zh  ) rang[4][zh+2] = zh  ;

					if (rang[1][zi  ] < zi+2) rang[1][zi  ] = zi+2; 
					if (rang[1][zi+1] < zi+2) rang[1][zi+1] = zi+2; 
					if (rang[1][zi+2] < zi+2) rang[1][zi+2] = zi+2; 

					if (rang[2][zi  ] < zi+2) rang[2][zi  ] = zi+2; 
					if (rang[2][zi+1] < zi+2) rang[2][zi+1] = zi+2; 
					if (rang[2][zi+2] < zi+2) rang[2][zi+2] = zi+2;

					if (rang[3][zi  ] > zh  ) rang[3][zi  ] = zh  ; 
					if (rang[3][zi+1] > zh  ) rang[3][zi+1] = zh  ; 
					if (rang[3][zi+2] > zh  ) rang[3][zi+2] = zh  ; 

					if (rang[4][zi  ] > zh  ) rang[4][zi  ] = zh  ; 
					if (rang[4][zi+1] > zh  ) rang[4][zi+1] = zh  ; 
					if (rang[4][zi+2] > zh  ) rang[4][zi+2] = zh  ;
			      	}

    			}
    			if ((Winch[zg].exit[zj+1] == 1) && (Winch[zg].exit[zj  ] == 0))
    			{
    				noeud1 = Winch[zg].noeud[zj+1];
    				noeud2 = Winch[zg].noeud[1   ];
				zh = 3*noeud1-2;
				zi = 3*noeud2-2;
				
    				dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    				dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    				dz = wf[3*noeud1-0]-wf[3*noeud2-0];
    				Winch[zg].longueur[zj] = sqrt(dx*dx + dy*dy + dz*dz);
    				longu = sqrt(dx*dx + dy*dy + dz*dz);
    				long3 = longu*longu*longu;
    				tension_w = Winch[zg].adjust_force;
    				waelem[3*noeud1-2] -= dx/longu*tension_w;
    				waelem[3*noeud1-1] -= dy/longu*tension_w;
    				waelem[3*noeud1-0] -= dz/longu*tension_w;
    				waelem[3*noeud2-2] += dx/longu*tension_w;
    				waelem[3*noeud2-1] += dy/longu*tension_w;
    				waelem[3*noeud2-0] += dz/longu*tension_w;
    				/*
    				printf("noeuds %3d %3d ",noeud1,noeud2);
    				printf("tension dans la barre %3d = %6.3lf\n",zj,tension_w);
    				*/
  				
				wd[1] = tension_w/longu-dx*dx*tension_w/long3; 	/*raideur [1][1], et [4][4], -raideur [1][4] et [4][1]*/
				wd[4] = tension_w/longu-dy*dy*tension_w/long3; 	/*raideur [2][2], et [5][5], -raideur [5][2] et [2][5]*/
				wd[6] = tension_w/longu-dz*dz*tension_w/long3; 	/*raideur [3][3], et [6][6], -raideur [6][3] et [3][6]*/
				wd[2] = -dy*tension_w*dx/long3;			/*raideur [1][2], [2][1], [5][4] et [4][5] , -raideur [5][1], [4][2], [2][4] et [1][5]*/
				wd[3] = -dx*tension_w*dz/long3;			/*raideur [1][3], [3][1], [6][4] et [4][6] , -raideur [6][1], [1][6], [4][3] et [3][4]*/
				wd[5] = -dy*tension_w*dz/long3;			/*raideur [2][3], [3][2], [6][5] et [5][6] , -raideur [6][2], [2][6], [5][3] et [3][5]*/

				zh = 3*noeud1-2;
				zi = 3*noeud2-2;
				
				if (Structure.type_solver == 1)
				{
					ze[zh  ][eca  ] += wd[1];    	ze[zh  ][eca+1] += wd[2];    	ze[zh  ][eca+2] += wd[3];
					ze[zh+1][eca-1] += wd[2];    	ze[zh+1][eca  ] += wd[4];    	ze[zh+1][eca+1] += wd[5];
					ze[zh+2][eca-2] += wd[3];    	ze[zh+2][eca-1] += wd[5];    	ze[zh+2][eca  ] += wd[6];
	
					ze[zi  ][eca  ] += wd[1];    	ze[zi  ][eca+1] += wd[2];    	ze[zi  ][eca+2] += wd[3];
					ze[zi+1][eca-1] += wd[2];    	ze[zi+1][eca  ] += wd[4];    	ze[zi+1][eca+1] += wd[5];
					ze[zi+2][eca-2] += wd[3];    	ze[zi+2][eca-1] += wd[5];    	ze[zi+2][eca  ] += wd[6];

					ze[zh  ][eca+zi-zh  ] -= wd[1];	ze[zh  ][eca+zi-zh+1] -= wd[2];	ze[zh  ][eca+zi-zh+2] -= wd[3];
					ze[zh+1][eca+zi-zh-1] -= wd[2];	ze[zh+1][eca+zi-zh  ] -= wd[4];	ze[zh+1][eca+zi-zh+1] -= wd[5];
					ze[zh+2][eca+zi-zh-2] -= wd[3];	ze[zh+2][eca+zi-zh-1] -= wd[5];	ze[zh+2][eca+zi-zh  ] -= wd[6];

					ze[zi  ][eca-zi+zh  ] -= wd[1];	ze[zi  ][eca-zi+zh+1] -= wd[2];	ze[zi  ][eca-zi+zh+2] -= wd[3];
					ze[zi+1][eca-zi+zh-1] -= wd[2];	ze[zi+1][eca-zi+zh  ] -= wd[4];	ze[zi+1][eca-zi+zh+1] -= wd[5];
					ze[zi+2][eca-zi+zh-2] -= wd[3];	ze[zi+2][eca-zi+zh-1] -= wd[5];	ze[zi+2][eca-zi+zh  ] -= wd[6];

					if (rang[1][zh  ] < zi+2) rang[1][zh  ] = zi+2; 
					if (rang[1][zh+1] < zi+2) rang[1][zh+1] = zi+2; 
					if (rang[1][zh+2] < zi+2) rang[1][zh+2] = zi+2; 

					if (rang[2][zh  ] < zi+2) rang[2][zh  ] = zi+2; 
					if (rang[2][zh+1] < zi+2) rang[2][zh+1] = zi+2; 
					if (rang[2][zh+2] < zi+2) rang[2][zh+2] = zi+2;

					if (rang[3][zh  ] > zh  ) rang[3][zh  ] = zh  ; 
					if (rang[3][zh+1] > zh  ) rang[3][zh+1] = zh  ; 
					if (rang[3][zh+2] > zh  ) rang[3][zh+2] = zh  ; 

					if (rang[4][zh  ] > zh  ) rang[4][zh  ] = zh  ; 
					if (rang[4][zh+1] > zh  ) rang[4][zh+1] = zh  ; 
					if (rang[4][zh+2] > zh  ) rang[4][zh+2] = zh  ;

					if (rang[1][zi  ] < zi+2) rang[1][zi  ] = zi+2; 
					if (rang[1][zi+1] < zi+2) rang[1][zi+1] = zi+2; 
					if (rang[1][zi+2] < zi+2) rang[1][zi+2] = zi+2; 

					if (rang[2][zi  ] < zi+2) rang[2][zi  ] = zi+2; 
					if (rang[2][zi+1] < zi+2) rang[2][zi+1] = zi+2; 
					if (rang[2][zi+2] < zi+2) rang[2][zh+2] = zi+2;

					if (rang[3][zi  ] > zh  ) rang[3][zi  ] = zh  ; 
					if (rang[3][zi+1] > zh  ) rang[3][zi+1] = zh  ; 
					if (rang[3][zi+2] > zh  ) rang[3][zi+2] = zh  ; 

					if (rang[4][zi  ] > zh  ) rang[4][zi  ] = zh  ; 
					if (rang[4][zi+1] > zh  ) rang[4][zi+1] = zh  ; 
					if (rang[4][zi+2] > zh  ) rang[4][zi+2] = zh  ;
				}
 				else if (Structure.type_solver == 2)
			      	{
					affectation_pardiso(wd[1], zh, zh);	affectation_pardiso(wd[2], zh, zh+1);	affectation_pardiso(wd[3], zh, zh+2);
					affectation_pardiso(wd[2], zh+1, zh);	affectation_pardiso(wd[4], zh+1, zh+1);	affectation_pardiso(wd[5], zh+1, zh+2);
					affectation_pardiso(wd[3], zh+2, zh);	affectation_pardiso(wd[5], zh+2, zh+1);	affectation_pardiso(wd[6], zh+2, zh+2);

					affectation_pardiso(wd[1], zi, zi);	affectation_pardiso(wd[2], zi, zi+1);	affectation_pardiso(wd[3], zi, zi+2);
					affectation_pardiso(wd[2], zi+1, zi);	affectation_pardiso(wd[4], zi+1, zi+1);	affectation_pardiso(wd[5], zi+1, zi+2);
					affectation_pardiso(wd[3], zi+2, zi);	affectation_pardiso(wd[5], zi+2, zi+1);	affectation_pardiso(wd[6], zi+2, zi+2);

					affectation_pardiso(-wd[1], zh, zi);	affectation_pardiso(-wd[2], zh, zi+1);	 affectation_pardiso(-wd[3], zh, zi+2);
					affectation_pardiso(-wd[2], zh+1, zi);	affectation_pardiso(-wd[4], zh+1, zi+1); affectation_pardiso(-wd[5], zh+1, zi+2);
					affectation_pardiso(-wd[3], zh+2, zi);	affectation_pardiso(-wd[5], zh+2, zi+1); affectation_pardiso(-wd[6], zh+2, zi+2);

					affectation_pardiso(-wd[1], zi, zh);	affectation_pardiso(-wd[2], zi, zh+1);	 affectation_pardiso(-wd[3], zi, zh+2);
					affectation_pardiso(-wd[2], zi+1, zh);	affectation_pardiso(-wd[4], zi+1, zh+1); affectation_pardiso(-wd[5], zi+1, zh+2);
					affectation_pardiso(-wd[3], zi+2, zh);	affectation_pardiso(-wd[5], zi+2, zh+1); affectation_pardiso(-wd[6], zi+2, zh+2);

					if (rang[1][zh  ] < zi+2) rang[1][zh  ] = zi+2; 
					if (rang[1][zh+1] < zi+2) rang[1][zh+1] = zi+2; 
					if (rang[1][zh+2] < zi+2) rang[1][zh+2] = zi+2; 

					if (rang[2][zh  ] < zi+2) rang[2][zh  ] = zi+2; 
					if (rang[2][zh+1] < zi+2) rang[2][zh+1] = zi+2; 
					if (rang[2][zh+2] < zi+2) rang[2][zh+2] = zi+2;

					if (rang[3][zh  ] > zh  ) rang[3][zh  ] = zh  ; 
					if (rang[3][zh+1] > zh  ) rang[3][zh+1] = zh  ; 
					if (rang[3][zh+2] > zh  ) rang[3][zh+2] = zh  ; 

					if (rang[4][zh  ] > zh  ) rang[4][zh  ] = zh  ; 
					if (rang[4][zh+1] > zh  ) rang[4][zh+1] = zh  ; 
					if (rang[4][zh+2] > zh  ) rang[4][zh+2] = zh  ;

					if (rang[1][zi  ] < zi+2) rang[1][zi  ] = zi+2; 
					if (rang[1][zi+1] < zi+2) rang[1][zi+1] = zi+2; 
					if (rang[1][zi+2] < zi+2) rang[1][zi+2] = zi+2; 

					if (rang[2][zi  ] < zi+2) rang[2][zi  ] = zi+2; 
					if (rang[2][zi+1] < zi+2) rang[2][zi+1] = zi+2; 
					if (rang[2][zi+2] < zi+2) rang[2][zh+2] = zi+2;

					if (rang[3][zi  ] > zh  ) rang[3][zi  ] = zh  ; 
					if (rang[3][zi+1] > zh  ) rang[3][zi+1] = zh  ; 
					if (rang[3][zi+2] > zh  ) rang[3][zi+2] = zh  ; 

					if (rang[4][zi  ] > zh  ) rang[4][zi  ] = zh  ; 
					if (rang[4][zi+1] > zh  ) rang[4][zi+1] = zh  ; 
					if (rang[4][zi+2] > zh  ) rang[4][zi+2] = zh  ;
			      	}
    			}
    		}
  
  	/*premiere barre*/
  	zj = 1;
  	if ((Winch[zg].exit[zj+1] == 1) && (Winch[zg].exit[zj  ] == 0))
  	{
    		noeud1 = Winch[zg].noeud[zj+1];
    		noeud2 = Winch[zg].noeud[zj  ];
    		dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    		dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    		dz = wf[3*noeud1-0]-wf[3*noeud2-0];
  		dr2 = dx*dx + dy*dy + dz*dz;
  		dr  = sqrt(dr2);		
    		Winch[zg].longueur[zj] = dr;
    		if (dr > l_zero)	raideur_effective = Winch[zg].raideur_traction;
    		else			raideur_effective = Winch[zg].raideur_compression;
    		tension_w = (dr - l_zero) / l_zero * raideur_effective;
    		if (tension_w > Winch[zg].adjust_force)
    		{
    			waelem[3*noeud1-2] -= dx/dr*tension_w;
    			waelem[3*noeud1-1] -= dy/dr*tension_w;
    			waelem[3*noeud1-0] -= dz/dr*tension_w;
    			waelem[3*noeud2-2] += dx/dr*tension_w;
    			waelem[3*noeud2-1] += dy/dr*tension_w;
			waelem[3*noeud2-0] += dz/dr*tension_w;
    			/*
			printf("noeuds %3d %3d ",noeud1,noeud2);
    			printf("l %6.3lf l_zero %6.3lf raideur %6.3lf ",Winch[zg].longueur[zj],l_zero,raideur_effective);
    			printf("tension dans la barre %3d = %6.3lf\n",zj,tension_w);
    			*/
			/*imprvectreel(36, waelem);*/
  			rl = raideur_effective / Winch[zg].longueur[zj] / Winch[zg].longueur[zj] / Winch[zg].longueur[zj];
 
  			/* Calcul des raideurs elementaires, dans les commentaires raideur[1][1] est la derivee de Fx1 par rapport a x1
  			raideur[1][2] est la derivee de Fx1 par rapport a y1
 			ou Fx1 est la composante selon l'axe des X de l'effort du a la tension, a l'extremite 1 du bout
  			(x1,y1,z1) et (x2,y2,z2) sont les composantes des extremites 1 et 2 du bout.*/
  			wd[1] = rl/l_zero*(dr2*dr-dr2*l_zero+l_zero*dx*dx); /*raideur [1][1], et [4][4], -raideur [1][4],[4][1]*/
  			wd[4] = rl/l_zero*(dr2*dr-dr2*l_zero+l_zero*dy*dy); /*raideur [2][2], et [5][5], -raideur [5][2] et [2][5]*/
  			wd[6] = rl/l_zero*(dr2*dr-dr2*l_zero+l_zero*dz*dz); /*raideur [3][3], et [6][6], -raideur [6][3] et [3][6]*/
  			wd[2] = rl*dx*dy;                       /*raideur [1][2], [2][1], [5][4] et [4][5] , -raideur [5][1], [4][2], [2][4] et [1][5]*/
  			wd[3] = rl*dx*dz;                       /*raideur [1][3], [3][1], [6][4] et [4][6] , -raideur [6][1], [1][6], [4][3] et [3][4]*/
  			wd[5] = rl*dy*dz;                       /*raideur [2][3], [3][2], [6][5] et [5][6] , -raideur [6][2], [2][6], [5][3] et [3][5]*/
  			
			zh = 3*noeud1-2;
			zi = 3*noeud2-2;
			
			if (Structure.type_solver == 1)
			{
				ze[zh  ][eca  ] += wd[1];    	ze[zh  ][eca+1] += wd[2];    	ze[zh  ][eca+2] += wd[3];
				ze[zh+1][eca-1] += wd[2];    	ze[zh+1][eca  ] += wd[4];    	ze[zh+1][eca+1] += wd[5];
				ze[zh+2][eca-2] += wd[3];    	ze[zh+2][eca-1] += wd[5];    	ze[zh+2][eca  ] += wd[6];

				ze[zi  ][eca  ] += wd[1];    	ze[zi  ][eca+1] += wd[2];    	ze[zi  ][eca+2] += wd[3];
				ze[zi+1][eca-1] += wd[2];    	ze[zi+1][eca  ] += wd[4];    	ze[zi+1][eca+1] += wd[5];
				ze[zi+2][eca-2] += wd[3];    	ze[zi+2][eca-1] += wd[5];    	ze[zi+2][eca  ] += wd[6];

				ze[zh  ][eca+zi-zh  ] -= wd[1];	ze[zh  ][eca+zi-zh+1] -= wd[2];	ze[zh  ][eca+zi-zh+2] -= wd[3];
				ze[zh+1][eca+zi-zh-1] -= wd[2];	ze[zh+1][eca+zi-zh  ] -= wd[4];	ze[zh+1][eca+zi-zh+1] -= wd[5];
				ze[zh+2][eca+zi-zh-2] -= wd[3];	ze[zh+2][eca+zi-zh-1] -= wd[5];	ze[zh+2][eca+zi-zh  ] -= wd[6];

				ze[zi  ][eca-zi+zh  ] -= wd[1];	ze[zi  ][eca-zi+zh+1] -= wd[2];	ze[zi  ][eca-zi+zh+2] -= wd[3];
				ze[zi+1][eca-zi+zh-1] -= wd[2];	ze[zi+1][eca-zi+zh  ] -= wd[4];	ze[zi+1][eca-zi+zh+1] -= wd[5];
				ze[zi+2][eca-zi+zh-2] -= wd[3];	ze[zi+2][eca-zi+zh-1] -= wd[5];	ze[zi+2][eca-zi+zh  ] -= wd[6];

				if (rang[1][zh  ] < zi+2) rang[1][zh  ] = zi+2; 
				if (rang[1][zh+1] < zi+2) rang[1][zh+1] = zi+2; 
				if (rang[1][zh+2] < zi+2) rang[1][zh+2] = zi+2; 
				if (rang[2][zh  ] < zi+2) rang[2][zh  ] = zi+2; 
				if (rang[2][zh+1] < zi+2) rang[2][zh+1] = zi+2; 
				if (rang[2][zh+2] < zi+2) rang[2][zh+2] = zi+2;
				if (rang[3][zh  ] > zh  ) rang[3][zh  ] = zh  ; 
				if (rang[3][zh+1] > zh  ) rang[3][zh+1] = zh  ; 
				if (rang[3][zh+2] > zh  ) rang[3][zh+2] = zh  ; 
				if (rang[4][zh  ] > zh  ) rang[4][zh  ] = zh  ; 
				if (rang[4][zh+1] > zh  ) rang[4][zh+1] = zh  ; 
				if (rang[4][zh+2] > zh  ) rang[4][zh+2] = zh  ;
				if (rang[1][zi  ] < zi+2) rang[1][zi  ] = zi+2; 
				if (rang[1][zi+1] < zi+2) rang[1][zi+1] = zi+2; 
				if (rang[1][zi+2] < zi+2) rang[1][zi+2] = zi+2; 
				if (rang[2][zi  ] < zi+2) rang[2][zi  ] = zi+2; 
				if (rang[2][zi+1] < zi+2) rang[2][zi+1] = zi+2; 
				if (rang[2][zi+2] < zi+2) rang[2][zh+2] = zi+2;
				if (rang[3][zi  ] > zh  ) rang[3][zi  ] = zh  ; 
				if (rang[3][zi+1] > zh  ) rang[3][zi+1] = zh  ; 
				if (rang[3][zi+2] > zh  ) rang[3][zi+2] = zh  ; 
				if (rang[4][zi  ] > zh  ) rang[4][zi  ] = zh  ; 
				if (rang[4][zi+1] > zh  ) rang[4][zi+1] = zh  ; 
				if (rang[4][zi+2] > zh  ) rang[4][zi+2] = zh  ;
			}
			else if (Structure.type_solver == 2)
			{
				affectation_pardiso(wd[1], zh, zh);	affectation_pardiso(wd[2], zh, zh+1);	affectation_pardiso(wd[3], zh, zh+2);
				affectation_pardiso(wd[2], zh+1, zh);	affectation_pardiso(wd[4], zh+1, zh+1);	affectation_pardiso(wd[5], zh+1, zh+2);
				affectation_pardiso(wd[3], zh+2, zh);	affectation_pardiso(wd[5], zh+2, zh+1);	affectation_pardiso(wd[6], zh+2, zh+2);

				affectation_pardiso(wd[1], zi, zi);	affectation_pardiso(wd[2], zi, zi+1);	affectation_pardiso(wd[3], zi, zi+2);
				affectation_pardiso(wd[2], zi+1, zi);	affectation_pardiso(wd[4], zi+1, zi+1);	affectation_pardiso(wd[5], zi+1, zi+2);
				affectation_pardiso(wd[3], zi+2, zi);	affectation_pardiso(wd[5], zi+2, zi+1);	affectation_pardiso(wd[6], zi+2, zi+2);

				affectation_pardiso(-wd[1], zh, zi);	affectation_pardiso(-wd[2], zh, zi+1);	 affectation_pardiso(-wd[3], zh, zi+2);
				affectation_pardiso(-wd[2], zh+1, zi);	affectation_pardiso(-wd[4], zh+1, zi+1); affectation_pardiso(-wd[5], zh+1, zi+2);
				affectation_pardiso(-wd[3], zh+2, zi);	affectation_pardiso(-wd[5], zh+2, zi+1); affectation_pardiso(-wd[6], zh+2, zi+2);

				affectation_pardiso(-wd[1], zi, zh);	affectation_pardiso(-wd[2], zi, zh+1);	 affectation_pardiso(-wd[3], zi, zh+2);
				affectation_pardiso(-wd[2], zi+1, zh);	affectation_pardiso(-wd[4], zi+1, zh+1); affectation_pardiso(-wd[5], zi+1, zh+2);
				affectation_pardiso(-wd[3], zi+2, zh);	affectation_pardiso(-wd[5], zi+2, zh+1); affectation_pardiso(-wd[6], zi+2, zh+2);

				if (rang[1][zh  ] < zi+2) rang[1][zh  ] = zi+2; 
				if (rang[1][zh+1] < zi+2) rang[1][zh+1] = zi+2; 
				if (rang[1][zh+2] < zi+2) rang[1][zh+2] = zi+2; 
				if (rang[2][zh  ] < zi+2) rang[2][zh  ] = zi+2; 
				if (rang[2][zh+1] < zi+2) rang[2][zh+1] = zi+2; 
				if (rang[2][zh+2] < zi+2) rang[2][zh+2] = zi+2;
				if (rang[3][zh  ] > zh  ) rang[3][zh  ] = zh  ; 
				if (rang[3][zh+1] > zh  ) rang[3][zh+1] = zh  ; 
				if (rang[3][zh+2] > zh  ) rang[3][zh+2] = zh  ; 
				if (rang[4][zh  ] > zh  ) rang[4][zh  ] = zh  ; 
				if (rang[4][zh+1] > zh  ) rang[4][zh+1] = zh  ; 
				if (rang[4][zh+2] > zh  ) rang[4][zh+2] = zh  ;
				if (rang[1][zi  ] < zi+2) rang[1][zi  ] = zi+2; 
				if (rang[1][zi+1] < zi+2) rang[1][zi+1] = zi+2; 
				if (rang[1][zi+2] < zi+2) rang[1][zi+2] = zi+2; 
				if (rang[2][zi  ] < zi+2) rang[2][zi  ] = zi+2; 
				if (rang[2][zi+1] < zi+2) rang[2][zi+1] = zi+2; 
				if (rang[2][zi+2] < zi+2) rang[2][zh+2] = zi+2;
				if (rang[3][zi  ] > zh  ) rang[3][zi  ] = zh  ; 
				if (rang[3][zi+1] > zh  ) rang[3][zi+1] = zh  ; 
				if (rang[3][zi+2] > zh  ) rang[3][zi+2] = zh  ; 
				if (rang[4][zi  ] > zh  ) rang[4][zi  ] = zh  ; 
				if (rang[4][zi+1] > zh  ) rang[4][zi+1] = zh  ; 
				if (rang[4][zi+2] > zh  ) rang[4][zi+2] = zh  ;
			}
		}
    		else
    		{
    			tension_w = Winch[zg].adjust_force;
    			waelem[3*noeud1-2] -= dx/Winch[zg].longueur[zj]*tension_w;
    			waelem[3*noeud1-1] -= dy/Winch[zg].longueur[zj]*tension_w;
    			waelem[3*noeud1-0] -= dz/Winch[zg].longueur[zj]*tension_w;
    			waelem[3*noeud2-2] += dx/Winch[zg].longueur[zj]*tension_w;
    			waelem[3*noeud2-1] += dy/Winch[zg].longueur[zj]*tension_w;
    			waelem[3*noeud2-0] += dz/Winch[zg].longueur[zj]*tension_w;
    		}
	}
  	}
	/*imprvectreel(36, wf);*/
}

