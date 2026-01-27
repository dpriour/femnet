#define PRINCIPAL 0
#include "4c19.h"

void serie()
	{
	/* 
	Procedure qui calcule la nouvelle numeration des points pour obtenir la largeur
   	de bande la plus faible.  Pour cela on determine une zone appelee frontiere actuelle, 
   	qui separe les noeuds deja rencontres des noeuds non encore rencontres. 
   	Au debut, la frontiere actuelle commence au point fixation[1] Noeud[1].new_numero.
   	La frontiere future est l ensemble des noeuds en contact avec la frontiere actuelle. 
   	Des qu un noeud est sur la frontiere future il est range dans le vecteur fixation (Noeud[].new_numero).
   	Fixation (Noeud[].new_numero) contient donc les numeros des noeuds dans leur ordre d'apparition dans le maillage.
   	Ces noeuds seront renumerotes dans la procedure nouvelleserie. 
   	*/

  	TLARGE1 frontiereactuelle,fontierefuture,compte;
  	int     zi,zj,zk,zl,zm;

  	/*
  	modification de la liste des noeuds des coulisses pour une estimation
  	de la largeur de bande plus aisee
  	en fait on rajoute a la liste de noeud interne .noeud les 2 extremites
  	*/
  	for (zi=1;zi<=NOMBRE_COULISSES;zi++)
  		{ 
    		Coulisse[zi].noeud[Coulisse[zi].nb_noeud + 1] = Coulisse[zi].extremite[1];
    		Coulisse[zi].noeud[Coulisse[zi].nb_noeud + 2] = Coulisse[zi].extremite[2];
 		}

	/* 
	Initialisation des frontieres et d'un compteur appele compte 
	compte = 0 si le noeud n a pas ete traite c est a dire si le noeud na pas ete et n est pas dans 
	la frontiere actuelle
	et si le noeud n a pas ete et n est pas dans la fontiere future
	frontiereactuelle[zi] = 1 si zi est sur la frontiere actuelle 
	fontierefuture[zi] = 1 si zi est sur la frontiere future
	la frontiere future est la liste de noeud en contact avec la frontiere actuelle
	*/
  	for ( zi = 1 ; zi<= NOMBRE_NOEUDS; zi++ )
  		{
   		frontiereactuelle[zi] = 0;
   		fontierefuture[zi]    = 0;
   		compte[zi]            = 0;
  		}
  
  	for ( zi = 2 ; zi<= NOMBRE_NOEUDS; zi++ )
  		{
   		fixation[zi] = 0;
   		Noeud[zi].new_numero = 0;
   		}

  	/*frontiereactuelle[Noeud[1].new_numero] = 1;*/
  	frontiereactuelle[fixation[1]] = 1;
	/*printf("fixation[1] = %d  frontiereactuelle[fixation[1]] = %d \n",fixation[1],frontiereactuelle[fixation[1]]);*/
  	compte[fixation[1]] = 1;
  	/*compte[Noeud[1].new_numero] = 1;*/
  	zk = 2;
  	/*while (Noeud[NOMBRE_NOEUDS].new_numero == 0)*/
  	/*at this step the balls are not taken into account because the balls have no contact with somthing else*/
	/*printf("Ball.nb %d \n",Ball.nb);*/

  	while (fixation[NOMBRE_NOEUDS-Ball.nb] == 0)
  		{
    		for ( zi = 1 ; zi<= NOMBRE_NOEUDS-Ball.nb; zi++ ) 
    			{
      			if (frontiereactuelle[zi] == 1)	/*zi est sur la frontière actuelle*/
      				{
        			/* traitement des elements */
        			for ( zj = 1 ; zj<= NOMBRE_ELEMENTS; zj++ ) 
        				{
          				if (Element[zj].extremite[1] == zi && compte[Element[zj].extremite[2]] == 0) 
          					{
            					fontierefuture[Element[zj].extremite[2]] = 1;
            					compte[Element[zj].extremite[2]] = 1;
            					fixation[zk] = Element[zj].extremite[2];
            					Noeud[zk].new_numero = Element[zj].extremite[2];
            					zk++;
          					}
          				if (Element[zj].extremite[2] == zi && compte[Element[zj].extremite[1]] == 0) 
          					{
            					fontierefuture[Element[zj].extremite[1]] = 1;
            					compte[Element[zj].extremite[1]] = 1;
            					fixation[zk] = Element[zj].extremite[1];
            					Noeud[zk].new_numero = Element[zj].extremite[1];
            					zk++;
          					}
        				}

        			/* traitement des coulisses */
        			for ( zj = 1 ; zj<= NOMBRE_COULISSES; zj++ ) 
        				{
        				for ( zm = 1 ; zm<= Coulisse[zj].nb_noeud + 2; zm++ ) 
        					{
        					if (Coulisse[zj].noeud[zm] == zi)
        						{
        						for ( zl = 1 ; zl<= Coulisse[zj].nb_noeud + 2; zl++ ) 
        							{
        							if(compte[Coulisse[zj].noeud[zl]] == 0)
        								{
            								fontierefuture[Coulisse[zj].noeud[zl]] = 1;
            								compte[Coulisse[zj].noeud[zl]] = 1;
            								fixation[zk] = Coulisse[zj].noeud[zl];
            								Noeud[zk].new_numero = Coulisse[zj].noeud[zl];
            								zk++;
        								}
        							}
        						}
        					}
        				}

        			/* traitement des winchs */
        			for ( zj = 1 ; zj<= NOMBRE_WINCHS; zj++ ) 
        				{
        				for ( zm = 1 ; zm<= Winch[zj].nb_barre + 1; zm++ ) 
        					{
        					if (Winch[zj].noeud[zm] == zi)
        						{
        						for ( zl = 1 ; zl<= Winch[zj].nb_barre + 1; zl++ ) 
        							{
        							if(compte[Winch[zj].noeud[zl]] == 0)
        								{
            								fontierefuture[Winch[zj].noeud[zl]] = 1;
            								compte[Winch[zj].noeud[zl]] = 1;
            								fixation[zk] = Winch[zj].noeud[zl];
            								Noeud[zk].new_numero = Winch[zj].noeud[zl];
            								zk++;
        								}
        							}
        						}
        					}
        				}

        			/* traitement des surfaces a mailles losanges*/
        			for ( zj = 1 ; zj<= NOMBRE_SURFACES; zj++ ) 
        				{
					/*printf("zi %4d surface %4d sommets  %4d %4d %4d\n",zi,zj,Surface[zj].extremite[1],Surface[zj].extremite[2],Surface[zj].extremite[3]);*/
          				if (Surface[zj].extremite[1] == zi && compte[Surface[zj].extremite[2]] == 0) 
          					{
            					fontierefuture[Surface[zj].extremite[2]] = 1;
            					compte[Surface[zj].extremite[2]] = 1;
            					fixation[zk] = Surface[zj].extremite[2];
            					Noeud[zk].new_numero = Surface[zj].extremite[2];
            					zk++;
          					}
          				if (Surface[zj].extremite[2] == zi && compte[Surface[zj].extremite[1]] == 0) 
          					{
            					fontierefuture[Surface[zj].extremite[1]] = 1;
            					compte[Surface[zj].extremite[1]] = 1;
            					fixation[zk] = Surface[zj].extremite[1];
            					Noeud[zk].new_numero = Surface[zj].extremite[1];
            					zk++;
          					}
          
          				if (Surface[zj].extremite[1] == zi && compte[Surface[zj].extremite[3]] == 0) 
          					{
            					fontierefuture[Surface[zj].extremite[3]] = 1;
            					compte[Surface[zj].extremite[3]] = 1;
            					fixation[zk] = Surface[zj].extremite[3];
            					Noeud[zk].new_numero = Surface[zj].extremite[3];
            					zk++;
          					}
          				if (Surface[zj].extremite[3] == zi && compte[Surface[zj].extremite[1]] == 0) 
          					{
            					fontierefuture[Surface[zj].extremite[1]] = 1;
            					compte[Surface[zj].extremite[1]] = 1;
            					fixation[zk] = Surface[zj].extremite[1];
            					Noeud[zk].new_numero = Surface[zj].extremite[1];
            					zk++;
          					}
          
          				if (Surface[zj].extremite[3] == zi && compte[Surface[zj].extremite[2]] == 0) 
          					{
            					fontierefuture[Surface[zj].extremite[2]] = 1;
            					compte[Surface[zj].extremite[2]] = 1;
            					fixation[zk] = Surface[zj].extremite[2];
            					Noeud[zk].new_numero = Surface[zj].extremite[2];
            					zk++;
          					}
          				if (Surface[zj].extremite[2] == zi && compte[Surface[zj].extremite[3]] == 0) 
          					{
            					fontierefuture[Surface[zj].extremite[3]] = 1;
            					compte[Surface[zj].extremite[3]] = 1;
            					fixation[zk] = Surface[zj].extremite[3];
            					Noeud[zk].new_numero = Surface[zj].extremite[3];
            					zk++;
          					}
        				}
        			/* traitement des surfaces a mailles hexagonales*/
        			for ( zj = 1 ; zj<= NOMBRE_SURF_HEXA; zj++ ) 
        				{
    					/*printf("NB_SURF_HEXA = %3d ",NOMBRE_SURF_HEXA);
     					printf("cpt[%3d] = %3d ",Surf_Hexa[zj].extremite[1],compte[Surf_Hexa[zj].extremite[1]]);
      					printf("cpt[%3d] = %3d ",Surf_Hexa[zj].extremite[2],compte[Surf_Hexa[zj].extremite[2]]);
     					printf("cpt[%3d] = %3d ",Surf_Hexa[zj].extremite[3],compte[Surf_Hexa[zj].extremite[3]]);
     					printf("zi = %3d  ",zi);
     					printf("zj = %3d\n",zj);*/
     					
     					
          				if (Surf_Hexa[zj].extremite[1] == zi && compte[Surf_Hexa[zj].extremite[2]] == 0) 
          					{
            					fontierefuture[Surf_Hexa[zj].extremite[2]] = 1;
            					compte[Surf_Hexa[zj].extremite[2]] = 1;
            					fixation[zk] = Surf_Hexa[zj].extremite[2];
            					Noeud[zk].new_numero = Surf_Hexa[zj].extremite[2];
            					zk++;
          					}
          				if (Surf_Hexa[zj].extremite[2] == zi && compte[Surf_Hexa[zj].extremite[1]] == 0) 
          					{
            					fontierefuture[Surf_Hexa[zj].extremite[1]] = 1;
            					compte[Surf_Hexa[zj].extremite[1]] = 1;
            					fixation[zk] = Surf_Hexa[zj].extremite[1];
            					Noeud[zk].new_numero = Surf_Hexa[zj].extremite[1];
            					zk++;
          					}
          
          				if (Surf_Hexa[zj].extremite[1] == zi && compte[Surf_Hexa[zj].extremite[3]] == 0) 
          					{
            					fontierefuture[Surf_Hexa[zj].extremite[3]] = 1;
            					compte[Surf_Hexa[zj].extremite[3]] = 1;
            					fixation[zk] = Surf_Hexa[zj].extremite[3];
            					Noeud[zk].new_numero = Surf_Hexa[zj].extremite[3];
            					zk++;
          					}
          				if (Surf_Hexa[zj].extremite[3] == zi && compte[Surf_Hexa[zj].extremite[1]] == 0) 
          					{
            					fontierefuture[Surf_Hexa[zj].extremite[1]] = 1;
            					compte[Surf_Hexa[zj].extremite[1]] = 1;
            					fixation[zk] = Surf_Hexa[zj].extremite[1];
            					Noeud[zk].new_numero = Surf_Hexa[zj].extremite[1];
            					zk++;
          					}
          
          				if (Surf_Hexa[zj].extremite[3] == zi && compte[Surf_Hexa[zj].extremite[2]] == 0) 
          					{
            					fontierefuture[Surf_Hexa[zj].extremite[2]] = 1;
            					compte[Surf_Hexa[zj].extremite[2]] = 1;
            					fixation[zk] = Surf_Hexa[zj].extremite[2];
            					Noeud[zk].new_numero = Surf_Hexa[zj].extremite[2];
            					zk++;
          					}
          				if (Surf_Hexa[zj].extremite[2] == zi && compte[Surf_Hexa[zj].extremite[3]] == 0) 
          					{
            					fontierefuture[Surf_Hexa[zj].extremite[3]] = 1;
            					compte[Surf_Hexa[zj].extremite[3]] = 1;
            					fixation[zk] = Surf_Hexa[zj].extremite[3];
            					Noeud[zk].new_numero = Surf_Hexa[zj].extremite[3];
            					zk++;
          					}
        				}
     				}
 			}
     			 
    		for ( zi = 1 ; zi<= NOMBRE_NOEUDS; zi++ ) 
    			{

       			frontiereactuelle[zi] = fontierefuture[zi];
       			fontierefuture[zi] = 0;
    			/*printf("f[%3d] = %2d  ",zi,frontiereactuelle[zi]);*/
    			}
  		}

 		/*balls*/
    		for ( zi = 1 ; zi<= Ball.nb; zi++ ) 
    			{
            		fixation[zi+NOMBRE_NOEUDS-Ball.nb] = zi+NOMBRE_NOEUDS-Ball.nb;
            		Noeud[zi+NOMBRE_NOEUDS].new_numero = zi+NOMBRE_NOEUDS-Ball.nb;
    			}
    		/*printf("*************************************************************\n");
    		for ( zi = 1 ; zi<= NOMBRE_NOEUDS; zi++ ) 
    			{
    			printf("fixation[%d] = %4d\n",zi,fixation[zi]);
    			}*/
	}

