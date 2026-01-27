#include "batz.h"

void fils_contour_calculer()
	{
	int sommet1,sommet2,sommet3,pa;
	float U1,U2,U3,V1,V2,V3,n1,n2,n3,m1,m2,m3;
	float ve1[4],ve2[4],ve3[4];
	float u12[4],u23[4],u31[4],v12[4],v23[4],v31[4];
	float u21[4],u32[4],u13[4],v21[4],v32[4],v13[4];
	float lside12,lside23,lside31,side12[4],side23[4],side31[4],debut,deb1,deb2,lu13,lu12;
	
	printf(" fils_contour_calculer arg \n");
			
   	if (periode_fils <= 0) periode_fils = 1;
	
	for (pa=1;pa<=NOMBRE_SURFACES;pa++)
		{
		/*if (pa == 89) exit(0);*/
		/*if (Surface[pa].type == 1)	periode_fils =10;
		if (Surface[pa].type == 2)	periode_fils =10;
		if (Surface[pa].type == 3)	periode_fils =10;
		if (Surface[pa].type == 4)	periode_fils =3;
		if (Surface[pa].type == 5)	periode_fils =3;
		if (Surface[pa].type == 6)	periode_fils =3;
		if (Surface[pa].type == 7)	periode_fils =3;
		if (Surface[pa].type == 8)	periode_fils =3;
		if (Surface[pa].type == 9)	periode_fils =3;
		if (Surface[pa].type == 10)	periode_fils =10;
		if (Surface[pa].type == 11)	periode_fils =10;
		if (Surface[pa].type == 12)	periode_fils =10;
		if (Surface[pa].type == 13)	periode_fils =10;
		if (Surface[pa].type == 14)	periode_fils =10;
		if (Surface[pa].type == 15)	periode_fils =10;
		if (Surface[pa].type == 16)	periode_fils =20;
		if (Surface[pa].type == 17)	periode_fils =20;
		if (Surface[pa].type == 18)	periode_fils =20;
		if (Surface[pa].type == 19)	periode_fils =40;
		if (Surface[pa].type == 20)	periode_fils =40;
		if (Surface[pa].type == 21)	periode_fils =40;
		if (Surface[pa].type == 22)	periode_fils =20;
		if (Surface[pa].type == 23)	periode_fils =20;
		if (Surface[pa].type == 24)	periode_fils =20;
		if (Surface[pa].type == 25)	periode_fils =10;
		if (Surface[pa].type == 26)	periode_fils =10;
		if (Surface[pa].type == 27)	periode_fils =10;*/
		sommet1 = Surface[pa].extremite[1];
		sommet2 = Surface[pa].extremite[2];
		sommet3 = Surface[pa].extremite[3];

		//printf("pa %d sommets  %8d %8d %8d \n",pa,sommet1,sommet2,sommet3);/**/
		
		U1 = (float) Surface[pa].lon[2] + (float) Surface[pa].lon[1]; 	V1 = (float) Surface[pa].lon[2] - (float) Surface[pa].lon[1];
		U2 = (float) Surface[pa].lon[4] + (float) Surface[pa].lon[3]; 	V2 = (float) Surface[pa].lon[4] - (float) Surface[pa].lon[3];
		U3 = (float) Surface[pa].lon[6] + (float) Surface[pa].lon[5]; 	V3 = (float) Surface[pa].lon[6] - (float) Surface[pa].lon[5];

		U1 = (float) U1 / periode_fils;					V1 = (float) V1 / periode_fils;
		U2 = (float) U2 / periode_fils;					V2 = (float) V2 / periode_fils;
		U3 = (float) U3 / periode_fils;					V3 = (float) V3 / periode_fils;


		/*printf(" U  : %8f %8f %8f \n",U1,U2,U3);
		printf(" V  : %8f %8f %8f \n",V1,V2,V3);
		exit(0);*/
		
		ve1[1] = (REEL) Noeud[sommet1].inix; ve1[2] = (REEL) Noeud[sommet1].iniy; ve1[3] = (REEL) Noeud[sommet1].iniz;
		ve2[1] = (REEL) Noeud[sommet2].inix; ve2[2] = (REEL) Noeud[sommet2].iniy; ve2[3] = (REEL) Noeud[sommet2].iniz;
		ve3[1] = (REEL) Noeud[sommet3].inix; ve3[2] = (REEL) Noeud[sommet3].iniy; ve3[3] = (REEL) Noeud[sommet3].iniz;

		n1 = fabs(U3-U2);
		n2 = fabs(U1-U3);
		n3 = fabs(U2-U1);
		/*printf("n1  : %8f  n2  : %8f  n3  : %8f \n",n1,n2,n3);*/

		m1 = fabs(V3-V2);
		m2 = fabs(V1-V3);
		m3 = fabs(V2-V1);
		/*printf("m1  : %8f  m2  : %8f  m3  : %8f \n",m1,m2,m3);*/
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
			
		sou_vect(ve2, ve1, side12);			/*the side 12 is ve2-ve1*/
		sou_vect(ve3, ve2, side23);			/*the side 12 is ve2-ve1*/
		sou_vect(ve1, ve3, side31);			/*the side 12 is ve2-ve1*/
		lside12 = produit_scal(side12,side12);		/*length of side 12*/
		lside23 = produit_scal(side23,side23);		/*length of side 23*/
		lside31 = produit_scal(side31,side31);		/*length of side 31*/

		/*printf("pa %5d ",pa);
		printf("n1 %5.2f  n2 %5.2f  n3 %5.2f   \n",n1,n2,n3);*/
		if ((n3>=n1) && (n3>=n2))
			{
  			hachu4_u(pa,ve1,u13,u12,n2,U1,U2);	/*start from vertex 1, */
			Surface[pa].vertexU1 = 1;						
			if (n3 != 0.0) 	Surface[pa].stepU11 = (float) 1.0/n3;	
			else 		Surface[pa].stepU11 = (float) 0.0;
			if (n2 != 0.0) 	Surface[pa].stepU12 = (float) 1.0/n2;	
			else 		Surface[pa].stepU12 = (float) 0.0;
			if (U3 > U1)	debut = (float) ( - U1 + ceil  ((double) U1)) / (U3 - U1);
			else 		debut = (float) (   U1 - floor ((double) U1)) / (U1 - U3);
			if (U3 == U1)	debut = 0.0;			
			Surface[pa].beginU12 = (float) debut;
			Surface[pa].nU1 = (int) (floor(n2-debut+1));
			if (U2 > U1)	debut = (float) ( - U1 + ceil  ((double) U1)) / (U2 - U1);
			else 		debut = (float) (   U1 - floor ((double) U1)) / (U1 - U2);
			if (U2 == U1) debut = 0.0;
			Surface[pa].beginU11 = (float) debut;/**/
			/*printf("pa %5d ",pa);
			printf("n3 %5.2f   \n",n3);
			printf("vertexU1 %5d ",Surface[pa].vertexU1);
			printf("nU1 %5d  ",Surface[pa].nU1);
			printf("beginU1 %5.2f ",Surface[pa].beginU11);
			printf("stepU1 %5.2f ",Surface[pa].stepU11);
			printf("beginU2 %5.2f ",Surface[pa].beginU12);
			printf("stepU2 %5.2f \n",Surface[pa].stepU12);
			printf(" U  : %8.2f %8.2f %8.2f ",U1,U2,U3);
			printf(" V  : %8.2f %8.2f %8.2f \n",V1,V2,V3);*/

  			hachu4_u(pa,ve2,u21,u23,n1,U2,U1);
			Surface[pa].vertexU2 = 2;				/*the twines will be drawn from vertex 1 and vertex 2*/
			if (n1 != 0.0) 	Surface[pa].stepU21 = (float) 1.0/n1;	
			else 		Surface[pa].stepU21 = (float) 0.0;
			if (n3 != 0.0) 	Surface[pa].stepU22 = (float) 1.0/n3;	
			else 		Surface[pa].stepU22 = (float) 0.0;			
			if (U1 > U2)	debut = (float) ( - U2 + ceil  ((double) U2)) / (U1 - U2);
			else 		debut = (float) (   U2 - floor ((double) U2)) / (U2 - U1);
			if (U1 == U2)	debut = 0.0;			
			Surface[pa].beginU22 = (float) debut;						
			Surface[pa].nU2 = (int) (floor(n1-debut+1));			
			if (U3 > U2)	debut = (float) ( - U2 + ceil  ((double) U2)) / (U3 - U2);
			else 		debut = (float) (   U2 - floor ((double) U2)) / (U2 - U3);
			if (U2 == U3) debut = 0.0;
			Surface[pa].beginU21 = (float) debut;/**/
			/*printf("pa %5d ",pa);
			printf("n3 %5.2f   \n",n3);
			printf("vertexU2 %5d ",Surface[pa].vertexU2);
			printf("nU1 %5d  ",Surface[pa].nU2);
			printf("beginU1 %5.2f ",Surface[pa].beginU21);
			printf("stepU1 %5.2f ",Surface[pa].stepU21);
			printf("beginU2 %5.2f ",Surface[pa].beginU22);
			printf("stepU2 %5.2f \n",Surface[pa].stepU22);
			printf(" U  : %8.2f %8.2f %8.2f ",U1,U2,U3);
			printf(" V  : %8.2f %8.2f %8.2f \n",V1,V2,V3);*/
			}
		if ((n2> n3) && (n2>=n1))
			{
  			hachu4_u(pa,ve1,u13,u12,n3,U1,U3);
  					
			Surface[pa].vertexU1 = 1;				/*the twines will be drawn from vertex 1 and vertex 2*/
			if (n3 != 0.0) 	Surface[pa].stepU11 = (float) 1.0/n3;	/*step along side 13*/
			else 		Surface[pa].stepU11 = (float) 0.0;	/*step along side 13*/
			if (n2 != 0.0) 	Surface[pa].stepU12 = (float) 1.0/n2;	/*step along side 13*/
			else 		Surface[pa].stepU12 = (float) 0.0;	/*step along side 13*/
			if (U3 > U1)	debut = (float) ( - U1 + ceil  ((double) U1)) / (U3 - U1); /*beginning twine*/
			else 		debut = (float) (   U1 - floor ((double) U1)) / (U1 - U3);
			if (U3 == U1) debut = 0.0;
			Surface[pa].beginU12 = (float) debut;
			Surface[pa].nU1 = (int) (floor(n3-debut+1));
			if (U2 > U1)	debut = (float) ( - U1 + ceil  ((double) U1)) / (U2 - U1); /*beginning twine*/
			else 		debut = (float) (   U1 - floor ((double) U1)) / (U1 - U2);
			if (U2 == U1) debut = 0.0;
			Surface[pa].beginU11 = (float) debut;
			/*
			printf("pa %5d ",pa);
			printf("n3 %5.2f   \n",n3);
			printf("vertexU1 %5d ",Surface[pa].vertexU1);
			printf("nU1 %5d  ",Surface[pa].nU1);
			printf("beginU1 %5.2f ",Surface[pa].beginU11);
			printf("stepU1 %5.2f ",Surface[pa].stepU11);
			printf("beginU2 %5.2f ",Surface[pa].beginU12);
			printf("stepU2 %5.2f \n",Surface[pa].stepU12);
			printf(" U  : %8.2f %8.2f %8.2f ",U1,U2,U3);
			printf(" V  : %8.2f %8.2f %8.2f \n",V1,V2,V3);
			*/
  			
  			
  			
  			hachu4_u(pa,ve3,u31,u32,n1,U3,U1);
			Surface[pa].vertexU2 = 3;				/*the twines will be drawn from vertex 1 and vertex 2*/
			if (n2 != 0.0) 	Surface[pa].stepU21 = (float) 1.0/n2;	/*step along side 13*/
			else 		Surface[pa].stepU21 = (float) 0.0;	/*step along side 13*/
			if (n1 != 0.0) 	Surface[pa].stepU22 = (float) 1.0/n1;	/*step along side 13*/
			else 		Surface[pa].stepU22 = (float) 0.0;	/*step along side 13*/
			if (U2 > U3)	debut = (float) ( - U3 + ceil  ((double) U3)) / (U2 - U3); /*beginning twine*/
			else 		debut = (float) (   U3 - floor ((double) U3)) / (U3 - U2);
			if (U2 == U3) debut = 0.0;
			Surface[pa].beginU22 = (float) debut;
			Surface[pa].nU2 = (int) (floor(n1-debut+1));
			if (U1 > U3)	debut = (float) ( - U3 + ceil  ((double) U3)) / (U1 - U3); /*beginning twine*/
			else 		debut = (float) (   U3 - floor ((double) U3)) / (U3 - U1);
			if (U3 == U1) debut = 0.0;
			Surface[pa].beginU21 = (float) debut;
			/*printf("pa %5d ",pa);
			printf("n3 %5.2f   \n",n3);
			printf("vertexU2 %5d ",Surface[pa].vertexU2);
			printf("nU1 %5d  ",Surface[pa].nU2);
			printf("beginU1 %5.2f ",Surface[pa].beginU21);
			printf("stepU1 %5.2f ",Surface[pa].stepU21);
			printf("beginU2 %5.2f ",Surface[pa].beginU22);
			printf("stepU2 %5.2f \n",Surface[pa].stepU22);
			printf(" U  : %8.2f %8.2f %8.2f ",U1,U2,U3);
			printf(" V  : %8.2f %8.2f %8.2f \n",V1,V2,V3);*/

			}	
		if ((n1> n2) && (n1> n3))
			{
  			hachu4_u(pa,ve2,u23,u21,n3,U2,U3);
			Surface[pa].vertexU1 = 2;
			if (n1 != 0.0) 	Surface[pa].stepU11 = (float) 1.0/n1;	
			else 		Surface[pa].stepU11 = (float) 0.0;
			if (n3 != 0.0) 	Surface[pa].stepU12 = (float) 1.0/n3;	
			else 		Surface[pa].stepU12 = (float) 0.0;			
			if (U1 > U2)	debut = (float) ( - U2 + ceil  ((double) U2)) / (U1 - U2);
			else 		debut = (float) (   U2 - floor ((double) U2)) / (U2 - U1);
			if (U1 == U2)	debut = 0.0;			
			Surface[pa].beginU12 = (float) debut;						
			Surface[pa].nU1 = (int) (floor(n3-debut+1));			
			if (U3 > U2)	debut = (float) ( - U2 + ceil  ((double) U2)) / (U3 - U2);
			else 		debut = (float) (   U2 - floor ((double) U2)) / (U2 - U3);
			if (U2 == U3) debut = 0.0;
			Surface[pa].beginU11 = (float) debut;/**/
			/*
			printf("pa %5d ",pa);
			printf("n3 %5.2f   \n",n3);
			printf("vertexU1 %5d ",Surface[pa].vertexU1);
			printf("nU1 %5d  ",Surface[pa].nU1);
			printf("beginU1 %5.2f ",Surface[pa].beginU11);
			printf("stepU1 %5.2f ",Surface[pa].stepU11);
			printf("beginU2 %5.2f ",Surface[pa].beginU12);
			printf("stepU2 %5.2f \n",Surface[pa].stepU12);
			printf(" U  : %8.2f %8.2f %8.2f ",U1,U2,U3);
			printf(" V  : %8.2f %8.2f %8.2f \n",V1,V2,V3);
			*/
			
  			hachu4_u(pa,ve3,u32,u31,n2,U3,U2);
			Surface[pa].vertexU2 = 3;				
			if (n2 != 0.0) 	Surface[pa].stepU21 = (float) 1.0/n2;	
			else 		Surface[pa].stepU21 = (float) 0.0;	
			if (n1 != 0.0) 	Surface[pa].stepU22 = (float) 1.0/n1;	
			else 		Surface[pa].stepU22 = (float) 0.0;	
			if (U2 > U3)	debut = (float) ( - U3 + ceil  ((double) U3)) / (U2 - U3); 
			else 		debut = (float) (   U3 - floor ((double) U3)) / (U3 - U2);
			if (U2 == U3) debut = 0.0;
			Surface[pa].beginU22 = (float) debut;
			Surface[pa].nU2 = (int) (floor(n2-debut+1));
			if (U1 > U3)	debut = (float) ( - U3 + ceil  ((double) U3)) / (U1 - U3); 
			else 		debut = (float) (   U3 - floor ((double) U3)) / (U3 - U1);
			if (U3 == U1) debut = 0.0;
			Surface[pa].beginU21 = (float) debut;/**/
			}
						
		if ((m3>=m1) && (m3>=m2)) 
			{
  			hachu4_v(pa,ve1,v13,v12,m2,V1,V2);
			Surface[pa].vertexV1 = 1;						
			if (m3 != 0.0) 	Surface[pa].stepV11 = (float) 1.0/m3;	
			else 		Surface[pa].stepV11 = (float) 0.0;
			if (m2 != 0.0) 	Surface[pa].stepV12 = (float) 1.0/m2;	
			else 		Surface[pa].stepV12 = (float) 0.0;
			if (V3 > V1)	deb2= (float) ( - V1 + ceil  ((double) V1)) / (V3 - V1);
			else 		deb2= (float) (   V1 - floor ((double) V1)) / (V1 - V3);
			if (V3 == V1)	deb2= 0.0;			
			if (V2 > V1)	deb1 = (float) ( - V1 + ceil  ((double) V1)) / (V2 - V1);
			else 		deb1 = (float) (   V1 - floor ((double) V1)) / (V1 - V2);
			if (V2 == V1) 	deb1 = 0.0;
			Surface[pa].beginV12 = (float) deb2;
			Surface[pa].beginV11 = (float) deb1;
			if (Surface[pa].beginV12 != 0.0)	Surface[pa].nV1 = (int) (floor(m2-deb2+0));
			else					Surface[pa].nV1 = (int) (floor(m2-deb2+1));
			/*
			printf("pa %5d ",pa);
			printf("m3 %5.2f   \n",m3);
			printf("vertexV1 %5d ",Surface[pa].vertexV1);
			printf("nV1 %5d  ",Surface[pa].nV1);
			printf("beginV11 %5.2f ",Surface[pa].beginV11);
			printf("stepV11 %5.2f ",Surface[pa].stepV11);
			printf("beginV12 %5.2f ",Surface[pa].beginV12);
			printf("stepV12 %5.2f ",Surface[pa].stepV12);
			printf("deb1 %8.2f deb2 %8.2f \n",deb1,deb2);
			printf(" U  : %8.2f %8.2f %8.2f ",U1,U2,U3);
			printf(" V  : %8.2f %8.2f %8.2f \n",V1,V2,V3);
			*/
  			hachu4_v(pa,ve2,v21,v23,m1,V2,V1);
			Surface[pa].vertexV2 = 2;				/*the twines will be drawn from vertex 1 and vertex 2*/
			if (m1 != 0.0) 	Surface[pa].stepV21 = (float) 1.0/m1;	
			else 		Surface[pa].stepV21 = (float) 0.0;
			if (m3 != 0.0) 	Surface[pa].stepV22 = (float) 1.0/m3;	
			else 		Surface[pa].stepV22 = (float) 0.0;			
			if (V1 > V2)	debut = (float) ( - V2 + ceil  ((double) V2)) / (V1 - V2);
			else 		debut = (float) (   V2 - floor ((double) V2)) / (V2 - V1);
			if (V1 == V2)	debut = 0.0;			
			Surface[pa].beginV22 = (float) debut;						
			if (Surface[pa].beginV22 != 0.0)	Surface[pa].nV2 = (int) (floor(m1-debut+0));
			else					Surface[pa].nV2 = (int) (floor(m1-debut+1));
			if (V3 > V2)	debut = (float) ( - V2 + ceil  ((double) V2)) / (V3 - V2);
			else 		debut = (float) (   V2 - floor ((double) V2)) / (V2 - V3);
			if (V2 == V3) debut = 0.0;
			Surface[pa].beginV21 = (float) debut;/**/
			/*printf("pa %5d ",pa);
			printf("m3 %5.2f   \n",m3);
			printf("vertexV2 %5d ",Surface[pa].vertexV2);
			printf("nV2 %5d  ",Surface[pa].nV2);
			printf("beginV21 %5d  ",Surface[pa].beginV21);
			printf("stepV21 %5.2f ",Surface[pa].stepV21);
			printf("beginV22 %5.2f ",Surface[pa].beginV22);
			printf("stepV22 %5.2f ",Surface[pa].stepV22);
			printf("U  : %8.2f %8.2f %8.2f ",U1,U2,U3);
			printf("V  : %8.2f %8.2f %8.2f \n",V1,V2,V3);*/
			}
		if ((m2> m3) && (m2>=m1)) 
			{
  			hachu4_v(pa,ve1,v13,v12,m3,V1,V3);
			Surface[pa].vertexV1 = 1;				/*the twines will be drawn from vertex 1 and vertex 2*/
			if (m3 != 0.0) 	Surface[pa].stepV11 = (float) 1.0/m3;	/*step along side 13*/
			else 		Surface[pa].stepV11 = (float) 0.0;	/*step along side 13*/
			if (m2 != 0.0) 	Surface[pa].stepV12 = (float) 1.0/m2;	/*step along side 13*/
			else 		Surface[pa].stepV12 = (float) 0.0;	/*step along side 13*/
			if (V3 > V1)	debut = (float) ( - V1 + ceil  ((double) V1)) / (V3 - V1); /*beginning twine*/
			else 		debut = (float) (   V1 - floor ((double) V1)) / (V1 - V3);
			if (V3 == V1) debut = 0.0;
			Surface[pa].beginV12 = (float) debut;
			Surface[pa].nV1 = (int) (floor(m3-debut+0));
			if (V2 > V1)	debut = (float) ( - V1 + ceil  ((double) V1)) / (V2 - V1); /*beginning twine*/
			else 		debut = (float) (   V1 - floor ((double) V1)) / (V1 - V2);
			if (V2 == V1) debut = 0.0;
			Surface[pa].beginV11 = (float) debut;
  			hachu4_v(pa,ve3,v31,v32,m1,V3,V1);
			Surface[pa].vertexV2 = 3;				/*the twines will be drawn from vertex 1 and vertex 2*/
			if (m2 != 0.0) 	Surface[pa].stepV21 = (float) 1.0/m2;	/*step along side 13*/
			else 		Surface[pa].stepV21 = (float) 0.0;	/*step along side 13*/
			if (m1 != 0.0) 	Surface[pa].stepV22 = (float) 1.0/m1;	/*step along side 13*/
			else 		Surface[pa].stepV22 = (float) 0.0;	/*step along side 13*/
			if (V2 > V3)	debut = (float) ( - V3 + ceil  ((double) V3)) / (V2 - V3); /*beginning twine*/
			else 		debut = (float) (   V3 - floor ((double) V3)) / (V3 - V2);
			if (V2 == V3) debut = 0.0;
			Surface[pa].beginV22 = (float) debut;
			Surface[pa].nV2 = (int) (floor(m1-debut+0));
			if (V1 > V3)	debut = (float) ( - V3 + ceil  ((double) V3)) / (V1 - V3); /*beginning twine*/
			else 		debut = (float) (   V3 - floor ((double) V3)) / (V3 - V1);
			if (V3 == V1) debut = 0.0;
			Surface[pa].beginV21 = (float) debut;
			}
		if ((m1> m2) && (m1> m3)) 
			{
  			hachu4_v(pa,ve2,v23,v21,m3,V2,V3);
			Surface[pa].vertexV1 = 2;
			if (m1 != 0.0) 	Surface[pa].stepV11 = (float) 1.0/m1;	
			else 		Surface[pa].stepV11 = (float) 0.0;
			if (m3 != 0.0) 	Surface[pa].stepV12 = (float) 1.0/m3;	
			else 		Surface[pa].stepV12 = (float) 0.0;			
			if (V1 > V2)	debut = (float) ( - V2 + ceil  ((double) V2)) / (V1 - V2);
			else 		debut = (float) (   V2 - floor ((double) V2)) / (V2 - V1);
			if (V1 == V2)	debut = 0.0;			
			Surface[pa].beginV12 = (float) debut;						
			Surface[pa].nV1 = (int) (floor(m3-debut+0));			
			if (V3 > V2)	debut = (float) ( - V2 + ceil  ((double) V2)) / (V3 - V2);
			else 		debut = (float) (   V2 - floor ((double) V2)) / (V2 - V3);
			if (V2 == V3) debut = 0.0;
			Surface[pa].beginV11 = (float) debut;/**/
  			hachu4_v(pa,ve3,v32,v31,m2,V3,V2);
			Surface[pa].vertexV2 = 3;				
			if (m2 != 0.0) 	Surface[pa].stepV21 = (float) 1.0/m2;	
			else 		Surface[pa].stepV21 = (float) 0.0;	
			if (m1 != 0.0) 	Surface[pa].stepV22 = (float) 1.0/m1;	
			else 		Surface[pa].stepV22 = (float) 0.0;	
			if (V2 > V3)	debut = (float) ( - V3 + ceil  ((double) V3)) / (V2 - V3); 
			else 		debut = (float) (   V3 - floor ((double) V3)) / (V3 - V2);
			if (V2 == V3) debut = 0.0;
			Surface[pa].beginV22 = (float) debut;
			Surface[pa].nV2 = (int) (floor(m2-debut+0));
			if (V1 > V3)	debut = (float) ( - V3 + ceil  ((double) V3)) / (V1 - V3); 
			else 		debut = (float) (   V3 - floor ((double) V3)) / (V3 - V1);
			if (V3 == V1) debut = 0.0;
			Surface[pa].beginV21 = (float) debut;/**/
			}
			
		}
	}	

