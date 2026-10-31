#include "batz.h"

void fils_contour_hexa()
	{
	int sommet1,sommet2,sommet3,pa;
	float U1,U2,U3,V1,V2,V3,n1,n2,n3,m1,m2,m3;
	float ve1[4],ve2[4],ve3[4];
	float u12[4],u23[4],u31[4],v12[4],v23[4],v31[4];
	float u21[4],u32[4],u13[4],v21[4],v32[4],v13[4];
	
	printf(" fils_contour_hexa \n");
			
   	if (periode_fils <= 0) periode_fils = 1;
	
	for (pa=1;pa<=NOMBRE_SURF_HEXA;pa++)
		{
		periode_fils =1;
		
		sommet1 = Surf_Hexa[pa].extremite[1];
		sommet2 = Surf_Hexa[pa].extremite[2];
		sommet3 = Surf_Hexa[pa].extremite[3];

		/*printf(" sommets  : %8d %8d %8d \n",sommet1,sommet2,sommet3);*/
		
		U1 = (float) Surf_Hexa[pa].lon[2] + (float) Surf_Hexa[pa].lon[1]; 	V1 = (float) Surf_Hexa[pa].lon[2] - (float) Surf_Hexa[pa].lon[1];
		U2 = (float) Surf_Hexa[pa].lon[4] + (float) Surf_Hexa[pa].lon[3]; 	V2 = (float) Surf_Hexa[pa].lon[4] - (float) Surf_Hexa[pa].lon[3];
		U3 = (float) Surf_Hexa[pa].lon[6] + (float) Surf_Hexa[pa].lon[5]; 	V3 = (float) Surf_Hexa[pa].lon[6] - (float) Surf_Hexa[pa].lon[5];

		U1 = (float) U1 / periode_fils;					V1 = (float) V1 / periode_fils;
		U2 = (float) U2 / periode_fils;					V2 = (float) V2 / periode_fils;
		U3 = (float) U3 / periode_fils;					V3 = (float) V3 / periode_fils;


		/*printf(" U  : %8f %8f %8f \n",U1,U2,U3);
		printf(" V  : %8f %8f %8f \n",V1,V2,V3);*/
		
		ve1[1] = (REEL) Noeud[sommet1].inix; ve1[2] = (REEL) Noeud[sommet1].iniy; ve1[3] = (REEL) Noeud[sommet1].iniz;
		ve2[1] = (REEL) Noeud[sommet2].inix; ve2[2] = (REEL) Noeud[sommet2].iniy; ve2[3] = (REEL) Noeud[sommet2].iniz;
		ve3[1] = (REEL) Noeud[sommet3].inix; ve3[2] = (REEL) Noeud[sommet3].iniy; ve3[3] = (REEL) Noeud[sommet3].iniz;

		n1 = fabs(U3-U2);
		n2 = fabs(U1-U3);
		n3 = fabs(U2-U1);

		m1 = fabs(V3-V2);
		m2 = fabs(V1-V3);
		m3 = fabs(V2-V1);
		if (n3 != 0.0) 
			{
			u12[1] = (ve2[1]-ve1[1]) / n3; 	u21[1] = -(ve2[1]-ve1[1]) / n3; 
			u12[2] = (ve2[2]-ve1[2]) / n3; 	u21[2] = -(ve2[2]-ve1[2]) / n3; 
			u12[3] = (ve2[3]-ve1[3]) / n3; 	u21[3] = -(ve2[3]-ve1[3]) / n3; 
			}
		else 
			{
			/*printf(" pa  : %8d n1 :  %8.2f  n2 :  %8.2f  n3 :  %8.2f \n",pa,n1,n2,n3);*/
			u12[1] = 0.0;			u21[1] = 0.0;
			u12[2] = 0.0;			u21[2] = 0.0;
			u12[3] = 0.0;			u21[3] = 0.0;
			}
		if (m3 != 0.0) 
			{
			v12[1] = (ve2[1]-ve1[1]) / m3; 	v21[1] = -(ve2[1]-ve1[1]) / m3; 
			v12[2] = (ve2[2]-ve1[2]) / m3; 	v21[2] = -(ve2[2]-ve1[2]) / m3; 
			v12[3] = (ve2[3]-ve1[3]) / m3; 	v21[3] = -(ve2[3]-ve1[3]) / m3; 
			}
		else 
			{
			v12[1] = 0.0;			v21[1] = 0.0;
			v12[2] = 0.0;			v21[2] = 0.0;
			v12[3] = 0.0;			v21[3] = 0.0;
			}
			
		if (n2 != 0.0) 
			{
			u31[1] = (ve1[1]-ve3[1]) / n2; 	u13[1] = -(ve1[1]-ve3[1]) / n2; 
			u31[2] = (ve1[2]-ve3[2]) / n2; 	u13[2] = -(ve1[2]-ve3[2]) / n2; 
			u31[3] = (ve1[3]-ve3[3]) / n2; 	u13[3] = -(ve1[3]-ve3[3]) / n2; 
			}
		else 
			{
			u31[1] = 0.0;			u13[1] = 0.0;
			u31[2] = 0.0;			u13[2] = 0.0;
			u31[3] = 0.0;			u13[3] = 0.0;
			}
		if (m2 != 0.0) 
			{
			v31[1] = (ve1[1]-ve3[1]) / m2; 	v13[1] = -(ve1[1]-ve3[1]) / m2; 
			v31[2] = (ve1[2]-ve3[2]) / m2; 	v13[2] = -(ve1[2]-ve3[2]) / m2; 
			v31[3] = (ve1[3]-ve3[3]) / m2; 	v13[3] = -(ve1[3]-ve3[3]) / m2; 
			}
		else 
			{
			v31[1] = 0.0;			v13[1] = 0.0;
			v31[2] = 0.0;			v13[2] = 0.0;
			v31[3] = 0.0;			v13[3] = 0.0;
			}
			
		if (n1 != 0.0) 
			{
			u23[1] = (ve3[1]-ve2[1]) / n1; 	u32[1] = -(ve3[1]-ve2[1]) / n1; 
			u23[2] = (ve3[2]-ve2[2]) / n1; 	u32[2] = -(ve3[2]-ve2[2]) / n1; 
			u23[3] = (ve3[3]-ve2[3]) / n1; 	u32[3] = -(ve3[3]-ve2[3]) / n1; 
			}
		else 
			{
			u23[1] = 0.0;			u32[1] = 0.0;
			u23[2] = 0.0;			u32[2] = 0.0;
			u23[3] = 0.0;			u32[3] = 0.0;
			}
		if (m1 != 0.0) 
			{
			v23[1] = (ve3[1]-ve2[1]) / m1; 	v32[1] = -(ve3[1]-ve2[1]) / m1; 
			v23[2] = (ve3[2]-ve2[2]) / m1; 	v32[2] = -(ve3[2]-ve2[2]) / m1; 
			v23[3] = (ve3[3]-ve2[3]) / m1; 	v32[3] = -(ve3[3]-ve2[3]) / m1; 
			}
		else 
			{
			v23[1] = 0.0;			v32[1] = 0.0;
			v23[2] = 0.0;			v32[2] = 0.0;
			v23[3] = 0.0;			v32[3] = 0.0;
			}

		if ((n3>=n1) && (n3>=n2))
			{
  			hachu_hexa_u(pa,ve1,u13,u12,n2,U1,U2);
  			hachu_hexa_u(pa,ve2,u21,u23,n1,U2,U1);
			}
		if ((n2> n3) && (n2>=n1))
			{
  			hachu_hexa_u(pa,ve1,u13,u12,n3,U1,U3);
 			/*exit(0);*/
 			hachu_hexa_u(pa,ve3,u31,u32,n1,U3,U1);
			}	
		if ((n1> n2) && (n1> n3))
			{
  			hachu_hexa_u(pa,ve2,u23,u21,n3,U2,U3);
  			hachu_hexa_u(pa,ve3,u32,u31,n2,U3,U2);
			}
						
		if ((m3>=m1) && (m3>=m2)) 
			{
  			hachu_hexa_v(pa,ve1,v13,v12,m2,V1,V2);
  			hachu_hexa_v(pa,ve2,v21,v23,m1,V2,V1);
			}
		if ((m2> m3) && (m2>=m1)) 
			{
  			hachu_hexa_v(pa,ve1,v13,v12,m3,V1,V3);
  			hachu_hexa_v(pa,ve3,v31,v32,m1,V3,V1);
			}
		if ((m1> m2) && (m1> m3)) 
			{
  			hachu_hexa_v(pa,ve2,v23,v21,m3,V2,V3);
  			hachu_hexa_v(pa,ve3,v32,v31,m2,V3,V2);
			}
			
		}
	}
	
