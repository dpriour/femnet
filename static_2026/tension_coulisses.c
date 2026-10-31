#define PRINCIPAL 0
#include "4c19.h"

void tension_coulisses()
	{
	/* Calcul des efforts en chaque noeud issus de la tension des coulisses*/
  	int zi,zj,noeud1,noeud2,el,zu,zv;
  	double dx,dy,dz,l_slider;

  	/*prise en compte de la tension dans les coulisses*************************************************************/
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
    		if (Coulisse[zi].lgtendue < 0.01 * Coulisse[zi].lgrepos)
    			{
      			Coulisse[zi].lgtendue = 0.01 * Coulisse[zi].lgrepos;
    			}
    		if (Coulisse[zi].lgtendue <  Coulisse[zi].lgrepos)	Coulisse[zi].raideur_effective = Coulisse[zi].raideur_compression;
      		else							Coulisse[zi].raideur_effective = Coulisse[zi].raideur_traction;         
    
    		/* Coulisse[zi].raideur_effective = le module d'elasticite* section associe l'element(ie la coulisse)
       		Coulisse[zi].wt est la tension dans la coulisse zi : > 0 en traction, < 0 en compression*/
       
    		Coulisse[zi].wt = (Coulisse[zi].lgtendue-Coulisse[zi].lgrepos) * Coulisse[zi].raideur_effective / Coulisse[zi].lgrepos ;
    		
  		/*calcul des efforts aux noeuds*/
    		for (zj = 1 ; zj<= Coulisse[zi].nb_noeud + 1; zj++) 
    			{
    			if (zj == 1) noeud1 = Coulisse[zi].extremite[1];
    			if (zj != 1) noeud1 = Coulisse[zi].noeud[zj-1];
    			if (zj != Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].noeud[zj];
    			if (zj == Coulisse[zi].nb_noeud + 1) noeud2 = Coulisse[zi].extremite[2];
    			dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    			dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    			dz = wf[3*noeud1-0]-wf[3*noeud2-0];
    			waelem[3*noeud1-2] -= dx/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			waelem[3*noeud1-1] -= dy/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			waelem[3*noeud1-0] -= dz/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			waelem[3*noeud2-2] += dx/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			waelem[3*noeud2-1] += dy/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			waelem[3*noeud2-0] += dz/Coulisse[zi].longueur[zj]*Coulisse[zi].wt;
    			}
  		}
  		
  	/*prise en compte de la tension nouvelle formule dans les sliders****************************************************/
    	//printf("nb_slider %d\n",Structure.nb_slider);
  	for (zi = 1 ; zi<= Structure.nb_slider ; zi++)
  		{
    		//printf("ziiiiiiiiiiii %d  nb_slider %d\n",zi,Structure.nb_slider);
  		//nb_bar = Slider[zi].nb_bar;
      		Slider[zi].lgtendue = 0.0;
    		for (zj = 1 ; zj<=Slider[zi].nb_bar; zj++) 
    			{
    			el = Slider[zi].barre[zj];
    			noeud1 = Element[el].extremite[1];
    			noeud2 = Element[el].extremite[2];
    			dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    			dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    			dz = wf[3*noeud1-0]-wf[3*noeud2-0];
    			Element[el].lgtendue = sqrt(dx*dx + dy*dy + dz*dz);
    			Slider[zi].lgtendue += Element[el].lgtendue;
    			}
    		//printf("Slider[zi].lgrepos %lf ",Slider[zi].lgrepos);
    		//printf("Slider[zi].lgtendue %lf \n",Slider[zi].lgtendue);
 
    		/*si la slider est trop detendue on limite sa longueur a 0.01 sa longueur au repos*/
    		if (Slider[zi].lgtendue < 0.01 * Slider[zi].lgrepos)
    			{
      			Slider[zi].lgtendue = 0.01 * Slider[zi].lgrepos;
    			}
    		if (Slider[zi].lgtendue <  Slider[zi].lgrepos)	Slider[zi].raideur_effective = Slider[zi].raideur_compression;
      		else							Slider[zi].raideur_effective = Slider[zi].raideur_traction;         

    		Slider[zi].wt = (Slider[zi].lgtendue-Slider[zi].lgrepos) * Slider[zi].raideur_effective / Slider[zi].lgrepos ;
    		for (zj = 1 ; zj<= Slider[zi].nb_bar; zj++) 
    			{
    			el = Slider[zi].barre[zj];
    			Element[el].wt = Slider[zi].wt;
    			Element[el].lgrepos = Element[el].lgtendue*Slider[zi].raideur_effective/(Slider[zi].wt+Slider[zi].raideur_effective);
     			//printf("Element[%d].lgrepos %lf ",el,Element[el].lgrepos);
    			//printf("Element[%d].wt %6.0lf \n",el,Element[el].wt);
   			}
    		//printf("Slider[zi].raideur_compression %lf \n",Slider[zi].raideur_compression);
    		//printf("Slider[zi].raideur_traction %lf \n",Slider[zi].raideur_traction);
    		//printf("Slider[zi].raideur_effective %lf \n",Slider[zi].raideur_effective);
    		//printf("Slider[zi].lgrepos %lf ",Slider[zi].lgrepos);
   		//printf("Slider[zi].lgtendue %lf ",Slider[zi].lgtendue);
   		//printf("Slider[zi].raideur_effective %lf ",Slider[zi].raideur_effective);
    		//printf("Slider[zi].wt %6.0lf \n",Slider[zi].wt);
		//exit(0); 
     		
  		/*calcul des efforts aux noeuds*/
    		for (zj = 1 ; zj<= Slider[zi].nb_bar; zj++) 
    			{
    			el = Slider[zi].barre[zj];
    			noeud1 = Element[el].extremite[1];
    			noeud2 = Element[el].extremite[2];
    			dx = wf[3*noeud1-2]-wf[3*noeud2-2];
    			dy = wf[3*noeud1-1]-wf[3*noeud2-1];
    			dz = wf[3*noeud1-0]-wf[3*noeud2-0];
    			//waelem[3*noeud1-2] -= dx/Element[el].lgtendue*Element[el].wt;
    			//waelem[3*noeud1-1] -= dy/Element[el].lgtendue*Element[el].wt;
    			//waelem[3*noeud1-0] -= dz/Element[el].lgtendue*Element[el].wt;
    			//waelem[3*noeud2-2] += dx/Element[el].lgtendue*Element[el].wt;
    			//waelem[3*noeud2-1] += dy/Element[el].lgtendue*Element[el].wt;
    			//waelem[3*noeud2-0] += dz/Element[el].lgtendue*Element[el].wt;
    			//printf("waelem[%d] %6.0lf %6.0lf %6.0lf waelem[%d] %6.0lf %6.0lf %6.0lf\n",noeud1,waelem[3*noeud1-2],waelem[3*noeud1-1],waelem[3*noeud1-0],noeud2,waelem[3*noeud2-2],waelem[3*noeud2-1],waelem[3*noeud2-0]);		
    			}
	  	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  	/*prise en compte de la tension nouvelle formule dans les sliders****************************************************/
    	//printf("nb_slider %d\n",Structure.nb_slider);
  	for (zi = 1 ; zi<= Structure.nb_slider ; zi++)
  		{
  		int nblign;
		double **KA,*FA,*FB,deltah; 
		int *LI;
		nblign = 3* (Slider[zi].nb_bar +1);
		//KA=(double **) malloc((nblign+1)*sizeof(double*));
		//for (zj=1; zj<nblign+1; zj++) 	KA[zj]=(double *) malloc((nblign+1)*sizeof(double));
		KA=(double **) malloc((nblign+1)*sizeof(double*));
		for (zj=0; zj<(nblign+1); zj++)	KA[zj]=(double *) malloc((nblign+1)*sizeof(double));

		
		
		
		
		FA=(double *) malloc((nblign+1)*sizeof(double*));
		FB=(double *) malloc((nblign+1)*sizeof(double*));
		LI=(int *) malloc((nblign+1)*sizeof(int*));
		deltah=0.0001;
		
    		for (zj = 1 ; zj<=Slider[zi].nb_bar; zj++) 
    			{
    			el = Slider[zi].barre[zj];
    			noeud1 = Element[el].extremite[1];
    			noeud2 = Element[el].extremite[2];
    			LI[3*zj-2]=3*noeud1-2;
    			LI[3*zj-1]=3*noeud1-1;
    			LI[3*zj-0]=3*noeud1-0;
    			LI[3*zj+1]=3*noeud2-2;
    			LI[3*zj+2]=3*noeud2-1;
    			LI[3*zj+3]=3*noeud2-0;
    			} 
		//printf("LI  ");
		//imprvectint(nblign, LI);
	  	for (zu = 0 ; zu<= nblign+1 ; zu++)
	  		{
			//////////////////////////////////////////////////////////////////////////////
			if ((zu>=1) && (zu<=nblign))
				{
				wf[LI[zu]]+=deltah;
				}
	      		Slider[zi].lgtendue = 0.0;
	    		for (zj = 1 ; zj<=Slider[zi].nb_bar; zj++) 
	    			{
	    			el = Slider[zi].barre[zj];
	    			noeud1 = Element[el].extremite[1];
	    			noeud2 = Element[el].extremite[2];
	    			dx = wf[3*noeud1-2]-wf[3*noeud2-2];
	    			dy = wf[3*noeud1-1]-wf[3*noeud2-1];
	    			dz = wf[3*noeud1-0]-wf[3*noeud2-0];
	    			Element[el].lgtendue = sqrt(dx*dx + dy*dy + dz*dz);
	    			Slider[zi].lgtendue += Element[el].lgtendue;
	    			} 
	    		/*si la slider est trop detendue on limite sa longueur a 0.01 sa longueur au repos*/
	    		if (Slider[zi].lgtendue < 0.01 * Slider[zi].lgrepos)
	    			{
	      			Slider[zi].lgtendue = 0.01 * Slider[zi].lgrepos;
	    			}
	    		if (Slider[zi].lgtendue <  Slider[zi].lgrepos)	Slider[zi].raideur_effective = Slider[zi].raideur_compression;
	      		else							Slider[zi].raideur_effective = Slider[zi].raideur_traction;         

	    		Slider[zi].wt = (Slider[zi].lgtendue-Slider[zi].lgrepos) * Slider[zi].raideur_effective / Slider[zi].lgrepos ;
	    		for (zj = 1 ; zj<= Slider[zi].nb_bar; zj++) 
	    			{
	    			el = Slider[zi].barre[zj];
	    			Element[el].wt = Slider[zi].wt;
	    			Element[el].lgrepos = Element[el].lgtendue*Slider[zi].raideur_effective/(Slider[zi].wt+Slider[zi].raideur_effective);
	   			}
	  		/*calcul des efforts aux noeuds*/
	    		for (zj = 1 ; zj<= nblign; zj++) 
	    			{
	    			FA[zj]=0.0;
	    			}
			//printf("FA  ");
			//imprvectreel(nblign, FA);
	    		for (zj = 1 ; zj<= Slider[zi].nb_bar; zj++) 
	    			{
	    			el = Slider[zi].barre[zj];
	    			noeud1 = Element[el].extremite[1];
	    			noeud2 = Element[el].extremite[2];
	    			dx = wf[3*noeud1-2]-wf[3*noeud2-2];
	    			dy = wf[3*noeud1-1]-wf[3*noeud2-1];
	    			dz = wf[3*noeud1-0]-wf[3*noeud2-0];
	    			FA[3*zj-2]-= dx/Element[el].lgtendue*Element[el].wt;
	    			FA[3*zj-1]-= dy/Element[el].lgtendue*Element[el].wt;
	    			FA[3*zj-0]-= dz/Element[el].lgtendue*Element[el].wt;
	    			FA[3*zj+1]+= dx/Element[el].lgtendue*Element[el].wt;
	    			FA[3*zj+2]+= dy/Element[el].lgtendue*Element[el].wt;
	    			FA[3*zj+3]+= dz/Element[el].lgtendue*Element[el].wt;
	    			}
			//printf("FA  ");
			//imprvectreel(nblign, FA);
			///////////////////////////////////////////////////////////////////////////////////////////
			if (zu == 0)
				{
		    		for (zj = 1 ; zj<= nblign; zj++) 
		    			{
		    			FB[zj]=FA[zj];
   					waelem[LI[zj]] += FA[zj];
		    			}
				}
			if ((zu>=1) && (zu<=nblign))
				{
				wf[LI[zu]]-=deltah;
				}
 			for( zv = 1 ; zv <= nblign ; zv++ )
				{
				KA[zv][zu] = (FB[zv]-FA[zv]) / deltah;
				//printf("KA[%d][%d]=%lf  \n",zv,zu,KA[zv][zu]);
				}
			}
		//printf("KA  \n");		
		
		//imprmatreel3( 1, nblign,  1,  nblign,  KA, nblign+1);
		for( zu = 1 ; zu <= nblign ; zu++ )
			{
			for( zv = 1 ; zv <= nblign ; zv++ )
				{
				//printf("%8.2lf  ",KA[zv][zu]);
				affectation_ze_rang(LI[zu], LI[zv], KA[zv][zu]);
				}
			//printf("\n");
			}
	    	free(KA); 
    		free(FA); 
    		free(FB); 
    		free(LI); 
    		//exit(0);
	  	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}

