#define PRINCIPAL 0
#include "4c19.h"
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define PRINT 0
//#define DEBUG

//===================================================================================================================================//
// debut du programme

void pliage_barre_pardiso4()
{
	/*  pliage de 2 barres faisant un angle non nul au repos:
	efforts wae d un element barre qui se plie les efforts sont calcules
	pour tout les plis aux noeuds appartenant a un element barre ces noeuds
	n etant pas aux extremites de l element*/


	//------------------------------------------------------------------------------------------------------------------------------------
	// Donnees	
	int i, j, ii, jj, zu, typ1,typ2;
	int elem1,elem2,zi,zj,zk,zl,zm;

	int voisin_trouve=0;
	int typelem1 = 0;
	int typelem2 = 0;

	//double pi = (4.0 * atan(1.0));//3.14159265;
	//static const double E = 210000000000;    // module de Young


	//------------------------------------------------------------------------------------------------------------------------------------
	/*
	Nous allons chercher les elements qui sont voisins a l'aide des noeuds composants ceux-ci.
	le noeud zj est le noeud qui est situé au milieu des deux elements. 
	les noeuds zi et zk se situent de chaque cote de zj.
	*/
	/*for (elem1 = 1; elem1<= NOMBRE_ELEMENTS; elem1++)
	{
		typ1 = Element[elem1].type;
		printf ("nb link_flexion_elem2  %d elem1 %d\n", TypeElement[typ1].nb_link_flexion2,elem1);
		for (ii = 1; ii<= TypeElement[typ1].nb_link_flexion2; ii++)
		{
			printf ("bar %d cable bar %d bar link = %d at angle %lf\n", elem1, typ1, TypeElement[typ1].link_flexion2[ii], TypeElement[typ1].angle_link_flexion2[ii]);
		}
	
	}*/

	/*
	for (elem1 = 1; elem1<= NOMBRE_ELEMENTS-1; elem1++)
	{
		typ1 = Element[elem1].type;
		for (zl = 1; zl <=TypeElement[typ1].nb_link_flexion2 ; zl++)
		{
		printf("elem1 %d typ1 %d nb_link_flexion2  %d\n",elem1,typ1,TypeElement[typ1].nb_link_flexion2);
		printf("cable2 %d angle  %lf\n",TypeElement[typ1].link_flexion2[zl],TypeElement[typ1].angle_link_flexion2[zl]);
		}
	}
	*/
	//------------------------------------------------------------------------------------------------------------------------------------
	//						Recherche des éléments ciblés
	//------------------------------------------------------------------------------------------------------------------------------------

	int zii,zjj,zkk,znn,zn,typ22,bar1,bar2,typ11;

	//for (elem1 = 231; elem1<= 231; elem1++)
	for (elem1 = 1; elem1<= NOMBRE_ELEMENTS-1; elem1++)
	{
		typ1 = Element[elem1].type;
		if ((Element[elem1].EI_flexion > 0.0) && (TypeElement[typ1].nb_link_flexion2 >0))
		{
			for (zl = 1; zl<= 2; zl++)
			{
				if (zl == 1) zm = 2;
				if (zl == 2) zm = 1;
				zi = Element[elem1].extremite[zl];
				zj = Element[elem1].extremite[zm];
				zk = 0;
				voisin_trouve = 0;
				// Recherche d'element voisin
				//for (elem2 = elem1+1; elem2 <= 232; elem2++)
				for (elem2 = elem1+1; elem2 <= NOMBRE_ELEMENTS; elem2++)
				{
					typ2 = Element[elem2].type;
					if (Element[elem2].extremite[1] == zj || Element[elem2].extremite[2] == zj)
					{
			  			if (Element[elem2].extremite[1] == zj) zk = Element[elem2].extremite[2];
						if (Element[elem2].extremite[2] == zj) zk = Element[elem2].extremite[1];
					 	voisin_trouve = 1;
						for (zn = 1; zn<= TypeElement[typ1].nb_link_flexion2; zn++)
						{
							if (typ2 == TypeElement[typ1].link_flexion2[zn])
							{
								voisin_trouve = 1;
								bar1 = elem1;
								bar2 = elem2;
								zii = zi;
								zjj = zj;
								zkk = zk;
								znn = zn;
								typ11 = typ1;
								typ22 = typ2;
								//printf("elem1 %d typ1 %d nb_link_flexion2  %d liaison %d  ",elem1,typ1,TypeElement[typ1].nb_link_flexion2,zn);
								//printf("cable2 %d angle  %lf  ",TypeElement[typ1].link_flexion2[zn],TypeElement[typ1].angle_link_flexion2[zn]);
								//printf("typ2 %d \n",typ2);
								toto4( bar1,  bar2,  zii,  zjj,  zkk,  znn);
								//toto();
								//break; // ce break sert à sortir du for ligne 63.
							}
						}
						//if (voisin_trouve == 1) break; // ce break sert à sortir du for ligne 63.
					}
					//if (voisin_trouve == 1) break;
				}
				//if (voisin_trouve == 1) break;
			}
		}
	}
	/*
	printf("voisin_trouve %d \n",voisin_trouve);
	if (voisin_trouve == 1)

		{
		printf("bar1 %d typ11 %d nb_link_flexion2  %d liaison %d\n",bar1,typ11,TypeElement[typ11].nb_link_flexion2,znn);
		printf("cable2 %d angle  %lf  ",TypeElement[typ11].link_flexion2[znn],TypeElement[typ11].angle_link_flexion2[znn]);
		printf("bar2 %d typ22 %d \n",bar2,typ22);
		}

	*/
}	





