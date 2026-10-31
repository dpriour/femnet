#define PRINCIPAL 0
#include "4c19.h"

void raideur_coulisses()
	{
	/* Calcul des efforts en chaque noeud issus de la tension des coulisses*/
  	int zi,zj,noeud1,noeud2,noeud3,zk,zl,zm,coord1,coord2;
  	double dx,dy,dz,delta,raideur[130][130],rai;
  	double wt_ref[DIM1],wt_modi[DIM1];
  	
  	/*for (zi = 1 ; zi<= 129 ; zi++)
  		{
    		for (zj = 1 ; zj<= 129; zj++) 
    			{
			raideur[zi][zj] = 0;
			}
		}*/

  	/*delta est le delta x qui permet de calculer la derivee d effort par difference finie*/
    	delta = 0.00011;	/*delta est exprime en metre*/
  	/*prise en compte de la tension*/
  	for (zi = 1 ; zi<= NOMBRE_COULISSES ; zi++)
  		{
  		/*calcul de la longueur tendue*/
      		Coulisse[zi].lgtendue = 0.0;
    		for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    			{
    			if (zj == 1) noeud1 = Coulisse[zi].extremite[1];
    			if (zj != 1) noeud1 = Coulisse[zi].noeud[zj-1];
    			if (zj != Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].noeud[zj];
    			if (zj == Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].extremite[2];
    			dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    			dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    			dz = wf[3*noeud1-0]-wf[3*noeud2-0];
    			Coulisse[zi].longueur[zj] = sqrt(dx*dx + dy*dy + dz*dz);
    			Coulisse[zi].lgtendue += Coulisse[zi].longueur[zj];
    			}
    		/*si la coulisse est trop detendue on limite sa longueur a 0.01 sa longueur au repos*/
    		if (Coulisse[zi].lgtendue < 0.01 * Coulisse[zi].lgrepos)	Coulisse[zi].lgtendue = 0.01 * Coulisse[zi].lgrepos;
    
    		if (Coulisse[zi].lgtendue <  Coulisse[zi].lgrepos)	Coulisse[zi].raideur_effective = Coulisse[zi].raideur_compression;
      		else							Coulisse[zi].raideur_effective = Coulisse[zi].raideur_traction;         
    
    		/* Coulisse[zi].raideur_effective = le module d'elasticite* section associe l'element(ie la coulisse)
       		Coulisse[zi].wt est la tension dans la coulisse zi : > 0 en traction, < 0 en compression*/
    		Coulisse[zi].wt = (Coulisse[zi].lgtendue-Coulisse[zi].lgrepos) * Coulisse[zi].raideur_effective / Coulisse[zi].lgrepos ;

  		/*mise a zero des efforts de reference aux noeuds*/
    		for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    			{
    			if (zj == 1) noeud1 = Coulisse[zi].extremite[1];
    			if (zj != 1) noeud1 = Coulisse[zi].noeud[zj-1];
    			if (zj != Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].noeud[zj];
    			if (zj == Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].extremite[2];
    			wt_ref[3*noeud1-2] = 0.0;	wt_ref[3*noeud1-1] = 0.0;	wt_ref[3*noeud1-0] = 0.0;
    			wt_ref[3*noeud2-2] = 0.0;	wt_ref[3*noeud2-1] = 0.0;	wt_ref[3*noeud2-0] = 0.0;
    			}
    		
  		/*calcul des efforts de ref aux noeuds*/
    		for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    			{
    			if (zj == 1) 				noeud1 = Coulisse[zi].extremite[1];
    			if (zj != 1) 				noeud1 = Coulisse[zi].noeud[zj-1];
    			if (zj != Coulisse[zi].nb_noeud + 1) 	noeud2 = Coulisse[zi].noeud[zj];
    			if (zj == Coulisse[zi].nb_noeud + 1) 	noeud2 = Coulisse[zi].extremite[2];
    			dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    			dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    			dz = wf[3*noeud1-0]-wf[3*noeud2-0];
    			wt_ref[3*noeud1-2] -= dx/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			wt_ref[3*noeud1-1] -= dy/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			wt_ref[3*noeud1-0] -= dz/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			wt_ref[3*noeud2-2] += dx/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			wt_ref[3*noeud2-1] += dy/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			wt_ref[3*noeud2-0] += dz/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			}
  		}

  	/*prise en compte de la raideur*/
  	for (zi = 1 ; zi<= NOMBRE_COULISSES ; zi++)
  		{
  		/*calcul des raideurs par difference finies aux noeuds*/
    		for (zk = 1 ; zk<= Coulisse[zi].nb_noeud + 2; zk++) 
    			{
    			/*noeud3 est le numero du noeud que l on traite*/
    			if (zk == 1) 						noeud3 = Coulisse[zi].extremite[1];
    			if ((zk != 1) && (zk != Coulisse[zi].nb_noeud + 2)) 	noeud3 = Coulisse[zi].noeud[zk-1];
    			if (zk == Coulisse[zi].nb_noeud + 2) 			noeud3 = Coulisse[zi].extremite[2];
    			
    			/*modification d une coordonnee en commencant par la coordonnee x*/
    			for (zl = 1 ; zl<= 3; zl++) 
    				{
    				/*ajout d une longueur delta a cette coordonnee*/
    				coord1 = 3*noeud3+zl-3;
    				
    				wf[coord1] += delta;	/*coordonnee augmentee de delta*/
    				
  				/*calcul de la longueur tendue qui resulte de cette augmentation*/
      				Coulisse[zi].lgtendue = 0.0;
    				for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    					{
    					if (zj == 1) 				noeud1 = Coulisse[zi].extremite[1];
    					if (zj != 1) 				noeud1 = Coulisse[zi].noeud[zj-1];
    					if (zj != Coulisse[zi].nb_noeud + 1) 	noeud2 = Coulisse[zi].noeud[zj];
    					if (zj == Coulisse[zi].nb_noeud + 1) 	noeud2 = Coulisse[zi].extremite[2];
    					dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    					dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    					dz = wf[3*noeud1-0]-wf[3*noeud2-0];
    					Coulisse[zi].longueur[zj] = sqrt(dx*dx + dy*dy + dz*dz);
    					Coulisse[zi].lgtendue += Coulisse[zi].longueur[zj];
    					}
   			
    				/*si la coulisse est trop detendue on limite sa longueur a 0.01 sa longueur au repos*/
    				if (Coulisse[zi].lgtendue < 0.01 * Coulisse[zi].lgrepos)	Coulisse[zi].lgtendue = 0.01 * Coulisse[zi].lgrepos;
    				if (Coulisse[zi].lgtendue <  Coulisse[zi].lgrepos)	Coulisse[zi].raideur_effective = Coulisse[zi].raideur_compression;
      				else							Coulisse[zi].raideur_effective = Coulisse[zi].raideur_traction;         

    				/* Coulisse[zi].raideur_effective = le module d'elasticite* section associe l'element(ie la coulisse)
       				Coulisse[zi].wt est la tension dans la coulisse zi : > 0 en traction, < 0 en compression*/
    				Coulisse[zi].wt = (Coulisse[zi].lgtendue-Coulisse[zi].lgrepos) * Coulisse[zi].raideur_effective / Coulisse[zi].lgrepos ;
    		
  				/*mise a zero des efforts modifies aux noeuds par barres de coulisse*/
    				for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    					{
    					if (zj == 1) noeud1 = Coulisse[zi].extremite[1];
    					if (zj != 1) noeud1 = Coulisse[zi].noeud[zj-1];
    					if (zj != Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].noeud[zj];
    					if (zj == Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].extremite[2];
    					wt_modi[3*noeud1-2] = 0.0;wt_modi[3*noeud1-1] = 0.0;wt_modi[3*noeud1-0] = 0.0;
    					wt_modi[3*noeud2-2] = 0.0;wt_modi[3*noeud2-1] = 0.0;wt_modi[3*noeud2-0] = 0.0;
    					}
    		
  				/*calcul des efforts modifies aux noeuds par barres de coulisse*/
    				for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    					{
    					if (zj == 1) noeud1 = Coulisse[zi].extremite[1];
    					if (zj != 1) noeud1 = Coulisse[zi].noeud[zj-1];
    					if (zj != Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].noeud[zj];
    					if (zj == Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].extremite[2];
 					/*printf("zj = %5d noeud1 = %5d noeud2 = %5d \n",zj,noeud1,noeud2);*/
    					dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    					dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    					dz = wf[3*noeud1-0]-wf[3*noeud2-0];
    					wt_modi[3*noeud1-2] -= dx/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    					wt_modi[3*noeud1-1] -= dy/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    					wt_modi[3*noeud1-0] -= dz/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    					wt_modi[3*noeud2-2] += dx/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    					wt_modi[3*noeud2-1] += dy/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    					wt_modi[3*noeud2-0] += dz/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    					}
  	
				if (Structure.type_solver == 1)
				{
	  				/*calcul des raideurs par difference finies aux noeuds*/
	    				for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 2; zj++) 
    					{
	    					if (zj == 1) 						noeud2 = Coulisse[zi].extremite[1];
	    					if ((zj != 1) && (zj != Coulisse[zi].nb_noeud + 2)) 	noeud2 = Coulisse[zi].noeud[zj-1];
	    					if (zj == Coulisse[zi].nb_noeud + 2) 			noeud2 = Coulisse[zi].extremite[2];
	    					/*coordonnee modifiee en commencant par la coordonnee x puis y et ensuite z*/
	    					for (zm = 1 ; zm<= 3; zm++) 
    						{
	    						/*ajout d un millimetre a cette coordonnee*/
	    						coord2 = 3*noeud2+zm-3;
	    						/*raideur[coord2][coord1] += -(wt_modi[coord2] - wt_ref[coord2]) / delta;*/
	    						ze[coord2][eca-coord2+coord1] -= (wt_modi[coord2] - wt_ref[coord2]) / delta;
	    						
	       						if (rang[1][coord2] < coord1) rang[1][coord2] = coord1; /*borne basse  de la raideur ze*/
	       						if (rang[2][coord2] < coord1) rang[2][coord2] = coord1; /*borne droite de la raideur ze*/
	       						if (rang[3][coord2] > coord1) rang[3][coord2] = coord1; /*borne haute  de la raideur ze*/
	       						if (rang[4][coord2] > coord1) rang[4][coord2] = coord1; /*borne gauche de la raideur ze*/
	       				
	       						if (rang[1][coord1] < coord2) rang[1][coord1] = coord2; /*borne basse  de la raideur ze*/
	       						if (rang[2][coord1] < coord2) rang[2][coord1] = coord2; /*borne droite de la raideur ze*/
	       						if (rang[3][coord1] > coord2) rang[3][coord1] = coord2; /*borne haute  de la raideur ze*/
	       						if (rang[4][coord1] > coord2) rang[4][coord1] = coord2; /*borne gauche de la raideur ze*/
   						}
    					}
				}
				else if (Structure.type_solver == 2)
      				{
	    				for (zj = 0 ; zj< Coulisse[zi].nb_noeud + 2; zj++) 
    					{
	    					if (zj == 1) 						noeud2 = Coulisse[zi].extremite[1];
	    					if ((zj != 1) && (zj != Coulisse[zi].nb_noeud + 2)) 	noeud2 = Coulisse[zi].noeud[zj-1];
	    					if (zj == Coulisse[zi].nb_noeud + 2) 			noeud2 = Coulisse[zi].extremite[2];
	    					for (zm = 1 ; zm<= 3; zm++) 
    						{
	    						coord2 = 3*noeud2+zm-3;
							affectation_pardiso(-(wt_modi[coord2] - wt_ref[coord2]) / delta, coord2, coord1);
	    						
	       						if (rang[1][coord2] < coord1) rang[1][coord2] = coord1; /*borne basse  de la raideur ze*/
	       						if (rang[2][coord2] < coord1) rang[2][coord2] = coord1; /*borne droite de la raideur ze*/
	       						if (rang[3][coord2] > coord1) rang[3][coord2] = coord1; /*borne haute  de la raideur ze*/
	       						if (rang[4][coord2] > coord1) rang[4][coord2] = coord1; /*borne gauche de la raideur ze*/
	       				
	       						if (rang[1][coord1] < coord2) rang[1][coord1] = coord2; /*borne basse  de la raideur ze*/
	       						if (rang[2][coord1] < coord2) rang[2][coord1] = coord2; /*borne droite de la raideur ze*/
	       						if (rang[3][coord1] > coord2) rang[3][coord1] = coord2; /*borne haute  de la raideur ze*/
	       						if (rang[4][coord1] > coord2) rang[4][coord1] = coord2; /*borne gauche de la raideur ze*/
						}
					}
      				}

    				wf[coord1] -= delta;
    				}
    			}
  		}
	}

