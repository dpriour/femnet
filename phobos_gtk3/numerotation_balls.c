#define PRINCIPAL 0
#include "phobos.h"

void numerotation_balls()
	{
	/*renumerotation de tous les noeuds pour tenir compte des liaisons et
	des liens entre noeuds*/
	int no,co,liaison_trouve,noeud_reference,mode,el,te,ex,element_trouve;
	float volume_balls;
	
	if (Structure.graphic == 1)
		{
		/*faire le numerotation_globale si ce n est pas fait*/
		mode = GetMenuItemChecked(w[2]);
		if (mode == 0) numerotation_globale();
		}
	
	printf("debut  numerotation_balls  \n" );
	volume_balls = 0.0;
	
	for (no=1;no<=Ball.nb;no++)
		{
		Structure.nb_global++;
		Structure.nb_total++;
		total2global[Structure.nb_total] = Structure.nb_global;
		Ball.noeud[no] = Structure.nb_total;
		/*printf("no %4d total %4d global %4d\n",no,Structure.nb_total,Structure.nb_global);*/
		noeud_global[Structure.nb_global].x = Ball.x[no];
		noeud_global[Structure.nb_global].y = Ball.y[no];
		noeud_global[Structure.nb_global].z = Ball.z[no];
		noeud[Structure.nb_total].x = Ball.x[no];
		noeud[Structure.nb_total].y = Ball.y[no];
		noeud[Structure.nb_total].z = Ball.z[no];
		noeud[Structure.nb_total].type = Ball.type[no];
		volume_balls = volume_balls + 4.0 / 3.0 * PI * Ball.radius[no] * Ball.radius[no] * Ball.radius[no];
		/*printf("noeud[ %4d].type  %4d\n",Structure.nb_total,noeud[Structure.nb_total].type);*/
		noeud_global[total2global[Structure.nb_total]] = noeud[Structure.nb_total];
		}
	printf("Structure.nb_global %4d Structure.nb_total %4d\n",Structure.nb_global,Structure.nb_total);
	printf("Total balls volume %f m^3\n",volume_balls);
	printf("fin  numerotation_balls  \n" );
	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[88],1);
		}
	}
	
	
