#define PRINCIPAL 0
#include "4c19.h"

void etirement5()
	{
	/* 
	Raideurs kwe et efforts wae d une nappe de filet mailles losange, dus a l'elasticite des fils, dans le plan XOY.
   	Le module d'elasticite des fils est differents en traction et en compression.
   	Il est beaucoup plus faible en compression
   	*/

  	double u1,u2,u3,v1,v2,v3;
  	double EAu,EAv,n0,ff[10],KWE[10][10],kwe[10][10];
  	double S,XX1,YY1,ZZ1,XX2,YY2,ZZ2,XX3,YY3,ZZ3;
  	double nx,ny,nz,mx,my,mz,n,m,delta_x;
  	double NX,NY,NZ,MX,MY,MZ,N,M;
  	double Dnx[13],Dny[13],Dnz[13],Dmx[13],Dmy[13],Dmz[13],Dnn[13],Dmm[13];
  	double DNX[13],DNY[13],DNZ[13],DMX[13],DMY[13],DMZ[13],DNN[13],DMM[13];
  	int z1,z2,z3,zi,zu,zv,elem,zl,zk;
  	
 	
  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
		{
  		/*for (elem = 131; elem<= 131; elem++)*/
		/*numero des coordonnees x des sommets 1 2 et 3 du triangle*/
		z1 = yc(elem,1);  z2 = yc(elem,4);  z3 = yc(elem,7);
				
  		n0 = Surface[elem].lgrepos;    /*longueur au repos d une maille*/
  		
  		u1 =   Surface[elem].lon[1] + Surface[elem].lon[2] - Surface[elem].lon[2] - Surface[elem].lon[1]; 
  		u2 =   Surface[elem].lon[3] + Surface[elem].lon[4] - Surface[elem].lon[2] - Surface[elem].lon[1]; 
  		u3 =   Surface[elem].lon[5] + Surface[elem].lon[6] - Surface[elem].lon[2] - Surface[elem].lon[1];  
  		v1 = - Surface[elem].lon[1] + Surface[elem].lon[2] - Surface[elem].lon[2] + Surface[elem].lon[1];  
  		v2 = - Surface[elem].lon[3] + Surface[elem].lon[4] - Surface[elem].lon[2] + Surface[elem].lon[1];  
  		v3 = - Surface[elem].lon[5] + Surface[elem].lon[6] - Surface[elem].lon[2] + Surface[elem].lon[1]; 
  		/* u1 : coordonnee du noeud 1 en nb de fils de direction u = 0.0*/
  		/* u2 : coordonnee du noeud 2 en nb de fils de direction u.*/
  		/* u3 : coordonnee du noeud 3 en nb de fils de direction u. */    
  		/* v1 : coordonnee du noeud 1 en nb de fils de direction v = 0.0*/
  		/* v2 : coordonnee du noeud 2 en nb de fils de direction v. */
  		/* v3 : coordonnee du noeud 3 en nb de fils de direction v. */

  		/*Allongement des mailles selon les direction X et Y*/

		S = ((u2-u1)*(v3-v1) - (u3-u1)*(v2-v1));
  		/* S = 1 * nb de fils dans le triangle = 2 * nb de fils u = 2 * nb de fils v = 4 * nb de mailles */
  		if( S == 0.0 ) 
			{
  			printf("ERREUR: changez les coordonnees U et V des sommets du triangle numero  %5.d", elem);
  			exit(0);
			}
  
  		/* (Xi,Yi) coordonnees cartesiennes dans le plan XOY du sommet i du triangle elem*/
             
  		/* nx : Coordonnees selon x d'un cote de maille (selon u )*/
  		/* ny : Coordonnees selon y d'un cote de maille (selon u )*/
  		/* nz : Coordonnees selon z d'un cote de maille (selon u )*/
  		/* mx : Coordonnees selon x d'un cote de maille (selon v )*/
  		/* my : Coordonnees selon y d'un cote de maille (selon v )*/
  		/* mz : Coordonnees selon z d'un cote de maille (selon v )*/

    		XX1 = wf[z1+0];    	YY1 = wf[z1+1];    	ZZ1 = wf[z1+2];
    		XX2 = wf[z2+0];    	YY2 = wf[z2+1];    	ZZ2 = wf[z2+2];
    		XX3 = wf[z3+0];    	YY3 = wf[z3+1];    	ZZ3 = wf[z3+2];
    		
      		/*TEST_debut
		delta_x = 0.000001;
		for( zu = 0 ; zu <= 10 ; zu++ )
      			{
      			if (zu == 1) XX1 =XX1 + delta_x;
      			if (zu == 2) YY1 =YY1 + delta_x;
      			if (zu == 3) ZZ1 =ZZ1 + delta_x;
      			if (zu == 4) XX2 =XX2 + delta_x;
      			if (zu == 5) YY2 =YY2 + delta_x;
      			if (zu == 6) ZZ2 =ZZ2 + delta_x;
      			if (zu == 7) XX3 =XX3 + delta_x;
      			if (zu == 8) YY3 =YY3 + delta_x;
      			if (zu == 9) ZZ3 =ZZ3 + delta_x;
      			TEST_fin*/
      		
  			nx =  (v3*(XX2-XX1) - v2*(XX3-XX1))/S;  	ny =  (v3*(YY2-YY1) - v2*(YY3-YY1))/S;  	nz =  (v3*(ZZ2-ZZ1) - v2*(ZZ3-ZZ1))/S;
  			mx =  (u2*(XX3-XX1) - u3*(XX2-XX1))/S;  	my =  (u2*(YY3-YY1) - u3*(YY2-YY1))/S;  	mz =  (u2*(ZZ3-ZZ1) - u3*(ZZ2-ZZ1))/S;
  
  			Surface[elem].nx = nx;  	Surface[elem].ny = ny;  	Surface[elem].nz = nz;
  			Surface[elem].mx = mx;  	Surface[elem].my = my;  	Surface[elem].mz = mz;
  			Surface[elem].n[1]= nx;		Surface[elem].n[2]= ny;		Surface[elem].n[3]= nz;
  			Surface[elem].m[1]= mx;		Surface[elem].m[2]= my;		Surface[elem].m[3]= mz;
  	
  			/* Allongement des mailles selon les direction u et v*/
  			n = sqrt(nx*nx + ny*ny + nz*nz);	Surface[elem].lg_tendue1 = n;
  			m = sqrt(mx*mx + my*my + mz*mz);	Surface[elem].lg_tendue2 = m;
	
  			/* EAu et EAv = Module d'elasticite*section du fil. C'est donne dans le fichier .don */
  			if (n >= n0) EAu = Surface[elem].raideur_traction;  	if (n <  n0) EAu = Surface[elem].raideur_compression;
  			if (m >= n0) EAv = Surface[elem].raideur_traction;  	if (m <  n0) EAv = Surface[elem].raideur_compression;
  	
  			/*compteur de fils en tension*/
			if (n >= n0) nb_u_tension = nb_u_tension + 1;
  			if (m >= n0) nb_v_tension = nb_v_tension + 1;

  			if(n <= 0.0 || m <= 0.0) 
				{
  				printf("Erreur, la longueur de la maille tendue est negative ou nulle dans l element %d\n",elem);
				printf("composante de n = %12.3lf %12.3lf %12.3lf   \n",Surface[elem].nx,Surface[elem].ny,Surface[elem].nz);
				printf("composante de m = %12.3lf %12.3lf %12.3lf   \n",Surface[elem].mx,Surface[elem].my,Surface[elem].mz);
    				printf("n = %20.3lf   \n",n);
    				printf("m = %20.3lf   \n",m);
    				printf("S = %20.5lf   \n",S);
  				if(n <= 0.0)	n = 0.5 * n0;
  				if(m <= 0.0)	m = 0.5 * n0;
				}
  			if(n0 <= 0.0) 
				{
  				printf("Erreur, la longueur de la maille au repos est negative ou nulle dans l element %d\n",elem);
				printf("composante de n = %12.3lf %12.3lf %12.3lf   \n",Surface[elem].nx,Surface[elem].ny,Surface[elem].nz);
				printf("composante de m = %12.3lf %12.3lf %12.3lf   \n",Surface[elem].mx,Surface[elem].my,Surface[elem].mz);
     				printf("n = %20.2lf   \n",n);
    				printf("m = %20.2lf   \n",m);
    				printf("maille au repos = %20.2lf   \n",n0);
 				exit(0);
				}
			Surface[elem].tension1 = EAu * (n-n0) / n0;
			Surface[elem].tension2 = EAv * (m-n0) / n0;

  			/* Efforts aux 3 noeuds, sommets du triangle.*/
  			wae[1] = EAu/2.0 *(v3-v2)*nx*(1/n0-1/n) + EAv/2.0 *(u2-u3)*mx*(1/n0-1/m);
  			wae[2] = EAu/2.0 *(v3-v2)*ny*(1/n0-1/n) + EAv/2.0 *(u2-u3)*my*(1/n0-1/m);
  			wae[3] = EAu/2.0 *(v3-v2)*nz*(1/n0-1/n) + EAv/2.0 *(u2-u3)*mz*(1/n0-1/m);
  			wae[4] = EAu/2.0 *(v1-v3)*nx*(1/n0-1/n) + EAv/2.0 *(u3-u1)*mx*(1/n0-1/m);
  			wae[5] = EAu/2.0 *(v1-v3)*ny*(1/n0-1/n) + EAv/2.0 *(u3-u1)*my*(1/n0-1/m);
  			wae[6] = EAu/2.0 *(v1-v3)*nz*(1/n0-1/n) + EAv/2.0 *(u3-u1)*mz*(1/n0-1/m);
  			wae[7] = EAu/2.0 *(v2-v1)*nx*(1/n0-1/n) + EAv/2.0 *(u1-u2)*mx*(1/n0-1/m);
  			wae[8] = EAu/2.0 *(v2-v1)*ny*(1/n0-1/n) + EAv/2.0 *(u1-u2)*my*(1/n0-1/m);
  			wae[9] = EAu/2.0 *(v2-v1)*nz*(1/n0-1/n) + EAv/2.0 *(u1-u2)*mz*(1/n0-1/m);
  			//printf("wae");
			//imprvectreel(9, wae);/**/
		
			/*energie d elongation par fil u = EAu * (n-n0) * (n-n0) / n0 / 2.0*/
			Surface[elem].energy_elastique = (EAu * (n-n0) * (n-n0) + EAv * (m-n0) * (m-n0)) * S / n0 / 4.0;
			
	 		//printf("S %8.3lf  E %8.3lf  Et %8.3lf\n",S,(EAu * (n-n0) * (n-n0) + EAv * (m-n0) * (m-n0)) / n0 / 2.0,Surface[elem].energy_elastique);
	 
  			/* Calcul des derivees partielles de nx par rapport a XX1(Dnx[1]), a YY1(Dnx[2])...*/
                
  			Dnx[1] = (v2-v3)/S;  Dnx[2] = 0.0;        Dnx[3] = 0.0;        Dnx[4] = (v3-v1)/S;  Dnx[5] = 0.0;        Dnx[6] = 0.0;        Dnx[7] = (v1-v2)/S;  Dnx[8] = 0.0;        Dnx[9] = 0.0;
  			Dny[1] = 0.0;        Dny[2] = (v2-v3)/S;  Dny[3] = 0.0;        Dny[4] = 0.0;        Dny[5] = (v3-v1)/S;  Dny[6] = 0.0;        Dny[7] = 0.0;        Dny[8] = (v1-v2)/S;  Dny[9] = 0.0;
  			Dnz[1] = 0.0;        Dnz[2] = 0.0;        Dnz[3] = (v2-v3)/S;  Dnz[4] = 0.0;        Dnz[5] = 0.0;        Dnz[6] = (v3-v1)/S;  Dnz[7] = 0.0;        Dnz[8] = 0.0;        Dnz[9] = (v1-v2)/S;
  			Dmx[1] = (u3-u2)/S;  Dmx[2] = 0.0;        Dmx[3] = 0.0;        Dmx[4] = (u1-u3)/S;  Dmx[5] = 0.0;        Dmx[6] = 0.0;        Dmx[7] = (u2-u1)/S;  Dmx[8] = 0.0;        Dmx[9] = 0.0;
  			Dmy[1] = 0.0;        Dmy[2] = (u3-u2)/S;  Dmy[3] = 0.0;        Dmy[4] = 0.0;        Dmy[5] = (u1-u3)/S;  Dmy[6] = 0.0;        Dmy[7] = 0.0;        Dmy[8] = (u2-u1)/S;  Dmy[9] = 0.0;
  			Dmz[1] = 0.0;        Dmz[2] = 0.0;        Dmz[3] = (u3-u2)/S;  Dmz[4] = 0.0;        Dmz[5] = 0.0;        Dmz[6] = (u1-u3)/S;  Dmz[7] = 0.0;        Dmz[8] = 0.0;        Dmz[9] = (u2-u1)/S;

  
  			/* Calcul des derivees partielles de n par rapport a XX1(Dasn), a YY1(Dbsn)...*/

			Dnn[1] = nx*(v2-v3)/n/S;  Dnn[2] = ny*(v2-v3)/n/S;  Dnn[3] = nz*(v2-v3)/n/S;  Dnn[4] = nx*(v3-v1)/n/S;  Dnn[5] = ny*(v3-v1)/n/S;  Dnn[6] = nz*(v3-v1)/n/S;  Dnn[7] = nx*(v1-v2)/n/S;  Dnn[8] = ny*(v1-v2)/n/S;  Dnn[9] = nz*(v1-v2)/n/S;
			Dmm[1] = mx*(u3-u2)/m/S;  Dmm[2] = my*(u3-u2)/m/S;  Dmm[3] = mz*(u3-u2)/m/S;  Dmm[4] = mx*(u1-u3)/m/S;  Dmm[5] = my*(u1-u3)/m/S;  Dmm[6] = mz*(u1-u3)/m/S;  Dmm[7] = mx*(u2-u1)/m/S;  Dmm[8] = my*(u2-u1)/m/S;  Dmm[9] = mz*(u2-u1)/m/S;

  			/* kwe : Matrice de raideur elementaire = -df/dx*/
  			/*
			kwe[1][1]([1][2], [1][3]...) = derivee de f1x par rapport a XX1( a YY1, A XX2...).
     			kwe[2][1]([2][2], [2][3]...) = derivee de f1y par rapport a XX1( a YY1, A XX2...)
     			kwe[3][1]([3][2], [3][3]...) = derivee de f1z par rapport a XX1( a YY1, A XX2...)
     			kwe[4][1]([4][2], [4][3]...) = derivee de f2x par rapport a XX1( a YY1, A XX2...)
     			kwe[5][1]([5][2], [5][3]...) = derivee de f2y par rapport a XX1( a YY1, A XX2...)
     			kwe[6][1]([6][2], [6][3]...) = derivee de f2z par rapport a XX1( a YY1, A XX2...)
     			kwe[7][1]([7][2], [7][3]...) = derivee de f3x par rapport a XX1( a YY1, A XX2...)
     			kwe[8][1]([8][2], [8][3]...) = derivee de f3y par rapport a XX1( a YY1, A XX2...)
     			kwe[9][1]([9][2], [9][3]...) = derivee de f3z par rapport a XX1( a YY1, A XX2...)
			*/
     	   	   
			for (zi = 1 ;zi <= 9 ;zi++ )
				{
				kwe[1][zi] = - EAu/2.0 * (v3-v2)*(Dnx[zi]*(1/n0-1/n)+nx*Dnn[zi]/n/n) - EAv/2.0 * (u2-u3)*(Dmx[zi]*(1/n0-1/m)+mx*Dmm[zi]/m/m);
				kwe[2][zi] = - EAu/2.0 * (v3-v2)*(Dny[zi]*(1/n0-1/n)+ny*Dnn[zi]/n/n) - EAv/2.0 * (u2-u3)*(Dmy[zi]*(1/n0-1/m)+my*Dmm[zi]/m/m);
				kwe[3][zi] = - EAu/2.0 * (v3-v2)*(Dnz[zi]*(1/n0-1/n)+nz*Dnn[zi]/n/n) - EAv/2.0 * (u2-u3)*(Dmz[zi]*(1/n0-1/m)+mz*Dmm[zi]/m/m);
				kwe[4][zi] = - EAu/2.0 * (v1-v3)*(Dnx[zi]*(1/n0-1/n)+nx*Dnn[zi]/n/n) - EAv/2.0 * (u3-u1)*(Dmx[zi]*(1/n0-1/m)+mx*Dmm[zi]/m/m);
				kwe[5][zi] = - EAu/2.0 * (v1-v3)*(Dny[zi]*(1/n0-1/n)+ny*Dnn[zi]/n/n) - EAv/2.0 * (u3-u1)*(Dmy[zi]*(1/n0-1/m)+my*Dmm[zi]/m/m);
				kwe[6][zi] = - EAu/2.0 * (v1-v3)*(Dnz[zi]*(1/n0-1/n)+nz*Dnn[zi]/n/n) - EAv/2.0 * (u3-u1)*(Dmz[zi]*(1/n0-1/m)+mz*Dmm[zi]/m/m);
				kwe[7][zi] = - EAu/2.0 * (v2-v1)*(Dnx[zi]*(1/n0-1/n)+nx*Dnn[zi]/n/n) - EAv/2.0 * (u1-u2)*(Dmx[zi]*(1/n0-1/m)+mx*Dmm[zi]/m/m);
				kwe[8][zi] = - EAu/2.0 * (v2-v1)*(Dny[zi]*(1/n0-1/n)+ny*Dnn[zi]/n/n) - EAv/2.0 * (u1-u2)*(Dmy[zi]*(1/n0-1/m)+my*Dmm[zi]/m/m);
				kwe[9][zi] = - EAu/2.0 * (v2-v1)*(Dnz[zi]*(1/n0-1/n)+nz*Dnn[zi]/n/n) - EAv/2.0 * (u1-u2)*(Dmz[zi]*(1/n0-1/m)+mz*Dmm[zi]/m/m);
				}
			
      			/*TEST_debut
	      		if (zu == 0)
				{
				NX = nx;	NY = ny;	NZ = nz;	MX = mx;	MY = my;	MZ = mz;
	      			N = n;		M = m;
				for (zi = 1 ;zi <= 9 ;zi++ )	ff[zi] = wae[zi];
				}
	      		if (zu == 1) XX1 =XX1 - delta_x;
	      		if (zu == 2) YY1 =YY1 - delta_x;
	      		if (zu == 3) ZZ1 =ZZ1 - delta_x;
	      		if (zu == 4) XX2 =XX2 - delta_x;
	      		if (zu == 5) YY2 =YY2 - delta_x;
	      		if (zu == 6) ZZ2 =ZZ2 - delta_x;
	      		if (zu == 7) XX3 =XX3 - delta_x;
	      		if (zu == 8) YY3 =YY3 - delta_x;
	      		if (zu == 9) ZZ3 =ZZ3 - delta_x;
	      		
	      		if ((zu > 0) && (zu < 10))
				{
				for (zi = 1 ;zi <= 9 ;zi++ )	KWE[zi][zu] = - (wae[zi] - ff[zi]) / delta_x;
				DNX[zu] = (nx -NX) / delta_x;	DNY[zu] = (ny -NY) / delta_x;	DNZ[zu] = (nz -NZ) / delta_x;
				DMX[zu] = (mx -MX) / delta_x;	DMY[zu] = (my -MY) / delta_x;	DMZ[zu] = (mz -MZ) / delta_x;
				DNN[zu] = (n -N) / delta_x;	DMM[zu] = (m -M) / delta_x;
	      			}
	      		if (zu == 10)
      				{
	      			if (elem == 286)
	      				{
					printf("elem : %d z1 : %d z2 : %d z3 : %d\n",elem,z1,z2,z3);
					printf("u1 : %lf u2 : %lf u3 : %lf\n",u1,u2,u3);
					printf("v1 : %lf v2 : %lf v3 : %lf\n",v1,v2,v3);
					printf("S : %lf\n",S);
				
					printf("Dnx = ");	for (zv = 1 ;zv <= 9 ;zv++ ) 	printf("%8.3lf ",Dnx[zv]);	printf(" \n");
					printf("DNX = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%8.3lf ",DNX[zv]);	printf(" \n");
					printf("Dny = ");	for (zv = 1 ;zv <= 9 ;zv++ ) 	printf("%8.3lf ",Dny[zv]);	printf(" \n");
					printf("DNY = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%8.3lf ",DNY[zv]);	printf(" \n");
					printf("Dnz = ");	for (zv = 1 ;zv <= 9 ;zv++ ) 	printf("%8.3lf ",Dnz[zv]);	printf(" \n");
					printf("DNZ = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%8.3lf ",DNZ[zv]);	printf(" \n");
			
					printf("Dmx = ");	for (zv = 1 ;zv <= 9 ;zv++ ) 	printf("%8.3lf ",Dmx[zv]);	printf(" \n");
					printf("DMX = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%8.3lf ",DMX[zv]);	printf(" \n");
					printf("Dmy = ");	for (zv = 1 ;zv <= 9 ;zv++ ) 	printf("%8.3lf ",Dmy[zv]);	printf(" \n");
					printf("DMY = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%8.3lf ",DMY[zv]);	printf(" \n");
					printf("Dmz = ");	for (zv = 1 ;zv <= 9 ;zv++ ) 	printf("%8.3lf ",Dmz[zv]);	printf(" \n");
					printf("DMZ = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%8.3lf ",DMZ[zv]);	printf(" \n");
			
					printf("Dnn = ");	for (zv = 1 ;zv <= 9 ;zv++ ) 	printf("%8.3lf ",Dnn[zv]);	printf(" \n");
					printf("DNN = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%8.3lf ",DNN[zv]);	printf(" \n");
					printf("Dmm = ");	for (zv = 1 ;zv <= 9 ;zv++ ) 	printf("%8.3lf ",Dmm[zv]);	printf(" \n");
					printf("DMM = ");	for (zv = 1 ;zv <= 9 ;zv++ )	printf("%8.3lf ",DMM[zv]);	printf(" \n");
					
					printf("kwe = \n");						
					for (zi = 1 ;zi <= 9 ;zi++ )	
						{
						for (zv = 1 ;zv <= 9 ;zv++ )	printf("%12.4lf ",kwe[zi][zv]);
						printf(" \n");
						}
					printf("KWE = \n");
					for (zi = 1 ;zi <= 9 ;zi++ )	
						{
						for (zv = 1 ;zv <= 9 ;zv++ )	printf("%12.4lf ",KWE[zi][zv]);
						printf(" \n");
						}
					}
				}
			}
		//}
		exit(0);
		TEST_fin*/

		if (Structure.type_solver == 1)
			{
			/* Mise a jour de la matrice de raideur globale*/
			for (zl = 1; zl<= 9; zl++)
				{
				for (zk = 1; zk<= 9; zk++) 
					{
					/* kwe est la matrice de raideur calculee dans etirement5.
					La matrice globale est rangee differemment. Ce n'est plus une matrice
					bande. La diagonale est devenu la colonne eca de ze*/
					//ze[yc(elem,zl)][eca+yc(elem,zk)-yc(elem,zl)] += kwe[zl][zk];
					affectation_ze_rang(yc(elem,zl), yc(elem,zk), kwe[zl][zk]);
					}
				}
			}
		else if (Structure.type_solver == 2)
      			{
			for (zl = 1; zl<= 9; zl++)
				{
				//for (zk=1;zk<=9;zk++)	affectation_pardiso(kwe[zl][zk], yc(elem,zl), yc(elem,zk));
				}
      			}
		/* Mise a jour du vecteur effort global*/
		for (zl = 1; zl<= 9; zl++)	wasurf[yc(elem,zl)] += wae[zl];
		/*
		printf("elem = %4d ",elem);		printf("z1 = %4d ",z1);	printf("z2 = %4d ",z2);	printf("z3 = %4d \n",z3);
		printf("etirement\n");imprvectreel1(9, 3, wae);
		printf("kwe = \n");						
		for (zi = 1 ;zi <= 9 ;zi++ )
			{
			for (zv = 1 ;zv <= 9 ;zv++ )	printf("%12.4lf ",kwe[zi][zv]);	printf(" \n");
			}
		printf("S %lf ",S);	printf("n0 %4lf ",n0);	printf("n %4lf ",n);	printf("m %4lf \n",m);
		*/
		}
	}



