#define PRINCIPAL 0
#include "4c19.h"

double efforttendance()
/* Calcul de l effort moyen sur toutes les coordonnees des noeuds*/
{
  int zi;
  double Rx,Ry,Rz,RR;

  Rx = 0.0;
  Ry = 0.0;
  Rz = 0.0;
  for (zi = 1; zi<= NOMBRE_NOEUDS; zi++)
  {
    Rx += wa[3*zi-2];
    Ry += wa[3*zi-1];
    Rz += wa[3*zi-0];
  }
  RR = (sqrt(Rx*Rx + Ry*Ry + Rz*Rz)) / (double) NOMBRE_NOEUDS;

  return RR;
}


