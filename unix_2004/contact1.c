#define PRINCIPAL 0
#include "4c19.h"  

void contact1()
{
	//printf("debut contact11\n");     			
  	/* 
  	Calculation of forces and stiffness due to contact between elements. 
     	*/
     	int zg,zh,zi,zj,zk,zl,za,zb,zc,zd,zm,Cas,zu,typ1,typ2,cable_slave;
     	int caa,cab,baa,bab,noa,nob;
     	double u1[4],u2[4],u[4];
     	double v1[4],v2[4],v[4];
     	double vtmp[4],nn[4],alpha,beta,gamma,denom,dist,norm_n;
     	double D10,D20,D1,D2,F10,F20;
     	double Fu1[4],Fu2[4],Fv1[4],Fv2[4];
     	double P1[4],P2[4],P3[4],P4[4];
     	double Fp1[4],Fp2[4],Fp3[4],Fp4[4];
     	double Fo1[4],Fo2[4],Fo3[4],Fo4[4];
     	double delta_x,KK[13][13];;
  	
	delta_x = 0.00000001;
	//printf("contact \n");
	
	for (caa = 1 ; caa<= Structure.NbTypeelem-1 ; caa++) 
	{  	
		if (TypeElement[caa].nb_cable_contact > 0)
		{
			//printf("cable caa %d could be in contact\n",caa);			
			for (zh = 1 ; zh<= TypeElement[caa].nb_cable_contact; zh++) 
			{  
				cab = TypeElement[caa].cable_contact[zh];			
				//printf("cable caa %d could be in contact with cab %d\n",caa,cab);			
				for (baa = 1 ; baa<= TypeElement[caa].nb_barre; baa++) 
				{  	
					noa = TypeElement[caa].barre[baa];
					for (bab = 1 ; bab<= TypeElement[cab].nb_barre; bab++) 
					{  	
						nob = TypeElement[cab].barre[bab];
						//printf("bar %4d of cable %4d and bar %4d of cable %4d could be in contact \n",noa,caa,nob,cab);			
						//bar 1
						zi = yb(noa,1); 	zj = yb(noa,4); 	      			
						P1[1] = wf[zi+0];	P1[2] = wf[zi+1];	P1[3] = wf[zi+2];
						P2[1] = wf[zj+0];	P2[2] = wf[zj+1];	P2[3] = wf[zj+2];
						Cas = 0;
						//bar 2
						zk = yb(nob,1); 	zl = yb(nob,4); 	    
//printf("zi %4d zj %4d zk %4d zl %4d \n",zi,zj,zk,zl);			
//exit(0);
						if ((zk!=zi) && (zk!=zj) && (zl!=zi) && (zl!=zj))
						{  			
							P3[1] = wf[zk+0];	P3[2] = wf[zk+1];	P3[3] = wf[zk+2];
							P4[1] = wf[zl+0];	P4[2] = wf[zl+1];	P4[3] = wf[zl+2];
							Cas = contact_base(P1, P2, P3, P4, noa, nob, Fp1, Fp2, Fp3, Fp4);
				    			waelem[zi+0] += Fp1[1];	waelem[zi+1] += Fp1[2];	waelem[zi+2] += Fp1[3];
				    			waelem[zj+0] += Fp2[1];	waelem[zj+1] += Fp2[2];	waelem[zj+2] += Fp2[3];
				    			waelem[zk+0] += Fp3[1];	waelem[zk+1] += Fp3[2];	waelem[zk+2] += Fp3[3];
				    			waelem[zl+0] += Fp4[1];	waelem[zl+1] += Fp4[2];	waelem[zl+2] += Fp4[3];
							for( zu = 1 ; zu <= 3 ; zu++ )
				      			{
				      				Fo1[zu] = Fp1[zu];
				      				Fo2[zu] = Fp2[zu];
				      				Fo3[zu] = Fp3[zu];
				      				Fo4[zu] = Fp4[zu];
				      			}
				    			
							for( zu = 1 ; zu <= 12 ; zu++ )
				      			{
				      				if (zu == 1) P1[1] += delta_x;
				      				if (zu == 2) P1[2] += delta_x;
				      				if (zu == 3) P1[3] += delta_x;
				      				if (zu == 4) P2[1] += delta_x;
				      				if (zu == 5) P2[2] += delta_x;
				      				if (zu == 6) P2[3] += delta_x;
				      				if (zu == 7) P3[1] += delta_x;
				      				if (zu == 8) P3[2] += delta_x;
				      				if (zu == 9) P3[3] += delta_x;
				      				if (zu ==10) P4[1] += delta_x;
				      				if (zu ==11) P4[2] += delta_x;
				      				if (zu ==12) P4[3] += delta_x;
								Cas = contact_base(P1, P2, P3, P4, noa, nob, Fp1, Fp2, Fp3, Fp4);

			     					KK[ 1][zu] = (Fo1[1]-Fp1[1])/delta_x;	KK[ 2][zu] = (Fo1[2]-Fp1[2])/delta_x;	KK[ 3][zu] = (Fo1[3]-Fp1[3])/delta_x;
			      					KK[ 4][zu] = (Fo2[1]-Fp2[1])/delta_x;	KK[ 5][zu] = (Fo2[2]-Fp2[2])/delta_x;	KK[ 6][zu] = (Fo2[3]-Fp2[3])/delta_x;
			      					KK[ 7][zu] = (Fo3[1]-Fp3[1])/delta_x;	KK[ 8][zu] = (Fo3[2]-Fp3[2])/delta_x;	KK[ 9][zu] = (Fo3[3]-Fp3[3])/delta_x;
			      					KK[10][zu] = (Fo4[1]-Fp4[1])/delta_x;	KK[11][zu] = (Fo4[2]-Fp4[2])/delta_x;	KK[12][zu] = (Fo4[3]-Fp4[3])/delta_x;
			 
				      				if (zu == 1) P1[1] -= delta_x;
				      				if (zu == 2) P1[2] -= delta_x;
				      				if (zu == 3) P1[3] -= delta_x;
				      				if (zu == 4) P2[1] -= delta_x;
				      				if (zu == 5) P2[2] -= delta_x;
				      				if (zu == 6) P2[3] -= delta_x;
				      				if (zu == 7) P3[1] -= delta_x;
				      				if (zu == 8) P3[2] -= delta_x;
				      				if (zu == 9) P3[3] -= delta_x;
				      				if (zu ==10) P4[1] -= delta_x;
				      				if (zu ==11) P4[2] -= delta_x;
								if (zu ==12) P4[3] -= delta_x;
				      			}
				      			//imprmatreel3( 1, 12,  1,  12,  KK, 13);
							for( za = 1 ; za <= 12 ; za++ )
				      			{
				      				if (za >= 1) zc = zi+za- 1;
				      				if (za >= 4) zc = zj+za- 4;
				      				if (za >= 7) zc = zk+za- 7;
				      				if (za >=10) zc = zl+za-10;
								for( zb = 1 ; zb <= 12 ; zb++ )
					      			{
					      				if (zb >= 1) zd = zi+zb- 1;
					      				if (zb >= 4) zd = zj+zb- 4;
					      				if (zb >= 7) zd = zk+zb- 7;
					      				if (zb >=10) zd = zl+zb-10;
									affectation_ze_rang(zc, zd, KK[za][zb]);
									//printf("za %4d zb %4d zc %4d zd %4d KK %lf\n",za,zb,zc,zd,KK[za][zb]);
					      			}
				      			}
						}
					}
			
				}
			}
		}			 	      			
	}
	//exit(0);
}

