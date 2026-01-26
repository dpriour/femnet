#define PRINCIPAL 0
#include "4c19.h"

int modifraideur()
	{
  	/* Element[zi].wt  contient la tension dans le bout zi.
     	Donc Element[zi].wt est > 0 en traction et < 0 en compression.
     	Element[zi].wtfinal est initialise au depart a 1 donc >0. Pour chaque element zi, apres avoir
     	obtenu une position d'equilibre, on compare donc Element[zi].wt(tension a l'iteration nbpas) et
     	Element[zi].wtfinal( tension a l'iteration nbpas-1). S'ils sont de signe oppose , il y a eu passage
     	de traction en compression pour le bout zi. Ce n'est donc pas la position d'equilibre car 
     	le calcul a ete fait pour un des 2 modules d'elasticite(traction ou compression). 
     	On modifie donc le module pour cet element zi.Dans ce cas on retoune la valeur miseentension =-1.
     	On recommence les calculs(dans le programme principal) jusqu'a ce que wt et wtfinal
     	soit de meme signe pour chaque bout zi     */
     	
  	int zi;
  	
  	miseentension = 1;
     	
   	/*for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
   		{
      		if (Element[zi].lgtendue < Element[zi].lgrepos) 	Element[zi].raideur_effective = Element[zi].raideur_compression;
      		else 							Element[zi].raideur_effective = Element[zi].raideur_traction;
  		}*/
     	     	
   	for (zi = 1 ; zi<= NOMBRE_ELEMENTS; zi++) 
   		{
      		if (Element[zi].lgtendue < Element[zi].lgrepos) 	
      			{
      			//if(Element[zi].raideur_effective == Element[zi].raideur_traction) miseentension = -1;
      			Element[zi].raideur_effective = Element[zi].raideur_compression;
      			//printf("lgtendue - lgrepos %lf miseentension %d effective %lf traction %lf compression %lf\n",Element[11].lgtendue-Element[11].lgrepos,miseentension,Element[11].raideur_effective,Element[11].raideur_traction,Element[11].raideur_compression);
      			}
      		else 							
      			{
      			//if(Element[zi].raideur_effective == Element[zi].raideur_compression) miseentension = -1;
      			Element[zi].raideur_effective = Element[zi].raideur_traction;
      			//printf("mgtendue - lgrepos %lf miseentension %d effective %lf traction %lf compression %lf\n",Element[11].lgtendue-Element[11].lgrepos,miseentension,Element[11].raideur_effective,Element[11].raideur_traction,Element[11].raideur_compression);
    			}
  		}
     	     	
   	for (zi = 1 ; zi<= NOMBRE_COULISSES; zi++) 
   		{
    		if ( (Coulisse[zi].wt * Coulisse[zi].wtfinal < 0.0) && (Coulisse[zi].raideur_compression != Coulisse[zi].raideur_traction))
    			{
      			miseentension = -1;
      			Coulisse[zi].wtfinal = Coulisse[zi].wt;
      			if (Coulisse[zi].wt < 0.0) Coulisse[zi].raideur_effective = Coulisse[zi].raideur_compression;
      			if (Coulisse[zi].wt > 0.0) Coulisse[zi].raideur_effective = Coulisse[zi].raideur_traction;
    			}
  		}
  	return miseentension;
	}


