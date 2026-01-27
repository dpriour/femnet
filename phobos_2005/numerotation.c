#define PRINCIPAL 0
#include "phobos.h"

void numerotation_globale()
	{
	/*renumerotation de tous les noeuds pour tenir compte des liaisons et des liens entre noeuds*/
	int no,co,liaison_trouve,noeud_reference,mode,el,te,ex,element_trouve,type_trouve,int_tmp;
	
	if (Structure.graphic == 1)
		{
		/*faire le filet_interne si ce n est pas fait*/
		mode = GetMenuItemChecked(w[27]);
		if (mode == 0) filet_interne();
		}
	
	printf("beginning  numerotation_globale\n" );
	
	/*copie de tous  noeud dans noeud_global*/
	for (no=1;no<=Structure.nb_total;no++)
		{
		total2global[no] = no;
		}

	Structure.nb_global = Structure.nb_total;
	
	for (no=Structure.nb_total;no>=1;no--)
		{
		element_trouve = appartient_numero_element(no);		//bar or triangle numero
		type_trouve = appartient_type_element(no);		//1 coulisse, 2 barre, 3 winch, 4 surface_hexa, 5 surface	
		liaison_trouve = appartient_liaison(no);
		noeud_reference = 0;
		
		if ((liaison_trouve != 0) && (element_trouve != 0))
			{
			noeud_reference = noeud_reference_liaison(liaison_trouve);
			if (noeud_reference != no)
				{
				/*on elimine le noeud no qui sera affecte a noeud_reference*/
				total2global[no] = noeud_reference;
				Structure.nb_global--;
				for (co=no+1;co<=Structure.nb_total;co++)
					{
					if (total2global[co] > no)
						{
						total2global[co] = total2global[co] - 1;
						}
					}
				}
			}		
		//printf("no %4d liaison_trouve %4d noeud_reference %4d ",no,liaison_trouve,noeud_reference);/**/
		//printf("element_trouve  %4d type_trouve  %4d\n",element_trouve,type_trouve);/**/
		if (element_trouve == 0)
			{
			/*on elimine le noeud no puisqu il n est pas attache a un element, il sera affecte a 0*/
			total2global[no] = 0;
			Structure.nb_global--;
			//printf("nb_global %4d el %4d \n",Structure.nb_global,no);
			for (co=no+1;co<=Structure.nb_total;co++)
				{
				if (total2global[co] > no)
					{
					total2global[co] = total2global[co] - 1;
					}
				}
			}
		//printf("nototal %4d liaison %4d element %4d type %4d  ",no,liaison_trouve,element_trouve,type_trouve);/**/
		//printf("noeud_ref %4d ",noeud_reference);/**/
		//printf("glob %4d \n",total2global[no]);/**/
		}
		
	/*for (no=1;no<=Structure.nb_total;no++)
		{
		printf("nototal %4d noglob %4d\n",no,total2global[no]);
		}*/
	if (Structure.total1 != 0)
		{
		printf("The total node %d and %d are linked\n",Structure.total1,Structure.total2);
		int_tmp = total2global[Structure.total2];
		total2global[Structure.total2] = total2global[Structure.total1];
		Structure.nb_global--;
		for (co=1;co<=Structure.nb_total;co++)
			{
			if (total2global[co] > int_tmp)
				{
				total2global[co] = total2global[co] - 1;
				}
			}
		}
		
	/*for (no=1;no<=Structure.nb_total;no++)
		{
		printf("total2global[%4d] = %4d\n",no,total2global[no] );
		}*/
	/*calcul des nouvelles coordonnees des points renumerotes*/
	for (no=1;no<=Structure.nb_total;no++)
		{
		if (total2global[no] >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,total2global[no] );
			exit(0);
			}
		noeud_global[total2global[no]] = noeud[no];
		}
	
	/*
	for (no=1;no<=Structure.nb_liaison;no++)
		{
		if (total2global[Lien[no].noeud[1]] >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,total2global[Lien[no].noeud[1]] );
			exit(0);
			}
		noeud_global[total2global[Lien[no].noeud[1]]].x = 0.0;
		noeud_global[total2global[Lien[no].noeud[1]]].y = 0.0;
		noeud_global[total2global[Lien[no].noeud[1]]].z = 0.0;
		for (co=1;co<=Lien[no].nb_liaison;co++)
			{
			if (total2global[Lien[no].noeud[co]] >= NBMAXNOEUD)
				{
				printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,total2global[Lien[no].noeud[co]] );
				exit(0);
				}
			noeud_global[total2global[Lien[no].noeud[co]]].x += noeud[Lien[no].noeud[co]].x / Lien[no].nb_liaison;
			noeud_global[total2global[Lien[no].noeud[co]]].y += noeud[Lien[no].noeud[co]].y / Lien[no].nb_liaison;
			noeud_global[total2global[Lien[no].noeud[co]]].z += noeud[Lien[no].noeud[co]].z / Lien[no].nb_liaison;
			}
		}
	*/
	
	//printf("Structure.nb_liaison %4d\n",Structure.nb_liaison);
	//printf("Structure.nb_lien %4d\n",Structure.nb_lien);
	//exit(0);
		
	for (no=1;no<=Structure.nb_lien;no++)
		{
		noeud_reference = noeud_reference_liaison(no);
		//printf("noeud_reference %4d total2global[noeud_reference] %4d\n",noeud_reference,total2global[noeud_reference]);
		if (total2global[noeud_reference] >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,total2global[noeud_reference] );
			exit(0);
			}
		noeud_global[total2global[noeud_reference]].x = 0.0;
		noeud_global[total2global[noeud_reference]].y = 0.0;
		noeud_global[total2global[noeud_reference]].z = 0.0;
		for (co=1;co<=Lien[no].nb_liaison;co++)
			{
			//printf("no %4d \n",no);
			if (total2global[Lien[no].noeud[co]] >= NBMAXNOEUD)
				{
				printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,total2global[Lien[no].noeud[co]] );
				exit(0);
				}
			noeud_global[total2global[noeud_reference]].x += noeud[Lien[no].noeud[co]].x / Lien[no].nb_liaison;
			noeud_global[total2global[noeud_reference]].y += noeud[Lien[no].noeud[co]].y / Lien[no].nb_liaison;
			noeud_global[total2global[noeud_reference]].z += noeud[Lien[no].noeud[co]].z / Lien[no].nb_liaison;
			}
		}

	printf("Structure.nb_total  %4d \n",Structure.nb_total);
	printf("Structure.nb_global %4d \n",Structure.nb_global);
		
	/*
	mise a jour du numero de noeud situe en extremite d element
	a l endroit ou on veut la sortie de la tension 
	de l element, pour le mettre en numerotation globale
	*/
	
	for (te=1;te<=Sortie_texte.nb_tension_element;te++)
		{
		printf("tension no %d    ",te );
		ex = Sortie_texte.element_extremite[te];
		el = Sortie_texte.element_tension[te];
		
		printf("extremity %d    ", ex);
		printf("element %d   ", el);
		
		/*
		ici ex est l extremite de l element
		el ou on veut la tension
		ex est egal a 1 ou 2 tel que defini dans le fichier *.don
		*/
		
		co = element[el].extremite[ex];
		printf("node no total %d    ", co);
		
		/*
		co est le numero d extremite en numerotation totale
		*/
		
		Sortie_texte.element_extremite[te] = total2global[co];
		/*exit(0);*/
		
		printf("node no global %d  \n", Sortie_texte.element_extremite[te]);
		
		/*
		et maintenant en numerotation globale
		*/
		}
	printf("end of  numerotation_globale  \n");
	
	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[2],1);
		}
	
	for ( no = 1 ; no <= Structure.nombreSurfHexa ; no++ )
		{
		printf("triangle %4d : ", no );
		printf("sommets %4d  %4d  %4d\n",surf_hexa[no].extremite[1],surf_hexa[no].extremite[2],surf_hexa[no].extremite[3]);
		}
	for ( no = 1 ; no <= Structure.nombreSurfHexa ; no++ )
		{
		printf("triangle %4d : ", no );
		printf("sommets %4d  %4d  %4d\n",total2global[surf_hexa[no].extremite[1]],total2global[surf_hexa[no].extremite[2]],total2global[surf_hexa[no].extremite[3]]);
		}
	}
	
	
int noeud_reference_liaison(int no_liaison)
	{
	/*renvoie le numero du noeud de reference de la liaison 
	c a d le noeud dont le numero est le plus petit dans
	cette liaison et qui appartient à un élément*/
	int no_ref,co;
	
	no_ref = Structure.nb_total;
	for (co=1;co<=Lien[no_liaison].nb_liaison;co++)
		{
		if((Lien[no_liaison].noeud[co] < no_ref) && (appartient_numero_element(Lien[no_liaison].noeud[co]) != 0))
			{
			no_ref = Lien[no_liaison].noeud[co];
			}
		}
	return no_ref;
	}
	
	
