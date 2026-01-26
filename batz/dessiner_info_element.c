#include "batz.h"

void dessiner_contour_triangle_element()
	{
	int pa,ba,no,deb,fin,pt1,pt2,pt3,nb_total;
	double pt4x,pt4y,pt5x,pt5y;

	nb_total = NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES+Ball.nb;

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES+Ball.nb;no++)
		{ 
		pa = profondeur[no];

		/*printf("no = %8d total = %8d pa = %8d NOMBRE_SURFACES = %8d \n",no,nb_total,pa,NOMBRE_SURFACES);*/
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
			/*
			if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float)) break;
			*/
			if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt1 pt2*/
				/*pt5 est situe sur le cote pt1 pt3*/
				pt4x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].x-Noeud[pt1].x) / (Noeud[pt2].z-Noeud[pt1].z);
				pt4y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].y-Noeud[pt1].y) / (Noeud[pt2].z-Noeud[pt1].z);
				pt5x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].x-Noeud[pt1].x) / (Noeud[pt3].z-Noeud[pt1].z);
				pt5y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].y-Noeud[pt1].y) / (Noeud[pt3].z-Noeud[pt1].z);
			
				if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
					{
					EffaceTriangle(gris_externe, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y, pt5x, pt5y);
					EffaceTriangle(gris_externe, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y, pt5x, pt5y);
					}	
				else	
					{
					EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y, pt5x, pt5y);
					EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y, pt5x, pt5y);
					}
				/*
				EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y, pt5x, pt5y);
				EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y, pt5x, pt5y);
				*/
				TraceSegment(Surface[pa].color_side[1], Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(Surface[pa].color_side[2], Noeud[pt3].x, Noeud[pt3].y, pt5x,pt5y);
				TraceSegment(BLACK, pt5x, pt5y, pt4x, pt4y);
				TraceSegment(Surface[pa].color_side[3], pt4x, pt4y, Noeud[pt2].x, Noeud[pt2].y);
				}
			
			if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt2 pt3*/
				/*pt5 est situe sur le cote pt2 pt1*/
				pt4x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].x-Noeud[pt2].x) / (Noeud[pt3].z-Noeud[pt2].z);
				pt4y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].y-Noeud[pt2].y) / (Noeud[pt3].z-Noeud[pt2].z);
				pt5x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].x-Noeud[pt2].x) / (Noeud[pt1].z-Noeud[pt2].z);
				pt5y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].y-Noeud[pt2].y) / (Noeud[pt1].z-Noeud[pt2].z);
				
				if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
					{
					EffaceTriangle(gris_externe, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y, pt5x, pt5y);
					EffaceTriangle(gris_externe, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y, pt5x, pt5y);
					}	
				else	
					{
					EffaceTriangle(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y, pt5x, pt5y);
					EffaceTriangle(WHITE, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y, pt5x, pt5y);
					}
				/*
				EffaceTriangle(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y, pt5x, pt5y);
				EffaceTriangle(WHITE, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y, pt5x, pt5y);
				*/
				TraceSegment(Surface[pa].color_side[2], Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
				TraceSegment(Surface[pa].color_side[3], Noeud[pt1].x, Noeud[pt1].y, pt5x, pt5y);
				TraceSegment(BLACK, pt5x, pt5y, pt4x, pt4y);
				TraceSegment(Surface[pa].color_side[1], pt4x, pt4y, Noeud[pt3].x, Noeud[pt3].y);
				}
			
			if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt3 pt1*/
				/*pt5 est situe sur le cote pt3 pt2*/
				pt4x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].x-Noeud[pt3].x) / (Noeud[pt1].z-Noeud[pt3].z);
				pt4y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].y-Noeud[pt3].y) / (Noeud[pt1].z-Noeud[pt3].z);
				pt5x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].x-Noeud[pt3].x) / (Noeud[pt2].z-Noeud[pt3].z);
				pt5y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].y-Noeud[pt3].y) / (Noeud[pt2].z-Noeud[pt3].z);
				
				if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
					{
					EffaceTriangle(gris_externe, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, pt5x, pt5y);
					EffaceTriangle(gris_externe, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y, pt5x, pt5y);
					}	
				else	
					{
					EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, pt5x, pt5y);
					EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y, pt5x, pt5y);
					}
				/*
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, pt5x, pt5y);
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y, pt5x, pt5y);
				*/
				TraceSegment(Surface[pa].color_side[2], Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(Surface[pa].color_side[1], pt5x, pt5y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(Surface[pa].color_side[3], Noeud[pt2].x, Noeud[pt2].y, Noeud[pt1].x, Noeud[pt1].y);
				}
			
			
			if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt1 pt2*/
				/*pt5 est situe sur le cote pt1 pt3*/
				pt4x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].x-Noeud[pt1].x) / (Noeud[pt2].z-Noeud[pt1].z);
				pt4y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].y-Noeud[pt1].y) / (Noeud[pt2].z-Noeud[pt1].z);
				pt5x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].x-Noeud[pt1].x) / (Noeud[pt3].z-Noeud[pt1].z);
				pt5y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].y-Noeud[pt1].y) / (Noeud[pt3].z-Noeud[pt1].z);

				if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
					{
					EffaceTriangle(gris_externe, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y, pt5x, pt5y);
					}	
				else	
					{
					EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y, pt5x, pt5y);
					}
				/*
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y, pt5x, pt5y);
				*/
				TraceSegment(Surface[pa].color_side[3], Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(Surface[pa].color_side[2], pt5x, pt5y, Noeud[pt1].x, Noeud[pt1].y);
				}
			
			if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt2 pt3*/
				/*pt5 est situe sur le cote pt2 pt1*/
				pt4x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].x-Noeud[pt2].x) / (Noeud[pt3].z-Noeud[pt2].z);
				pt4y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].y-Noeud[pt2].y) / (Noeud[pt3].z-Noeud[pt2].z);
				pt5x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].x-Noeud[pt2].x) / (Noeud[pt1].z-Noeud[pt2].z);
				pt5y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].y-Noeud[pt2].y) / (Noeud[pt1].z-Noeud[pt2].z);

				if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
					{
					EffaceTriangle(gris_externe, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y, pt5x, pt5y);
					}	
				else	
					{
					EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y, pt5x, pt5y);
					}
				/*
				EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y, pt5x, pt5y);
				*/
				TraceSegment(Surface[pa].color_side[1], Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(Surface[pa].color_side[3], pt5x, pt5y, Noeud[pt2].x, Noeud[pt2].y);
				}
			
			if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt3 pt1*/
				/*pt5 est situe sur le cote pt3 pt2*/
				pt4x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].x-Noeud[pt3].x) / (Noeud[pt1].z-Noeud[pt3].z);
				pt4y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].y-Noeud[pt3].y) / (Noeud[pt1].z-Noeud[pt3].z);
				pt5x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].x-Noeud[pt3].x) / (Noeud[pt2].z-Noeud[pt3].z);
				pt5y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].y-Noeud[pt3].y) / (Noeud[pt2].z-Noeud[pt3].z);
				
				if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
					{
					EffaceTriangle(gris_externe, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y, pt5x, pt5y);
					}	
				else	
					{
					EffaceTriangle(WHITE, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y, pt5x, pt5y);
					}
				/*
				EffaceTriangle(WHITE, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y, pt5x, pt5y);
				*/
				TraceSegment(Surface[pa].color_side[2], Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(Surface[pa].color_side[1], pt5x, pt5y, Noeud[pt3].x, Noeud[pt3].y);
				}
			
			if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
				{
				if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
					{
					EffaceTriangle(gris_externe, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
					}	
				else	
					{
					EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
					}
				/*
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				*/
				TraceSegment(Surface[pa].color_side[3], Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(Surface[pa].color_side[1], Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(Surface[pa].color_side[2], Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
				}
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
			
			if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt1 pt2*/
				/*pt5 est situe sur le cote pt1 pt3*/
				pt4x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].x-Noeud[pt1].x) / (Noeud[pt2].z-Noeud[pt1].z);
				pt4y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].y-Noeud[pt1].y) / (Noeud[pt2].z-Noeud[pt1].z);
				pt5x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].x-Noeud[pt1].x) / (Noeud[pt3].z-Noeud[pt1].z);
				pt5y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].y-Noeud[pt1].y) / (Noeud[pt3].z-Noeud[pt1].z);
			
				EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y, pt5x, pt5y);
				EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, pt5x,pt5y);
				TraceSegment(BLACK, pt5x, pt5y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, Noeud[pt2].x, Noeud[pt2].y);
				}
			
			if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt2 pt3*/
				/*pt5 est situe sur le cote pt2 pt1*/
				pt4x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].x-Noeud[pt2].x) / (Noeud[pt3].z-Noeud[pt2].z);
				pt4y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].y-Noeud[pt2].y) / (Noeud[pt3].z-Noeud[pt2].z);
				pt5x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].x-Noeud[pt2].x) / (Noeud[pt1].z-Noeud[pt2].z);
				pt5y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].y-Noeud[pt2].y) / (Noeud[pt1].z-Noeud[pt2].z);
				
				EffaceTriangle(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y, pt5x, pt5y);
				EffaceTriangle(WHITE, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
				TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, pt5x, pt5y);
				TraceSegment(BLACK, pt5x, pt5y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, Noeud[pt3].x, Noeud[pt3].y);
				}
			
			if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt3 pt1*/
				/*pt5 est situe sur le cote pt3 pt2*/
				pt4x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].x-Noeud[pt3].x) / (Noeud[pt1].z-Noeud[pt3].z);
				pt4y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].y-Noeud[pt3].y) / (Noeud[pt1].z-Noeud[pt3].z);
				pt5x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].x-Noeud[pt3].x) / (Noeud[pt2].z-Noeud[pt3].z);
				pt5y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].y-Noeud[pt3].y) / (Noeud[pt2].z-Noeud[pt3].z);
				
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, pt5x, pt5y);
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, pt5x, pt5y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt1].x, Noeud[pt1].y);
				}
			
			
			if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt1 pt2*/
				/*pt5 est situe sur le cote pt1 pt3*/
				pt4x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].x-Noeud[pt1].x) / (Noeud[pt2].z-Noeud[pt1].z);
				pt4y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].y-Noeud[pt1].y) / (Noeud[pt2].z-Noeud[pt1].z);
				pt5x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].x-Noeud[pt1].x) / (Noeud[pt3].z-Noeud[pt1].z);
				pt5y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].y-Noeud[pt1].y) / (Noeud[pt3].z-Noeud[pt1].z);

				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, pt5x, pt5y, Noeud[pt1].x, Noeud[pt1].y);
				}
			
			if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt2 pt3*/
				/*pt5 est situe sur le cote pt2 pt1*/
				pt4x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].x-Noeud[pt2].x) / (Noeud[pt3].z-Noeud[pt2].z);
				pt4y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].y-Noeud[pt2].y) / (Noeud[pt3].z-Noeud[pt2].z);
				pt5x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].x-Noeud[pt2].x) / (Noeud[pt1].z-Noeud[pt2].z);
				pt5y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].y-Noeud[pt2].y) / (Noeud[pt1].z-Noeud[pt2].z);

				EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, pt5x, pt5y, Noeud[pt2].x, Noeud[pt2].y);
				}
			
			if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
				{
				/*pt4 est situe sur le cote pt3 pt1*/
				/*pt5 est situe sur le cote pt3 pt2*/
				pt4x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].x-Noeud[pt3].x) / (Noeud[pt1].z-Noeud[pt3].z);
				pt4y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].y-Noeud[pt3].y) / (Noeud[pt1].z-Noeud[pt3].z);
				pt5x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].x-Noeud[pt3].x) / (Noeud[pt2].z-Noeud[pt3].z);
				pt5y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].y-Noeud[pt3].y) / (Noeud[pt2].z-Noeud[pt3].z);
				
				EffaceTriangle(WHITE, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y);
				TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
				TraceSegment(BLACK, pt5x, pt5y, Noeud[pt3].x, Noeud[pt3].y);
				}
			
			if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
				{
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
		
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			
			if ((Noeud[deb].z <= profondeur_coupe_float) && (Noeud[fin].z > profondeur_coupe_float))
				{
				/*pt4 est situe sur le segment deb fin a la profondeur profondeur_coupe_float*/
				pt4x = Noeud[deb].x + (profondeur_coupe_float-Noeud[deb].z) * (Noeud[fin].x-Noeud[deb].x) / (Noeud[fin].z-Noeud[deb].z);
				pt4y = Noeud[deb].y + (profondeur_coupe_float-Noeud[deb].z) * (Noeud[fin].y-Noeud[deb].y) / (Noeud[fin].z-Noeud[deb].z);
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, pt4x, pt4y);
				}
				
			if ((Noeud[deb].z > profondeur_coupe_float) && (Noeud[fin].z <= profondeur_coupe_float))
				{
				/*pt4 est situe sur le segment deb fin a la profondeur profondeur_coupe_float*/
				pt4x = Noeud[deb].x + (profondeur_coupe_float-Noeud[deb].z) * (Noeud[fin].x-Noeud[deb].x) / (Noeud[fin].z-Noeud[deb].z);
				pt4y = Noeud[deb].y + (profondeur_coupe_float-Noeud[deb].z) * (Noeud[fin].y-Noeud[deb].y) / (Noeud[fin].z-Noeud[deb].z);
				TraceSegment(BLACK, Noeud[fin].x, Noeud[fin].y, pt4x, pt4y);
				}
				
			if ((Noeud[deb].z <= profondeur_coupe_float) && (Noeud[fin].z <= profondeur_coupe_float))
				{
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				/*TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);*/
			
				if ((Noeud[deb].z <= profondeur_coupe_float) && (Noeud[fin].z > profondeur_coupe_float))
					{
					/*pt4 est situe sur le segment deb fin a la profondeur profondeur_coupe_float*/
					pt4x = Noeud[deb].x + (profondeur_coupe_float-Noeud[deb].z) * (Noeud[fin].x-Noeud[deb].x) / (Noeud[fin].z-Noeud[deb].z);
					pt4y = Noeud[deb].y + (profondeur_coupe_float-Noeud[deb].z) * (Noeud[fin].y-Noeud[deb].y) / (Noeud[fin].z-Noeud[deb].z);
					TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, pt4x, pt4y);
					}
				
				if ((Noeud[deb].z > profondeur_coupe_float) && (Noeud[fin].z <= profondeur_coupe_float))
					{
					/*pt4 est situe sur le segment deb fin a la profondeur profondeur_coupe_float*/
					pt4x = Noeud[deb].x + (profondeur_coupe_float-Noeud[deb].z) * (Noeud[fin].x-Noeud[deb].x) / (Noeud[fin].z-Noeud[deb].z);
					pt4y = Noeud[deb].y + (profondeur_coupe_float-Noeud[deb].z) * (Noeud[fin].y-Noeud[deb].y) / (Noeud[fin].z-Noeud[deb].z);
					TraceSegment(BLACK, Noeud[fin].x, Noeud[fin].y, pt4x, pt4y);
					}
				
				if ((Noeud[deb].z <= profondeur_coupe_float) && (Noeud[fin].z <= profondeur_coupe_float))
					{
					TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
					}
				}
			}
		}
	}

