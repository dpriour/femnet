#define PRINCIPAL 0
#include "4c19.h"

void echangenoeuds(int Noeudi,int Noeudj)
	{
  	NOEUD  NoeudInter;
  	int    zg,zh;

  	/* Echange des valeurs caractéristiques aux noeuds */
  	memcpy(&NoeudInter,&Noeud[Noeudi],sizeof(NOEUD));
  	memcpy(&Noeud[Noeudi],&Noeud[Noeudj],sizeof(NOEUD));
  	memcpy(&Noeud[Noeudj],&NoeudInter,sizeof(NOEUD));
  
  

  	/* recherche du noeud Noeudi dans les extremites des elements*/
  	for ( zg = 1 ; zg<= NOMBRE_ELEMENTS; zg++ ) 
    		for ( zh = 1 ; zh<= 2; zh++ ) 
      			if ( Element[zg].extremite[zh] == Noeudi )
      				Element[zg].extremite[zh] = NOMBRE_NOEUDS + 1 ;
      				
  	/* recherche du noeud Noeudi dans les extremites des winchs*/
  	for ( zg = 1 ; zg<= NOMBRE_WINCHS; zg++ ) 
    		for ( zh = 1 ; zh<= 2; zh++ ) 
      			if ( Winch[zg].extremite[zh] == Noeudi )
      				Winch[zg].extremite[zh] = NOMBRE_NOEUDS + 1 ;
        
  	/* recherche du noeud Noeudi a l interieur des winchs*/
  	for ( zg = 1 ; zg<= NOMBRE_WINCHS; zg++ ) 
    		for ( zh = 1 ; zh<= Winch[zg].nb_barre+1; zh++ ) 
      			if ( Winch[zg].noeud[zh] == Noeudi )
      				Winch[zg].noeud[zh] = NOMBRE_NOEUDS + 1 ;
        
  	/* recherche du noeud Noeudi dans les extremites des coulisses*/
  	for ( zg = 1 ; zg<= NOMBRE_COULISSES; zg++ ) 
    		for ( zh = 1 ; zh<= 2; zh++ ) 
      			if ( Coulisse[zg].extremite[zh] == Noeudi )
      				Coulisse[zg].extremite[zh] = NOMBRE_NOEUDS + 1 ;
        
  	/* recherche du noeud Noeudi a l interieur des coulisses*/
  	for ( zg = 1 ; zg<= NOMBRE_COULISSES; zg++ ) 
    		for ( zh = 1 ; zh<= Coulisse[zg].nb_noeud; zh++ ) 
      			if ( Coulisse[zg].noeud[zh] == Noeudi )
      				Coulisse[zg].noeud[zh] = NOMBRE_NOEUDS + 1 ;
        
  	/* recherche du noeud Noeudi dans les coins des surfaces*/
  	for ( zg = 1 ; zg<= NOMBRE_SURFACES; zg++ ) 
    		for ( zh = 1 ; zh<= 3; zh++ ) 
      			if ( Surface[zg].extremite[zh] == Noeudi )
        			Surface[zg].extremite[zh] = NOMBRE_NOEUDS + 1 ;
        
  	/* recherche du noeud Noeudi dans les coins des surfaces hexagonales*/
  	for ( zg = 1 ; zg<= NOMBRE_SURF_HEXA; zg++ ) 
    		for ( zh = 1 ; zh<= 3; zh++ ) 
      			if ( Surf_Hexa[zg].extremite[zh] == Noeudi )
        			Surf_Hexa[zg].extremite[zh] = NOMBRE_NOEUDS + 1 ;



  	/* recherche du noeud Noeudj dans les extremites des elements et echange avec Noeudi*/
  	for ( zg = 1 ; zg<= NOMBRE_ELEMENTS; zg++ ) 
    		for ( zh = 1 ; zh<= 2; zh++ ) 
      			if ( Element[zg].extremite[zh] == Noeudj )
        			Element[zg].extremite[zh] = Noeudi ;
        			
  	/* recherche du noeud Noeudj dans les extremites des winchs et echange avec Noeudi*/
  	for ( zg = 1 ; zg<= NOMBRE_COULISSES; zg++ ) 
    		for ( zh = 1 ; zh<= 2; zh++ ) 
      			if ( Winch[zg].extremite[zh] == Noeudj )
        			Winch[zg].extremite[zh] = Noeudi ;
        
  	/* recherche du noeud Noeudj a l interieur des winchs et echange avec Noeudi*/
  	for ( zg = 1 ; zg<= NOMBRE_WINCHS; zg++ ) 
    		for ( zh = 1 ; zh<= Winch[zg].nb_barre+1; zh++ ) 
      			if ( Winch[zg].noeud[zh] == Noeudj )
      				Winch[zg].noeud[zh] =  Noeudi;
      				
  	/* recherche du noeud Noeudj dans les extremites des coulisses et echange avec Noeudi*/
  	for ( zg = 1 ; zg<= NOMBRE_COULISSES; zg++ ) 
    		for ( zh = 1 ; zh<= 2; zh++ ) 
      			if ( Coulisse[zg].extremite[zh] == Noeudj )
        			Coulisse[zg].extremite[zh] = Noeudi ;
        
  	/* recherche du noeud Noeudj a l interieur des coulisses et echange avec Noeudi*/
  	for ( zg = 1 ; zg<= NOMBRE_COULISSES; zg++ ) 
    		for ( zh = 1 ; zh<= Coulisse[zg].nb_noeud; zh++ ) 
      			if ( Coulisse[zg].noeud[zh] == Noeudj )
      				Coulisse[zg].noeud[zh] =  Noeudi;
      				
  	/* recherche du noeud Noeudi dans les coins des surfaces*/
  	for ( zg = 1 ; zg<= NOMBRE_SURFACES; zg++ ) 
    		for ( zh = 1 ; zh<= 3; zh++ ) 
      			if ( Surface[zg].extremite[zh] == Noeudj )
        			Surface[zg].extremite[zh] = Noeudi ;
        
  	/* recherche du noeud Noeudi dans les coins des surfaces hexagonales*/
  	for ( zg = 1 ; zg<= NOMBRE_SURF_HEXA; zg++ ) 
    		for ( zh = 1 ; zh<= 3; zh++ ) 
      			if ( Surf_Hexa[zg].extremite[zh] == Noeudj )
        			Surf_Hexa[zg].extremite[zh] = Noeudi ;
        
      				
  	/* recherche NOMBRE_NOEUDS + 1 dans les extremites des elements et echange avec Noeudj*/
  	for ( zg = 1 ; zg<= NOMBRE_ELEMENTS; zg++ ) 
    		for ( zh = 1 ; zh<= 2; zh++ ) 
      			if ( Element[zg].extremite[zh] == NOMBRE_NOEUDS + 1 )
        			Element[zg].extremite[zh] = Noeudj ;
      				
  	/* recherche NOMBRE_NOEUDS + 1 dans les extremites des winch et echange avec Noeudj*/
  	for ( zg = 1 ; zg<= NOMBRE_WINCHS; zg++ ) 
    		for ( zh = 1 ; zh<= 2; zh++ ) 
      			if ( Winch[zg].extremite[zh] == NOMBRE_NOEUDS + 1 )
        			Winch[zg].extremite[zh] = Noeudj ;
        			
  	/* recherche NOMBRE_NOEUDS + 1 a l interieur des winchs et echange avec Noeudj*/
  	for ( zg = 1 ; zg<= NOMBRE_WINCHS; zg++ ) 
    		for ( zh = 1 ; zh<= Winch[zg].nb_barre+1; zh++ ) 
      			if ( Winch[zg].noeud[zh] == NOMBRE_NOEUDS + 1 )
      				Winch[zg].noeud[zh] =  Noeudj;
      				
  	/* recherche NOMBRE_NOEUDS + 1 dans les extremites des coulisses et echange avec Noeudj*/
  	for ( zg = 1 ; zg<= NOMBRE_COULISSES; zg++ ) 
    		for ( zh = 1 ; zh<= 2; zh++ ) 
      			if ( Coulisse[zg].extremite[zh] == NOMBRE_NOEUDS + 1 )
        			Coulisse[zg].extremite[zh] = Noeudj ;
        			
  	/* recherche NOMBRE_NOEUDS + 1 a l interieur des coulisses et echange avec Noeudj*/
  	for ( zg = 1 ; zg<= NOMBRE_COULISSES; zg++ ) 
    		for ( zh = 1 ; zh<= Coulisse[zg].nb_noeud; zh++ ) 
      			if ( Coulisse[zg].noeud[zh] == NOMBRE_NOEUDS + 1 )
      				Coulisse[zg].noeud[zh] =  Noeudj;
      				
  	/* recherche NOMBRE_NOEUDS + 1 dans les coins des surfaces et echange avec Noeudj*/
  	for ( zg = 1 ; zg<= NOMBRE_SURFACES; zg++ ) 
    		for ( zh = 1 ; zh<= 3; zh++ ) 
      			if ( Surface[zg].extremite[zh] == NOMBRE_NOEUDS + 1 )
        			Surface[zg].extremite[zh] = Noeudj ;
 
  	/* recherche NOMBRE_NOEUDS + 1 dans les coins des surfaces hexagonales et echange avec Noeudj*/
  	for ( zg = 1 ; zg<= NOMBRE_SURF_HEXA; zg++ ) 
    		for ( zh = 1 ; zh<= 3; zh++ ) 
      			if ( Surf_Hexa[zg].extremite[zh] == NOMBRE_NOEUDS + 1 )
        			Surf_Hexa[zg].extremite[zh] = Noeudj ;
        			
	/*
	for (zg=1;zg<=NOMBRE_WINCHS;zg++)
  		{ 
		printf("zg %3d extremities %3d %3d\n",zg,Winch[zg].extremite[1],Winch[zg].extremite[2]);
		for (zh=1;zh<=Winch[zg].nb_barre+1;zh++)
  			{
			printf("zh %3d noeud %3d prop %lf\n",zh,Winch[zg].noeud[zh],Winch[zg].prop[zh]);
			}
		}
	*/
}


