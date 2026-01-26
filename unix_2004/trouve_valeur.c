#define PRINCIPAL 0
#include "4c19.h"
#include <stdlib.h>
#include <stdio.h>

void trouve_valeur(int l, int c)
{
int n, p;
valeur = 0.0;

	n = 3*NOMBRE_NOEUDS;
	p = (l-1)*n+(c-1);

	if (P[p] != -1)
	{
		valeur = A[p];
	}
	else
	{
		valeur = 0.0;
	}
}


/*
int  b_max, b_min, i, n,  p, trouve;
	i = rechDicho(p, b_min, b_max);
	if (i == -1)
	{
	}
	else
	{
		valeur = a[i];
		trouve = 1;
	}

	if (trouve != 1)
	{
		valeur = 0.0;
	}
*/