void draw_contour_triangle_diamond(int pa)
	{
	int ba,no,deb,fin,pt1,pt2,pt3,nb_total,color,rr,gg,bb,col[50];
	double pt4x,pt4y,pt5x,pt5y;

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
	
	color = panneau[Surface[pa].type].flag_dessin;
	//color = BLACK;

	if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt1 pt2*/
		/*pt5 est situe sur le cote pt1 pt3*/
		pt4x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].x-Noeud[pt1].x) / (Noeud[pt2].z-Noeud[pt1].z);
		pt4y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].y-Noeud[pt1].y) / (Noeud[pt2].z-Noeud[pt1].z);
		pt5x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].x-Noeud[pt1].x) / (Noeud[pt3].z-Noeud[pt1].z);
		pt5y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].y-Noeud[pt1].y) / (Noeud[pt3].z-Noeud[pt1].z);
	
		TraceSegment(color, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(color, Noeud[pt3].x, Noeud[pt3].y, pt5x,pt5y);
		TraceSegment(BLACK, pt5x, pt5y, pt4x, pt4y);
		TraceSegment(color, pt4x, pt4y, Noeud[pt2].x, Noeud[pt2].y);
		}
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt2 pt3*/
		/*pt5 est situe sur le cote pt2 pt1*/
		pt4x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].x-Noeud[pt2].x) / (Noeud[pt3].z-Noeud[pt2].z);
		pt4y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].y-Noeud[pt2].y) / (Noeud[pt3].z-Noeud[pt2].z);
		pt5x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].x-Noeud[pt2].x) / (Noeud[pt1].z-Noeud[pt2].z);
		pt5y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].y-Noeud[pt2].y) / (Noeud[pt1].z-Noeud[pt2].z);
		
		TraceSegment(color, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		TraceSegment(color, Noeud[pt1].x, Noeud[pt1].y, pt5x, pt5y);
		TraceSegment(BLACK, pt5x, pt5y, pt4x, pt4y);
		TraceSegment(color, pt4x, pt4y, Noeud[pt3].x, Noeud[pt3].y);
		}
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt3 pt1*/
		/*pt5 est situe sur le cote pt3 pt2*/
		pt4x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].x-Noeud[pt3].x) / (Noeud[pt1].z-Noeud[pt3].z);
		pt4y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].y-Noeud[pt3].y) / (Noeud[pt1].z-Noeud[pt3].z);
		pt5x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].x-Noeud[pt3].x) / (Noeud[pt2].z-Noeud[pt3].z);
		pt5y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].y-Noeud[pt3].y) / (Noeud[pt2].z-Noeud[pt3].z);
		
		TraceSegment(color, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y);
		TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
		TraceSegment(color, pt5x, pt5y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(color, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt1].x, Noeud[pt1].y);
		}
	
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt1 pt2*/
		/*pt5 est situe sur le cote pt1 pt3*/
		pt4x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].x-Noeud[pt1].x) / (Noeud[pt2].z-Noeud[pt1].z);
		pt4y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].y-Noeud[pt1].y) / (Noeud[pt2].z-Noeud[pt1].z);
		pt5x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].x-Noeud[pt1].x) / (Noeud[pt3].z-Noeud[pt1].z);
		pt5y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].y-Noeud[pt1].y) / (Noeud[pt3].z-Noeud[pt1].z);

		TraceSegment(color, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y);
		TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
		TraceSegment(color, pt5x, pt5y, Noeud[pt1].x, Noeud[pt1].y);
		}
	
	if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt2 pt3*/
		/*pt5 est situe sur le cote pt2 pt1*/
		pt4x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].x-Noeud[pt2].x) / (Noeud[pt3].z-Noeud[pt2].z);
		pt4y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].y-Noeud[pt2].y) / (Noeud[pt3].z-Noeud[pt2].z);
		pt5x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].x-Noeud[pt2].x) / (Noeud[pt1].z-Noeud[pt2].z);
		pt5y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].y-Noeud[pt2].y) / (Noeud[pt1].z-Noeud[pt2].z);

		TraceSegment(color, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y);
		TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
		TraceSegment(color, pt5x, pt5y, Noeud[pt2].x, Noeud[pt2].y);
		}
	
	if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt3 pt1*/
		/*pt5 est situe sur le cote pt3 pt2*/
		pt4x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].x-Noeud[pt3].x) / (Noeud[pt1].z-Noeud[pt3].z);
		pt4y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].y-Noeud[pt3].y) / (Noeud[pt1].z-Noeud[pt3].z);
		pt5x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].x-Noeud[pt3].x) / (Noeud[pt2].z-Noeud[pt3].z);
		pt5y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].y-Noeud[pt3].y) / (Noeud[pt2].z-Noeud[pt3].z);
		
		TraceSegment(color, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y);
		TraceSegment(BLACK, pt4x, pt4y, pt5x, pt5y);
		TraceSegment(color, pt5x, pt5y, Noeud[pt3].x, Noeud[pt3].y);
		}
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		rr = (int) (nb_col*pa/NOMBRE_SURFACES);
		color = colo[rr];
		color = panneau[Surface[pa].type].flag_dessin;
		/*bb = 0;
		rr = (int) (nb_col*pa/NOMBRE_SURFACES);
		color = colo[rr];
		gg = 0;
		rr = 0;
		rr = (int) (255*pa/NOMBRE_SURFACES);
		gg = (int) (pa/NOMBRE_SURFACES*255);
		bb = (int) (pa/NOMBRE_SURFACES*255);
		rr = (int) (5000*((double) rand() / RAND_MAX));
		gris_externe = ColorRGB(rr,gg,bb);
		printf("pa %d nbsur %d rr %d gg %d bb %d gr %d\n",pa,NOMBRE_SURFACES,rr,gg,bb,gris_externe);*/
		/*EffaceTriangle(rr, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);*/
		/*TraceSegment(color, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(color, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(color, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);*/
		draw_segment_color(panneau[Surface[pa].type].flag_dessin, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);	/*generatrice*/
		draw_segment_color(panneau[Surface[pa].type].flag_dessin, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);	/*generatrice*/
		draw_segment_color(panneau[Surface[pa].type].flag_dessin, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);	/*generatrice*/
		draw_segment_color(color, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);	/*generatrice*/
		draw_segment_color(color, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);	/*generatrice*/
		draw_segment_color(color, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);	/*generatrice*/
		}
	}

