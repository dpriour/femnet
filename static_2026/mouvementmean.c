#define PRINCIPAL 0
#include "4c19.h"

double mouvementmean()
/*calcul de la moyenne de deplacement de toutes les coordonnees des noeuds*/
{
  int zi;
  double Rx,RR;

  Rx = 0.0;
  for (zi = 1; zi<= NOMBRE_NOEUDS; zi++)
  {
    Rx += sqrt(wv[3*zi-2]*wv[3*zi-2] + wv[3*zi-1]*wv[3*zi-1] + wv[3*zi-0]*wv[3*zi-0]);
  }
  RR = Rx / (double) NOMBRE_NOEUDS;
  return RR;
}


