#define PRINCIPAL 0
#include "phobos.h"

void maillage_winch_libre(int wi)
	{
	int    zi, nb_coupe, deb, fin ;
	float  xdeb, xfin, ydeb, yfin, zdeb, zfin ;
	
	deb = winch[wi].extremite[1];
	fin = winch[wi].extremite[2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	nb_coupe = winch[wi].nb_barre;

	for (zi=1;zi<=nb_coupe - 1 ;zi++)
		{
		Structure.nb_barre_winch++;
		if ( Structure.nb_barre_winch>= NBMAXBARRE)
			{
			printf(" NBMAXBARRE trop petit %4d < %4d \n",NBMAXBARRE,Structure.nb_barre_winch );
			exit(0);
				}
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		/*creation des barre_winchs*/
		if (zi == 1) barre_winch[Structure.nb_barre_winch].noeud[1] = deb;
		if (zi != 1) barre_winch[Structure.nb_barre_winch].noeud[1] = Structure.nb_total - 1;
		barre_winch[Structure.nb_barre_winch].noeud[2] = Structure.nb_total;
		/*Le no de type de la barre_winch est le numero de l winch*/
		barre_winch[Structure.nb_barre_winch].type = wi;
		/*Creation d un noeud sur l winch*/
		winch[wi].noeud[zi] = Structure.nb_total;
		/*Creation du noeud*/
		noeud[Structure.nb_total].x = xdeb + zi * (xfin-xdeb) / nb_coupe;
		noeud[Structure.nb_total].y = ydeb + zi * (yfin-ydeb) / nb_coupe;
		noeud[Structure.nb_total].z = zdeb + zi * (zfin-zdeb) / nb_coupe;
		barre_winch[Structure.nb_barre_winch].pro[1] = (float) (zi-1) / nb_coupe ;
		barre_winch[Structure.nb_barre_winch].pro[2] = (float)  zi    / nb_coupe ;
		barre_winch[Structure.nb_barre_winch].longueur_repos = (float)  winch[wi].longueur_repos * fabs(barre_winch[Structure.nb_barre_winch].pro[1]-barre_winch[Structure.nb_barre_winch].pro[2]);
		noeud[Structure.nb_total].type = winch[wi].type_noeud;
		}
	Structure.nb_barre_winch++;
	if (Structure.nb_barre_winch >= NBMAXBARRE)
		{
		printf(" NBMAXBARRE trop petit %4d < %4d \n",NBMAXBARRE,Structure.nb_barre_winch );
		exit(0);
		}
	if (nb_coupe >  1) 
		{
		barre_winch[Structure.nb_barre_winch].noeud[1] = Structure.nb_total;
		barre_winch[Structure.nb_barre_winch].pro[1] = (float) (nb_coupe - 1) / nb_coupe ;
		}
	if (nb_coupe == 1) 
		{
		barre_winch[Structure.nb_barre_winch].noeud[1] = deb;
		barre_winch[Structure.nb_barre_winch].pro[1] = 0.0 ;
		}
	barre_winch[Structure.nb_barre_winch].noeud[2] = fin;
	barre_winch[Structure.nb_barre_winch].pro[2] = 1.0;
	barre_winch[Structure.nb_barre_winch].longueur_repos = (float)  winch[wi].longueur_repos * fabs(barre_winch[Structure.nb_barre_winch].pro[1]-barre_winch[Structure.nb_barre_winch].pro[2]);
	barre_winch[Structure.nb_barre_winch].type = wi;
	
	printf(" wi= %4d ",wi);
	printf(" Structure.nb_barre_winch= %4d \n",Structure.nb_barre_winch);
	printf(" Structure.nb_total= %4d \n",Structure.nb_total);
	}
	