void draw_contour_triangle_hexa(int pa)
	{
	int ba,no,deb,fin,pt1,pt2,pt3,nb_total;
	double pt4x,pt4y,pt5x,pt5y;


	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];
	
	if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt1 pt2*/
		/*pt5 est situe sur le cote pt1 pt3*/
		pt4x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].x-Noeud[pt1].x) / (Noeud[pt2].z-Noeud[pt1].z);
		pt4y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].y-Noeud[pt1].y) / (Noeud[pt2].z-Noeud[pt1].z);
		pt5x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].x-Noeud[pt1].x) / (Noeud[pt3].z-Noeud[pt1].z);
		pt5y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].y-Noeud[pt1].y) / (Noeud[pt3].z-Noeud[pt1].z);
	
		TraceSegment(BLUE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(BLUE, Noeud[pt3].x, Noeud[pt3].y, pt5x,pt5y);
		TraceSegment(BLUE, pt5x, pt5y, pt4x, pt4y);
		TraceSegment(BLUE, pt4x, pt4y, Noeud[pt2].x, Noeud[pt2].y);
		}
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt2 pt3*/
		/*pt5 est situe sur le cote pt2 pt1*/
		pt4x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].x-Noeud[pt2].x) / (Noeud[pt3].z-Noeud[pt2].z);
		pt4y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].y-Noeud[pt2].y) / (Noeud[pt3].z-Noeud[pt2].z);
		pt5x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].x-Noeud[pt2].x) / (Noeud[pt1].z-Noeud[pt2].z);
		pt5y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].y-Noeud[pt2].y) / (Noeud[pt1].z-Noeud[pt2].z);
		
		TraceSegment(BLUE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		TraceSegment(BLUE, Noeud[pt1].x, Noeud[pt1].y, pt5x, pt5y);
		TraceSegment(BLUE, pt5x, pt5y, pt4x, pt4y);
		TraceSegment(BLUE, pt4x, pt4y, Noeud[pt3].x, Noeud[pt3].y);
		}
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt3 pt1*/
		/*pt5 est situe sur le cote pt3 pt2*/
		pt4x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].x-Noeud[pt3].x) / (Noeud[pt1].z-Noeud[pt3].z);
		pt4y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].y-Noeud[pt3].y) / (Noeud[pt1].z-Noeud[pt3].z);
		pt5x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].x-Noeud[pt3].x) / (Noeud[pt2].z-Noeud[pt3].z);
		pt5y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].y-Noeud[pt3].y) / (Noeud[pt2].z-Noeud[pt3].z);
		
		TraceSegment(BLUE, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y);
		TraceSegment(BLUE, pt4x, pt4y, pt5x, pt5y);
		TraceSegment(BLUE, pt5x, pt5y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(BLUE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt1].x, Noeud[pt1].y);
		}
	
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt1 pt2*/
		/*pt5 est situe sur le cote pt1 pt3*/
		pt4x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].x-Noeud[pt1].x) / (Noeud[pt2].z-Noeud[pt1].z);
		pt4y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt2].y-Noeud[pt1].y) / (Noeud[pt2].z-Noeud[pt1].z);
		pt5x = Noeud[pt1].x + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].x-Noeud[pt1].x) / (Noeud[pt3].z-Noeud[pt1].z);
		pt5y = Noeud[pt1].y + (profondeur_coupe_float-Noeud[pt1].z) * (Noeud[pt3].y-Noeud[pt1].y) / (Noeud[pt3].z-Noeud[pt1].z);

		TraceSegment(BLUE, Noeud[pt1].x, Noeud[pt1].y, pt4x, pt4y);
		TraceSegment(BLUE, pt4x, pt4y, pt5x, pt5y);
		TraceSegment(BLUE, pt5x, pt5y, Noeud[pt1].x, Noeud[pt1].y);
		}
	
	if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z > profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt2 pt3*/
		/*pt5 est situe sur le cote pt2 pt1*/
		pt4x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].x-Noeud[pt2].x) / (Noeud[pt3].z-Noeud[pt2].z);
		pt4y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt3].y-Noeud[pt2].y) / (Noeud[pt3].z-Noeud[pt2].z);
		pt5x = Noeud[pt2].x + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].x-Noeud[pt2].x) / (Noeud[pt1].z-Noeud[pt2].z);
		pt5y = Noeud[pt2].y + (profondeur_coupe_float-Noeud[pt2].z) * (Noeud[pt1].y-Noeud[pt2].y) / (Noeud[pt1].z-Noeud[pt2].z);

		TraceSegment(BLUE, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y);
		TraceSegment(BLUE, pt4x, pt4y, pt5x, pt5y);
		TraceSegment(BLUE, pt5x, pt5y, Noeud[pt2].x, Noeud[pt2].y);
		}
	
	if ((Noeud[pt1].z > profondeur_coupe_float) &&(Noeud[pt2].z > profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		/*pt4 est situe sur le cote pt3 pt1*/
		/*pt5 est situe sur le cote pt3 pt2*/
		pt4x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].x-Noeud[pt3].x) / (Noeud[pt1].z-Noeud[pt3].z);
		pt4y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt1].y-Noeud[pt3].y) / (Noeud[pt1].z-Noeud[pt3].z);
		pt5x = Noeud[pt3].x + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].x-Noeud[pt3].x) / (Noeud[pt2].z-Noeud[pt3].z);
		pt5y = Noeud[pt3].y + (profondeur_coupe_float-Noeud[pt3].z) * (Noeud[pt2].y-Noeud[pt3].y) / (Noeud[pt2].z-Noeud[pt3].z);
		
		TraceSegment(BLUE, Noeud[pt3].x, Noeud[pt3].y, pt4x, pt4y);
		TraceSegment(BLUE, pt4x, pt4y, pt5x, pt5y);
		TraceSegment(BLUE, pt5x, pt5y, Noeud[pt3].x, Noeud[pt3].y);
		}
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		TraceSegment(BLUE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(BLUE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(BLUE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		}
	}

void dessiner_orientation_volume()
	{
	int pa,no,pt1,pt2,pt3;
	int orient;
	char chaine[7];
	
	/*printf("dessiner_orientation_volume \n"); */
	changement_variable_catch();

	EcritText(RED, (double) binx, (double) biny, "orientation des elements / courant", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			orient = orientation_triangle(pa);
    			sprintf(chaine,"%d",orient);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa > NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			orient = orientation_triangle(pa);
    			sprintf(chaine,"%d",orient);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		}
	}

void draw_orientation_volume_diamond(int pa)
	{
	int no,pt1,pt2,pt3;
	int orient;
	char chaine[7];
	
	/*printf("dessiner_orientation_volume \n"); */
	changement_variable_catch();

	EcritText(RED, (double) binx, (double) biny, "orientation des elements / courant", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
	
	orient = orientation_triangle(pa);
	sprintf(chaine,"%d",orient);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_orientation_volume_hexa(int pa)
	{
	int no,pt1,pt2,pt3;
	int orient;
	char chaine[7];
	
	/*printf("dessiner_orientation_volume \n"); */
	changement_variable_catch();

	EcritText(RED, (double) binx, (double) biny, "orientation des elements / courant", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];
	
	orient = orientation_triangle(pa);
	sprintf(chaine,"%d",orient);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void dessiner_surface_elementaire()
	{
	int pa,no,pt1,pt2,pt3;
	double dvolume,dsurface;
	char chaine[70];
	
	/*printf("dessiner_surface_elementaire \n"); */
	changement_variable_catch();

	EcritText(RED, (double) binx, (double) biny, "surface elementaire face au courant (m^2)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			surface_volume(pa,  frontx, &dvolume,&dsurface);
    			sprintf(chaine,"%.3g",dsurface);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa > NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			surface_volume(pa,  frontx, &dvolume,&dsurface);
    			sprintf(chaine,"%.3g",dsurface);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		}
	}
	
void draw_surface_elementaire_diamond(int pa)
	{
	int no,pt1,pt2,pt3;
	double dvolume,dsurface;
	char chaine[70];
	
	/*printf("dessiner_surface_elementaire \n"); */
	changement_variable_catch();

	EcritText(RED, (double) binx, (double) biny, "surface elementaire face au courant (m^2)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	surface_volume(pa,  frontx, &dvolume,&dsurface);
	sprintf(chaine,"%.3g",dsurface);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}
	
void draw_surface_elementaire_hexa(int pa)
	{
	int no,pt1,pt2,pt3;
	double dvolume,dsurface;
	char chaine[70];
	
	/*printf("dessiner_surface_elementaire \n"); */
	changement_variable_catch();

	EcritText(RED, (double) binx, (double) biny, "surface elementaire face au courant (m^2)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	surface_volume(pa,  frontx, &dvolume,&dsurface);
	sprintf(chaine,"%.3g",dsurface);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void dessiner_defaut_discretisation()
	{
	int pa,no,pt1,pt2,pt3,couleur,rapport_blue,rapport_red,pa_min;
	double dvolume,dsurface,defaut_max,defaut_min;
	char chaine[70];
	
	/*printf("dessiner_defaut_discretisation \n"); */
	changement_variable_catch();

	defaut_max = -1.0;
	defaut_min =  1.0;
	for (pa=1;pa<=NOMBRE_SURFACES;pa++)
		{ 
		if (Surface[pa].defaut_disc > defaut_max) defaut_max = Surface[pa].defaut_disc;
		if (Surface[pa].defaut_disc < defaut_min)
			{
			defaut_min = Surface[pa].defaut_disc;
			pa_min = pa;
			}
		}

    	sprintf(chaine,"defaut max de discretisation de %5.2lf en panneau %5d",defaut_min,Surface[pa_min].type);
	EcritText(RED, (double) binx, (double) biny, chaine, (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			if (defaut_max != defaut_min)
				{
				rapport_blue = (int) 255.0 * (Surface[pa].defaut_disc-defaut_min) / (defaut_max-defaut_min);
				}
			else
				{
				rapport_blue = 124;
				}
			rapport_red = 255 - rapport_blue;
			couleur = ColorRGB(rapport_red,0,rapport_blue);
			/*
			printf("couleur de %4d = %8d, r %4d b %4d \n",pa,couleur,rapport_red,rapport_blue);
			*/
			
			EffaceTriangle(couleur, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
    			sprintf(chaine,"%5.2lf",Surface[pa].defaut_disc);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
    			/*
			*/
			}
		if ((pa > NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
    			/*
    			sprintf(chaine,"%.3g",dsurface);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			*/
			}
		}
	}

void draw_defaut_discretisation_diamond(int pa)
	{
	int no,pt1,pt2,pt3,couleur,rapport_blue,rapport_red,pa_min;
	double dvolume,dsurface,defaut_max,defaut_min;
	char chaine[70];
	
	/*printf("dessiner_defaut_discretisation \n"); */
	changement_variable_catch();

    	sprintf(chaine,"defaut de discretisation");
	EcritText(RED, (double) binx, (double) biny, chaine, (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%5.2lf",Surface[pa].defaut_disc);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void dessiner_profondeur_barycentre()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "barycentre numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",no);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",no);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%d",no);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sprintf(chaine,"%d",no);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_profondeur_barycentre_diamond(int pa, int no)
	{
	int ba,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "barycentre numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%d",no);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_profondeur_barycentre_hexa(int pa, int no)
	{
	int ba,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "barycentre numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];
	
	sprintf(chaine,"%d",no);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_profondeur_barycentre_element(int pa, int no)
	{
	int ba,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "barycentre numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%d",no);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_profondeur_barycentre_coulisse(int pa, int no)
	{
	int ba,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "barycentre numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%d",no);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void draw_profondeur_barycentre_noeud(int pa, int no)
	{
	int ba,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "barycentre numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	sprintf(chaine,"%d",no);
	EcritText(GREEN, Noeud[pa].x, Noeud[pa].y, chaine, 0.0);
	}

void dessiner_numero_element()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) && (panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			if (Noeud[pt1].z > profondeur_coupe_float) break;
			if (Noeud[pt2].z > profondeur_coupe_float) break;
			if (Noeud[pt3].z > profondeur_coupe_float) break;
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%d",pa);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa > NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%d",pa);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa > NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <= NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%d",pa);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa > NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				Color(BLACK);
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				sprintf(chaine,"%d",pa);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_numero_element_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%d",pa);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_numero_element_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%d",pa);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_numero_element_barre(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%d",pa);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_numero_element_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element numero", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		Color(BLACK);
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];

		sprintf(chaine,"%d",pa);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_type_element()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element type", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			if (Noeud[pt1].z > profondeur_coupe_float) break;
			if (Noeud[pt2].z > profondeur_coupe_float) break;
			if (Noeud[pt3].z > profondeur_coupe_float) break;
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%d",Surface[pa].type);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa > NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);

			sprintf(chaine,"%d",Surf_Hexa[pa].type);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			
			if (Noeud[deb].z > profondeur_coupe_float) break;
			if (Noeud[fin].z > profondeur_coupe_float) break;
			
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
    			
			sprintf(chaine,"%d",Element[pa].type);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sprintf(chaine,"%d",pa);
				EcritText(BLACK, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_type_element_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element type", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%d",Surface[pa].type);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}
	
void draw_type_element_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element type", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%d",Surf_Hexa[pa].type);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}
	
void draw_type_element_barre(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element type", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%d",Element[pa].type);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}
	
void draw_type_element_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	
	EcritText(RED, (double) binx, (double) biny, "element type", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/


	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%d",pa);
		EcritText(BLACK, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}
		
void dessiner_raideur_traction()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "traction stiffness (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].raideur_traction);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_traction_l);
			/***********************************************************************************************************
			MANQUE m et n
			***********************************************************************************************************/
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Element[pa].raideur_traction);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				
				sprintf(chaine,"%.3g",Coulisse[pa].raideur_traction);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_raideur_traction_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "traction stiffness (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].raideur_traction);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_raideur_traction_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_traction_l);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.00);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_traction_m);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.02);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_traction_n);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.04);
	}

void draw_raideur_traction_barre(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "traction stiffness (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Element[pa].raideur_traction);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_raideur_traction_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "traction stiffness (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
		
		sprintf(chaine,"%.3g",Coulisse[pa].raideur_traction);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_raideur_compression()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "compression stiffness (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].raideur_compression);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_compression_l);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.00);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_compression_m);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_compression_n);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.06);
	/***********************************************************************************************************
	VERIFIER m et n
	***********************************************************************************************************/
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Element[pa].raideur_compression);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
						}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sprintf(chaine,"%.3g",Coulisse[pa].raideur_compression);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_raideur_compression_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "compression stiffness (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].raideur_compression);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_raideur_compression_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_compression_l);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.00);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_compression_m);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.02);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].raideur_compression_n);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.04);
	}

void draw_raideur_compression_barre(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "compression stiffness (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Element[pa].raideur_compression);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_raideur_compression_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "compression stiffness (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
		
		sprintf(chaine,"%.3g",Coulisse[pa].raideur_compression);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_raideur_ouverture()
	{
	int pa,no,pt1,pt2,pt3;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "mesh opening stiffness (N.m/rad)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].raideur_ouverture);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		}
	}

void draw_raideur_ouverture_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "mesh opening stiffness (N.m/rad)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].raideur_ouverture);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void dessiner_tension()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "tension (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa > 0) && ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0)))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].tension1);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
			
			sprintf(chaine,"%.3g",Surface[pa].tension2);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);

			sprintf(chaine,"%.3g",Surf_Hexa[pa].tension1);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].tension2);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].tension3);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.06);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%7.1e",Element[pa].wt);
			if (Element[pa].wt > 0)EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			else EcritText(BLUE, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				
				sprintf(chaine,"%.3g",Coulisse[pa].wt);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_tension_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "tension (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].tension1);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
	
	sprintf(chaine,"%.3g",Surface[pa].tension2);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_tension_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].tension1);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].tension2);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].tension3);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.06);
	}

