#include "batz.h"

int orientation_triangle(int elem)
	{
  	/*calculer l orientation du triangle 
  	si > 0 le volume compris entre ce triangle et le front s ajoute a la prise
  	si < 0 le volume compris entre ce triangle et le front se retranche de la prise
  	pour l orientation on calcule le produit vectoriel entre 12 et 13, 1 2 3 sont les sommets du triangle*/
  	
  	int orientation,zh,zi,zj;
  	double nxx;
  	double y12,z12,y23,z23;
  	
  	/*numeros des coordonnees selon x des sommets du triangle*/
  	zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  	
  	/*variation de coordonnees entre les sommets*/
  	y12 = wfcodend[zi+1] - wfcodend[zh+1];y23 = wfcodend[zj+1] - wfcodend[zi+1];
  	z12 = wfcodend[zi+2] - wfcodend[zh+2];z23 = wfcodend[zj+2] - wfcodend[zi+2];
  	
  	/*vecteur normal au triangle*/
  	nxx = y12*z23 - z12*y23;

  	/*calcul du sens du triangle si > 0 volume ajoute et surface ajoute si < 0 retranche*/
  	if (fabs(nxx) != 0.0)
  		{
  		orientation = (int) (- nxx / fabs(nxx));
  		}
  	else
  		{
  		orientation = 1;
  		}
  	/*printf("nxx = %12.4lf  \n",nxx);*/
  	
  	return orientation;
  	}
  	
  	
