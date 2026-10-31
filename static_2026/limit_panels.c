#define PRINCIPAL 0
#include "4c19.h"

void limit_panels()
	{
  	/*
	calculation of the limit between 2 panels
	*/

	int elem1,elem2,za,zb,zh,zi,zj,nb_points;
	double limit;
   
	changement_variable_catch();
	nb_points = 0;
	limit = 0.0;
	for (elem1 = 1; elem1<= NOMBRE_SURFACES; elem1++)
		{
		if (Surface[elem1].type == Prise.panels[1])
			{
    			/*numeros des coordonnees selon x des sommets du triangle*/
    			zh = yc(elem1,1);  zi = yc(elem1,4);  zj = yc(elem1,7);
			for (za = 1; za<= 3; za++)
				{
				if(za == 1) zb = zh;
				if(za == 2) zb = zi;
				if(za == 3) zb = zj;
				for (elem2 = 1; elem2<= NOMBRE_SURFACES; elem2++)
					{
					if (Surface[elem2].type == Prise.panels[2])
						{
						if(zb == yc(elem2,1))
							{
							nb_points = nb_points + 1;
							limit = limit + wfcodend[zb];
							} 
						if(zb == yc(elem2,2))
							{
							nb_points = nb_points + 1;
							limit = limit + wfcodend[zb];
							} 
						if(zb == yc(elem2,3))
							{
							nb_points = nb_points + 1;
							limit = limit + wfcodend[zb];
							} 
						}
					}
				}
			}
		}
	Prise.limit_panels = 1.000;
	Prise.limit_panels = limit / nb_points; /*mean cartesian position between the two panels*/
	printf("nb_points used for the calculation of the mean cartesian position between the two panels = %d  \n",nb_points);	/*nb of points used for the calculation of the mean cartesian position between the two panels*/
	/*printf("limit = %lf  \n",limit);*/
	printf("Prise.limit_panels mean cartesian position between the two panels = %lf \n",Prise.limit_panels);
	}
