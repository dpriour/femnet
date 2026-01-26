#define PRINCIPAL 0
#include "4c19.h"
#include <string.h>
#include <math.h>


void affectation_ia()
{
int i, inonnul, j, n, tmp;
FILE *f;

//f = fopen("donnee_ia.data", "w");

n = 3* NOMBRE_NOEUDS;

ia[0] = 1;
//fprintf(f, "ia[0] = %d\n", ia[0]);
inonnul = 2;
j=1;
tmp = ka[0];
for (i=1; i<Nnonnul; i++)
{
	if (ka[i] > tmp)
	{
		ia[j]=inonnul;
//fprintf(f, "ia[%d] = %d\n", j, ia[j]);
		j++;
		tmp = ka[i];
	}
	inonnul++;
}

ia[n] = Nnonnul+1;
//fprintf(f, "ia[%d] = %d\n", n, ia[n]);
//fclose(f);
}
