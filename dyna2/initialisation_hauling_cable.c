#include "4c19.h"

void initialisation_hauling_cable()
	{
	int zi,zj;
	double total_reduction,remaining_length,propose_times;
	
	if (Structure.nb_hauling_cable > 0)
		{	
		for (zi=1;zi<=Structure.NbTypeelem;zi++)
			{
			if (TypeElement[zi].haul_extremity != 0)
				{
				printf("The cable %d is reduced at %lf m/s by its extremity %d. Its minimal length is %lf. It starts to reduce at %lf s.\n",zi,TypeElement[zi].haul_speed,TypeElement[zi].haul_extremity,TypeElement[zi].haul_limit,TypeElement[zi].haul_time);
			  	for (zj = 1 ; zj<= NOMBRE_ELEMENTS ; zj++)
			  		{
			  		if (Element[zj].type == zi)
			  			{
						/*printf("zj  %d extremities %d %d pro %lf %lf\n",zj,Element[zj].extremite[1],Element[zj].extremite[2],Element[zj].pro[1],Element[zj].pro[2]);*/
			  			if ((TypeElement[zi].haul_extremity == 1) && (Element[zj].pro[1] == 0.0))
			  				{
							TypeElement[zi].haul_bar = zj;			/*first bar which is reduced*/
							TypeElement[zi].haul_node = yb(zj,6)/3;		/*next node which is removed*/
							TypeElement[zi].haul_bar_limit = TypeElement[zi].haul_limit * (fabs(Element[zj].pro[1]-Element[zj].pro[2]));
							printf("a the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d TypeElement[zi].haul_bar_limit %lf\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node,TypeElement[zi].haul_bar_limit);
							}
			  			if ((TypeElement[zi].haul_extremity == 1) && (Element[zj].pro[2] == 0.0))
			  				{
							TypeElement[zi].haul_bar = zj;
							TypeElement[zi].haul_node = yb(zj,3)/3;
							TypeElement[zi].haul_bar_limit = TypeElement[zi].haul_limit * (fabs(Element[zj].pro[1]-Element[zj].pro[2]));
							printf("b the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d TypeElement[zi].haul_bar_limit %lf\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node,TypeElement[zi].haul_bar_limit);
							}
			  			if ((TypeElement[zi].haul_extremity == 2) && (Element[zj].pro[1] == 1.0))
			  				{
							TypeElement[zi].haul_bar = zj;
							TypeElement[zi].haul_node = yb(zj,6)/3;
							TypeElement[zi].haul_bar_limit = TypeElement[zi].haul_limit * (fabs(Element[zj].pro[1]-Element[zj].pro[2]));
							printf("c the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d TypeElement[zi].haul_bar_limit %lf\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node,TypeElement[zi].haul_bar_limit);
							}
			  			if ((TypeElement[zi].haul_extremity == 2) && (Element[zj].pro[2] == 1.0))
			  				{
							TypeElement[zi].haul_bar = zj;
							TypeElement[zi].haul_node = yb(zj,3)/3;
							TypeElement[zi].haul_bar_limit = TypeElement[zi].haul_limit * (fabs(Element[zj].pro[1]-Element[zj].pro[2]));
							printf("d the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d TypeElement[zi].haul_bar_limit %lf\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node,TypeElement[zi].haul_bar_limit);
							}
			  			}
			  		}				
				}
			}
		}
		
	
	if (Structure.nb_hauling_cable2 > 0)
		{	
		for (zi=1;zi<=Structure.NbTypeelem;zi++)
			{
			if (TypeElement[zi].haul_extremity != 0)
				{
				total_reduction = (TypeElement[zi].haul_end_times-TypeElement[zi].haul_beg_times)*(TypeElement[zi].haul_beg_speed+TypeElement[zi].haul_end_speed)/2.0;
				remaining_length = TypeElement[zi].lgrepos - total_reduction;
				printf("The cable %d by its extremity %d.\n",zi,TypeElement[zi].haul_extremity);
				printf("Beginning times %lf s, end times %lf s, begining speed %lf m/s, end speed %lf m/s\n",TypeElement[zi].haul_beg_times,TypeElement[zi].haul_end_times,TypeElement[zi].haul_beg_speed,TypeElement[zi].haul_end_speed);
				printf("total_reduction %lf\n",total_reduction);
				printf("lgrepos %lf\n",TypeElement[zi].lgrepos);
				printf("remaining_length %lf\n",remaining_length);
				TypeElement[zi].haul_limit = remaining_length;
				if (remaining_length <= 0.0)
					{
					propose_times = 0.999 * TypeElement[zi].lgrepos *2.0 /(TypeElement[zi].haul_beg_speed+TypeElement[zi].haul_end_speed) + TypeElement[zi].haul_beg_times;
					printf("The remaining_length = %lf m which must be > 0 m. ",remaining_length);
					printf("The end times must be < %lf s\n",propose_times);
					printf("The command line input hauling_cable2 could be modified in:\n");
					printf("input hauling_cable2 %d %d %lf %lf %lf %lf\n",zi,TypeElement[zi].haul_extremity,TypeElement[zi].haul_beg_times,propose_times,TypeElement[zi].haul_beg_speed,TypeElement[zi].haul_end_speed);
					exit(0);				
					}
			  	for (zj = 1 ; zj<= NOMBRE_ELEMENTS ; zj++)
			  		{
			  		if (Element[zj].type == zi)
			  			{
						/*printf("zj  %d extremities %d %d pro %lf %lf\n",zj,Element[zj].extremite[1],Element[zj].extremite[2],Element[zj].pro[1],Element[zj].pro[2]);*/
			  			if ((TypeElement[zi].haul_extremity == 1) && (Element[zj].pro[1] == 0.0))
			  				{
							TypeElement[zi].haul_bar = zj;			/*first bar which is reduced*/
							TypeElement[zi].haul_node = yb(zj,6)/3;		/*next node which is removed*/
							TypeElement[zi].haul_bar_limit = TypeElement[zi].haul_limit * (fabs(Element[zj].pro[1]-Element[zj].pro[2]));
							printf("a the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d TypeElement[zi].haul_bar_limit %lf\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node,TypeElement[zi].haul_bar_limit);
							}
			  			if ((TypeElement[zi].haul_extremity == 1) && (Element[zj].pro[2] == 0.0))
			  				{
							TypeElement[zi].haul_bar = zj;
							TypeElement[zi].haul_node = yb(zj,3)/3;
							TypeElement[zi].haul_bar_limit = TypeElement[zi].haul_limit * (fabs(Element[zj].pro[1]-Element[zj].pro[2]));
							printf("b the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d TypeElement[zi].haul_bar_limit %lf\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node,TypeElement[zi].haul_bar_limit);
							}
			  			if ((TypeElement[zi].haul_extremity == 2) && (Element[zj].pro[1] == 1.0))
			  				{
							TypeElement[zi].haul_bar = zj;
							TypeElement[zi].haul_node = yb(zj,6)/3;
							TypeElement[zi].haul_bar_limit = TypeElement[zi].haul_limit * (fabs(Element[zj].pro[1]-Element[zj].pro[2]));
							printf("c the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d TypeElement[zi].haul_bar_limit %lf\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node,TypeElement[zi].haul_bar_limit);
							}
			  			if ((TypeElement[zi].haul_extremity == 2) && (Element[zj].pro[2] == 1.0))
			  				{
							TypeElement[zi].haul_bar = zj;
							TypeElement[zi].haul_node = yb(zj,3)/3;
							TypeElement[zi].haul_bar_limit = TypeElement[zi].haul_limit * (fabs(Element[zj].pro[1]-Element[zj].pro[2]));
							printf("d the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d TypeElement[zi].haul_bar_limit %lf\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node,TypeElement[zi].haul_bar_limit);
							}
			  			}
			  		}				
				}
			}
		}
		




		
	
	for (zi=1;zi<=Structure.NbTypeelem;zi++)
		{
		if (TypeElement[zi].nb_times >= 2)
			{
		  	for (zj = 1 ; zj<= NOMBRE_ELEMENTS ; zj++)
		  		{
		  		if (Element[zj].type == zi)
		  			{
					/*printf("zj  %d extremities %d %d pro %lf %lf\n",zj,Element[zj].extremite[1],Element[zj].extremite[2],Element[zj].pro[1],Element[zj].pro[2]);*/
		  			if ((TypeElement[zi].haul_extremity == 1) && (Element[zj].pro[1] == 0.0))
		  				{
						TypeElement[zi].haul_bar = zj;			/*first bar which is reduced*/
						TypeElement[zi].haul_node = yb(zj,6)/3;		/*next node which is removed*/
						printf("a the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node);
						}
		  			if ((TypeElement[zi].haul_extremity == 1) && (Element[zj].pro[2] == 0.0))
		  				{
						TypeElement[zi].haul_bar = zj;
						TypeElement[zi].haul_node = yb(zj,3)/3;
						printf("b the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node);
						}
		  			if ((TypeElement[zi].haul_extremity == 2) && (Element[zj].pro[1] == 1.0))
		  				{
						TypeElement[zi].haul_bar = zj;
						TypeElement[zi].haul_node = yb(zj,6)/3;
						printf("c the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node);
						}
		  			if ((TypeElement[zi].haul_extremity == 2) && (Element[zj].pro[2] == 1.0))
		  				{
						TypeElement[zi].haul_bar = zj;
						TypeElement[zi].haul_node = yb(zj,3)/3;
						printf("d the first bar reduced is  %d its extremities are nodes %d %d at proportion of the cable reference %lf %lf. That means that the first bar is %d and the next node removed is %d\n",zj,yb(zj,3)/3,yb(zj,6)/3,Element[zj].pro[1],Element[zj].pro[2],TypeElement[zi].haul_bar,TypeElement[zi].haul_node);
						}
		  			}
		  		}				
			}
		}
 	}


