#include "4c19.h"

void trainee_noeud()
	{
	/*calcul de la trainee des noeuds en dynamique*/
	
  	int zi;
  	double modulevitesse,immersion,demirhovit,immer,v2;
  	
  	/*prise en compte de l imersion*/
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  		{
		v2=(mvb[3*zi-2]-mvh[3*zi-2])*(mvb[3*zi-2]-mvh[3*zi-2])
		  +(mvb[3*zi-1]-mvh[3*zi-1])*(mvb[3*zi-1]-mvh[3*zi-1])
		  +(mvb[3*zi-0]-mvh[3*zi-0])*(mvb[3*zi-0]-mvh[3*zi-0]);
		modulevitesse=sqrt(v2);
    		demirhovit = 0.5 * RHO * modulevitesse;


      			/* flotteur flottant */
    		if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] <= mh[3*zi]) && (wf[3*zi] + Noeud[zi].lonz >= mh[3*zi]))
    			{
      			immersion = mh[3*zi] - wf[3*zi];               /*immersion positive*/ 
			trainee_noeud_base(zi,Noeud[zi].lonx,Noeud[zi].lony,Noeud[zi].lonz,Noeud[zi].cdx,Noeud[zi].cdy,Noeud[zi].cdz,demirhovit,immersion);

    			}


      			/* flotteur inonde */
    		if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] + Noeud[zi].lonz < mh[3*zi]))
    			{
			immersion = Noeud[zi].lonz;
 			trainee_noeud_base(zi,Noeud[zi].lonx,Noeud[zi].lony,Noeud[zi].lonz,Noeud[zi].cdx,Noeud[zi].cdy,Noeud[zi].cdz,demirhovit,immersion);
    			}



      			/* flotteur exonde */
    		if ((Noeud[zi].lonz > 0.0) && (wf[3*zi] > mh[3*zi]))
    			{
    			}


    		if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] >= mh[3*zi]) && (wf[3*zi] + Noeud[zi].lonz <= mh[3*zi]))
    			{
      			/* lest flottant */
      			immersion = - Noeud[zi].lonz - wf[3*zi] + mh[3*zi];               /*immersion positive*/
 			trainee_noeud_base(zi,Noeud[zi].lonx,Noeud[zi].lony,Noeud[zi].lonz,Noeud[zi].cdx,Noeud[zi].cdy,Noeud[zi].cdz,demirhovit,immersion);
    			}
    		if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] < mh[3*zi]))
    			{
     	 		/* lest inonde */
 			immersion = - Noeud[zi].lonz;
			trainee_noeud_base(zi,Noeud[zi].lonx,Noeud[zi].lony,Noeud[zi].lonz,Noeud[zi].cdx,Noeud[zi].cdy,Noeud[zi].cdz,demirhovit,immersion);
    			}
    		if ((Noeud[zi].lonz < 0.0) && (wf[3*zi] + Noeud[zi].lonz > mh[3*zi]))
    			{
      			/* lest exonde */
    			}
  		}
	}

void trainee_noeud_base(int zi,double lonx,double lony,double lonz,double cdx,double cdy,double cdz,double demirhovit,double immersion)
{
	double immer;
  	double drag_tmp[4],depl_tmp[4];
	
	
  		if (lonz != 0.0) immer = pow((fabs(immersion/lonz)),0.4); else immer = 1.0; /*facteur correctif du passage de la SL*/
  		
		wanoeud[3*zi-2]      -= demirhovit*cdx*lony * immersion   *(mvb[3*zi-2]-mvh[3*zi-2]);
		wanoeud[3*zi-1]      -= demirhovit*cdy*lonx * immersion   *(mvb[3*zi-1]-mvh[3*zi-1]);
		wanoeud[3*zi-0]      -= demirhovit*cdz*lonx * lony*(mvb[3*zi-0]-mvh[3*zi-0])*immer;
		
		drag_tmp[1] = -demirhovit*cdx*lony * immersion   *(mvb[3*zi-2]-mvh[3*zi-2]);		drag_tmp[2] = -demirhovit*cdy*lonx * immersion   *(mvb[3*zi-1]-mvh[3*zi-1]);		drag_tmp[3] = -demirhovit*cdz*lonx * lony*(mvb[3*zi-0]-mvh[3*zi-0])*immer; 	//drag (N)
		depl_tmp[1] = wf[3*zi-2] - wf1[3*zi-2];	depl_tmp[2] = wf[3*zi-1] - wf1[3*zi-1];	depl_tmp[3] = wf[3*zi-0] - wf1[3*zi-0];	//deplacement (m)	
		Structure.node_energy -= produit_scal(drag_tmp,depl_tmp);
		Structure.node_power = Structure.node_energy/Pascalcul;
		
		

    		if (Structure.type_solver == 1)
		{
      			ze[3*zi-2][eca] += demirhovit*cdx*lony * immersion   /Pascalcul;
      			ze[3*zi-1][eca] += demirhovit*cdy*lonx * immersion   /Pascalcul;
      			ze[3*zi-0][eca] += demirhovit*cdz*lonx * lony/Pascalcul*immer;
	  	}
		else if (Structure.type_solver == 2)
		{
			//affectation_pardiso(demirhovit*cdx*lony * immersion   /Pascalcul, 3*zi-2, 3*zi-2);
			//affectation_pardiso(demirhovit*cdy*lonx * immersion   /Pascalcul, 3*zi-1, 3*zi-1);
			//affectation_pardiso(demirhovit*cdz*lonx * lony/Pascalcul*immer, 3*zi, 3*zi);
		}

}

