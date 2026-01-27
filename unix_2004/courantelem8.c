#define PRINCIPAL 0
#include "4c19.h"  

void courantelem8()
{
  	/* 
  	Calcul de l'effort hydrodynamique exerce sur chaque element. 
     	*/
     	
     	int zg,zh,zi,zj,zk,pa,zl;
  	double ba[4],V[4],nt[4],ZZ1,vitesseM,directionM;
  	double lbt;
  	
	/*
	efforttraineeelem retourne 
	un vecteur ,note NT ,a 6 composantes contenant la somme des efforts normaux N1 et
	tangentiels T1 suivant x,y,z aux deux extremites de l'element.
	Cette procedure retourne aussi une matrice wg contenant 36 termes. C'est la matrice de
	raideur de l'element 
	*/
	Structure.element_drag = 0.0;
	for (zg = 1 ; zg<= NOMBRE_ELEMENTS ; zg++) 
	{  			 	      			
		//printf("zg %d \n",zg);
		/*numero des coordonnees selon x des 2 extremites de cet element*/
    		zh = yb(zg,1);
    		zi = yb(zg,4);
    		
		/* Definition du vecteur courant grace au fichier .mdf */
	     	V[1] = Courant.vitesse*cos(Courant.direction*PI/180);
	     	V[2] = Courant.vitesse*sin(Courant.direction*PI/180);
	     	V[3] = 0.0 ;

		if (TypeElement[zg].nb_tab_drag_lift == 0)	//drag non tabulee
			{
			//extremity 1
			if (Courant.nb_courant != 0)		//curent profile with depth
				{
				ZZ1 = wf[zh+2];			/*depth of this extremity*/
				for (zl = 1 ;zl <= Courant.nb_courant ;zl++ )
					{
					if (((ZZ1-Courant.depth1[zl])*(ZZ1-Courant.depth2[zl])) <= 0.0)
						{
						vitesseM   = Courant.courant1[zl]   +(ZZ1-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.courant2[zl]  -Courant.courant1[zl]);
						directionM = Courant.direction1[zl] +(ZZ1-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.direction2[zl]-Courant.direction1[zl]);
						V[1] = vitesseM*cos(directionM*PI/180.0);
						V[2] = vitesseM*sin(directionM*PI/180.0);
						V[3] = 0.0                              ;
						}
					}
			
				}
			//effort_trainee_elem_flottant2(zg,zh,zi,V,nt);	//drag and lift without ponderation

			//printf("nt1=   ");	imprvectreel(3, nt);
			ba[1] = wf[zi+0] - wf[zh+0];		//composante x de la barre	
			ba[2] = wf[zi+1] - wf[zh+1];		//composante y de la barre		
			ba[3] = wf[zi+2] - wf[zh+2];		//composante z de la barre		
			lbt = sqrt(produit_scal(ba,ba));			//bar length (m)
			//imprvectreel1(3, 3, ba);
			//printf("lbt %lf   \n",lbt);	
			//printf("zi %d   \n",zi);	
			//imprvectreel1(18, 3, wf);
			
			if (produit_scal(ba,ba) == 0.0)
				{
				printf("courantelem8 a\n");	
				printf("ba: %d ",zg);	
				imprvectreel1(3, 3, ba);
				printf("bar length %lf   \n",lbt);	
				printf("extremity zi %d: %lf %lf %lf\n",zi,wf[zi+0],wf[zi+1],wf[zi+2]);	
				printf("extremity zh %d: %lf %lf %lf\n",zh,wf[zh+0],wf[zh+1],wf[zh+2]);	
				//exit(0);
				}
			
			
			basic_bar_drag1(Element[zg].diametrehydro, Element[zg].lgrepos, Element[zg].cdnormal, Element[zg].ftangent, ba, V, nt);
			//printf("nt2=   ");	imprvectreel(3, nt);

			NT[1]=nt[1]/2.0*Element[zg].pondFS[1];	//uniquement la moitie de la trainee totale de la barre sur l extremité 1
			NT[2]=nt[2]/2.0*Element[zg].pondFS[1];
			NT[3]=nt[3]/2.0*Element[zg].pondFS[1];
			

			//extremity 2
			if (Courant.nb_courant != 0)		//curent profile with depth
				{
				ZZ1 = wf[zi+2];			/*depth of this extremity*/
				for (zl = 1 ;zl <= Courant.nb_courant ;zl++ )
					{
					if (((ZZ1-Courant.depth1[zl])*(ZZ1-Courant.depth2[zl])) <= 0.0)
						{
						vitesseM   = Courant.courant1[zl]   +(ZZ1-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.courant2[zl]  -Courant.courant1[zl]);
						directionM = Courant.direction1[zl] +(ZZ1-Courant.depth1[zl])/(Courant.depth2[zl]-Courant.depth1[zl])*(Courant.direction2[zl]-Courant.direction1[zl]);
						V[1] = vitesseM*cos(directionM*PI/180.0);
						V[2] = vitesseM*sin(directionM*PI/180.0);
						V[3] = 0.0                              ;
						}
					}
			
				}
			//effort_trainee_elem_flottant2(zg,zi,zh,V,nt);	//drag and lift without ponderation

			//printf("nt1=   ");	imprvectreel(3, nt);
			ba[1] = wf[zi+0] - wf[zh+0];		//composante x de la barre	
			ba[2] = wf[zi+1] - wf[zh+1];		//composante y de la barre		
			ba[3] = wf[zi+2] - wf[zh+2];		//composante z de la barre		
			lbt = sqrt(produit_scal(ba,ba));			//bar length (m)
			//imprvectreel1(3, 3, ba);
			//printf("lbt %lf   \n",lbt);	
			//printf("zj %d   \n",zi);	
			//imprvectreel1(18, 3, wf);
			if (produit_scal(ba,ba) == 0.0)
				{
				printf("courantelem8 b\n");	
				printf("ba: %d ",zg);	
				imprvectreel1(3, 3, ba);
				printf("bar length %lf   \n",lbt);	
				printf("extremity zi %d: %lf %lf %lf\n",zi,wf[zi+0],wf[zi+1],wf[zi+2]);	
				printf("extremity zh %d: %lf %lf %lf\n",zh,wf[zh+0],wf[zh+1],wf[zh+2]);	
				//exit(0);
				}
			
			basic_bar_drag1(Element[zg].diametrehydro, Element[zg].lgrepos, Element[zg].cdnormal, Element[zg].ftangent, ba, V, nt);
			//printf("nt2=   ");	imprvectreel(3, nt);

			NT[4]=nt[1]/2.0*Element[zg].pondFS[2];	//uniquement la moitie de la trainee totale de la barre sur l extremité 2
			NT[5]=nt[2]/2.0*Element[zg].pondFS[2];
			NT[6]=nt[3]/2.0*Element[zg].pondFS[2];
			}
		else
			{
			//efforttraineeelem_tab(zg,zh,zi,V);	//in case the drag is defined in a table
			}
   		
		//printf("Element[%d].pondFS[2] %lf   ",zg,Element[zg].pondFS[1]);	
		//printf(" %lf   \n",Element[zg].pondFS[2]);	
		//imprvectreel(6, NT); 
		
		/*mise a jour du vecteur effort global */  
    		/* waelem est le vecteur effort agissant sur les elements et affecte aux noeuds */
    		waelem[zh  ] += NT[1] ;	waelem[zh+1] += NT[2] ;	waelem[zh+2] += NT[3] ;
    		waelem[zi  ] += NT[4] ;	waelem[zi+1] += NT[5] ;	waelem[zi+2] += NT[6] ;
		//printf("wa[%2d] %4.0lf wa[%2d] %4.0lf wa[%2d] %4.0lf wa[%2d] %4.0lf wa[%2d] %4.0lf wa[%2d] %4.0lf \n",zh,waelem[zh  ],zh+1,waelem[zh+1],zh+2,waelem[zh+2],zi,waelem[zi  ],zi+1,waelem[zi+1],zi+2,waelem[zi+2]);
    		
		//Structure.element_drag = Structure.element_drag + NT[1] + NT[4];	//affectation of the global drag
		nt[1] = NT[1] + NT[4];
		nt[2] = NT[2] + NT[5];
		nt[3] = NT[3] + NT[6];
		if (produit_scal(V,V) != 0.0)
			{
			Structure.element_drag = Structure.element_drag + produit_scal(nt,V)/sqrt(produit_scal(V,V));
			}
		else
			{
			Structure.element_drag = Structure.element_drag + 0.0;
			}
		//printf("zg %4d structure drag %9.4lf\n",zg,Structure.element_drag);
		if (Sortie_texte.cable_drag == 1)
			{
			pa = Element[zg].type;
		    	TypeElement[pa].cable_drag = TypeElement[pa].cable_drag + NT[1] + NT[4];
		    	Element[zg].cable_drag = Element[zg].cable_drag + NT[1] + NT[4];
			/*printf("elem %4d pa %4d panel_drag %9.4lf\n",elem,pa,panneau[pa].drag);*/
			//printf("elem %4d elem_drag %9.4lf\n",zg,Element[zg].cable_drag);
			}
		if (Structure.hydro_forces == 1)
		{
			zj = (int) yb(zg,3) / 3;	Noeud[zj].fhx += NT[1];	Noeud[zj].fhy += NT[2];	Noeud[zj].fhz += NT[3];
			zj = (int) yb(zg,6) / 3;	Noeud[zj].fhx += NT[4];	Noeud[zj].fhy += NT[5];	Noeud[zj].fhz += NT[6];
		}

	   	if (Structure.type_solver == 1)		//type_solver : 1 for gauss, 2 for pardiso
		{
	  		for (zk = 1;zk <= 6;zk++)
	  		{
	  			for (zj = 1;zj <= 6;zj++)
	  		 	{
					/* mise a jour de la matrice de raideur globale */
	  			 	ze[yb(zg,zk)][eca+yb(zg,zj)-yb(zg,zk)] += wg[zk][zj];
	  			}
	  		}
	  	}
		else if (Structure.type_solver == 2)	//type_solver : 1 for gauss, 2 for pardiso
      		{
			for (zk=1; zk<=6; zk++)
			{
				for (zj=1; zj<=6; zj++)
				{
					//affectation_pardiso(wg[zk][zj], yb(zg,zk), yb(zg,zj));
				}
			}
      		}
	
  		 	
  		 /* calcul des bornes pour chaque ligne de la matrice de raideur globale */
	  	for (zk = 1;zk <= 6;zk++)
		{
	  		for (zj = 1;zj <= 6;zj++)
		 	{
	  		 	/*borne basse de la raideur ze*/
				if (rang[1][yb(zg,zk)] < yb(zg,zj)) rang[1][yb(zg,zk)] = yb(zg,zj);
				/*borne droite de la raideur ze*/
				if (rang[2][yb(zg,zk)] < yb(zg,zj)) rang[2][yb(zg,zk)] = yb(zg,zj);
				/*borne haute de la raideur ze*/
				if (rang[3][yb(zg,zk)] > yb(zg,zj)) rang[3][yb(zg,zk)] = yb(zg,zj); 
				/*borne gauche de la raideur ze*/
				if (rang[4][yb(zg,zk)] > yb(zg,zj)) rang[4][yb(zg,zk)] = yb(zg,zj);
			}
		 }
	}
	//exit(0);
}