void draw_tension_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "tension (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	if (TypeElement[Element[pa].type].constant_tension == 0)
		{
		sprintf(chaine,"%8.2e",Element[pa].wt);				//usual bar
		}
	else
		{
		if (Element[pa].wt < TypeElement[Element[pa].type].tension_constant)
			{
			sprintf(chaine,"%8.2e",Element[pa].wt);				//usual bar
			}
		else
			{
			sprintf(chaine,"%8.2e",TypeElement[Element[pa].type].tension_constant);		//bar at constant tension
			}
		}
	if (Element[pa].wt > 0)EcritText(RED , (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	else                   EcritText(BLUE, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_tension_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "tension (N)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
		
		sprintf(chaine,"%.3g",Coulisse[pa].wt);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_nrj()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "potential energy per bar and twine (J)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa > 0) && ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0)))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%5.2lg",Surface[pa].nrj1);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
			
			sprintf(chaine,"%5.2lg",Surface[pa].nrj2);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);

			sprintf(chaine,"%.3g",Surf_Hexa[pa].nrj1);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].nrj2);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].nrj3);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.06);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Element[pa].nrj);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				
				sprintf(chaine,"%.3g",Coulisse[pa].nrj);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_nrj_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin,col,co;
	char chaine[70];
	
	EcritText(BLUE, (double) binx, (double) biny, "potential energy per bar and twine (J)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
	
	co = (int) ((Surface[pa].nrj-min_energy)/(max_energy-min_energy) * nb_col);
	col  = colo[co];
	EffaceTriangle(col, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
	/*sprintf(chaine,"%5.2lg",Surface[pa].nrj1+Surface[pa].nrj2);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);*/
	}

void draw_nrj_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "potential energy per bar and twine (J)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].nrj1+Surf_Hexa[pa].nrj2+Surf_Hexa[pa].nrj3);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_nrj_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "potential energy per bar and twine (J)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	/*sprintf(chaine,"%.3g",Element[pa].nrj);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);*/
	}

