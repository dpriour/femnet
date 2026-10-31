#define PRINCIPAL 0
#include "4c19.h"

double effortmean()
/* Calcul de l effort moyen sur toutes les coordonnees des noeuds*/
	{
	int zi;
	double Rx,RR;

	Rx = 0.0;
	for (zi = 1; zi<= NOMBRE_NOEUDS; zi++)
		{
		Rx += sqrt(wa[3*zi-2]*wa[3*zi-2] + wa[3*zi-1]*wa[3*zi-1] + wa[3*zi-0]*wa[3*zi-0]);
		}
	RR = Rx / (double) NOMBRE_NOEUDS;

	if (Structure.mean_XYZ_desequilibrium == 1)
		{
		mean_desequilibrium_X = 0.0;
		mean_desequilibrium_Y = 0.0;
		mean_desequilibrium_Z = 0.0;
		for (zi = 1; zi<= NOMBRE_NOEUDS; zi++)
			{
			mean_desequilibrium_X += wa[3*zi-2];
			mean_desequilibrium_Y += wa[3*zi-1];
			mean_desequilibrium_Z += wa[3*zi-0];
			}
		mean_desequilibrium_X = mean_desequilibrium_X / (double) NOMBRE_NOEUDS;
		mean_desequilibrium_Y = mean_desequilibrium_Y / (double) NOMBRE_NOEUDS;
		mean_desequilibrium_Z = mean_desequilibrium_Z / (double) NOMBRE_NOEUDS;
		/*
		printf("mean_desequilibrium_X %lf \nmean_desequilibrium_Y %lf \nmean_desequilibrium_Z %lf \n ",mean_desequilibrium_X,mean_desequilibrium_Y,mean_desequilibrium_Z);
		exit(0);
		*/
		}

	return RR;
	}


