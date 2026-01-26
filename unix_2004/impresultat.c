#define PRINCIPAL 0
#include "4c19.h"

/*void impr_effort(int noe);
void impr_tension(int noe);
void impr_tension2(int noe, int nb_decim);
void impr_tension2_coulisse(int noe, int nb_decim);
void impr_position(int noe);
void impr_position2(int noe, int axe, int nb_decim);
void impr_distance(int noe1, int noe2);
void impr_effort2(int noe, int axe, int dec);
void impr_distance_brut2(int noe1, int noe2, int dec);*/

void impr_effort(int noe)
	{
	/*ecrit a l ecran les efforts sur le noeud numero noe*/
  	printf("Efforts sur le %4d   (N) : ", noe);
  	printf("%12.4lf %12.4lf %12.4lf \n",
  	wa[3*fixa[noe]-2]/1.0,wa[3*fixa[noe]-1]/1.0,wa[3*fixa[noe]-0]/1.0);
	}
	
void impr_effort2(int noe, int axe, int nb_decim)
	{
	/*ecrit a l ecran les efforts sur le noeud numero noe et selon laxe axe et avec nb_decim decimale*/
  	if (nb_decim <= 0 ) printf("%12.0lf \n",wa[3*fixa[noe]-3+axe]);
  	if (nb_decim == 1 ) printf("%12.1lf \n",wa[3*fixa[noe]-3+axe]);
  	if (nb_decim == 2 ) printf("%12.2lf \n",wa[3*fixa[noe]-3+axe]);
  	if (nb_decim == 3 ) printf("%12.3lf \n",wa[3*fixa[noe]-3+axe]);
  	if (nb_decim == 4 ) printf("%12.4lf \n",wa[3*fixa[noe]-3+axe]);
  	if (nb_decim == 5 ) printf("%12.5lf \n",wa[3*fixa[noe]-3+axe]);
  	if (nb_decim == 6 ) printf("%12.6lf \n",wa[3*fixa[noe]-3+axe]);
  	if (nb_decim == 7 ) printf("%12.7lf \n",wa[3*fixa[noe]-3+axe]);
  	if (nb_decim == 8 ) printf("%12.8lf \n",wa[3*fixa[noe]-3+axe]);
  	if (nb_decim >= 9 ) printf("%12.9lf \n",wa[3*fixa[noe]-3+axe]);
	}
	
void impr_tension(int noe)
	{
	/*ecrit a l ecran tension dans l element  numero noe*/
  	printf("Tension dans %4d     (N) : ", noe);
  	printf("%12.0lf \n",Element[noe].wt / 1.0);
	}
	
void impr_tension2(int noe, int nb_decim)
	{
	/*ecrit a l ecran tension dans l element  numero noe*/
  	if (nb_decim <= 0 ) printf("%12.0lf \n",Element[noe].wt);
  	if (nb_decim == 1 ) printf("%12.1lf \n",Element[noe].wt);
  	if (nb_decim == 2 ) printf("%12.2lf \n",Element[noe].wt);
  	if (nb_decim == 3 ) printf("%12.3lf \n",Element[noe].wt);
  	if (nb_decim == 4 ) printf("%12.4lf \n",Element[noe].wt);
  	if (nb_decim == 5 ) printf("%12.5lf \n",Element[noe].wt);
  	if (nb_decim == 6 ) printf("%12.6lf \n",Element[noe].wt);
  	if (nb_decim == 7 ) printf("%12.7lf \n",Element[noe].wt);
  	if (nb_decim == 8 ) printf("%12.8lf \n",Element[noe].wt);
  	if (nb_decim >= 9 ) printf("%12.9lf \n",Element[noe].wt);
	}
	
void impr_tension2_coulisse(int noe, int nb_decim)
	{
	/*ecrit a l ecran tension dans la coulisse  numero noe*/
  	if (nb_decim <= 0 ) printf("%12.0lf \n",Coulisse[noe].wt);
  	if (nb_decim == 1 ) printf("%12.1lf \n",Coulisse[noe].wt);
  	if (nb_decim == 2 ) printf("%12.2lf \n",Coulisse[noe].wt);
  	if (nb_decim == 3 ) printf("%12.3lf \n",Coulisse[noe].wt);
  	if (nb_decim == 4 ) printf("%12.4lf \n",Coulisse[noe].wt);
  	if (nb_decim == 5 ) printf("%12.5lf \n",Coulisse[noe].wt);
  	if (nb_decim == 6 ) printf("%12.6lf \n",Coulisse[noe].wt);
  	if (nb_decim == 7 ) printf("%12.7lf \n",Coulisse[noe].wt);
  	if (nb_decim == 8 ) printf("%12.8lf \n",Coulisse[noe].wt);
  	if (nb_decim >= 9 ) printf("%12.9lf \n",Coulisse[noe].wt);
	}
	
void impr_position(int noe)
	{
	/*ecrit a l ecran les position du noeud numero noe*/
  	printf("Position du %4d      (m) : " , noe);
  	printf("%12.2lf %12.2lf %12.2lf \n",
  	wf[3*fixa[noe]-2],wf[3*fixa[noe]-1],wf[3*fixa[noe]-0]);
	}
	
