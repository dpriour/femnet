#define PRINCIPAL 0
#include "4c19.h"

void efforttraineeelem(int zg,int zh,int zi,double *V)	
	{
	/*
	cette procedure prend en entree le numero d'un element zg, le numero selon x des deux 
	extremites de cet element zh,zi et le vecteur courant V (V[1] V[2] et V[3]). Elle retourne 
	un vecteur ,note NT ,a 6 composantes contenant la somme des efforts normaux N1 et
	tangentiels T1 suivant x,y,z aux deux extremites de l'element.
	Ainsi NT[i]= N1[i]+T1[i].
	Cette procedure retourne aussi une matrice wg contenant 36 termes. C'est la matrice de
	raideur de l'element 
	wg[1][3] = derivee de NT[1] par rapport a z1
	wg[1][6] = derivee de NT[1] par rapport a z2
	x1,y1,z1 sont les coordonnees de l'extremite 1
	x2,y2,z2 sont les coordonnees de l'extremite 2
	*/
	
  	int zk,zj;
  	double modV,model,modne,sign,prodsc;  	
  	double f,k,n,t;  	
  	double temp1,temp2,temp3,temp4,temp5,temp6,temp7;
  	double d1,d2,d3,d4,d5,d6,dd1,dd2,dd3,dd4,dd5,dd6;
  	double e1,e2,e3,e4,e5,e6,ee1,ee2,ee3,ee4,ee5,ee6,eee1,eee2,eee3,eee4,eee5,eee6;
  	double F1,F2,F3,F4,F5,F6,g1,g2,g3,g4;
  	double a1,a2,a3,a4,a5,a6,aa1,aa2,aa3,aa4,aa5,aa6,aaa1,aaa2,aaa3,aaa4,aaa5,aaa6;
  	double b1,b2,b3,b4,b5,b6,bb1,bb2,bb3,bb4,bb5,bb6,bbb1,bbb2,bbb3,bbb4,bbb5,bbb6;
  	double c1,c2,c3,c4,cc1,cc2,cc3,cc4;
  	double DNT1x1,DNT1y1,DNT1z1,DNT1x2,DNT1y2,DNT1z2;
  	double DNT2x1,DNT2y1,DNT2z1,DNT2x2,DNT2y2,DNT2z2;
  	double DNT3x1,DNT3y1,DNT3z1,DNT3x2,DNT3y2,DNT3z2;
  	double DNT4x1,DNT4y1,DNT4z1,DNT4x2,DNT4y2,DNT4z2;
  	double DNT5x1,DNT5y1,DNT5z1,DNT5x2,DNT5y2,DNT5z2;
  	double DNT6x1,DNT6y1,DNT6z1,DNT6x2,DNT6y2,DNT6z2;
  	double ne[4],te[4],el[4],N1[7],T1[7],theta;
  	
  	/*printf("debut calcul des efforts\n");
	printf("V \n");
	imprvectreel(3, V);*/    		
	
	/*
	if ((zg == 2))
		{
			printf("wf[zi+2] %lf  wf[zh+2] %lf  \n",wf[zi+2],wh[zi+2]);
		}
	*/

    	if ((wf[zi+2] >= 0.0) && (wf[zh+2] >= 0.0)) 
    		{
      		/* element exonde : pas d effort de trainee*/
      		/* extremite 1 */
      		T1[1] = 0.0; T1[2] = 0.0; T1[3] = 0.0;  
      		N1[1] = 0.0; N1[2] = 0.0; N1[3] = 0.0;
      		/* extremite 2 */  
    		T1[4] = 0.0; T1[5] = 0.0; T1[6] = 0.0;
    		N1[4] = 0.0; N1[5] = 0.0; N1[6] = 0.0;
    		
    		NT[1] = N1[1] + T1[1]; 		NT[2] = N1[2] + T1[2]; 		NT[3] = N1[3] + T1[3];
    		NT[4] = N1[4] + T1[4]; 		NT[5] = N1[5] + T1[5]; 		NT[6] = N1[6] + T1[6];
  		/*mise a zero de la matrice de raideur des elements wg de taille 6*6*/
  		for (zk = 1;zk <= 6;zk++)
  			{
  			for (zj = 1;zj <= 6;zj++)
  		 		{
  		 		wg[zk][zj]=0.0;
  		 		}
  		 	}
    		}
    	else	
    		{    		
    		el[1] = wf[zi  ]-wf[zh  ];    		el[2] = wf[zi+1]-wf[zh+1];    		el[3] = wf[zi+2]-wf[zh+2];
  		modV=sqrt(V[1]*V[1]+V[2]*V[2]+V[3]*V[3]);		/*calcul de la norme de V*/
	  	model=sqrt(el[1]*el[1]+el[2]*el[2]+el[3]*el[3]);	/*calcul de la norme de el*/
	  		  		  		  	
	  	/*les intermediaires */
	  	prodsc  = (wf[zi  ]-wf[zh  ])*V[1]+(wf[zi+1]-wf[zh+1])*V[2];
	  	temp1   = -V[1]*(pow(wf[zi+1]-wf[zh+1],2.0)+pow(wf[zi+2]-wf[zh+2],2.0)) +V[2]*(wf[zi+1]-wf[zh+1])*(wf[zi  ]-wf[zh  ]);
		temp2   =  V[2]*(pow(wf[zi+2]-wf[zh+2],2.0)+pow(wf[zi  ]-wf[zh  ],2.0)) -V[1]*(wf[zi  ]-wf[zh  ])*(wf[zi+1] -wf[zh+1]);
		temp3   = pow(wf[zi+1]-wf[zh+1],2.0)+pow(wf[zi+2]-wf[zh+2],2.0);
		temp4   = pow(wf[zi  ]-wf[zh  ],2.0)+pow(wf[zi+2]-wf[zh+2],2.0);
		temp5   = pow(wf[zi  ]-wf[zh  ],2.0)+pow(wf[zi+1]-wf[zh+1],2.0);
		temp6   = V[2]*V[2]*(pow(wf[zi+2]-wf[zh+2],2.0)+pow(wf[zi  ]-wf[zh  ],2.0))-2*V[1]*V[2]*(wf[zi  ]-wf[zh ])*(wf[zi+1]-wf[zh+1])+V[1]*V[1]*(pow(wf[zi+2]-wf[zh+2],2.0)+pow(wf[zi+1]-wf[zh+1],2.0));
	  		  		  	     		    		
	  	/*calcul de l'angle entre V et theta : c'est l'arccos du produit scalaire des vecteurs V et el normes !!!!*/    		
	  	if ((model==0) || (modV==0))	  		theta = 0;
	  	else			    			
			{
			temp7 = prodsc/modV/model;
			if (temp7 > 1.0) temp7 = 1.0;
			if (temp7 <-1.0) temp7 =-1.0;
			theta=acos(temp7);
			}
    		
   		/* Calcul des directions des efforts, retournees dans les vecteurs ne et te*/
    		/*norme de ne*/
    		modne = sin(theta);
    		
     		/* ne est le produit vectoriel de el/model et de (v/modV  vectoriel  el/model) */
	  	if ((model==0) || (modV==0) || (modne==0))
	  		{
	  		ne[1] = 0;	  				ne[2] = 0;	  				ne[3] = 0;
	  		}
	  	else
    			{
     			ne[1] = -temp1/pow(model,2.0)/modV/modne;	ne[2] =  temp2/pow(model,2.0)/modV/modne;	ne[3] = -(wf[zi+2]-wf[zh+2])*prodsc/pow(model,2.0)/modV/modne;
			}
		
		if ((theta < PI/2) &&  (theta > -PI/2))			sign = 1;
		else							sign = -1;

	  	if (model==0)
	  		{
	  		te[1] = 0;	  		te[2] = 0;	  		te[3] = 0;
	  		}
	  	else
    			{
			te[1] = sign*el[1]/model;	te[2] = sign*el[2]/model;	te[3] = sign*el[3]/model;
			}
			
		/*calcul des amplitudes */
		/*on ne prend pas en compte l allongement des elements*/
		
   		f = Element[zg].ftangent;
     		k = 0.5*RHO*Element[zg].cdnormal*Element[zg].diametrehydro*Element[zg].lgrepos*modV*modV;
    		
	  	/*n = amplitude des efforts normaux */
  	   	/*t = amplitude des efforts tangentiels */
  	   	
		n = k*sin(theta)*sin(theta);
		t = f*k*cos(theta)*cos(theta);
		
		
      		N1[1] = 0.5*n*ne[1];      		N1[2] = 0.5*n*ne[2];     		N1[3] = 0.5*n*ne[3];
      		N1[4] = 0.5*n*ne[1];      		N1[5] = 0.5*n*ne[2];        		N1[6] = 0.5*n*ne[3];
		
      
      		T1[1] = 0.5*t*te[1];      		T1[2] = 0.5*t*te[2];         		T1[3] = 0.5*t*te[3];
      		T1[4] = 0.5*t*te[1];           		T1[5] = 0.5*t*te[2];           		T1[6] = 0.5*t*te[3];
      		
     		/*CALCULS DES DERIVEES de n,t,ne,te*/
    			/*derivees de n par rapport a x1,x2,y1,y2,z1,z2*/
	  	if ((model==0.0) || (modV==0.0))
	  		{
	  		d1 = 0.0;	d2 = 0.0;	 d3 = 0.0;	d4 = 0.0;	d5 = 0.0;	d6 = 0.0;
	  		}
	  	else
    			{
    			d1 = -2*k*prodsc*temp1/pow(modV,2.0)/pow(model,4.0);
			d2 =  2*k*prodsc*temp1/pow(modV,2.0)/pow(model,4.0);
			d3 =  2*k*prodsc*temp2/pow(modV,2.0)/pow(model,4.0);
			d4 = -2*k*prodsc*temp2/pow(modV,2.0)/pow(model,4.0);
			d5 = -2*k*pow(prodsc,2.0)*(wf[zi+2]-wf[zh+2])/pow(modV,2.0)/pow(model,4.0);
			d6 =  2*k*pow(prodsc,2.0)*(wf[zi+2]-wf[zh+2])/pow(modV,2.0)/pow(model,4.0);
			}
			
    			/*derivees de t par rapport a x1,x2,y1,y2,z1,z2*/
	  	if ((model==0.0) || (modV==0.0))
	  		{
	  		dd1 = 0.0;	dd2 = 0.0;	dd3 = 0.0;	dd4 = 0.0;	dd5 = 0.0;	dd6 = 0.0;
	  		}
	  	else
    			{
    			dd1 =  2*f*k*prodsc*temp1/pow(modV,2.0)/pow(model,4.0);
			dd2 = -2*f*k*prodsc*temp1/pow(modV,2.0)/pow(model,4.0);
			dd3 = -2*f*k*prodsc*temp2/pow(modV,2.0)/pow(model,4.0);
			dd4 =  2*f*k*prodsc*temp2/pow(modV,2.0)/pow(model,4.0);
			dd5 =  2*f*k*pow(prodsc,2.0)*(wf[zi+2]-wf[zh+2])/pow(modV,2.0)/pow(model,4.0);
			dd6 = -2*f*k*pow(prodsc,2.0)*(wf[zi+2]-wf[zh+2])/pow(modV,2.0)/pow(model,4.0);
			}
			
    			/*derivees de temp1 par rapport a x1,x2,y1,y2,z1,z2*/
			e1 = -(wf[zi+1]-wf[zh+1])*V[2];
			e2 =  (wf[zi+1]-wf[zh+1])*V[2];
			e3 =  2*V[1]*(wf[zi+1]-wf[zh+1])-V[2]*(wf[zi  ]-wf[zh  ]); 
			e4 = -2*V[1]*(wf[zi+1]-wf[zh+1])+V[2]*(wf[zi  ]-wf[zh  ]); 
			e5 =  2*V[1]*(wf[zi+2]-wf[zh+2]); 
			e6 = -2*V[1]*(wf[zi+2]-wf[zh+2]);
			
			/*derivees de model^2 par rapport a x1,x2,y1,y2,z1,z2*/
			ee1 = -2*(wf[zi  ]-wf[zh  ]); 
			ee2 =  2*(wf[zi  ]-wf[zh  ]);
			ee3 = -2*(wf[zi+1]-wf[zh+1]);
			ee4 =  2*(wf[zi+1]-wf[zh+1]);
			ee5 = -2*(wf[zi+2]-wf[zh+2]);
			ee6 =  2*(wf[zi+2]-wf[zh+2]);
			
		/*derivees de modne par rapport a x1,x2,y1,y2,z1,z2*/
		if ((model==0) || (modV==0) || (temp6==0))
			{
			eee1 = 0.0;	eee2 = 0.0;	eee3 = 0.0;	eee4 = 0.0;	eee5 = 0.0;	eee6 = 0.0;
			}
		else
			{
			eee1 = -1.0/pow(temp6/pow(model,2.0)/pow(modV,2.0),0.5)*prodsc*temp1/pow(model,4.0)/pow(modV,2.0);
			eee2 =  1.0/pow(temp6/pow(model,2.0)/pow(modV,2.0),0.5)*prodsc*temp1/pow(model,4.0)/pow(modV,2.0);
			eee3 =  1.0/pow(temp6/pow(model,2.0)/pow(modV,2.0),0.5)*prodsc*temp2/pow(model,4.0)/pow(modV,2.0);
			eee4 = -1.0/pow(temp6/pow(model,2.0)/pow(modV,2.0),0.5)*prodsc*temp2/pow(model,4.0)/pow(modV,2.0);
			eee5 = -pow(prodsc,2.0)*(wf[zi+2]-wf[zh+2])/pow(temp6/pow(model,2.0)/pow(modV,2.0),0.5)/pow(model,4.0)/pow(modV,2.0);
			eee6 =  pow(prodsc,2.0)*(wf[zi+2]-wf[zh+2])/pow(temp6/pow(model,2.0)/pow(modV,2.0),0.5)/pow(model,4.0)/pow(modV,2.0);
			}
			
		/*derivees de temp2 par rapport a x1,x2,y1,y2,z1,z2*/
		F1 = -2.0*V[2]*(wf[zi  ]-wf[zh  ])+V[1]*(wf[zi+1]-wf[zh+1]);
		F2 =  2.0*V[2]*(wf[zi  ]-wf[zh  ])-V[1]*(wf[zi+1]-wf[zh+1]);
		F3 =  (wf[zi  ]-wf[zh  ])*V[1];
		F4 = -(wf[zi  ]-wf[zh  ])*V[1];
		F5 = -2.0*V[2]*(wf[zi+2]-wf[zh+2]);
		F6 =  2.0*V[2]*(wf[zi+2]-wf[zh+2]);
		
		/*derivees de prodsc par rapport a x1,x2,y1,y2*/
		g1 = -V[1];		g2 =  V[1];		g3 = -V[2];		g4 =  V[2];

		
		
    		/*derivees de ne[1] par rapport a x1,x2,y1,y2,z1,z2*/
	  	if ((model==0) || (modV==0) || (modne==0))
	  		{
	  		a1 = 0;	  	a2 = 0;	  	a3 = 0;	  	a4 = 0;		a5 = 0;		a6 = 0;
	  		}
	  	else
    			{
			a1 = -(e1*pow(model,2.0)*modV*modne-temp1*(ee1*modV*modne+pow(model,2.0)*modV*eee1))/pow(pow(model,2.0)*modV*modne,2.0);
			a2 = -(e2*pow(model,2.0)*modV*modne-temp1*(ee2*modV*modne+pow(model,2.0)*modV*eee2))/pow(pow(model,2.0)*modV*modne,2.0);
			a3 = -(e3*pow(model,2.0)*modV*modne-temp1*(ee3*modV*modne+pow(model,2.0)*modV*eee3))/pow(pow(model,2.0)*modV*modne,2.0);
			a4 = -(e4*pow(model,2.0)*modV*modne-temp1*(ee4*modV*modne+pow(model,2.0)*modV*eee4))/pow(pow(model,2.0)*modV*modne,2.0);
			a5 = -(e5*pow(model,2.0)*modV*modne-temp1*(ee5*modV*modne+pow(model,2.0)*modV*eee5))/pow(pow(model,2.0)*modV*modne,2.0);
			a6 = -(e6*pow(model,2.0)*modV*modne-temp1*(ee6*modV*modne+pow(model,2.0)*modV*eee6))/pow(pow(model,2.0)*modV*modne,2.0);
			}

     			/*derivees de ne[2] par rapport a x1,x2,y1,y2,z1,z2*/
	  	if ((model==0) || (modV==0) || (modne==0))
	  		{
	  		aa1 = 0;	aa2 = 0;	aa3 = 0;	aa4 = 0;	aa5 = 0;	aa6 = 0;
	  		}
	  	else
    			{
			aa1 = (F1*pow(model,2.0)*modV*modne-temp2*(ee1*modV*modne+pow(model,2.0)*modV*eee1))/pow(pow(model,2.0)*modV*modne,2.0);
			aa2 = (F2*pow(model,2.0)*modV*modne-temp2*(ee2*modV*modne+pow(model,2.0)*modV*eee2))/pow(pow(model,2.0)*modV*modne,2.0);
			aa3 = (F3*pow(model,2.0)*modV*modne-temp2*(ee3*modV*modne+pow(model,2.0)*modV*eee3))/pow(pow(model,2.0)*modV*modne,2.0);
			aa4 = (F4*pow(model,2.0)*modV*modne-temp2*(ee4*modV*modne+pow(model,2.0)*modV*eee4))/pow(pow(model,2.0)*modV*modne,2.0);
			aa5 = (F5*pow(model,2.0)*modV*modne-temp2*(ee5*modV*modne+pow(model,2.0)*modV*eee5))/pow(pow(model,2.0)*modV*modne,2.0);
			aa6 = (F6*pow(model,2.0)*modV*modne-temp2*(ee6*modV*modne+pow(model,2.0)*modV*eee6))/pow(pow(model,2.0)*modV*modne,2.0);
			}
			
			/*derivees de ne[3] par rapport a x1,x2,y1,y2,z1,z2*/
	  	if ((model==0) || (modV==0) || (modne==0))
	  		{
	  		aaa1 = 0;	aaa2 = 0;	aaa3 = 0;	aaa4 = 0;	aaa5 = 0;	aaa6 = 0;
	  		}
	  	else
    			{
			aaa1 = -((wf[zi+2]-wf[zh+2])*g1*pow(model,2.0)*modV*modne-(wf[zi+2]-wf[zh+2])*prodsc*(ee1*modV*modne+pow(model,2.0)*modV*eee1))/pow(pow(model,2.0)*modV*modne,2.0);
			aaa2 = -((wf[zi+2]-wf[zh+2])*g2*pow(model,2.0)*modV*modne-(wf[zi+2]-wf[zh+2])*prodsc*(ee2*modV*modne+pow(model,2.0)*modV*eee2))/pow(pow(model,2.0)*modV*modne,2.0);
			aaa3 = -((wf[zi+2]-wf[zh+2])*g3*pow(model,2.0)*modV*modne-(wf[zi+2]-wf[zh+2])*prodsc*(ee3*modV*modne+pow(model,2.0)*modV*eee3))/pow(pow(model,2.0)*modV*modne,2.0);
			aaa4 = -((wf[zi+2]-wf[zh+2])*g4*pow(model,2.0)*modV*modne-(wf[zi+2]-wf[zh+2])*prodsc*(ee4*modV*modne+pow(model,2.0)*modV*eee4))/pow(pow(model,2.0)*modV*modne,2.0);
			aaa5 = -(-prodsc*pow(model,2.0)*modV*modne-(wf[zi+2]-wf[zh+2])*prodsc*(ee5*modV*modne+pow(model,2.0)*modV*eee5))/pow(pow(model,2.0)*modV*modne,2.0);
			aaa6 = -( prodsc*pow(model,2.0)*modV*modne-(wf[zi+2]-wf[zh+2])*prodsc*(ee6*modV*modne+pow(model,2.0)*modV*eee6))/pow(pow(model,2.0)*modV*modne,2.0);
			}

    			/*derivees de te[1] par rapport a x1,x2,y1,y2,z1,z2*/
	  	if (model==0)
	  		{
	  		b1 = 0;		b2 = 0;		b3 = 0;		b4 = 0;		b5 = 0;		b6 = 0;
	  		}
	  	else
    			{
			b1 = -sign*temp3/pow(model,3.0);
			b2 =  sign*temp3/pow(model,3.0);
			b3 =  sign*(wf[zi  ]-wf[zh  ])*(wf[zi+1]-wf[zh+1])/pow(model,3.0);
			b4 = -sign*(wf[zi  ]-wf[zh  ])*(wf[zi+1]-wf[zh+1])/pow(model,3.0);
			b5 =  sign*(wf[zi  ]-wf[zh  ])*(wf[zi+2]-wf[zh+2])/pow(model,3.0);
			b6 = -sign*(wf[zi  ]-wf[zh  ])*(wf[zi+2]-wf[zh+2])/pow(model,3.0);
			}
			
    			/*derivees de te[2] par rapport a x1,x2,y1,y2,z1,z2*/
	  	if (model==0)
	  		{
	  		bb1 = 0;	bb2 = 0;	bb3 = 0;	bb4 = 0;	bb5 = 0;	bb6 = 0;
	  		}
	  	else
    			{
			bb1 =  sign*(wf[zi  ]-wf[zh  ])*(wf[zi+1]-wf[zh+1])/pow(model,3.0);
			bb2 = -sign*(wf[zi  ]-wf[zh  ])*(wf[zi+1]-wf[zh+1])/pow(model,3.0);
			bb3 = -sign*temp4/pow(model,3.0);
			bb4 =  sign*temp4/pow(model,3.0);
			bb5 =  sign*(wf[zi+1]-wf[zh+1])*(wf[zi+2]-wf[zh+2])/pow(model,3.0);
			bb6 = -sign*(wf[zi+1]-wf[zh+1])*(wf[zi+2]-wf[zh+2])/pow(model,3.0);
			}
			
			/*derivees de te[3] par rapport a x1,x2,y1,y2,z1,z2*/
	  	if (model==0)
	  		{
	  		bbb1 = 0;	bbb2 = 0;	bbb3 = 0;	bbb4 = 0;	bbb5 = 0;	bbb6 = 0;
	  		}
	  	else
    			{
			bbb1 =  sign*(wf[zi  ]-wf[zh  ])*(wf[zi+2]-wf[zh+2])/pow(model,3.0);
			bbb2 = -sign*(wf[zi  ]-wf[zh  ])*(wf[zi+2]-wf[zh+2])/pow(model,3.0);
			bbb3 =  sign*(wf[zi+1]-wf[zh+1])*(wf[zi+2]-wf[zh+2])/pow(model,3.0);
			bbb4 = -sign*(wf[zi+1]-wf[zh+1])*(wf[zi+2]-wf[zh+2])/pow(model,3.0);
			bbb5 = -sign*temp5/pow(model,3.0);
			bbb6 =  sign*temp5/pow(model,3.0);
     			}
     		
    		if ((wf[zi+2] > 0.0) && (wf[zh+2] <= 0.0))
    			{    
    			/*element flottant ascendant*********************************************************************/
 			/*modif du /05/2001*/
 			
			N1[1] = 0.5*n*ne[1]*(wf[zh+2]*wf[zh+2]-2*wf[zi+2]*wf[zh+2])/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			N1[2] = 0.5*n*ne[2]*(wf[zh+2]*wf[zh+2]-2*wf[zi+2]*wf[zh+2])/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			N1[3] = 0.5*n*ne[3]*(wf[zh+2]*wf[zh+2]-2*wf[zi+2]*wf[zh+2])/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			N1[4] = 0.5*n*ne[1]*(wf[zh+2]*wf[zh+2]                    )/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			N1[5] = 0.5*n*ne[2]*(wf[zh+2]*wf[zh+2]                    )/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			N1[6] = 0.5*n*ne[3]*(wf[zh+2]*wf[zh+2]                    )/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
 				
			T1[1] = 0.5*t*te[1]*(wf[zh+2]*wf[zh+2]-2*wf[zi+2]*wf[zh+2])/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			T1[2] = 0.5*t*te[2]*(wf[zh+2]*wf[zh+2]-2*wf[zi+2]*wf[zh+2])/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			T1[3] = 0.5*t*te[3]*(wf[zh+2]*wf[zh+2]-2*wf[zi+2]*wf[zh+2])/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			T1[4] = 0.5*t*te[1]*(wf[zh+2]*wf[zh+2] 		          )/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			T1[5] = 0.5*t*te[2]*(wf[zh+2]*wf[zh+2] 		          )/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
			T1[6] = 0.5*t*te[3]*(wf[zh+2]*wf[zh+2] 		          )/((wf[zi+2]-wf[zh+2])*(wf[zi+2]-wf[zh+2]));
    				    			
    			/*CALCULS DES DERIVEES*/
 
    			/*derivees des expressions donnant la repartition aux deux extremites par rapport a z1,z2*/
			/*extremite 1*/
			c1 = -2*pow(wf[zi+2],2.0)/pow(wf[zi+2]-wf[zh+2],3.0);
			c2 =  2*wf[zi+2]*wf[zh+2]/pow(wf[zi+2]-wf[zh+2],3.0);
			/*extremite 2*/
			c3 =  2*wf[zi+2]*wf[zh+2]/pow(wf[zi+2]-wf[zh+2],3.0);
			c4 = -2*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],3.0);

			/*extremite 1*/

			DNT1x1 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d1*ne[1]+n*a1+dd1*te[1]+t*b1);
			DNT2x1 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d1*ne[2]+n*aa1+dd1*te[2]+t*bb1);
			DNT3x1 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d1*ne[3]+n*aaa1+dd1*te[3]+t*bbb1);

			DNT1x2 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d2*ne[1]+n*a2+dd2*te[1]+t*b2);
			DNT2x2 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d2*ne[2]+n*aa2+dd2*te[2]+t*bb2);
			DNT3x2 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d2*ne[3]+n*aaa2+dd2*te[3]+t*bbb2);

			DNT1y1 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d3*ne[1]+n*a3+dd3*te[1]+t*b3);
			DNT2y1 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d3*ne[2]+n*aa3+dd3*te[2]+t*bb3);
			DNT3y1 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d3*ne[3]+n*aaa3+dd3*te[3]+t*bbb3);

			DNT1y2 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d4*ne[1]+n*a4+dd4*te[1]+t*b4);
			DNT2y2 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d4*ne[2]+n*aa4+dd4*te[2]+t*bb4);
			DNT3y2 = 0.5*(pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d4*ne[3]+n*aaa4+dd4*te[3]+t*bbb4);

			DNT1z1 = 0.5*((pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d5*ne[1]+n*a5+dd5*te[1]+t*b5)+c1*(n*ne[1]+t*te[1]));
			DNT2z1 = 0.5*((pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d5*ne[2]+n*aa5+dd5*te[2]+t*bb5)+c1*(n*ne[2]+t*te[2]));
			DNT3z1 = 0.5*((pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d5*ne[3]+n*aaa5+dd5*te[3]+t*bbb5)+c1*(n*ne[3]+t*te[3]));

			DNT1z2 = 0.5*((pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d6*ne[1]+n*a6+dd6*te[1]+t*b6)+c2*(n*ne[1]+t*te[1]));
			DNT2z2 = 0.5*((pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d6*ne[2]+n*aa6+dd6*te[2]+t*bb6)+c2*(n*ne[2]+t*te[2]));
			DNT3z2 = 0.5*((pow(wf[zh+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zi+2]-wf[zh+2],2.0)*(d6*ne[3]+n*aaa6+dd6*te[3]+t*bbb6)+c2*(n*ne[3]+t*te[3]));
			
			/*extremite 2*/

			DNT4x1 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d1*ne[1]+n*a1+dd1*te[1]+t*b1);
			DNT5x1 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d1*ne[2]+n*aa1+dd1*te[2]+t*bb1);
			DNT6x1 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d1*ne[3]+n*aaa1+dd1*te[3]+t*bbb1);

			DNT4x2 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d2*ne[1]+n*a2+dd2*te[1]+t*b2);
			DNT5x2 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d2*ne[2]+n*aa2+dd2*te[2]+t*bb2);
			DNT6x2 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d2*ne[3]+n*aaa2+dd2*te[3]+t*bbb2);

			DNT4y1 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d3*ne[1]+n*a3+dd3*te[1]+t*b3);
			DNT5y1 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d3*ne[2]+n*aa3+dd3*te[2]+t*bb3);
			DNT6y1 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d3*ne[3]+n*aaa3+dd3*te[3]+t*bbb3);

			DNT4y2 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d4*ne[1]+n*a4+dd4*te[1]+t*b4);
			DNT5y2 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d4*ne[2]+n*aa4+dd4*te[2]+t*bb4);
			DNT6y2 = 0.5*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d4*ne[3]+n*aaa4+dd4*te[3]+t*bbb4);

			DNT4z1 = 0.5*(pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d5*ne[1]+n*a5+dd5*te[1]+t*b5)+c3*(n*ne[1]+t*te[1]));
			DNT5z1 = 0.5*(pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d5*ne[2]+n*aa5+dd5*te[2]+t*bb5)+c3*(n*ne[2]+t*te[2]));
			DNT6z1 = 0.5*(pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d5*ne[3]+n*aaa5+dd5*te[3]+t*bbb5)+c3*(n*ne[3]+t*te[3]));
			
			DNT4z2 = 0.5*(pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d6*ne[1]+n*a6+dd6*te[1]+t*b6)+c4*(n*ne[1]+t*te[1]));
			DNT5z2 = 0.5*(pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d6*ne[2]+n*aa6+dd6*te[2]+t*bb6)+c4*(n*ne[2]+t*te[2]));
			DNT6z2 = 0.5*(pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],2.0)*(d6*ne[3]+n*aaa6+dd6*te[3]+t*bbb6)+c4*(n*ne[3]+t*te[3]));
   			
   			/* REMPLISSAGE DE LA MATRICE wg */
    			
    			wg[1][1] = -DNT1x1;	wg[2][1] = -DNT2x1;	wg[3][1] = -DNT3x1;	wg[4][1] = -DNT4x1;	wg[5][1] = -DNT5x1;	wg[6][1] = -DNT6x1;
			wg[1][2] = -DNT1y1;	wg[2][2] = -DNT2y1;	wg[3][2] = -DNT3y1;	wg[4][2] = -DNT4y1;	wg[5][2] = -DNT5y1;	wg[6][2] = -DNT6y1;
    			wg[1][3] = -DNT1z1;	wg[2][3] = -DNT2z1;	wg[3][3] = -DNT3z1;	wg[4][3] = -DNT4z1;	wg[5][3] = -DNT5z1;	wg[6][3] = -DNT6z1;
		  	wg[1][4] = -DNT1x2;	wg[2][4] = -DNT2x2;	wg[3][4] = -DNT3x2;	wg[4][4] = -DNT4x2;	wg[5][4] = -DNT5x2;	wg[6][4] = -DNT6x2;
    			wg[1][5] = -DNT1y2;	wg[2][5] = -DNT2y2;	wg[3][5] = -DNT3y2;	wg[4][5] = -DNT4y2;	wg[5][5] = -DNT5y2;	wg[6][5] = -DNT6y2;	
			wg[1][6] = -DNT1z2;	wg[2][6] = -DNT2z2;	wg[3][6] = -DNT3z2;	wg[4][6] = -DNT4z2;	wg[5][6] = -DNT5z2;	wg[6][6] = -DNT6z2;
    			}
    			
    		if ((wf[zh+2] > 0.0) && (wf[zi+2] <= 0.0))
    			{
      			/*element flottant descendant****************************************************************************/
  			/*modif du /05/2001*/
        		N1[1] = 0.5*n*ne[1]*(wf[zi+2]*wf[zi+2]                    )/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
       			N1[2] = 0.5*n*ne[2]*(wf[zi+2]*wf[zi+2]                    )/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 			N1[3] = 0.5*n*ne[3]*(wf[zi+2]*wf[zi+2]                    )/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 			N1[4] = 0.5*n*ne[1]*(wf[zi+2]*wf[zi+2]-2*wf[zh+2]*wf[zi+2])/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 			N1[5] = 0.5*n*ne[2]*(wf[zi+2]*wf[zi+2]-2*wf[zh+2]*wf[zi+2])/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 			N1[6] = 0.5*n*ne[3]*(wf[zi+2]*wf[zi+2]-2*wf[zh+2]*wf[zi+2])/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 				
 			T1[1] = 0.5*t*te[1]*(wf[zi+2]*wf[zi+2] 		          )/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 			T1[2] = 0.5*t*te[2]*(wf[zi+2]*wf[zi+2] 		          )/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 			T1[3] = 0.5*t*te[3]*(wf[zi+2]*wf[zi+2] 		          )/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 			T1[4] = 0.5*t*te[1]*(wf[zi+2]*wf[zi+2]-2*wf[zh+2]*wf[zi+2])/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 			T1[5] = 0.5*t*te[2]*(wf[zi+2]*wf[zi+2]-2*wf[zh+2]*wf[zi+2])/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 			T1[6] = 0.5*t*te[3]*(wf[zi+2]*wf[zi+2]-2*wf[zh+2]*wf[zi+2])/((wf[zh+2]-wf[zi+2])*(wf[zh+2]-wf[zi+2]));
 				
			/*if ((zg == 2))
				{
				printf("descendant zg %d  \n",zg);
				printf("N1 ");imprvectreel(6, N1);     			
				printf("T1 ");imprvectreel(6, T1);     			
				}*/

    			/*CALCUL DES DERIVEES */
 
    			/*derivees des expressions donnant la repartition aux deux extremites par rapport a z1,z2*/
			/*extremite 2*/
			cc1 = -2*wf[zi+2]*wf[zh+2]/pow(wf[zi+2]-wf[zh+2],3.0);
			cc2 =  2*pow(wf[zh+2],2.0)/pow(wf[zi+2]-wf[zh+2],3.0);
			/*extremite 1*/
			cc3 =  2*pow(wf[zi+2],2.0)/pow(wf[zi+2]-wf[zh+2],3.0);
			cc4 = -2*wf[zi+2]*wf[zh+2]/pow(wf[zi+2]-wf[zh+2],3.0);
			
			/*extremite 1*/
			DNT1x1 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d1*ne[1]+n*a1+dd1*te[1]+t*b1);
			DNT2x1 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d1*ne[2]+n*aa1+dd1*te[2]+t*bb1);
			DNT3x1 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d1*ne[3]+n*aaa1+dd1*te[3]+t*bbb1);

			DNT1x2 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d2*ne[1]+n*a2+dd2*te[1]+t*b2);
			DNT2x2 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d2*ne[2]+n*aa2+dd2*te[2]+t*bb2);
			DNT3x2 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d2*ne[3]+n*aaa2+dd2*te[3]+t*bbb2);

			DNT1y1 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d3*ne[1]+n*a3+dd3*te[1]+t*b3);
			DNT2y1 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d3*ne[2]+n*aa3+dd3*te[2]+t*bb3);
			DNT3y1 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d3*ne[3]+n*aaa3+dd3*te[3]+t*bbb3);

			DNT1y2 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d4*ne[1]+n*a4+dd4*te[1]+t*b4);
			DNT2y2 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d4*ne[2]+n*aa4+dd4*te[2]+t*bb4);
			DNT3y2 = 0.5*pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d4*ne[3]+n*aaa4+dd4*te[3]+t*bbb4);

			DNT1z1 = 0.5*(pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d5*ne[1]+n*a5+dd5*te[1]+t*b5)+cc3*(n*ne[1]+t*te[1]));
			DNT2z1 = 0.5*(pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d5*ne[2]+n*aa5+dd5*te[2]+t*bb5)+cc3*(n*ne[2]+t*te[2]));
			DNT3z1 = 0.5*(pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d5*ne[3]+n*aaa5+dd5*te[3]+t*bbb5)+cc3*(n*ne[3]+t*te[3]));

			DNT1z2 = 0.5*(pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d6*ne[1]+n*a6+dd6*te[1]+t*b6)+cc4*(n*ne[1]+t*te[1]));
			DNT2z2 = 0.5*(pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d6*ne[2]+n*aa6+dd6*te[2]+t*bb6)+cc4*(n*ne[2]+t*te[2]));
			DNT3z2 = 0.5*(pow(wf[zi+2],2.0)/pow(wf[zh+2]-wf[zi+2],2.0)*(d6*ne[3]+n*aaa6+dd6*te[3]+t*bbb6)+cc4*(n*ne[3]+t*te[3]));

			/*extremite 2*/

			DNT4x1 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d1*ne[1]+n*a1+dd1*te[1]+t*b1);
			DNT5x1 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d1*ne[2]+n*aa1+dd1*te[2]+t*bb1);
			DNT6x1 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d1*ne[3]+n*aaa1+dd1*te[3]+t*bbb1);

			DNT4x2 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d2*ne[1]+n*a2+dd2*te[1]+t*b2);
			DNT5x2 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d2*ne[2]+n*aa2+dd2*te[2]+t*bb2);
			DNT6x2 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d2*ne[3]+n*aaa2+dd2*te[3]+t*bbb2);

			DNT4y1 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d3*ne[1]+n*a3+dd3*te[1]+t*b3);
			DNT5y1 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d3*ne[2]+n*aa3+dd3*te[2]+t*bb3);
			DNT6y1 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d3*ne[3]+n*aaa3+dd3*te[3]+t*bbb3);

			DNT4y2 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d4*ne[1]+n*a4+dd4*te[1]+t*b4);
			DNT5y2 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d4*ne[2]+n*aa4+dd4*te[2]+t*bb4);
			DNT6y2 = 0.5*(pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d4*ne[3]+n*aaa4+dd4*te[3]+t*bbb4);

			DNT4z1 = 0.5*((pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d5*ne[1]+n*a5+dd5*te[1]+t*b5)+cc1*(n*ne[1]+t*te[1]));
			DNT5z1 = 0.5*((pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d5*ne[2]+n*aa5+dd5*te[2]+t*bb5)+cc1*(n*ne[2]+t*te[2]));
			DNT6z1 = 0.5*((pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d5*ne[3]+n*aaa5+dd5*te[3]+t*bbb5)+cc1*(n*ne[3]+t*te[3]));

			DNT4z2 = 0.5*((pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d6*ne[1]+n*a6+dd6*te[1]+t*b6)+cc2*(n*ne[1]+t*te[1]));
			DNT5z2 = 0.5*((pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d6*ne[2]+n*aa6+dd6*te[2]+t*bb6)+cc2*(n*ne[2]+t*te[2]));
			DNT6z2 = 0.5*((pow(wf[zi+2],2.0)-2*wf[zh+2]*wf[zi+2])/pow(wf[zh+2]-wf[zi+2],2.0)*(d6*ne[3]+n*aaa6+dd6*te[3]+t*bbb6)+cc2*(n*ne[3]+t*te[3]));

   			/* REMPLISSAGE DE LA MATRICE wg */
    			
    			wg[1][1] = -DNT1x1;	wg[2][1] = -DNT2x1;	wg[3][1] = -DNT3x1;	wg[4][1] = -DNT4x1;	wg[5][1] = -DNT5x1;	wg[6][1] = -DNT6x1;
			wg[1][2] = -DNT1y1;	wg[2][2] = -DNT2y1;	wg[3][2] = -DNT3y1;	wg[4][2] = -DNT4y1;	wg[5][2] = -DNT5y1;	wg[6][2] = -DNT6y1;	
			wg[1][3] = -DNT1z1;	wg[2][3] = -DNT2z1;	wg[3][3] = -DNT3z1;	wg[4][3] = -DNT4z1;	wg[5][3] = -DNT5z1;	wg[6][3] = -DNT6z1;
		  	wg[1][4] = -DNT1x2;	wg[2][4] = -DNT2x2;	wg[3][4] = -DNT3x2;	wg[4][4] = -DNT4x2;	wg[5][4] = -DNT5x2;	wg[6][4] = -DNT6x2;
    			wg[1][5] = -DNT1y2;	wg[2][5] = -DNT2y2;	wg[3][5] = -DNT3y2;	wg[4][5] = -DNT4y2;	wg[5][5] = -DNT5y2;	wg[6][5] = -DNT6y2;
    			wg[1][6] = -DNT1z2;	wg[2][6] = -DNT2z2;	wg[3][6] = -DNT3z2;	wg[4][6] = -DNT4z2;	wg[5][6] = -DNT5z2;	wg[6][6] = -DNT6z2;
   			}
    		NT[1] = N1[1] + T1[1]; 		NT[2] = N1[2] + T1[2]; 		NT[3] = N1[3] + T1[3];
    		NT[4] = N1[4] + T1[4]; 		NT[5] = N1[5] + T1[5]; 		NT[6] = N1[6] + T1[6];

     		}
	//printf("NT ");imprvectreel(6, NT);  
	//imprmatreel3( 1, 6, 1,  6,  wg, 7); 			
     	}