void  hachu4_u(int pa, float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui)
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
	/*printf(" Uh  %8.2f Ui %8.2f debut %8.2f\n",Uh,Ui,debut);*/
	nb = (int) (floor(nh-debut+1));
	
	/*if (nh == 0.0) printf("nh = %8.2f debut = %8.2f  nb = %8d\n",nh,debut,nb );*/
	
	for (ind=1;ind<=nb;ind++)
		{
		Surface[pa].nb_ufils++;
		fils = Surface[pa].nb_ufils;
		/*printf("Surface[%d].nb_ufils = %d\n",pa,fils);*/

		Surface[pa].g1_ux = 	(float *) Realloc_float(Surface[pa].g1_ux,1 + fils);
		Surface[pa].g1_uy = 	(float *) Realloc_float(Surface[pa].g1_uy,1 + fils);
		Surface[pa].g1_uz = 	(float *) Realloc_float(Surface[pa].g1_uz,1 + fils);
		Surface[pa].g2_ux = 	(float *) Realloc_float(Surface[pa].g2_ux,1 + fils);
		Surface[pa].g2_uy = 	(float *) Realloc_float(Surface[pa].g2_uy,1 + fils);
		Surface[pa].g2_uz = 	(float *) Realloc_float(Surface[pa].g2_uz,1 + fils);
		Surface[pa].f1_ux = 	(float *) Realloc_float(Surface[pa].f1_ux,1 + fils);
		Surface[pa].f1_uy = 	(float *) Realloc_float(Surface[pa].f1_uy,1 + fils);
		Surface[pa].f2_ux = 	(float *) Realloc_float(Surface[pa].f2_ux,1 + fils);
		Surface[pa].f2_uy = 	(float *) Realloc_float(Surface[pa].f2_uy,1 + fils);

		Surface[pa].g1_ux[fils] = vh[1]+debut*uh1[1] + (ind-1) * uh1[1]; /*coordonnee selon x de l extremite 1 du fil*/
		Surface[pa].g2_ux[fils] = vh[1]+debut*uh2[1] + (ind-1) * uh2[1]; /*coordonnee selon x de l extremite 2 du fil*/
		Surface[pa].g1_uy[fils] = vh[2]+debut*uh1[2] + (ind-1) * uh1[2]; /*coordonnee selon y de l extremite 1 du fil*/
		Surface[pa].g2_uy[fils] = vh[2]+debut*uh2[2] + (ind-1) * uh2[2]; /*coordonnee selon y de l extremite 2 du fil*/
		Surface[pa].g1_uz[fils] = vh[3]+debut*uh1[3] + (ind-1) * uh1[3]; /*coordonnee selon z de l extremite 1 du fil*/
		Surface[pa].g2_uz[fils] = vh[3]+debut*uh2[3] + (ind-1) * uh2[3]; /*coordonnee selon z de l extremite 2 du fil*/
		Surface[pa].f1_ux[fils] = Surface[pa].g1_ux[fils];
		Surface[pa].f2_ux[fils] = Surface[pa].g2_ux[fils];
		Surface[pa].f1_uy[fils] = Surface[pa].g1_uy[fils];
		Surface[pa].f2_uy[fils] = Surface[pa].g2_uy[fils];
		
		/*printf(" Surface[pa].g1_u  : %8.2f %8.2f\n",Surface[pa].g1_ux[fils],Surface[pa].g1_uy[fils]);
		printf(" Surface[pa].g2_u  : %8.2f %8.2f\n",Surface[pa].g2_ux[fils],Surface[pa].g2_uy[fils]);*/
		}
	/*printf("Surface[%d].nb_ufils = %d\n",pa,Surface[pa].nb_ufils);*/
	}
	
	
