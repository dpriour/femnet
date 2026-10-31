#include "4c19.h"

int creedynamique(nomfichier)
char *nomfichier;
	{
  	char   tonom[100];
  	FILE   *f2;
  	int    elem;
  	double elongation;

  	strcpy(tonom,nomfichier);
  	strcat(tonom,".dyn");
  	/*
  	printf(" \n");
  	printf("%s %s \n","fichier ",tonom);
	*/
  	f2 = fopen(tonom,"w");
  	/*creation ou nettoyage du fichier de resultat dynamique*/
   	fclose(f2);
	}
