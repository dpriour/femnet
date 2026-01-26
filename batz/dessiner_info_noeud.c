#include "batz.h"

void dessiner_type_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node type", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0) && (panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",Noeud[pt1].type);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt2].type);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt3].type);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",Noeud[pt1].type);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt2].type);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt3].type);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%d",Noeud[deb].type);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[fin].type);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%d",Noeud[deb].type);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
				sprintf(chaine,"%d",Noeud[fin].type);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
				}
			}
		}
	}

void draw_type_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node type", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%d",Noeud[pt1].type);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt2].type);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt3].type);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	}

void draw_type_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node type", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%d",Noeud[pt1].type);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt2].type);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt3].type);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	}

void draw_type_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node type", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%d",Noeud[deb].type);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[fin].type);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
	}

void draw_type_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node type", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%d",Noeud[deb].type);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
		sprintf(chaine,"%d",Noeud[fin].type);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
		}
	}

void dessiner_numero_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node numero", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",pt1);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine, 0.0);
			sprintf(chaine,"%d",pt2);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine, 0.0);
			sprintf(chaine,"%d",pt3);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);

			sprintf(chaine,"%d",pt1);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine, 0.0);
			sprintf(chaine,"%d",pt2);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine, 0.0);
			sprintf(chaine,"%d",pt3);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%d",deb);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, 0.0);
			sprintf(chaine,"%d",fin);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, 0.0);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%d",deb);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, 0.0);
				sprintf(chaine,"%d",fin);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, 0.0);
				}
			}
		}
	}

void draw_numero_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node numero", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%d",pt1);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine, 0.0);
	sprintf(chaine,"%d",pt2);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine, 0.0);
	sprintf(chaine,"%d",pt3);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine, 0.0);
	}

void draw_numero_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node numero", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%d",pt1);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine, 0.0);
	sprintf(chaine,"%d",pt2);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine, 0.0);
	sprintf(chaine,"%d",pt3);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine, 0.0);
	}

void draw_numero_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node numero", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%d",deb);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, 0.0);
	sprintf(chaine,"%d",fin);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, 0.0);
	}

void draw_numero_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node numero", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%d",deb);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, 0.0);
		sprintf(chaine,"%d",fin);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, 0.0);
		}
	}

void dessiner_masse_noeud()

	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
		extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node mass (kg)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Noeud[pt1].mx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].my);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].mz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].mx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].my);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].mz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].mx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].my);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].mz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);

			sprintf(chaine,"%.3g",Noeud[pt1].mx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].my);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].mz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].mx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].my);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].mz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].mx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].my);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].mz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Noeud[deb].mx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[deb].my);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[deb].mz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[fin].mx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[fin].my);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[fin].mz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%.3g",Noeud[deb].mx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
				sprintf(chaine,"%.3g",Noeud[deb].my);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
				sprintf(chaine,"%.3g",Noeud[deb].mz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
			
				sprintf(chaine,"%.3g",Noeud[fin].mx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
				sprintf(chaine,"%.3g",Noeud[fin].my);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
				sprintf(chaine,"%.3g",Noeud[fin].mz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
				}
			}
		}
	}

void draw_masse_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node mass (kg)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].mx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].my);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].mz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt2].mx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].my);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].mz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt3].mx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].my);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].mz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_masse_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node mass (kg)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].mx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].my);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].mz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt2].mx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].my);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].mz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt3].mx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].my);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].mz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_masse_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node mass (kg)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Noeud[deb].mx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[deb].my);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[deb].mz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[fin].mx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[fin].my);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[fin].mz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
	}

