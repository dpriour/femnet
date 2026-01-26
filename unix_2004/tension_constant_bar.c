#define PRINCIPAL 0
#include "4c19.h"

void tension_constant_bar()
	{
  	int elem,zh,zi;
  	//double dx,dy,dz;
  	double dx,dy,dz,rl,dr2,dr,lo,t_critic,t_lim;
 	void extern tension();
	void extern stockagec4();
	for (elem = 1; elem<= NOMBRE_ELEMENTS; elem++)
		{
		if ((TypeElement[Element[elem].type].constant_tension == 1) && (TypeElement[Element[elem].type].slider == 0))
			{
			//stockagec4();/**/
			zh = yb(elem,1);	//numero of the ccordinate x of the first  extremity of the bar elem
			zi = yb(elem,4);	//numero of the ccordinate x of the second extremity of the bar elem
			/* wf contient les coordonnees de noeuds. */
		  	dx = wf[yb(elem,4)]-wf[yb(elem,1)];
		  	dy = wf[yb(elem,5)]-wf[yb(elem,2)];
		  	dz = wf[yb(elem,6)]-wf[yb(elem,3)];
		  	dr2 = dx*dx + dy*dy + dz*dz;
		  	if (dr2 < 0.01 * Element[elem].lgrepos * 0.01 * Element[elem].lgrepos)	dr2 = 0.01 * Element[elem].lgrepos * 0.01 * Element[elem].lgrepos;
		  
			/* Longueur de la barre apres deformation */  
		  	dr  = sqrt(dr2);		
		  	Element[elem].lgtendue = dr;
		  	t_lim =TypeElement[Element[elem].type].tension_constant;
			t_critic = (dr-Element[elem].lgrepos) * Element[elem].raideur_effective / Element[elem].lgrepos ;
	    		//printf("cable_tension_constant, bar %d constant tension %lf N  \n",elem,t_lim);
			//printf("t_lim %lf N t_critic %lf N\n",t_lim,t_critic);
		  	  
			/* Longueur de la barre au repos, donnee dans le fichier .mdf*/  
		  	lo = Element[elem].lgrepos; 
		  	rl = Element[elem].raideur_effective / (dr2 * dr);
		  	
		  	if (t_critic <= t_lim)
		  		{
		  		//usual bar without constant tension		  
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
				else if  (Structure.type_solver == 2)
					{
					}
		   		
		    		Element[elem].wt = (dr-Element[elem].lgrepos) * Element[elem].raideur_effective / Element[elem].lgrepos ;
		    		
		    		//imprvectreel(21, waelem);
		    		waelem[yb(elem,1)] += dx/dr*Element[elem].wt;
		    		waelem[yb(elem,2)] += dy/dr*Element[elem].wt;
		    		waelem[yb(elem,3)] += dz/dr*Element[elem].wt;
		    		waelem[yb(elem,4)] -= dx/dr*Element[elem].wt;
		    		waelem[yb(elem,5)] -= dy/dr*Element[elem].wt;
		    		waelem[yb(elem,6)] -= dz/dr*Element[elem].wt;
		    		
		    		//imprvectreel(21, waelem);
		  		}
		  	else
		  		{
		  		//not usual bar with constant tension		  
			  	/* Calcul des raideurs elementaires, dans les commentaires raideur[1][1] est la derivee de Fx1 par rapport a x1
			  						raideur[1][2] est la derivee de Fx1 par rapport a y1
			 	ou Fx1 est la composante selon l'axe des X de l'effort du a la tension, a l'extremite 1 du bout
			  	(x1,y1,z1) et (x2,y2,z2) sont les composantes des extremites 1 et 2 du bout.*/
			  	wd[1] = -(dx*dx*t_lim)/(dr*dr*dr)+t_lim/dr; /*raideur [1][1], et [4][4], -raideur [1][4],[4][1]*/
			  	wd[4] = -(dy*dy*t_lim)/(dr*dr*dr)+t_lim/dr; /*raideur [2][2], et [5][5], -raideur [5][2] et [2][5]*/
			  	wd[6] = -(dz*dz*t_lim)/(dr*dr*dr)+t_lim/dr; /*raideur [3][3], et [6][6], -raideur [6][3] et [3][6]*/
			  	wd[2] = -(dx*dy*t_lim)/(dr*dr*dr);          /*raideur [1][2], [2][1], [5][4] et [4][5] , -raideur [5][1], [4][2], [2][4] et [1][5]*/
			  	wd[3] = -(dx*dz*t_lim)/(dr*dr*dr);          /*raideur [1][3], [3][1], [6][4] et [4][6] , -raideur [6][1], [1][6], [4][3] et [3][4]*/
			  	wd[5] = -(dy*dz*t_lim)/(dr*dr*dr);          /*raideur [2][3], [3][2], [6][5] et [5][6] , -raideur [6][2], [2][6], [5][3] et [3][5]*/
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
				else if  (Structure.type_solver == 2)
					{
					}
		   		
		    		Element[elem].wt =  t_lim;
		    		
		    		//imprvectreel(21, waelem);
		    		waelem[yb(elem,1)] += dx/dr*Element[elem].wt;
		    		waelem[yb(elem,2)] += dy/dr*Element[elem].wt;
		    		waelem[yb(elem,3)] += dz/dr*Element[elem].wt;
		    		waelem[yb(elem,4)] -= dx/dr*Element[elem].wt;
		    		waelem[yb(elem,5)] -= dy/dr*Element[elem].wt;
		    		waelem[yb(elem,6)] -= dz/dr*Element[elem].wt;
		    		
		    		//imprvectreel(21, waelem);
		  		}
			}
  		}
	}