int contact_base(double p1[4], double p2[4], double p3[4], double p4[4], int elem_12, int elem_34, double *fp1, double *fp2, double *fp3, double *fp4)
{
     	double u[4],v[4],vtmp[4],nn[4],alpha,beta,gamma,denom,dist,norm_n,dir[4],wtmp[4],xtmp[4];
     	double D10,D20,D1,D2,F10,F20;
     	int type_12,type_34,cas;
     	
     	cas = 0;	//default value no contact between bar 12 (elem_12) and bar 34 (elem_34)
	fp1[1] =  0.0;	fp1[2] =  0.0;	fp1[3] =  0.0;
	fp2[1] =  0.0;	fp2[2] =  0.0;	fp2[3] =  0.0;
	fp3[1] =  0.0;	fp3[2] =  0.0;	fp3[3] =  0.0;
	fp4[1] =  0.0;	fp4[2] =  0.0;	fp4[3] =  0.0;
	add_scal_vect_2(1.0, p2, -1.0, p1, u);	//u = p2-p1
	add_scal_vect_2(1.0, p4, -1.0, p3, v);	//v = p4-p3
	produit_vect3(u, v, nn);
	type_12 = Element[elem_12].type;
	type_34 = Element[elem_34].type;
	denom = nn[1]*(u[3]*v[2]-u[2]*v[3])+u[1]*(nn[2]*v[3]-nn[3]*v[2])+(nn[3]*u[2]-nn[2]*u[3])*v[1];
	if (denom == 0.0)
	{
		cas = 10;
	}
	else
	{
		alpha=(nn[1]*(-p4[2]*v[3]+p1[2]*v[3]+(p4[3]-p1[3])*v[2])+p4[1]*(nn[2]*v[3]-nn[3]*v[2])+p1[1]*(nn[3]*v[2]-nn[2]*v[3])+(nn[2]*(p1[3]-p4[3])+nn[3]*p4[2]-nn[3]*p1[2])*v[1])/denom;
		beta=-(u[1]*(-p4[2]*v[3]+p1[2]*v[3]+(p4[3]-p1[3])*v[2])+p4[1]*(u[2]*v[3]-u[3]*v[2])+p1[1]*(u[3]*v[2]-u[2]*v[3])+(u[2]*(p1[3]-p4[3])+u[3]*p4[2]-p1[2]*u[3])*v[1])/denom;
		gamma=(u[1]*(nn[2]*(p4[3]-p1[3])-nn[3]*p4[2]+nn[3]*p1[2])+nn[1]*(u[2]*(p1[3]-p4[3])+u[3]*p4[2]-p1[2]*u[3])+(nn[3]*u[2]-nn[2]*u[3])*p4[1]+p1[1]*(nn[2]*u[3]-nn[3]*u[2]))/denom;
		/*printf(" g %4d ",elem_12);
		printf("   h %4d ",elem_34);
		printf("  denom %10.0lf",denom);
		printf("  alpha %6.3lf",alpha);
		printf("  beta %6.3lf",beta);
		printf("  gamma %6.3lf\n",gamma);*/
		//printf("  dist %6.3lf\n",dist);
		if ((alpha >= 0.0) && (alpha <= 1.0) && (gamma >= 0.0) && (gamma <= 1.0))
		{
			add_scal_vect_1(beta, nn, dir);	//dir = beta*nn
			dist = sqrt(produit_scal(dir,dir));
			if (dist < (Element[elem_12].diametrehydro+Element[elem_34].diametrehydro)/2.0)
			{
				cas = 1;
				//bar 12 contact with bar 34
				D10 = Element[elem_12].diametrehydro;
				D20 = Element[elem_34].diametrehydro;
				D1 = 2.0*dist*D10 / (D10+D20);
				D2 = 2.0*dist*D20 / (D10+D20);
				F10 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D1-D10)/D10;
				F20 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D2-D20)/D20;
				fp1[1] =  F10*(1.0-alpha)*dir[1]/dist;
				fp1[2] =  F10*(1.0-alpha)*dir[2]/dist;
				fp1[3] =  F10*(1.0-alpha)*dir[3]/dist;
				fp2[1] =  F10*(    alpha)*dir[1]/dist;
				fp2[2] =  F10*(    alpha)*dir[2]/dist;
				fp2[3] =  F10*(    alpha)*dir[3]/dist;
				fp3[1] = -F10*(    gamma)*dir[1]/dist;
				fp3[2] = -F10*(    gamma)*dir[2]/dist;
				fp3[3] = -F10*(    gamma)*dir[3]/dist;
				fp4[1] = -F10*(1.0-gamma)*dir[1]/dist;
				fp4[2] = -F10*(1.0-gamma)*dir[2]/dist;
				fp4[3] = -F10*(1.0-gamma)*dir[3]/dist;
			}
		}
		if ((alpha <= 0.0) && (gamma >= 0.0) && (gamma <= 1.0))
		{
			add_scal_vect_2(alpha, u, beta, nn, dir);	//dir = alpha*u+beta*nn
			dist = sqrt(produit_scal(dir,dir));
			if (dist < (Element[elem_12].diametrehydro+Element[elem_34].diametrehydro)/2.0)
			{
				cas = 2;
				//extremity 1 contact with bar 34
				D10 = Element[elem_12].diametrehydro;
				D20 = Element[elem_34].diametrehydro;
				D1 = 2.0*dist*D10 / (D10+D20);
				D2 = 2.0*dist*D20 / (D10+D20);
				F10 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D1-D10)/D10;
				F20 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D2-D20)/D20;
				fp1[1] =  F10*(1.0      )*dir[1]/dist;
				fp1[2] =  F10*(1.0      )*dir[2]/dist;
				fp1[3] =  F10*(1.0      )*dir[3]/dist;
				fp2[1] =  F10*(0.0      )*dir[1]/dist;
				fp2[2] =  F10*(0.0      )*dir[2]/dist;
				fp2[3] =  F10*(0.0      )*dir[3]/dist;
				fp3[1] = -F10*(    gamma)*dir[1]/dist;
				fp3[2] = -F10*(    gamma)*dir[2]/dist;
				fp3[3] = -F10*(    gamma)*dir[3]/dist;
				fp4[1] = -F10*(1.0-gamma)*dir[1]/dist;
				fp4[2] = -F10*(1.0-gamma)*dir[2]/dist;
				fp4[3] = -F10*(1.0-gamma)*dir[3]/dist;
			}
		}
		if ((alpha >= 1.0) && (gamma >= 0.0) && (gamma <= 1.0))
		{
			add_scal_vect_3(alpha, u, -1.0, u, beta, nn, dir);	//dir = alpha*u+-u+beta*nn
			dist = sqrt(produit_scal(dir,dir));
			if (dist < (Element[elem_12].diametrehydro+Element[elem_34].diametrehydro)/2.0)
			{
				cas = 3;
				//extremity 2 contact with bar 34
				D10 = Element[elem_12].diametrehydro;
				D20 = Element[elem_34].diametrehydro;
				D1 = 2.0*dist*D10 / (D10+D20);
				D2 = 2.0*dist*D20 / (D10+D20);
				F10 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D1-D10)/D10;
				F20 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D2-D20)/D20;
				fp1[1] =  F10*(0.0      )*dir[1]/dist;
				fp1[2] =  F10*(0.0      )*dir[2]/dist;
				fp1[3] =  F10*(0.0      )*dir[3]/dist;
				fp2[1] =  F10*(1.0      )*dir[1]/dist;
				fp2[2] =  F10*(1.0      )*dir[2]/dist;
				fp2[3] =  F10*(1.0      )*dir[3]/dist;
				fp3[1] = -F10*(    gamma)*dir[1]/dist;
				fp3[2] = -F10*(    gamma)*dir[2]/dist;
				fp3[3] = -F10*(    gamma)*dir[3]/dist;
				fp4[1] = -F10*(1.0-gamma)*dir[1]/dist;
				fp4[2] = -F10*(1.0-gamma)*dir[2]/dist;
				fp4[3] = -F10*(1.0-gamma)*dir[3]/dist;
			}
		}
		if ((alpha >= 0.0) && (alpha <= 1.0) && (gamma <= 0.0))
		{
			add_scal_vect_2(beta, nn, gamma, v, dir);	//dir = beta*nn+gamma*v
			dist = sqrt(produit_scal(dir,dir));
			if (dist < (Element[elem_12].diametrehydro+Element[elem_34].diametrehydro)/2.0)
			{
				cas = 4;
				//bar 12 contact with extremity 4
				D10 = Element[elem_12].diametrehydro;
				D20 = Element[elem_34].diametrehydro;
				D1 = 2.0*dist*D10 / (D10+D20);
				D2 = 2.0*dist*D20 / (D10+D20);
				F10 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D1-D10)/D10;
				F20 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D2-D20)/D20;
				fp1[1] =  F10*(1.0-alpha)*dir[1]/dist;
				fp1[2] =  F10*(1.0-alpha)*dir[2]/dist;
				fp1[3] =  F10*(1.0-alpha)*dir[3]/dist;
				fp2[1] =  F10*(    alpha)*dir[1]/dist;
				fp2[2] =  F10*(    alpha)*dir[2]/dist;
				fp2[3] =  F10*(    alpha)*dir[3]/dist;
				fp3[1] = -F10*(0.0      )*dir[1]/dist;
				fp3[2] = -F10*(0.0      )*dir[2]/dist;
				fp3[3] = -F10*(0.0      )*dir[3]/dist;
				fp4[1] = -F10*(1.0      )*dir[1]/dist;
				fp4[2] = -F10*(1.0      )*dir[2]/dist;
				fp4[3] = -F10*(1.0      )*dir[3]/dist;
			}
		}
		if ((alpha >= 0.0) && (alpha <= 1.0) && (gamma >= 1.0))
		{
			add_scal_vect_3(beta, nn, -gamma, v, 1.0, v, dir);	//dir = beta*nn-gamma*v+v
			dist = sqrt(produit_scal(dir,dir));
			if (dist < (Element[elem_12].diametrehydro+Element[elem_34].diametrehydro)/2.0)
			{
				cas = 5;
				//bar 12 contact with extremity 3
				D10 = Element[elem_12].diametrehydro;
				D20 = Element[elem_34].diametrehydro;
				D1 = 2.0*dist*D10 / (D10+D20);
				D2 = 2.0*dist*D20 / (D10+D20);
				F10 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D1-D10)/D10;
				F20 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D2-D20)/D20;
				fp1[1] =  F10*(1.0-alpha)*dir[1]/dist;
				fp1[2] =  F10*(1.0-alpha)*dir[2]/dist;
				fp1[3] =  F10*(1.0-alpha)*dir[3]/dist;
				fp2[1] =  F10*(    alpha)*dir[1]/dist;
				fp2[2] =  F10*(    alpha)*dir[2]/dist;
				fp2[3] =  F10*(    alpha)*dir[3]/dist;
				fp3[1] = -F10*(1.0      )*dir[1]/dist;
				fp3[2] = -F10*(1.0      )*dir[2]/dist;
				fp3[3] = -F10*(1.0      )*dir[3]/dist;
				fp4[1] = -F10*(0.0      )*dir[1]/dist;
				fp4[2] = -F10*(0.0      )*dir[2]/dist;
				fp4[3] = -F10*(0.0      )*dir[3]/dist;
			}
		}
		if ((alpha <= 0.0) && (gamma <= 0.0))
		{
			add_scal_vect_3(alpha, u, beta, nn, gamma, v, dir);	//dir = alpha*u+beta*nn+gamma*v
			dist = sqrt(produit_scal(dir,dir));
			if (dist < (Element[elem_12].diametrehydro+Element[elem_34].diametrehydro)/2.0)
			{
				cas = 6;
				//extremity 1 contact with extremity 4
				D10 = Element[elem_12].diametrehydro;
				D20 = Element[elem_34].diametrehydro;
				D1 = 2.0*dist*D10 / (D10+D20);
				D2 = 2.0*dist*D20 / (D10+D20);
				F10 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D1-D10)/D10;
				F20 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D2-D20)/D20;
				fp1[1] =  F10*(1.0      )*dir[1]/dist;
				fp1[2] =  F10*(1.0      )*dir[2]/dist;
				fp1[3] =  F10*(1.0      )*dir[3]/dist;
				fp2[1] =  F10*(0.0      )*dir[1]/dist;
				fp2[2] =  F10*(0.0      )*dir[2]/dist;
				fp2[3] =  F10*(0.0      )*dir[3]/dist;
				fp3[1] = -F10*(0.0      )*dir[1]/dist;
				fp3[2] = -F10*(0.0      )*dir[2]/dist;
				fp3[3] = -F10*(0.0      )*dir[3]/dist;
				fp4[1] = -F10*(1.0      )*dir[1]/dist;
				fp4[2] = -F10*(1.0      )*dir[2]/dist;
				fp4[3] = -F10*(1.0      )*dir[3]/dist;
			}
		}
		if ((alpha >= 1.0) && (gamma <= 0.0))
		{
			add_scal_vect_4(alpha, u, -1.0, u, beta, nn, gamma, v, dir);	//dir = alpha*u-u+beta*nn+gamma*v
			dist = sqrt(produit_scal(dir,dir));
			if (dist < (Element[elem_12].diametrehydro+Element[elem_34].diametrehydro)/2.0)
			{
				cas = 7;
				//extremity 2 contact with extremity 4
				D10 = Element[elem_12].diametrehydro;
				D20 = Element[elem_34].diametrehydro;
				D1 = 2.0*dist*D10 / (D10+D20);
				D2 = 2.0*dist*D20 / (D10+D20);
				F10 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D1-D10)/D10;
				F20 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D2-D20)/D20;
				fp1[1] =  F10*(0.0      )*dir[1]/dist;
				fp1[2] =  F10*(0.0      )*dir[2]/dist;
				fp1[3] =  F10*(0.0      )*dir[3]/dist;
				fp2[1] =  F10*(1.0      )*dir[1]/dist;
				fp2[2] =  F10*(1.0      )*dir[2]/dist;
				fp2[3] =  F10*(1.0      )*dir[3]/dist;
				fp3[1] = -F10*(0.0      )*dir[1]/dist;
				fp3[2] = -F10*(0.0      )*dir[2]/dist;
				fp3[3] = -F10*(0.0      )*dir[3]/dist;
				fp4[1] = -F10*(1.0      )*dir[1]/dist;
				fp4[2] = -F10*(1.0      )*dir[2]/dist;
				fp4[3] = -F10*(1.0      )*dir[3]/dist;
			}
		}
		if ((alpha <= 0.0) && (gamma >= 1.0))
		{
			add_scal_vect_4(alpha, u, beta, nn, gamma, v, -1.0, v, dir); //dir=alpha*u+beta*nn+gamma*v-v
			dist = sqrt(produit_scal(dir,dir));
			if (dist < (Element[elem_12].diametrehydro+Element[elem_34].diametrehydro)/2.0)
			{
				cas = 8;
				//extremity 1 contact with extremity 3
				D10 = Element[elem_12].diametrehydro;
				D20 = Element[elem_34].diametrehydro;
				D1 = 2.0*dist*D10 / (D10+D20);
				D2 = 2.0*dist*D20 / (D10+D20);
				F10 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D1-D10)/D10;
				F20 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D2-D20)/D20;
				fp1[1] =  F10*(1.0      )*dir[1]/dist;
				fp1[2] =  F10*(1.0      )*dir[2]/dist;
				fp1[3] =  F10*(1.0      )*dir[3]/dist;
				fp2[1] =  F10*(0.0      )*dir[1]/dist;
				fp2[2] =  F10*(0.0      )*dir[2]/dist;
				fp2[3] =  F10*(0.0      )*dir[3]/dist;
				fp3[1] = -F10*(1.0      )*dir[1]/dist;
				fp3[2] = -F10*(1.0      )*dir[2]/dist;
				fp3[3] = -F10*(1.0      )*dir[3]/dist;
				fp4[1] = -F10*(0.0      )*dir[1]/dist;
				fp4[2] = -F10*(0.0      )*dir[2]/dist;
				fp4[3] = -F10*(0.0      )*dir[3]/dist;
			}
		}
		if ((alpha >= 1.0) && (gamma >= 1.0))
		{
			add_scal_vect_5(alpha, u, -1.0, u, beta, nn, gamma, v, -1.0, v, dir); //dir=alpha*u+beta*nn+gamma*v-v
			dist = sqrt(produit_scal(dir,dir));
			if (dist < (Element[elem_12].diametrehydro+Element[elem_34].diametrehydro)/2.0)
			{
				cas = 9;
				//extremity 2 contact with extremity 3
				D10 = Element[elem_12].diametrehydro;
				D20 = Element[elem_34].diametrehydro;
				D1 = 2.0*dist*D10 / (D10+D20);
				D2 = 2.0*dist*D20 / (D10+D20);
				F10 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D1-D10)/D10;
				F20 = (Element[elem_12].raideur_traction + Element[elem_34].raideur_traction)*(D2-D20)/D20;
				fp1[1] =  F10*(0.0      )*dir[1]/dist;
				fp1[2] =  F10*(0.0      )*dir[2]/dist;
				fp1[3] =  F10*(0.0      )*dir[3]/dist;
				fp2[1] =  F10*(1.0      )*dir[1]/dist;
				fp2[2] =  F10*(1.0      )*dir[2]/dist;
				fp2[3] =  F10*(1.0      )*dir[3]/dist;
				fp3[1] = -F10*(1.0      )*dir[1]/dist;
				fp3[2] = -F10*(1.0      )*dir[2]/dist;
				fp3[3] = -F10*(1.0      )*dir[3]/dist;
				fp4[1] = -F10*(0.0      )*dir[1]/dist;
				fp4[2] = -F10*(0.0      )*dir[2]/dist;
				fp4[3] = -F10*(0.0      )*dir[3]/dist;
			}
		}
		if (cas != 0) 
			{
			//printf("cas %d\n",cas);
			//exit(0);
			}
		/*
		if (cas == 0)
		{
			printf("elem_12  %4d ",elem_12);
			printf("elem_34  %4d ",elem_34);
			printf("denom %10.0lf  ",denom);
			printf("alpha %6.3lf  ",alpha);
			printf("beta %6.3lf  ",beta);
			printf("gamma %6.3lf  ",gamma);
			printf("dist %6.3lf \n",dist);
			imprvectreel1(3, 3, p1);
			imprvectreel1(3, 3, p2);
			imprvectreel1(3, 3, p3);
			imprvectreel1(3, 3, p4);
			printf("cas %d\n",cas);
			exit(0);
		}
		*/
	}
	return cas;	
}

