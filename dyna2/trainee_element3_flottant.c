#include "4c19.h"

void trainee_element3_flottant()
	{
  	/* 
  	Calcul de l'effort hydrodynamique de trainee exerce sur chaque element lie au courant 
  	mais aussi a la vitesse des extremites de l element
    	L'effort tangentiel se decompose selon T1, T2 et T3 suivant les 3 axes X, Y et Z. 
    	L'effort normal     se decompose selon N1, N2 et N3 suivant les 3 axes X, Y et Z. 
    	Ces composantes sont calculees et reparties sur chaque extremite 1 et 2 de l'element. 
    	mais pour autant waelem[zi] != waelem[zh] ou zh et zi sont les 2 extremites de l'element. 
    	On ne calcule pas les termes de la matrice de raideur issus de ces efforts
    	(c'est a dire l'oppose des derivees) car ils sont negligeables par rapport
    	a ceux deja calcules avec l elasticite des elements.
    	Ici les efforts tiennent compte de la proximité de la surface libre : un cube centré sur les extremités dont le volume
    	est 1/2 du volume de la barre; la ponderation est la proportion de ce cube immerge
    	*/
  
     	int zg,zh,zi;
  	double ba[4],V[4],nt[4];
  	double drag_tmp[4],depl_tmp[4];
  	
   	for (zg = 1 ; zg<= NOMBRE_ELEMENTS ; zg++) 
		{  			 	      			
		/*numero des coordonnees selon x des 2 extremites de cet element*/
    		zh = yb(zg,1);
    		zi = yb(zg,4);
    		
    		//zh extremite 1
		/* Definition du vecteur courant grace au fichier .mdf */
	     	V[1] = mvh[zh+0]-mvb[zh+0];
	     	V[2] = mvh[zh+1]-mvb[zh+1];
	     	V[3] = mvh[zh+2]-mvb[zh+2];
 
		ba[1] = wf[zi+0] - wf[zh+0];		//composante x de la barre	
		ba[2] = wf[zi+1] - wf[zh+1];		//composante y de la barre		
		ba[3] = wf[zi+2] - wf[zh+2];		//composante z de la barre		
		//printf("tra38 mvh %5.2lf %5.2lf %5.2lf mvb  %15.0lf %15.0lf %15.0lf ",mvh[zh+0],mvh[zh+1],mvh[zh+2],mvb[zh+0],mvb[zh+1],mvb[zh+2]);
		//printf("tra38 ba %5.2lf %5.2lf %5.2lf V  %15.0lf %15.0lf %15.0lf\n",ba[1],ba[2],ba[3],V[1],V[2],V[3]);
		basic_bar_drag1(Element[zg].diametrehydro, Element[zg].lgrepos, Element[zg].cdnormal, Element[zg].ftangent, ba, V, nt);
		//printf("nt2=   ");	imprvectreel(3, nt);

		NT[1]=nt[1]/2.0*Element[zg].pondFS[1];	//uniquement la moitie de la trainee totale de la barre sur l extremité 1
		NT[2]=nt[2]/2.0*Element[zg].pondFS[1];
		NT[3]=nt[3]/2.0*Element[zg].pondFS[1];

		//effort_trainee_elem_flottant2(zg,zh,zi,V,nt);	//drag and lift without ponderation
		//NT[1]=nt[1]*Element[zg].pondFS[1];
		//NT[2]=nt[2]*Element[zg].pondFS[1];
		//NT[3]=nt[3]*Element[zg].pondFS[1];
		
    		//zi extremite 2
		/* Definition du vecteur courant grace au fichier .mdf */
	     	V[1] = mvh[zi+0]-mvb[zi+0];
	     	V[2] = mvh[zi+1]-mvb[zi+1];
	     	V[3] = mvh[zi+2]-mvb[zi+2];
 
		ba[1] = wf[zi+0] - wf[zh+0];		//composante x de la barre	
		ba[2] = wf[zi+1] - wf[zh+1];		//composante y de la barre		
		ba[3] = wf[zi+2] - wf[zh+2];		//composante z de la barre		
		//printf("tra60 mvh %5.2lf %5.2lf %5.2lf mvb  %15.0lf %15.0lf %15.0lf ",mvh[zi+0],mvh[zi+1],mvh[zi+2],mvb[zi+0],mvb[zi+1],mvb[zi+2]);
		//printf("tra60 ba %5.2lf %5.2lf %5.2lf V  %15.0lf %15.0lf %15.0lf\n",ba[1],ba[2],ba[3],V[1],V[2],V[3]);
		basic_bar_drag1(Element[zg].diametrehydro, Element[zg].lgrepos, Element[zg].cdnormal, Element[zg].ftangent, ba, V, nt);
		//printf("nt2=   ");	imprvectreel(3, nt);

		NT[4]=nt[1]/2.0*Element[zg].pondFS[2];	//uniquement la moitie de la trainee totale de la barre sur l extremité 2
		NT[5]=nt[2]/2.0*Element[zg].pondFS[2];
		NT[6]=nt[3]/2.0*Element[zg].pondFS[2];

		//effort_trainee_elem_flottant2(zg,zi,zh,V,nt);	//drag and lift without ponderation
		//NT[4]=nt[1]*Element[zg].pondFS[2];
		//NT[5]=nt[2]*Element[zg].pondFS[2];
		//NT[6]=nt[3]*Element[zg].pondFS[2];

    		waelem[zh  ] += NT[1] ;	waelem[zh+1] += NT[2] ;	waelem[zh+2] += NT[3] ;
    		waelem[zi  ] += NT[4] ;	waelem[zi+1] += NT[5] ;	waelem[zi+2] += NT[6] ;
     			
    		drag_tmp[1] = NT[1] ;	drag_tmp[2] = NT[2] ;	drag_tmp[3] = NT[3] ; 	//drag (N) first extremity
    		depl_tmp[1] = wf[zh  ] -  wf1[zh  ];	depl_tmp[2] = wf[zh+1] -  wf1[zh+1];	depl_tmp[3] = wf[zh+2] -  wf1[zh+2];	//deplacement (m)	 first extremity
    		Structure.element_energy -= produit_scal(drag_tmp,depl_tmp);	//add the energy on the first extremity
    		drag_tmp[1] = NT[4] ;	drag_tmp[2] = NT[5] ;	drag_tmp[3] = NT[6] ;//drag (N)
    		depl_tmp[1] = wf[zi  ] -  wf1[zi  ];	depl_tmp[2] = wf[zi+1] -  wf1[zi+1];	depl_tmp[3] = wf[zi+2] -  wf1[zi+2];	//deplacement (m)	
    		Structure.element_energy -= produit_scal(drag_tmp,depl_tmp);	//add the energy on the second extremity
    		Structure.element_power = Structure.element_energy/Pascalcul;
		}
	}
	
	

