#define PRINCIPAL 0
#include "4c19.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int modif_pardiso(double K, int l, int c)
{
int i, n, p;

n = 3*NOMBRE_NOEUDS;
p = (l-1)*n+(c-1);

	if (K == 0)
	{
		if (P[p] == -1)
		{
		}
		else
		{
			P[p] = -1;
			A[p] = K;
	
			Nnonnul--;
		}
	}
	else
	{
			P[p] = p;
			A[p] = K;
	}
return 0;
}

/*	for (i= 0; i<Nnonnul; i++)
	{
		if(ka[i] == l && ja[i] == c)
		{
			if (K == 0)
			{
				memmove (&a[i], &a[i+1], (Nnonnul-(i+1))*sizeof(double)); // decalage a gauche de a //
				a[Nnonnul-1] = 0.0;

				memmove (&ja[i], &ja[i+1], (Nnonnul-(i+1))*sizeof(int));  // decalage a gauche de ja//
				ja[Nnonnul-1] = 0;

				memmove (&ka[i], &ka[i+1], (Nnonnul-(i+1))*sizeof(int));  // decalage a gauche de ka//
				ka[Nnonnul-1] = 0;

				Nnonnul--;
			}
			else
			{
				a[i] = K;
			}
			break;
		}
	}*/
