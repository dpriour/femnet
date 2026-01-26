#define PRINCIPAL 0
#include "4c19.h"

void efforttraineeelem_tab(int zg,int zh,int zi,double *C)	
	{
	/*
	cette procedure prend en entree le numero d'un element zg, le numero selon x des deux 
	extremites de cet element zh,zi et le vecteur courant C (C[1] C[2] et C[3]). Elle retourne 
	un vecteur ,note NT ,a 6 composantes contenant la somme des efforts de trainee d et
	de portance l suivant x,y,z aux deux extremites de l'element.
	Ainsi NT[i]= d[i]+l[i] pour i de 1 à 6.
	*/
	
	int zj,nb_tab;
  	double modC,modB,modN,sign,prodsc;  	
  	double nd,nl,CD,CL;  	
  	double temp7;
  	double N[4],l[4],d[4],B[4],theta;
  	double theta_min,theta_max,CD_min,CD_max,CL_min,CL_max;
  	
  	nb_tab = TypeElement[zg].nb_tab_drag_lift;
  	
	B[1] = wf[zi  ]-wf[zh  ];    		B[2] = wf[zi+1]-wf[zh+1];    		B[3] = wf[zi+2]-wf[zh+2];	//vecteur element
	//printf("B ");imprvectreel(3, B);  
	modC=sqrt(produit_scal(C,C));	/*calcul de la norme de C*/
  	modB=sqrt(produit_scal(B,B));	/*calcul de la norme de B*/
	//printf("modC %lf modB %lf \n",modC,modB);
			  		  		  	
  	/*les intermediaires */
  	prodsc = produit_scal(C,B);
	//printf("prodsc %lf \n",prodsc);
  		  		  	     		    		
  	/*calcul de l'angle theta entre C et l'element : arccos du produit scalaire des vecteurs C et B normes*/    		
  	if ((modB==0) || (modC==0))	  		theta = 0;
  	else			    			
		{
		temp7 = prodsc/modC/modB;
		if (temp7 > 1.0) temp7 = 1.0;
		if (temp7 <-1.0) temp7 =-1.0;
		theta = acos(temp7);
		}
	//printf("theta %lf \n",theta);
	
	for (zj = 1; zj<=nb_tab-1 ; zj++)
		{
		if ((theta >= TypeElement[zg].angle_tab_drag_lift[zj]*PI/180.0) && (theta < TypeElement[zg].angle_tab_drag_lift[zj+1]*PI/180.0))
			{
			theta_min = TypeElement[zg].angle_tab_drag_lift[zj]*PI/180.0;	theta_max = TypeElement[zg].angle_tab_drag_lift[zj+1]*PI/180.0;
			CD_min = TypeElement[zg].drag_tab_drag_lift[zj];			CD_max = TypeElement[zg].drag_tab_drag_lift[zj+1];
			CL_min = TypeElement[zg].lift_tab_drag_lift[zj];			CL_max = TypeElement[zg].lift_tab_drag_lift[zj+1];
			CD = CD_min + (theta-theta_min)/(theta_max-theta_min)*(CD_max-CD_min);
			CL = CL_min + (theta-theta_min)/(theta_max-theta_min)*(CL_max-CL_min);
			}
		}
	if (theta == TypeElement[zg].angle_tab_drag_lift[nb_tab]*PI/180.0)
		{
		CD = TypeElement[zg].drag_tab_drag_lift[nb_tab];
		CL = TypeElement[zg].lift_tab_drag_lift[nb_tab];
		}

	//calcul du vecteur N normal a B et C
	N[1] = C[2]*(wf[zi+2]-wf[zh+2])-C[3]*(wf[zi+1]-wf[zh+1]);
	N[2] = C[3]*(wf[zi+0]-wf[zh+0])-C[1]*(wf[zi+2]-wf[zh+2]);
	N[3] = C[1]*(wf[zi+1]-wf[zh+1])-C[2]*(wf[zi+0]-wf[zh+0]);
	//printf("N ");imprvectreel(3, N);  
	
	modN = sqrt(produit_scal(N,N));	/*calcul de la norme de N*/
	//printf("modN %lf \n",modN);
	
	/* Amplitude des efforts de trainee sur la totalite de l element*/
	nd = 0.5*RHO*CD*Element[zg].diametrehydro*Element[zg].lgrepos*modC*modC;
	//printf("RHO %lf \n",RHO);
	//printf("CD %lf CL %lf zg %d diam %lf lo %lf modC %lf \n",CD,CL,zg,Element[zg].diametrehydro,Element[zg].lgrepos,modC);
	
	/* Amplitude des efforts de portance sur la totalite de l element*/
	if (theta < PI/2)
		{
		nl = -0.5*RHO*CL*Element[zg].diametrehydro*Element[zg].lgrepos*modC*modC;
		}
	else
		{
		nl =  0.5*RHO*CL*Element[zg].diametrehydro*Element[zg].lgrepos*modC*modC;
		}
	
	//printf("nd %lf nl %lf \n",nd,nl);
	
	//efforts de trainee
	if (modC == 0.0)
		{
		d[1] = 0.0;					d[2] = 0.0;					d[3] = 0.0;
		}
	else
		{
		d[1] = nd*C[1]/modC;				d[2] = nd*C[2]/modC;				d[3] = nd*C[3]/modC;
		}
	
	//efforts de portance
	if ((modC == 0.0) || (modN == 0.0))
		{
		l[1] = 0.0;					l[2] = 0.0;					l[3] = 0.0;
		}
	else
		{
		l[1] = nl/modC/modN*(C[3]*N[2]-C[2]*N[3]);	l[2] = nl/modC/modN*(C[1]*N[3]-C[3]*N[1]);	l[3] = nl/modC/modN*(C[2]*N[1]-C[1]*N[2]);
		}

	//printf("d ");imprvectreel(3, d);  
	//printf("l ");imprvectreel(3, l);  
	
	NT[1] = (d[1] + l[1])/2.0; 		NT[2] = (d[2] + l[2])/2.0; 		NT[3] = (d[3] + l[3])/2.0;
	NT[4] = (d[1] + l[1])/2.0; 		NT[5] = (d[2] + l[2])/2.0; 		NT[6] = (d[3] + l[3])/2.0;
	//printf("NT ");imprvectreel(6, NT);  

     	}
