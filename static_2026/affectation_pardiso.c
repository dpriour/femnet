#define PRINCIPAL 0
#include "4c19.h"
#include <stdlib.h>
#include <stdio.h>

int affectation_pardiso(double K, int l, int c)
{
int n, p;
n = 3*NOMBRE_NOEUDS;

	if (K == 0)
	{
	}
	else
	{
		p = (l-1)*n+(c-1);
	
		if (Nnonnul == 0)
		{
			A[p] = K;
			P[p] = p;
			Nnonnul++;
		}
		else
		{
			if (P[p] != -1)
			{
				A[p] += K; 		
			}
			else
			{
				A[p] = K;
				P[p] = p;
				Nnonnul++;
			}
		}
	}
return 0;
}

