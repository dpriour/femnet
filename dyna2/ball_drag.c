#include "4c19.h"

void ball_drag()
	{
  	int zi,zj,no;
  	double modulevitesse,immersion,demirhovit,immer,v2,cd_ball;
  	
  	cd_ball = 0.4; /*sphere cd = 0.4*/
  	
  	/* pour chaque ball prendre en compte la trainee*/
   	for (zi = 1 ; zi<= Ball.nb; zi++) 
  		{
  		no = Ball.noeud[zi];
  		if ((wf[3*no-0]<=0.0) && (times >= Ball.birth_time[zi]))
  			{
			v2=(mvb[3*no-2]-mvh[3*no-2])*(mvb[3*no-2]-mvh[3*no-2])
			  +(mvb[3*no-1]-mvh[3*no-1])*(mvb[3*no-1]-mvh[3*no-1])
			  +(mvb[3*no-0]-mvh[3*no-0])*(mvb[3*no-0]-mvh[3*no-0]);
			modulevitesse=sqrt(v2);
    			demirhovit = cd_ball * RHO / 2.0 *PI*Ball.radius[zi]*Ball.radius[zi];
    			
      			/*printf("no %d v2 %16.10lf Pascalcul %16.10lf demirhovit %16.10lf modulevitesse %16.10lf\n",no,v2,Pascalcul,demirhovit,modulevitesse);
			printf("mvb %12.2lf %12.2lf %12.2lf   \n",mvb[3*no-2],mvb[3*no-1],mvb[3*no-0]);
			printf("mvh %12.2lf %12.2lf %12.2lf   \n",mvh[3*no-2],mvh[3*no-1],mvh[3*no-0]);*/
    		
      			wanoeud[3*no-2] -= demirhovit* modulevitesse  *(mvb[3*no-2]-mvh[3*no-2]);
      			wanoeud[3*no-1] -= demirhovit* modulevitesse  *(mvb[3*no-1]-mvh[3*no-1]);
      			wanoeud[3*no-0] -= demirhovit* modulevitesse  *(mvb[3*no-0]-mvh[3*no-0]);
		      	/*printf("ze[3*no-2][eca  ] %6.0lf  ",ze[3*no-2][eca  ]);
		      	printf("ze[3*no-2][eca+1] %6.0lf  ",ze[3*no-2][eca+1]);
		      	printf("ze[3*no-2][eca+2] %6.0lf \n",ze[3*no-2][eca+2]);
		      	printf("ze[3*no-1][eca-1] %6.0lf  ",ze[3*no-1][eca-1]);
		      	printf("ze[3*no-1][eca  ] %6.0lf  ",ze[3*no-1][eca  ]);
		      	printf("ze[3*no-1][eca+1] %6.0lf \n",ze[3*no-1][eca+1]);
		      	printf("ze[3*no-0][eca-2] %6.0lf  ",ze[3*no-0][eca-2]);
		      	printf("ze[3*no-0][eca-1] %6.0lf  ",ze[3*no-0][eca-1]);
		      	printf("ze[3*no-0][eca  ] %6.0lf \n",ze[3*no-0][eca  ]);*/
      				
			if (Structure.type_solver == 1)
			{	
      				if (modulevitesse > 0.0)
      				{
      					ze[3*no-2][eca  ] += demirhovit/ Pascalcul * (((mvb[3*no-2]-mvh[3*no-2])*(mvb[3*no-2]-mvh[3*no-2]))/modulevitesse + modulevitesse);
      					ze[3*no-2][eca+1] += demirhovit/ Pascalcul * (((mvb[3*no-2]-mvh[3*no-2])*(mvb[3*no-1]-mvh[3*no-1]))/modulevitesse);
      					ze[3*no-2][eca+2] += demirhovit/ Pascalcul * (((mvb[3*no-2]-mvh[3*no-2])*(mvb[3*no-0]-mvh[3*no-0]))/modulevitesse);

      					ze[3*no-1][eca-1] += demirhovit/ Pascalcul * (((mvb[3*no-1]-mvh[3*no-1])*(mvb[3*no-2]-mvh[3*no-2]))/modulevitesse);
      					ze[3*no-1][eca  ] += demirhovit/ Pascalcul * (((mvb[3*no-1]-mvh[3*no-1])*(mvb[3*no-1]-mvh[3*no-1]))/modulevitesse + modulevitesse);
      					ze[3*no-1][eca+1] += demirhovit/ Pascalcul * (((mvb[3*no-1]-mvh[3*no-1])*(mvb[3*no-0]-mvh[3*no-0]))/modulevitesse);

      					ze[3*no-0][eca-2] += demirhovit/ Pascalcul * (((mvb[3*no-0]-mvh[3*no-0])*(mvb[3*no-2]-mvh[3*no-2]))/modulevitesse);
      					ze[3*no-0][eca-1] += demirhovit/ Pascalcul * (((mvb[3*no-0]-mvh[3*no-0])*(mvb[3*no-1]-mvh[3*no-1]))/modulevitesse);
      					ze[3*no-0][eca  ] += demirhovit/ Pascalcul * (((mvb[3*no-0]-mvh[3*no-0])*(mvb[3*no-0]-mvh[3*no-0]))/modulevitesse + modulevitesse);
      				}
			}
			else if (Structure.type_solver == 2)
			{
				//affectation_pardiso(demirhovit/ Pascalcul * (((mvb[3*no-2]-mvh[3*no-2])*(mvb[3*no-2]-mvh[3*no-2]))/modulevitesse + modulevitesse), 3*no-2, 3*no-2);
				//affectation_pardiso(demirhovit/ Pascalcul * (((mvb[3*no-2]-mvh[3*no-2])*(mvb[3*no-1]-mvh[3*no-1]))/modulevitesse), 3*no-2, 3*no-1);
				//affectation_pardiso(demirhovit/ Pascalcul * (((mvb[3*no-2]-mvh[3*no-2])*(mvb[3*no-0]-mvh[3*no-0]))/modulevitesse), 3*no-2, 3*no);

				//affectation_pardiso(demirhovit/ Pascalcul * (((mvb[3*no-1]-mvh[3*no-1])*(mvb[3*no-2]-mvh[3*no-2]))/modulevitesse), 3*no-1, 3*no-2);
				//affectation_pardiso(demirhovit/ Pascalcul * (((mvb[3*no-1]-mvh[3*no-1])*(mvb[3*no-1]-mvh[3*no-1]))/modulevitesse + modulevitesse), 3*no-1, 3*no-1);
				//affectation_pardiso(demirhovit/ Pascalcul * (((mvb[3*no-2]-mvh[3*no-2])*(mvb[3*no-0]-mvh[3*no-0]))/modulevitesse), 3*no-2, 3*no);

				//affectation_pardiso(demirhovit/ Pascalcul * (((mvb[3*no-0]-mvh[3*no-0])*(mvb[3*no-2]-mvh[3*no-2]))/modulevitesse), 3*no, 3*no-2);
				//affectation_pardiso(demirhovit/ Pascalcul * (((mvb[3*no-0]-mvh[3*no-0])*(mvb[3*no-1]-mvh[3*no-1]))/modulevitesse), 3*no, 3*no-1);
				//affectation_pardiso(demirhovit/ Pascalcul * (((mvb[3*no-0]-mvh[3*no-0])*(mvb[3*no-0]-mvh[3*no-0]))/modulevitesse + modulevitesse), 3*no, 3*no);
			}

		      	/*printf("ze[3*no-2][eca  ] %6.0lf  ",ze[3*no-2][eca  ]);
		      	printf("ze[3*no-2][eca+1] %6.0lf  ",ze[3*no-2][eca+1]);
		      	printf("ze[3*no-2][eca+2] %6.0lf \n",ze[3*no-2][eca+2]);
		      	printf("ze[3*no-1][eca-1] %6.0lf  ",ze[3*no-1][eca-1]);
		      	printf("ze[3*no-1][eca  ] %6.0lf  ",ze[3*no-1][eca  ]);
		      	printf("ze[3*no-1][eca+1] %6.0lf \n",ze[3*no-1][eca+1]);
		      	printf("ze[3*no-0][eca-2] %6.0lf  ",ze[3*no-0][eca-2]);
		      	printf("ze[3*no-0][eca-1] %6.0lf  ",ze[3*no-0][eca-1]);
		      	printf("ze[3*no-0][eca  ] %6.0lf \n",ze[3*no-0][eca  ]);*/
      		
			if (rang[1][3*no-2  ] < 3*no    ) rang[1][3*no-2  ] = 3*no;
			if (rang[1][3*no-1  ] < 3*no    ) rang[1][3*no-1  ] = 3*no;
			if (rang[1][3*no    ] < 3*no    ) rang[1][3*no    ] = 3*no;
			if (rang[2][3*no-2  ] < 3*no    ) rang[2][3*no-2  ] = 3*no;
			if (rang[2][3*no-1  ] < 3*no    ) rang[2][3*no-1  ] = 3*no;
			if (rang[2][3*no    ] < 3*no    ) rang[2][3*no    ] = 3*no;
			if (rang[3][3*no-2  ] > 3*no-2  ) rang[3][3*no-2  ] = 3*no-2;
			if (rang[3][3*no-1  ] > 3*no-2  ) rang[3][3*no-1  ] = 3*no-2;
			if (rang[3][3*no    ] > 3*no-2  ) rang[3][3*no    ] = 3*no-2;
			if (rang[4][3*no-2  ] > 3*no-2  ) rang[4][3*no-2  ] = 3*no-2;
			if (rang[4][3*no-1  ] > 3*no-2  ) rang[4][3*no-1  ] = 3*no-2;
			if (rang[4][3*no    ] > 3*no-2  ) rang[4][3*no    ] = 3*no-2;
		
      		
			/*printf("times %lf ball %d noeud %5d ",times,zi,Ball.noeud[zi]);
			printf("coord %5d %5d %5d \n",3*Ball.noeud[zi]-2,3*Ball.noeud[zi]-1,3*Ball.noeud[zi]-0);*/
  			}
  		}
  	/*for (zi = 1 ; zi<= 3 ; zi++)
  		{
    		for (zj = 1 ; zj<= 3 ; zj++) 
    			{
      			printf(" %6.0lf ",ze[3*no-2-1+zi][eca-zi+zj]);
    			}
    		printf("\n");
  		}
  	printf("\n");*/
      		
	}



