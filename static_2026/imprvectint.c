#define PRINCIPAL 0
#include "4c19.h"

void imprvectint(int nb,int *vect)

/*
nb nombre de valeurs affichees
vect nom du vecteur d entiers
*/

{
  int elem;
  printf(" \n");
  for (elem = 1 ; elem<= nb ; elem++)
  {
    printf(" %4d ",vect[elem]);
    if (10*(elem/10) == elem) 
      printf(" \n");
  }
  if (10*(elem/10) != elem) 
    printf("\n");
  printf("\n");
}


