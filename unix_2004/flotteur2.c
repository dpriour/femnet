#define PRINCIPAL 0
#include "4c19.h"

/*prise en compte des efforts et des raideurs de flottabilite des noeuds*/

void flotteur2()
{
  int zi;
  for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  {
     /* mh est la hauteur de la surface libre(par rapport a la cote Z = 0). Ne sert qu'en dynamique.
        Donc, dans notre cas mh = 0.0*/


      /* flotteur flottant */
    if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] <= mh[3*zi]) && (wf[3*zi] + Noeud[zi].lonz >= mh[3*zi]))
    {
      wanoeud[3*zi]      += RHO * G * fabs(Noeud[zi].lonx * Noeud[zi].lony * (mh[3*zi] - wf[3*zi]));
	if (Structure.type_solver == 1)
	{
		ze[3*zi][eca] += RHO * G * fabs(Noeud[zi].lonx * Noeud[zi].lony);
	}
	else if (Structure.type_solver == 2)
      	{
		//affectation_pardiso(RHO * G * fabs(Noeud[zi].lonx * Noeud[zi].lony), 3*zi, 3*zi);
      	}	
    }


      /* flotteur inonde */
    if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] + Noeud[zi].lonz < mh[3*zi]))
    {
      wanoeud[3*zi]      += RHO * G * fabs(Noeud[zi].lonx * Noeud[zi].lony * Noeud[zi].lonz);
    }


      /* flotteur exonde */
    if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] > mh[3*zi]))
    {
    }
    


    if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] >= mh[3*zi]) && (wf[3*zi] + Noeud[zi].lonz <= mh[3*zi]))
    {
      /* lest flottant */
      wanoeud[3*zi]      += RHO * G * fabs(Noeud[zi].lonx * Noeud[zi].lony * (mh[3*zi] - Noeud[zi].lonz - wf[3*zi]));
	if (Structure.type_solver == 1)
	{
		ze[3*zi][eca] += RHO * G * fabs(Noeud[zi].lonx * Noeud[zi].lony);
	}
	else if (Structure.type_solver == 2)
      	{
		//affectation_pardiso(RHO * G * fabs(Noeud[zi].lonx * Noeud[zi].lony), 3*zi, 3*zi);
      	}	
    }
    if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] < mh[3*zi]))
    {
      /* lest inonde */
      wanoeud[3*zi]      += RHO * G * fabs(Noeud[zi].lonx * Noeud[zi].lony * Noeud[zi].lonz);
    }
    if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] + Noeud[zi].lonz > mh[3*zi]))
    {
      /* lest exonde */
    }
  }
}