void draw_masse_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node mass (kg)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%.3g",Noeud[deb].mx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
		sprintf(chaine,"%.3g",Noeud[deb].my);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
		sprintf(chaine,"%.3g",Noeud[deb].mz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
	
		sprintf(chaine,"%.3g",Noeud[fin].mx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
		sprintf(chaine,"%.3g",Noeud[fin].my);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
		sprintf(chaine,"%.3g",Noeud[fin].mz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
		}
	}

void dessiner_longueur_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
		extern void EcritText(int icolor, double dx, double dy, char *chaine, double  decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node length (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Noeud[pt1].sx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].sy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].sz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].sx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].sy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].sz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].sx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].sy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].sz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Noeud[pt1].sx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].sy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].sz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].sx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].sy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].sz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].sx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].sy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].sz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Noeud[deb].sx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.00);
			sprintf(chaine,"%.3g",Noeud[deb].sy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.02);
			sprintf(chaine,"%.3g",Noeud[deb].sz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.04);
			sprintf(chaine,"%.3g",Noeud[fin].sx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.00);
			sprintf(chaine,"%.3g",Noeud[fin].sy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.02);
			sprintf(chaine,"%.3g",Noeud[fin].sz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%.3g",Noeud[deb].sx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.00);
				sprintf(chaine,"%.3g",Noeud[deb].sy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.02);
				sprintf(chaine,"%.3g",Noeud[deb].sz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.04);
				sprintf(chaine,"%.3g",Noeud[fin].sx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.00);
				sprintf(chaine,"%.3g",Noeud[fin].sy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.02);
				sprintf(chaine,"%.3g",Noeud[fin].sz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.04);
				}
			}
		}
	}

void draw_longueur_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double  decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node length (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].sx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].sy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].sz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt2].sx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].sy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].sz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt3].sx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].sy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].sz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_longueur_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double  decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node length (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].sx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].sy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].sz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt2].sx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].sy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].sz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt3].sx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].sy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].sz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_longueur_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double  decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node length (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Noeud[deb].sx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.00);
	sprintf(chaine,"%.3g",Noeud[deb].sy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.02);
	sprintf(chaine,"%.3g",Noeud[deb].sz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.04);
	
	sprintf(chaine,"%.3g",Noeud[fin].sx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.00);
	sprintf(chaine,"%.3g",Noeud[fin].sy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.02);
	sprintf(chaine,"%.3g",Noeud[fin].sz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.04);
	}
	
void draw_longueur_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double  decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node length (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%.3g",Noeud[deb].sx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.00);
		sprintf(chaine,"%.3g",Noeud[deb].sy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.02);
		sprintf(chaine,"%.3g",Noeud[deb].sz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine, -0.04);
		
		sprintf(chaine,"%.3g",Noeud[fin].sx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.00);
		sprintf(chaine,"%.3g",Noeud[fin].sy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.02);
		sprintf(chaine,"%.3g",Noeud[fin].sz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine, -0.04);
		}
	}
	
void dessiner_cd_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
		extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node drag coefficient", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Noeud[pt1].cdx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].cdy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].cdz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].cdx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].cdy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].cdz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].cdx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].cdy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].cdz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Noeud[pt1].cdx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].cdy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].cdz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].cdx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].cdy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].cdz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].cdx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].cdy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].cdz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Noeud[deb].cdx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[deb].cdy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[deb].cdz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
			sprintf(chaine,"%.3g",Noeud[fin].cdx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[fin].cdy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[fin].cdz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%.3g",Noeud[deb].cdx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
				sprintf(chaine,"%.3g",Noeud[deb].cdy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
				sprintf(chaine,"%.3g",Noeud[deb].cdz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
				sprintf(chaine,"%.3g",Noeud[fin].cdx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
				sprintf(chaine,"%.3g",Noeud[fin].cdy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
				sprintf(chaine,"%.3g",Noeud[fin].cdz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
				}
			}
		}
	}
	
void draw_cd_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node drag coefficient", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].cdx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].cdy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].cdz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt2].cdx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].cdy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].cdz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt3].cdx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].cdy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].cdz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}
	
void draw_cd_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node drag coefficient", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].cdx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].cdy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].cdz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt2].cdx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].cdy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].cdz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt3].cdx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].cdy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].cdz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_cd_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node drag coefficient", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Noeud[deb].cdx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[deb].cdy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[deb].cdz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[fin].cdx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[fin].cdy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[fin].cdz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
	}

void draw_cd_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node drag coefficient", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%.3g",Noeud[deb].cdx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
		sprintf(chaine,"%.3g",Noeud[deb].cdy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
		sprintf(chaine,"%.3g",Noeud[deb].cdz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
		
		sprintf(chaine,"%.3g",Noeud[fin].cdx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
		sprintf(chaine,"%.3g",Noeud[fin].cdy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
		sprintf(chaine,"%.3g",Noeud[fin].cdz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
		}
	}
	
void dessiner_effort_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
		extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node exterior forces (N)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Noeud[pt1].fx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].fy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].fz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].fx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].fy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].fz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].fx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].fy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].fz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Noeud[pt1].fx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].fy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].fz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].fx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].fy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].fz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].fx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].fy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].fz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Noeud[deb].fx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[deb].fy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[deb].fz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
			sprintf(chaine,"%.3g",Noeud[fin].fx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[fin].fy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[fin].fz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%.3g",Noeud[deb].fx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
				sprintf(chaine,"%.3g",Noeud[deb].fy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
				sprintf(chaine,"%.3g",Noeud[deb].fz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
				sprintf(chaine,"%.3g",Noeud[fin].fx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
				sprintf(chaine,"%.3g",Noeud[fin].fy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
				sprintf(chaine,"%.3g",Noeud[fin].fz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
				}
			}
		}
	}

void draw_effort_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node exterior forces (N)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].fx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].fy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].fz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt2].fx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].fy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].fz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt3].fx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].fy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].fz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_effort_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node exterior forces (N)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].fx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].fy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].fz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);

	sprintf(chaine,"%.3g",Noeud[pt2].fx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].fy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].fz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);

	sprintf(chaine,"%.3g",Noeud[pt3].fx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].fy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].fz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_effort_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node exterior forces (N)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Noeud[deb].fx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[deb].fy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[deb].fz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[fin].fx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[fin].fy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[fin].fz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
	}

