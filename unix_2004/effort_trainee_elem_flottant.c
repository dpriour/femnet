#define PRINCIPAL 0
#include "4c19.h"
//#define DEBUG

void effort_trainee_elem_flottant(int zg,int zh,int zi,double *V, double *nt, double mhh)	
	{
	/*
	cette procedure prend en entree le numero d'un element zg, le numero selon x des deux 
	extremites de cet element zh,zi et le vecteur courant V (V[1] V[2] et V[3]). 
	Elle prend en compte une pondération lorsque que l'extremité 1 est proche de la surface libre.
	Elle retourne un vecteur ,note NT ,a 3 composantes contenant la somme des efforts normaux N1 et
	tangentiels T1 suivant x,y,z à l'extremite 1 de l'element.
	Ainsi NT[i]= N1[i]+T1[i].
	Cette procedure ne retourne pas la matrice wg contenant 36 termes. C'est la matrice de
	raideur de l'element 
	wg[1][3] = derivee de NT[1] par rapport a z1
	wg[1][6] = derivee de NT[1] par rapport a z2
	pour l instant wg = 0
	mhh est la hauteur de la surface libre à la position de l'extremite 1, en statique mhh = 0.0
	*/
			
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double ttx,tty,ttz,eex,eey,eez,lle,eeex,eeey,eeez,ddx,ddy,ddz;
	double Cx,Cy,Cz,len,tx1,ty1,tz1,fx1,fy1,fz1,Pond,sinat2,cosat2,cosat;
	double att2,att,Atx,Aty,Atz,xx1,yy1,zz1,coefT,coefN;
	double x1,y1,z1,x2,y2,z2,lbt,ct;
	int zj,zk;
	x1 = wf[zh  ];	y1 = wf[zh+1];	z1 = wf[zh+2];
	x2 = wf[zi  ];	y2 = wf[zi+1];	z2 = wf[zi+2];
	#ifdef DEBUG
	printf("zg %d   //////////////////////////////////////////\n",zg);
	printf("xzi=%lf;  yzi=%lf;  zzi=%lf; ",x1,y1,z1);
	printf("xzj=%lf;  yzj=%lf;  zzj=%lf; \n",x2,y2,z2);
	#endif
	
	Cx = V[1];	Cy = V[2];	Cz = V[3];

	lbt=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1));					//bar length (m)
	len = pow((Element[zg].lgrepos*PI*pow(Element[zg].diametrehydro,2)/8.0),(1.0/3.0));		//size of the cubique volume per node
	ct=sqrt(Cz*Cz+Cy*Cy+Cx*Cx);					    				//speed amplitude (m/s)
	coefN=0.5*RHO*Element[zg].cdnormal*Element[zg].lgrepos*Element[zg].diametrehydro*ct*ct;		//constant coef of normal   drag
	coefT=Element[zg].ftangent*coefN;								//constant coef of tangent  drag
	
	#ifdef DEBUG
	printf("l0=%lf;  diam=%lf;  \n",Element[zg].lgrepos,Element[zg].diametrehydro);
	printf("len=%lf;  ct=%lf;  \n",len,ct);
	printf("coefN=%lf;  coefT=%lf;  \n",coefN,coefT);
	#endif

	xx1=x2-x1;							//x component of the bar
	yy1=y2-y1;							//y component of the bar
	zz1=z2-z1;							//z component of the bar

	Atx=Cy*zz1-Cz*yy1;						//x component of vectorial product of speed by bar
	Aty=Cz*xx1-Cx*zz1;						//y component of vectorial product of speed by bar
	Atz=Cx*yy1-Cy*xx1;						//z component of vectorial product of speed by bar
	att=sqrt(Atz*Atz+Aty*Aty+Atx*Atx);				//amplitude of vectorial product of speed by bar
	if (att==0)
	{
	  	if(abs(xx1)<=abs(yy1) && abs(xx1)<=abs(zz1))
	  	{  
	  		Atx=0*zz1-0*yy1;				//x component of vectorial product of speed by bar
	    		Aty=0*xx1-1*zz1;				//y component of vectorial product of speed by bar
	    		Atz=1*yy1-0*xx1;				//z component of vectorial product of speed by bar
	  	}
	  	if(abs(yy1)<=abs(zz1) && abs(yy1)<=abs(xx1))
	  	{
	    		Atx=1*zz1-0*yy1;				//x component of vectorial product of speed by bar
	    		Aty=0*xx1-0*zz1;				//y component of vectorial product of speed by bar
	    		Atz=0*yy1-1*xx1;				//z component of vectorial product of speed by bar
	  	}  
	  	if(abs(zz1)<=abs(xx1) && abs(zz1)<=abs(yy1))
	    	{
	    		Atx=0*zz1-1*yy1;				//x component of vectorial product of speed by bar
	    		Aty=1*xx1-0*zz1;				//y component of vectorial product of speed by bar
	    		Atz=0*yy1-0*xx1;				//z component of vectorial product of speed by bar
	  	}
	  	att=sqrt(Atz*Atz+Aty*Aty+Atx*Atx);			//amplitude of vectorial product of speed by bar
	}
	#ifdef DEBUG
	printf("Atx=%lf  %lf %lf \n",Atx,Aty,Atz);
	#endif

	att2=att*att;
	cosat=(Cz*zz1)/(ct*lbt)+(Cy*yy1)/(ct*lbt)+(Cx*xx1)/(ct*lbt);	//cos of the angle between speed and bar
	cosat2=cosat*cosat;
	sinat2=1-cosat2;						//sin² of the angle between speed and bar
	#ifdef DEBUG
	printf("cosat2=%lf;  sinat2=%lf;  \n",cosat2,sinat2);
	printf("att=%lf;  lbt=%lf;  \n",att,lbt);
	#endif

	if(z1-len/2.0>mhh)
	{		
	  	Pond = 0.0;							//Pond : ponderation of drag force on extremity 1 of the bar if this extremity is close to the free surface
		#ifdef DEBUG
		printf("1len=%lf;  Pond=%lf;  mhh=%lf;  z1=%lf;  \n",len,Pond,mhh,z1);
		#endif
	}
	if((z1-len/2.0<=mhh) && (z1+len/2.0>=mhh))
	{	
	  	Pond=(mhh-z1+len/2.0)/len;
		#ifdef DEBUG
		printf("2len=%lf;  Pond=%lf;  mhh=%lf;  z1=%lf;  \n",len,Pond,mhh,z1);
		#endif
	}
	if(z1+len/2.0<mhh)
	{		
	  	Pond = 1.0;
		#ifdef DEBUG
		printf("3len=%lf;  Pond=%lf;  mhh=%lf;  z1=%lf;  \n",len,Pond,mhh,z1);
		#endif
	}

	fx1=(Pond*coefN*sinat2*(Atz*yy1-Aty*zz1))/(att*lbt);
	fy1=(Pond*coefN*sinat2*(Atx*zz1-Atz*xx1))/(att*lbt);
	fz1=(Pond*coefN*sinat2*(Aty*xx1-Atx*yy1))/(att*lbt);
	#ifdef DEBUG
	printf("f=%lf  %lf %lf \n",fx1,fy1,fz1);
	#endif
		                                   
	if (cosat != 0.0)
	{
		ttx = xx1 * cosat / fabs (lbt * cosat);		//tangent drag direction along bar direction by cos alpha sign
		tty = yy1 * cosat / fabs (lbt * cosat);
		ttz = zz1 * cosat / fabs (lbt * cosat);
	}
	else
	{
		ttx = xx1 / lbt;
		tty = yy1 / lbt;
		ttz = zz1 / lbt;
	}
	#ifdef DEBUG
	printf("ttx=%lf tty %lf ttz%lf \n",ttx,tty,ttz);
	#endif

	tx1=Pond*coefT*cosat2*ttx;
	ty1=Pond*coefT*cosat2*tty;
	tz1=Pond*coefT*cosat2*ttz;
	nt[1] = fx1+tx1;
	nt[2] = fy1+ty1;
	nt[3] = fz1+tz1;
	#ifdef DEBUG
	printf("nt=%   ");
	imprvectreel(3, nt);
	#endif
	for (zk = 1 ; zk<= 3 ; zk++) {if(isnan(nt[zk]))	{printf("effort_trainee_elem_flottant zg %d \n",zg);	exit(0);}}
	for (zk = 1;zk <= 6;zk++)
		{
		for (zj = 1;zj <= 6;zj++)
	 		{
	 		wg[zk][zj]=0.0;		//for now the stiffness matrix is null
	 		}
	 	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////
}
