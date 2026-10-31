#define PRINCIPAL 0
#include "4c19.h"

/*lecture du fichier spe si il existe*/

int lecturespe(char *nomfichier)
	{
  	char tonom[1000],c;
  	int j,tmp,elem,itmp;
  	double elongation,tempo;
  	FILE *f1;

  	strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0;

  	strcat(tonom,".spe");
  	f1 = fopen(tonom,"r");


  	if (f1 == NULL) 
  		{
  		} 
  	else
  		{
		Structure.openfoam = 2;
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom," exists ");
	    	//do  c=fgetc(f1); while (c !=':'); 
    		for (elem=1;elem<=NOMBRE_NOEUDS;elem++)
    			{
			//itmp = fscanf(f1,"%d ",&tmp);
			itmp = fscanf(f1,"%lf ",&Noeud[elem].vx);
			itmp = fscanf(f1,"%lf ",&Noeud[elem].vy);
			itmp = fscanf(f1,"%lf ",&Noeud[elem].vz);
    			//printf("node %d water speed %lf %lf %lf\n",elem,Noeud[elem].vx,Noeud[elem].vy,Noeud[elem].vz);
   			//Noeud[elem].vx += (2.0*rand()-RAND_MAX)/RAND_MAX * 0.5;	//add a random between -0.1 to +0.1
    			//Noeud[elem].vy += (2.0*rand()-RAND_MAX)/RAND_MAX * 0.5;
    			//Noeud[elem].vz += (2.0*rand()-RAND_MAX)/RAND_MAX * 0.5;
    			//printf("node %d water speed %lf %lf %lf\n",elem,Noeud[elem].vx,Noeud[elem].vy,Noeud[elem].vz);
   			}
    		//printf("RAND_MAX %d\n",RAND_MAX);
    		fclose(f1);
    		//exit(0);
    		return 1;
  		}
	}	


