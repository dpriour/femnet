#define PRINCIPAL 0
#include "4c19.h"

/*lecture du fichier pre si il existe*/

int lecturepre(char *nomfichier)
	{
  	char tonom[1000],c;
  	int j,tmp,elem,itmp;
  	double elongation,tempo;
  	FILE *f1;

  	strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0;

  	strcat(tonom,".pre");
  	f1 = fopen(tonom,"r");


  	if (f1 == NULL) 
  		{
  		} 
  	else
  		{
		Structure.openfoam = 3;
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom," exists ");
	    	do  c=fgetc(f1); while (c !=':'); 
    		for (elem=1;elem<=NOMBRE_SURFACES;elem++)
    			{
			//itmp = fscanf(f1,"%d ",&tmp);
			itmp = fscanf(f1,"%lf ",&Surface[elem].pressure_n);
			itmp = fscanf(f1,"%lf ",&Surface[elem].pressure_t1);
			itmp = fscanf(f1,"%lf ",&Surface[elem].pressure_t2);
    			//printf("triangular element %d water pressure %lf %lf %lf\n",elem,Surface[elem].pressure_n,Surface[elem].pressure_t1,Surface[elem].pressure_t2);
   			}
    		//printf("RAND_MAX %d\n",RAND_MAX);
    		fclose(f1);
    		//exit(0);
    		return 1;
  		}
	}	


