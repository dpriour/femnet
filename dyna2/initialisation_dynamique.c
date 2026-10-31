#include "4c19.h"

void initialisation_dynamique(char *nomfichier)
	{
  	int zi,no,itmp,node,component,temp_int;
  	FILE   *f2;
  	char c,tonom[1000];;
  
 	/* wf1 : vecteur contenant les coordonnes des noeuds au temps t-1*/
 	/* wf2 : vecteur contenant les coordonnes des noeuds au temps t-2*/
 	/* mvb : vecteur contenant les vitesses des coordonnes des noeuds au temps t*/
 	/* mvb1 : vecteur contenant les vitesses des coordonnes des noeuds au temps t-1*/
 	/* mgb : vecteur contenant les accelerations des coordonnes des noeuds au temps t*/
   	for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS; zi++) 
  		{
    		wf1[zi]   = wf[zi];
    		mvb[zi]   = 0.0;
    		mvb1[zi]  = 0.0;
    		mgb[zi]   = 0.0;
  		}
 	for (zi = 1 ; zi<= Ball.nb; zi++) 
		{
		no = Ball.noeud[zi];
		mvb[3*no-2] = Ball.ini_speed_x[zi];
		mvb[3*no-1] = Ball.ini_speed_y[zi];
		mvb[3*no-0] = Ball.ini_speed_z[zi];
		mvb1[3*no-2] = Ball.ini_speed_x[zi];
		mvb1[3*no-1] = Ball.ini_speed_y[zi];
		mvb1[3*no-0] = Ball.ini_speed_z[zi];
    		wf1[3*no-2]   = wf[3*no-2] - Ball.ini_speed_x[zi] * Pascalcul;
    		wf1[3*no-1]   = wf[3*no-1] - Ball.ini_speed_y[zi] * Pascalcul;
    		wf1[3*no-0]   = wf[3*no-0] - Ball.ini_speed_z[zi] * Pascalcul;
 		}	
	if (Energy_bottom.step > 0.0)
		{
		Energy_bottom.nb_square = 0;
		Energy_bottom.nbx =	(int *) Malloc_int(1 + Energy_bottom.nb_square);
		Energy_bottom.nby =	(int *) Malloc_int(1 + Energy_bottom.nb_square);
		Energy_bottom.nrj =	(double *) Malloc_double(1 + Energy_bottom.nb_square);
		}
  	if(Sortie_texte.effort_structure == 1)
		{
  		/*Copy the 3 first lines of efg file (forces on structures) and remove the following if any, in case
  		of a dynamic calculation has already been done*/
   		
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".efg");	
	  	f2 = fopen(tonom,"r");
	    	do  c=fgetc(f2); while (c !=':'); 
	    	itmp = fscanf(f2,"%d\n",&temp_int);
		printf("temp_int  %4d is the nb of stored forces  \n",temp_int );
		printf("Structure.nb_fixed_components  %4d   \n", Structure.nb_fixed_components);
	    	do  c=fgetc(f2); while (c !=':'); 

		for ( zi = 1 ; zi <= Structure.nb_fixed_components ; zi++ )
	     	{ 
	    		itmp = fscanf(f2,"%lf",&wanoeud[zi]);
			//stockage of the static forces in wanoeud momentarily
			//printf("zi %4d force %lf  \n",zi,wanoeud[zi]);
		}
		fclose(f2);


		strcpy(tonom,nomfichier);
	  	strcat(tonom,".efg");	
	  	f2 = fopen(tonom,"w");
	    	fprintf(f2,"nb of fixed components: %d n(node) a(axe)\n",Structure.nb_fixed_components);
	    	fprintf(f2,"  times (s)");
		for ( zi = 1 ; zi <= Structure.nb_fixed_components ; zi++ )
		     	{ 
	    		fprintf(f2,"  n%5d ",Structure.list_fixed_node[zi] );
	    		fprintf(f2,"a %1d ",Structure.list_fixed_axe[zi] );
	    		}
	    	fprintf(f2,"\n");
	    	fprintf(f2,"static_forc:");
	     	for ( zi = 1 ; zi <= Structure.nb_fixed_components ; zi++ )
	     	{ 
	     		node = fixa[Structure.list_fixed_node[zi]];
	     		component = 3 * node + Structure.list_fixed_axe[zi] - 3;
			fprintf(f2," %10.2lf  ",wanoeud[zi]);
		}
		fprintf(f2,"\n");
		fclose(f2);
	    	}
	}


