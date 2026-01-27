#include "4c19.h"

void surface3()
	{
	int zi;
	double kk,omega,depth,eta2,aa,wave_vector[4],OP[4];
	
	/*
	calcul de la hauteur de la houle Houle.hh1, Houle.hh1 est la hauteur de la houle :
	croissant de 0 a Houle.hauteur pour times de 0 a Houle.periode, ensuite Houle.hh1 = Houle.hauteur.
	zi numero du noeud
	calcul de la hauteur de la surface libre a chaque noeud       : mh[3*zi-0]
    	calcul de l immersion des noeuds : >0 si flotteur, <0 si lest : mh[3*zi-1]
	calcul de la distance noeud a l'origine de la houle 	       : mh[3*zi-2]
	*/


	//Airy finite depth
	//printf("lambda %lf \n",Houle.lambda);
	//exit(0);
	
	/*rampe from times=0 to times=period*/
	if (times < Houle.periode)  
		{
		Houle.hh1 = Houle.hauteur * times/Houle.periode; 
		//Houle.hh1 = Houle.hauteur;
		}
	else 
		Houle.hh1 = Houle.hauteur;
	
	aa = Houle.hh1/2;
	kk = Houle.k;
	omega = Houle.omega;
	depth = Houle.depth;
	wave_vector[1] = cos(PI / 180.0 * Houle.direction);
	wave_vector[2] = 0.0;
	wave_vector[3] = sin(PI / 180.0 * Houle.direction);
		
	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
		{ 
		OP[1] = wf[3*zi-2];
		OP[2] = 0.0;
		OP[3] = wf[3*zi-1];
		mh[3*zi-2] =  produit_scal(wave_vector, OP);

	if (Structure.wave_model == 1)
		{
		//Airy finite depth
		//////////////////////////////////////////////////////////////////////////////////////////////
		//mh[3*zi-0] =   Houle.hh1/2  * sin(2.0*PI*(times/Houle.periode - mh[3*zi-2]/Houle.lambda));
		mh[3*zi-0] = Houle.hh1/2*cos(kk*mh[3*zi-2]-omega*times);
		//////////////////////////////////////////////////////////////////////////////////////////////
		}
	if (Structure.wave_model == 2)
		{
		//Stokes 2d order finite depth
		//////////////////////////////////////////////////////////////////////////////////////////////
		mh[3*zi-0] = Houle.hh1/2*((Houle.hh1/2*kk*(3-pow(tanh(depth*kk),2.0))*cos(2*(kk*mh[3*zi-2]-omega*times)))/(4*pow(tanh(depth*kk),3))+cos(kk*mh[3*zi-2]-omega*times));
		//////////////////////////////////////////////////////////////////////////////////////////////
		}
	if (Structure.wave_model == 3)
		{
		//Stokes 3d order infinite depth
		//////////////////////////////////
		mh[3*zi-0] = aa*((3.0*aa*aa*kk*kk*cos(3.0*(kk*mh[3*zi-2]-omega*times)))/8.0+(aa*kk*cos(2.0*(kk*mh[3*zi-2]-omega*times)))/2.0+(1.0-(aa*aa*kk*kk)/16.0)*cos(kk*mh[3*zi-2]-omega*times));
		///////////////////////////////////
		}


		//mh[3*zi-0] =   Houle.hh1/2  * sin(2.0*PI*(times/Houle.periode - mh[3*zi-2]/Houle.lambda));

    		/* calcul de l'immersion de chaque noeud mh[3*zi-1] */ 
    		if (Noeud[zi].lonz >= 0.0)
    			{
      			/* flotteur  */
      			if (( wf[3*zi] <= mh[3*zi-0]) && (wf[3*zi] + Noeud[zi].lonz >= mh[3*zi-0]) )
      				{
				/*  flottant */
				mh[3*zi-1] = mh[3*zi-0] - wf[3*zi];
      				}
      			if (wf[3*zi] + Noeud[zi].lonz < mh[3*zi-0])
      				{
				/*  inonde */
				mh[3*zi-1] = Noeud[zi].lonz;
      				}
      			if (wf[3*zi] > mh[3*zi-0])
      				{
				/*  exonde */
				mh[3*zi-1] = 0.0;
				//printf("a zi %2d mh %lf\n",zi,wf[3*zi]-mh[3*zi-0]);	
				/*printf("zi = %d ",zi);
				wf[3*zi] = mh[3*zi-0];*/
      				}
    			}
    		if (Noeud[zi].lonz < 0.0)
    			{
      			/* lest  */
      			if ( (wf[3*zi] >= mh[3*zi-0]) && (wf[3*zi] + Noeud[zi].lonz <= mh[3*zi-0]))
      				{
				/*  flottant */
				mh[3*zi-1] =  Noeud[zi].lonz + wf[3*zi] - mh[3*zi-0];
      				}
      			if (wf[3*zi] < mh[3*zi-0])
      				{
				/*  inonde */
				mh[3*zi-1] =  Noeud[zi].lonz;
      				}
      			if (wf[3*zi] + Noeud[zi].lonz > mh[3*zi-0])
      				{
				/*  exonde */
				mh[3*zi-1] = 0.0;
				//printf("b zi %d mh %lf\n",zi,mh[3*zi-1]);	
       			}
    			}                        
  		}
  	}

