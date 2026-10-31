#define PRINCIPAL 0
#include "phobos.h"

void maillage_seam()
	{
	int i,mode,pa,el,nlo1,nlo2;
	double nbU,nbV;
	int    zi,nb_coupe,deb,fin,premier_loc,premier_cote,nb_lai,nlo3;
	float  xdeb,xfin,ydeb,yfin,zdeb,zfin;

	printf("maillage_seam \n");
	
	Structure.nb_selvedges = 0;
	Structure.nb_barre_selvedges = 0;	/*nb of bars in the selvedges*/
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].seam != 0.0)
			{
			for (nlo1=1;nlo1<=panneau[pa].nb_noeud_contour;nlo1++)
				{
				Structure.nb_selvedges += 1;
				/*this selvedges is from node nlo1 to nlo2*/
				if (Structure.NbTypeelem + Structure.nb_selvedges >= NBMAXELEMENT)
					{
					printf(" NBMAXELEMENT trop petit %4d < %4d \n",NBMAXELEMENT,Structure.NbTypeelem + Structure.nb_selvedges );
					exit(0);
					}
				deb = panneau[pa].noeud_contour[nlo1];
				if (nlo1 != panneau[pa].nb_noeud_contour) 
					{
					nlo2 = nlo1 + 1;
					fin = panneau[pa].noeud_contour[nlo1+1];
					}
				if (nlo1 == panneau[pa].nb_noeud_contour) 
					{
					nlo2 = 1;
					fin = panneau[pa].noeud_contour[1];
					}
				nbU = fabs(noeud[deb].U - noeud[fin].U);
				nbV = fabs(noeud[deb].V - noeud[fin].V);
				}
			/*bars creation along the seams*/
	
			/* 
			el    : numero de l element
			pa    : numero du panneau auquel el est lie
			nlo1  : numero de l extremite du panneau liee a l extremite 1 de el
			nlo2  :     -   -      -       -   -      -   -     -       2  -  -
			Maillage d un element a partir d un panneau deja maille, auquel il est lie par les extremites 
			*/
	
			/* determination du nombre de coupes de l element el a partir du maillage du panneau pa auquel selvedge est lie */
			if (nlo1 + 1 == nlo2)
				{
				if(panneau[pa].suivant_contour[nlo1] == 0)
					{
					/*pas de point de cote sur ce segment de contour*/
					nb_coupe = 1;
					}
				else
					{
					/*there is node along this side*/
					nlo3 = nlo2 - 1;
					do
						{
						nlo3 += 1;
						}
					while ((panneau[pa].suivant_contour[nlo3] == 0) && (nlo3 != panneau[pa].nb_noeud_contour));
					if (panneau[pa].suivant_contour[nlo3] != 0)
						{
						nb_coupe = panneau[pa].suivant_contour[nlo3] - panneau[pa].suivant_contour[nlo1] + 1;
						}
					else
						{
						nb_coupe = panneau[pa].nb_noeud_cote - panneau[pa].suivant_contour[nlo1] + 2;
						}
					}
				}
			if ((nlo1 - 1 != nlo2) && (nlo1 + 1 != nlo2))
				{
				/*dans ce cas nlo1 et nlo2 sont 1 et panneau[pa].nb_noeud_contour ou inversement*/
				if(panneau[pa].suivant_contour[panneau[pa].nb_noeud_contour] == 0)
					{
					/*pas de point de cote sur ce segment de contour*/
					nb_coupe = 1;
					}
				else
					{
					nb_coupe = panneau[pa].nb_noeud_cote - panneau[pa].suivant_contour[panneau[pa].nb_noeud_contour] + 2;
					}
				}
			/*Changement du nombre de barres sur l element el*/
			element[Structure.NbTypeelem + Structure.nb_selvedges].nb_barre = nb_coupe; 		
	
			/**********************************************/
		  	element[Structure.NbTypeelem + Structure.nb_selvedges].noeud = (int *) realloc(element[Structure.NbTypeelem + Structure.nb_selvedges].noeud, (1+ element[Structure.NbTypeelem + Structure.nb_selvedges].nb_barre) * sizeof(int));
			if (element[Structure.NbTypeelem + Structure.nb_selvedges].noeud    == NULL)
				{
				printf(" element[Structure.NbTypeelem + Structure.nb_selvedges].noeud 2 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
		  	element[Structure.NbTypeelem + Structure.nb_selvedges].barre = (int *) realloc(element[Structure.NbTypeelem + Structure.nb_selvedges].barre, (1+ element[Structure.NbTypeelem + Structure.nb_selvedges].nb_barre) * sizeof(int));
			if (element[Structure.NbTypeelem + Structure.nb_selvedges].barre    == NULL)
				{
				printf(" element[Structure.NbTypeelem + Structure.nb_selvedges].barre 2 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
		  	element[Structure.NbTypeelem + Structure.nb_selvedges].prop = (double *) realloc(element[Structure.NbTypeelem + Structure.nb_selvedges].prop, (1+ element[Structure.NbTypeelem + Structure.nb_selvedges].nb_barre) * sizeof(double));
			if (element[Structure.NbTypeelem + Structure.nb_selvedges].prop    == NULL)
				{
				printf(" element[Structure.NbTypeelem + Structure.nb_selvedges].prop 2 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
	
			/* sens de maillage du panneau et initialisation en consequence du premier noeud de cote du panneau */
			premier_loc = panneau[pa].suivant_contour[nlo1];		
			/*premier_loc  = node which follows the contour node in local numerotation*/
			premier_cote = panneau[pa].noeud_cote[panneau[pa].suivant_contour[nlo1]];
			/*premier_cote = node which follows the contour node in total numerotation*/
		
			for ( zi = 1 ; zi <= nb_coupe - 1 ; zi++ )
				{
				Structure.nb_barre_selvedges++;
				/*creation des barres*/
				if (zi == 1) barre[Structure.nb_barre_selvedges].noeud[1] = deb ;
				if (zi != 1) barre[Structure.nb_barre_selvedges].noeud[1] = premier_cote + zi - 1; 
				barre[Structure.nb_barre_selvedges].noeud[2] = Structure.nb_total;
				/*le no de type de la barre est le numero de l element*/
				barre[Structure.nb_barre_selvedges].type = Structure.NbTypeelem + Structure.nb_selvedges;
				barre[Structure.nb_barre_selvedges].netting2ropes_panel = 0;
			
				element[Structure.NbTypeelem + Structure.nb_selvedges].noeud[zi]    = Structure.nb_total;
		
				/* On parcourt le cote du panneau dans le sens maillé donc */
				barre[Structure.nb_barre_selvedges].pro[2] = panneau[pa].prop_cote[premier_loc + zi - 1];
				if ( zi == 1 ) 
					{ 
					/* Pour la 1ère barre, on a 0.0 */
					barre[Structure.nb_barre_selvedges].pro[1] = 0.0; 
					}		
				else           
					{ 
					/* Pour les autres barres, on s'appuie sur la barre precedente */
					barre[Structure.nb_barre_selvedges].pro[1] = barre[Structure.nb_barre_selvedges - 1].pro[2]; 
					}				
				barre[Structure.nb_barre_selvedges].longueur_repos = (float)  element[Structure.NbTypeelem + Structure.nb_selvedges].lgrepos * fabs(barre[Structure.nb_barre_selvedges].pro[1]-barre[Structure.nb_barre_selvedges].pro[2]);	
				}
			/*last bar of the selvedge*/
			Structure.nb_barre_selvedges++;
			if ( Structure.nb_barre_selvedges>= NBMAXBARRE)
				{
				printf(" NBMAXBARRE trop petit %4d < %4d \n",NBMAXBARRE,Structure.nb_barre_selvedges );
				exit(0);
				}
			if (zi == 1)  barre[Structure.nb_barre_selvedges].noeud[1] = deb ;
			else          barre[Structure.nb_barre_selvedges].noeud[1] = premier_cote + zi - 1;
			barre[Structure.nb_barre_selvedges].noeud[2] = fin;
			if (nb_coupe == 1 ) 
				{ 
				/* Pour le cas d'une seule barre */
				barre[Structure.nb_barre_selvedges].pro[1] = 0.0 ;
				}					
			else 		    
				{ 
				/* pour les autres, on s'appuie sur la barre précédente*/
				barre[Structure.nb_barre_selvedges].pro[1] = barre[Structure.nb_barre_selvedges - 1].pro[2] ;
				}
			barre[Structure.nb_barre_selvedges].pro[2] = 1.0;
			barre[Structure.nb_barre_selvedges].longueur_repos = (float)  element[Structure.NbTypeelem + Structure.nb_selvedges].lgrepos * fabs(barre[Structure.nb_barre_selvedges].pro[1]-barre[Structure.nb_barre_selvedges].pro[2]);
			barre[Structure.nb_barre_selvedges].type = el;	
			barre[Structure.nb_barre_selvedges].netting2ropes_panel = 0;
			printf(" el= %4d ",el);
			printf(" Structure.nb_barre_selvedges= %4d ",Structure.nb_barre_selvedges);
			printf(" Structure.nb_total= %4d \n",Structure.nb_total);
			}
		}
	}	


