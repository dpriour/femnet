#define PRINCIPAL 0
#include "4c19.h"  

void deck_contact()
	{
	/*force effect deck if any*/
	int zk,zi,ma;
	double v1[4],v2[4],v3[4],v4[4],vm[4],v12[4],v23[4],v31[4],v41[4],v42[4],v43[4],v4m[4];
	double uu[4],vv[4],ww[4],nn[4];
	double s12_23,s23_41,s23_23,s12_41,s12_12,s41_41,dist,dist2,dist3;
	double alpha,beta,gamma,delta,epsilon,eta,theta,phi,kappa,lambda,nu,mu,sigma,tau;
	double force[4],force_amplitude,vect_amplitude,K[4][4];
	printf("%d deck \n",Structure.nb_deck);
	for (zk = 1; zk<= Structure.nb_deck; zk++)
		{
		printf("master %4d ",Deck[zk].master_node);
		printf("vertex1 %6.2lf m ",Deck[zk].x1);	printf(" %6.2lf m ",Deck[zk].y1);	printf(" %6.2lf m ",Deck[zk].z1);
		printf("vertex2 %6.2lf m ",Deck[zk].x2);	printf(" %6.2lf m ",Deck[zk].y2);	printf(" %6.2lf m ",Deck[zk].z2);
		printf("vertex3 %6.2lf m ",Deck[zk].x3);	printf(" %6.2lf m ",Deck[zk].y3);	printf(" %6.2lf m ",Deck[zk].z3);
		printf("thikness %6.2lf m ",Deck[zk].thickness);
		printf("stiffness %8.0lf N/m\n",Deck[zk].stiffness);
		ma = Deck[zk].master_node;
		/*coordinates of points vertex v1 v2 & v3*/
		v1[1] = wf [3*ma-2]+Deck[zk].x1;	v1[2] = wf [3*ma-1]+Deck[zk].y1;	v1[3] = wf [3*ma-0]+Deck[zk].z1;
		v2[1] = wf [3*ma-2]+Deck[zk].x2;	v2[2] = wf [3*ma-1]+Deck[zk].y2;	v2[3] = wf [3*ma-0]+Deck[zk].z2;
		v3[1] = wf [3*ma-2]+Deck[zk].x3;	v3[2] = wf [3*ma-1]+Deck[zk].y3;	v3[3] = wf [3*ma-0]+Deck[zk].z3;
		substract_vect(v2,v1,v12);	//v12[1] = v2[1]-v1[1];	v12[2] = v2[2]-v1[2];	v12[3] = v2[3]-v1[3];	
		substract_vect(v3,v2,v23);	//v23[1] = v3[1]-v2[1];	v23[2] = v3[2]-v2[2];	v23[3] = v3[3]-v2[3];
		substract_vect(v1,v3,v31);	//v31[1] = v1[1]-v3[1];	v31[2] = v1[2]-v3[2];	v31[3] = v1[3]-v3[3];
		produit_vect3(v12, v23, nn);	
		produit_vect3(v12, nn, uu);	
		produit_vect3(v23, nn, vv);	
		produit_vect3(v31, nn, ww);	
		s12_23 = produit_scal(v23, v12);
		s23_23 = produit_scal(v23, v23);
	  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
 			{
			v4[1] = wf [3*zi-2];	
			v4[2] = wf [3*zi-1];	
			v4[3] = wf [3*zi-0];	/*coordinates of point 4*/
			substract_vect(v1,v4,v41);	
			v41[1] = v1[1]-v4[1];	
			v41[2] = v1[2]-v4[2];	
			v41[3] = v1[3]-v4[3];		
			substract_vect(v2,v4,v42);	//v41[1] = v1[1]-v4[1];	v41[2] = v1[2]-v4[2];	v41[3] = v1[3]-v4[3];		
			substract_vect(v3,v4,v43);	//v41[1] = v1[1]-v4[1];	v41[2] = v1[2]-v4[2];	v41[3] = v1[3]-v4[3];		
			//s23_41 = produit_scal(v41, v23);
			//s12_41 = produit_scal(v41, v12);
			//s12_12 = produit_scal(v12, v12);
			//s41_41 = produit_scal(v41, v41);
			//alpha = (s12_23*s23_41-s23_23*s12_41) / (s23_23*s12_12-s12_23*s12_23);
			//beta  = (s12_23*s12_41-s12_12*s23_41) / (s23_23*s12_12-s12_23*s12_23);
			calc_alphaa_betaa(v41, v12, v23, &alpha, &beta);
			calc_alphaa_betaa(v42, v23, vv, &gamma, &delta);
			calc_alphaa_betaa(v43, v31, ww, &epsilon, &eta);
			calc_alphaa_betaa(v41, v12, uu, &theta, &phi);
			calc_alphaa_betaa(v41, v12, v31, &kappa, &lambda);
			calc_alphaa_betaa(v42, v12, v23, &nu, &mu);
			calc_alphaa_betaa(v43, v23, v31, &sigma, &tau);
			//printf("zi %4d ",zi);
			/*
			printf("pt4 : x %lf y %lf z %lf\n",v4[1],v4[2],v4[3]);
			printf("uu : x %lf y %lf z %lf\n",uu[1],uu[2],uu[3]);
			printf("vv : x %lf y %lf z %lf\n",vv[1],vv[2],vv[3]);
			printf("ww : x %lf y %lf z %lf\n",ww[1],ww[2],ww[3]);
			printf("zi %d alpha %lf beta %lf\n",zi,alpha,beta);
			printf("zi %d gamma %lf delta %lf\n",zi,gamma,delta);
			printf("zi %d epsilon %lf eta %lf\n",zi,epsilon,eta);
			printf("zi %d theta %lf phi %lf\n",zi,theta,phi);
			printf("zi %d kappa %lf lambda %lf\n",zi,kappa,lambda);
			printf("zi %d nu %lf mu %lf\n",zi,nu,mu);
			printf("zi %d sigma %lf tau %lf\n",zi,sigma,tau);
			*/

			if ((alpha>=0.0) && (alpha<=1.0) && (beta>=0.0) && (beta<=alpha))
				{
				//zone A: m is inside the triangle v1 v2 v3. v4 is above the triangle v1 v2 v3.
				v4m[1] = v41[1]+alpha*v12[1]+beta*v23[1];		//m in triangle of v1, v2 and v3 such as m_v4 normal to v1, v2 and v3
				v4m[2] = v41[2]+alpha*v12[2]+beta*v23[2];		//v1_m is alpha*v12 + beta*v23
				v4m[3] = v41[3]+alpha*v12[3]+beta*v23[3];
				dist = sqrt(produit_scal(v4m, v4m));
				if (dist < Deck[zk].thickness)
					{
					force_amplitude = (Deck[zk].thickness - dist) * Deck[zk].stiffness;
					force[1] = - force_amplitude * v4m[1] / dist;
					force[2] = - force_amplitude * v4m[2] / dist;
					force[3] = - force_amplitude * v4m[3] / dist;
					vm[1] = v1[1]+alpha*v12[1]+beta*v23[1];		//m in triangle of v1, v2 and v3 such as m_v4 normal to v1, v2 and v3
					vm[2] = v1[2]+alpha*v12[2]+beta*v23[2];		//v1_m is alpha*v12 + beta*v23
					vm[3] = v1[3]+alpha*v12[3]+beta*v23[3];
					dist2 = dist*dist;
					dist3 = dist*dist2;

					K[1][1] = (vm[1]*vm[1]*Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist3-(Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist+(vm[1]*vm[1]*Deck[zk].stiffness)/dist2;
					K[1][2] = (vm[1]*vm[2]*Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist3+(vm[1]*vm[2]*Deck[zk].stiffness)/dist2;
					K[1][3] = (vm[1]*vm[3]*Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist3+(vm[1]*vm[3]*Deck[zk].stiffness)/dist2;
					K[2][1] = (vm[1]*vm[2]*Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist3+(vm[1]*vm[2]*Deck[zk].stiffness)/dist2;
					K[2][2] = (vm[2]*vm[2]*Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist3-(Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist+(vm[2]*vm[2]*Deck[zk].stiffness)/dist2;
					K[2][3] = (vm[2]*vm[3]*Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist3+(vm[2]*vm[3]*Deck[zk].stiffness)/dist2;
					K[3][1] = (vm[1]*vm[3]*Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist3+(vm[1]*vm[3]*Deck[zk].stiffness)/dist2;
					K[3][2] = (vm[2]*vm[3]*Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist3+(vm[2]*vm[3]*Deck[zk].stiffness)/dist2;
					K[3][3] = (vm[3]*vm[3]*Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist3-(Deck[zk].stiffness*(Deck[zk].thickness-dist))/dist+(vm[3]*vm[3]*Deck[zk].stiffness)/dist2;					
					/*printf("pt1 : x %lf y %lf z %lf  \n",v1[1],v1[2],v1[3]);
					printf("pt2 : x %lf y %lf z %lf  \n",v2[1],v2[2],v2[3]);
					printf("pt3 : x %lf y %lf z %lf  \n",v3[1],v3[2],v3[3]);
					printf("pt4 : x %lf y %lf z %lf  \n",v4[1],v4[2],v4[3]);
					printf("vm : x %lf y %lf z %lf  \n",vm[1],vm[2],vm[3]);
					printf("v4m : x %lf y %lf z %lf  \n",v4m[1],v4m[2],v4m[3]);
					printf("v41 : x %lf y %lf z %lf  \n",v41[1],v41[2],v41[3]);
					printf("v12 : x %lf y %lf z %lf  \n",v12[1],v12[2],v12[3]);
					printf("v23 : x %lf y %lf z %lf  \n",v23[1],v23[2],v23[3]);
					printf("dist  %lf\n",dist);
					printf("zi %d alpha %lf beta %lf\n",zi,alpha,beta);
					printf("force : x %lf y %lf z %lf\n",force[1],force[2],force[3]);*/
					}
				/*printf("A ");
				printf("alpha %lf beta %lf ",alpha,beta);
				printf("v4 %lf  %lf %lf ",v4[1],v4[2],v4[3]);*/
				}
			if ((gamma>=0.0) && (gamma<=1.0) && (delta>0.0))
				{
				//zone B:
				v4m[1] = v42[1]+gamma*v23[1];		//m on side v2 to v3 
				v4m[2] = v42[2]+gamma*v23[2];		//v2_p is gamma*v23 + delta*vv
				v4m[3] = v42[3]+gamma*v23[3];
				dist = sqrt(produit_scal(v4m, v4m));
				//printf("B ");
				}
			if ((epsilon>=0.0) && (epsilon<=1.0) && (eta>0.0))
				{
				//zone C:
				v4m[1] = v43[1]+epsilon*v31[1];		//m on side v3 to v1 
				v4m[2] = v43[2]+epsilon*v31[2];		//v3_p is eplsilon*v31 + eta*ww
				v4m[3] = v43[3]+epsilon*v31[3];
				dist = sqrt(produit_scal(v4m, v4m));
				//printf("C ");
				}
			if ((theta>=0.0) && (theta<=1.0) && (phi>0.0))
				{
				//zone D:
				v4m[1] = v41[1]+theta*v12[1];		//m on side v3 to v1 
				v4m[2] = v41[2]+theta*v12[2];		//v1_p is theta*v12 + phi*uu
				v4m[3] = v41[3]+theta*v12[3];
				dist = sqrt(produit_scal(v4m, v4m));
				//printf("D ");
				}
			if ((kappa<0.0) && (lambda>0.0))
				{
				//zone E:
				dist = sqrt(produit_scal(v41, v41));	//m is v1	v1_p is kappa*uu + lambda*ww
				//printf("E ");
				}
			if ((nu>0.0) && (mu<0.0))
				{
				//zone F:
				dist = sqrt(produit_scal(v42, v42));	//m is v2	v2_p is mu*vv + nu*uu
				//printf("F ");
				}
			if ((sigma>0.0) && (tau<0.0))
				{
				//zone G:
				dist = sqrt(produit_scal(v43, v43));	//m is v3	v3_p is sigma*ww + tau*vv
				//printf("G ");
				}
			//printf("\n");
  			}
		}
	//exit(0);
	}						

void calc_alphaa_betaa(double vect_41[4], double vect_12[4], double vect_23[4], double *alphaa, double *betaa)
	{
	double ps23_41,ps12_41,ps12_12,ps23_23,ps12_23;
	ps12_23 = produit_scal(vect_12, vect_23);
	ps23_23 = produit_scal(vect_23, vect_23);
	ps23_41 = produit_scal(vect_41, vect_23);
	ps12_41 = produit_scal(vect_41, vect_12);
	ps12_12 = produit_scal(vect_12, vect_12);
	*alphaa = (ps12_23*ps23_41-ps23_23*ps12_41) / (ps23_23*ps12_12-ps12_23*ps12_23);
	*betaa  = (ps12_23*ps12_41-ps12_12*ps23_41) / (ps23_23*ps12_12-ps12_23*ps12_23);
	//printf("ps23_41 %lf ps12_41 %lf ps12_12 %lf \n",ps23_41,ps12_41,ps12_12); 
	//printf("alphaa %lf betaa %lf  \n",*alphaa,*betaa); exit(0);
	}



