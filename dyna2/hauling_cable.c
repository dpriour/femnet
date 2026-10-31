#include "4c19.h"

void hauling_cable(char *nomfichier)
	{
	int zi,zj,no,trouve,zg,extremity,extrem_global,no_bar;
	double reduction,reduction_new;
	for (zi=1;zi<=Structure.NbTypeelem;zi++)
	{
		if (TypeElement[zi].nb_times >= 2)	/*the cable zi is reduced in case of times table*/
		{
			/*the hauling speed in m/s*/
			TypeElement[zi].haul_speed = 0.0;			/*the default hauling speed*/
      			for (zg=1;zg<=TypeElement[zi].nb_times-1;zg++)
			{
				if ((times >= TypeElement[zi].times[zg]) && (times <= TypeElement[zi].times[zg+1]))
				{
					if (TypeElement[zi].times[zg] != TypeElement[zi].times[zg+1])
					{
						TypeElement[zi].haul_speed = TypeElement[zi].haul_v[zg] + (TypeElement[zi].haul_v[zg+1]-TypeElement[zi].haul_v[zg])*(times-TypeElement[zi].times[zg])/(TypeElement[zi].times[zg+1]-TypeElement[zi].times[zg]);
						extremity = TypeElement[zi].haul_ext[zg];
					}
					else
					{
						TypeElement[zi].haul_speed = TypeElement[zi].haul_v[zg];
						extremity = TypeElement[zi].haul_ext[zg];

					}
				}
			}


			/*reduction in m*/				
			reduction = TypeElement[zi].haul_speed * Pascalcul;
			//printf("zi %d speed %lf reduction %lf haul_mini %lf haul_maxi %lf\n",zi,TypeElement[zi].haul_speed,reduction,TypeElement[zi].haul_mini,TypeElement[zi].haul_maxi);/**/
						
			/*printf("cable zi %d bar zj %d no %d speed %lf length bar %lf reduction %lf\n",zi,zj,no,TypeElement[zi].haul_speed,Element[zj].lgrepos,reduction);*/
			
			
			if (TypeElement[zi].haul_speed >= 0.0)	//hauling
			{
				trouve =  find_bar(TypeElement[zi].haul_speed, zi, extremity);
				TypeElement[zi].haul_bar = trouve;
				//TypeElement[zi].wt = Element[trouve].wt;	//stackage of the tension of the reduced bar in TypeElement[zi].wt
				//printf("zi %d  trouve  %d extremity %d  wt %lf\n",zi,trouve,extremity,TypeElement[zi].wt);
				if (trouve != 0)
				{
					if (Element[trouve].lgrepos - reduction > TypeElement[zi].haul_mini)
					{
						Element[trouve].lgrepos = Element[trouve].lgrepos - reduction;
						//TypeElement[zi].haul_energy = TypeElement[zi].haul_energy + reduction * Element[trouve].wt;
						TypeElement[zi].haul_energy = reduction * Element[trouve].wt;
						Structure.haul_energy += reduction * Element[trouve].wt;
						//printf(" lgrepos %6.2lf tension %6.0lf energy %6.0lf J ",Element[trouve].lgrepos,Element[trouve].wt,TypeElement[zi].haul_energy);/**/
						//printf("haul_energy %5.0lf \n",Structure.haul_energy);
					}
					else
					{
						//TypeElement[zi].haul_energy = TypeElement[zi].haul_energy + (Element[trouve].lgrepos - TypeElement[zi].haul_mini) * Element[trouve].wt;
						TypeElement[zi].haul_energy = (Element[trouve].lgrepos - TypeElement[zi].haul_mini) * Element[trouve].wt;
						Structure.haul_energy += (Element[trouve].lgrepos - TypeElement[zi].haul_mini) * Element[trouve].wt;
						//printf("l       %lf t       %lf e       %lf J    ",Element[trouve].lgrepos,Element[trouve].wt,TypeElement[zi].haul_energy);					
						//printf("o l d bar %d  ",TypeElement[zi].haul_bar);/**/
						reduction_new = reduction + TypeElement[zi].haul_mini - Element[trouve].lgrepos;
						Element[trouve].lgrepos = TypeElement[zi].haul_mini;
						/*research of the next bar*/
						trouve =  find_bar(TypeElement[zi].haul_speed, zi, extremity);
						//printf("zb %d  trouve  %d extremity %d\n",zi,trouve,extremity);
						if (trouve != 0)
						{
							Element[trouve].lgrepos = Element[trouve].lgrepos - reduction_new;
							//TypeElement[zi].haul_energy = TypeElement[zi].haul_energy + reduction_new * Element[trouve].wt;
							TypeElement[zi].haul_energy = reduction_new * Element[trouve].wt;
							Structure.haul_energy += reduction_new * Element[trouve].wt;
						}
					}
				}
			}
			if (TypeElement[zi].haul_speed < 0.0)	//shooting
			{
				trouve =  find_bar(TypeElement[zi].haul_speed, zi, extremity);
				TypeElement[zi].haul_bar = trouve;
				//TypeElement[zi].wt = Element[trouve].wt;
				//printf("zc %d  trouve  %d extremity %d\n",zi,trouve,extremity);
				if (trouve != 0)
				{
					if (Element[trouve].lgrepos - reduction < TypeElement[zi].haul_maxi)
					{
						Element[trouve].lgrepos = Element[trouve].lgrepos - reduction;
						//TypeElement[zi].haul_energy = TypeElement[zi].haul_energy + reduction * Element[trouve].wt;
						TypeElement[zi].haul_energy = reduction * Element[trouve].wt;
						Structure.haul_energy += reduction * Element[trouve].wt;						
						//printf("bar %d hauling lgrepos %lf tension %lf energy  %lf J    ",trouve,Element[trouve].lgrepos,Element[trouve].wt,TypeElement[zi].haul_energy);/**/
					}
					else
					{
						//TypeElement[zi].haul_energy = TypeElement[zi].haul_energy + (Element[trouve].lgrepos - TypeElement[zi].haul_maxi) * Element[trouve].wt;
						TypeElement[zi].haul_energy = (Element[trouve].lgrepos - TypeElement[zi].haul_maxi) * Element[trouve].wt;
						Structure.haul_energy += (Element[trouve].lgrepos - TypeElement[zi].haul_maxi) * Element[trouve].wt;
						//printf("o l d bar %d  ",TypeElement[zi].haul_bar);/**/
						reduction_new = reduction + TypeElement[zi].haul_maxi - Element[trouve].lgrepos;
						Element[trouve].lgrepos = TypeElement[zi].haul_maxi;
						//printf("bar %d l               %lf t       %lf e       %lf J    \n",trouve,Element[trouve].lgrepos,Element[trouve].wt,TypeElement[zi].haul_energy);					
						/*research of the next bar*/
						trouve =  find_bar(TypeElement[zi].haul_speed, zi, extremity);
						//printf("zd %d  trouve  %d extremity %d\n",zi,trouve,extremity);
						if (trouve != 0)
						{
							Element[trouve].lgrepos = Element[trouve].lgrepos - reduction_new;
							//TypeElement[zi].haul_energy = TypeElement[zi].haul_energy + reduction_new * Element[trouve].wt;
							TypeElement[zi].haul_energy = reduction_new * Element[trouve].wt;
							Structure.haul_energy += reduction_new * Element[trouve].wt;
							//printf("bar %d l               %lf t       %lf e       %lf J    ",trouve,Element[trouve].lgrepos,Element[trouve].wt,TypeElement[zi].haul_energy);					
						}
					}
				}
			}
		}
	}
	Structure.haul_power = Structure.haul_energy / Pascalcul;
}
 	
