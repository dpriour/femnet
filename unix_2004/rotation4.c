#define PRINCIPAL 0
#include "4c19.h"

void rotation4(int zh, int zi, int zj, double *angle3, double *angle2)
	{
	/* 
	Calcul les angles de rotation autour de l axe z (angle3) et de l axe y (angle2) du triangle elem
	pour que sa normale soit verticale ascendante
	*/
	
  	double Denominateur,D,c1,c2,c3,c4,c5,c6;
  	double vect[10],norm[4];
 
  	/*coordonnees du triangle vect*/
  	vect[1] = wf[zh  ];  vect[2] = wf[zh+1];  vect[3] = wf[zh+2];
  	vect[4] = wf[zi  ];  vect[5] = wf[zi+1];  vect[6] = wf[zi+2];
  	vect[7] = wf[zj  ];  vect[8] = wf[zj+1];  vect[9] = wf[zj+2];

  	/*orientation du vecteur normal au triangle norm*/
  	c1 = vect[5]-vect[2] ;   c2 = vect[9]-vect[3] ;   c3 = vect[8]-vect[2] ;    
  	c4 = vect[6]-vect[3] ;   c5 = vect[7]-vect[1] ;   c6 = vect[4]-vect[1] ; 
  
  	Denominateur = pow(c1*c2-c3*c4,2.0) + pow(c4*c5-c2*c6,2.0) + pow(c1*c5-c3*c6,2.0);
  	D = sqrt(Denominateur);
  
  	if ( D != 0.0)
  		{ 
  		norm[1] = -(vect[5]*vect[3]-vect[5]*vect[9]+vect[2]*vect[9]+vect[6]*vect[8]-vect[6]*vect[2]-vect[3]*vect[8])/D;
  		norm[2] =  (vect[7]*vect[6]-vect[7]*vect[3]-vect[1]*vect[6]-vect[9]*vect[4]+vect[9]*vect[1]+vect[3]*vect[4])/D;
  		norm[3] = -(vect[7]*vect[5]-vect[1]*vect[5]-vect[7]*vect[2]+vect[2]*vect[4]-vect[8]*vect[4]+vect[8]*vect[1])/D;
  		}
  
  	/* Les 3 sommets du triangle sont confondus en un seul et unique point : */
  	if ( D == 0.0 && c1 == 0.0 && c2 ==0.0 && c3 == 0.0 && c4 == 0.0 && c5 == 0.0 && c6 == 0.0 )
  		{
  		norm[1] = 0.0 ;
  		norm[2] = 0.0 ;
  		norm[3] = 1.0 ;
  		}
  
  	/* Les 3 sommets du triangle sont alignes : */
  
  	if ( D == 0.0 && (c6*c5 + c1*c3 + c4*c2 ) != 0.0 )
  		{   
     		D = sqrt(c5*c5 + c3*c3 + c2*c2);
     		norm[1] = -c3/D ; norm[2] = c5/D ;  norm[3] = c2/D ;  
  		}
              
  	/*elimination des valeurs abberantes de norm*/
  	if (norm[1] >  1.0) norm[1] =  1.0;
  	if (norm[2] >  1.0) norm[2] =  1.0;
  	if (norm[3] >  1.0) norm[3] =  1.0;
  	if (norm[1] < -1.0) norm[1] = -1.0;
  	if (norm[2] < -1.0) norm[2] = -1.0;
  	if (norm[3] < -1.0) norm[3] = -1.0;
    
  	/* *angle3 = angle de rotation du triangle autour de l'axe OZ, de telle sorte que la
  	normale, norm, au triangle soit dans le plan XOZ. */ 
   
  	if ((norm[1]*norm[1] + norm[2]*norm[2]) == 0.0) *angle3 =   0.0;
  	if  (norm[2] >  0.0)                            *angle3 = - acos(norm[1]/sqrt(norm[1]*norm[1] + norm[2]*norm[2]));
  	if  (norm[2] <  0.0)                            *angle3 =   acos(norm[1]/sqrt(norm[1]*norm[1] + norm[2]*norm[2]));
  	if  (norm[2] == 0.0 && norm[1] > 0.0)           *angle3 =   0.0;
  	if  (norm[2] == 0.0 && norm[1] < 0.0)           *angle3 =   PI;

  	/*rotation du vecteur normal norm*/
  	base1( *angle3, 3, 0.0,  3,  3, norm);

  	/* *angle2 = angle de rotation du triangle autour de l'axe OY de telle sorte que
    	la normale au triangle soit egale a (0 0 1). */

  	if (norm[1]  > 0.0)                  *angle2 = - acos(norm[3]/sqrt(norm[1]*norm[1] + norm[3]*norm[3]));
  	if (norm[1]  < 0.0)                  *angle2 =   acos(norm[3]/sqrt(norm[1]*norm[1] + norm[3]*norm[3]));
  	if (norm[1] == 0.0 && norm[3] < 0.0) *angle2 =   PI;
  	if (norm[1] == 0.0 && norm[3] > 0.0) *angle2 =   0.0;
  
}

