#include "4c19.h"

int ecriturehauling(char *nomfichier)
{
  	char   tonom[100];
  	FILE   *f2;
  	int    elem;


  	strcpy(tonom,nomfichier);
  	strcat(tonom,".haul");
  	/*
  	printf(" \n");
  	printf("%s %s \n","fichier ",tonom);
	*/
	
  	f2 = fopen(tonom,"a");

    	fprintf(f2,"  %11.3lf",times);
  	for (elem = 1 ; elem<= NOMBRE_ELEMENTS ; elem++) 
  	{
		fprintf(f2," %11.6lf ", Element[elem].lgrepos);
 	}
    	fprintf(f2,"\n");
   	fclose(f2);
}
