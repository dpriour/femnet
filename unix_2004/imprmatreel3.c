#define PRINCIPAL 0
#include "4c19.h"

void imprmatreel3(int ncol1, int ncol2, int nlig1, int  nlig2, double *mat, int dimcol)

	{
  	int zi,zj;
  	printf(" \n");
  	for (zi = nlig1 ; zi<= nlig2 ; zi++)
  		{
    		for (zj = ncol1 ; zj<= ncol2 ; zj++) 
    			{
      			/*printf(" %8.0lf ",*(mat+ zj+(dimcol/2)-zi +((zi-0)*dimcol) ));*/
      			/*printf(" %8.0lf ",*(mat+zj+((zi-0)*dimcol)));*/
      			printf(" %8.0lf ",mat[zj+((zi-0)*dimcol)]);
      			/*if (20*(zj/20) == zj) printf(" \n");*/
    			}
    		printf("\n");
  		}
  	printf("\n");
	}