void draw_nrj_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "potential energy per bar and twine (J)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
		
		sprintf(chaine,"%.3g",Coulisse[pa].nrj);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_longueur_repos()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "longueur au repos (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].lgrepos);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);

			sprintf(chaine,"%.3g",Surf_Hexa[pa].lo_repos);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].mo_repos);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].no_repos);EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.06);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Element[pa].lgrepos);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sprintf(chaine,"%.3g",Coulisse[pa].lgrepos);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_longueur_repos_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "unstretched length (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].lgrepos);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_longueur_repos_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "unstretched length (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].lo_repos);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.00);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].mo_repos);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.02);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].no_repos);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.04);
	}

void draw_longueur_repos_barre(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "unstretched length (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Element[pa].lgrepos);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_longueur_repos_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "unstretched length (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
		
		sprintf(chaine,"%.3g",Coulisse[pa].lgrepos);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}


void dessiner_longueur_tendue()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	float lll,mmm,nnn;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "stretched length (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			nnn = sqrt(Surface[pa].nx*Surface[pa].nx + Surface[pa].ny*Surface[pa].ny + Surface[pa].nz*Surface[pa].nz);
			sprintf(chaine,"lgt1=%.3g",nnn);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
			
			mmm = sqrt(Surface[pa].mx*Surface[pa].mx + Surface[pa].my*Surface[pa].my + Surface[pa].mz*Surface[pa].mz);
			sprintf(chaine,"lgt2=%.3g",mmm);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			lll = sqrt(Surf_Hexa[pa].lx*Surf_Hexa[pa].lx + Surf_Hexa[pa].ly*Surf_Hexa[pa].ly + Surf_Hexa[pa].lz*Surf_Hexa[pa].lz);
			sprintf(chaine,"%.3g",lll);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			mmm = sqrt(Surf_Hexa[pa].mx*Surf_Hexa[pa].mx + Surf_Hexa[pa].my*Surf_Hexa[pa].my + Surf_Hexa[pa].mz*Surf_Hexa[pa].mz);
			sprintf(chaine,"%.3g",mmm);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
			nnn = sqrt(Surf_Hexa[pa].nx*Surf_Hexa[pa].nx + Surf_Hexa[pa].ny*Surf_Hexa[pa].ny + Surf_Hexa[pa].nz*Surf_Hexa[pa].nz);
			sprintf(chaine,"%.3g",nnn);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.06);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Element[pa].lgtendue);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sprintf(chaine,"%.3g",Coulisse[pa].lgtendue);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_longueur_tendue_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float lll,mmm,nnn;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "stretched length (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	nnn = sqrt(Surface[pa].nx*Surface[pa].nx + Surface[pa].ny*Surface[pa].ny + Surface[pa].nz*Surface[pa].nz);
	sprintf(chaine,"%.3g",nnn);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
	
	mmm = sqrt(Surface[pa].mx*Surface[pa].mx + Surface[pa].my*Surface[pa].my + Surface[pa].mz*Surface[pa].mz);
	sprintf(chaine,"%.3g",mmm);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_longueur_tendue_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float lll,mmm,nnn;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "stretched length (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	lll = sqrt(Surf_Hexa[pa].lx*Surf_Hexa[pa].lx + Surf_Hexa[pa].ly*Surf_Hexa[pa].ly + Surf_Hexa[pa].lz*Surf_Hexa[pa].lz);
	sprintf(chaine,"%.3g",lll);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	mmm = sqrt(Surf_Hexa[pa].mx*Surf_Hexa[pa].mx + Surf_Hexa[pa].my*Surf_Hexa[pa].my + Surf_Hexa[pa].mz*Surf_Hexa[pa].mz);
	sprintf(chaine,"%.3g",mmm);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.03);
	nnn = sqrt(Surf_Hexa[pa].nx*Surf_Hexa[pa].nx + Surf_Hexa[pa].ny*Surf_Hexa[pa].ny + Surf_Hexa[pa].nz*Surf_Hexa[pa].nz);
	sprintf(chaine,"%.3g",nnn);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.06);
	}

