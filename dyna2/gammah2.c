#include "4c19.h"

void gammah2()
	{
  	/*
  	calcule l acceleration des particules d'eau au milieu des flotteurs des noeuds :
  	mgh[3*zi-2] = acceleration selon l axe x
  	mgh[3*zi-1] = accelerations selon l axe y
  	mgh[3*zi-0] = acceleration verticale : selon l axe z
  	prise en compte de la profondeur Depth
  	attention mgh != 0 pour un noeud exondé
  	*/

  	int zi;
  	double kz,tetah,positionzplusd,prof;
  	double omega,aa,kk,depth,distance,zz;
  	
  	tetah = PI / 180.0 * Houle.direction;

	if (Structure.wave_model == 1)
		{
 		//Airy finite depth
		omega = Houle.omega;
		aa = Houle.hh1 / 2.0;
		kk = Houle.k;
		depth = Houle.depth;
		if(depth<0.5*G/2/PI*Houle.periode*Houle.periode) 
			{
			//intermediate depth
			//to be sure not overpassing limit of double
		  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
		  		{
		    		distance = mh[3*zi-2];
		    		zz = wf[3*zi-0];
				mgh[3*zi-2] = ((omega*omega*aa*sin(kk*distance-omega*times)*cosh(kk*(zz+depth)))/sinh(depth*kk)) * cos(tetah);
				mgh[3*zi-1] = ((omega*omega*aa*sin(kk*distance-omega*times)*cosh(kk*(zz+depth)))/sinh(depth*kk)) * sin(tetah);
				mgh[3*zi-0] = -(omega*omega*aa*cos(kk*distance-omega*times)*sinh(kk*(zz+depth)))/sinh(depth*kk);
		  		}
	  		}
	  	else
	  		{
		  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
		  		{
		    		distance = mh[3*zi-2];
		    		zz = wf[3*zi-0];
				mgh[3*zi-2] = omega*omega*aa*sin(kk*distance-omega*times)*exp(kk*zz) * cos(tetah);
				mgh[3*zi-1] = omega*omega*aa*sin(kk*distance-omega*times)*exp(kk*zz) * sin(tetah);
				mgh[3*zi-0] =-omega*omega*aa*cos(kk*distance-omega*times)*exp(kk*zz);
		  		}
		  	}
  		}
	if (Structure.wave_model == 2)
		{
		//Stokes 2d order finite depth
		omega = Houle.omega;
		aa = Houle.hh1 / 2.0;
		kk = Houle.k;
		depth = Houle.depth;
		if(depth<0.5*G/2/PI*Houle.periode*Houle.periode) 
			{
			//intermediate depth
			//to be sure not overpassing limit of double
		  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
		  		{
		    		distance = mh[3*zi-2];
		    		zz = wf[3*zi-0];
				mgh[3*zi-2] = ((omega*aa*( (3.0*omega*aa*kk*kk*sin(2.0*(kk*distance-omega*times))*cosh(2.0*kk*(zz+depth)))/(2.0*pow(sinh(depth*kk),3.0))+omega*kk*sin(kk*distance-omega*times)*cosh(kk*(zz+depth))))/(kk*sinh(depth*kk))) * cos(tetah);
				mgh[3*zi-1] = ((omega*aa*( (3.0*omega*aa*kk*kk*sin(2.0*(kk*distance-omega*times))*cosh(2.0*kk*(zz+depth)))/(2.0*pow(sinh(depth*kk),3.0))+omega*kk*sin(kk*distance-omega*times)*cosh(kk*(zz+depth))))/(kk*sinh(depth*kk))) * sin(tetah);
				mgh[3*zi-0] =  (omega*aa*(-(3.0*omega*aa*kk*kk*cos(2.0*(kk*distance-omega*times))*sinh(2.0*kk*(zz+depth)))/(2.0*pow(sinh(depth*kk),3.0))-omega*kk*cos(kk*distance-omega*times)*sinh(kk*(zz+depth))))/(kk*sinh(depth*kk));
		  		}
	  		}
	  	else
	  		{
		  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
		  		{
		    		distance = mh[3*zi-2];
		    		zz = wf[3*zi-0];
				mgh[3*zi-2] = omega*omega*aa*sin(kk*distance-omega*times)*exp(kk*zz) * cos(tetah);
				mgh[3*zi-1] = omega*omega*aa*sin(kk*distance-omega*times)*exp(kk*zz) * sin(tetah);
				mgh[3*zi-0] =-omega*omega*aa*cos(kk*distance-omega*times)*exp(kk*zz);
		  		}
		  	}
  		}
	if (Structure.wave_model == 3)
		{
		//Stokes 3d order infinite depth
		omega = Houle.omega;
		aa = Houle.hh1 / 2.0;
		kk = Houle.k;
		depth = Houle.depth;
	  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
	  		{
	    		distance = mh[3*zi-2];
	    		zz = wf[3*zi-0];
			mgh[3*zi-2] = (omega*aa*sqrt(G/kk)*kk*sin(kk*distance-omega*times)*exp(kk*zz)) * cos(tetah);
			mgh[3*zi-1] = (omega*aa*sqrt(G/kk)*kk*sin(kk*distance-omega*times)*exp(kk*zz)) * sin(tetah);
			mgh[3*zi-0] = -omega*aa*sqrt(G/kk)*kk*cos(kk*distance-omega*times)*exp(kk*zz);
	  		}
  		}
	}
