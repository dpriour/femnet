#define PRINCIPAL 0
#include "4c19.h"

void pesanteurelem()
	{
 	/*prise en compte de la pesanteur des elements
 	la pesanteur c a dire le volume (pi r^2) * la masse volumique * la gravite (G)
 	One thing seems not clear:
 	For hauling process use Element[zi].mass otherwise using 
 	Element[zi].lgrepos * PI * Element[zi].diametrehydro * Element[zi].diametrehydro / 4.0 * Element[zi].rhoelement
 	means that the mass decreses with hauling process (lgrepos decreases).
 	It seems that for some other cases Element[zi].mass is not appropriate: not clear must be solved
 	*/
 	
  	int    zi;
  	double p;
  	
  	for (zi = 1 ; zi<= NOMBRE_ELEMENTS ; zi++) 
  		{
    		//p = Element[zi].lgrepos * PI * Element[zi].diametrehydro * Element[zi].diametrehydro / 4.0 * Element[zi].rhoelement * G;
 		p = Element[zi].mass * G;
    		waelem[yb(zi,3)] -= p / 2.0;
    		waelem[yb(zi,6)] -= p / 2.0;
		}
	}