void impr_position2(int noe, int axe, int nb_decim)
	{
	/*ecrit a l ecran les position du noeud numero noe*/
  	if (nb_decim <= 0 ) printf("%12.0lf \n",wf[3*fixa[noe]-3+axe]);
  	if (nb_decim == 1 ) printf("%12.1lf \n",wf[3*fixa[noe]-3+axe]);
  	if (nb_decim == 2 ) printf("%12.2lf \n",wf[3*fixa[noe]-3+axe]);
  	if (nb_decim == 3 ) printf("%12.3lf \n",wf[3*fixa[noe]-3+axe]);
  	if (nb_decim == 4 ) printf("%12.4lf \n",wf[3*fixa[noe]-3+axe]);
  	if (nb_decim == 5 ) printf("%12.5lf \n",wf[3*fixa[noe]-3+axe]);
  	if (nb_decim == 6 ) printf("%12.6lf \n",wf[3*fixa[noe]-3+axe]);
  	if (nb_decim == 7 ) printf("%12.7lf \n",wf[3*fixa[noe]-3+axe]);
  	if (nb_decim == 8 ) printf("%12.8lf \n",wf[3*fixa[noe]-3+axe]);
  	if (nb_decim >= 9 ) printf("%12.9lf \n",wf[3*fixa[noe]-3+axe]);
	}
	
void impr_distance(int noe1, int noe2)
	{
	/*ecrit a l ecran la distance entre le noeud numero noe1 et noe2*/
	double dx,dy,dz,distance2,distance;
	
	dx = wf[3*fixa[noe2]-2] - wf[3*fixa[noe1]-2];
	dy = wf[3*fixa[noe2]-1] - wf[3*fixa[noe1]-1];
	dz = wf[3*fixa[noe2]-0] - wf[3*fixa[noe1]-0];
	distance2 = dx*dx + dy*dy + dz*dz;
	if (distance2 >= 0.0) 
		{
		distance = sqrt (distance2);
		}
	else
		{
		distance = 0.0;
		}
  	printf("Distance %4d au %4d (m) : " , noe1, noe2);
  	printf("%12.2lf \n",distance);
	}
	
void impr_distance_brut(int noe1, int noe2)
	{
	/*ecrit a l ecran la distance entre le noeud numero noe1 et noe2*/
	double dx,dy,dz,distance2,distance;
	
	/*
	printf("noe1 = %d  ",noe1);
	printf("noe2 = %d\n",noe2);
	printf("fixa[noe1] = %d  ",fixa[noe1]);
	printf("fixa[noe2] = %d\n",fixa[noe2]);
	*/
	
	dx = wf[3*fixa[noe2]-2] - wf[3*fixa[noe1]-2];
	dy = wf[3*fixa[noe2]-1] - wf[3*fixa[noe1]-1];
	dz = wf[3*fixa[noe2]-0] - wf[3*fixa[noe1]-0];
	distance2 = dx*dx + dy*dy + dz*dz;
  	/*printf("distance2 = %12.2lf \n",distance2);*/
	if (distance2 >= 0.0) 
		{
		distance = sqrt (distance2);
		}
	else
		{
		distance = 0.0;
		}
  	/*printf("Distance %4d au %4d (m) : " , noe1, noe2);*/
  	printf("%12.2lf \n",distance);
	}
	
void impr_distance_brut2(int noe1, int noe2, int nb_decim)
	{
	/*ecrit a l ecran la distance entre le noeud numero noe1 et noe2*/
	double dx,dy,dz,distance2,distance;
	
	/*
	printf("noe1 = %d  ",noe1);
	printf("noe2 = %d\n",noe2);
	printf("fixa[noe1] = %d  ",fixa[noe1]);
	printf("fixa[noe2] = %d\n",fixa[noe2]);
	*/
	
	dx = wf[3*fixa[noe2]-2] - wf[3*fixa[noe1]-2];
	dy = wf[3*fixa[noe2]-1] - wf[3*fixa[noe1]-1];
	dz = wf[3*fixa[noe2]-0] - wf[3*fixa[noe1]-0];
	distance2 = dx*dx + dy*dy + dz*dz;
  	/*printf("distance2 = %12.2lf \n",distance2);*/
	if (distance2 >= 0.0) 
		{
		distance = sqrt (distance2);
		}
	else
		{
		distance = 0.0;
		}
  	/*printf("Distance %4d au %4d (m) : " , noe1, noe2);*/
  	if (nb_decim <= 0 ) printf("%12.0lf \n",distance);
  	if (nb_decim == 1 ) printf("%12.1lf \n",distance);
  	if (nb_decim == 2 ) printf("%12.2lf \n",distance);
  	if (nb_decim == 3 ) printf("%12.3lf \n",distance);
  	if (nb_decim == 4 ) printf("%12.4lf \n",distance);
  	if (nb_decim == 5 ) printf("%12.5lf \n",distance);
  	if (nb_decim == 6 ) printf("%12.6lf \n",distance);
  	if (nb_decim == 7 ) printf("%12.7lf \n",distance);
  	if (nb_decim == 8 ) printf("%12.8lf \n",distance);
  	if (nb_decim >= 9 ) printf("%12.9lf \n",distance);
	}
