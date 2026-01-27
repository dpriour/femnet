#define PRINCIPAL 0
#include "4c19.h"

void rota1(double *VV,double *NM)
	{    
	/* Calcul des rotations necessaires pour que  les vecteurs NM et VV soient dans le plan XOY. 
	ces vecteurs sont VV[1] VV[2] VV[3] et NM[1] NM[2] et NM[3]*/
	
  	double Np[4],D1;
  	int j;
  
  	/* VV : Composantes selon X, Y et Z du vecteur VV */    
  	/* NM : Composantes selon X, Y et Z du vecteur NM */ 
	
	/*printf(" Debut rota1\n");  	
 	printf(" VV = ");  	imprvectreel(3, VV);
 	printf(" NM = ");  	imprvectreel(3, NM);*/
    
  	/* Initialisation de Np, vecteur normal au plan forme par VV et NM  */
     	for (j=1 ; j <=3; j++)
     		{ 
       		Np[j] = 0.0;
     		}
     
	/* Np : composantes de la normale au plan parallele a VV et NM, definies par le produit vectoriel 
   	de VV et de NM */
   
    	D1 = (VV[2]*NM[3] - VV[3]*NM[2])*(VV[2]*NM[3] - VV[3]*NM[2]) +
       	     (VV[3]*NM[1] - VV[1]*NM[3])*(VV[3]*NM[1] - VV[1]*NM[3]) +
       	     (VV[1]*NM[2] - VV[2]*NM[1])*(VV[1]*NM[2] - VV[2]*NM[1]);
    	D1 = sqrt(D1);
    
     	if ( D1 != 0.0 )
   		{ 
      		Np[1] = (VV[2]*NM[3] - VV[3]*NM[2])/D1;
      		Np[2] = (VV[3]*NM[1] - VV[1]*NM[3])/D1;
      		Np[3] = (VV[1]*NM[2] - VV[2]*NM[1])/D1;
   		} 
 
    	if( D1 == 0.0 )
    		{
  		/* Cas ou les vecteurs NM et VV sont nuls */
     		if( VV[1] == 0.0 && VV[2] == 0.0 && VV[3] == 0.0 && NM[1] == 0.0 && NM[2 ]== 0.0 && NM[3] == 0.0)
     			{
       			Np[1] = 0.0;    Np[2] = 0.0;     Np[3] = 1.0;
     			}
     
  		/* Cas ou le vecteur VV est nul. Dans ce cas Np est perpendiculaire a NM : */
     		if(VV[1] == 0.0 && VV[2] == 0.0 && VV[3] == 0.0)
     			{ 
       			D1 = sqrt(NM[1]*NM[1] + NM[2]*NM[2] + NM[3]*NM[3]);
       			Np[1] = - NM[2]/D1;     Np[2] = NM[1]/D1;      Np[3] = NM[3]/D1;
     			}
     
  		/* Cas ou le vecteur NM est nul. Dans ce cas, le vecteur Np est perpendiculaire a VV */
     		if(NM[1] == 0.0 && NM[2] == 0.0 && NM[3] == 0.0)  
     			{
       			D1 = sqrt(VV[1]*VV[1] + VV[2]*VV[2] + VV[3]*VV[3]);
       			Np[1] = - VV[2]/D1;     Np[2] = VV[1]/D1;       Np[3] = VV[3]/D1;
     			}
          
   		/* Cas ou VV et NM sont colineaires. Dans ce cas Np est perpendiculaire a ces vecteurs. */
      		if(VV[1]*NM[1] + VV[2]*NM[2] + VV[3]*NM[3] != 0.0)
      			{
       			D1 = sqrt(VV[1]*VV[1] + VV[2]*VV[2] + VV[3]*VV[3]);
       			Np[1] = - VV[2]/D1;     Np[2] = VV[1]/D1;       Np[3] = VV[3]/D1;
      			}
    		} 
       
  
  	/* Elimination des valeurs abberantes de Np*/
     	if (Np[1] >  1.0) 	Np[1] =  1.0;
     	if (Np[2] >  1.0) 	Np[2] =  1.0;
     	if (Np[3] >  1.0) 	Np[3] =  1.0;
     	if (Np[1] < -1.0) 	Np[1] = -1.0;
     	if (Np[2] < -1.0) 	Np[2] = -1.0;
     	if (Np[3] < -1.0) 	Np[3] = -1.0;
    
 	/*printf(" Np = ");  	imprvectreel(3, Np);*/
  
  	/* Rotation de alpha1 autour de Z et de beta1 autour de Y pour avoir Np selon l'axe Z et norme .
     	Apres rotations, les deux vecteurs VV et NM seront dans le plan (X, Y). */
  
  	/* Definition, et rotation du vecteur Np, de alpha1 autour de Z, de telle sorte que Np soit dans le plan X0Z*/
  	if ( Np[1]*Np[1] +Np[2]*Np[2] == 0.0) alpha1 = 0.0 ;
  	if (Np[2] > 0.0) alpha1 = - acos(Np[1]/sqrt(Np[1]*Np[1] + Np[2]*Np[2]));
  	if (Np[2] < 0.0) alpha1 =   acos(Np[1]/sqrt(Np[1]*Np[1] + Np[2]*Np[2]));
  	if (Np[2] == 0.0 && Np[1] > 0.0) alpha1 = 0.0;
  	if (Np[2] == 0.0 && Np[1] < 0.0) alpha1 = PI;
  	base1(alpha1,3,0.0,3,3,Np);
  
 	/*printf("alpha1 = %lf \n",alpha1);*/
 	/*printf(" Np = ");  	imprvectreel(3, Np);*/

  
  	/* Definition, et rotation du vecteur Np, de beta1 autour de Y, de telle sorte que Np soit parallele a Z */
  	if (Np[1] > 0.0) beta1 = - acos(Np[3]/sqrt(Np[1]*Np[1] + Np[3]*Np[3]));
  	if (Np[1] < 0.0) beta1 =   acos(Np[3]/sqrt(Np[1]*Np[1] + Np[3]*Np[3]));
  	if (Np[1] == 0.0 && Np[3] < 0.0) beta1 = PI;
  	if (Np[1] == 0.0 && Np[3] > 0.0) beta1 = 0.0;
 
  	base1(beta1,2,0.0,3,3,Np);
  
 	/*printf("beta1 = %lf \n",beta1);*/
 	/*printf(" Np = ");  	imprvectreel(3, Np);*/
    
}
 
