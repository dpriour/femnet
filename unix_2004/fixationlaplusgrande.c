#define PRINCIPAL 0
#include "4c19.h"

int fixationlaplusgrande()

/* cette procedure retourne le numero du dernier noeud rencontre, ayant le plus de coordonnees fixes,
   Si aucun noeud n'a de coordonnee fixe, le numero est  1 */
{
  int nbfixation,nbfixationzi,zi,zj;
  
  nbfixation = 0 ;
  zj = 1 ;
  for ( zi = 1 ; zi<= NOMBRE_NOEUDS; zi++ ) 
  {
    nbfixationzi = 0;
    if (Noeud[zi].fixx == 1) nbfixationzi++;
    if (Noeud[zi].fixy == 1) nbfixationzi++;
    if (Noeud[zi].fixz == 1) nbfixationzi++;
    fixation[zi] = nbfixationzi;
    Noeud[zi].new_numero = nbfixationzi;
    if (nbfixationzi > nbfixation) 
    {
      nbfixation = nbfixationzi;
      zj = zi;
    }
  }
  return zj;
}