void toto4(int bar1, int bar2, int zii, int zjj, int zkk, int znn)
{
	//------------------------------------------------------------------------------------------------------------------------------------
	//						Fonction principale
	//------------------------------------------------------------------------------------------------------------------------------------
	//bar1 : bar 1; bar2 : bar2; zii : noeud 1; zjj : noeud 2; zkk : noeud 3; znn : numero link_flexion2
	int type1,type2,nb_lien,error,trouve;
	double angle_repos;
	// Donnees	
	int i, j, ii, jj, zu, zw, typ1,typ2, zi,zj;
	int zl,zm;

	double x1,y1,z1,x2,y2,z2,x3,y3,z3,x3prime,y3prime,z3prime;
	double ac,alpha,A,B, hA,hB,hC, co,beta, ux, uy, uz ,module_U, module_U2, Ux, Uy, Uz,hx3prime,hy3prime,hz3prime;
	double D, EI, h, H, I, P, hPS, r, R, t1, T1,delta_x;
	
	double f1x, f2x, f3x, f1y, f2y, f3y, f1z, f2z, f3z;
	double hFx1, hFx2, hFx3, hFy1, hFy2, hFy3, hFz1, hFz2, hFz3, hFx3prime, hFy3prime, hFz3prime;
	double Rot11, Rot12,Rot13,Rot21,Rot22,Rot23,Rot31,Rot32,Rot33;
	double hRot11, hRot12,hRot13,hRot21,hRot22,hRot23,hRot31,hRot32,hRot33;
	double cos_beta,sin_beta,mod_F1,mod_F3prime;
	double U,hU,tata,test_U;

	double dx3prime[10];
	double dy3prime[10];
	double dz3prime[10];
	double dU[10];
	double dRot11[10],dRot12[10],dRot13[10],dRot21[10],dRot22[10],dRot23[10],dRot31[10],dRot32[10],dRot33[10];
	double dhRot11[10],dhRot12[10],dhRot13[10],dhRot21[10],dhRot22[10],dhRot23[10],dhRot31[10],dhRot32[10],dhRot33[10];
	double dC[10];
	double dhC[10];
	double dPS[10];
	double dA[10];
	double dB[10];
	double dhU[10];
	double dhPS[10];
	double dhA[10];
	double dhB[10];
	double dFx1[10], dFx2[10], dFx3[10], dFy1[10], dFy2[10], dFy3[10], dFz1[10], dFz2[10], dFz3[10], dFx3prime[10], dFy3prime[10], dFz3prime[10];
	double dhFx1[10], dhFx2[10], dhFx3[10], dhFy1[10], dhFy2[10], dhFy3[10], dhFz1[10], dhFz2[10], dhFz3[10], dhFx3prime[10], dhFy3prime[10], dhFz3prime[10];
	double dhx3prime[10] , dhy3prime[10] , dhz3prime[10];
	double K[10][10];

	int voisin_trouve=0;
	int typelem1 = 0;
	int typelem2 = 0;
	
	double VNx,VNy,VNz,VN,a,b,c,c1,c2,c3,a2,PS;
	double term1,term2_1x,term2_1y,term2_1z,term2_2x,term2_2y,term2_2z,term2_3x,term2_3y,term2_3z;
	double C;
	double Term1,Term2_1x,Term2_1y,Term2_1z,Term2_2x,Term2_2y,Term2_2z,Term2_3x,Term2_3y,Term2_3z;
	double Fx1, Fx2, Fx3, Fy1, Fy2, Fy3, Fz1, Fz2, Fz3, Fx3prime, Fy3prime, Fz3prime;
	double fx1, fx2, fx3, fy1, fy2, fy3, fz1, fz2, fz3;
	double xq3,yq3,zq3,Xq3,Yq3,Zq3;
	double Dxq3[10],dxq3[10];
	double Dyq3[10],dyq3[10];
	double Dzq3[10],dzq3[10];
	double Dterm1[10],dterm1[10];
	double Dterm2_1x[10],dterm2_1x[10];
	double Dterm2_1y[10],dterm2_1y[10];
	double Dterm2_1z[10],dterm2_1z[10];
	double Dterm2_2x[10],dterm2_2x[10];
	double Dterm2_2y[10],dterm2_2y[10];
	double Dterm2_2z[10],dterm2_2z[10];
	double Dterm2_3x[10],dterm2_3x[10];
	double Dterm2_3y[10],dterm2_3y[10];
	double Dterm2_3z[10],dterm2_3z[10];
	double Dterm3[10],dterm3[10];
	double term3;
	double Term3;
	double dx1[10];
	double dy1[10];
	double dz1[10];
	double Dc[10],dc[10];
	double DFx1[10];
	double DFy1[10];
	double DFz1[10];
	double DFx2[10];
	double DFy2[10];
	double DFz2[10];
	double DFx3[10];
	double DFy3[10];
	double DFz3[10];
	double sommex,sommey,sommez;
	double DFxsomme[10],DFysomme[10],DFzsomme[10],dFxsomme[10],dFysomme[10],dFzsomme[10];
	double fxsomme,Fxsomme,fysomme,Fysomme,fzsomme,Fzsomme;
	int p;
	
	double curvature_new,curvature_old,Perimeter;
	int curvature_nb;

	error = 0;

	type1 = Element[bar1].type;
	type2 = Element[bar2].type;

	
	/*D = Element[elem1].diametrehydro; // Diamètre
	I = PI*D*D*D*D/64.;   // Moment quadratique d'un cable de nylon de 1cm²
	EI = E*I; // N.m / Rad*/
	EI=(Element[bar1].EI_flexion+Element[bar2].EI_flexion)/2;//0.00004682
	if (Element[bar1].EI_flexion <= Element[bar2].EI_flexion)
		{
		EI=Element[bar1].EI_flexion;
		}
	else
		{
		EI=Element[bar2].EI_flexion;
		}

	beta=TypeElement[type1].angle_link_flexion2[znn]*PI/180;

	x1 = wf[3*zii-2];	y1 = wf[3*zii-1];	z1 = wf[3*zii-0];
	x2 = wf[3*zjj-2];	y2 = wf[3*zjj-1];	z2 = wf[3*zjj-0];
	x3 = wf[3*zkk-2];	y3 = wf[3*zkk-1];	z3 = wf[3*zkk-0];

	/*TEST_debut
	delta_x = 0.0000001;
	for( zu = 0 ; zu <= 10 ; zu++ )
		{
		if (zu == 1) x1 = x1 + delta_x;
		if (zu == 2) y1 = y1 + delta_x;
		if (zu == 3) z1 = z1 + delta_x;
		if (zu == 4) x2 = x2 + delta_x;
		if (zu == 5) y2 = y2 + delta_x;

		if (zu == 6) z2 = z2 + delta_x;
		if (zu == 7) x3 = x3 + delta_x;
		if (zu == 8) y3 = y3 + delta_x;
		if (zu == 9) z3 = z3 + delta_x;
		printf("zu %d  \n",zu);

	TEST_fin*/


	if (PRINT) printf("bar1 %d bar2 %d  \n",bar1,bar2);
	if (PRINT) printf("x1 %lf y1 %lf z1 %lf  ",x1,y1,z1);
	if (PRINT) printf("x2 %lf y2 %lf z2 %lf  ",x2,y2,z2);
	if (PRINT) printf("x3 %lf y3 %lf z3 %lf\n",x3,y3,z3);
	if (PRINT) printf("beta %lf EI %lf\n",beta,EI);

	//position de vecteur du VN
	VNx=(y2-y1)*(z3-z2)-(y3-y2)*(z2-z1);
	VNy=(x3-x2)*(z2-z1)-(x2-x1)*(z3-z2);
	VNz=(x2-x1)*(y3-y2)-(x3-x2)*(y2-y1);
	VN= sqrt(VNx*VNx+VNy*VNy+VNz*VNz);
	if (VN <= 0.0000001) 
		{
		if(fabs(z3-z2)<=fabs(x3-x2) && fabs(z3-z2)<=fabs(y3-y2)) 
			{
			VNx=(y3-y2);
			VNy=-(x3-x2);
			VNz=0;
			//printf("1 bars %4d %4d VNx %lf VNy %lf VNz %lf\n",bar1,bar2,VNx,VNy,VNz);	
			}
		if(fabs(y3-y2)<=fabs(x3-x2) && fabs(y3-y2)<=fabs(z3-z2)) 
			{
			VNx=(z3-z2);
			VNy=0;
			VNz=-(x3-x2);
			//printf("2 bars %4d %4d VNx %lf VNy %lf VNz %lf\n",bar1,bar2,VNx,VNy,VNz);	
			}
		if(fabs(x3-x2)<=fabs(z3-z2) && fabs(x3-x2)<=fabs(y3-y2)) 
			{
			VNx=0;
			VNy=(z3-z2);
			VNz=-(y3-y2);
			//printf("3 bars %4d %4d VNx %lf VNy %lf VNz %lf\n",bar1,bar2,VNx,VNy,VNz);	
			}
		VN= sqrt(VNx*VNx+VNy*VNy+VNz*VNz);
		}
	//longueur de a b c 
	a=sqrt((z2-z1)*(z2-z1)+(y2-y1)*(y2-y1)+(x2-x1)*(x2-x1));
	b=sqrt((z3-z2)*(z3-z2)+(y3-y2)*(y3-y2)+(x3-x2)*(x3-x2));
	c1=-sin(beta)*((VNy*(z3-z2))/VN-(VNz*(y3-y2))/VN)+cos(beta)*(x3-x2)+x2-x1;
	c2=-sin(beta)*((VNz*(x3-x2))/VN-(VNx*(z3-z2))/VN)+cos(beta)*(y3-y2)+y2-y1;
	c3=cos(beta)*(z3-z2)+z2-z1-sin(beta)*((VNx*(y3-y2))/VN-(VNy*(x3-x2))/VN);
	c=sqrt(c1*c1+c2*c2+c3*c3);
	if(isnan(c))	
		{
		printf("x1 %lf y1 %lf z1 %lf\n",x1,y1,z1);	
		printf("x2 %lf y2 %lf z2 %lf\n",x2,y2,z2);	
		printf("x3 %lf y3 %lf z3 %lf\n",x3,y3,z3);	
		printf("c1 %lf\n",c1);	
		printf("c2 %lf\n",c2);	
		printf("c3 %lf\n",c3);	
		printf("c %lf\n",c);	
		printf("VN %lf\n",VN);	
		printf("VNx %lf VNy %lf VNz %lf\n",VNx,VNy,VNz);	
		exit(0);
		}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	Perimeter = (a+b+c)/2.0;
	curvature_new = 4.0*sqrt(Perimeter*(Perimeter-a)*(Perimeter-b)*(Perimeter-c))/a/b/c;
	curvature_old = Noeud[zjj].curvature;
	curvature_nb = Noeud[zjj].curvature_nb;
	Noeud[zjj].curvature = (curvature_nb*curvature_old+curvature_new)/(curvature_nb+1);
	Noeud[zjj].curvature_nb = curvature_nb+1;
	//printf("zjj %5d ",zjj);
	//printf("nb %5d ",Noeud[zjj].curvature_nb);
	//printf("curvature %lf \n",Noeud[zjj].curvature);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	//printf("c1 %lf c2 %lf c3 %lf\n",c1,c2,c3);
	//printf("a %lf b %lf c %lf\n",a,b,c);

	//produit scalaire
	PS=(z2-z1)*(z3-z2)+(y2-y1)*(y3-y2)+(x2-x1)*(x3-x2);
	if (PRINT) printf("PS %lf\n",PS);
	//alpha
	ac = PS/(a*b);
	if (ac <= -1 ) ac = -1;
	if (ac >=  1 ) ac  = 1;
	alpha = acos(ac);	// si alpha est nul les barres sont alignées et si alpha égal Pi elle sont repliées l'une sur l'autre.

	//alpha=acos(PS/(a*b));
	if (alpha == 0.0) alpha = 0.001;
	if (PRINT) printf("alpha %lf\n",alpha);
	//term1
	term1=(2*EI)/(a*b);
	//printf("term1 %lf\n",term1);
	//term2
	term2_1x=(PS*(x2-x1))/(a*a)-x3+x2;
	term2_1y=(PS*(y2-y1))/(a*a)-y3+y2;
	term2_1z=(PS*(z2-z1))/(a*a)-z3+z2;
	term2_2x=(PS*(x1-x2))/(a*a)+(PS*(x3-x2))/(b*b)+x3-2*x2+x1;
	term2_2y=(PS*(y1-y2))/(a*a)+(PS*(y3-y2))/(b*b)+y3-2*y2+y1;
	term2_2z=(PS*(z1-z2))/(a*a)+(PS*(z3-z2))/(b*b)+z3-2*z2+z1;
	term2_3x=(PS*(x2-x3))/(b*b)+x2-x1;
	term2_3y=(PS*(y2-y3))/(b*b)+y2-y1;
	term2_3z=(PS*(z2-z3))/(b*b)+z2-z1;
	//term3
	term3=sin(alpha-beta)/sin(alpha);

	//printf("term2_1x %lf term2_1y %lf term2_1z %lf\n",term2_1x,term2_1y,term2_1z);
	//printf("term2_2x %lf term2_2y %lf term2_2z %lf\n",term2_2x,term2_2y,term2_2z);
	//printf("term2_3x %lf term2_3y %lf term2_3z %lf\n",term2_3x,term2_3y,term2_3z);
	//les forces de F1 F2 F3
	
	//Fx1=((2*EI)/c)* (((x2-x1)*PS)/(a*a*a*b)+(x2-x3)/(a*b));
	Fx1=2*EI/c*	(((x2-x1)*PS/a/a/a/b+(x2-x3)/a/b)*sin(alpha-beta))/sin(alpha);
	Fy1=2*EI/c*	(((y2-y1)*PS/a/a/a/b+(y2-y3)/a/b)*sin(alpha-beta))/sin(alpha);
	Fz1=2*EI/c*	(((z2-z1)*PS/a/a/a/b+(z2-z3)/a/b)*sin(alpha-beta))/sin(alpha);
	Fx2=2*EI/c*	(((x1-x2)*PS/a/a/a/b+(x3-x2)*PS/a/b/b/b+	(x3-2*x2+x1)/a/b)*sin(alpha-beta))/sin(alpha);
	Fy2=2*EI/c*	(((y1-y2)*PS/a/a/a/b+(y3-y2)*PS/a/b/b/b+	(y3-2*y2+y1)/a/b)*sin(alpha-beta))/sin(alpha);
	Fz2=2*EI/c*	(((z1-z2)*PS/a/a/a/b+(z3-z2)*PS/a/b/b/b+	(z3-2*z2+z1)/a/b)*sin(alpha-beta))/sin(alpha);
	Fx3=2*EI/c*	(((x2-x3)*PS/a/b/b/b+(x2-x1)/a/b)*sin(alpha-beta))/sin(alpha);
	Fy3=2*EI/c*	(((y2-y3)*PS/a/b/b/b+(y2-y1)/a/b)*sin(alpha-beta))/sin(alpha);
	Fz3=2*EI/c*	(((z2-z3)*PS/a/b/b/b+(z2-z1)/a/b)*sin(alpha-beta))/sin(alpha);
	if (PRINT) printf(" Fx1 %lf Fy1 %lf Fz1 %lf\n",Fx1,Fy1,Fz1);
	if (PRINT) printf(" Fx2 %lf Fy2 %lf Fz2 %lf\n",Fx2,Fy2,Fz2);
	if (PRINT) printf(" Fx3 %lf Fy3 %lf Fz3 %lf\n",Fx3,Fy3,Fz3);
	
	//q3 point p3 apres rotation de -alpha
	xq3=-sin(beta)*((VNy*(z3-z2))/VN-(VNz*(y3-y2))/VN)+cos(beta)*(x3-x2)+x2;
	yq3=-sin(beta)*((VNz*(x3-x2))/VN-(VNx*(z3-z2))/VN)+cos(beta)*(y3-y2)+y2;
	zq3=-sin(beta)*((VNx*(y3-y2))/VN-(VNy*(x3-x2))/VN)+cos(beta)*(z3-z2)+z2;
	
	//derivee de xq3 (9)
	
	Dxq3[1]=-sin(beta)*((z3-z2)*(z3-z2)/VN-((y2-y3)*(y3-y2))/VN-(VNy*(z3-z2)*(2*VNy*(z3-z2)+2*VNz*(y2-y3)))/(2*VN*VN*VN)+(VNz*(y3-y2)*(2*VNy*(z3-z2)+2*VNz*(y2-y3)))/(2*VN*VN*VN));
	Dxq3[2]=-sin(beta)*(-((x3-x2)*(y3-y2))/VN-(VNy*(2*VNx*(z2-z3)+2*VNz*(x3-x2))*(z3-z2))/(2*VN*VN*VN)+(VNz*(y3-y2)*(2*VNx*(z2-z3)+2*VNz*(x3-x2)))/(2*VN*VN*VN));
	Dxq3[3]=-sin(beta)*(((x2-x3)*(z3-z2))/VN-(VNy*(2*VNx*(y3-y2)+2*VNy*(x2-x3))*(z3-z2))/(2*VN*VN*VN)+(VNz*(y3-y2)*(2*VNx*(y3-y2)+2*VNy*(x2-x3)))/(2*VN*VN));
	Dxq3[4]=-sin(beta)*(((z1-z3)*(z3-z2))/VN-((y3-y1)*(y3-y2))/VN-(VNy*(2*VNy*(z1-z3)+2*VNz*(y3-y1))*(z3-z2))/(2*VN*VN*VN)+(VNz*(y3-y2)*(2*VNy*(z1-z3)+2*VNz*(y3-y1)))/(2*VN*VN*VN))-cos(beta)+1;
	Dxq3[5]=-sin(beta)*(-((x1-x3)*(y3-y2))/VN+VNz/VN-(VNy*(z3-z2)*(2*VNx*(z3-z1)+2*VNz*(x1-x3)))/(2*VN*VN*VN)+(VNz*(y3-y2)*(2*VNx*(z3-z1)+2*VNz*(x1-x3)))/(2*VN*VN*VN));
	Dxq3[6]=-sin(beta)*(((x3-x1)*(z3-z2))/VN-VNy/VN-(VNy*(2*VNx*(y1-y3)+2*VNy*(x3-x1))*(z3-z2))/(2*VN*VN*VN)+(VNz*(2*VNx*(y1-y3)+2*VNy*(x3-x1))*(y3-y2))/(2*VN*VN*VN));
	Dxq3[7]=cos(beta)-sin(beta)*(((z2-z1)*(z3-z2))/VN-((y1-y2)*(y3-y2))/VN-(VNy*(2*VNy*(z2-z1)+2*VNz*(y1-y2))*(z3-z2))/(2*VN*VN*VN)+(VNz*(y3-y2)*(2*VNy*(z2-z1)+2*VNz*(y1-y2)))/(2*VN*VN*VN));
	Dxq3[8]=-sin(beta)*(-((x2-x1)*(y3-y2))/VN-VNz/VN-(VNy*(2*VNx*(z1-z2)+2*VNz*(x2-x1))*(z3-z2))/(2*VN*VN*VN)+(VNz*(y3-y2)*(2*VNx*(z1-z2)+2*VNz*(x2-x1)))/(2*VN*VN*VN));
	Dxq3[9]=-sin(beta)*(((x1-x2)*(z3-z2))/VN+VNy/VN-(VNy*(2*VNx*(y2-y1)+2*VNy*(x1-x2))*(z3-z2))/(2*VN*VN*VN)+(VNz*(2*VNx*(y2-y1)+2*VNy*(x1-x2))*(y3-y2))/(2*VN*VN*VN));
	//printf(" Dxq3[1] %8.0lf Dxq3[2] %8.0lf Dxq3[3] %8.0lf\n",Dxq3[1],Dxq3[2],Dxq3[3]);
	//printf(" Dxq3[4] %8.0lf Dxq3[5] %8.0lf Dxq3[6] %8.0lf\n",Dxq3[4],Dxq3[5],Dxq3[6]);
	//printf(" Dxq3[7] %8.0lf Dxq3[8] %8.0lf Dxq3[9] %8.0lf\n",Dxq3[7],Dxq3[8],Dxq3[9]);
	
	//derivee de yq3  (9)
	
	Dyq3[1]=-sin(beta)*(((x3-x2)*(y2-y3))/VN+(VNx*(z3-z2)*(2*VNy*(z3-z2)+2*VNz*(y2-y3)))/(2*VN*VN*VN)-(VNz*(x3-x2)*(2*VNy*(z3-z2)+2*VNz*(y2-y3)))/(2*VN*VN*VN));
	Dyq3[2]=-sin(beta)*(-((z2-z3)*(z3-z2))/VN+(x3-x2)*(x3-x2)/VN+(VNx*(2*VNx*(z2-z3)+2*VNz*(x3-x2))*(z3-z2))/(2*VN*VN*VN)-(VNz*(x3-x2)*(2*VNx*(z2-z3)+2*VNz*(x3-x2)))/(2*VN*VN*VN));
	Dyq3[3]=-sin(beta)*(-((y3-y2)*(z3-z2))/VN+(VNx*(2*VNx*(y3-y2)+2*VNy*(x2-x3))*(z3-z2))/(2*VN*VN*VN)-(VNz*(x3-x2)*(2*VNx*(y3-y2)+2*VNy*(x2-x3)))/(2*VN*VN*VN));
	Dyq3[4]=-sin(beta)*(((x3-x2)*(y3-y1))/VN-VNz/VN+(VNx*(2*VNy*(z1-z3)+2*VNz*(y3-y1))*(z3-z2))/(2*VN*VN*VN)-(VNz*(x3-x2)*(2*VNy*(z1-z3)+2*VNz*(y3-y1)))/(2*VN*VN*VN));
	Dyq3[5]=-sin(beta)*(-((z3-z1)*(z3-z2))/VN+((x1-x3)*(x3-x2))/VN+(VNx*(z3-z2)*(2*VNx*(z3-z1)+2*VNz*(x1-x3)))/(2*VN*VN*VN)-(VNz*(x3-x2)*(2*VNx*(z3-z1)+2*VNz*(x1-x3)))/(2*VN*VN*VN))-cos(beta)+1;
	Dyq3[6]=-sin(beta)*(-((y1-y3)*(z3-z2))/VN+VNx/VN+(VNx*(2*VNx*(y1-y3)+2*VNy*(x3-x1))*(z3-z2))/(2*VN*VN*VN)-(VNz*(x3-x2)*(2*VNx*(y1-y3)+2*VNy*(x3-x1)))/(2*VN*VN*VN));
	Dyq3[7]=-sin(beta)*(((x3-x2)*(y1-y2))/VN+VNz/VN+(VNx*(2*VNy*(z2-z1)+2*VNz*(y1-y2))*(z3-z2))/(2*VN*VN*VN)-(VNz*(x3-x2)*(2*VNy*(z2-z1)+2*VNz*(y1-y2)))/(2*VN*VN*VN));
	Dyq3[8]=cos(beta)-sin(beta)*(-((z1-z2)*(z3-z2))/VN+((x2-x1)*(x3-x2))/VN+(VNx*(2*VNx*(z1-z2)+2*VNz*(x2-x1))*(z3-z2))/(2*VN*VN*VN)-(VNz*(x3-x2)*(2*VNx*(z1-z2)+2*VNz*(x2-x1)))/(2*VN*VN*VN));
	Dyq3[9]=-sin(beta)*(-((y2-y1)*(z3-z2))/VN-VNx/VN+(VNx*(2*VNx*(y2-y1)+2*VNy*(x1-x2))*(z3-z2))/(2*VN*VN*VN)-(VNz*(x3-x2)*(2*VNx*(y2-y1)+2*VNy*(x1-x2)))/(2*VN*VN*VN));
	//printf(" Dyq3[1] %8.0lf Dyq3[2] %8.0lf Dyq3[3] %8.0lf\n",Dyq3[1],Dyq3[2],Dyq3[3]);
	//printf(" Dyq3[4] %8.0lf Dyq3[5] %8.0lf Dyq3[6] %8.0lf\n",Dyq3[4],Dyq3[5],Dyq3[6]);
	//printf(" Dyq3[7] %8.0lf Dyq3[8] %8.0lf Dyq3[9] %8.0lf\n",Dyq3[7],Dyq3[8],Dyq3[9]);
	//derivee de zq3  (9)
	
	Dzq3[1]=-sin(beta)*(-((x3-x2)*(z3-z2))/VN-(VNx*(y3-y2)*(2*VNy*(z3-z2)+2*VNz*(y2-y3)))/(2*VN*VN*VN)+(VNy*(x3-x2)*(2*VNy*(z3-z2)+2*VNz*(y2-y3)))/(2*VN*VN*VN));
	Dzq3[2]=-sin(beta)*(((y3-y2)*(z2-z3))/VN-(VNx*(y3-y2)*(2*VNx*(z2-z3)+2*VNz*(x3-x2)))/(2*VN*VN*VN)+(VNy*(x3-x2)*(2*VNx*(z2-z3)+2*VNz*(x3-x2)))/(2*VN*VN*VN));
	Dzq3[3]=-sin(beta)*((y3-y2)*(y3-y2)/VN-((x2-x3)*(x3-x2))/VN-(VNx*(y3-y2)*(2*VNx*(y3-y2)+2*VNy*(x2-x3)))/(2*VN*VN*VN)+(VNy*(x3-x2)*(2*VNx*(y3-y2)+2*VNy*(x2-x3)))/(2*VN*VN*VN));
	Dzq3[4]=-sin(beta)*(-((x3-x2)*(z1-z3))/VN+VNy/VN-(VNx*(y3-y2)*(2*VNy*(z1-z3)+2*VNz*(y3-y1)))/(2*VN*VN*VN)+(VNy*(x3-x2)*(2*VNy*(z1-z3)+2*VNz*(y3-y1)))/(2*VN*VN*VN));
	Dzq3[5]=-sin(beta)*(((y3-y2)*(z3-z1))/VN-VNx/VN-(VNx*(y3-y2)*(2*VNx*(z3-z1)+2*VNz*(x1-x3)))/(2*VN*VN*VN)+(VNy*(x3-x2)*(2*VNx*(z3-z1)+2*VNz*(x1-x3)))/(2*VN*VN*VN));
	Dzq3[6]=-sin(beta)*(((y1-y3)*(y3-y2))/VN-((x3-x1)*(x3-x2))/VN-(VNx*(2*VNx*(y1-y3)+2*VNy*(x3-x1))*(y3-y2))/(2*VN*VN*VN)+(VNy*(x3-x2)*(2*VNx*(y1-y3)+2*VNy*(x3-x1)))/(2*VN*VN*VN))-cos(beta)+1;
	Dzq3[7]=-sin(beta)*(-((x3-x2)*(z2-z1))/VN-VNy/VN-(VNx*(y3-y2)*(2*VNy*(z2-z1)+2*VNz*(y1-y2)))/(2*VN*VN*VN)+(VNy*(x3-x2)*(2*VNy*(z2-z1)+2*VNz*(y1-y2)))/(2*VN*VN*VN));
	Dzq3[8]=-sin(beta)*(((y3-y2)*(z1-z2))/VN+VNx/VN-(VNx*(y3-y2)*(2*VNx*(z1-z2)+2*VNz*(x2-x1)))/(2*VN*VN*VN)+(VNy*(x3-x2)*(2*VNx*(z1-z2)+2*VNz*(x2-x1)))/(2*VN*VN*VN));
	Dzq3[9]=cos(beta)-sin(beta)*(((y2-y1)*(y3-y2))/VN-((x1-x2)*(x3-x2))/VN-(VNx*(2*VNx*(y2-y1)+2*VNy*(x1-x2))*(y3-y2))/(2*VN*VN*VN)+(VNy*(x3-x2)*(2*VNx*(y2-y1)+2*VNy*(x1-x2)))/(2*VN*VN*VN));
	//printf(" Dzq3[1] %8.0lf Dzq3[2] %8.0lf Dzq3[3] %8.0lf\n",Dzq3[1],Dzq3[2],Dzq3[3]);
	//printf(" Dzq3[4] %8.0lf Dzq3[5] %8.0lf Dzq3[6] %8.0lf\n",Dzq3[4],Dzq3[5],Dzq3[6]);
	//printf(" Dzq3[7] %8.0lf Dzq3[8] %8.0lf Dzq3[9] %8.0lf\n",Dzq3[7],Dzq3[8],Dzq3[9]);
	
	//derivee de term1  (9)
	
	Dterm1[1]=(2*(x2-x1)*EI)/(a*a*a*b);
	Dterm1[4]=(2*(x3-x2)*EI)/(a*b*b*b)-(2*(x2-x1)*EI)/(a*a*a*b);
	Dterm1[7]=-(2*(x3-x2)*EI)/(a*b*b*b);
	Dterm1[2]=(2*(y2-y1)*EI)/(a*a*a*b);
	Dterm1[5]=(2*(y3-y2)*EI)/(a*b*b*b)-(2*(y2-y1)*EI)/(a*a*a*b);
	Dterm1[8]=-(2*(y3-y2)*EI)/(a*b*b*b);
	Dterm1[3]=(2*(z2-z1)*EI)/(a*a*a*b);
	Dterm1[6]=(2*(z3-z2)*EI)/(a*b*b*b)-(2*(z2-z1)*EI)/(a*a*a*b);
	Dterm1[9]=-(2*(z3-z2)*EI)/(a*b*b*b);
	
	//printf(" Dterm1[1] %8.0lf Dterm1[2] %8.0lf Dterm1[3] %8.0lf\n",Dterm1[1],Dterm1[2],Dterm1[3]);
	//printf(" Dterm1[4] %8.0lf Dterm1[5] %8.0lf Dterm1[6] %8.0lf\n",Dterm1[4],Dterm1[5],Dterm1[6]);
	//printf(" Dterm1[7] %8.0lf Dterm1[8] %8.0lf Dterm1[9] %8.0lf\n",Dterm1[7],Dterm1[8],Dterm1[9]);
	
	//derivee de term2   (81)
	Dterm2_1x[1]=((x2-x1)*(x2-x3))/(a*a)-PS/(a*a)+(2*PS*(x2-x1)*(x2-x1))/(a*a*a*a);
	Dterm2_1x[4]=(PS)/(a*a)-(2*(x2-x1)*(x2-x1)*PS)/(a*a*a*a)+((x2-x1)*(x3-2*x2+x1))/(a*a)+1;
	Dterm2_1x[7]=(x2-x1)*(x2-x1)/(a*a)-1;
	Dterm2_1x[2]=(2*(x2-x1)*(y2-y1)*PS)/(a*a*a*a)+((x2-x1)*(y2-y3))/(a*a);
	Dterm2_1x[5]=((x2-x1)*(y3-2*y2+y1))/(a*a)-(2*(x2-x1)*(y2-y1)*PS)/(a*a*a*a);
	Dterm2_1x[8]=((x2-x1)*(y2-y1))/(a*a);
	Dterm2_1x[3]=(2*(x2-x1)*(z2-z1)*PS)/(a*a*a*a)+((x2-x1)*(z2-z3))/(a*a);
	Dterm2_1x[6]=((x2-x1)*(z3-2*z2+z1))/(a*a)-(2*(x2-x1)*(z2-z1)*PS)/(a*a*a*a);
	Dterm2_1x[9]=((x2-x1)*(z2-z1))/(a*a);
	//printf(" Dterm2_1x[1] %8.0lf Dterm2_1x[2] %8.0lf Dterm2_1x[3] %8.0lf",Dterm2_1x[1],Dterm2_1x[2],Dterm2_1x[3]);
	//printf(" Dterm2_1x[4] %8.0lf Dterm2_1x[5] %8.0lf Dterm2_1x[6] %8.0lf",Dterm2_1x[4],Dterm2_1x[5],Dterm2_1x[6]);
	//printf(" Dterm2_1x[7] %8.0lf Dterm2_1x[8] %8.0lf Dterm2_1x[9] %8.0lf\n",Dterm2_1x[7],Dterm2_1x[8],Dterm2_1x[9]);
	
	Dterm2_1y[1]=(2*(x2-x1)*(y2-y1)*PS)/(a*a*a*a)+((x2-x3)*(y2-y1))/(a*a);
	Dterm2_1y[4]=((x3-2*x2+x1)*(y2-y1))/(a*a)-(2*(x2-x1)*(y2-y1)*PS)/(a*a*a*a);
	Dterm2_1y[7]=((x2-x1)*(y2-y1))/(a*a);
	Dterm2_1y[2]=-(PS)/(a*a)+(2*(y2-y1)*(y2-y1)*PS)/(a*a*a*a)+((y2-y1)*(y2-y3))/(a*a);
	Dterm2_1y[5]=(PS)/(a*a)-(2*(y2-y1)*(y2-y1)*PS)/(a*a*a*a)+((y2-y1)*(y3-2*y2+y1))/(a*a)+1;
	Dterm2_1y[8]=(y2-y1)*(y2-y1)/(a*a)-1;
	Dterm2_1y[3]=(2*(y2-y1)*(z2-z1)*PS)/(a*a*a*a)+((y2-y1)*(z2-z3))/(a*a);
	Dterm2_1y[6]=((y2-y1)*(z3-2*z2+z1))/(a*a)-(2*(y2-y1)*(z2-z1)*PS)/(a*a*a*a);
	Dterm2_1y[9]=((y2-y1)*(z2-z1))/(a*a);
	//printf(" Dterm2_1y[1] %8.0lf Dterm2_1y[2] %8.0lf Dterm2_1y[3] %8.0lf",Dterm2_1y[1],Dterm2_1y[2],Dterm2_1y[3]);
	//printf(" Dterm2_1y[4] %8.0lf Dterm2_1y[5] %8.0lf Dterm2_1y[6] %8.0lf",Dterm2_1y[4],Dterm2_1y[5],Dterm2_1y[6]);
	//printf(" Dterm2_1y[7] %8.0lf Dterm2_1y[8] %8.0lf Dterm2_1y[9] %8.0lf\n",Dterm2_1y[7],Dterm2_1y[8],Dterm2_1y[9]);
	
	Dterm2_1z[1]=(2*(x2-x1)*(z2-z1)*PS)/(a*a*a*a)+((x2-x3)*(z2-z1))/(a*a);
	Dterm2_1z[4]=((x3-2*x2+x1)*(z2-z1))/(a*a)-(2*(x2-x1)*(z2-z1)*PS)/(a*a*a*a);
	Dterm2_1z[7]=((x2-x1)*(z2-z1))/(a*a);
	Dterm2_1z[2]=(2*(y2-y1)*(z2-z1)*PS)/(a*a*a*a)+((y2-y3)*(z2-z1))/(a*a);
	Dterm2_1z[5]=((y3-2*y2+y1)*(z2-z1))/(a*a)-(2*(y2-y1)*(z2-z1)*PS)/(a*a*a*a);
	Dterm2_1z[8]=((y2-y1)*(z2-z1))/(a*a);
	Dterm2_1z[3]=-(PS)/(a*a)+(2*(z2-z1)*(z2-z1)*PS)/(a*a*a*a)+((z2-z1)*(z2-z3))/(a*a);
	Dterm2_1z[6]=(PS)/(a*a)-(2*(z2-z1)*(z2-z1)*PS)/(a*a*a*a)+((z2-z1)*(z3-2*z2+z1))/(a*a)+1;
	Dterm2_1z[9]=(z2-z1)*(z2-z1)/(a*a)-1;
	//printf(" Dterm2_1z[1] %8.0lf Dterm2_1z[2] %8.0lf Dterm2_1z[3] %8.0lf",Dterm2_1z[1],Dterm2_1z[2],Dterm2_1z[3]);
	//printf(" Dterm2_1z[4] %8.0lf Dterm2_1z[5] %8.0lf Dterm2_1z[6] %8.0lf",Dterm2_1z[4],Dterm2_1z[5],Dterm2_1z[6]);
	//printf(" Dterm2_1z[7] %8.0lf Dterm2_1z[8] %8.0lf Dterm2_1z[9] %8.0lf\n",Dterm2_1z[7],Dterm2_1z[8],Dterm2_1z[9]);
	
	Dterm2_2x[1]=(PS)/(a*a)+(2*(x1-x2)*(x2-x1)*PS)/(a*a*a*a)+((x2-x3)*(x3-x2))/(b*b)+((x1-x2)*(x2-x3))/(a*a)+1;
	Dterm2_2x[4]=-(PS)/(b*b)+(2*(x3-x2)*(x3-x2)*PS)/(b*b*b*b)-(PS)/(a*a)-(2*(x1-x2)*(x2-x1)*PS)/(a*a*a*a)+((x3-2*x2+x1)*(x3-x2))/(b*b)+((x1-x2)*(x3-2*x2+x1))/(a*a)-2;
	Dterm2_2x[7]=(PS)/(b*b)-(2*(x3-x2)*(x3-x2)*PS)/(b*b*b*b)+((x2-x1)*(x3-x2))/(b*b)+(x1-x2)*(x2-x1)/(a*a)+1;
	Dterm2_2x[2]=(2*(x1-x2)*(y2-y1)*PS)/(a*a*a*a)+((x3-x2)*(y2-y3))/(b*b)+((x1-x2)*(y2-y3))/(a*a);
	Dterm2_2x[5]=(2*(x3-x2)*(y3-y2)*PS)/(b*b*b*b)-(2*(x1-x2)*(y2-y1)*PS)/(a*a*a*a)+((x3-x2)*(y3-2*y2+y1))/(b*b)+((x1-x2)*(y3-2*y2+y1))/(a*a);
	Dterm2_2x[8]=-(2*(x3-x2)*(y3-y2)*PS)/(b*b*b*b)+((x3-x2)*(y2-y1))/(b*b)+((x1-x2)*(y2-y1))/(a*a);
	Dterm2_2x[3]=(2*(x1-x2)*(z2-z1)*PS)/(a*a*a*a)+((x3-x2)*(z2-z3))/(b*b)+((x1-x2)*(z2-z3))/(a*a);
	Dterm2_2x[6]=(2*(x3-x2)*(z3-z2)*PS)/(b*b*b*b)-(2*(x1-x2)*(z2-z1)*PS)/(a*a*a*a)+((x3-x2)*(z3-2*z2+z1))/(b*b)+((x1-x2)*(z3-2*z2+z1))/(a*a);
	Dterm2_2x[9]=-(2*(x3-x2)*(z3-z2)*PS)/(b*b*b*b)+((x3-x2)*(z2-z1))/(b*b)+((x1-x2)*(z2-z1))/(a*a);
	//printf(" Dterm2_2x[1] %8.0lf Dterm2_2x[2] %8.0lf Dterm2_2x[3] %8.0lf",Dterm2_2x[1],Dterm2_2x[2],Dterm2_2x[3]);
	//printf(" Dterm2_2x[4] %8.0lf Dterm2_2x[5] %8.0lf Dterm2_2x[6] %8.0lf",Dterm2_2x[4],Dterm2_2x[5],Dterm2_2x[6]);
	//printf(" Dterm2_2x[7] %8.0lf Dterm2_2x[8] %8.0lf Dterm2_2x[9] %8.0lf\n",Dterm2_2x[7],Dterm2_2x[8],Dterm2_2x[9]);
	
	Dterm2_2y[1]=(2*(x2-x1)*(y1-y2)*PS)/(a*a*a*a)+((x2-x3)*(y3-y2))/(b*b)+((x2-x3)*(y1-y2))/(a*a);
	Dterm2_2y[4]=(2*(x3-x2)*(y3-y2)*PS)/(b*b*b*b)-(2*(x2-x1)*(y1-y2)*PS)/(a*a*a*a)+((x3-2*x2+x1)*(y3-y2))/(b*b)+((x3-2*x2+x1)*(y1-y2))/(a*a);
	Dterm2_2y[7]=-(2*(x3-x2)*(y3-y2)*PS)/(b*b*b*b)+((x2-x1)*(y3-y2))/(b*b)+((x2-x1)*(y1-y2))/(a*a);
	Dterm2_2y[2]=(PS)/(a*a)+(2*(y1-y2)*(y2-y1)*PS)/(a*a*a*a)+((y2-y3)*(y3-y2))/(b*b)+((y1-y2)*(y2-y3))/(a*a)+1;
	Dterm2_2y[5]=-(PS)/(b*b)+(2*(y3-y2)*(y3-y2)*PS)/(b*b*b*b)-(PS)/(a*a)-(2*(y1-y2)*(y2-y1)*PS)/(a*a*a*a)+((y3-2*y2+y1)*(y3-y2))/(b*b)+((y1-y2)*(y3-2*y2+y1))/(a*a)-2;
	Dterm2_2y[8]=(PS)/(b*b)-(2*(y3-y2)*(y3-y2)*PS)/(b*b*b*b)+((y2-y1)*(y3-y2))/(b*b)+(y1-y2)*(y2-y1)/(a*a)+1;
	Dterm2_2y[3]=(2*(y1-y2)*(z2-z1)*PS)/(a*a*a*a)+((y3-y2)*(z2-z3))/(b*b)+((y1-y2)*(z2-z3))/(a*a);
	Dterm2_2y[6]=(2*(y3-y2)*(z3-z2)*PS)/(b*b*b*b)-(2*(y1-y2)*(z2-z1)*PS)/(a*a*a*a)+((y3-y2)*(z3-2*z2+z1))/(b*b)+((y1-y2)*(z3-2*z2+z1))/(a*a);
	Dterm2_2y[9]=-(2*(y3-y2)*(z3-z2)*PS)/(b*b*b*b)+((y3-y2)*(z2-z1))/(b*b)+((y1-y2)*(z2-z1))/(a*a);
	//printf(" Dterm2_2y[1] %8.0lf Dterm2_2y[2] %8.0lf Dterm2_2y[3] %8.0lf",Dterm2_2y[1],Dterm2_2y[2],Dterm2_2y[3]);
	//printf(" Dterm2_2y[4] %8.0lf Dterm2_2y[5] %8.0lf Dterm2_2y[6] %8.0lf",Dterm2_2y[4],Dterm2_2y[5],Dterm2_2y[6]);
	//printf(" Dterm2_2y[7] %8.0lf Dterm2_2y[8] %8.0lf Dterm2_2y[9] %8.0lf\n",Dterm2_2y[7],Dterm2_2y[8],Dterm2_2y[9]);
	
	Dterm2_2z[1]=(2*(x2-x1)*(z1-z2)*PS)/(a*a*a*a)+((x2-x3)*(z3-z2))/(b*b)+((x2-x3)*(z1-z2))/(a*a);
	Dterm2_2z[4]=(2*(x3-x2)*(z3-z2)*PS)/(b*b*b*b)-(2*(x2-x1)*(z1-z2)*PS)/(a*a*a*a)+((x3-2*x2+x1)*(z3-z2))/(b*b)+((x3-2*x2+x1)*(z1-z2))/(a*a);
	Dterm2_2z[7]=-(2*(x3-x2)*(z3-z2)*PS)/(b*b*b*b)+((x2-x1)*(z3-z2))/(b*b)+((x2-x1)*(z1-z2))/(a*a);
	Dterm2_2z[2]=(2*(y2-y1)*(z1-z2)*PS)/(a*a*a*a)+((y2-y3)*(z3-z2))/(b*b)+((y2-y3)*(z1-z2))/(a*a);
	Dterm2_2z[5]=(2*(y3-y2)*(z3-z2)*PS)/(b*b*b*b)-(2*(y2-y1)*(z1-z2)*PS)/(a*a*a*a)+((y3-2*y2+y1)*(z3-z2))/(b*b)+((y3-2*y2+y1)*(z1-z2))/(a*a);
	Dterm2_2z[8]=-(2*(y3-y2)*(z3-z2)*PS)/(b*b*b*b)+((y2-y1)*(z3-z2))/(b*b)+((y2-y1)*(z1-z2))/(a*a);
	Dterm2_2z[3]=(PS)/(a*a)+(2*(z1-z2)*(z2-z1)*PS)/(a*a*a*a)+((z2-z3)*(z3-z2))/(b*b)+((z1-z2)*(z2-z3))/(a*a)+1;
	Dterm2_2z[6]=-(PS)/(b*b)+(2*(z3-z2)*(z3-z2)*PS)/(b*b*b*b)-(PS)/(a*a)-(2*(z1-z2)*(z2-z1)*PS)/(a*a*a*a)+((z3-2*z2+z1)*(z3-z2))/(b*b)+((z1-z2)*(z3-2*z2+z1))/(a*a)-2;
	Dterm2_2z[9]=(PS)/(b*b)-(2*(z3-z2)*(z3-z2)*PS)/(b*b*b*b)+((z2-z1)*(z3-z2))/(b*b)+(z1-z2)*(z2-z1)/(a*a)+1;
	//printf(" Dterm2_2z[1] %8.0lf Dterm2_2z[2] %8.0lf Dterm2_2z[3] %8.0lf",Dterm2_2z[1],Dterm2_2z[2],Dterm2_2z[3]);
	//printf(" Dterm2_2z[4] %8.0lf Dterm2_2z[5] %8.0lf Dterm2_2z[6] %8.0lf",Dterm2_2z[4],Dterm2_2z[5],Dterm2_2z[6]);
	//printf(" Dterm2_2z[7] %8.0lf Dterm2_2z[8] %8.0lf Dterm2_2z[9] %8.0lf\n",Dterm2_2z[7],Dterm2_2z[8],Dterm2_2z[9]);
	
	Dterm2_3x[1]=(x2-x3)*(x2-x3)/b/b-1;
	Dterm2_3x[4]=PS/b/b+(2*(x2-x3)*(x3-x2)*PS)/b/b/b/b+((x2-x3)*(x3-2*x2+x1))/b/b+1;
	Dterm2_3x[7]=-PS/b/b-(2*(x2-x3)*(x3-x2)*PS)/b/b/b/b+((x2-x1)*(x2-x3))/b/b;
	Dterm2_3x[2]=((x2-x3)*(y2-y3))/b/b;
	Dterm2_3x[5]=(2*(x2-x3)*(y3-y2)*PS)/b/b/b/b+((x2-x3)*(y3-2*y2+y1))/b/b;
	Dterm2_3x[8]=((x2-x3)*(y2-y1))/b/b-(2*(x2-x3)*(y3-y2)*PS)/b/b/b/b;
	Dterm2_3x[3]=((x2-x3)*(z2-z3))/b/b;
	Dterm2_3x[6]=(2*(x2-x3)*(z3-z2)*PS)/b/b/b/b+((x2-x3)*(z3-2*z2+z1))/b/b;
	Dterm2_3x[9]=((x2-x3)*(z2-z1))/b/b-(2*(x2-x3)*(z3-z2)*PS)/b/b/b/b;
	//printf(" Dterm2_3x[1] %8.0lf Dterm2_3x[2] %8.0lf Dterm2_3x[3] %8.0lf",Dterm2_3x[1],Dterm2_3x[2],Dterm2_3x[3]);
	//printf(" Dterm2_3x[4] %8.0lf Dterm2_3x[5] %8.0lf Dterm2_3x[6] %8.0lf",Dterm2_3x[4],Dterm2_3x[5],Dterm2_3x[6]);
	//printf(" Dterm2_3x[7] %8.0lf Dterm2_3x[8] %8.0lf Dterm2_3x[9] %8.0lf\n",Dterm2_3x[7],Dterm2_3x[8],Dterm2_3x[9]);
	
	Dterm2_3y[1]=((x2-x3)*(y2-y3))/b/b;
	Dterm2_3y[4]=(2*(x3-x2)*(y2-y3)*PS)/b/b/b/b+((x3-2*x2+x1)*(y2-y3))/b/b;
	Dterm2_3y[7]=((x2-x1)*(y2-y3))/b/b-(2*(x3-x2)*(y2-y3)*PS)/b/b/b/b;
	Dterm2_3y[2]=(y2-y3)*(y2-y3)/b/b-1;
	Dterm2_3y[5]=PS/b/b+(2*(y2-y3)*(y3-y2)*PS)/b/b/b/b+((y2-y3)*(y3-2*y2+y1))/b/b+1;
	Dterm2_3y[8]=-PS/b/b-(2*(y2-y3)*(y3-y2)*PS)/b/b/b/b+((y2-y1)*(y2-y3))/b/b;
	Dterm2_3y[3]=((y2-y3)*(z2-z3))/b/b;
	Dterm2_3y[6]=(2*(y2-y3)*(z3-z2)*PS)/b/b/b/b+((y2-y3)*(z3-2*z2+z1))/b/b;
	Dterm2_3y[9]=((y2-y3)*(z2-z1))/b/b-(2*(y2-y3)*(z3-z2)*PS)/b/b/b/b;
	//printf(" Dterm2_3y[1] %8.0lf Dterm2_3y[2] %8.0lf Dterm2_3y[3] %8.0lf",Dterm2_3y[1],Dterm2_3y[2],Dterm2_3y[3]);
	//printf(" Dterm2_3y[4] %8.0lf Dterm2_3y[5] %8.0lf Dterm2_3y[6] %8.0lf",Dterm2_3y[4],Dterm2_3y[5],Dterm2_3y[6]);
	//printf(" Dterm2_3y[7] %8.0lf Dterm2_3y[8] %8.0lf Dterm2_3y[9] %8.0lf\n",Dterm2_3y[7],Dterm2_3y[8],Dterm2_3y[9]);
	
	Dterm2_3z[1]=((x2-x3)*(z2-z3))/b/b;
	Dterm2_3z[4]=(2*(x3-x2)*(z2-z3)*PS)/b/b/b/b+((x3-2*x2+x1)*(z2-z3))/b/b;
	Dterm2_3z[7]=((x2-x1)*(z2-z3))/b/b-(2*(x3-x2)*(z2-z3)*PS)/b/b/b/b;
	Dterm2_3z[2]=((y2-y3)*(z2-z3))/b/b;
	Dterm2_3z[5]=(2*(y3-y2)*(z2-z3)*PS)/b/b/b/b+((y3-2*y2+y1)*(z2-z3))/b/b;
	Dterm2_3z[8]=((y2-y1)*(z2-z3))/b/b-(2*(y3-y2)*(z2-z3)*PS)/b/b/b/b;
	Dterm2_3z[3]=(z2-z3)*(z2-z3)/b/b-1;
	Dterm2_3z[6]=PS/b/b+(2*(z2-z3)*(z3-z2)*PS)/b/b/b/b+((z2-z3)*(z3-2*z2+z1))/b/b+1l;
	Dterm2_3z[9]=-PS/b/b-(2*(z2-z3)*(z3-z2)*PS)/b/b/b/b+((z2-z1)*(z2-z3))/b/b;
	//printf(" Dterm2_3z[1] %8.0lf Dterm2_3z[2] %8.0lf Dterm2_3z[3] %8.0lf",Dterm2_3z[1],Dterm2_3z[2],Dterm2_3z[3]);
	//printf(" Dterm2_3z[4] %8.0lf Dterm2_3z[5] %8.0lf Dterm2_3z[6] %8.0lf",Dterm2_3z[4],Dterm2_3z[5],Dterm2_3z[6]);
	//printf(" Dterm2_3z[7] %8.0lf Dterm2_3z[8] %8.0lf Dterm2_3z[9] %8.0lf\n",Dterm2_3z[7],Dterm2_3z[8],Dterm2_3z[9]);
	//derivee de term3
	Dterm3[1]=-((((x2-x1)*PS)/(a*a*a*b)+(x2-x3)/(a*b))*(sin(alpha)*cos(alpha-beta)-cos(alpha)*sin(alpha-beta)))/sin(alpha)/sin(alpha)/sin(alpha);
	Dterm3[2]=-((((y2-y1)*PS)/(a*a*a*b)+(y2-y3)/(a*b))*(sin(alpha)*cos(alpha-beta)-cos(alpha)*sin(alpha-beta)))/sin(alpha)/sin(alpha)/sin(alpha);
	Dterm3[3]=-((((z2-z1)*PS)/(a*a*a*b)+(z2-z3)/(a*b))*(sin(alpha)*cos(alpha-beta)-cos(alpha)*sin(alpha-beta)))/sin(alpha)/sin(alpha)/sin(alpha);
	Dterm3[4]=-((-((x2-x1)*PS)/(a*a*a*b)+((x3-x2)*PS)/(a*b*b*b)+(x3-2*x2+x1)/(a*b))*(sin(alpha)*cos(alpha-beta)-cos(alpha)*sin(alpha-beta)))/sin(alpha)/sin(alpha)/sin(alpha);
	Dterm3[5]=-((-((y2-y1)*PS)/(a*a*a*b)+((y3-y2)*PS)/(a*b*b*b)+(y3-2*y2+y1)/(a*b))*(sin(alpha)*cos(alpha-beta)-cos(alpha)*sin(alpha-beta)))/sin(alpha)/sin(alpha)/sin(alpha);
	Dterm3[6]=-((-((z2-z1)*PS)/(a*a*a*b)+((z3-z2)*PS)/(a*b*b*b)+(z3-2*z2+z1)/(a*b))*(sin(alpha)*cos(alpha-beta)-cos(alpha)*sin(alpha-beta)))/sin(alpha)/sin(alpha)/sin(alpha);
	Dterm3[7]=-(((x2-x1)/(a*b)-((x3-x2)*PS)/(a*b*b*b))*(sin(alpha)*cos(alpha-beta)-cos(alpha)*sin(alpha-beta)))/sin(alpha)/sin(alpha)/sin(alpha);
	Dterm3[8]=-(((y2-y1)/(a*b)-((y3-y2)*PS)/(a*b*b*b))*(sin(alpha)*cos(alpha-beta)-cos(alpha)*sin(alpha-beta)))/sin(alpha)/sin(alpha)/sin(alpha);
	Dterm3[9]=-(((z2-z1)/(a*b)-((z3-z2)*PS)/(a*b*b*b))*(sin(alpha)*cos(alpha-beta)-cos(alpha)*sin(alpha-beta)))/sin(alpha)/sin(alpha)/sin(alpha);
	if (PRINT) printf("PS %8.3lf alpha %8.3lf a %8.3lf b %8.3lf c %8.3lf cos(alpha)=%8.3lf sin(alpha)=%8.3lf sin(alpha-beta)=%8.3lf",PS,alpha,a,b,c,cos(alpha),sin(alpha),sin(alpha-beta));
	if (PRINT) printf("\n");
	//derivee de x1 x2 x3 y1 y2 y3 z1 z2 z3
	dx1[1]=1;
	dx1[2]=0;
	dx1[3]=0;
	dx1[4]=0;
	dx1[5]=0;
	dx1[6]=0;
	dx1[7]=0;
	dx1[8]=0;
	dx1[9]=0;

	dy1[1]=0;
	dy1[2]=1;
	dy1[3]=0;
	dy1[4]=0;
	dy1[5]=0;
	dy1[6]=0;
	dy1[7]=0;
	dy1[8]=0;
	dy1[9]=0;

	dz1[1]=0;
	dz1[2]=0;
	dz1[3]=1;
	dz1[4]=0;
	dz1[5]=0;
	dz1[6]=0;
	dz1[7]=0;
	dz1[8]=0;
	dz1[9]=0;
	
	
	//derivee de c
	for (p=1;p<=9;p++)
		{
		Dc[p]=((xq3-x1)*(Dxq3[p]-dx1[p])+(yq3-y1)*(Dyq3[p]-dy1[p])+(zq3-z1)*(Dzq3[p]-dz1[p]))/c;		
		//printf("Dc[%d] %8.0lf ",p,Dc[p]);
		}
	//printf("\n");
	
	
	
		
	//derivee de F1 F2 F3
	for (p=1;p<=9;p++)
		{
		DFx1[p]=-1*(-Dc[p]*term1*term2_1x*term3/c/c+Dterm1[p]*term2_1x*term3/c+term1*Dterm2_1x[p]*term3/c+term1*term2_1x*Dterm3[p]/c);				
		//printf("DFx1[%d] %8.0lf ",p,DFx1[p]);
		//printf("\n");
		//printf("Dc[%d] %8.0lf ",p,Dc[p]);
		//printf("\n");
		//printf("Dterm1[%d] %8.0lf ",p,Dterm1[p]);
		//printf("\n");
		//printf("Dterm2_1x[%d] %8.0lf ",p,Dterm2_1x[p]);
		//printf("\n");
		//printf("Dterm3[%d] %8.0lf ",p,Dterm3[p]);
		//printf("\n");
		//printf("term1 %8.0lf ",term1);
		//printf("\n");
		//printf("term2_1x %8.0lf ",term2_1x);
		//printf("\n");
		//printf("term3 %8.0lf ",term3);
		//printf("\n");
		//printf("c %8.0lf ",c);
		//printf("\n");
		}
	//printf("\n");
	for (p=1;p<=9;p++)
		{
		DFy1[p]=-1*(-Dc[p]*term1*term2_1y*term3/c/c+Dterm1[p]*term2_1y*term3/c+term1*Dterm2_1y[p]*term3/c+term1*term2_1y*Dterm3[p]/c);
		//DFy1[p]=-Dc[p]*term1*term2_1y*term3/c/c;
		//DFy1[p]=Dterm1[p]*term2_1y*term3/c;
		//DFy1[p]=term1*Dterm2_1y[p]*term3/c;
		//DFy1[p]=term1*term2_1y*Dterm3[p]/c;

	
		//printf("DFy1[%d] %8.0lf ",p,DFy1[p]);
		}
	//printf("\n");
	for (p=1;p<=9;p++)
		{
		DFz1[p]=-1*(-Dc[p]*term1*term2_1z*term3/c/c+Dterm1[p]*term2_1z*term3/c+term1*Dterm2_1z[p]*term3/c+term1*term2_1z*Dterm3[p]/c);
				
		//printf("DFz1[%d] %8.0lf ",p,DFz1[p]);
		}
	//printf("\n");
	for (p=1;p<=9;p++)
		{
		DFx2[p]=-1*(-Dc[p]*term1*term2_2x*term3/c/c+Dterm1[p]*term2_2x*term3/c+term1*Dterm2_2x[p]*term3/c+term1*term2_2x*Dterm3[p]/c);
		//DFx2[p]=-Dc[p]*term1*term2_2x*term3/c/c;
		//DFx2[p]=Dterm1[p]*term2_2x*term3/c;
		//DFx2[p]=term1*Dterm2_2x[p]*term3/c;
		//DFx2[p]=term1*term2_2x*Dterm3[p]/c;		
		//printf("DFx2[%d] %8.0lf ",p,DFx2[p]);
		}
	//printf("\n");
	for (p=1;p<=9;p++)
		{
		DFy2[p]=-1*(-Dc[p]*term1*term2_2y*term3/c/c+Dterm1[p]*term2_2y*term3/c+term1*Dterm2_2y[p]*term3/c+term1*term2_2y*Dterm3[p]/c);
		//DFy2[p]=-Dc[p]*term1*term2_2y*term3/c/c;
		//DFy2[p]=Dterm1[p]*term2_2y*term3/c;
		//DFy2[p]=term1*Dterm2_2y[p]*term3/c;
		//DFy2[p]=term1*term2_2y*Dterm3[p]/c;		
		//printf("DFy2[%d] %8.0lf ",p,DFy2[p]);
		}
	//printf("\n");
	for (p=1;p<=9;p++)
	{
		DFz2[p]=-1*(-Dc[p]*term1*term2_2z*term3/c/c+Dterm1[p]*term2_2z*term3/c+term1*Dterm2_2z[p]*term3/c+term1*term2_2z*Dterm3[p]/c);
				
	//printf("DFz2[%d] %8.0lf ",p,DFz2[p]);
	}
	//printf("\n");
	for (p=1;p<=9;p++)
		{
		DFx3[p]=-1*(-Dc[p]*term1*term2_3x*term3/c/c+Dterm1[p]*term2_3x*term3/c+term1*Dterm2_3x[p]*term3/c+term1*term2_3x*Dterm3[p]/c);
		//DFx3[p]=-Dc[p]*term1*term2_3x*term3/c/c;
		//DFx3[p]=Dterm1[p]*term2_3x*term3/c;
		//DFx3[p]=term1*Dterm2_3x[p]*term3/c;
		//DFx3[p]=term1*term2_3x*Dterm3[p]/c;		
		//printf("DFx3[%d] %8.0lf ",p,DFx3[p]);
		}
	//printf("\n");
	for (p=1;p<=9;p++)
		{
		DFy3[p]=-1*(-Dc[p]*term1*term2_3y*term3/c/c+Dterm1[p]*term2_3y*term3/c+term1*Dterm2_3y[p]*term3/c+term1*term2_3y*Dterm3[p]/c);				
		//printf("DFy3[%d] %8.0lf ",p,DFy3[p]);
		}
	//printf("\n");
	for (p=1;p<=9;p++)
		{
		DFz3[p]=-1*(-Dc[p]*term1*term2_3z*term3/c/c+Dterm1[p]*term2_3z*term3/c+term1*Dterm2_3z[p]*term3/c+term1*term2_3z*Dterm3[p]/c);				
		//printf("DFz3[%d] %8.0lf ",p,DFz3[p]);
		}
	//printf("\n");
	
	

	//verification
	sommex=Fx1+Fx2+Fx3;
	sommey=Fy1+Fy2+Fy3;
	sommez=Fz1+Fz2+Fz3;
	//printf(" \nsommex %lf sommey %lf sommez %lf\n",sommex,sommey,sommez);
	for (p=1;p<=9;p++)
		{
		DFxsomme[p]=DFx1[p]+DFx2[p]+DFx3[p];				
		//printf("DFxsomme[%d] %lf\n ",p,DFxsomme[p]);
		}
	for (p=1;p<=9;p++)
		{
		DFysomme[p]=DFy1[p]+DFy2[p]+DFy3[p];				
		//printf("DFysomme[%d] %lf\n ",p,DFysomme[p]);	
		}
	for (p=1;p<=9;p++)
		{
		DFzsomme[p]=DFz1[p]+DFz2[p]+DFz3[p];
		//printf("DFzsomme[%d] %lf\n ",p,DFzsomme[p]);
		}
	//exit(0);

	/*TEST_debut
		if (zu == 0)
			{
			Xq3=xq3; 
			Yq3=yq3; 
			Zq3=zq3; 
			Term1=term1;
			Term2_1x=term2_1x;
			C=c;
			fx1=Fx1;	fy1=Fy1;	fz1=Fz1;	
			fx2=Fx2;	fy2=Fy2;	fz2=Fz2;	
			fx3=Fx3;	fy3=Fy3;	fz3=Fz3;	
			
			Term2_1x=term2_1x;
			Term2_1y=term2_1y;
			Term2_1z=term2_1z;
			Term2_2x=term2_2x;
			Term2_2y=term2_2y;
			Term2_2z=term2_2z;
			Term2_3x=term2_3x;
			Term2_3y=term2_3y;
			Term2_3z=term2_3z;
			Term3= term3;
			}

		if ((zu > 0) && (zu < 10)) 
			{
			dxq3[zu] 	= (xq3 - Xq3) 		/ delta_x; 
			dyq3[zu] 	= (yq3 - Yq3) 		/ delta_x; 
			dzq3[zu] 	= (zq3 - Zq3) 		/ delta_x; 
			dterm1[zu] 	= (term1 - Term1) 	/ delta_x;
			dc[zu] 		= (c - C) 		/ delta_x;
			dFx1[zu]	= (Fx1-fx1)		/ delta_x;	
			dFy1[zu]	= (Fy1-fy1)		/ delta_x;	
			dFz1[zu]	= (Fz1-fz1)		/ delta_x;
			dFx2[zu]	= (Fx2-fx2)		/ delta_x;	
			dFy2[zu]	= (Fy2-fy2)		/ delta_x;	
			dFz2[zu]	= (Fz2-fz2)		/ delta_x;
			dFx3[zu]	= (Fx3-fx3)		/ delta_x;	
			dFy3[zu]	= (Fy3-fy3)		/ delta_x;	
			dFz3[zu]	= (Fz3-fz3)		/ delta_x;
			dterm2_1x[zu]	= (term2_1x-Term2_1x)	/ delta_x;
			dterm2_1y[zu]	= (term2_1y-Term2_1y)	/ delta_x;
			dterm2_1z[zu]	= (term2_1z-Term2_1z)	/ delta_x;
			dterm2_2x[zu]	= (term2_2x-Term2_2x)	/ delta_x;
			dterm2_2y[zu]	= (term2_2y-Term2_2y)	/ delta_x;
			dterm2_2z[zu]	= (term2_2z-Term2_2z)	/ delta_x;
			dterm2_3x[zu]	= (term2_3x-Term2_3x)	/ delta_x;
			dterm2_3y[zu]	= (term2_3y-Term2_3y)	/ delta_x;
			dterm2_3z[zu]	= (term2_3z-Term2_3z)	/ delta_x;
			dterm3[zu]	= (term3 - Term3)	/ delta_x;
			}
		if (zu == 1) 	x1 = x1 - delta_x;
		if (zu == 2)	y1 = y1 - delta_x;
		if (zu == 3)	z1 = z1 - delta_x;
		if (zu == 4)	x2 = x2 - delta_x;
		if (zu == 5)	y2 = y2 - delta_x;
		if (zu == 6)	z2 = z2 - delta_x;
		if (zu == 7)	x3 = x3 - delta_x;
		if (zu == 8)	y3 = y3 - delta_x;
		if (zu == 9)	z3 = z3 - delta_x;
	}
      					
	printf("Dxq3 =");       imprvectreel(9, Dxq3);		printf("dxq3 =");       	imprvectreel(9, dxq3);
	printf("Dyq3 =");       imprvectreel(9, Dyq3);		printf("dyq3 =");       	imprvectreel(9, dyq3);
	printf("Dzq3 =");       imprvectreel(9, Dzq3);		printf("dzq3 =");       	imprvectreel(9, dzq3);
	printf("Dterm1 =");     imprvectreel(9, Dterm1);	printf("dterm1 ="); 		imprvectreel(9, dterm1);
	printf("Dc =");     	imprvectreel(9, Dc);		printf("dc ="); 		imprvectreel(9, dc);
	printf("DFx1 =");     	imprvectreel(9, DFx1);		printf("dFx1 =");     		imprvectreel(9, dFx1);
	printf("DFy1 =");     	imprvectreel(9, DFy1);		printf("dFy1 =");     		imprvectreel(9, dFy1);
	printf("DFz1 =");    	 imprvectreel(9, DFz1);		printf("dFz1 =");     		imprvectreel(9, dFz1);
	printf("DFx2 =");    	 imprvectreel(9, DFx2);		printf("dFx2 =");     		imprvectreel(9, dFx2);
	printf("DFy2 =");    	 imprvectreel(9, DFy2);		printf("dFy2 =");     		imprvectreel(9, dFy2);
	printf("DFz2 =");    	 imprvectreel(9, DFz2);		printf("dFz2 =");     		imprvectreel(9, dFz2);
	printf("DFx3 =");    	 imprvectreel(9, DFx3);		printf("dFx3 =");     		imprvectreel(9, dFx3);
	printf("DFy3 =");    	 imprvectreel(9, DFy3);		printf("dFy3 =");     		imprvectreel(9, dFy3);
	printf("DFz3 =");    	 imprvectreel(9, DFz3);		printf("dFz3 =");     		imprvectreel(9, dFz3);
	//printf("Dterm2_1x =");   imprvectreel(9, Dterm2_1x);	printf("dterm2_1x =");     	imprvectreel(9, dterm2_1x);
	//printf("Dterm2_1y =");   imprvectreel(9, Dterm2_1y);	printf("dterm2_1y =");     	imprvectreel(9, dterm2_1y);
	//printf("Dterm2_1z =");   imprvectreel(9, Dterm2_1z);	printf("dterm2_1z =");     	imprvectreel(9, dterm2_1z);
	//printf("Dterm2_2x =");   imprvectreel(9, Dterm2_2x);	printf("dterm2_2x =");     	imprvectreel(9, dterm2_2x);
	//printf("Dterm2_2y =");   imprvectreel(9, Dterm2_2y);	printf("dterm2_2y =");     	imprvectreel(9, dterm2_2y);
	//printf("Dterm2_2z =");   imprvectreel(9, Dterm2_2z);	printf("dterm2_2z =");     	imprvectreel(9, dterm2_2z);
	//printf("Dterm2_3x =");   imprvectreel(9, Dterm2_3x);	printf("dterm2_3x =");     	imprvectreel(9, dterm2_3x);
	//printf("Dterm2_3y =");   imprvectreel(9, Dterm2_3y);	printf("dterm2_3y =");     	imprvectreel(9, dterm2_3y);
	//printf("Dterm2_3z =");   imprvectreel(9, Dterm2_3z);	printf("dterm2_3z =");     	imprvectreel(9, dterm2_3z);
	//printf("Dterm3 =");      imprvectreel(9, Dterm3);	printf("dterm3 ="); 		imprvectreel(9, dterm3);
	
	printf("VNx %lf VNy %lf VNz %lf VN %lf\n",VNx,VNy,VNz,VN);
	printf("alpha (deg.) %lf beta (deg.) %lf\n",alpha*180/PI,beta*180/PI);
	printf("x1 %lf y1 %lf z1 %lf  \n",x1,y1,z1);
	printf("x2 %lf y2 %lf z2 %lf  \n",x2,y2,z2);
	printf("x3 %lf y3 %lf z3 %lf  \n",x3,y3,z3);
	printf("xq3 %lf yq3 %lf zq3 %lf\n",xq3,yq3,zq3);
	printf(" Fx1 %lf Fy1 %lf Fz1 %lf\n",Fx1,Fy1,Fz1);
	printf(" Fx2 %lf Fy2 %lf Fz2 %lf\n",Fx2,Fy2,Fz2);
	printf(" Fx3 %lf Fy3 %lf Fz3 %lf\n",Fx3,Fy3,Fz3);
	exit(0);
	
	TEST_fin*/

	//------------------------------------------------------------------------------------------------------------------------------------

	waelem[3*zii-2] += Fx1;
	waelem[3*zii-1] += Fy1;
	waelem[3*zii-0] += Fz1;

	waelem[3*zjj-2] += Fx2;
	waelem[3*zjj-1] += Fy2;
	waelem[3*zjj-0] += Fz2;

	waelem[3*zkk-2] += Fx3;
	waelem[3*zkk-1] += Fy3;
	waelem[3*zkk-0] += Fz3;
	
	if (PRINT) printf(" Fx1 %lf Fy1 %lf Fz1 %lf\n",Fx1,Fy1,Fz1);
	if (PRINT) printf(" Fx2 %lf Fy2 %lf Fz2 %lf\n",Fx2,Fy2,Fz2);
	if (PRINT) printf(" Fx3 %lf Fy3 %lf Fz3 %lf\n",Fx3,Fy3,Fz3);
	
	/*problem: the derivative is opposite => K = + derivative in place of K = - derivative*/
	for (p=1;p<=9;p++)
		{
		K[1][p] = DFx1[p];	K[2][p] = DFy1[p];	K[3][p] = DFz1[p];
		K[4][p] = DFx2[p];	K[5][p] = DFy2[p];	K[6][p] = DFz2[p];
		K[7][p] = DFx3[p];	K[8][p] = DFy3[p];	K[9][p] = DFz3[p];
		}
	ii = 3*zii-2; jj = 3*zii-2;	ze[ii][eca-ii+jj] += K[1][1];	
	ii = 3*zii-2; jj = 3*zii-1;	ze[ii][eca-ii+jj] += K[1][2];	
	ii = 3*zii-2; jj = 3*zii-0;	ze[ii][eca-ii+jj] += K[1][3];	
	ii = 3*zii-2; jj = 3*zjj-2;	ze[ii][eca-ii+jj] += K[1][4];	
	ii = 3*zii-2; jj = 3*zjj-1;	ze[ii][eca-ii+jj] += K[1][5];	
	ii = 3*zii-2; jj = 3*zjj-0;	ze[ii][eca-ii+jj] += K[1][6];	
	ii = 3*zii-2; jj = 3*zkk-2;	ze[ii][eca-ii+jj] += K[1][7];	
	ii = 3*zii-2; jj = 3*zkk-1;	ze[ii][eca-ii+jj] += K[1][8];	
	ii = 3*zii-2; jj = 3*zkk-0;	ze[ii][eca-ii+jj] += K[1][9];
	
	ii = 3*zii-1; jj = 3*zii-2;	ze[ii][eca-ii+jj] += K[2][1];	
	ii = 3*zii-1; jj = 3*zii-1;	ze[ii][eca-ii+jj] += K[2][2];	
	ii = 3*zii-1; jj = 3*zii-0;	ze[ii][eca-ii+jj] += K[2][3];	
	ii = 3*zii-1; jj = 3*zjj-2;	ze[ii][eca-ii+jj] += K[2][4];	
	ii = 3*zii-1; jj = 3*zjj-1;	ze[ii][eca-ii+jj] += K[2][5];	
	ii = 3*zii-1; jj = 3*zjj-0;	ze[ii][eca-ii+jj] += K[2][6];	
	ii = 3*zii-1; jj = 3*zkk-2;	ze[ii][eca-ii+jj] += K[2][7];	
	ii = 3*zii-1; jj = 3*zkk-1;	ze[ii][eca-ii+jj] += K[2][8];	
	ii = 3*zii-1; jj = 3*zkk-0;	ze[ii][eca-ii+jj] += K[2][9];
	
	ii = 3*zii-0; jj = 3*zii-2;	ze[ii][eca-ii+jj] += K[3][1];	
	ii = 3*zii-0; jj = 3*zii-1;	ze[ii][eca-ii+jj] += K[3][2];	
	ii = 3*zii-0; jj = 3*zii-0;	ze[ii][eca-ii+jj] += K[3][3];	
	ii = 3*zii-0; jj = 3*zjj-2;	ze[ii][eca-ii+jj] += K[3][4];	
	ii = 3*zii-0; jj = 3*zjj-1;	ze[ii][eca-ii+jj] += K[3][5];	
	ii = 3*zii-0; jj = 3*zjj-0;	ze[ii][eca-ii+jj] += K[3][6];	
	ii = 3*zii-0; jj = 3*zkk-2;	ze[ii][eca-ii+jj] += K[3][7];	
	ii = 3*zii-0; jj = 3*zkk-1;	ze[ii][eca-ii+jj] += K[3][8];	
	ii = 3*zii-0; jj = 3*zkk-0;	ze[ii][eca-ii+jj] += K[3][9];
	
	ii = 3*zjj-2; jj = 3*zii-2;	ze[ii][eca-ii+jj] += K[4][1];	
	ii = 3*zjj-2; jj = 3*zii-1;	ze[ii][eca-ii+jj] += K[4][2];	
	ii = 3*zjj-2; jj = 3*zii-0;	ze[ii][eca-ii+jj] += K[4][3];	
	ii = 3*zjj-2; jj = 3*zjj-2;	ze[ii][eca-ii+jj] += K[4][4];	
	ii = 3*zjj-2; jj = 3*zjj-1;	ze[ii][eca-ii+jj] += K[4][5];	
	ii = 3*zjj-2; jj = 3*zjj-0;	ze[ii][eca-ii+jj] += K[4][6];	
	ii = 3*zjj-2; jj = 3*zkk-2;	ze[ii][eca-ii+jj] += K[4][7];	
	ii = 3*zjj-2; jj = 3*zkk-1;	ze[ii][eca-ii+jj] += K[4][8];	
	ii = 3*zjj-2; jj = 3*zkk-0;	ze[ii][eca-ii+jj] += K[4][9];
	
	ii = 3*zjj-1; jj = 3*zii-2;	ze[ii][eca-ii+jj] += K[5][1];	
	ii = 3*zjj-1; jj = 3*zii-1;	ze[ii][eca-ii+jj] += K[5][2];	
	ii = 3*zjj-1; jj = 3*zii-0;	ze[ii][eca-ii+jj] += K[5][3];	
	ii = 3*zjj-1; jj = 3*zjj-2;	ze[ii][eca-ii+jj] += K[5][4];	
	ii = 3*zjj-1; jj = 3*zjj-1;	ze[ii][eca-ii+jj] += K[5][5];	
	ii = 3*zjj-1; jj = 3*zjj-0;	ze[ii][eca-ii+jj] += K[5][6];	
	ii = 3*zjj-1; jj = 3*zkk-2;	ze[ii][eca-ii+jj] += K[5][7];	
	ii = 3*zjj-1; jj = 3*zkk-1;	ze[ii][eca-ii+jj] += K[5][8];	
	ii = 3*zjj-1; jj = 3*zkk-0;	ze[ii][eca-ii+jj] += K[5][9];
	
	ii = 3*zjj-0; jj = 3*zii-2;	ze[ii][eca-ii+jj] += K[6][1];	
	ii = 3*zjj-0; jj = 3*zii-1;	ze[ii][eca-ii+jj] += K[6][2];	
	ii = 3*zjj-0; jj = 3*zii-0;	ze[ii][eca-ii+jj] += K[6][3];	
	ii = 3*zjj-0; jj = 3*zjj-2;	ze[ii][eca-ii+jj] += K[6][4];	
	ii = 3*zjj-0; jj = 3*zjj-1;	ze[ii][eca-ii+jj] += K[6][5];	
	ii = 3*zjj-0; jj = 3*zjj-0;	ze[ii][eca-ii+jj] += K[6][6];	
	ii = 3*zjj-0; jj = 3*zkk-2;	ze[ii][eca-ii+jj] += K[6][7];	
	ii = 3*zjj-0; jj = 3*zkk-1;	ze[ii][eca-ii+jj] += K[6][8];	
	ii = 3*zjj-0; jj = 3*zkk-0;	ze[ii][eca-ii+jj] += K[6][9];
	
	ii = 3*zkk-2; jj = 3*zii-2;	ze[ii][eca-ii+jj] += K[7][1];	
	ii = 3*zkk-2; jj = 3*zii-1;	ze[ii][eca-ii+jj] += K[7][2];	
	ii = 3*zkk-2; jj = 3*zii-0;	ze[ii][eca-ii+jj] += K[7][3];	
	ii = 3*zkk-2; jj = 3*zjj-2;	ze[ii][eca-ii+jj] += K[7][4];	
	ii = 3*zkk-2; jj = 3*zjj-1;	ze[ii][eca-ii+jj] += K[7][5];	
	ii = 3*zkk-2; jj = 3*zjj-0;	ze[ii][eca-ii+jj] += K[7][6];	
	ii = 3*zkk-2; jj = 3*zkk-2;	ze[ii][eca-ii+jj] += K[7][7];	
	ii = 3*zkk-2; jj = 3*zkk-1;	ze[ii][eca-ii+jj] += K[7][8];	
	ii = 3*zkk-2; jj = 3*zkk-0;	ze[ii][eca-ii+jj] += K[7][9];
	
	ii = 3*zkk-1; jj = 3*zii-2;	ze[ii][eca-ii+jj] += K[8][1];	
	ii = 3*zkk-1; jj = 3*zii-1;	ze[ii][eca-ii+jj] += K[8][2];	
	ii = 3*zkk-1; jj = 3*zii-0;	ze[ii][eca-ii+jj] += K[8][3];	
	ii = 3*zkk-1; jj = 3*zjj-2;	ze[ii][eca-ii+jj] += K[8][4];	
	ii = 3*zkk-1; jj = 3*zjj-1;	ze[ii][eca-ii+jj] += K[8][5];	
	ii = 3*zkk-1; jj = 3*zjj-0;	ze[ii][eca-ii+jj] += K[8][6];	
	ii = 3*zkk-1; jj = 3*zkk-2;	ze[ii][eca-ii+jj] += K[8][7];	
	ii = 3*zkk-1; jj = 3*zkk-1;	ze[ii][eca-ii+jj] += K[8][8];	
	ii = 3*zkk-1; jj = 3*zkk-0;	ze[ii][eca-ii+jj] += K[8][9];
	
	ii = 3*zkk-0; jj = 3*zii-2;	ze[ii][eca-ii+jj] += K[9][1];	
	ii = 3*zkk-0; jj = 3*zii-1;	ze[ii][eca-ii+jj] += K[9][2];	
	ii = 3*zkk-0; jj = 3*zii-0;	ze[ii][eca-ii+jj] += K[9][3];	
	ii = 3*zkk-0; jj = 3*zjj-2;	ze[ii][eca-ii+jj] += K[9][4];	
	ii = 3*zkk-0; jj = 3*zjj-1;	ze[ii][eca-ii+jj] += K[9][5];	
	ii = 3*zkk-0; jj = 3*zjj-0;	ze[ii][eca-ii+jj] += K[9][6];	
	ii = 3*zkk-0; jj = 3*zkk-2;	ze[ii][eca-ii+jj] += K[9][7];	
	ii = 3*zkk-0; jj = 3*zkk-1;	ze[ii][eca-ii+jj] += K[9][8];	
	ii = 3*zkk-0; jj = 3*zkk-0;	ze[ii][eca-ii+jj] += K[9][9];
	////////////////////////////////////////////////////////////////////////
	if (rang[1][3*zii-2] < 3*zii-0) rang[1][3*zii-2] = 3*zii-0;	if (rang[1][3*zii-2] < 3*zjj-0) rang[1][3*zii-2] = 3*zjj-0;	if (rang[1][3*zii-2] < 3*zkk-0) rang[1][3*zii-2] = 3*zkk-0; 
	if (rang[1][3*zii-1] < 3*zii-0) rang[1][3*zii-1] = 3*zii-0; 	if (rang[1][3*zii-1] < 3*zjj-0) rang[1][3*zii-1] = 3*zjj-0; 	if (rang[1][3*zii-1] < 3*zkk-0) rang[1][3*zii-1] = 3*zkk-0; 
	if (rang[1][3*zii-0] < 3*zii-0) rang[1][3*zii-0] = 3*zii-0;	if (rang[1][3*zii-0] < 3*zjj-0) rang[1][3*zii-0] = 3*zjj-0;	if (rang[1][3*zii-0] < 3*zkk-0) rang[1][3*zii-0] = 3*zkk-0; 

	if (rang[2][3*zii-2] < 3*zii-0) rang[2][3*zii-2] = 3*zii-0; 	if (rang[2][3*zii-2] < 3*zjj-0) rang[2][3*zii-2] = 3*zjj-0; 	if (rang[2][3*zii-2] < 3*zkk-0) rang[2][3*zii-2] = 3*zkk-0; 
	if (rang[2][3*zii-1] < 3*zii-0) rang[2][3*zii-1] = 3*zii-0;	if (rang[2][3*zii-1] < 3*zjj-0) rang[2][3*zii-1] = 3*zjj-0;	if (rang[2][3*zii-1] < 3*zkk-0) rang[2][3*zii-1] = 3*zkk-0; 
	if (rang[2][3*zii-0] < 3*zii-0) rang[2][3*zii-0] = 3*zii-0;	if (rang[2][3*zii-0] < 3*zjj-0) rang[2][3*zii-0] = 3*zjj-0;	if (rang[2][3*zii-0] < 3*zkk-0) rang[2][3*zii-0] = 3*zkk-0;

	if (rang[3][3*zii-2] > 3*zii-2) rang[3][3*zii-2] = 3*zii-2; 	if (rang[3][3*zii-2] > 3*zjj-2) rang[3][3*zii-2] = 3*zjj-2; 	if (rang[3][3*zii-2] > 3*zkk-2) rang[3][3*zii-2] = 3*zkk-2; 
	if (rang[3][3*zii-1] > 3*zii-2) rang[3][3*zii-1] = 3*zii-2; 	if (rang[3][3*zii-1] > 3*zjj-2) rang[3][3*zii-1] = 3*zjj-2; 	if (rang[3][3*zii-1] > 3*zkk-2) rang[3][3*zii-1] = 3*zkk-2; 
	if (rang[3][3*zii-0] > 3*zii-2) rang[3][3*zii-0] = 3*zii-2; 	if (rang[3][3*zii-0] > 3*zjj-2) rang[3][3*zii-0] = 3*zjj-2; 	if (rang[3][3*zii-0] > 3*zkk-2) rang[3][3*zii-0] = 3*zkk-2; 

	if (rang[4][3*zii-2] > 3*zii-2) rang[4][3*zii-2] = 3*zii-2; 	if (rang[4][3*zii-2] > 3*zjj-2) rang[4][3*zii-2] = 3*zjj-2; 	if (rang[4][3*zii-2] > 3*zkk-2) rang[4][3*zii-2] = 3*zkk-2; 
	if (rang[4][3*zii-1] > 3*zii-2) rang[4][3*zii-1] = 3*zii-2; 	if (rang[4][3*zii-1] > 3*zjj-2) rang[4][3*zii-1] = 3*zjj-2; 	if (rang[4][3*zii-1] > 3*zkk-2) rang[4][3*zii-1] = 3*zkk-2; 
	if (rang[4][3*zii-0] > 3*zii-2) rang[4][3*zii-0] = 3*zii-2;	if (rang[4][3*zii-0] > 3*zjj-2) rang[4][3*zii-0] = 3*zjj-2;	if (rang[4][3*zii-0] > 3*zkk-2) rang[4][3*zii-0] = 3*zkk-2;

	if (rang[1][3*zjj-2] < 3*zii-0) rang[1][3*zjj-2] = 3*zii-0;	if (rang[1][3*zjj-2] < 3*zjj-0) rang[1][3*zjj-2] = 3*zjj-0;	if (rang[1][3*zjj-2] < 3*zkk-0) rang[1][3*zjj-2] = 3*zkk-0; 
	if (rang[1][3*zjj-1] < 3*zii-0) rang[1][3*zjj-1] = 3*zii-0; 	if (rang[1][3*zjj-1] < 3*zjj-0) rang[1][3*zjj-1] = 3*zjj-0; 	if (rang[1][3*zjj-1] < 3*zkk-0) rang[1][3*zjj-1] = 3*zkk-0; 
	if (rang[1][3*zjj-0] < 3*zii-0) rang[1][3*zjj-0] = 3*zii-0;	if (rang[1][3*zjj-0] < 3*zjj-0) rang[1][3*zjj-0] = 3*zjj-0;	if (rang[1][3*zjj-0] < 3*zkk-0) rang[1][3*zjj-0] = 3*zkk-0; 

	if (rang[2][3*zjj-2] < 3*zii-0) rang[2][3*zjj-2] = 3*zii-0; 	if (rang[2][3*zjj-2] < 3*zjj-0) rang[2][3*zjj-2] = 3*zjj-0; 	if (rang[2][3*zjj-2] < 3*zkk-0) rang[2][3*zjj-2] = 3*zkk-0; 
	if (rang[2][3*zjj-1] < 3*zii-0) rang[2][3*zjj-1] = 3*zii-0;	if (rang[2][3*zjj-1] < 3*zjj-0) rang[2][3*zjj-1] = 3*zjj-0;	if (rang[2][3*zjj-1] < 3*zkk-0) rang[2][3*zjj-1] = 3*zkk-0; 
	if (rang[2][3*zjj-0] < 3*zii-0) rang[2][3*zjj-0] = 3*zii-0;	if (rang[2][3*zjj-0] < 3*zjj-0) rang[2][3*zjj-0] = 3*zjj-0;	if (rang[2][3*zjj-0] < 3*zkk-0) rang[2][3*zjj-0] = 3*zkk-0;

	if (rang[3][3*zjj-2] > 3*zii-2) rang[3][3*zjj-2] = 3*zii-2; 	if (rang[3][3*zjj-2] > 3*zjj-2) rang[3][3*zjj-2] = 3*zjj-2; 	if (rang[3][3*zjj-2] > 3*zkk-2) rang[3][3*zjj-2] = 3*zkk-2; 
	if (rang[3][3*zjj-1] > 3*zii-2) rang[3][3*zjj-1] = 3*zii-2; 	if (rang[3][3*zjj-1] > 3*zjj-2) rang[3][3*zjj-1] = 3*zjj-2; 	if (rang[3][3*zjj-1] > 3*zkk-2) rang[3][3*zjj-1] = 3*zkk-2; 
	if (rang[3][3*zjj-0] > 3*zii-2) rang[3][3*zjj-0] = 3*zii-2; 	if (rang[3][3*zjj-0] > 3*zjj-2) rang[3][3*zjj-0] = 3*zjj-2; 	if (rang[3][3*zjj-0] > 3*zkk-2) rang[3][3*zjj-0] = 3*zkk-2; 

	if (rang[4][3*zjj-2] > 3*zii-2) rang[4][3*zjj-2] = 3*zii-2; 	if (rang[4][3*zjj-2] > 3*zjj-2) rang[4][3*zjj-2] = 3*zjj-2; 	if (rang[4][3*zjj-2] > 3*zkk-2) rang[4][3*zjj-2] = 3*zkk-2; 
	if (rang[4][3*zjj-1] > 3*zii-2) rang[4][3*zjj-1] = 3*zii-2; 	if (rang[4][3*zjj-1] > 3*zjj-2) rang[4][3*zjj-1] = 3*zjj-2; 	if (rang[4][3*zjj-1] > 3*zkk-2) rang[4][3*zjj-1] = 3*zkk-2; 
	if (rang[4][3*zjj-0] > 3*zii-2) rang[4][3*zjj-0] = 3*zii-2;	if (rang[4][3*zjj-0] > 3*zjj-2) rang[4][3*zjj-0] = 3*zjj-2;	if (rang[4][3*zjj-0] > 3*zkk-2) rang[4][3*zjj-0] = 3*zkk-2;


	if (rang[1][3*zkk-2] < 3*zii-0) rang[1][3*zkk-2] = 3*zii-0;	if (rang[1][3*zkk-2] < 3*zjj-0) rang[1][3*zkk-2] = 3*zjj-0;	if (rang[1][3*zkk-2] < 3*zkk-0) rang[1][3*zkk-2] = 3*zkk-0; 
	if (rang[1][3*zkk-1] < 3*zii-0) rang[1][3*zkk-1] = 3*zii-0; 	if (rang[1][3*zkk-1] < 3*zjj-0) rang[1][3*zkk-1] = 3*zjj-0; 	if (rang[1][3*zkk-1] < 3*zkk-0) rang[1][3*zkk-1] = 3*zkk-0; 
	if (rang[1][3*zkk-0] < 3*zii-0) rang[1][3*zkk-0] = 3*zii-0;	if (rang[1][3*zkk-0] < 3*zjj-0) rang[1][3*zkk-0] = 3*zjj-0;	if (rang[1][3*zkk-0] < 3*zkk-0) rang[1][3*zkk-0] = 3*zkk-0; 

	if (rang[2][3*zkk-2] < 3*zii-0) rang[2][3*zkk-2] = 3*zii-0; 	if (rang[2][3*zkk-2] < 3*zjj-0) rang[2][3*zkk-2] = 3*zjj-0; 	if (rang[2][3*zkk-2] < 3*zkk-0) rang[2][3*zkk-2] = 3*zkk-0; 
	if (rang[2][3*zkk-1] < 3*zii-0) rang[2][3*zkk-1] = 3*zii-0;	if (rang[2][3*zkk-1] < 3*zjj-0) rang[2][3*zkk-1] = 3*zjj-0;	if (rang[2][3*zkk-1] < 3*zkk-0) rang[2][3*zkk-1] = 3*zkk-0; 
	if (rang[2][3*zkk-0] < 3*zii-0) rang[2][3*zkk-0] = 3*zii-0;	if (rang[2][3*zkk-0] < 3*zjj-0) rang[2][3*zkk-0] = 3*zjj-0;	if (rang[2][3*zkk-0] < 3*zkk-0) rang[2][3*zkk-0] = 3*zkk-0;

	if (rang[3][3*zkk-2] > 3*zii-2) rang[3][3*zkk-2] = 3*zii-2; 	if (rang[3][3*zkk-2] > 3*zjj-2) rang[3][3*zkk-2] = 3*zjj-2; 	if (rang[3][3*zkk-2] > 3*zkk-2) rang[3][3*zkk-2] = 3*zkk-2; 
	if (rang[3][3*zkk-1] > 3*zii-2) rang[3][3*zkk-1] = 3*zii-2; 	if (rang[3][3*zkk-1] > 3*zjj-2) rang[3][3*zkk-1] = 3*zjj-2; 	if (rang[3][3*zkk-1] > 3*zkk-2) rang[3][3*zkk-1] = 3*zkk-2; 
	if (rang[3][3*zkk-0] > 3*zii-2) rang[3][3*zkk-0] = 3*zii-2; 	if (rang[3][3*zkk-0] > 3*zjj-2) rang[3][3*zkk-0] = 3*zjj-2; 	if (rang[3][3*zkk-0] > 3*zkk-2) rang[3][3*zkk-0] = 3*zkk-2; 

	if (rang[4][3*zkk-2] > 3*zii-2) rang[4][3*zkk-2] = 3*zii-2; 	if (rang[4][3*zkk-2] > 3*zjj-2) rang[4][3*zkk-2] = 3*zjj-2; 	if (rang[4][3*zkk-2] > 3*zkk-2) rang[4][3*zkk-2] = 3*zkk-2; 
	if (rang[4][3*zkk-1] > 3*zii-2) rang[4][3*zkk-1] = 3*zii-2; 	if (rang[4][3*zkk-1] > 3*zjj-2) rang[4][3*zkk-1] = 3*zjj-2; 	if (rang[4][3*zkk-1] > 3*zkk-2) rang[4][3*zkk-1] = 3*zkk-2; 
	if (rang[4][3*zkk-0] > 3*zii-2) rang[4][3*zkk-0] = 3*zii-2;	if (rang[4][3*zkk-0] > 3*zjj-2) rang[4][3*zkk-0] = 3*zjj-2;	if (rang[4][3*zkk-0] > 3*zkk-2) rang[4][3*zkk-0] = 3*zkk-2;

	////////////////////////////////////////////////////////////////////////
					
	/*
	trouve = 0;
	if (zii == 1099 && zjj == 1091) trouve = 1;	if (zjj == 1099 && zii == 1091) trouve = 1;
	if (zii == 1099 && zkk == 1091) trouve = 1;	if (zkk == 1099 && zii == 1091) trouve = 1;
	if (zjj == 1099 && zkk == 1091) trouve = 1;	if (zkk == 1099 && zjj == 1091) trouve = 1;
	if (trouve == 1)
		{
		printf("bar1 %d bar2 %d\n",bar1,bar2);
		printf("zii %d zjj %d zkk %d\n",zii,zjj,zkk);
		printf("K\n");
		for( zu = 1 ; zu <= 9 ; zu++ )
			{
			for( zw = 1 ; zw <= 9 ; zw++ )
				{
				printf("%11.0lf   ",K[zu][zw]);
				}
			printf("\n");
			}
		printf("ze[%d][%d] %11.0lf   ",3297,1474,ze[3297][1474]);
		printf("rang[1][%d] %d  ",3297,rang[1][3297]);
		printf("rang[2][%d] %d  ",3297,rang[2][3297]);
		printf("rang[2][%d] %d  ",3297,rang[3][3297]);
		printf("rang[4][%d] %d\n",3297,rang[4][3297]);
		printf("zii %d zjj %d zkk %d\n",zii,zjj,zkk);
		}

	*/
}