void  hachu4_v(int pa, float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui)
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
		Surface[pa].nb_vfils++;
		fils = Surface[pa].nb_vfils;
		/*printf("Surface[pa].nb_vfils = %d\n",fils);*/
		Surface[pa].g1_vx = 	(float *) Realloc_float(Surface[pa].g1_vx,1 + fils);
		Surface[pa].g1_vy = 	(float *) Realloc_float(Surface[pa].g1_vy,1 + fils);
		Surface[pa].g1_vz = 	(float *) Realloc_float(Surface[pa].g1_vz,1 + fils);
		Surface[pa].g2_vx = 	(float *) Realloc_float(Surface[pa].g2_vx,1 + fils);
		Surface[pa].g2_vy = 	(float *) Realloc_float(Surface[pa].g2_vy,1 + fils);
		Surface[pa].g2_vz = 	(float *) Realloc_float(Surface[pa].g2_vz,1 + fils);
		Surface[pa].f1_vx = 	(float *) Realloc_float(Surface[pa].f1_vx,1 + fils);
		Surface[pa].f1_vy = 	(float *) Realloc_float(Surface[pa].f1_vy,1 + fils);
		Surface[pa].f2_vx = 	(float *) Realloc_float(Surface[pa].f2_vx,1 + fils);
		Surface[pa].f2_vy = 	(float *) Realloc_float(Surface[pa].f2_vy,1 + fils);
		
		Surface[pa].g1_vx[fils] = vh[1]+debut*uh1[1] + (ind-1) * uh1[1]; /*coordonnee selon x de l extremite 1 du fil*/
		Surface[pa].g2_vx[fils] = vh[1]+debut*uh2[1] + (ind-1) * uh2[1]; /*coordonnee selon x de l extremite 2 du fil*/
		Surface[pa].g1_vy[fils] = vh[2]+debut*uh1[2] + (ind-1) * uh1[2]; /*coordonnee selon y de l extremite 1 du fil*/
		Surface[pa].g2_vy[fils] = vh[2]+debut*uh2[2] + (ind-1) * uh2[2]; /*coordonnee selon y de l extremite 2 du fil*/
		Surface[pa].g1_vz[fils] = vh[3]+debut*uh1[3] + (ind-1) * uh1[3]; /*coordonnee selon z de l extremite 1 du fil*/
		Surface[pa].g2_vz[fils] = vh[3]+debut*uh2[3] + (ind-1) * uh2[3]; /*coordonnee selon z de l extremite 2 du fil*/
		Surface[pa].f1_vx[fils] = Surface[pa].g1_vx[fils];
		Surface[pa].f2_vx[fils] = Surface[pa].g2_vx[fils];
		Surface[pa].f1_vy[fils] = Surface[pa].g1_vy[fils];
		Surface[pa].f2_vy[fils] = Surface[pa].g2_vy[fils];
		
		/*printf(" Surface[pa].g1_v  : %8.2f %8.2f\n",Surface[pa].g1_vx[fils],Surface[pa].g1_vy[fils]);
		printf(" Surface[pa].g2_v  : %8.2f %8.2f\n",Surface[pa].g2_vx[fils],Surface[pa].g2_vy[fils]);*/
		}
	}
	
	