void draw_longueur_tendue_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float lll,mmm,nnn;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "stretched length (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Element[pa].lgtendue);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_longueur_tendue_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float lll,mmm,nnn;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "stretched length (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%.3g",Coulisse[pa].lgtendue);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_masse_volumique()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "masse volumique (kg/m^3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].rhosurface);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Surf_Hexa[pa].rhosurface);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Element[pa].rhoelement);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sprintf(chaine,"%.3g",Coulisse[pa].rhocoulisse);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_masse_volumique_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "density (Kg/m3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].rhosurface);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_masse_volumique_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "density (Kg/m3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].rhosurface);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.00);
	}

void draw_masse_volumique_barre(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "density (Kg/m3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Element[pa].rhoelement);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_masse_volumique_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "density (Kg/m3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
		
		sprintf(chaine,"%.3g",Coulisse[pa].rhocoulisse);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_diametre()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "diameter (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].diametrehydro);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Surf_Hexa[pa].diametrehydro);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Element[pa].diametrehydro);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sprintf(chaine,"%.3g",Coulisse[pa].diametrehydro);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_diametre_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "diameter (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].diametrehydro);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_diametre_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "diameter (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].diametrehydro);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.00);
	}

void draw_diametre_barre(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "diameter (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Element[pa].diametrehydro);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_diametre_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "diameter (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
		
		sprintf(chaine,"%.3g",Coulisse[pa].diametrehydro);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_largeur_noeud()
	{
	int pa,no,pt1,pt2,pt3;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "knot size (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);

			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].largeurnoeud);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Surf_Hexa[pa].largeurnoeud);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		}
	}