void draw_effort_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node exterior forces (N)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%.3g",Noeud[deb].fx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
		sprintf(chaine,"%.3g",Noeud[deb].fy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
		sprintf(chaine,"%.3g",Noeud[deb].fz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
		
		sprintf(chaine,"%.3g",Noeud[fin].fx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
		sprintf(chaine,"%.3g",Noeud[fin].fy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
		sprintf(chaine,"%.3g",Noeud[fin].fz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
		}
	}

void dessiner_limite_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
		extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Noeud[pt1].limx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].limy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].limz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].limx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].limy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].limz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].limx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].limy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].limz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Noeud[pt1].limx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt1].limy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt1].limz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt2].limx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt2].limy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt2].limz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%.3g",Noeud[pt3].limx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[pt3].limy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[pt3].limz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%.3g",Noeud[deb].limx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[deb].limy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[deb].limz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
			sprintf(chaine,"%.3g",Noeud[fin].limx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Noeud[fin].limy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
			sprintf(chaine,"%.3g",Noeud[fin].limz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%.3g",Noeud[deb].limx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
				sprintf(chaine,"%.3g",Noeud[deb].limy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
				sprintf(chaine,"%.3g",Noeud[deb].limz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
				sprintf(chaine,"%.3g",Noeud[fin].limx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
				sprintf(chaine,"%.3g",Noeud[fin].limy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
				sprintf(chaine,"%.3g",Noeud[fin].limz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
				}
			}
		}
	}
	
void draw_limite_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].limx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].limy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].limz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt2].limx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].limy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].limz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt3].limx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].limy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].limz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}
	
void draw_limite_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Noeud[pt1].limx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt1].limy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt1].limz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt2].limx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt2].limy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt2].limz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[pt3].limx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[pt3].limy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[pt3].limz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_limite_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%.3g",Noeud[deb].limx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[deb].limy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[deb].limz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
	
	sprintf(chaine,"%.3g",Noeud[fin].limx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Noeud[fin].limy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
	sprintf(chaine,"%.3g",Noeud[fin].limz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
	}

void draw_limite_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit (m)", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%.3g",Noeud[deb].limx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
		sprintf(chaine,"%.3g",Noeud[deb].limy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
		sprintf(chaine,"%.3g",Noeud[deb].limz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
		
		sprintf(chaine,"%.3g",Noeud[fin].limx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
		sprintf(chaine,"%.3g",Noeud[fin].limy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
		sprintf(chaine,"%.3g",Noeud[fin].limz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
		}
	}

void dessiner_sens_limite_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
		extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit direction", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",Noeud[pt1].fmx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt1].fmy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt1].fmz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt2].fmx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt2].fmy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt2].fmz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt3].fmx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt3].fmy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt3].fmz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",Noeud[pt1].fmx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt1].fmy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt1].fmz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt2].fmx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt2].fmy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt2].fmz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt3].fmx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt3].fmy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt3].fmz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%d",Noeud[deb].fmx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[deb].fmy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[deb].fmz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
			sprintf(chaine,"%d",Noeud[fin].fmx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[fin].fmy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[fin].fmz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%d",Noeud[deb].fmx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
				sprintf(chaine,"%d",Noeud[deb].fmy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
				sprintf(chaine,"%d",Noeud[deb].fmz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
				sprintf(chaine,"%d",Noeud[fin].fmx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
				sprintf(chaine,"%d",Noeud[fin].fmy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
				sprintf(chaine,"%d",Noeud[fin].fmz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
				}
			}
		}
	}
	
void draw_sens_limite_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit direction", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%d",Noeud[pt1].fmx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt1].fmy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt1].fmz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt2].fmx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt2].fmy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt2].fmz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt3].fmx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt3].fmy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt3].fmz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}
	
