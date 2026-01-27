#define PRINCIPAL 0
#include "4c19.h"

void coordonnees4()
	{
	/* Cacul des nouvelles positions (wf) des noeuds en fonction 
   	des anciennes et du mouvement (wv). Ces nouvelles positions 
   	ne prennent pas en compte les limites des coordonnees (wh) (donnees dans le fichier .mdf)
   	et le sens des limites (whs), et le facteur de relaxation Relaxation(Il est toujours = 1 !!!)*/
	
  	int zi,zj,noeud1,noeud2,noeud3,noeud4;
  	double l_effec,l_zero,l_refe,dx,dy,dz,tension_b;
  	
  	for (zi = 1; zi<= 3*NOMBRE_NOEUDS; zi++)
  		{
    		wf[zi] = wf[zi] + Relaxation * wv[zi];
  		}
  		
  	/*prise en compte des winchs*/
  	for (zi = 1 ; zi<= NOMBRE_WINCHS ; zi++)
  		{
    		for (zj = Winch[zi].nb_barre-1  ; zj>= 1; zj--) 
    			{
    			if ((Winch[zi].exit[zj+2] == 1) && (Winch[zi].exit[zj+1] == 1) && (Winch[zi].exit[zj  ] == 0))
    				{
    				/*noeud1 et noeud2 sont sortis et noeud3 rentre*/
    				noeud1 = Winch[zi].noeud[zj+2];
    				noeud2 = Winch[zi].noeud[zj+1];
    				noeud3 = Winch[zi].noeud[zj  ];
    				noeud4 = Winch[zi].noeud[1   ];
    				
    				/*l_effec : distance entre le deuxieme point sorti (noeud1) et le winch (noeud4)*/
    				dx = wf[3*noeud1-2]-wf[3*noeud4-2];
    				dy = wf[3*noeud1-1]-wf[3*noeud4-1];
    				dz = wf[3*noeud1-0]-wf[3*noeud4-0];
    				l_effec= sqrt(dx*dx + dy*dy + dz*dz);
 
    				/*l_zero : longueur au repos la 2eme barre sortie*/
				l_zero = fabs(Winch[zi].prop[zj+2]-Winch[zi].prop[zj+1]) * Winch[zi].longueur_repos;
				
				/*l_refe : longueur reference (sous tension) de la 2eme barre sortie*/
				l_refe = l_zero * (1.0 + Winch[zi].adjust_force / Winch[zi].raideur_traction);
				/*printf("noeud %3d %3d %3d %3d l %7.3lf %7.3lf %7.3lf \n",noeud1,noeud2,noeud3,noeud4,l_effec,l_zero,l_refe);*/
				
				if (l_effec < l_refe)
				 	{
				 	/*noeud2 et trop pres du winch : il rentre*/
				 	Winch[zi].exit[zj+1] = 0;
				 	wf[3*noeud2-2] = wf[3*noeud4-2];
				 	wf[3*noeud2-1] = wf[3*noeud4-1];
				 	wf[3*noeud2-0] = wf[3*noeud4-0];
					printf("noeud %3d %3d %3d %9d l %7.3lf %7.3lf %7.3lf \n",noeud1,noeud2,noeud3,nbiter,l_effec,l_zero,l_refe);
				 	}
				 }
    			if ((Winch[zi].exit[zj+2] == 1) && (Winch[zi].exit[zj+1] == 0) && (Winch[zi].exit[zj  ] == 0))
    				{
    				/*noeud1 est sorti et noeud2 et noeud3 rentres*/
    				noeud1 = Winch[zi].noeud[zj+2];
    				noeud2 = Winch[zi].noeud[zj+1];
    				noeud3 = Winch[zi].noeud[zj  ];
    				noeud4 = Winch[zi].noeud[1   ];
    				
    				/*l_effec : distance entre le point sorti (noeud1) et le winch (noeud4)*/
    				dx = wf[3*noeud1-2]-wf[3*noeud4-2];
    				dy = wf[3*noeud1-1]-wf[3*noeud4-1];
    				dz = wf[3*noeud1-0]-wf[3*noeud4-0];
    				l_effec = sqrt(dx*dx + dy*dy + dz*dz);
 
    				/*l_zero : longueur au repos la barre sortie*/
				l_zero = fabs(Winch[zi].prop[zj+2]-Winch[zi].prop[zj+1]) * Winch[zi].longueur_repos;
				
				/*l_refe : longueur reference (sous tension d ajustement) de la barre sortie*/
				l_refe = l_zero * (1.0 + Winch[zi].adjust_force / Winch[zi].raideur_traction);
				
				/*tension de la barre sortie*/
				tension_b = (l_effec - l_zero) / l_zero * Winch[zi].raideur_traction;
				
				if (Winch[zi].adjust_force < tension_b)
				 	{
				 	/*tension est trop forte => noeud2 sort du winch*/
				 	Winch[zi].exit[zj+1] = 1;
				 	/*noeud2 se deplace de telle sorte que la tension entre noeud2 et noeud1 = adjust_force*/
				 	wf[3*noeud2-2] = wf[3*noeud1-2] - l_refe / l_effec * dx;
				 	wf[3*noeud2-1] = wf[3*noeud1-1] - l_refe / l_effec * dy;
				 	wf[3*noeud2-0] = wf[3*noeud1-0] - l_refe / l_effec * dz;
					printf("noeud %3d %3d %3d %8d tt %7.3lf %7.3lf %7.3lf \n",noeud1,noeud2,noeud3,nbiter,tension_b,l_zero,l_effec);
				 	}
    				}
    			}
  		}
/*
  	for (zi = 1 ; zi<= NOMBRE_WINCHS ; zi++)
  		{
		printf("exit   ");
    		for (zj = 1 ; zj<= Winch[zi].nb_barre+1; zj++) 
    			{
			printf(" %d  ",Winch[zi].exit[zj]);
    			}
		printf("\n");
  		}
*/
	}

