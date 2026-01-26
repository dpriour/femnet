#define PRINCIPAL 0
#include "4c19.h"

  /* Prise en compte de la pesanteur des noeuds*/

void pesanteur()
{
  int zi;
  for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  {
    wanoeud[3*zi] -= Noeud[zi].mz * G;
  }
}


