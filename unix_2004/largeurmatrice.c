#define PRINCIPAL 0
#include "4c19.h"

int largeurmatrice()

	{
	/* Calcul la largeur de la matrice de raideur bande, divisee par trois*/
  	typedef int    TABECHANGE[DIM1];
  	TABECHANGE     compte,largeur;
  	int            zi,zj,cout,zk,zl;


  	for ( zi = 1 ; zi<= NOMBRE_NOEUDS; zi++ ) 
  		{
    		compte [zi] = 0 ;
    		largeur[zi] = 0 ;
  		}
  
  	for ( zi = 1 ; zi <= NOMBRE_NOEUDS; zi++ ) 
  		{
    		compte [zi] = 1 ;
    
    		/* 
    		Pour chaque zi : Parcours de tous les bouts et mise a 1 de compte[i]
       		si i et zi sont les extremites d'un bout et si compte [i] valait 0 . 
       		*/
       
    		for ( zj = 1 ; zj <= NOMBRE_ELEMENTS; zj++ ) 
    			{
      			if ( ( Element[zj].extremite[1] == zi ) && (compte[Element[zj].extremite[2]] == 0) )compte[Element[zj].extremite[2]] = 1 ;
      			if ( ( Element[zj].extremite[2] == zi ) && (compte[Element[zj].extremite[1]] == 0) )compte[Element[zj].extremite[1]] = 1 ;
    			}
    
    		/* 
    		Pour chaque zi : Parcours de toutes les coulisses et mise a 1 de compte[i]
       		si i et zi sont des noeuds d'une coulisse et si compte [i] valait 0 . 
       		*/
       
    		for ( zj = 1 ; zj <= NOMBRE_COULISSES; zj++ ) 
    			{
    			for ( zk = 1 ; zk <= Coulisse[zj].nb_noeud + 2; zk++ ) 
    				{
    				if ( Coulisse[zj].noeud[zk] == zi )
    					{
    					for ( zl = 1 ; zl <= Coulisse[zj].nb_noeud + 2; zl++ ) 
    						{
    						if (compte[Coulisse[zj].noeud[zl]] = 0)
    							{
    							compte[Coulisse[zj].noeud[zl]] = 1;
    							}
    						}
    					}
    				}
    			}
    
    		/* 
    		Pour les mailles losanges :
    		Pour chaque zi : Parcours de tous les triangle et mise a 1 de compte[i]
      	 	si i et zi sont 2 sommets d'un meme triangle et si compte [i] valait 0 . 
      	 	*/  
         
    		for ( zj = 1 ; zj <= NOMBRE_SURFACES; zj++ ) 
    			{
      			if ( ( Surface[zj].extremite[1] == zi ) && (compte[Surface[zj].extremite[2]] == 0) )compte[Surface[zj].extremite[2]] = 1 ;
      			if ( ( Surface[zj].extremite[2] == zi ) && (compte[Surface[zj].extremite[1]] == 0) )compte[Surface[zj].extremite[1]] = 1 ;
      			if ( ( Surface[zj].extremite[1] == zi ) && (compte[Surface[zj].extremite[3]] == 0) )compte[Surface[zj].extremite[3]] = 1 ;
      			if ( ( Surface[zj].extremite[3] == zi ) && (compte[Surface[zj].extremite[1]] == 0) )compte[Surface[zj].extremite[1]] = 1 ;
      			if ( ( Surface[zj].extremite[3] == zi ) && (compte[Surface[zj].extremite[2]] == 0) )compte[Surface[zj].extremite[2]] = 1 ;
      			if ( ( Surface[zj].extremite[2] == zi ) && (compte[Surface[zj].extremite[3]] == 0) )compte[Surface[zj].extremite[3]] = 1 ;
    			}
    
    		/* 
    		Pour les mailles hexagonales :
    		Pour chaque zi : Parcours de tous les triangle et mise a 1 de compte[i]
      	 	si i et zi sont 2 sommets d'un meme triangle et si compte [i] valait 0 . 
      	 	*/  
         
    		for ( zj = 1 ; zj <= NOMBRE_SURF_HEXA; zj++ ) 
    			{
      			if ( ( Surf_Hexa[zj].extremite[1] == zi ) && (compte[Surf_Hexa[zj].extremite[2]] == 0) )compte[Surf_Hexa[zj].extremite[2]] = 1 ;
      			if ( ( Surf_Hexa[zj].extremite[2] == zi ) && (compte[Surf_Hexa[zj].extremite[1]] == 0) )compte[Surf_Hexa[zj].extremite[1]] = 1 ;
      			if ( ( Surf_Hexa[zj].extremite[1] == zi ) && (compte[Surf_Hexa[zj].extremite[3]] == 0) )compte[Surf_Hexa[zj].extremite[3]] = 1 ;
      			if ( ( Surf_Hexa[zj].extremite[3] == zi ) && (compte[Surf_Hexa[zj].extremite[1]] == 0) )compte[Surf_Hexa[zj].extremite[1]] = 1 ;
      			if ( ( Surf_Hexa[zj].extremite[3] == zi ) && (compte[Surf_Hexa[zj].extremite[2]] == 0) )compte[Surf_Hexa[zj].extremite[2]] = 1 ;
      			if ( ( Surf_Hexa[zj].extremite[2] == zi ) && (compte[Surf_Hexa[zj].extremite[3]] == 0) )compte[Surf_Hexa[zj].extremite[3]] = 1 ;
    			}

    		/* 
    		Pour chaque noeud zi, largeur[zi] est egale au nombre de sommets de triangles
     		ayant pour noeud commun zi (zi est aussi compte) 
     		*/
       
    		for ( zj = 1 ; zj <= NOMBRE_NOEUDS; zj++ ) largeur[zi] = largeur[zi] + compte[zj] ;
    
   		/* 
   		Remise de compte a 0 pour les noeud de numero 1 jusqu'a zi-1 
   		*/ 
   		
    		if ( zi > 1 ) 
    			{
      			for ( zj = 1 ; zj <= zi-1; zj++ )  compte[zj] = 0;
    			}
 		}
  		cout = 0;
  		
  		/* 
  		cout = max des largeur[zi] pour tous les zi : c'est la largeur de
     		la matrice bande/3 .(car il y a 3 coordonnees par noeud)
     		*/
     		
  		for ( zi = 1 ; zi<= NOMBRE_NOEUDS; zi++ ) 
  			{
    			compte [zi] = 0 ;
    			if ( cout < largeur[zi] ) cout = largeur[zi] ;
  			}
  
  		return (cout); 
	}


