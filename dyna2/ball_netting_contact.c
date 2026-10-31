#include "4c19.h"

void ball_netting_contact()
	{
  	int zb,zn,zc,zd,zu,p1,p2,p3,p4,no[13];
  	double seuil,multiplicateur;
  	double normal_vector[4],n_vector[4],m_vector[4],nn,mm,uu,vv;
  	double v1[4],v2[4],v3[4],v4[4],v12[4],v23[4],v41[4],v4m[4];
  	double vf1[4],vf2[4],vf3[4],vf4[4];
  	double s12_23,s23_41,s23_23,s12_41,s12_12,s41_41,s4m_4m;
  	double beta,mu,dist,delta_x;
  	double xm_x4p[13],ym_y4p[13],zm_z4p[13],s41_41p[13],s12_41p[13],s23_41p[13],s12_23p[13],s12_12p[13],s23_23p[13];
  	double distp[13],betap[13],mup[13],tmpa[13],tmpb[13],tmpc[13],tmpd[13],tmpe[13],tmpf[13],tmpg[13],tmph[13],up[13],vp[13];
  	double f1xp[13],f1yp[13],f1zp[13],f2xp[13],f2yp[13],f2zp[13],f3xp[13],f3yp[13],f3zp[13],f4xp[13],f4yp[13],f4zp[13];
	double u_beta,up_beta[13],v_beta,vp_beta[13],u_mu,up_mu[13],v_mu,vp_mu[13];
	
  	double Beta,Mu,Dist,Xm_x4,Ym_y4,Zm_z4,S41_41,S12_23,S23_41,S23_23,S12_41,S12_12;
  	double Distp[13],Betap[13],Mup[13],Xm_x4p[13],Ym_y4p[13],Zm_z4p[13];
  	double S41_41p[13],S12_41p[13],S23_41p[13],S12_23p[13],S12_12p[13],S23_23p[13];
	double U_beta,Up_beta[13],V_beta,Vp_beta[13],U_mu,Up_mu[13],V_mu,Vp_mu[13];
  	double Vf1[4],Vf2[4],Vf3[4],Vf4[4];
  	double F1xp[13],F1yp[13],F1zp[13],F2xp[13],F2yp[13],F2zp[13],F3xp[13],F3yp[13],F3zp[13],F4xp[13],F4yp[13],F4zp[13];
	
  	/* pour chaque ball prendre en compte le contact avec le filet*/
   	for (zb = 1 ; zb<= Ball.nb; zb++) 
  		{
  		if (times >= Ball.birth_time[zb])
  			{
  			p4 = Ball.noeud[zb];
  			/*coordinates of point 4*/
			v4[1] = wf [3*p4-2];	v4[2] = wf [3*p4-1];	v4[3] = wf [3*p4-0];
			for (zn = 1 ; zn <= NOMBRE_SURFACES ; zn++)
				{
				p1 = (int) yc(zn,3) / 3;
				p2 = (int) yc(zn,6) / 3;
				p3 = (int) yc(zn,9) / 3;
  				/*coordinates of points 1 2 & 3*/
				v1[1] = wf [3*p1-2];	v1[2] = wf [3*p1-1];	v1[3] = wf [3*p1-0];
				v2[1] = wf [3*p2-2];	v2[2] = wf [3*p2-1];	v2[3] = wf [3*p2-0];
				v3[1] = wf [3*p3-2];	v3[2] = wf [3*p3-1];	v3[3] = wf [3*p3-0];
				
      				/*TEST_debut
				delta_x = 0.0000001;
				for( zu = 0 ; zu <= 13 ; zu++ )
      					{
      					if (zu == 1) v1[ 1] = v1[ 1] + delta_x;
      					if (zu == 2) v1[ 2] = v1[ 2] + delta_x;
      					if (zu == 3) v1[ 3] = v1[ 3] + delta_x;
      					if (zu == 4) v2[ 1] = v2[ 1] + delta_x;
      					if (zu == 5) v2[ 2] = v2[ 2] + delta_x;
      					if (zu == 6) v2[ 3] = v2[ 3] + delta_x;
      					if (zu == 7) v3[ 1] = v3[ 1] + delta_x;
      					if (zu == 8) v3[ 2] = v3[ 2] + delta_x;
      					if (zu == 9) v3[ 3] = v3[ 3] + delta_x;
      					if (zu ==10) v4[ 1] = v4[ 1] + delta_x;
      					if (zu ==11) v4[ 2] = v4[ 2] + delta_x;
      					if (zu ==12) v4[ 3] = v4[ 3] + delta_x;
      				TEST_fin*/
      				
				v12[1] = v2[1]-v1[1];	v12[2] = v2[2]-v1[2];	v12[3] = v2[3]-v1[3];		
				v23[1] = v3[1]-v2[1];	v23[2] = v3[2]-v2[2];	v23[3] = v3[3]-v2[3];		
				v41[1] = v1[1]-v4[1];	v41[2] = v1[2]-v4[2];	v41[3] = v1[3]-v4[3];		
				s12_23 = produit_scal(v23, v12);
				s23_41 = produit_scal(v41, v23);
				s23_23 = produit_scal(v23, v23);
				s12_41 = produit_scal(v41, v12);
				s12_12 = produit_scal(v12, v12);
				s41_41 = produit_scal(v41, v41);
				beta = (s12_23*s23_41-s23_23*s12_41) / (s23_23*s12_12-s12_23*s12_23);
				mu   = (s12_23*s12_41-s12_12*s23_41) / (s23_23*s12_12-s12_23*s12_23);
				v4m[1] = v41[1]+beta*v12[1]+mu*v23[1];
				v4m[2] = v41[2]+beta*v12[2]+mu*v23[2];
				v4m[3] = v41[3]+beta*v12[3]+mu*v23[3];
				s4m_4m = produit_scal(v4m, v4m);			
				dist = sqrt(s4m_4m);
				if (dist <= Ball.radius[zb])
					{
					seuil = sqrt(Ball.radius[zb]*Ball.radius[zb]-dist*dist);
			
					/*
					printf("beta %12.2lf mu %12.2lf  ",beta,mu);
					printf("dist %12.2lf   ",dist);
					printf("Ball.radius[zb] %12.2lf   \n",Ball.radius[zb]);
					printf("v4 %lf %lf %lf   ",v4[1],v4[2],v4[3]);
					printf("v4m %12.2lf %12.2lf %12.2lf \n",v4m[1],v4m[2],v4m[3]);
					*/
			
					/*if ((times>3.489) && (times<3.491) && (nbiter>=107) && (nbiter<=108) && (zb == 2))
						{
						printf("times %8.3lf ball %4d surface %4d noeuds %4d %4d %4d  \n",times,zb,zn,p1,p2,p3);
						printf("beta %22.12lf mu %22.12lf  \n",beta,mu);
						printf("Ball.radius[zb]-dist %22.12lf   \n",Ball.radius[zb]-dist);
						printf("limite 1 beta-1 					%lf\n",beta-1.0);
						printf("limite 2 mu-beta 					%lf\n",mu-beta);
						printf("limite 3 mu 						%lf\n",mu);
						printf("limite 4 (beta-1.0)*sqrt(s12_12) - seuil 		%lf\n",(beta-1.0)*sqrt(s12_12) - seuil);
						printf("limite 5 (mu-beta)*sqrt(s23_23) - seuil 		%lf\n",(mu-beta)*sqrt(s23_23) - seuil);
						printf("limite 6 (-mu)*sqrt(s23_23) - seuil 			%lf\n",(-mu)*sqrt(s23_23) - seuil);
						printf("limite 7 2.0*mu-beta					%lf\n",2.0*mu-beta);
						printf("limite 8 (beta-1.0)*sqrt(s12_12)+mu*sqrt(s23_23)	%lf\n",(beta-1.0)*sqrt(s12_12)+mu*sqrt(s23_23));
						printf("limite 9 (beta-1.0)*sqrt(s12_12)-(mu-beta)*sqrt(s23_23)	%lf\n",(beta-1.0)*sqrt(s12_12)-(mu-beta)*sqrt(s23_23));
						}*/
				
					/*if ((beta >= 0.0) && (beta <= 1.0) && (mu >= 0.0) && (mu <= beta) && (dist <= Ball.radius[zb]))*/
					if (((beta-1.0)*sqrt(s12_12) <= seuil) && ((mu-beta)*sqrt(s23_23) <= seuil) && ((-mu)*sqrt(s23_23) <= seuil))
						{
						/*contact*/
						if ((times>3.489) && (times<3.491) && (nbiter>=107) && (nbiter<=108) && (zb == 2))printf("contact %lf\n",multiplicateur);/**/
						
						multiplicateur = 1.0;
						if (((beta-1.0)*sqrt(s12_12)>=(mu-beta)*sqrt(s23_23)) && ((beta-1.0)*sqrt(s12_12)>=(-mu)*sqrt(s23_23)) && (beta >=1.0))
							{
							/*zone 1*/
							multiplicateur = (seuil-(beta-1.0)*sqrt(s12_12))/seuil;
							/*if ((times>3.489) && (times<3.491) && (nbiter>=107) && (nbiter<=108) && (zb == 2))printf("zone 1 multiplicateur %lf\n",multiplicateur);*/
							}
						if ((2.0*mu>=beta) && ((beta-1.0)*sqrt(s12_12)<=(mu-beta)*sqrt(s23_23)) && (mu >=beta))
							{
							/*zone 2*/
							multiplicateur = (seuil-(mu-beta)*sqrt(s23_23))/seuil;
							/*printf("zone 2 multiplicateur %lf\n",multiplicateur);*/
							/*if ((times>3.489) && (times<3.491) && (nbiter>=107) && (nbiter<=108) && (zb == 2))printf("zone 2 multiplicateur %lf\n",multiplicateur);*/
							}
						if ((2.0*mu<=beta) && ((beta-1.0)*sqrt(s12_12)<=(-mu)*sqrt(s23_23)) && (mu <=0.0))
							{
							/*zone 3*/
							multiplicateur = (seuil+mu*sqrt(s23_23))/seuil;
							/*printf("zone 3 multiplicateur %lf\n",multiplicateur);*/
							/*if ((times>3.489) && (times<3.491) && (nbiter>=107) && (nbiter<=108) && (zb == 2))printf("zone 3 multiplicateur %lf\n",multiplicateur);*/
							}
						if ((beta<=1.0) && (mu<=beta) && (mu >=0.0))
							{
							/*zone 4*/
							multiplicateur = 1.0;
							/*printf("zone 4 multiplicateur %lf\n",multiplicateur);*/
							/*if ((times>3.489) && (times<3.491) && (nbiter>=107) && (nbiter<=108) && (zb == 2))printf("zone 4 multiplicateur %lf\n",multiplicateur);*/
							}
						if ((multiplicateur < 0.0) && (multiplicateur > 1.0))
							{
							printf("limite 1 beta-1 					%lf\n",beta-1.0);
							printf("limite 2 mu-beta 					%lf\n",mu-beta);
							printf("limite 3 mu 						%lf\n",mu);
							printf("limite 4 (beta-1.0)*sqrt(s12_12) - seuil 		%lf\n",(beta-1.0)*sqrt(s12_12) - seuil);
							printf("limite 5 (mu-beta)*sqrt(s23_23) - seuil 		%lf\n",(mu-beta)*sqrt(s23_23) - seuil);
							printf("limite 6 (-mu)*sqrt(s23_23) - seuil 			%lf\n",(-mu)*sqrt(s23_23) - seuil);
							printf("limite 7 (-beta)*sqrt(s12_12)-(mu)*sqrt(s23_23)		%lf\n",(-beta)*sqrt(s12_12)-(mu)*sqrt(s23_23));
							printf("limite 8 (beta-1.0)*sqrt(s12_12)+mu*sqrt(s23_23)	%lf\n",(beta-1.0)*sqrt(s12_12)+mu*sqrt(s23_23));
							printf("limite 9 (beta-1.0)*sqrt(s12_12)-(mu-beta)*sqrt(s23_23)	%lf\n",(beta-1.0)*sqrt(s12_12)-(mu-beta)*sqrt(s23_23));
							/*exit(0);*/
							if (multiplicateur < 0.0) multiplicateur = 0.0;
							if (multiplicateur > 1.0) multiplicateur = 1.0;
							}
						produit_scal_vect((1.0-beta)/dist*Ball.stiffness[zb]*(Ball.radius[zb]-dist)/Ball.radius[zb]*multiplicateur, v4m, vf1);
						produit_scal_vect( (beta-mu)/dist*Ball.stiffness[zb]*(Ball.radius[zb]-dist)/Ball.radius[zb]*multiplicateur, v4m, vf2);
						produit_scal_vect(       mu /dist*Ball.stiffness[zb]*(Ball.radius[zb]-dist)/Ball.radius[zb]*multiplicateur, v4m, vf3);
						produit_scal_vect(     -1.0 /dist*Ball.stiffness[zb]*(Ball.radius[zb]-dist)/Ball.radius[zb]*multiplicateur, v4m, vf4);
				
						/*printf("v4m %12.2lf %12.2lf %12.2lf \n",v4m[1],v4m[2],v4m[3]);
						printf("vf1 %12.2lf %12.2lf %12.2lf   ",vf1[1],vf1[2],vf1[3]);
						printf("vf2 %12.2lf %12.2lf %12.2lf \n",vf2[1],vf2[2],vf2[3]);
						printf("vf3 %12.2lf %12.2lf %12.2lf   ",vf3[1],vf3[2],vf3[3]);
						printf("vf4 %12.2lf %12.2lf %12.2lf \n",vf4[1],vf4[2],vf4[3]);*/
		      			
						wanoeud[3*p1-2] += vf1[1];	wanoeud[3*p1-1] += vf1[2];	wanoeud[3*p1-0] += vf1[3];
		      				wanoeud[3*p2-2] += vf2[1];	wanoeud[3*p2-1] += vf2[2];	wanoeud[3*p2-0] += vf2[3];
		      				wanoeud[3*p3-2] += vf3[1];	wanoeud[3*p3-1] += vf3[2];	wanoeud[3*p3-0] += vf3[3];
		      				wanoeud[3*p4-2] += vf4[1];	wanoeud[3*p4-1] += vf4[2];	wanoeud[3*p4-0] += vf4[3];

						/*if ((times>3.489) && (times<3.491) && (nbiter>=107) && (nbiter<=108) && (zb == 2)){printf(" net_co");	imprvectreel(177, wanoeud);}/**/
		      			
						/*derivative of s41_41 : s41_41p[13]*/
						s41_41p[ 1] = 2.0*(v1[1]-v4[1]);	s41_41p[ 2] = 2.0*(v1[2]-v4[2]);	s41_41p[ 3] = 2.0*(v1[3]-v4[3]);
						s41_41p[ 4] = 0.0;			s41_41p[ 5] = 0.0;			s41_41p[ 6] = 0.0;
						s41_41p[ 7] = 0.0;			s41_41p[ 8] = 0.0;			s41_41p[ 9] = 0.0;
						s41_41p[10] = 2.0*(v4[1]-v1[1]);	s41_41p[11] = 2.0*(v4[2]-v1[2]);	s41_41p[12] = 2.0*(v4[3]-v1[3]);
		      			
						/*derivative of s12_41 : s12_41p[13]*/
						s12_41p[ 1] = v2[1]-2.0*v1[1]+v4[1];	s12_41p[ 2] = v2[2]-2.0*v1[2]+v4[2];	s12_41p[ 3] = v2[3]-2.0*v1[3]+v4[3];
						s12_41p[ 4] = v1[1]-v4[1];		s12_41p[ 5] = v1[2]-v4[2];		s12_41p[ 6] = v1[3]-v4[3];
						s12_41p[ 7] = 0.0;			s12_41p[ 8] = 0.0;			s12_41p[ 9] = 0.0;
						s12_41p[10] = v1[1]-v2[1];		s12_41p[11] = v1[2]-v2[2];		s12_41p[12] = v1[3]-v2[3];
		      			
						/*derivative of s23_41 : s23_41p[13]*/
						s23_41p[ 1] = v3[1]-v2[1];		s23_41p[ 2] = v3[2]-v2[2];		s23_41p[ 3] = v3[3]-v2[3];
						s23_41p[ 4] = v4[1]-v1[1];		s23_41p[ 5] = v4[2]-v1[2];		s23_41p[ 6] = v4[3]-v1[3];
						s23_41p[ 7] = v1[1]-v4[1];		s23_41p[ 8] = v1[2]-v4[2];		s23_41p[ 9] = v1[3]-v4[3];
						s23_41p[10] = v2[1]-v3[1];		s23_41p[11] = v2[2]-v3[2];		s23_41p[12] = v2[3]-v3[3];
		      			
						/*derivative of s12_23 : s12_23p[13]*/
						s12_23p[ 1] = v2[1]-v3[1];		s12_23p[ 2] = v2[2]-v3[2];		s12_23p[ 3] = v2[3]-v3[3];
						s12_23p[ 4] = v3[1]-2.0*v2[1]+v1[1];	s12_23p[ 5] = v3[2]-2.0*v2[2]+v1[2];	s12_23p[ 6] = v3[3]-2.0*v2[3]+v1[3];
						s12_23p[ 7] = v2[1]-v1[1];		s12_23p[ 8] = v2[2]-v1[2];		s12_23p[ 9] = v2[3]-v1[3];
						s12_23p[10] = 0.0;			s12_23p[11] = 0.0;			s12_23p[12] = 0.0;
		      			
						/*derivative of s12_12 : s12_12p[13]*/
						s12_12p[ 1] = -2.0*(v2[1]-v1[1]);	s12_12p[ 2] = -2.0*(v2[2]-v1[2]);	s12_12p[ 3] = -2.0*(v2[3]-v1[3]);
						s12_12p[ 4] = 2.0*(v2[1]-v1[1]);	s12_12p[ 5] = 2.0*(v2[2]-v1[2]);	s12_12p[ 6] = 2.0*(v2[3]-v1[3]);
						s12_12p[ 7] = 0.0;			s12_12p[ 8] = 0.0;			s12_12p[ 9] = 0.0;
						s12_12p[10] = 0.0;			s12_12p[11] = 0.0;			s12_12p[12] = 0.0;
		      			
						/*derivative of s23_23 : s23_23p[13]*/
						s23_23p[ 1] = 0.0;			s23_23p[ 2] = 0.0;			s23_23p[ 3] = 0.0;
						s23_23p[ 4] = -2.0*(v3[1]-v2[1]);	s23_23p[ 5] = -2.0*(v3[2]-v2[2]);	s23_23p[ 6] = -2.0*(v3[3]-v2[3]);
						s23_23p[ 7] = 2.0*(v3[1]-v2[1]);	s23_23p[ 8] = 2.0*(v3[2]-v2[2]);	s23_23p[ 9] = 2.0*(v3[3]-v2[3]);
						s23_23p[10] = 0.0;			s23_23p[11] = 0.0;			s23_23p[12] = 0.0;

						/*derivative of beta*/
						u_beta = s12_23*s23_41-s23_23*s12_41;
						v_beta = s23_23*s12_12-s12_23*s12_23;
					
						/*derivative of u_beta*/
						produit_scal_vect_12( s23_41, s12_23p, tmpa);
						produit_scal_vect_12( s12_23, s23_41p, tmpb);
						produit_scal_vect_12(-s12_41, s23_23p, tmpc);
						produit_scal_vect_12(-s23_23, s12_41p, tmpd);
						add_vect_12(tmpa, tmpb, tmpe);
						add_vect_12(tmpc, tmpd, tmpf);
						add_vect_12(tmpe, tmpf, up_beta);
					
						/*derivative of v_beta*/
						produit_scal_vect_12( s12_12, s23_23p, tmpa);
						produit_scal_vect_12( s23_23, s12_12p, tmpb);
						produit_scal_vect_12(-2.0*s12_23, s12_23p, tmpc);
						add_vect_12(tmpa, tmpb, tmpe);
						add_vect_12(tmpc, tmpe, vp_beta);
					
						/*derivative of beta = (up_beta*v_beta-u_beta*vp_beta) / v2_beta*/
						produit_scal_vect_12( v_beta, up_beta, tmpa);
						produit_scal_vect_12(-u_beta, vp_beta, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);
						produit_scal_vect_12(1.0/v_beta/v_beta, tmpc, betap);

						/*derivative of mu*/
						u_mu = s12_23*s12_41-s12_12*s23_41;
						v_mu = s23_23*s12_12-s12_23*s12_23;
					
						/*derivative of u_mu*/
						produit_scal_vect_12( s12_23, s12_41p, tmpa);
						produit_scal_vect_12( s12_41, s12_23p, tmpb);
						produit_scal_vect_12(-s12_12, s23_41p, tmpc);
						produit_scal_vect_12(-s23_41, s12_12p, tmpd);
						add_vect_12(tmpa, tmpb, tmpe);
						add_vect_12(tmpc, tmpd, tmpf);
						add_vect_12(tmpe, tmpf, up_mu);
					
						/*derivative of v_mu*/
						produit_scal_vect_12( s12_12, s23_23p, tmpa);
						produit_scal_vect_12( s23_23, s12_12p, tmpb);
						produit_scal_vect_12(-2.0*s12_23, s12_23p, tmpc);
						add_vect_12(tmpa, tmpb, tmpe);
						add_vect_12(tmpc, tmpe, vp_mu);
					
						/*derivative of mu = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( v_mu, up_mu, tmpa);
						produit_scal_vect_12(-u_mu, vp_mu, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);
						produit_scal_vect_12(1.0/v_mu/v_mu, tmpc, mup);
					
						/*derivative of dist*/
						produit_scal_vect_12( 2.0*(s12_41+beta*s12_12+  mu*s12_23),   betap , tmpa);
						produit_scal_vect_12( 2.0*(s23_41+  mu*s23_23+beta*s12_23),     mup , tmpb);
						produit_scal_vect_12( 2.0*beta                            , s12_41p , tmpc);
						produit_scal_vect_12( 2.0*mu                              , s23_41p , tmpd);
						produit_scal_vect_12( beta*beta                           , s12_12p , tmpe);
						produit_scal_vect_12( mu*mu                               , s23_23p , tmpf);
						produit_scal_vect_12( 2.0*beta*mu                         , s12_23p , tmpg);
						add_vect_12(s41_41p, tmpa, tmph);
						add_vect_12(   tmph, tmpb, tmph);
						add_vect_12(   tmph, tmpc, tmph);
						add_vect_12(   tmph, tmpd, tmph);
						add_vect_12(   tmph, tmpe, tmph);
						add_vect_12(   tmph, tmpf, tmph);
						add_vect_12(   tmph, tmpg, tmph);
						produit_scal_vect_12( 0.5/dist , tmph , distp);
					
		      				/*derivative of 4m*/
		      				tmpa[ 1] = 1.0 - beta;		tmpa[ 2] = 0.0;			tmpa[ 3] = 0.0;
		      				tmpa[ 4] = beta - mu;		tmpa[ 5] = 0.0;			tmpa[ 6] = 0.0;
		      				tmpa[ 7] = mu;			tmpa[ 8] = 0.0;			tmpa[ 9] = 0.0;
		      				tmpa[10] = -1.0;		tmpa[11] = 0.0;			tmpa[12] = 0.0;
						produit_scal_vect_12( v2[1]-v1[1], betap , tmpb);
						produit_scal_vect_12( v3[1]-v2[1],   mup , tmpc);
						add_vect_12(   tmpa, tmpb, tmpd);
						add_vect_12(   tmpd, tmpc, xm_x4p);
		      			
		      				tmpa[ 1] = 0.0;			tmpa[ 2] = 1.0 - beta;		tmpa[ 3] = 0.0;
		      				tmpa[ 4] = 0.0;			tmpa[ 5] = beta - mu;		tmpa[ 6] = 0.0;
		      				tmpa[ 7] = 0.0;			tmpa[ 8] = mu;			tmpa[ 9] = 0.0;
		      				tmpa[10] = 0.0;			tmpa[11] = -1.0;		tmpa[12] = 0.0;
						produit_scal_vect_12( v2[2]-v1[2], betap , tmpb);
						produit_scal_vect_12( v3[2]-v2[2],   mup , tmpc);
						add_vect_12(   tmpa, tmpb, tmpd);
						add_vect_12(   tmpd, tmpc, ym_y4p);
		      			
		      				tmpa[ 1] = 0.0;			tmpa[ 2] = 0.0;			tmpa[ 3] = 1.0 - beta;
		      				tmpa[ 4] = 0.0;			tmpa[ 5] = 0.0;			tmpa[ 6] = beta - mu;
		      				tmpa[ 7] = 0.0;			tmpa[ 8] = 0.0;			tmpa[ 9] = mu;
		      				tmpa[10] = 0.0;			tmpa[11] = 0.0;			tmpa[12] = -1.0;
						produit_scal_vect_12( v2[3]-v1[3], betap , tmpb);
						produit_scal_vect_12( v3[3]-v2[3],   mup , tmpc);
						add_vect_12(   tmpa, tmpb, tmpd);
						add_vect_12(   tmpd, tmpc, zm_z4p);
		      			
						/*tous les efforts sont de la forme uu/vv leur derivees sont donc de la
						la forme (up*vv-uu*vp)/vv/vv
						vv est identique pour tous les efforts on le calcul qu'une fois
						ainsi que sa derivee*/
						vv = dist*Ball.radius[zb]/Ball.stiffness[zb];
						/*derivative of vv*/
						produit_scal_vect_12(Ball.radius[zb]/Ball.stiffness[zb]  ,  distp, vp);
					
						/*derivative of f1x*/
						uu = (1.0-beta)*v4m[1]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12(-v4m[1]*(Ball.radius[zb]-dist)      ,  betap, tmpa);
						produit_scal_vect_12((1.0-beta)*(Ball.radius[zb]-dist)   , xm_x4p, tmpb);
						produit_scal_vect_12(-(1.0-beta)*v4m[1]                  ,  distp, tmpc);
						add_vect_12(tmpa, tmpb, tmpd);		add_vect_12(tmpc, tmpd, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f1xp);
					
						/*derivative of f1y remplacer v4m[1] par v4m[2], xm_x4p par ym_y4p*/
						uu = (1.0-beta)*v4m[2]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12(-v4m[2]*(Ball.radius[zb]-dist)      ,  betap, tmpa);
						produit_scal_vect_12((1.0-beta)*(Ball.radius[zb]-dist)   , ym_y4p, tmpb);
						produit_scal_vect_12(-(1.0-beta)*v4m[2]                  ,  distp, tmpc);
						add_vect_12(tmpa, tmpb, tmpd);		add_vect_12(tmpc, tmpd, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f1yp);
						
						/*derivative of f1z remplacer v4m[1] par v4m[3], xm_x4p par zm_z4p*/
						uu = (1.0-beta)*v4m[3]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12(-v4m[3]*(Ball.radius[zb]-dist)      ,  betap, tmpa);
						produit_scal_vect_12((1.0-beta)*(Ball.radius[zb]-dist)   , zm_z4p, tmpb);
						produit_scal_vect_12(-(1.0-beta)*v4m[3]                  ,  distp, tmpc);
						add_vect_12(tmpa, tmpb, tmpd);		add_vect_12(tmpc, tmpd, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f1zp);
					
						/*derivative of f2x  remplacer 1-beta par beta-mu, et betap par mup-betap (tmpe)*/
						uu = (beta-mu)*v4m[1]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12(-1.0, betap, tmpa);	add_vect_12(tmpa, mup, tmpe);  /*calcul de mup-betap*/
						produit_scal_vect_12(-v4m[1]*(Ball.radius[zb]-dist)      , tmpe , tmpa);
						produit_scal_vect_12((beta-mu)*(Ball.radius[zb]-dist)   , xm_x4p, tmpb);
						produit_scal_vect_12(-(beta-mu)*v4m[1]                  ,  distp, tmpc);
						add_vect_12(tmpa, tmpb, tmpd);		add_vect_12(tmpc, tmpd, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f2xp);
					
						/*derivative of f2y  remplacer 1-beta par beta-mu, et betap par mup-betap (tmpe)*/
						uu = (beta-mu)*v4m[2]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12(-1.0, betap, tmpa);	add_vect_12(tmpa, mup, tmpe);  /*calcul de mup-betap*/
						produit_scal_vect_12(-v4m[2]*(Ball.radius[zb]-dist)      , tmpe , tmpa);
						produit_scal_vect_12((beta-mu)*(Ball.radius[zb]-dist)   , ym_y4p, tmpb);
						produit_scal_vect_12(-(beta-mu)*v4m[2]                  ,  distp, tmpc);
						add_vect_12(tmpa, tmpb, tmpd);		add_vect_12(tmpc, tmpd, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f2yp);
					
						/*derivative of f2z  remplacer 1-beta par beta-mu, et betap par mup-betap (tmpe)*/
						uu = (beta-mu)*v4m[3]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12(-1.0, betap, tmpa);	add_vect_12(tmpa, mup, tmpe);  /*calcul de mup-betap*/
						produit_scal_vect_12(-v4m[3]*(Ball.radius[zb]-dist)      , tmpe , tmpa);
						produit_scal_vect_12((beta-mu)*(Ball.radius[zb]-dist)   , zm_z4p, tmpb);
						produit_scal_vect_12(-(beta-mu)*v4m[3]                  ,  distp, tmpc);
						add_vect_12(tmpa, tmpb, tmpd);		add_vect_12(tmpc, tmpd, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f2zp);
					
						/*derivative of f3x  remplacer 1-beta par mu, et betap par -mup*/
						uu = (mu)*v4m[1]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12( v4m[1]*(Ball.radius[zb]-dist)      ,  mup, tmpa);
						produit_scal_vect_12((mu)*(Ball.radius[zb]-dist)   , xm_x4p, tmpb);
						produit_scal_vect_12(-(mu)*v4m[1]                  ,  distp, tmpc);
						add_vect_12(tmpa, tmpb, tmpd);		add_vect_12(tmpc, tmpd, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f3xp);
					
						/*derivative of f3y  remplacer 1-beta par mu, et betap par -mup*/
						uu = (mu)*v4m[2]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12( v4m[2]*(Ball.radius[zb]-dist)      ,  mup, tmpa);
						produit_scal_vect_12((mu)*(Ball.radius[zb]-dist)   , ym_y4p, tmpb);
						produit_scal_vect_12(-(mu)*v4m[2]                  ,  distp, tmpc);
						add_vect_12(tmpa, tmpb, tmpd);		add_vect_12(tmpc, tmpd, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f3yp);
					
						/*derivative of f3z  remplacer 1-beta par mu, et betap par -mup*/
						uu = (mu)*v4m[3]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12( v4m[3]*(Ball.radius[zb]-dist)      ,  mup, tmpa);
						produit_scal_vect_12((mu)*(Ball.radius[zb]-dist)   , zm_z4p, tmpb);
						produit_scal_vect_12(-(mu)*v4m[3]                  ,  distp, tmpc);
						add_vect_12(tmpa, tmpb, tmpd);		add_vect_12(tmpc, tmpd, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f3zp);
									
						/*derivative of f4x remplacer 1-beta par -1, et betap par 0*/
						uu = -v4m[1]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12(-(Ball.radius[zb]-dist)         , xm_x4p, tmpb);
						produit_scal_vect_12(v4m[1]                          ,  distp, tmpc);
						add_vect_12(tmpb, tmpc, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f4xp);
					
						/*derivative of f4y*/
						uu = -v4m[2]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12(-(Ball.radius[zb]-dist)         , ym_y4p, tmpb);
						produit_scal_vect_12(v4m[2]                          ,  distp, tmpc);
						add_vect_12(tmpb, tmpc, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f4yp);
					
						/*derivative of f4z*/
						uu = -v4m[3]*(Ball.radius[zb]-dist);
						/*derivative of uu*/
						produit_scal_vect_12(-(Ball.radius[zb]-dist)         , zm_z4p, tmpb);
						produit_scal_vect_12(v4m[3]                          ,  distp, tmpc);
						add_vect_12(tmpb, tmpc, up);
						/*derivative of f1x = (up*vv-uu*vp) / v2*/
						produit_scal_vect_12( vv, up, tmpa);	produit_scal_vect_12(-uu, vp, tmpb);
						add_vect_12(tmpa, tmpb, tmpc);		produit_scal_vect_12(1.0/vv/vv, tmpc, f4zp);
					
						/*prise en compte des bordures par multiplicateurs*/
						produit_scal_vect_12(multiplicateur, f1xp, f1xp);
						produit_scal_vect_12(multiplicateur, f1yp, f1yp);
						produit_scal_vect_12(multiplicateur, f1zp, f1zp);
						produit_scal_vect_12(multiplicateur, f2xp, f2xp);
						produit_scal_vect_12(multiplicateur, f2yp, f2yp);
						produit_scal_vect_12(multiplicateur, f2zp, f2zp);
						produit_scal_vect_12(multiplicateur, f3xp, f3xp);
						produit_scal_vect_12(multiplicateur, f3yp, f3yp);
						produit_scal_vect_12(multiplicateur, f3zp, f3zp);
						produit_scal_vect_12(multiplicateur, f4xp, f4xp);
						produit_scal_vect_12(multiplicateur, f4yp, f4yp);
						produit_scal_vect_12(multiplicateur, f4zp, f4zp);
						
						no[ 1] = 3*p1-2;	no[ 2] = 3*p1-1;	no[ 3] = 3*p1-0;
						no[ 4] = 3*p2-2;	no[ 5] = 3*p2-1;	no[ 6] = 3*p2-0;
						no[ 7] = 3*p3-2;	no[ 8] = 3*p3-1;	no[ 9] = 3*p3-0;
						no[10] = 3*p4-2;	no[11] = 3*p4-1;	no[12] = 3*p4-0;
					
						if (Structure.type_solver == 1)
						{
   							for (zc = 1 ; zc<= 12; zc++) 
  							{
								ze[3*p1-2][eca-(3*p1-2)+no[zc]] -= f1xp[zc];
								ze[3*p1-1][eca-(3*p1-1)+no[zc]] -= f1yp[zc];
								ze[3*p1-0][eca-(3*p1-0)+no[zc]] -= f1zp[zc];

								ze[3*p2-2][eca-(3*p2-2)+no[zc]] -= f2xp[zc];
								ze[3*p2-1][eca-(3*p2-1)+no[zc]] -= f2yp[zc];
								ze[3*p2-0][eca-(3*p2-0)+no[zc]] -= f2zp[zc];

								ze[3*p3-2][eca-(3*p3-2)+no[zc]] -= f3xp[zc];
								ze[3*p3-1][eca-(3*p3-1)+no[zc]] -= f3yp[zc];
								ze[3*p3-0][eca-(3*p3-0)+no[zc]] -= f3zp[zc];

								ze[3*p4-2][eca-(3*p4-2)+no[zc]] -= f4xp[zc];
								ze[3*p4-1][eca-(3*p4-1)+no[zc]] -= f4yp[zc];
								ze[3*p4-0][eca-(3*p4-0)+no[zc]] -= f4zp[zc];
							}
						}
						else if (Structure.type_solver == 2)
						{
   							for (zc = 1 ; zc<= 12; zc++) 
  							{
								//affectation_pardiso(-f1xp[zc], 3*p1-2, no[zc]);
								//affectation_pardiso(-f1yp[zc], 3*p1-1, no[zc]);
								//affectation_pardiso(-f1zp[zc], 3*p1, no[zc]);

								//affectation_pardiso(-f2xp[zc], 3*p2-2, no[zc]);
								//affectation_pardiso(-f2yp[zc], 3*p2-1, no[zc]);
								//affectation_pardiso(-f2zp[zc], 3*p2, no[zc]);

								//affectation_pardiso(-f3xp[zc], 3*p3-2, no[zc]);
								//affectation_pardiso(-f3yp[zc], 3*p3-1, no[zc]);
								//affectation_pardiso(-f3zp[zc], 3*p3, no[zc]);

								//affectation_pardiso(-f4xp[zc], 3*p4-2, no[zc]);
								//affectation_pardiso(-f4yp[zc], 3*p4-1, no[zc]);
								//affectation_pardiso(-f4zp[zc], 3*p4, no[zc]);
							}
						}

   						for (zc = 1 ; zc<= 12; zc++) 
  							{
   							for (zd = 1 ; zd<= 12; zd++) 
  								{
  								if (rang[1][no[zc]] < no[zd])	rang[1][no[zc]] = no[zd];
  								if (rang[2][no[zc]] < no[zd])	rang[2][no[zc]] = no[zd];
  								if (rang[3][no[zc]] > no[zd])	rang[3][no[zc]] = no[zd];
  								if (rang[4][no[zc]] > no[zd])	rang[4][no[zc]] = no[zd];
  								}
  							}
  						/*for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f1xp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f1yp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f1zp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f2xp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f2yp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f2zp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f3xp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f3yp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f3zp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f4xp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f4yp[zc]);	printf("\n");
  						for (zc = 1 ; zc<= 12; zc++) 	printf("%8.0lf ",f4zp[zc]);	printf("\n");*/
  						}
  					}
      				/*TEST_debut
      					if (zu == 0)
      						{
      						Beta = beta;		Mu = mu;		Dist = dist;  
						Xm_x4 = v4m[1];		Ym_y4 = v4m[2];		Zm_z4 = v4m[3];
     						S41_41 = s41_41;	S12_41 = s12_41;	S23_41 = s23_41;
     						S12_23 = s12_23;	S12_12 = s12_12;	S23_23 = s23_23;
						Vf1[1] = vf1[1];	Vf1[2] = vf1[2];	Vf1[3] = vf1[3];
						Vf2[1] = vf2[1];	Vf2[2] = vf2[2];	Vf2[3] = vf2[3];
						Vf3[1] = vf3[1];	Vf3[2] = vf3[2];	Vf3[3] = vf3[3];
						Vf4[1] = vf4[1];	Vf4[2] = vf4[2];	Vf4[3] = vf4[3];
						}
					if ((zu > 0) && (zu < 13)) 
						{
						Betap[zu] 	= (beta - Beta) 	/ delta_x;
						Mup[zu] 	= (mu - Mu) 		/ delta_x;
						Distp[zu] 	= (dist - Dist) 	/ delta_x;
						Xm_x4p[zu] 	= (v4m[1] - Xm_x4) 	/ delta_x;
						Ym_y4p[zu] 	= (v4m[2] - Ym_y4) 	/ delta_x;
						Zm_z4p[zu] 	= (v4m[3] - Zm_z4) 	/ delta_x;
						S41_41p[zu]	= (s41_41 - S41_41) 	/ delta_x;
						S12_41p[zu]	= (s12_41 - S12_41) 	/ delta_x;
						S23_41p[zu]	= (s23_41 - S23_41) 	/ delta_x;
						S12_23p[zu]	= (s12_23 - S12_23) 	/ delta_x;
						S12_12p[zu]	= (s12_12 - S12_12) 	/ delta_x;
						S23_23p[zu]	= (s23_23 - S23_23) 	/ delta_x;
						F1xp[zu]	= (vf1[1] - Vf1[1]) 	/ delta_x;
						F1yp[zu]	= (vf1[2] - Vf1[2]) 	/ delta_x;
						F1zp[zu]	= (vf1[3] - Vf1[3]) 	/ delta_x;
						F2xp[zu]	= (vf2[1] - Vf2[1]) 	/ delta_x;
						F2yp[zu]	= (vf2[2] - Vf2[2]) 	/ delta_x;
						F2zp[zu]	= (vf2[3] - Vf2[3]) 	/ delta_x;
						F3xp[zu]	= (vf3[1] - Vf3[1]) 	/ delta_x;
						F3yp[zu]	= (vf3[2] - Vf3[2]) 	/ delta_x;
						F3zp[zu]	= (vf3[3] - Vf3[3]) 	/ delta_x;
						F4xp[zu]	= (vf4[1] - Vf4[1]) 	/ delta_x;
						F4yp[zu]	= (vf4[2] - Vf4[2]) 	/ delta_x;
						F4zp[zu]	= (vf4[3] - Vf4[3]) 	/ delta_x;
						}
      					if (zu == 1) v1[ 1] = v1[ 1] - delta_x;
      					if (zu == 2) v1[ 2] = v1[ 2] - delta_x;
      					if (zu == 3) v1[ 3] = v1[ 3] - delta_x;
      					if (zu == 4) v2[ 1] = v2[ 1] - delta_x;
      					if (zu == 5) v2[ 2] = v2[ 2] - delta_x;
      					if (zu == 6) v2[ 3] = v2[ 3] - delta_x;
      					if (zu == 7) v3[ 1] = v3[ 1] - delta_x;
      					if (zu == 8) v3[ 2] = v3[ 2] - delta_x;
      					if (zu == 9) v3[ 3] = v3[ 3] - delta_x;
      					if (zu ==10) v4[ 1] = v4[ 1] - delta_x;
      					if (zu ==11) v4[ 2] = v4[ 2] - delta_x;
      					if (zu ==12) v4[ 3] = v4[ 3] - delta_x;
      					}
				printf("s41_41p =");	imprvectreel(12, s41_41p);	printf("S41_41p =");	imprvectreel(12, S41_41p);
				printf("s12_41p =");	imprvectreel(12, s12_41p);	printf("S12_41p =");	imprvectreel(12, S12_41p);
				printf("s23_41p =");	imprvectreel(12, s23_41p);	printf("S23_41p =");	imprvectreel(12, S23_41p);
				printf("s12_23p =");	imprvectreel(12, s12_23p);	printf("S12_23p =");	imprvectreel(12, S12_23p);
				printf("s12_12p =");	imprvectreel(12, s12_12p);	printf("S12_12p =");	imprvectreel(12, S12_12p);
				printf("s23_23p =");	imprvectreel(12, s23_23p);	printf("S23_23p =");	imprvectreel(12, S23_23p);
				printf("betap =");	imprvectreel(12, betap);	printf("Betap =");	imprvectreel(12, Betap);
				printf("mup =");	imprvectreel(12, mup);		printf("Mup =");	imprvectreel(12, Mup);
				printf("distp =");	imprvectreel(12, distp);	printf("Distp =");	imprvectreel(12, Distp);
				printf("xm_x4p =");	imprvectreel(12, xm_x4p);	printf("Xm_x4p =");	imprvectreel(12, Xm_x4p);
				printf("ym_y4p =");	imprvectreel(12, ym_y4p);	printf("Ym_y4p =");	imprvectreel(12, Ym_y4p);
				printf("zm_z4p =");	imprvectreel(12, zm_z4p);	printf("Zm_z4p =");	imprvectreel(12, Zm_z4p);
				printf("f1xp =");	imprvectreel(12, f1xp);		printf("F1xp =");	imprvectreel(12, F1xp);
				printf("f1yp =");	imprvectreel(12, f1yp);		printf("F1yp =");	imprvectreel(12, F1yp);
				printf("f1zp =");	imprvectreel(12, f1zp);		printf("F1zp =");	imprvectreel(12, F1zp);
				printf("f2xp =");	imprvectreel(12, f2xp);		printf("F2xp =");	imprvectreel(12, F2xp);
				printf("f2yp =");	imprvectreel(12, f2yp);		printf("F2yp =");	imprvectreel(12, F2yp);
				printf("f2zp =");	imprvectreel(12, f2zp);		printf("F2zp =");	imprvectreel(12, F2zp);
				printf("f3xp =");	imprvectreel(12, f3xp);		printf("F3xp =");	imprvectreel(12, F3xp);
				printf("f3yp =");	imprvectreel(12, f3yp);		printf("F3yp =");	imprvectreel(12, F3yp);
				printf("f3zp =");	imprvectreel(12, f3zp);		printf("F3zp =");	imprvectreel(12, F3zp);
				printf("f4xp =");	imprvectreel(12, f4xp);		printf("F4xp =");	imprvectreel(12, F4xp);
				printf("f4yp =");	imprvectreel(12, f4yp);		printf("F4yp =");	imprvectreel(12, F4yp);
				printf("f4zp =");	imprvectreel(12, f4zp);		printf("F4zp =");	imprvectreel(12, F4zp);
				exit(0);
      				TEST_fin*/
				}										/*fin de if trouve*/		
  			}
  		}
	}



