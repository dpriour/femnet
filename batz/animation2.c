#include "batz.h"
#include <time.h>
#include <unistd.h>
#include "omp.h"

void animation2(int code_video)
	{
	/*code_video = 0;		animation not video*/
	/*code_video = 1;		video not animation*/
	int pt1,pt2,pt3,nb_total,no,zj;
	int te,te1,pa,deb,fin,ra,nc;
	int nb_thread;

	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();
	char text[10];
	float valinter;
	float valinter2;
	int nb_angle;
	float u1,u2,u3,v1,v2,v3,u12,u23,u31,ua,ub,uc;
	float xa,ya,za,xb,yb,zb,xc,yc,zc;
	time_t sleep_ralenti_microsec;
	float sleep_ralenti;
	char buf[255];
	double vect1[4],vect2[4],vect3[4];
	char command[1000];
	int rrr,aaa;
	double x1,x2,x3,x4,x5,x6,x7,x8,y1,y2,y3,y4,y5,y6,y7,y8,z1,z2,z3,z4,z5,z6,z7,z8;
	double angle_ball_1,angle_ball_2;
	double ext1[4],ext2[4];
	double U[4],V[4],W[4],norm;

	
	flag_plain_color = TRUE;	/*pas de dégrade de couleur car incompatible avec fichier ps*/
	ClearDrawArea();
	Color(WHITE);
	Move_to((float)0.0,(float)0.0);
	Line_to((float)1.0,(float)0.0);
	Line_to((float)1.0,(float)1.0);
	Line_to((float)0.0,(float)1.0);
	Surface_end();	/*faire un fond blanc */
	
	clock_t start, stop;
	aaa = 0;
	nb_angle = 20;	/*nb of segment for drawing the balls*/

	if (nbtemps > 1)
		{
		for (nc=1;nc<=nb_animation;nc++)
       			{
			te=depart_anim-step_animation;
			for (te1=0;te1<=(fin_anim_sec-depart_anim_sec)/(Passtockage*step_animation);te1++)
				{ 
				te=te+step_animation;
				aaa=aaa+1;
				nb_total = NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;

				valinter2 = te1*Passtockage*step_animation+depart_anim_sec; /*time corresponding to te step*/

				sprintf(text,"%f",valinter2);
  				SetStringEntry(w[91], text);

				printf("time animation_video %s / %7.2f   ",text,fin_anim_sec);
				if (code_video == 0)
					{
					printf("\n");
					}
				if (code_video == 1)
					{
					sprintf(buf,"%s%05d",fname1,aaa);
					flag_ps = TRUE;
					ClearDrawArea();
					strcpy(nom_fichier,buf);
					Chk_ps_open();
					}
				
				if (Ball.flag_dessin != 0)
					{
					for (pa=1;pa<=Ball.nb;pa++)
						{ 
						deb = Ball.noeud[pa];
						for (no=1;no<=nb_angle;no++)
							{ 
							angle_ball_1 = (no-1) * (2.0 * PI / nb_angle);
							angle_ball_2 = (no+0) * (2.0 * PI / nb_angle);
							TraceSegment(RED, Noeud[deb].ex[te] + Ball.radius[pa]*sin(angle_ball_1), Noeud[deb].ey[te] + Ball.radius[pa]*cos(angle_ball_1), Noeud[deb].ex[te] + Ball.radius[pa]*sin(angle_ball_2), Noeud[deb].ey[te] + Ball.radius[pa]*cos(angle_ball_2));
							}
						}
					}
				for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES+NOMBRE_WINCHS+Ball.nb+NOMBRE_NOEUDS;no++)
					{ 
					pa = profondeur[no];
					if ((pa <= NOMBRE_SURFACES) && (panneau[Surface[pa].type].flag_dessin != 0))
						{	
						/*surfaces*/
						pa = pa - 0;
						pt1 = Surface[pa].extremite[1];			pt2 = Surface[pa].extremite[2];			pt3 = Surface[pa].extremite[3];
						if (Surface[pa].flag_dessin_u == 1)
							{
							/*u twines*/		
							u1 = ((float) Surface[pa].lon[2] + (float) Surface[pa].lon[1]) / periode_fils; 	
							u2 = ((float) Surface[pa].lon[4] + (float) Surface[pa].lon[3]) / periode_fils; 	
							u3 = ((float) Surface[pa].lon[6] + (float) Surface[pa].lon[5]) / periode_fils;
							u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
							if ((u12 >= u23) && (u12 >= u31))
								{
								/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];			
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);

								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							}
						if (Surface[pa].flag_dessin_v == 1)
							{
							/*v twines*/		
							u1 = ((float) Surface[pa].lon[2] - (float) Surface[pa].lon[1]) / periode_fils;
							u2 = ((float) Surface[pa].lon[4] - (float) Surface[pa].lon[3]) / periode_fils;
							u3 = ((float) Surface[pa].lon[6] - (float) Surface[pa].lon[5]) / periode_fils;		
							u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
							if ((u12 >= u23) && (u12 >= u31))
								{
								/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];				
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( 2, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							}
						}
					if ((pa >  NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
						{
						/*surface_hexa*/
						pa = pa - NOMBRE_SURFACES;
						pt1 = Surf_Hexa[pa].extremite[1];			pt2 = Surf_Hexa[pa].extremite[2];			pt3 = Surf_Hexa[pa].extremite[3];
						}
					if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
						{
						pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
						if (TypeElement[Element[pa].type].flag_dessin != 0)
							{
							/*element*/
							deb = Element[pa].extremite[1];			fin = Element[pa].extremite[2];
							//draw_segment_color(TypeElement[Element[pa].type].flag_dessin, Noeud[deb].ex[te], Noeud[deb].ey[te], Noeud[fin].ex[te], Noeud[fin].ey[te]);	/*display element*/
							/*TraceSegment(BLUE, Noeud[deb].ex[te], Noeud[deb].ey[te], Noeud[fin].ex[te], Noeud[fin].ey[te]);*/	/*display element*/
				/***************************************************************************************************************************************/
							x1 = Noeud[deb].ex[te];		y1 = Noeud[deb].ey[te];		z1 = Noeud[deb].ez[te];
							x2 = Noeud[fin].ex[te];		y2 = Noeud[fin].ey[te];		z2 = Noeud[fin].ez[te];
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
							norm = sqrt(produit_scal_double(U,U));		/*length of side U*/
							produit_scal_vect_double(1.0/norm, U, U);						/*U vector is the normalized element vector*/
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
							for (zj=1;zj<=20;zj++)
								{
								alpha = (zj -1)*2*PI/20;
								betaa  = (zj -0)*2*PI/20;
								x3 = x1 + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = y1 + cos(alpha) * V[2] + sin(alpha) * W[2];
								x4 = x1 + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = y1 + cos( betaa) * V[2] + sin( betaa) * W[2];
								draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);
								x3 = x2 + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = y2 + cos(alpha) * V[2] + sin(alpha) * W[2];
								x4 = x2 + cos( betaa) * V[1] + sin( betaa) * W[1];	y4 = y2 + cos( betaa) * V[2] + sin( betaa) * W[2];
								draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);
								x3 = x1 + cos(alpha) * V[1] + sin(alpha) * W[1];	y3 = y1 + cos(alpha) * V[2] + sin(alpha) * W[2];
								x4 = x2 + cos(alpha) * V[1] + sin(alpha) * W[1];	y4 = y2 + cos(alpha) * V[2] + sin(alpha) * W[2];
								draw_segment_color(TypeElement[Element[pa].type].flag_dessin, x3, y3, x4, y4);
								}

				/***************************************************************************************************************************************/
							vect1[1]=Noeud[fin].sx;					vect1[2]=0;					vect1[3]=0;	/*for display floats*/
							vect2[1]=0;						vect2[2]=Noeud[fin].sy;				vect2[3]=0;
							vect3[1]=0;						vect3[2]=0;					vect3[3]=Noeud[fin].sz;

	  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
	  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
	  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);

							x1 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2;
							y1 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2;
							z1 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2;

							x2 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2;
							y2 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2;
							z2 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2;

							x3 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2;
							y3 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2;
							z3 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2;

							x4 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2;
							y4 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2;
							z4 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2;

							x5 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2 +vect3[1];
							y5 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2 +vect3[2];
							z5 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2 +vect3[3];

							x6 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2 +vect3[1];	
							y6 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2 +vect3[2];
							z6 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2 +vect3[3];

							x7 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2 +vect3[1];
							y7 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2 +vect3[2];
							z7 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2 +vect3[3];

							x8 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2 +vect3[1];
							y8 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2 +vect3[2];
							z8 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2 +vect3[3];
		
							TraceSegment(BLACK,x1,y1,x2,y2);	TraceSegment(BLACK,x2,y2,x3,y3);	TraceSegment(BLACK,x3,y3,x4,y4);	TraceSegment(BLACK,x4,y4,x1,y1);
							TraceSegment(BLACK,x1,y1,x5,y5);	TraceSegment(BLACK,x2,y2,x6,y6);	TraceSegment(BLACK,x3,y3,x7,y7);	TraceSegment(BLACK,x4,y4,x8,y8);
							TraceSegment(BLACK,x5,y5,x6,y6);	TraceSegment(BLACK,x6,y6,x7,y7);	TraceSegment(BLACK,x7,y7,x8,y8);	TraceSegment(BLACK,x8,y8,x5,y5);
							}
						}
					}
				if (Structure.free_surface == 1)
					{
					for (no=1;no<=Houle.nb_point-1;no=no+2)
						{ 
						/*trace des barres transversales*/
						deb = no;
						fin = no+1;
						TraceSegment(BLUE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);
						}
					}
	
				if (code_video == 1)
					{
			 		Chk_ps_close();
					flag_ps = FALSE;
					sprintf(command,"convert -density 180x180 %s%05d.ps -depth 8  %s%05d.png",fname1,aaa,fname1,aaa);		system(command);	/*create png file*/
					sprintf(command,"rm %s%05d.ps",fname1,aaa);/**/									system(command);	/*delete ps file*/
					sleep_ralenti=Passtockage*ralenti_animation;
					}
				/*******************************************************effacement**********************************************************************/

				if (Ball.flag_dessin != 0)
					{
					for (pa=1;pa<=Ball.nb;pa++)
						{ 
						deb = Ball.noeud[pa];
						for (no=1;no<=nb_angle;no++)
							{ 
							angle_ball_1 = (no-1) * (2.0 * PI / nb_angle);
							angle_ball_2 = (no+0) * (2.0 * PI / nb_angle);
							TraceSegment(WHITE, Noeud[deb].ex[te] + Ball.radius[pa]*sin(angle_ball_1), Noeud[deb].ey[te] + Ball.radius[pa]*cos(angle_ball_1), Noeud[deb].ex[te] + Ball.radius[pa]*sin(angle_ball_2), Noeud[deb].ey[te] + Ball.radius[pa]*cos(angle_ball_2));
							}
						}
					}
					
				for (pa=1;pa<=NOMBRE_SURFACES;pa++)
					{ 
					if (panneau[Surface[pa].type].flag_dessin != 0)
						{ 
						/*surfaces*/
						pt1 = Surface[pa].extremite[1];		pt2 = Surface[pa].extremite[2];		pt3 = Surface[pa].extremite[3];
						if (Surface[pa].flag_dessin_u == 1)
							{
							/*u twines*/		
							u1 = ((float) Surface[pa].lon[2] + (float) Surface[pa].lon[1]) / periode_fils; 	
							u2 = ((float) Surface[pa].lon[4] + (float) Surface[pa].lon[3]) / periode_fils; 	
							u3 = ((float) Surface[pa].lon[6] + (float) Surface[pa].lon[5]) / periode_fils;
							u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
//exit(0);
							if ((u12 >= u23) && (u12 >= u31))
								{
								/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];			
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}							}
						if (Surface[pa].flag_dessin_v == 1)
							{							
							/*v twines*/		
							u1 = ((float) Surface[pa].lon[2] - (float) Surface[pa].lon[1]) / periode_fils;
							u2 = ((float) Surface[pa].lon[4] - (float) Surface[pa].lon[3]) / periode_fils;
							u3 = ((float) Surface[pa].lon[6] - (float) Surface[pa].lon[5]) / periode_fils;		
							u12 = fabsf(u2-u1);	u23 = fabsf(u3-u2);	u31 = fabsf(u1-u3);
							if ((u12 >= u23) && (u12 >= u31))
								{
								/*vertex(b) = 3 start(a) = 1 remain(c) = 2*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];				
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( 6, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							}					
						}
					}
				for (pa=1;pa<=NOMBRE_SURF_HEXA;pa++)
					{
					/*surface_hexa*/
					pa = pa - NOMBRE_SURFACES;
					pt1 = Surf_Hexa[pa].extremite[1];			pt2 = Surf_Hexa[pa].extremite[2];			pt3 = Surf_Hexa[pa].extremite[3];
					}
				for (pa=1;pa<=NOMBRE_ELEMENTS;pa++)
					{ 
					/*element*/
					if (TypeElement[Element[pa].type].flag_dessin != 0)
						{
						deb = Element[pa].extremite[1];		fin = Element[pa].extremite[2];
						draw_segment_color(0, Noeud[deb].ex[te], Noeud[deb].ey[te], Noeud[fin].ex[te], Noeud[fin].ey[te]);

						vect1[1]=Noeud[fin].sx;				vect1[2]=0;				vect1[3]=0;	/*for remove floats*/
						vect2[1]=0;					vect2[2]=Noeud[fin].sy;			vect2[3]=0;
						vect3[1]=0;					vect3[2]=0;				vect3[3]=Noeud[fin].sz;

  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);

						x1 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2;
						y1 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2;
						z1 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2;

						x2 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2;
						y2 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2;
						z2 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2;

						x3 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2;	
						y3 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2;
						z3 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2;
				
						x4 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2;
						y4 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2;
						z4 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2;

						x5 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2 +vect3[1];
						y5 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2 +vect3[2];
						z5 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2 +vect3[3];

						x6 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2 +vect3[1];
						y6 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2 +vect3[2];
						z6 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2 +vect3[3];

						x7 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2 +vect3[1];
						y7 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2 +vect3[2];
						z7 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2 +vect3[3];

						x8 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2 +vect3[1];
						y8 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2 +vect3[2];
						z8 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2 +vect3[3];

						//TraceSegment(WHITE,x1,y1,x2,y2);	TraceSegment(WHITE,x2,y2,x3,y3);	TraceSegment(WHITE,x3,y3,x4,y4);	TraceSegment(WHITE,x4,y4,x1,y1);
						//TraceSegment(WHITE,x1,y1,x5,y5);	TraceSegment(WHITE,x2,y2,x6,y6);	TraceSegment(WHITE,x3,y3,x7,y7);	TraceSegment(WHITE,x4,y4,x8,y8);
						//TraceSegment(WHITE,x5,y5,x6,y6);	TraceSegment(WHITE,x6,y6,x7,y7);	TraceSegment(WHITE,x7,y7,x8,y8);	TraceSegment(WHITE,x8,y8,x5,y5);
						}
					}
				if (Structure.free_surface == 1)
					{
					for (no=1;no<=Houle.nb_point-1;no=no+2)
						{ 
						/*trace des barres transversales*/
						deb = no;
						fin = no+1;
						TraceSegment(WHITE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);
						}
					}
					
				if (code_video == 0)
					{
					sleep_ralenti_microsec=(int) floor(Passtockage*ralenti_animation*1000000);
					usleep(sleep_ralenti_microsec);
					}
				}
			}
		}
	if (code_video == 1)
		{
		//nb_thread = (mkl_get_max_threads()-1);
		nb_thread = 1;
		printf("nb_thread: %d\n" , nb_thread);
		printf("begining of encoding, File: %s\n" , fname1);
		rrr=floor(1.0/(Passtockage*ralenti_animation));
		printf("FPS = rrr = %d\n", rrr);
		sprintf(command,"rm %s.avi",fname1);												system(command);	/*delete avi file*/
		//sprintf(command,"avconv -threads %d -f image2 -r %d -i %s%%05d.png -s wxga -r %d %s.avi", nb_thread, rrr, fname1, rrr, fname1);	system(command);	/*create avi file*/
		//sprintf(command,"avconv -threads %d -f image2 -r %d -i %s%%05d.png -r %d %s.avi", nb_thread, rrr, fname1, rrr, fname1);	system(command);	/*create avi file*/
		sprintf(command,"ffmpeg -f image2 -i %s%%05d.png -r 12  %s.avi", fname1, fname1);	system(command);
		sprintf(command,"rm %s*.png",fname1);												system(command);	/*delete png file*/
		printf("end of encoding, File : %s\n" , fname1);
		}	
	flag_plain_color = FALSE;
	}
	
	
	