void draw_largeur_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "knot size (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].largeurnoeud);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void dessiner_coefficient_cd()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "cd normal coef.", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].cdnormal);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Surf_Hexa[pa].cdnormal);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Element[pa].cdnormal);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sprintf(chaine,"%.3g",Coulisse[pa].cdnormal);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_coefficient_cd_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "cd coefficient", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].cdnormal);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_coefficient_cd_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "cd coefficient", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].cdnormal);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.00);
	}

void draw_coefficient_cd_barre(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "cd coefficient", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Element[pa].cdnormal);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_coefficient_cd_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "cd coefficient", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
		
		sprintf(chaine,"%.3g",Coulisse[pa].cdnormal);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_coefficient_f()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "f tangential coef.", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sprintf(chaine,"%.3g",Surface[pa].ftangent);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Surf_Hexa[pa].ftangent);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Element[pa].ftangent);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sprintf(chaine,"%.3g",Coulisse[pa].ftangent);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_coefficient_f_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "f coefficient", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Surface[pa].ftangent);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_coefficient_f_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "f coefficient", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].ftangent);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.00);
	}

void draw_coefficient_f_barre(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "f coefficient", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Element[pa].ftangent);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_coefficient_f_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "f coefficient", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
		
		sprintf(chaine,"%.3g",Coulisse[pa].ftangent);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_section_element()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "section (m^2)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sca = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro / 4.0;
			sprintf(chaine,"%.3g",sca);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sca = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro / 4.0;
			sprintf(chaine,"%.3g",sca);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sca = PI * Element[pa].diametrehydro * Element[pa].diametrehydro / 4.0;
			sprintf(chaine,"%.3g",sca);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				Color(BLACK);
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sca = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro / 4.0;
				sprintf(chaine,"%.3g",sca);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_section_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "section (m^2)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sca = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro / 4.0;
	sprintf(chaine,"%.3g",sca);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_section_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "section (m^2)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sca = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro / 4.0;
	sprintf(chaine,"%.3g",sca);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_section_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "section (m^2)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sca = PI * Element[pa].diametrehydro * Element[pa].diametrehydro / 4.0;
	sprintf(chaine,"%.3g",sca);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_section_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "section (m^2)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		Color(BLACK);
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sca = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro / 4.0;
		sprintf(chaine,"%.3g",sca);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_volume_element()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "element volume (m^3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sca = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro / 4.0 * Surface[pa].lgrepos;
			sprintf(chaine,"%.3g",sca);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sca = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro / 4.0 * (Surf_Hexa[pa].lo_repos+Surf_Hexa[pa].mo_repos+Surf_Hexa[pa].no_repos);
			sprintf(chaine,"%.3g",sca);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sca = PI * Element[pa].diametrehydro * Element[pa].diametrehydro / 4.0 * Element[pa].lgrepos;
			sprintf(chaine,"%.3g",sca);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sca = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro / 4.0 * Coulisse[pa].lgrepos;
				sprintf(chaine,"%.3g",sca);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_volume_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "element volume (m^3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sca = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro / 4.0 * Surface[pa].lgrepos;
	sprintf(chaine,"%.3g",sca);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_volume_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "element volume (m^3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sca = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro / 4.0 * (Surf_Hexa[pa].lo_repos+Surf_Hexa[pa].mo_repos+Surf_Hexa[pa].no_repos);
	sprintf(chaine,"%.3g",sca);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_volume_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "element volume (m^3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sca = PI * Element[pa].diametrehydro * Element[pa].diametrehydro / 4.0 * Element[pa].lgrepos;
	sprintf(chaine,"%.3g",sca);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_volume_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "element volume (m^3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sca = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro / 4.0 * Coulisse[pa].lgrepos;
		sprintf(chaine,"%.3g",sca);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_masse_element()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "twine/bar mass (kg)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sca = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro / 4.0 * Surface[pa].lgrepos * Surface[pa].rhosurface;
			sprintf(chaine,"%.3g",sca);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sca = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro / 4.0 * (Surf_Hexa[pa].lo_repos+Surf_Hexa[pa].mo_repos+Surf_Hexa[pa].no_repos) * Surf_Hexa[pa].rhosurface;
			sprintf(chaine,"%.3g",sca);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sca = PI * Element[pa].diametrehydro * Element[pa].diametrehydro / 4.0 * Element[pa].lgrepos * Element[pa].rhoelement;
			sprintf(chaine,"%.3g",sca);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sca = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro / 4.0 * Coulisse[pa].lgrepos * Coulisse[pa].rhocoulisse;
				sprintf(chaine,"%.3g",sca);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_masse_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "twine/bar mass (kg)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sca = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro / 4.0 * Surface[pa].lgrepos * Surface[pa].rhosurface;
	sprintf(chaine,"%.3g",sca);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_masse_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "twine/bar mass (kg)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sca = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro / 4.0 * (Surf_Hexa[pa].lo_repos+Surf_Hexa[pa].mo_repos+Surf_Hexa[pa].no_repos) * Surf_Hexa[pa].rhosurface;
	sprintf(chaine,"%.3g",sca);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_masse_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "twine/bar mass (kg)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sca = PI * Element[pa].diametrehydro * Element[pa].diametrehydro / 4.0 * Element[pa].lgrepos * Element[pa].rhoelement;
	sprintf(chaine,"%.3g",sca);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_masse_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "twine/bar mass (kg)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

			
	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sca = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro / 4.0 * Coulisse[pa].lgrepos * Coulisse[pa].rhocoulisse;
		sprintf(chaine,"%.3g",sca);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_masse_lineique()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	Color(RED);
	EcritText(RED, (double) binx, (double) biny, "dry lineic mass (kg/m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			sca = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro / 4.0 * Surface[pa].rhosurface;
			sprintf(chaine,"%.3g",sca);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sca = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro / 4.0 * Surf_Hexa[pa].rhosurface;
			sprintf(chaine,"%.3g",sca);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sca = PI * Element[pa].diametrehydro * Element[pa].diametrehydro / 4.0 * Element[pa].rhoelement;
			sprintf(chaine,"%.3g",sca);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				sca = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro / 4.0 * Coulisse[pa].rhocoulisse;
				sprintf(chaine,"%.3g",sca);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}

