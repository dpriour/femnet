#include "batz.h"
#include <time.h>
#include <unistd.h>

void animation()
	{
	int pt1,pt2,pt3,nb_total,no,np;
	int te,te1,pa,deb,fin,ra,nc;
	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();
	char text[10];
	float valinter;
	float valinter2;
	int nb_angle;
	float ve1[4],ve2[4],ve3[4],ve12[4],ve23[4],ve31[4],extr1[4],extr2[4];
	float u1,u2,u3,v1,v2,v3,u12,u23,u31,ua,ub,uc;
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;
	time_t sleep_ralenti_microsec;
	
	flag_plain_color = TRUE;
	ClearDrawArea();
	Color(WHITE);
	Move_to((float)0.0,(float)0.0);
	Line_to((float)1.0,(float)0.0);
	Line_to((float)1.0,(float)1.0);
	Line_to((float)0.0,(float)1.0);
	Surface_end();	/*faire un fond blanc */
	
	double angle_ball_1,angle_ball_2;
	
	nb_angle = 20;	/*nb of segment for drawing the balls*/
	if (nbtemps > 1)
		{
		for (nc=1;nc<=nb_animation;nc++)
       		{
			te=depart_anim-step_animation;
			for (te1=0;te1<=(fin_anim_sec-depart_anim_sec)/(Passtockage*step_animation);te1++)
				{ 
				te=te+step_animation;
				nb_total = NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;

				valinter2 = te1*Passtockage*step_animation+depart_anim_sec; /*time corresponding to te step*/

				sprintf(text,"%f",valinter2);
  				SetStringEntry(w[91], text);


				printf("time animation_video %s / %7.2f \n",text,fin_anim_sec);

				
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

				for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
					{ 
					pa = profondeur[no];
					if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
						{	
						/*surfaces*/
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
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
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
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
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
						/*element*/
						pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
						deb = Element[pa].extremite[1];			fin = Element[pa].extremite[2];
						TraceSegment(BLUE, Noeud[deb].ex[te], Noeud[deb].ey[te], Noeud[fin].ex[te], Noeud[fin].ey[te]);	/*display element*/

						double vect1[4],vect2[4],vect3[4];

						vect1[1]=Noeud[fin].sx;					vect1[2]=0;					vect1[3]=0;	/*for display floats*/
						vect2[1]=0;						vect2[2]=Noeud[fin].sy;				vect2[3]=0;
						vect3[1]=0;						vect3[2]=0;					vect3[3]=Noeud[fin].sz;

  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);

						double x1 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2;
						double y1 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2;
						double z1 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2;

						double x2 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2;
						double y2 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2;
						double z2 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2;

						double x3 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2;
						double y3 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2;
						double z3 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2;

						double x4 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2;
						double y4 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2;
						double z4 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2;

						double x5 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2 +vect3[1];
						double y5 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2 +vect3[2];
						double z5 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2 +vect3[3];

						double x6 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2 +vect3[1];	
						double y6 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2 +vect3[2];
						double z6 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2 +vect3[3];

						double x7 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2 +vect3[1];
						double y7 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2 +vect3[2];
						double z7 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2 +vect3[3];

						double x8 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2 +vect3[1];
						double y8 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2 +vect3[2];
						double z8 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2 +vect3[3];
		
						TraceSegment(BLACK,x1,y1,x2,y2);	TraceSegment(BLACK,x2,y2,x3,y3);	TraceSegment(BLACK,x3,y3,x4,y4);	TraceSegment(BLACK,x4,y4,x1,y1);
						TraceSegment(BLACK,x1,y1,x5,y5);	TraceSegment(BLACK,x2,y2,x6,y6);	TraceSegment(BLACK,x3,y3,x7,y7);	TraceSegment(BLACK,x4,y4,x8,y8);
						TraceSegment(BLACK,x5,y5,x6,y6);	TraceSegment(BLACK,x6,y6,x7,y7);	TraceSegment(BLACK,x7,y7,x8,y8);	TraceSegment(BLACK,x8,y8,x5,y5);
						}
					}
				printf("Structure.free_surface : %d\n", Structure.free_surface);
				if (Structure.free_surface == 1)
					{
					for (no=1;no<=Houle.nb_point-1;no=no+2)
						{ 
						/*trace des barres transversales*/
						deb = no;
						fin = no+1;
						TraceSegment(BLUE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);
						}
					for (no=1;no<=Houle.nb_point-3;no=no+2)
						{ 
						/*trace des segments paralleles a la houle*/
						deb = no;
						fin = no+2;
						/* debut modifdp du 17 mars 2010*/
						/*TraceSegment(BLUE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);*/
						/* fin modifdp du 17 mars 2010*/
						/*trace des segments paralleles a la houle*/
						deb = no+1;
						fin = no+3;
						/* debut modifdp du 17 mars 2010*/
						/*TraceSegment(BLUE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);*/
						/* fin modifdp du 17 mars 2010*/
						}
					}
	
				/*printf("Temps écoulé : %lf\n", elapsed);*/
				/*for (ra=1;ra<=ralenti_animation;ra++)	ra = ra;*/

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
				if ((pa >  NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
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
						TraceSegment(WHITE, Noeud[deb].ex[te], Noeud[deb].ey[te], Noeud[fin].ex[te], Noeud[fin].ey[te]);

						double vect1[4],vect2[4],vect3[4];

						vect1[1]=Noeud[fin].sx;				vect1[2]=0;				vect1[3]=0;
						vect2[1]=0;					vect2[2]=Noeud[fin].sy;			vect2[3]=0;
						vect3[1]=0;					vect3[2]=0;				vect3[3]=Noeud[fin].sz;

  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);

						double x1 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2;
						double y1 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2;
						double z1 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2;

						double x2 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2;
						double y2 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2;
						double z2 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2;

						double x3 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2;	
						double y3 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2;
						double z3 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2;
				
						double x4 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2;
						double y4 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2;
						double z4 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2;

						double x5 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2 +vect3[1];
						double y5 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2 +vect3[2];
						double z5 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2 +vect3[3];

						double x6 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2 +vect3[1];
						double y6 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2 +vect3[2];
						double z6 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2 +vect3[3];

						double x7 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2 +vect3[1];
						double y7 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2 +vect3[2];
						double z7 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2 +vect3[3];

						double x8 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2 +vect3[1];
						double y8 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2 +vect3[2];
						double z8 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2 +vect3[3];

						TraceSegment(WHITE,x1,y1,x2,y2);	TraceSegment(WHITE,x2,y2,x3,y3);	TraceSegment(WHITE,x3,y3,x4,y4);	TraceSegment(WHITE,x4,y4,x1,y1);
						TraceSegment(WHITE,x1,y1,x5,y5);	TraceSegment(WHITE,x2,y2,x6,y6);	TraceSegment(WHITE,x3,y3,x7,y7);	TraceSegment(WHITE,x4,y4,x8,y8);
						TraceSegment(WHITE,x5,y5,x6,y6);	TraceSegment(WHITE,x6,y6,x7,y7);	TraceSegment(WHITE,x7,y7,x8,y8);	TraceSegment(WHITE,x8,y8,x5,y5);
						}
					}
				printf("Structure.free_surface : %d\n", Structure.free_surface);
				if (Structure.free_surface == 1)
					{
					for (no=1;no<=Houle.nb_point-1;no=no+2)
						{ 
						/*trace des barres transversales*/
						deb = no;
						fin = no+1;
						TraceSegment(WHITE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);
						}
					for (no=1;no<=Houle.nb_point-3;no=no+2)
						{ 
						/*trace des segments paralleles a la houle*/
						deb = no;
						fin = no+2;
						/* debut modifdp du 17 mars 2010*/
						TraceSegment(WHITE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);
						/*trace des segments paralleles a la houle*/
						deb = no+1;
						fin = no+3;
						TraceSegment(WHITE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);
						}
					}
					
					sleep_ralenti_microsec=(int) floor(Passtockage*ralenti_animation*1000000);

					usleep(sleep_ralenti_microsec);
					
				}
			}
		}
	flag_plain_color = FALSE;
	}




