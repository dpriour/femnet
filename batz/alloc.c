#include "batz.h"

double **Malloc_double_tab(int nb_li, int nb_co)
	{
	int zk;
	double *xmat,*cmat,**ff;
	
        /*allocation des matrices ff*/
	xmat = (double *) Malloc_double(1 + nb_li * nb_co);
	ff = (double **) malloc (nb_li * sizeof(double *));		if (ff	 == NULL){printf("ff	= NULL \n" );exit(0);}
  	cmat = xmat;
  	for (zk=0;zk<nb_li;zk++)
  		{
  		ff[zk] = cmat;
  		cmat += nb_co;
		}
	free(xmat);
	return ff;
	}
	
        				/*allocation des matrices houle.x*/
				/*n_ligne 	= Houle.nb_trace + 1;
       				p_colonne 	= nbtemps + 1;
     
       				xmat = (double *) malloc (n_ligne * p_colonne * sizeof(double));  	if (xmat == NULL){printf("xmat	= NULL \n" );exit(0);}
				Houle.x = (double **) malloc (n_ligne * sizeof(double *));	if (Houle.x	 == NULL){printf("Houle.x	= NULL \n" );exit(0);}
  				cmat = xmat;
  				for (zk=0;zk<n_ligne;zk++)
  					{
  					Houle.x[zk] = cmat;
  					cmat += p_colonne;
					}
				free(xmat);*/
    	
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
	

