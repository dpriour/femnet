#define PRINCIPAL 1
#include "4c19.h"
#include <time.h>
#include<stdlib.h>
#include<stdio.h>
#include "omp.h"
#include <math.h>
#include "nr.h"



/* 
programme principal de calcul d'equilibre d'elements lineaires a partir des fichiers *.mdh. 
prise en compte de whs sens de deplacement des noeuds: +1 si un noeud peut decoller du fond 
  						       -1 si le noeud peut descendre 
La matrice de raideur est non symetrique
lecture de la derniere position calculee si elle existe dans le fichier .sta
*/

int main(int argc,char *argv[])

  	{
	int i;
 	char nomfichier[200],tonom[996],command[1000];
	double ratio,delta_x,ecart[21];
	double volumefr,sum,kmax,kmin,kmean;
	TCOO1  wa_surf,wa_elem,wa_noeud;
	int zu,zv,zw,zx,ecartij[3][21],maxlarg,zf,iii,j;
  	int zh,zi,zg,zj,noeud1,noeud2;
  	double dx,dy,dz,l_zero,tension_w,raideur_effective,dr,dr2,rl,Rmax;
  	FILE   *f9,*file2;
	double t0, t1, time_taken;
	long idum;

	clock_t start, end;

	float* volumefr1 = NULL;	
	volumefr1 = malloc((Structure.nb_cage_volume+1) * sizeof(float));

	float* volumefr2 = NULL;	
	volumefr2 = malloc((Structure.nb_cage_volume+1) * sizeof(float));
	strcpy(nomfichier,argv[1]);
  	charger(nomfichier);                  	/*lecture des donnees initiales don*/
 	lectureDo4(nomfichier);                  	/*lecture des donnees initiales mdg*/

	if (Sortie_texte.effort_structure == 1)
		{
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".efg");	
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"nb of fixed components: %d n(node) a(axe)\n",Structure.nb_fixed_components);
	    	fprintf(file2,"  times (s)");
		for ( zi = 1 ; zi <= Structure.nb_fixed_components ; zi++ )
		     	{ 
	    		fprintf(file2,"  n%5d ",Structure.list_fixed_node[zi] );
	    		fprintf(file2,"a %1d ",Structure.list_fixed_axe[zi] );
	    		}
	    	fprintf(file2,"\n");
		fclose(file2);
		}
  	if (Structure.stiffness_matrix == 1)
  		{
  		strcpy(tonom,nomfichier);
	  	strcat(tonom,".sti");	
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"size of the squarre stiffness matrix: %d\n",3*NOMBRE_NOEUDS);
		fclose(file2);
  		}
  	if (Structure.pressure_file == 1)
  		{
  		strcpy(tonom,nomfichier);
	  	strcat(tonom,".pre");	
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"triangular element normal pressure (Pa) tangential pressure along u twine (Pa) tangential pressure perpendicular to the normal and u:\n");
		fclose(file2);
  		}
  	charger(nomfichier);                  	/*lecture des donnees initiales don*/
	//exit(0);

 	lectsta = lecturesta(nomfichier);        	/*lecture des positions calculees si elles existent sta*/
	/*printf("ball x %12.2lf y %12.2lf z %12.2lf  \n",Noeud[517].x,Noeud[517].y,Noeud[517].z);*/
	largeur_matrice = largeurbande();

	//t0 = omp_get_wtime();

 	initialisation();
	if (Structure.openfoam == 1) lecturespe(nomfichier);      	/*reading of water speed per node*/
 	if (Structure.openfoam == 1) lecturepre(nomfichier);     	/*reading of pressure per triangular element*/
	printf("Structure.openfoam: %d\n",Structure.openfoam);
	//imprvectreel1(18, 3, wf);
  	direct();
	//lectParam();
	lectParam2(nomfichier);
	//printf("totooooo\n");	exit(0);
	etirement5();
	surglob2();
 	nbmaille_triangle();
 	initialisation_pondFS();
 	trouve_voisin();

	volumefr1 = cage_volume();
	volumefr2 = volume_cage();

	printf("\n");
	for (iii=1;iii<=Structure.nb_cage_volume;iii++)
	{
		printf("Volume de la cage n°%d en position initiale : %lf m3\n", iii, -volumefr1[iii]);
			
		/*Ce volume initial doit être égal à celui d'un cylindre "polygonal" à savoir
		V=hauteur_de_filet*rayon_du_filet*rayon_du_filet*nb_de_coté*cos(pi/nb_de_coté)*sin(pi/nb_de_coté)*/

		printf("Volume imergé de la cage n°%d en position initiale : %lf m3\n", iii, -2*volumefr1[iii]+volumefr2[iii]);
	}
	printf("\n");

	/*resultat_debut
  	f9 = fopen("resultat.txt","w");
  	do
  		{
	resultat_fin*/


	deltat = 0.000001;  	/*pas de temps deltat qui correspond au temps d une iteration 
				la raideur = effort / deltat 
				vitesse = delta_deplacement / deltat
				raideur = - 1/2 1000 1 D L / deltat*/
  	nbiter = 0;
  	nbpas = 0;
	do
  		{ 
    		nbpas++;
   		do
    			{
      			nbiter++;
      			//printf("nbpas = %4d nbiter = %4d \n",nbpas,nbiter);
			//if (nbiter > 150)	exit(0);
 			//lectParam();
			lectParam2(nomfichier);
      			/*TEST_debut
			delta_x = 0.0000000001;
			for( zu = 1 ; zu <= 20 ; zu++ ) ecart[zu] = 0.0;
			for( zu = 0 ; zu <= 3*NOMBRE_NOEUDS+1 ; zu++ )
      				{
      				printf("zu = %4d 3*NOMBRE_NOEUDS = %4d\n",zu,3*NOMBRE_NOEUDS);
      				if (zu != 0) wf[zu] = wf[zu] + delta_x;
      			TEST_fin*/
      				
      			misezero4();			/*printf("misezero		ze[%5d][%5d] = %17.0lf\n",150,1500,ze[150][1500]);*/
 			miseajourPondFS();
 			
			//printf("misezero\n");imprvectreel1(435, 0, wasurf);
      			/*efforts sur les triangles de filet*****************************************************************************/
			etirement5();		//elasticity diamond meshes
			surglob2();		//elasticity hexagonal meshes
			flexion2();		//flexion in plane
			fermeture2();		//contact between knots
			flotteursurf3();	//buyoancy of netting
  			pesanteurSurface();	//weight of netting
			//pliage_triangle4();	//flexion out of plane
			/*printf("Courant.vitesse = %17.4lf\n",Courant.vitesse);
			printf("Prise.volume = %17.4lf\n",Prise.volume);
			printf("Prise.seuil = %17.4lf\n",Prise.seuil);
			printf("Structure.nb_tarp_diamond = %17d\n",Structure.nb_tarp_diamond);
			printf("Structure.nb_tarp_hexa = %17d\n",Structure.nb_tarp_hexa);
			printf("Structure.nb_catch2_length = %17d\n",Structure.nb_catch2_length);
			printf("Structure.nb_catch2_surface = %17d\n",Structure.nb_catch2_surface);
			printf("Structure.nb_catch2_volume = %17d\n",Structure.nb_catch2_volume);
			printf("Structure.nb_cage_volume = %17d\n",Structure.nb_cage_volume);
			printf("Structure.nb_catch2_weight = %17d\n",Structure.nb_catch2_weight);
			printf("Prise.catch_gravity = %17.4lf\n",Prise.catch_gravity);*/
			if((Courant.vitesse != 0.0) && (Prise.volume < Prise.seuil) && (Structure.nb_tarp_diamond  == 0) && (Structure.nb_tarp_hexa  == 0) && (Structure.nb_catch2_length  == 0) && (Structure.nb_catch2_surface  == 0) && (Structure.nb_catch2_volume  == 0) && (Structure.nb_cage_volume  == 0) && (Structure.nb_catch2_weight  == 0))
      				{
				//printf("A\n");
				//printf("Prise.catch_gravity = %17.0lf\n",Prise.catch_gravity);//
				if (Structure.drag_forces_type == 1) filethydro4_sta();	//The hydrodynamic forces on diamond netting is calculated using Morison formulations
				if (Structure.drag_forces_type == 2) filethydro4_sta_zhan();	//The hydrodynamic forces on diamond netting is calculated using Zhan formulations
				//if (Structure.drag_forces_type == 3) filethydro4_sta();	//The hydrodynamic forces on diamond netting is calculated using drop pressure formulations
				//if (Structure.drag_forces_type == 4) filethydro4_sta();	//The hydrodynamic forces on diamond netting is calculated using Aarnes formulations
      				}
			//imprvectreel1(51, 3, wasurf);
     			if ((Prise.volume > Prise.seuil) && (Prise.catch_gravity == 0.0)) 
      				{
				//printf("B\n");
				//printf("Qrise.catch_gravity = %17.0lf\n",Prise.catch_gravity);//
      				//in this case the catch is expected below the free surface
	      			catch_hexa();			//forces and stiffness due to the catch
    				trainee_front();		//hydrodynamic forces on netting in front of the catch
      				}
     			if ((Prise.volume > Prise.seuil) && (Prise.catch_gravity > 0.0)) 
      				{
				//printf("C\n");
				//printf("Rrise.catch_gravity = %17.0lf\n",Prise.catch_gravity);//
      				//in this case the catch is expected above the free surface
				//printf("Prise.catch_gravity = %17.0lf\n",Prise.catch_gravity);
	      			catch_hexa();			//forces and stiffness due to the catch
      				}
			if (Structure.nb_tarp_diamond > 0)
				{
				//printf("D\n");
				//printf("Srise.catch_gravity = %17.0lf\n",Prise.catch_gravity);//
       				catch_hexa();			//forces and stiffness due to the catch
     				trainee_front();		//hydrodynamic forces on netting in front of the catch
				}
     			if ((Structure.nb_catch2_volume != 0) && (Prise.catch_gravity == 0.0)) 
      				{
				//printf("E\n");
				//printf("Qrise.catch_gravity = %17.0lf\n",Prise.catch_gravity);//
      				//in this case the catch is expected below the free surface
	      			catch2_volume();		//forces and stiffness due to the catch
    				//trainee_front();		//hydrodynamic forces on netting in front of the catch
      				}
			//imprvectreel1(51, 3, wasurf);
      			/*efforts sur les elements******************************************************************************/
			
														//if (nbiter > 144)	printf("a %8.0lf ",waelem[624]);
			//imprvectreel(10, waelem);										//if (nbiter > 144)	printf("d %8.0lf ",waelem[624]);
			tension_bar();										//if (nbiter > 144)	printf("b %8.0lf ",waelem[624]);
			//imprvectreel(10, waelem);										//if (nbiter > 144)	printf("d %8.0lf ",waelem[624]);
			tension_constant_bar();									//if (nbiter > 144)	printf("c %8.0lf ",waelem[624]);
			pesanteurelem();/**/ 	
			flotteurelement2();/**/									//if (nbiter > 144)	printf("e %8.0lf ",waelem[624]);
			for (zv = 1 ; zv<= 3*NOMBRE_NOEUDS ; zv++) {if(isnan(waelem[zv]))	{printf("flotteurelement2 zv %d \n",zv);	exit(0);}}
			courantelem8();/**/									//if (nbiter > 144)	printf("f %8.0lf ",waelem[624]);
			for (zv = 1 ; zv<= 3*NOMBRE_NOEUDS ; zv++) {if(isnan(waelem[zv]))	{printf("courantelem8 zv %d \n",zv);	exit(0);}}
			pliage_barre_pardiso2_3();/**/	// flexion de barres avec angle au repos nul 		//if (nbiter > 144)	printf("g %8.0lf ",waelem[624]);
			for (zv = 1 ; zv<= 3*NOMBRE_NOEUDS ; zv++) {if(isnan(waelem[zv]))	{printf("pliage_barre_pardiso2 zv %d \n",zv);	exit(0);}}
			pliage_barre_pardiso4();/**/	// flexion de barres avec angle au repos non nul	//if (nbiter > 144)	printf("h %8.0lf ",waelem[624]);
			for (zv = 1 ; zv<= 3*NOMBRE_NOEUDS ; zv++) {if(isnan(waelem[zv]))	{printf("pliage_barre_pardiso4 zv %d \n",zv);	exit(0);}}
			if (Structure.nb_ballast > 0) ballast_calcul2();
			//printf("debut contact1\n");     			
			if (Structure.nb_cable_contact > 0)	contact1();
			//printf("fin contact1\n");     			

      			/*efforts sur les coulisses************************************************************************************/
      			tension_coulisses();
     			raideur_coulisses();
     			contact_coulisses();/**/

      			/*forces in winchs**********************************************************************************************/
      			tension_winchs();/**/

      			/*efforts sur les noeuds******************************************************************************************/ 
     			effortexterieurs();
      			pesanteur(); 
      			traineecourant2();/**/
      			if (Vent.vitesse > 0.0) traineevent1();
      			flotteur2();
      			spheric_limit1();/**/
			/*imprvectreel(1320, wasurf);*/   
      			fond();  	//force on nodes
			if (Structure.nb_deck > 0) deck_contact();
      			//fond2();     		//force on elements	
			//printf("fonde		");imprvectreel(21, waelem);/**/
      			//imprvectreel(6, wanoeud);   			
			//printf("wanoeud\n");imprvectreel1(1032, 0, wasurf);
			//exit(0);
			/*sum = 0.0;  			
			for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
				{
				sum = sum + wanoeud[3*zi-2];
				}
			printf("sumg %9.2lf \n",sum);*/
      			/*printf(" ze ");
  			for (zi = 1 ; zi<= 240 ; zi++)
  				{
    				for (zj = 1495 ; zj<= 1505 ; zj++)	printf(" %9.0lf ",ze[zi][zj]);
    				printf("\n");
  				}
  			printf("\n");
  			exit(0);*/
			//for (zv = 1 ; zv<= 3*NOMBRE_NOEUDS ; zv++) {if(isnan(wanoeud[zv]))	{printf("wanoeud zv %d \n",zv);	exit(0);}}
  			
      			/*TEST_debut
      				if (zu == 0) 
      					{
      					for( zw = 1 ; zw <= 3*NOMBRE_NOEUDS ; zw++ )   	
						{
						wa_surf[zw]  = wasurf[zw];
						wa_elem[zw]  = waelem[zw];
						wa_noeud[zw] = wanoeud[zw];
						}
					}
      				if ((zu > 0) && (zu < 3*NOMBRE_NOEUDS+1)) 
					{
					wf[zu] = wf[zu] - delta_x;
					for( zv = 1 ; zv <= 3*NOMBRE_NOEUDS ; zv++ )
      						{
      						if (((eca - zv + zu) > 0) && ((eca - zv + zu) < 2*eca+1))
      							{
							ze_modif[zv][eca - zv + zu] = - (wasurf[zv] - wa_surf[zv] + waelem[zv] - wa_elem[zv] + wanoeud[zv] - wa_noeud[zv]) / delta_x;
							}
      						}
					}
      				}	//fin de la boucle zu
 
				for( zu = 1 ; zu <= 3*NOMBRE_NOEUDS ; zu++ )
      					{
					for( zw = 1 ; zw <= 2*eca ; zw++ )
						{
      						if ((zw - eca + zu > 0) && (zw - eca + zu <= 3*NOMBRE_NOEUDS)) 
							{
							zx = 0;
							for( zv = 1 ; zv <= 20 ; zv++ )
								{
								if (fabs(ze[zu][zw]-ze_modif[zu][zw]) > ecart[zv])
									{
									zx = zv;
									}
								}
							if (zx != 0)
								{
								for( zv = 1 ; zv <= zx-1 ; zv++ )
									{
									ecart[zv] = ecart[zv+1];
									ecartij[1][zv] = ecartij[1][zv+1];
									ecartij[2][zv] = ecartij[2][zv+1];
									}
								ecart[zx] = fabs(ze[zu][zw]-ze_modif[zu][zw]);
								ecartij[1][zx] = zu;
								ecartij[2][zx] = zw;
								}
							}
						}
					}
														
				for( zu = 1 ; zu <= 20 ; zu++ )
      					{
      					printf("ecart[%5d][%5d] = %17.4lf      ",ecartij[1][zu],ecartij[2][zu],ecart[zu]);
					printf("ze[%5d][%5d] = %17.4lf\n",ecartij[1][zu],ecartij[2][zu],ze[ecartij[1][zu]][ecartij[2][zu]]);
					}
				printf("ze global elements finis (ten first)\n");
				for( zu = 1 ; zu <= 6 ; zu++ )
      					{
					for( zw = 1492 ; zw <= 1508 ; zw++ )
						{
						printf("%7.0lf   ",ze[zu][zw]);
						}
					printf("\n");
					}
				printf("ze_modif global differences finies (ten first)\n");
				for( zu = 1 ; zu <= 6 ; zu++ )
      					{
					for( zw = 1492 ; zw <= 1508 ; zw++ )
						{
						printf("%7.0lf   ",ze_modif[zu][zw]);
						}
					printf("\n");
					}
				printf("K global elements finis (ten first)\n");
				for( zu = 1 ; zu <= 10 ; zu++ )
      					{
					for( zw = 1 ; zw <= 10 ; zw++ )
						{
						printf("%11.0lf   ",ze[zu][eca-zu+zw]);
						}
					printf("\n");
					}
				printf("k global differences finies (ten first)\n");
				for( zu = 1 ; zu <= 10 ; zu++ )
      					{
					for( zw = 1 ; zw <= 10 ; zw++ )
						{
						printf("%11.0lf   ",ze_modif[zu][eca-zu+zw]);
						}
					printf("\n");
					}
				printf("rang[1]:  ");	for( zu = 1 ; zu <= 9 ; zu++ )	printf("%4d   ",rang[1][zu]);		printf("\n");
				printf("rang[2]:  ");	for( zu = 1 ; zu <= 9 ; zu++ )	printf("%4d   ",rang[2][zu]);		printf("\n");
				printf("rang[3]:  ");	for( zu = 1 ; zu <= 9 ; zu++ )	printf("%4d   ",rang[3][zu]);		printf("\n");
				printf("rang[4]:  ");	for( zu = 1 ; zu <= 9 ; zu++ )	printf("%4d   ",rang[4][zu]);		printf("\n");
      				exit(0);
      			TEST_fin*/
    	
			//imprvectreel(200, wasurf);
			//imprvectreel(10, waelem);
			//imprvectreel(200, wanoeud);
			//exit(0);/**/

      			//fond();     			
			//printf("wanoeud\n");imprvectreel1(1032, 0, wasurf);
			//exit(0);
			/*
			printf("ze global elements finis\n");
			for( zu = 1 ; zu <= 9 ; zu++ )
				{
				for( zw = 1491 ; zw <= 1509 ; zw++ )
					{
					printf("%7.2lf   ",ze[zu][zw]);
					}
				printf("\n");
				}
			*/
    			symetrie2();
		    	/*
		    	if (nbiter > 144)
		    		{
				printf("wasurf %8.3lf ",wasurf[624]);
				printf("waelem %8.3lf ",waelem[624]);
				printf("wanoeud %8.3lf ",wanoeud[624]);
				printf("wa %8.3lf ",wa[624]);
				}
			*/		
			//imprvectreel1(45, 3, wanoeud);		  			
			//imprvectreel1(45, 3, waelem);		  			
			//imprvectreel1(45, 3, wasurf);		  			
      			chaineeff3();
      			kmin = ze[1][eca];
      			kmax = ze[1][eca];
      			kmean = 0.0;
			for( zu = 1 ; zu <= 3*NOMBRE_NOEUDS ; zu++ )
      				{
				//if (fabs(ze[zu][eca]) < fabs(kmin))	kmin = ze[zu][eca];
				//if (fabs(ze[zu][eca]) > fabs(kmax))	kmax = ze[zu][eca];
				//kmean = kmean + fabs(ze[zu][eca]);
				if ((ze[zu][eca]) < (kmin))	kmin = ze[zu][eca];
				if ((ze[zu][eca]) > (kmax))	kmax = ze[zu][eca];
				kmean = kmean + (ze[zu][eca]);
				}
			kmean = kmean / 3.0 / NOMBRE_NOEUDS;
      			transnoeud();
      			modification4();

      			RW = effortmax();
      			RMEAN = effortmean();
      			RSUM = effortsum();

			//if (nbiter > 22) {	printf("modification4\n");imprvectreel1(435, 3, waelem);	}
			//start = clock();
			if (Structure.type_solver == 1)
			{
	      			resolution4();
	      			remonteb4();
      			}
	      		else if (Structure.type_solver == 2)
      			{
				//affectation();			// code qui affecte les vecteurs necessaires a pardiso (affectation de a, ja, et ka)
				//affectation_ia();		// code qui affecte le dernier vecteur necessaire a pardiso ia
      				//resolution_mkl_pardiso();
      			}

      			/*resolution_gradient();*/

      			MW = mouvementmax();
      			MMEAN = mouvementmean();
      			MSUM = mouvementsum();
      			if (Auto_convergence == 1) etat_convergence();/**/

      			coordonnees4();
//   			miseentension = modifraideur();
			if ((nbpas == 1) && (nbiter == 1))
				{
				if (Prise.volume > 0.0) 	printf("nbiter         Max (N)       Max (m)      Mean (N) Mean (m)   thick (m)  kadd (N/m)\n");
				else 				printf("nbiter         Max (N)       Max (m)      Mean (N) Mean (m)  	    kadd (N/m)\n");
				}
     			if (Periodeimpression*(nbiter/Periodeimpression) == nbiter) 
      				{
        			iterationfin = 0.0;
       				if ( (RMEAN != 0.0)  && (precedent != 0.0) && (log( precedent / fabs(RMEAN )) != 0.0) ) iterationfin = Periodeimpression * log( fabs(RMEAN) / Seuilconvergence ) / log(precedent / fabs(RMEAN));
       				else											iterationfin = -1.0;
				if (Prise.volume > 0.0) 	printf("%6d %15.4lf %13.5lf %13.4lf %8.5lf %11.4lf",nbiter,RW,MW,RMEAN,MMEAN,Prise.epaisseur);
				else 				printf("%6d %15.4lf %13.5lf %13.4lf %8.5lf",nbiter,RW,MW,RMEAN,MMEAN);
				if (Structure.mean_XYZ_desequilibrium == 1)
					{
					printf(" mean_desequilibrium_XYZ %8.2lf %8.2lf %8.2lf ",mean_desequilibrium_X,mean_desequilibrium_Y,mean_desequilibrium_Z);
					}
				/*printf(" %11.0lg",Numtemps_relax*Numtemps);*/
				printf(" %11.0lg",Numtemps);
				//printf(" %11.0lg %11.0lg %11.0lg",kmin,kmean,kmax);
				//printf(" %6.3lg",Structure.ratio_num_temp);
        			//if (iterationfin >= 0.0) 	printf(" %7.0lf\n", iterationfin + nbiter);
        			//else 				printf("\n");
        			printf("\n");
        			precedent = RMEAN;
				}
    			}
    			while (fabs(RMEAN)> Seuilconvergence  && nbiter < Nbmaxiterations) ;
//   			miseentension = modifraideur();
//			printf(" %d ",miseentension);
   		}

  		while (miseentension < 0 && nbiter < Nbmaxiterations) ;
  		if (Prise.volume > 0.0)	printf("%6d %15.4f %13.5lf %13.4lf %8.5lf %11.4lf %11.0lg",nbiter ,RW,MW,RMEAN,MMEAN,Prise.epaisseur,Numtemps);
  		else 				printf("%6d %15.4f %13.5lf %13.4lf %8.5lf %11.0lg",nbiter ,RW,MW,RMEAN,MMEAN,Numtemps);
		//printf(" %11.0lg %11.0lg %11.0lg",kmin,kmean,kmax);
  		if (iterationfin >= 0.0) 	printf(" %7.0lf\n", iterationfin + nbiter );
  		else 				printf(" \n");
		/*******************************************************/  		
	  	for (zg = 1 ; zg<= NOMBRE_WINCHS ; zg++)
	  		{
	    		for (zj = Winch[zg].nb_barre  ; zj>= 1; zj--) 
	    			{
	    			noeud1 = Winch[zg].noeud[zj+1];
	    			noeud2 = Winch[zg].noeud[zj  ];
				l_zero = fabs(Winch[zg].prop[zj+1]-Winch[zg].prop[zj  ]) * Winch[zg].longueur_repos;
	    			dx = wf[3*noeud1-2]-wf[3*noeud2-2];
	    			dy = wf[3*noeud1-1]-wf[3*noeud2-1];
	    			dz = wf[3*noeud1-0]-wf[3*noeud2-0];
	  			dr2 = dx*dx + dy*dy + dz*dz;
	  			dr  = sqrt(dr2);		
	    			Winch[zg].longueur[zj] = dr;
	    			if (dr > l_zero)	raideur_effective = Winch[zg].raideur_traction;
	    			else			raideur_effective = Winch[zg].raideur_compression;
	    			tension_w = (dr - l_zero) / l_zero * raideur_effective;
				printf("noeuds %3d %3d ",noeud1,noeud2);
	    			printf("l_tendue %6.3lf l_zero %6.3lf raideur %10.0lf ",Winch[zg].longueur[zj],l_zero,raideur_effective);
	    			printf("tension dans la barre %3d = %10.3lf\n",zj,tension_w);
	    			}
	  		}
		/********************************************************/
      		if (Prise.volume > Prise.seuil) 
      			{
       			catch_hexa();
      			trainee_front();
      			}
  		misezero4();
  		miseajourPondFS();
  		
		/*efforts sur les surfaces*/
		etirement5();
		surglob2();
		flexion2();
		fermeture2();
		flotteursurf3(); /**/
    		pesanteurSurface();/**/
		//pliage_triangle4();
		if((Prise.volume < Prise.seuil) && (Structure.nb_tarp_diamond  == 0) && (Structure.nb_tarp_hexa  == 0) && (Structure.nb_catch2_length  == 0) && (Structure.nb_catch2_surface  == 0) && (Structure.nb_catch2_volume  == 0) && (Structure.nb_cage_volume  == 0) && (Structure.nb_catch2_weight  == 0))
			{
			//printf("A\n");
			if (Structure.drag_forces_type == 1) filethydro4_sta();	//The hydrodynamic forces on diamond netting is calculated using Morison formulations
			if (Structure.drag_forces_type == 2) filethydro4_sta_zhan();	//The hydrodynamic forces on diamond netting is calculated using Zhan formulations
			//if (Structure.drag_forces_type == 3) filethydro4_sta();	//The hydrodynamic forces on diamond netting is calculated using drop pressure formulations
			//if (Structure.drag_forces_type == 4) filethydro4_sta();	//The hydrodynamic forces on diamond netting is calculated using Aarnes formulations
			}
    		if ((Prise.volume > Prise.seuil) && (Prise.catch_gravity == 0.0)) 
			{
			//printf("B\n");
			//in this case the catch is expected below the free surface
			//printf("Prise.catch_gravity = %17.0lf\n",Prise.catch_gravity);
			catch_hexa();
			trainee_front();/**/
			}
		if ((Prise.volume > Prise.seuil) && (Prise.catch_gravity > 0.0)) 
			{
			//printf("C\n");
			//in this case the catch is expected above the free surface
			//printf("Prise.catch_gravity = %17.0lf\n",Prise.catch_gravity);
      			catch_hexa();
			}
		if (Structure.nb_tarp_diamond > 0)
			{
			//printf("D\n");
			catch_hexa();
			trainee_front();/**/
			}

		/*efforts sur les elements*/
		tension_bar();/* */
		tension_constant_bar();
		pesanteurelem();/**/ 
		flotteurelement2();/**/
		courantelem8();/**/
		pliage_barre_pardiso2_3();/**/	// code de raideur en flexion prenant en compte les symétries et le cas ou il y a plusieurs "poutres" en liaison			
		pliage_barre_pardiso4();/**/	// code de raideur en flexion prenant en compte les symétries et le cas ou il y a plusieurs "poutres" en liaison
		if (Structure.nb_ballast > 0) ballast_calcul2();
		if (Structure.nb_cable_contact > 0)	contact1();

		/*efforts sur les coulisses*/
		tension_coulisses();
		raideur_coulisses();
		contact_coulisses();/**/

		/*forces in winchs*/
		tension_winchs();/**/

		/*efforts sur les noeuds*/ 
		effortexterieurs();
		pesanteur(); 
		traineecourant2();/**/
		if (Vent.vitesse > 0.0) traineevent1();
		flotteur2();
		spheric_limit1();/**/
      		fond();     //force on nodes	
		if (Structure.nb_deck > 0) deck_contact();
		ecriturestatique(nomfichier);/**/
		sortie_texte_ecran();
  		symetrie2();
      		modification4();

		//double volumefront,surfacefront;
		//surface_volume(-1000, &surfacefront, &volumefront);
		//printf("surfacefront %lf\n",surfacefront);
		//printf("volumefront %lf\n",volumefront);


		/*resultat_debut
   		fprintf(f9,"  %5d",nbiter);
    		fprintf(f9,"  %17.9lf",double_temp);
    		fprintf(f9,"  %17.9lf",Prise.volume);
    		fprintf(f9,"  %17.9lf",Prise.epaisseur);
    		fprintf(f9,"  %17.9lf",Prise.diametre);
    		fprintf(f9,"\n");
		Prise.volume = Prise.volume - 1.0/1000.0;
  		}*/

	printf("\n");
	for (iii=1;iii<=Structure.nb_cage_volume;iii++)
	{
		printf("Volume de la cage n°%d en position statique : %lf m3\n", iii, -volumefr1[iii]);
		printf("Volume imergé de la cage n°%d en position statique : %lf m3\n", iii, -2*volumefr1[iii]+volumefr2[iii]);
	}
	printf("\n");
	

 
  	/*while ((Prise.volume >= 1.50) && (nbiter<2000));
 	fclose(f9);
	resultat_fin*/

	//t1 = omp_get_wtime();
	//time_taken = (double)(t1-t0);
	//printf("time taken for %d elements : %f\n", NOMBRE_ELEMENTS, time_taken);
  	if (Structure.stiffness_matrix == 1)
		{
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".sti");	
	  	file2 = fopen(tonom,"a");
		for (zi=1;zi<=3*NOMBRE_NOEUDS;zi++)
			{
			for (zj=1;zj<=rang[4][zi]-1;zj++)
				{
				fprintf(file2,"%lf ",0.0);
				}
			for (zj=rang[4][zi];zj<=rang[2][zi];zj++)
				{
				fprintf(file2,"%lf ",ze[zi][eca+zj-zi]);
				}
			for (zj=rang[2][zi]+1;zj<=3*NOMBRE_NOEUDS;zj++)
				{
				fprintf(file2,"%lf ",0.0);
				}
			fprintf(file2,"\n");
			}
		fclose(file2);
		}
	
  	if (Structure.pressure_file == 1)
  		{
		output_pressure(nomfichier);
		}

	libere_memoire();
	if (volumefr1	!= NULL)        free(volumefr1);
	if (volumefr2	!= NULL)        free(volumefr2);
  	strcpy(tonom,nomfichier);
	j=strlen(tonom);
	while ((tonom[j])!='.' && j>0) j--;
	if (tonom[j]=='.') tonom[j]=0;
  	strcat(tonom,".par");
	file2 = fopen(tonom,"r");
  	if (file2 != NULL) 
  		{
		sprintf(command,"rm %s",tonom);									
		system(command);	/*delete par file*/
  		} 
	return 0;
	}

