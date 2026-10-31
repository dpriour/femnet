#define PRINCIPAL 0
#include "4c19.h"

double value_calculation3(double lim_Y, int sens_lim_Y)
	{
	/*idem to value_calculation2 but with a limit along Y axe: that means that for the surface of the triangle over
	lim_Y the value is zero. There are two parameters lim_Y (double) and sens_lim_Y (int)
	if sens_lim_Y is = 1 value is zero for triangle surface > lim_Y
	if sens_lim_Y is =-1 value is zero for triangle surface < lim_Y
	if fact there are 
	
	other wise it is idem to value_calculation2:
	
	calculation of the value caugth by the trawl. tHE value is defined by a linear fonction (two points: min_depth, min_value
	and max_depth max_value). For each triangular element the vale of each vertex is calculated (val1 val2 and val3)
	the value caugtrh by this triangular element is the mean value of val1, val2 and val3 multiplied par the surface of
	the triangular element projected on the plane perpendicular to the towing speed (here the plane YZ)
	In fact therer are 27 cases depending on the vertical absisse of the vertex (ZZ1, ZZ2 and ZZ2) relatively to 
	min_depth and max_depth: these cases correspond to (ZZ1>= max_depth), (ZZ1<max_depth & ZZ1>=min_depth), (ZZ1<min_depth) with the same for ZZ2 and ZZ3*/
	int zi,surf,z1,z2,z3,sgn;
	double amplitude,min_depth,max_depth,min_value,max_value;
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3;
  	double PX,PY,PZ,QX,QY,QZ;
  	double val1,val2,val3,surface_projetee;
  	
	amplitude = 0.0;
 	for (zi = 1; zi<=Structure.nb_value ; zi++)
		{
		if (Value.depth1[zi] > Value.depth2[zi])
			{
			max_depth = Value.depth1[zi];	max_value = Value.value1[zi];
			min_depth = Value.depth2[zi];	min_value = Value.value2[zi];
			}
		else
			{
			max_depth = Value.depth2[zi];	max_value = Value.value2[zi];
			min_depth = Value.depth1[zi];	min_value = Value.value1[zi];
			}
		/*printf("value nb %d:",zi);
		printf("min value %lf at depth %lf and max value %lf at depth %lf\n",min_value,min_depth,max_value,max_depth);*/
	  	for (surf = 1; surf<= NOMBRE_SURFACES; surf++)
			{
			/*numero des coordonnees x des sommets 1 2 et 3 du triangle*/
			z1 = yc(surf,1);  	z2 = yc(surf,4);  	z3 = yc(surf,7);
	    		XX1 = wf[z1+0];    	YY1 = wf[z1+1];    	ZZ1 = wf[z1+2];
	    		XX2 = wf[z2+0];    	YY2 = wf[z2+1];    	ZZ2 = wf[z2+2];
	    		XX3 = wf[z3+0];    	YY3 = wf[z3+1];    	ZZ3 = wf[z3+2];
			sgn = orientation_triangle_val(z1, z2, z3);
			if (sens_lim_Y  < 0)
				{
				if (YY1 < lim_Y)
					{
					if (YY2 < lim_Y)
						{
						if (YY3 < lim_Y)
							{
							/*case 1: 1 2 and 3 inside*/
							amplitude = amplitude + value_calculation_triangle(min_depth, min_value, max_depth, max_value, XX1, XX2, XX3, YY1, YY2, YY3, ZZ1, ZZ2, ZZ3, sgn);
							}
						else
							{
				    			/*case 2: 1, 2 inside, 3 outside. two intermediaires points P (1-3) & Q (2-3)*/
				    			PY = lim_Y;					QY = lim_Y;
				    			PX = XX3 + (XX1-XX3) * (PY-YY3) / (YY1-YY3);	QX = XX3 + (XX2-XX3) * (QY-YY3) / (YY2-YY3);	
				    			PZ = ZZ3 + (ZZ1-ZZ3) * (PY-YY3) / (YY1-YY3);	QZ = ZZ3 + (ZZ2-ZZ3) * (QY-YY3) / (YY2-YY3);
							amplitude = amplitude + value_calculation_triangle(min_depth, min_value, max_depth, max_value, XX1, XX2, XX3, YY1, YY2, YY3, ZZ1, ZZ2, ZZ3, sgn);
							amplitude = amplitude - value_calculation_triangle(min_depth, min_value, max_depth, max_value, PX, QX, XX3, PY, QY, YY3, PZ, QZ, ZZ3, sgn);
							}
						}
					else
						{
						if (YY3 < lim_Y)
							{
				    			/*case 3: 1, 3 inside, 2 outside. two intermediaires points P (1-2) & Q (2-3)*/
				    			PY = lim_Y;					QY = lim_Y;
				    			PX = XX2 + (XX1-XX2) * (PY-YY2) / (YY1-YY2);	QX = XX2 + (XX3-XX2) * (QY-YY2) / (YY3-YY2);	
				    			PZ = ZZ2 + (ZZ1-ZZ2) * (PY-YY2) / (YY1-YY2);	QZ = ZZ2 + (ZZ3-ZZ2) * (QY-YY2) / (YY3-YY2);
							amplitude = amplitude + value_calculation_triangle(min_depth, min_value, max_depth, max_value, XX1, XX2, XX3, YY1, YY2, YY3, ZZ1, ZZ2, ZZ3, sgn);
							amplitude = amplitude - value_calculation_triangle(min_depth, min_value, max_depth, max_value, PX, XX2, QX, PY, QY, YY3, PZ, ZZ2, QZ, sgn);
							}
						else
							{
				    			/*case 4: 1 inside, 2 3 outside. two intermediaires points P (1-3) & Q (1-2)*/
				    			PY = lim_Y;					QY = lim_Y;
				    			PX = XX1 + (XX3-XX1) * (PY-YY1) / (YY3-YY1);	QX = XX1 + (XX2-XX1) * (QY-YY1) / (YY2-YY1);	
				    			PZ = ZZ1 + (ZZ3-ZZ1) * (PY-YY1) / (YY3-YY1);	QZ = ZZ1 + (ZZ2-ZZ1) * (QY-YY1) / (YY2-YY1);
							amplitude = amplitude + value_calculation_triangle(min_depth, min_value, max_depth, max_value, XX1, QX, PX, YY1, QY, PY, ZZ1, QZ, PZ, sgn);
							}
						}
					}
				else
					{
					if (YY2 < lim_Y)
						{
						if (YY3 < lim_Y)
							{
							/*case 5: 1, 2 inside, 1 outside. two intermediaires points P (1-3) & Q (1-2)*/
				    			PY = lim_Y;					QY = lim_Y;
				    			PX = XX1 + (XX3-XX1) * (PY-YY1) / (YY3-YY1);	QX = XX1 + (XX2-XX1) * (QY-YY1) / (YY2-YY1);	
				    			PZ = ZZ1 + (ZZ3-ZZ1) * (PY-YY1) / (YY3-YY1);	QZ = ZZ1 + (ZZ2-ZZ1) * (QY-YY1) / (YY2-YY1);
							amplitude = amplitude + value_calculation_triangle(min_depth, min_value, max_depth, max_value, XX1, XX2, XX3, YY1, YY2, YY3, ZZ1, ZZ2, ZZ3, sgn);
							amplitude = amplitude - value_calculation_triangle(min_depth, min_value, max_depth, max_value, XX1, QX, PX, YY1, QY, PY, ZZ1, QZ, PZ, sgn);
							}
						else
							{
							/*case 6: 2 inside, 1 3 outside. two intermediaires points P (1-2) & Q (2-3)*/
				    			PY = lim_Y;					QY = lim_Y;
				    			PX = XX2 + (XX1-XX2) * (PY-YY2) / (YY1-YY2);	QX = XX2 + (XX3-XX2) * (QY-YY2) / (YY3-YY2);	
				    			PZ = ZZ2 + (ZZ1-ZZ2) * (PY-YY2) / (YY1-YY2);	QZ = ZZ2 + (ZZ3-ZZ2) * (QY-YY2) / (YY3-YY2);
							amplitude = amplitude + value_calculation_triangle(min_depth, min_value, max_depth, max_value, PX, XX2, QX, PY, QY, YY3, PZ, ZZ2, QZ, sgn);
							}
						}
					else
						{
						if (YY3 < lim_Y)
							{
				    			/*case 7: 3 inside, 1 2 outside. two intermediaires points P (1-3) & Q (2-3)*/
				    			PY = lim_Y;					QY = lim_Y;
				    			PX = XX3 + (XX1-XX3) * (PY-YY3) / (YY1-YY3);	QX = XX3 + (XX2-XX3) * (QY-YY3) / (YY2-YY3);	
				    			PZ = ZZ3 + (ZZ1-ZZ3) * (PY-YY3) / (YY1-YY3);	QZ = ZZ3 + (ZZ2-ZZ3) * (QY-YY3) / (YY2-YY3);
							amplitude = amplitude + value_calculation_triangle(min_depth, min_value, max_depth, max_value, PX, QX, XX3, PY, QY, YY3, PZ, QZ, ZZ3, sgn);
							}
						else
							{
				    			/*case 8: 1 2 3 outside.*/
							}
						}
					}
				}
			}
		}
	printf("Avalue_calculation = %lf ",amplitude);
	amplitude_value_calculation = amplitude;
	return amplitude;
	}
	
	
