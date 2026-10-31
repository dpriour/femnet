#define PRINCIPAL 0
#include "4c19.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//#define DEBUG

//===================================================================================================================================//
// debut du programme

void pliage_barre_pardiso2_2()
{
	/*barres alignées au repos
	efforts waelem des barres d'un element qui se plient. Les efforts sont calcules
	pour tout les plis aux noeuds appartenant a cet element, ces noeuds
	n etant pas aux extremites de l element*/
	//------------------------------------------------------------------------------------------------------------------------------------
	// Donnees	
	int elem1,elem2,zi,zj,zk,zl,zm,zr,zs;				//elem1&elem2 : les 2 barres, zi,zj&zk noeuds des 3 extremités (1,2&3) des 2 barres
	double x1,y1,z1,x2,y2,z2,x3,y3,z3;			//coordonnees des 3 extremités (1,2&3) des 2 barres
	double na,na2,na3,na4;					//distance 1 2 et son carre cube ...
	double nb,nb2,nb3,nb4;					//distance 2 3 et son carre cube ...
	double nc,nc2,nc3,nc4;					//distance 1 3 et son carre cube ...
	double EI, PS;						//raideur en flexion, produit scalaire barre1 barre2
	double Fx1, Fx2, Fx3, Fy1, Fy2, Fy3, Fz1, Fz2, Fz3;	//efforts locaux
	double K[10][10];	//matrice raideur locale
	int coor[10];		//transformation composantes locales vers composantes globales

	int voisin_trouve=0;
	int symetrie = 0;

	double term1,term2,term3;				//parties des efforts
	double Dterm1_x1,Dterm1_y1,Dterm1_z1,Dterm1_x2,Dterm1_y2,Dterm1_z2,Dterm1_x3,Dterm1_y3,Dterm1_z3;	//D : dérivée _x1 par rapport à x1
	double Dterm2_x1,Dterm2_y1,Dterm2_z1,Dterm2_x2,Dterm2_y2,Dterm2_z2,Dterm2_x3,Dterm2_y3,Dterm2_z3;
	double Dterm3_x1,Dterm3_y1,Dterm3_z1,Dterm3_x2,Dterm3_y2,Dterm3_z2,Dterm3_x3,Dterm3_y3,Dterm3_z3;
	double dFx1_x1,dFx1_y1,dFx1_z1,dFx1_x2,dFx1_y2,dFx1_z2,dFx1_x3,dFx1_y3,dFx1_z3;
	double dFy1_x1,dFy1_y1,dFy1_z1,dFy1_x2,dFy1_y2,dFy1_z2,dFy1_x3,dFy1_y3,dFy1_z3;
	double dFz1_x1,dFz1_y1,dFz1_z1,dFz1_x2,dFz1_y2,dFz1_z2,dFz1_x3,dFz1_y3,dFz1_z3;
	double dFx2_x1,dFx2_y1,dFx2_z1,dFx2_x2,dFx2_y2,dFx2_z2,dFx2_x3,dFx2_y3,dFx2_z3;
	double dFy2_x1,dFy2_y1,dFy2_z1,dFy2_x2,dFy2_y2,dFy2_z2,dFy2_x3,dFy2_y3,dFy2_z3;
	double dFz2_x1,dFz2_y1,dFz2_z1,dFz2_x2,dFz2_y2,dFz2_z2,dFz2_x3,dFz2_y3,dFz2_z3;
	double dFx3_x1,dFx3_y1,dFx3_z1,dFx3_x2,dFx3_y2,dFx3_z2,dFx3_x3,dFx3_y3,dFx3_z3;
	double dFy3_x1,dFy3_y1,dFy3_z1,dFy3_x2,dFy3_y2,dFy3_z2,dFy3_x3,dFy3_y3,dFy3_z3;
	double dFz3_x1,dFz3_y1,dFz3_z1,dFz3_x2,dFz3_y2,dFz3_z2,dFz3_x3,dFz3_y3,dFz3_z3;

	//------------------------------------------------------------------------------------------------------------------------------------
	/*
	Nous allons chercher les barres qui sont voisines a l'aide des noeuds composants celles-ci.
	le noeud zj est le noeud qui est situé au milieu des deux barres. 
	les noeuds zi et zk se situent de chaque cote de zj.
	*/
	for (elem1 = 1; elem1<= NOMBRE_ELEMENTS-1; elem1++)
	{
		if (Element[elem1].EI_flexion > 0.0)
		{
			for (zl = 1; zl<= 2; zl++)
			{
				if (zl == 1) zm = 2;
				if (zl == 2) zm = 1;
				zi = Element[elem1].extremite[zl];	//premiere extremite de la barre 1
				zj = Element[elem1].extremite[zm];	//seconde extremite de la barre 1 et premiere extremite de la barre 2
				zk = 0;					//seconde extremite de la barre 2
				voisin_trouve = 0;
				symetrie = 0;
				//printf("zl %d elem1 %d zi %d zj %d  \n",zl,elem1,zi,zj);
				//printf("sym %d  %d  %d  \n",Noeud[zj].symx,Noeud[zj].symy,Noeud[zj].symz);

				if (Noeud[zj].symx || Noeud[zj].symy || Noeud[zj].symz) //test de la symétrie
				{
					// Voisin virtuel
					x1 = wf[3*zi-2];	y1 = wf[3*zi-1];	z1 = wf[3*zi-0];
					x2 = wf[3*zj-2];	y2 = wf[3*zj-1];	z2 = wf[3*zj-0]; // noeud sur le plan de symetrie
					x3 = wf[3*zi-2];	y3 = wf[3*zi-1];	z3 = wf[3*zi-0]; // Clone du premier point

					// test pour trouver la coordonnee du point symetrique
					if (Noeud[zj].symx) x3 = 2*x2 - x1;
					if (Noeud[zj].symy) y3 = 2*y2 - y1;
					if (Noeud[zj].symz) z3 = 2*z2 - z1;

					na = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));	//a
					nb = sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)+(z3-z2)*(z3-z2));	//b
					nc = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3)+(z1-z3)*(z1-z3));	//c
										
					na2=na*na;
					nb2=nb*nb;
					
					PS = (z2-z1)*(z3-z2)+(y2-y1)*(y3-y2)+(x2-x1)*(x3-x2);
					symetrie = 1;
					voisin_trouve = 1;
					//printf("elem1 %d zi %d zj %d  \n",elem1,zi,zj);

				}
				else
				{	
					// Recherche d'element voisin
		  			for (elem2 = elem1+1; elem2 <= NOMBRE_ELEMENTS; elem2++)
					{
						if (Element[elem2].type == Element[elem1].type)
						{
							if (Element[elem2].extremite[1] == zj || Element[elem2].extremite[2] == zj)
							{
					  			if (Element[elem2].extremite[1] == zj) zk = Element[elem2].extremite[2];
								if (Element[elem2].extremite[2] == zj) zk = Element[elem2].extremite[1];
								x1 = wf[3*zi-2];	y1 = wf[3*zi-1];	z1 = wf[3*zi-0];
								x2 = wf[3*zj-2];	y2 = wf[3*zj-1];	z2 = wf[3*zj-0];
								x3 = wf[3*zk-2];	y3 = wf[3*zk-1];	z3 = wf[3*zk-0];

								na = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));	//a
								nb = sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)+(z3-z2)*(z3-z2));	//b
								nc = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3)+(z1-z3)*(z1-z3));	//c

								na2=na*na;	na3=na*na2;	na4=na*na3;
								nb2=nb*nb;	nb3=nb*nb2;	nb4=nb*nb3;
								nc2=nc*nc;	nc3=nc*nc2;	nc4=nc*nc3;
																
								PS = (z2-z1)*(z3-z2)+(y2-y1)*(y3-y2)+(x2-x1)*(x3-x2);		//vA . vB
								voisin_trouve = 1;
								break; // ce break sert à sortir du for ligne 100.
							}
						}
					}
				}
				//------------------------------------------------------------------------------------------------------------------------------------
				if (voisin_trouve)
				{
					EI = Element[elem1].EI_flexion;
					
					//Rayon*sin(alpha) = c/2 = nc/2
      
					Fx1 = 2*EI/na/nb/nc*((x2-x1)*PS/na2+x2-x3);	//Fx1 = term1*((x2-x1)*term2+x2-x3);
					Fy1 = 2*EI/na/nb/nc*((y2-y1)*PS/na2+y2-y3);	//Fy1 = term1*((y2-y1)*term2+y2-y3);
					Fz1 = 2*EI/na/nb/nc*((z2-z1)*PS/na2+z2-z3);	//Fz1 = term1*((z2-z1)*term2+z2-z3);
					Fx3 = 2*EI/na/nb/nc*((x2-x3)*PS/nb2+x2-x1);	//Fx3 = term1*((x2-x3)*term3+x2-x1);
					Fy3 = 2*EI/na/nb/nc*((y2-y3)*PS/nb2+y2-y1);	//Fy3 = term1*((y2-y3)*term3+y2-y1);
					Fz3 = 2*EI/na/nb/nc*((z2-z3)*PS/nb2+z2-z1);	//Fz3 = term1*((z2-z3)*term3+z2-z1);
					Fx2 = -Fx1-Fx3;
					Fy2 = -Fy1-Fy3;
					Fz2 = -Fz1-Fz3;
	      
		 			#ifdef DEBUG
					printf("elem= %4d, %4d  \n", elem1, elem2);
					printf("zi= %d; zj= %d; zk= %d;\n", zi, zj, zk);

					printf("na= %f; na2= %f nb= %f; nb2= %f nc= %f;  \n", na,na2,nb,nb2,nc);
					printf("na+nb-nc= %f; PS= %lf \n", na+nb-nc,PS);
					printf("x1= %f; y1= %f; z1= %f;\n", x1, y1, z1);
					printf("x2= %f; y2= %f; z2= %f;\n", x2, y2, z2);
					printf("x3= %f; y3= %f; z3= %f;\n", x3, y3, z3);
		
					printf("Fx1= %f, Fy1= %f, Fz1= %f\n", Fx1, Fy1, Fz1);
					printf("Fx2= %f, Fy2= %f, Fz2= %f\n", Fx2, Fy2, Fz2);
					printf("Fx3= %f, Fy3= %f, Fz3= %f\n", Fx3, Fy3, Fz3);
					
					if(isnan(Fx1))		{printf("Fx1 zi %d zj %d zk %d \n",zi,zj,zk);	exit(0);}
					if(isnan(Fy1))		{printf("Fy1 zi %d zj %d zk %d \n",zi,zj,zk);	exit(0);}
					if(isnan(Fz1))		{printf("Fz1 zi %d zj %d zk %d \n",zi,zj,zk);	exit(0);}
					if(isnan(Fx2))		{printf("Fx2 zi %d zj %d zk %d \n",zi,zj,zk);	exit(0);}
					if(isnan(Fy2))		{printf("Fy2 zi %d zj %d zk %d \n",zi,zj,zk);	exit(0);}
					if(isnan(Fz2))		{printf("Fz2 zi %d zj %d zk %d \n",zi,zj,zk);	exit(0);}

					#endif
					//-------------------------------------------------------------------------------------------------------------------------------------
					//  Les efforts sont mis dans le vecteur effort global

					if (symetrie)
					{
						// Compensation de l'effet en cas de symétrie (en divisant F2 par deux)
						// On divise par deux car ces efforts seront multipliés par deux dans le module symetrie2
						Fx2 = Fx2*0.5;
						Fy2 = Fy2*0.5;
						Fz2 = Fz2*0.5;

						waelem[3*zi-2] += Fx1;
						waelem[3*zi-1] += Fy1;
						waelem[3*zi-0] += Fz1;

						waelem[3*zj-2] += Fx2;
						waelem[3*zj-1] += Fy2;
						waelem[3*zj-0] += Fz2;
					}
					else
					{
						waelem[3*zi-2] += Fx1;
						waelem[3*zi-1] += Fy1;
						waelem[3*zi-0] += Fz1;

						waelem[3*zj-2] += Fx2;
						waelem[3*zj-1] += Fy2;
						waelem[3*zj-0] += Fz2;

						waelem[3*zk-2] += Fx3;
						waelem[3*zk-1] += Fy3;
						waelem[3*zk-0] += Fz3;
					}
					//-------------------------------------------------------derivees---------------------
					term1 = 2*EI/na/nb/nc;
					term2 = PS/na2;
					term3 = PS/nb2;
					//printf("term= %lf %lf %lf\n", term1,term2,term3);

					Dterm1_x1 =  (2*EI*(x3-x1))/(na*nb*nc3)+(2*EI*(x2-x1))/(na3*nb*nc);
					Dterm1_y1 =  (2*EI*(y3-y1))/(na*nb*nc3)+(2*EI*(y2-y1))/(na3*nb*nc);
					Dterm1_z1 =  (2*EI*(z3-z1))/(na*nb*nc3)+(2*EI*(z2-z1))/(na3*nb*nc);
					Dterm1_x2 =  (2*EI*(x3-x2))/(na*nb3*nc)-(2*EI*(x2-x1))/(na3*nb*nc);
					Dterm1_y2 =  (2*EI*(y3-y2))/(na*nb3*nc)-(2*EI*(y2-y1))/(na3*nb*nc);
					Dterm1_z2 =  (2*EI*(z3-z2))/(na*nb3*nc)-(2*EI*(z2-z1))/(na3*nb*nc);
					Dterm1_x3 = -(2*EI*(x3-x2))/(na*nb3*nc)-(2*EI*(x3-x1))/(na*nb*nc3);
					Dterm1_y3 = -(2*EI*(y3-y2))/(na*nb3*nc)-(2*EI*(y3-y1))/(na*nb*nc3);
					Dterm1_z3 = -(2*EI*(z3-z2))/(na*nb3*nc)-(2*EI*(z3-z1))/(na*nb*nc3);
					//printf("Dterm1= %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",Dterm1_x1,Dterm1_y1,Dterm1_z1,Dterm1_x2,Dterm1_y2,Dterm1_z2,Dterm1_x3,Dterm1_y3,Dterm1_z3);
						
					Dterm2_x1 = (x2-x3)/na2+(2*PS*(x2-x1))/na4;
					Dterm2_y1 = (y2-y3)/na2+(2*PS*(y2-y1))/na4;
					Dterm2_z1 = (z2-z3)/na2+(2*PS*(z2-z1))/na4;
					Dterm2_x2 = (x3-2*x2+x1)/na2-(2*PS*(x2-x1))/na4;
					Dterm2_y2 = (y3-2*y2+y1)/na2-(2*PS*(y2-y1))/na4;
					Dterm2_z2 = (z3-2*z2+z1)/na2-(2*PS*(z2-z1))/na4;
					Dterm2_x3 = (x2-x1)/na2;
					Dterm2_y3 = (y2-y1)/na2;
					Dterm2_z3 = (z2-z1)/na2;
					//printf("Dterm2= %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",Dterm2_x1,Dterm2_y1,Dterm2_z1,Dterm2_x2,Dterm2_y2,Dterm2_z2,Dterm2_x3,Dterm2_y3,Dterm2_z3);

					Dterm3_x1 = (x2-x3)/nb2;
					Dterm3_y1 = (y2-y3)/nb2;
					Dterm3_z1 = (z2-z3)/nb2;
					Dterm3_x2 = (2*PS*(x3-x2))/nb4+(x3-2*x2+x1)/nb2;
					Dterm3_y2 = (2*PS*(y3-y2))/nb4+(y3-2*y2+y1)/nb2;
					Dterm3_z2 = (2*PS*(z3-z2))/nb4+(z3-2*z2+z1)/nb2;
					Dterm3_x3 = (x2-x1)/nb2-(2*PS*(x3-x2))/nb4;
					Dterm3_y3 = (y2-y1)/nb2-(2*PS*(y3-y2))/nb4;
					Dterm3_z3 = (z2-z1)/nb2-(2*PS*(z3-z2))/nb4;
					//printf("Dterm3= %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",Dterm3_x1,Dterm3_y1,Dterm3_z1,Dterm3_x2,Dterm3_y2,Dterm3_z2,Dterm3_x3,Dterm3_y3,Dterm3_z3);

					//Fx1 = term1*((x2-x1)*term2+x2-x3);
					//Fx1' =   term1'   *((x2-x1)*term2+x2-x3) + term1*((x2-x1)'*term2 + (x2-x1)*term2'    +(x2-x3)');
					dFx1_x1 = Dterm1_x1*((x2-x1)*term2+x2-x3) + term1*(   -1   *term2 + (x2-x1)*Dterm2_x1          );
					dFx1_y1 = Dterm1_y1*((x2-x1)*term2+x2-x3) + term1*(                 (x2-x1)*Dterm2_y1          );
					dFx1_z1 = Dterm1_z1*((x2-x1)*term2+x2-x3) + term1*(                 (x2-x1)*Dterm2_z1          );
					dFx1_x2 = Dterm1_x2*((x2-x1)*term2+x2-x3) + term1*(  1     *term2 + (x2-x1)*Dterm2_x2 +  1     );
					dFx1_y2 = Dterm1_y2*((x2-x1)*term2+x2-x3) + term1*(                 (x2-x1)*Dterm2_y2          );
					dFx1_z2 = Dterm1_z2*((x2-x1)*term2+x2-x3) + term1*(                 (x2-x1)*Dterm2_z2          );
					dFx1_x3 = Dterm1_x3*((x2-x1)*term2+x2-x3) + term1*(                 (x2-x1)*Dterm2_x3     - 1  );
					dFx1_y3 = Dterm1_y3*((x2-x1)*term2+x2-x3) + term1*(                 (x2-x1)*Dterm2_y3          );
					dFx1_z3 = Dterm1_z3*((x2-x1)*term2+x2-x3) + term1*(                 (x2-x1)*Dterm2_z3          );
					//printf("dFx1= %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",dFx1_x1,dFx1_y1,dFx1_z1,dFx1_x2,dFx1_y2,dFx1_z2,dFx1_x3,dFx1_y3,dFx1_z3);

					//Fy1 = term1*((y2-y1)*term2+y2-y3);
					//Fy1' =   term1'   *((y2-y1)*term2+y2-y3) + term1*((y2-y1)'*term2 + (y2-y1)*term2'    +(y2-y3)');
					dFy1_x1 = Dterm1_x1*((y2-y1)*term2+y2-y3) + term1*(                 (y2-y1)*Dterm2_x1          );
					dFy1_y1 = Dterm1_y1*((y2-y1)*term2+y2-y3) + term1*(   -1   *term2 + (y2-y1)*Dterm2_y1          );
					dFy1_z1 = Dterm1_z1*((y2-y1)*term2+y2-y3) + term1*(                 (y2-y1)*Dterm2_z1          );
					dFy1_x2 = Dterm1_x2*((y2-y1)*term2+y2-y3) + term1*(                 (y2-y1)*Dterm2_x2          );
					dFy1_y2 = Dterm1_y2*((y2-y1)*term2+y2-y3) + term1*( 1      *term2 + (y2-y1)*Dterm2_y2 +  1     );
					dFy1_z2 = Dterm1_z2*((y2-y1)*term2+y2-y3) + term1*(                 (y2-y1)*Dterm2_z2          );
					dFy1_x3 = Dterm1_x3*((y2-y1)*term2+y2-y3) + term1*(                 (y2-y1)*Dterm2_x3          );
					dFy1_y3 = Dterm1_y3*((y2-y1)*term2+y2-y3) + term1*(                 (y2-y1)*Dterm2_y3     - 1  );
					dFy1_z3 = Dterm1_z3*((y2-y1)*term2+y2-y3) + term1*(                 (y2-y1)*Dterm2_z3          );

					//Fz1 = term1*((z2-z1)*term2+z2-z3);
					//Fz1' =   term1'   *((z2-z1)*term2+z2-z3) + term1*((z2-z1)'*term2 + (z2-z1)*term2'    +(z2-z3)');
					dFz1_x1 = Dterm1_x1*((z2-z1)*term2+z2-z3) + term1*(                 (z2-z1)*Dterm2_x1          );
					dFz1_y1 = Dterm1_y1*((z2-z1)*term2+z2-z3) + term1*(                 (z2-z1)*Dterm2_y1          );
					dFz1_z1 = Dterm1_z1*((z2-z1)*term2+z2-z3) + term1*(   -1   *term2 + (z2-z1)*Dterm2_z1          );
					dFz1_x2 = Dterm1_x2*((z2-z1)*term2+z2-z3) + term1*(                 (z2-z1)*Dterm2_x2          );
					dFz1_y2 = Dterm1_y2*((z2-z1)*term2+z2-z3) + term1*(                 (z2-z1)*Dterm2_y2          );
					dFz1_z2 = Dterm1_z2*((z2-z1)*term2+z2-z3) + term1*( 1      *term2 + (z2-z1)*Dterm2_z2 +  1     );
					dFz1_x3 = Dterm1_x3*((z2-z1)*term2+z2-z3) + term1*(                 (z2-z1)*Dterm2_x3          );
					dFz1_y3 = Dterm1_y3*((z2-z1)*term2+z2-z3) + term1*(                 (z2-z1)*Dterm2_y3          );
					dFz1_z3 = Dterm1_z3*((z2-z1)*term2+z2-z3) + term1*(                 (z2-z1)*Dterm2_z3     - 1  );

					//Fx3 = term1*((x2-x3)*term3+x2-x1);
					//Fx3' =   term1'   *((x2-x3)*term3+x2-x1) + term1*((x2-x3)'*term3 + (x2-x3)*term3'    +(x2-x1)');
					dFx3_x1 = Dterm1_x1*((x2-x3)*term3+x2-x1) + term1*(                 (x2-x3)*Dterm3_x1     - 1  );
					dFx3_y1 = Dterm1_y1*((x2-x3)*term3+x2-x1) + term1*(                 (x2-x3)*Dterm3_y1          );
					dFx3_z1 = Dterm1_z1*((x2-x3)*term3+x2-x1) + term1*(                 (x2-x3)*Dterm3_z1          );
					dFx3_x2 = Dterm1_x2*((x2-x3)*term3+x2-x1) + term1*( 1      *term3 + (x2-x3)*Dterm3_x2 +  1     );
					dFx3_y2 = Dterm1_y2*((x2-x3)*term3+x2-x1) + term1*(                 (x2-x3)*Dterm3_y2          );
					dFx3_z2 = Dterm1_z2*((x2-x3)*term3+x2-x1) + term1*(                 (x2-x3)*Dterm3_z2          );
					dFx3_x3 = Dterm1_x3*((x2-x3)*term3+x2-x1) + term1*(   -1   *term3 + (x2-x3)*Dterm3_x3          );
					dFx3_y3 = Dterm1_y3*((x2-x3)*term3+x2-x1) + term1*(                 (x2-x3)*Dterm3_y3          );
					dFx3_z3 = Dterm1_z3*((x2-x3)*term3+x2-x1) + term1*(                 (x2-x3)*Dterm3_z3          );

					//Fy3 = term1*((y2-y3)*term3+y2-y1);
					//Fy3' =   term1'   *((y2-y3)*term3+y2-y1) + term1*((y2-y3)'*term3 + (y2-y3)*term3'    +(y2-y1)');
					dFy3_x1 = Dterm1_x1*((y2-y3)*term3+y2-y1) + term1*(                 (y2-y3)*Dterm3_x1          );
					dFy3_y1 = Dterm1_y1*((y2-y3)*term3+y2-y1) + term1*(                 (y2-y3)*Dterm3_y1     - 1  );
					dFy3_z1 = Dterm1_z1*((y2-y3)*term3+y2-y1) + term1*(                 (y2-y3)*Dterm3_z1          );
					dFy3_x2 = Dterm1_x2*((y2-y3)*term3+y2-y1) + term1*(                 (y2-y3)*Dterm3_x2          );
					dFy3_y2 = Dterm1_y2*((y2-y3)*term3+y2-y1) + term1*( 1      *term3 + (y2-y3)*Dterm3_y2 +  1     );
					dFy3_z2 = Dterm1_z2*((y2-y3)*term3+y2-y1) + term1*(                 (y2-y3)*Dterm3_z2          );
					dFy3_x3 = Dterm1_x3*((y2-y3)*term3+y2-y1) + term1*(                 (y2-y3)*Dterm3_x3          );
					dFy3_y3 = Dterm1_y3*((y2-y3)*term3+y2-y1) + term1*(   -1   *term3 + (y2-y3)*Dterm3_y3          );
					dFy3_z3 = Dterm1_z3*((y2-y3)*term3+y2-y1) + term1*(                 (y2-y3)*Dterm3_z3          );

					//Fz3 = term1*((z2-z3)*term3+z2-z1);
					//Fz3' =   term1'   *((z2-z3)*term3+z2-z1) + term1*((z2-z3)'*term3 + (z2-z3)*term3'    +(z2-z1)');
					dFz3_x1 = Dterm1_x1*((z2-z3)*term3+z2-z1) + term1*(                 (z2-z3)*Dterm3_x1          );
					dFz3_y1 = Dterm1_y1*((z2-z3)*term3+z2-z1) + term1*(                 (z2-z3)*Dterm3_y1          );
					dFz3_z1 = Dterm1_z1*((z2-z3)*term3+z2-z1) + term1*(                 (z2-z3)*Dterm3_z1     - 1  );
					dFz3_x2 = Dterm1_x2*((z2-z3)*term3+z2-z1) + term1*(                 (z2-z3)*Dterm3_x2          );
					dFz3_y2 = Dterm1_y2*((z2-z3)*term3+z2-z1) + term1*(                 (z2-z3)*Dterm3_y2          );
					dFz3_z2 = Dterm1_z2*((z2-z3)*term3+z2-z1) + term1*( 1      *term3 + (z2-z3)*Dterm3_z2 + 1      );
					dFz3_x3 = Dterm1_x3*((z2-z3)*term3+z2-z1) + term1*(                 (z2-z3)*Dterm3_x3          );
					dFz3_y3 = Dterm1_y3*((z2-z3)*term3+z2-z1) + term1*(                 (z2-z3)*Dterm3_y3          );
					dFz3_z3 = Dterm1_z3*((z2-z3)*term3+z2-z1) + term1*(   -1   *term3 + (z2-z3)*Dterm3_z3          );

					K[1][1] = -dFx1_x1;	K[1][2] = -dFx1_y1;	K[1][3] = -dFx1_z1;	K[1][4] = -dFx1_x2;	K[1][5] = -dFx1_y2;	K[1][6] = -dFx1_z2;	K[1][7] = -dFx1_x3;	K[1][8] = -dFx1_y3;	K[1][9] = -dFx1_z3;
					K[2][1] = -dFy1_x1;	K[2][2] = -dFy1_y1;	K[2][3] = -dFy1_z1;	K[2][4] = -dFy1_x2;	K[2][5] = -dFy1_y2;	K[2][6] = -dFy1_z2;	K[2][7] = -dFy1_x3;	K[2][8] = -dFy1_y3;	K[2][9] = -dFy1_z3;
					K[3][1] = -dFz1_x1;	K[3][2] = -dFz1_y1;	K[3][3] = -dFz1_z1;	K[3][4] = -dFz1_x2;	K[3][5] = -dFz1_y2;	K[3][6] = -dFz1_z2;	K[3][7] = -dFz1_x3;	K[3][8] = -dFz1_y3;	K[3][9] = -dFz1_z3;
					K[4][1] = dFx1_x1+dFx3_x1;	K[4][2] = dFx1_y1+dFx3_y1;	K[4][3] = dFx1_z1+dFx3_z1;	K[4][4] = dFx1_x2+dFx3_x2;	K[4][5] = dFx1_y2+dFx3_y2;	K[4][6] = dFx1_z2+dFx3_z2;	K[4][7] = dFx1_x3+dFx3_x3;	K[4][8] = dFx1_y3+dFx3_y3;	K[4][9] = dFx1_z3+dFx3_z3;
					K[5][1] = dFy1_x1+dFy3_x1;	K[5][2] = dFy1_y1+dFy3_y1;	K[5][3] = dFy1_z1+dFy3_z1;	K[5][4] = dFy1_x2+dFy3_x2;	K[5][5] = dFy1_y2+dFy3_y2;	K[5][6] = dFy1_z2+dFy3_z2;	K[5][7] = dFy1_x3+dFy3_x3;	K[5][8] = dFy1_y3+dFy3_y3;	K[5][9] = dFy1_z3+dFy3_z3;
					K[6][1] = dFz1_x1+dFz3_x1;	K[6][2] = dFz1_y1+dFz3_y1;	K[6][3] = dFz1_z1+dFz3_z1;	K[6][4] = dFz1_x2+dFz3_x2;	K[6][5] = dFz1_y2+dFz3_y2;	K[6][6] = dFz1_z2+dFz3_z2;	K[6][7] = dFz1_x3+dFz3_x3;	K[6][8] = dFz1_y3+dFz3_y3;	K[6][9] = dFz1_z3+dFz3_z3;
					K[7][1] = -dFx3_x1;	K[7][2] = -dFx3_y1;	K[7][3] = -dFx3_z1;	K[7][4] = -dFx3_x2;	K[7][5] = -dFx3_y2;	K[7][6] = -dFx3_z2;	K[7][7] = -dFx3_x3;	K[7][8] = -dFx3_y3;	K[7][9] = -dFx3_z3;
					K[8][1] = -dFy3_x1;	K[8][2] = -dFy3_y1;	K[8][3] = -dFy3_z1;	K[8][4] = -dFy3_x2;	K[8][5] = -dFy3_y2;	K[8][6] = -dFy3_z2;	K[8][7] = -dFy3_x3;	K[8][8] = -dFy3_y3;	K[8][9] = -dFy3_z3;
					K[9][1] = -dFz3_x1;	K[9][2] = -dFz3_y1;	K[9][3] = -dFz3_z1;	K[9][4] = -dFz3_x2;	K[9][5] = -dFz3_y2;	K[9][6] = -dFz3_z2;	K[9][7] = -dFz3_x3;	K[9][8] = -dFz3_y3;	K[9][9] = -dFz3_z3;
		 			#ifdef DEBUG
					imprmatreel3( 1, 9, 1,  9,  K, 10);				
					#endif
					coor[1] = 3*zi-2;	coor[2] = 3*zi-1;	coor[3] = 3*zi-0;
					coor[4] = 3*zj-2;	coor[5] = 3*zj-1;	coor[6] = 3*zj-0;
					coor[7] = 3*zk-2;	coor[8] = 3*zk-1;	coor[9] = 3*zk-0;
					/* Mise a jour de la matrice de raideur globale*/
					/* K est la matrice de raideur.
					La matrice globale est rangee differemment. Ce n'est plus une matrice
					bande. La diagonale est devenu la colonne eca de ze*/
					for (zr = 1; zr<= 9; zr++)
					{
						for (zs = 1; zs<= 9; zs++) 
						{
							ze[coor[zr]][eca+coor[zs]-coor[zr]] += K[zr][zs];
						}
					}
					/* Calcul des bornes pour chaque ligne de la matrice de raideur globale
					rang[1][coor[zr]]borne basse de la raideur ze
					rang[2][coor[zr]]borne droite de la raideur ze
					rang[3][coor[zr]]borne haute de la raideur ze
					rang[4][coor[zr]]borne gauche de la raideur ze*/
					/*
					for (zr = 1; zr<= 9; zr++)
					{
						for (zs = 1; zs<= 9; zs++)
						{
							if (rang[1][coor[zr]] < coor[zs]) rang[1][coor[zr]] = coor[zs]; 
							if (rang[2][coor[zr]] < coor[zs]) rang[2][coor[zr]] = coor[zs]; 
							if (rang[3][coor[zr]] > coor[zs]) rang[3][coor[zr]] = coor[zs]; 
							if (rang[4][coor[zr]] > coor[zs]) rang[4][coor[zr]] = coor[zs]; 
						}
					}
					*/
				}
		  	}
		}
	}
	//exit(1);  // Décommenter si on veut arreter le calcul apres une iteration
}

