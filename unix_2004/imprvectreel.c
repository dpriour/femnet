#define PRINCIPAL 0
#include "4c19.h"
#include <stdio.h>

void imprvectreel(int nb, double *vect)

	{
  	int elem;
  	/*printf(" \n");
  	impression vecteur vect, 12 par ligne, 3 chiffres apres la virgule*/
  	for (elem = 1 ; elem<= nb ; elem++)
  		{
    		printf(" %7.0lf ",vect[elem]);
    		if (12*(elem/12) == elem)	printf(" \n");
  		}
  	printf(" \n");
	}

void imprvectreel1(int nb, int dec, double *vect)

	{
  	int elem;
  	/*printf(" \n");
  	impression vecteur vect, 10 par ligne, dec chiffres apres la virgule*/
  	if (dec == 0)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.0lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 1)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.1lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 2)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.2lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 3)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.3lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 4)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.4lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 5)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.5lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 6)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.6lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 7)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.7lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 8)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.8lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 9)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.9lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 10)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %10.10lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 11)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %11.11lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 12)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %12.12lf ",vect[elem]);
	    		if (10*(elem/10) == elem)	printf(" \n");
	  		}
  		}
  	if (dec > 12)
  		{
	    	printf(" Sorry, change the code in imprvecreeel in /unix_2004/imprimvectreel.c : it must be <= 12");
  		}
  	/*if (10*(elem/10) != elem) printf("\n");*/
  	printf(" \n");
	}

void imprvectreel2(int nb, int dec, int col, double *vect)

	{
  	int elem;
  	/*printf(" \n");
  	impression vecteur vect, col par ligne, dec chiffres apres la virgule*/
  	if (dec == 0)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.0lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 1)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.1lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 2)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.2lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 3)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.3lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 4)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.4lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 5)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.5lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 6)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.6lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 7)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.7lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 8)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.8lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 9)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %9.9lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 10)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %10.10lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 11)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %11.11lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec == 12)
  		{
  		for (elem = 1 ; elem<= nb ; elem++)
	  		{
	    		printf(" %12.12lf ",vect[elem]);
	    		if (col*(elem/col) == elem)	printf(" \n");
	  		}
  		}
  	if (dec > 12)
  		{
	    	printf(" Sorry, change the code in imprvecreeel in /unix_2004/imprimvectreel.c : dec must be <= 12 and not %d",dec);
  		}
  	/*if (10*(elem/10) != elem) printf("\n");*/
  	printf(" \n");
	}


