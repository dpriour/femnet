#include "4c19.h"

void vitesseh2()
	{
  	/*
  	calcul de la vitesse des particules d eau au milieu des flotteurs des noeuds :
  	mvh[3*zi-2] = vitesse selon l axe x
  	mvh[3*zi-1] = vitesses selon l axe y
  	mvh[3*zi-0] = vitesse verticale : selon l axe z
  	prise en compte de la profondeur Depth
  	attention mvh est defini meme pour les noeuds exondes
	distance noeud a l'origine de la houle : mh[3*zi-2]
  	*/

  	int zi;
  	double kz,tetah,tetac,positionzplusd,vcourant,dcourant,prof;
 	double kk,omega,depth,aa,distance,zz,sinhh;
 
  	tetah = PI / 180.0 * Houle.direction;
  	tetac = PI / 180.0 * Courant.direction;

	if (Structure.wave_model == 1)
		{
 		//Airy finite depth
		kk = Houle.k;
		omega = Houle.omega;
		depth = Houle.depth;
		aa = Houle.hh1 / 2.0;
		if(depth<0.5*G/2/PI*Houle.periode*Houle.periode) 
			{
			//intermediate depth
			//to be sure not overpassing limit of double
		 	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
		  		{
		    		distance = mh[3*zi-2];
		    		zz = wf[3*zi-0];
				mvh[3*zi-2] = ((omega*aa*cos(kk*distance-omega*times)*cosh(kk*(zz+depth)))/sinh(depth*kk)) * cos(tetah) + Courant.vitesse * cos(tetac);
				mvh[3*zi-1] = ((omega*aa*cos(kk*distance-omega*times)*cosh(kk*(zz+depth)))/sinh(depth*kk)) * sin(tetah) + Courant.vitesse * sin(tetac);
				mvh[3*zi-0] =  (omega*aa*sin(kk*distance-omega*times)*sinh(kk*(zz+depth)))/sinh(depth*kk);
		  		}
		  	}
		else
			{
			//deep waters
		 	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
		  		{
		    		distance = mh[3*zi-2];
		    		zz = wf[3*zi-0];
				mvh[3*zi-2] = omega*aa*cos(kk*distance-omega*times)*exp(kk*zz) * cos(tetah) + Courant.vitesse * cos(tetac);
				mvh[3*zi-1] = omega*aa*cos(kk*distance-omega*times)*exp(kk*zz) * sin(tetah) + Courant.vitesse * sin(tetac);
				mvh[3*zi-0] = omega*aa*sin(kk*distance-omega*times)*exp(kk*zz);
		  		}
			}
										
 	  		/*
 	  		printf("tetah %5.2lf \n",tetah);
	  		printf("kk %5.2lf \n",kk);
	  		printf("aa %5.2lf \n",aa);
	  		printf("distance %5.2lf \n",distance);
	  		printf("zz %5.2lf \n",zz);
	  		printf("sinh(depth*kk) %5.2lf \n",sinhh);
	  		printf("mvh[3*1-2] %5.2lf \n",mvh[3*1-2]);
	  		printf("mvh[3*2-2] %5.2lf \n",mvh[3*2-2]);
	  		printf("mvh[3*1-1] %5.2lf \n",mvh[3*1-1]);
	  		printf("mvh[3*2-1] %5.2lf \n",mvh[3*2-1]);
	  		printf("mvh[3*1-0] %5.2lf \n",mvh[3*1-0]);
	  		printf("mvh[3*2-0] %5.2lf \n",mvh[3*2-0]);
	  		*/
		}
	if (Structure.wave_model == 2)
		{
		//Stokes 2d order finite depth
		kk = Houle.k;
		omega = Houle.omega;
		depth = Houle.depth;
		aa = Houle.hh1 / 2.0;
		if(depth<0.5*G/2/PI*Houle.periode*Houle.periode) 
			{
			//intermediate depth
			//to be sure not overpassing limit of double
		 	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
		  		{
		    		distance = mh[3*zi-2];
		    		zz = wf[3*zi-0];
				mvh[3*zi-2] = ((omega*aa*((3*aa*kk*kk*cos(2.0*(kk*distance-omega*times))*cosh(2.0*kk*(zz+depth)))/(4.0*pow(sinh(depth*kk),3.0))+kk*cos(kk*distance-omega*times)*cosh(kk*(zz+depth))))/(kk*sinh(depth*kk))) * cos(tetah) + Courant.vitesse * cos(tetac);
				mvh[3*zi-1] = ((omega*aa*((3*aa*kk*kk*cos(2.0*(kk*distance-omega*times))*cosh(2.0*kk*(zz+depth)))/(4.0*pow(sinh(depth*kk),3.0))+kk*cos(kk*distance-omega*times)*cosh(kk*(zz+depth))))/(kk*sinh(depth*kk))) * sin(tetah) + Courant.vitesse * sin(tetac);
				mvh[3*zi-0] =  (omega*aa*((3*aa*kk*kk*sin(2.0*(kk*distance-omega*times))*sinh(2.0*kk*(zz+depth)))/(4.0*pow(sinh(depth*kk),3.0))+kk*sin(kk*distance-omega*times)*sinh(kk*(zz+depth))))/(kk*sinh(depth*kk));
		  		}
	  		}
	  	else
	  		{
		 	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
		  		{
		    		distance = mh[3*zi-2];
		    		zz = wf[3*zi-0];
				mvh[3*zi-2] = omega*aa*(cos(kk*distance-omega*times))*exp(kk*zz) * cos(tetah) + Courant.vitesse * cos(tetac);
				mvh[3*zi-1] = omega*aa*(cos(kk*distance-omega*times))*exp(kk*zz) * sin(tetah) + Courant.vitesse * sin(tetac);
				mvh[3*zi-0] = omega*aa*(sin(kk*distance-omega*times))*exp(kk*zz);
				/*printf("mvh[%2d] %5.2lf %5.2lf %5.2lf ",zi,mvh[3*zi-2],mvh[3*zi-1],mvh[3*zi-0]);
	  			printf("omega %5.2lf ",omega);
	  			printf("times %5.2lf ",times);
	  			printf("kk %8.5lf ",kk);
		  		printf("aa %5.2lf ",aa);
		  		printf("distance %8.2lf ",distance);
		  		printf("zz %8.2lf ",zz);
		  		printf("exp(kk*zz) %5.2lf ",exp(kk*zz));
		  		printf("omega*aa %5.2lf\n",omega*aa);*/
		  		}
			//exit(0);
	  		}
 		}
	if (Structure.wave_model == 3)
		{
		//Stokes 3d order infinite depth
		kk = Houle.k;
		omega = Houle.omega;
		depth = Houle.depth;
		aa = Houle.hh1 / 2.0;
	 	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
	  		{
	    		distance = mh[3*zi-2];
	    		zz = wf[3*zi-0];
			mvh[3*zi-2] = (aa*sqrt(G/kk)*kk*(cos(kk*distance-omega*times))*exp(kk*zz)) * cos(tetah) + Courant.vitesse * cos(tetac);
			mvh[3*zi-1] = (aa*sqrt(G/kk)*kk*(cos(kk*distance-omega*times))*exp(kk*zz)) * sin(tetah) + Courant.vitesse * sin(tetac);
			mvh[3*zi-0] =  aa*sqrt(G/kk)*kk*(sin(kk*distance-omega*times))*exp(kk*zz);
	  		/*printf("mvh[%2d] %5.2lf %5.2lf %5.2lf ",zi,mvh[3*zi-2],mvh[3*zi-1],mvh[3*zi-0]);
	  		printf("omega %5.2lf ",omega);
	  		printf("times %5.2lf ",times);
	  		printf("kk %8.5lf ",kk);
	  		printf("aa %5.2lf ",aa);
	  		printf("distance %8.2lf ",distance);
	  		printf("zz %8.2lf ",zz);
	  		printf("exp(kk*zz) %5.2lf ",exp(kk*zz));
	  		printf("aa*sqrt(G/kk)*kk %5.2lf\n",aa*sqrt(G/kk)*kk);*/
	  		}
	  	//exit(0);
	  	/*if (times >= 1.0)
	  		{
	  		printf("tetah %5.2lf \n",tetah);
	  		printf("kk %5.2lf \n",kk);
	  		printf("aa %5.2lf \n",aa);
	  		printf("distance %5.2lf \n",distance);
	  		printf("zz %5.2lf \n",zz);
	  		printf("exp(kk*zz) %5.2lf \n",exp(kk*zz));
	  		printf("sqrt(G/kk) %5.2lf \n",sqrt(G/kk));
	  		printf("mvh[3*1-2] %5.2lf \n",mvh[3*1-2]);
	  		printf("mvh[3*2-2] %5.2lf \n",mvh[3*2-2]);
	  		printf("mvh[3*1-1] %5.2lf \n",mvh[3*1-1]);
	  		printf("mvh[3*2-1] %5.2lf \n",mvh[3*2-1]);
	  		printf("mvh[3*1-0] %5.2lf \n",mvh[3*1-0]);
	  		printf("mvh[3*2-0] %5.2lf \n",mvh[3*2-0]);
	  		exit(0);
	  		}*/
 		}
	}