double value_calculation2()
	{
	/*calculation of the value caugth by the trawl. tHE value is defined by a linear fonction (two points: min_depth, min_value
	and max_depth max_value). For each triangular element the vale of each vertex is calculated (val1 val2 and val3)
	the value caugtrh by this triangular element is the mean value of val1, val2 and val3 multiplied par the surface of
	the triangular element projected on the plane perpendicular to the towing speed (here the plane YZ)
	In fact therer are 27 cases depending on the vertical absisse of the vertex (ZZ1, ZZ2 and ZZ2) relatively to 
	min_depth and max_depth: these cases correspond to (ZZ1>= max_depth), (ZZ1<max_depth & ZZ1>=min_depth), (ZZ1<min_depth) with the same for ZZ2 and ZZ3*/
	int zi,surf,z1,z2,z3,sgn;
	double amplitude,min_depth,max_depth,min_value,max_value;
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3;
  	double PX,PY,PZ,QX,QY,QZ;
  	double val1,val2,val3,surface_projetee;
  	
	amplitude = 0.0;
 	for (zi = 1; zi<=Structure.nb_value ; zi++)
		{
		if (Value.depth1[zi] > Value.depth2[zi])
			{
			max_depth = Value.depth1[zi];	max_value = Value.value1[zi];
			min_depth = Value.depth2[zi];	min_value = Value.value2[zi];
			}
		else
			{
			max_depth = Value.depth2[zi];	max_value = Value.value2[zi];
			min_depth = Value.depth1[zi];	min_value = Value.value1[zi];
			}
		/*printf("value nb %d:",zi);
		printf("min value %lf at depth %lf and max value %lf at depth %lf\n",min_value,min_depth,max_value,max_depth);*/
	  	for (surf = 1; surf<= NOMBRE_SURFACES; surf++)
			{
			/*numero des coordonnees x des sommets 1 2 et 3 du triangle*/
			z1 = yc(surf,1);  	z2 = yc(surf,4);  	z3 = yc(surf,7);
	    		XX1 = wf[z1+0];    	YY1 = wf[z1+1];    	ZZ1 = wf[z1+2];
	    		XX2 = wf[z2+0];    	YY2 = wf[z2+1];    	ZZ2 = wf[z2+2];
	    		XX3 = wf[z3+0];    	YY3 = wf[z3+1];    	ZZ3 = wf[z3+2];
			sgn = orientation_triangle_val(z1, z2, z3);

			amplitude = amplitude + value_calculation_triangle(min_depth, min_value, max_depth, max_value, XX1, XX2, XX3, YY1, YY2, YY3, ZZ1, ZZ2, ZZ3, sgn);
			}
		}
	printf("Avalue_calculation = %lf ",amplitude);
	amplitude_value_calculation = amplitude;
	return amplitude;
	}
	
	
