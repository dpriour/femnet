#define PRINCIPAL 0
#include "4c19.h"
//#define DEBUG

void basic_bar_drag1(double diam, double lgrepos, double cdnormal, double ftangent, double *ba, double *Vw, double *nt)	
	{
	/*
	cette procedure calcul le vecteur trainée (drag + lift) sur un cylindre de diametre diam, longeur au repos de lgt0
	coefficient de trainee normale cdnormal, coefficient de trainee tangentielle ftangent
	la basse est selon le vecteur ba. la vitesse de l'eau relativement à la barre est Vw
	le vecteur trainée est nt
	*/

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double ttx,tty,ttz;
	double Cx,Cy,Cz,tx1,ty1,tz1,fx1,fy1,fz1,sinat2,cosat2,cosat;
	double att2,att,Atx,Aty,Atz,xx1,yy1,zz1,coefT,coefN;
	double lbt,ct;
	int zj,zk;
	
	#ifdef DEBUG
	printf("ba=\n");
	imprvectreel1(3, 3, ba);
	printf("Vw=\n");
	imprvectreel1(3, 3, Vw);
	#endif
	
	Cx = Vw[1];	Cy = Vw[2];	Cz = Vw[3];

	lbt = sqrt(produit_scal(ba,ba));			//bar length (m)
	ct= sqrt(produit_scal(Vw,Vw));				//speed amplitude (m/s)
	coefN=0.5*RHO*cdnormal*lgrepos*diam*ct*ct;		//constant coef of normal   drag
	coefT=ftangent*coefN;			//constant coef of tangent  drag
	
	#ifdef DEBUG
	printf("l0=%lf;  diam=%lf;  \n",lgrepos,diam);
	printf("l_stretched=%lf;  \n",lbt);
	printf("coefN=%lf;  coefT=%lf;  \n",coefN,coefT);
	#endif

	xx1=ba[1];							//x component of the bar
	yy1=ba[2];							//y component of the bar
	zz1=ba[3];							//z component of the bar

	Atx=Cy*zz1-Cz*yy1;						//x component of vectorial product of speed by bar
	Aty=Cz*xx1-Cx*zz1;						//y component of vectorial product of speed by bar
	Atz=Cx*yy1-Cy*xx1;						//z component of vectorial product of speed by bar
	att=sqrt(Atz*Atz+Aty*Aty+Atx*Atx);				//amplitude of vectorial product of speed by bar
	if (att==0)
	{
	  	if((fabs(xx1)<=fabs(yy1)) && (fabs(xx1)<=fabs(zz1)))
	  	{  
	  		Atx=0*zz1-0*yy1;				//x component of vectorial product of speed by bar
	    		Aty=0*xx1-1*zz1;				//y component of vectorial product of speed by bar
	    		Atz=1*yy1-0*xx1;				//z component of vectorial product of speed by bar
			#ifdef DEBUG
			printf("case 1 xx %lf %lf %lf \n",xx1,yy1,zz1);
			#endif
	  	}
	  	if((fabs(yy1)<=fabs(zz1)) && (fabs(yy1)<=fabs(xx1)))
	  	{
	    		Atx=1*zz1-0*yy1;				//x component of vectorial product of speed by bar
	    		Aty=0*xx1-0*zz1;				//y component of vectorial product of speed by bar
	    		Atz=0*yy1-1*xx1;				//z component of vectorial product of speed by bar
			#ifdef DEBUG
			printf("case 2 xx %lf %lf %lf \n",xx1,yy1,zz1);
			#endif
	  	}  
	  	if((fabs(zz1)<=fabs(xx1)) && (fabs(zz1)<=fabs(yy1)))
	    	{
	    		Atx=0*zz1-1*yy1;				//x component of vectorial product of speed by bar
	    		Aty=1*xx1-0*zz1;				//y component of vectorial product of speed by bar
	    		Atz=0*yy1-0*xx1;				//z component of vectorial product of speed by bar
			#ifdef DEBUG
			printf("case 3 xx %lf %lf %lf \n",xx1,yy1,zz1);
			#endif
	  	}
	  	att=sqrt(Atz*Atz+Aty*Aty+Atx*Atx);			//amplitude of vectorial product of speed by bar
	}
	if (att==0)
	{
    		//Atx=1.0;				//x component of vectorial product of speed by bar
    		//Aty=0.0;				//y component of vectorial product of speed by bar
    		//Atz=0.0;				//z component of vectorial product of speed by bar
	  	//att=sqrt(Atz*Atz+Aty*Aty+Atx*Atx);			//amplitude of vectorial product of speed by bar
	}
	#ifdef DEBUG
	printf("Atx=%lf  %lf %lf \n",Atx,Aty,Atz);
	#endif

	att2=att*att;
	if (ct>0.0)
		{
		cosat=(Cz*zz1)/(ct*lbt)+(Cy*yy1)/(ct*lbt)+(Cx*xx1)/(ct*lbt);	//cos of the angle between speed and bar
		}
	else
		{
		cosat=0.0;	//cos of the angle between speed and bar
		}
	if(isnan(cosat))	cosat=0.0;
	cosat2=cosat*cosat;
	sinat2=1-cosat2;						//sin² of the angle between speed and bar
	#ifdef DEBUG
	printf("cosat2=%lf;  sinat2=%lf;  \n",cosat2,sinat2);
	printf("att=%lf;  lbt=%lf;  \n",att,lbt);
	#endif

	fx1=(coefN*sinat2*(Atz*yy1-Aty*zz1))/(att*lbt);
	fy1=(coefN*sinat2*(Atx*zz1-Atz*xx1))/(att*lbt);
	fz1=(coefN*sinat2*(Aty*xx1-Atx*yy1))/(att*lbt);
	if(isnan(fx1))	fx1=0.0;
	if(isnan(fy1))	fy1=0.0;
	if(isnan(fz1))	fz1=0.0;
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
	if(isnan(ttx))	ttx=0.0;
	if(isnan(tty))	tty=0.0;
	if(isnan(ttz))	ttz=0.0;
	#ifdef DEBUG
	printf("ttx=%lf tty %lf ttz%lf \n",ttx,tty,ttz);
	#endif

	tx1=coefT*cosat2*ttx;
	ty1=coefT*cosat2*tty;
	tz1=coefT*cosat2*ttz;
	nt[1] = fx1+tx1;
	nt[2] = fy1+ty1;
	nt[3] = fz1+tz1;
	#ifdef DEBUG
	printf("nt=\n");
	imprvectreel1(3, 3, nt);
	#endif
	for (zk = 1 ; zk<= 3 ; zk++) 
		{
		if(isnan(nt[zk]))	
			{
			printf("effort_trainee_elem_flottant \n");
			printf("diam %lf \n",diam);
			printf("lgrepos %lf \n",lgrepos);
			printf("cdnormal %lf \n",cdnormal);
			printf("ftangent %lf \n",ftangent);
			printf("ba\n");
			imprvectreel1(3, 3, ba);
			printf("\n");
			printf("Vw\n");
			imprvectreel1(3, 3, Vw);
			printf("\n");
			exit(0);
			}
		}
	}
