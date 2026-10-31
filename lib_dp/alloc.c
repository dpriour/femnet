#define PRINCIPAL 0
#include <stdlib.h>
#include "protos_lib.h"
#include "definition_lib.h"

double *Malloc_double(int nb)
	{
	int i;
	double *ff;
	
  	ff = (double *) malloc(nb * sizeof(double));
	if ( ff   == NULL)
		{
		printf("Malloc_double  = NULL  : plus de memoire\n" );
		exit(0);
		}
	for (i=0;i<nb;i++) *(ff+i)=0.0;
	return ff;
	}
	
	
float *Malloc_float(int nb)
	{
	int i;
	float *ff;
	
  	ff = (float *) malloc(nb * sizeof(float));
	if ( ff   == NULL)
		{
		printf("Malloc_float  = NULL  : plus de memoire\n" );
		exit(0);
		}
	for (i=0;i<nb;i++) *(ff+i)=0.0;
	return ff;
	}
	
	
int *Malloc_int(int nb)
	{
	int i;
	int *ff;
	
  	ff = (int *) malloc(nb * sizeof(int));
	if ( ff   == NULL)
		{
		printf("Malloc_int  = NULL  : plus de memoire\n" );
		exit(0);
		}
	for (i=0;i<nb;i++) *(ff+i)=0;
	return ff;
	}
	
	
struct commentaire *Malloc_commentaire(int nb)
	{
	int i;
	struct commentaire *ff;
	
  	ff = (struct commentaire *) malloc(nb * sizeof(struct commentaire));
	if ( ff   == NULL)
		{
		printf("Malloc_commentaire  = NULL  : plus de memoire\n" );
		exit(0);
		}
	for (i=0;i<nb;i++) (ff+i)->texte[0]=0;
	return ff;
	}

	
	
double *Realloc_double(double *ff,int nb)
	{

	
  	ff = (double *) realloc(ff,nb * sizeof(double));
	if ( ff   == NULL)
		{
		printf("Realloc_double  = NULL  : plus de memoire\n" );
		exit(0);
		}
	return ff;
	}
	
	
float *Realloc_float(float *ff,int nb)
	{

	
  	ff = (float *) realloc(ff,nb * sizeof(float));
	if ( ff   == NULL)
		{
		printf("Realloc_float  = NULL  : plus de memoire\n" );
		exit(0);
		}
	return ff;
	}
	
	
int *Realloc_int(int *ff,int nb)
	{

	
  	ff = (int *) realloc(ff,nb * sizeof(int));
	if ( ff   == NULL)
		{
		printf("Realloc_int  = NULL  : plus de memoire\n" );
		exit(0);
		}
	return ff;
	}
	
struct commentaire *Realloc_commentaire(struct commentaire *ff,int nb)
	{

	
  	ff = (struct commentaire *) realloc(ff,nb * sizeof(struct commentaire));
	if ( ff   == NULL)
		{
		printf("Realloc_commentaire  = NULL  : plus de memoire\n" );
		exit(0);
		}
	return ff;
	}
	