double value_calculation()
	{
	/*calculation of the value caugth by the trawl. tHE value is defined by a linear fonction (two points: min_depth, min_value
	and max_depth max_value). For each triangular element the vale of each vertex is calculated (val1 val2 and val3)
	the value caugtrh by this triangular element is the mean value of val1, val2 and val3 multiplied par the surface of
	the triangular element projected on the plane perpendicular to the towing speed (here the plane YZ)
	In fact therer are 27 cases depending on the vertical absisse of the vertex (ZZ1, ZZ2 and ZZ2) relatively to 
	min_depth and max_depth: these cases correspond to (ZZ1>= max_depth), (ZZ1<max_depth & ZZ1>=min_depth), (ZZ1<min_depth) with the same for ZZ2 and ZZ3*/
	int zi,surf,z1,z2,z3,sgn;
	double amplitude,min_depth,max_depth,min_value,max_value;
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3;
  	double PX,PY,PZ,QX,QY,QZ;
  	double val1,val2,val3,surface_projetee;
  	
	amplitude = 0.0;
 	for (zi = 1; zi<=Structure.nb_value ; zi++)
		{
		if (Value.depth1[zi] > Value.depth2[zi])
			{
			max_depth = Value.depth1[zi];	max_value = Value.value1[zi];
			min_depth = Value.depth2[zi];	min_value = Value.value2[zi];
			}
		else
			{
			max_depth = Value.depth2[zi];	max_value = Value.value2[zi];
			min_depth = Value.depth1[zi];	min_value = Value.value1[zi];
			}
		/*printf("value nb %d:",zi);
		printf("min value %lf at depth %lf and max value %lf at depth %lf\n",min_value,min_depth,max_value,max_depth);*/
	  	for (surf = 1; surf<= NOMBRE_SURFACES; surf++)
			{
			/*numero des coordonnees x des sommets 1 2 et 3 du triangle*/
			z1 = yc(surf,1);  	z2 = yc(surf,4);  	z3 = yc(surf,7);
	    		XX1 = wf[z1+0];    	YY1 = wf[z1+1];    	ZZ1 = wf[z1+2];
	    		XX2 = wf[z2+0];    	YY2 = wf[z2+1];    	ZZ2 = wf[z2+2];
	    		XX3 = wf[z3+0];    	YY3 = wf[z3+1];    	ZZ3 = wf[z3+2];
			sgn = orientation_triangle_val(z1, z2, z3);
	    		if (ZZ1 >= max_depth)
	    			{
		    		if (ZZ2 >= max_depth)
		    			{
			    		if (ZZ3 >= max_depth)
			    			{			    			
			    			/*case:8 1, 2 & 3 above*/	
			    			val1 = 0.0; 	val2 = 0.0; 	val3 = 0.0; 		    			
			    			surface_projetee = 0.0;
			    			}
			    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
			    			{
			    			/*case:2 1, 2 above, 3 inside. only one vertex inside: two intermediaires points P (1) & Q (2)*/
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if (ZZ3< min_depth)
			    			{
			    			/*case:24 1, 2 above, 3 below. only one vertex inside: two intermediaires points P (1) & Q (2)*/
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
		    			}
		    		if ((ZZ2< max_depth) && (ZZ2 >= min_depth))
		    			{
			    		if (ZZ3 >= max_depth)
			    			{
			    			/*case:3 1, 3 above, 2 inside. only one vertex inside: two intermediaires points P (1) & Q (3)*/
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
			    			{
			    			/*case:10 1 above, 2, 3 inside. only one vertex outside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if (ZZ3< min_depth)
			    			{
			    			/*case:18 1 above, 2 inside, 3 below. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
		    			}
		    		if (ZZ2< min_depth)
		    			{
			    		if (ZZ3 >= max_depth)
			    			{
			    			/*case:23 1, 3 above, 2 below. only one vertex inside: two intermediaires points P (1) & Q (3)*/
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
						PZ = min_depth;					QZ = min_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
			    			{
			    			/*case:20 1 above, 2 below, 3 inside. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if (ZZ3< min_depth)
			    			{
			    			/*case:25 1 above, 2, 3 below. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
		    			}
	    			}
	    		if ((ZZ1< max_depth) && (ZZ1 >= min_depth))
	    			{
		    		if (ZZ2 >= max_depth)
		    			{
			    		if (ZZ3 >= max_depth)
			    			{
			    			/*case:4 1 inside, 2, 3 above. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
			    			{			    			
			    			/*case:11 2 above, 1, 3 inside. only one vertex outside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if (ZZ3< min_depth)
			    			{			    			
			    			/*case:17 1 inside, 2 above, 3 below. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
		    			}
		    		if ((ZZ2< max_depth) && (ZZ2 >= min_depth))
		    			{
			    		if (ZZ3 >= max_depth)
			    			{
			    			/*case:12 1, 2 inside, 3 above. only one vertex outside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
			    			{
			    			/*case:1 1, 2, 3 inside. all inside*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			/*if (sgn < 0)
			    				{
							printf("sgn %d:",sgn);
							printf("surf %d:",surf);
							printf("panel %d:",Surface[surf].type);
							printf("val1 %lf val2 %lf val3 %lf ",val1,val2,val3);
							printf("surface_projetee %lf \n",surface_projetee);
			    				}*/
			    			}
			    		if (ZZ3< min_depth)
			    			{
			    			/*case:15 1, 2 inside, 3 below. only one vertex outside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
		    			}
		    		if (ZZ2< min_depth)
		    			{
			    		if (ZZ3 >= max_depth)
			    			{
			    			/*case:16 1 inside, 2 below, 3 above. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
			    			{
			    			/*case:14 1, 3 inside, 2 below. only one vertex outside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
						PZ = min_depth;					QZ = min_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if (ZZ3< min_depth)
			    			{
			    			/*case:7 1 inside, 2, 3 below. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
		    			}
	    			}
	    		if (ZZ1< min_depth)
	    			{
		    		if (ZZ2 >= max_depth)
		    			{
			    		if (ZZ3 >= max_depth)
			    			{
			    			/*case:22 1 below, 2, 3 above. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
			    			{
			    			/*case:21 1 below, 2 above, 3 inside. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if (ZZ3< min_depth)
			    			{
			    			/*case:26 1, 3 below, 2 above. only one vertex inside: two intermediaires points P (1) & Q (3)*/
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
		    			}
		    		if ((ZZ2< max_depth) && (ZZ2 >= min_depth))
		    			{
			    		if (ZZ3 >= max_depth)
			    			{
			    			/*case:19 1 below, 2 inside, 3 above. only one vertex inside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
			    			{
			    			/*case:13 1 below, 2, 3 inside. only one vertex outside: two intermediaires points P (2) & Q (3)*/
			    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
			    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if (ZZ3< min_depth)
			    			{			    			
			    			/*case:6 1, 3 below, 2 inside. only one vertex inside: two intermediaires points P (1) & Q (3)*/
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
			    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
		    			}
		    		if (ZZ2< min_depth)
		    			{
			    		if (ZZ3 >= max_depth)
			    			{
			    			/*case:27 1, 2 below, 3 above. only one vertex inside: two intermediaires points P (1) & Q (2)*/
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			PZ = max_depth;					QZ = max_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
			    			{
			    			/*case:5 1, 2 below, 3 inside. only one vertex inside: two intermediaires points P (1) & Q (2)*/
			    			PZ = min_depth;					QZ = min_depth;
			    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
			    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
			    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
			    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
			    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
			    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
			    		if (ZZ3< min_depth)
			    			{
			    			/*case:9 1, 2, 3 below*/
			    			val1 = 0.0; 	val2 = 0.0; 	val3 = 0.0; 		    			
			    			surface_projetee = 0.0;
						amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
			    			}
		    			}
	    			}
			}
		}
	printf("Avalue_calculation = %lf ",amplitude);
	amplitude_value_calculation = amplitude;
	return amplitude;
	}
	
	
double value_calculation_triangle(double min_depth, double min_value, double max_depth, double max_value, double XX1, double XX2, double XX3, double YY1, double YY2, double YY3, double ZZ1, double ZZ2, double ZZ3, double sgn)
	{
	int zi,surf,z1,z2,z3;
	double amplitude;
  	double PX,PY,PZ,QX,QY,QZ;
  	double val1,val2,val3,surface_projetee;
  	
  	amplitude = 0.0;
	if (ZZ1 >= max_depth)
		{
    		if (ZZ2 >= max_depth)
    			{
	    		if (ZZ3 >= max_depth)
	    			{			    			
	    			/*case:8 1, 2 & 3 above*/	
	    			val1 = 0.0; 	val2 = 0.0; 	val3 = 0.0; 		    			
	    			surface_projetee = 0.0;
	    			}
	    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
	    			{
	    			/*case:2 1, 2 above, 3 inside. only one vertex inside: two intermediaires points P (1) & Q (2)*/
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if (ZZ3< min_depth)
	    			{
	    			/*case:24 1, 2 above, 3 below. only one vertex inside: two intermediaires points P (1) & Q (2)*/
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
    			}
    		if ((ZZ2< max_depth) && (ZZ2 >= min_depth))
    			{
	    		if (ZZ3 >= max_depth)
	    			{
	    			/*case:3 1, 3 above, 2 inside. only one vertex inside: two intermediaires points P (1) & Q (3)*/
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
	    			{
	    			/*case:10 1 above, 2, 3 inside. only one vertex outside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if (ZZ3< min_depth)
	    			{
	    			/*case:18 1 above, 2 inside, 3 below. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
    			}
    		if (ZZ2< min_depth)
    			{
	    		if (ZZ3 >= max_depth)
	    			{
	    			/*case:23 1, 3 above, 2 below. only one vertex inside: two intermediaires points P (1) & Q (3)*/
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
				PZ = min_depth;					QZ = min_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
	    			{
	    			/*case:20 1 above, 2 below, 3 inside. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if (ZZ3< min_depth)
	    			{
	    			/*case:25 1 above, 2, 3 below. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
    			}
		}
	if ((ZZ1< max_depth) && (ZZ1 >= min_depth))
		{
    		if (ZZ2 >= max_depth)
    			{
	    		if (ZZ3 >= max_depth)
	    			{
	    			/*case:4 1 inside, 2, 3 above. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
	    			{			    			
	    			/*case:11 2 above, 1, 3 inside. only one vertex outside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if (ZZ3< min_depth)
	    			{			    			
	    			/*case:17 1 inside, 2 above, 3 below. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
    			}
    		if ((ZZ2< max_depth) && (ZZ2 >= min_depth))
    			{
	    		if (ZZ3 >= max_depth)
	    			{
	    			/*case:12 1, 2 inside, 3 above. only one vertex outside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
	    			{
	    			/*case:1 1, 2, 3 inside. all inside*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			/*if (sgn < 0)
	    				{
					printf("sgn %d:",sgn);
					printf("surf %d:",surf);
					printf("panel %d:",Surface[surf].type);
					printf("val1 %lf val2 %lf val3 %lf ",val1,val2,val3);
					printf("surface_projetee %lf \n",surface_projetee);
	    				}*/
	    			}
	    		if (ZZ3< min_depth)
	    			{
	    			/*case:15 1, 2 inside, 3 below. only one vertex outside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
    			}
    		if (ZZ2< min_depth)
    			{
	    		if (ZZ3 >= max_depth)
	    			{
	    			/*case:16 1 inside, 2 below, 3 above. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
	    			{
	    			/*case:14 1, 3 inside, 2 below. only one vertex outside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
				PZ = min_depth;					QZ = min_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if (ZZ3< min_depth)
	    			{
	    			/*case:7 1 inside, 2, 3 below. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
    			}
		}
	if (ZZ1< min_depth)
		{
    		if (ZZ2 >= max_depth)
    			{
	    		if (ZZ3 >= max_depth)
	    			{
	    			/*case:22 1 below, 2, 3 above. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
	    			{
	    			/*case:21 1 below, 2 above, 3 inside. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if (ZZ3< min_depth)
	    			{
	    			/*case:26 1, 3 below, 2 above. only one vertex inside: two intermediaires points P (1) & Q (3)*/
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
    			}
    		if ((ZZ2< max_depth) && (ZZ2 >= min_depth))
    			{
	    		if (ZZ3 >= max_depth)
	    			{
	    			/*case:19 1 below, 2 inside, 3 above. only one vertex inside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
	    			{
	    			/*case:13 1 below, 2, 3 inside. only one vertex outside: two intermediaires points P (2) & Q (3)*/
	    			val1 = min_value + (max_value-min_value) * (ZZ1-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * (ZZ2-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, YY1, ZZ1, 0.0, YY2, ZZ2, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX1 + (XX2-XX1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QX = XX1 + (XX3-XX1) * (PZ-ZZ1) / (ZZ3-ZZ1);	
	    			PY = YY1 + (YY2-YY1) * (PZ-ZZ1) / (ZZ2-ZZ1);	QY = YY1 + (YY3-YY1) * (PZ-ZZ1) / (ZZ3-ZZ1);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY1, ZZ1);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if (ZZ3< min_depth)
	    			{			    			
	    			/*case:6 1, 3 below, 2 inside. only one vertex inside: two intermediaires points P (1) & Q (3)*/
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX2 + (XX1-XX2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QX = XX2 + (XX3-XX2) * (PZ-ZZ2) / (ZZ3-ZZ2);	
	    			PY = YY2 + (YY1-YY2) * (PZ-ZZ2) / (ZZ1-ZZ2);	QY = YY2 + (YY3-YY2) * (PZ-ZZ2) / (ZZ3-ZZ2);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY2, ZZ2);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
    			}
    		if (ZZ2< min_depth)
    			{
	    		if (ZZ3 >= max_depth)
	    			{
	    			/*case:27 1, 2 below, 3 above. only one vertex inside: two intermediaires points P (1) & Q (2)*/
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			PZ = max_depth;					QZ = max_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude - sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if ((ZZ3< max_depth) && (ZZ3 >= min_depth))
	    			{
	    			/*case:5 1, 2 below, 3 inside. only one vertex inside: two intermediaires points P (1) & Q (2)*/
	    			PZ = min_depth;					QZ = min_depth;
	    			PX = XX3 + (XX1-XX3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QX = XX3 + (XX2-XX3) * (PZ-ZZ3) / (ZZ2-ZZ3);	
	    			PY = YY3 + (YY1-YY3) * (PZ-ZZ3) / (ZZ1-ZZ3);	QY = YY3 + (YY2-YY3) * (PZ-ZZ3) / (ZZ2-ZZ3);
	    			val1 = min_value + (max_value-min_value) * ( PZ-min_depth) / (max_depth-min_depth);
	    			val2 = min_value + (max_value-min_value) * ( QZ-min_depth) / (max_depth-min_depth);
	    			val3 = min_value + (max_value-min_value) * (ZZ3-min_depth) / (max_depth-min_depth);
	    			surface_projetee = surface_triangle2(0.0, PY, PZ, 0.0, QY, QZ, 0.0, YY3, ZZ3);
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
	    		if (ZZ3< min_depth)
	    			{
	    			/*case:9 1, 2, 3 below*/
	    			val1 = 0.0; 	val2 = 0.0; 	val3 = 0.0; 		    			
	    			surface_projetee = 0.0;
				amplitude = amplitude + sgn * (val1+val2+val3) / 3.0 * surface_projetee;
	    			}
    			}
	    	}
	return amplitude;
	}

