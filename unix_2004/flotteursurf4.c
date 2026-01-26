#define PRINCIPAL 0
#include "4c19.h"

void flotteursurf4()
	{
	
	/*
	prise en compte des efforts de flottabilite des fils ; on considere la longueur au repos des fils 
	et non pas la longueur apres tension 
	*/
	
	int elem,zh,zi,zj;
	double fuv,f_l,f_m,f_n;
	
	/* 
	fuv est la flottabilite de tous les fils par sommet: la flottabilité totale = 3 * fuv
	*/
	   
	for (elem = 1 ; elem <= NOMBRE_SURFACES; elem++)
		{
		zh = yc(elem,3);  //no de la coordonee z du sommet 1
		zi = yc(elem,6);  
		zj = yc(elem,9);

		fuv = RHO * G * Surface[elem].lcube * Surface[elem].lcube * Surface[elem].lcube;	//flottabilité (N) par sommet si totalement inondé

		wasurf[zh] += fuv * Surface[elem].pondFS[1];
		wasurf[zi] += fuv * Surface[elem].pondFS[2];
		wasurf[zj] += fuv * Surface[elem].pondFS[3];
        }

	/* 
	f_l est la flottabilite pour un cote de maille selon l.
	f_m est la flottabilite pour un cote de maille selon m.
	f_n est la flottabilite pour un cote de maille selon n.
	*/
	
	for (elem = 1 ; elem <= NOMBRE_SURF_HEXA; elem++)
		{
		zh = yc_hexa(elem,3);  
		zi = yc_hexa(elem,6);  
		zj = yc_hexa(elem,9);
		
		//WARNING : n'a pas été fait comme pour les mailles losanges (lcube + 	pondFS)
		
		f_l = RHO * G * PI * Surf_Hexa[elem].diam_hydro_l * Surf_Hexa[elem].diam_hydro_l * Surf_Hexa[elem].lo_repos / 4.0;
		f_m = RHO * G * PI * Surf_Hexa[elem].diam_hydro_m * Surf_Hexa[elem].diam_hydro_m * Surf_Hexa[elem].mo_repos / 4.0;
		f_n = RHO * G * PI * Surf_Hexa[elem].diam_hydro_n * Surf_Hexa[elem].diam_hydro_n * Surf_Hexa[elem].no_repos / 4.0;

		wasurf[zh] += (f_l + f_m + f_n) * Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0 ;
		wasurf[zi] += (f_l + f_m + f_n) * Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0 ; 
		wasurf[zj] += (f_l + f_m + f_n) * Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0 ; 
         	}
        
	}
	
