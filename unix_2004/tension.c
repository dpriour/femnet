#define PRINCIPAL 0
#include "4c19.h"

void tension()
	{
	/* Calcul des efforts en chaque noeud issus de la tension des elements*/
  	int elem;
  	double dx,dy,dz;
  
  	/*prise en compte de la tension*/
  	for (elem = 1 ; elem<= NOMBRE_ELEMENTS ; elem++)
  		{
  		
  		/*if (yb(elem,4) == 247)
  			{
    			printf("elem = %d  ",elem);
    			printf("wf[] = %lf %lf %lf \n",wf[yb(elem,4)],wf[yb(elem,5)],wf[yb(elem,6)]);
 			}
  		
  		if (yb(elem,1) == 247)
  			{
    			printf("elem = %d  ",elem);
    			printf("wf[] = %lf %lf %lf \n",wf[yb(elem,1)],wf[yb(elem,2)],wf[yb(elem,3)]);
 			}*/
  		
    		dx = wf[yb(elem,4)]-wf[yb(elem,1)];
    		dy = wf[yb(elem,5)]-wf[yb(elem,2)];
    		dz = wf[yb(elem,6)]-wf[yb(elem,3)];
    
    		/* longueur tendue du bout: */
    		Element[elem].lgtendue = sqrt( (dx*dx) + (dy*dy) + (dz*dz) );
    
    		/*si le bout est trop detendu on limite sa longueur a 0.01 sa longueur au repos*/
    		if (Element[elem].lgtendue < 0.01 * Element[elem].lgrepos)
    			{
      			Element[elem].lgtendue = 0.01 * Element[elem].lgrepos;
    			}
    
    		/* Element[elem].raideur_effective = le module d'elasticite* section associe l'element(ie le bout)
       		Element[elem].wt est la tension dans le bout elem : > 0 en traction, < 0 en compression*/
       
    		Element[elem].wt = (Element[elem].lgtendue-Element[elem].lgrepos) * Element[elem].raideur_effective / Element[elem].lgrepos ;
    		
    		
    		//printf("wt = %lf \n",Element[elem].wt);
    		//exit(0);
    		//imprvectreel(21, waelem);
    		waelem[yb(elem,1)] += dx/Element[elem].lgtendue*Element[elem].wt;
    		waelem[yb(elem,2)] += dy/Element[elem].lgtendue*Element[elem].wt;
    		waelem[yb(elem,3)] += dz/Element[elem].lgtendue*Element[elem].wt;
    		waelem[yb(elem,4)] -= dx/Element[elem].lgtendue*Element[elem].wt;
    		waelem[yb(elem,5)] -= dy/Element[elem].lgtendue*Element[elem].wt;
    		waelem[yb(elem,6)] -= dz/Element[elem].lgtendue*Element[elem].wt;
    		
    		//imprvectreel(21, waelem);
/*		if (yb(elem,3) == 30)
  			{
    			printf("elem = %d  ",elem);
    			printf("wt %15.0lf ",Element[elem].wt);
     			printf("lgtendue %15.0lf ",Element[elem].lgtendue);
     			printf("lgrepos %15.0lf ",Element[elem].lgrepos);
     			printf("raideur_effective %15.0lf ",Element[elem].raideur_effective);
    			printf("waelem[] = %15.0lf %15.0lf %15.0lf \n",waelem[yb(elem,1)],waelem[yb(elem,2)],waelem[yb(elem,3)]);
 			}
  		if (yb(elem,6) == 30)
  			{
    			printf("elem = %d  ",elem);
    			printf("wt %15.0lf ",Element[elem].wt);
     			printf("lgtendue %15.0lf ",Element[elem].lgtendue);
     			printf("lgrepos %15.0lf ",Element[elem].lgrepos);
     			printf("raideur_effective %15.0lf ",Element[elem].raideur_effective);
    			printf("waelem[] = %15.0lf %15.0lf %15.0lf \n",waelem[yb(elem,4)],waelem[yb(elem,5)],waelem[yb(elem,6)]);
 			}*/
  		/*if (elem == 64)
  			{
			printf("tension %lf ",Element[elem].wt);
  			}*/
  		}
	}

