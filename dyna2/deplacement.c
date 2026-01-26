#define PRINCIPAL 0
#include "4c19.h"

void deplacement(nomfichier)
char *nomfichier;
	{
  	int zi,no3,no6;
 	
  	/* lorsque qu une nouvelle position wf a ete estimee meme si elle n est
  	pas equilibree on recalcule la vitesse et l acceleration au temps t*/
 	/* mvb : vecteur contenant les vitesses des coordonnes des noeuds au temps t*/
 	/* mgb : vecteur contenant les accelerations des coordonnes des noeuds au temps t*/
 	/*the imersion of nodes and wetlength of element are calculated*/
   	for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS; zi++) 
  		{
    		mvb[zi]  = ( wf[zi] -  wf1[zi]) / Pascalcul;
    		mgb[zi]  = (mvb[zi] - mvb1[zi]) / Pascalcul;
  		}
  	
  	
  		
   	for (zi = 1 ; zi<= NOMBRE_NOEUDS; zi++) 
  		{
    		Noeud[zi].imersion  = wf[3*zi] - mh[3*zi] ;
    		if (Noeud[zi].imersion > 0.0)
    			{
			Noeud[zi].lgwet = 0.0		/*node exonde*/;
			}
		else
			{
    			if (fabs(Noeud[zi].imersion) > fabs(Noeud[zi].lonz))
    				{
				Noeud[zi].lgwet = fabs(Noeud[zi].lonz);
				}
			else
				{
				Noeud[zi].lgwet = fabs(Noeud[zi].imersion);
				}
			}
  		}
   	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
  		{
    		no3 = (int) rint(yb(zi,3)/3); 	/*numero du noeud de l extremite  1 de l element*/
    		no6 = (int) rint(yb(zi,6)/3); 	/*numero du noeud de l extremite  2 de l element*/
    		
    		if ((wf[3*no3] <= mh[3*no3]) && (wf[3*no6] > mh[3*no6]))
    			{
     			/* element flottant no3 dans l eau no6 hors d eau*/
      			Element[zi].lgwet = Element[zi].lgrepos * (wf[3*no3] - mh[3*no3])/(wf[3*no3] - wf[3*no6]) ;
      			}
    		if ((wf[3*no3] > mh[3*no3]) && (wf[3*no6] <= mh[3*no6]))
    			{
     			/* element flottant no6 dans l eau no3 hors d eau*/
      			Element[zi].lgwet = Element[zi].lgrepos  * (wf[3*no6] - mh[3*no6])/(wf[3*no6] - wf[3*no3]);
     			}
    		if ((wf[3*no3] <= mh[3*no3]) && (wf[3*no6] <= mh[3*no6]))
    			{
     			/* element inonde*/
      			Element[zi].lgwet = Element[zi].lgrepos;
      			}
    		if ((wf[3*no3] > mh[3*no3]) && (wf[3*no6] > mh[3*no6]))
    			{
     			/* element exonde*/
      			Element[zi].lgwet = 0.0;
      			}
  		}
	}
	
	

