#define PRINCIPAL 0
#include "4c19.h"  

void ballast_calcul2()
	{
	/*force effect of ballast*/
	int zi,zj,zk,no_cable,int1;
	double minZ,maxZ,vol_node,lcube,altitude,volume_altitude,volume_precision;
	double verif_volume;
	
	volume_precision = Seuilconvergence / RHO / G / 10.0;
	//printf("nb ballast  %d\n",Structure.nb_ballast);

	//zero Noeud[zi].volume_ballast
	verif_volume = 0.0;
  	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++)
 		{
		Noeud[zi].volume_ballast = 0.0;
		}

	for (zi = 1; zi<=Structure.nb_ballast; zi++)
		{
		//printf("ballast %d vol_ballast %lf m³ cables nb %d\n",zi,Ballast[zi].volume,Ballast[zi].nb_cables);
		//minZ maxZ
		zj = 1;
		no_cable = Ballast[zi].cable[zj];
		vol_node = Ballast[zi].cable_volume[zj] / TypeElement[no_cable].nb_barre / 2.0;
		//vol_node = TypeElement[no_cable].lgrepos * PI * TypeElement[no_cable].diametrehydro * TypeElement[no_cable].diametrehydro / 4.0 / TypeElement[no_cable].nb_barre / 2.0;
		lcube = pow(vol_node,(1.0/3.0));	//size of the cubique volume per node
		//printf("cable %d vol_node %lf m³ lcube %lf m\n",no_cable,vol_node,lcube);
		for( zk = 1 ; zk <= NOMBRE_ELEMENTS ; zk++ )
			{
			if (Element[zk].type == no_cable)
				{
				minZ = wf[yb(zk,3)]-lcube/2.0;	//initial minZ for the dichotomy
				maxZ = wf[yb(zk,3)]+lcube/2.0;
				break;
				}
			}
		//printf("premier minZ %lf m maxZ %lf m\n",zk,minZ,maxZ);
		
		for (zj = 1; zj<= Ballast[zi].nb_cables; zj++)
			{
			no_cable = Ballast[zi].cable[zj];
			vol_node = Ballast[zi].cable_volume[zj] / TypeElement[no_cable].nb_barre / 2.0;
			//vol_node = TypeElement[no_cable].lgrepos * PI * TypeElement[no_cable].diametrehydro * TypeElement[no_cable].diametrehydro / 4.0 / TypeElement[no_cable].nb_barre / 2.0;
			lcube = pow(vol_node,(1.0/3.0));	//size of the cubique volume per node
			//printf("cable %d vol_node %lf m³ lcube %lf m\n",no_cable,vol_node,lcube);
			for( zk = 1 ; zk <= NOMBRE_ELEMENTS ; zk++ )
				{
				if (Element[zk].type == no_cable)
					{
					if (minZ > wf[yb(zk,3)]-lcube/2.0) minZ = wf[yb(zk,3)]-lcube/2.0;	//minZ for the dichotomy
					if (maxZ < wf[yb(zk,3)]+lcube/2.0) maxZ = wf[yb(zk,3)]+lcube/2.0;
					if (minZ > wf[yb(zk,6)]-lcube/2.0) minZ = wf[yb(zk,6)]-lcube/2.0;
					if (maxZ < wf[yb(zk,6)]+lcube/2.0) maxZ = wf[yb(zk,6)]+lcube/2.0;
					}
				}
			//printf("zk %d minZ %lf m maxZ %lf m\n",zk,minZ,maxZ);
			}
		//printf("minZ %lf m maxZ %lf m\n",minZ,maxZ);
		//exit(0);	
		do 
			{
			altitude = (minZ + maxZ) / 2.0;	//initial altitude
			volume_altitude = 0.0;
			for (zj = 1; zj<= Ballast[zi].nb_cables; zj++)
				{
				no_cable = Ballast[zi].cable[zj];
				vol_node = Ballast[zi].cable_volume[zj] / TypeElement[no_cable].nb_barre / 2.0;
				//vol_node = TypeElement[no_cable].lgrepos * PI * TypeElement[no_cable].diametrehydro * TypeElement[no_cable].diametrehydro / 4.0 / TypeElement[no_cable].nb_barre / 2.0;
				lcube = pow(vol_node,(1.0/3.0));	//size of the cubique volume per node
				for( zk = 1 ; zk <= NOMBRE_ELEMENTS ; zk++ )
					{
					if (Element[zk].type == no_cable)
						{
						//extremity 1
						if (altitude > wf[yb(zk,3)]+lcube/2.0)							//inonde
							{
							volume_altitude += vol_node;	
							}
						if ((altitude <= wf[yb(zk,3)]+lcube/2.0) && (altitude >= wf[yb(zk,3)]-lcube/2.0))	//flottant
							{
							volume_altitude += (altitude - wf[yb(zk,3)] + lcube/2.0)*lcube*lcube;
							}
						if (altitude < wf[yb(zk,3)]-lcube/2.0)							//exonde
							{
							}
						//extremity 2
						if (altitude > wf[yb(zk,6)]+lcube/2.0)
							{
							volume_altitude += vol_node;
							}
						if ((altitude <= wf[yb(zk,6)]+lcube/2.0) && (altitude >= wf[yb(zk,6)]-lcube/2.0))
							{
							volume_altitude += (altitude - wf[yb(zk,6)] + lcube/2.0)*lcube*lcube;
							}
						if (altitude < wf[yb(zk,6)]-lcube/2.0)
							{
							}
						}
					}
				}
			//printf("altitude %lf volume_altitude %lf m³ cible  %lf m³\n",altitude,volume_altitude,Ballast[zi].volume);
			if (volume_altitude > Ballast[zi].volume) maxZ = altitude;
			if (volume_altitude < Ballast[zi].volume) minZ = altitude;
			}
		while (fabs(volume_altitude-Ballast[zi].volume) > volume_precision);	
		//At this step altitude is known

		//force calculation
		for (zj = 1; zj<= Ballast[zi].nb_cables; zj++)
			{
			no_cable = Ballast[zi].cable[zj];
			vol_node = Ballast[zi].cable_volume[zj] / TypeElement[no_cable].nb_barre / 2.0;
			//vol_node = TypeElement[no_cable].lgrepos * PI * TypeElement[no_cable].diametrehydro * TypeElement[no_cable].diametrehydro / 4.0 / TypeElement[no_cable].nb_barre / 2.0;
			lcube = pow(vol_node,(1.0/3.0));	//size of the cubique volume per node
			for( zk = 1 ; zk <= NOMBRE_ELEMENTS ; zk++ )
				{
				if (Element[zk].type == no_cable)
					{
					//extremity 1
					//printf("lcube %lf\n",lcube);
					if (altitude > wf[yb(zk,3)]+lcube/2.0)							//inonde
						{
						volume_altitude = vol_node;			//volume of water on this node
						waelem[yb(zk,3)] -= volume_altitude * RHO * G;	//force on composant along Z
						int1 = (int) yb(zk,3)/3;			//node number
						Noeud[int1].volume_ballast += volume_altitude;	//volume of water on this node
						verif_volume += volume_altitude;
						}
					if ((altitude <= wf[yb(zk,3)]+lcube/2.0) && (altitude >= wf[yb(zk,3)]-lcube/2.0))	//flottant
						{
						volume_altitude = (altitude - wf[yb(zk,3)] + lcube/2.0)*lcube*lcube;
						waelem[yb(zk,3)] -= volume_altitude * RHO * G;
						ze[yb(zk,3)][eca] -= lcube * lcube * RHO * G;
						int1 = (int) yb(zk,3)/3;
						Noeud[int1].volume_ballast += volume_altitude;
						verif_volume += volume_altitude;
						}
					if (altitude < wf[yb(zk,3)]-lcube/2.0)							//exonde
						{
						}
					//extremity 2
					if (altitude > wf[yb(zk,6)]+lcube/2.0)							//inonde
						{
						volume_altitude = vol_node;
						waelem[yb(zk,6)] -= volume_altitude * RHO * G;
						int1 = (int) yb(zk,6)/3;
						Noeud[int1].volume_ballast += volume_altitude;
						verif_volume += volume_altitude;
						}
					if ((altitude <= wf[yb(zk,6)]+lcube/2.0) && (altitude >= wf[yb(zk,6)]-lcube/2.0))	//flottant
						{
						volume_altitude = (altitude - wf[yb(zk,6)] + lcube/2.0)*lcube*lcube;
						waelem[yb(zk,6)] -= volume_altitude * RHO * G;
						ze[yb(zk,6)][eca] -= lcube * lcube * RHO * G;
						int1 = (int) yb(zk,6)/3;
						Noeud[int1].volume_ballast += volume_altitude;
						verif_volume += volume_altitude;
						}
					if (altitude < wf[yb(zk,6)]-lcube/2.0)							//exone
						{
						}
					}
				}
			}
		Ballast[zi].altitude = altitude;
		//printf("ballast %d vol_ballast %lf m³ altitude %lf\n",zi,Ballast[zi].volume,altitude);
		//printf("verif_volume %lf m³ \n",verif_volume);
		}
	}						



