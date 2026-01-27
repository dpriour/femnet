#define PRINCIPAL 0
#include "4c19.h"

static int ifdrem = 1;
void remonteb4()
{
  int i,zg,zf,maxilarg;
  register double wrk;
  FILE *f;
  
  if (ifdrem != 0) 
  {
    ifdrem = 0;
    /* Largeur maximale de ze*/
    maxilarg = 0;
    for (zf = 1; zf <= 3*NOMBRE_NOEUDS; zf++)
    {
      if (maxilarg < rang[2][zf] - rang[4][zf]) maxilarg = rang[2][zf] - rang[4][zf];
    }
    printf("%s %d \n","Stiffness matrix width after resolution			:",maxilarg);

    /*largeur maximale a droite de la colonne eca de ze*/
    maxilarg = 0;
    for (zf = 1; zf <= 3*NOMBRE_NOEUDS; zf++)
    {
      if (maxilarg < rang[2][zf] - zf) maxilarg = rang[2][zf] - zf;
    }
    
    if (maxilarg > eca)
    {
      printf("%s %d \n","Warning: DIM3 in filwin.h is too small, increase it up to",maxilarg+1);
      exit(0);
    }
    printf("%s %d \n","Stiffness matrix width on right after resolution	:",maxilarg);

    /*largeur maximale a gauche de ze*/
    maxilarg = 0;
    for (zf = 1; zf <= 3*NOMBRE_NOEUDS; zf++)
    {
      if (maxilarg < zf - rang[4][zf]) maxilarg = zf - rang[4][zf];
    }
    
    if (maxilarg > eca)
    {
      printf("%s %d \n","Warning: DIM3 in filwin.h is too small, increase it up to",maxilarg+1);
      exit(0);
    }
    printf("%s %d \n","Stiffness matrix width on left after resolution		:",maxilarg);
  }

  /* Resolution du systeme triangulaire: on remonte la matrice de raideur X=F* inverse (K)*/
  for (zg = 3*NOMBRE_NOEUDS; zg >= 2; zg--) 
  {
    if (ze[zg][eca] != 0.0) 
    {
      wrk = wa[zg] / ze[zg][eca];
      if (fabs(wrk) > Deplacement)
      	{
      	/*printf("wrk = %lf ",wrk);*/
      	wrk = wrk / fabs(wrk) * Deplacement;
      	/*printf("wrk = %lf \n",wrk);*/
      	wrk = 0.0;
      	}
    }
    else
    {
      wrk = Deplacement;
      wrk = 0.0;
    }
    wv[zg] = wrk;
    for (zf = zg; zf >= rang[3][zg]; zf--) 
    {
      wa[zf] -= ze[zf][eca-zf+zg] * wrk;
    } 
  }
  wv[1] = wa[1] / ze[1][eca];
}

