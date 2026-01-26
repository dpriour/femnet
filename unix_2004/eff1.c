#define PRINCIPAL 0
#include "4c19.h" 

void eff1(int elem)
{
	/* 
	Calcul des efforts hydrodynamiques dans un triangle de numero elem 
	*/
     
  	int i;
  	double M[4],N[4],V[4],tfuv[4];
      
  	/* Definition du vecteur courant grace au fichier .mdf */
     	V[1] = Courant.vitesse*cos(Courant.direction*PI/180.0);
     	V[2] = Courant.vitesse*sin(Courant.direction*PI/180.0);
     	V[3] = 0.0 ;
  
  	/* N : Composantes selon X, Y et Z de la direction de la maille selon u */  
  	/* M : Composantes selon X, Y et Z de la direction de la maille selon v */  
     	N[1] = Surface[elem].nx ;   N[2] = Surface[elem].ny ;   N[3] = Surface[elem].nz;
     	M[1] = Surface[elem].mx ;   M[2] = Surface[elem].my ;   M[3] = Surface[elem].mz;
     	
  	/* Calcul des vecteurs effort tangent et effort normal pour un fil de direction u
  	et un fil de direction v 
  	dans le triangle numero elem, Resultat dans l'espace. */
  	
	trainee_fil( elem, V, &tfuv[0]);
           
}  

void eff_hexa1(int elem)
{
	/*
	Calcul des efforts hydrodynamiques dans un triangle de numero elem 
	*/
     
  	int i;
  	double L[4],M[4],N[4],V[4];
      
  	/* initialisation des vecteurs effort tangent et effort normal hydrodynamique, 
  	pour un element triangulaire */  
     	for( i =  1 ; i <= 9 ; i++)
     	{
       		ET[i] = 0.0 ;
       		EN[i] = 0.0 ;
     	}  
  
  	/* Definition du vecteur courant grace au fichier .mdf */
  	V[1] = Courant.vitesse*cos(Courant.direction*PI/180);
  	V[2] = Courant.vitesse*sin(Courant.direction*PI/180);
   	V[3] = 0.0 ;
  
 	/* L : Composantes selon X, Y et Z de la direction de la maille selon l */  
 	L[1] = Surf_Hexa[elem].lx ;   L[2] = Surf_Hexa[elem].ly ;   L[3] = Surf_Hexa[elem].lz;

	/* Calcul des vecteurs effort tangent et effort normal pour les fils de direction l 
	dans le triangle numero elem, Resultat dans l'espace. */
	efflmn(elem,V,L,Surf_Hexa[elem].lo_repos);
   
	/* Effort tangent sauvegarde dans le vecteur ET */
	/* Effort nomal sauvegarde dans le vecteur EN */   
	for ( i = 1 ; i <= 9 ; i++)
     	{
       		ET[i] = ETlmn[i];
       		EN[i] = ENlmn[i];
     	}
     
  	/* M : Composantes selon X, Y et Z de la direction de la maille selon m */  
     	M[1] = Surf_Hexa[elem].mx ;   M[2] = Surf_Hexa[elem].my ;   M[3] = Surf_Hexa[elem].mz; 
           
  	/* Calcul des vecteurs effort tangent et effort normal pour les fils de direction m 
  	dans le triangle numero elem, Resultat dans l'espace. */
     	efflmn(elem,V,M,Surf_Hexa[elem].mo_repos);
     
  	/* On somme les efforts selon la direction m et ceux selon la direction l */   
     	for ( i = 1 ; i <= 9 ; i++)
     	{
       		ET[i] += ETlmn[i];
       		EN[i] += ENlmn[i];
     	} 
            
  	/* N : Composantes selon X, Y et Z de la direction de la maille selon n */  
     	N[1] = Surf_Hexa[elem].nx ;   N[2] = Surf_Hexa[elem].ny ;   N[3] = Surf_Hexa[elem].nz;

  	/* Calcul des vecteurs effort tangent et effort normal pour les fils de direction n 
  	dans le triangle numero elem, Resultat dans l'espace. */
     	efflmn(elem,V,N,Surf_Hexa[elem].no_repos);
 
  	/* On somme les efforts selon la direction n et ceux selon la direction l et m */   
     	for ( i = 1 ; i <= 9 ; i++)
     	{
       		ET[i] += ETlmn[i];
       		EN[i] += ENlmn[i];
     	} 
}  

  
  
  
  
  
  
  
