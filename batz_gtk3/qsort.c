#include <stdio.h>
#include "batz.h"

void swapfloat(float *ttab1,float *ttab2);
void swapint(int *ttab1,int *ttab2);
void quicksort(float a[],int m, int n);
void tri();

void swapfloat(float *ttab1,float *ttab2)
	{
	float temp;
	temp   = *ttab1;
	*ttab1 = *ttab2;
	*ttab2 = temp;
	}


void swapint(int *ttab1,int *ttab2)
	{
	int temp;
	temp   = *ttab1;
	*ttab1 = *ttab2;
	*ttab2 = temp;
	}


void quicksort(float a[],int m, int n)
    	{
	int i,j; 
	float x;
	
       	i=m; 
       	j=n; 
       	x=a[(m+n) / 2]; 
       	while (i<=j) 
       		{
           	while (a[i]<x)  i++;
           	while (a[j]>x)  j--;
           	if (i <= j)
           		{    
               		swapfloat(&a[i],&a[j]); 
               		swapint(&profondeur[i],&profondeur[j]);
               		i++; 
               		j--;
               		}
               	}
       	if (m<j)  quicksort(a,m,j);
       	if (i<n)  quicksort(a,i,n);
    	}

void tri()
	{
	float tab[NBMAXTRIANGLE + NBMAXTRIANGLE + NBMAXELEMENT + NBMAXELEMENT + NBMAXELEMENT + NOMBRE_NOEUDS + NOMBRE_NOEUDS];
	int i,j,taille,min,max,no_ba;

	/*tab contient le barycentre des triangles des elements et des coulisses*/
	/*profondeur contient les numeros des triangles des elements  et des coulisses dans l ordre croissant*/
	/*si profondeur[i] <= NOMBRE_SURFACES profondeur[i] est le numero du  triangle au rang i*/
	/*si profondeur[i] >  NOMBRE_SURFACES et < NOMBRE_SURFACES+NOMBRE_ELEMENTS profondeur[i] est le numero de l element au rang i*/
	/*si profondeur[i] >  NOMBRE_SURFACES+NOMBRE_ELEMENTS profondeur[i] est le numero de la coulisse au rang i*/
	
	/*taille = NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS + Ball.nb;*/
	taille = NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS + Ball.nb + NOMBRE_NOEUDS;
	
	if(taille > NBMAXTRIANGLE + NBMAXTRIANGLE + NBMAXELEMENT + NBMAXELEMENT + NBMAXNOEUD + NBMAXNOEUD)
		{
		printf("Warning : NBMAXTRIANGLE ou NBMAXELEMENT pas assez grand\n");
		exit(0);
		}
	
	/*rangement de la position perpendiculaires a l ecran des triangles*/
	max = 0;
	min = max + 1;
	max = max + NOMBRE_SURFACES;
	for(i=min;i<=max;i++)
		{
		j = i - 0;
		tab[i] = (float) (Noeud[Surface[j].extremite[1]].z + Noeud[Surface[j].extremite[2]].z + Noeud[Surface[j].extremite[3]].z) / 3.0;
		profondeur[i] = i;
		}

	/*rangement de la position perpendiculaires a l ecran des triangles a mailles hesagonales*/
	min = max + 1;
	max = max + NOMBRE_SURF_HEXA;
	for(i=min;i<=max;i++)
		{
		j = i - NOMBRE_SURFACES;
		tab[i] = (float) (Noeud[Surf_Hexa[j].extremite[1]].z + Noeud[Surf_Hexa[j].extremite[2]].z + Noeud[Surf_Hexa[j].extremite[3]].z) / 3.0;
		profondeur[i] = i;
		}
		
	/*rangement de la position perpendiculaires a l ecran des elements*/
	min = max + 1;
	max = max + NOMBRE_ELEMENTS;
	for(i=min;i<=max;i++)
		{
		j = i - NOMBRE_SURFACES - NOMBRE_SURF_HEXA;
		tab[i] = (float) (Noeud[Element[j].extremite[1]].z + Noeud[Element[j].extremite[2]].z                             ) / 2.0;
		/*printf("element: i %4d j %4d tab %f\n",i,j,tab[i]);*/
		profondeur[i] = i;
		}
		
	/*rangement de la position perpendiculaires a l ecran des coulisses*/
	min = max + 1;
	max = max + NOMBRE_COULISSES;
	for(i=min;i<=max;i++)
		{
		j = i - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS;
		tab[i] = (float) (Noeud[Coulisse[j].extremite[1]].z + Noeud[Coulisse[j].extremite[2]].z                             ) / 2.0;
		profondeur[i] = i;
		}
		
	/*rangement de la position perpendiculaires a l ecran des winchs*/
	min = max + 1;
	max = max + NOMBRE_WINCHS;
	for(i=min;i<=max;i++)
		{
		j = i - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS - NOMBRE_COULISSES;
		tab[i] = (float) (Noeud[Winch[j].noeud[1]].z + Noeud[Winch[j].noeud[2]].z                             ) / 2.0;
		profondeur[i] = i;
		}
		
	/*rangement de la position perpendiculaires a l ecran des balls*/
	min = max + 1;
	max = max + Ball.nb;
	for(i=min;i<=max;i++)
		{
		j = i - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS - NOMBRE_COULISSES - NOMBRE_WINCHS;
		no_ba = Ball.noeud[j];
		/*printf("i %4d j %4d no_ba %4d  \n",i,j,no_ba);*/
		tab[i] = (float) Noeud[Ball.noeud[j]].z;
		profondeur[i] = i;
		}
		
	/*rangement de la position perpendiculaires a l ecran des noeuds*/
	min = max + 1;
	max = max + NOMBRE_NOEUDS;
	for(i=min;i<=max;i++)
		{
		j = i - NOMBRE_SURFACES - NOMBRE_SURF_HEXA - NOMBRE_ELEMENTS - NOMBRE_COULISSES - NOMBRE_WINCHS - Ball.nb;
		tab[i] = (float) Noeud[j].z;
		/*printf("node: i %4d j %4d tab %f\n",i,j,tab[i]);*/
		profondeur[i] = i;
		}
		
	/*
	for(i= 1;i<=NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS + Ball.nb + NOMBRE_NOEUDS;i++)
		{
		printf("avant tri i %4d t %8.3f p %4d  ",i,tab[i],profondeur[i]);
		if (i == 1 * (i/1)) printf("\n");
		}
		printf("\n");
	*/
	
	/*rangement par ordre croissant de leur position des triangles et elements*/
	quicksort(tab,1,taille); 
	
	/*
	for(i= 1;i<=NOMBRE_SURFACES + NOMBRE_SURF_HEXA + NOMBRE_ELEMENTS + NOMBRE_COULISSES + NOMBRE_WINCHS + Ball.nb + NOMBRE_NOEUDS;i++)
		{
		printf("apres tri i %4d t %8.3f p %4d  ",i,tab[i],profondeur[i]);
		if (i == 1 * (i/1)) printf("\n");
		}
		printf("\n");
	*/
	}	
	