void surface_volume(int elem, double frontxx, double *surfacefront,double *volumefront)
  	{
  	/*calcul de la surface du front et du volume entre le front et le fond du filet 
  	connaissant la position du front : frontxx*/
  	
  	double XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3,x12,y12,z12,x23,y23,z23,x31,y31,z31,surfacetriangle,volumetriangle;
  	double yinter1,zinter1,yinter2,zinter2,surfacetriangleamont;
  	int zh,zi,zj,sgn;
  	
  	extern double surface_triangle2(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double
  	z3);
  	
	*volumefront = 0.0;
	*surfacefront = 0.0;
	
  		/*numeros des coordonnees selon x des sommets du triangle*/
  		zh = yc(elem,1);  zi = yc(elem,4);  zj = yc(elem,7);
  		
  		/*coordonnees du triangle*/
  		XX1 = wfcodend[zh  ];	XX2 = wfcodend[zi  ];	XX3 = wfcodend[zj  ];
  		YY1 = wfcodend[zh+1];	YY2 = wfcodend[zi+1];	YY3 = wfcodend[zj+1];
  		ZZ1 = wfcodend[zh+2];	ZZ2 = wfcodend[zi+2];	ZZ3 = wfcodend[zj+2];

  		/*ne traiter que les surfaces a l arriere ou en partie a l arriere du front*/
  		if ((XX1 > frontxx) || (XX2 > frontxx) || (XX3 > frontxx))
  			{
			sgn = orientation_triangle( elem);
  			
  			x12 = XX2 - XX1;	x23 = XX3 - XX2;	x31 = XX1 - XX3;
  			y12 = YY2 - YY1;	y23 = YY3 - YY2;	y31 = YY1 - YY3;
  			z12 = ZZ2 - ZZ1;	z23 = ZZ3 - ZZ2;	z31 = ZZ1 - ZZ3;
  			
  			/* surfaces totalement a l arriere  du front*/
  			if ((XX1 > frontxx) && (XX2 > frontxx) && (XX3 > frontxx))
  				{
				surfacetriangle = surface_triangle2(frontxx, YY1, ZZ1, frontxx, YY2, ZZ2, frontxx, YY3, ZZ3);
  				volumetriangle = surfacetriangle * fabs((XX1 + XX2 + XX3) / 3.0 - frontxx);
  				/*ajout a la surface et au volume delimite par le front*/
  				*surfacefront +=  sgn * surfacetriangle;
  				*volumefront += sgn * volumetriangle;
  				}
  			/* surfaces partiellement a l arriere  du front : point 1 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  			on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  			if ((XX1 <= frontxx) && (XX2 > frontxx) && (XX3 > frontxx))
  				{
  				yinter1 = YY1 + y12 / x12 * (frontxx - XX1);
  				zinter1 = ZZ1 + z12 / x12 * (frontxx - XX1);
  				yinter2 = YY1 + y31 / x31 * (frontxx - XX1);
  				zinter2 = ZZ1 + z31 / x31 * (frontxx - XX1);
				surfacetriangle = surface_triangle2(frontxx, YY1, ZZ1, frontxx, YY2, ZZ2, frontxx, YY3, ZZ3);
  				volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontxx);
  				/*surface du triangle amont forme par 1 inter1 et inter2 : en amont du front a retranche de la surface totale*/
				surfacetriangleamont = surface_triangle2(frontxx, YY1, ZZ1, frontxx, yinter1, zinter1, frontxx, yinter2, zinter2);
  				/*surface et volume en aval au front*/
    				surfacetriangle -=  surfacetriangleamont;
  				volumetriangle -=  (surfacetriangleamont * ((XX1 + frontxx + frontxx) / 3.0 - frontxx));
				
  				*surfacefront +=  sgn * surfacetriangle;
  				*volumefront += sgn * volumetriangle;
  				}
  			/* surfaces partiellement a l arriere  du front : point 2 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  			on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  			if ((XX1 > frontxx) && (XX2 <= frontxx) && (XX3 > frontxx))
  				{
  				yinter1 = YY2 + y23 / x23 * (frontxx - XX2);
  				zinter1 = ZZ2 + z23 / x23 * (frontxx - XX2);
  				yinter2 = YY2 + y12 / x12 * (frontxx - XX2);
  				zinter2 = ZZ2 + z12 / x12 * (frontxx - XX2);
				surfacetriangle = surface_triangle2(frontxx, YY1, ZZ1, frontxx, YY2, ZZ2, frontxx, YY3, ZZ3);
  				volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontxx);
				surfacetriangleamont = surface_triangle2(frontxx, yinter2, zinter2, frontxx, YY2, ZZ2, frontxx, yinter1, zinter1);
  				/*surface et volume en aval au front*/
  				surfacetriangle  -= surfacetriangleamont;
  				volumetriangle -= (surfacetriangleamont * ((frontxx + XX2 + frontxx) / 3.0 - frontxx));
  				
  				*surfacefront += sgn * surfacetriangle;
  				*volumefront += sgn * volumetriangle;
  				}
  			/* surfaces partiellement a l arriere  du front : point 3 en amont du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  			on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  			if ((XX1 > frontxx) && (XX2 > frontxx) && (XX3 <= frontxx))
  				{
  				yinter1 = YY3 + y31 / x31 * (frontxx - XX3);
  				zinter1 = ZZ3 + z31 / x31 * (frontxx - XX3);
  				yinter2 = YY3 + y23 / x23 * (frontxx - XX3);
  				zinter2 = ZZ3 + z23 / x23 * (frontxx - XX3);
				surfacetriangle = surface_triangle2(frontxx, YY1, ZZ1, frontxx, YY2, ZZ2, frontxx, YY3, ZZ3);
  				/*surface totale du triangle*/
  				volumetriangle = surfacetriangle * ((XX1 + XX2 + XX3) / 3.0 - frontxx);
				surfacetriangleamont = surface_triangle2(frontxx, yinter1, zinter1, frontxx, yinter2, zinter2, frontxx, YY3, ZZ3);
  				/*surface et volume en aval au front*/
  				surfacetriangle  -= surfacetriangleamont;
  				volumetriangle -= (surfacetriangleamont * ((frontxx + frontxx + XX3) / 3.0 - frontxx));
  				
  				*surfacefront += sgn * surfacetriangle;
  				*volumefront += sgn * volumetriangle;
  				}
  			/* surfaces partiellement a l arriere  du front : point 1 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 12 (31)
  			on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  			if ((XX1 > frontxx) && (XX2 <= frontxx) && (XX3 <= frontxx))
  				{
  				yinter1 = YY1 + y12 / x12 * (frontxx - XX1);
  				zinter1 = ZZ1 + z12 / x12 * (frontxx - XX1);
  				yinter2 = YY1 + y31 / x31 * (frontxx - XX1);
  				zinter2 = ZZ1 + z31 / x31 * (frontxx - XX1);
				surfacetriangle = surface_triangle2(frontxx, YY1, ZZ1, frontxx, yinter1, zinter1, frontxx, yinter2, zinter2);
  				volumetriangle = surfacetriangle * ((XX1 + frontxx + frontxx) / 3.0 - frontxx);
  			
  				*surfacefront += sgn * surfacetriangle;
  				*volumefront += sgn * volumetriangle;
  				}
  			/* surfaces partiellement a l arriere  du front : point 2 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 23 (12)
  			on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  			if ((XX1 <= frontxx) && (XX2 > frontxx) && (XX3 <= frontxx))
  				{
  				yinter1 = YY2 + y23 / x23 * (frontxx - XX2);
  				zinter1 = ZZ2 + z23 / x23 * (frontxx - XX2);
  				yinter2 = YY2 + y12 / x12 * (frontxx - XX2);
  				zinter2 = ZZ2 + z12 / x12 * (frontxx - XX2);
				surfacetriangle = surface_triangle2(frontxx, yinter2, zinter2, frontxx, YY2, ZZ2, frontxx, yinter1, zinter1);
  				volumetriangle = surfacetriangle * ((frontxx + XX2 + frontxx) / 3.0 - frontxx);
  			
  				*surfacefront += sgn * surfacetriangle;
  				*volumefront += sgn * volumetriangle;
  				}
  			/* surfaces partiellement a l arriere  du front : point 3 en aval du front
  			inter1 (inter2) est le point intersection du front avec le cote 31 (23)
  			on calcule le volume en amont que l on retranche au volume du cylindre de section triangulaire*/
  			if ((XX1 <= frontxx) && (XX2 <= frontxx) && (XX3 > frontxx))
  				{
  				yinter1 = YY3 + y31 / x31 * (frontxx - XX3);
  				zinter1 = ZZ3 + z31 / x31 * (frontxx - XX3);
  				yinter2 = YY3 + y23 / x23 * (frontxx - XX3);
  				zinter2 = ZZ3 + z23 / x23 * (frontxx - XX3);
				surfacetriangle = surface_triangle2(frontxx, yinter1, zinter1, frontxx, yinter2, zinter2, frontxx, YY3, ZZ3);
  				volumetriangle = surfacetriangle * ((frontxx + frontxx + XX3) / 3.0 - frontxx);
  			
  				*surfacefront += sgn * surfacetriangle;
  				*volumefront += sgn * volumetriangle;
  				}
  			}
		}
  	
  	
double surface_triangle2(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
	
	{
	double sx,sy,sz,surface;
	
	/*
	calcul de la surface du triangle dont les coordonnes du sommet 1 (2&3) sont
	x1, y1 z1, (x2, y2,z2 & x3, y3,z3) a l aide du produit vectoriel entre 12 et 13
	*/
	
	sx = (y2-y1) * (z3-z1) - (y3-y1) * (z2-z1);
	sy = (z2-z1) * (x3-x1) - (z3-z1) * (x2-x1);
	sz = (x2-x1) * (y3-y1) - (x3-x1) * (y2-y1);
  	     
  	surface = 0.5 * sqrt( (sx * sx) + (sy * sy) + (sz * sz) );
  	return surface;
  	}
	
	
 	
