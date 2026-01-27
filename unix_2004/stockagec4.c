#define PRINCIPAL 0
#include "4c19.h"

/* Calcul des raideurs dues a la tension dans les elements(ie les bouts) */

void stockagec4()
{
  int elem,zh,zi;
  void extern allongement2(int elem);
  for (elem = 1; elem<= NOMBRE_ELEMENTS; elem++)
  {
    zh = yb(elem,1);
    zi = yb(elem,4);
    allongement2(elem);
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

		//affectation_pardiso(wd[1], zh, zh);	affectation_pardiso(wd[2], zh, zh+1);	affectation_pardiso(wd[3], zh, zh+2);
		//affectation_pardiso(wd[2], zh+1, zh);	affectation_pardiso(wd[4], zh+1, zh+1);	affectation_pardiso(wd[5], zh+1, zh+2);
		//affectation_pardiso(wd[3], zh+2, zh);	affectation_pardiso(wd[5], zh+2, zh+1);	affectation_pardiso(wd[6], zh+2, zh+2);

		//affectation_pardiso(wd[1], zi, zi);	affectation_pardiso(wd[2], zi, zi+1);	affectation_pardiso(wd[3], zi, zi+2);
		//affectation_pardiso(wd[2], zi+1, zi);	affectation_pardiso(wd[4], zi+1, zi+1);	affectation_pardiso(wd[5], zi+1, zi+2);
		//affectation_pardiso(wd[3], zi+2, zi);	affectation_pardiso(wd[5], zi+2, zi+1);	affectation_pardiso(wd[6], zi+2, zi+2);

		//affectation_pardiso(-wd[1], zh, zi);	 affectation_pardiso(-wd[2], zh, zi+1);	  affectation_pardiso(-wd[3], zh, zi+2);
		//affectation_pardiso(-wd[2], zh+1, zi); affectation_pardiso(-wd[4], zh+1, zi+1); affectation_pardiso(-wd[5], zh+1, zi+2);
		//affectation_pardiso(-wd[3], zh+2, zi); affectation_pardiso(-wd[5], zh+2, zi+1); affectation_pardiso(-wd[6], zh+2, zi+2);

		//affectation_pardiso(-wd[1], zi, zh);	affectation_pardiso(-wd[2], zi, zh+1);	 affectation_pardiso(-wd[3], zi, zh+2);
		//affectation_pardiso(-wd[2], zi+1, zh);	affectation_pardiso(-wd[4], zi+1, zh+1); affectation_pardiso(-wd[5], zi+1, zh+2);
		//affectation_pardiso(-wd[3], zi+2, zh);	affectation_pardiso(-wd[5], zi+2, zh+1); affectation_pardiso(-wd[6], zi+2, zh+2);

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

