#include "batz.h"
#define rouge1 0xFF9999
#define rouge2 0xFF6666
#define rouge3 0xCC3333
#define rouge4 0xAA1111
#define rouge5 0x990000
#define bleu5  0x0000FF
#define bleu4  0x3333FF
#define bleu3  0x6666FF
#define bleu2  0x9999FF
#define bleu1  0xCCCCFF
#define marron 0x996600

#define couleur1  0x990000 /*rouge foncé*/
#define couleur2  0x000000 /*rnoir*/
#define couleur3  0x3300FF /*bleu*/
#define couleur4  0x00CC00 /*vert*/
#define couleur5  0xCCCC66 /*jaune foncé*/
#define couleur6  0x33FFFF /*turquoise*/
#define couleur7  0xFF33CC /*rose*/
#define couleur8  0x9999FF /*bleu clair*/
#define couleur9  0xFF9933 /*orange*/
#define couleur10  0x9900FF /*violet*/

void dessiner_contour_winch()
	{
	int pa,deb,fin,no;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*dx01,dx02,dy01,dy02 sont les coordonnees des extremites de segment a desssiner.
	dx01,dx02,dy01,dy02 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	Color(BLACK);

	for (pa=1;pa<=NOMBRE_WINCHS;pa++)
		{ 
		if (Winch[pa].flag_dessin != 0)
			{
			for (no=1;no<=Winch[pa].nb_barre;no++)
				{ 
				deb = Winch[pa].noeud[1];
    				fin = Winch[pa].noeud[no];
				/*TraceSegment(YELLOW, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);*/
				TraceSegment(Winch[pa].flag_dessin, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			}
		}
	}


void draw_contour_winch(int pa)
	{
	int deb,fin,no;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*dx01,dx02,dy01,dy02 sont les coordonnees des extremites de segment a desssiner.
	dx01,dx02,dy01,dy02 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	for (no=1;no<=Winch[pa].nb_barre;no++)
		{ 
		deb = Winch[pa].noeud[no  ];
		fin = Winch[pa].noeud[no+1];
		//printf("deb %d fin %d ",deb,fin);
		//printf("x %lf  %lf ",Noeud[deb].x, Noeud[fin].x);
		//printf("y %lf  %lf \n",Noeud[deb].y, Noeud[fin].y);
		TraceSegment(Winch[pa].flag_dessin, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
		}
	}


void dessiner_contour_ball()
	{
	int pa,deb,fin,no,nb_angle;
	float angle_ball_1,angle_ball_2;
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*dx01,dx02,dy01,dy02 sont les coordonnees des extremites de segment a desssiner.
	dx01,dx02,dy01,dy02 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	Color(RED);
	nb_angle = 20;	/*nb of segment in the contour of balls*/

	for (pa=1;pa<=Ball.nb;pa++)
		{ 
		deb = Ball.noeud[pa];
 		/*printf("pa %4d deb %4d inix %5.0lf %5.0lf %5.0lf",pa,deb,Noeud[deb].inix,Noeud[deb].iniy,Noeud[deb].iniz);
 		printf(" x %5.0lf %5.0lf %5.0lf\n",Noeud[deb].x,Noeud[deb].y,Noeud[deb].z);*/
		for (no=1;no<=nb_angle;no++)
			{ 
			angle_ball_1 = (no-1) * (2.0 * PI / nb_angle);
			angle_ball_2 = (no+0) * (2.0 * PI / nb_angle);
			TraceSegment(RED, Noeud[deb].x + Ball.radius[pa]*sin(angle_ball_1), Noeud[deb].y + Ball.radius[pa]*cos(angle_ball_1), Noeud[deb].x + Ball.radius[pa]*sin(angle_ball_2), Noeud[deb].y + Ball.radius[pa]*cos(angle_ball_2));
			}
		}
	}


void draw_contour_ball(int pa)
	{
	int deb,fin,no,nb_angle;
	float angle_ball_1,angle_ball_2;
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	nb_angle = 20;	/*nb of segment in the contour of balls*/

	deb = Ball.noeud[pa];
	/*printf("pa %4d deb %4d inix %5.0lf %5.0lf %5.0lf",pa,deb,Noeud[deb].inix,Noeud[deb].iniy,Noeud[deb].iniz);
	printf(" x %5.0lf %5.0lf %5.0lf\n",Noeud[deb].x,Noeud[deb].y,Noeud[deb].z);*/
	for (no=1;no<=nb_angle;no++)
		{ 
		angle_ball_1 = (no-1) * (2.0 * PI / nb_angle);
		angle_ball_2 = (no+0) * (2.0 * PI / nb_angle);
		TraceSegment(RED, Noeud[deb].x + Ball.radius[pa]*sin(angle_ball_1), Noeud[deb].y + Ball.radius[pa]*cos(angle_ball_1), Noeud[deb].x + Ball.radius[pa]*sin(angle_ball_2), Noeud[deb].y + Ball.radius[pa]*cos(angle_ball_2));
		}
	}


void dessiner_contour_coulisse()
	{
	int pa,deb,fin,no,zi,el;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*dx01,dx02,dy01,dy02 sont les coordonnees des extremites de segment a desssiner.
	dx01,dx02,dy01,dy02 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	Color(BLACK);

	for (pa=1;pa<=NOMBRE_COULISSES;pa++)
		{ 
		if (Coulisse[pa].flag_dessin != 0)
			{
			for (no=1;no<=Coulisse[pa].nb_noeud + 1;no++)
				{ 
				if (no == 1) deb = Coulisse[pa].extremite[1];
				if (no != 1) deb = Coulisse[pa].noeud[no-1];
    				if (no != Coulisse[pa].nb_noeud + 1) fin = Coulisse[pa].noeud[no];
    				if (no == Coulisse[pa].nb_noeud + 1) fin = Coulisse[pa].extremite[2];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			}
		}
	for (pa=1;pa<=Structure.nb_slider;pa++)
		{ 
		printf("pa %d\n", pa);
		for (zi=1;zi<=Slider[pa].nb_bar;zi++)
			{
			el = Slider[pa].barre[zi];
			printf("  zi %d ", zi);
			printf("  el %d  ", el);
			//exit(0);
			//element[el].slider = pa;	//this element is part of a slider
			//element[el].flag_dessin = 0;
			deb = element[el].extremite[1];
			fin = element[el].extremite[2];
			TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			}
		}
	}


void draw_contour_coulisse(int pa)
	{
	int deb,fin,no;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*dx01,dx02,dy01,dy02 sont les coordonnees des extremites de segment a desssiner.
	dx01,dx02,dy01,dy02 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	for (no=1;no<=Coulisse[pa].nb_noeud + 1;no++)
		{ 
		if (no == 1) deb = Coulisse[pa].extremite[1];
		if (no != 1) deb = Coulisse[pa].noeud[no-1];
		if (no != Coulisse[pa].nb_noeud + 1) fin = Coulisse[pa].noeud[no];
		if (no == Coulisse[pa].nb_noeud + 1) fin = Coulisse[pa].extremite[2];
		TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
		}
	}


void dessiner_contour_element()
	{
	int pa,deb,fin,elem,nb,zi,zj,zk,type,zl;
	double diam,x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,y5,y6,z1,z2,pas_x,pas_y,ratio,ratio_local,U[4],V[4],W[4],norm;
	double ext1[4],ext2[4];
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*dx01,dx02,dy01,dy02 sont les coordonnees des extremites de segment a desssiner.
	dx01,dx02,dy01,dy02 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	Color(BLUE);

	for (pa=1;pa<=NOMBRE_ELEMENTS;pa++)
		{ 
		if (TypeElement[Element[pa].type].flag_dessin != 0)
			{
			/*if (TypeElement[Element[pa].type].flag_dessin != 0)
				{
				deb = Element[pa].extremite[1];
				fin = Element[pa].extremite[2];
				TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}*/
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			/*TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);*/
			/*TraceSegment(TypeElement[Element[pa].type].flag_dessin, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);*/
			/*draw_segment_color(TypeElement[Element[pa].type].flag_dessin, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);*/
			x1 = Noeud[deb].x;		y1 = Noeud[deb].y;
			x2 = Noeud[fin].x;		y2 = Noeud[fin].y;
			U[1] = x2-x1;			U[2] = y2-y1;			U[3] = 0.0; 		/*U vector is the element vector in pplane XoY*/
			/*printf("U %lf %lf %lf  ",U[1],U[2],U[3]);*/
			norm = sqrt(produit_scal_double(U,U));		/*length of side U*/
			U[1] = (x2-x1)/norm;		U[2] = (y2-y1)/norm;		U[3] = (0.0)/norm; 	/*U vector is the normalized element vector*/
			V[1] = 0.0;			V[2] = 0.0;			V[3] = 1.0;
			produit_vect3_double(U, V, W); 								/*W vector is normal to U and in the plane XoY*/
		
			/*
			printf("norm %lf ",norm);
			printf("diametrehydro %lf ",Element[pa].diametrehydro);
			printf("U %lf %lf %lf  ",U[1],U[2],U[3]);
			printf("V %lf %lf %lf  ",V[1],V[2],V[3]);
			printf("W %lf %lf %lf \n",W[1],W[2],W[3]);
			*/
		
		
			x3 = x1 + W[1] * Element[pa].diametrehydro / 2.0;		y3 = y1 + W[2] * Element[pa].diametrehydro / 2.0;
			x4 = x2 + W[1] * Element[pa].diametrehydro / 2.0;		y4 = y2 + W[2] * Element[pa].diametrehydro / 2.0;
			x5 = x1 - W[1] * Element[pa].diametrehydro / 2.0;		y5 = y1 - W[2] * Element[pa].diametrehydro / 2.0;
			x6 = x2 - W[1] * Element[pa].diametrehydro / 2.0;		y6 = y2 - W[2] * Element[pa].diametrehydro / 2.0;

			/*
			printf("1 %lf %lf ",x1,y1);
			printf("2 %lf %lf ",x2,y2);
			printf("3 %lf %lf ",x3,y3);
			printf("4 %lf %lf ",x4,y4);
			printf("5 %lf %lf ",x5,y5);
			printf("6 %lf %lf  \n",x6,y6);
			*/
		
		
			/*
			draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);
			draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x4, y4, x6, y6);
			draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x6, y6, x5, y5);
			draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x5, y5, x3, y3);
			*/
			
			x1 = Noeud[deb].x;		y1 = Noeud[deb].y;		z1 = Noeud[deb].z;
			x2 = Noeud[fin].x;		y2 = Noeud[fin].y;		z2 = Noeud[fin].z;
			if (Noeud[deb].z > Noeud[fin].z)
				{
				ext1[1] = Noeud[deb].x;		ext1[2] = Noeud[deb].y;		ext1[3] = Noeud[deb].z;	/*element extremity closer to the eye*/
				ext2[1] = Noeud[fin].x;		ext2[2] = Noeud[fin].y;		ext2[3] = Noeud[fin].z;
				}
			else
				{
				ext1[1] = Noeud[fin].x;		ext1[2] = Noeud[fin].y;		ext1[3] = Noeud[fin].z;	/*element extremity closer to the eye*/
				ext2[1] = Noeud[deb].x;		ext2[2] = Noeud[deb].y;		ext2[3] = Noeud[deb].z;
				}
			U[1] = x2-x1;			U[2] = y2-y1;			U[3] = z2-z1; 		/*U vector is the element vector*/
			/*printf("U %lf %lf %lf\n",U[1],U[2],U[3]);*/
			norm = sqrt(produit_scal_double(U,U));		/*length of side U*/
			produit_scal_vect_double(1.0/norm, U, U);						/*U vector is the normalized element vector*/
			/*printf("norm %lf \n",norm);
			printf("Un %lf %lf %lf\n",U[1],U[2],U[3]);*/
	
			if (U[1] != 0.0)
				{
				V[1] = -U[2];	V[2] = U[1];	V[3] =  0.0;	/*V is normal to U*/
				norm = sqrt(produit_scal_double(V,V));		/*length of side V*/
				produit_scal_vect_double(1.0/norm, V, V);	/*V is normalized*/
				produit_vect3_double(U, V, W);			/*W is normal to U & V*/
				}
			if (U[2] != 0.0)
				{
				V[1] = 0.0;	V[2] = -U[3];	V[3] =  U[2];
				norm = sqrt(produit_scal_double(V,V));		/*length of side V*/
				produit_scal_vect_double(1.0/norm, V, V);
				produit_vect3_double(U, V, W);
				}
			if (U[3] != 0.0)
				{
				V[1] = U[3];	V[2] = 0.0;	V[3] =  -U[1];
				norm = sqrt(produit_scal_double(V,V));		/*length of side V*/
				produit_scal_vect_double(1.0/norm, V, V);
				produit_vect3_double(U, V, W);
				}
			produit_scal_vect_double(Element[pa].diametrehydro / 2.0, V, V);	/*V is normal to U and of diametrehydro length*/
			produit_scal_vect_double(Element[pa].diametrehydro / 2.0, W, W);	/*W is normal to U&V and of diametrehydro length*/
			/*printf("V %lf %lf %lf\n",V[1],V[2],V[3]);*/
			/*printf("W %lf %lf %lf\n",W[1],W[2],W[3]);*/
			for (zj=1;zj<=20;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = x1 + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = y1 + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = x1 + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = y1 + cos( betaa) * V[2] + sin( betaa) * W[2];
				draw_segment_color(2, x3, y3, x4, y4);
				x3 = x2 + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = y2 + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = x2 + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = y2 + cos( betaa) * V[2] + sin( betaa) * W[2];
				draw_segment_color(2, x3, y3, x4, y4);
				x3 = x1 + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = y1 + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = x2 + cos(alpha) * V[1] + sin(alpha) * W[1];	y4 = y2 + cos(alpha) * V[2] + sin(alpha) * W[2];
				draw_segment_color(2, x3, y3, x4, y4);
				/*printf("zj %d xy %lf %lf %lf %lf\n",zj,x3,y3,x4,y4);*/
				}
			}
			
		}
	for (pa=1;pa<=Structure.nb_sphere_element;pa++)
		{ 
		type = Sphere_element.element[pa];
		if (TypeElement[type].flag_dessin != 0)
			{
			nb = Sphere_element.nb[pa];
			/*if (Structure.symetry == 1) nb = 2 * nb;	symetry x*/
			/*if (Structure.symetry == 2) nb = 2 * nb;	symetry y*/
			/*if (Structure.symetry == 4) nb = 2 * nb;	symetry z*/
			/*if (Structure.symetry == 3) nb = 4 * nb;	symetry xy*/
			/*if (Structure.symetry == 5) nb = 4 * nb;	symetry xz*/
			/*if (Structure.symetry == 6) nb = 4 * nb;	symetry yz*/
			/*if (Structure.symetry == 7) nb = 4 * nb;	symetry xyz*/
			diam = Sphere_element.diameter[pa];

			/*
			printf("type %d  ",type);
			printf("nb %d diam %lf\n",nb,diam);
			*/
			for (zk=1;zk<=nb;zk++)
				{
				ratio = 1.0 / 2 / nb + 2.0 / 2 / nb * (zk-1);
				/*
				printf("zk %d ratio %lf \n",zk,ratio);
				*/
				for (zl=1;zl<=NOMBRE_ELEMENTS;zl++)
					{
					if (Element[zl].type == type)
						{
						if ((Element[zl].pro[1]-ratio)*(Element[zl].pro[2]-ratio) <=0.0)
						
							{
							/*
							printf("zl %d  ",zl);
							printf("Element[zl].pro[1] %lf Element[zl].pro[2] %lf\n",Element[zl].pro[1],Element[zl].pro[2]);
							*/				
							ratio_local = (ratio - Element[zl].pro[1]) / (Element[zl].pro[2] - Element[zl].pro[1]);
							deb = Element[zl].extremite[1];
							fin = Element[zl].extremite[2];
						
							x1 = (REEL) Noeud[deb].x;
							y1 = (REEL) Noeud[deb].y;
							x2 = (REEL) Noeud[fin].x;
							y2 = (REEL) Noeud[fin].y;
						
							x3 = x1 + ratio_local * (x2 -x1);
							y3 = y1 + ratio_local * (y2 -y1);
							for (zj=1;zj<=20;zj++)
								{
								x4 = x3 + diam / 2 * cos((zj -1)*2*PI/20);
								y4 = y3 + diam / 2 * sin((zj -1)*2*PI/20);
								x5 = x3 + diam / 2 * cos((zj -0)*2*PI/20);
								y5 = y3 + diam / 2 * sin((zj -0)*2*PI/20);
								draw_segment_color(TypeElement[type].flag_dessin, x4,y4,x5,y5);/**/
								}
							}
						}
					}
				}
			}
		}

	}
	
	
	
void dessiner_contour_element2()
	{
	int pa,deb,fin,elem,nb,zi,zj,zk,type,zl;
	double diam,x3,x4,x5,x6,y3,y4,y5,y6,pas_x,pas_y,ratio,ratio_local,U[4],V[4],W[4],norm;
	double ext1[4],ext2[4];
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*dx01,dx02,dy01,dy02 sont les coordonnees des extremites de segment a desssiner.
	dx01,dx02,dy01,dy02 sont compris entre 0 et 1. 
	0 correspond au bas ou a gauche ?
	1 correspond en haut et a droite de l ecran ?*/
	
	Color(BLUE);

	for (pa=1;pa<=NOMBRE_ELEMENTS;pa++)
		{ 
		if (TypeElement[Element[pa].type].flag_dessin != 0)
			{
			/*printf("element %d    ",pa);*/
			deb = Element[pa].extremite[1];	fin = Element[pa].extremite[2];
			ext1[1] = Noeud[deb].x;		ext1[2] = Noeud[deb].y;		ext1[3] = Noeud[deb].z;
			ext2[1] = Noeud[fin].x;		ext2[2] = Noeud[fin].y;		ext2[3] = Noeud[fin].z;
			if (Noeud[deb].z > Noeud[fin].z)
				{
				ext1[1] = Noeud[deb].x;		ext1[2] = Noeud[deb].y;		ext1[3] = Noeud[deb].z;		/*element extremity closer to the eye*/
				ext2[1] = Noeud[fin].x;		ext2[2] = Noeud[fin].y;		ext2[3] = Noeud[fin].z;
				}
			else
				{
				ext1[1] = Noeud[fin].x;		ext1[2] = Noeud[fin].y;		ext1[3] = Noeud[fin].z;		/*element extremity closer to the eye*/
				ext2[1] = Noeud[deb].x;		ext2[2] = Noeud[deb].y;		ext2[3] = Noeud[deb].z;
				}
			U[1] = ext2[1]-ext1[1];			U[2] = ext2[2]-ext1[2];		U[3] = ext2[3]-ext1[3]; 	/*U vector is the element vector*/
			/*printf("U %lf %lf %lf\n",U[1],U[2],U[3]);*/
			norm = sqrt(produit_scal_double(U,U));		/*length of side U*/
			/*printf("normU %lf ",norm);*/

			produit_scal_vect_double(1.0/norm, U, U);	/*U vector is the normalized element vector*/
			/*norm = sqrt(produit_scal_double(U,U));*/		/*length of side U*/
			/*printf("normU %lf ",norm);*/			/*printf("Un %lf %lf %lf\n",U[1],U[2],U[3]);*/
			
			W[1] = 0.0;	W[2] = 0.0;	W[3] = 1.0; 	/*W vector is normalized and normal to XoY*/
			/*norm = sqrt(produit_scal_double(W,W));*/		/*length of side U*/
			/*printf("normW %lf  ",norm);*/
			
			produit_vect3_double(U, W, V);			/*V is normal to U & W*/
			norm = sqrt(produit_scal_double(V,V));		/*length of side U*/
			/*printf("normV %lf  ",norm);*/
			produit_scal_vect_double(1.0/norm, V, V);	/*U vector is the normalized element vector*/
			/*norm = sqrt(produit_scal_double(V,V));*/		/*length of side U*/
			/*printf("normV %lf  ",norm);*/
			
			produit_vect3_double(U, V, W);			/*W is normal to U & V*/	
			norm = sqrt(produit_scal_double(W,W));		/*length of side U*/
			/*printf("normW %lf  ",norm);*/
			produit_scal_vect_double(1.0/norm, W, W);	/*U vector is the normalized element vector*/
			/*norm = sqrt(produit_scal_double(W,W));*/		/*length of side U*/
			/*printf("normV %lf  \n",norm);*/
	
			produit_scal_vect_double(Element[pa].diametrehydro / 2.0, V, V);	/*V is normal to U and of diametrehydro length*/
			produit_scal_vect_double(Element[pa].diametrehydro / 2.0, W, W);	/*W is normal to U&V and of diametrehydro length*/
			for (zj=1;zj<=20;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext1[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext1[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);	/*front circle*/
				}
			for (zj=11;zj<=20;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext2[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y4 = ext2[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);	/*generatrice*/
				x3 = ext2[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext2[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext2[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext2[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);	/*back circle*/
				/*printf("zj %d xy %lf %lf %lf %lf\n",zj,x3,y3,x4,y4);*/
				}
			}
			
		}
	for (pa=1;pa<=Structure.nb_sphere_element;pa++)
		{ 
		type = Sphere_element.element[pa];
		if (TypeElement[type].flag_dessin != 0)
			{
			nb = Sphere_element.nb[pa];
			/*if (Structure.symetry == 1) nb = 2 * nb;	symetry x*/
			/*if (Structure.symetry == 2) nb = 2 * nb;	symetry y*/
			/*if (Structure.symetry == 4) nb = 2 * nb;	symetry z*/
			/*if (Structure.symetry == 3) nb = 4 * nb;	symetry xy*/
			/*if (Structure.symetry == 5) nb = 4 * nb;	symetry xz*/
			/*if (Structure.symetry == 6) nb = 4 * nb;	symetry yz*/
			/*if (Structure.symetry == 7) nb = 4 * nb;	symetry xyz*/
			diam = Sphere_element.diameter[pa];

			/*
			printf("type %d  ",type);
			printf("nb %d diam %lf\n",nb,diam);
			*/
			for (zk=1;zk<=nb;zk++)
				{
				ratio = 1.0 / 2 / nb + 2.0 / 2 / nb * (zk-1);
				/*
				printf("zk %d ratio %lf \n",zk,ratio);
				*/
				for (zl=1;zl<=NOMBRE_ELEMENTS;zl++)
					{
					if (Element[zl].type == type)
						{
						if ((Element[zl].pro[1]-ratio)*(Element[zl].pro[2]-ratio) <=0.0)
						
							{
							/*
							printf("zl %d  ",zl);
							printf("Element[zl].pro[1] %lf Element[zl].pro[2] %lf\n",Element[zl].pro[1],Element[zl].pro[2]);
							*/				
							ratio_local = (ratio - Element[zl].pro[1]) / (Element[zl].pro[2] - Element[zl].pro[1]);
							deb = Element[zl].extremite[1];
							fin = Element[zl].extremite[2];
						
							ext1[1] = (REEL) Noeud[deb].x;			ext1[2] = (REEL) Noeud[deb].y;
							ext2[1] = (REEL) Noeud[fin].x;			ext2[2] = (REEL) Noeud[fin].y;
						
							x3 = ext1[1] + ratio_local * (ext2[1] -ext1[1]);
							y3 = ext1[2] + ratio_local * (ext2[2] -ext1[2]);
							for (zj=1;zj<=20;zj++)
								{
								x4 = x3 + diam / 2 * cos((zj -1)*2*PI/20);	y4 = y3 + diam / 2 * sin((zj -1)*2*PI/20);
								x5 = x3 + diam / 2 * cos((zj -0)*2*PI/20);	y5 = y3 + diam / 2 * sin((zj -0)*2*PI/20);
								draw_segment_color(TypeElement[type].flag_dessin, x4,y4,x5,y5);
								}
							}
						}
					}
				}
			}
		}

	}
	
	

void dessiner_contour_element3()
	{
	int ba,pa,deb,fin,no,np,pt1,pt2,pt3,interne,um,vm,minu,maxu,minv,maxv,nb_twine,color;
	float a1,a2,b1,b2,ru,rv,denom,vect_ux,vect_uy,vect_vx,vect_vy;
	float u1,u2,u3,v1,v2,v3,x01,x02,x03,y01,y02,y03,xm,ym,u12,u23,u31,ua,ub,uc;
	int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
	void trace_fil_hexa(float a1, float b1, float a2, float b2, float x01, float y01, float x02, float y02, float x03, float y03);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	float extr1[4],extr2[4];
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;



	int elem,nb,zi,zj,zk,type,zl;
	double diam,x3,x4,x5,x6,y3,y4,y5,y6,pas_x,pas_y,ratio,ratio_local,U[4],V[4],W[4],norm;
	double ext1[4],ext2[4];



	
	/*printf("NOMBRE_SURFACES = %8d NOMBRE_ELEMENTS = %8d   \n",NOMBRE_SURFACES,NOMBRE_ELEMENTS);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if (pa == 0) printf("attention : pa = %8d no = %8d   \n",pa,no);
		if ((pa > 0) && (pa <= NOMBRE_SURFACES))
			{
			/*printf("pa = %8d panel %d color = %8d   \n",pa,Surface[pa].type,panneau[Surface[pa].type].flag_dessin);*/
			color = panneau[Surface[pa].type].flag_dessin;
			if (color != 0)
				{
				pt1 = Surface[pa].extremite[1];
				pt2 = Surface[pa].extremite[2];
				pt3 = Surface[pa].extremite[3];
			
				if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
					{
					/*EffaceTriangle(gris_externe, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);*/
					EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
					}	
				else	
					{
					EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
					}

				/*u twines*/		
				u1 = ((float) Surface[pa].lon[2] + (float) Surface[pa].lon[1]) / periode_fils; 	
				u2 = ((float) Surface[pa].lon[4] + (float) Surface[pa].lon[3]) / periode_fils; 	
				u3 = ((float) Surface[pa].lon[6] + (float) Surface[pa].lon[5]) / periode_fils;
				/*V1 = (float) Surface[pa].lon[2] - (float) Surface[pa].lon[1];*/
				/*V2 = (float) Surface[pa].lon[4] - (float) Surface[pa].lon[3];*/
				/*V3 = (float) Surface[pa].lon[6] - (float) Surface[pa].lon[5];*/			
				/*printf("u123 %8.2f %8.2f %8.2f \n",u1,u2,u3);*/

				u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
				if ((u12 >= u23) && (u12 >= u31))
					{
					/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
					ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
					ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
					uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;			
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
					ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
					ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
					uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				if ((u23 >= u31) && (u23 >= u12))
					{
					/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
					ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
					ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
					uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
					ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
					ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
					uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				if ((u31 >= u12) && (u31 >= u23))
					{
					/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
					ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
					ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
					uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
					ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
					ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
					uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				
				/*v twines*/		
				/*u1 = (float) Surface[pa].lon[2] + (float) Surface[pa].lon[1];*/ 	
				/*u2 = (float) Surface[pa].lon[4] + (float) Surface[pa].lon[3];*/ 	
				/*u3 = (float) Surface[pa].lon[6] + (float) Surface[pa].lon[5];*/
				u1 = ((float) Surface[pa].lon[2] - (float) Surface[pa].lon[1]) / periode_fils;
				u2 = ((float) Surface[pa].lon[4] - (float) Surface[pa].lon[3]) / periode_fils;
				u3 = ((float) Surface[pa].lon[6] - (float) Surface[pa].lon[5]) / periode_fils;		
				u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
				/*printf("u123 %8.2f %8.2f %8.2f \n",u1,u2,u3);*/
				if ((u12 >= u23) && (u12 >= u31))
					{
					/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
					ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
					ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
					uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
					ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
					ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
					uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				if ((u23 >= u31) && (u23 >= u12))
					{
					/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
					ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
					ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
					uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
					ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
					ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
					uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				if ((u31 >= u12) && (u31 >= u23))
					{
					/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
					ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
					ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
					uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
					ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
					ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
					uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}

				if (GetMenuItemChecked(w[10]))
					{
					TraceSegment(BLACK, (double) Noeud[pt1].x, (double) Noeud[pt1].y, (double) Noeud[pt2].x, (double) Noeud[pt2].y);
					TraceSegment(BLACK, (double) Noeud[pt2].x, (double) Noeud[pt2].y, (double) Noeud[pt3].x, (double) Noeud[pt3].y);
					TraceSegment(BLACK, (double) Noeud[pt3].x, (double) Noeud[pt3].y, (double) Noeud[pt1].x, (double) Noeud[pt1].y);
					}
				}
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA))
			{
			pa = pa - NOMBRE_SURFACES;
			if (TypeSurfHexa[Surf_Hexa[pa].type].flag_dessin != 0)
				{
			/*if (pa > 0)*/
			if (pa > 0)
			{
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
			
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			/**/
			
			x01 = (REEL) (Noeud[pt1].x - binx) / (baxx - binx);
			x02 = (REEL) (Noeud[pt2].x - binx) / (baxx - binx);
			x03 = (REEL) (Noeud[pt3].x - binx) / (baxx - binx);
			y01 = (REEL) (Noeud[pt1].y - biny) / (baxy - biny);
			y02 = (REEL) (Noeud[pt2].y - biny) / (baxy - biny);
			y03 = (REEL) (Noeud[pt3].y - biny) / (baxy - biny);
			
			interne = interieur_triangle((double) x01,(double) x02,(double) x03,(double) y01,(double) y02,(double) y03);
			if (interne == 1)
				{
			
			/*
			if (Surf_Hexa[pa].orientation*((x02-x01)*(y03-y02)-(y02-y01)*(x03-x02)) >= 0.0)	SetColor(gris_interne);
			else	SetColor(gris_externe);
			*/
			
			if (ARTICLE_HEXA_2001 == 0)
				{
				/*triangle*/
				Color(WHITE);
				Move_to(x01,y01);
				Line_to(x02,y02);
				Line_to(x03,y03);
				Line_to(x01,y01);
				Surface_end();
				Color(BLUE);
				Color(BLACK);
				}
			else
				{
				Color(BLACK);
				Color(BLUE);
				}
			
			/*SetColor(Surf_Hexa[pa].color_v);*/
		u1 = Surf_Hexa[pa].lon[1]; v1 = Surf_Hexa[pa].lon[2];
		u2 = Surf_Hexa[pa].lon[3]; v2 = Surf_Hexa[pa].lon[4];
		u3 = Surf_Hexa[pa].lon[5]; v3 = Surf_Hexa[pa].lon[6];
		u1 = (float) Surf_Hexa[pa].lon[1] / periode_fils; v1 = (float) Surf_Hexa[pa].lon[2] / periode_fils;
		u2 = (float) Surf_Hexa[pa].lon[3] / periode_fils; v2 = (float) Surf_Hexa[pa].lon[4] / periode_fils;
		u3 = (float) Surf_Hexa[pa].lon[5] / periode_fils; v3 = (float) Surf_Hexa[pa].lon[6] / periode_fils;
		/*
		*/
		x01 = Noeud[pt1].x;	y01 = Noeud[pt1].y;
		x02 = Noeud[pt2].x;	y02 = Noeud[pt2].y;
		x03 = Noeud[pt3].x;	y03 = Noeud[pt3].y;
	       	denom = (u3-u1)*(v2-v1) - (u2-u1)*(v3-v1);
	       	/* precautions en cas de denominateur nul*/
	       	if (fabs(denom) <= 0.00001)
	               	{  
	        	printf(" * noeud_panneau * denom = %f\n",denom); 
	               	} 
	       	/*calcul des vecteur elementaires cartesiens de cote de maille vect_u et vect_v*/
	       	ru = u1+1.0;
	       	rv = v1+0.0;
	     	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
	     	betaa  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;
	       	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
	       	vect_ux = alpha * ( x02 - x01 )+ betaa * ( x03 - x01 );
	       	vect_uy = alpha * ( y02 - y01 )+ betaa * ( y03 - y01 );
	       	ru = u1+0.0;
	       	rv = v1+1.0;
	     	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
	     	betaa  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;
	       	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
	       	vect_vx = alpha * ( x02 - x01 )+ betaa * ( x03 - x01 );
	       	vect_vy = alpha * ( y02 - y01 )+ betaa * ( y03 - y01 );
		minu = (int) floor(u1);		maxu = (int) ceil(u1);
		minv = (int) floor(v1);		maxv = (int) ceil(v1);
		if (minu>u2) minu = (int) floor(u2);  if (maxu<u2) maxu = (int) ceil(u2);
		if (minu>u3) minu = (int) floor(u3);  if (maxu<u3) maxu = (int) ceil(u3);
		if (minv>v2) minv = (int) floor(v2);  if (maxv<v2) maxv = (int) ceil(v2);
		if (minv>v3) minv = (int) floor(v3);  if (maxv<v3) maxv = (int) ceil(v3);
		/*printf("minu = %d maxu = %d minv = %d maxv = %d \n",minu,maxu,minv,maxv); */
		/*for (um=minu;um<=minu;um++)*/
		for (um=minu;um<=maxu;um++)
			{ 
			/*for (vm=minv;vm<=maxv;vm++)*/
			for (vm=minv;vm<=maxv;vm++)
				{
				/*printf("um   : %8d ,vm  :  %8d ",um,vm);*/
	       			/* determination des coefficients alpha01 et betaa definis tels que 1m = alpha01*12 + betaa*13 */
	     			alpha =   ( (vm-v1)*(u3-u1) - (um-u1)*(v3-v1) ) / denom;
	     			betaa  =   ( (um-u1)*(v2-v1) - (vm-v1)*(u2-u1) ) / denom;
	         		/*printf("alpha01= %f,betaa = %f ",alpha01,betaa);*/
	       			/* determination des coordonnees cartesiennes de l origine de la maille proche d une position d equilibre */
	       			xm = alpha * ( x02 - x01 )+ betaa * ( x03 - x01 ) + x01;
	       			ym = alpha * ( y02 - y01 )+ betaa * ( y03 - y01 ) + y01;
	         		/*trace des 6 fils a l interieur d une maille*/
	         		/*
				Line(((REEL) xm-0.08-binx) / (baxx-binx),((REEL) ym-biny) / (baxy-biny),((REEL) xm+0.08-binx) / (baxx-binx),((REEL) ym-biny) / (baxy-biny));
				Line(((REEL) xm-binx) / (baxx-binx),((REEL) ym-0.08-biny) / (baxy-biny),((REEL) xm-binx) / (baxx-binx),((REEL) ym+0.08-biny) / (baxy-biny));
				*/
				a1 = xm +vect_ux*1.0/6.0 +vect_vx*1.0/2.0;
				b1 = ym +vect_uy*1.0/6.0 +vect_vy*1.0/2.0;
				a2 = xm +vect_ux*0.0/6.0 +vect_vx*0.0/2.0;
				b2 = ym +vect_uy*0.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);

				a2 = xm +vect_ux*0.0/6.0 +vect_vx*2.0/2.0;
				b2 = ym +vect_uy*0.0/6.0 +vect_vy*2.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a2 = xm +vect_ux*3.0/6.0 +vect_vx*1.0/2.0;
				b2 = ym +vect_uy*3.0/6.0 +vect_vy*1.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a1 = xm +vect_ux*4.0/6.0 +vect_vx*2.0/2.0;
				b1 = ym +vect_uy*4.0/6.0 +vect_vy*2.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a1 = xm +vect_ux*4.0/6.0 +vect_vx*0.0/2.0;
				b1 = ym +vect_uy*4.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a2 = xm +vect_ux*6.0/6.0 +vect_vx*0.0/2.0;
				b2 = ym +vect_uy*6.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				}
			}
				}
			}
			}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
/******************************************************************************************************************/			
			if (TypeElement[Element[pa].type].flag_dessin != 0)
				{
				/*printf("element %d    ",pa);*/
				deb = Element[pa].extremite[1];	fin = Element[pa].extremite[2];
				ext1[1] = Noeud[deb].x;		ext1[2] = Noeud[deb].y;		ext1[3] = Noeud[deb].z;
				ext2[1] = Noeud[fin].x;		ext2[2] = Noeud[fin].y;		ext2[3] = Noeud[fin].z;
				if (Noeud[deb].z > Noeud[fin].z)
					{
					ext1[1] = Noeud[deb].x;		ext1[2] = Noeud[deb].y;		ext1[3] = Noeud[deb].z;		/*element extremity closer to the eye*/
					ext2[1] = Noeud[fin].x;		ext2[2] = Noeud[fin].y;		ext2[3] = Noeud[fin].z;
					}
				else
					{
					ext1[1] = Noeud[fin].x;		ext1[2] = Noeud[fin].y;		ext1[3] = Noeud[fin].z;		/*element extremity closer to the eye*/
					ext2[1] = Noeud[deb].x;		ext2[2] = Noeud[deb].y;		ext2[3] = Noeud[deb].z;
					}
				U[1] = ext2[1]-ext1[1];			U[2] = ext2[2]-ext1[2];		U[3] = ext2[3]-ext1[3]; 	/*U vector is the element vector*/
				/*printf("U %lf %lf %lf\n",U[1],U[2],U[3]);*/
				norm = sqrt(produit_scal_double(U,U));		/*length of side U*/
				/*printf("normU %lf ",norm);*/

				produit_scal_vect_double(1.0/norm, U, U);	/*U vector is the normalized element vector*/
				/*norm = sqrt(produit_scal_double(U,U));*/		/*length of side U*/
				/*printf("normU %lf ",norm);*/			/*printf("Un %lf %lf %lf\n",U[1],U[2],U[3]);*/
				
				W[1] = 0.0;	W[2] = 0.0;	W[3] = 1.0; 	/*W vector is normalized and normal to XoY*/
				/*norm = sqrt(produit_scal_double(W,W));*/		/*length of side U*/
				/*printf("normW %lf  ",norm);*/
				
				produit_vect3_double(U, W, V);			/*V is normal to U & W*/
				norm = sqrt(produit_scal_double(V,V));		/*length of side U*/
				/*printf("normV %lf  ",norm);*/
				produit_scal_vect_double(1.0/norm, V, V);	/*U vector is the normalized element vector*/
				/*norm = sqrt(produit_scal_double(V,V));*/		/*length of side U*/
				/*printf("normV %lf  ",norm);*/
				
				produit_vect3_double(U, V, W);			/*W is normal to U & V*/	
				norm = sqrt(produit_scal_double(W,W));		/*length of side U*/
				/*printf("normW %lf  ",norm);*/
				produit_scal_vect_double(1.0/norm, W, W);	/*U vector is the normalized element vector*/
				/*norm = sqrt(produit_scal_double(W,W));*/		/*length of side U*/
				/*printf("normV %lf  \n",norm);*/
		
				produit_scal_vect_double(Element[pa].diametrehydro / 2.0, V, V);	/*V is normal to U and of diametrehydro length*/
				produit_scal_vect_double(Element[pa].diametrehydro / 2.0, W, W);	/*W is normal to U&V and of diametrehydro length*/
				for (zj=1;zj<=20;zj++)
					{
					alpha = (zj -1)*2*PI/20;
					betaa  = (zj -0)*2*PI/20;
					x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
					x4 = ext1[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext1[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
					draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);	/*front circle*/
					}
				for (zj=11;zj<=20;zj++)
					{
					alpha = (zj -1)*2*PI/20;
					betaa  = (zj -0)*2*PI/20;
					x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
					x4 = ext2[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y4 = ext2[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
					draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);	/*generatrice*/
					x3 = ext2[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext2[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
					x4 = ext2[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext2[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
					draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);	/*back circle*/
					/*printf("zj %d xy %lf %lf %lf %lf\n",zj,x3,y3,x4,y4);*/
					}
				}
				
			}
		for (pa=1;pa<=Structure.nb_sphere_element;pa++)
			{ 
			type = Sphere_element.element[pa];
			if (TypeElement[type].flag_dessin != 0)
				{
				nb = Sphere_element.nb[pa];
				/*if (Structure.symetry == 1) nb = 2 * nb;	symetry x*/
				/*if (Structure.symetry == 2) nb = 2 * nb;	symetry y*/
				/*if (Structure.symetry == 4) nb = 2 * nb;	symetry z*/
				/*if (Structure.symetry == 3) nb = 4 * nb;	symetry xy*/
				/*if (Structure.symetry == 5) nb = 4 * nb;	symetry xz*/
				/*if (Structure.symetry == 6) nb = 4 * nb;	symetry yz*/
				/*if (Structure.symetry == 7) nb = 4 * nb;	symetry xyz*/
				diam = Sphere_element.diameter[pa];

				/*
				printf("type %d  ",type);
				printf("nb %d diam %lf\n",nb,diam);
				*/
				for (zk=1;zk<=nb;zk++)
					{
					ratio = 1.0 / 2 / nb + 2.0 / 2 / nb * (zk-1);
					/*
					printf("zk %d ratio %lf \n",zk,ratio);
					*/
					for (zl=1;zl<=NOMBRE_ELEMENTS;zl++)
						{
						if (Element[zl].type == type)
							{
							if ((Element[zl].pro[1]-ratio)*(Element[zl].pro[2]-ratio) <=0.0)
							
								{
								/*
								printf("zl %d  ",zl);
								printf("Element[zl].pro[1] %lf Element[zl].pro[2] %lf\n",Element[zl].pro[1],Element[zl].pro[2]);
								*/				
								ratio_local = (ratio - Element[zl].pro[1]) / (Element[zl].pro[2] - Element[zl].pro[1]);
								deb = Element[zl].extremite[1];
								fin = Element[zl].extremite[2];
							
								ext1[1] = (REEL) Noeud[deb].x;			ext1[2] = (REEL) Noeud[deb].y;
								ext2[1] = (REEL) Noeud[fin].x;			ext2[2] = (REEL) Noeud[fin].y;
							
								x3 = ext1[1] + ratio_local * (ext2[1] -ext1[1]);
								y3 = ext1[2] + ratio_local * (ext2[2] -ext1[2]);
								for (zj=1;zj<=20;zj++)
									{
									x4 = x3 + diam / 2 * cos((zj -1)*2*PI/20);	y4 = y3 + diam / 2 * sin((zj -1)*2*PI/20);
									x5 = x3 + diam / 2 * cos((zj -0)*2*PI/20);	y5 = y3 + diam / 2 * sin((zj -0)*2*PI/20);
									draw_segment_color(TypeElement[type].flag_dessin, x4,y4,x5,y5);
									}
								}
							}
						}
					}
				}
/******************************************************************************************************************/			
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			if (Coulisse[pa].flag_dessin != 0)
				{
				for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
					{
					if (ba == 1)	deb = Coulisse[pa].extremite[1];
					if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
					if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
					if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
					TraceSegment(Coulisse[pa].flag_dessin, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
					}
				}
			}
		}
	}
	

void draw_contour_element3(int pa)
	{
	int ba,deb,fin,no,np,pt1,pt2,pt3,interne,um,vm,minu,maxu,minv,maxv,nb_twine,color,gris_interne,condition_draw_contour_element3,flag_draw_contour_element3;
	float a1,a2,b1,b2,ru,rv,denom,vect_ux,vect_uy,vect_vx,vect_vy;
	float u1,u2,u3,v1,v2,v3,x01,x02,x03,y01,y02,y03,xm,ym,u12,u23,u31,ua,ub,uc;
	int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
	void trace_fil_hexa(float a1, float b1, float a2, float b2, float x01, float y01, float x02, float y02, float x03, float y03);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	float extr1[4],extr2[4];
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;

	int elem,nb,zi,zj,zk,type,zl;
	double diam,x1,x2,x3,x4,x5,x6,y1,y2,y3,y4,y5,y6,pas_x,pas_y,ratio,ratio_local,U[4],V[4],W[4],norm;
	double ext1[4],ext2[4];
	int panel;
	double period,diameter;

	//printf("draw_contour_element3 pa %4d\n",pa);

   	/*for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
    		{
	    	printf("element %d extr1 %lf %lf %lf \n",zi,Noeud[Element[zi].extremite[1]].x,Noeud[Element[zi].extremite[1]].y,Noeud[Element[zi].extremite[1]].z);
 	    	printf("element %d extr2 %lf %lf %lf \n",zi,Noeud[Element[zi].extremite[2]].x,Noeud[Element[zi].extremite[2]].y,Noeud[Element[zi].extremite[2]].z);
     		}*/




	
	deb = Element[pa].extremite[1];	fin = Element[pa].extremite[2];
	ext1[1] = Noeud[deb].x;		ext1[2] = Noeud[deb].y;		ext1[3] = Noeud[deb].z;
	ext2[1] = Noeud[fin].x;		ext2[2] = Noeud[fin].y;		ext2[3] = Noeud[fin].z;
	if (Noeud[deb].z > Noeud[fin].z)
		{
		ext1[1] = Noeud[deb].x;		ext1[2] = Noeud[deb].y;		ext1[3] = Noeud[deb].z;		/*element extremity closer to the eye*/
		ext2[1] = Noeud[fin].x;		ext2[2] = Noeud[fin].y;		ext2[3] = Noeud[fin].z;
		}
	else
		{
		ext1[1] = Noeud[fin].x;		ext1[2] = Noeud[fin].y;		ext1[3] = Noeud[fin].z;		/*element extremity closer to the eye*/
		ext2[1] = Noeud[deb].x;		ext2[2] = Noeud[deb].y;		ext2[3] = Noeud[deb].z;
		}
 	U[1] = ext2[1]-ext1[1];			U[2] = ext2[2]-ext1[2];		U[3] = ext2[3]-ext1[3]; 	/*U vector is the element vector*/
	/*printf("U %lf %lf %lf\n",U[1],U[2],U[3]);*/
	norm = sqrt(produit_scal_double(U,U));		/*length of side U*/
	/*printf("normU %lf ",norm);*/

	produit_scal_vect_double(1.0/norm, U, U);	/*U vector is the normalized element vector*/
	/*norm = sqrt(produit_scal_double(U,U));*/		/*length of side U*/
	/*printf("normU %lf ",norm);*/			/*printf("Un %lf %lf %lf\n",U[1],U[2],U[3]);*/

	W[1] = 0.0;	W[2] = 0.0;	W[3] = 1.0; 	/*W vector is normalized and normal to XoY*/
	/*norm = sqrt(produit_scal_double(W,W));*/		/*length of side U*/
	/*printf("normW %lf  ",norm);*/

	produit_vect3_double(U, W, V);			/*V is normal to U & W*/
	norm = sqrt(produit_scal_double(V,V));		/*length of side U*/
	/*printf("normV %lf  ",norm);*/
	produit_scal_vect_double(1.0/norm, V, V);	/*V vector is the normalized element vector*/
	/*norm = sqrt(produit_scal_double(V,V));*/		/*length of side V*/
	/*printf("normV %lf  ",norm);*/

	produit_vect3_double(U, V, W);			/*W is normal to U & V*/	
	norm = sqrt(produit_scal_double(W,W));		/*length of side W*/
	/*printf("normW %lf  ",norm);*/
	produit_scal_vect_double(1.0/norm, W, W);	/*W vector is the normalized element vector*/
	/*norm = sqrt(produit_scal_double(W,W));*/		/*length of side W*/
	/*printf("normW %lf  \n",norm);*/

	if(Element[pa].type > 0)
		{
		produit_scal_vect_double(Element[pa].diametrehydro / 2.0, V, V);	/*V is normal to U and of diametrehydro length*/
		produit_scal_vect_double(Element[pa].diametrehydro / 2.0, W, W);	/*W is normal to U&V and of diametrehydro length*/
		}
	else
		{
		panel = -Element[pa].type;
		period = (double) panneau[panel].netting_2_ropes_period;
		diameter = panneau[panel].diam_hydro * sqrt(period);

		produit_scal_vect_double(diameter / 2.0, V, V);	/*V is normal to U and of diametrehydro length*/
		produit_scal_vect_double(diameter / 2.0, W, W);	/*W is normal to U&V and of diametrehydro length*/

		}
	
	condition_draw_contour_element3 = 0;	//not draw
	if(Element[pa].type > 0)
		{
		//the bar belongs to a cable
		if ((TypeElement[Element[pa].type].flag_dessin != 0) && (Element[pa].flag_dessin != 0))
			{	
			condition_draw_contour_element3 = 1;	//draw
			flag_draw_contour_element3 = Element[pa].flag_dessin;
			}
		}
	else
		{
		//the bar belongs to a panel
		if (panneau[-Element[pa].type].flag_dessin != 0)
			{	
			condition_draw_contour_element3 = 1;	//draw
			flag_draw_contour_element3 = panneau[-Element[pa].type].flag_dessin;
			}
		}

	if (condition_draw_contour_element3 == 1)
		{
		if (TypeElement[Element[pa].type].flag_dessin == -1)
			{
			//printf("pa %4d Element[pa].type %4d typeflag %4d \n",pa,Element[pa].type,TypeElement[Element[pa].type].flag_dessin);
			/*	
			for (zj = 1; zj<= NOMBRE_ELEMENTS; zj++)
				{
				//draw_segment_color(Element[zj].flag_dessin
				deb = Element[zj].extremite[1];
				fin = Element[zj].extremite[2];
				draw_segment_color(flag_draw_contour_element3, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			*/
			for (zj=1;zj<=20;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext1[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext1[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				EffaceTriangle(WHITE, ext1[1], ext1[2], x3, y3, x4, y4);
				draw_segment_color(flag_draw_contour_element3, x3, y3, x4, y4);	/*front circle*/
				}
			for (zj=11;zj<=21;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext2[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y4 = ext2[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x1 = ext1[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y1 = ext1[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				x2 = ext2[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y2 = ext2[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				EffaceQuadrangle(WHITE, x1, y1, x2, y2, x4, y4, x3, y3);
				draw_segment_color(flag_draw_contour_element3, x3, y3, x4, y4);	/*generatrice*/
				draw_segment_color(flag_draw_contour_element3, x1, y1, x2, y2);	/*generatrice*/
				}
			for (zj=1;zj<=20;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext1[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext1[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				EffaceTriangle(WHITE, ext1[1], ext1[2], x3, y3, x4, y4);
				draw_segment_color(flag_draw_contour_element3, x3, y3, x4, y4);	/*front circle*/
				}
			for (zj=11;zj<=20;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext2[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext2[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext2[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext2[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				draw_segment_color(flag_draw_contour_element3, x3, y3, x4, y4);	/*back circle*/
				/*printf("zj %d xy %lf %lf %lf %lf\n",zj,x3,y3,x4,y4);*/
				}
			}
		else
			{
			//printf("pb %4d flag_draw_contour_element3 %4d \n",pa,flag_draw_contour_element3);
	 		//printf("ext1xyz %lf %lf %lf ",ext1[1],ext1[2],ext1[3]);
	 		//printf("ext2xyz %lf %lf %lf \n",ext2[1],ext2[2],ext2[3]);
			//draw_segment_color(1, ext1[1],ext1[2], ext2[1],ext2[2]);	/*black*/
			for (zj=1;zj<=20;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext1[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext1[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				EffaceTriangle(WHITE, ext1[1], ext1[2], x3, y3, x4, y4);
				draw_segment_color(flag_draw_contour_element3, x3, y3, x4, y4);	/*front circle*/
				}
			for (zj=11;zj<=21;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext2[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y4 = ext2[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x1 = ext1[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y1 = ext1[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				x2 = ext2[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y2 = ext2[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				EffaceQuadrangle(WHITE, x1, y1, x2, y2, x4, y4, x3, y3);
				draw_segment_color(flag_draw_contour_element3, x3, y3, x4, y4);	/*generatrice*/
				draw_segment_color(flag_draw_contour_element3, x1, y1, x2, y2);	/*generatrice*/
				}
			for (zj=1;zj<=20;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext1[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext1[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext1[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext1[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				EffaceTriangle(WHITE, ext1[1], ext1[2], x3, y3, x4, y4);
				draw_segment_color(flag_draw_contour_element3, x3, y3, x4, y4);	/*front circle*/
				}
			for (zj=11;zj<=20;zj++)
				{
				alpha = (zj -1)*2*PI/20;
				betaa  = (zj -0)*2*PI/20;
				x3 = ext2[1] + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = ext2[2] + cos(alpha) * V[2] + sin(alpha) * W[2];
				x4 = ext2[1] + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = ext2[2] + cos( betaa) * V[2] + sin( betaa) * W[2];
				draw_segment_color(flag_draw_contour_element3, x3, y3, x4, y4);	/*back circle*/
				/*printf("zj %d xy %lf %lf %lf %lf\n",zj,x3,y3,x4,y4);*/
				}
			}
		}
	for (zi=1;zi<=Structure.nb_sphere_element;zi++)
		{ 
		type = Sphere_element.element[zi];
		if (Element[pa].type == type)
			{
			nb = Sphere_element.nb[zi];
			diam = Sphere_element.diameter[zi];
			for (zk=1;zk<=nb;zk++)
				{
				ratio = 1.0 / 2 / nb + 2.0 / 2 / nb * (zk-1);
				if ((Element[pa].pro[1]-ratio)*(Element[pa].pro[2]-ratio) <=0.0)
					{
					ratio_local = (ratio - Element[pa].pro[1]) / (Element[pa].pro[2] - Element[pa].pro[1]);
					deb = Element[pa].extremite[1];
					fin = Element[pa].extremite[2];
				
					ext1[1] = (REEL) Noeud[deb].x;			ext1[2] = (REEL) Noeud[deb].y;
					ext2[1] = (REEL) Noeud[fin].x;			ext2[2] = (REEL) Noeud[fin].y;
				
					x3 = ext1[1] + ratio_local * (ext2[1] -ext1[1]);
					y3 = ext1[2] + ratio_local * (ext2[2] -ext1[2]);
					for (zj=1;zj<=20;zj++)
						{
						x4 = x3 + diam / 2 * cos((zj -1)*2*PI/20);	y4 = y3 + diam / 2 * sin((zj -1)*2*PI/20);
						x5 = x3 + diam / 2 * cos((zj -0)*2*PI/20);	y5 = y3 + diam / 2 * sin((zj -0)*2*PI/20);
						/* debut modifdp du 15 mars 2010*/
						EffaceTriangle(WHITE, x3, y3, x4, y4, x5, y5);
						/* fin modifdp du 15 mars 2010*/
						draw_segment_color(TypeElement[type].flag_dessin, x4,y4,x5,y5);
						}
					}
				}
			}
		}
	}
	
void draw_contour_noeud(int pa)
	{
	double vect1[4];
	double vect2[4];
	double vect3[4];


	vect1[1]=Noeud[pa].sx;		vect1[2]=0;			vect1[3]=0;
	vect2[1]=0;			vect2[2]=Noeud[pa].sy;		vect2[3]=0;
	vect3[1]=0;			vect3[2]=0;			vect3[3]=Noeud[pa].sz;

	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);


	double x1 = Noeud[pa].x + vect1[1]/2 - vect2[1]/2;
	double y1 = Noeud[pa].y + vect1[2]/2 - vect2[2]/2;
	double z1 = Noeud[pa].z + vect1[3]/2 - vect2[3]/2;

	double x2 = Noeud[pa].x + vect1[1]/2 + vect2[1]/2;
	double y2 = Noeud[pa].y + vect1[2]/2 + vect2[2]/2;
	double z2 = Noeud[pa].z + vect1[3]/2 + vect2[3]/2;

	double x3 = Noeud[pa].x - vect1[1]/2 + vect2[1]/2;
	double y3 = Noeud[pa].y - vect1[2]/2 + vect2[2]/2;
	double z3 = Noeud[pa].z - vect1[3]/2 + vect2[3]/2;

	double x4 = Noeud[pa].x - vect1[1]/2 - vect2[1]/2;
	double y4 = Noeud[pa].y - vect1[2]/2 - vect2[2]/2;
	double z4 = Noeud[pa].z - vect1[3]/2 - vect2[3]/2;

	double x5 = Noeud[pa].x + vect1[1]/2 - vect2[1]/2 +vect3[1];
	double y5 = Noeud[pa].y + vect1[2]/2 - vect2[2]/2 +vect3[2];
	double z5 = Noeud[pa].z + vect1[3]/2 - vect2[3]/2 +vect3[3];

	double x6 = Noeud[pa].x + vect1[1]/2 + vect2[1]/2 +vect3[1];
	double y6 = Noeud[pa].y + vect1[2]/2 + vect2[2]/2 +vect3[2];
	double z6 = Noeud[pa].z + vect1[3]/2 + vect2[3]/2 +vect3[3];

	double x7 = Noeud[pa].x - vect1[1]/2 + vect2[1]/2 +vect3[1];
	double y7 = Noeud[pa].y - vect1[2]/2 + vect2[2]/2 +vect3[2];
	double z7 = Noeud[pa].z - vect1[3]/2 + vect2[3]/2 +vect3[3];

	double x8 = Noeud[pa].x - vect1[1]/2 - vect2[1]/2 +vect3[1];
	double y8 = Noeud[pa].y - vect1[2]/2 - vect2[2]/2 +vect3[2];
	double z8 = Noeud[pa].z - vect1[3]/2 - vect2[3]/2 +vect3[3];

	/*
	printf("x1 : %lf  y1 : %lf \n",x1,y1);
	printf("xx1 : %lf  yy1 : %lf \n",xx1,yy1);
	TraceSegment(BLACK,x1,y1,x2,y2);
	TraceSegment(BLACK,x2,y2,x3,y3);
	TraceSegment(BLACK,x3,y3,x4,y4);
	TraceSegment(BLACK,x4,y4,x1,y1);

	TraceSegment(BLACK,x1,y1,x5,y5);
	TraceSegment(BLACK,x2,y2,x6,y6);
	TraceSegment(BLACK,x3,y3,x7,y7);
	TraceSegment(BLACK,x4,y4,x8,y8);

	TraceSegment(BLACK,x5,y5,x6,y6);
	TraceSegment(BLACK,x6,y6,x7,y7);
	TraceSegment(BLACK,x7,y7,x8,y8);
	TraceSegment(BLACK,x8,y8,x5,y5);
	*/
	if ((z1 >= z2) && (z1 >= z3) && (z1 >= z4) && (z1 >= z5) && (z1 >= z6) && (z1 >= z7) && (z1 >= z8))
		{
		EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
		EffaceQuadrangle(WHITE, x1, y1, x2, y2, x6, y6, x5, y5);
		EffaceQuadrangle(WHITE, x1, y1, x5, y5, x8, y8, x4, y4);
		TraceSegment(BLACK,x1,y1,x2,y2);
		TraceSegment(BLACK,x2,y2,x3,y3);
		TraceSegment(BLACK,x3,y3,x4,y4);
		TraceSegment(BLACK,x4,y4,x1,y1);
		TraceSegment(BLACK,x2,y2,x6,y6);
		TraceSegment(BLACK,x1,y1,x5,y5);
		TraceSegment(BLACK,x4,y4,x8,y8);
		TraceSegment(BLACK,x5,y5,x6,y6);
		TraceSegment(BLACK,x8,y8,x5,y5);
		}
	if ((z2 >= z1) && (z2 >= z3) && (z2 >= z4) && (z2 >= z5) && (z2 >= z6) && (z2 >= z7) && (z2 >= z8))
		{
		EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
		EffaceQuadrangle(WHITE, x2, y2, x3, y3, x7, y7, x6, y6);
		EffaceQuadrangle(WHITE, x2, y2, x6, y6, x5, y5, x1, y1);
		TraceSegment(BLACK,x1,y1,x2,y2);
		TraceSegment(BLACK,x2,y2,x3,y3);
		TraceSegment(BLACK,x3,y3,x4,y4);
		TraceSegment(BLACK,x4,y4,x1,y1);
		TraceSegment(BLACK,x1,y1,x5,y5);
		TraceSegment(BLACK,x2,y2,x6,y6);
		TraceSegment(BLACK,x3,y3,x7,y7);
		TraceSegment(BLACK,x5,y5,x6,y6);
		TraceSegment(BLACK,x6,y6,x7,y7);
		}
	if ((z3 >= z1) && (z3 >= z2) && (z3 >= z4) && (z3 >= z5) && (z3 >= z6) && (z3 >= z7) && (z3 >= z8))
		{
		EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
		EffaceQuadrangle(WHITE, x3, y3, x7, y7, x8, y8, x4, y4);
		EffaceQuadrangle(WHITE, x3, y3, x2, y2, x6, y6, x7, y7);
		TraceSegment(BLACK,x1,y1,x2,y2);
		TraceSegment(BLACK,x2,y2,x3,y3);
		TraceSegment(BLACK,x3,y3,x4,y4);
		TraceSegment(BLACK,x4,y4,x1,y1);
		TraceSegment(BLACK,x2,y2,x6,y6);
		TraceSegment(BLACK,x3,y3,x7,y7);
		TraceSegment(BLACK,x4,y4,x8,y8);
		TraceSegment(BLACK,x6,y6,x7,y7);
		TraceSegment(BLACK,x7,y7,x8,y8);
		}
	if ((z4 >= z1) && (z4 >= z2) && (z4 >= z3) && (z4 >= z5) && (z4 >= z6) && (z4 >= z7) && (z4 >= z8))
		{
		EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
		EffaceQuadrangle(WHITE, x4, y4, x1, y1, x5, y5, x8, y8);
		EffaceQuadrangle(WHITE, x4, y4, x8, y8, x7, y7, x3, y3);
		TraceSegment(BLACK,x1,y1,x2,y2);
		TraceSegment(BLACK,x2,y2,x3,y3);
		TraceSegment(BLACK,x3,y3,x4,y4);
		TraceSegment(BLACK,x4,y4,x1,y1);
		TraceSegment(BLACK,x1,y1,x5,y5);
		TraceSegment(BLACK,x3,y3,x7,y7);
		TraceSegment(BLACK,x4,y4,x8,y8);
		TraceSegment(BLACK,x7,y7,x8,y8);
		TraceSegment(BLACK,x8,y8,x5,y5);
		}
	if ((z5 >= z1) && (z5 >= z2) && (z5 >= z3) && (z5 >= z4) && (z5 >= z6) && (z5 >= z7) && (z5 >= z8))
		{
		EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
		EffaceQuadrangle(WHITE, x5, y5, x6, y6, x2, y2, x1, y1);
		EffaceQuadrangle(WHITE, x5, y5, x8, y8, x4, y4, x1, y1);
		TraceSegment(BLACK,x5,y5,x6,y6);
		TraceSegment(BLACK,x6,y6,x7,y7);
		TraceSegment(BLACK,x7,y7,x8,y8);
		TraceSegment(BLACK,x8,y8,x5,y5);
		TraceSegment(BLACK,x1,y1,x5,y5);
		TraceSegment(BLACK,x2,y2,x6,y6);
		TraceSegment(BLACK,x4,y4,x8,y8);
		TraceSegment(BLACK,x1,y1,x2,y2);
		TraceSegment(BLACK,x4,y4,x1,y1);
		}
	if ((z6 >= z1) && (z6 >= z2) && (z6 >= z3) && (z6 >= z4) && (z6 >= z5) && (z6 >= z7) && (z6 >= z8))
		{
		EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
		EffaceQuadrangle(WHITE, x6, y6, x5, y5, x1, y1, x2, y2);
		EffaceQuadrangle(WHITE, x6, y6, x7, y7, x3, y3, x2, y2);
		TraceSegment(BLACK,x5,y5,x6,y6);
		TraceSegment(BLACK,x6,y6,x7,y7);
		TraceSegment(BLACK,x7,y7,x8,y8);
		TraceSegment(BLACK,x8,y8,x5,y5);
		TraceSegment(BLACK,x1,y1,x5,y5);
		TraceSegment(BLACK,x2,y2,x6,y6);
		TraceSegment(BLACK,x3,y3,x7,y7);
		TraceSegment(BLACK,x1,y1,x2,y2);
		TraceSegment(BLACK,x2,y2,x3,y3);
		}
	if ((z7 >= z1) && (z7 >= z2) && (z7 >= z3) && (z7 >= z4) && (z7 >= z5) && (z7 >= z6) && (z7 >= z8))
		{
		EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
		EffaceQuadrangle(WHITE, x7, y7, x3, y3, x2, y2, x6, y6);
		EffaceQuadrangle(WHITE, x7, y7, x3, y3, x4, y4, x8, y8);
		TraceSegment(BLACK,x5,y5,x6,y6);
		TraceSegment(BLACK,x6,y6,x7,y7);
		TraceSegment(BLACK,x7,y7,x8,y8);
		TraceSegment(BLACK,x8,y8,x5,y5);
		TraceSegment(BLACK,x2,y2,x6,y6);
		TraceSegment(BLACK,x3,y3,x7,y7);
		TraceSegment(BLACK,x4,y4,x8,y8);
		TraceSegment(BLACK,x2,y2,x3,y3);
		TraceSegment(BLACK,x3,y3,x4,y4);
		}
	if ((z8 >= z1) && (z8 >= z2) && (z8 >= z3) && (z8 >= z4) && (z8 >= z5) && (z8 >= z6) && (z8 >= z7))
		{
		EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
		EffaceQuadrangle(WHITE, x8, y8, x4, y4, x1, y1, x5, y5);
		EffaceQuadrangle(WHITE, x8, y8, x4, y4, x3, y3, x7, y7);
		TraceSegment(BLACK,x5,y5,x6,y6);
		TraceSegment(BLACK,x6,y6,x7,y7);
		TraceSegment(BLACK,x7,y7,x8,y8);
		TraceSegment(BLACK,x8,y8,x5,y5);
		TraceSegment(BLACK,x1,y1,x5,y5);
		TraceSegment(BLACK,x3,y3,x7,y7);
		TraceSegment(BLACK,x4,y4,x8,y8);
		TraceSegment(BLACK,x3,y3,x4,y4);
		TraceSegment(BLACK,x4,y4,x1,y1);
		}
	}
	
void draw_efforts_externes(int pa)
	{
	double echelle,vect[4];

	echelle = 0.01;
	vect[1] = Noeud[pa].fx * echelle;
	vect[2] = Noeud[pa].fy * echelle;
	vect[3] = Noeud[pa].fz * echelle;
	
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
	base1(angle_z*PI/180.0,3,0.0,2,3,vect);
	TraceSegment(GREEN, Noeud[pa].x, Noeud[pa].y, Noeud[pa].x+vect[1], Noeud[pa].y+vect[2]);
	}
	
void draw_eigen_values(int pa)
	{
	double echelle,vect[4];
	char chaine[30];

	//printf("NOMBRE_NOEUDS %d n_jacobi_result %d pa %d v_jacobi_result %f   \n",NOMBRE_NOEUDS,n_jacobi_result,pa,v_jacobi_result[1][no_eigenvalue]);
					
	if ((3*pa-0) <= n_jacobi_result)
		{
		//printf("NOMBRE_NOEUDS %4d n_jacobi_result %4d pa %4d  no_eigenvalue  %4d scale_eigenvalue %6.2f prod  %6.2f  ",NOMBRE_NOEUDS,n_jacobi_result,pa,no_eigenvalue,scale_eigenvalue,scale_eigenvalue*v_jacobi_result[3*pa-2][no_eigenvalue]);
		//printf("v_jacobi_result %6.2f   %6.2f   %6.2f\n",v_jacobi_result[3*pa-2][no_eigenvalue],v_jacobi_result[3*pa-1][no_eigenvalue],v_jacobi_result[3*pa-0][no_eigenvalue]);
		//printf("scale_eigenvalue %f   \n",scale_eigenvalue); 	
		vect[1] = v_jacobi_result[3*pa-2][no_eigenvalue] * scale_eigenvalue;
		vect[2] = v_jacobi_result[3*pa-1][no_eigenvalue] * scale_eigenvalue;
		vect[3] = v_jacobi_result[3*pa-0][no_eigenvalue] * scale_eigenvalue;
	
		base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
		base1(angle_z*PI/180.0,3,0.0,2,3,vect);
		TraceSegment(GREEN, Noeud[pa].x, Noeud[pa].y, Noeud[pa].x+vect[1], Noeud[pa].y+vect[2]);
		sprintf(chaine,"eigen period %8.6f s",d_jacobi_result[no_eigenvalue]);
		EcritText(GREEN, (double) binx, (double) biny, chaine, (1.0 * 0.02));
		}
	}
	
void dessiner_contour_noeud()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin,nb_couleur,i;
	double min,max;
	char chaine[70];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double  decalage_y);

	EcritText(RED, (double) binx, (double) biny, "red", (0.0 * 0.02)); 
	EcritText(BLACK, (double) binx+25, (double) biny, "-> compression", (0.0 * 0.02)); 
	EcritText(BLUE, (double) binx+85, (double) biny, "blue", (0.0 * 0.02)); 
	EcritText(BLACK, (double) binx+105, (double) biny, "-> traction", (0.0 * 0.02)); 




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
			
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			Color(BLUE);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];

			min = 0;
			max = Element[1].wt;
			nb_couleur=10;
    			for (i=1;i<=NOMBRE_ELEMENTS;i++)
    				{
				if (max < Element[i].wt)	max = Element[i].wt;
				}
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
/*			if (Element[pa].wt <= 0)TraceSegment(marron, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > 0)&& (Element[pa].wt <= (max/nb_couleur)*1))TraceSegment(bleu5, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > (max/nb_couleur)*1)&& (Element[pa].wt <= (max/nb_couleur)*2))TraceSegment(bleu4, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > (max/nb_couleur)*2)&& (Element[pa].wt <= (max/nb_couleur)*3))TraceSegment(bleu3, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > (max/nb_couleur)*3)&& (Element[pa].wt <= (max/nb_couleur)*4))TraceSegment(bleu2, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > (max/nb_couleur)*4)&& (Element[pa].wt <= (max/nb_couleur)*5))TraceSegment(bleu1, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > (max/nb_couleur)*5)&& (Element[pa].wt <= (max/nb_couleur)*6))TraceSegment(rouge1, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > (max/nb_couleur)*6)&& (Element[pa].wt <= (max/nb_couleur)*7))TraceSegment(rouge2, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > (max/nb_couleur)*7)&& (Element[pa].wt <= (max/nb_couleur)*8))TraceSegment(rouge3, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > (max/nb_couleur)*8)&& (Element[pa].wt <= (max/nb_couleur)*9))TraceSegment(rouge4, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			else if ((Element[pa].wt > (max/nb_couleur)*9)&& (Element[pa].wt <= (max/nb_couleur)*10))TraceSegment(rouge5, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
*/
/**************************************************************************************************************************/
/**************************************************************************************************************************/


			double vect1[4];
			double vect2[4];
			double vect3[4];


			vect1[1]=Noeud[deb].sx;		vect1[2]=0;			vect1[3]=0;
			vect2[1]=0;			vect2[2]=Noeud[deb].sy;		vect2[3]=0;
			vect3[1]=0;			vect3[2]=0;			vect3[3]=Noeud[deb].sz;

  			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
  			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
  			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);


			double x1 = Noeud[deb].x + vect1[1]/2 - vect2[1]/2;
			double y1 = Noeud[deb].y + vect1[2]/2 - vect2[2]/2;
			double z1 = Noeud[deb].z + vect1[3]/2 - vect2[3]/2;

			double x2 = Noeud[deb].x + vect1[1]/2 + vect2[1]/2;
			double y2 = Noeud[deb].y + vect1[2]/2 + vect2[2]/2;
			double z2 = Noeud[deb].z + vect1[3]/2 + vect2[3]/2;

			double x3 = Noeud[deb].x - vect1[1]/2 + vect2[1]/2;
			double y3 = Noeud[deb].y - vect1[2]/2 + vect2[2]/2;
			double z3 = Noeud[deb].z - vect1[3]/2 + vect2[3]/2;

			double x4 = Noeud[deb].x - vect1[1]/2 - vect2[1]/2;
			double y4 = Noeud[deb].y - vect1[2]/2 - vect2[2]/2;
			double z4 = Noeud[deb].z - vect1[3]/2 - vect2[3]/2;

			double x5 = Noeud[deb].x + vect1[1]/2 - vect2[1]/2 +vect3[1];
			double y5 = Noeud[deb].y + vect1[2]/2 - vect2[2]/2 +vect3[2];
			double z5 = Noeud[deb].z + vect1[3]/2 - vect2[3]/2 +vect3[3];

			double x6 = Noeud[deb].x + vect1[1]/2 + vect2[1]/2 +vect3[1];
			double y6 = Noeud[deb].y + vect1[2]/2 + vect2[2]/2 +vect3[2];
			double z6 = Noeud[deb].z + vect1[3]/2 + vect2[3]/2 +vect3[3];

			double x7 = Noeud[deb].x - vect1[1]/2 + vect2[1]/2 +vect3[1];
			double y7 = Noeud[deb].y - vect1[2]/2 + vect2[2]/2 +vect3[2];
			double z7 = Noeud[deb].z - vect1[3]/2 + vect2[3]/2 +vect3[3];

			double x8 = Noeud[deb].x - vect1[1]/2 - vect2[1]/2 +vect3[1];
			double y8 = Noeud[deb].y - vect1[2]/2 - vect2[2]/2 +vect3[2];
			double z8 = Noeud[deb].z - vect1[3]/2 - vect2[3]/2 +vect3[3];

			/*
			printf("x1 : %lf  y1 : %lf \n",x1,y1);
			printf("xx1 : %lf  yy1 : %lf \n",xx1,yy1);
			*/
			TraceSegment(BLACK,x1,y1,x2,y2);
			TraceSegment(BLACK,x2,y2,x3,y3);
			TraceSegment(BLACK,x3,y3,x4,y4);
			TraceSegment(BLACK,x4,y4,x1,y1);

			TraceSegment(BLACK,x1,y1,x5,y5);
			TraceSegment(BLACK,x2,y2,x6,y6);
			TraceSegment(BLACK,x3,y3,x7,y7);
			TraceSegment(BLACK,x4,y4,x8,y8);

			TraceSegment(BLACK,x5,y5,x6,y6);
			TraceSegment(BLACK,x6,y6,x7,y7);
			TraceSegment(BLACK,x7,y7,x8,y8);
			TraceSegment(BLACK,x8,y8,x5,y5);


			vect1[1]=Noeud[fin].sx;		vect1[2]=0;			vect1[3]=0;
			vect2[1]=0;			vect2[2]=Noeud[fin].sy;		vect2[3]=0;
			vect3[1]=0;			vect3[2]=0;			vect3[3]=Noeud[fin].sz;

  			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
  			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
  			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);


			x1 = Noeud[fin].x + vect1[1]/2 - vect2[1]/2;
			y1 = Noeud[fin].y + vect1[2]/2 - vect2[2]/2;
			z1 = Noeud[fin].z + vect1[3]/2 - vect2[3]/2;

			x2 = Noeud[fin].x + vect1[1]/2 + vect2[1]/2;
			y2 = Noeud[fin].y + vect1[2]/2 + vect2[2]/2;
			z2 = Noeud[fin].z + vect1[3]/2 + vect2[3]/2;

			x3 = Noeud[fin].x - vect1[1]/2 + vect2[1]/2;
			y3 = Noeud[fin].y - vect1[2]/2 + vect2[2]/2;
			z3 = Noeud[fin].z - vect1[3]/2 + vect2[3]/2;

			x4 = Noeud[fin].x - vect1[1]/2 - vect2[1]/2;
			y4 = Noeud[fin].y - vect1[2]/2 - vect2[2]/2;
			z4 = Noeud[fin].z - vect1[3]/2 - vect2[3]/2;

			x5 = Noeud[fin].x + vect1[1]/2 - vect2[1]/2 +vect3[1];
			y5 = Noeud[fin].y + vect1[2]/2 - vect2[2]/2 +vect3[2];
			z5 = Noeud[fin].z + vect1[3]/2 - vect2[3]/2 +vect3[3];

			x6 = Noeud[fin].x + vect1[1]/2 + vect2[1]/2 +vect3[1];
			y6 = Noeud[fin].y + vect1[2]/2 + vect2[2]/2 +vect3[2];
			z6 = Noeud[fin].z + vect1[3]/2 + vect2[3]/2 +vect3[3];

			x7 = Noeud[fin].x - vect1[1]/2 + vect2[1]/2 +vect3[1];
			y7 = Noeud[fin].y - vect1[2]/2 + vect2[2]/2 +vect3[2];
			z7 = Noeud[fin].z - vect1[3]/2 + vect2[3]/2 +vect3[3];

			x8 = Noeud[fin].x - vect1[1]/2 - vect2[1]/2 +vect3[1];
			y8 = Noeud[fin].y - vect1[2]/2 - vect2[2]/2 +vect3[2];
			z8 = Noeud[fin].z - vect1[3]/2 - vect2[3]/2 +vect3[3];

			/*
			printf("x1 : %lf  y1 : %lf \n",x1,y1);
			printf("xx1 : %lf  yy1 : %lf \n",xx1,yy1);
			*/
			TraceSegment(BLACK,x1,y1,x2,y2);
			TraceSegment(BLACK,x2,y2,x3,y3);
			TraceSegment(BLACK,x3,y3,x4,y4);
			TraceSegment(BLACK,x4,y4,x1,y1);

			TraceSegment(BLACK,x1,y1,x5,y5);
			TraceSegment(BLACK,x2,y2,x6,y6);
			TraceSegment(BLACK,x3,y3,x7,y7);
			TraceSegment(BLACK,x4,y4,x8,y8);

			TraceSegment(BLACK,x5,y5,x6,y6);
			TraceSegment(BLACK,x6,y6,x7,y7);
			TraceSegment(BLACK,x7,y7,x8,y8);
			TraceSegment(BLACK,x8,y8,x5,y5);


			/*DrawFilledBox(Noeud[fin].x - Noeud[fin].sx/2,Noeud[fin].y - Noeud[fin].sy/2,Noeud[fin].sy,Noeud[fin].sz);*/
			/*DrawFilledBox(Noeud[fin].x - Noeud[fin].sx/2,Noeud[fin].z,Noeud[fin].sy,Noeud[fin].sz);*/

			/**************************************************************************************************************************/
			/**************************************************************************************************************************/





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
			
				}
			}
		}
	}


void dessiner_angle_fils()
	{
	int pa,no,pt1,pt2,pt3,deb,fin,ba;
	float alpha01,n,m,sca,angle_mini;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "contact entre les fils u et v", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES+NOMBRE_WINCHS;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];

			n = (float) sqrt(Surface[pa].nx*Surface[pa].nx + Surface[pa].ny*Surface[pa].ny + Surface[pa].nz*Surface[pa].nz);
			m = (float) sqrt(Surface[pa].mx*Surface[pa].mx + Surface[pa].my*Surface[pa].my + Surface[pa].mz*Surface[pa].mz);
			sca = (float) (Surface[pa].nx*Surface[pa].mx + Surface[pa].ny*Surface[pa].my + Surface[pa].nz*Surface[pa].mz);
			alpha01 = 0.5 * acos(sca/n/m);	/*demi angle entre les fils u et v*/
    			//sprintf(chaine,"%3.0f",alpha01*180/PI);
			angle_mini = atan(fabs(Surface[pa].largeurnoeud / 2.0 / Surface[pa].lgrepos));	/*demi angle de contact entre les fils u et v*/
	
			if ((alpha01 < angle_mini) || (alpha01 > PI/2-angle_mini))
				{
				EffaceTriangle(BLUE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLUE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(BLUE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(BLUE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
				}
			else
				{
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
				TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
				}
			//EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
    			/*
			*/
			
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
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(RED, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURFACES - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS) && (Winch[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS - NOMBRE_COULISSES].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURFACES - NOMBRE_ELEMENTS - NOMBRE_COULISSES;
			for (ba=1;ba<=Winch[pa].nb_barre;ba++)
				{
				deb = Winch[pa].noeud[ba  ];
				fin = Winch[pa].noeud[ba+1];
				TraceSegment(YELLOW, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			}
		}
	}
	
/* debut modifdp du 4 mars 2010*/
void draw_solidity_ratio(int pa)
	{
	int no,pt1,pt2,pt3,deb,fin,ba;
	float alpha01,n,m,sca,angle_mini,mesh_surface,Vn[4],Vm[4],normal[4],twine_surface,Sn,norm;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(RED, (double) binx, (double) biny, "solidity ratio out Aarnes limits", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/
	EcritText(BLUE, (double) binx, (double) biny, "solidity ratio in  Aarnes limits", (2.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
	
	Vn[1] = (float) Surface[pa].nx;	Vn[2] = (float) Surface[pa].ny;	Vn[3] = (float) Surface[pa].nz; /*u twine vector*/
	Vm[1] = (float) Surface[pa].mx;	Vm[2] = (float) Surface[pa].my;	Vm[3] = (float) Surface[pa].mz; /*v twine vector*/
	produit_vect3(Vn, Vm, normal);
	mesh_surface = 2.0 * sqrt(produit_scal(normal,normal));	/*surface of one mesh*/
	twine_surface = 4.0 * Surface[pa].diametrehydro * Surface[pa].lgrepos;	/*surface of twine in one mesh*/
	Sn = twine_surface / mesh_surface;
	if (Sn > 1.0) Sn = 1.0;

	sprintf(chaine,"%4.2f",Sn);
	if ((Sn >=0.13) && (Sn <=0.32))
		{
		/*valid with Aarnes limits*/
		EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
		}
	else
		{
		EcritText(RED, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
		}
	}

void draw_max_exit_size(int pa)
	{
	int pt1,pt2,pt3;
	int col,co;
	float mesh_surface,Vn[4],Vm[4],normal[4],twine_surface,Sn,norm_n,norm_m,scal,cos_gamma,sin_gamma,dn,dm,d_min;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

	EcritText(BLUE, (double) binx, (double) biny, "max exit size (m)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
	d_min = (float) Surface[pa].max_exit_size;
	
	sprintf(chaine,"%4.2f",d_min);
	//EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);

	co = (int) ((Surface[pa].max_exit_size-min_exit_diameter)/(max_exit_diameter-min_exit_diameter) * nb_col);
	co = (int) ((Surface[pa].max_exit_size-min_exit_diameter)/(max_exit_diameter-min_exit_diameter) * nb_col);
	col  = colo[co];
	EffaceTriangle(col, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
	/*sprintf(chaine,"%5.2lg",Surface[pa].nrj1+Surface[pa].nrj2);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);*/
	}

void draw_flow_orientation(int pa)
	{
	int no,pt1,pt2,pt3,deb,fin,ba;
	float alpha01,n,m,sca,angle_mini,Vn[4],Vm[4],normal[4],current[4],norm;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "orientation relatively to the flow (deg.)", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
	
	Vn[1] = (float) Surface[pa].nx;	Vn[2] = (float) Surface[pa].ny;	Vn[3] = (float) Surface[pa].nz; /*u twine vector*/
	Vm[1] = (float) Surface[pa].mx;	Vm[2] = (float) Surface[pa].my;	Vm[3] = (float) Surface[pa].mz; /*v twine vector*/
	produit_vect3(Vn, Vm, normal);
	norm = sqrt(produit_scal(normal,normal));		/*length of normal vector*/
	produit_scal_vect(1.0/norm, normal, normal);		/*normal vector is normalized*/
	current[1] = cos(PI/180.0*Courant.direction);		/*vector direction of flow*/
	current[2] = sin(PI/180.0*Courant.direction);
	current[3] = 0.0;
	norm = fabs(produit_scal(normal,current));			/*cos of the angle between the normal and the current*/
	if (norm >  1) norm =  1.0;
	if (norm < -1) norm = -1.0;
	alpha01 = 90.0 - acos(norm)*180/PI;				/*angle between the normal and the current in deg.*/

	sprintf(chaine,"%3.0f",alpha01);
	EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}
/* fin modifdp du 4 mars 2010*/

void draw_angle_fils(int pa)
	{
	int no,pt1,pt2,pt3,deb,fin,ba;
	float alpha01,n,m,sca,angle_mini;
	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "Blue contact between twines. Green no contact", (1.0 * 0.02)); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	n = (float) sqrt(Surface[pa].nx*Surface[pa].nx + Surface[pa].ny*Surface[pa].ny + Surface[pa].nz*Surface[pa].nz);
	m = (float) sqrt(Surface[pa].mx*Surface[pa].mx + Surface[pa].my*Surface[pa].my + Surface[pa].mz*Surface[pa].mz);
	sca = (float) (Surface[pa].nx*Surface[pa].mx + Surface[pa].ny*Surface[pa].my + Surface[pa].nz*Surface[pa].mz);
	alpha01 = 0.5 * acos(sca/n/m);	/*demi angle entre les fils u et v*/
	//sprintf(chaine,"%3.0f",alpha01*180/PI);
	angle_mini = atan(fabs(Surface[pa].largeurnoeud / 2.0 / Surface[pa].lgrepos));	/*demi angle de contact entre les fils u et v*/

	if ((alpha01 < angle_mini) || (alpha01 > PI/2-angle_mini))
		{
		EffaceTriangle(BLUE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(BLUE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(BLUE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(BLUE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		}
	else
		{
		EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
		TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
		}
	//EcritText(BLUE, (Noeud[pt1].x+Noeud[pt2].x+Noeud[pt3].x)/3.0, (Noeud[pt1].y+Noeud[pt2].y+Noeud[pt3].y)/3.0, chaine, 0.0);
	}

void dessiner_efforts_externes()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;

	double vect[4];
	double echelle;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "efforts externes", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	echelle = 0.01;
	/*printf("angle_x = %f angle_y = %8f  angle_z = %8f   \n",angle_x,angle_y,angle_z);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLUE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLUE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLUE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
  			vect[1] = Noeud[pt1].fx * echelle;
  			vect[2] = Noeud[pt1].fy * echelle;
  			vect[3] = Noeud[pt1].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt1].x+vect[1], Noeud[pt1].y+vect[2]);
			
  			vect[1] = Noeud[pt2].fx * echelle;
  			vect[2] = Noeud[pt2].fy * echelle;
  			vect[3] = Noeud[pt2].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt2].x+vect[1], Noeud[pt2].y+vect[2]);
			
  			vect[1] = Noeud[pt3].fx * echelle;
  			vect[2] = Noeud[pt3].fy * echelle;
  			vect[3] = Noeud[pt3].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt3].x+vect[1], Noeud[pt3].y+vect[2]);
			

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
			
  			vect[1] = Noeud[pt1].fx * echelle;
  			vect[2] = Noeud[pt1].fy * echelle;
  			vect[3] = Noeud[pt1].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt1].x+vect[1], Noeud[pt1].y+vect[2]);
			
  			vect[1] = Noeud[pt2].fx * echelle;
  			vect[2] = Noeud[pt2].fy * echelle;
  			vect[3] = Noeud[pt2].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt2].x+vect[1], Noeud[pt2].y+vect[2]);
			
  			vect[1] = Noeud[pt3].fx * echelle;
  			vect[2] = Noeud[pt3].fy * echelle;
  			vect[3] = Noeud[pt3].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt3].x+vect[1], Noeud[pt3].y+vect[2]);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			Color(RED);
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(RED, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
  			vect[1] = Noeud[deb].fx * echelle;
  			vect[2] = Noeud[deb].fy * echelle;
  			vect[3] = Noeud[deb].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[deb].x, Noeud[deb].y, Noeud[deb].x+vect[1], Noeud[deb].y+vect[2]);
			
  			vect[1] = Noeud[fin].fx * echelle;
  			vect[2] = Noeud[fin].fy * echelle;
  			vect[3] = Noeud[fin].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[fin].x, Noeud[fin].y, Noeud[fin].x+vect[1], Noeud[fin].y+vect[2]);
			
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
			{
			Color(BLACK);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURFACES - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
  				vect[1] = Noeud[deb].fx * echelle;
  				vect[2] = Noeud[deb].fy * echelle;
  				vect[3] = Noeud[deb].fz * echelle;
  			
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
				base1(angle_z*PI/180.0,3,0.0,2,3,vect);
				TraceSegment(GREEN, Noeud[deb].x, Noeud[deb].y, Noeud[deb].x+vect[1], Noeud[deb].y+vect[2]);
			
  				vect[1] = Noeud[fin].fx * echelle;
  				vect[2] = Noeud[fin].fy * echelle;
  				vect[3] = Noeud[fin].fz * echelle;
  			
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
				base1(angle_z*PI/180.0,3,0.0,2,3,vect);
				TraceSegment(GREEN, Noeud[fin].x, Noeud[fin].y, Noeud[fin].x+vect[1], Noeud[fin].y+vect[2]);
			
				}
			}
		}
	}

void dessiner_eigen_values()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;

	double vect[4];
	double echelle;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "efforts externes", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	echelle = 0.01;
	/*printf("angle_x = %f angle_y = %8f  angle_z = %8f   \n",angle_x,angle_y,angle_z);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLUE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLUE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLUE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
  			vect[1] = Noeud[pt1].fx * echelle;
  			vect[2] = Noeud[pt1].fy * echelle;
  			vect[3] = Noeud[pt1].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt1].x+vect[1], Noeud[pt1].y+vect[2]);
			
  			vect[1] = Noeud[pt2].fx * echelle;
  			vect[2] = Noeud[pt2].fy * echelle;
  			vect[3] = Noeud[pt2].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt2].x+vect[1], Noeud[pt2].y+vect[2]);
			
  			vect[1] = Noeud[pt3].fx * echelle;
  			vect[2] = Noeud[pt3].fy * echelle;
  			vect[3] = Noeud[pt3].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt3].x+vect[1], Noeud[pt3].y+vect[2]);
			

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
			
  			vect[1] = Noeud[pt1].fx * echelle;
  			vect[2] = Noeud[pt1].fy * echelle;
  			vect[3] = Noeud[pt1].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt1].x+vect[1], Noeud[pt1].y+vect[2]);
			
  			vect[1] = Noeud[pt2].fx * echelle;
  			vect[2] = Noeud[pt2].fy * echelle;
  			vect[3] = Noeud[pt2].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt2].x+vect[1], Noeud[pt2].y+vect[2]);
			
  			vect[1] = Noeud[pt3].fx * echelle;
  			vect[2] = Noeud[pt3].fy * echelle;
  			vect[3] = Noeud[pt3].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt3].x+vect[1], Noeud[pt3].y+vect[2]);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			Color(RED);
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(RED, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
  			vect[1] = Noeud[deb].fx * echelle;
  			vect[2] = Noeud[deb].fy * echelle;
  			vect[3] = Noeud[deb].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[deb].x, Noeud[deb].y, Noeud[deb].x+vect[1], Noeud[deb].y+vect[2]);
			
  			vect[1] = Noeud[fin].fx * echelle;
  			vect[2] = Noeud[fin].fy * echelle;
  			vect[3] = Noeud[fin].fz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[fin].x, Noeud[fin].y, Noeud[fin].x+vect[1], Noeud[fin].y+vect[2]);
			
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
			{
			Color(BLACK);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURFACES - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
  				vect[1] = Noeud[deb].fx * echelle;
  				vect[2] = Noeud[deb].fy * echelle;
  				vect[3] = Noeud[deb].fz * echelle;
  			
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
				base1(angle_z*PI/180.0,3,0.0,2,3,vect);
				TraceSegment(GREEN, Noeud[deb].x, Noeud[deb].y, Noeud[deb].x+vect[1], Noeud[deb].y+vect[2]);
			
  				vect[1] = Noeud[fin].fx * echelle;
  				vect[2] = Noeud[fin].fy * echelle;
  				vect[3] = Noeud[fin].fz * echelle;
  			
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
				base1(angle_z*PI/180.0,3,0.0,2,3,vect);
				TraceSegment(GREEN, Noeud[fin].x, Noeud[fin].y, Noeud[fin].x+vect[1], Noeud[fin].y+vect[2]);
			
				}
			}
		}
	}

void dessiner_immersion()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin,te;



	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "immersion", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) && (panneau[Surface[pa].type].flag_dessin != 0))
			{
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			for (te=1;te<=nbtemps-1;te++)
				{
				TraceSegment(RED, Noeud[deb].gx[te], Noeud[deb].gy[te], Noeud[deb].gx[te+1], Noeud[deb].gy[te+1]);
				TraceSegment(RED, Noeud[fin].gx[te], Noeud[fin].gy[te], Noeud[fin].gx[te+1], Noeud[fin].gy[te+1]);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
			{
			}
		}
	}

void draw_immersion_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin,te;

	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	for (te=1;te<=nbtemps-1;te++)
		{
		TraceSegment(BLUE, Noeud[deb].gx[te], Noeud[deb].gy[te], Noeud[deb].gx[te+1], Noeud[deb].gy[te+1]);
		TraceSegment(BLUE, Noeud[fin].gx[te], Noeud[fin].gy[te], Noeud[fin].gx[te+1], Noeud[fin].gy[te+1]);
		}
	}

void draw_immersion_surface(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin,te;

	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
	for (te=1;te<=nbtemps-1;te++)
		{
		TraceSegment(BLUE, Noeud[pt1].gx[te], Noeud[pt1].gy[te], Noeud[pt1].gx[te+1], Noeud[pt1].gy[te+1]);
		TraceSegment(BLUE, Noeud[pt2].gx[te], Noeud[pt2].gy[te], Noeud[pt2].gx[te+1], Noeud[pt2].gy[te+1]);
		TraceSegment(BLUE, Noeud[pt3].gx[te], Noeud[pt3].gy[te], Noeud[pt3].gx[te+1], Noeud[pt3].gy[te+1]);
		}
	}

void dessiner_trajectoire()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin,te;
	int zi;
	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	EcritText(RED, (double) binx, (double) biny, "trajectoire", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) && (panneau[Surface[pa].type].flag_dessin != 0))
			{
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			for (te=1;te<=nbtemps-1;te++)
				{
				TraceSegment(RED, Noeud[deb].ex[te], Noeud[deb].ey[te], Noeud[deb].ex[te+1], Noeud[deb].ey[te+1]);
				TraceSegment(RED, Noeud[fin].ex[te], Noeud[fin].ey[te], Noeud[fin].ex[te+1], Noeud[fin].ey[te+1]);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
			{
			}
		}
	}

void draw_trajectoire_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin,te;
	int zi;
	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "trajectory", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	for (te=1;te<=nbtemps-1;te++)
		{
		if (Noeud[deb].flag_dessin != 0)
			{
			TraceSegment(RED, Noeud[deb].ex[te], Noeud[deb].ey[te], Noeud[deb].ex[te+1], Noeud[deb].ey[te+1]);
			}
		if (Noeud[fin].flag_dessin != 0)
			{
			TraceSegment(RED, Noeud[fin].ex[te], Noeud[fin].ey[te], Noeud[fin].ex[te+1], Noeud[fin].ey[te+1]);
			}
		}
	}

void draw_trajectoire_surface(int pa)
	{
	int ba,no,pt1,pt2,pt3,te;
	int zi;
	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "trajectory", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	for (te=1;te<=nbtemps-1;te++)
		{
		if (Noeud[pt1].flag_dessin != 0)
			{
			TraceSegment(BLUE, Noeud[pt1].ex[te], Noeud[pt1].ey[te], Noeud[pt1].ex[te+1], Noeud[pt1].ey[te+1]);
			}
		if (Noeud[pt2].flag_dessin != 0)
			{
			TraceSegment(BLUE, Noeud[pt2].ex[te], Noeud[pt2].ey[te], Noeud[pt2].ex[te+1], Noeud[pt2].ey[te+1]);
			}
		if (Noeud[pt3].flag_dessin != 0)
			{
			TraceSegment(BLUE, Noeud[pt3].ex[te], Noeud[pt3].ey[te], Noeud[pt3].ex[te+1], Noeud[pt3].ey[te+1]);
			}
		}
	}

void dessiner_deplacement()
	{
	int ba,pa,no,pt1,pt2,pt3,deb,fin;



	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "deplacements", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	max = 0.0;
	for (no=1;no<=NOMBRE_NOEUDS;no++)
		{
		ampl = sqrt(Noeud[no].depx * Noeud[no].depx + Noeud[no].depy * Noeud[no].depy + Noeud[no].depz * Noeud[no].depz);
		if (ampl > max) max = ampl;
		}
	echelle = ecartmax / max * 0.1;
	/*printf("angle_x = %f angle_y = %8f  angle_z = %8f   \n",angle_x,angle_y,angle_z);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if ((pa <= NOMBRE_SURFACES) && (panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLUE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLUE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLUE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
  			vect[1] = Noeud[pt1].depx * echelle;
  			vect[2] = Noeud[pt1].depy * echelle;
  			vect[3] = Noeud[pt1].depz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt1].x+vect[1], Noeud[pt1].y+vect[2]);
			
  			vect[1] = Noeud[pt2].depx * echelle;
  			vect[2] = Noeud[pt2].depy * echelle;
  			vect[3] = Noeud[pt2].depz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt2].x+vect[1], Noeud[pt2].y+vect[2]);
			
  			vect[1] = Noeud[pt3].depx * echelle;
  			vect[2] = Noeud[pt3].depy * echelle;
  			vect[3] = Noeud[pt3].depz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt3].x+vect[1], Noeud[pt3].y+vect[2]);
			

			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(BLACK, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(BLACK, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
  			vect[1] = Noeud[pt1].depx * echelle;
  			vect[2] = Noeud[pt1].depy * echelle;
  			vect[3] = Noeud[pt1].depz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt1].x+vect[1], Noeud[pt1].y+vect[2]);
			
  			vect[1] = Noeud[pt2].depx * echelle;
  			vect[2] = Noeud[pt2].depy * echelle;
  			vect[3] = Noeud[pt2].depz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt2].x+vect[1], Noeud[pt2].y+vect[2]);
			
  			vect[1] = Noeud[pt3].depx * echelle;
  			vect[2] = Noeud[pt3].depy * echelle;
  			vect[3] = Noeud[pt3].depz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt3].x+vect[1], Noeud[pt3].y+vect[2]);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			Color(RED);
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(RED, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			
  			vect[1] = Noeud[deb].depx * echelle;
  			vect[2] = Noeud[deb].depy * echelle;
  			vect[3] = Noeud[deb].depz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[deb].x, Noeud[deb].y, Noeud[deb].x+vect[1], Noeud[deb].y+vect[2]);
			
  			vect[1] = Noeud[fin].depx * echelle;
  			vect[2] = Noeud[fin].depy * echelle;
  			vect[3] = Noeud[fin].depz * echelle;
  			
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
			base1(angle_z*PI/180.0,3,0.0,2,3,vect);
			TraceSegment(GREEN, Noeud[fin].x, Noeud[fin].y, Noeud[fin].x+vect[1], Noeud[fin].y+vect[2]);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
			{
			Color(BLACK);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURFACES - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
  				vect[1] = Noeud[deb].depx * echelle;
  				vect[2] = Noeud[deb].depy * echelle;
  				vect[3] = Noeud[deb].depz * echelle;
  			
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
				base1(angle_z*PI/180.0,3,0.0,2,3,vect);
				TraceSegment(GREEN, Noeud[deb].x, Noeud[deb].y, Noeud[deb].x+vect[1], Noeud[deb].y+vect[2]);
			
  				vect[1] = Noeud[fin].depx * echelle;
  				vect[2] = Noeud[fin].depy * echelle;
  				vect[3] = Noeud[fin].depz * echelle;
  			
				base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
				base1(angle_z*PI/180.0,3,0.0,2,3,vect);
				TraceSegment(GREEN, Noeud[fin].x, Noeud[fin].y, Noeud[fin].x+vect[1], Noeud[fin].y+vect[2]);
			
				}
			}
		}
	}

void draw_deplacement_diamond(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "deplacements", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	echelle = 0.1;
	
	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
	
	vect[1] = Noeud[pt1].depx * echelle;
	vect[2] = Noeud[pt1].depy * echelle;
	vect[3] = Noeud[pt1].depz * echelle;
	
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
	base1(angle_z*PI/180.0,3,0.0,2,3,vect);
	TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt1].x+vect[1], Noeud[pt1].y+vect[2]);
	
	vect[1] = Noeud[pt2].depx * echelle;
	vect[2] = Noeud[pt2].depy * echelle;
	vect[3] = Noeud[pt2].depz * echelle;
	
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
	base1(angle_z*PI/180.0,3,0.0,2,3,vect);
	TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt2].x+vect[1], Noeud[pt2].y+vect[2]);
	
	vect[1] = Noeud[pt3].depx * echelle;
	vect[2] = Noeud[pt3].depy * echelle;
	vect[3] = Noeud[pt3].depz * echelle;
	
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
	base1(angle_z*PI/180.0,3,0.0,2,3,vect);
	TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt3].x+vect[1], Noeud[pt3].y+vect[2]);
	}

void draw_deplacement_hexa(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "deplacements", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	echelle = 0.1;

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];

	vect[1] = Noeud[pt1].depx * echelle;
	vect[2] = Noeud[pt1].depy * echelle;
	vect[3] = Noeud[pt1].depz * echelle;
	
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
	base1(angle_z*PI/180.0,3,0.0,2,3,vect);
	TraceSegment(GREEN, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt1].x+vect[1], Noeud[pt1].y+vect[2]);
	
	vect[1] = Noeud[pt2].depx * echelle;
	vect[2] = Noeud[pt2].depy * echelle;
	vect[3] = Noeud[pt2].depz * echelle;
	
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
	base1(angle_z*PI/180.0,3,0.0,2,3,vect);
	TraceSegment(GREEN, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt2].x+vect[1], Noeud[pt2].y+vect[2]);
	
	vect[1] = Noeud[pt3].depx * echelle;
	vect[2] = Noeud[pt3].depy * echelle;
	vect[3] = Noeud[pt3].depz * echelle;
	
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
	base1(angle_z*PI/180.0,3,0.0,2,3,vect);
	TraceSegment(GREEN, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt3].x+vect[1], Noeud[pt3].y+vect[2]);
	}

void draw_deplacement_element(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "deplacements", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	echelle = 0.1;

	deb = Element[pa].extremite[1];
	fin = Element[pa].extremite[2];
	
	vect[1] = Noeud[deb].depx * echelle;
	vect[2] = Noeud[deb].depy * echelle;
	vect[3] = Noeud[deb].depz * echelle;
	
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
	base1(angle_z*PI/180.0,3,0.0,2,3,vect);
	TraceSegment(GREEN, Noeud[deb].x, Noeud[deb].y, Noeud[deb].x+vect[1], Noeud[deb].y+vect[2]);
	
	vect[1] = Noeud[fin].depx * echelle;
	vect[2] = Noeud[fin].depy * echelle;
	vect[3] = Noeud[fin].depz * echelle;
	
	base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
	base1(angle_z*PI/180.0,3,0.0,2,3,vect);
	TraceSegment(GREEN, Noeud[fin].x, Noeud[fin].y, Noeud[fin].x+vect[1], Noeud[fin].y+vect[2]);
	}

void draw_deplacement_coulisse(int pa)
	{
	int ba,no,pt1,pt2,pt3,deb,fin;
	double vect[4];
	double echelle,max,ampl;
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	EcritText(RED, (double) binx, (double) biny, "deplacements", 1.0 * 0.02); 	/*decalage de 1 puisque c est un element*/

	echelle = 0.1;

	for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
		{
		if (ba == 1)	deb = Coulisse[pa].extremite[1];
		if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
		if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
		if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];

		vect[1] = Noeud[deb].depx * echelle;
		vect[2] = Noeud[deb].depy * echelle;
		vect[3] = Noeud[deb].depz * echelle;
	
		base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
		base1(angle_z*PI/180.0,3,0.0,2,3,vect);
		TraceSegment(GREEN, Noeud[deb].x, Noeud[deb].y, Noeud[deb].x+vect[1], Noeud[deb].y+vect[2]);
	
		vect[1] = Noeud[fin].depx * echelle;
		vect[2] = Noeud[fin].depy * echelle;
		vect[3] = Noeud[fin].depz * echelle;
	
		base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect);
		base1(angle_z*PI/180.0,3,0.0,2,3,vect);
		TraceSegment(GREEN, Noeud[fin].x, Noeud[fin].y, Noeud[fin].x+vect[1], Noeud[fin].y+vect[2]);			
		}
	}

void dessiner_commentaire()
	{
	commentaire();
	}


void dessiner_fils_u()
	{
	int ba,pa,deb,fin,no,pt1,pt2,pt3,col;
	float u1,u2,u3,v1,v2,v3,x01,x02,x03,y01,y02,y03,xm,ym,u12,u23,u31,ua,ub,uc;
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*printf("NOMBRE_SURFACES = %8d NOMBRE_ELEMENTS = %8d   \n",NOMBRE_SURFACES,NOMBRE_ELEMENTS);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if (pa == 0) printf("attention : pa = %8d no = %8d   \n",pa,no);
		if ((pa > 0) && (pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
				{
				EffaceTriangle(gris_externe, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				}	
			else	
				{
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				}
			/*u twines*/		
			col = Surface[pa].color_side[1];
			u1 = ((float) Surface[pa].lon[2] + (float) Surface[pa].lon[1]) / periode_fils; 	
			u2 = ((float) Surface[pa].lon[4] + (float) Surface[pa].lon[3]) / periode_fils; 	
			u3 = ((float) Surface[pa].lon[6] + (float) Surface[pa].lon[5]) / periode_fils;
			/*V1 = (float) Surface[pa].lon[2] - (float) Surface[pa].lon[1];*/
			/*V2 = (float) Surface[pa].lon[4] - (float) Surface[pa].lon[3];*/
			/*V3 = (float) Surface[pa].lon[6] - (float) Surface[pa].lon[5];*/			
			/*printf("u123 %8.2f %8.2f %8.2f \n",u1,u2,u3);*/

			u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
			if ((u12 >= u23) && (u12 >= u31))
				{
				/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
				ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
				ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
				uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;			
				if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
				ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
				ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
				uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
				if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				}
			if ((u23 >= u31) && (u23 >= u12))
				{
				/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
				ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
				ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
				uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
				if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
				ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
				ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
				uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
				if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				}
			if ((u31 >= u12) && (u31 >= u23))
				{
				/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
				ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
				ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
				uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
				if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
				ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
				ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
				uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
				if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				}
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			for (deb=1;deb<=Surf_Hexa[pa].nb_Ufils;deb += 1)
				{ 
				TraceSegment(BLUE, (double) Surf_Hexa[pa].f1_Ux[deb], (double) Surf_Hexa[pa].f1_Uy[deb], (double) Surf_Hexa[pa].f2_Ux[deb],	(double) Surf_Hexa[pa].f2_Uy[deb]);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			/*SetColor(Element[pa].color);*/
			Color(RED);
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(RED, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
			{
			Color(BLACK);
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
				{
				if (ba == 1)	deb = Coulisse[pa].extremite[1];
				if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
				if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
				if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				TraceSegment(BLACK, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			}
		}
	}

void draw_fils_u(int pa)
	{
	int ba,deb,fin,no,pt1,pt2,pt3,col;
	float u1,u2,u3,v1,v2,v3,x01,x02,x03,y01,y02,y03,xm,ym,u12,u23,u31,ua,ub,uc;
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	col = Surface[pa].color_side[1];
	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	/*u twines*/		
	u1 = ((float) Surface[pa].lon[2] + (float) Surface[pa].lon[1]) / periode_fils; 	
	u2 = ((float) Surface[pa].lon[4] + (float) Surface[pa].lon[3]) / periode_fils; 	
	u3 = ((float) Surface[pa].lon[6] + (float) Surface[pa].lon[5]) / periode_fils;
	/*V1 = (float) Surface[pa].lon[2] - (float) Surface[pa].lon[1];*/
	/*V2 = (float) Surface[pa].lon[4] - (float) Surface[pa].lon[3];*/
	/*V3 = (float) Surface[pa].lon[6] - (float) Surface[pa].lon[5];*/			
	/*printf("u123 %8.2f %8.2f %8.2f \n",u1,u2,u3);*/

	u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
	if ((u12 >= u23) && (u12 >= u31))
		{
		/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
		ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
		ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
		uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;			
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
		ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
		ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
		uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		}
	if ((u23 >= u31) && (u23 >= u12))
		{
		/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
		ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
		ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
		uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
		ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
		ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
		uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		}
	if ((u31 >= u12) && (u31 >= u23))
		{
		/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
		ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
		ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
		uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
		ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
		ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
		uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		}
	}

void draw_fils_u_hexa(int pa)
	{
	int ba,deb;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	for (deb=1;deb<=Surf_Hexa[pa].nb_Ufils;deb += 1)
		{
		TraceSegment(BLUE, (double) Surf_Hexa[pa].f1_Ux[deb], (double) Surf_Hexa[pa].f1_Uy[deb], (double) Surf_Hexa[pa].f2_Ux[deb],	(double) Surf_Hexa[pa].f2_Uy[deb]);
		}
	}
	
void draw_fils_v_hexa(int pa)
	{
	int ba,deb;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	for (deb=1;deb<=Surf_Hexa[pa].nb_Ufils;deb += 1)
		{ 
		TraceSegment(BLUE, (double) Surf_Hexa[pa].f1_Vx[deb], (double) Surf_Hexa[pa].f1_Vy[deb], (double) Surf_Hexa[pa].f2_Vx[deb],	(double) Surf_Hexa[pa].f2_Vy[deb]);
		}
	}
	
void dessiner_fils_v()
	{
	int ba,pa,deb,fin,no,pt1,pt2,pt3;
	float u1,u2,u3,v1,v2,v3,x01,x02,x03,y01,y02,y03,xm,ym,u12,u23,u31,ua,ub,uc;
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*printf("NOMBRE_SURFACES = %8d NOMBRE_ELEMENTS = %8d   \n",NOMBRE_SURFACES,NOMBRE_ELEMENTS);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if (pa == 0) printf("attention : pa = %8d no = %8d   \n",pa,no);
		if ((pa > 0) && (pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
				{
				EffaceTriangle(gris_externe, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				}	
			else	
				{
				EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
				}
			/*v twines*/		
			/*u1 = (float) Surface[pa].lon[2] + (float) Surface[pa].lon[1];*/ 	
			/*u2 = (float) Surface[pa].lon[4] + (float) Surface[pa].lon[3];*/ 	
			/*u3 = (float) Surface[pa].lon[6] + (float) Surface[pa].lon[5];*/
			u1 = ((float) Surface[pa].lon[2] - (float) Surface[pa].lon[1]) / periode_fils;
			u2 = ((float) Surface[pa].lon[4] - (float) Surface[pa].lon[3]) / periode_fils;
			u3 = ((float) Surface[pa].lon[6] - (float) Surface[pa].lon[5]) / periode_fils;		
			u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
			/*printf("u123 %8.2f %8.2f %8.2f \n",u1,u2,u3);*/
			if ((u12 >= u23) && (u12 >= u31))
				{
				/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
				ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
				ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
				uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
				draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
				ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
				ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
				uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
				draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				}
			if ((u23 >= u31) && (u23 >= u12))
				{
				/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
				ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
				ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
				uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
				draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
				ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
				ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
				uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
				draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				}
			if ((u31 >= u12) && (u31 >= u23))
				{
				/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
				ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
				ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
				uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
				draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
				ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
				ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
				uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
				draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
				}
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			/*SetColor(Surf_Hexa[pa].color_v);*/
			Color(BLUE);
			for (deb=1;deb<=Surf_Hexa[pa].nb_Vfils;deb += 1)
				{ 
				TraceSegment(BLUE, (double) Surf_Hexa[pa].f1_Vx[deb], (double) Surf_Hexa[pa].f1_Vy[deb], (double) Surf_Hexa[pa].f2_Vx[deb],	(double) Surf_Hexa[pa].f2_Vy[deb]);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			/*SetColor(Element[pa].color);*/
			Color(RED);
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(RED, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
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

void draw_fils_v(int pa)
	{
	int ba,deb,fin,no,pt1,pt2,pt3,col;
	float u1,u2,u3,v1,v2,v3,x01,x02,x03,y01,y02,y03,xm,ym,u12,u23,u31,ua,ub,uc;
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	col = Surface[pa].color_side[2];	
	//col = panneau[Surface[pa].type].flag_dessin;
	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];

	/*v twines*/		
	/*u1 = (float) Surface[pa].lon[2] + (float) Surface[pa].lon[1];*/ 	
	/*u2 = (float) Surface[pa].lon[4] + (float) Surface[pa].lon[3];*/ 	
	/*u3 = (float) Surface[pa].lon[6] + (float) Surface[pa].lon[5];*/
	u1 = ((float) Surface[pa].lon[2] - (float) Surface[pa].lon[1]) / periode_fils;
	u2 = ((float) Surface[pa].lon[4] - (float) Surface[pa].lon[3]) / periode_fils;
	u3 = ((float) Surface[pa].lon[6] - (float) Surface[pa].lon[5]) / periode_fils;		
	u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
	/*printf("u123 %8.2f %8.2f %8.2f \n",u1,u2,u3);*/
	if ((u12 >= u23) && (u12 >= u31))
		{
		/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
		ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
		ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
		uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
		ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
		ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
		uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		}
	if ((u23 >= u31) && (u23 >= u12))
		{
		/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
		ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
		ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
		uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
		ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
		ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
		uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		}
	if ((u31 >= u12) && (u31 >= u23))
		{
		/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
		ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
		ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
		uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
		ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
		ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
		uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
		if (flag_ps) 	draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		else		draw_twines_color(col, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
		}
	}

void trace_fil_hexa(float a1, float b1, float a2, float b2, float x01, float y01, float x02, float y02, float x03, float y03)
	{
	/*a1,b1 a a2,b2 est le fil a tracer dans le triangle de sommets x01,y01 x02,y02 x03,y03*/
	int inside1,inside2,secant,secant1,secant2;
	double xx,yy,xx01,yy01;
	
	int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
	int segment_secant(double a1, double b1, double a2, double b2, double x01, double y01, double x02, double y02);
	void intersection_segment(double a1, double b1, double a2, double b2, double x01, double y01, double x02, double y02, double *x,double *y);
	inside1 = appartient_triangle4((double) a1, (double) b1, (double) x01, (double) y01, (double) x02, (double) y02, (double) x03, (double) y03);
	inside2 = appartient_triangle4((double) a2, (double) b2, (double) x01, (double) y01, (double) x02, (double) y02, (double) x03, (double) y03);

	/*printf("inside1 = %d inside2 = %d  \n",inside1,inside2);*/
	
	
	
	if ((inside1 == 1) && (inside2 == 1))
		{
		/*ici les 2 extremites a1,b1 et a2,b2 du fil sont dans le triangle 1 2 3, on peut le tracer*/
		if (ARTICLE_HEXA_2001 == 0)
			{
			Line(((REEL) a1-binx) / (baxx-binx),((REEL) b1-biny) / (baxy-biny),((REEL) a2-binx) / (baxx-binx),((REEL) b2-biny) / (baxy-biny));
			}
		else
			{
			pointille(a1, b1, a2, b2);
			TraceSegment(BLACK,a1,b1,a2,b2);
			}
		}
	/*ici l extremite a1,b1 est dans le triangle 1 2 3 et a2,b2 est a l exterieur*/
	if ((inside1 == 1) && (inside2 != 1))
		{
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x01, (double) y01, (double) x02, (double) y02);
		/*printf("secant = %d    \n",secant);*/
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x01, (double) y01, (double) x02, (double) y02, &xx, &yy);
			if (ARTICLE_HEXA_2001 == 0)
				{
				Line(((REEL) a1-binx) / (baxx-binx),((REEL) b1-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
				}
			else
				{
				pointille((float) a1, (float) b1, (float) xx, (float) yy);
				TraceSegment(BLACK,a1,b1,xx,yy);
				}
			}
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x02, (double) y02, (double) x03, (double) y03);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x02, (double) y02, (double) x03, (double) y03, &xx, &yy);
			if (ARTICLE_HEXA_2001 == 0)
				{
				Line(((REEL) a1-binx) / (baxx-binx),((REEL) b1-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
				}
			else
				{
				pointille(a1, b1, (REEL) xx, (REEL) yy);
				TraceSegment(BLACK,a1,b1,xx,yy);
				}
			}
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x03, (double) y03, (double) x01, (double) y01);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x03, (double) y03, (double) x01, (double) y01, &xx, &yy);
			if (ARTICLE_HEXA_2001 == 0)
				{
				Line(((REEL) a1-binx) / (baxx-binx),((REEL) b1-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
				}
			else
				{
				pointille(a1, b1, (REEL) xx, (REEL) yy);
				TraceSegment(BLACK,a1,b1,xx,yy);
				}
			}
		}
	if ((inside1 != 1) && (inside2 == 1))
		{
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x01, (double) y01, (double) x02, (double) y02);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x01, (double) y01, (double) x02, (double) y02, &xx, &yy);
			if (ARTICLE_HEXA_2001 == 0)
				{
				Line(((REEL) a2-binx) / (baxx-binx),((REEL) b2-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
				}
			else
				{
				pointille(a2, b2, (REEL) xx, (REEL) yy);
				TraceSegment(BLACK,a2,b2,xx,yy);
				}
			}
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x02, (double) y02, (double) x03, (double) y03);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x02, (double) y02, (double) x03, (double) y03, &xx, &yy);
			if (ARTICLE_HEXA_2001 == 0)
				{
				Line(((REEL) a2-binx) / (baxx-binx),((REEL) b2-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
				}
			else
				{
				pointille(a2, b2, (REEL) xx, (REEL) yy);
				TraceSegment(BLACK,a2,b2,xx,yy);
				}
			}
		secant =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x03, (double) y03, (double) x01, (double) y01);
		if (secant == 1)
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x03, (double) y03, (double) x01, (double) y01, &xx, &yy);
			if (ARTICLE_HEXA_2001 == 0)
				{
				Line(((REEL) a2-binx) / (baxx-binx),((REEL) b2-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
				}
			else
				{
				pointille(a2, b2, (REEL) xx, (REEL) yy);
				TraceSegment(BLACK,a2,b2,xx,yy);
				}
			}
		}
	if ((inside1 != 1) && (inside2 != 1))
		{
		/*les 2 points sont a l exterieur du triangle*/
		secant1 =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x01, (double) y01, (double) x02, (double) y02);
		secant2 =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x02, (double) y02, (double) x03, (double) y03);
/*printf("1,2 et 2,3 secant1 = %d   secant2 = %d   \n",secant1,secant2);*/
		if ((secant1 == 1) && (secant2 == 1))
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x01, (double) y01, (double) x02, (double) y02, &xx, &yy);
			xx01 = xx;
			yy01 = yy;
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x02, (double) y02, (double) x03, (double) y03, &xx, &yy);
			if (ARTICLE_HEXA_2001 == 0)
				{
				Line(((REEL) xx01-binx) / (baxx-binx),((REEL) yy01-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
				}
			else
				{
				pointille((REEL) xx01, (REEL) yy01, (REEL) xx, (REEL) yy);
				TraceSegment(BLACK,xx01,yy01,xx,yy);
				}
			}
		secant1 =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x02, (double) y02, (double) x03, (double) y03);
		secant2 =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x03, (double) y03, (double) x01, (double) y01);
/*printf("2,3 et 3,1 secant1 = %d   secant2 = %d   \n",secant1,secant2);*/
		if ((secant1 == 1) && (secant2 == 1))
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x02, (double) y02, (double) x03, (double) y03, &xx, &yy);
			xx01 = xx;
			yy01 = yy;
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x03, (double) y03, (double) x01, (double) y01, &xx, &yy);
			if (ARTICLE_HEXA_2001 == 0)
				{
				Line(((REEL) xx01-binx) / (baxx-binx),((REEL) yy01-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
				}
			else
				{
				pointille((REEL) xx01, (REEL) yy01, (REEL) xx, (REEL) yy);
				TraceSegment(BLACK,xx01,yy01,xx,yy);
				}
			}
		secant1 =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x03, (double) y03, (double) x01, (double) y01);
		secant2 =  segment_secant((double) a1, (double) b1, (double) a2, (double) b2, (double) x01, (double) y01, (double) x02, (double) y02);
/*printf("3,1 et 1,2 secant1 = %d   secant2 = %d   \n",secant1,secant2);*/
		if ((secant1 == 1) && (secant2 == 1))
			{
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x03, (double) y03, (double) x01, (double) y01, &xx, &yy);
			xx01 = xx;
			yy01 = yy;
			intersection_segment((double) a1, (double) b1, (double) a2, (double) b2, (double) x01, (double) y01, (double) x02, (double) y02, &xx, &yy);
			if (ARTICLE_HEXA_2001 == 0)
				{
				Line(((REEL) xx01-binx) / (baxx-binx),((REEL) yy01-biny) / (baxy-biny),((REEL) xx-binx) / (baxx-binx),((REEL) yy-biny) / (baxy-biny));
				}
			else
				{
				pointille((REEL) xx01, (REEL) yy01, (REEL) xx, (REEL) yy);
				TraceSegment(BLACK,xx01,yy01,xx,yy);
				}
			}



		}
	}
	
	
	
void pointille(float x01, float y01, float x02, float y02)
	{
	int zi;
	float ll,deb,fin,pas,xdeb,ydeb,xfin,yfin;
	
	pas = 0.02;
	ll = (float) sqrt((x02-x01)*(x02-x01) + (y02-y01)*(y02-y01));
	zi = 0;
	if (ll != 0.0)
		{
		do
			{
			deb = zi * pas;
			fin = (zi+1) * pas;
			xdeb = x01 + (x02-x01) / ll * deb;
			ydeb = y01 + (y02-y01) / ll * deb;
			if (((xdeb>x01) && (xdeb>x02)) || ((xdeb<x01) && (xdeb<x02)) || ((ydeb>y01) && (ydeb>y02)) || ((ydeb<y01) && (ydeb<y02)))
				{
				/*si deb depasse le point 1 le ramene sur 1*/
				xdeb = x02;	ydeb = y02;
				}
			xfin = x01 + (x02-x01) / ll * fin;
			yfin = y01 + (y02-y01) / ll * fin;
			if (((xfin>x01) && (xfin>x02)) || ((xfin<x01) && (xfin<x02)) || ((yfin>y01) && (yfin>y02)) || ((yfin<y01) && (yfin<y02)))
				{
				/*si fin depasse le point 2 le ramene sur 2*/
				xfin = x02;	yfin = y02;
				}
			Line((xdeb-binx) / (baxx-binx),(ydeb-biny) / (baxy-biny),(xfin-binx) / (baxx-binx),(yfin-biny) / (baxy-biny));
			zi = zi + 2;
			}
		while (fin<ll);
		}
	}
	
void dessiner_fils_uv()
	{
	int ba,pa,deb,fin,no,np,pt1,pt2,pt3,interne,um,vm,minu,maxu,minv,maxv,nb_twine,color;
	float a1,a2,b1,b2,ru,rv,denom,vect_ux,vect_uy,vect_vx,vect_vy;
	float u1,u2,u3,v1,v2,v3,x01,x02,x03,y01,y02,y03,xm,ym,u12,u23,u31,ua,ub,uc;
	int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
	void trace_fil_hexa(float a1, float b1, float a2, float b2, float x01, float y01, float x02, float y02, float x03, float y03);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	float extr1[4],extr2[4];
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;
	
	/*printf("NOMBRE_SURFACES = %8d NOMBRE_ELEMENTS = %8d   \n",NOMBRE_SURFACES,NOMBRE_ELEMENTS);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if (pa == 0) printf("attention : pa = %8d no = %8d   \n",pa,no);
		if ((pa > 0) && (pa <= NOMBRE_SURFACES))
			{
			/*printf("pa = %8d panel %d color = %8d   \n",pa,Surface[pa].type,panneau[Surface[pa].type].flag_dessin);*/
			color = panneau[Surface[pa].type].flag_dessin;
			if (color != 0)
				{
				pt1 = Surface[pa].extremite[1];
				pt2 = Surface[pa].extremite[2];
				pt3 = Surface[pa].extremite[3];
			
				if (Surface[pa].orientation*((Noeud[pt2].x-Noeud[pt1].x)*(Noeud[pt3].y-Noeud[pt2].y)-(Noeud[pt2].y-Noeud[pt1].y)*(Noeud[pt3].x-Noeud[pt2].x)) >= 0.0)
					{
					/*EffaceTriangle(gris_externe, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);*/
					EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
					}	
				else	
					{
					EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
					}

				/*u twines*/		
				u1 = ((float) Surface[pa].lon[2] + (float) Surface[pa].lon[1]) / periode_fils; 	
				u2 = ((float) Surface[pa].lon[4] + (float) Surface[pa].lon[3]) / periode_fils; 	
				u3 = ((float) Surface[pa].lon[6] + (float) Surface[pa].lon[5]) / periode_fils;
				/*V1 = (float) Surface[pa].lon[2] - (float) Surface[pa].lon[1];*/
				/*V2 = (float) Surface[pa].lon[4] - (float) Surface[pa].lon[3];*/
				/*V3 = (float) Surface[pa].lon[6] - (float) Surface[pa].lon[5];*/			
				/*printf("u123 %8.2f %8.2f %8.2f \n",u1,u2,u3);*/

				u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
				if ((u12 >= u23) && (u12 >= u31))
					{
					/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
					ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
					ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
					uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;			
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
					ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
					ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
					uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				if ((u23 >= u31) && (u23 >= u12))
					{
					/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
					ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
					ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
					uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
					ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
					ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
					uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				if ((u31 >= u12) && (u31 >= u23))
					{
					/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
					ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
					ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
					uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
					ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
					ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
					uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				
				/*v twines*/		
				/*u1 = (float) Surface[pa].lon[2] + (float) Surface[pa].lon[1];*/ 	
				/*u2 = (float) Surface[pa].lon[4] + (float) Surface[pa].lon[3];*/ 	
				/*u3 = (float) Surface[pa].lon[6] + (float) Surface[pa].lon[5];*/
				u1 = ((float) Surface[pa].lon[2] - (float) Surface[pa].lon[1]) / periode_fils;
				u2 = ((float) Surface[pa].lon[4] - (float) Surface[pa].lon[3]) / periode_fils;
				u3 = ((float) Surface[pa].lon[6] - (float) Surface[pa].lon[5]) / periode_fils;		
				u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
				/*printf("u123 %8.2f %8.2f %8.2f \n",u1,u2,u3);*/
				if ((u12 >= u23) && (u12 >= u31))
					{
					/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
					ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
					ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
					uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
					ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
					ub = u3;	xb = (REEL) Noeud[pt3].x; yb = (REEL) Noeud[pt3].y;
					uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				if ((u23 >= u31) && (u23 >= u12))
					{
					/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
					ua = u2;	xa = (REEL) Noeud[pt2].x; ya = (REEL) Noeud[pt2].y;
					ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
					uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
					ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
					ub = u1;	xb = (REEL) Noeud[pt1].x; yb = (REEL) Noeud[pt1].y;
					uc = u2;	xc = (REEL) Noeud[pt2].x; yc = (REEL) Noeud[pt2].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}
				if ((u31 >= u12) && (u31 >= u23))
					{
					/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
					ua = u3;	xa = (REEL) Noeud[pt3].x; ya = (REEL) Noeud[pt3].y;
					ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
					uc = u1;	xc = (REEL) Noeud[pt1].x; yc = (REEL) Noeud[pt1].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
					ua = u1;	xa = (REEL) Noeud[pt1].x; ya = (REEL) Noeud[pt1].y;
					ub = u2;	xb = (REEL) Noeud[pt2].x; yb = (REEL) Noeud[pt2].y;
					uc = u3;	xc = (REEL) Noeud[pt3].x; yc = (REEL) Noeud[pt3].y;
					/*draw_twines( pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);*/
					draw_twines_color( color, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
					}

				if (GetMenuItemChecked(w[10]))
					{
					TraceSegment(BLACK, (double) Noeud[pt1].x, (double) Noeud[pt1].y, (double) Noeud[pt2].x, (double) Noeud[pt2].y);
					TraceSegment(BLACK, (double) Noeud[pt2].x, (double) Noeud[pt2].y, (double) Noeud[pt3].x, (double) Noeud[pt3].y);
					TraceSegment(BLACK, (double) Noeud[pt3].x, (double) Noeud[pt3].y, (double) Noeud[pt1].x, (double) Noeud[pt1].y);
					}
				}
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA))
			{
			pa = pa - NOMBRE_SURFACES;
			if (TypeSurfHexa[Surf_Hexa[pa].type].flag_dessin != 0)
				{
			/*if (pa > 0)*/
			if (pa > 0)
			{
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
			
			
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			/**/
			
			x01 = (REEL) (Noeud[pt1].x - binx) / (baxx - binx);
			x02 = (REEL) (Noeud[pt2].x - binx) / (baxx - binx);
			x03 = (REEL) (Noeud[pt3].x - binx) / (baxx - binx);
			y01 = (REEL) (Noeud[pt1].y - biny) / (baxy - biny);
			y02 = (REEL) (Noeud[pt2].y - biny) / (baxy - biny);
			y03 = (REEL) (Noeud[pt3].y - biny) / (baxy - biny);
			
			interne = interieur_triangle((double) x01,(double) x02,(double) x03,(double) y01,(double) y02,(double) y03);
			if (interne == 1)
				{
			
			/*
			if (Surf_Hexa[pa].orientation*((x02-x01)*(y03-y02)-(y02-y01)*(x03-x02)) >= 0.0)	SetColor(gris_interne);
			else	SetColor(gris_externe);
			*/
			
			if (ARTICLE_HEXA_2001 == 0)
				{
				/*triangle*/
				Color(WHITE);
				Move_to(x01,y01);
				Line_to(x02,y02);
				Line_to(x03,y03);
				Line_to(x01,y01);
				Surface_end();
				Color(BLUE);
				Color(BLACK);
				}
			else
				{
				Color(BLACK);
				Color(BLUE);
				}
			
			/*SetColor(Surf_Hexa[pa].color_v);*/
		u1 = Surf_Hexa[pa].lon[1]; v1 = Surf_Hexa[pa].lon[2];
		u2 = Surf_Hexa[pa].lon[3]; v2 = Surf_Hexa[pa].lon[4];
		u3 = Surf_Hexa[pa].lon[5]; v3 = Surf_Hexa[pa].lon[6];
		u1 = (float) Surf_Hexa[pa].lon[1] / periode_fils; v1 = (float) Surf_Hexa[pa].lon[2] / periode_fils;
		u2 = (float) Surf_Hexa[pa].lon[3] / periode_fils; v2 = (float) Surf_Hexa[pa].lon[4] / periode_fils;
		u3 = (float) Surf_Hexa[pa].lon[5] / periode_fils; v3 = (float) Surf_Hexa[pa].lon[6] / periode_fils;
		/*
		*/
		x01 = Noeud[pt1].x;	y01 = Noeud[pt1].y;
		x02 = Noeud[pt2].x;	y02 = Noeud[pt2].y;
		x03 = Noeud[pt3].x;	y03 = Noeud[pt3].y;
	       	denom = (u3-u1)*(v2-v1) - (u2-u1)*(v3-v1);
	       	/* precautions en cas de denominateur nul*/
	       	if (fabs(denom) <= 0.00001)
	               	{  
	        	printf(" * noeud_panneau * denom = %f\n",denom); 
	               	} 
	       	/*calcul des vecteur elementaires cartesiens de cote de maille vect_u et vect_v*/
	       	ru = u1+1.0;
	       	rv = v1+0.0;
	     	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
	     	betaa  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;
	       	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
	       	vect_ux = alpha * ( x02 - x01 )+ betaa * ( x03 - x01 );
	       	vect_uy = alpha * ( y02 - y01 )+ betaa * ( y03 - y01 );
	       	ru = u1+0.0;
	       	rv = v1+1.0;
	     	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
	     	betaa  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;
	       	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
	       	vect_vx = alpha * ( x02 - x01 )+ betaa * ( x03 - x01 );
	       	vect_vy = alpha * ( y02 - y01 )+ betaa * ( y03 - y01 );
		minu = (int) floor(u1);		maxu = (int) ceil(u1);
		minv = (int) floor(v1);		maxv = (int) ceil(v1);
		if (minu>u2) minu = (int) floor(u2);  if (maxu<u2) maxu = (int) ceil(u2);
		if (minu>u3) minu = (int) floor(u3);  if (maxu<u3) maxu = (int) ceil(u3);
		if (minv>v2) minv = (int) floor(v2);  if (maxv<v2) maxv = (int) ceil(v2);
		if (minv>v3) minv = (int) floor(v3);  if (maxv<v3) maxv = (int) ceil(v3);
		/*printf("minu = %d maxu = %d minv = %d maxv = %d \n",minu,maxu,minv,maxv); */
		/*for (um=minu;um<=minu;um++)*/
		for (um=minu;um<=maxu;um++)
			{ 
			/*for (vm=minv;vm<=maxv;vm++)*/
			for (vm=minv;vm<=maxv;vm++)
				{
				/*printf("um   : %8d ,vm  :  %8d ",um,vm);*/
	       			/* determination des coefficients alpha01 et betaa definis tels que 1m = alpha01*12 + betaa*13 */
	     			alpha =   ( (vm-v1)*(u3-u1) - (um-u1)*(v3-v1) ) / denom;
	     			betaa  =   ( (um-u1)*(v2-v1) - (vm-v1)*(u2-u1) ) / denom;
	         		/*printf("alpha01= %f,betaa = %f ",alpha01,betaa);*/
	       			/* determination des coordonnees cartesiennes de l origine de la maille proche d une position d equilibre */
	       			xm = alpha * ( x02 - x01 )+ betaa * ( x03 - x01 ) + x01;
	       			ym = alpha * ( y02 - y01 )+ betaa * ( y03 - y01 ) + y01;
	         		/*trace des 6 fils a l interieur d une maille*/
	         		/*
				Line(((REEL) xm-0.08-binx) / (baxx-binx),((REEL) ym-biny) / (baxy-biny),((REEL) xm+0.08-binx) / (baxx-binx),((REEL) ym-biny) / (baxy-biny));
				Line(((REEL) xm-binx) / (baxx-binx),((REEL) ym-0.08-biny) / (baxy-biny),((REEL) xm-binx) / (baxx-binx),((REEL) ym+0.08-biny) / (baxy-biny));
				*/
				a1 = xm +vect_ux*1.0/6.0 +vect_vx*1.0/2.0;
				b1 = ym +vect_uy*1.0/6.0 +vect_vy*1.0/2.0;
				a2 = xm +vect_ux*0.0/6.0 +vect_vx*0.0/2.0;
				b2 = ym +vect_uy*0.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);

				a2 = xm +vect_ux*0.0/6.0 +vect_vx*2.0/2.0;
				b2 = ym +vect_uy*0.0/6.0 +vect_vy*2.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a2 = xm +vect_ux*3.0/6.0 +vect_vx*1.0/2.0;
				b2 = ym +vect_uy*3.0/6.0 +vect_vy*1.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a1 = xm +vect_ux*4.0/6.0 +vect_vx*2.0/2.0;
				b1 = ym +vect_uy*4.0/6.0 +vect_vy*2.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a1 = xm +vect_ux*4.0/6.0 +vect_vx*0.0/2.0;
				b1 = ym +vect_uy*4.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a2 = xm +vect_ux*6.0/6.0 +vect_vx*0.0/2.0;
				b2 = ym +vect_uy*6.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				}
			}
				}
			}
			}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			if (TypeElement[Element[pa].type].flag_dessin != 0)
				{
				/*SetColor(Element[pa].color);
				Color(RED);*/
				deb = Element[pa].extremite[1];
				fin = Element[pa].extremite[2];
				/*TraceSegment(TypeElement[Element[pa].type].flag_dessin, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);*/
				draw_segment_color(TypeElement[Element[pa].type].flag_dessin, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
			if (Coulisse[pa].flag_dessin != 0)
				{
				for (ba=1;ba<=Coulisse[pa].nb_noeud+1;ba++)
					{
					if (ba == 1)	deb = Coulisse[pa].extremite[1];
					if (ba != 1)	deb = Coulisse[pa].noeud[ba-1];
					if (ba == Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].extremite[2];
					if (ba != Coulisse[pa].nb_noeud+1)	fin = Coulisse[pa].noeud[ba];
					TraceSegment(Coulisse[pa].flag_dessin, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
					}
				}
			}
		}
	}

void draw_fils_uv_hexa(int pa)
	{
	int ba,deb,fin,no,np,pt1,pt2,pt3,interne,um,vm,minu,maxu,minv,maxv,nb_twine,color;
	float a1,a2,b1,b2,ru,rv,denom,vect_ux,vect_uy,vect_vx,vect_vy;
	float u1,u2,u3,v1,v2,v3,x01,x02,x03,y01,y02,y03,xm,ym,u12,u23,u31,ua,ub,uc;
	int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
	void trace_fil_hexa(float a1, float b1, float a2, float b2, float x01, float y01, float x02, float y02, float x03, float y03);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	float extr1[4],extr2[4];
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;
	

	pt1 = Surf_Hexa[pa].extremite[1];
	pt2 = Surf_Hexa[pa].extremite[2];
	pt3 = Surf_Hexa[pa].extremite[3];
	
	
	x01 = (REEL) (Noeud[pt1].x - binx) / (baxx - binx);
	x02 = (REEL) (Noeud[pt2].x - binx) / (baxx - binx);
	x03 = (REEL) (Noeud[pt3].x - binx) / (baxx - binx);
	y01 = (REEL) (Noeud[pt1].y - biny) / (baxy - biny);
	y02 = (REEL) (Noeud[pt2].y - biny) / (baxy - biny);
	y03 = (REEL) (Noeud[pt3].y - biny) / (baxy - biny);
	
	interne = interieur_triangle((double) x01,(double) x02,(double) x03,(double) y01,(double) y02,(double) y03);
	if (interne == 1)
		{
			
		/*
		if (Surf_Hexa[pa].orientation*((x02-x01)*(y03-y02)-(y02-y01)*(x03-x02)) >= 0.0)	SetColor(gris_interne);
		else	SetColor(gris_externe);
		*/
		
		if (ARTICLE_HEXA_2001 == 0)
			{
			/*triangle*/
			Color(WHITE);
			Move_to(x01,y01);
			Line_to(x02,y02);
			Line_to(x03,y03);
			Line_to(x01,y01);
			Surface_end();
			Color(BLUE);
			Color(BLACK);
			}
		else
			{
			Color(BLACK);
			Color(BLUE);
			}
		
		/*SetColor(Surf_Hexa[pa].color_v);*/
		u1 = Surf_Hexa[pa].lon[1]; v1 = Surf_Hexa[pa].lon[2];
		u2 = Surf_Hexa[pa].lon[3]; v2 = Surf_Hexa[pa].lon[4];
		u3 = Surf_Hexa[pa].lon[5]; v3 = Surf_Hexa[pa].lon[6];
		u1 = (float) Surf_Hexa[pa].lon[1] / periode_fils; v1 = (float) Surf_Hexa[pa].lon[2] / periode_fils;
		u2 = (float) Surf_Hexa[pa].lon[3] / periode_fils; v2 = (float) Surf_Hexa[pa].lon[4] / periode_fils;
		u3 = (float) Surf_Hexa[pa].lon[5] / periode_fils; v3 = (float) Surf_Hexa[pa].lon[6] / periode_fils;
		/*
		*/
		x01 = Noeud[pt1].x;	y01 = Noeud[pt1].y;
		x02 = Noeud[pt2].x;	y02 = Noeud[pt2].y;
		x03 = Noeud[pt3].x;	y03 = Noeud[pt3].y;
	       	denom = (u3-u1)*(v2-v1) - (u2-u1)*(v3-v1);
	       	/* precautions en cas de denominateur nul*/
	       	if (fabs(denom) <= 0.00001)
	               	{  
	        	printf(" * noeud_panneau * denom = %f\n",denom); 
	               	} 
	       	/*calcul des vecteur elementaires cartesiens de cote de maille vect_u et vect_v*/
	       	ru = u1+1.0;
	       	rv = v1+0.0;
	     	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
	     	betaa  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;
	       	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
	       	vect_ux = alpha * ( x02 - x01 )+ betaa * ( x03 - x01 );
	       	vect_uy = alpha * ( y02 - y01 )+ betaa * ( y03 - y01 );
	       	ru = u1+0.0;
	       	rv = v1+1.0;
	     	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
	     	betaa  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;
	       	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
	       	vect_vx = alpha * ( x02 - x01 )+ betaa * ( x03 - x01 );
	       	vect_vy = alpha * ( y02 - y01 )+ betaa * ( y03 - y01 );
		minu = (int) floor(u1);		maxu = (int) ceil(u1);
		minv = (int) floor(v1);		maxv = (int) ceil(v1);
		if (minu>u2) minu = (int) floor(u2);  if (maxu<u2) maxu = (int) ceil(u2);
		if (minu>u3) minu = (int) floor(u3);  if (maxu<u3) maxu = (int) ceil(u3);
		if (minv>v2) minv = (int) floor(v2);  if (maxv<v2) maxv = (int) ceil(v2);
		if (minv>v3) minv = (int) floor(v3);  if (maxv<v3) maxv = (int) ceil(v3);
		/*printf("minu = %d maxu = %d minv = %d maxv = %d \n",minu,maxu,minv,maxv); */
		/*for (um=minu;um<=minu;um++)*/
		for (um=minu;um<=maxu;um++)
			{ 
			/*for (vm=minv;vm<=maxv;vm++)*/
			for (vm=minv;vm<=maxv;vm++)
				{
				/*printf("um   : %8d ,vm  :  %8d ",um,vm);*/
	       			/* determination des coefficients alpha01 et betaa definis tels que 1m = alpha01*12 + betaa*13 */
	     			alpha =   ( (vm-v1)*(u3-u1) - (um-u1)*(v3-v1) ) / denom;
	     			betaa  =   ( (um-u1)*(v2-v1) - (vm-v1)*(u2-u1) ) / denom;
	         		/*printf("alpha01= %f,betaa = %f ",alpha01,betaa);*/
	       			/* determination des coordonnees cartesiennes de l origine de la maille proche d une position d equilibre */
	       			xm = alpha * ( x02 - x01 )+ betaa * ( x03 - x01 ) + x01;
	       			ym = alpha * ( y02 - y01 )+ betaa * ( y03 - y01 ) + y01;
	         		/*trace des 6 fils a l interieur d une maille*/
	         		/*
				Line(((REEL) xm-0.08-binx) / (baxx-binx),((REEL) ym-biny) / (baxy-biny),((REEL) xm+0.08-binx) / (baxx-binx),((REEL) ym-biny) / (baxy-biny));
				Line(((REEL) xm-binx) / (baxx-binx),((REEL) ym-0.08-biny) / (baxy-biny),((REEL) xm-binx) / (baxx-binx),((REEL) ym+0.08-biny) / (baxy-biny));
				*/
				a1 = xm +vect_ux*1.0/6.0 +vect_vx*1.0/2.0;
				b1 = ym +vect_uy*1.0/6.0 +vect_vy*1.0/2.0;
				a2 = xm +vect_ux*0.0/6.0 +vect_vx*0.0/2.0;
				b2 = ym +vect_uy*0.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);

				a2 = xm +vect_ux*0.0/6.0 +vect_vx*2.0/2.0;
				b2 = ym +vect_uy*0.0/6.0 +vect_vy*2.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a2 = xm +vect_ux*3.0/6.0 +vect_vx*1.0/2.0;
				b2 = ym +vect_uy*3.0/6.0 +vect_vy*1.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a1 = xm +vect_ux*4.0/6.0 +vect_vx*2.0/2.0;
				b1 = ym +vect_uy*4.0/6.0 +vect_vy*2.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a1 = xm +vect_ux*4.0/6.0 +vect_vx*0.0/2.0;
				b1 = ym +vect_uy*4.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				a2 = xm +vect_ux*6.0/6.0 +vect_vx*0.0/2.0;
				b2 = ym +vect_uy*6.0/6.0 +vect_vy*0.0/2.0;
				trace_fil_hexa( a1,  b1,  a2,  b2,  x01,  y01,  x02,  y02,  x03,  y03);
				}
			}
		}
	}

void dessiner_fils_u_initial()
	{
	int ba,pa,deb,fin,no,pt1,pt2,pt3;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*printf("NOMBRE_SURFACES = %8d NOMBRE_ELEMENTS = %8d   \n",NOMBRE_SURFACES,NOMBRE_ELEMENTS);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if (pa == 0) printf("attention : pa = %8d no = %8d   \n",pa,no);
		if ((pa > 0) && (pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			for (deb=1;deb<=Surface[pa].nb_ufils;deb++)
				{ 
				TraceSegment(BLUE, (double) Surface[pa].f1_ux[deb], (double) Surface[pa].f1_uy[deb], (double) Surface[pa].f2_ux[deb], (double) Surface[pa].f2_uy[deb]);
				}
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			for (deb=1;deb<=Surf_Hexa[pa].nb_Ufils;deb++)
				{ 
				TraceSegment(BLUE, (double) Surf_Hexa[pa].f1_Ux[deb], (double) Surf_Hexa[pa].f1_Uy[deb], (double) Surf_Hexa[pa].f2_Ux[deb], (double) Surf_Hexa[pa].f2_Uy[deb]);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
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

void dessiner_fils_v_initial()
	{
	int ba,pa,deb,fin,no,pt1,pt2,pt3;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*printf("NOMBRE_SURFACES = %8d NOMBRE_ELEMENTS = %8d   \n",NOMBRE_SURFACES,NOMBRE_ELEMENTS);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if (pa == 0) printf("attention : pa = %8d no = %8d   \n",pa,no);
		if ((pa > 0) && (pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			for (deb=1;deb<=Surface[pa].nb_vfils;deb++)
				{ 
				TraceSegment(BLUE, (double) Surface[pa].f1_vx[deb], (double) Surface[pa].f1_vy[deb], (double) Surface[pa].f2_vx[deb], (double) Surface[pa].f2_vy[deb]);
				}
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			for (deb=1;deb<=Surf_Hexa[pa].nb_Vfils;deb++)
				{ 
				TraceSegment(BLUE, (double) Surf_Hexa[pa].f1_Vx[deb], (double) Surf_Hexa[pa].f1_Vy[deb], (double) Surf_Hexa[pa].f2_Vx[deb],	(double) Surf_Hexa[pa].f2_Vy[deb]);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA ) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA ;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			}
		if (pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA  + NOMBRE_ELEMENTS)
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA  - NOMBRE_ELEMENTS;
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

void dessiner_fils_uv_initial()
	{
	int ba,pa,deb,fin,no,pt1,pt2,pt3;

	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*printf("NOMBRE_SURFACES = %8d NOMBRE_ELEMENTS = %8d   \n",NOMBRE_SURFACES,NOMBRE_ELEMENTS);*/
	for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
		{ 
		pa = profondeur[no];
		if (pa == 0) printf("attention : pa = %8d no = %8d   \n",pa,no);
		if ((pa > 0) && (pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
			{
			pt1 = Surface[pa].extremite[1];
			pt2 = Surface[pa].extremite[2];
			pt3 = Surface[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			for (deb=1;deb<=Surface[pa].nb_ufils;deb++)
				{ 
				TraceSegment(BLUE, (double) Surface[pa].f1_ux[deb], (double) Surface[pa].f1_uy[deb], (double) Surface[pa].f2_ux[deb], (double) Surface[pa].f2_uy[deb]);
				}
			
			for (deb=1;deb<=Surface[pa].nb_vfils;deb++)
				{ 
				TraceSegment(BLUE, (double) Surface[pa].f1_vx[deb], (double) Surface[pa].f1_vy[deb], (double) Surface[pa].f2_vx[deb], (double) Surface[pa].f2_vy[deb]);
				}
			}
		if ((pa >  NOMBRE_SURFACES) && (pa <=  NOMBRE_SURFACES+NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES;
			pt1 = Surf_Hexa[pa].extremite[1];
			pt2 = Surf_Hexa[pa].extremite[2];
			pt3 = Surf_Hexa[pa].extremite[3];
		
			EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);
			TraceSegment(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
			TraceSegment(WHITE, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);
			
			for (deb=1;deb<=Surf_Hexa[pa].nb_Ufils;deb++)
				{ 
				TraceSegment(BLUE, (double) Surf_Hexa[pa].f1_Ux[deb], (double) Surf_Hexa[pa].f1_Uy[deb], (double) Surf_Hexa[pa].f2_Ux[deb], (double) Surf_Hexa[pa].f2_Uy[deb]);
				}
			
			for (deb=1;deb<=Surf_Hexa[pa].nb_Vfils;deb++)
				{ 
				TraceSegment(BLUE, (double) Surf_Hexa[pa].f1_Vx[deb], (double) Surf_Hexa[pa].f1_Vy[deb], (double) Surf_Hexa[pa].f2_Vx[deb],	(double) Surf_Hexa[pa].f2_Vy[deb]);
				}
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
			{
			pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
			deb = Element[pa].extremite[1];
			fin = Element[pa].extremite[2];
			TraceSegment(BLUE, Noeud[deb].x, Noeud[deb].y, Noeud[fin].x, Noeud[fin].y);
			}
		if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (Coulisse[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS].flag_dessin != 0))
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

void dessiner_surface_libre()
	{
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	TraceSegment(BLUE, surface_libre[1][1], surface_libre[2][1], surface_libre[1][2], surface_libre[2][2]);
	TraceSegment(BLUE, surface_libre[1][2], surface_libre[2][2], surface_libre[1][3], surface_libre[2][3]);
	TraceSegment(BLUE, surface_libre[1][3], surface_libre[2][3], surface_libre[1][4], surface_libre[2][4]);
	TraceSegment(BLUE, surface_libre[1][4], surface_libre[2][4], surface_libre[1][1], surface_libre[2][1]);
	
	TraceSegment(BLACK, surface_fond[1][1], surface_fond[2][1], surface_fond[1][2], surface_fond[2][2]);
	TraceSegment(BLACK, surface_fond[1][2], surface_fond[2][2], surface_fond[1][3], surface_fond[2][3]);
	TraceSegment(BLACK, surface_fond[1][3], surface_fond[2][3], surface_fond[1][4], surface_fond[2][4]);
	TraceSegment(BLACK, surface_fond[1][4], surface_fond[2][4], surface_fond[1][1], surface_fond[2][1]);
	/*
	printf("surface_libre[1][1] %8.2lf surface_libre[2][1] %8.2lf  surface_libre[3][1] %8.2lf \n",surface_libre[1][1],surface_libre[2][1],surface_libre[3][1]);
	printf("surface_libre[1][4] %8.2lf surface_libre[2][4] %8.2lf  surface_libre[3][4] %8.2lf \n",surface_libre[1][4],surface_libre[2][4],surface_libre[3][4]);
	printf("volume_value_dessine[1][1] %8.2lf volume_value_dessine[2][1] %8.2lf  volume_value_dessine[3][1] %8.2lf \n",volume_value_dessine[1][1],volume_value_dessine[2][1],volume_value_dessine[3][1]);
	printf("volume_value_dessine[1][7] %8.2lf volume_value_dessine[2][7] %8.2lf  volume_value_dessine[3][7] %8.2lf \n\n",volume_value_dessine[1][7],volume_value_dessine[2][7],volume_value_dessine[3][7]);
	EffaceTriangle(GREEN, volume_value_dessine[1][1], volume_value_dessine[2][1], volume_value_dessine[1][2], volume_value_dessine[2][2], volume_value_dessine[1][4], volume_value_dessine[2][4]);
	EffaceTriangle(GREEN, volume_value_dessine[1][2], volume_value_dessine[2][2], volume_value_dessine[1][3], volume_value_dessine[2][3], volume_value_dessine[1][4], volume_value_dessine[2][4]);
	*/	
	TraceSegment(BLACK, volume_value_dessine[1][1], volume_value_dessine[2][1], volume_value_dessine[1][2], volume_value_dessine[2][2]);
	TraceSegment(BLACK, volume_value_dessine[1][2], volume_value_dessine[2][2], volume_value_dessine[1][3], volume_value_dessine[2][3]);
	TraceSegment(BLACK, volume_value_dessine[1][3], volume_value_dessine[2][3], volume_value_dessine[1][4], volume_value_dessine[2][4]);
	TraceSegment(BLACK, volume_value_dessine[1][4], volume_value_dessine[2][4], volume_value_dessine[1][1], volume_value_dessine[2][1]);
	TraceSegment(BLACK, volume_value_dessine[1][5], volume_value_dessine[2][5], volume_value_dessine[1][6], volume_value_dessine[2][6]);
	TraceSegment(BLACK, volume_value_dessine[1][6], volume_value_dessine[2][6], volume_value_dessine[1][7], volume_value_dessine[2][7]);
	TraceSegment(BLACK, volume_value_dessine[1][7], volume_value_dessine[2][7], volume_value_dessine[1][8], volume_value_dessine[2][8]);
	TraceSegment(BLACK, volume_value_dessine[1][8], volume_value_dessine[2][8], volume_value_dessine[1][5], volume_value_dessine[2][5]);
	TraceSegment(BLACK, volume_value_dessine[1][1], volume_value_dessine[2][1], volume_value_dessine[1][5], volume_value_dessine[2][5]);
	TraceSegment(BLACK, volume_value_dessine[1][2], volume_value_dessine[2][2], volume_value_dessine[1][6], volume_value_dessine[2][6]);
	TraceSegment(BLACK, volume_value_dessine[1][3], volume_value_dessine[2][3], volume_value_dessine[1][7], volume_value_dessine[2][7]);
	TraceSegment(BLACK, volume_value_dessine[1][4], volume_value_dessine[2][4], volume_value_dessine[1][8], volume_value_dessine[2][8]);
	}

void dessiner_ballast_altitude()
	{
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	TraceSegment(RED, surface_ballast[1][1], surface_ballast[2][1], surface_ballast[1][2], surface_ballast[2][2]);
	TraceSegment(RED, surface_ballast[1][2], surface_ballast[2][2], surface_ballast[1][3], surface_ballast[2][3]);
	TraceSegment(RED, surface_ballast[1][3], surface_ballast[2][3], surface_ballast[1][4], surface_ballast[2][4]);
	TraceSegment(RED, surface_ballast[1][4], surface_ballast[2][4], surface_ballast[1][1], surface_ballast[2][1]);
	
	//TraceSegment(BLACK, volume_value_dessine[1][1], volume_value_dessine[2][1], volume_value_dessine[1][2], volume_value_dessine[2][2]);
	//TraceSegment(BLACK, volume_value_dessine[1][2], volume_value_dessine[2][2], volume_value_dessine[1][3], volume_value_dessine[2][3]);
	//TraceSegment(BLACK, volume_value_dessine[1][3], volume_value_dessine[2][3], volume_value_dessine[1][4], volume_value_dessine[2][4]);
	//TraceSegment(BLACK, volume_value_dessine[1][4], volume_value_dessine[2][4], volume_value_dessine[1][1], volume_value_dessine[2][1]);
	//TraceSegment(BLACK, volume_value_dessine[1][5], volume_value_dessine[2][5], volume_value_dessine[1][6], volume_value_dessine[2][6]);
	//TraceSegment(BLACK, volume_value_dessine[1][6], volume_value_dessine[2][6], volume_value_dessine[1][7], volume_value_dessine[2][7]);
	//TraceSegment(BLACK, volume_value_dessine[1][7], volume_value_dessine[2][7], volume_value_dessine[1][8], volume_value_dessine[2][8]);
	//TraceSegment(BLACK, volume_value_dessine[1][8], volume_value_dessine[2][8], volume_value_dessine[1][5], volume_value_dessine[2][5]);
	//TraceSegment(BLACK, volume_value_dessine[1][1], volume_value_dessine[2][1], volume_value_dessine[1][5], volume_value_dessine[2][5]);
	//TraceSegment(BLACK, volume_value_dessine[1][2], volume_value_dessine[2][2], volume_value_dessine[1][6], volume_value_dessine[2][6]);
	//TraceSegment(BLACK, volume_value_dessine[1][3], volume_value_dessine[2][3], volume_value_dessine[1][7], volume_value_dessine[2][7]);
	//TraceSegment(BLACK, volume_value_dessine[1][4], volume_value_dessine[2][4], volume_value_dessine[1][8], volume_value_dessine[2][8]);
	}

void dessiner_cube_size()
	{
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	double volume, size,x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4,x5,y5,z5,x6,y6,z6,x7,y7,z7,x8,y8,z8;
	double vect1[4],vect2[4],vect3[4],length,diameter,period;
	int no,deb,fin,vertex1,vertex2,vertex3,condition,flag,panel;



	for (no=1;no<=NOMBRE_SURFACES;no++)
		{
		if (panneau[Surface[no].type].flag_dessin != 0)

			{
			//printf("TypeElement[Element[%d].type].flag_dessin %d\n",no,TypeElement[Element[no].type].flag_dessin);		
			vertex1 = Surface[no].extremite[1];
			vertex2 = Surface[no].extremite[2];
			vertex3 = Surface[no].extremite[3];
			volume = Surface[no].lgrepos * PI * Surface[no].diametrehydro * Surface[no].diametrehydro / 4.0 * 2.0 * Surface[no].nb_ufils;
			size = pow(volume/3.0, 1.0/3.0);

			vect1[1]=size/2.0;	vect1[2]=0;		vect1[3]=0;
			vect2[1]=0;		vect2[2]=size/2.0;	vect2[3]=0;
			vect3[1]=0;		vect3[2]=0;		vect3[3]=size/2.0;

			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);


			x1 = Noeud[vertex1].x + vect1[1] - vect2[1] - vect3[1];
			y1 = Noeud[vertex1].y + vect1[2] - vect2[2] - vect3[2];
			z1 = Noeud[vertex1].z + vect1[3] - vect2[3] - vect3[3];

			x2 = Noeud[vertex1].x + vect1[1] + vect2[1] - vect3[1];
			y2 = Noeud[vertex1].y + vect1[2] + vect2[2] - vect3[2];
			z2 = Noeud[vertex1].z + vect1[3] + vect2[3] - vect3[3];

			x3 = Noeud[vertex1].x - vect1[1] + vect2[1] - vect3[1];
			y3 = Noeud[vertex1].y - vect1[2] + vect2[2] - vect3[2];
			z3 = Noeud[vertex1].z - vect1[3] + vect2[3] - vect3[3];

			x4 = Noeud[vertex1].x - vect1[1] - vect2[1] - vect3[1];
			y4 = Noeud[vertex1].y - vect1[2] - vect2[2] - vect3[2];
			z4 = Noeud[vertex1].z - vect1[3] - vect2[3] - vect3[3];

			x5 = Noeud[vertex1].x + vect1[1] - vect2[1] + vect3[1];
			y5 = Noeud[vertex1].y + vect1[2] - vect2[2] + vect3[2];
			z5 = Noeud[vertex1].z + vect1[3] - vect2[3] + vect3[3];

			x6 = Noeud[vertex1].x + vect1[1] + vect2[1] + vect3[1];
			y6 = Noeud[vertex1].y + vect1[2] + vect2[2] + vect3[2];
			z6 = Noeud[vertex1].z + vect1[3] + vect2[3] + vect3[3];

			x7 = Noeud[vertex1].x - vect1[1] + vect2[1] + vect3[1];
			y7 = Noeud[vertex1].y - vect1[2] + vect2[2] + vect3[2];
			z7 = Noeud[vertex1].z - vect1[3] + vect2[3] + vect3[3];

			x8 = Noeud[vertex1].x - vect1[1] - vect2[1] + vect3[1];
			y8 = Noeud[vertex1].y - vect1[2] - vect2[2] + vect3[2];
			z8 = Noeud[vertex1].z - vect1[3] - vect2[3] + vect3[3];

			if ((z1 >= z2) && (z1 >= z3) && (z1 >= z4) && (z1 >= z5) && (z1 >= z6) && (z1 >= z7) && (z1 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x6, y6, x5, y5);
				//EffaceQuadrangle(WHITE, x1, y1, x5, y5, x8, y8, x4, y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z2 >= z1) && (z2 >= z3) && (z2 >= z4) && (z2 >= z5) && (z2 >= z6) && (z2 >= z7) && (z2 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x2, y2, x3, y3, x7, y7, x6, y6);
				//EffaceQuadrangle(WHITE, x2, y2, x6, y6, x5, y5, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				}
			if ((z3 >= z1) && (z3 >= z2) && (z3 >= z4) && (z3 >= z5) && (z3 >= z6) && (z3 >= z7) && (z3 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x7, y7, x8, y8, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x2, y2, x6, y6, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				}
			if ((z4 >= z1) && (z4 >= z2) && (z4 >= z3) && (z4 >= z5) && (z4 >= z6) && (z4 >= z7) && (z4 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x4, y4, x1, y1, x5, y5, x8, y8);
				//EffaceQuadrangle(WHITE, x4, y4, x8, y8, x7, y7, x3, y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z5 >= z1) && (z5 >= z2) && (z5 >= z3) && (z5 >= z4) && (z5 >= z6) && (z5 >= z7) && (z5 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x2, y2, x1, y1);
				//EffaceQuadrangle(WHITE, x5, y5, x8, y8, x4, y4, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}
			if ((z6 >= z1) && (z6 >= z2) && (z6 >= z3) && (z6 >= z4) && (z6 >= z5) && (z6 >= z7) && (z6 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x6, y6, x5, y5, x1, y1, x2, y2);
				//EffaceQuadrangle(WHITE, x6, y6, x7, y7, x3, y3, x2, y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				}
			if ((z7 >= z1) && (z7 >= z2) && (z7 >= z3) && (z7 >= z4) && (z7 >= z5) && (z7 >= z6) && (z7 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x2, y2, x6, y6);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x4, y4, x8, y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				}
			if ((z8 >= z1) && (z8 >= z2) && (z8 >= z3) && (z8 >= z4) && (z8 >= z5) && (z8 >= z6) && (z8 >= z7))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x1, y1, x5, y5);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x3, y3, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}		
				
			x1 = Noeud[vertex2].x + vect1[1] - vect2[1] - vect3[1];
			y1 = Noeud[vertex2].y + vect1[2] - vect2[2] - vect3[2];
			z1 = Noeud[vertex2].z + vect1[3] - vect2[3] - vect3[3];

			x2 = Noeud[vertex2].x + vect1[1] + vect2[1] - vect3[1];
			y2 = Noeud[vertex2].y + vect1[2] + vect2[2] - vect3[2];
			z2 = Noeud[vertex2].z + vect1[3] + vect2[3] - vect3[3];

			x3 = Noeud[vertex2].x - vect1[1] + vect2[1] - vect3[1];
			y3 = Noeud[vertex2].y - vect1[2] + vect2[2] - vect3[2];
			z3 = Noeud[vertex2].z - vect1[3] + vect2[3] - vect3[3];

			x4 = Noeud[vertex2].x - vect1[1] - vect2[1] - vect3[1];
			y4 = Noeud[vertex2].y - vect1[2] - vect2[2] - vect3[2];
			z4 = Noeud[vertex2].z - vect1[3] - vect2[3] - vect3[3];

			x5 = Noeud[vertex2].x + vect1[1] - vect2[1] + vect3[1];
			y5 = Noeud[vertex2].y + vect1[2] - vect2[2] + vect3[2];
			z5 = Noeud[vertex2].z + vect1[3] - vect2[3] + vect3[3];

			x6 = Noeud[vertex2].x + vect1[1] + vect2[1] + vect3[1];
			y6 = Noeud[vertex2].y + vect1[2] + vect2[2] + vect3[2];
			z6 = Noeud[vertex2].z + vect1[3] + vect2[3] + vect3[3];

			x7 = Noeud[vertex2].x - vect1[1] + vect2[1] + vect3[1];
			y7 = Noeud[vertex2].y - vect1[2] + vect2[2] + vect3[2];
			z7 = Noeud[vertex2].z - vect1[3] + vect2[3] + vect3[3];

			x8 = Noeud[vertex2].x - vect1[1] - vect2[1] + vect3[1];
			y8 = Noeud[vertex2].y - vect1[2] - vect2[2] + vect3[2];
			z8 = Noeud[vertex2].z - vect1[3] - vect2[3] + vect3[3];

			if ((z1 >= z2) && (z1 >= z3) && (z1 >= z4) && (z1 >= z5) && (z1 >= z6) && (z1 >= z7) && (z1 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x6, y6, x5, y5);
				//EffaceQuadrangle(WHITE, x1, y1, x5, y5, x8, y8, x4, y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z2 >= z1) && (z2 >= z3) && (z2 >= z4) && (z2 >= z5) && (z2 >= z6) && (z2 >= z7) && (z2 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x2, y2, x3, y3, x7, y7, x6, y6);
				//EffaceQuadrangle(WHITE, x2, y2, x6, y6, x5, y5, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				}
			if ((z3 >= z1) && (z3 >= z2) && (z3 >= z4) && (z3 >= z5) && (z3 >= z6) && (z3 >= z7) && (z3 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x7, y7, x8, y8, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x2, y2, x6, y6, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				}
			if ((z4 >= z1) && (z4 >= z2) && (z4 >= z3) && (z4 >= z5) && (z4 >= z6) && (z4 >= z7) && (z4 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x4, y4, x1, y1, x5, y5, x8, y8);
				//EffaceQuadrangle(WHITE, x4, y4, x8, y8, x7, y7, x3, y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z5 >= z1) && (z5 >= z2) && (z5 >= z3) && (z5 >= z4) && (z5 >= z6) && (z5 >= z7) && (z5 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x2, y2, x1, y1);
				//EffaceQuadrangle(WHITE, x5, y5, x8, y8, x4, y4, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}
			if ((z6 >= z1) && (z6 >= z2) && (z6 >= z3) && (z6 >= z4) && (z6 >= z5) && (z6 >= z7) && (z6 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x6, y6, x5, y5, x1, y1, x2, y2);
				//EffaceQuadrangle(WHITE, x6, y6, x7, y7, x3, y3, x2, y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				}
			if ((z7 >= z1) && (z7 >= z2) && (z7 >= z3) && (z7 >= z4) && (z7 >= z5) && (z7 >= z6) && (z7 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x2, y2, x6, y6);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x4, y4, x8, y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				}
			if ((z8 >= z1) && (z8 >= z2) && (z8 >= z3) && (z8 >= z4) && (z8 >= z5) && (z8 >= z6) && (z8 >= z7))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x1, y1, x5, y5);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x3, y3, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}
			x1 = Noeud[vertex3].x + vect1[1] - vect2[1] - vect3[1];
			y1 = Noeud[vertex3].y + vect1[2] - vect2[2] - vect3[2];
			z1 = Noeud[vertex3].z + vect1[3] - vect2[3] - vect3[3];

			x2 = Noeud[vertex3].x + vect1[1] + vect2[1] - vect3[1];
			y2 = Noeud[vertex3].y + vect1[2] + vect2[2] - vect3[2];
			z2 = Noeud[vertex3].z + vect1[3] + vect2[3] - vect3[3];

			x3 = Noeud[vertex3].x - vect1[1] + vect2[1] - vect3[1];
			y3 = Noeud[vertex3].y - vect1[2] + vect2[2] - vect3[2];
			z3 = Noeud[vertex3].z - vect1[3] + vect2[3] - vect3[3];

			x4 = Noeud[vertex3].x - vect1[1] - vect2[1] - vect3[1];
			y4 = Noeud[vertex3].y - vect1[2] - vect2[2] - vect3[2];
			z4 = Noeud[vertex3].z - vect1[3] - vect2[3] - vect3[3];

			x5 = Noeud[vertex3].x + vect1[1] - vect2[1] + vect3[1];
			y5 = Noeud[vertex3].y + vect1[2] - vect2[2] + vect3[2];
			z5 = Noeud[vertex3].z + vect1[3] - vect2[3] + vect3[3];

			x6 = Noeud[vertex3].x + vect1[1] + vect2[1] + vect3[1];
			y6 = Noeud[vertex3].y + vect1[2] + vect2[2] + vect3[2];
			z6 = Noeud[vertex3].z + vect1[3] + vect2[3] + vect3[3];

			x7 = Noeud[vertex3].x - vect1[1] + vect2[1] + vect3[1];
			y7 = Noeud[vertex3].y - vect1[2] + vect2[2] + vect3[2];
			z7 = Noeud[vertex3].z - vect1[3] + vect2[3] + vect3[3];

			x8 = Noeud[vertex3].x - vect1[1] - vect2[1] + vect3[1];
			y8 = Noeud[vertex3].y - vect1[2] - vect2[2] + vect3[2];
			z8 = Noeud[vertex3].z - vect1[3] - vect2[3] + vect3[3];

			if ((z1 >= z2) && (z1 >= z3) && (z1 >= z4) && (z1 >= z5) && (z1 >= z6) && (z1 >= z7) && (z1 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x6, y6, x5, y5);
				//EffaceQuadrangle(WHITE, x1, y1, x5, y5, x8, y8, x4, y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z2 >= z1) && (z2 >= z3) && (z2 >= z4) && (z2 >= z5) && (z2 >= z6) && (z2 >= z7) && (z2 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x2, y2, x3, y3, x7, y7, x6, y6);
				//EffaceQuadrangle(WHITE, x2, y2, x6, y6, x5, y5, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				}
			if ((z3 >= z1) && (z3 >= z2) && (z3 >= z4) && (z3 >= z5) && (z3 >= z6) && (z3 >= z7) && (z3 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x7, y7, x8, y8, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x2, y2, x6, y6, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				}
			if ((z4 >= z1) && (z4 >= z2) && (z4 >= z3) && (z4 >= z5) && (z4 >= z6) && (z4 >= z7) && (z4 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x4, y4, x1, y1, x5, y5, x8, y8);
				//EffaceQuadrangle(WHITE, x4, y4, x8, y8, x7, y7, x3, y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z5 >= z1) && (z5 >= z2) && (z5 >= z3) && (z5 >= z4) && (z5 >= z6) && (z5 >= z7) && (z5 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x2, y2, x1, y1);
				//EffaceQuadrangle(WHITE, x5, y5, x8, y8, x4, y4, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}
			if ((z6 >= z1) && (z6 >= z2) && (z6 >= z3) && (z6 >= z4) && (z6 >= z5) && (z6 >= z7) && (z6 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x6, y6, x5, y5, x1, y1, x2, y2);
				//EffaceQuadrangle(WHITE, x6, y6, x7, y7, x3, y3, x2, y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				}
			if ((z7 >= z1) && (z7 >= z2) && (z7 >= z3) && (z7 >= z4) && (z7 >= z5) && (z7 >= z6) && (z7 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x2, y2, x6, y6);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x4, y4, x8, y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				}
			if ((z8 >= z1) && (z8 >= z2) && (z8 >= z3) && (z8 >= z4) && (z8 >= z5) && (z8 >= z6) && (z8 >= z7))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x1, y1, x5, y5);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x3, y3, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}
			}
		}	
	for (no=1;no<=NOMBRE_ELEMENTS;no++)
		{
		condition = 0;	//not draw
		if(Element[no].type > 0)
			{
			//the bar belongs to a cable
			if ((TypeElement[Element[no].type].flag_dessin != 0) && (Element[no].flag_dessin != 0))
				{	
				condition = 1;	//draw
				flag = Element[no].flag_dessin;
				volume = Element[no].lgrepos * PI * Element[no].diametrehydro * Element[no].diametrehydro / 4.0;
				}
			}
		else
			{
			//the bar belongs to a panel
			if (panneau[-Element[no].type].flag_dessin != 0)
				{	
				condition = 1;	//draw
				flag = panneau[-Element[no].type].flag_dessin;
				panel = -Element[no].type;
				length = (Element[no].pro[2] - Element[no].pro[1]) * panneau[panel].longueur_repos;
				period = (double)panneau[panel].netting_2_ropes_period;
				diameter = panneau[panel].diam_hydro * sqrt(period);
				volume = length * PI * diameter * diameter / 4.0;
				//printf("panneau[panel].longueur_repos %lf panneau[panel].diam_hydro %lf netting_2_ropes_gap_U %d\n",panneau[panel].longueur_repos,panneau[panel].diam_hydro,panneau[panel].netting_2_ropes_period);		
				//printf("period %lf\n",period);
				//printf("no %d condition %d flag %d panel %d length %lf diameter %lf volume %lf\n",no,condition,flag,panel,length,diameter,volume);		
				}
			}
		if ((condition == 1) && (flag != 0))
			{
			//printf("TypeElement[Element[%d].type].flag_dessin %d\n",no,TypeElement[Element[no].type].flag_dessin);		
			deb = Element[no].extremite[1];
			fin = Element[no].extremite[2];
			volume = Element[no].lgrepos * PI * Element[no].diametrehydro * Element[no].diametrehydro / 4.0;
			size = pow(volume/2.0, 1.0/3.0);

			vect1[1]=size/2.0;	vect1[2]=0;		vect1[3]=0;
			vect2[1]=0;		vect2[2]=size/2.0;	vect2[3]=0;
			vect3[1]=0;		vect3[2]=0;		vect3[3]=size/2.0;

			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
			base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);


			x1 = Noeud[deb].x + vect1[1] - vect2[1] - vect3[1];
			y1 = Noeud[deb].y + vect1[2] - vect2[2] - vect3[2];
			z1 = Noeud[deb].z + vect1[3] - vect2[3] - vect3[3];

			x2 = Noeud[deb].x + vect1[1] + vect2[1] - vect3[1];
			y2 = Noeud[deb].y + vect1[2] + vect2[2] - vect3[2];
			z2 = Noeud[deb].z + vect1[3] + vect2[3] - vect3[3];

			x3 = Noeud[deb].x - vect1[1] + vect2[1] - vect3[1];
			y3 = Noeud[deb].y - vect1[2] + vect2[2] - vect3[2];
			z3 = Noeud[deb].z - vect1[3] + vect2[3] - vect3[3];

			x4 = Noeud[deb].x - vect1[1] - vect2[1] - vect3[1];
			y4 = Noeud[deb].y - vect1[2] - vect2[2] - vect3[2];
			z4 = Noeud[deb].z - vect1[3] - vect2[3] - vect3[3];

			x5 = Noeud[deb].x + vect1[1] - vect2[1] + vect3[1];
			y5 = Noeud[deb].y + vect1[2] - vect2[2] + vect3[2];
			z5 = Noeud[deb].z + vect1[3] - vect2[3] + vect3[3];

			x6 = Noeud[deb].x + vect1[1] + vect2[1] + vect3[1];
			y6 = Noeud[deb].y + vect1[2] + vect2[2] + vect3[2];
			z6 = Noeud[deb].z + vect1[3] + vect2[3] + vect3[3];

			x7 = Noeud[deb].x - vect1[1] + vect2[1] + vect3[1];
			y7 = Noeud[deb].y - vect1[2] + vect2[2] + vect3[2];
			z7 = Noeud[deb].z - vect1[3] + vect2[3] + vect3[3];

			x8 = Noeud[deb].x - vect1[1] - vect2[1] + vect3[1];
			y8 = Noeud[deb].y - vect1[2] - vect2[2] + vect3[2];
			z8 = Noeud[deb].z - vect1[3] - vect2[3] + vect3[3];

			if ((z1 >= z2) && (z1 >= z3) && (z1 >= z4) && (z1 >= z5) && (z1 >= z6) && (z1 >= z7) && (z1 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x6, y6, x5, y5);
				//EffaceQuadrangle(WHITE, x1, y1, x5, y5, x8, y8, x4, y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z2 >= z1) && (z2 >= z3) && (z2 >= z4) && (z2 >= z5) && (z2 >= z6) && (z2 >= z7) && (z2 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x2, y2, x3, y3, x7, y7, x6, y6);
				//EffaceQuadrangle(WHITE, x2, y2, x6, y6, x5, y5, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				}
			if ((z3 >= z1) && (z3 >= z2) && (z3 >= z4) && (z3 >= z5) && (z3 >= z6) && (z3 >= z7) && (z3 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x7, y7, x8, y8, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x2, y2, x6, y6, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				}
			if ((z4 >= z1) && (z4 >= z2) && (z4 >= z3) && (z4 >= z5) && (z4 >= z6) && (z4 >= z7) && (z4 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x4, y4, x1, y1, x5, y5, x8, y8);
				//EffaceQuadrangle(WHITE, x4, y4, x8, y8, x7, y7, x3, y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z5 >= z1) && (z5 >= z2) && (z5 >= z3) && (z5 >= z4) && (z5 >= z6) && (z5 >= z7) && (z5 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x2, y2, x1, y1);
				//EffaceQuadrangle(WHITE, x5, y5, x8, y8, x4, y4, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}
			if ((z6 >= z1) && (z6 >= z2) && (z6 >= z3) && (z6 >= z4) && (z6 >= z5) && (z6 >= z7) && (z6 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x6, y6, x5, y5, x1, y1, x2, y2);
				//EffaceQuadrangle(WHITE, x6, y6, x7, y7, x3, y3, x2, y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				}
			if ((z7 >= z1) && (z7 >= z2) && (z7 >= z3) && (z7 >= z4) && (z7 >= z5) && (z7 >= z6) && (z7 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x2, y2, x6, y6);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x4, y4, x8, y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				}
			if ((z8 >= z1) && (z8 >= z2) && (z8 >= z3) && (z8 >= z4) && (z8 >= z5) && (z8 >= z6) && (z8 >= z7))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x1, y1, x5, y5);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x3, y3, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}		
				
			x1 = Noeud[fin].x + vect1[1] - vect2[1] - vect3[1];
			y1 = Noeud[fin].y + vect1[2] - vect2[2] - vect3[2];
			z1 = Noeud[fin].z + vect1[3] - vect2[3] - vect3[3];

			x2 = Noeud[fin].x + vect1[1] + vect2[1] - vect3[1];
			y2 = Noeud[fin].y + vect1[2] + vect2[2] - vect3[2];
			z2 = Noeud[fin].z + vect1[3] + vect2[3] - vect3[3];

			x3 = Noeud[fin].x - vect1[1] + vect2[1] - vect3[1];
			y3 = Noeud[fin].y - vect1[2] + vect2[2] - vect3[2];
			z3 = Noeud[fin].z - vect1[3] + vect2[3] - vect3[3];

			x4 = Noeud[fin].x - vect1[1] - vect2[1] - vect3[1];
			y4 = Noeud[fin].y - vect1[2] - vect2[2] - vect3[2];
			z4 = Noeud[fin].z - vect1[3] - vect2[3] - vect3[3];

			x5 = Noeud[fin].x + vect1[1] - vect2[1] + vect3[1];
			y5 = Noeud[fin].y + vect1[2] - vect2[2] + vect3[2];
			z5 = Noeud[fin].z + vect1[3] - vect2[3] + vect3[3];

			x6 = Noeud[fin].x + vect1[1] + vect2[1] + vect3[1];
			y6 = Noeud[fin].y + vect1[2] + vect2[2] + vect3[2];
			z6 = Noeud[fin].z + vect1[3] + vect2[3] + vect3[3];

			x7 = Noeud[fin].x - vect1[1] + vect2[1] + vect3[1];
			y7 = Noeud[fin].y - vect1[2] + vect2[2] + vect3[2];
			z7 = Noeud[fin].z - vect1[3] + vect2[3] + vect3[3];

			x8 = Noeud[fin].x - vect1[1] - vect2[1] + vect3[1];
			y8 = Noeud[fin].y - vect1[2] - vect2[2] + vect3[2];
			z8 = Noeud[fin].z - vect1[3] - vect2[3] + vect3[3];

			if ((z1 >= z2) && (z1 >= z3) && (z1 >= z4) && (z1 >= z5) && (z1 >= z6) && (z1 >= z7) && (z1 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x6, y6, x5, y5);
				//EffaceQuadrangle(WHITE, x1, y1, x5, y5, x8, y8, x4, y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z2 >= z1) && (z2 >= z3) && (z2 >= z4) && (z2 >= z5) && (z2 >= z6) && (z2 >= z7) && (z2 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x2, y2, x3, y3, x7, y7, x6, y6);
				//EffaceQuadrangle(WHITE, x2, y2, x6, y6, x5, y5, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				}
			if ((z3 >= z1) && (z3 >= z2) && (z3 >= z4) && (z3 >= z5) && (z3 >= z6) && (z3 >= z7) && (z3 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x7, y7, x8, y8, x4, y4);
				//EffaceQuadrangle(WHITE, x3, y3, x2, y2, x6, y6, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				}
			if ((z4 >= z1) && (z4 >= z2) && (z4 >= z3) && (z4 >= z5) && (z4 >= z6) && (z4 >= z7) && (z4 >= z8))
				{
				//EffaceQuadrangle(WHITE, x1, y1, x2, y2, x3, y3, x4, y4);
				//EffaceQuadrangle(WHITE, x4, y4, x1, y1, x5, y5, x8, y8);
				//EffaceQuadrangle(WHITE, x4, y4, x8, y8, x7, y7, x3, y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				}
			if ((z5 >= z1) && (z5 >= z2) && (z5 >= z3) && (z5 >= z4) && (z5 >= z6) && (z5 >= z7) && (z5 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x2, y2, x1, y1);
				//EffaceQuadrangle(WHITE, x5, y5, x8, y8, x4, y4, x1, y1);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}
			if ((z6 >= z1) && (z6 >= z2) && (z6 >= z3) && (z6 >= z4) && (z6 >= z5) && (z6 >= z7) && (z6 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x6, y6, x5, y5, x1, y1, x2, y2);
				//EffaceQuadrangle(WHITE, x6, y6, x7, y7, x3, y3, x2, y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x2,y2);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				}
			if ((z7 >= z1) && (z7 >= z2) && (z7 >= z3) && (z7 >= z4) && (z7 >= z5) && (z7 >= z6) && (z7 >= z8))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x2, y2, x6, y6);
				//EffaceQuadrangle(WHITE, x7, y7, x3, y3, x4, y4, x8, y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x2,y2,x3,y3);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				}
			if ((z8 >= z1) && (z8 >= z2) && (z8 >= z3) && (z8 >= z4) && (z8 >= z5) && (z8 >= z6) && (z8 >= z7))
				{
				//EffaceQuadrangle(WHITE, x5, y5, x6, y6, x7, y7, x8, y8);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x1, y1, x5, y5);
				//EffaceQuadrangle(WHITE, x8, y8, x4, y4, x3, y3, x7, y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x5,y5,x6,y6);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x6,y6,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x7,y7,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x8,y8,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x1,y1,x5,y5);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x7,y7);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x8,y8);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x3,y3,x4,y4);
				TraceSegment(TypeElement[Element[no].type].flag_dessin,x4,y4,x1,y1);
				}
			}
		}	
	}

void dessiner_surface_front()
	{
	int zi,nb_teta;
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	char chaine[7];

	TraceSegment(GREEN, surface_front_dessine[1][1], surface_front_dessine[2][1], surface_front_dessine[1][2], surface_front_dessine[2][2]);
	TraceSegment(GREEN, surface_front_dessine[1][2], surface_front_dessine[2][2], surface_front_dessine[1][3], surface_front_dessine[2][3]);
	TraceSegment(GREEN, surface_front_dessine[1][3], surface_front_dessine[2][3], surface_front_dessine[1][4], surface_front_dessine[2][4]);
	TraceSegment(GREEN, surface_front_dessine[1][4], surface_front_dessine[2][4], surface_front_dessine[1][1], surface_front_dessine[2][1]);
	TraceSegment(BLACK, surface_front_dessine[1][1], surface_front_dessine[2][1], surface_front_dessine[1][2], surface_front_dessine[2][2]);
	TraceSegment(BLACK, surface_front_dessine[1][2], surface_front_dessine[2][2], surface_front_dessine[1][3], surface_front_dessine[2][3]);
	TraceSegment(BLACK, surface_front_dessine[1][3], surface_front_dessine[2][3], surface_front_dessine[1][4], surface_front_dessine[2][4]);
	TraceSegment(BLACK, surface_front_dessine[1][4], surface_front_dessine[2][4], surface_front_dessine[1][1], surface_front_dessine[2][1]);

	if (Sortie_texte.inner_surface == 1)
		{
		nb_teta = 20;
  		for (zi = 1; zi<= nb_teta; zi++)
  			{
			TraceSegment(BLACK, surface_inner_dessine[1][zi-1], surface_inner_dessine[2][zi-1], surface_inner_dessine[1][zi], surface_inner_dessine[2][zi]);
			}
		}
	if (Sortie_texte.inner_surface_triangulation == 1)
		{
  		for (zi = 1; zi<= Prise.nb_triangles; zi++)
  			{
			TraceSegment(RED, Prise.xx[Prise.vertex_1[zi]], Prise.yy[Prise.vertex_1[zi]], Prise.xx[Prise.vertex_2[zi]], Prise.yy[Prise.vertex_2[zi]]);
			TraceSegment(RED, Prise.xx[Prise.vertex_2[zi]], Prise.yy[Prise.vertex_2[zi]], Prise.xx[Prise.vertex_3[zi]], Prise.yy[Prise.vertex_3[zi]]);
			TraceSegment(RED, Prise.xx[Prise.vertex_3[zi]], Prise.yy[Prise.vertex_3[zi]], Prise.xx[Prise.vertex_1[zi]], Prise.yy[Prise.vertex_1[zi]]);
			}
		}
	}

void dessiner_axes()
	{
	int expx,nbbasex,nbticks;
	double Xmin,Xmax,Ymin,Ymax,basex;
  	char chaine[7];
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*extremites des axes*/
	if (1.0+2.0*marge == 0.0){printf("1.0+2.0*marge = 0.0   \n");exit(0);}
	Xmin = ((1.0+marge)*binx + marge*baxx) / (1.0+2.0*marge);
	Xmax = ((1.0+marge)*baxx + marge*binx) / (1.0+2.0*marge);
	Ymin = ((1.0+marge)*biny + marge*baxy) / (1.0+2.0*marge);
	Ymax = ((1.0+marge)*baxy + marge*biny) / (1.0+2.0*marge);
	/*Ymax = Ymin + 60;*/
	/*Ymax = Ymin + 1.0 / (1.0+2.0*marge) * (baxy - biny) / 5.0;*/
	
	printf("Xmin %8.2f Ymin %8.2f   ",Xmin,Ymin);
	printf("Xmax %8.2f Ymax %8.2f \n",Xmax,Ymax);
	
	/*printf("binx %8.2f biny %8.2f   ",binx,biny);
	printf("baxx %8.2f baxy %8.2f \n",baxx,baxy);
 	
 	printf("cinx %8.2f ciny %8.2f   ",cinx,ciny);
	printf("caxx %8.2f caxy %8.2f \n",caxx,caxy);*/
 	
	/*calcul des ticks X*/
	expx = (int) floor(log10(Xmax-Xmin));
	basex = (float) pow(10.0,(double)expx);
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Xmax-Xmin) / basex);
	
	/*printf("Xmax-Xmin = %8.2f  ",Xmax-Xmin);
	printf("expx = %4d  ",expx);
	printf("basex = %8.2f  ",basex);
	printf("nbbasex = %4d  ",nbbasex);*/
	
	if ((nbbasex>=2) && (nbbasex<4)) 	basex = basex / 2.0;
	if ( nbbasex<2) 			basex = basex / 5.0;
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Xmax-Xmin) / basex);
	
	/*printf("basex = %8.2f  ",basex);
	printf("nbbasex = %4d  \n",nbbasex);*/
	
	/*trace des ticks selon l axe X*/
	Color(BLACK);
	for (nbticks=0;nbticks<=nbbasex;nbticks++)
		{ 
		TraceSegment(BLACK, Xmin + nbticks * basex, Ymin, Xmin + nbticks * basex, Ymin + (baxy - biny) * marge * 0.25);
    		sprintf(chaine,"%5.2f",nbticks * basex);
		EcritText(BLACK, Xmin + nbticks * basex, Ymin - (baxy - biny) * marge * 0.5, chaine, 0.0);
		}
	
	
	/*calcul des ticks Y*/
	expx = (int) floor(log10(Ymax-Ymin));
	basex = (float) pow(10.0,(double)expx);
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Ymax-Ymin) / basex);
	
	/*printf("Xmax-Xmin = %8.2f  ",Ymax-Ymin);
	printf("expx = %4d  ",expx);
	printf("basex = %8.2f  ",basex);
	printf("nbbasex = %4d  ",nbbasex);*/

	if ((nbbasex>=2) && (nbbasex<4)) 	basex = basex / 2.0;
	if ( nbbasex<2) 			basex = basex / 5.0;
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Ymax-Ymin) / basex);
	
	/*printf("basex = %8.2f  ",basex);
	printf("nbbasex = %4d  \n",nbbasex);*/
	
	/*trace des ticks selon l axe Y*/
	Color(BLACK);
	for (nbticks=1;nbticks<=nbbasex;nbticks++)
		{ 
		TraceSegment(BLACK, Xmin, Ymin + nbticks * basex, Xmin + (baxx - binx) * marge * 0.25, Ymin + nbticks * basex);
    		sprintf(chaine,"%5.2f",nbticks * basex);
		EcritText(BLACK, Xmin - (baxx - binx) * marge * 0.9, Ymin + nbticks * basex, chaine, 0.0);
		}
	
	/*trace des axes*/
	TraceSegment(BLACK, Xmin, Ymin, Xmax, Ymin);
	TraceSegment(BLACK, Xmin, Ymin, Xmin, Ymax);
	}

void dessiner_repere()
	{
	extern void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	TraceSegment(RED, repere[1][1], repere[2][1], repere[1][2], repere[2][2]);
	TraceSegment(RED, repere[1][1], repere[2][1], repere[1][3], repere[2][3]);
	TraceSegment(RED, repere[1][1], repere[2][1], repere[1][4], repere[2][4]);
	
	EcritText(RED, (double) repere[1][2], (double) repere[2][2], "x", (1.0 * 0.00));
	EcritText(RED, (double) repere[1][3], (double) repere[2][3], "y", (1.0 * 0.00));
	EcritText(RED, (double) repere[1][4], (double) repere[2][4], "z", (1.0 * 0.00));
	}

void dessiner_quadrillage()
	{
	int expx,nbbasex,nbticks;
	double Xmin,Xmax,Ymin,Ymax,basex;
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);
	
	/*extremites des axes*/
	if (1.0+2.0*marge == 0.0){printf("1.0+2.0*marge = 0.0   \n");exit(0);}
	Xmin = ((1.0+marge)*binx + marge*baxx) / (1.0+2.0*marge);
	Xmax = ((1.0+marge)*baxx + marge*binx) / (1.0+2.0*marge);
	Ymin = ((1.0+marge)*biny + marge*baxy) / (1.0+2.0*marge);
	Ymax = ((1.0+marge)*baxy + marge*biny) / (1.0+2.0*marge);
	
	/*calcul des ticks X*/
	expx = (int) floor(log10(Xmax-Xmin));
	basex = (float) pow(10.0,(double)expx);
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Xmax-Xmin) / basex);
	
	if ((nbbasex>=2) && (nbbasex<4)) 	basex = basex / 2.0;
	if ( nbbasex<2) 			basex = basex / 5.0;
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Xmax-Xmin) / basex);
	
	/*trace des ticks selon l axe X*/
	Color(BLACK);
	for (nbticks=0;nbticks<=nbbasex;nbticks++)
		{ 
		TraceSegment(BLACK, Xmin + nbticks * basex, Ymin, Xmin + nbticks * basex, Ymax);
		}
	
	
	/*calcul des ticks Y*/
	expx = (int) floor(log10(Ymax-Ymin));
	basex = (float) pow(10.0,(double)expx);
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Ymax-Ymin) / basex);
	

	if ((nbbasex>=2) && (nbbasex<4)) 	basex = basex / 2.0;
	if ( nbbasex<2) 			basex = basex / 5.0;
	if (basex == 0.0){printf("basex = 0.0   \n");exit(0);}
	nbbasex = (int) ((Ymax-Ymin) / basex);
	
	/*trace des ticks selon l axe Y*/
	Color(BLACK);
	for (nbticks=0;nbticks<=nbbasex;nbticks++)
		{ 
		TraceSegment(BLACK, Xmin, Ymin + nbticks * basex, Xmax, Ymin + nbticks * basex);
		}
	}
	
	
void draw_twines(int pa, float ua, float xa, float ya, float ub, float xb, float yb, float uc, float xc, float yc)
	{
	int deb,nb_twine;
	float debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	if (ub >= ua) 	debb = ((float)  ceil((double)ua)) - ua;
	else 		debb = ua - ((float) floor((double)ua));
	nb_twine = (int) floor(fabsf(ub - ua) - debb) + 1;
	for (deb=1;deb<=nb_twine;deb += 1)
		{
		if (fabsf(ub - ua) != 0.0) prob = (debb + deb - 1) / fabsf(ub - ua); else prob = 0.0;
		proc = (debb + deb - 1) / fabsf(uc - ua);
		x1m = xa + prob * (xb-xa);	y1m = ya + prob * (yb-ya);
		x2m = xa + proc * (xc-xa);	y2m = ya + proc * (yc-ya);
		if (Surface[pa].tarp == 1) 	TraceSegment(BLACK, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
		else				TraceSegment( BLUE, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
		}
	}
	
void draw_twines_color(int color, int pa, float ua, float xa, float ya, float ub, float xb, float yb, float uc, float xc, float yc)
	{
	int deb,nb_twine;
	float debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;
	extern void TraceSegment(int icolor, double dx01, double dy01, double dx02, double dy02);

	if (ub >= ua) 	debb = ((float)  ceil((double)ua)) - ua;
	else 		debb = ua - ((float) floor((double)ua));
	nb_twine = (int) floor(fabsf(ub - ua) - debb) + 1;
	for (deb=1;deb<=nb_twine;deb += 1)
		{
		if (fabsf(ub - ua) != 0.0) prob = (debb + deb - 1) / fabsf(ub - ua); else prob = 0.0;
		proc = (debb + deb - 1) / fabsf(uc - ua);
		x1m = xa + prob * (xb-xa);	y1m = ya + prob * (yb-ya);
		x2m = xa + proc * (xc-xa);	y2m = ya + proc * (yc-ya);
		if (Surface[pa].tarp == 1) 	TraceSegment(BLACK, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
		else				
			{
			if (flag_ps || flag_plain_color)
				{
				if (color == 1) TraceSegment( BLACK, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 2) TraceSegment(  BLUE, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 3) TraceSegment(   RED, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 4) TraceSegment( GREEN, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 5) TraceSegment(YELLOW, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 6) TraceSegment( couleur6, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 7) TraceSegment( couleur7, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 8) TraceSegment( couleur8, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 9) TraceSegment( couleur9, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 10) TraceSegment( couleur10, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				if (color == 11) TraceSegment( WHITE, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				}
			else
				{
				TraceSegment( color, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
				}
			}
		}
	}
	
void draw_segment_color(int color, double x1m, double y1m, double x2m, double y2m)
	{
	if (color == 0) TraceSegment( WHITE, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 1) TraceSegment( BLACK, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 2) TraceSegment(  BLUE, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 3) TraceSegment(   RED, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 4) TraceSegment( GREEN, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 5) TraceSegment(YELLOW, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 6) TraceSegment( couleur6, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 7) TraceSegment( couleur7, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 8) TraceSegment( couleur8, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 9) TraceSegment( couleur9, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 10) TraceSegment( couleur10, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	if (color == 11) TraceSegment( WHITE, (double) x1m, (double) y1m, (double) x2m, (double) y2m);
	}
	
void white_triangle_diamond(int pa)
	{
	int ba,no,deb,fin,pt1,pt2,pt3,nb_total,color;
	double pt4x,pt4y,pt5x,pt5y;

	pt1 = Surface[pa].extremite[1];
	pt2 = Surface[pa].extremite[2];
	pt3 = Surface[pa].extremite[3];
	
	color = panneau[Surface[pa].type].flag_dessin;

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
		}
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		}
	}

void white_triangle_hexa(int pa)
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
	
		EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y, pt5x, pt5y);
		EffaceTriangle(WHITE, Noeud[pt2].x, Noeud[pt2].y, pt4x, pt4y, pt5x, pt5y);
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
		}
	
	if ((Noeud[pt1].z <= profondeur_coupe_float) &&(Noeud[pt2].z <= profondeur_coupe_float) &&(Noeud[pt3].z <= profondeur_coupe_float))
		{
		EffaceTriangle(WHITE, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);
		}
	}


