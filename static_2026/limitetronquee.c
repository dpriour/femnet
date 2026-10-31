#define PRINCIPAL 0
#include "4c19.h"

void limitetronquee()
/*limite tronquee du mouvement*/
{
  int zi;
  /*Deplacement = limite du deplacement des coordonnees*/
  if (fabs(MW) > Deplacement)
  {
    for (zi = 1; zi<= 3*NOMBRE_NOEUDS; zi++)
      if (fabs(wv[zi]) > Deplacement)
        wv[zi] = Deplacement * wv[zi] / fabs(wv[zi]); 
  }
}

