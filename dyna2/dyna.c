#define PRINCIPAL 1
#include "4c19.h"
#include <time.h>
#include<stdlib.h>
#include<stdio.h>
#include "omp.h"
#include <math.h>
#include "../unix_2004/nr.h"


/* 
programme principal de calcul d' equilibre d'elements lineaires a partir des fichiers *.mdh. 
prise en compte de whs sens de deplacement des noeuds: +1 si un noeud peut decoller du fond 
  							 -1 si le noeud peut descendre 
La matrice de raideur est non symetrique
lecture de la derniere position calculee si elle existe dans le fichier .sta
*/

int main(int argc,char *argv[])

  	{
 	char nomfichier[100],tonom[996],command[1000];
	double ratio,delta_x,ecart[21];
	TCOO1  wa_surf,wa_elem,wa_noeud;
	int zu,zv,zw,zx,ecartij[3][21],maxlarg,zf,j;
  	int zh,zi,zg,zj,noeud1,noeud2,elem,Nextscreen;
  	double dx,dy,dz,l_zero,tension_w,raideur_effective,dr,dr2,rl,ratio_drag;
	double frx, surfacefr, volumefr, waold[1000];
  	FILE   *f9;
  	
  	/*haul cable*/
  	double reduction,limit,reduction_new;
  	int no,next_bar,next_node,trouve;
  	/*haul cable*/
  	
	strcpy(nomfichier,argv[1]);
  	charger(nomfichier);                  		/*lecture des donnees initiales *.don*/
  	lectureDo4(nomfichier);                  	/*lecture des donnees initiales *.mdg*/
  	charger(nomfichier);                  		/*lecture des donnees initiales *.don*/
  	
  	lectsta = lecturesta(nomfichier);        	/*lecture des positions calculees si elles existent*/
 	largeur_matrice = largeurbande();
  	initialisation();
	initialisation_dynamique(nomfichier);
	initialisation_hauling_cable();
	
  	if (Structure.haul == 1)
  		{
  		strcpy(tonom,nomfichier);
	  	strcat(tonom,".haul");
	  	file2 = fopen(tonom,"w");
	    	//fprintf(file2,"times (s) bars length (m)\n");
	    	fprintf(file2,"\n");
	   	fclose(file2);
	   	}

	if(Sortie_texte.bar_tension == 1)	
		{
	  	strcpy(tonom,nomfichier);
	  	strcat(tonom,".ten");
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"times (s) bars tension (N)\n");
	    	//fprintf(file2,"\n");
	   	fclose(file2);
	   	}
   	
	if(Sortie_texte.diamond_tension == 1)	
		{
	  	strcpy(tonom,nomfichier);
	  	strcat(tonom,".ted");
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"times (s) diamond twines tension (N)\n");
	    	//fprintf(file2,"\n");
	   	fclose(file2);
	   	}
   	
	if(Structure.hauling_cable4_tension == 1)	
		{
	  	strcpy(tonom,nomfichier);
	  	strcat(tonom,".hwt");
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"times (s) hauling tensions (N)\n");
	    	//fprintf(file2,"\n");
	   	fclose(file2);
	   	}
   	
   	
	if(Structure.ballast_altitude == 1)	
		{
	  	strcpy(tonom,nomfichier);
	  	strcat(tonom,".bal");
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"times (s) ballast altitude (m) volume (m^3)\n");
	    	//fprintf(file2,"\n");
	   	fclose(file2);
	   	}
	if (Structure.total_mass != 0.0)
		{
	  	strcpy(tonom,nomfichier);
	  	strcat(tonom,".cgp");
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"times (s) mass (kg) gravity position x y z (m) volume (m^3) floatability centre x y z (m)\n");
	    	//fprintf(file2,"\n");
	   	fclose(file2);
	   	}
	if(Structure.netting_volume_calculation == 1)	
		{
	  	strcpy(tonom,nomfichier);
	  	strcat(tonom,".vol");
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"times (s) nettings volume (m^3)\n");
	    	//fprintf(file2,"\n");
	   	fclose(file2);
	   	}
  	/*if(Sortie_texte.effort_structure == 1)
  		{
	  	strcpy(tonom,nomfichier);
	  	strcat(tonom,".eff");
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"times (s) x y z forces on structure (N)\n");
	   	fclose(file2);
  		}*/
  		
   	
  	if (Structure.nrj == 1)
  		{
  		strcpy(tonom,nomfichier);
	  	strcat(tonom,".nrj");
	  	file2 = fopen(tonom,"w");
	    	fprintf(file2,"\n");
	   	fclose(file2);
	   	}
   	
	printf("nb ball %d \n",Ball.nb);
   	for (zi = 1 ; zi<= Ball.nb; zi++) 
  		{
		printf("ball %d noeud %5d birth_time %lf  ",zi,Ball.noeud[zi],Ball.birth_time[zi]);
		printf("type %d stiffness %lf radius %lf  ",Ball.type[zi],Ball.stiffness[zi],Ball.radius[zi]);
		printf("position %lf %lf %lf\n",wf[3*Ball.noeud[zi]-2],wf[3*Ball.noeud[zi]-1],wf[3*Ball.noeud[zi]-0]);
  		}/**/

  	direct();
	//lectParam();
	lectParam2(nomfichier);
	etirement5();
	surglob2();
 	nbmaille_triangle();
 	initialisation_pondFS();		//calculation of lcube for elements and triangles
  	times = - Pascalcul;
	Nextstockage = Debutstockage;
	Nextscreen = 0;
	creedynamique(nomfichier);

	do
  		{
  		times = times + Pascalcul;
	  	for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++) 
			{
	    		Noeud[zi].precedent_ballast = Noeud[zi].volume_ballast;
			}
      		if ((Prise.catch_dynamic > 0.0) && (times > Pascalcul/2.0))
      			{
			/*printf("using of catch_dynamic %lf m^3/s\n",Prise.catch_dynamic);*/
  			Prise.volume = Prise.volume + Prise.catch_dynamic * Pascalcul;
			printf("Prise.volume %lf m^3  ",Prise.volume);
      			}
      		Structure.haul_energy = 0.0;
      		Structure.haul_power = 0.0;
      		hauling_cable(nomfichier);
		if (Structure.nb_ratio_drag_panel >= 2)	/*the netting Cd is reduced in case of times table*/
			{
			//printf("Structure.nb_ratio_drag_panel %d\n",Structure.nb_ratio_drag_panel);
      			for (zg=1;zg<=Structure.nb_ratio_drag_panel-1;zg++)
				{
				if ((times >= Structure.times_drag_panel[zg]) && (times <= Structure.times_drag_panel[zg+1]))
					{
					ratio_drag = Structure.ratio_drag_panel[zg] + (Structure.ratio_drag_panel[zg+1]-Structure.ratio_drag_panel[zg])*(times-Structure.times_drag_panel[zg])/(Structure.times_drag_panel[zg+1]-Structure.times_drag_panel[zg]);
					//printf("times %lf ratio %lf\n",times,ratio_drag);
					for (zi=1;zi<=NOMBRE_SURFACES;zi++)
					  	{ 
						Surface[zi].cdnormal            = panneau[Surface[zi].type].cdnormal * ratio_drag;
						}
					}
				}
			}
  		nbiter = 0;
  		nbpas = 0;
		actualiser_position(nomfichier);
		//actualiser_deplacement_balls();
		estime_position();
		Numtemps_relax = 1.0 * Numtemps_relax;/**/
		do
	  		{ 
	    		nbpas++; /*stockage step*/
	   		do
	    			{
	      			nbiter++;
				//lectParam();
				lectParam2(nomfichier);
	      			/*TEST_debut
				delta_x = 0.00000000001;
				for( zu = 1 ; zu <= 20 ; zu++ ) ecart[zu] = 0.0;
				for( zu = 0 ; zu <= 3*NOMBRE_NOEUDS+1 ; zu++ )
	      				{
	      				if (zu != 0) wf[zu] = wf[zu] + delta_x;
	      			TEST_fin*/
	      			
				////////////////////////////////////////////////////////////////////////////////////////////////////////////
				if(Sortie_texte.surface_filtree == 1)	
					{
					changement_variable2(0.0);  //in order to change the x coordinates in the towing direction
					//imprvectreel(30, wf);
					//imprvectreel(30, wfcodend);
					frx = wfcodend[3*1-2];
					for (elem = 1; elem<= NOMBRE_NOEUDS; elem++)
						{
						if (frx > wfcodend[3*elem-2])
							{
							frx = wfcodend[3*elem-2];
							}
						}
					surface_volume( frx,  &Structure.filtered_surface, &volumefr);
					}
				//exit(0);
				//printf("frx %lf sur %lf vol %lf ",frx,  surfacefr, volumefr);
				////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//surface();
				surface3();
				//vitesseh();
				vitesseh2();
				//gammah();
				gammah2();
	      			deplacement(nomfichier);
	      			misezero4();
 				miseajourPondFS_dyna();
				//printf(" wanoeua \n");	imprvectreel1(18, 3, wanoeud);     			
				//printf(" waelea \n");	imprvectreel1(18, 3, waelem);     			
				/*printf("mvb  ");imprvectreel(12, mvb);*/

	      			/*efforts sur les triangles de filet*/
				etirement5();			/*printf("etirement		ze[%5d][%5d] = %17.0lf\n",150,1500,ze[150][1500]);*/
				surglob2();			/*printf("surglob		ze[%5d][%5d] = %17.0lf\n",150,1500,ze[150][1500]);*/
				//for( zu = 1 ; zu <= 3*NOMBRE_NOEUDS ; zu++ )	if(isnan(wasurf[zu]))	printf("a wasurf(%d): %17.0lf      ",zu,wasurf[zu]);
				//printf("a wasurf \nStructure.haul_energy");	imprvectreel(150, wasurf);
	 			flexion2();/**/			/*printf("flexion		ze[%5d][%5d] = %17.0lf\n",150,1500,ze[150][1500]);*/
	 			fermeture2();/**/		/*printf("fermeture		ze[%5d][%5d] = %17.0lf\n",150,1500,ze[150][1500]);*/
				flotteursurf4();/**/		/*printf("flotteursurf		ze[%5d][%5d] = %17.0lf\n",150,1500,ze[150][1500]);*/
	      			pesanteurSurface();/**/		/*printf("pesanteurSurface	ze[%5d][%5d] = %17.0lf\n",150,1500,ze[150][1500]);*/
				/*pliage_triangle4();*/


				if((Prise.volume < Prise.seuil) && (Structure.nb_tarp_diamond  == 0) && (Structure.nb_tarp_hexa  == 0) && (Structure.nb_catch2_length  == 0) && (Structure.nb_catch2_surface  == 0) && (Structure.nb_catch2_volume  == 0) && (Structure.nb_cage_volume  == 0) && (Structure.nb_catch2_weight  == 0))
	      				{
					if (Structure.drag_forces_type == 1) filethydro3();		//The hydrodynamic forces on diamond netting is calculated using Morison formulations
					if (Structure.drag_forces_type == 2) calculeffort_zhan_dyna();	//The hydrodynamic forces on diamond netting is calculated using Zhan formulations
					//printf("filethydro3\n");imprvectreel1(435, 3, wasurf);
	      				}
	     			if (Prise.volume > Prise.seuil) 
	      				{
	       			catch_hexa();
	     				trainee_front();
	      				}
				//printf("b wasurf \n");	imprvectreel(150, wasurf);
     				if ((Prise.volume > Prise.seuil) && (Prise.catch_gravity == 0.0)) 
	      				{
	      				filethydro3();
	      				}
				//printf("c wasurf \n");	imprvectreel(150, wasurf);
 	     			if ((Prise.volume > Prise.seuil) && (Prise.catch_gravity > 0.0)) 
	      				{
					/*printf("Prise.catch_gravity = %17.0lf\n",Prise.catch_gravity);*/
	      				catch_hexa();
	      				}
				inertie_surface2();			
				//if (times >= 23.7) {printf("wasurf");imprvectreel1(129, 0, wasurf);}
	      			/*efforts sur les elements*/
				//if (nbiter >= 80)	{	printf("a %7.0lf ",waelem[443]);	}
				inertie_element2();/**/
				//if (times > 13.60) {printf("waelea");imprvectreel1(100, 0, waelem);}
				//if (times > 13.80) {exit(0);}
    				tension_bar();
				//if (times > 12.40) {printf("waeleb");imprvectreel1(250, 0, waelem);}
	      			pesanteurelem();/**/
				//if (times > 12.40) {printf("waelec");imprvectreel1(250, 0, waelem);}
				flotteurelement_dyna2();/**/
				//if (times > 12.40) {printf("waeled");imprvectreel1(250, 0, waelem);}
				trainee_element3_flottant();/**/
				//if (times > 12.40) {printf("waelee");imprvectreel1(250, 0, waelem);}
				pliage_barre_pardiso2_2();/**/	// code de raideur en flexion prenant en compte les symétries et le cas ou il y a plusieurs "poutres" en liaison			
				//printf(" wanoeuh \n");	imprvectreel1(18, 3, wanoeud);     			
				//printf(" waelec \n");	imprvectreel1(18, 3, waelem);     			
				pliage_barre_pardiso4();/**/	// code de raideur en flexion prenant en compte les symétries et le cas ou il y a plusieurs "poutres" en liaison
				//if (times > -1.0) {printf("waeleg");imprvectreel1(12, 0, waelem);}
				if (Structure.nb_ballast > 0) ballast_calcul_dyna1();
				//printf(" wanoeui \n");	imprvectreel1(18, 3, wanoeud);     			
				//printf(" waelec \n");	imprvectreel1(18, 3, waelem);     			
				if (Structure.nb_ballast > 0) ballast_quantite_mouvement1();
				//if (times > 0.5) printf("waelem\n");imprvectreel1(1032, 0, waelem);
				//contact1();
 				//if (times > 12.40) {printf("waelef");imprvectreel1(250, 0, waelem);}
 				//if (times > 12.50) {exit(0);}
 	
	      			/*efforts sur les coulisses*/
	      			tension_coulisses();
	     			raideur_coulisses();
	     			//contact_coulisses();/**/

	      			/*efforts sur les balls*/
	      			//ball_contact();/**/
	      			//ball_drag();/**/
				//ball_pesanteur();/**/
				//ball_netting_contact();/**/ 
				//ball_inertie();/**/
	  
				//printf(" wanoeuk \n");	imprvectreel1(18, 3, wanoeud);     			
				//printf(" waelee \n");	imprvectreel1(18, 3, waelem);     			
				/*efforts sur les noeuds*/ 
				//if (nbiter >= 1)	{printf("g wanoeud[66] %11.4lf",wanoeud[66]);	printf("welem[66] %11.4lf",waelem[66]);	printf("wasurf[66] %11.4lf\n",wasurf[66]);}
	      			inertie_noeud();/**/
				//if (nbiter >= 1)	{printf("h wanoeud[66] %11.4lf",wanoeud[66]);	printf("welem[66] %11.4lf",waelem[66]);	printf("wasurf[66] %11.4lf\n",wasurf[66]);}
	      			effortexterieurs_dyn();
				//if (nbiter >= 1)	{printf("i wanoeud[66] %11.4lf",wanoeud[66]);	printf("welem[66] %11.4lf",waelem[66]);	printf("wasurf[66] %11.4lf\n",wasurf[66]);}
	      			pesanteur();  
				//if (nbiter >= 1)	{printf("j wanoeud[66] %11.4lf",wanoeud[66]);	printf("welem[66] %11.4lf",waelem[66]);	printf("wasurf[66] %11.4lf\n",wasurf[66]);}
				trainee_noeud();
				//if (nbiter >= 1)	{printf("k wanoeud[66] %11.4lf",wanoeud[66]);	printf("welem[66] %11.4lf",waelem[66]);	printf("wasurf[66] %11.4lf\n",wasurf[66]);}
	      			flotteur2();
				//if (nbiter >= 1)	{printf("l wanoeud[66] %11.4lf",wanoeud[66]);	printf("welem[66] %11.4lf",waelem[66]);	printf("wasurf[66] %11.4lf\n",wasurf[66]);}
	      			spheric_limit1();
				//if (nbiter >= 1)	{printf("m wanoeud[66] %11.4lf",wanoeud[66]);	printf("welem[66] %11.4lf",waelem[66]);	printf("wasurf[66] %11.4lf\n",wasurf[66]);}
				if (Vent.vitesse > 0.0) traineevent1();
				//if (nbiter >= 1)	{printf("n wanoeud[66] %11.4lf",wanoeud[66]);	printf("welem[66] %11.4lf",waelem[66]);	printf("wasurf[66] %11.4lf\n",wasurf[66]);}
	      			fond_dyn();
	
	       			/*TEST_debut
	      				if (zu == 0) for( zw = 1 ; zw <= 3*NOMBRE_NOEUDS ; zw++ )   	
						{
						wa_surf[zw]  = wasurf[zw];
						wa_elem[zw]  = waelem[zw];
						wa_noeud[zw] = wanoeud[zw];
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
	      				}

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
	      					printf("ecart[%5d][%5d] = %17.0lf      ",ecartij[1][zu],ecartij[2][zu],ecart[zu]);
						printf("ze[%5d][%5d] = %17.0lf\n",ecartij[1][zu],ecartij[2][zu],ze[ecartij[1][zu]][ecartij[2][zu]]);
						}
	      				exit(0);
	      			TEST_fin*/      			
				symetrie2();
				//if (nbiter >= 1)	{printf("p wanoeud[66] %11.4lf",wanoeud[66]);	printf("welem[66] %11.4lf",waelem[66]);	printf("wasurf[66] %11.4lf\n",wasurf[66]);}
	      			chaineeff3();
	      			/*fond_dyn();*/
	      			transnoeud();
	      			modification4();
	       			
	      			RW = effortmax();
	      			RMEAN = effortmean();
	      			RSUM = effortsum();

				KLL = 0;
				KUU = 0;
	  			for (zi = 1 ; zi<= 3*NOMBRE_NOEUDS ; zi++)
	  				{
	  				if (KLL < (rang[1][zi] - zi)) 	KLL = (rang[1][zi] - zi);
	  				if (KLL < (zi - rang[4][zi])) 	KLL = (zi - rang[4][zi]);
	  				if (KUU < (rang[2][zi] - zi)) 	KUU = (rang[2][zi] - zi);
	  				if (KUU < (zi - rang[3][zi])) 	KUU = (zi - rang[3][zi]);
	  				}

				if (Structure.type_solver == 1)
				{
		      			resolution4();
		      			remonteb4();
      				}
      				else if (Structure.type_solver == 2)
      				{
					//realloc_pardiso();

					affectation();

					affectation_ia();

      					//resolution_mkl_pardiso();
					//exit(1);
      				}

	      			MW = mouvementmax();
	      			MMEAN = mouvementmean();
	      			MSUM = mouvementsum();
	      			if (Auto_convergence == 1) etat_convergence();/**/
	      			/*limitetronquee();*/
	      			coordonnees4();
	   			miseentension = modifraideur();
	      			if (Periodeimpression*(nbiter/Periodeimpression) == nbiter) 
	      				{
	        			iterationfin = 0.0;       			
       				if ( (RMEAN != 0.0)  && (precedent != 0.0) && (log( precedent / fabs(RMEAN )) != 0.0) ) iterationfin = log( fabs(RMEAN) / Seuilconvergence ) / log(precedent / fabs(RMEAN) );
       				else iterationfin = -1.0;      			
					printf("%6.2lf %2d %5d %15.4lf %13.5lf %13.4lf %8.5lf %11.4lf",times,nbpas, nbiter,RW,MW,RMEAN,MMEAN,Prise.epaisseur);
					printf(" %11.5lg",Numtemps_relax*Numtemps);

				

	        			if (iterationfin >= 0.0) printf(" %7.0lf\n", iterationfin + nbiter);
	        			if (iterationfin <  0.0) printf("\n");

	        			precedent = RMEAN;
					}
	   			}
	    			while (fabs(RMEAN)> Seuilconvergence  && nbiter < Nbmaxiterations) ;
	   			miseentension = modifraideur();
	   		}
	  		while (miseentension < 0 && nbiter < Nbmaxiterations) ;
			if (Energy_bottom.step > 0.0)	energy_bottom2();

	  		if (times >= Nextstockage ) 
	  			{
	  			Nextstockage = Nextstockage + Passtockage;
	  			if (Structure.nrj == 1) ecriturestatique3(nomfichier);
	  			ecrituredynamique(nomfichier);
				if (Structure.haul == 1) ecriturehauling(nomfichier);
	  			}
	  		if (times >= Nextscreen ) 
	  			{
	  			Nextscreen = Nextscreen + Passtockage;
				printf("Haul(W) %5.0lf ",Structure.haul_power);
				printf("Bottom(W) %5.0lf ",Bottom.power);
				printf("Cable(W) %5.0lf ",Structure.element_power);
				printf("Netting(W) %5.0lf ",Structure.surface_power);
				printf("Node(W) %5.0lf ",Structure.node_power);
				if(Sortie_texte.surface_filtree == 1)	printf("filtered_surface %4.0lf ",Structure.filtered_surface);
				printf("nb_iter %5d ", nbiter);
				printf("times/End %6.2lf /%6.2lf\n",times,Finstockage);
				}
		}
	while (times < Finstockage ) ;	
	if ((Energy_bottom.step > 0.0) && (Structure.nrj == 1)) ecriturestatique2(nomfichier);
	libere_memoire_dyna();
  	strcpy(tonom,nomfichier);
	j=strlen(tonom);
	while ((tonom[j])!='.' && j>0) j--;
	if (tonom[j]=='.') tonom[j]=0;
  	strcat(tonom,".par");
	sprintf(command,"rm %s",tonom);									
	system(command);	/*delete ps file*/
	}