void draw_sens_limite_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit direction", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/


	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%d",Noeud[pt1].fmx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt1].fmy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt1].fmz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt2].fmx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt2].fmy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt2].fmz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt3].fmx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt3].fmy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt3].fmz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}
	
void draw_sens_limite_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit direction", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/


	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%d",Noeud[deb].fmx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[deb].fmy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[deb].fmz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[fin].fmx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[fin].fmy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[fin].fmz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
	}
	
void draw_sens_limite_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node limit direction", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%d",Noeud[deb].fmx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
		sprintf(chaine,"%d",Noeud[deb].fmy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
		sprintf(chaine,"%d",Noeud[deb].fmz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
		
		sprintf(chaine,"%d",Noeud[fin].fmx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
		sprintf(chaine,"%d",Noeud[fin].fmy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
		sprintf(chaine,"%d",Noeud[fin].fmz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
		}
	}
	
void dessiner_deplacement_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;

	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node free/fixed", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",Noeud[pt1].fixx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt1].fixy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt1].fixz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt2].fixx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt2].fixy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt2].fixz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt3].fixx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt3].fixy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt3].fixz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",Noeud[pt1].fixx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt1].fixy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt1].fixz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt2].fixx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt2].fixy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt2].fixz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt3].fixx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt3].fixy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt3].fixz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%d",Noeud[deb].fixx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[deb].fixy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[deb].fixz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
			sprintf(chaine,"%d",Noeud[fin].fixx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[fin].fixy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[fin].fixz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%d",Noeud[deb].fixx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
				sprintf(chaine,"%d",Noeud[deb].fixy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
				sprintf(chaine,"%d",Noeud[deb].fixz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
				sprintf(chaine,"%d",Noeud[fin].fixx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
				sprintf(chaine,"%d",Noeud[fin].fixy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
				sprintf(chaine,"%d",Noeud[fin].fixz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
				}
			}
		}
	}

void draw_deplacement_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;

	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node free/fixed", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%d",Noeud[pt1].fixx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt1].fixy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt1].fixz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt2].fixx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt2].fixy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt2].fixz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt3].fixx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt3].fixy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt3].fixz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_deplacement_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;

	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node free/fixed", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%d",Noeud[pt1].fixx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt1].fixy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt1].fixz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt2].fixx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt2].fixy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt2].fixz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt3].fixx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt3].fixy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt3].fixz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_deplacement_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;

	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node free/fixed", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

			
	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%d",Noeud[deb].fixx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[deb].fixy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[deb].fixz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[fin].fixx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[fin].fixy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[fin].fixz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
	}

