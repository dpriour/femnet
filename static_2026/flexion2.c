#define PRINCIPAL 0
#include "4c19.h"

void flexion2()
	{
	/*  
	efforts wae d une nappe de filet, dus a la flexion entre fil a chaque noeud, dans le plan du triangle.
   	le couple varie lineairement avec le 1/2 angle entre les fils u et v
   	*/
	int ii, jj;
	int z1,z2,z3,elem,zl,zk,ZL,ZK,zu;
  	double deno,u1,u2,u3,v1,v2,v3,seuil,mean_tension;
  	double nx,ny,nz,mx,my,mz,nn,mm,nxc,nyc,nzc,mxc,myc,mzc,nc,mc,sca,coef;
  	double angle,angle0,angle_x1,angle_x2,angle_x3,angle_y1,angle_y2,angle_y3,angle_z1,angle_z2,angle_z3;
  	double xx1,xx2,xx3,yy1,yy2,yy3,zz1,zz2,zz3;
  	double fx1,fx2,fx3,fy1,fy2,fy3,fz1,fz2,fz3,H;
  	double Dnx[10],Dny[10],Dnz[10],Dmx[10],Dmy[10],Dmz[10],Dnn[10],Dmm[10],Dsca[10],Dangle[10],Dcoef[10];
	double Dangle_x1[10],Dangle_y1[10],Dangle_z1[10],Dangle_x2[10],Dangle_y2[10],Dangle_z2[10],Dangle_x3[10],Dangle_y3[10],Dangle_z3[10];
	double Dfx1[10],Dfy1[10],Dfz1[10],Dfx2[10],Dfy2[10],Dfz2[10],Dfx3[10],Dfy3[10],Dfz3[10];
 	double k_elem[10][10],delta_x;
 	
      	/*TEST_debut
  	double nX,nY,nZ,mX,mY,mZ,nN,mM,scA,coeF,anglE;
  	double fX1,fX2,fX3,fY1,fY2,fY3,fZ1,fZ2,fZ3;
  	double DnX[10],DnY[10],DnZ[10],DmX[10],DmY[10],DmZ[10],DnN[10],DmM[10],DscA[10],DanglE[10],DcoeF[10];
	double Dangle_X1[10],Dangle_Y1[10],Dangle_Z1[10],Dangle_X2[10],Dangle_Y2[10],Dangle_Z2[10],Dangle_X3[10],Dangle_Y3[10],Dangle_Z3[10];
	double DfX1[10],DfY1[10],DfZ1[10],DfX2[10],DfY2[10],DfZ2[10],DfX3[10],DfY3[10],DfZ3[10];
      	TEST_fin*/
  	
  	for (elem = 1; elem<= NOMBRE_SURFACES; elem++)
  		{
		if ((Surface[elem].EI_flexion > 0.0) || (Surface[elem].raideur_ouverture > 0.0))
			{
			/*numero des coordonnees x des sommets 1 2 et 3 du triangle*/
			z1 = yc(elem,1);  z2 = yc(elem,4);  z3 = yc(elem,7);
				
	  		u1 =   Surface[elem].lon[1] + Surface[elem].lon[2] - Surface[elem].lon[2] - Surface[elem].lon[1]; 
	  		u2 =   Surface[elem].lon[3] + Surface[elem].lon[4] - Surface[elem].lon[2] - Surface[elem].lon[1]; 
	  		u3 =   Surface[elem].lon[5] + Surface[elem].lon[6] - Surface[elem].lon[2] - Surface[elem].lon[1];  
	  		v1 = - Surface[elem].lon[1] + Surface[elem].lon[2] - Surface[elem].lon[2] + Surface[elem].lon[1];  
	  		v2 = - Surface[elem].lon[3] + Surface[elem].lon[4] - Surface[elem].lon[2] + Surface[elem].lon[1];  
	  		v3 = - Surface[elem].lon[5] + Surface[elem].lon[6] - Surface[elem].lon[2] + Surface[elem].lon[1]; 
	  	
	  		/*ATTENTION ici u1 = 0 et v1 = 0, parfois on en tient compte parfois pas !!!!!*/
	  	
			/*printf("u = %6.3lf %6.3lf %6.3lf   ",u1,u2,u3);
			printf("v = %6.3lf %6.3lf %6.3lf \n",v1,v2,v3);*/
	 	
			deno = ((u2-u1)*(v3-v1) - (u3-u1)*(v2-v1));
	  		/* deno = 1 * nb de fils dans le triangle = 2 * nb de fils u = 2 * nb de fils v = 4 * nb de mailles */

			if (deno == 0.0) 
				{
				printf("deno = 0 dans flexion2.c    \n");
				exit(0);
				}
	
			/*coordonnees des 3 sommets 1 2 et 3*/		
	   		xx1 = wf[z1+0];	yy1 = wf[z1+1];	zz1 = wf[z1+2];
	   		xx2 = wf[z2+0];	yy2 = wf[z2+1];	zz2 = wf[z2+2];
	   		xx3 = wf[z3+0];	yy3 = wf[z3+1];	zz3 = wf[z3+2];
	   				
	      		/*TEST_debut
			delta_x = 0.000001;
			for( zu = 0 ; zu <= 10 ; zu++ )
	      			{
	      			if (zu == 1) xx1 = xx1 + delta_x;
	      			if (zu == 2) yy1 = yy1 + delta_x;
	      			if (zu == 3) zz1 = zz1 + delta_x;
	      			if (zu == 4) xx2 = xx2 + delta_x;
	      			if (zu == 5) yy2 = yy2 + delta_x;
	      			if (zu == 6) zz2 = zz2 + delta_x;
	      			if (zu == 7) xx3 = xx3 + delta_x;
	      			if (zu == 8) yy3 = yy3 + delta_x;
	      			if (zu == 9) zz3 = zz3 + delta_x;
	      		TEST_fin*/
	      				
	  		/* (xxi,yyi,zzi) coordonnees cartesiennes du sommet i du triangle elem*/
		     
	  		nx = ((v2-v1)*(xx1-xx3) + (v3-v1)*(xx2-xx1)) / deno;
	  		mx = ((u2-u1)*(xx3-xx1) + (u3-u1)*(xx1-xx2)) / deno;
	  		ny = ((v2-v1)*(yy1-yy3) + (v3-v1)*(yy2-yy1)) / deno;
	  		my = ((u2-u1)*(yy3-yy1) + (u3-u1)*(yy1-yy2)) / deno;
	  		nz = ((v2-v1)*(zz1-zz3) + (v3-v1)*(zz2-zz1)) / deno;
	  		mz = ((u2-u1)*(zz3-zz1) + (u3-u1)*(zz1-zz2)) / deno;

	  		/* nx (ny,nz): Coordonnees selon x (y,z) d'un cote de maille (selon u )*/
	  		/* mx (mx,mz): Coordonnees selon x (y,z) d'un cote de maille (selon v )*/

			/*printf("n = %6.3lf %6.3lf %6.3lf   ",nx,ny,nz);	printf("m = %6.3lf %6.3lf %6.3lf   \n",mx,my,mz);
			printf("n = %12.3lf %12.3lf %12.3lf   \n",Surface[elem].nx,Surface[elem].ny,Surface[elem].nz);  
			printf("m = %12.3lf %12.3lf %12.3lf   \n",Surface[elem].mx,Surface[elem].my,Surface[elem].mz);*/  

			nxc = nx * nx;	nyc = ny * ny;	nzc = nz * nz;
			mxc = mx * mx;	myc = my * my;	mzc = mz * mz;

			if ((nxc+nyc+nzc < 0.0) || (mxc+myc+mzc < 0.0)) 
				{
				printf("nxc+nyc+nzc = 0 dans flexion2.c    \n");
				exit(0);
				}

			nn = sqrt(nxc+nyc+nzc);		mm = sqrt(mxc+myc+mzc);
	
			if ((nn == 0.0) || (mm == 0.0)) 
				{
				printf("nn | mm = 0 dans flexion2.c    \n");
	  			if(nn <= 0.0)
	  				{
	  				nn = 0.5 * Surface[elem].lgrepos;
	  				}
	  			if(mm <= 0.0)
	  				{
	  				mm = 0.5 * Surface[elem].lgrepos;
	  				}
				}
			nc = nn*nn;			mc = mm*mm;
			sca = nx*mx+ny*my+nz*mz;		/*produit scalaire entre u et v*/
			if(sca/nn/mm < -1.0)
				{
				angle = PI / 2.0;
				sca = -1.0 * nn * mm;
				printf("angle ne peut pas etre calcule dans flexion2.c    ");
				printf("elem %d sca/nn/mm   = %lf\n",elem,sca/nn/mm);
				printf("n = %6.3lf %6.3lf   ",nx,ny);	printf("m = %6.3lf %6.3lf   \n",mx,my);
				printf("n = %12.3lf %12.3lf %12.3lf   \n",Surface[elem].nx,Surface[elem].ny,Surface[elem].nz);  
				printf("m = %12.3lf %12.3lf %12.3lf   \n",Surface[elem].mx,Surface[elem].my,Surface[elem].mz);
				/*exit(0);*/
				}
			if(sca/nn/mm >  1.0)
				{
				angle = 0.0 / 2.0;
				sca =  1.0 * nn * mm;
				printf("angle ne peut pas etre calcule dans flexion2.c    ");
				printf("elem %d sca/nn/mm   = %lf\n",elem,sca/nn/mm);
				/*exit(0);*/
				}
			else
				{
				angle = acos(sca/nn/mm) / 2.0;	
				/*
				angle entre u et la grande diagonale. 
				Le vecteur grande diagonale est =~ u + v 
				Le vecteur petite diagonale est =~ u - v 
				angle est compris entre 0 et pi
				*/
				}
	
	   		seuil = 0.00001; /*angle limite pour eliminer les divisions par zero*/
	   				
	   		if (fabs(angle) > seuil)	coef = 1.0 / 2.0 / sin(angle) /deno / nn / mm;
	   		else				coef = 1.0 / 2.0 / sin(seuil) /deno / nn / mm;
						
			/*angle_x1 = derivee de angle par rapport a x1*/
			angle_x1 = coef* (mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2));
			angle_y1 = coef* (my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2));
			angle_z1 = coef* (mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2));
		
			angle_x2 = coef* (mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3));
			angle_y2 = coef* (my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3));
			angle_z2 = coef* (mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3));
		
			angle_x3 = coef* (mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1));
			angle_y3 = coef* (my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1));
			angle_z3 = coef* (mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1));
			/*if (elem == 59)
				{
				printf("angle_x1 %6.3lf \n",angle_x1);
				printf("coef %6.3lf \n",coef);
				printf("sca %6.3lf \n",sca);
				printf("nc %6.3lf \n",nc);
				printf("mc %6.3lf \n",mc);
				printf("v2 %6.3lf \n",v2);
				printf("v3 %6.3lf \n",v3);
				printf("u2 %6.3lf \n",u2);
				printf("u3 %6.3lf \n",u3);
				exit(0);
				}*/

			H = Surface[elem].raideur_ouverture;  /*couple = H en  N.m pour 1 radian d ouverture pour un noeud*/
			/*H = 6.0 * Surface[elem].EI_flexion / Surface[elem].lgrepos;*/
		
			if ((Surface[elem].EI_flexion != 0.0) && (Surface[elem].raideur_ouverture != 0.0))
				{
				H = 6.0 * Surface[elem].EI_flexion / Surface[elem].lgrepos; /*cf herrmann, priour krag, 2006, fisheries resaerch 84 222-232*/
				/*printf("H %6.3lf ",H);*/
				mean_tension = sqrt(((Surface[elem].tension1 * Surface[elem].tension1) + (Surface[elem].tension2 * Surface[elem].tension2))/2.0);/**/
				/*H = 2.0 * sqrt(Surface[elem].EI_flexion * mean_tension);*/		/*from Barry the 03/02/06*/
				/*printf("H %6.3lf ",H);
				printf("tension1&2 %6.3lf %6.3lf ",Surface[elem].tension1,Surface[elem].tension2);
				printf("mean %6.3lf \n",mean_tension);
				exit(0);*/
				}
		
			/*printf("Surface[%d].raideur_ouverture = %6.3lf \n",elem,Surface[elem].raideur_ouverture);*/

			/*printf("nn = %6.3lf %6.3lf %6.3lf   ",nx,ny,nz);
			printf("mm = %6.3lf %6.3lf %6.3lf   ",mx,my,mz);
			printf("angle = %9.6lf  deno = %3.0lf \n",angle,deno);*/
	
			/*angle0 = angle au repos*/
			angle0 = Surface[elem].neutral_angle;
	
			/*
			avec angle = 1/2 angle entre les fils - l angle au repos
			si le couple par fils = H * (angle - angle0)
			le travail interne = travail externe
			le travail interne = deno * H * (angle - angle0) * dangle
			avec deno = nb de fils
			le travail externe = fx1 * dx1
			dangle / dx1 = angle_x1
			deno * H * (angle - angle0) * dangle = fx1 * dx1
			deno * H * (angle - angle0) * angle_x1 = fx1
			fx1 = deno * H * (angle - angle0) * angle_x1
			*/
		
			fx1 = deno * H * (angle - angle0) * angle_x1;	fx2 = deno * H * (angle - angle0) * angle_x2;	fx3 = deno * H * (angle - angle0) * angle_x3;
			fy1 = deno * H * (angle - angle0) * angle_y1;	fy2 = deno * H * (angle - angle0) * angle_y2;	fy3 = deno * H * (angle - angle0) * angle_y3;
			fz1 = deno * H * (angle - angle0) * angle_z1;	fz2 = deno * H * (angle - angle0) * angle_z2;	fz3 = deno * H * (angle - angle0) * angle_z3;
	
			/*printf("f = %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf  \n",fx1,fx2,fx3,fy1,fy2,fy3,fz1,fz2,fz3);
			printf("fx = %7.3lf  fy = %7.3lf  fz = %7.3lf   \n",fx1+fx2+fx3,fy1+fy2+fy3,fz1+fz2+fz3);*/

	
	  		/* Efforts aux 3 noeuds, sommets du triangle.*/
	  		wae[1] = fx1; 		wae[2] = fy1;  		wae[3] = fz1;
	  		wae[4] = fx2;  		wae[5] = fy2;  		wae[6] = fz2;
	  		wae[7] = fx3;  		wae[8] = fy3;  		wae[9] = fz3;
	
			/* Mise a jour du vecteur effort global*/
			for (zl = 1; zl<= 9; zl++)
				{
				wasurf[yc(elem,zl)] += wae[zl];
				}
	
	  		Dnx[1] = (v2-v3)/deno;  Dnx[2] = 0.0;        	Dnx[3] = 0.0;        	Dnx[4] = (v3-v1)/deno;  Dnx[5] = 0.0;        	Dnx[6] = 0.0;        	Dnx[7] = (v1-v2)/deno;  Dnx[8] = 0.0;        	Dnx[9] = 0.0;
	  		Dny[1] = 0.0;        	Dny[2] = (v2-v3)/deno;  Dny[3] = 0.0;        	Dny[4] = 0.0;        	Dny[5] = (v3-v1)/deno;  Dny[6] = 0.0;        	Dny[7] = 0.0;        	Dny[8] = (v1-v2)/deno;  Dny[9] = 0.0;
	  		Dnz[1] = 0.0;        	Dnz[2] = 0.0;        	Dnz[3] = (v2-v3)/deno;  Dnz[4] = 0.0;        	Dnz[5] = 0.0;        	Dnz[6] = (v3-v1)/deno;  Dnz[7] = 0.0;        	Dnz[8] = 0.0;        	Dnz[9] = (v1-v2)/deno;
	  		Dmx[1] = (u3-u2)/deno;  Dmx[2] = 0.0;        	Dmx[3] = 0.0;        	Dmx[4] = (u1-u3)/deno;  Dmx[5] = 0.0;        	Dmx[6] = 0.0;        	Dmx[7] = (u2-u1)/deno;  Dmx[8] = 0.0;        	Dmx[9] = 0.0;
	  		Dmy[1] = 0.0;        	Dmy[2] = (u3-u2)/deno;  Dmy[3] = 0.0;        	Dmy[4] = 0.0;        	Dmy[5] = (u1-u3)/deno;  Dmy[6] = 0.0;        	Dmy[7] = 0.0;        	Dmy[8] = (u2-u1)/deno;  Dmy[9] = 0.0;
	  		Dmz[1] = 0.0;        	Dmz[2] = 0.0;        	Dmz[3] = (u3-u2)/deno;  Dmz[4] = 0.0;        	Dmz[5] = 0.0;        	Dmz[6] = (u1-u3)/deno;  Dmz[7] = 0.0;        	Dmz[8] = 0.0;        	Dmz[9] = (u2-u1)/deno;
			
			Dnn[1] = nx*(v2-v3)/nn/deno;  Dnn[2] = ny*(v2-v3)/nn/deno;  Dnn[3] = nz*(v2-v3)/nn/deno;  Dnn[4] = nx*(v3-v1)/nn/deno;  Dnn[5] = ny*(v3-v1)/nn/deno;  Dnn[6] = nz*(v3-v1)/nn/deno;  Dnn[7] = nx*(v1-v2)/nn/deno;  Dnn[8] = ny*(v1-v2)/nn/deno;  Dnn[9] = nz*(v1-v2)/nn/deno;
			Dmm[1] = mx*(u3-u2)/mm/deno;  Dmm[2] = my*(u3-u2)/mm/deno;  Dmm[3] = mz*(u3-u2)/mm/deno;  Dmm[4] = mx*(u1-u3)/mm/deno;  Dmm[5] = my*(u1-u3)/mm/deno;  Dmm[6] = mz*(u1-u3)/mm/deno;  Dmm[7] = mx*(u2-u1)/mm/deno;  Dmm[8] = my*(u2-u1)/mm/deno;  Dmm[9] = mz*(u2-u1)/mm/deno;

			Dsca[1] = Dnx[1]*mx + nx * Dmx[1] + Dny[1]*my + ny * Dmy[1] + Dnz[1]*mz + nz * Dmz[1];		
			Dsca[2] = Dnx[2]*mx + nx * Dmx[2] + Dny[2]*my + ny * Dmy[2] + Dnz[2]*mz + nz * Dmz[2];		
			Dsca[3] = Dnx[3]*mx + nx * Dmx[3] + Dny[3]*my + ny * Dmy[3] + Dnz[3]*mz + nz * Dmz[3];		
			Dsca[4] = Dnx[4]*mx + nx * Dmx[4] + Dny[4]*my + ny * Dmy[4] + Dnz[4]*mz + nz * Dmz[4];		
			Dsca[5] = Dnx[5]*mx + nx * Dmx[5] + Dny[5]*my + ny * Dmy[5] + Dnz[5]*mz + nz * Dmz[5];		
			Dsca[6] = Dnx[6]*mx + nx * Dmx[6] + Dny[6]*my + ny * Dmy[6] + Dnz[6]*mz + nz * Dmz[6];		
			Dsca[7] = Dnx[7]*mx + nx * Dmx[7] + Dny[7]*my + ny * Dmy[7] + Dnz[7]*mz + nz * Dmz[7];		
			Dsca[8] = Dnx[8]*mx + nx * Dmx[8] + Dny[8]*my + ny * Dmy[8] + Dnz[8]*mz + nz * Dmz[8];		
			Dsca[9] = Dnx[9]*mx + nx * Dmx[9] + Dny[9]*my + ny * Dmy[9] + Dnz[9]*mz + nz * Dmz[9];		
	
			if (fabs(angle) > seuil)			
				{
				Dangle[1] = -1.0/ sin(2.0*angle) *(Dsca[1]*nn*mm - sca*(Dnn[1]*mm + nn*Dmm[1])) / nc / mc / 2.0;
				Dangle[2] = -1.0/ sin(2.0*angle) *(Dsca[2]*nn*mm - sca*(Dnn[2]*mm + nn*Dmm[2])) / nc / mc / 2.0;
				Dangle[3] = -1.0/ sin(2.0*angle) *(Dsca[3]*nn*mm - sca*(Dnn[3]*mm + nn*Dmm[3])) / nc / mc / 2.0;
				Dangle[4] = -1.0/ sin(2.0*angle) *(Dsca[4]*nn*mm - sca*(Dnn[4]*mm + nn*Dmm[4])) / nc / mc / 2.0;
				Dangle[5] = -1.0/ sin(2.0*angle) *(Dsca[5]*nn*mm - sca*(Dnn[5]*mm + nn*Dmm[5])) / nc / mc / 2.0;
				Dangle[6] = -1.0/ sin(2.0*angle) *(Dsca[6]*nn*mm - sca*(Dnn[6]*mm + nn*Dmm[6])) / nc / mc / 2.0;
				Dangle[7] = -1.0/ sin(2.0*angle) *(Dsca[7]*nn*mm - sca*(Dnn[7]*mm + nn*Dmm[7])) / nc / mc / 2.0;
				Dangle[8] = -1.0/ sin(2.0*angle) *(Dsca[8]*nn*mm - sca*(Dnn[8]*mm + nn*Dmm[8])) / nc / mc / 2.0;
				Dangle[9] = -1.0/ sin(2.0*angle) *(Dsca[9]*nn*mm - sca*(Dnn[9]*mm + nn*Dmm[9])) / nc / mc / 2.0;
				}
			else
				{
				Dangle[1] = -1.0/ sin(2.0*seuil) *(Dsca[1]*nn*mm - sca*(Dnn[1]*mm + nn*Dmm[1])) / nc / mc / 2.0;
				Dangle[2] = -1.0/ sin(2.0*seuil) *(Dsca[2]*nn*mm - sca*(Dnn[2]*mm + nn*Dmm[2])) / nc / mc / 2.0;
				Dangle[3] = -1.0/ sin(2.0*seuil) *(Dsca[3]*nn*mm - sca*(Dnn[3]*mm + nn*Dmm[3])) / nc / mc / 2.0;
				Dangle[4] = -1.0/ sin(2.0*seuil) *(Dsca[4]*nn*mm - sca*(Dnn[4]*mm + nn*Dmm[4])) / nc / mc / 2.0;
				Dangle[5] = -1.0/ sin(2.0*seuil) *(Dsca[5]*nn*mm - sca*(Dnn[5]*mm + nn*Dmm[5])) / nc / mc / 2.0;
				Dangle[6] = -1.0/ sin(2.0*seuil) *(Dsca[6]*nn*mm - sca*(Dnn[6]*mm + nn*Dmm[6])) / nc / mc / 2.0;
				Dangle[7] = -1.0/ sin(2.0*seuil) *(Dsca[7]*nn*mm - sca*(Dnn[7]*mm + nn*Dmm[7])) / nc / mc / 2.0;
				Dangle[8] = -1.0/ sin(2.0*seuil) *(Dsca[8]*nn*mm - sca*(Dnn[8]*mm + nn*Dmm[8])) / nc / mc / 2.0;
				Dangle[9] = -1.0/ sin(2.0*seuil) *(Dsca[9]*nn*mm - sca*(Dnn[9]*mm + nn*Dmm[9])) / nc / mc / 2.0;
				}
			
	  		if (fabs(angle) > seuil)			
				{
				Dcoef[1] = -(cos(angle)*Dangle[1]*nn*mm + sin(angle)*(Dnn[1]*mm+nn*Dmm[1]))/2.0/deno/(sin(angle)*nn*mm)/(sin(angle)*nn*mm);
				Dcoef[2] = -(cos(angle)*Dangle[2]*nn*mm + sin(angle)*(Dnn[2]*mm+nn*Dmm[2]))/2.0/deno/(sin(angle)*nn*mm)/(sin(angle)*nn*mm);
				Dcoef[3] = -(cos(angle)*Dangle[3]*nn*mm + sin(angle)*(Dnn[3]*mm+nn*Dmm[3]))/2.0/deno/(sin(angle)*nn*mm)/(sin(angle)*nn*mm);
				Dcoef[4] = -(cos(angle)*Dangle[4]*nn*mm + sin(angle)*(Dnn[4]*mm+nn*Dmm[4]))/2.0/deno/(sin(angle)*nn*mm)/(sin(angle)*nn*mm);
				Dcoef[5] = -(cos(angle)*Dangle[5]*nn*mm + sin(angle)*(Dnn[5]*mm+nn*Dmm[5]))/2.0/deno/(sin(angle)*nn*mm)/(sin(angle)*nn*mm);
				Dcoef[6] = -(cos(angle)*Dangle[6]*nn*mm + sin(angle)*(Dnn[6]*mm+nn*Dmm[6]))/2.0/deno/(sin(angle)*nn*mm)/(sin(angle)*nn*mm);
				Dcoef[7] = -(cos(angle)*Dangle[7]*nn*mm + sin(angle)*(Dnn[7]*mm+nn*Dmm[7]))/2.0/deno/(sin(angle)*nn*mm)/(sin(angle)*nn*mm);
				Dcoef[8] = -(cos(angle)*Dangle[8]*nn*mm + sin(angle)*(Dnn[8]*mm+nn*Dmm[8]))/2.0/deno/(sin(angle)*nn*mm)/(sin(angle)*nn*mm);
				Dcoef[9] = -(cos(angle)*Dangle[9]*nn*mm + sin(angle)*(Dnn[9]*mm+nn*Dmm[9]))/2.0/deno/(sin(angle)*nn*mm)/(sin(angle)*nn*mm);
				}
			else
				{
				Dcoef[1] = -(cos(seuil)*Dangle[1]*nn*mm + sin(seuil)*(Dnn[1]*mm+nn*Dmm[1]))/2.0/deno/(sin(seuil)*nn*mm)/(sin(seuil)*nn*mm);
				Dcoef[2] = -(cos(seuil)*Dangle[2]*nn*mm + sin(seuil)*(Dnn[2]*mm+nn*Dmm[2]))/2.0/deno/(sin(seuil)*nn*mm)/(sin(seuil)*nn*mm);
				Dcoef[3] = -(cos(seuil)*Dangle[3]*nn*mm + sin(seuil)*(Dnn[3]*mm+nn*Dmm[3]))/2.0/deno/(sin(seuil)*nn*mm)/(sin(seuil)*nn*mm);
				Dcoef[4] = -(cos(seuil)*Dangle[4]*nn*mm + sin(seuil)*(Dnn[4]*mm+nn*Dmm[4]))/2.0/deno/(sin(seuil)*nn*mm)/(sin(seuil)*nn*mm);
				Dcoef[5] = -(cos(seuil)*Dangle[5]*nn*mm + sin(seuil)*(Dnn[5]*mm+nn*Dmm[5]))/2.0/deno/(sin(seuil)*nn*mm)/(sin(seuil)*nn*mm);
				Dcoef[6] = -(cos(seuil)*Dangle[6]*nn*mm + sin(seuil)*(Dnn[6]*mm+nn*Dmm[6]))/2.0/deno/(sin(seuil)*nn*mm)/(sin(seuil)*nn*mm);
				Dcoef[7] = -(cos(seuil)*Dangle[7]*nn*mm + sin(seuil)*(Dnn[7]*mm+nn*Dmm[7]))/2.0/deno/(sin(seuil)*nn*mm)/(sin(seuil)*nn*mm);
				Dcoef[8] = -(cos(seuil)*Dangle[8]*nn*mm + sin(seuil)*(Dnn[8]*mm+nn*Dmm[8]))/2.0/deno/(sin(seuil)*nn*mm)/(sin(seuil)*nn*mm);
				Dcoef[9] = -(cos(seuil)*Dangle[9]*nn*mm + sin(seuil)*(Dnn[9]*mm+nn*Dmm[9]))/2.0/deno/(sin(seuil)*nn*mm)/(sin(seuil)*nn*mm);
				}
		
			Dangle_x1[1] = Dcoef[1]*(mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2)) + coef*(Dmx[1]*(v2-v3)+Dnx[1]*(u3-u2)-(v2-v3)*((Dsca[1]*nx+sca*Dnx[1])*nc-sca*nx*2.0*nn*Dnn[1])/nc/nc-(u3-u2)*((Dsca[1]*mx+sca*Dmx[1])*mc-sca*mx*2.0*mm*Dmm[1])/mc/mc);
			Dangle_x1[2] = Dcoef[2]*(mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2)) + coef*(Dmx[2]*(v2-v3)+Dnx[2]*(u3-u2)-(v2-v3)*((Dsca[2]*nx+sca*Dnx[2])*nc-sca*nx*2.0*nn*Dnn[2])/nc/nc-(u3-u2)*((Dsca[2]*mx+sca*Dmx[2])*mc-sca*mx*2.0*mm*Dmm[2])/mc/mc);
			Dangle_x1[3] = Dcoef[3]*(mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2)) + coef*(Dmx[3]*(v2-v3)+Dnx[3]*(u3-u2)-(v2-v3)*((Dsca[3]*nx+sca*Dnx[3])*nc-sca*nx*2.0*nn*Dnn[3])/nc/nc-(u3-u2)*((Dsca[3]*mx+sca*Dmx[3])*mc-sca*mx*2.0*mm*Dmm[3])/mc/mc);
			Dangle_x1[4] = Dcoef[4]*(mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2)) + coef*(Dmx[4]*(v2-v3)+Dnx[4]*(u3-u2)-(v2-v3)*((Dsca[4]*nx+sca*Dnx[4])*nc-sca*nx*2.0*nn*Dnn[4])/nc/nc-(u3-u2)*((Dsca[4]*mx+sca*Dmx[4])*mc-sca*mx*2.0*mm*Dmm[4])/mc/mc);
			Dangle_x1[5] = Dcoef[5]*(mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2)) + coef*(Dmx[5]*(v2-v3)+Dnx[5]*(u3-u2)-(v2-v3)*((Dsca[5]*nx+sca*Dnx[5])*nc-sca*nx*2.0*nn*Dnn[5])/nc/nc-(u3-u2)*((Dsca[5]*mx+sca*Dmx[5])*mc-sca*mx*2.0*mm*Dmm[5])/mc/mc);
			Dangle_x1[6] = Dcoef[6]*(mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2)) + coef*(Dmx[6]*(v2-v3)+Dnx[6]*(u3-u2)-(v2-v3)*((Dsca[6]*nx+sca*Dnx[6])*nc-sca*nx*2.0*nn*Dnn[6])/nc/nc-(u3-u2)*((Dsca[6]*mx+sca*Dmx[6])*mc-sca*mx*2.0*mm*Dmm[6])/mc/mc);
			Dangle_x1[7] = Dcoef[7]*(mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2)) + coef*(Dmx[7]*(v2-v3)+Dnx[7]*(u3-u2)-(v2-v3)*((Dsca[7]*nx+sca*Dnx[7])*nc-sca*nx*2.0*nn*Dnn[7])/nc/nc-(u3-u2)*((Dsca[7]*mx+sca*Dmx[7])*mc-sca*mx*2.0*mm*Dmm[7])/mc/mc);
			Dangle_x1[8] = Dcoef[8]*(mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2)) + coef*(Dmx[8]*(v2-v3)+Dnx[8]*(u3-u2)-(v2-v3)*((Dsca[8]*nx+sca*Dnx[8])*nc-sca*nx*2.0*nn*Dnn[8])/nc/nc-(u3-u2)*((Dsca[8]*mx+sca*Dmx[8])*mc-sca*mx*2.0*mm*Dmm[8])/mc/mc);
			Dangle_x1[9] = Dcoef[9]*(mx*(v2-v3)  +nx*(u3-u2)  -sca/nc*nx*(v2-v3)  -sca/mc*mx*(u3-u2)) + coef*(Dmx[9]*(v2-v3)+Dnx[9]*(u3-u2)-(v2-v3)*((Dsca[9]*nx+sca*Dnx[9])*nc-sca*nx*2.0*nn*Dnn[9])/nc/nc-(u3-u2)*((Dsca[9]*mx+sca*Dmx[9])*mc-sca*mx*2.0*mm*Dmm[9])/mc/mc);
		
			Dangle_y1[1] = Dcoef[1]*(my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2)) + coef*(Dmy[1]*(v2-v3)+Dny[1]*(u3-u2)-(v2-v3)*((Dsca[1]*ny+sca*Dny[1])*nc-sca*ny*2.0*nn*Dnn[1])/nc/nc-(u3-u2)*((Dsca[1]*my+sca*Dmy[1])*mc-sca*my*2.0*mm*Dmm[1])/mc/mc);
			Dangle_y1[2] = Dcoef[2]*(my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2)) + coef*(Dmy[2]*(v2-v3)+Dny[2]*(u3-u2)-(v2-v3)*((Dsca[2]*ny+sca*Dny[2])*nc-sca*ny*2.0*nn*Dnn[2])/nc/nc-(u3-u2)*((Dsca[2]*my+sca*Dmy[2])*mc-sca*my*2.0*mm*Dmm[2])/mc/mc);
			Dangle_y1[3] = Dcoef[3]*(my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2)) + coef*(Dmy[3]*(v2-v3)+Dny[3]*(u3-u2)-(v2-v3)*((Dsca[3]*ny+sca*Dny[3])*nc-sca*ny*2.0*nn*Dnn[3])/nc/nc-(u3-u2)*((Dsca[3]*my+sca*Dmy[3])*mc-sca*my*2.0*mm*Dmm[3])/mc/mc);
			Dangle_y1[4] = Dcoef[4]*(my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2)) + coef*(Dmy[4]*(v2-v3)+Dny[4]*(u3-u2)-(v2-v3)*((Dsca[4]*ny+sca*Dny[4])*nc-sca*ny*2.0*nn*Dnn[4])/nc/nc-(u3-u2)*((Dsca[4]*my+sca*Dmy[4])*mc-sca*my*2.0*mm*Dmm[4])/mc/mc);
			Dangle_y1[5] = Dcoef[5]*(my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2)) + coef*(Dmy[5]*(v2-v3)+Dny[5]*(u3-u2)-(v2-v3)*((Dsca[5]*ny+sca*Dny[5])*nc-sca*ny*2.0*nn*Dnn[5])/nc/nc-(u3-u2)*((Dsca[5]*my+sca*Dmy[5])*mc-sca*my*2.0*mm*Dmm[5])/mc/mc);
			Dangle_y1[6] = Dcoef[6]*(my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2)) + coef*(Dmy[6]*(v2-v3)+Dny[6]*(u3-u2)-(v2-v3)*((Dsca[6]*ny+sca*Dny[6])*nc-sca*ny*2.0*nn*Dnn[6])/nc/nc-(u3-u2)*((Dsca[6]*my+sca*Dmy[6])*mc-sca*my*2.0*mm*Dmm[6])/mc/mc);
			Dangle_y1[7] = Dcoef[7]*(my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2)) + coef*(Dmy[7]*(v2-v3)+Dny[7]*(u3-u2)-(v2-v3)*((Dsca[7]*ny+sca*Dny[7])*nc-sca*ny*2.0*nn*Dnn[7])/nc/nc-(u3-u2)*((Dsca[7]*my+sca*Dmy[7])*mc-sca*my*2.0*mm*Dmm[7])/mc/mc);
			Dangle_y1[8] = Dcoef[8]*(my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2)) + coef*(Dmy[8]*(v2-v3)+Dny[8]*(u3-u2)-(v2-v3)*((Dsca[8]*ny+sca*Dny[8])*nc-sca*ny*2.0*nn*Dnn[8])/nc/nc-(u3-u2)*((Dsca[8]*my+sca*Dmy[8])*mc-sca*my*2.0*mm*Dmm[8])/mc/mc);
			Dangle_y1[9] = Dcoef[9]*(my*(v2-v3)  +ny*(u3-u2)  -sca/nc*ny*(v2-v3)  -sca/mc*my*(u3-u2)) + coef*(Dmy[9]*(v2-v3)+Dny[9]*(u3-u2)-(v2-v3)*((Dsca[9]*ny+sca*Dny[9])*nc-sca*ny*2.0*nn*Dnn[9])/nc/nc-(u3-u2)*((Dsca[9]*my+sca*Dmy[9])*mc-sca*my*2.0*mm*Dmm[9])/mc/mc);
		
			Dangle_z1[1] = Dcoef[1]*(mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2)) + coef*(Dmz[1]*(v2-v3)+Dnz[1]*(u3-u2)-(v2-v3)*((Dsca[1]*nz+sca*Dnz[1])*nc-sca*nz*2.0*nn*Dnn[1])/nc/nc-(u3-u2)*((Dsca[1]*mz+sca*Dmz[1])*mc-sca*mz*2.0*mm*Dmm[1])/mc/mc);
			Dangle_z1[2] = Dcoef[2]*(mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2)) + coef*(Dmz[2]*(v2-v3)+Dnz[2]*(u3-u2)-(v2-v3)*((Dsca[2]*nz+sca*Dnz[2])*nc-sca*nz*2.0*nn*Dnn[2])/nc/nc-(u3-u2)*((Dsca[2]*mz+sca*Dmz[2])*mc-sca*mz*2.0*mm*Dmm[2])/mc/mc);
			Dangle_z1[3] = Dcoef[3]*(mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2)) + coef*(Dmz[3]*(v2-v3)+Dnz[3]*(u3-u2)-(v2-v3)*((Dsca[3]*nz+sca*Dnz[3])*nc-sca*nz*2.0*nn*Dnn[3])/nc/nc-(u3-u2)*((Dsca[3]*mz+sca*Dmz[3])*mc-sca*mz*2.0*mm*Dmm[3])/mc/mc);
			Dangle_z1[4] = Dcoef[4]*(mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2)) + coef*(Dmz[4]*(v2-v3)+Dnz[4]*(u3-u2)-(v2-v3)*((Dsca[4]*nz+sca*Dnz[4])*nc-sca*nz*2.0*nn*Dnn[4])/nc/nc-(u3-u2)*((Dsca[4]*mz+sca*Dmz[4])*mc-sca*mz*2.0*mm*Dmm[4])/mc/mc);
			Dangle_z1[5] = Dcoef[5]*(mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2)) + coef*(Dmz[5]*(v2-v3)+Dnz[5]*(u3-u2)-(v2-v3)*((Dsca[5]*nz+sca*Dnz[5])*nc-sca*nz*2.0*nn*Dnn[5])/nc/nc-(u3-u2)*((Dsca[5]*mz+sca*Dmz[5])*mc-sca*mz*2.0*mm*Dmm[5])/mc/mc);
			Dangle_z1[6] = Dcoef[6]*(mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2)) + coef*(Dmz[6]*(v2-v3)+Dnz[6]*(u3-u2)-(v2-v3)*((Dsca[6]*nz+sca*Dnz[6])*nc-sca*nz*2.0*nn*Dnn[6])/nc/nc-(u3-u2)*((Dsca[6]*mz+sca*Dmz[6])*mc-sca*mz*2.0*mm*Dmm[6])/mc/mc);
			Dangle_z1[7] = Dcoef[7]*(mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2)) + coef*(Dmz[7]*(v2-v3)+Dnz[7]*(u3-u2)-(v2-v3)*((Dsca[7]*nz+sca*Dnz[7])*nc-sca*nz*2.0*nn*Dnn[7])/nc/nc-(u3-u2)*((Dsca[7]*mz+sca*Dmz[7])*mc-sca*mz*2.0*mm*Dmm[7])/mc/mc);
			Dangle_z1[8] = Dcoef[8]*(mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2)) + coef*(Dmz[8]*(v2-v3)+Dnz[8]*(u3-u2)-(v2-v3)*((Dsca[8]*nz+sca*Dnz[8])*nc-sca*nz*2.0*nn*Dnn[8])/nc/nc-(u3-u2)*((Dsca[8]*mz+sca*Dmz[8])*mc-sca*mz*2.0*mm*Dmm[8])/mc/mc);
			Dangle_z1[9] = Dcoef[9]*(mz*(v2-v3)  +nz*(u3-u2)  -sca/nc*nz*(v2-v3)  -sca/mc*mz*(u3-u2)) + coef*(Dmz[9]*(v2-v3)+Dnz[9]*(u3-u2)-(v2-v3)*((Dsca[9]*nz+sca*Dnz[9])*nc-sca*nz*2.0*nn*Dnn[9])/nc/nc-(u3-u2)*((Dsca[9]*mz+sca*Dmz[9])*mc-sca*mz*2.0*mm*Dmm[9])/mc/mc);

			Dangle_x2[1] = Dcoef[1]*(mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3)) + coef*(Dmx[1]*(v3-v1)+Dnx[1]*(u1-u3)-(v3-v1)*((Dsca[1]*nx+sca*Dnx[1])*nc-sca*nx*2.0*nn*Dnn[1])/nc/nc-(u1-u3)*((Dsca[1]*mx+sca*Dmx[1])*mc-sca*mx*2.0*mm*Dmm[1])/mc/mc);
			Dangle_x2[2] = Dcoef[2]*(mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3)) + coef*(Dmx[2]*(v3-v1)+Dnx[2]*(u1-u3)-(v3-v1)*((Dsca[2]*nx+sca*Dnx[2])*nc-sca*nx*2.0*nn*Dnn[2])/nc/nc-(u1-u3)*((Dsca[2]*mx+sca*Dmx[2])*mc-sca*mx*2.0*mm*Dmm[2])/mc/mc);
			Dangle_x2[3] = Dcoef[3]*(mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3)) + coef*(Dmx[3]*(v3-v1)+Dnx[3]*(u1-u3)-(v3-v1)*((Dsca[3]*nx+sca*Dnx[3])*nc-sca*nx*2.0*nn*Dnn[3])/nc/nc-(u1-u3)*((Dsca[3]*mx+sca*Dmx[3])*mc-sca*mx*2.0*mm*Dmm[3])/mc/mc);
			Dangle_x2[4] = Dcoef[4]*(mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3)) + coef*(Dmx[4]*(v3-v1)+Dnx[4]*(u1-u3)-(v3-v1)*((Dsca[4]*nx+sca*Dnx[4])*nc-sca*nx*2.0*nn*Dnn[4])/nc/nc-(u1-u3)*((Dsca[4]*mx+sca*Dmx[4])*mc-sca*mx*2.0*mm*Dmm[4])/mc/mc);
			Dangle_x2[5] = Dcoef[5]*(mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3)) + coef*(Dmx[5]*(v3-v1)+Dnx[5]*(u1-u3)-(v3-v1)*((Dsca[5]*nx+sca*Dnx[5])*nc-sca*nx*2.0*nn*Dnn[5])/nc/nc-(u1-u3)*((Dsca[5]*mx+sca*Dmx[5])*mc-sca*mx*2.0*mm*Dmm[5])/mc/mc);
			Dangle_x2[6] = Dcoef[6]*(mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3)) + coef*(Dmx[6]*(v3-v1)+Dnx[6]*(u1-u3)-(v3-v1)*((Dsca[6]*nx+sca*Dnx[6])*nc-sca*nx*2.0*nn*Dnn[6])/nc/nc-(u1-u3)*((Dsca[6]*mx+sca*Dmx[6])*mc-sca*mx*2.0*mm*Dmm[6])/mc/mc);
			Dangle_x2[7] = Dcoef[7]*(mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3)) + coef*(Dmx[7]*(v3-v1)+Dnx[7]*(u1-u3)-(v3-v1)*((Dsca[7]*nx+sca*Dnx[7])*nc-sca*nx*2.0*nn*Dnn[7])/nc/nc-(u1-u3)*((Dsca[7]*mx+sca*Dmx[7])*mc-sca*mx*2.0*mm*Dmm[7])/mc/mc);
			Dangle_x2[8] = Dcoef[8]*(mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3)) + coef*(Dmx[8]*(v3-v1)+Dnx[8]*(u1-u3)-(v3-v1)*((Dsca[8]*nx+sca*Dnx[8])*nc-sca*nx*2.0*nn*Dnn[8])/nc/nc-(u1-u3)*((Dsca[8]*mx+sca*Dmx[8])*mc-sca*mx*2.0*mm*Dmm[8])/mc/mc);
			Dangle_x2[9] = Dcoef[9]*(mx*(v3-v1)  +nx*(u1-u3)  -sca/nc*nx*(v3-v1)  -sca/mc*mx*(u1-u3)) + coef*(Dmx[9]*(v3-v1)+Dnx[9]*(u1-u3)-(v3-v1)*((Dsca[9]*nx+sca*Dnx[9])*nc-sca*nx*2.0*nn*Dnn[9])/nc/nc-(u1-u3)*((Dsca[9]*mx+sca*Dmx[9])*mc-sca*mx*2.0*mm*Dmm[9])/mc/mc);
		
			Dangle_y2[1] = Dcoef[1]*(my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3)) + coef*(Dmy[1]*(v3-v1)+Dny[1]*(u1-u3)-(v3-v1)*((Dsca[1]*ny+sca*Dny[1])*nc-sca*ny*2.0*nn*Dnn[1])/nc/nc-(u1-u3)*((Dsca[1]*my+sca*Dmy[1])*mc-sca*my*2.0*mm*Dmm[1])/mc/mc);
			Dangle_y2[2] = Dcoef[2]*(my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3)) + coef*(Dmy[2]*(v3-v1)+Dny[2]*(u1-u3)-(v3-v1)*((Dsca[2]*ny+sca*Dny[2])*nc-sca*ny*2.0*nn*Dnn[2])/nc/nc-(u1-u3)*((Dsca[2]*my+sca*Dmy[2])*mc-sca*my*2.0*mm*Dmm[2])/mc/mc);
			Dangle_y2[3] = Dcoef[3]*(my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3)) + coef*(Dmy[3]*(v3-v1)+Dny[3]*(u1-u3)-(v3-v1)*((Dsca[3]*ny+sca*Dny[3])*nc-sca*ny*2.0*nn*Dnn[3])/nc/nc-(u1-u3)*((Dsca[3]*my+sca*Dmy[3])*mc-sca*my*2.0*mm*Dmm[3])/mc/mc);
			Dangle_y2[4] = Dcoef[4]*(my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3)) + coef*(Dmy[4]*(v3-v1)+Dny[4]*(u1-u3)-(v3-v1)*((Dsca[4]*ny+sca*Dny[4])*nc-sca*ny*2.0*nn*Dnn[4])/nc/nc-(u1-u3)*((Dsca[4]*my+sca*Dmy[4])*mc-sca*my*2.0*mm*Dmm[4])/mc/mc);
			Dangle_y2[5] = Dcoef[5]*(my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3)) + coef*(Dmy[5]*(v3-v1)+Dny[5]*(u1-u3)-(v3-v1)*((Dsca[5]*ny+sca*Dny[5])*nc-sca*ny*2.0*nn*Dnn[5])/nc/nc-(u1-u3)*((Dsca[5]*my+sca*Dmy[5])*mc-sca*my*2.0*mm*Dmm[5])/mc/mc);
			Dangle_y2[6] = Dcoef[6]*(my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3)) + coef*(Dmy[6]*(v3-v1)+Dny[6]*(u1-u3)-(v3-v1)*((Dsca[6]*ny+sca*Dny[6])*nc-sca*ny*2.0*nn*Dnn[6])/nc/nc-(u1-u3)*((Dsca[6]*my+sca*Dmy[6])*mc-sca*my*2.0*mm*Dmm[6])/mc/mc);
			Dangle_y2[7] = Dcoef[7]*(my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3)) + coef*(Dmy[7]*(v3-v1)+Dny[7]*(u1-u3)-(v3-v1)*((Dsca[7]*ny+sca*Dny[7])*nc-sca*ny*2.0*nn*Dnn[7])/nc/nc-(u1-u3)*((Dsca[7]*my+sca*Dmy[7])*mc-sca*my*2.0*mm*Dmm[7])/mc/mc);
			Dangle_y2[8] = Dcoef[8]*(my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3)) + coef*(Dmy[8]*(v3-v1)+Dny[8]*(u1-u3)-(v3-v1)*((Dsca[8]*ny+sca*Dny[8])*nc-sca*ny*2.0*nn*Dnn[8])/nc/nc-(u1-u3)*((Dsca[8]*my+sca*Dmy[8])*mc-sca*my*2.0*mm*Dmm[8])/mc/mc);
			Dangle_y2[9] = Dcoef[9]*(my*(v3-v1)  +ny*(u1-u3)  -sca/nc*ny*(v3-v1)  -sca/mc*my*(u1-u3)) + coef*(Dmy[9]*(v3-v1)+Dny[9]*(u1-u3)-(v3-v1)*((Dsca[9]*ny+sca*Dny[9])*nc-sca*ny*2.0*nn*Dnn[9])/nc/nc-(u1-u3)*((Dsca[9]*my+sca*Dmy[9])*mc-sca*my*2.0*mm*Dmm[9])/mc/mc);
		
			Dangle_z2[1] = Dcoef[1]*(mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3)) + coef*(Dmz[1]*(v3-v1)+Dnz[1]*(u1-u3)-(v3-v1)*((Dsca[1]*nz+sca*Dnz[1])*nc-sca*nz*2.0*nn*Dnn[1])/nc/nc-(u1-u3)*((Dsca[1]*mz+sca*Dmz[1])*mc-sca*mz*2.0*mm*Dmm[1])/mc/mc);
			Dangle_z2[2] = Dcoef[2]*(mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3)) + coef*(Dmz[2]*(v3-v1)+Dnz[2]*(u1-u3)-(v3-v1)*((Dsca[2]*nz+sca*Dnz[2])*nc-sca*nz*2.0*nn*Dnn[2])/nc/nc-(u1-u3)*((Dsca[2]*mz+sca*Dmz[2])*mc-sca*mz*2.0*mm*Dmm[2])/mc/mc);
			Dangle_z2[3] = Dcoef[3]*(mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3)) + coef*(Dmz[3]*(v3-v1)+Dnz[3]*(u1-u3)-(v3-v1)*((Dsca[3]*nz+sca*Dnz[3])*nc-sca*nz*2.0*nn*Dnn[3])/nc/nc-(u1-u3)*((Dsca[3]*mz+sca*Dmz[3])*mc-sca*mz*2.0*mm*Dmm[3])/mc/mc);
			Dangle_z2[4] = Dcoef[4]*(mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3)) + coef*(Dmz[4]*(v3-v1)+Dnz[4]*(u1-u3)-(v3-v1)*((Dsca[4]*nz+sca*Dnz[4])*nc-sca*nz*2.0*nn*Dnn[4])/nc/nc-(u1-u3)*((Dsca[4]*mz+sca*Dmz[4])*mc-sca*mz*2.0*mm*Dmm[4])/mc/mc);
			Dangle_z2[5] = Dcoef[5]*(mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3)) + coef*(Dmz[5]*(v3-v1)+Dnz[5]*(u1-u3)-(v3-v1)*((Dsca[5]*nz+sca*Dnz[5])*nc-sca*nz*2.0*nn*Dnn[5])/nc/nc-(u1-u3)*((Dsca[5]*mz+sca*Dmz[5])*mc-sca*mz*2.0*mm*Dmm[5])/mc/mc);
			Dangle_z2[6] = Dcoef[6]*(mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3)) + coef*(Dmz[6]*(v3-v1)+Dnz[6]*(u1-u3)-(v3-v1)*((Dsca[6]*nz+sca*Dnz[6])*nc-sca*nz*2.0*nn*Dnn[6])/nc/nc-(u1-u3)*((Dsca[6]*mz+sca*Dmz[6])*mc-sca*mz*2.0*mm*Dmm[6])/mc/mc);
			Dangle_z2[7] = Dcoef[7]*(mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3)) + coef*(Dmz[7]*(v3-v1)+Dnz[7]*(u1-u3)-(v3-v1)*((Dsca[7]*nz+sca*Dnz[7])*nc-sca*nz*2.0*nn*Dnn[7])/nc/nc-(u1-u3)*((Dsca[7]*mz+sca*Dmz[7])*mc-sca*mz*2.0*mm*Dmm[7])/mc/mc);
			Dangle_z2[8] = Dcoef[8]*(mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3)) + coef*(Dmz[8]*(v3-v1)+Dnz[8]*(u1-u3)-(v3-v1)*((Dsca[8]*nz+sca*Dnz[8])*nc-sca*nz*2.0*nn*Dnn[8])/nc/nc-(u1-u3)*((Dsca[8]*mz+sca*Dmz[8])*mc-sca*mz*2.0*mm*Dmm[8])/mc/mc);
			Dangle_z2[9] = Dcoef[9]*(mz*(v3-v1)  +nz*(u1-u3)  -sca/nc*nz*(v3-v1)  -sca/mc*mz*(u1-u3)) + coef*(Dmz[9]*(v3-v1)+Dnz[9]*(u1-u3)-(v3-v1)*((Dsca[9]*nz+sca*Dnz[9])*nc-sca*nz*2.0*nn*Dnn[9])/nc/nc-(u1-u3)*((Dsca[9]*mz+sca*Dmz[9])*mc-sca*mz*2.0*mm*Dmm[9])/mc/mc);

			Dangle_x3[1] = Dcoef[1]*(mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1)) + coef*(Dmx[1]*(v1-v2)+Dnx[1]*(u2-u1)-(v1-v2)*((Dsca[1]*nx+sca*Dnx[1])*nc-sca*nx*2.0*nn*Dnn[1])/nc/nc-(u2-u1)*((Dsca[1]*mx+sca*Dmx[1])*mc-sca*mx*2.0*mm*Dmm[1])/mc/mc);
			Dangle_x3[2] = Dcoef[2]*(mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1)) + coef*(Dmx[2]*(v1-v2)+Dnx[2]*(u2-u1)-(v1-v2)*((Dsca[2]*nx+sca*Dnx[2])*nc-sca*nx*2.0*nn*Dnn[2])/nc/nc-(u2-u1)*((Dsca[2]*mx+sca*Dmx[2])*mc-sca*mx*2.0*mm*Dmm[2])/mc/mc);
			Dangle_x3[3] = Dcoef[3]*(mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1)) + coef*(Dmx[3]*(v1-v2)+Dnx[3]*(u2-u1)-(v1-v2)*((Dsca[3]*nx+sca*Dnx[3])*nc-sca*nx*2.0*nn*Dnn[3])/nc/nc-(u2-u1)*((Dsca[3]*mx+sca*Dmx[3])*mc-sca*mx*2.0*mm*Dmm[3])/mc/mc);
			Dangle_x3[4] = Dcoef[4]*(mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1)) + coef*(Dmx[4]*(v1-v2)+Dnx[4]*(u2-u1)-(v1-v2)*((Dsca[4]*nx+sca*Dnx[4])*nc-sca*nx*2.0*nn*Dnn[4])/nc/nc-(u2-u1)*((Dsca[4]*mx+sca*Dmx[4])*mc-sca*mx*2.0*mm*Dmm[4])/mc/mc);
			Dangle_x3[5] = Dcoef[5]*(mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1)) + coef*(Dmx[5]*(v1-v2)+Dnx[5]*(u2-u1)-(v1-v2)*((Dsca[5]*nx+sca*Dnx[5])*nc-sca*nx*2.0*nn*Dnn[5])/nc/nc-(u2-u1)*((Dsca[5]*mx+sca*Dmx[5])*mc-sca*mx*2.0*mm*Dmm[5])/mc/mc);
			Dangle_x3[6] = Dcoef[6]*(mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1)) + coef*(Dmx[6]*(v1-v2)+Dnx[6]*(u2-u1)-(v1-v2)*((Dsca[6]*nx+sca*Dnx[6])*nc-sca*nx*2.0*nn*Dnn[6])/nc/nc-(u2-u1)*((Dsca[6]*mx+sca*Dmx[6])*mc-sca*mx*2.0*mm*Dmm[6])/mc/mc);
			Dangle_x3[7] = Dcoef[7]*(mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1)) + coef*(Dmx[7]*(v1-v2)+Dnx[7]*(u2-u1)-(v1-v2)*((Dsca[7]*nx+sca*Dnx[7])*nc-sca*nx*2.0*nn*Dnn[7])/nc/nc-(u2-u1)*((Dsca[7]*mx+sca*Dmx[7])*mc-sca*mx*2.0*mm*Dmm[7])/mc/mc);
			Dangle_x3[8] = Dcoef[8]*(mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1)) + coef*(Dmx[8]*(v1-v2)+Dnx[8]*(u2-u1)-(v1-v2)*((Dsca[8]*nx+sca*Dnx[8])*nc-sca*nx*2.0*nn*Dnn[8])/nc/nc-(u2-u1)*((Dsca[8]*mx+sca*Dmx[8])*mc-sca*mx*2.0*mm*Dmm[8])/mc/mc);
			Dangle_x3[9] = Dcoef[9]*(mx*(v1-v2)  +nx*(u2-u1)  -sca/nc*nx*(v1-v2)  -sca/mc*mx*(u2-u1)) + coef*(Dmx[9]*(v1-v2)+Dnx[9]*(u2-u1)-(v1-v2)*((Dsca[9]*nx+sca*Dnx[9])*nc-sca*nx*2.0*nn*Dnn[9])/nc/nc-(u2-u1)*((Dsca[9]*mx+sca*Dmx[9])*mc-sca*mx*2.0*mm*Dmm[9])/mc/mc);
		
			Dangle_y3[1] = Dcoef[1]*(my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1)) + coef*(Dmy[1]*(v1-v2)+Dny[1]*(u2-u1)-(v1-v2)*((Dsca[1]*ny+sca*Dny[1])*nc-sca*ny*2.0*nn*Dnn[1])/nc/nc-(u2-u1)*((Dsca[1]*my+sca*Dmy[1])*mc-sca*my*2.0*mm*Dmm[1])/mc/mc);
			Dangle_y3[2] = Dcoef[2]*(my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1)) + coef*(Dmy[2]*(v1-v2)+Dny[2]*(u2-u1)-(v1-v2)*((Dsca[2]*ny+sca*Dny[2])*nc-sca*ny*2.0*nn*Dnn[2])/nc/nc-(u2-u1)*((Dsca[2]*my+sca*Dmy[2])*mc-sca*my*2.0*mm*Dmm[2])/mc/mc);
			Dangle_y3[3] = Dcoef[3]*(my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1)) + coef*(Dmy[3]*(v1-v2)+Dny[3]*(u2-u1)-(v1-v2)*((Dsca[3]*ny+sca*Dny[3])*nc-sca*ny*2.0*nn*Dnn[3])/nc/nc-(u2-u1)*((Dsca[3]*my+sca*Dmy[3])*mc-sca*my*2.0*mm*Dmm[3])/mc/mc);
			Dangle_y3[4] = Dcoef[4]*(my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1)) + coef*(Dmy[4]*(v1-v2)+Dny[4]*(u2-u1)-(v1-v2)*((Dsca[4]*ny+sca*Dny[4])*nc-sca*ny*2.0*nn*Dnn[4])/nc/nc-(u2-u1)*((Dsca[4]*my+sca*Dmy[4])*mc-sca*my*2.0*mm*Dmm[4])/mc/mc);
			Dangle_y3[5] = Dcoef[5]*(my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1)) + coef*(Dmy[5]*(v1-v2)+Dny[5]*(u2-u1)-(v1-v2)*((Dsca[5]*ny+sca*Dny[5])*nc-sca*ny*2.0*nn*Dnn[5])/nc/nc-(u2-u1)*((Dsca[5]*my+sca*Dmy[5])*mc-sca*my*2.0*mm*Dmm[5])/mc/mc);
			Dangle_y3[6] = Dcoef[6]*(my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1)) + coef*(Dmy[6]*(v1-v2)+Dny[6]*(u2-u1)-(v1-v2)*((Dsca[6]*ny+sca*Dny[6])*nc-sca*ny*2.0*nn*Dnn[6])/nc/nc-(u2-u1)*((Dsca[6]*my+sca*Dmy[6])*mc-sca*my*2.0*mm*Dmm[6])/mc/mc);
			Dangle_y3[7] = Dcoef[7]*(my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1)) + coef*(Dmy[7]*(v1-v2)+Dny[7]*(u2-u1)-(v1-v2)*((Dsca[7]*ny+sca*Dny[7])*nc-sca*ny*2.0*nn*Dnn[7])/nc/nc-(u2-u1)*((Dsca[7]*my+sca*Dmy[7])*mc-sca*my*2.0*mm*Dmm[7])/mc/mc);
			Dangle_y3[8] = Dcoef[8]*(my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1)) + coef*(Dmy[8]*(v1-v2)+Dny[8]*(u2-u1)-(v1-v2)*((Dsca[8]*ny+sca*Dny[8])*nc-sca*ny*2.0*nn*Dnn[8])/nc/nc-(u2-u1)*((Dsca[8]*my+sca*Dmy[8])*mc-sca*my*2.0*mm*Dmm[8])/mc/mc);
			Dangle_y3[9] = Dcoef[9]*(my*(v1-v2)  +ny*(u2-u1)  -sca/nc*ny*(v1-v2)  -sca/mc*my*(u2-u1)) + coef*(Dmy[9]*(v1-v2)+Dny[9]*(u2-u1)-(v1-v2)*((Dsca[9]*ny+sca*Dny[9])*nc-sca*ny*2.0*nn*Dnn[9])/nc/nc-(u2-u1)*((Dsca[9]*my+sca*Dmy[9])*mc-sca*my*2.0*mm*Dmm[9])/mc/mc);
		
			Dangle_z3[1] = Dcoef[1]*(mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1)) + coef*(Dmz[1]*(v1-v2)+Dnz[1]*(u2-u1)-(v1-v2)*((Dsca[1]*nz+sca*Dnz[1])*nc-sca*nz*2.0*nn*Dnn[1])/nc/nc-(u2-u1)*((Dsca[1]*mz+sca*Dmz[1])*mc-sca*mz*2.0*mm*Dmm[1])/mc/mc);
			Dangle_z3[2] = Dcoef[2]*(mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1)) + coef*(Dmz[2]*(v1-v2)+Dnz[2]*(u2-u1)-(v1-v2)*((Dsca[2]*nz+sca*Dnz[2])*nc-sca*nz*2.0*nn*Dnn[2])/nc/nc-(u2-u1)*((Dsca[2]*mz+sca*Dmz[2])*mc-sca*mz*2.0*mm*Dmm[2])/mc/mc);
			Dangle_z3[3] = Dcoef[3]*(mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1)) + coef*(Dmz[3]*(v1-v2)+Dnz[3]*(u2-u1)-(v1-v2)*((Dsca[3]*nz+sca*Dnz[3])*nc-sca*nz*2.0*nn*Dnn[3])/nc/nc-(u2-u1)*((Dsca[3]*mz+sca*Dmz[3])*mc-sca*mz*2.0*mm*Dmm[3])/mc/mc);
			Dangle_z3[4] = Dcoef[4]*(mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1)) + coef*(Dmz[4]*(v1-v2)+Dnz[4]*(u2-u1)-(v1-v2)*((Dsca[4]*nz+sca*Dnz[4])*nc-sca*nz*2.0*nn*Dnn[4])/nc/nc-(u2-u1)*((Dsca[4]*mz+sca*Dmz[4])*mc-sca*mz*2.0*mm*Dmm[4])/mc/mc);
			Dangle_z3[5] = Dcoef[5]*(mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1)) + coef*(Dmz[5]*(v1-v2)+Dnz[5]*(u2-u1)-(v1-v2)*((Dsca[5]*nz+sca*Dnz[5])*nc-sca*nz*2.0*nn*Dnn[5])/nc/nc-(u2-u1)*((Dsca[5]*mz+sca*Dmz[5])*mc-sca*mz*2.0*mm*Dmm[5])/mc/mc);
			Dangle_z3[6] = Dcoef[6]*(mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1)) + coef*(Dmz[6]*(v1-v2)+Dnz[6]*(u2-u1)-(v1-v2)*((Dsca[6]*nz+sca*Dnz[6])*nc-sca*nz*2.0*nn*Dnn[6])/nc/nc-(u2-u1)*((Dsca[6]*mz+sca*Dmz[6])*mc-sca*mz*2.0*mm*Dmm[6])/mc/mc);
			Dangle_z3[7] = Dcoef[7]*(mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1)) + coef*(Dmz[7]*(v1-v2)+Dnz[7]*(u2-u1)-(v1-v2)*((Dsca[7]*nz+sca*Dnz[7])*nc-sca*nz*2.0*nn*Dnn[7])/nc/nc-(u2-u1)*((Dsca[7]*mz+sca*Dmz[7])*mc-sca*mz*2.0*mm*Dmm[7])/mc/mc);
			Dangle_z3[8] = Dcoef[8]*(mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1)) + coef*(Dmz[8]*(v1-v2)+Dnz[8]*(u2-u1)-(v1-v2)*((Dsca[8]*nz+sca*Dnz[8])*nc-sca*nz*2.0*nn*Dnn[8])/nc/nc-(u2-u1)*((Dsca[8]*mz+sca*Dmz[8])*mc-sca*mz*2.0*mm*Dmm[8])/mc/mc);
			Dangle_z3[9] = Dcoef[9]*(mz*(v1-v2)  +nz*(u2-u1)  -sca/nc*nz*(v1-v2)  -sca/mc*mz*(u2-u1)) + coef*(Dmz[9]*(v1-v2)+Dnz[9]*(u2-u1)-(v1-v2)*((Dsca[9]*nz+sca*Dnz[9])*nc-sca*nz*2.0*nn*Dnn[9])/nc/nc-(u2-u1)*((Dsca[9]*mz+sca*Dmz[9])*mc-sca*mz*2.0*mm*Dmm[9])/mc/mc);

			Dfx1[1] = deno * H * (Dangle[1] * angle_x1 + (angle-angle0) * Dangle_x1[1]);
			Dfx1[2] = deno * H * (Dangle[2] * angle_x1 + (angle-angle0) * Dangle_x1[2]);
			Dfx1[3] = deno * H * (Dangle[3] * angle_x1 + (angle-angle0) * Dangle_x1[3]);
			Dfx1[4] = deno * H * (Dangle[4] * angle_x1 + (angle-angle0) * Dangle_x1[4]);
			Dfx1[5] = deno * H * (Dangle[5] * angle_x1 + (angle-angle0) * Dangle_x1[5]);
			Dfx1[6] = deno * H * (Dangle[6] * angle_x1 + (angle-angle0) * Dangle_x1[6]);
			Dfx1[7] = deno * H * (Dangle[7] * angle_x1 + (angle-angle0) * Dangle_x1[7]);
			Dfx1[8] = deno * H * (Dangle[8] * angle_x1 + (angle-angle0) * Dangle_x1[8]);
			Dfx1[9] = deno * H * (Dangle[9] * angle_x1 + (angle-angle0) * Dangle_x1[9]);
		
			Dfy1[1] = deno * H * (Dangle[1] * angle_y1 + (angle-angle0) * Dangle_y1[1]);
			Dfy1[2] = deno * H * (Dangle[2] * angle_y1 + (angle-angle0) * Dangle_y1[2]);
			Dfy1[3] = deno * H * (Dangle[3] * angle_y1 + (angle-angle0) * Dangle_y1[3]);
			Dfy1[4] = deno * H * (Dangle[4] * angle_y1 + (angle-angle0) * Dangle_y1[4]);
			Dfy1[5] = deno * H * (Dangle[5] * angle_y1 + (angle-angle0) * Dangle_y1[5]);
			Dfy1[6] = deno * H * (Dangle[6] * angle_y1 + (angle-angle0) * Dangle_y1[6]);
			Dfy1[7] = deno * H * (Dangle[7] * angle_y1 + (angle-angle0) * Dangle_y1[7]);
			Dfy1[8] = deno * H * (Dangle[8] * angle_y1 + (angle-angle0) * Dangle_y1[8]);
			Dfy1[9] = deno * H * (Dangle[9] * angle_y1 + (angle-angle0) * Dangle_y1[9]);
		
			Dfz1[1] = deno * H * (Dangle[1] * angle_z1 + (angle-angle0) * Dangle_z1[1]);
			Dfz1[2] = deno * H * (Dangle[2] * angle_z1 + (angle-angle0) * Dangle_z1[2]);
			Dfz1[3] = deno * H * (Dangle[3] * angle_z1 + (angle-angle0) * Dangle_z1[3]);
			Dfz1[4] = deno * H * (Dangle[4] * angle_z1 + (angle-angle0) * Dangle_z1[4]);
			Dfz1[5] = deno * H * (Dangle[5] * angle_z1 + (angle-angle0) * Dangle_z1[5]);
			Dfz1[6] = deno * H * (Dangle[6] * angle_z1 + (angle-angle0) * Dangle_z1[6]);
			Dfz1[7] = deno * H * (Dangle[7] * angle_z1 + (angle-angle0) * Dangle_z1[7]);
			Dfz1[8] = deno * H * (Dangle[8] * angle_z1 + (angle-angle0) * Dangle_z1[8]);
			Dfz1[9] = deno * H * (Dangle[9] * angle_z1 + (angle-angle0) * Dangle_z1[9]);
		
			Dfx2[1] = deno * H * (Dangle[1] * angle_x2 + (angle-angle0) * Dangle_x2[1]);
			Dfx2[2] = deno * H * (Dangle[2] * angle_x2 + (angle-angle0) * Dangle_x2[2]);
			Dfx2[3] = deno * H * (Dangle[3] * angle_x2 + (angle-angle0) * Dangle_x2[3]);
			Dfx2[4] = deno * H * (Dangle[4] * angle_x2 + (angle-angle0) * Dangle_x2[4]);
			Dfx2[5] = deno * H * (Dangle[5] * angle_x2 + (angle-angle0) * Dangle_x2[5]);
			Dfx2[6] = deno * H * (Dangle[6] * angle_x2 + (angle-angle0) * Dangle_x2[6]);
			Dfx2[7] = deno * H * (Dangle[7] * angle_x2 + (angle-angle0) * Dangle_x2[7]);
			Dfx2[8] = deno * H * (Dangle[8] * angle_x2 + (angle-angle0) * Dangle_x2[8]);
			Dfx2[9] = deno * H * (Dangle[9] * angle_x2 + (angle-angle0) * Dangle_x2[9]);
		
			Dfy2[1] = deno * H * (Dangle[1] * angle_y2 + (angle-angle0) * Dangle_y2[1]);
			Dfy2[2] = deno * H * (Dangle[2] * angle_y2 + (angle-angle0) * Dangle_y2[2]);
			Dfy2[3] = deno * H * (Dangle[3] * angle_y2 + (angle-angle0) * Dangle_y2[3]);
			Dfy2[4] = deno * H * (Dangle[4] * angle_y2 + (angle-angle0) * Dangle_y2[4]);
			Dfy2[5] = deno * H * (Dangle[5] * angle_y2 + (angle-angle0) * Dangle_y2[5]);
			Dfy2[6] = deno * H * (Dangle[6] * angle_y2 + (angle-angle0) * Dangle_y2[6]);
			Dfy2[7] = deno * H * (Dangle[7] * angle_y2 + (angle-angle0) * Dangle_y2[7]);
			Dfy2[8] = deno * H * (Dangle[8] * angle_y2 + (angle-angle0) * Dangle_y2[8]);
			Dfy2[9] = deno * H * (Dangle[9] * angle_y2 + (angle-angle0) * Dangle_y2[9]);
		
			Dfz2[1] = deno * H * (Dangle[1] * angle_z2 + (angle-angle0) * Dangle_z2[1]);
			Dfz2[2] = deno * H * (Dangle[2] * angle_z2 + (angle-angle0) * Dangle_z2[2]);
			Dfz2[3] = deno * H * (Dangle[3] * angle_z2 + (angle-angle0) * Dangle_z2[3]);
			Dfz2[4] = deno * H * (Dangle[4] * angle_z2 + (angle-angle0) * Dangle_z2[4]);
			Dfz2[5] = deno * H * (Dangle[5] * angle_z2 + (angle-angle0) * Dangle_z2[5]);
			Dfz2[6] = deno * H * (Dangle[6] * angle_z2 + (angle-angle0) * Dangle_z2[6]);
			Dfz2[7] = deno * H * (Dangle[7] * angle_z2 + (angle-angle0) * Dangle_z2[7]);
			Dfz2[8] = deno * H * (Dangle[8] * angle_z2 + (angle-angle0) * Dangle_z2[8]);
			Dfz2[9] = deno * H * (Dangle[9] * angle_z2 + (angle-angle0) * Dangle_z2[9]);
		
			Dfx3[1] = deno * H * (Dangle[1] * angle_x3 + (angle-angle0) * Dangle_x3[1]);
			Dfx3[2] = deno * H * (Dangle[2] * angle_x3 + (angle-angle0) * Dangle_x3[2]);
			Dfx3[3] = deno * H * (Dangle[3] * angle_x3 + (angle-angle0) * Dangle_x3[3]);
			Dfx3[4] = deno * H * (Dangle[4] * angle_x3 + (angle-angle0) * Dangle_x3[4]);
			Dfx3[5] = deno * H * (Dangle[5] * angle_x3 + (angle-angle0) * Dangle_x3[5]);
			Dfx3[6] = deno * H * (Dangle[6] * angle_x3 + (angle-angle0) * Dangle_x3[6]);
			Dfx3[7] = deno * H * (Dangle[7] * angle_x3 + (angle-angle0) * Dangle_x3[7]);
			Dfx3[8] = deno * H * (Dangle[8] * angle_x3 + (angle-angle0) * Dangle_x3[8]);
			Dfx3[9] = deno * H * (Dangle[9] * angle_x3 + (angle-angle0) * Dangle_x3[9]);
		
			Dfy3[1] = deno * H * (Dangle[1] * angle_y3 + (angle-angle0) * Dangle_y3[1]);
			Dfy3[2] = deno * H * (Dangle[2] * angle_y3 + (angle-angle0) * Dangle_y3[2]);
			Dfy3[3] = deno * H * (Dangle[3] * angle_y3 + (angle-angle0) * Dangle_y3[3]);
			Dfy3[4] = deno * H * (Dangle[4] * angle_y3 + (angle-angle0) * Dangle_y3[4]);
			Dfy3[5] = deno * H * (Dangle[5] * angle_y3 + (angle-angle0) * Dangle_y3[5]);
			Dfy3[6] = deno * H * (Dangle[6] * angle_y3 + (angle-angle0) * Dangle_y3[6]);
			Dfy3[7] = deno * H * (Dangle[7] * angle_y3 + (angle-angle0) * Dangle_y3[7]);
			Dfy3[8] = deno * H * (Dangle[8] * angle_y3 + (angle-angle0) * Dangle_y3[8]);
			Dfy3[9] = deno * H * (Dangle[9] * angle_y3 + (angle-angle0) * Dangle_y3[9]);
		
			Dfz3[1] = deno * H * (Dangle[1] * angle_z3 + (angle-angle0) * Dangle_z3[1]);
			Dfz3[2] = deno * H * (Dangle[2] * angle_z3 + (angle-angle0) * Dangle_z3[2]);
			Dfz3[3] = deno * H * (Dangle[3] * angle_z3 + (angle-angle0) * Dangle_z3[3]);
			Dfz3[4] = deno * H * (Dangle[4] * angle_z3 + (angle-angle0) * Dangle_z3[4]);
			Dfz3[5] = deno * H * (Dangle[5] * angle_z3 + (angle-angle0) * Dangle_z3[5]);
			Dfz3[6] = deno * H * (Dangle[6] * angle_z3 + (angle-angle0) * Dangle_z3[6]);
			Dfz3[7] = deno * H * (Dangle[7] * angle_z3 + (angle-angle0) * Dangle_z3[7]);
			Dfz3[8] = deno * H * (Dangle[8] * angle_z3 + (angle-angle0) * Dangle_z3[8]);
			Dfz3[9] = deno * H * (Dangle[9] * angle_z3 + (angle-angle0) * Dangle_z3[9]);
		
					
			/*matrice raideur elementaire k_elem = -Df*/
	  		for (zl = 1; zl<= 9; zl++)	k_elem[ 1][zl] = -Dfx1[zl];
	  		for (zl = 1; zl<= 9; zl++)	k_elem[ 2][zl] = -Dfy1[zl];
	  		for (zl = 1; zl<= 9; zl++)	k_elem[ 3][zl] = -Dfz1[zl];
	  		for (zl = 1; zl<= 9; zl++)	k_elem[ 4][zl] = -Dfx2[zl];
	  		for (zl = 1; zl<= 9; zl++)	k_elem[ 5][zl] = -Dfy2[zl];
	  		for (zl = 1; zl<= 9; zl++)	k_elem[ 6][zl] = -Dfz2[zl];
	  		for (zl = 1; zl<= 9; zl++)	k_elem[ 7][zl] = -Dfx3[zl];
	  		for (zl = 1; zl<= 9; zl++)	k_elem[ 8][zl] = -Dfy3[zl];
	  		for (zl = 1; zl<= 9; zl++)	k_elem[ 9][zl] = -Dfz3[zl];
	  		/*if (elem == 83)
	  			{
	  			for (zk = 1; zk<= 9; zk++)
	  				{
	  				printf("zk %d  \n",zk);
	  				for (zl = 1; zl<= 9; zl++)
	  					{
	  					printf("%7.3lf  ",k_elem[zk][zl]);
	  					}
	  				printf("\n");
	  				}
	  			}*/
					
			if (Structure.type_solver == 1)
			{
				/*rangement de la raideur elementaire dans la matrice globale*/
				/*et Calcul des bornes pour chaque ligne de la matrice de raideur globale*/
	  			for (zl = 1; zl<= 9; zl++)
	  			{
	  				if (zl == 1) ZL = z1;		if (zl == 2) ZL = z1+1;		if (zl == 3) ZL = z1+2;
	  				if (zl == 4) ZL = z2;		if (zl == 5) ZL = z2+1;		if (zl == 6) ZL = z2+2;
	  				if (zl == 7) ZL = z3;		if (zl == 8) ZL = z3+1;		if (zl == 9) ZL = z3+2;
	  				for (zk = 1; zk<= 9; zk++)
	  				{
	  					if (zk == 1) ZK = z1;		if (zk == 2) ZK = z1+1;		if (zk == 3) ZK = z1+2;
	  					if (zk == 4) ZK = z2;		if (zk == 5) ZK = z2+1;		if (zk == 6) ZK = z2+2;
	  					if (zk == 7) ZK = z3;		if (zk == 8) ZK = z3+1;		if (zk == 9) ZK = z3+2;
	  					ze[ZL][eca+ZK-ZL] += k_elem[zl][zk];/**/
								
						if (rang[1][ZL] < ZK) rang[1][ZL] = ZK; 	/*borne basse  de la raideur ze*/
						if (rang[2][ZL] < ZK) rang[2][ZL] = ZK;		/*borne droite de la raideur ze*/ 
						if (rang[3][ZL] > ZK) rang[3][ZL] = ZK; 	/*borne haute  de la raideur ze*/
						if (rang[4][ZL] > ZK) rang[4][ZL] = ZK; 	/*borne gauche de la raideur ze*/
					}
				}
			}
			else if (Structure.type_solver == 2)
      			{
				for (zl=0;zl<9;zl++)
				{
					ii = new_coor(zl, (z1+2)/3, (z2+2)/3, (z3+2)/3, 0);
					for (zk=0;zk<9;zk++)
					{
						jj = new_coor(zk, (z1+2)/3, (z2+2)/3, (z3+2)/3, 0);
						affectation_pardiso (k_elem[zl+1][zk+1], ii, jj);
							
						if (rang[1][ii] < jj) rang[1][ii] = jj; 	/*borne basse  de la raideur ze*/
						if (rang[2][ii] < jj) rang[2][ii] = jj;		/*borne droite de la raideur ze*/ 
						if (rang[3][ii] > jj) rang[3][ii] = jj; 	/*borne haute  de la raideur ze*/
						if (rang[4][ii] > jj) rang[4][ii] = jj; 	/*borne gauche de la raideur ze*/
					}
				}
      			}	

			
			Surface[elem].energy_ouverture += 0.5 * H * angle * angle * 1.0/2.0 * deno;
		
	      		/*TEST_debut
	      			if (zu == 0)
	      				{
	      				nX = nx;	nY = ny;	nZ = nz;
	      				mX = mx;	mY = my;	mZ = mz;
	       				nN = nn;	mM = mm;
	      				scA = sca;	coeF = coef;	anglE = angle;
					fX1 = fx1;	fY1 = fy1;	fZ1 = fz1;	fX2 = fx2;	fY2 = fy2;	fZ2 = fz2;	fX3 = fx3;	fY3 = fy3;	fZ3 = fz3;
	     				}
	       			if ((zu > 0) && (zu < 10)) 
					{
					DnX[zu] = (nx - nX) / delta_x;	DnY[zu] = (ny - nY) / delta_x;	DnZ[zu] = (nz - nZ) / delta_x;
					DmX[zu] = (mx - mX) / delta_x;	DmY[zu] = (my - mY) / delta_x;	DmZ[zu] = (mz - mZ) / delta_x;
					DnN[zu] = (nn - nN) / delta_x;	DmM[zu] = (mm - mM) / delta_x;
					DscA[zu] = (sca - scA) / delta_x;	DcoeF[zu] = (coef - coeF) / delta_x;	DanglE[zu] = (angle - anglE) / delta_x;
					DfX1[zu] = (fx1 - fX1) / delta_x;	DfY1[zu] = (fy1 - fY1) / delta_x;	DfZ1[zu] = (fz1 - fZ1) / delta_x;
					DfX2[zu] = (fx2 - fX2) / delta_x;	DfY2[zu] = (fy2 - fY2) / delta_x;	DfZ2[zu] = (fz2 - fZ2) / delta_x;
					DfX3[zu] = (fx3 - fX3) / delta_x;	DfY3[zu] = (fy3 - fY3) / delta_x;	DfZ3[zu] = (fz3 - fZ3) / delta_x;
					}
	       			if (zu == 1) 	xx1 = xx1 - delta_x;
	     			if (zu == 2)	yy1 = yy1 - delta_x;
	      			if (zu == 3)	zz1 = zz1 - delta_x;
	      			if (zu == 4)	xx2 = xx2 - delta_x;
	      			if (zu == 5)	yy2 = yy2 - delta_x;
	      			if (zu == 6)	zz2 = zz2 - delta_x;
	      			if (zu == 7)	xx3 = xx3 - delta_x;
	      			if (zu == 8)	yy3 = yy3 - delta_x;
	      			if (zu == 9)	zz3 = zz3 - delta_x;
				printf("f %7.3lf %7.3lf %7.3lf   %7.3lf %7.3lf %7.3lf   %7.3lf %7.3lf %7.3lf   \n",fx1,fy1,fz1,fx2,fy2,fz2,fx3,fy3,fz3);
	      			}
		
			printf("Dnx =");       imprvectreel(9, Dnx);	printf("DnX =");       imprvectreel(9, DnX);
			printf("Dny =");       imprvectreel(9, Dny);	printf("DnY =");       imprvectreel(9, DnY);
			printf("Dnz =");       imprvectreel(9, Dnz);	printf("DnZ =");       imprvectreel(9, DnZ);
			printf("Dmx =");       imprvectreel(9, Dmx);	printf("DmX =");       imprvectreel(9, DmX);
			printf("Dmy =");       imprvectreel(9, Dmy);	printf("DmY =");       imprvectreel(9, DmY);
			printf("Dmz =");       imprvectreel(9, Dmz);	printf("DmZ =");       imprvectreel(9, DmZ);
			printf("Dnn =");       imprvectreel(9, Dnn);	printf("DnN =");       imprvectreel(9, DnN);
			printf("Dmm =");       imprvectreel(9, Dmm);	printf("DmM =");       imprvectreel(9, DmM);
			printf("Dsca =");      imprvectreel(9, Dsca);	printf("DscA =");      imprvectreel(9, DscA);
			printf("Dangle =");    imprvectreel(9, Dangle); printf("DanglE =");    imprvectreel(9, DanglE);
			printf("Dcoef =");     imprvectreel(9, Dcoef);	printf("DcoeF =");     imprvectreel(9, DcoeF);
			printf("Dfx1 =");      imprvectreel(9, Dfx1);	printf("DfX1 =");      imprvectreel(9, DfX1);
			printf("Dfy1 =");      imprvectreel(9, Dfy1);	printf("DfY1 =");      imprvectreel(9, DfY1);
			printf("Dfz1 =");      imprvectreel(9, Dfz1);	printf("DfZ1 =");      imprvectreel(9, DfZ1);
	 		printf("Dfx2 =");      imprvectreel(9, Dfx2);	printf("DfX2 =");      imprvectreel(9, DfX2);
			printf("Dfy2 =");      imprvectreel(9, Dfy2);	printf("DfY2 =");      imprvectreel(9, DfY2);
			printf("Dfz2 =");      imprvectreel(9, Dfz2);	printf("DfZ2 =");      imprvectreel(9, DfZ2);
	 		printf("Dfx3 =");      imprvectreel(9, Dfx3);	printf("DfX3 =");      imprvectreel(9, DfX3);
			printf("Dfy3 =");      imprvectreel(9, Dfy3);	printf("DfY3 =");      imprvectreel(9, DfY3);
			printf("Dfz3 =");      imprvectreel(9, Dfz3);	printf("DfZ3 =");      imprvectreel(9, DfZ3);
	 				
	   		exit(0);
	      		TEST_fin*/
      			}
      		
		}
	/*imprvectreel(320, wasurf);
	exit(0);*/ 			
	}