void animation_eigenvalue(int code_video)
	{
	/*code_video = 0;		animation not video*/
	/*code_video = 1;		video not animation*/
	int pt1,pt2,pt3,nb_total,no;
	int te,pa,deb,fin,nc;

	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();
	time_t sleep_ralenti_microsec;
	float sleep_ralenti;
	char buf[255];
	double vect1[4],vect2[4],vect3[4];
	char command[1000];
	int aaa;

	flag_plain_color = TRUE;
	ClearDrawArea();
	Color(WHITE);
	Move_to((float)0.0,(float)0.0);
	Line_to((float)1.0,(float)0.0);
	Line_to((float)1.0,(float)1.0);
	Line_to((float)0.0,(float)1.0);
	Surface_end();	/*faire un fond blanc */
	
	clock_t start, stop;
	aaa = 0;
	nbtemps = 100;
	nb_animation = 1;

	for (nc=1;nc<=nb_animation;nc++)
		{
		for (te=0;te<=nbtemps;te++)
			{ 
			aaa=aaa+1;
			nb_total = NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;

			printf("time animation_video %7d / %7d   ",te,nbtemps);

			if (code_video == 0)
				{
				printf("\n");
				}
			if (code_video == 1)
				{
				sprintf(buf,"%s%05d",fname1,aaa);
				flag_ps = TRUE;
				ClearDrawArea();
				strcpy(nom_fichier,buf);
				Chk_ps_open();
				}
			
			for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES+NOMBRE_WINCHS+Ball.nb+NOMBRE_NOEUDS;no++)
				{ 
				pa = profondeur[no];
				if ((pa <= NOMBRE_SURFACES) && (panneau[Surface[pa].type].flag_dessin != 0))
					{	
					/*surfaces*/
					pa = pa - 0;
					pt1 = Surface[pa].extremite[1];			pt2 = Surface[pa].extremite[2];			pt3 = Surface[pa].extremite[3];
					draw_segment_color(2, Noeud[pt1].x, Noeud[pt1].y, Noeud[pt2].x, Noeud[pt2].y);						
					draw_segment_color(2, Noeud[pt2].x, Noeud[pt2].y, Noeud[pt3].x, Noeud[pt3].y);						
					draw_segment_color(2, Noeud[pt3].x, Noeud[pt3].y, Noeud[pt1].x, Noeud[pt1].y);						
					}
				if ((pa >  NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
					{
					/*surface_hexa*/
					pa = pa - NOMBRE_SURFACES;
					pt1 = Surf_Hexa[pa].extremite[1];			pt2 = Surf_Hexa[pa].extremite[2];			pt3 = Surf_Hexa[pa].extremite[3];
					}
				if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
					{
					pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
					if (TypeElement[Element[pa].type].flag_dessin != 0)
						{
						/*element*/
						deb = Element[pa].extremite[1];			fin = Element[pa].extremite[2];
						//draw_segment_color(TypeElement[Element[pa].type].flag_dessin, Noeud[deb].x+ (double) v_jacobi_rotati[3*deb-2][1], Noeud[deb].y+ (double) v_jacobi_rotati[3*deb-1][1], Noeud[fin].x+ (double) v_jacobi_rotati[3*fin-2][1], Noeud[fin].y+ (double) v_jacobi_rotati[3*fin-1][1]);
						
						printf("deb %3d fin %3d   ",deb,fin);
						printf("xydeb %7.2lf %7.2lf   ",Noeud[deb].x,Noeud[deb].y);
						printf("xyfin %7.2lf %7.2lf   ",Noeud[fin].x,Noeud[fin].y);
						//printf("eigdeb %7.2f %7.2f   ",v_jacobi_rotati[3*deb-2][1],v_jacobi_rotati[3*deb-1][1]);
						//printf("eigfin %7.2f %7.2f   ",v_jacobi_rotati[3*fin-2][1],v_jacobi_rotati[3*fin-1][1]);
						printf("\n");
						
						}
					}
				}
			if (code_video == 1)
				{
		 		Chk_ps_close();
				flag_ps = FALSE;
				sprintf(command,"convert -density 180x180 %s%05d.ps -depth 8  %s%05d.png",fname1,aaa,fname1,aaa);		system(command);	/*create png file*/
				sprintf(command,"rm %s%05d.ps",fname1,aaa);/**/									system(command);	/*delete ps file*/
				sleep_ralenti=Passtockage*ralenti_animation;
				}
			/*******************************************************effacement**********************************************************************/

			for (pa=1;pa<=NOMBRE_SURFACES;pa++)
				{ 
				if (panneau[Surface[pa].type].flag_dessin != 0)
					{ 
					/*surfaces*/
					pt1 = Surface[pa].extremite[1];		pt2 = Surface[pa].extremite[2];		pt3 = Surface[pa].extremite[3];
					}
				}
			for (pa=1;pa<=NOMBRE_SURF_HEXA;pa++)
				{
				/*surface_hexa*/
				pa = pa - NOMBRE_SURFACES;
				pt1 = Surf_Hexa[pa].extremite[1];		pt2 = Surf_Hexa[pa].extremite[2];	pt3 = Surf_Hexa[pa].extremite[3];
				}
			for (pa=1;pa<=NOMBRE_ELEMENTS;pa++)
				{ 
				/*element*/
				if (TypeElement[Element[pa].type].flag_dessin != 0)
					{
					deb = Element[pa].extremite[1];		fin = Element[pa].extremite[2];
					//draw_segment_color(0, Noeud[deb].x+ (double) v_jacobi_rotati[3*deb-2][1], Noeud[deb].y+ (double) v_jacobi_rotati[3*deb-1][1], Noeud[fin].x+ (double) v_jacobi_rotati[3*fin-2][1], Noeud[fin].y+ (double) v_jacobi_rotati[3*fin-1][1]);
					}
				}				
			if (code_video == 0)
				{
				sleep_ralenti_microsec=(int) floor(ralenti_animation*10000);
				usleep(sleep_ralenti_microsec);
				}
			}
		}
	flag_plain_color = FALSE;
	}