void draw_deplacement_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;

	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node free/fixed", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%d",Noeud[deb].fixx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
		sprintf(chaine,"%d",Noeud[deb].fixy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
		sprintf(chaine,"%d",Noeud[deb].fixz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
		
		sprintf(chaine,"%d",Noeud[fin].fixx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
		sprintf(chaine,"%d",Noeud[fin].fixy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
		sprintf(chaine,"%d",Noeud[fin].fixz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
		}
	}

void dessiner_symmetrie_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node symetry", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",Noeud[pt1].symx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt1].symy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt1].symz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt2].symx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt2].symy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt2].symz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt3].symx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt3].symy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt3].symz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%d",Noeud[pt1].symx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt1].symy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt1].symz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt2].symx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt2].symy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt2].symz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
			
			sprintf(chaine,"%d",Noeud[pt3].symx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[pt3].symy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[pt3].symz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
			sprintf(chaine,"%d",Noeud[deb].symx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[deb].symy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[deb].symz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
			sprintf(chaine,"%d",Noeud[fin].symx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
			sprintf(chaine,"%d",Noeud[fin].symy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
			sprintf(chaine,"%d",Noeud[fin].symz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].flag_dessin != 0))
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
			
				sprintf(chaine,"%d",Noeud[deb].symx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
				sprintf(chaine,"%d",Noeud[deb].symy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
				sprintf(chaine,"%d",Noeud[deb].symz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
				sprintf(chaine,"%d",Noeud[fin].symx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
				sprintf(chaine,"%d",Noeud[fin].symy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
				sprintf(chaine,"%d",Noeud[fin].symz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
				}
			}
		}
	}

void draw_symmetrie_noeud_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node symetry", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	sprintf(chaine,"%d",Noeud[pt1].symx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt1].symy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt1].symz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt2].symx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt2].symy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt2].symz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt3].symx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt3].symy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt3].symz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_symmetrie_noeud_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node symetry", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%d",Noeud[pt1].symx);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt1].symy);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt1].symz);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt2].symx);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt2].symy);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt2].symz);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[pt3].symx);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[pt3].symy);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[pt3].symz);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.04);
	}

void draw_symmetrie_noeud_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node symetry", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	sprintf(chaine,"%d",Noeud[deb].symx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[deb].symy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[deb].symz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
	
	sprintf(chaine,"%d",Noeud[fin].symx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
	sprintf(chaine,"%d",Noeud[fin].symy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
	sprintf(chaine,"%d",Noeud[fin].symz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
	}

void draw_symmetrie_noeud_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLACK, (double) binx, (double) biny, "node symetry", (0.0 * 0.02)); 	/*decalage de 1 puisque c est un noeud*/

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
	
		sprintf(chaine,"%d",Noeud[deb].symx);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.00);
		sprintf(chaine,"%d",Noeud[deb].symy);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.02);
		sprintf(chaine,"%d",Noeud[deb].symz);EcritText(RED, Noeud[deb].x, Noeud[deb].y, chaine,-0.04);
		
		sprintf(chaine,"%d",Noeud[fin].symx);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.00);
		sprintf(chaine,"%d",Noeud[fin].symy);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.02);
		sprintf(chaine,"%d",Noeud[fin].symz);EcritText(RED, Noeud[fin].x, Noeud[fin].y, chaine,-0.04);
		}
	}



