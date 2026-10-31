#include "batz.h"

int interieur_triangle(double xx1, double xx2, double xx3, double yy1, double yy2, double yy3)
	{
	float  S, S_ref;
	
	/*RECHERCHE SI LE NOEUD DE COORDONNEES 0,0 (1,0 1,1 et 0,1) EST A L INTERIEUR DU triangle de coordonnees
	xx1 yy1, xx2 yy2 et xx3 yy3.
	SI A L INTERIEUR DU triangle RETURN = 1
	SI A L EXTERIEUR DU triangle RETURN = 0
	0,0 (1,0 1,1 et 0,1) sont les coordonnees de l ecran
	pour ne tracer que ces triangles
	*/

	/*S_REF = SURFACE DU TRIANGLE xx1 yy1, xx2 yy2 et xx3 yy3*/
	S_ref = surface_triangle( xx1, yy1, xx2, yy2, xx3, yy3);
	
	S     = surface_triangle( xx1, yy1, xx2, yy2, 0.0, 0.0);
	S    += surface_triangle( xx2, yy2, xx3, yy3, 0.0, 0.0);
	S    += surface_triangle( xx3, yy3, xx1, yy1, 0.0, 0.0);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
		
	S     = surface_triangle( xx1, yy1, xx2, yy2, 0.0, 1.0);
	S    += surface_triangle( xx2, yy2, xx3, yy3, 0.0, 1.0);
	S    += surface_triangle( xx3, yy3, xx1, yy1, 0.0, 1.0);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
		
	S     = surface_triangle( xx1, yy1, xx2, yy2, 1.0, 0.0);
	S    += surface_triangle( xx2, yy2, xx3, yy3, 1.0, 0.0);
	S    += surface_triangle( xx3, yy3, xx1, yy1, 1.0, 0.0);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
		
	S     = surface_triangle( xx1, yy1, xx2, yy2, 1.0, 1.0);
	S    += surface_triangle( xx2, yy2, xx3, yy3, 1.0, 1.0);
	S    += surface_triangle( xx3, yy3, xx1, yy1, 1.0, 1.0);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
		
	/*RECHERCHE SI LE NOEUD DE COORDONNEES xx1,yy1 (xx2,yy2 et xx3,yy3) EST A L INTERIEUR DU triangle de coordonnees
	0 0, 1 1 et 0 1.
	SI A L INTERIEUR DU triangle RETURN = 1
	SI A L EXTERIEUR DU triangle RETURN = 0
	*/

	/*S_REF = SURFACE DU TRIANGLE 0 0, 1 1 et 0 1*/
	S_ref = 0.5;
	
	S     = surface_triangle( 0.0, 0.0, 1.0, 1.0, xx1, yy1);
	S    += surface_triangle( 1.0, 1.0, 0.0, 1.0, xx1, yy1);
	S    += surface_triangle( 0.0, 1.0, 0.0, 0.0, xx1, yy1);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
		
	S     = surface_triangle( 0.0, 0.0, 1.0, 1.0, xx2, yy2);
	S    += surface_triangle( 1.0, 1.0, 0.0, 1.0, xx2, yy2);
	S    += surface_triangle( 0.0, 1.0, 0.0, 0.0, xx2, yy2);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
	
	S     = surface_triangle( 0.0, 0.0, 1.0, 1.0, xx3, yy3);
	S    += surface_triangle( 1.0, 1.0, 0.0, 1.0, xx3, yy3);
	S    += surface_triangle( 0.0, 1.0, 0.0, 0.0, xx3, yy3);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
		
		
	/*RECHERCHE SI LE NOEUD DE COORDONNEES xx1,yy1 (xx2,yy2 et xx3,yy3) EST A L INTERIEUR DU triangle de coordonnees
	0 0, 1 0 et 1 1.
	SI A L INTERIEUR DU triangle RETURN = 1
	SI A L EXTERIEUR DU triangle RETURN = 0
	*/

	/*S_REF = SURFACE DU TRIANGLE 0 0, 1 1 et 0 1*/
	S_ref = 0.5;
	
	S     = surface_triangle( 0.0, 0.0, 1.0, 0.0, xx1, yy1);
	S    += surface_triangle( 1.0, 0.0, 1.0, 1.0, xx1, yy1);
	S    += surface_triangle( 1.0, 1.0, 0.0, 0.0, xx1, yy1);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
		
	S     = surface_triangle( 0.0, 0.0, 1.0, 0.0, xx2, yy2);
	S    += surface_triangle( 1.0, 0.0, 1.0, 1.0, xx2, yy2);
	S    += surface_triangle( 1.0, 1.0, 0.0, 0.0, xx2, yy2);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
		
	S     = surface_triangle( 0.0, 0.0, 1.0, 0.0, xx3, yy3);
	S    += surface_triangle( 1.0, 0.0, 1.0, 1.0, xx3, yy3);
	S    += surface_triangle( 1.0, 1.0, 0.0, 0.0, xx3, yy3);
	if ((S > S_ref * 0.999) && (S < S_ref * 1.001)) return 1;
		
	return 0;
	}
	
	
double surface_triangle(double xx1, double yy1, double xx2, double yy2, double xx3, double yy3)
	{
	double surface,prod_vect;
	
	/*
	calcul de la surface du triangle dont les coordonnes du sommet 1 (2&3) sont
	xx1, yy1, (xx2, yy2 & xx3, yy3) a l aide du produit vectoriel entre 12 et 13
	*/
	
  	prod_vect = (double) ((xx3-xx1)*(yy2-yy1) - (yy3-yy1)*(xx2-xx1));
  	surface   = (double) (0.5 * fabs(prod_vect));
  	return surface;
  	}
	
	
 	
