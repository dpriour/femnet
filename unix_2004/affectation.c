#define PRINCIPAL 0
#include "4c19.h"
#include <stdlib.h>
#include <stdio.h>

//#define DEBUG

int affectation()
{
int c, i, l, n, N;
FILE *f;

i = 0;
n = 3*NOMBRE_NOEUDS;
N = 0;

a = (double *) malloc (Nnonnul * sizeof(double));
if (a	== NULL){printf("a	= NULL \n" );exit(0);}

ka = (int *) malloc (Nnonnul * sizeof(int));
if (ka	== NULL){printf("ka	= NULL \n" );exit(0);}

ja = (int *) malloc (Nnonnul * sizeof(int));
if (ja	== NULL){printf("ja	= NULL \n" );exit(0);}

	while (N != Nnonnul)
	{
		if (P[i] == -1)
		{
		}
		else
		{
			l = (int) (P[i]/n);
			c = (P[i]-l*n);
			a[N] = A[i];
			ka[N] = l+1;
			ja[N] = c+1;
			N++;
		}
		i++;
	}

#ifdef DEBUG
/*// Stocke donnee dans un fichier
f = fopen("donnee.data","a");
fprintf(f,"K %f, l %d, c %d, Nnonnul %d\n", K, l, c, Nnonnul);
fclose(f);*/

	// Stocke ka dans un fichier
f = fopen("donnee_ka.data","w");
for (i = 0; i<Nnonnul; i++) fprintf(f,"ka[%d] = %d\n", i, ka[i]);
fclose(f);

	// Stocke a dans un fichier
f = fopen("donnee_a.data","w");
for (i = 0; i<Nnonnul; i++) fprintf(f,"a[%d] = %f\n", i, a[i]);
fclose(f);

	// Stocke ja dans un fichier
f = fopen("donnee_ja.data","w");
for (i = 0; i<Nnonnul; i++) fprintf(f,"ja[%d] = %d\n", i, ja[i]);
fclose(f);
#endif

return 0;
}
