#define PRINCIPAL 0
#include "4c19.h"


int largeurbande()
	{
	/* 
	Calcule la largeur de la matrice avant: 3 * coutavant, puis apres: 3 * coutapres, la renumerotation
 	des noeuds 
 	*/
 	
  	int zi,zj,coutavant,coutapres;

  	coutavant = largeurmatrice();
 	printf("%s %d \n","Stiffness matrix width before renumerotation		:",3*coutavant);
  
  	/* fixation[1] Noeud[1].new_numero : numero du dernier noeud rencontre ayant le max de ses coordonnees fixes.
     	Si aucun noeud n'a une coordonnee fixe, le numero est  1 */     
  	fixation[1]  = fixationlaplusgrande();
  	Noeud[1].new_numero  = fixation[1];
  
  	/*  Calcul de la nouvelle numerotation des noeuds, en prenant pour point de depart le noeud Noeud[1].new_numero*/

    	serie();
 
  	nouvelleserie();
 
  	coutapres = largeurmatrice();
  	printf("%s %d \n","Stiffness matrix width after renumerotation		:",3*coutapres);
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  		{
    		fixa[fixation[zi]] = zi;
  		}
  		
  	/*renumeratation des noeud des cables*/
	for (zi=1;zi<=Structure.NbTypeelem;zi++)
		{
	  	for (zj=1;zj<=TypeElement[zi].nb_barre+1;zj++)
	  		{
			TypeElement[zi].noeud[zj] = fixa[TypeElement[zi].noeud[zj]];
	  		}
		}

	/*
	for (zi=1;zi<=Structure.NbTypeelem;zi++)
		{
		printf("cable %d  ",zi);
		printf("nb_barre %d\n",TypeElement[zi].nb_barre);
		printf("noeuds :  ");
	  	for (zj=1;zj<=TypeElement[zi].nb_barre+1;zj++)
	  		{
			printf("%3d ",TypeElement[zi].noeud[zj]);
	  		}
		printf("\n");
		printf("barres :  ");
	  	for (zj=1;zj<=TypeElement[zi].nb_barre;zj++)
	  		{
			printf("%3d ",TypeElement[zi].barre[zj]);
	  		}
		printf("\n");
		}
	*/
  		  		
  	return coutapres; 
	}

