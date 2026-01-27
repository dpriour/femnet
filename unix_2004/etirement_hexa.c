#define PRINCIPAL 0
#include "4c19.h"

double lo,mo,no,U1,U2,U3,V1,V2,V3,deno,lx,ly,mx,my,nx,ny,l,m,n;
double max,seuil;	
double Ux,Uy,Vx,Vy,EAl,EAm,EAn;
double coelem[7],temp[10];
double Tmax[9],Tl[9],Tm[9],Tn[9];
int Tcompteur[9],Ttest[9];
int compteur,limite_compteur;
int test,cas;

void etirement_hexa(int elem)
	{
	/* 
	Raideurs we et efforts wae d une nappe de filet a maille hexagonale, 
	dus a l'elasticite des fils, dans le plan XOY.
   	Le module d'elasticite des fils est differents en traction et en compression.
   	Il est beaucoup plus faible en compression
   	*/

	double fx1,fy1,fx2,fy2,fx3,fy3,fx1_diff,fy1_diff,fx2_diff,fy2_diff,fx3_diff,fy3_diff;
	double pas,C1x,C1y,C2x,C2y,C1x_diff,C1y_diff,C2x_diff,C2y_diff;
	double A,B,C,p,S,perimetre;
	double h1,h2,h3;	
  	int k,zh,zi,zj;

  	/*superposition est un label, utilise par goto*/
  	superposition:{} 
  	
  	/* coelem() contient les coordonnees cartesiennes dans le plan XOY des sommets du triangle elem*/
  	coelem[1]=X1;  	coelem[2]=Y1;  	coelem[3]=X2;  	coelem[4]=Y2;  	coelem[5]=X3;  	coelem[6]=Y3;
  	
  	lo = Surf_Hexa[elem].lo_repos;    /*longueur au repos d une maille de direction l*/
  	mo = Surf_Hexa[elem].mo_repos;    /*longueur au repos d une maille de direction m*/
  	no = Surf_Hexa[elem].no_repos;    /*longueur au repos d une maille de direction n*/
   	
   	/* U1 : coordonnee du noeud 1 en nb de maille selon les fils de direction U.*/
   	/* U2 : coordonnee du noeud 2 en nb de maille selon les fils de direction U.*/
 	/* U3 : coordonnee du noeud 3 en nb de maille selon les fils de direction U. */    
  	/* V1 : coordonnee du noeud 1 en nb de maille selon les fils de direction V. */
  	/* V2 : coordonnee du noeud 2 en nb de maille selon les fils de direction V. */
  	/* V3 : coordonnee du noeud 3 en nb de maille selon les fils de direction V. */
 	U1 =   Surf_Hexa[elem].lon[1] - Surf_Hexa[elem].lon[1]; 
  	U2 =   Surf_Hexa[elem].lon[3] - Surf_Hexa[elem].lon[1]; 
  	U3 =   Surf_Hexa[elem].lon[5] - Surf_Hexa[elem].lon[1];  
  	V1 =   Surf_Hexa[elem].lon[2] - Surf_Hexa[elem].lon[2];  
  	V2 =   Surf_Hexa[elem].lon[4] - Surf_Hexa[elem].lon[2];  
  	V3 =   Surf_Hexa[elem].lon[6] - Surf_Hexa[elem].lon[2]; 
 
	deno=(U3-U1)*(V2-V1)-(U2-U1)*(V3-V1);
  	if( deno == 0.0 ) 
  		{
  		printf("ERREUR: changez les coordonnees U et V des sommets du triangle numero  %5.d", elem);
  		exit(0);
  		}

	calcul_lmn_hexa( elem);

  	/*On calcule les valeurs des composantes des mailles hexagonales dans l'espace.
  	  On les sauvegarde ensuite dans la structure Surf_Hexa.*/
  	temp[1] = lx;  	temp[2] = ly;  	temp[3] = 0.0;
  	temp[4] = mx;  	temp[5] = my;  	temp[6] = 0.0;
  	temp[7] = nx;  	temp[8] = ny;  	temp[9] = 0.0;
 	
	/*if ((elem == 1) || (elem == 2) || (elem == 10))
		{
		printf("elem = %d  ",elem);		
		printf("lx %lf  ",lx);	printf("ly %lf  ",ly);
		printf("mx %lf  ",mx);	printf("my %lf  ",my);
		printf("nx %lf  ",nx);	printf("ny %lf  \n",ny);
		}*/
 	
	/*printf("etirement_hexa alpha1 = %12.2lf  beta1= %12.2lf \n",alpha1/PI*180,beta1/PI*180);  */
  	base1( -betaa, 2, -alpha,  3,  9, temp);
  	Surf_Hexa[elem].lx = temp[1];  	Surf_Hexa[elem].ly = temp[2];  	Surf_Hexa[elem].lz = temp[3];
  	Surf_Hexa[elem].mx = temp[4];  	Surf_Hexa[elem].my = temp[5];  	Surf_Hexa[elem].mz = temp[6];
  	Surf_Hexa[elem].nx = temp[7];  	Surf_Hexa[elem].ny = temp[8];  	Surf_Hexa[elem].nz = temp[9];
  			
	/*Efforts du a l'elasticite sur les cotes elementaire de la maille(cf page 32 du rappoort de cgallee) */
	C1x=( EAl*(l-lo)/lo*lx/l - EAm*(m-mo)/mo*mx/m);
	C2x=(-EAn*(n-no)/no*nx/n                     );
	C1y=( EAl*(l-lo)/lo*ly/l - EAm*(m-mo)/mo*my/m);
	C2y=(-EAn*(n-no)/no*ny/n                      );
	
	/*Efforts du a l'elasticite de la structure en chacun des sommets du triangle 'elem'(cf page 33 du rappoort de cgallee).*/
	fx1=1/2.0*((U2-U3)*C1x+(V2-V3)*C2x);
	fy1=1/2.0*((U2-U3)*C1y+(V2-V3)*C2y);
	fx2=1/2.0*((U3-U1)*C1x+(V3-V1)*C2x);
	fy2=1/2.0*((U3-U1)*C1y+(V3-V1)*C2y);
	fx3=1/2.0*((U1-U2)*C1x+(V1-V2)*C2x);
	fy3=1/2.0*((U1-U2)*C1y+(V1-V2)*C2y);
	
if (elem == 5)
	{
	/*printf("l %lf %lf %lf %lf %lf %lf \n",lx,ly,mx,my,nx,ny);*/
	/*printf("C %lf %lf %lf %lf   \n",C1x,C1y,C2x,C2y);*/
	/*printf("f %lf %lf %lf %lf %lf %lf \n",fx1,fy1,fx2,fy2,fx3,fy3);*/
	}

  	/* Efforts aux 3 noeuds, sommets du triangle.*/
  	wae[1] = fx1;  	wae[2] = fy1;  	wae[3] = 0.0;
  	wae[4] = fx2;  	wae[5] = fy2;  	wae[6] = 0.0;
  	wae[7] = fx3;  	wae[8] = fy3;  	wae[9] = 0.0;
  	  	
/*On utilise la methode des differences finies pour calculer la matrice de raideur associee.*/
  	/*calcul du perimetre du triangle*/
  	A = sqrt((X3-X2)*(X3-X2) + (Y3-Y2)*(Y3-Y2));
  	B = sqrt((X1-X3)*(X1-X3) + (Y1-Y3)*(Y1-Y3));
  	C = sqrt((X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1));
  	perimetre=A+B+C;
  	/*valeur du pas pour la methode des differences finies */
  	pas=0.0000000001*perimetre;
  	
	for (k=1; k<=6; k++)
		{
		/*modification d'un epsilon de la position des noeuds.*/
		coelem[k]=coelem[k]+pas;
		
		calcul_lmn_hexa( elem);
		
		C1x_diff=( EAl*(l-lo)/lo*lx/l-EAm*(m-mo)/mo*mx/m);
		C2x_diff=(-EAn*(n-no)/no*nx/n                   );
		C1y_diff=( EAl*(l-lo)/lo*ly/l-EAm*(m-mo)/mo*my/m);
		C2y_diff=(-EAn*(n-no)/no*ny/n                   );
		/*effort du a l'elasticite avec la modification de la position des noeuds.*/
		fx1_diff=1/2.0*((U2-U3)*C1x_diff+(V2-V3)*C2x_diff);
		fy1_diff=1/2.0*((U2-U3)*C1y_diff+(V2-V3)*C2y_diff);
		fx2_diff=1/2.0*((U3-U1)*C1x_diff+(V3-V1)*C2x_diff);
		fy2_diff=1/2.0*((U3-U1)*C1y_diff+(V3-V1)*C2y_diff);
		fx3_diff=1/2.0*((U1-U2)*C1x_diff+(V1-V2)*C2x_diff);
		fy3_diff=1/2.0*((U1-U2)*C1y_diff+(V1-V2)*C2y_diff);
		
		/*restauration de la valeur initiale de la coordonnee modifiee.*/
		coelem[k]=coelem[k]-pas;
		
		/*calcul de la matrice de raideur we, pour la surface elem, par differences finies.
		(k+(k-1)/2) est egale a 1, 2, 4, 5, 7, 8 pour k= 1...6*/ 
		we[1][k+(k-1)/2]=(fx1-fx1_diff)/pas;
		we[2][k+(k-1)/2]=(fy1-fy1_diff)/pas;
		we[3][k+(k-1)/2]=0.0;
		we[4][k+(k-1)/2]=(fx2-fx2_diff)/pas;
		we[5][k+(k-1)/2]=(fy2-fy2_diff)/pas;
		we[6][k+(k-1)/2]=0.0;
		we[7][k+(k-1)/2]=(fx3-fx3_diff)/pas;
		we[8][k+(k-1)/2]=(fy3-fy3_diff)/pas;
		we[9][k+(k-1)/2]=0.0;
			
		}
  	
  	/*calcul des raideurs liees a un deplacement normal a la nappe de filet triangulaire*/

  	/*cotes A oppose au point 1 cotes B oppose au point 2 cotes C oppose au point 3*/
  
  	if( A == 0.0 )
  		{
  		if (nbiter == 1) printf("les sommets 2 et 3 du triangle %5d sont superposes.\n",elem);
  		printf("les sommets 2 et 3 du triangle %5d sont superposes.\n",elem);
  		zh = (int) yc_hexa(elem,3) / 3;
  		zi = (int) yc_hexa(elem,6) / 3;
  		zj = (int) yc_hexa(elem,9) / 3;
  		if (nbiter == 1) printf("les sommets 2 et 3 du triangle %5d sont %5d et %5d.\n",elem,zi,zj);
  		h1 = wf[yc_hexa(elem,7)] - wf[yc_hexa(elem,4)];
  		h2 = wf[yc_hexa(elem,8)] - wf[yc_hexa(elem,5)];
  		h3 = wf[yc_hexa(elem,9)] - wf[yc_hexa(elem,6)];
  		if (nbiter == 1) printf("dx = %lf dy = %lf dz = %lf \n",h1,h2,h3);
  		X3 = X2 + 0.0001;
  		Y3 = Y2 + 0.0001;
  		/*exit(0);*/
  		goto superposition;
  		}
  	if( B == 0.0 )
  		{
  		if (nbiter == 1) printf("les sommets 1 et 3 du triangle %5d sont superposes.\n",elem);
  		printf("les sommets 1 et 3 du triangle %5d sont superposes.\n",elem);
  		zh = (int) yc_hexa(elem,3) / 3;
  		zi = (int) yc_hexa(elem,6) / 3;
  		zj = (int) yc_hexa(elem,9) / 3;
  		if (nbiter == 1) printf("les sommets 1 et 3 du triangle %5d sont %5d et %5d.\n",elem,zh,zj);
  		X3 = X1 + 0.0001;
  		Y3 = Y1 + 0.0001;
  		/*exit(0);*/
  		goto superposition;
  		}
  	if( C == 0.0 )
  		{
  		if (nbiter == 1) printf("les sommets 1 et 2 du triangle %5d sont superposes.\n",elem);
  		printf("les sommets 1 et 2 du triangle %5d sont superposes.\n",elem);
  		zh = (int) yc_hexa(elem,3) / 3;
  		zi = (int) yc_hexa(elem,6) / 3;
  		zj = (int) yc_hexa(elem,9) / 3;
  		if (nbiter == 1) printf("les sommets 1 et 2 du triangle %5d sont %5d et %5d.\n",elem,zh,zi);
  		X2 = X1 + 0.0001;
  		Y2 = Y1 + 0.0001;
  		/*exit(0);*/
  		goto superposition;
  		}

  	/*p : demi perimetre du triangle*/
  	p = (A + B + C)/2.0;

  	/*S : surface du triangle*/
  	S = sqrt(p*(p-A)*(p-B)*(p-C));
 
  	if( S == 0.0 )
  		{
  		printf("la surface du triangle %5d est nulle.\n",elem);
  		/*on rajoute un petit quelque chose a X1 et Y1*/
  		X1 = X1 + rand() / RAND_MAX / 10000.0;
  		Y1 = Y1 + rand() / RAND_MAX / 10000.0;
  		goto superposition;
  		}
  	/*h1 : hauteur du triangle du point 1 au cote oppose*/
  	h1 = 2.0 * S / A;
  	h2 = 2.0 * S / B;
  	h3 = 2.0 * S / C;
  	if( (h1 == 0.0) || (h2 == 0.0) || (h3 == 0.0) )
  		{
  		printf("p S = %lf %lf\n",p,S);
  		printf("A B C = %lf %lf %lf\n",A,B,C);
  		printf("h1 h2 h3 = %lf %lf %lf\n",h1,h2,h3);
  		printf("X1 X2 X3 = %lf %lf %lf\n",X1,X2,X3);
  		printf("Y1 Y2 Y3 = %lf %lf %lf\n",Y1,Y2,Y3);
  		printf("h1, h2 ou h3 = 0.0\n");
  		exit(0);
  		}
  
  	/*raideur liees au deplacement du point 1 normalement au triangle*/
  	we[1][3] = 0.0;  we[2][3] = 0.0;  we[3][3] = (fx1*(Y3-Y2)-fy1*(X3-X2))/A/h1;
  	we[4][3] = 0.0;  we[5][3] = 0.0;  we[6][3] = (fx2*(Y3-Y2)-fy2*(X3-X2))/A/h1;
  	we[7][3] = 0.0;  we[8][3] = 0.0;  we[9][3] = (fx3*(Y3-Y2)-fy3*(X3-X2))/A/h1;

  	/*raideur liees au deplacement du point 2 normalement au triangle*/
  	we[1][6] = 0.0;  we[2][6] = 0.0;  we[3][6] = (fx1*(Y1-Y3)-fy1*(X1-X3))/B/h2;
  	we[4][6] = 0.0;  we[5][6] = 0.0;  we[6][6] = (fx2*(Y1-Y3)-fy2*(X1-X3))/B/h2;
  	we[7][6] = 0.0;  we[8][6] = 0.0;  we[9][6] = (fx3*(Y1-Y3)-fy3*(X1-X3))/B/h2;

 
  	/*raideur liees au deplacement du point 3 normalement au triangle*/
  	we[1][9] = 0.0;  we[2][9] = 0.0;  we[3][9] = (fx1*(Y2-Y1)-fy1*(X2-X1))/C/h3;
  	we[4][9] = 0.0;  we[5][9] = 0.0;  we[6][9] = (fx2*(Y2-Y1)-fy2*(X2-X1))/C/h3;
  	we[7][9] = 0.0;  we[8][9] = 0.0;  we[9][9] = (fx3*(Y2-Y1)-fy3*(X2-X1))/C/h3;
 
  	/* Effort elementaire place dans l'espace*/
  	base1( -betaa, 2, -alpha,  3,  9, wae);
  	/* Matrice elementaire placee dans l'espace*/
  	base9( -betaa, 2, -alpha,  3,  9, we);
  	
	/*
	if (elem == 232)
		{
		imprmatreel3( 1, 9, 1,  9,  we, 10);
		imprvectreel(9, wae);
		}
	*/


	}
	
	
