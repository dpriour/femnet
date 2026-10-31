#define PRINCIPAL 0
#include "4c19.h"  
//#define DEBUG
//#define DEBUG2

void ballast_calcul_dyna1()
	{
	/*force effect of ballast*/
	int zi,zk;
	double t1,t2,vol1,vol2,vol_cible;
	
	#ifdef DEBUG	
		printf("nb ballast  %d ",Structure.nb_ballast);
	#endif
	for (zi = 1; zi<= Structure.nb_ballast; zi++)
		{
		#ifdef DEBUG	
			printf("za %d Ballast[zi].nb_times %d times %lf vol_cible %lf\n",zi,Ballast[zi].nb_times,times,vol_cible);
		#endif
		if (times<Ballast[zi].times[1])
			{
			#ifdef DEBUG	
				printf("zb %d       times %lf vol_cible %lf\n",zi,times,vol_cible);
			#endif
			vol_cible = Ballast[zi].volume_table[1];
			#ifdef DEBUG	
				printf("zc %d       times %lf vol_cible %lf\n",zi,times,vol_cible);
			#endif
			}
		for (zk = 1; zk<= Ballast[zi].nb_times-1; zk++)
			{
			#ifdef DEBUG	
				printf("zd %d zk %d times %lf vol_cible %lf\n",zi,zk,times,vol_cible);
			#endif
			t1 = Ballast[zi].times[zk  ];
			t2 = Ballast[zi].times[zk+1];
			if ((times >= t1) && (times <= t2))
				{
				vol1 = Ballast[zi].volume_table[zk  ];
				vol2 = Ballast[zi].volume_table[zk+1];
				vol_cible = vol1 + (times-t1) / (t2-t1) * (vol2-vol1);
				}
			}
		#ifdef DEBUG	
			printf("ze %d       times %lf vol_cible %lf\n",zi,times,vol_cible);
		#endif
		if (times>Ballast[zi].times[Ballast[zi].nb_times])
			{
			#ifdef DEBUG	
				printf("zf %d       times %lf vol_cible %lf\n",zi,times,vol_cible);
			#endif
			vol_cible = Ballast[zi].volume_table[Ballast[zi].nb_times];
			#ifdef DEBUG	
				printf("zg %d       times %lf vol_cible %lf\n",zi,times,vol_cible);
			#endif
			}
		#ifdef DEBUG	
			printf("zh %d       times %lf vol_cible %lf\n",zi,times,vol_cible);
		#endif
		//Ballast[zi].speed = (vol_cible-Ballast[zi].volume) / Pascalcul;
		Ballast[zi].volume = vol_cible;
		//if (times >= 1.00) exit(0);
		#ifdef DEBUG	
			printf("zi %d       times %lf vol_cible %lf\n",zi,times,vol_cible);
		#endif
		}
	#ifdef DEBUG2	
		printf("zi %d       times %lf vol_cible %lf speed %lf\n",zi,times,vol_cible,Ballast[zi].speed);
	#endif
	ballast_calcul2();
	//if (times >= 1.0) exit(0);
	}				



