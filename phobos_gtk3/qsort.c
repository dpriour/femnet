#define PRINCIPAL 0
#include <stdio.h>
#include "phobos.h"

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
	float tab[NBMAXNOEUD];
	int i,j,taille,min,max;
	
	/*tab contient la coordonnee en U des noeuds*/
	/*profondeur contient les numeros des noeuds dans l ordre croissant de leur coordonnee en U*/
	
	taille = Structure.nb_total;
		
	/*rangement de la coordonnee en U des noeuds*/
	for(i=1;i<=Structure.nb_total;i++)
		{
		tab[i] = noeud[i].x + noeud[i].y / 1000.0;
		profondeur[i] = i;
		}

	/*rangement par ordre croissant de leur coordonnee en U*/
	quicksort(tab,1,taille); 
	
	/*
	for(i= 1;i<=Structure.nb_total;i++)
		{
		printf("i %4d t %4.0f p %4d  ",i,tab[i],profondeur[i]);
		if (i == 1 * (i/1)) printf("\n");
		}
		printf("\n");
	*/
	}	
	


