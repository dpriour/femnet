#define PRINCIPAL 0
#include "4c19.h"

void resolution4()
	{
	/*modification de la matrice ze pour la rendre triangulaire superieure: elimination de Gauss*/
  	register int zj,zk,zi,borninf,bornsup;
  	int singu;
  	double rai;
  	register double inter,*a,*b;     				/* a et b sont des pointeurs */

  	/*for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++)
  		{
    		for (zj = 1 ; zj<= 3*NOMBRE_NOEUDS ; zj++) 
    			{
    			if (rang[1][zj] == zi) printf("1");
    			else
    				{
    				if (rang[2][zi] == zj) printf("2");
    				else
    					{
    					if (rang[3][zj] == zi) printf("3");
    					else	
    						{
    						if (rang[4][zi] == zj) printf("4");
    						else
    							{
 							printf(".");
    							}
    						}
    					}
    				}
			}
		}*/
  	/*for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++)
  		{
		printf(" ");
    		for (zj = 1 ; zj<= 3*NOMBRE_NOEUDS ; zj++) 
    			{
    			if (fabs(ze[zi][eca-zi+zj]) > 0.0000000001) 	
    				{
    				rai = (log10(fabs(ze[zi][eca-zi+zj]))+3.0)/2.0;
    				printf("%1.0lf",rai);
    				}
    			else 	printf(".");
			}
 		printf("\n");
		}*/
  	/*for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++)
  		{
		printf(" ");
    		for (zj = eca-70 ; zj<= eca+70 ; zj++) 
    			{
    			if ((zi+zj-eca <1) || (zi+zj-eca >3*NOMBRE_NOEUDS))
    				{
				printf(" ");
    				}
    			else
    				{
    				if (fabs(ze[zi][zj]) > 0.0000000001) 	
    					{
    					rai = (log10(fabs(ze[zi][zj]))+3.0)/2.0;
    					printf("%1.0lf",rai);
    					}
    				else 	printf(".");
    				}
			}
 		printf("\n");
		}*/


  	for (zi = 2; zi<= 3*NOMBRE_NOEUDS  ; zi++) if (rang[1][zi] < rang[1][zi-1]) rang[1][zi] = rang[1][zi-1]; /*traitement de tous les rang[1] changement eventuel de la borne basse de la coordonnee zi*/
  	for (zi = 2; zi<= 3*NOMBRE_NOEUDS  ; zi++) if (rang[2][zi] < rang[2][zi-1]) rang[2][zi] = rang[2][zi-1]; /*traitement de tous les rang[2] changement eventuel de la borne droite de la coordonnee zi*/
  	for (zi = 3*NOMBRE_NOEUDS-1; zi>= 1; zi--) if (rang[3][zi] > rang[3][zi+1]) rang[3][zi] = rang[3][zi+1]; /*traitement de tous les rang[3] changement eventuel de la borne haute de la coordonnee zi*/
  	for (zi = 3*NOMBRE_NOEUDS-1; zi>= 1; zi--) if (rang[4][zi] > rang[4][zi+1]) rang[4][zi] = rang[4][zi+1]; /*traitement de tous les rang[4] changement eventuel de la borne gauche de la coordonnee zi*/

  	/*for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++)
  		{
    		for (zj = 1 ; zj<= 3*NOMBRE_NOEUDS ; zj++) 
    			{
    			if (rang[1][zj] == zi) printf("1");
    			else
    				{
    				if (rang[2][zi] == zj) printf("2");
    				else
    					{
    					if (rang[3][zj] == zi) printf("3");
    					else	
    						{
    						if (rang[4][zi] == zj) printf("4");
    						else
    							{
 							printf(".");
    							}
    						}
    					}
    				}
			}
		printf(" ");
    		for (zj = 1 ; zj<= 3*NOMBRE_NOEUDS ; zj++) 
    			{
    			if (fabs(ze[zi][eca-zi+zj]) > 0.0000000001) 	
    				{
    				rai = (log10(fabs(ze[zi][eca-zi+zj]))+10.0)/3.0;
    				printf("%1.0lf",rai);
    				}
    			else 	printf(".");
			}
 		printf("\n");
		}*/

  	singu = 0;
  	for (zi = 1; zi<= 3*NOMBRE_NOEUDS-1 ; zi++)                	/*traitement de toutes les colonnes zi*/
  		{
    		if (fabs(ze[zi][eca]) < 0.00000000001)
    			{
      			ze[zi][eca] = 0.00000000001;				/*matrice singuliere*/
      			if (singu == 0)
      				{
        			printf("matrice raideur singuliere node component %d\n",zi);
        			singu = 1;
      				}
    			}
    		borninf = eca+zi+1;
    		bornsup = eca+rang[2][zi];
    		b = *(ze+zi)-zi;                                    	/* A  b on affecte la valeur pointee par" 1er terme de la ligne zi"-zi termes*/
    		for (zj = zi+1; zj<= rang[1][zi] ; zj++)            	/*traitement de toutes les lignes zj*/
    			{
      			a = *(ze+zj)-zj;				/* A  a on met la valeur pointee" 1er terme de la ligne zj"-zj termes*/
      			inter = ze[zj][eca-zj+zi] / ze[zi][eca]; 	/*facteur de multiplication de la ligne zj*/
      			wa[zj] -= wa[zi] * inter;               	/*modification de l effort*/
			for (zk = borninf; zk<= bornsup ; zk++) 	/*traitement de toutes les colonnes zk*/
        			*(a+zk) -= (*(b+zk)) * inter;         	/*modification des termes de  la matrice de raideur*/
      			ze[zj][eca-zj+zi] = 0.0;                	/* Mise a zero des colonnes */
    			}    
  		}
  	/*for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++)
  		{
    		for (zj = 1 ; zj<= 3*NOMBRE_NOEUDS ; zj++) 
    			{
    			if (rang[1][zj] == zi) printf("1");
    			else
    				{
    				if (rang[2][zi] == zj) printf("2");
    				else
    					{
    					if (rang[3][zj] == zi) printf("3");
    					else	
    						{
    						if (rang[4][zi] == zj) printf("4");
    						else
    							{
 							printf(".");
    							}
    						}
    					}
    				}
			}
		printf(" ");
    		for (zj = 1 ; zj<= 3*NOMBRE_NOEUDS ; zj++) 
    			{
    			if (fabs(ze[zi][eca-zi+zj]) > 0.0000000001) 	
    				{
    				rai = (log10(fabs(ze[zi][eca-zi+zj]))+10.0)/3.0;
    				printf("%1.0lf",rai);
    				}
    			else 	printf(".");
			}
 		printf("\n");
		}*/

	}