void  hachu_hexa_u(int pa, float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui)
	{
	/*
	pa est le numero du triangle dans lequel on calcule les positions des 2 extremites
	des fils
	vh est le sommet a partir du quel on calcule les fils
	uh1 est le premier vecteur de separation des fils sur le premier cote
	uh2 est le second  vecteur de separation des fils sur le second  cote
	nh est le nb de fils
	Uh et Ui sont les decalages du premier fil relativement au sommet vh
	*/
	
	float debut;
	int ind,nb,fils;
	
	/*printf(" vh  : %8.2f %8.2f %8.2f\n",vh [1],vh [2],vh [3]);*/
	if (Ui > Uh)	debut = (float) ( - Uh + ceil  ((double) Uh)); 
	else 		debut = (float) (   Uh - floor ((double) Uh));
	nb = (int) (floor(nh-debut+1));
	
	/*if (nh == 0.0) printf("nh = %8.2f debut = %8.2f  nb = %8d\n",nh,debut,nb );*/
	
	for (ind=1;ind<=nb;ind++)
		{
		Surf_Hexa[pa].nb_Ufils++;
		fils = Surf_Hexa[pa].nb_Ufils;
		/*printf("Surf_Hexa[pa].nb_Ufils = %d\n",fils);*/
		
		Surf_Hexa[pa].g1_Ux = 	(float *) Realloc_float(Surf_Hexa[pa].g1_Ux,1 + fils);
		Surf_Hexa[pa].g1_Uy = 	(float *) Realloc_float(Surf_Hexa[pa].g1_Uy,1 + fils);
		Surf_Hexa[pa].g1_Uz = 	(float *) Realloc_float(Surf_Hexa[pa].g1_Uz,1 + fils);
		Surf_Hexa[pa].g2_Ux = 	(float *) Realloc_float(Surf_Hexa[pa].g2_Ux,1 + fils);
		Surf_Hexa[pa].g2_Uy = 	(float *) Realloc_float(Surf_Hexa[pa].g2_Uy,1 + fils);
		Surf_Hexa[pa].g2_Uz = 	(float *) Realloc_float(Surf_Hexa[pa].g2_Uz,1 + fils);
		Surf_Hexa[pa].f1_Ux = 	(float *) Realloc_float(Surf_Hexa[pa].f1_Ux,1 + fils);
		Surf_Hexa[pa].f1_Uy = 	(float *) Realloc_float(Surf_Hexa[pa].f1_Uy,1 + fils);
		Surf_Hexa[pa].f2_Ux = 	(float *) Realloc_float(Surf_Hexa[pa].f2_Ux,1 + fils);
		Surf_Hexa[pa].f2_Uy = 	(float *) Realloc_float(Surf_Hexa[pa].f2_Uy,1 + fils);

		Surf_Hexa[pa].g1_Ux[fils] = vh[1]+debut*uh1[1] + (ind-1) * uh1[1]; /*coordonnee selon x de l extremite 1 du fil*/
		Surf_Hexa[pa].g2_Ux[fils] = vh[1]+debut*uh2[1] + (ind-1) * uh2[1]; /*coordonnee selon x de l extremite 2 du fil*/
		Surf_Hexa[pa].g1_Uy[fils] = vh[2]+debut*uh1[2] + (ind-1) * uh1[2]; /*coordonnee selon y de l extremite 1 du fil*/
		Surf_Hexa[pa].g2_Uy[fils] = vh[2]+debut*uh2[2] + (ind-1) * uh2[2]; /*coordonnee selon y de l extremite 2 du fil*/
		Surf_Hexa[pa].g1_Uz[fils] = vh[3]+debut*uh1[3] + (ind-1) * uh1[3]; /*coordonnee selon z de l extremite 1 du fil*/
		Surf_Hexa[pa].g2_Uz[fils] = vh[3]+debut*uh2[3] + (ind-1) * uh2[3]; /*coordonnee selon z de l extremite 2 du fil*/
		Surf_Hexa[pa].f1_Ux[fils] = Surf_Hexa[pa].g1_Ux[fils];
		Surf_Hexa[pa].f2_Ux[fils] = Surf_Hexa[pa].g2_Ux[fils];
		Surf_Hexa[pa].f1_Uy[fils] = Surf_Hexa[pa].g1_Uy[fils];
		Surf_Hexa[pa].f2_Uy[fils] = Surf_Hexa[pa].g2_Uy[fils];
		
		/*printf(" Surf_Hexa[pa].g1_U  : %8.2f %8.2f\n",Surf_Hexa[pa].g1_Ux[fils],Surf_Hexa[pa].g1_Uy[fils]);
		printf(" Surf_Hexa[pa].g2_U  : %8.2f %8.2f\n",Surf_Hexa[pa].g2_Ux[fils],Surf_Hexa[pa].g2_Uy[fils]);*/
		}
	}
	
	
