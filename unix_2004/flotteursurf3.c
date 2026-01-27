#define PRINCIPAL 0
#include "4c19.h"

void flotteursurf3()
	{
	
	/*
	prise en compte des efforts de flottabilite des fils ; on considere la longueur au repos des fils 
	et non pas la longueur apres tension 
	*/
	
	int elem,zh,zi,zj;
	double f_u,f_v,f_l,f_m,f_n;
	
	/* 
	f_u est la flottabilite pour un cote de maille selon u.
	f_v est la flottabilite pour un cote de maille selon v.
	ces 2 flottabilites sont egales
	*/
	   
	for (elem = 1 ; elem <= NOMBRE_SURFACES; elem++)
		{
		zh = yc(elem,3);  
		zi = yc(elem,6);  
		zj = yc(elem,9);
		
   	       	/*fils inondes*/
              	/* 
              	Des que la cote d'un sommet d'un triangle est <=0, on calcule la flottabilite sur tous les fils 
                de ce triangle...  
                */
 
   			f_u = RHO * G * PI * Surface[elem].diametrehydro * Surface[elem].diametrehydro * Surface[elem].lgrepos / 4.0;
   			f_v = RHO * G * PI * Surface[elem].diametrehydro * Surface[elem].diametrehydro * Surface[elem].lgrepos / 4.0;

        		wasurf[zh] += ( f_u + f_v ) * Surface[elem].nb_cote_u_ou_v/3.0;
        		wasurf[zi] += ( f_u + f_v ) * Surface[elem].nb_cote_u_ou_v/3.0;
        		wasurf[zj] += ( f_u + f_v ) * Surface[elem].nb_cote_u_ou_v/3.0;
   		/*if(wf[zh] <= 0.0 || wf[zi] <= 0.0 || wf[zj] <= 0.0 )
   		{
        	}*/
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
		
   	       	/*fils inondes*/
              	/* 
              	Des que la cote d'un sommet d'un triangle est <=0, on calcule la flottabilite sur tous les fils 
                de ce triangle...  
                */
 
   		if(wf[zh] <= 0.0 || wf[zi] <= 0.0 || wf[zj] <= 0.0 )
   			{
   			f_l = RHO * G * PI * Surf_Hexa[elem].diam_hydro_l * Surf_Hexa[elem].diam_hydro_l * Surf_Hexa[elem].lo_repos / 4.0;
   			f_m = RHO * G * PI * Surf_Hexa[elem].diam_hydro_m * Surf_Hexa[elem].diam_hydro_m * Surf_Hexa[elem].mo_repos / 4.0;
   			f_n = RHO * G * PI * Surf_Hexa[elem].diam_hydro_n * Surf_Hexa[elem].diam_hydro_n * Surf_Hexa[elem].no_repos / 4.0;

        		wasurf[zh] += (f_l + f_m + f_n) * Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0 ;
        		wasurf[zi] += (f_l + f_m + f_n) * Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0 ; 
        		wasurf[zj] += (f_l + f_m + f_n) * Surf_Hexa[elem].nb_cote_l_m_ou_n/3.0 ; 
  			}
        	}
        
	}
	
