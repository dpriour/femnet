#define PRINCIPAL 0
#include "4c19.h"  
//#define DEBUG

void ballast_quantite_mouvement1()
	{
	/*force effect of ballast due to momentum M*V
	This force is - d(M*V)/dt which is 
	-dM/dt * V
	and
	-M * dV/dt
	*/
	int zi;
	double ballast_speed;
	
	//printf(" wanoeuc \n");	imprvectreel1(18, 3, wanoeud);     			
  	for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++) 
		{
		ballast_speed = (Noeud[zi].volume_ballast - Noeud[zi].precedent_ballast) / Pascalcul;
		//-dM/dt * V
		wanoeud[zi] -= ballast_speed * RHO * mvb[zi];
		ze[zi][eca] += ballast_speed * RHO / Pascalcul;	
		//-M * dV/dt
		wanoeud[zi] -= Noeud[zi].volume_ballast * RHO * mgb[zi];
		ze[zi][eca] += Noeud[zi].volume_ballast * RHO / Pascalcul / Pascalcul;	
		//printf("%5.2lf  ",ballast_speed);  			
		//printf("%5.2lf  ",Noeud[zi].volume_ballast);  			
		}
	//printf("\n");    			
	//printf(" wanoeud \n");	imprvectreel1(18, 3, wanoeud);     			
	//printf(" mvb \n");	imprvectreel1(18, 3, mvb);     			
	//printf(" mgb \n");	imprvectreel1(18, 3, mgb);   
	}				