void draw_masse_lineique_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	Color(RED);
	EcritText(RED, (double) binx, (double) biny, "dry lineic mass (kg/m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sca = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro / 4.0 * Surface[pa].rhosurface;
	sprintf(chaine,"%.3g",sca);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_masse_lineique_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	Color(RED);
	EcritText(RED, (double) binx, (double) biny, "dry lineic mass (kg/m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sca = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro / 4.0 * Surf_Hexa[pa].rhosurface;
	sprintf(chaine,"%.3g",sca);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_masse_lineique_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	Color(RED);
	EcritText(RED, (double) binx, (double) biny, "dry lineic mass (kg/m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sca = PI * Element[pa].diametrehydro * Element[pa].diametrehydro / 4.0 * Element[pa].rhoelement;
	sprintf(chaine,"%.3g",sca);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}

void draw_masse_lineique_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca;
	char chaine[70];
	
	Color(RED);
	EcritText(RED, (double) binx, (double) biny, "dry lineic mass (kg/m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sca = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro / 4.0 * Coulisse[pa].rhocoulisse;
		sprintf(chaine,"%.3g",sca);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}

void dessiner_flottabilite()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	float sca,volume;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "flottabilite (kg)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			volume = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro  * Surface[pa].lgrepos / 4.0;
			sca = volume * (RHO);
			sprintf(chaine,"%.3g",sca);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			volume = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro  * (Surf_Hexa[pa].lo_repos+Surf_Hexa[pa].mo_repos+Surf_Hexa[pa].no_repos) / 4.0;
			sca = volume * (RHO);
			sprintf(chaine,"%.3g",sca);
			EcritText(BLACK, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			volume = PI * Element[pa].diametrehydro * Element[pa].diametrehydro  * Element[pa].lgrepos / 4.0;
			sca = volume * (RHO);
			sprintf(chaine,"%.3g",sca);
			EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
				volume = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro  * Coulisse[pa].lgrepos / 4.0;
				sca = volume * (RHO);
				sprintf(chaine,"%.3g",sca);
				EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
				}
			}
		}
	}


void draw_flottabilite_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca,volume;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "flottabilite (kg) ", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	volume = PI * Surface[pa].diametrehydro * Surface[pa].diametrehydro  * Surface[pa].lgrepos / 4.0;
	sca = volume * (RHO);
	sprintf(chaine,"%.3g",sca);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}


void draw_flottabilite_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca,volume;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "flottabilite (kg)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];
	
	volume = PI * Surf_Hexa[pa].diametrehydro * Surf_Hexa[pa].diametrehydro  * (Surf_Hexa[pa].lo_repos+Surf_Hexa[pa].mo_repos+Surf_Hexa[pa].no_repos) / 4.0;
	sca = volume * (RHO);
	sprintf(chaine,"%.3g",sca);
	EcritText(BLACK, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}


void draw_flottabilite_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca,volume;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "flottabilite (kg)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	volume = PI * Element[pa].diametrehydro * Element[pa].diametrehydro  * Element[pa].lgrepos / 4.0;
	sca = volume * (RHO);
	sprintf(chaine,"%.3g",sca);
	EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
	}


void draw_flottabilite_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float sca,volume;
	char chaine[70];
	
	EcritText(RED, (double) binx, (double) biny, "flottabilite (kg)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		volume = PI * Coulisse[pa].diametrehydro * Coulisse[pa].diametrehydro  * Coulisse[pa].lgrepos / 4.0;
		sca = volume * (RHO);
		sprintf(chaine,"%.3g",sca);
		EcritText(RED, (Noeud[deb].x+Noeud[fin].x)/2.0, (Noeud[deb].y+Noeud[fin].y)/2.0, chaine, 0.0);
		}
	}


void dessiner_volume_elementaire()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	double dvolume,dsurface;
	char chaine[70];
	
	/*printf("dessiner_volume_elementaire \n"); */
	changement_variable_catch();

	EcritText(RED, (double) binx, (double) biny, "volume elementaire / courant (m^3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			surface_volume(pa,  frontx, &dvolume,&dsurface);
    			sprintf(chaine,"%.3g",dvolume);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		
			surface_volume(pa,  frontx, &dvolume,&dsurface);
    			sprintf(chaine,"%.3g",dvolume);
			EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(RED, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			}
		}
	}

void draw_volume_elementaire_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	double dvolume,dsurface;
	char chaine[70];
	
	/*printf("dessiner_volume_elementaire \n"); */
	changement_variable_catch();

	EcritText(RED, (double) binx, (double) biny, "volume elementaire / courant (m^3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	surface_volume(pa,  frontx, &dvolume,&dsurface);
	sprintf(chaine,"%.3g",dvolume);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void draw_volume_elementaire_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	double dvolume,dsurface;
	char chaine[70];
	
	/*printf("dessiner_volume_elementaire \n"); */
	changement_variable_catch();

	EcritText(RED, (double) binx, (double) biny, "volume elementaire / courant (m^3)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	surface_volume(pa,  frontx, &dvolume,&dsurface);
	sprintf(chaine,"%.3g",dvolume);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void dessiner_orientation_xy_element()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	float orientation;
	
	EcritText(RED, (double) binx, (double) biny, "orientation xy", 0.02); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du triangle*/
			orientation = (float) Surface[pa].orientation * ((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt1].y) - (Noeud[pt3].x-Noeud[pt1].x)*(Noeud[pt2].y-Noeud[pt1].y));
		
			if (orientation < 0.0)
				{
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
				}
			else
				{
				EffaceTriangle(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
				}
			}
  		if ((pa > NOMBRE_SURFACES)&& (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
  			{
  			pa = pa - NOMBRE_SURFACES;
  			pt1 = Surf_Hexa[pa].extremite[1];
  			pt2 = Surf_Hexa[pa].extremite[2];
  			pt3 = Surf_Hexa[pa].extremite[3];
  			
  			/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du triangle*/
			orientation = (float) Surface[pa].orientation * ((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt1].y) - (Noeud[pt3].x-Noeud[pt1].x)*(Noeud[pt2].y-Noeud[pt1].y));
  		
  			if (orientation < 0.0)
  				{
  				Color(WHITE);
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
  				}
  			else
  				{
  				Color(GREEN);
				EffaceTriangle(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
  				}
  			}
  		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA ) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(RED, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			}
  		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)				deb = Coulisse[pa].extremite[1];
				if (ba != 1)				deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			}
		}
	}
	
	
void draw_orientation_xy_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float orientation;
	
	EcritText(RED, (double) binx, (double) biny, "orientation xy", 0.02); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du triangle*/
	orientation = (float) Surface[pa].orientation * ((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt1].y) - (Noeud[pt3].x-Noeud[pt1].x)*(Noeud[pt2].y-Noeud[pt1].y));

	if (orientation < 0.0)
		{
		EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		EffaceTriangle(gris_externe, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		/*TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);*/
		}
	else
		{
		EffaceTriangle(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		EffaceTriangle(gris_interne, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		/*TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);*/
		}
	}

void draw_orientation_xy_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	float orientation;
	
	EcritText(RED, (double) binx, (double) biny, "orientation xy", 0.02); 	/*decalage de 1 puisque c est un element*/


	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];
	
	/*la composante selon w du produit vectoriel entre 12 et 13 donne l orientation du triangle*/
	orientation = (float) Surface[pa].orientation * ((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt1].y) - (Noeud[pt3].x-Noeud[pt1].x)*(Noeud[pt2].y-Noeud[pt1].y));

	if (orientation < 0.0)
		{
		Color(WHITE);
		EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		/*TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);*/
		}
	else
		{
		Color(GREEN);
		EffaceTriangle(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		/*TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);*/
		}
	}
	

