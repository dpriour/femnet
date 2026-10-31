#define PRINCIPAL 0
#include "4c19.h"

void rotation3(int zh,int zi,int zj)
	{
	/* Calcul des angles de rotation et des nouvelles coordonnees du triangle dans son plan.
	zh, zi, zj sont les 3 sommets du triangle.
	Cette procedure calcule les 6 coordonnees des sommets dans le plan horizontale (X1...Y3)
	et les 2 angles de rotation pour rendre le triangle horizontal.*/
  	double Denominateur,D,c1,c2,c3,c4,c5,c6;
  	double vect[10],norm[4];
  	
	/*printf("elem = %d  \n",elem); 
	printf("zh = %5d %5d %5d \n",zh,zi,zj); 
	printf("sommets = %d %d %d \n",Surface[elem].nop[1],Surface[elem].nop[2],Surface[elem].nop[3]);
	printf("sommets = %d %d %d \n",Surf_Hexa[elem].nop[1],Surf_Hexa[elem].nop[2],Surf_Hexa[elem].nop[3]);*/
  
  	/*coordonnees du triangle vect*/
  	vect[1] = wf[zh  ];  vect[2] = wf[zh+1];  vect[3] = wf[zh+2];
  	vect[4] = wf[zi  ];  vect[5] = wf[zi+1];  vect[6] = wf[zi+2];
  	vect[7] = wf[zj  ];  vect[8] = wf[zj+1];  vect[9] = wf[zj+2];

  	/*sommet 1 = origine du repere*/
  	c1 = vect[4]-vect[1];	c2 = vect[5]-vect[2];	c3 = vect[6]-vect[3];
  	c4 = vect[7]-vect[1];	c5 = vect[8]-vect[2];	c6 = vect[9]-vect[3];       
  
  	Denominateur = pow(c2*c6-c5*c3,2.0) + pow(c3*c4-c6*c1,2.0) + pow(c2*c4-c5*c1,2.0);
  	D = sqrt(Denominateur);
  	
	/*printf("Denominateur = %lf \n",Denominateur); 
	printf("D = %lf \n",D); 
	printf("c = %lf %lf %lf %lf %lf %lf \n",c1,c2,c3,c4,c5,c6);*/

  	if ( D != 0.0)
  		{ 
  		norm[1] = -(vect[5]*vect[3]-vect[5]*vect[9]+vect[2]*vect[9]+vect[6]*vect[8]-vect[6]*vect[2]-vect[3]*vect[8])/D;
  		norm[2] =  (vect[7]*vect[6]-vect[7]*vect[3]-vect[1]*vect[6]-vect[9]*vect[4]+vect[9]*vect[1]+vect[3]*vect[4])/D;
  		norm[3] = -(vect[7]*vect[5]-vect[1]*vect[5]-vect[7]*vect[2]+vect[2]*vect[4]-vect[8]*vect[4]+vect[8]*vect[1])/D;
  		}
  	else
  		{
  		/* Les 3 sommets du triangle sont confondus en un seul et unique point : */
  		if (c1 == 0.0 && c2 ==0.0 && c3 == 0.0 && c4 == 0.0 && c5 == 0.0 && c6 == 0.0 )
  			{
  			norm[1] = 0.0 ;
  			norm[2] = 0.0 ;
  			norm[3] = 1.0 ;
  			}
  		else
  			{
  			/* Les 3 sommets du triangle sont alignes : */
  			if ((c1*c4 + c2*c5 + c3*c6 ) != 0.0 )
  				{   
     				D = sqrt(c4*c4 + c5*c5 + c6*c6);
     				norm[1] = -c5/D ; norm[2] = c4/D ;  norm[3] = c6/D ;  
  				}
  			else
  				{
  				/* Les sommets 1 & 2 du triangle sont confondus : */
  				if ( c1 == 0.0 && c2 == 0.0 && c3 == 0.0 )
  					{   
     					D = sqrt(c4*c4 + c5*c5 + c6*c6);
     					norm[1] = -c5/D ; norm[2] = c4/D ;  norm[3] = c6/D ;  
  					}
		
  				/* Les sommets 1 & 3 du triangle sont confondus : */
  				if ( c4 == 0.0 && c5 == 0.0 && c6 == 0.0 )
  					{   
     					D = sqrt(c1*c1 + c2*c2 + c3*c3);
     					norm[1] = -c2/D ; norm[2] = c1/D ;  norm[3] = c3/D ;  
  					}
  		
  				/* Les sommets 2 & 3 du triangle sont confondus : */
  				if ( c4 == c1 && c5 == c2 && c6 == c3 )
  					{   
     					D = sqrt(c4*c4 + c5*c5 + c6*c6);
     					norm[1] = -c2/D ; norm[2] = c1/D ;  norm[3] = c3/D ;  
  					}
  				}
  			}
  		}
 
 		
  		
	/*if ((zh == 610) && (zi == 613) && (zj == 568))
	{
	printf("D = %lf \n",D); 
	imprvectreel(9, vect);
	exit(0);
	} */
  
	/*imprvectreel(9, vect);
	imprvectreel(3, norm);*/             
       
  	/*elimination des valeurs abberantes de norm*/
  	if (norm[1] >  1.0) norm[1] =  1.0;
  	if (norm[2] >  1.0) norm[2] =  1.0;
  	if (norm[3] >  1.0) norm[3] =  1.0;
  	if (norm[1] < -1.0) norm[1] = -1.0;
  	if (norm[2] < -1.0) norm[2] = -1.0;
  	if (norm[3] < -1.0) norm[3] = -1.0;
    
       
  	/* alpha = angle de rotation du triangle autour de l'axe OZ, de telle sorte que la
  	normale, norm, au triangle soit dans le plan XOZ. */ 
   
  	if ((norm[1]*norm[1] + norm[2]*norm[2]) == 0.0) alpha =   0.0;
  	if  (norm[2] >  0.0)                            alpha = - acos(norm[1]/sqrt(norm[1]*norm[1] + norm[2]*norm[2]));
  	if  (norm[2] <  0.0)                            alpha =   acos(norm[1]/sqrt(norm[1]*norm[1] + norm[2]*norm[2]));
  	if  (norm[2] == 0.0 && norm[1] > 0.0)           alpha =   0.0;
  	if  (norm[2] == 0.0 && norm[1] < 0.0)           alpha =   PI;

  	/*rotation du vecteur normal norm*/
  	base1( alpha, 3, 0.0,  3,  3, norm);

  	/* betaa = angle de rotation du triangle autour de l'axe OY de telle sorte que
    	la normale au triangle soit egale a (0 0 1). */

  	if (norm[1]  > 0.0)                  betaa = - acos(norm[3]/sqrt(norm[1]*norm[1] + norm[3]*norm[3]));
  	if (norm[1]  < 0.0)                  betaa =   acos(norm[3]/sqrt(norm[1]*norm[1] + norm[3]*norm[3]));
  	if (norm[1] == 0.0 && norm[3] < 0.0) betaa =   PI;
  	if (norm[1] == 0.0 && norm[3] > 0.0) betaa =   0.0;
  
  	/*rotation du vecteur normal norm*/
  	base1( betaa, 2, 0.0,  3,  3, norm);
  
	
  	/*rotation des 9 coordonnees des sommets du triangle (vect) de alpha puis de betaa*/
     	base1( alpha, 3, betaa,  2,  9, vect);
	
  	/*nouvelles coordonnees du triangle dans le plan XOY*/
  	X1 = vect[1];
  	Y1 = vect[2];
  	X2 = vect[4];
  	Y2 = vect[5];
  	X3 = vect[7];
  	Y3 = vect[8];
  
  	/* Le triangle, dans son plan doit etre dans le sens direct 
	printf("rotation3 alpha1 = %12.6lf  beta1= %12.6lf \n",alpha,betaa);*/ 

	}