void animation_video()
	{
	int pt1,pt2,pt3,nb_total,no,np;
	int te1,te,pa,deb,fin,ra,nc;
	extern void Move_to (float ,float );
	extern void Line_to (float ,float );
	extern void Surface_end();
	float valinter;
	float valinter2;
	int nbtemps_bis,nb_angle;
	char text[10];
	float ve1[4],ve2[4],ve3[4],ve12[4],ve23[4],ve31[4],extr1[4],extr2[4];
	float u1,u2,u3,v1,v2,v3,u12,u23,u31,ua,ub,uc;
	float xa,ya,za,xb,yb,zb,xc,yc,zc,debb,prob,proc,x1m,x2m,y1m,y2m,z1m,z2m;
	float sleep_ralenti;

	flag_plain_color = TRUE;
	ClearDrawArea();
	Color(WHITE);
	Move_to((float)0.0,(float)0.0);
	Line_to((float)1.0,(float)0.0);
	Line_to((float)1.0,(float)1.0);
	Line_to((float)0.0,(float)1.0);
	Surface_end();	/*faire un fond blanc */

	clock_t start, stop;
	double elapsed,angle_ball_1,angle_ball_2;
	nb_angle = 20;	/*nb of segment for drawing the balls*/
	int aaa = 0;
	
	if (nbtemps > 1)
		{
		for (nc=1;nc<=nb_animation;nc++)
       			{
			te=depart_anim-step_animation;
			/*for (te=depart_anim;te<=fin_anim;te++)*/
			for (te1=0;te1<=(fin_anim_sec-depart_anim_sec)/(Passtockage*step_animation);te1++)
				{
				te=te+step_animation;
				aaa=aaa+1;
				nb_total = NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;

				valinter2 = te1*Passtockage*step_animation+depart_anim_sec; /*time corresponding to te step*/

				sprintf(text,"%f",valinter2);  
  				SetStringEntry(w[91], text);

				printf("time animation_video %s / %7.2f ",text,fin_anim_sec);/**/

				char buf[255];

				sprintf(buf,"%s%05d",fname1,aaa);
				flag_ps = TRUE;
				ClearDrawArea();
				/*strcpy(nom_fichier,GetStringEntry(w_main[1]));*/
				strcpy(nom_fichier,buf);
				/*Retrace_fenetre();*/
			    	/*printf("fname1 = %s \n",fname1);*/
				/*mode_portrait = FALSE;*/
				Chk_ps_open();
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
				for (no=1;no<=NOMBRE_SURFACES+NOMBRE_SURF_HEXA+NOMBRE_ELEMENTS+NOMBRE_COULISSES;no++)
					{ 
					pa = profondeur[no];

					/*printf("no = %8d total = %8d pa = %8d NOMBRE_SURFACES = %8d \n",no,nb_total,pa,NOMBRE_SURFACES);*/
					if ((pa <= NOMBRE_SURFACES) &&(panneau[Surface[pa].type].flag_dessin != 0))
						{			
						pt1 = Surface[pa].extremite[1];		pt2 = Surface[pa].extremite[2];		pt3 = Surface[pa].extremite[3];
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
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
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
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color( panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							}				
						}
					if ((pa >  NOMBRE_SURFACES) && (pa <= NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (TypeSurfHexa[Surf_Hexa[pa - NOMBRE_SURFACES].type].flag_dessin != 0))
						{
						/*surface_hexa*/
						pa = pa - NOMBRE_SURFACES;
						pt1 = Surf_Hexa[pa].extremite[1];		pt2 = Surf_Hexa[pa].extremite[2];		pt3 = Surf_Hexa[pa].extremite[3];
						}
					if ((pa >  NOMBRE_SURFACES + NOMBRE_SURF_HEXA) && (pa <=  NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS) && (TypeElement[Element[pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA].type].flag_dessin != 0))
						{
						/*element*/
						pa = pa - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
						deb = Element[pa].extremite[1];		fin = Element[pa].extremite[2];
						TraceSegment(BLUE, Noeud[deb].ex[te], Noeud[deb].ey[te], Noeud[fin].ex[te], Noeud[fin].ey[te]);

						double vect1[4],vect2[4],vect3[4];

						vect1[1]=Noeud[fin].sx;				vect1[2]=0;				vect1[3]=0;
						vect2[1]=0;					vect2[2]=Noeud[fin].sy;			vect2[3]=0;
						vect3[1]=0;					vect3[2]=0;				vect3[3]=Noeud[fin].sz;

  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);

						double x1 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2;
						double y1 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2;
						double z1 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2;

						double x2 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2;
						double y2 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2;
						double z2 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2;

						double x3 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2;
						double y3 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2;
						double z3 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2;

						double x4 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2;
						double y4 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2;
						double z4 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2;

						double x5 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2 +vect3[1];
						double y5 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2 +vect3[2];
						double z5 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2 +vect3[3];

						double x6 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2 +vect3[1];	
						double y6 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2 +vect3[2];
						double z6 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2 +vect3[3];

						double x7 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2 +vect3[1];
						double y7 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2 +vect3[2];
						double z7 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2 +vect3[3];

						double x8 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2 +vect3[1];
						double y8 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2 +vect3[2];
						double z8 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2 +vect3[3];
		
						TraceSegment(BLACK,x1,y1,x2,y2);	TraceSegment(BLACK,x2,y2,x3,y3);	TraceSegment(BLACK,x3,y3,x4,y4);	TraceSegment(BLACK,x4,y4,x1,y1);
						TraceSegment(BLACK,x1,y1,x5,y5);	TraceSegment(BLACK,x2,y2,x6,y6);	TraceSegment(BLACK,x3,y3,x7,y7);	TraceSegment(BLACK,x4,y4,x8,y8);
						TraceSegment(BLACK,x5,y5,x6,y6);	TraceSegment(BLACK,x6,y6,x7,y7);	TraceSegment(BLACK,x7,y7,x8,y8);	TraceSegment(BLACK,x8,y8,x5,y5);
						}
					}
				printf("Structure.free_surface : %d\n", Structure.free_surface);
				if (Structure.free_surface == 1)
					{
					for (no=1;no<=Houle.nb_point-1;no=no+2)
						{ 
						/*trace des barres transversales*/
						deb = no;
						fin = no+1;
						TraceSegment(BLUE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);
						}
					for (no=1;no<=Houle.nb_point-3;no=no+2)
						{ 
						/*trace des segments paralleles a la houle*/
						deb = no;
						fin = no+2;
						/*TraceSegment(BLUE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);*/
						/*trace des segments paralleles a la houle*/
						deb = no+1;
						fin = no+3;
						/*TraceSegment(BLUE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);*/
						}
					}

		 		Chk_ps_close();
				flag_ps = FALSE;

				char second[1000];
				char essai[1000];
				sprintf(second,"convert -density 180x180  %s%05d.ps -depth 8  %s%05d.png",fname1,aaa,fname1,aaa);
				/*sprintf(second,"convert -density 180x180 /export/home/hexa/batz/image/%s%05d.ps -depth 8 /export/home/hexa/batz/image/%s%05d.png",fname1,aaa,fname1,aaa);*/
				/*sprintf(second,"convert -density 180x180 /export/home/hexa/batz/%s%05d.ps -depth 8  /export/home/hexa/batz/%s%05d.png",fname1,aaa,fname1,aaa);*/
				/*sprintf(second,"convert -density 180x180 /export/home/hexa/batz/image%05d.ps -depth 8 /export/home/hexa/batz/image%05d.png",aaa,aaa);*/
				system(second);

				sprintf(essai,"rm %s%05d.ps",fname1,aaa);
				system(essai);


				sleep_ralenti=Passtockage*ralenti_animation;



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
				for (pa=1;pa<=NOMBRE_ELEMENTS;pa++)
					{ 
					if (TypeElement[Element[pa].type].flag_dessin != 0)
						{
						deb = Element[pa].extremite[1];
						fin = Element[pa].extremite[2];
						TraceSegment(WHITE, Noeud[deb].ex[te], Noeud[deb].ey[te], Noeud[fin].ex[te], Noeud[fin].ey[te]);

						double vect1[4],vect2[4],vect3[4];

						vect1[1]=Noeud[fin].sx;				vect1[2]=0;				vect1[3]=0;
						vect2[1]=0;					vect2[2]=Noeud[fin].sy;			vect2[3]=0;
						vect3[1]=0;					vect3[2]=0;				vect3[3]=Noeud[fin].sz;

  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect1);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect2);
  						base1((double)angle_x*PI/180.0,1,(double)angle_y*PI/180.0,2,3,vect3);

						double x1 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2;
						double y1 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2;
						double z1 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2;

						double x2 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2;
						double y2 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2;
						double z2 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2;

						double x3 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2;	
						double y3 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2;
						double z3 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2;
				
						double x4 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2;
						double y4 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2;
						double z4 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2;

						double x5 = Noeud[fin].ex[te] + vect1[1]/2 - vect2[1]/2 +vect3[1];
						double y5 = Noeud[fin].ey[te] + vect1[2]/2 - vect2[2]/2 +vect3[2];
						double z5 = Noeud[fin].ez[te] + vect1[3]/2 - vect2[3]/2 +vect3[3];

						double x6 = Noeud[fin].ex[te] + vect1[1]/2 + vect2[1]/2 +vect3[1];
						double y6 = Noeud[fin].ey[te] + vect1[2]/2 + vect2[2]/2 +vect3[2];
						double z6 = Noeud[fin].ez[te] + vect1[3]/2 + vect2[3]/2 +vect3[3];

						double x7 = Noeud[fin].ex[te] - vect1[1]/2 + vect2[1]/2 +vect3[1];
						double y7 = Noeud[fin].ey[te] - vect1[2]/2 + vect2[2]/2 +vect3[2];
						double z7 = Noeud[fin].ez[te] - vect1[3]/2 + vect2[3]/2 +vect3[3];

						double x8 = Noeud[fin].ex[te] - vect1[1]/2 - vect2[1]/2 +vect3[1];
						double y8 = Noeud[fin].ey[te] - vect1[2]/2 - vect2[2]/2 +vect3[2];
						double z8 = Noeud[fin].ez[te] - vect1[3]/2 - vect2[3]/2 +vect3[3];

						TraceSegment(WHITE,x1,y1,x2,y2);	TraceSegment(WHITE,x2,y2,x3,y3);	TraceSegment(WHITE,x3,y3,x4,y4);	TraceSegment(WHITE,x4,y4,x1,y1);
						TraceSegment(WHITE,x1,y1,x5,y5);	TraceSegment(WHITE,x2,y2,x6,y6);	TraceSegment(WHITE,x3,y3,x7,y7);	TraceSegment(WHITE,x4,y4,x8,y8);
						TraceSegment(WHITE,x5,y5,x6,y6);	TraceSegment(WHITE,x6,y6,x7,y7);	TraceSegment(WHITE,x7,y7,x8,y8);	TraceSegment(WHITE,x8,y8,x5,y5);
						}
					}
				for (pa=1;pa<=NOMBRE_SURFACES;pa++)
					{ 
					if (panneau[Surface[pa].type].flag_dessin != 0)
						{ 
						pt1 = Surface[pa].extremite[1];		pt2 = Surface[pa].extremite[2];		pt3 = Surface[pa].extremite[3];

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
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
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
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 3 start(a) = 2 remain(c) = 1*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u3;	xb = (REEL) Noeud[pt3].ex[te]; yb = (REEL) Noeud[pt3].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u23 >= u31) && (u23 >= u12))
								{
								/*vertex(b) = 1 start(a) = 2 remain(c) = 3*/				
								ua = u2;	xa = (REEL) Noeud[pt2].ex[te]; ya = (REEL) Noeud[pt2].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 1 start(a) = 3 remain(c) = 2*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u1;	xb = (REEL) Noeud[pt1].ex[te]; yb = (REEL) Noeud[pt1].ey[te];
								uc = u2;	xc = (REEL) Noeud[pt2].ex[te]; yc = (REEL) Noeud[pt2].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							if ((u31 >= u12) && (u31 >= u23))
								{
								/*vertex(b) = 2 start(a) = 3 remain(c) = 1*/				
								ua = u3;	xa = (REEL) Noeud[pt3].ex[te]; ya = (REEL) Noeud[pt3].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u1;	xc = (REEL) Noeud[pt1].ex[te]; yc = (REEL) Noeud[pt1].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								/*vertex(b) = 2 start(a) = 1 remain(c) = 3*/				
								ua = u1;	xa = (REEL) Noeud[pt1].ex[te]; ya = (REEL) Noeud[pt1].ey[te];
								ub = u2;	xb = (REEL) Noeud[pt2].ex[te]; yb = (REEL) Noeud[pt2].ey[te];
								uc = u3;	xc = (REEL) Noeud[pt3].ex[te]; yc = (REEL) Noeud[pt3].ey[te];
								draw_twines_color(panneau[Surface[pa].type].flag_dessin, pa, ua, xa, ya, ub, xb, yb, uc, xc, yc);
								}
							}						
						}
					}
				printf("Structure.free_surface : %d\n", Structure.free_surface);
				if (Structure.free_surface == 1)
					{
					for (no=1;no<=Houle.nb_point-1;no=no+2)
						{ 
						/*trace des barres transversales*/
						deb = no;
						fin = no+1;
						TraceSegment(WHITE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);
						}
					for (no=1;no<=Houle.nb_point-3;no=no+2)
						{ 
						/*trace des segments paralleles a la houle*/
						deb = no;
						fin = no+2;
						/* debut modifdp du 17 mars 2010*/
						/*TraceSegment(WHITE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);*/
						/* fin modifdp du 17 mars 2010*/
						/*trace des segments paralleles a la houle*/
						deb = no+1;
						fin = no+3;
						/* debut modifdp du 17 mars 2010*/
						/*TraceSegment(WHITE, Houle.U[deb][te], Houle.V[deb][te], Houle.U[fin][te], Houle.V[fin][te]);*/
						/* fin modifdp du 17 mars 2010*/
						}
					}
				}
			}
		}

	flag_plain_color = FALSE;
	printf("begining of encoding, File: %s\n" , fname1);

	int rrr=floor(1/(Passtockage*ralenti_animation));

	char second[1000];
	char essai1[1000];

	//sprintf(second,"ffmpeg -f image2 -r %d -i %s%%05d.png -r %d %s.avi",rrr,fname1,rrr,fname1);
	//exit(0);
	sprintf(second,"avconv -f image2 -r %d -i %s%%05d.png -r %d %s.avi",rrr,fname1,rrr,fname1);
	system(second);

	for (no=1;no<=aaa;no++)
	{
		//sprintf(essai1,"rm %s%05d.png",fname1,no);
		//system(essai1);
	}
	printf("end of encoding, File : %s\n" , fname1);

	flag_plain_color = FALSE;
	}