void dessiner_nb_mailles()
	{
	int pa,no,pt1,pt2,pt3;
	char chaine[317];
	double xxm,yym,xxn,yyn,xxo,yyo,xxp,yyp,aa,bb;
	
	EcritText(BLACK, (double) binx, (double) biny, "meshes number", (0.0 * 0.02));/**/ 	/*decalage de 1 puisque c est un noeud*/
	
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
					
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			sprintf(chaine,"%.3g",Surface[pa].lon[1]);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Surface[pa].lon[2]);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
			
			sprintf(chaine,"%.3g",Surface[pa].lon[3]);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Surface[pa].lon[4]);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
			
			sprintf(chaine,"%.3g",Surface[pa].lon[5]);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Surface[pa].lon[6]);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			/*EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);*/
		
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);/**/

			sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[1]);EcritText(BLACK, Noeud[pt1].x+0.6, Noeud[pt1].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[2]);EcritText(BLACK, Noeud[pt1].x+0.6, Noeud[pt1].y, chaine,-0.02);
			
			sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[3]);EcritText(BLACK, Noeud[pt2].x+0.6, Noeud[pt2].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[4]);EcritText(BLACK, Noeud[pt2].x+0.6, Noeud[pt2].y, chaine,-0.02);
			
			sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[5]);EcritText(BLACK, Noeud[pt3].x+0.6, Noeud[pt3].y, chaine,-0.00);
			sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[6]);EcritText(BLACK, Noeud[pt3].x+0.6, Noeud[pt3].y, chaine,-0.02);
			
			if (ARTICLE_HEXA_2001 == 1)
				{
				/*sprintf(chaine,"%d",pt1);EcritText(BLACK, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.01);
				sprintf(chaine,"%d",pt2);EcritText(BLACK, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.01);
				sprintf(chaine,"%d",pt3);EcritText(BLACK, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.01);
			
				TraceSegment(BLACK, Noeud[pt1].x+0.3, Noeud[pt1].y+0.3, Noeud[pt1].x+0.3, Noeud[pt1].y-0.7);
				TraceSegment(BLACK, Noeud[pt2].x+0.3, Noeud[pt2].y+0.3, Noeud[pt2].x+0.3, Noeud[pt2].y-0.7);
				TraceSegment(BLACK, Noeud[pt3].x+0.3, Noeud[pt3].y+0.3, Noeud[pt3].x+0.3, Noeud[pt3].y-0.7);*/
				if (pa ==1)
					{
					aa = 1.0/5.0 * (2.0 - 2.5/3.0);
					bb = +1.0/3.0;
					xxm = Noeud[pt1].x  + aa *(Noeud[pt2].x-Noeud[pt1].x) + bb * (Noeud[pt3].x-Noeud[pt1].x);
					yym = Noeud[pt1].y  + aa *(Noeud[pt2].y-Noeud[pt1].y) + bb * (Noeud[pt3].y-Noeud[pt1].y);
					aa = 1.0/5.0 * (3.0 - 2.5/3.0);
					bb = 1.0/3.0;
					xxn = Noeud[pt1].x  + aa *(Noeud[pt2].x-Noeud[pt1].x) + bb * (Noeud[pt3].x-Noeud[pt1].x);
					yyn = Noeud[pt1].y  + aa *(Noeud[pt2].y-Noeud[pt1].y) + bb * (Noeud[pt3].y-Noeud[pt1].y);
					aa = 1.0/5.0 * (2.0 - 2.5*2.0/3.0);
					bb = 2.0/3.0;
					xxo = Noeud[pt1].x  + aa *(Noeud[pt2].x-Noeud[pt1].x) + bb * (Noeud[pt3].x-Noeud[pt1].x);
					yyo = Noeud[pt1].y  + aa *(Noeud[pt2].y-Noeud[pt1].y) + bb * (Noeud[pt3].y-Noeud[pt1].y);
					aa = 1.0/5.0 * (3.0 - 2.5*2.0/3.0);
					bb = 2.0/3.0;
					xxp = Noeud[pt1].x  + aa *(Noeud[pt2].x-Noeud[pt1].x) + bb * (Noeud[pt3].x-Noeud[pt1].x);
					yyp = Noeud[pt1].y  + aa *(Noeud[pt2].y-Noeud[pt1].y) + bb * (Noeud[pt3].y-Noeud[pt1].y);
					EffaceTriangle(230, xxm, yym, xxn, yyn, xxo, yyo);
					EffaceTriangle(230, xxp, yyp, xxn, yyn, xxo, yyo);
					/*TraceSegment(BLACK, xxm, yym, xxn, yyn);
					TraceSegment(BLACK, xxm, yym, xxo, yyo);
					EcritText(BLACK, xxn-0.01, yyn, "U",-0.01);
					EcritText(BLACK, xxo-0.6, yyo, "V",-0.01);*/
					}
				}
			}
		
		}
	}
	
void draw_nb_mailles_diamond(int pa)
	{
	int no,pt1,pt2,pt3;
	char chaine[317];
	double xxm,yym,xxn,yyn,xxo,yyo,xxp,yyp,aa,bb;
	
	EcritText(BLACK, (double) binx, (double) biny, "meshes number", (0.0 * 0.02));/**/ 	/*decalage de 1 puisque c est un noeud*/
	
	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
			
	sprintf(chaine,"%.3g",Surface[pa].lon[1]);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Surface[pa].lon[2]);EcritText(BLUE, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.02);
	
	sprintf(chaine,"%.3g",Surface[pa].lon[3]);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Surface[pa].lon[4]);EcritText(BLUE, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.02);
	
	sprintf(chaine,"%.3g",Surface[pa].lon[5]);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Surface[pa].lon[6]);EcritText(BLUE, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.02);
	}
	
