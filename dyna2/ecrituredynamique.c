#include "4c19.h"

int ecrituredynamique(nomfichier)
char *nomfichier;
	{
  	char   tonom[100];
  	FILE   *f2;
  	int    elem,zi,zk,node,component;
  	double elongation,value,x1,y1,z1;

  	/*ecriture des coordonnees a l equilibre dynamique dans le meme ordre que dans le fichier de donnees*/
  	strcpy(tonom,nomfichier);
  	strcat(tonom,".dyn");
  	f2 = fopen(tonom,"a");
    	fprintf(f2,"  %11.3lf",times);
  	for (elem = 1 ; elem<= NOMBRE_NOEUDS ; elem++) 
  		{
    		fprintf(f2," %11.6lf",wf[3*fixa[elem]-2]);
    		fprintf(f2," %11.6lf",wf[3*fixa[elem]-1]);
    		fprintf(f2," %11.6lf",wf[3*fixa[elem]-0]);
 		}
    		fprintf(f2,"\n");
   	fclose(f2);

  	/*ecriture des tensions de barres*/
	if(Sortie_texte.bar_tension == 1)	
		{
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".ten");	
	  	f2 = fopen(tonom,"a");
	    	fprintf(f2,"  %11.3lf",times);
	  	for (zi = 1 ; zi<= NOMBRE_ELEMENTS ; zi++) 
	  		{
			fprintf(f2," %8.2lf ", (Element[zi].lgtendue-Element[zi].lgrepos) * Element[zi].raideur_effective / Element[zi].lgrepos);
	 		}
	    	fprintf(f2,"\n");
   		fclose(f2);
	    	}

  	/*ecriture des tensions de twines*/
	if(Sortie_texte.diamond_tension == 1)	
		{
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".ted");	
	  	f2 = fopen(tonom,"a");
	    	fprintf(f2,"  %11.3lf",times);
	  	for (zi = 1 ; zi<= NOMBRE_SURFACES; zi++) 
	  		{
			fprintf(f2," %9.3lf %9.3lf ", Surface[zi].tension1, Surface[zi].tension2);
	 		}
	    	fprintf(f2,"\n");
   		fclose(f2);
	    	}

  	/*writting tensions of hauling if any*/
	if(Structure.hauling_cable4_tension == 1)	
		{
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".hwt");	
	  	f2 = fopen(tonom,"a");
	    	fprintf(f2,"  %11.3lf",times);
		for (zi=1;zi<=Structure.NbTypeelem;zi++)
			{
			if (TypeElement[zi].nb_times >= 2)	/*the cable zi is reduced in case of times table*/
				{
    				//fprintf(f2," %d",TypeElement[zi].haul_bar);
    				//fprintf(f2," %11.6lf",TypeElement[zi].wt);
    				fprintf(f2," %11.6lf",Element[TypeElement[zi].haul_bar].wt);
	 			}
	 		}
	    	fprintf(f2,"\n");
   		fclose(f2);
	    	}
  	/*ecriture ballast*/
	if(Structure.ballast_altitude == 1)	
		{
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".bal");	
	  	f2 = fopen(tonom,"a");
	    	fprintf(f2,"%11.3lf  ",times);
		for (zi = 1; zi<=Structure.nb_ballast; zi++)
			{
			fprintf(f2," %4d  %14.7lf   %14.7lf  ",zi,Ballast[zi].altitude,Ballast[zi].volume);
			//printf("ballast: %4d, altitude: %10.3lf (m)\n",zi,Ballast[zi].altitude);
			}
	    	fprintf(f2,"\n");
   		fclose(f2);
	    	}
  	/*ecriture centre gravite et de poussee*/
	if (Structure.total_mass != 0.0)
		{
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".cgp");	
	  	f2 = fopen(tonom,"a");
	    	fprintf(f2,"%11.3lf  ",times);
	 	Structure.total_mass = 0.0;
	 	Structure.total_volume_floatability = 0.0;
	  	for (zi = 1 ; zi<= NOMBRE_ELEMENTS ; zi++) 
	  		{
	 		value = Element[zi].mass/ 2.0;
			//printf("value %lf \n",value);
 	 		//extremity 1
	 		x1 = (Structure.x_g*Structure.total_mass + wf[yb(zi,1)]*value) / (Structure.total_mass+value);
	 		y1 = (Structure.y_g*Structure.total_mass + wf[yb(zi,2)]*value) / (Structure.total_mass+value);
	 		z1 = (Structure.z_g*Structure.total_mass + wf[yb(zi,3)]*value) / (Structure.total_mass+value);
	 		Structure.total_mass += value;
	 		Structure.x_g = x1;
	 		Structure.y_g = y1;
	 		Structure.z_g = z1;
	 		//extremity 2
	 		x1 = (Structure.x_g*Structure.total_mass + wf[yb(zi,4)]*value) / (Structure.total_mass+value);
	 		y1 = (Structure.y_g*Structure.total_mass + wf[yb(zi,5)]*value) / (Structure.total_mass+value);
	 		z1 = (Structure.z_g*Structure.total_mass + wf[yb(zi,6)]*value) / (Structure.total_mass+value);
	 		Structure.total_mass += value;
	 		Structure.x_g = x1;
	 		Structure.y_g = y1;
	 		Structure.z_g = z1;
			}
		if (Structure.nb_ballast > 0)
			{
			for( zk = 1 ; zk <= NOMBRE_NOEUDS ; zk++ )
				{
				if (Noeud[zk].volume_ballast > 0.0)
					{
					value = Noeud[zk].volume_ballast * RHO;
					//printf("zk %4d volume_ballast %lf\n",zk,Noeud[int1].volume_ballast);
			 		x1 = (Structure.x_g*Structure.total_mass + wf[3*zk-2]*value) / (Structure.total_mass+value);
			 		y1 = (Structure.y_g*Structure.total_mass + wf[3*zk-1]*value) / (Structure.total_mass+value);
			 		z1 = (Structure.z_g*Structure.total_mass + wf[3*zk-0]*value) / (Structure.total_mass+value);
			 		Structure.total_mass += value;
			 		Structure.x_g = x1;
			 		Structure.y_g = y1;
			 		Structure.z_g = z1;
					}
				}
			}
			
		for (zi = 1 ; zi<= NOMBRE_ELEMENTS ; zi++) 
	  		{
			if (TypeElement[Element[zi].type].noeud_trainee == 1) //volume des barres reporté dans des cubes centrés sur les 2 extremités de la barre
				{
				//extremite 1
				value = Element[zi].lcube * Element[zi].lcube * Element[zi].lcube * Element[zi].pondFS[1];
		 		x1 = (Structure.x_p*Structure.total_volume_floatability + wf[yb(zi,1)]*value) / (Structure.total_volume_floatability+value);
		 		y1 = (Structure.y_p*Structure.total_volume_floatability + wf[yb(zi,2)]*value) / (Structure.total_volume_floatability+value);
		 		z1 = (Structure.z_p*Structure.total_volume_floatability + wf[yb(zi,3)]*value) / (Structure.total_volume_floatability+value);
		 		Structure.total_volume_floatability += value;
		 		Structure.x_p = x1;
		 		Structure.y_p = y1;
		 		Structure.z_p = z1;
				//extremite 2
				value = Element[zi].lcube * Element[zi].lcube * Element[zi].lcube * Element[zi].pondFS[2];
		 		x1 = (Structure.x_p*Structure.total_volume_floatability + wf[yb(zi,4)]*value) / (Structure.total_volume_floatability+value);
		 		y1 = (Structure.y_p*Structure.total_volume_floatability + wf[yb(zi,5)]*value) / (Structure.total_volume_floatability+value);
		 		z1 = (Structure.z_p*Structure.total_volume_floatability + wf[yb(zi,6)]*value) / (Structure.total_volume_floatability+value);
		 		Structure.total_volume_floatability += value;
		 		Structure.x_p = x1;
		 		Structure.y_p = y1;
		 		Structure.z_p = z1;
				}
			}
		fprintf(f2,"%lf  %lf  %lf  %lf       ",Structure.total_mass               ,Structure.x_g,Structure.y_g,Structure.z_g);
		fprintf(f2,"%lf  %lf  %lf  %lf\n",Structure.total_volume_floatability,Structure.x_p,Structure.y_p,Structure.z_p);
   		fclose(f2);
	    	}
  	/*ecriture netting volume*/
	if(Structure.netting_volume_calculation == 1)	
		{
		double volumefront,surfacefront;
		for( zk = 1 ; zk <= NOMBRE_NOEUDS ; zk++ )
			{
			wfcodend[3*zk-2] = wf[3*zk-2];
			wfcodend[3*zk-1] = wf[3*zk-1];
			wfcodend[3*zk-0] = wf[3*zk-0];
			}
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".vol");	
	  	f2 = fopen(tonom,"a");
	    	fprintf(f2,"%11.3lf  ",times);
		surface_volume(Structure.front_netting_volume, &surfacefront, &volumefront);
		fprintf(f2," %lf  ",surfacefront);
		fprintf(f2," %lf\n",volumefront);
   		fclose(f2);
	    	}

  	if(Sortie_texte.effort_structure == 1)
		{
  		/*effortstructur();
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".eff");	
	  	f2 = fopen(tonom,"a");
	    	fprintf(f2,"%11.3lf  ",times);
		fprintf(f2," %lf  ",wa[1]);
		fprintf(f2," %lf  ",wa[2]);
		fprintf(f2," %lf\n",wa[3]);
   		fclose(f2);*/
   		
		strcpy(tonom,nomfichier);
	  	strcat(tonom,".efg");	
	  	f2 = fopen(tonom,"a");
	    	fprintf(f2,"%11.3lf ",times);
	     	for ( zi = 1 ; zi <= Structure.nb_fixed_components ; zi++ )
	     	{ 
	     		node = fixa[Structure.list_fixed_node[zi]];
	     		component = 3 * node + Structure.list_fixed_axe[zi] - 3;
			fprintf(f2," %10.2lf  ",wasurf[component] + waelem[component] + wanoeud[component]);
			//fprintf(f2," %10.2lf  ",mvh[component]);
		}
		fprintf(f2,"\n");
		fclose(f2);
	    	}

	}
