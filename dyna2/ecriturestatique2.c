#include "4c19.h"

int ecriturestatique2(char *nomfichier)
	{
  	char   tonom[1000];
  	FILE   *f3;
  	int    j,elem,pa,no,zi,el,int1,int2,int3,nb_recouv,nb_angles,zu,zv;
  	double elongation,surface_filtree,amplitude,effort;
	double dx,dy,dz,distance2,distance,longueur;
	/* debut modifdp du 5 mars 2010*/
	double VECT[4],dir[4];	
	/* fin modifdp du 5 mars 2010*/	
	double UU[4],VV[4],NUU,NVV,ps,alpha;

  	strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0;
  	strcat(tonom,".nrj");
  	printf(" \n");
  	printf("%s %s \n","fichier ",tonom);

  	f3 = fopen(tonom,"a");

	fprintf(f3,"\n");
	fprintf(f3,"Dynamic. Energy (J) spent in the bottom. Calculated by square. square side = %lf m. \n",Energy_bottom.step);
	fprintf(f3,"The position, of square is nbx*step (nbx+1)*step  nby*step (nby+1)*step  in m. \n");
	fprintf(f3,"nb_square = %d \n",Energy_bottom.nb_square);
	fprintf(f3,"     nbx     nby     energy\n");
	for (zi = 1; zi<= Energy_bottom.nb_square; zi++)
		{
		fprintf(f3,"%8d",Energy_bottom.nbx[zi]);
		fprintf(f3,"%8d",Energy_bottom.nby[zi]);
		fprintf(f3,"%17.9lf \n",Energy_bottom.nrj[zi]);
		}
		
  	fclose(f3);
  	}
 
int ecriturestatique3(char *nomfichier)
	{
  	char   tonom[1000];
  	FILE   *f3;
  	int    j,elem,pa,no,zi,el,int1,int2,int3,nb_recouv,nb_angles,zu,zv;
  	double elongation,surface_filtree,amplitude,effort;
	double dx,dy,dz,distance2,distance,longueur;
	/* debut modifdp du 5 mars 2010*/
	double VECT[4],dir[4];	
	/* fin modifdp du 5 mars 2010*/	
	double UU[4],VV[4],NUU,NVV,ps,alpha;

  	strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0;
  	strcat(tonom,".nrj");
  	//printf(" \n");
  	//printf("%s %s \n","fichier ",tonom);

  	f3 = fopen(tonom,"a");

	if(Sortie_texte.surface_filtree == 1)	fprintf(f3,"filtered_surface %5.0lf ",Structure.filtered_surface);
	fprintf(f3,"haul_power %5.0lf ",Structure.haul_power);
	fprintf(f3,"Bottom.power %5.0lf ",Bottom.power);
	fprintf(f3,"element_power %5.3lf ",Structure.element_power);
	fprintf(f3,"surface_power %5.0lf ",Structure.surface_power);
	fprintf(f3,"node_power %5.0lf ",Structure.node_power);
	if (Structure.boat_no > 0)
		{
		fprintf(f3,"boat_power %5.0lf ",Structure.boat_power);
		}

	fprintf(f3,"times / End %7.3lf / %7.3lf\n",times,Finstockage);
	
  	fclose(f3);
  	}
 

