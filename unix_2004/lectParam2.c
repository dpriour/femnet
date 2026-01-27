#define PRINCIPAL 0
#include <unistd.h>
#include "4c19.h"

int lectParam2(char *nomfichier)
	{
  	char tonom[1000],CWD[256];
  	FILE *f1;
  	int itmp,j;

  	/*strcpy(tonom,"/home/alre/surface/unix97/param.txt");*/
  	if (Structure.convergence_parameters == 0)  	
  		{
		if (getcwd(CWD, sizeof(CWD)) == NULL)
			{
			perror("getcwd() error in lectParam2.c");
			}
		else
			{
			//printf("Current directory: %s\n", CWD);
			strcpy(tonom,CWD);
		  	strcat(tonom,"/param.txt");	
    			//printf("%s %s %s \n","file ",tonom," exists");
			}
  		//strcpy(tonom,"/home/daniel/femnet/unix_2004/param.txt");
  		}
  	if (Structure.convergence_parameters == 1)
  		{
	  	strcpy(tonom,nomfichier);
		j=strlen(tonom);
		while ((tonom[j])!='.' && j>0) j--;
		if (tonom[j]=='.') tonom[j]=0;
	  	strcat(tonom,".par");
  		}

  	f1 = fopen(tonom,"r");
  	if (f1 == NULL) 
  		{
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom," don't exist ?");
    		//printf("Create the file param.txt in the current folder (~/hexa/unix_2004/)\n");
			strcpy(tonom,CWD);
    		printf("Create the file param.txt in the current folder (%s)\n",tonom);
    		printf("This file has a real on the first line\n");
    		printf("This file has an integer on the second line\n");
    		printf("This file has a real on the third line\n");
    		printf("The first real is between 0 and 1, prefer 1\n"); 
    		printf("It is the proportion of the calculated displacement applied on coordinates\n");
    		printf("The integer is the period of display on screen: must be > 0 \n");
    		printf("The second real is the additional stiffness (N): it is the force required to get 1m of displacement\n"); 
    		printf("Begin with a large value (e+6) and gently decrease (up to e+1)\n");
    		exit(0);
  		} 
  	itmp = fscanf(f1,"%lf",&Relaxation); 		/* terme de relaxation du mouvement. En general =1 donc ne chamge rien!*/
  	itmp = fscanf(f1,"%d",&Periodeimpression);	/*  periode d'affichage a l'ecran de certains renseignements */
  	itmp = fscanf(f1,"%lf",&Numtemps ); 		/* Numtemps : le terme qui l'on ajoute a la diagonale de la matrice de raideur*/
    	//printf("Numtemps = %lf \n",Numtemps);
  	Numtemps = Numtemps * Numtemps_relax;
    	//printf("Numtemps = %lf \n",Numtemps);
    	//exit(0);
  	/*itmp = fscanf(f1,"%lf",&deltat );  deltat : increment de temps pour une iteration avec lequel on calcul une raideur
  	additionnelle*/
  	fclose(f1);
 	
    	/*printf("nbiter = %d MW = %lf Deplacement = %lf\n",nbiter,MW,Deplacement);
  	if (nbiter > 1)
  		{
  		if (fabs(MW) > Deplacement)
  			{
  			deltat = deltat * Deplacement / fabs(MW);
    			printf("> deltat = %lf \n",deltat);
  			}
  		if (fabs(MW) <  Deplacement / 1000.0)
  			{
  			deltat = deltat * Deplacement / fabs(MW);
    			printf("< deltat = %lf \n",deltat);
  			}
  		}
  	*/
  	
  	return 0;
	}	