int find_bar(double speed, int cable, int extremity)
	{
	/*In case of cable hauling or shooting this function return the numero of the bar which is modified in function
	of speed (if >0 hauling, if <0 shooting) and in function of the extremity of the cable by which that starts*/
	int trouve,zg,no_bar;
	
	if (speed >= 0.0)	//hauling
		{
		/*research of the bar which is reduced = trouve*/
		if (extremity == 1)
			{
			/*in this case the cable bars are reduced beginning by the first of the list*/
			trouve = 0;
      			for (zg=1;zg<=TypeElement[cable].nb_barre;zg++)
				{
				no_bar = TypeElement[cable].barre[zg];
				//printf("ze %d no_bar %d trouve  %d lgrepos %lf extremity %d\n",zg,no_bar,trouve,Element[no_bar].lgrepos,extremity);
				if ((Element[no_bar].lgrepos>TypeElement[cable].haul_mini) && (trouve == 0))
					{
					trouve = no_bar;
					}
				}
			}
		if (extremity == 2)
			{
			/*in this case the cable bars are reduced beginning by the end of the list*/
			trouve = 0;
      			for (zg=TypeElement[cable].nb_barre;zg>=1;zg--)
				{
				no_bar = TypeElement[cable].barre[zg];
				//printf("zf %d no_bar %d trouve  %d lgrepos %lf extremity %d\n",zg,no_bar,trouve,Element[no_bar].lgrepos,extremity);
				if ((Element[no_bar].lgrepos>TypeElement[cable].haul_mini) && (trouve == 0))
					{
					trouve = no_bar;
					}
				}
			}
		}
	if (speed < 0.0)	//shooting
		{
		/*research of the bar which is reduced = trouve*/
		if (extremity == 2)
			{
			/*in this case the cable bars are reduced beginning by the first of the list because the drum is on extremity 2*/
			trouve = 0;
      			for (zg=1;zg<=TypeElement[cable].nb_barre;zg++)
				{
				no_bar = TypeElement[cable].barre[zg];
				//printf("zg %d no_bar %d trouve  %d lgrepos %lf extremity %d\n",zg,no_bar,trouve,Element[no_bar].lgrepos,extremity);
				if ((Element[no_bar].lgrepos<TypeElement[cable].haul_maxi) && (trouve == 0))
					{
					trouve = no_bar;
					}
				}
			}
		if (extremity == 1)
			{
			/*in this case the cable bars are reduced beginning by the end of the list because the drum is on extremity 1*/
			trouve = 0;
			//printf("nb_barre %d trouve  %d \n",TypeElement[cable].nb_barre,trouve);
      			for (zg=TypeElement[cable].nb_barre;zg>=1;zg--)
				{
				no_bar = TypeElement[cable].barre[zg];
				//printf("zh %d no_bar %d trouve  %d lgrepos %lf extremity %d\n",zg,no_bar,trouve,Element[no_bar].lgrepos,extremity);
				if ((Element[no_bar].lgrepos<TypeElement[cable].haul_maxi) && (trouve == 0))
					{
					trouve = no_bar;
					}
				}
			}
		}
	
	return trouve;
	}