void draw_nb_mailles_hexa(int pa)
	{
	int no,pt1,pt2,pt3;
	char chaine[317];
	double xxm,yym,xxn,yyn,xxo,yyo,xxp,yyp,aa,bb;
	
	EcritText(BLACK, (double) binx, (double) biny, "meshes number", (0.0 * 0.02));/**/ 	/*decalage de 1 puisque c est un noeud*/
	
	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[1]);EcritText(BLACK, Noeud[pt1].x+0.6, Noeud[pt1].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[2]);EcritText(BLACK, Noeud[pt1].x+0.6, Noeud[pt1].y, chaine,-0.02);
	
	sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[3]);EcritText(BLACK, Noeud[pt2].x+0.6, Noeud[pt2].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[4]);EcritText(BLACK, Noeud[pt2].x+0.6, Noeud[pt2].y, chaine,-0.02);
	
	sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[5]);EcritText(BLACK, Noeud[pt3].x+0.6, Noeud[pt3].y, chaine,-0.00);
	sprintf(chaine,"%.3g",Surf_Hexa[pa].lon[6]);EcritText(BLACK, Noeud[pt3].x+0.6, Noeud[pt3].y, chaine,-0.02);
	
	if (ARTICLE_HEXA_2001 == 1)
		{
		/*sprintf(chaine,"%d",pt1);EcritText(BLACK, Noeud[pt1].x, Noeud[pt1].y, chaine,-0.01);
		sprintf(chaine,"%d",pt2);EcritText(BLACK, Noeud[pt2].x, Noeud[pt2].y, chaine,-0.01);
		sprintf(chaine,"%d",pt3);EcritText(BLACK, Noeud[pt3].x, Noeud[pt3].y, chaine,-0.01);
	
		TraceSegment(BLACK, Noeud[pt1].x+0.3, Noeud[pt1].y+0.3, Noeud[pt1].x+0.3, Noeud[pt1].y-0.7);
		TraceSegment(BLACK, Noeud[pt2].x+0.3, Noeud[pt2].y+0.3, Noeud[pt2].x+0.3, Noeud[pt2].y-0.7);
		TraceSegment(BLACK, Noeud[pt3].x+0.3, Noeud[pt3].y+0.3, Noeud[pt3].x+0.3, Noeud[pt3].y-0.7);*/
		if (pa ==1)
			{
			aa = 1.0/5.0 * (2.0 - 2.5/3.0);
			bb = +1.0/3.0;
			xxm = Noeud[pt1].x  + aa *(Noeud[pt2].x-Noeud[pt1].x) + bb * (Noeud[pt3].x-Noeud[pt1].x);
			yym = Noeud[pt1].y  + aa *(Noeud[pt2].y-Noeud[pt1].y) + bb * (Noeud[pt3].y-Noeud[pt1].y);
			aa = 1.0/5.0 * (3.0 - 2.5/3.0);
			bb = 1.0/3.0;
			xxn = Noeud[pt1].x  + aa *(Noeud[pt2].x-Noeud[pt1].x) + bb * (Noeud[pt3].x-Noeud[pt1].x);
			yyn = Noeud[pt1].y  + aa *(Noeud[pt2].y-Noeud[pt1].y) + bb * (Noeud[pt3].y-Noeud[pt1].y);
			aa = 1.0/5.0 * (2.0 - 2.5*2.0/3.0);
			bb = 2.0/3.0;
			xxo = Noeud[pt1].x  + aa *(Noeud[pt2].x-Noeud[pt1].x) + bb * (Noeud[pt3].x-Noeud[pt1].x);
			yyo = Noeud[pt1].y  + aa *(Noeud[pt2].y-Noeud[pt1].y) + bb * (Noeud[pt3].y-Noeud[pt1].y);
			aa = 1.0/5.0 * (3.0 - 2.5*2.0/3.0);
			bb = 2.0/3.0;
			xxp = Noeud[pt1].x  + aa *(Noeud[pt2].x-Noeud[pt1].x) + bb * (Noeud[pt3].x-Noeud[pt1].x);
			yyp = Noeud[pt1].y  + aa *(Noeud[pt2].y-Noeud[pt1].y) + bb * (Noeud[pt3].y-Noeud[pt1].y);
			EffaceTriangle(230, xxm, yym, xxn, yyn, xxo, yyo);
			EffaceTriangle(230, xxp, yyp, xxn, yyn, xxo, yyo);
			/*TraceSegment(BLACK, xxm, yym, xxn, yyn);
			TraceSegment(BLACK, xxm, yym, xxo, yyo);
			EcritText(BLACK, xxn-0.01, yyn, "U",-0.01);
			EcritText(BLACK, xxo-0.6, yyo, "V",-0.01);*/
			}
		}
	}