void  hachu_hexa_v(int pa, float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui)
	{
	/*
	pa est le numero du triangle dans lequel on calcule les positions des 2 extremites
	des fils
	vh est le sommet a partir du quel on calcule les fils
	uh1 est le premier vecteur de separation des fils sur le premier cote
	uh2 est le second  vecteur de separation des fils sur le second  cote
	nh est le nb de fils
	Uh et Ui sont les decalages du premier fil relativement au sommet vh
	*/
	
	float debut;
	int ind,nb,fils;
	
	/*printf(" vh  : %8.2f %8.2f %8.2f\n",vh [1],vh [2],vh [3]);*/
	if (Ui > Uh)	debut = (float) ( - Uh + ceil  ((double) Uh)); 
	else 		debut = (float) (   Uh - floor ((double) Uh));
	nb = (int) (floor(nh-debut+1));
	
	/*if (nh == 0.0) printf("nh = %8.2f debut = %8.2f  nb = %8d\n",nh,debut,nb );*/
	
	for (ind=1;ind<=nb;ind++)
		{
		Surf_Hexa[pa].nb_Vfils++;
		fils = Surf_Hexa[pa].nb_Vfils;
		/*printf("Surf_Hexa[pa].nb_Vfils = %d\n",fils);*/
		Surf_Hexa[pa].g1_Vx = 	(float *) Realloc_float(Surf_Hexa[pa].g1_Vx,1 + fils);
		Surf_Hexa[pa].g1_Vy = 	(float *) Realloc_float(Surf_Hexa[pa].g1_Vy,1 + fils);
		Surf_Hexa[pa].g1_Vz = 	(float *) Realloc_float(Surf_Hexa[pa].g1_Vz,1 + fils);
		Surf_Hexa[pa].g2_Vx = 	(float *) Realloc_float(Surf_Hexa[pa].g2_Vx,1 + fils);
		Surf_Hexa[pa].g2_Vy = 	(float *) Realloc_float(Surf_Hexa[pa].g2_Vy,1 + fils);
		Surf_Hexa[pa].g2_Vz = 	(float *) Realloc_float(Surf_Hexa[pa].g2_Vz,1 + fils);
		Surf_Hexa[pa].f1_Vx = 	(float *) Realloc_float(Surf_Hexa[pa].f1_Vx,1 + fils);
		Surf_Hexa[pa].f1_Vy = 	(float *) Realloc_float(Surf_Hexa[pa].f1_Vy,1 + fils);
		Surf_Hexa[pa].f2_Vx = 	(float *) Realloc_float(Surf_Hexa[pa].f2_Vx,1 + fils);
		Surf_Hexa[pa].f2_Vy = 	(float *) Realloc_float(Surf_Hexa[pa].f2_Vy,1 + fils);

		Surf_Hexa[pa].g1_Vx[fils] = vh[1]+debut*uh1[1] + (ind-1) * uh1[1]; /*coordonnee selon x de l extremite 1 du fil*/
		Surf_Hexa[pa].g2_Vx[fils] = vh[1]+debut*uh2[1] + (ind-1) * uh2[1]; /*coordonnee selon x de l extremite 2 du fil*/
		Surf_Hexa[pa].g1_Vy[fils] = vh[2]+debut*uh1[2] + (ind-1) * uh1[2]; /*coordonnee selon y de l extremite 1 du fil*/
		Surf_Hexa[pa].g2_Vy[fils] = vh[2]+debut*uh2[2] + (ind-1) * uh2[2]; /*coordonnee selon y de l extremite 2 du fil*/
		Surf_Hexa[pa].g1_Vz[fils] = vh[3]+debut*uh1[3] + (ind-1) * uh1[3]; /*coordonnee selon z de l extremite 1 du fil*/
		Surf_Hexa[pa].g2_Vz[fils] = vh[3]+debut*uh2[3] + (ind-1) * uh2[3]; /*coordonnee selon z de l extremite 2 du fil*/
		Surf_Hexa[pa].f1_Vx[fils] = Surf_Hexa[pa].g1_Vx[fils];
		Surf_Hexa[pa].f2_Vx[fils] = Surf_Hexa[pa].g2_Vx[fils];
		Surf_Hexa[pa].f1_Vy[fils] = Surf_Hexa[pa].g1_Vy[fils];
		Surf_Hexa[pa].f2_Vy[fils] = Surf_Hexa[pa].g2_Vy[fils];
		
		/*printf(" Surf_Hexa[pa].g1_V  : %8.2f %8.2f\n",Surf_Hexa[pa].g1_Vx[fils],Surf_Hexa[pa].g1_Vy[fils]);
		printf(" Surf_Hexa[pa].g2_V  : %8.2f %8.2f\n",Surf_Hexa[pa].g2_Vx[fils],Surf_Hexa[pa].g2_Vy[fils]);*/
		}
	}
	
	