void calcul_lmn_hexa(int elem)
	{
	/*calcul des longueur l m n de chaque triangle elem*/
	
	double XX1,XX2,XX3,YY1,YY2,YY3,dist,hh,dist_12,dist_23,dist_31,aa,bb,orient, hdirx,hdiry,Q1x,Q1y,Q2x,Q2y,Q3x,Q3y;	
	double Px,Py,Qx,Qy,TM,TN,TL;
	
	/*seuil de convergence sur les efforts et nb maxi d iterations*/
	seuil = 1e-10;
	limite_compteur = 100;
	
	/*printf("elem = %d ",elem);
	printf("nbiter = %d \n",nbiter);*/
	/*coelem : coordonnees de l element triangulaire*/
	/*Ux Uy (Vx, Vy) : coordonnees filaires de la maille*/

	Ux = -((V3-V1)*(coelem[3]-coelem[1])-(V2-V1)*(coelem[5]-coelem[1]))/deno;
	Vx =  ((U3-U1)*(coelem[3]-coelem[1])-(U2-U1)*(coelem[5]-coelem[1]))/deno;
	Uy = -((V3-V1)*(coelem[4]-coelem[2])-(V2-V1)*(coelem[6]-coelem[2]))/deno;
	Vy =  ((U3-U1)*(coelem[4]-coelem[2])-(U2-U1)*(coelem[6]-coelem[2]))/deno;
	
	/*coordonnees des 3 extremites des fils l,m etn, ou encore centres des 3 cercles*/
	/*le fil m va vers XX1,YY1*/
	/*le fil n va vers XX2,YY2*/
	/*le fil l va vers XX3,YY3*/
	XX1 = 0;		YY1 = 0;
	XX2 = (Ux+Vx)/2.0;	YY2 = (Uy+Vy)/2.0;
	XX3 = Vx;		YY3 = Vy;

	/*if ((elem == 5) && (nbiter > 12))
		{
		printf("elem = %d  ",elem);		
		printf("XX1 %lf  ",XX1);	printf("YY1 %lf  ",YY1);
		printf("XX2 %lf  ",XX2);	printf("YY2 %lf  ",YY2);
		printf("XX3 %lf  ",XX3);	printf("YY3 %lf  \n",YY3);
		}*/
 	
	test = 0;
	if (test == 0)
		{
		/*l tendu, m tendu, n tendu*/
       		cas = 1;
		EAl=Surf_Hexa[elem].raideur_traction_l;	EAm=Surf_Hexa[elem].raideur_traction_m; EAn=Surf_Hexa[elem].raideur_traction_n;	  
		mx = XX1-(XX1+XX2+XX3)/3.0;	my = YY1-(YY1+YY2+YY3)/3.0;
		calcul_lmn_iteratif(elem);
		if((l > lo - 0.0) && (m >= mo - seuil * mo / EAm) && (n >= no - seuil * no / EAn) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
		}
	if (test == 0)
		{
		/*l compresse, m tendu, n tendu*/
       		EAl=Surf_Hexa[elem].raideur_compression_l; EAm=Surf_Hexa[elem].raideur_traction_m; EAn=Surf_Hexa[elem].raideur_traction_n;	  
		dist = sqrt((XX2-XX1)*(XX2-XX1)+(YY2-YY1)*(YY2-YY1));
		if (dist<mo+no)
			{
			hh = sqrt(mo*mo-((dist*dist-no*no+mo*mo)/2.0/dist)*((dist*dist-no*no+mo*mo)/2.0/dist));
			Qx = XX1+ (dist*dist-no*no+mo*mo)/2.0/dist * (XX2-XX1) / dist;
			Qy = YY1+ (dist*dist-no*no+mo*mo)/2.0/dist * (YY2-YY1) / dist;
			if (((XX2-XX1)*(YY3-YY1)-(YY2-YY1)*(XX3-XX1)) > 0.0)
				{
				cas = 211;
				mx = XX1 - Qx + hh * (YY1-YY2) / dist;
				my = YY1 - Qy + hh * (XX2-XX1) / dist;
				calcul_lmn_iteratif(elem);
				if((l <= lo + 0.0) && (m >= mo - seuil * mo / EAm) && (n >= no - seuil * no / EAn) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			else
				{
				cas = 212;
				mx = XX1 - Qx - hh * (YY1-YY2) / dist;
				my = YY1 - Qy - hh * (XX2-XX1) / dist;
				calcul_lmn_iteratif(elem);
				if((l <= lo + 0.0) && (m >= mo - seuil * mo / EAm) && (n >= no - seuil * no / EAn) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			}
		else
			{
			cas = 22;
			m = (EAm-EAn+EAn*dist/no)/(EAm/mo+EAn/no);
			n = dist - m;
			Px = XX1-m*(XX1-XX2)/dist;				Py = YY1-m*(YY1-YY2)/dist;
			l = sqrt((XX3-Px)*(XX3-Px)+(YY3-Py)*(YY3-Py));
			TM = (m-mo)/mo*EAm;				TN = (n-no)/no*EAn;				TL = (l-lo)/lo*EAl;
			hh = TL/dist/l*(XX3*(YY1-YY2)+YY3*(XX2-XX1))/(TL/l+TM/m+TN/n);
			mx = m*(XX1-XX2)/dist;				my = m*(YY1-YY2)/dist;
			calcul_lmn_iteratif(elem);
			if((l <= lo + 0.0) && (m >= mo - seuil * mo / EAm) && (n >= no - seuil * no / EAn) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
			}
		}
		
	if (test == 0)		
		{
		/*l tendu, m compresse, n tendu*/
       		EAl=Surf_Hexa[elem].raideur_traction_l;	EAm=Surf_Hexa[elem].raideur_compression_m; EAn=Surf_Hexa[elem].raideur_traction_n;	  
		dist = sqrt((XX3-XX2)*(XX3-XX2)+(YY3-YY2)*(YY3-YY2));
		if (dist<no+lo)
			{
			hh = sqrt(no*no-((dist*dist-lo*lo+no*no)/2.0/dist)*((dist*dist-lo*lo+no*no)/2.0/dist));
			Qx = XX2 + (dist*dist-lo*lo+no*no)/2.0/dist * (XX3-XX2) / dist;
			Qy = YY2 + (dist*dist-lo*lo+no*no)/2.0/dist * (YY3-YY2) / dist;
			if (((XX3-XX2)*(YY1-YY2)-(YY3-YY2)*(XX1-XX2)) > 0.0)
				{
				cas = 311;
				mx = XX1 - Qx + hh * (YY2-YY3) / dist;
				my = YY1 - Qy + hh * (XX3-XX2) / dist;
				calcul_lmn_iteratif(elem);
				if((l > lo - 0.0) && (m <= mo + 0.0) && (n > no - 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			else
				{
				cas = 312;
				mx = XX1 - Qx - hh * (YY2-YY3) / dist;
				my = YY1 - Qy - hh * (XX3-XX2) / dist;
				calcul_lmn_iteratif(elem);
				if((l > lo - 0.0) && (m <= mo + 0.0) && (n > no - 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			}
		else
			{
			cas = 32;
			n = (EAn-EAl+EAl*dist/lo)/(EAn/no+EAl/lo);
			l = dist - n;
			Px = XX2-n*(XX2-XX3)/dist;				Py = YY2-n*(YY2-YY3)/dist;
			m = sqrt((XX1-Px)*(XX1-Px)+(YY1-Py)*(YY1-Py));
			TM = (m-mo)/mo*EAm;				TN = (n-no)/no*EAn;				TL = (l-lo)/lo*EAl;
			hh = TM/dist/m*(XX1*(YY2-YY3)+YY1*(XX3-XX2))/(TM/m+TN/n+TL/l);
			mx = XX1-XX2-n*(XX3-XX2)/dist;			my = YY1-YY2-n*(YY3-YY2)/dist;
			calcul_lmn_iteratif(elem);
			if((l > lo - 0.0) && (m <= mo + 0.0) && (n > no - 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
			}
		}
			
	if (test == 0)		
		{
		/*l tendu, m tendu, n compresse*/
       		EAl=Surf_Hexa[elem].raideur_traction_l;	EAm=Surf_Hexa[elem].raideur_traction_m;	EAn=Surf_Hexa[elem].raideur_compression_n;	  
		dist = sqrt((XX1-XX3)*(XX1-XX3)+(YY1-YY3)*(YY1-YY3));
		if (dist<lo+mo)
			{
			hh = sqrt(lo*lo-((dist*dist-mo*mo+lo*lo)/2.0/dist)*((dist*dist-mo*mo+lo*lo)/2.0/dist));
			Qx = XX3 + (dist*dist-mo*mo+lo*lo)/2.0/dist * (XX1-XX3) / dist;
			Qy = YY3 + (dist*dist-mo*mo+lo*lo)/2.0/dist * (YY1-YY3) / dist;
			if (((XX3-XX2)*(YY1-YY2)-(YY3-YY2)*(XX1-XX2)) > 0.0)
				{
				cas = 411;
				mx = XX1 - Qx + hh * (YY3-YY1) / dist;
				my = YY1 - Qy + hh * (XX1-XX3) / dist;
				calcul_lmn_iteratif(elem);
				if((l > lo - 0.0) && (m > mo - 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			else
				{
				cas = 412;
				mx = XX1 - Qx - hh * (YY3-YY1) / dist;
				my = YY1 - Qy - hh * (XX1-XX3) / dist;
				calcul_lmn_iteratif(elem);
				if((l > lo - 0.0) && (m > mo - 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			}
		else
			{
			cas = 42;
			l = (EAl-EAm+EAm*dist/mo)/(EAl/lo+EAm/mo);
			m = dist - l;
			Px = XX3-l*(XX3-XX1)/dist;			Py = YY3-l*(YY3-YY1)/dist;
			n = sqrt((XX2-Px)*(XX2-Px)+(YY2-Py)*(YY2-Py));
			TM = (m-mo)/mo*EAm;				TN = (n-no)/no*EAn;				TL = (l-lo)/lo*EAl;
			hh = TN/dist/n*(XX2*(YY3-YY1)+YY2*(XX1-XX3))/(TN/n+TL/l+TM/m);
			/*mx = XX3-XX1+l*(XX3-XX1)/dist;			my = YY3-YY1+l*(YY3-YY1)/dist;*/
			mx = -l*(XX3-XX1)/dist;				my = -l*(YY3-YY1)/dist;
			/*if (elem == 7)
				{
				printf("elem = %d  ",elem);		
				printf("XX1 %lf  ",XX1);	printf("YY1 %lf  ",YY1);
				printf("XX2 %lf  ",XX2);	printf("YY2 %lf  ",YY2);
				printf("XX3 %lf  ",XX3);	printf("YY3 %lf  \n",YY3);
  				printf("l = %15.5lf m = %15.5lf n = %15.5lf ",l,m,n);
  				printf("mx my = %10.4lf %10.4lf ",mx,my);
  				printf("Px Py = %10.4lf %10.4lf ",Px,Py);
  				printf("TM TN = %10.4lf %10.4lf ",TM,TN);
  				printf("hh = %10.4lf ",hh);
  				printf("dist = %10.4lf ",dist);
				printf("casssssssssssssssssssss %5d  \n",cas);
				}*/
			calcul_lmn_iteratif(elem);
			if((l > lo - 0.0) && (m > mo - 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
			/*if (elem == 7)
				{
				printf("elem = %d  ",elem);		
				printf("XX1 %lf  ",XX1);	printf("YY1 %lf  ",YY1);
				printf("XX2 %lf  ",XX2);	printf("YY2 %lf  ",YY2);
				printf("XX3 %lf  ",XX3);	printf("YY3 %lf  \n",YY3);
  				printf("l = %15.5lf m = %15.5lf n = %15.5lf ",l,m,n);
  				printf("mx my = %10.4lf %10.4lf ",mx,my);
  				printf("Px Py = %10.4lf %10.4lf ",Px,Py);
  				printf("TM TN = %10.4lf %10.4lf ",TM,TN);
  				printf("hh = %10.4lf ",hh);
  				printf("dist = %10.4lf ",dist);
				printf("cas %5d  \n",cas);
				exit(0);
				}*/
			}
		}
					
	if (test == 0)		
		{
		cas = 5;
		/*ici on cherche le barycentre de l ntersection des 3 cercles de rayons mo lo et no
		l intersection de 2 cercles est soit 0 1 ou 2 points ici on se place dans le cas de 2 points
		et on prend le point le plus proche du sommet oppose: par ex si on cherche l intersection des cercles de centre
		1 et 2 on trouve 2 points on prend le plus proche du sommet 3 cf. if (orient > 0)*/
		/*l compresse, m compresse, n compresse*/
       		EAl=Surf_Hexa[elem].raideur_compression_l; EAm=Surf_Hexa[elem].raideur_compression_m; EAn=Surf_Hexa[elem].raideur_compression_n;

		dist_12 = sqrt((XX2-XX1)*(XX2-XX1)+(YY2-YY1)*(YY2-YY1));
		aa = (mo*mo-no*no+dist_12*dist_12)/2.0/dist_12;
		bb = dist_12 - aa;
		Px = XX1 + (XX2-XX1) * aa / dist_12;
		Py = YY1 + (YY2-YY1) * aa / dist_12;
		orient = ((XX2-XX1)*(YY3-YY2))-((YY2-YY1)*(XX3-XX2));
		if (orient > 0.0)
			{
			hdirx = -(YY2-YY1) / dist_12;
			hdiry = +(XX2-XX1) / dist_12;
			}
		else
			{
			hdirx = +(YY2-YY1) / dist_12;
			hdiry = -(XX2-XX1) / dist_12;
			}
		hh = sqrt(mo*mo-aa*aa);
		Q3x = Px + hh * hdirx;
		Q3y = Py + hh * hdiry;
		
		dist_23 = sqrt((XX3-XX2)*(XX3-XX2)+(YY3-YY2)*(YY3-YY2));
		aa = (no*no-lo*lo+dist_23*dist_23)/2.0/dist_23;
		bb = dist_23 - aa;
		Px = XX2 + (XX3-XX2) * aa / dist_23;
		Py = YY2 + (YY3-YY2) * aa / dist_23;
		orient = ((XX2-XX1)*(YY3-YY2))-((YY2-YY1)*(XX3-XX2));
		if (orient > 0.0)
			{
			hdirx = -(YY3-YY2) / dist_23;
			hdiry = +(XX3-XX2) / dist_23;
			}
		else
			{
			hdirx = +(YY3-YY2) / dist_23;
			hdiry = -(XX3-XX2) / dist_23;
			}
		hh = sqrt(no*no-aa*aa);
		Q1x = Px + hh * hdirx;
		Q1y = Py + hh * hdiry;
		
		dist_31 = sqrt((XX1-XX3)*(XX1-XX3)+(YY1-YY3)*(YY1-YY3));
		aa = (lo*lo-mo*mo+dist_31*dist_31)/2.0/dist_31;
		bb = dist_31 - aa;
		Px = XX3 + (XX1-XX3) * aa / dist_31;
		Py = YY3 + (YY1-YY3) * aa / dist_31;
		orient = ((XX2-XX1)*(YY3-YY2))-((YY2-YY1)*(XX3-XX2));
		if (orient > 0.0)
			{
			hdirx = -(YY1-YY3) / dist_31;
			hdiry = +(XX1-XX3) / dist_31;
			}
		else
			{
			hdirx = +(YY1-YY3) / dist_31;
			hdiry = -(XX1-XX3) / dist_31;
			}
		hh = sqrt(lo*lo-aa*aa);
		Q2x = Px + hh * hdirx;
		Q2y = Py + hh * hdiry;
		mx = -(Q1x + Q2x + Q3x) / 3.0;
		my = -(Q1y + Q2y + Q3y) / 3.0;
		calcul_lmn_iteratif(elem);
		if((l <= lo + 0.0) && (m <= mo + 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
		}
					
	if (test == 0)		
		{
		cas = 51;
		/*ici on cherche le barycentre Px, Py des intersections des 2 cercles de rayons mo et no de sommets 1 & 2*/
		/*l compresse, m compresse, n compresse*/
       		EAl=Surf_Hexa[elem].raideur_compression_l; EAm=Surf_Hexa[elem].raideur_compression_m; EAn=Surf_Hexa[elem].raideur_compression_n;
		dist_12 = sqrt((XX2-XX1)*(XX2-XX1)+(YY2-YY1)*(YY2-YY1));
		aa = (mo*mo-no*no+dist_12*dist_12)/2.0/dist_12;
		bb = dist_12 - aa;
		Px = XX1 + (XX2-XX1) * aa / dist_12;
		Py = YY1 + (YY2-YY1) * aa / dist_12;
		mx = -Px;	my = -Py;
		calcul_lmn_iteratif(elem);
		if((l <= lo + 0.0) && (m <= mo + 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
		}
					
	if (test == 0)		
		{
		cas = 52;
		/*ici on cherche le barycentre Px, Py des intersections des 2 cercles de rayons no et lo de sommets 2 & 3*/
		/*l compresse, m compresse, n compresse*/
       		EAl=Surf_Hexa[elem].raideur_compression_l; EAm=Surf_Hexa[elem].raideur_compression_m; EAn=Surf_Hexa[elem].raideur_compression_n;
		dist_23 = sqrt((XX3-XX2)*(XX3-XX2)+(YY3-YY2)*(YY3-YY2));
		aa = (no*no-lo*lo+dist_23*dist_23)/2.0/dist_23;
		bb = dist_23 - aa;
		Px = XX2 + (XX3-XX2) * aa / dist_23;
		Py = YY2 + (YY3-YY2) * aa / dist_23;
		mx = -Px;	my = -Py;
		calcul_lmn_iteratif(elem);
		if((l <= lo + 0.0) && (m <= mo + 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
		}
					
	if (test == 0)		
		{
		cas = 53;
		/*ici on cherche le barycentre Px, Py des intersections des 2 cercles de rayons lo et mo de sommets 3 & 1*/
		/*l compresse, m compresse, n compresse*/
       		EAl=Surf_Hexa[elem].raideur_compression_l; EAm=Surf_Hexa[elem].raideur_compression_m; EAn=Surf_Hexa[elem].raideur_compression_n;
		dist_31 = sqrt((XX1-XX3)*(XX1-XX3)+(YY1-YY3)*(YY1-YY3));
		aa = (lo*lo-mo*mo+dist_31*dist_31)/2.0/dist_31;
		bb = dist_31 - aa;
		Px = XX3 + (XX1-XX3) * aa / dist_31;
		Py = YY3 + (YY1-YY3) * aa / dist_31;
		mx = -Px;	my = -Py;
		calcul_lmn_iteratif(elem);
		if((l <= lo + 0.0) && (m <= mo + 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
		}
					
	if (test == 0)		
		{
		cas = 6;
		/*l tendu, m compresse, n compresse*/
       		EAl=Surf_Hexa[elem].raideur_traction_l; EAm=Surf_Hexa[elem].raideur_compression_m; EAn=Surf_Hexa[elem].raideur_compression_n;	  
		dist = sqrt((XX3-XX2)*(XX3-XX2)+(YY3-YY2)*(YY3-YY2));
		n = (EAn-EAl+EAl*dist/lo)/(EAn/no+EAl/lo);
		mx = XX1-XX2+n*(XX2-XX3)/dist;				my = YY1-YY2+n*(YY2-YY3)/dist;
		calcul_lmn_iteratif(elem);
		if((l > lo - 0.0) && (m <= mo + 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
		}
	if (test == 0)		
		{
		/*l tendu, m compresse, n compresse*/
       		EAl=Surf_Hexa[elem].raideur_traction_l;	EAm=Surf_Hexa[elem].raideur_compression_m; EAn=Surf_Hexa[elem].raideur_compression_n;
		dist = sqrt((XX2-XX1)*(XX2-XX1)+(YY2-YY1)*(YY2-YY1));
		if (dist<mo+no)
			{
			hh = sqrt(mo*mo-((dist*dist-no*no+mo*mo)/2.0/dist)*((dist*dist-no*no+mo*mo)/2.0/dist));
			Qx = XX1+ (dist*dist-no*no+mo*mo)/2.0/dist * (XX2-XX1) / dist;
			Qy = YY1+ (dist*dist-no*no+mo*mo)/2.0/dist * (YY2-YY1) / dist;
			if (((XX2-XX1)*(YY3-YY1)-(YY2-YY1)*(XX3-XX1)) > 0.0)
				{
				cas = 611;
				mx = XX1 - Qx + hh * (YY1-YY2) / dist;
				my = YY1 - Qy + hh * (XX2-XX1) / dist;
				calcul_lmn_iteratif(elem);
				if((l > lo - 0.0) && (m <= mo + 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			else
				{
				cas = 612;
				mx = XX1 - Qx - hh * (YY1-YY2) / dist;
				my = YY1 - Qy - hh * (XX2-XX1) / dist;
				calcul_lmn_iteratif(elem);
				if((l > lo - 0.0) && (m <= mo + 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			}
		else
			{
			cas = 62;
			m = (EAm-EAn+EAn*dist/no)/(EAm/mo+EAn/no);
			n = dist - m;
			Px = XX1-m*(XX1-XX2)/dist;				Py = YY1-m*(YY1-YY2)/dist;
			l = sqrt((XX3-Px)*(XX3-Px)+(YY3-Py)*(YY3-Py));
			TM = (m-mo)/mo*EAm;				TN = (n-no)/no*EAn;				TL = (l-lo)/lo*EAl;
			hh = TL/dist/l*(XX3*(YY1-YY2)+YY3*(XX2-XX1))/(TL/l+TM/m+TN/n);
			mx = XX1-XX1+m*(XX1-XX2)/dist;			my = YY1-YY1+m*(YY1-YY2)/dist;
			calcul_lmn_iteratif(elem);
			if((l > lo - 0.0) && (m <= mo + 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
			}
		}
		
					
	if (test == 0)		
		{
		cas = 7;
		/*l compresse, m tendu, n compresse*/
       		EAl=Surf_Hexa[elem].raideur_compression_l; EAm=Surf_Hexa[elem].raideur_traction_m; EAn=Surf_Hexa[elem].raideur_compression_n;
		dist = sqrt((XX3-XX2)*(XX3-XX2)+(YY3-YY2)*(YY3-YY2));
		n = (EAn-EAl+EAl*dist/lo)/(EAn/no+EAl/lo);
		mx = XX1-XX2+n*(XX2-XX3)/dist;				my = YY1-YY2+n*(YY2-YY3)/dist;
		calcul_lmn_iteratif(elem);
		if((l <= lo + 0.0) && (m > mo - 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
		}			
	if (test == 0)		
		{
		/*l compresse, m tendu, n compresse*/
       		EAl=Surf_Hexa[elem].raideur_compression_l; EAm=Surf_Hexa[elem].raideur_traction_m; EAn=Surf_Hexa[elem].raideur_compression_n;
		dist = sqrt((XX3-XX2)*(XX3-XX2)+(YY3-YY2)*(YY3-YY2));
		if (dist<no+lo)
			{
			/*ici la dist entre 2&3 est < no+lo*/
			hh = sqrt(no*no-((dist*dist-lo*lo+no*no)/2.0/dist)*((dist*dist-lo*lo+no*no)/2.0/dist));
			Qx = XX2 + (dist*dist-lo*lo+no*no)/2.0/dist * (XX3-XX2) / dist;
			Qy = YY2 + (dist*dist-lo*lo+no*no)/2.0/dist * (YY3-YY2) / dist;
			/*(XX3-XX2)*(YY1-YY2)-(YY3-YY2)*(XX1-XX2)  est la surface orientee du triangle le signe >0 ou <=0 donne son orientation*/
			if (((XX3-XX2)*(YY1-YY2)-(YY3-YY2)*(XX1-XX2)) > 0.0)
				{
				cas = 711;
				mx = XX1 - Qx + hh * (YY2-YY3) / dist;
				my = YY1 - Qy + hh * (XX3-XX2) / dist;
				calcul_lmn_iteratif(elem);
				if((l <= lo + 0.0) && (m > mo - 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			else
				{
				cas = 712;
				mx = XX1 - Qx - hh * (YY2-YY3) / dist;
				my = YY1 - Qy - hh * (XX3-XX2) / dist;
				calcul_lmn_iteratif(elem);
				if((l <= lo + 0.0) && (m > mo - 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			}
		else
			{
			cas = 72;
			n = (EAn-EAl+EAl*dist/lo)/(EAn/no+EAl/lo);
			l = dist - n;
			Px = XX2-n*(XX2-XX3)/dist;				Py = YY2-n*(YY2-YY3)/dist;
			m = sqrt((XX1-Px)*(XX1-Px)+(YY1-Py)*(YY1-Py));
			TM = (m-mo)/mo*EAm;				TN = (n-no)/no*EAn;				TL = (l-lo)/lo*EAl;
			hh = TM/dist/m*(XX1*(YY2-YY3)+YY1*(XX3-XX2))/(TM/m+TN/n+TL/l);
			mx = XX2-XX1+n*(XX2-XX3)/dist;			my = YY2-YY1+n*(YY2-YY3)/dist;
			calcul_lmn_iteratif(elem);
			if((l <= lo + 0.0) && (m > mo - 0.0) && (n <= no + 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
			}
		}
			
					
	if (test == 0)		
		{
		cas = 8;
		/*l compresse, m compresse, n tendu*/
       		EAl=Surf_Hexa[elem].raideur_compression_l; EAm=Surf_Hexa[elem].raideur_compression_m; EAn=Surf_Hexa[elem].raideur_traction_n;
		dist = sqrt((XX1-XX3)*(XX1-XX3)+(YY1-YY3)*(YY1-YY3));
		l = (EAl-EAm+EAm*dist/mo)/(EAl/lo+EAm/mo);
		mx = XX1-XX3+l*(XX3-XX1)/dist;				my = YY1-YY3+l*(YY3-YY1)/dist;
		calcul_lmn_iteratif(elem);
		if((l <= lo + 0.0) && (m <= mo + 0.0) && (n > no - 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
		}									
	if (test == 0)		
		{
		/*l compresse, m compresse, n tendu*/
       		EAl=Surf_Hexa[elem].raideur_compression_m; EAm=Surf_Hexa[elem].raideur_compression_m; EAn=Surf_Hexa[elem].raideur_traction_n;
		dist = sqrt((XX1-XX3)*(XX1-XX3)+(YY1-YY3)*(YY1-YY3));
		if (dist<lo+mo)
			{
			hh = sqrt(lo*lo-((dist*dist-mo*mo+lo*lo)/2.0/dist)*((dist*dist-mo*mo+lo*lo)/2.0/dist));
			Qx = XX3 + (dist*dist-mo*mo+lo*lo)/2.0/dist * (XX1-XX3) / dist;
			Qy = YY3 + (dist*dist-mo*mo+lo*lo)/2.0/dist * (YY1-YY3) / dist;
			if (((XX3-XX2)*(YY1-YY2)-(YY3-YY2)*(XX1-XX2)) > 0.0)
				{
				cas = 811;
				mx = XX1 - Qx + hh * (YY3-YY1) / dist;
				my = YY1 - Qy + hh * (XX1-XX3) / dist;
				calcul_lmn_iteratif(elem);
				if((l <= lo + 0.0) && (m <= mo + 0.0) && (n > no - 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			else
				{
				cas = 812;
				mx = XX1 - Qx - hh * (YY3-YY1) / dist;
				my = YY1 - Qy - hh * (XX1-XX3) / dist;
				calcul_lmn_iteratif(elem);
				if((l <= lo + 0.0) && (m <= mo + 0.0) && (n > no - 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
				}
			}
		else
			{
			cas = 82;
			l = (EAl-EAm+EAm*dist/mo)/(EAl/lo+EAm/mo);
			m = dist - l;
			Px = XX3-l*(XX3-XX1)/dist;				Py = YY3-l*(YY3-YY1)/dist;
			n = sqrt((XX2-Px)*(XX2-Px)+(YY2-Py)*(YY2-Py));
			TM = (m-mo)/mo*EAm;				TN = (n-no)/no*EAn;				TL = (l-lo)/lo*EAl;
			hh = TN/dist/n*(XX2*(YY3-YY1)+YY2*(XX1-XX3))/(TN/n+TL/l+TM/m);
			mx = XX3-XX1+l*(XX3-XX1)/dist;			my = YY3-YY1+l*(YY3-YY1)/dist;
			calcul_lmn_iteratif(elem);
			if((l <= lo + 0.0) && (m <= mo + 0.0) && (n > no - 0.0) && ((max <= seuil) || (compteur >= limite_compteur))) test=1;
			}
		}
					
	if (test == 0)		
		{
		printf("erreur dans l elem = %d selon le cas %d \n",elem,cas);
		printf("wf =[ %10.6lf %10.6lf 0 %10.6lf %10.6lf 0 %10.6lf %10.6lf 0 ];\n",coelem[1],coelem[2],coelem[3],coelem[4],coelem[5],coelem[6]);
		printf("U1 = %10.2le; V1 = %10.2le; U2 = %10.2le; V2 = %10.2le;  U3 = %10.2le; V3 = %10.2le; \n",U1,V1,U2,V2,U3,V3);
		printf("lo = %10.2le; mo = %10.2le; no = %10.2le; \n",lo,mo,no);
		exit(0);
		}
	}

	
void calcul_lmn_iteratif(int elem)
	{
	double F1,F2,M11,M22,M12,M21,ha,hb,EAlo,EAmo,EAno;
	
	EAlo = EAl/lo/lo;
	EAmo = EAm/mo/mo;
	EAno = EAn/no/no;
		
	compteur = 0;
	/*On calcule les composantes lx, ly mx, my, nx, ny par une methode iterative car on n'a pas un systeme lineaire.*/
	
	do 
		{
		compteur += 1;
		lx=(Vx+mx);		ly=(Vy+my);
		nx=((Ux+Vx)/2.0+mx);	ny=((Uy+Vy)/2.0+my);
		l=sqrt(lx*lx+ly*ly);	m=sqrt(mx*mx+my*my);	n=sqrt(nx*nx+ny*ny);

		/* F1 et F2 sont les 2 equations a 2 inconnues que l'on essaie de resoudre (cf page 29 du rapport de cgallee).*/
		F1=lx*(l-lo)*EAlo+mx*(m-mo)*EAmo+nx*(n-no)*EAno;
		F2=ly*(l-lo)*EAlo+my*(m-mo)*EAmo+ny*(n-no)*EAno;
	
		max=sqrt(F1*F1 + F2*F2);
		if (max > seuil)
			{
			/*(cf page 30 du rapport de cgallee)*/
			M11 = -((l-lo)*EAlo+lx*(lx/l)*EAlo+(m-mo)*EAmo+mx*(mx/m)*EAmo+(n-no)*EAno+nx*(nx/n)*EAno);
			M22 = -((l-lo)*EAlo+ly*(ly/l)*EAlo+(m-mo)*EAmo+my*(my/m)*EAmo+(n-no)*EAno+ny*(ny/n)*EAno);
			M12 = -(            lx*(ly/l)*EAlo            +mx*(my/m)*EAmo            +nx*(ny/n)*EAno);
			M21 = -(            ly*(lx/l)*EAlo            +my*(mx/m)*EAmo            +ny*(nx/n)*EAno);
	
			/*ha et hb variation de mx et my(cf page 30 du rapport de cgallee)*/
			ha=(M22*F1-M12*F2)/(M11*M22-M12*M21);	hb=(F1*M21-F2*M11)/(M12*M21-M11*M22);
			mx=mx+ha;	my=my+hb;
			}
		/*if (elem == 7)
			{
  			printf("max = %15.10lf ",max);
  			printf("mx my = %10.4lf %10.4lf ",mx,my);
  			printf("EA = %10.4lf %10.4lf %10.4lf ",EAlo,EAmo,EAno);
			printf("cas %5d  \n",cas);
			}*/
		}
	while((max > seuil) && (compteur < 100));
	lx=(Vx+mx);		ly=(Vy+my);
	nx=((Ux+Vx)/2.0+mx);	ny=((Uy+Vy)/2.0+my);
	l=sqrt(lx*lx+ly*ly);	m=sqrt(mx*mx+my*my);	n=sqrt(nx*nx+ny*ny);
	
	/*if ((elem == 5) && (nbiter > 12))
		{
  		printf("EAlmn = %15.0lf %15.0lf %15.0lf ",EAlo,EAmo,EAno);
  		printf("mx my = %10.4lf %10.4lf ",mx,my);
		printf("cas %5d  \n",cas);
		}
	if (nbiter > 20) exit(0);*/

	/*verification de l elasticite des fils*/
	/*test=0;
	Tmax[cas]=max;
	Tcompteur[cas]=compteur;
	Tl[cas]=l-lo;
	Tm[cas]=m-mo;
	Tn[cas]=n-no;*/
	}




