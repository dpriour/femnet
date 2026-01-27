#define PRINCIPAL 0
#include "4c19.h"

void pliage_triangle4()
	{
	/*
	ATTENTION : non prise en compte des plans de symmetrie
	efforts wae d un panneau de filet qui se plie les efforts sont calcules
	pour tout les plis aux noeuds appartenant a un panneau de filet ces noeuds
	n etant pas sur le pourtour de ce panneau de filet
	le couple entre 2 triangles voisins est proportionel a la courbure estimée entre les fils des 2 triangle
	*/
	int ii, jj;
  	int elem1,elem2,elem3,za,zg,zu,z1,z2,z3,z4,trouve,trouve_sym,signe,zl,zk,ZL,ZK;
  	double hh,delta_x,nb1,nb2;
  	double nx,ny,nz,mx,my,mz,nn,mm,ps,u1,u2,u3,u4,v1,v2,v3,v4,U1,U2,U3,U4,V1,V2,V3,V4,n2,m2;
	double d1,d2,coef,seuil,acos_a,UU,VV,UP,VP;
	double Alpha,lamda,pxx,qxx,aa,bb,cc,pp,rho,couple,racine,racine2;
	
	double n_vector[4],m_vector[4],v_vector[5],d_vector[3],coord_vector[13];
	double xx1,xx2,xx3,xx4,yy1,yy2,yy3,yy4,zz1,zz2,zz3,zz4,f_x1,f_y1,f_z1,f_x2,f_y2,f_z2,f_x3,f_y3,f_z3,f_x4,f_y4,f_z4;
	
	double dcc[13],dpp[13],drho[13],dracine[13];
	double d_alpha_x1[13],d_alpha_y1[13],d_alpha_z1[13],d_alpha_x2[13],d_alpha_y2[13],d_alpha_z2[13],d_alpha_x3[13],d_alpha_y3[13],d_alpha_z3[13],d_alpha_x4[13],d_alpha_y4[13],d_alpha_z4[13];
	double alpha_x1,alpha_y1,alpha_z1,alpha_x2,alpha_y2,alpha_z2,alpha_x3,alpha_y3,alpha_z3,alpha_x4,alpha_y4,alpha_z4;
	double dfxyz[13][13],dnx[13],dny[13],dnz[13],dmx[13],dmy[13],dmz[13],fxyz[13],dps[13],dnn[13],dmm[13],dAlpha[13],dcoef[13];
 	double d_fx1[13],d_fy1[13],d_fz1[13],d_fx2[13],d_fy2[13],d_fz2[13],d_fx3[13],d_fy3[13],d_fz3[13],d_fx4[13],d_fy4[13],d_fz4[13];
 	double k_elem[13][13];

  	double nX,nY,nZ,mX,mY,mZ,nN,mM,pS,coeF,AlphA,cC,pP,racinE;
  	double dnX[13],dnY[13],dnZ[13],dmX[13],dmY[13],dmZ[13],dnN[13],dmM[13],dpS[13],dcoeF[13],dAlphA[13],dcC[13],dpP[13],dracinE[13];
	double f_X1,f_Y1,f_Z1,f_X2,f_Y2,f_Z2,f_X3,f_Y3,f_Z3,f_X4,f_Y4,f_Z4,D_alpha_x1[13],D_alpha_x2[13],Alpha_x1,Alpha_x2;
 	double d_fX1[13],d_fY1[13],d_fZ1[13],d_fX2[13],d_fY2[13],d_fZ2[13],d_fX3[13],d_fY3[13],d_fZ3[13],d_fX4[13],d_fY4[13],d_fZ4[13];

  	for (elem1 = 1; elem1<= NOMBRE_SURFACES-1; elem1++)/**/
  		{
		if (Surface[elem1].EI_flexion > 0.0)
			{
	  		hh =  Surface[elem1].EI_flexion;
			/*printf("elem1 = %5d hh = %lf       \n",elem1,hh);*/
	  		for (za = 1; za<= 3; za++)
	  			{
	  			/*faire pour les 3 sommets du triangle elem1, z1 est le sommet 1 z3 et z4 les sommets 3 et 4*/
	  			/*if((elem1 == 1206) && (za == 1))
					{
					printf("elem1 = %5d za = %5d       \n",elem1,za);
					}*/
	    			if (za == 1) 
					{
					/*le point z1 est sur le sommet 1 => le point z4 (z3) sur le sommet 2 (3)*/
					z1 = yc(elem1,1);  z4 = yc(elem1,4);  z3 = yc(elem1,7);
					U1 =   Surface[elem1].lon[1] + Surface[elem1].lon[2]; 
					U4 =   Surface[elem1].lon[3] + Surface[elem1].lon[4]; 
					U3 =   Surface[elem1].lon[5] + Surface[elem1].lon[6]; 
					V1 = - Surface[elem1].lon[1] + Surface[elem1].lon[2]; 
					V4 = - Surface[elem1].lon[3] + Surface[elem1].lon[4]; 
					V3 = - Surface[elem1].lon[5] + Surface[elem1].lon[6];
					trouve = Surface[elem1].voisin_1.exist;
					elem2 = Surface[elem1].voisin_1.elem_voisin;
					z2 = Surface[elem1].voisin_1.sommet_oppose;
					U2 = Surface[elem1].voisin_1.U_oppose;
					V2 = Surface[elem1].voisin_1.V_oppose;
					}
	    			if (za == 2) 
					{
					/*le point z1 est sur le sommet 2 => le point z4 (z3) sur le sommet 3 (1)*/
					z1 = yc(elem1,4);  z4 = yc(elem1,7);  z3 = yc(elem1,1);
					U1 =   Surface[elem1].lon[3] + Surface[elem1].lon[4]; 
					U4 =   Surface[elem1].lon[5] + Surface[elem1].lon[6]; 
					U3 =   Surface[elem1].lon[1] + Surface[elem1].lon[2]; 
					V1 = - Surface[elem1].lon[3] + Surface[elem1].lon[4]; 
					V4 = - Surface[elem1].lon[5] + Surface[elem1].lon[6]; 
					V3 = - Surface[elem1].lon[1] + Surface[elem1].lon[2]; 
					trouve = Surface[elem1].voisin_2.exist;
					elem2 = Surface[elem1].voisin_2.elem_voisin;
					z2 = Surface[elem1].voisin_2.sommet_oppose;
					U2 = Surface[elem1].voisin_2.U_oppose;
					V2 = Surface[elem1].voisin_2.V_oppose;
					}
	    			if (za == 3) 
					{
					/*le point z1 est sur le sommet 3 => le point z4 (z3) sur le sommet 1 (2)*/
					z1 = yc(elem1,7);  z4 = yc(elem1,1);  z3 = yc(elem1,4);
					U1 =   Surface[elem1].lon[5] + Surface[elem1].lon[6]; 
					U4 =   Surface[elem1].lon[1] + Surface[elem1].lon[2]; 
					U3 =   Surface[elem1].lon[3] + Surface[elem1].lon[4]; 
					V1 = - Surface[elem1].lon[5] + Surface[elem1].lon[6]; 
					V4 = - Surface[elem1].lon[1] + Surface[elem1].lon[2]; 
					V3 = - Surface[elem1].lon[3] + Surface[elem1].lon[4]; 
					trouve = Surface[elem1].voisin_3.exist;
					elem2 = Surface[elem1].voisin_3.elem_voisin;
					z2 = Surface[elem1].voisin_3.sommet_oppose;
					U2 = Surface[elem1].voisin_3.U_oppose;
					V2 = Surface[elem1].voisin_3.V_oppose;
					}
				/*trouve = trouver(elem1,z1,&elem2,&z2,&U2,&V2);*/
				trouve_sym = trouver_sym(elem1, z1);
			
	  			if (trouve == 1)
	  				{
	  				/*le triangle elem2 est voisin de elem1*/
	  		
					/*coordonnees des 4 sommets 1 2 3 et 4*/		
	   				xx1 = wf[z1+0];	yy1 = wf[z1+1];	zz1 = wf[z1+2];
	   				xx2 = wf[z2+0];	yy2 = wf[z2+1];	zz2 = wf[z2+2];
	   				xx3 = wf[z3+0];	yy3 = wf[z3+1];	zz3 = wf[z3+2];
	   				xx4 = wf[z4+0];	yy4 = wf[z4+1];	zz4 = wf[z4+2];
	   				
	      				/*TEST_debut_non_sym
					delta_x = 0.000000001;
					for( zu = 0 ; zu <= 13 ; zu++ )
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
	      					if (zu ==10) xx4 = xx4 + delta_x;
	      					if (zu ==11) yy4 = yy4 + delta_x;
	      					if (zu ==12) zz4 = zz4 + delta_x;
	      				TEST_fin_non_sym*/
	      				
					coord_vector[ 1] = xx1;	coord_vector[ 2] = yy1;	coord_vector[ 3] = zz1;
					coord_vector[ 4] = xx2;	coord_vector[ 5] = yy2;	coord_vector[ 6] = zz2;
					coord_vector[ 7] = xx3;	coord_vector[ 8] = yy3;	coord_vector[ 9] = zz3;
					coord_vector[10] = xx4;	coord_vector[11] = yy4;	coord_vector[12] = zz4;
								
					d1 = (U4-U1)*(V3-V1)-(U3-U1)*(V4-V1);
					d2 = (U3-U2)*(V4-V2)-(U4-U2)*(V3-V2);
					d_vector[1] = d1;	d_vector[2] = d2;
			
	  				/* d1 = 1 * nb de fils dans le triangle 1 = 2 * nb de fils u = 2 * nb de fils v = 4 * nb de mailles */
	  				/* d2 = 1 * nb de fils dans le triangle 2 = 2 * nb de fils u = 2 * nb de fils v = 4 * nb de mailles */

	  				for (zg = 1; zg<= 2; zg++)
	  					{
	  					/*boucle sur les fils u si zg = 1 et fils v si zg = 2*/
	   					if (zg == 1)
							{
							/*fils u*/
	   						v1 = V1;	v2 = V2;	v3 = V3;	v4 = V4;  						
	   						/*composante du fil u du triangle 1*/
							nx = Surface[elem1].nx; ny = Surface[elem1].ny; nz = Surface[elem1].nz;
							if ((nx == 0.0) && (ny == 0.0) && (nz == 0.0))
								{
								nx = 1.0 * Surface[elem1].lgrepos;
								}
	   						/*composante du fil u du triangle 2*/
							mx = Surface[elem2].nx; my = Surface[elem2].ny; mz = Surface[elem2].nz;
	 						if ((mx == 0.0) && (my == 0.0) && (mz == 0.0))
								{
								mx = -1.0 * Surface[elem1].lgrepos;
								}
	  						}
	   					if (zg == 2)
							{
							/*fils v*/
	   						v1 =-U1;	v2 =-U2;	v3 =-U3;	v4 =-U4;						
	   						/*composante du fil v du triangle 1*/
							nx = Surface[elem1].mx; ny = Surface[elem1].my; nz = Surface[elem1].mz;
							if ((nx == 0.0) && (ny == 0.0) && (nz == 0.0))
								{
								nx = 1.0 * Surface[elem1].lgrepos;
								}
	   						/*composante du fil v du triangle 2*/
							mx = Surface[elem2].mx; my = Surface[elem2].my; mz = Surface[elem2].mz;
	 						if ((mx == 0.0) && (my == 0.0) && (mz == 0.0))
								{
								mx = -1.0 * Surface[elem1].lgrepos;
								}
	   						}
	   				
						v_vector[1] = v1;	v_vector[2] = v2;	v_vector[3] = v3;	v_vector[4] = v4;
					
	   					/*composante du fils du triangle 1*/
	  					nx =  ((v3-v1)*(xx4-xx1) - (v4-v1)*(xx3-xx1))/d1;  	
						ny =  ((v3-v1)*(yy4-yy1) - (v4-v1)*(yy3-yy1))/d1;  	
						nz =  ((v3-v1)*(zz4-zz1) - (v4-v1)*(zz3-zz1))/d1;
						if ((nx == 0.0) && (ny == 0.0) && (nz == 0.0))
							{
							nx = 1.0 * Surface[elem1].lgrepos;
							}
				
	   					/*composante du fils du triangle 2*/
	  					mx =  ((v4-v2)*(xx3-xx2) - (v3-v2)*(xx4-xx2))/d2;  	
						my =  ((v4-v2)*(yy3-yy2) - (v3-v2)*(yy4-yy2))/d2;  	
						mz =  ((v4-v2)*(zz3-zz2) - (v3-v2)*(zz4-zz2))/d2;
	 					if ((mx == 0.0) && (my == 0.0) && (mz == 0.0))
							{
							mx = -1.0 * Surface[elem1].lgrepos;
							}

						n_vector[1] = nx;	n_vector[2] = ny;	n_vector[3] = nz;
						m_vector[1] = mx;	m_vector[2] = my;	m_vector[3] = mz;
				
	  					n2 = produit_scal(n_vector, n_vector);		m2 = produit_scal(m_vector, m_vector);
	   					nn = sqrt(n2); /*longueur tendu du fil du triangle 1*/
	   					mm = sqrt(m2); /*longueur tendu du fil du triangle 2*/
	  					if(nn <= 0.0)
	  						{
	  						nn = 0.5 * Surface[elem1].lgrepos;
	  						}
	  					if(mm <= 0.0)
	  						{
	  						mm = 0.5 * Surface[elem2].lgrepos;
	  						}
	 					ps = produit_scal(n_vector, m_vector);
	  					acos_a = ps/nn/mm;
	   					if (acos_a >  1.0) acos_a =  1.0;
	   					if (acos_a < -1.0) acos_a = -1.0;
	   					Alpha = acos(acos_a); /*angle entre les fils des 2 triangles*/
	   					seuil = 0.00001; /*angle limite pour eliminer les divisions par zero*/
	   					
	/*if (fabs(Alpha) > 0.720)
		{
	printf("%5d   ",elem1);printf("%5d    \n",elem2);
	printf("U1 %6.3lf U2 %6.3lf U3 %6.3lf  U4 %6.3lf \n",U1,U2,U3,U4);
	printf("V1 %6.3lf V2 %6.3lf V3 %6.3lf  V4 %6.3lf \n",V1,V2,V3,V4);
	printf("d1 %6.3lf d2 %6.3lf Alpha %6.3lf \n",d1,d2,Alpha);
	printf("ps %6.3lf nn %6.3lf mm %6.3lf \n",ps,nn,mm);
	printf("acos_a %6.3lf n2 %6.3lf m2 %6.3lf \n",acos_a,n2,m2);
		}*/
	   					if(fabs(v3-v4) > 0.0)
							{
							nb1 = d1 / fabs(v3-v4); /*nb moyen de fil sur le trianle 1*/
	   						nb2 = d2 / fabs(v3-v4); /*nb moyen de fil sur le trianle 1*/
	   						}
	   					else
	   						{
	   						nb1 = sqrt(fabs(d1)); /*nb moyen de fil sur le trianle 1*/
	   						nb2 = sqrt(fabs(d2)); /*nb moyen de fil sur le trianle 1*/
	   						}
	   					aa = nb1*nn; /*longueur moyenne du fil sur le trianle 1*/
						bb = nb2*mm; /*longueur moyenne du fil sur le trianle 2*/
						/*le vecteur cc = aa + bb*/
	   					cc = sqrt((nb1*nx+nb2*mx)*(nb1*nx+nb2*mx)+(nb1*ny+nb2*my)*(nb1*ny+nb2*my)+(nb1*nz+nb2*mz)*(nb1*nz+nb2*mz));
	   					if (cc == 0.0)
	   						{
	   						cc = 0.0001 * aa;
	   						}
	   					pp = 0.5 * (aa+bb+cc);	/*pp est le 1/2 perimétre du triangle forme par les cotes aa bb et cc*/
	   					racine2 = pp*(pp-aa)*(pp-bb)*(pp-cc);
	   					if (racine2 <= 0.0)
	   						{
	   						racine = 0.0;
	   						}
	   					else
	   						{
	   						racine = sqrt(pp*(pp-aa)*(pp-bb)*(pp-cc));	/*parametre intermediaire*/
	   						}
	   					if ((fabs(Alpha) >= seuil) && (fabs(Alpha-PI) >= seuil) && (racine!=0.0)) /*verifie si les 2 fils sont alignes*/
	   						{
	   						rho = aa*bb*cc/4.0/racine;
	   						}
	   					else
	   						{
	   						rho = 1.0;
	   						if (fabs(Alpha-PI) < seuil)
	   							{
	   							if (cc/aa < 0.0001)
	   								{
	   								/*c est quasi nul modif de cc pour eviter une division par zero dans couple*/
	   								cc = 0.0001 * aa;
	   								}
	   							}
							}
						if ((aa!=0.0) && (bb!=0.0) && (cc!=0.0))
							{
	   						couple = fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc;
							}
						else
							{
	   						couple = 0.0;
							}
	/*if (fabs(Alpha) > 0.720)
		{
	printf("el %5d %5d  ",elem1,elem2);
	printf("nb1 %7.3lf nb2 %7.3lf  nn %7.3lf  mm %7.3lf\n",nb1,nb2,nn,mm);
	printf("racine %7.3lf rho %7.3lf  \n",racine,rho);
	printf("aa %7.4lf bb %7.4lf  cc %7.4lf\n",aa,bb,cc);
	printf("couple %7.3lf Alpha %7.3lf  n %7.3lf  %7.3lf  %7.3lf  m %7.3lf  %7.3lf  %7.3lf  \n",couple,Alpha,nx,ny,nz,mx,my,mz);
		}*/
	/*
	printf("el %5d %5d",elem1,elem2);
	printf("couple %7.3lf Alpha %7.3lf  n %7.3lf  %7.3lf  %7.3lf  m %7.3lf  %7.3lf  %7.3lf  \n",couple,Alpha,nx,ny,nz,mx,my,mz);
	*/
	   						
						/*l energie par couple de triangles E = somme(couple.d_teta). couple = EI/rho.
						avec rho.teta = l : longueur du fils. ca donne E = somme(EI.teta/l.d_teta).
						donc E = EI/l/2.alpha^2 donc E = EI/Rho/2.alpha soit E = couple.alpha/2
						reparti entre les 2 triangles*/
					
						Surface[elem1].energy_pliage += 0.25 * couple * Alpha;
						Surface[elem2].energy_pliage += 0.25 * couple * Alpha;/**/
	   						
						/*15/11/04 l energie a repartir entre les 2 triangles est 
						Surface[elem1].energy_pliage += fabs(v3-v4) * hh / aa / bb * ((aa+bb)*(aa+bb)-sqrt(aa*aa+bb*bb+2.0*aa*bb*cos(Alpha)));
						Surface[elem2].energy_pliage += fabs(v3-v4) * hh / aa / bb * ((aa+bb)*(aa+bb)-sqrt(aa*aa+bb*bb+2.0*aa*bb*cos(Alpha)));
	   					*/
	
						/*
						avec couple = fabs(v3-v4) * hh / rho
						travail interne wi = Couple dalpha
						travail externe we = fx dx 
						donc fx1 = abs(v3-v4) * h / rho * Dalpha_x1;
						donc fx1 = abs(v3-v4) * h * 4.0 * racine / aa / bb / cc * Dalpha_x1;
						*/
						
						
	 					diff_Alph_vector(Alpha, seuil, v_vector, d_vector, n_vector, m_vector, dAlpha);
	/*if (fabs(Alpha) > 0.720)
		{
	 	imprvectreel(4, v_vector);
	 	imprvectreel(2, d_vector);
	 	imprvectreel(3, n_vector);
	 	imprvectreel(3, m_vector);
	 	imprvectreel1(12, 4,dAlpha);
	 	}*/
						
	 					f_x1 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[ 1];
	 					f_y1 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[ 2];
	 					f_z1 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[ 3];
	 					f_x2 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[ 4];
	 					f_y2 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[ 5];
	 					f_z2 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[ 6];
	 					f_x3 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[ 7];
	 					f_y3 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[ 8];
	 					f_z3 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[ 9];
	 					f_x4 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[10];
	 					f_y4 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[11];
	 					f_z4 = -fabs(v3-v4) * hh * racine * 4.0 / aa / bb / cc * dAlpha[12];
	 					
	 					/*stiffness*/
						diff_nx_vector(v_vector, d_vector, dnx);	diff_ny_vector(v_vector, d_vector, dny);	diff_nz_vector(v_vector, d_vector, dnz);
						diff_mx_vector(v_vector, d_vector, dmx);	diff_my_vector(v_vector, d_vector, dmy);	diff_mz_vector(v_vector, d_vector, dmz);
					
						dcc[ 1] = ((nb1*nx+nb2*mx)*(nb1*dnx[ 1]+nb2*dmx[ 1]) + (nb1*ny+nb2*my)*(nb1*dny[ 1]+nb2*dmy[ 1]) + (nb1*nz+nb2*mz)*(nb1*dnz[ 1]+nb2*dmz[ 1])) / cc;
						dcc[ 2] = ((nb1*nx+nb2*mx)*(nb1*dnx[ 2]+nb2*dmx[ 2]) + (nb1*ny+nb2*my)*(nb1*dny[ 2]+nb2*dmy[ 2]) + (nb1*nz+nb2*mz)*(nb1*dnz[ 2]+nb2*dmz[ 2])) / cc;
						dcc[ 3] = ((nb1*nx+nb2*mx)*(nb1*dnx[ 3]+nb2*dmx[ 3]) + (nb1*ny+nb2*my)*(nb1*dny[ 3]+nb2*dmy[ 3]) + (nb1*nz+nb2*mz)*(nb1*dnz[ 3]+nb2*dmz[ 3])) / cc;
						dcc[ 4] = ((nb1*nx+nb2*mx)*(nb1*dnx[ 4]+nb2*dmx[ 4]) + (nb1*ny+nb2*my)*(nb1*dny[ 4]+nb2*dmy[ 4]) + (nb1*nz+nb2*mz)*(nb1*dnz[ 4]+nb2*dmz[ 4])) / cc;
						dcc[ 5] = ((nb1*nx+nb2*mx)*(nb1*dnx[ 5]+nb2*dmx[ 5]) + (nb1*ny+nb2*my)*(nb1*dny[ 5]+nb2*dmy[ 5]) + (nb1*nz+nb2*mz)*(nb1*dnz[ 5]+nb2*dmz[ 5])) / cc;
						dcc[ 6] = ((nb1*nx+nb2*mx)*(nb1*dnx[ 6]+nb2*dmx[ 6]) + (nb1*ny+nb2*my)*(nb1*dny[ 6]+nb2*dmy[ 6]) + (nb1*nz+nb2*mz)*(nb1*dnz[ 6]+nb2*dmz[ 6])) / cc;
						dcc[ 7] = ((nb1*nx+nb2*mx)*(nb1*dnx[ 7]+nb2*dmx[ 7]) + (nb1*ny+nb2*my)*(nb1*dny[ 7]+nb2*dmy[ 7]) + (nb1*nz+nb2*mz)*(nb1*dnz[ 7]+nb2*dmz[ 7])) / cc;
						dcc[ 8] = ((nb1*nx+nb2*mx)*(nb1*dnx[ 8]+nb2*dmx[ 8]) + (nb1*ny+nb2*my)*(nb1*dny[ 8]+nb2*dmy[ 8]) + (nb1*nz+nb2*mz)*(nb1*dnz[ 8]+nb2*dmz[ 8])) / cc;
						dcc[ 9] = ((nb1*nx+nb2*mx)*(nb1*dnx[ 9]+nb2*dmx[ 9]) + (nb1*ny+nb2*my)*(nb1*dny[ 9]+nb2*dmy[ 9]) + (nb1*nz+nb2*mz)*(nb1*dnz[ 9]+nb2*dmz[ 9])) / cc;
						dcc[10] = ((nb1*nx+nb2*mx)*(nb1*dnx[10]+nb2*dmx[10]) + (nb1*ny+nb2*my)*(nb1*dny[10]+nb2*dmy[10]) + (nb1*nz+nb2*mz)*(nb1*dnz[10]+nb2*dmz[10])) / cc;
						dcc[11] = ((nb1*nx+nb2*mx)*(nb1*dnx[11]+nb2*dmx[11]) + (nb1*ny+nb2*my)*(nb1*dny[11]+nb2*dmy[11]) + (nb1*nz+nb2*mz)*(nb1*dnz[11]+nb2*dmz[11])) / cc;
						dcc[12] = ((nb1*nx+nb2*mx)*(nb1*dnx[12]+nb2*dmx[12]) + (nb1*ny+nb2*my)*(nb1*dny[12]+nb2*dmy[12]) + (nb1*nz+nb2*mz)*(nb1*dnz[12]+nb2*dmz[12])) / cc;
	 						
						diff_nn_vector(v_vector, d_vector, n_vector, dnn);
						diff_mm_vector(v_vector, d_vector, m_vector, dmm);
						
	 					dpp[ 1] = 0.5 * (nb1*dnn[ 1] + nb2*dmm[ 1] + dcc[ 1]);
	 					dpp[ 2] = 0.5 * (nb1*dnn[ 2] + nb2*dmm[ 2] + dcc[ 2]);
	 					dpp[ 3] = 0.5 * (nb1*dnn[ 3] + nb2*dmm[ 3] + dcc[ 3]);
	 					dpp[ 4] = 0.5 * (nb1*dnn[ 4] + nb2*dmm[ 4] + dcc[ 4]);
	 					dpp[ 5] = 0.5 * (nb1*dnn[ 5] + nb2*dmm[ 5] + dcc[ 5]);
	 					dpp[ 6] = 0.5 * (nb1*dnn[ 6] + nb2*dmm[ 6] + dcc[ 6]);
	 					dpp[ 7] = 0.5 * (nb1*dnn[ 7] + nb2*dmm[ 7] + dcc[ 7]);
	 					dpp[ 8] = 0.5 * (nb1*dnn[ 8] + nb2*dmm[ 8] + dcc[ 8]);
	 					dpp[ 9] = 0.5 * (nb1*dnn[ 9] + nb2*dmm[ 9] + dcc[ 9]);
	 					dpp[10] = 0.5 * (nb1*dnn[10] + nb2*dmm[10] + dcc[10]);
	 					dpp[11] = 0.5 * (nb1*dnn[11] + nb2*dmm[11] + dcc[11]);
	 					dpp[12] = 0.5 * (nb1*dnn[12] + nb2*dmm[12] + dcc[12]);
	 						
	   					if ((fabs(Alpha) >= seuil) && (fabs(Alpha-PI) >= seuil) && (racine != 0.0)) /*verifie si les 2 fils sont alignes*/
	   						{
	 						dracine[ 1] = 0.5*(dpp[ 1]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[ 1]-nb1*dnn[ 1])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[ 1]-nb2*dmm[ 1])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[ 1]-dcc[ 1]))/racine;
	 						dracine[ 2] = 0.5*(dpp[ 2]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[ 2]-nb1*dnn[ 2])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[ 2]-nb2*dmm[ 2])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[ 2]-dcc[ 2]))/racine;
	 						dracine[ 3] = 0.5*(dpp[ 3]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[ 3]-nb1*dnn[ 3])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[ 3]-nb2*dmm[ 3])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[ 3]-dcc[ 3]))/racine;
	 						dracine[ 4] = 0.5*(dpp[ 4]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[ 4]-nb1*dnn[ 4])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[ 4]-nb2*dmm[ 4])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[ 4]-dcc[ 4]))/racine;
	 						dracine[ 5] = 0.5*(dpp[ 5]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[ 5]-nb1*dnn[ 5])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[ 5]-nb2*dmm[ 5])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[ 5]-dcc[ 5]))/racine;
	 						dracine[ 6] = 0.5*(dpp[ 6]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[ 6]-nb1*dnn[ 6])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[ 6]-nb2*dmm[ 6])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[ 6]-dcc[ 6]))/racine;
	 						dracine[ 7] = 0.5*(dpp[ 7]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[ 7]-nb1*dnn[ 7])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[ 7]-nb2*dmm[ 7])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[ 7]-dcc[ 7]))/racine;
	 						dracine[ 8] = 0.5*(dpp[ 8]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[ 8]-nb1*dnn[ 8])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[ 8]-nb2*dmm[ 8])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[ 8]-dcc[ 8]))/racine;
	 						dracine[ 9] = 0.5*(dpp[ 9]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[ 9]-nb1*dnn[ 9])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[ 9]-nb2*dmm[ 9])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[ 9]-dcc[ 9]))/racine;
	 						dracine[10] = 0.5*(dpp[10]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[10]-nb1*dnn[10])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[10]-nb2*dmm[10])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[10]-dcc[10]))/racine;
	 						dracine[11] = 0.5*(dpp[11]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[11]-nb1*dnn[11])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[11]-nb2*dmm[11])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[11]-dcc[11]))/racine;
	 						dracine[12] = 0.5*(dpp[12]*(pp-aa)*(pp-bb)*(pp-cc) + pp*(dpp[12]-nb1*dnn[12])*(pp-bb)*(pp-cc) + pp*(pp-aa)*(dpp[12]-nb2*dmm[12])*(pp-cc) + pp*(pp-aa)*(pp-bb)*(dpp[12]-dcc[12]))/racine;
	 						}
	 					else
	 						{
							dracine[ 1] = 0.0;	dracine[ 2] = 0.0;	dracine[ 3] = 0.0;	dracine[ 4] = 0.0;
	 						dracine[ 5] = 0.0;	dracine[ 6] = 0.0;	dracine[ 7] = 0.0;	dracine[ 8] = 0.0;
	 						dracine[ 9] = 0.0;	dracine[10] = 0.0;	dracine[11] = 0.0;	dracine[12] = 0.0;
	 						}
	 					
	/*if (fabs(Alpha) > 0.720)
					{
	printf("elem1 %5d elem2 %5d ",elem1,elem2);
	printf("trouve %3d tr_sym %3d ",trouve,trouve_sym);
	printf("z1 %5d z2 %5d z3 %5d z4 %5d \n",z1,z2,z3,z4);
	printf("zg %d  ",zg);
	printf("f %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf %7.3lf  \n",f_x1,f_y1,f_z1,f_x2,f_y2,f_z2,f_x3,f_y3,f_z3,f_x4,f_y4,f_z4);
	printf("v %7.3lf %7.3lf %7.3lf %7.3lf    ",v1,v2,v3,v4);
	printf("d1 %7.3lf d2 %7.3lf \n",d1,d2);
	printf("aa %7.3lf bb %7.3lf cc %7.3lf  \n",aa,bb,cc);
	printf("n %7.3lf %7.3lf %7.3lf    ",nx,ny,nz);
	printf("m %7.3lf %7.3lf %7.3lf  \n",mx,my,mz);
	printf("nb1 %7.3lf nb2 %7.3lf  ",nb1,nb2);
	printf("couple %7.3lf Alpha %7.3lf  ",couple,Alpha);
	printf("racine %7.3lf  ",racine);
	printf("pp %7.3lf rho %7.3lf couple %7.3lf  \n",pp,rho,couple);

	printf("d_alpha_x1  = ");       imprvectreel1(12, 4,d_alpha_x1);
	printf(" dracine = ");       	imprvectreel1(12, 4,dracine);
	printf(" dpp = ");       	imprvectreel1(12, 4,dpp);
	printf(" dcc = ");       	imprvectreel1(12, 4,dcc);
	printf(" dnn = ");       	imprvectreel1(12, 4,dnn);
	printf(" dmm = ");       	imprvectreel1(12, 4,dmm);
	printf(" dAlpha = ");       	imprvectreel1(12, 4,dAlpha);
	printf("Surface[elem1].energy_pliage %17.13lf  \n",Surface[elem1].energy_pliage);
	printf("pliage_triangle5	ze[%5d][%5d] = %17.0lf\n",150,1500,ze[150][1500]);
					}*/
						diff_ps_vector(v_vector, d_vector, coord_vector, dps);
				
						alpha_x1 = dAlpha[ 1];	alpha_y1 = dAlpha[ 2];	alpha_z1 = dAlpha[ 3];
						alpha_x2 = dAlpha[ 4];	alpha_y2 = dAlpha[ 5];	alpha_z2 = dAlpha[ 6];
						alpha_x3 = dAlpha[ 7];	alpha_y3 = dAlpha[ 8];	alpha_z3 = dAlpha[ 9];
						alpha_x4 = dAlpha[10];	alpha_y4 = dAlpha[11];	alpha_z4 = dAlpha[12];
					
						diff_alphax1_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dnx, dmm, dmx, dps, d_alpha_x1);
						diff_alphay1_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dny, dmm, dmy, dps, d_alpha_y1);
						diff_alphaz1_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dnz, dmm, dmz, dps, d_alpha_z1);
						diff_alphax2_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dnx, dmm, dmx, dps, d_alpha_x2);
						diff_alphay2_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dny, dmm, dmy, dps, d_alpha_y2);
						diff_alphaz2_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dnz, dmm, dmz, dps, d_alpha_z2);
						diff_alphax3_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dnx, dmm, dmx, dps, d_alpha_x3);
						diff_alphay3_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dny, dmm, dmy, dps, d_alpha_y3);
						diff_alphaz3_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dnz, dmm, dmz, dps, d_alpha_z3);
						diff_alphax4_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dnx, dmm, dmx, dps, d_alpha_x4);
						diff_alphay4_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dny, dmm, dmy, dps, d_alpha_y4);
						diff_alphaz4_vector( Alpha, dAlpha, d_vector, v_vector, n_vector, m_vector, dnn, dnz, dmm, dmz, dps, d_alpha_z4);
						
						d_fx1[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_x1+racine*d_alpha_x1[ 1])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fy1[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_y1+racine*d_alpha_y1[ 1])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fz1[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_z1+racine*d_alpha_z1[ 1])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fx2[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_x2+racine*d_alpha_x2[ 1])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fy2[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_y2+racine*d_alpha_y2[ 1])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fz2[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_z2+racine*d_alpha_z2[ 1])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fx3[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_x3+racine*d_alpha_x3[ 1])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fy3[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_y3+racine*d_alpha_y3[ 1])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fz3[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_z3+racine*d_alpha_z3[ 1])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fx4[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_x4+racine*d_alpha_x4[ 1])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fy4[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_y4+racine*d_alpha_y4[ 1])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
						d_fz4[ 1] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 1]*alpha_z4+racine*d_alpha_z4[ 1])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[ 1]*bb*cc+aa*nb2*dmm[ 1]*cc+aa*bb*dcc[ 1]));
	 					
						d_fx1[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_x1+racine*d_alpha_x1[ 2])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fy1[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_y1+racine*d_alpha_y1[ 2])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fz1[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_z1+racine*d_alpha_z1[ 2])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fx2[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_x2+racine*d_alpha_x2[ 2])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fy2[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_y2+racine*d_alpha_y2[ 2])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fz2[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_z2+racine*d_alpha_z2[ 2])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fx3[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_x3+racine*d_alpha_x3[ 2])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fy3[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_y3+racine*d_alpha_y3[ 2])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fz3[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_z3+racine*d_alpha_z3[ 2])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fx4[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_x4+racine*d_alpha_x4[ 2])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fy4[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_y4+racine*d_alpha_y4[ 2])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
						d_fz4[ 2] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 2]*alpha_z4+racine*d_alpha_z4[ 2])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[ 2]*bb*cc+aa*nb2*dmm[ 2]*cc+aa*bb*dcc[ 2]));
					
						d_fx1[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_x1+racine*d_alpha_x1[ 3])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fy1[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_y1+racine*d_alpha_y1[ 3])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fz1[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_z1+racine*d_alpha_z1[ 3])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fx2[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_x2+racine*d_alpha_x2[ 3])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fy2[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_y2+racine*d_alpha_y2[ 3])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fz2[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_z2+racine*d_alpha_z2[ 3])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fx3[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_x3+racine*d_alpha_x3[ 3])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fy3[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_y3+racine*d_alpha_y3[ 3])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fz3[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_z3+racine*d_alpha_z3[ 3])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fx4[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_x4+racine*d_alpha_x4[ 3])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fy4[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_y4+racine*d_alpha_y4[ 3])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));
						d_fz4[ 3] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 3]*alpha_z4+racine*d_alpha_z4[ 3])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[ 3]*bb*cc+aa*nb2*dmm[ 3]*cc+aa*bb*dcc[ 3]));

						d_fx1[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_x1+racine*d_alpha_x1[ 4])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fy1[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_y1+racine*d_alpha_y1[ 4])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fz1[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_z1+racine*d_alpha_z1[ 4])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fx2[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_x2+racine*d_alpha_x2[ 4])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fy2[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_y2+racine*d_alpha_y2[ 4])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fz2[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_z2+racine*d_alpha_z2[ 4])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fx3[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_x3+racine*d_alpha_x3[ 4])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fy3[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_y3+racine*d_alpha_y3[ 4])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fz3[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_z3+racine*d_alpha_z3[ 4])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fx4[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_x4+racine*d_alpha_x4[ 4])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fy4[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_y4+racine*d_alpha_y4[ 4])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));
						d_fz4[ 4] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 4]*alpha_z4+racine*d_alpha_z4[ 4])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[ 4]*bb*cc+aa*nb2*dmm[ 4]*cc+aa*bb*dcc[ 4]));

						d_fx1[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_x1+racine*d_alpha_x1[ 5])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fy1[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_y1+racine*d_alpha_y1[ 5])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fz1[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_z1+racine*d_alpha_z1[ 5])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fx2[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_x2+racine*d_alpha_x2[ 5])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fy2[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_y2+racine*d_alpha_y2[ 5])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fz2[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_z2+racine*d_alpha_z2[ 5])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fx3[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_x3+racine*d_alpha_x3[ 5])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fy3[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_y3+racine*d_alpha_y3[ 5])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fz3[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_z3+racine*d_alpha_z3[ 5])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fx4[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_x4+racine*d_alpha_x4[ 5])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fy4[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_y4+racine*d_alpha_y4[ 5])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));
						d_fz4[ 5] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 5]*alpha_z4+racine*d_alpha_z4[ 5])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[ 5]*bb*cc+aa*nb2*dmm[ 5]*cc+aa*bb*dcc[ 5]));

						d_fx1[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_x1+racine*d_alpha_x1[ 6])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fy1[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_y1+racine*d_alpha_y1[ 6])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fz1[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_z1+racine*d_alpha_z1[ 6])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fx2[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_x2+racine*d_alpha_x2[ 6])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fy2[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_y2+racine*d_alpha_y2[ 6])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fz2[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_z2+racine*d_alpha_z2[ 6])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fx3[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_x3+racine*d_alpha_x3[ 6])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fy3[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_y3+racine*d_alpha_y3[ 6])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fz3[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_z3+racine*d_alpha_z3[ 6])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fx4[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_x4+racine*d_alpha_x4[ 6])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fy4[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_y4+racine*d_alpha_y4[ 6])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));
						d_fz4[ 6] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 6]*alpha_z4+racine*d_alpha_z4[ 6])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[ 6]*bb*cc+aa*nb2*dmm[ 6]*cc+aa*bb*dcc[ 6]));

						d_fx1[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_x1+racine*d_alpha_x1[ 7])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fy1[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_y1+racine*d_alpha_y1[ 7])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fz1[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_z1+racine*d_alpha_z1[ 7])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fx2[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_x2+racine*d_alpha_x2[ 7])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fy2[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_y2+racine*d_alpha_y2[ 7])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fz2[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_z2+racine*d_alpha_z2[ 7])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fx3[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_x3+racine*d_alpha_x3[ 7])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fy3[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_y3+racine*d_alpha_y3[ 7])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fz3[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_z3+racine*d_alpha_z3[ 7])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fx4[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_x4+racine*d_alpha_x4[ 7])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fy4[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_y4+racine*d_alpha_y4[ 7])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));
						d_fz4[ 7] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 7]*alpha_z4+racine*d_alpha_z4[ 7])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[ 7]*bb*cc+aa*nb2*dmm[ 7]*cc+aa*bb*dcc[ 7]));

						d_fx1[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_x1+racine*d_alpha_x1[ 8])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fy1[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_y1+racine*d_alpha_y1[ 8])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fz1[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_z1+racine*d_alpha_z1[ 8])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fx2[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_x2+racine*d_alpha_x2[ 8])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fy2[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_y2+racine*d_alpha_y2[ 8])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fz2[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_z2+racine*d_alpha_z2[ 8])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fx3[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_x3+racine*d_alpha_x3[ 8])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fy3[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_y3+racine*d_alpha_y3[ 8])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fz3[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_z3+racine*d_alpha_z3[ 8])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fx4[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_x4+racine*d_alpha_x4[ 8])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fy4[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_y4+racine*d_alpha_y4[ 8])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));
						d_fz4[ 8] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 8]*alpha_z4+racine*d_alpha_z4[ 8])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[ 8]*bb*cc+aa*nb2*dmm[ 8]*cc+aa*bb*dcc[ 8]));

						d_fx1[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_x1+racine*d_alpha_x1[ 9])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fy1[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_y1+racine*d_alpha_y1[ 9])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fz1[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_z1+racine*d_alpha_z1[ 9])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fx2[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_x2+racine*d_alpha_x2[ 9])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fy2[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_y2+racine*d_alpha_y2[ 9])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fz2[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_z2+racine*d_alpha_z2[ 9])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fx3[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_x3+racine*d_alpha_x3[ 9])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fy3[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_y3+racine*d_alpha_y3[ 9])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fz3[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_z3+racine*d_alpha_z3[ 9])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fx4[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_x4+racine*d_alpha_x4[ 9])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fy4[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_y4+racine*d_alpha_y4[ 9])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));
						d_fz4[ 9] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[ 9]*alpha_z4+racine*d_alpha_z4[ 9])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[ 9]*bb*cc+aa*nb2*dmm[ 9]*cc+aa*bb*dcc[ 9]));

						d_fx1[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_x1+racine*d_alpha_x1[10])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fy1[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_y1+racine*d_alpha_y1[10])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fz1[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_z1+racine*d_alpha_z1[10])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fx2[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_x2+racine*d_alpha_x2[10])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fy2[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_y2+racine*d_alpha_y2[10])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fz2[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_z2+racine*d_alpha_z2[10])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fx3[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_x3+racine*d_alpha_x3[10])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fy3[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_y3+racine*d_alpha_y3[10])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fz3[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_z3+racine*d_alpha_z3[10])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fx4[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_x4+racine*d_alpha_x4[10])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fy4[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_y4+racine*d_alpha_y4[10])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));
						d_fz4[10] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[10]*alpha_z4+racine*d_alpha_z4[10])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[10]*bb*cc+aa*nb2*dmm[10]*cc+aa*bb*dcc[10]));

						d_fx1[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_x1+racine*d_alpha_x1[11])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fy1[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_y1+racine*d_alpha_y1[11])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fz1[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_z1+racine*d_alpha_z1[11])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fx2[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_x2+racine*d_alpha_x2[11])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fy2[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_y2+racine*d_alpha_y2[11])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fz2[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_z2+racine*d_alpha_z2[11])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fx3[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_x3+racine*d_alpha_x3[11])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fy3[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_y3+racine*d_alpha_y3[11])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fz3[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_z3+racine*d_alpha_z3[11])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fx4[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_x4+racine*d_alpha_x4[11])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fy4[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_y4+racine*d_alpha_y4[11])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));
						d_fz4[11] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[11]*alpha_z4+racine*d_alpha_z4[11])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[11]*bb*cc+aa*nb2*dmm[11]*cc+aa*bb*dcc[11]));

						d_fx1[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_x1+racine*d_alpha_x1[12])*(aa*bb*cc)-(racine*alpha_x1)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fy1[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_y1+racine*d_alpha_y1[12])*(aa*bb*cc)-(racine*alpha_y1)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fz1[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_z1+racine*d_alpha_z1[12])*(aa*bb*cc)-(racine*alpha_z1)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fx2[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_x2+racine*d_alpha_x2[12])*(aa*bb*cc)-(racine*alpha_x2)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fy2[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_y2+racine*d_alpha_y2[12])*(aa*bb*cc)-(racine*alpha_y2)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fz2[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_z2+racine*d_alpha_z2[12])*(aa*bb*cc)-(racine*alpha_z2)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fx3[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_x3+racine*d_alpha_x3[12])*(aa*bb*cc)-(racine*alpha_x3)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fy3[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_y3+racine*d_alpha_y3[12])*(aa*bb*cc)-(racine*alpha_y3)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fz3[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_z3+racine*d_alpha_z3[12])*(aa*bb*cc)-(racine*alpha_z3)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fx4[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_x4+racine*d_alpha_x4[12])*(aa*bb*cc)-(racine*alpha_x4)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fy4[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_y4+racine*d_alpha_y4[12])*(aa*bb*cc)-(racine*alpha_y4)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));
						d_fz4[12] = -4.0*fabs(v3-v4)*hh/aa/aa/bb/bb/cc/cc*((dracine[12]*alpha_z4+racine*d_alpha_z4[12])*(aa*bb*cc)-(racine*alpha_z4)*(nb1*dnn[12]*bb*cc+aa*nb2*dmm[12]*cc+aa*bb*dcc[12]));

		
						/*matrice raideur elementaire k_elem = -d_f*/
	  					for (zl = 1; zl<= 12; zl++)	k_elem[ 1][zl] = -d_fx1[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[ 2][zl] = -d_fy1[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[ 3][zl] = -d_fz1[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[ 4][zl] = -d_fx2[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[ 5][zl] = -d_fy2[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[ 6][zl] = -d_fz2[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[ 7][zl] = -d_fx3[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[ 8][zl] = -d_fy3[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[ 9][zl] = -d_fz3[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[10][zl] = -d_fx4[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[11][zl] = -d_fy4[zl];
	  					for (zl = 1; zl<= 12; zl++)	k_elem[12][zl] = -d_fz4[zl];
	/*if (elem1 == 551)
		{
	printf("%5d   ",elem1);printf("%5d   ",elem2);  	 
	imprmatreel3( 1, 12,  1,  12,  k_elem, 13);
		}*/
					
						wasurf[z1+0] +=   f_x1;	wasurf[z1+1] +=   f_y1;	wasurf[z1+2] +=   f_z1;
						wasurf[z2+0] +=   f_x2;	wasurf[z2+1] +=   f_y2;	wasurf[z2+2] +=   f_z2;
						wasurf[z3+0] +=   f_x3;	wasurf[z3+1] +=   f_y3;	wasurf[z3+2] +=   f_z3;
						wasurf[z4+0] +=   f_x4;	wasurf[z4+1] +=   f_y4;	wasurf[z4+2] +=   f_z4;
	/*if ((z1 == 880) || (z2 == 880) || (z3 == 880) || (z4 == 880))
		{
		printf("elem1 %d elem2 %d \n",elem1,elem2);
		printf("z1 %d wasurf[z1] =  %9.3lf \n",z1,wasurf[z1]);
		printf("z2 %d wasurf[z2] =  %9.3lf \n",z2,wasurf[z2]);
		printf("z3 %d wasurf[z3] =  %9.3lf \n",z3,wasurf[z3]);
		printf("z4 %d wasurf[z4] =  %9.3lf \n",z4,wasurf[z4]);
		}*/
	/*if (fabs(Alpha) > 0.720)
		{
		printf("%5d   ",elem1);printf("%5d   ",elem2);
		printf("f_x1 - f_z4 %6.3lf ",f_x1);printf("%6.3lf ",f_x2);printf("%6.3lf ",f_x3);printf("%6.3lf ",f_x4);
		printf("%6.3lf ",f_y1);printf("%6.3lf ",f_y2);printf("%6.3lf ",f_y3);printf("%6.3lf ",f_y4);
		printf("%6.3lf ",f_z1);printf("%6.3lf ",f_z2);printf("%6.3lf ",f_z3);printf("%6.3lf ",f_z4);
		printf("Aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaal %6.3lf \n",Alpha);
		}*/
						if (Structure.type_solver == 1)
						{
							/*rangement de la raideur elementaire dans la matrice globale*/
							/*et Calcul des bornes pour chaque ligne de la matrice de raideur globale*/
		  					for (zl = 1; zl<= 12; zl++)
	  						{
		  						if (zl == 1) ZL = z1;		if (zl == 2) ZL = z1+1;		if (zl == 3) ZL = z1+2;
		  						if (zl == 4) ZL = z2;		if (zl == 5) ZL = z2+1;		if (zl == 6) ZL = z2+2;
		  						if (zl == 7) ZL = z3;		if (zl == 8) ZL = z3+1;		if (zl == 9) ZL = z3+2;
		  						if (zl ==10) ZL = z4;		if (zl ==11) ZL = z4+1;		if (zl ==12) ZL = z4+2;
		  						for (zk = 1; zk<= 12; zk++)
	  							{
		  							if (zk == 1) ZK = z1;		if (zk == 2) ZK = z1+1;		if (zk == 3) ZK = z1+2;
		  							if (zk == 4) ZK = z2;		if (zk == 5) ZK = z2+1;		if (zk == 6) ZK = z2+2;
		  							if (zk == 7) ZK = z3;		if (zk == 8) ZK = z3+1;		if (zk == 9) ZK = z3+2;
		  							if (zk ==10) ZK = z4;		if (zk ==11) ZK = z4+1;		if (zk ==12) ZK = z4+2;
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
		  					for (zl = 0; zl< 12; zl++)
	  						{
								ii = new_coor(zl, (z1+2)/3, (z2+2)/3, (z3+2)/3, (z4+2)/3);
		  						for (zk = 0; zk< 12; zk++)
	  							{
									jj = new_coor(zk, (z1+2)/3, (z2+2)/3, (z3+2)/3, (z4+2)/3);
									affectation_pardiso(k_elem[zl+1][zk+1], ii, jj);
							
									if (rang[1][ii] < jj) rang[1][ii] = jj; 	/*borne basse  de la raideur ze*/
									if (rang[2][ii] < jj) rang[2][ii] = jj;		/*borne droite de la raideur ze*/ 
									if (rang[3][ii] > jj) rang[3][ii] = jj; 	/*borne haute  de la raideur ze*/
									if (rang[4][ii] > jj) rang[4][ii] = jj; 	/*borne gauche de la raideur ze*/
								}
							}
      						}

	/*
	printf("trouve %3d tr_sym %3d ",trouve,trouve_sym);
	printf("elem1 %5d elem2 %5d ",elem1,elem2);
	printf("pliage_triangle5	ze[%5d][%5d] = %17.0lf\n",150,1500,ze[150][1500]);
	*/
	    					}									/*fin de boucle sur zg : les 2 fils*/
	      				/*TEST_debut_non_sym
	      					if (zu == 0)
	      						{
	      						nX = nx;	nY = ny;	nZ = nz;
	      						mX = mx;	mY = my;	mZ = mz;
	       						nN = nn;	mM = mm;	pP = pp;	racinE = racine;
	      						pS = ps;	cC = cc;	AlphA = Alpha;
	      						Alpha_x1 = alpha_x1;		Alpha_x2 = alpha_x2;
							f_X1 = f_x1;	f_Y1 = f_y1;	f_Z1 = f_z1;	f_X2 = f_x2;	f_Y2 = f_y2;	f_Z2 = f_z2;	
							f_X3 = f_x3;	f_Y3 = f_y3;	f_Z3 = f_z3;	f_X4 = f_x4;	f_Y4 = f_y4;	f_Z4 = f_z4;
	     						}
						if ((zu > 0) && (zu < 13)) 
							{
							dnX[zu] = (nx - nX) / delta_x;	dnY[zu] = (ny - nY) / delta_x;	dnZ[zu] = (nz - nZ) / delta_x;
							dmX[zu] = (mx - mX) / delta_x;	dmY[zu] = (my - mY) / delta_x;	dmZ[zu] = (mz - mZ) / delta_x;
							dnN[zu] = (nn - nN) / delta_x;	dmM[zu] = (mm - mM) / delta_x;	dpP[zu] = (pp - pP) / delta_x;
							dpS[zu] = (ps - pS) / delta_x;	dcC[zu] = (cc - cC) / delta_x;	
							dAlphA[zu] = (Alpha - AlphA) / delta_x;				dracinE[zu] = (racine - racinE) / delta_x;	
							D_alpha_x1[zu] = (alpha_x1 - Alpha_x1) / delta_x;	D_alpha_x2[zu] = (alpha_x2 - Alpha_x2) / delta_x;	
							d_fX1[zu] = (f_x1 - f_X1) / delta_x;	d_fY1[zu] = (f_y1 - f_Y1) / delta_x;	d_fZ1[zu] = (f_z1 - f_Z1) / delta_x;
							d_fX2[zu] = (f_x2 - f_X2) / delta_x;	d_fY2[zu] = (f_y2 - f_Y2) / delta_x;	d_fZ2[zu] = (f_z2 - f_Z2) / delta_x;
							d_fX3[zu] = (f_x3 - f_X3) / delta_x;	d_fY3[zu] = (f_y3 - f_Y3) / delta_x;	d_fZ3[zu] = (f_z3 - f_Z3) / delta_x;
							d_fX4[zu] = (f_x4 - f_X4) / delta_x;	d_fY4[zu] = (f_y4 - f_Y4) / delta_x;	d_fZ4[zu] = (f_z4 - f_Z4) / delta_x;
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
	      					if (zu ==10)	xx4 = xx4 - delta_x;
	      					if (zu ==11)	yy4 = yy4 - delta_x;
	      					if (zu ==12)	zz4 = zz4 - delta_x;
	  				printf("n = %lf %lf %lf m = %lf %lf %lf  \n",nx,ny,nz,mx,my,mz);
	  				printf("Alpha = %lf \n",Alpha);
	 				
	      					}
					printf("dnx =");       imprvectreel(12, dnx);	printf("dnX =");       imprvectreel(12, dnX);
					printf("dny =");       imprvectreel(12, dny);	printf("dnY =");       imprvectreel(12, dnY);
					printf("dnz =");       imprvectreel(12, dnz);	printf("dnZ =");       imprvectreel(12, dnZ);
					printf("dmx =");       imprvectreel(12, dmx);	printf("dmX =");       imprvectreel(12, dmX);
					printf("dmy =");       imprvectreel(12, dmy);	printf("dmY =");       imprvectreel(12, dmY);
					printf("dmz =");       imprvectreel(12, dmz);	printf("dmZ =");       imprvectreel(12, dmZ);
					printf("dnn =");       imprvectreel(12, dnn);	printf("dnN =");       imprvectreel(12, dnN);
					printf("dmm =");       imprvectreel(12, dmm);	printf("dmM =");       imprvectreel(12, dmM);
					printf("dps =");       imprvectreel(12, dps);	printf("dpS =");       imprvectreel(12, dpS);
					printf("dcc =");       imprvectreel(12, dcc);	printf("dcC =");       imprvectreel(12, dcC);
					printf("dpp =");       imprvectreel(12, dpp);	printf("dpP =");       imprvectreel(12, dpP);
					printf("drac =");      imprvectreel(12, dracine);	printf("drac =");     imprvectreel(12, dracinE);
					printf("dAlp =");      imprvectreel(12, dAlpha);printf("dAlp =");    imprvectreel(12, dAlphA);
					printf("d_fx1 =");     imprvectreel(12, d_fx1);	printf("d_fX1 =");     imprvectreel(12, d_fX1);
					printf("d_fy1 =");     imprvectreel(12, d_fy1);	printf("d_fY1 =");     imprvectreel(12, d_fY1);
					printf("d_fz1 =");     imprvectreel(12, d_fz1);	printf("d_fZ1 =");     imprvectreel(12, d_fZ1);
	 				printf("d_fx2 =");     imprvectreel(12, d_fx2);	printf("d_fX2 =");     imprvectreel(12, d_fX2);
					printf("d_fy2 =");     imprvectreel(12, d_fy2);	printf("d_fY2 =");     imprvectreel(12, d_fY2);
					printf("d_fz2 =");     imprvectreel(12, d_fz2);	printf("d_fZ2 =");     imprvectreel(12, d_fZ2);
	 				printf("d_fx3 =");     imprvectreel(12, d_fx3);	printf("d_fX3 =");     imprvectreel(12, d_fX3);
					printf("d_fy3 =");     imprvectreel(12, d_fy3);	printf("d_fY3 =");     imprvectreel(12, d_fY3);
					printf("d_fz3 =");     imprvectreel(12, d_fz3);	printf("d_fZ3 =");     imprvectreel(12, d_fZ3);
	 				printf("d_fx4 =");     imprvectreel(12, d_fx4);	printf("d_fX4 =");     imprvectreel(12, d_fX4);
					printf("d_fy4 =");     imprvectreel(12, d_fy4);	printf("d_fY4 =");     imprvectreel(12, d_fY4);
					printf("d_fz4 =");     imprvectreel(12, d_fz4);	printf("d_fZ4 =");     imprvectreel(12, d_fZ4);
					printf("d_ax1 =");     imprvectreel(12, d_alpha_x1);	printf("d_Ax1 =");     imprvectreel(12, D_alpha_x1);
					printf("d_ax2 =");     imprvectreel(12, d_alpha_x2);	printf("d_Ax2 =");     imprvectreel(12, D_alpha_x2);
	 				
					exit(0);
	      				TEST_fin_non_sym*/
					}										/*fin de if trouve*/		
				if (trouve_sym != 0)
	  				{
					}										/*fin de if trouve_sym*/	
	 			}											/*fin de boucle sur za : les 3 sommets*/
			}
  		}												/*fin de boucle sur elem1*/
/*imprvectreel(320, wasurf);
exit(0);*/ 			
	}
