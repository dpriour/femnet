#define PRINCIPAL 0
#include "phobos.h"
	
	/* 
	maillage des panneaux en creant des points independament des noeuds reels du filet
	
	ATTENTION : pour le maillage interne, il est possible de modifier le facteur de determination des
	noeuds trop proches du contour ou d un autre noeud - voir fact dans maillage_interne3 
	*/

void maillage_panneau1()
	{
	int  pa, mode;
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		printf("Panneau = %12d \n",pa);
		printf("le pas du maillage  = %12.2f \n",panneau[pa].pas_maillage);
		}
	 
	/*FAIRE LE FILET_CONTOUR SI CE N EST PAS FAIT*/
	mode = GetMenuItemChecked(w[5]);
	if (mode == 0) filet_contour();

	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		if (panneau[pa].flag_maillage == 0)
			{
			if (panneau[pa].pas_maillage <= 0.0)
				{
				printf("ERREUR \n");
				printf("le pas du maillage n est pas positif = %12.2f \n",panneau[pa].pas_maillage);
				printf("Panneau = %12d \n",pa);
				exit(0);
				}
			panneau[pa].nb_noeud_cote = 0;
			/**********************************************/
  			panneau[pa].noeud_cote = (int *) malloc(1 * sizeof(int));
			if (panneau[pa].noeud_cote    == NULL)
				{
				printf(" panneau[pa].noeud_cote 1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			panneau[pa].prop_cote = (float *) malloc(1 * sizeof(float));
			if (panneau[pa].prop_cote    == NULL)
				{
				printf(" panneau[pa].prop_cote 1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
			maillage_contour1(pa);
			maillage_interne2(pa);
			panneau[pa].flag_maillage = 1;
			}
		}
		
	printf("Structure.nb_total = %4d \n",Structure.nb_total);

	SetMenuItemChecked(w[26],1);
	}
	
int appartient_liaison(int no_noeud)
	{
	/*RENVOIE LE NUMERO DU LIEN AUQUEL LE NOEUD EST RELIE, SINON 0*/
	int no_liaison,pa,co;
	
	no_liaison = 0;
	for (pa=1;pa<=Structure.nb_lien;pa++)
		{ 
		for (co=1;co<=Lien[pa].nb_liaison;co++)
			{
			if(Lien[pa].noeud[co] == no_noeud)
				{
				no_liaison = pa;
				break;
				}
			}
		}
	return no_liaison;
	}
	
	
int appartient_numero_element(int no_noeud)
	{
	/*RENVOIE LE NUMERO de l'element auquel LE NOEUD EST RELIE, SINON 0*/
	int no_element,pa,co;
	
	no_element = 0;

	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		if(coulisse[pa].extremite[1] == no_noeud)
			{
			no_element = pa;
			break;
			}
		if(coulisse[pa].extremite[2] == no_noeud)
			{
			no_element = pa;
			break;
			}
		for (co=1;co<=coulisse[pa].nb_noeud;co++)
			{ 
			if(coulisse[pa].noeud[co] == no_noeud)
				{
				no_element = pa;
				break;
				}
			}
		}

	for (pa=1;pa<=Structure.nb_barre;pa++)
		{ 
		if(barre[pa].noeud[1] == no_noeud)
			{
			no_element = pa;
			break;
			}
		if(barre[pa].noeud[2] == no_noeud)
			{
			no_element = pa;
			break;
			}
		}

	for (pa=1;pa<=Structure.nb_barre_winch;pa++)
		{ 
		if(barre_winch[pa].noeud[1] == no_noeud)
			{
			no_element = pa;
			break;
			}
		if(barre_winch[pa].noeud[2] == no_noeud)
			{
			no_element = pa;
			break;
			}
		}

	for (pa=1;pa<=Structure.nombreSurfHexa;pa++)
		{ 
		if(surf_hexa[pa].extremite[1] == no_noeud)
			{
			no_element = pa;
			break;
			}
		if(surf_hexa[pa].extremite[2] == no_noeud)
			{
			no_element = pa;
			break;
			}
		if(surf_hexa[pa].extremite[3] == no_noeud)
			{
			no_element = pa;
			break;
			}
		}

	for (pa=1;pa<=Structure.nombreSurfaces;pa++)
		{ 
		if(surface[pa].extremite[1] == no_noeud)
			{
			no_element = pa;
			break;
			}
		if(surface[pa].extremite[2] == no_noeud)
			{
			no_element = pa;
			break;
			}
		if(surface[pa].extremite[3] == no_noeud)
			{
			no_element = pa;
			break;
			}
		}

	return no_element;
	}
	
	
int appartient_type_element(int no_noeud)
	{
	/*RENVOIE LE type de l'element auquel LE NOEUD EST RELIE, SINON 0
	si 1 coulisse
	si 2 barre
	si 3 winch
	si 4 surface_hexa
	si 5 surface*/
	int no_element,pa,co;
	
	no_element = 0;

	for (pa=1;pa<=Structure.nombreCoulisses;pa++)
		{ 
		if(coulisse[pa].extremite[1] == no_noeud)
			{
			no_element = 1;
			break;
			}
		if(coulisse[pa].extremite[2] == no_noeud)
			{
			no_element = 1;
			break;
			}
		for (co=1;co<=coulisse[pa].nb_noeud;co++)
			{ 
			if(coulisse[pa].noeud[co] == no_noeud)
				{
				no_element = 1;
				break;
				}
			}
		}

	for (pa=1;pa<=Structure.nb_barre;pa++)
		{ 
		if(barre[pa].noeud[1] == no_noeud)
			{
			no_element = 2;
			break;
			}
		if(barre[pa].noeud[2] == no_noeud)
			{
			no_element = 2;
			break;
			}
		}

	for (pa=1;pa<=Structure.nb_barre_winch;pa++)
		{ 
		if(barre_winch[pa].noeud[1] == no_noeud)
			{
			no_element = 3;
			break;
			}
		if(barre_winch[pa].noeud[2] == no_noeud)
			{
			no_element = 3;
			break;
			}
		}

	for (pa=1;pa<=Structure.nombreSurfHexa;pa++)
		{ 
		if(surf_hexa[pa].extremite[1] == no_noeud)
			{
			no_element = 4;
			break;
			}
		if(surf_hexa[pa].extremite[2] == no_noeud)
			{
			no_element = 4;
			break;
			}
		if(surf_hexa[pa].extremite[3] == no_noeud)
			{
			no_element = 4;
			break;
			}
		}

	for (pa=1;pa<=Structure.nombreSurfaces;pa++)
		{ 
		if(surface[pa].extremite[1] == no_noeud)
			{
			no_element = 5;
			break;
			}
		if(surface[pa].extremite[2] == no_noeud)
			{
			no_element = 5;
			break;
			}
		if(surface[pa].extremite[3] == no_noeud)
			{
			no_element = 5;
			break;
			}
		}

	return no_element;
	}
	
	
int liaison_maille(int neud,int pannea,char *structur,int *nostructur,int *debutsegm,int *finsegm)
	{
	/*
	NEUD = DEBUT DU SEGMENT TRAITE,
	PANNEA = PANNEAU TRAITE,
	RENVOIE 1 OU 2 SI LE NOEUD EST LIE PAR UN LIEN A UN PANNEAU DEJA MAILLE, SINON 0
	1 si meme sens, 2 sens inverse
	RENVOIE 3 OU 4 SI LE NOEUD EST LIE PAR UN LIEN A UN CABLE DEJA MAILLE, SINON 0
	3 meme sens 4 sens inverse
	STRUCTUR = TYPE DE LA STRUCTURE MAILLEE 'p' ou 'e'
	NOSTRUCTUR = NUMERO DE CETTE STRUCTURE
	DEBUTSEGM = NUMERO DANS LA NUMEROTATION LOCALE DE LA PREMIERE EXTREMITE DU SEGMENT MAILLEE
	FINSEGM = NUMERO DANS LA NUMEROTATION LOCALE DE LA DERNIERE EXTREMITE DU SEGMENT MAILLEE
	*/
	
	int noeue, noliennoeud, noliennoeue, pa, el, noliendeb, nolienfin ;
	int co, cp, deb, fin ;
	
	/*NEUD = DEBUT DU COTE, NOEUE : FIN DU COTE DANS LA NUMEROTATION LOCALE*/
	if (neud != panneau[pannea].nb_noeud_contour) noeue = neud+1;
	if (neud == panneau[pannea].nb_noeud_contour) noeue = 1;
	
	deb = panneau[pannea].noeud_contour[neud];
	fin = panneau[pannea].noeud_contour[noeue];
	noliennoeud = appartient_liaison(deb);
	noliennoeue = appartient_liaison(fin);
	/*if((neud == 1) && (pannea == 10))
		{
		printf("panne = %8d ",pannea);
		printf("liason************** %8d %8d \n",noliennoeud,noliennoeue);
		}*/
	
	if ((noliennoeud != 0) && (noliennoeue != 0))
		{
		for (pa=1;pa<=Structure.NbTypesurf;pa++)
			{
			if ((pa != pannea) && (panneau[pa].flag_maillage == 1) && (panneau[pa].type_maillage != 4))
				{
				for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
					{
					/*CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE*/
					if (co != panneau[pa].nb_noeud_contour) cp = co+1;
					if (co == panneau[pa].nb_noeud_contour) cp = 1;
					/*DEB = DEBUT DU COTE, FIN : FIN DU COTE DANS LA NUMEROTATION GLOBALE*/
					deb = panneau[pa].noeud_contour[co];
					fin = panneau[pa].noeud_contour[cp];
					noliendeb = appartient_liaison(deb);
					nolienfin = appartient_liaison(fin);
					/*if((pa == 4) && (pannea == 10))
						{
						printf("pa = %8d ",pa);
						printf("co = %8d ",co);
						printf("liasons %8d %8d \n",noliendeb,nolienfin);
						}*/
					if((noliendeb == noliennoeud) && (nolienfin == noliennoeue))
						{
						*structur = 'p';
						*nostructur = pa;
						*debutsegm = co;
						*finsegm = cp;
						return 1;
						}
					if((noliendeb == noliennoeue) && (nolienfin == noliennoeud))
						{
						*structur = 'p';
						*nostructur = pa;
						*debutsegm = cp;
						*finsegm = co;
						return 2;
						}
					}
				}
			}

		for (el=1;el<=Structure.NbTypeelem;el++)
			{
			if (element[el].flag_maillage == 1)
				{
				deb = element[el].extremite[1];
				fin = element[el].extremite[2];
				noliendeb = appartient_liaison(deb);
				nolienfin = appartient_liaison(fin);
				if((noliendeb == noliennoeud) && (nolienfin == noliennoeue))
					{
					*structur = 'e';
					*nostructur = el;
					*debutsegm = 1;
					*finsegm = 2;
					return 3;
					}
				if((noliendeb == noliennoeue) && (nolienfin == noliennoeud))
					{
					*structur = 'e';
					*nostructur = el;
					*debutsegm = 2;
					*finsegm = 1;
					return 4;
					}
				}
			}
		}
	*structur = ' ';
	*nostructur = 0;
	*debutsegm = 0;
	*finsegm = 0;
	return 0;
	}


void maillage_contour_libre_filaire(int pa, int co, int cp)
	{
	/*
	PA = NO DU PANNEAU, CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE
	EN SE BASANT SUR LES COORDONNEES FILAIRES
	*/
	int    zi, nb_coupe, deb, fin;
	float  xdeb, xfin, ydeb, yfin, zdeb, zfin ;
	float  lg_tendue ;
	
	deb  = panneau[pa].noeud_contour[co];
	fin  = panneau[pa].noeud_contour[cp];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	lg_tendue = sqrt(((noeud[fin].u-noeud[deb].u) * (noeud[fin].u-noeud[deb].u)) + ((noeud[fin].v-noeud[deb].v) * (noeud[fin].v-noeud[deb].v)));
	nb_coupe = (int) (lg_tendue / panneau[pa].pas_maillage * panneau[pa].longueur_repos);
	
	panneau[pa].suivant_contour[co] = 0 ;
	
	for (zi=1;zi<=nb_coupe -1 ;zi++)
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		panneau[pa].nb_noeud_cote++;
		
		/**********************************************/
  		panneau[pa].noeud_cote = (int *) realloc(panneau[pa].noeud_cote, (1+ panneau[pa].nb_noeud_cote) * sizeof(int));
		if (panneau[pa].noeud_cote    == NULL)
			{
			printf(" panneau[pa].noeud_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		panneau[pa].prop_cote = (float *) realloc(panneau[pa].prop_cote, (1+ panneau[pa].nb_noeud_cote) * sizeof(float));
		if (panneau[pa].prop_cote    == NULL)
			{
			printf(" panneau[pa].prop_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		if (zi == 1)
			{
			panneau[pa].suivant_contour[co] = panneau[pa].nb_noeud_cote;
			}
		panneau[pa].noeud_cote[panneau[pa].nb_noeud_cote] = Structure.nb_total;
		panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] = (float) zi / nb_coupe;
		noeud[Structure.nb_total].x = xdeb + zi * (xfin-xdeb) / nb_coupe;
		noeud[Structure.nb_total].y = ydeb + zi * (yfin-ydeb) / nb_coupe;
		noeud[Structure.nb_total].z = zdeb + zi * (zfin-zdeb) / nb_coupe;
		noeud[Structure.nb_total].type = panneau[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].U = noeud[deb].U + zi * (noeud[fin].U-noeud[deb].U) / nb_coupe;
		noeud[Structure.nb_total].V = noeud[deb].V + zi * (noeud[fin].V-noeud[deb].V) / nb_coupe;
		noeud[Structure.nb_total].u = noeud[Structure.nb_total].U + noeud[Structure.nb_total].V; 
		noeud[Structure.nb_total].v = noeud[Structure.nb_total].V - noeud[Structure.nb_total].U; 
		}
	}
		
void maillage_contour_panneau(int pa, int co, int cp,int pa2,int nlo1,int nlo2)
	{
	/*
	PA = NO DU PANNEAU, CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE
	PA2 = NO DU 2EM PANNEAU, NLO1 = DEBUT DU COTE, NLO2 : FIN DU COTE DANS LA NUMEROTATION LOCALE
	*/
	
	int   zi, nb_coupe, deb, fin, premier_cote, sens_cote, nb_lai, premier_loc, nlo3 ;
	float xdeb, xfin, ydeb, yfin, zdeb, zfin, ss ;
	
	/*deb  = panneau[pa2].noeud_contour[nlo1];
	fin  = panneau[pa2].noeud_contour[nlo2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;*/
	
	/*CALCUL DE NB_COUPE*/
	if (nlo1 + 1 == nlo2)
		{
		if(panneau[pa2].suivant_contour[nlo1] == 0)
			{
			/*PAS DE POINT DE COTE SUR CE SEGMENT DE CONTOUR*/
			nb_coupe = 1;
			}
		else
			{
			nlo3 = nlo2 - 1;
			do
				{
				nlo3 += 1;
				}
			while ((panneau[pa2].suivant_contour[nlo3] == 0) && (nlo3 != panneau[pa2].nb_noeud_contour));
			if (panneau[pa2].suivant_contour[nlo3] != 0)
				{
				nb_coupe = panneau[pa2].suivant_contour[nlo3] - panneau[pa2].suivant_contour[nlo1] + 1;
				}
			else
				{
				nb_coupe = panneau[pa2].nb_noeud_cote - panneau[pa2].suivant_contour[nlo1] + 2;
				}
			}
		}
	if (nlo1 - 1 == nlo2)
		{
		if(panneau[pa2].suivant_contour[nlo2] == 0)
			{
			/*PAS DE POINT DE COTE SUR CE SEGMENT DE CONTOUR*/
			nb_coupe = 1;
			}
		else
			{
			nlo3 = nlo1 - 1;
			do
				{
				nlo3 += 1;
				}
			while ((panneau[pa2].suivant_contour[nlo3] == 0) && (nlo3 != panneau[pa2].nb_noeud_contour));
			if (panneau[pa2].suivant_contour[nlo3] != 0)
				{
				nb_coupe = panneau[pa2].suivant_contour[nlo3] - panneau[pa2].suivant_contour[nlo2] + 1;
				}
			else
				{
				nb_coupe = panneau[pa2].nb_noeud_cote - panneau[pa2].suivant_contour[nlo2] + 2;
				}
			}
		}
	if ((nlo1 - 1 != nlo2) && (nlo1 + 1 != nlo2))
		{
		/*DANS CE CAS NLO1 ET NLO2 SONT 1 ET PANNEAU[PA2].NB_NOEUD_CONTOUR OU INVERSEMENT*/
		if(panneau[pa2].suivant_contour[panneau[pa2].nb_noeud_contour] == 0)
			{
			/*pas de point de cote sur ce segment de contour*/
			nb_coupe = 1;
			}
		else
			{
			nb_coupe = panneau[pa2].nb_noeud_cote - panneau[pa2].suivant_contour[panneau[pa2].nb_noeud_contour] + 2;
			}
		}
	
	deb  = panneau[pa].noeud_contour[co];
	fin  = panneau[pa].noeud_contour[cp];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	
	if((nlo1 == nlo2-1) || ((nlo1 == panneau[pa2].nb_noeud_contour) && (nlo2 == 1)))
		{
		premier_loc  = panneau[pa2].suivant_contour[nlo1];
		premier_cote = panneau[pa2].noeud_cote[panneau[pa2].suivant_contour[nlo1]];
		sens_cote = +1;
		}
	if((nlo2 == nlo1-1) || ((nlo2 == panneau[pa2].nb_noeud_contour) && (nlo1 == 1)))
		{
		premier_loc  = panneau[pa2].suivant_contour[nlo2] + nb_coupe - 2;
		premier_cote = panneau[pa2].noeud_cote[panneau[pa2].suivant_contour[nlo2]] + nb_coupe - 2;
		sens_cote = -1;
		}
	for (zi=1;zi<=nb_coupe -1 ;zi++)
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		panneau[pa].nb_noeud_cote++;
		
		/**********************************************/
  		panneau[pa].noeud_cote = (int *) realloc(panneau[pa].noeud_cote, (1 + panneau[pa].nb_noeud_cote) * sizeof(int));
		if (panneau[pa].noeud_cote    == NULL)
			{
			printf(" panneau[pa].noeud_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		panneau[pa].prop_cote = (float *) realloc(panneau[pa].prop_cote, (1 + panneau[pa].nb_noeud_cote) * sizeof(float));
		if (panneau[pa].prop_cote    == NULL)
			{
			printf(" panneau[pa].prop_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		if (zi ==1)
			{
			panneau[pa].suivant_contour[co] = panneau[pa].nb_noeud_cote;
			}
			
		nb_lai = appartient_liaison(premier_cote + sens_cote * (zi - 1));
		
		if (nb_lai == 0)
			{		
			Structure.nb_lien++;
			if ( Structure.nb_lien >= NBMAXLIAISON)
				{
				printf(" NBMAXLIAISON trop petit %4d < %4d \n",NBMAXLIAISON,Structure.nb_lien );
				exit(0);
				}
			Lien[Structure.nb_lien].nb_liaison = 2;
			/**********************************************/
  			Lien[Structure.nb_lien].structure = (int *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(int));
			if (Lien[Structure.nb_lien].structure    == NULL)
				{
				printf("Lien[Structure.nb_lien].structure  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			Lien[Structure.nb_lien].extremite = (int *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(int));
			if (Lien[Structure.nb_lien].extremite    == NULL)
				{
				printf("Lien[Structure.nb_lien].extremite  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			Lien[Structure.nb_lien].noeud = (int *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(int));
			if (Lien[Structure.nb_lien].noeud    == NULL)
				{
				printf("Lien[Structure.nb_lien].noeud  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			Lien[Structure.nb_lien].type = (char *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(char));
			if (Lien[Structure.nb_lien].type    == NULL)
				{
				printf("Lien[Structure.nb_lien].type  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
			Lien[Structure.nb_lien].type[1] = 'p';
			Lien[Structure.nb_lien].type[2] = 'p';
			Lien[Structure.nb_lien].structure[1] = pa2;
			Lien[Structure.nb_lien].structure[2] = pa ;
			Lien[Structure.nb_lien].extremite[1] = premier_loc + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].extremite[2] = panneau[pa].nb_noeud_cote;
			Lien[Structure.nb_lien].noeud[1] = premier_cote + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].noeud[2] = Structure.nb_total;
			}
		if (nb_lai != 0)
			{		
			Lien[nb_lai].nb_liaison++;
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'p';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = pa;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = panneau[pa].nb_noeud_cote;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		ss = 0.5 * ( fabs( sens_cote - 1. ) );
		panneau[pa].noeud_cote[panneau[pa].nb_noeud_cote] = Structure.nb_total;
		panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] = (float) ( ss + sens_cote ) * zi /nb_coupe;
		noeud[Structure.nb_total].x = xdeb + zi * (xfin-xdeb) /nb_coupe;
		noeud[Structure.nb_total].y = ydeb + zi * (yfin-ydeb) /nb_coupe;
		noeud[Structure.nb_total].z = zdeb + zi * (zfin-zdeb) /nb_coupe;
		noeud[Structure.nb_total].U = noeud[deb].U +zi * (noeud[fin].U-noeud[deb].U)/nb_coupe ;
		noeud[Structure.nb_total].V = noeud[deb].V +zi * (noeud[fin].V-noeud[deb].V)/nb_coupe  ;
		noeud[Structure.nb_total].type = panneau[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].u = noeud[Structure.nb_total].U + noeud[Structure.nb_total].V; 
		noeud[Structure.nb_total].v = noeud[Structure.nb_total].V - noeud[Structure.nb_total].U; 
		}
	}

void maillage_contour_element(int pa,int co,int cp,int noele,int nloc)
	{
	/*
	PA = NO DU PANNEAU, CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE
	NOELE = NO DE L ELEMENT, NLOC = DEBUT DE L ELEMENT CORRESPONDANT A CO
	*/
	
	//printf(" Structure.nb_total deb %4d \n",Structure.nb_total );
	//printf("pa %d co %d cp %d noele %d nloc  %4d \n",pa,co,cp,noele,nloc );
	int   zi, nb_coupe, deb, fin, premier_cote, sens_cote, nb_lai, premier_loc ;
	float xdeb, xfin, ydeb, yfin, zdeb, zfin, ss ;
	
	if (nloc == 1)
		{
		deb = element[noele].extremite[1];
		fin = element[noele].extremite[2];
		}
	if (nloc == 2)
		{
		deb = element[noele].extremite[2];
		fin = element[noele].extremite[1];
		}
	nb_coupe = element[noele].nb_barre;
	
	deb  = panneau[pa].noeud_contour[co];
	fin  = panneau[pa].noeud_contour[cp];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	
	if(nloc == 1)
		{
		premier_loc = 1;
		premier_cote = element[noele].noeud[1];
		sens_cote = +1;
		}
	if(nloc ==2)
		{
		premier_loc = nb_coupe - 1;
		premier_cote = element[noele].noeud[nb_coupe - 1];
		sens_cote = -1;
		}
	for (zi=1;zi<=nb_coupe -1 ;zi++)
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		panneau[pa].nb_noeud_cote++;
		
		/**********************************************/
  		panneau[pa].noeud_cote = (int *) realloc(panneau[pa].noeud_cote, (1+ panneau[pa].nb_noeud_cote) * sizeof(int));
		if (panneau[pa].noeud_cote    == NULL)
			{
			printf(" panneau[pa].noeud_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		panneau[pa].prop_cote = (float *) realloc(panneau[pa].prop_cote, (1+ panneau[pa].nb_noeud_cote) * sizeof(float));
		if (panneau[pa].prop_cote    == NULL)
			{
			printf(" panneau[pa].prop_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		if (zi ==1)
			{
			panneau[pa].suivant_contour[co] = panneau[pa].nb_noeud_cote;
			}
		nb_lai = appartient_liaison(premier_cote + sens_cote * (zi - 1));
		if (nb_lai == 0)
			{		
			Structure.nb_lien++;
			if ( Structure.nb_lien >= NBMAXLIAISON)
				{
				printf(" NBMAXLIAISON trop petit %4d < %4d \n",NBMAXLIAISON,Structure.nb_lien );
				exit(0);
				}
			Lien[Structure.nb_lien].nb_liaison = 2;
			/**********************************************/
  			Lien[Structure.nb_lien].structure = (int *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(int));
			if (Lien[Structure.nb_lien].structure    == NULL)
				{
				printf("Lien[Structure.nb_lien].structure  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			Lien[Structure.nb_lien].extremite = (int *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(int));
			if (Lien[Structure.nb_lien].extremite    == NULL)
				{
				printf("Lien[Structure.nb_lien].extremite  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			Lien[Structure.nb_lien].noeud = (int *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(int));
			if (Lien[Structure.nb_lien].noeud    == NULL)
				{
				printf("Lien[Structure.nb_lien].noeud  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			Lien[Structure.nb_lien].type = (char *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(char));
			if (Lien[Structure.nb_lien].type    == NULL)
				{
				printf("Lien[Structure.nb_lien].type  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
			Lien[Structure.nb_lien].type[1] = 'e';
			Lien[Structure.nb_lien].type[2] = 'p';
			Lien[Structure.nb_lien].structure[1] = noele;
			Lien[Structure.nb_lien].structure[2] = pa ;
			Lien[Structure.nb_lien].extremite[1] = premier_loc + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].extremite[2] = panneau[pa].nb_noeud_cote;
			Lien[Structure.nb_lien].noeud[1] = premier_cote + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].noeud[2] = Structure.nb_total;
			}
		if (nb_lai != 0)
			{		
			Lien[nb_lai].nb_liaison++;
			/**********************************************/
  			Lien[nb_lai].structure = (int *) realloc(Lien[nb_lai].structure, (1 + Lien[nb_lai].nb_liaison) * sizeof(int));
			if (Lien[nb_lai].structure    == NULL)
				{
				printf("Lien[nb_lai].structure  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			Lien[nb_lai].extremite = (int *) realloc(Lien[nb_lai].extremite, (1 + Lien[nb_lai].nb_liaison) * sizeof(int));
			if (Lien[nb_lai].extremite    == NULL)
				{
				printf("Lien[nb_lai].extremite  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			Lien[nb_lai].noeud = (int *) realloc(Lien[nb_lai].noeud, (1 + Lien[nb_lai].nb_liaison) * sizeof(int));
			if (Lien[nb_lai].noeud    == NULL)
				{
				printf("Lien[nb_lai].noeud  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
  			Lien[nb_lai].type = (char *) realloc(Lien[nb_lai].type, (1 + Lien[nb_lai].nb_liaison) * sizeof(char));
			if (Lien[nb_lai].type    == NULL)
				{
				printf("Lien[nb_lai].type  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'p';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = pa;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = panneau[pa].nb_noeud_cote;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		
		/*modifie le 29/06/99 pour integrer prop_cote*/	
		ss = 0.5 * ( fabs( sens_cote - 1. ) );
		panneau[pa].noeud_cote[panneau[pa].nb_noeud_cote] = Structure.nb_total;
		if (sens_cote > 0)
			panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] = ss + (float) ( sens_cote ) * zi /nb_coupe;
		if (sens_cote < 0)
			panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] = (float) zi / (float) nb_coupe;
		
		
		//printf("Structure.nb_total = %d ",Structure.nb_total);
		//printf("sens_cote = %d ",sens_cote);
		//printf("ss = %f \n",ss);
		//printf("panneau[%d].prop_cote[%d] = %f \n ",pa,panneau[pa].nb_noeud_cote,panneau[pa].prop_cote[panneau[pa].nb_noeud_cote]);
		
		
		noeud[Structure.nb_total].x = xdeb + zi * (xfin-xdeb) / nb_coupe;
		noeud[Structure.nb_total].y = ydeb + zi * (yfin-ydeb) / nb_coupe;
		noeud[Structure.nb_total].z = zdeb + zi * (zfin-zdeb) / nb_coupe;
		noeud[Structure.nb_total].U = noeud[deb].U + zi * (noeud[fin].U-noeud[deb].U) / nb_coupe;
		noeud[Structure.nb_total].V = noeud[deb].V + zi * (noeud[fin].V-noeud[deb].V) / nb_coupe;
		noeud[Structure.nb_total].type = panneau[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].u = noeud[Structure.nb_total].U + noeud[Structure.nb_total].V; 
		noeud[Structure.nb_total].v = noeud[Structure.nb_total].V - noeud[Structure.nb_total].U; 
		}
	printf(" Structure.nb_total fin %4d \n",Structure.nb_total );
	}

void maillage_contour_element2(int pa,int co,int cp,int noele,int nloc)
	{
	/*
	pa = NO DU PANNEAU, co = DEBUT DU COTE, cp : FIN DU COTE DANS LA NUMEROTATION LOCALE
	noele = NO DE L ELEMENT, nloc = DEBUT DE L ELEMENT CORRESPONDANT A co
	*/
	int no,np,precedent_suivant_contour;
	int sewn,corner1,corner2;
	int deb,fin,nb_lai;
	float xdeb, xfin, ydeb, yfin, zdeb, zfin;
	
	
	
	
	sewn = sewn_diamond_panel2cable2(noele, pa, &corner1, &corner2);
	//printf("maillage_panneau1.c maillage_contour_element2 paneau %d cote %d fin cote %d elementtttttttttttttt[%2d].nb_nodes %2d extremite element %d sewn %d\n",pa,co,cp,noele,element[noele].nb_nodes,nloc,sewn);	
	//printf("panneau[%d].nb_noeud_cote %d\n",pa,panneau[pa].nb_noeud_cote);	
	if ((sewn == 1) && (element[noele].nb_nodes > 0))
		{
		//recherche precedent suivant_contour si co > 1
		if (co == 1)
			{
			precedent_suivant_contour = 0;
			}
		else
			{
			precedent_suivant_contour = 0;
			for (np=1;np<=co-1;np++)
				{
				if (panneau[pa].suivant_contour[np] > precedent_suivant_contour) precedent_suivant_contour = panneau[pa].suivant_contour[np];
				}			
			}
		
			//printf("precedent_suivant_contour %2d \n",precedent_suivant_contour);	
		
		
		
		
		
		if (nloc == 1)
			{
			deb  = panneau[pa].noeud_contour[co];
			fin  = panneau[pa].noeud_contour[cp];
			}
		else
			{
			deb  = panneau[pa].noeud_contour[cp];
			fin  = panneau[pa].noeud_contour[co];
			}
		xdeb = noeud[deb].x;	ydeb = noeud[deb].y;	zdeb = noeud[deb].z;
		xfin = noeud[fin].x;	yfin = noeud[fin].y;	zfin = noeud[fin].z;
		for (np=1;np<=element[noele].nb_nodes;np++)
			{
			if (nloc == 1)
				{
				no = np;
				}
			else
				{
				no = element[noele].nb_nodes - np +1;
				}
			//printf("element[%d].noeud %2d ",no,element[noele].noeud[no]);	
			//printf("element[%d].prop %lf \n",no,element[noele].prop[no]);	
			Structure.nb_total++;
			if (Structure.nb_total >= NBMAXNOEUD)
				{
				printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
				exit(0);
				}
			panneau[pa].nb_noeud_cote++;	
			//printf("panneau[%d].nb_noeud_cote %d\n",pa,panneau[pa].nb_noeud_cote);	
			/**********************************************/
	  		panneau[pa].noeud_cote = (int *) realloc(panneau[pa].noeud_cote, (1+ panneau[pa].nb_noeud_cote) * sizeof(int));
			if (panneau[pa].noeud_cote    == NULL)
				{
				printf(" panneau[pa].noeud_cote 2 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
	  		panneau[pa].prop_cote = (float *) realloc(panneau[pa].prop_cote, (1+ panneau[pa].nb_noeud_cote) * sizeof(float));
			if (panneau[pa].prop_cote    == NULL)
				{
				printf(" panneau[pa].prop_cote 2 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
			noeud[Structure.nb_total].x = xdeb + element[noele].prop[no] * (xfin-xdeb);
			noeud[Structure.nb_total].y = ydeb + element[noele].prop[no] * (yfin-ydeb);
			noeud[Structure.nb_total].z = zdeb + element[noele].prop[no] * (zfin-zdeb);
			noeud[Structure.nb_total].U = noeud[deb].U + element[noele].prop[no] * (noeud[fin].U-noeud[deb].U);
			noeud[Structure.nb_total].V = noeud[deb].V + element[noele].prop[no] * (noeud[fin].V-noeud[deb].V);
			noeud[Structure.nb_total].type = panneau[pa].type_suivant_contour[co] ;
			noeud[Structure.nb_total].u = noeud[Structure.nb_total].U + noeud[Structure.nb_total].V; 
			noeud[Structure.nb_total].v = noeud[Structure.nb_total].V - noeud[Structure.nb_total].U; 
			if (np == 1)
				{
				//add the first node on suivant_contour
				if ((co == 1) || (precedent_suivant_contour == 0))
					{
					panneau[pa].suivant_contour[co] = 1;
					}
				else
					{
					panneau[pa].suivant_contour[co] = precedent_suivant_contour + (Structure.nb_total - panneau[pa].noeud_cote[precedent_suivant_contour]);
					}
				//printf("precedent_suivant_contour %d\n",precedent_suivant_contour);	
				//printf("Structure.nb_total %d\n",Structure.nb_total);	
				//printf("panneau[pa].noeud_cote[precedent_suivant_contour] %d\n",panneau[pa].noeud_cote[precedent_suivant_contour]);	

				}
			panneau[pa].noeud_cote[panneau[pa].nb_noeud_cote] = Structure.nb_total;
			if (nloc == 1)
				{
				panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] = element[noele].prop[no];
				}
			else
				{
				panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] = 1.0 - element[noele].prop[no];
				}
					
			
			
			//lien
			nb_lai = appartient_liaison(element[noele].noeud[no]);
			//printf("appartient_liaison(element[%d].noeud[%d] = %d\n",noele,no,nb_lai);	
			//exit(0);
			if (nb_lai == 0)
				{		
				Structure.nb_lien++;
				if ( Structure.nb_lien >= NBMAXLIAISON)
					{
					printf(" NBMAXLIAISON trop petit %4d < %4d \n",NBMAXLIAISON,Structure.nb_lien );
					exit(0);
					}
				Lien[Structure.nb_lien].nb_liaison = 2;
				/**********************************************/
	  			Lien[Structure.nb_lien].structure = (int *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(int));
				if (Lien[Structure.nb_lien].structure    == NULL)
					{
					printf("Lien[Structure.nb_lien].structure  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
	  			Lien[Structure.nb_lien].extremite = (int *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(int));
				if (Lien[Structure.nb_lien].extremite    == NULL)
					{
					printf("Lien[Structure.nb_lien].extremite  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
	  			Lien[Structure.nb_lien].noeud = (int *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(int));
				if (Lien[Structure.nb_lien].noeud    == NULL)
					{
					printf("Lien[Structure.nb_lien].noeud  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
	  			Lien[Structure.nb_lien].type = (char *) malloc((1 + Lien[Structure.nb_lien].nb_liaison) * sizeof(char));
				if (Lien[Structure.nb_lien].type    == NULL)
					{
					printf("Lien[Structure.nb_lien].type  1 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				Lien[Structure.nb_lien].type[1] = 'e';
				Lien[Structure.nb_lien].type[2] = 'p';
				Lien[Structure.nb_lien].structure[1] = noele;
				Lien[Structure.nb_lien].structure[2] = pa ;
				Lien[Structure.nb_lien].extremite[1] = no;
				Lien[Structure.nb_lien].extremite[2] = panneau[pa].nb_noeud_cote;
				Lien[Structure.nb_lien].noeud[1] = element[noele].noeud[no];
				Lien[Structure.nb_lien].noeud[2] = Structure.nb_total;
				//printf("Structure.nb_lien 	%d\n",Structure.nb_lien);
				//printf("type 		%c 	%c\n",Lien[Structure.nb_lien].type[1],Lien[Structure.nb_lien].type[2]);
				//printf("structure 	%d 	%d\n",Lien[Structure.nb_lien].structure[1],Lien[Structure.nb_lien].structure[2]);
				//printf("extremite 	%d 	%d\n",Lien[Structure.nb_lien].extremite[1],Lien[Structure.nb_lien].extremite[2]);
				//printf("noeud 		%d 	%d\n",Lien[Structure.nb_lien].noeud[1],Lien[Structure.nb_lien].noeud[2]);
				/*
				int   nb_liaison;		//nb de noeud utilisant cette liaison//
				char *type; 			//types des structures liees//
				int  *structure; 		//indice des structures liees//
				int  *extremite; 		//indice des noeuds lies (numerotation locale)//
				int  *noeud; 			//indice des coins lies (numerotation totale)//
				*/
				}
			else
				{
				printf("maillage_panneau1.c, fct maillage_contour_element2 nb_lai = %d\n",nb_lai);
				exit(0);
				}

			}
			
			
		//printf("panneau[%d].nb_noeud_contour %4d \n",pa,panneau[pa].nb_noeud_contour );
		for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
			{
			//printf("panneau[%d].noeud_contour[%d]  %4d ",pa,no,panneau[pa].noeud_contour[no]);
			//printf("panneau[%d].suivant_contour[%d]  %4d \n",pa,no,panneau[pa].suivant_contour[no]);
			//printf("panneau[%d].type_suivant_contour[%d]  %4d \n",pa,no,panneau[pa].type_suivant_contour[no]);
			}
		//printf("panneau[%d].nb_noeud_cote %4d \n",pa,panneau[pa].nb_noeud_cote );
		for (no=1;no<=panneau[pa].nb_noeud_cote;no++)
			{
			//printf("panneau[%d].noeud_cote[%d]  %4d ",pa,no,panneau[pa].noeud_cote[no]);
			//printf("panneau[%d].prop_cote[%d]  %f \n",pa,no,panneau[pa].prop_cote[no]);
			}
			
			
		//if (pa == 6) exit(0);
			
			
			
			
		}
	}
	


void maillage_contour1(int pa)
	{
	int   co, cp, nloc1, nloc2, nopan, maille;
	char  pan ;
	
	/*printf("pa = %8d \n",pa);*/
	
	for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
		{
		/*CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROATTION LOCALE*/
		if (co != panneau[pa].nb_noeud_contour) cp = co+1;
		if (co == panneau[pa].nb_noeud_contour) cp = 1;
		
		maille = liaison_maille(co,pa,&pan,&nopan,&nloc1,&nloc2);
		
		if (maille == 0)
			{
			maillage_contour_libre_filaire(pa, co, cp);
		 	}
		if ((maille == 1) || (maille == 2))
			{
			maillage_contour_panneau(pa, co, cp, nopan, nloc1, nloc2);
			}
		if ((maille == 3) || (maille == 4))
			{
			maillage_contour_element(pa, co, cp, nopan, nloc1);
			}
		}
	}


float surface_triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3 )
	{
	float temp,A,B,C,p,S;
	
	/*X1,X2,X3,Y1,Y2,Y3 = COORDONNEES DU TRIANGLE*/

  	/* COTES A OPPOSE AU SOMMET_1*/ 
  	/* COTES B OPPOSE AU SOMMET_2*/ 
  	/* COTES C OPPOSE AU SOMMET_3*/
  	temp = (X3-X2)*(X3-X2) + (Y3-Y2)*(Y3-Y2);
  	if (temp <= 0.0)	A = 0.0;
  	else			A = sqrt(temp);
  	
  	temp = (X1-X3)*(X1-X3) + (Y1-Y3)*(Y1-Y3);
  	if (temp <= 0.0)	B = 0.0;
  	else			B = sqrt(temp);
  	
  	temp = (X2-X1)*(X2-X1) + (Y2-Y1)*(Y2-Y1);
  	if (temp <= 0.0)	C = 0.0;
  	else			C = sqrt(temp);
  	
    	/*P : DEMI PERIMETRE DU TRIANGLE*/
    	p = (A + B + C)/2.0;

    	/*S : SURFACE DU TRIANGLE
    	S = sqrt(p*(p-A)*(p-B)*(p-C));*/
    	
  	temp = p*(p-A)*(p-B)*(p-C);
  	if (temp <= 0.0)	S = 0.0;
  	else			S = sqrt(temp);

	/*printf("X1 Y3 %f %f %f %f %f %f A C %f %f %f p %f S %f\n",X1, Y1, X2, Y2, X3, Y3, A, B, C, p, S);*/
    	
	return S;
	}


void maillage_interne2(int pa)
	{
	/*
	CREE LES POINTS A L INTERIEUR DU PANNEAU PA, EN SE BASANT SUR LES FILS
	*/
	int   li, nbU, nbV, co, sommet_1, sommet_2, sommet_3, tri ,trouve, distant,debU,debV,finU,finV,no;
	float Uo, Vo, denominateur, coef_a, coef_b ;
	float min_U, min_V, max_U ,max_V ,fact ;
			
	/* FACTEUR DETERMINANT LA TOLERANCE DE PROXIMITE D UN NOEUD DU CONTOUR OU D UN NOEUD DU BORD*/
	/* DISTANCE DU NOEUD AU BORD OU A UN AUTRE NOEUD, INFERIEURE A (PAS DE MAILLAGE * FACT) */
	fact = 0.5 ;
	
	
	/*printf(" maillage_interne du panneau %4d \n", pa);*/
	/*RECHERCHE DES POINTS EXTREMES*/
	min_U = noeud[panneau[pa].noeud_contour[1]].u;
	min_V = noeud[panneau[pa].noeud_contour[1]].v;
	max_U = noeud[panneau[pa].noeud_contour[1]].u;
	max_V = noeud[panneau[pa].noeud_contour[1]].v;
	for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
		{
		if (noeud[panneau[pa].noeud_contour[co]].u > max_U) max_U = noeud[panneau[pa].noeud_contour[co]].u;
		if (noeud[panneau[pa].noeud_contour[co]].u < min_U) min_U = noeud[panneau[pa].noeud_contour[co]].u;
		if (noeud[panneau[pa].noeud_contour[co]].v > max_V) max_V = noeud[panneau[pa].noeud_contour[co]].v;
		if (noeud[panneau[pa].noeud_contour[co]].v < min_V) min_V = noeud[panneau[pa].noeud_contour[co]].v;
		}
	nbU = (int) ((max_U - min_U) / panneau[pa].pas_maillage * panneau[pa].longueur_repos);
	nbV = (int) ((max_V - min_V) / panneau[pa].pas_maillage * panneau[pa].longueur_repos);
	panneau[pa].nb_noeud_interieur = 0;
	
	/**********************************************/
  	panneau[pa].noeud_interieur = (int *) malloc(1 * sizeof(int));
	if (panneau[pa].noeud_interieur    == NULL)
		{
		printf(" panneau[pa].noeud_interieur 1 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	if(Structure.nb_add_node_panel > 0)
		{
		for (no=1;no<=Structure.nb_add_node_panel - 1;no++)
			{
			printf("add node %d in panel %d coordinates %lf %lf with type %d\n",no,Add_node_panel.panel[no],Add_node_panel.U[no],Add_node_panel.V[no],Add_node_panel.type[no]);
			exit(0);
			}
		}
	for (co=1;co<=nbV - 1;co++)
		{
		for (li=1;li<=nbU - 1;li++)
			{
			Uo = min_U + li * (max_U-min_U) / nbU;
			Vo = min_V + co * (max_V-min_V) / nbV;
			tri = interieur_panneau_filaire(Uo, Vo,  pa);
			trouve = proche_contour_filaire(Uo, Vo,  pa, fact);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / CONTOUR */
			distant = proche_panneau_filaire(Uo, Vo, pa, fact);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / NOEUD */
			/*
			printf("Uo = %8.2f ",Uo);	printf("Vo = %8.2f ",Vo);
			printf("tri = %4d ",tri);	printf("trouve = %4d ",trouve);	printf("distant = %4d\n",distant);
			*/
			
			if ((tri != 0) && (trouve != 0) && (distant != 0))
				{
				Structure.nb_total++;
				if (Structure.nb_total >= NBMAXNOEUD)
					{
					printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
					exit(0);
					}
				panneau[pa].nb_noeud_interieur = panneau[pa].nb_noeud_interieur + 1;
				/**********************************************/
  				panneau[pa].noeud_interieur = (int *) realloc(panneau[pa].noeud_interieur, (1+ panneau[pa].nb_noeud_interieur) * sizeof(int));
				if (panneau[pa].noeud_interieur    == NULL)
					{
					printf(" panneau[pa].noeud_interieur 2 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				panneau[pa].noeud_interieur[panneau[pa].nb_noeud_interieur] = Structure.nb_total;
				noeud[Structure.nb_total].u = Uo;
				noeud[Structure.nb_total].v = Vo;
				noeud[Structure.nb_total].type = panneau[pa].type_noeud;
			
				sommet_1 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]];
				sommet_2 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]];
				sommet_3 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]];
				/*LE VECTEUR 1UOVO = COEF_A * 12 + COEF_B * 13*/
				denominateur = (((noeud[sommet_2].u - noeud[sommet_1].u) * (noeud[sommet_3].v - noeud[sommet_1].v)) 
					      - ((noeud[sommet_2].v - noeud[sommet_1].v) * (noeud[sommet_3].u - noeud[sommet_1].u))); 
				coef_a = (((Uo - noeud[sommet_1].u) * (noeud[sommet_3].v - noeud[sommet_1].v)) 
					- ((Vo - noeud[sommet_1].v) * (noeud[sommet_3].u - noeud[sommet_1].u)))
					/ denominateur;
				coef_b = (((Uo - noeud[sommet_1].u) * (noeud[sommet_2].v - noeud[sommet_1].v)) 
					- ((Vo - noeud[sommet_1].v) * (noeud[sommet_2].u - noeud[sommet_1].u)))
					/ (-denominateur);
   				noeud[Structure.nb_total].x = noeud[sommet_1].x + coef_a * (noeud[sommet_2].x - noeud[sommet_1].x) 
   						         		     + coef_b * (noeud[sommet_3].x - noeud[sommet_1].x);
   				noeud[Structure.nb_total].y = noeud[sommet_1].y + coef_a * (noeud[sommet_2].y - noeud[sommet_1].y)
   				 		         		     + coef_b * (noeud[sommet_3].y - noeud[sommet_1].y);
   				noeud[Structure.nb_total].z = noeud[sommet_1].z + coef_a * (noeud[sommet_2].z - noeud[sommet_1].z)
   				 		         		     + coef_b * (noeud[sommet_3].z - noeud[sommet_1].z);
   				noeud[Structure.nb_total].U = (noeud[Structure.nb_total].u - noeud[Structure.nb_total].v) / 2.0;
   				noeud[Structure.nb_total].V = (noeud[Structure.nb_total].u + noeud[Structure.nb_total].v) / 2.0;
				}
			}
		}
	}
	
void maillage_interne5(int pa)
	{
	/*
	CREE DES ELEMENTS BARRES LES POINTS A L INTERIEUR DU PANNEAU rectangulaire PA, EN SE BASANT SUR LES FILS
	*/
	int s,sommet1,sommet2,sommet3,Umin,Umax,Vmin,Vmax;
	float U1,U2,U3,V1,V2,V3;
	
	for (s=1;s<=panneau[pa].nb_triangle_contour;s++)
		{
		sommet1 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[s][1]];
		sommet2 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[s][2]];
		sommet3 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[s][3]];
		
		U1 = noeud[sommet1].V + noeud[sommet1].U; V1 = noeud[sommet1].V - noeud[sommet1].U;
		U2 = noeud[sommet2].V + noeud[sommet2].U; V2 = noeud[sommet2].V - noeud[sommet2].U;
		U3 = noeud[sommet3].V + noeud[sommet3].U; V3 = noeud[sommet3].V - noeud[sommet3].U;
		
		if ((U1 <= U2) && (U1 <= U3))	Umin =  (int) floor(U1);
		if ((U2 <= U3) && (U2 <= U1))	Umin =  (int) floor(U2);
		if ((U3 <= U1) && (U3 <= U2))	Umin =  (int) floor(U2);
		if ((U1 >= U2) && (U1 >= U3))	Umax =  (int) ceil(U1);
		if ((U2 >= U3) && (U2 >= U1))	Umax =  (int) ceil(U2);
		if ((U3 >= U1) && (U3 >= U2))	Umax =  (int) ceil(U3);
		if ((V1 <= V2) && (V1 <= V3))	Vmin =  (int) floor(V1);
		if ((V2 <= V3) && (V2 <= V1))	Vmin =  (int) floor(V2);
		if ((V3 <= V1) && (V3 <= V2))	Vmin =  (int) floor(V2);
		if ((V1 >= V2) && (V1 >= V3))	Vmax =  (int) ceil(V1);
		if ((V2 >= V3) && (V2 >= V1))	Vmax =  (int) ceil(V2);
		if ((V3 >= V1) && (V3 >= V2))	Vmax =  (int) ceil(V3);
		printf("Umin %d Umax %d\n", Umin,Umax); 		
		printf("Vmin %d Vmax %d\n", Vmin,Vmax); 		
		}
	}


int interieur_panneau_filaire(float UU, float VV, int no_pa)
	{
	float  S, S_ref, U1, U2, U3, V1, V2, V3 ;
	int    trouve, sommet_1, sommet_2, sommet_3, no_tri ;
	
	/*RECHERCHE SI LE NOEUD DE COORDONNEES FILAIRE UU ET VV EST A L INTERIEUR DU CONTOUR  DU PANNEAU NO_PA
	SI A L INTERIEUR DU CONTOUR RETURN = NUMERO DU TRIANGLE CONTOUR OU EST SITUE LE POINT
	SI A L EXTERIEUR DU CONTOUR RETURN = 0
	*/
	trouve = 0;	/*LE TRIANGLE OU EST LE NOEUD N EST PAS TROUVE POUR L INSTANT*/

	for (no_tri=1;no_tri<=panneau[no_pa].nb_triangle_contour;no_tri++)
		{
		sommet_1 = panneau[no_pa].noeud_contour[panneau[no_pa].triangle_contour[no_tri][1]];
		sommet_2 = panneau[no_pa].noeud_contour[panneau[no_pa].triangle_contour[no_tri][2]];
		sommet_3 = panneau[no_pa].noeud_contour[panneau[no_pa].triangle_contour[no_tri][3]];
		U1 = noeud[sommet_1].u;
		U2 = noeud[sommet_2].u;
		U3 = noeud[sommet_3].u;
		V1 = noeud[sommet_1].v;
		V2 = noeud[sommet_2].v;
		V3 = noeud[sommet_3].v;
				
		/*S_REF = SURFACE DU TRIANGLE NO_TRI*/
		S_ref = surface_triangle( U1, V1, U2, V2, U3, V3);
		S = 0.0;
		S    += surface_triangle( U1, V1, U2, V2, UU, VV);
		S    += surface_triangle( U2, V2, U3, V3, UU, VV);
		S    += surface_triangle( U3, V3, U1, V1, UU, VV);
		/*
		printf("S_ref %f  S %f S / S_ref %f S_ref / S %f\n",S_ref,S, S / S_ref, S_ref / S);
		printf("UV %f  %f\n",UU,VV);
		printf("U1 %f  %f\n",U1,V1);
		printf("U2 %f  %f\n",U2,V2);
		printf("U3 %f  %f\n",U3,V3);
		*/
	
		/*
		if ((UU < 77.0) && (UU > 75.25) && (VV < 0.3) && (VV > 0.2))printf("S_ref %f  S %f S / S_ref %f S_ref / S %f\n",S_ref,S, S / S_ref, S_ref / S);
		*/
		if ((S / S_ref > 0.85) && (S / S_ref < 1.15))
			{
			/*LE NOEUD Structure.NB_TOTAL EST A L INTERIEUR DU CONTOUR*/
			trouve = no_tri;
			break;
			}
		}
	return trouve;
	}
	
	
int interieur_panneau_filaire2(float UU, float VV, int no_pa)
	{
	float  U1, U2, U3, V1, V2, V3, alpha, beta ;
	int    trouve, sommet_1, sommet_2, sommet_3, no_tri ;
	
	/*RECHERCHE SI LE NOEUD DE COORDONNEES FILAIRE UU ET VV EST A L INTERIEUR DU CONTOUR  DU PANNEAU NO_PA
	SI A L INTERIEUR DU CONTOUR RETURN = NUMERO DU TRIANGLE CONTOUR OU EST SITUE LE POINT
	SI A L EXTERIEUR DU CONTOUR RETURN = 0
	*/
	trouve = 0;	/*LE TRIANGLE OU EST LE NOEUD N EST PAS TROUVE POUR L INSTANT*/

	for (no_tri=1;no_tri<=panneau[no_pa].nb_triangle_contour;no_tri++)
		{
		sommet_1 = panneau[no_pa].noeud_contour[panneau[no_pa].triangle_contour[no_tri][1]];
		sommet_2 = panneau[no_pa].noeud_contour[panneau[no_pa].triangle_contour[no_tri][2]];
		sommet_3 = panneau[no_pa].noeud_contour[panneau[no_pa].triangle_contour[no_tri][3]];
		U1 = noeud[sommet_1].u;
		U2 = noeud[sommet_2].u;
		U3 = noeud[sommet_3].u;
		V1 = noeud[sommet_1].v;
		V2 = noeud[sommet_2].v;
		V3 = noeud[sommet_3].v;
		
		/*1P is a linear combinaison of 12 and 23: 1p = alpha 12 + beta 23
		p is inside the triangle if alpha >= 0, alpha <= 1.0, beta >= 0.0 and beta <= alpha*/
		
		alpha = ((UU-U1)*(V3-V2)-(VV-V1)*(U3-U2)) / ((U2-U1)*(V3-V2)-(V2-V1)*(U3-U2));
		beta  = ((VV-V1)*(U2-U1)-(UU-U1)*(V2-V1)) / ((U2-U1)*(V3-V2)-(V2-V1)*(U3-U2));
				
		//printf("tri %d U %f  %f  %f V %f %f %f alpha %f beta %f\n",no_tri,U1,U2,U3,V1,V2,V3,alpha,beta);
		//if ((alpha >= 0.0) && (alpha <= 1.0) && (alpha*beta >= 0.0) && (alpha*beta <= 1.0))
		//11/11/2025
		if ((alpha >= 0.0) && (alpha <= 1.0) && (beta >= 0.0) && (beta <= alpha))
			{
			/*LE NOEUD Structure.NB_TOTAL EST A L INTERIEUR DU CONTOUR*/
			trouve = no_tri;
			break;
			}
		}
	return trouve;
	}
	
	
int interieur_panneau_filaire3(double UU, double VV, int no_pa, double *alpha, double *beta)
	{
	double  U1, U2, U3, V1, V2, V3 ;
	int    trouve, sommet_1, sommet_2, sommet_3, no_tri ;
	
	/*RECHERCHE SI LE NOEUD DE COORDONNEES FILAIRE UU ET VV EST A L INTERIEUR DU CONTOUR  DU PANNEAU NO_PA
	SI A L INTERIEUR DU CONTOUR RETURN = NUMERO DU TRIANGLE CONTOUR OU EST SITUE LE POINT
	SI A L EXTERIEUR DU CONTOUR RETURN = 0
	*/
	trouve = 0;	/*LE TRIANGLE OU EST LE NOEUD N EST PAS TROUVE POUR L INSTANT*/

	for (no_tri=1;no_tri<=panneau[no_pa].nb_triangle_contour;no_tri++)
		{
		sommet_1 = panneau[no_pa].noeud_contour[panneau[no_pa].triangle_contour[no_tri][1]];
		sommet_2 = panneau[no_pa].noeud_contour[panneau[no_pa].triangle_contour[no_tri][2]];
		sommet_3 = panneau[no_pa].noeud_contour[panneau[no_pa].triangle_contour[no_tri][3]];
		U1 = noeud[sommet_1].u;
		U2 = noeud[sommet_2].u;
		U3 = noeud[sommet_3].u;
		V1 = noeud[sommet_1].v;
		V2 = noeud[sommet_2].v;
		V3 = noeud[sommet_3].v;
		
		/*1P is a linear combinaison of 12 and 23: 1p = alpha 12 + beta 23
		p is inside the triangle if alpha >= 0, alpha <= 1.0, beta >= 0.0 and beta <= alpha*/
		
		*alpha = ((UU-U1)*(V3-V2)-(VV-V1)*(U3-U2)) / ((U2-U1)*(V3-V2)-(V2-V1)*(U3-U2));
		*beta  = ((VV-V1)*(U2-U1)-(UU-U1)*(V2-V1)) / ((U2-U1)*(V3-V2)-(V2-V1)*(U3-U2));
				
		//printf("tri %d U %f  %f  %f V %f %f %f alpha %f beta %f\n",no_tri,U1,U2,U3,V1,V2,V3,alpha,beta);
		//if ((alpha >= 0.0) && (alpha <= 1.0) && (alpha*beta >= 0.0) && (alpha*beta <= 1.0))
		//11/11/2025
		if ((*alpha >= 0.0) && (*alpha <= 1.0) && (*beta >= 0.0) && (*beta <= *alpha))
			{
			/*LE NOEUD Structure.NB_TOTAL EST A L INTERIEUR DU CONTOUR*/
			trouve = no_tri;
			break;
			}
		}
	return trouve;
	}
	
	
int proche_contour_filaire(float UU, float VV, int no_pa, float fact)
	{
	float  S, U1, U2, U3, V1, V2, V3, A, B, C, p, ha, ac, ab ,s2;
	int    trouve, no, deb, fin ;
	
	/*RECHERCHE DES NOEUDS TROP PROCHE DES SEGMENTS DU CONTOUR DU PANNEAU NO_PA
	SI TROP PROCHE DU CONTOUR TROUVE = 0
	SI LOIN DU CONTOUR TROUVE = 1
	LA RECHERCHE SE FAIT SUR LES COORDONNEES FILAIRES DES NOEUDS*/
	trouve = 1;
	for (no=1;no<=panneau[no_pa].nb_noeud_contour;no++)
		{
		deb = panneau[no_pa].noeud_contour[no];
		if (no != panneau[no_pa].nb_noeud_contour) fin = panneau[no_pa].noeud_contour[no + 1];
		if (no == panneau[no_pa].nb_noeud_contour) fin = panneau[no_pa].noeud_contour[1];
		
		/*COORDONNEES DU TRIANGLE TRAITE*/
		U1 = UU;
		U2 = noeud[deb].u;
		U3 = noeud[fin].u;
		V1 = VV;
		V2 = noeud[deb].v;
		V3 = noeud[fin].v;

  		/* COTES A OPPOSE AU SOMMET_1 Structure.NB_TOTAL*/ 
  		/* COTES B OPPOSE AU SOMMET_2 DEB*/ 
  		/* COTES C OPPOSE AU SOMMET_3 FIN*/
    		A = sqrt((U3-U2)*(U3-U2) + (V3-V2)*(V3-V2));
    		B = sqrt((U1-U3)*(U1-U3) + (V1-V3)*(V1-V3));
    		C = sqrt((U2-U1)*(U2-U1) + (V2-V1)*(V2-V1));
  
    		/*P : DEMI PERIMETRE DU TRIANGLE*/
    		p = (A + B + C)/2.0;

    		/*S : SURFACE DU TRIANGLE*/
    		s2 = p*(p-A)*(p-B)*(p-C);
    		if (s2 < 0.0) s2 = 0.0;
    		S = sqrt(s2);
    	
    		/*HA : HAUTEUR DU TRIANGLE A PARTIR DU SOMMET Structure.NB_TOTAL*/
		ha = 2 * S / A;
				
		/*ac + ab = A */
		ac = sqrt(B*B - ha*ha);
		ab = sqrt(C*C - ha*ha);
				
		/*RECHERCHE SI LE PIED DE LA HAUTEUR EST POSE SUR LE COTE A*/
		if((ac < A) && (ab < A))
			{
			/*RECHERCHE SI LA HAUTEUR EST INFERIEUR AU PAS_MAILLAGE * FACT DANS CE CAS LE NOEUD EST TROP PROCHE DU CONTOUR*/
			if (ha < panneau[no_pa].pas_maillage / panneau[no_pa].longueur_repos * fact)
				{
				trouve = 0;
				break;
				}
			}
		}
	return trouve;
	}
	
	
int proche_panneau_filaire(float UU, float VV, int no_pa, float fact)
	{
	float  U1, V1, distance ;
	int    trouve, no, deb;
	
	/*
	RECHERCHE DES NOEUDS TROP PROCHE DES NOEUDS DU CONTOUR DU PANNEAU NO_PA
	SI TROP PROCHE DU CONTOUR TROUVE = 0
	SI LOIN DU CONTOUR TROUVE = 1
	*/
	trouve = 1;
	for (no=1;no<=panneau[no_pa].nb_noeud_contour;no++)
		{
		deb = panneau[no_pa].noeud_contour[no];
		
		/*COORDONNEES DU NOEUD DU CONTOUR TRAITE*/
		U1 = noeud[deb].u;
		V1 = noeud[deb].v;
				
		/*DISTANCE ENTRE LES POINTS*/
		distance = sqrt((U1-UU) * (U1-UU) + (V1-VV) * (V1-VV));
		
		/*RECHERCHE SI LA DISTANCE  EST INFERIEUR AU PAS_MAILLAGE * FACT DANS CE CAS LE NOEUD 
		EST TROP PROCHE DU CONTOUR*/
		if (distance < panneau[no_pa].pas_maillage / panneau[no_pa].longueur_repos * fact)
			{
			trouve = 0;
			break;
			}
		}
	return trouve;
	}
	
int sewn_diamond_panel2cable(int cable, int panel)
	{
	//return 1 if the cable n° cable is sewn to the diamond panel n° panel 
	int no,deb_panel,fin_panel,link1,link2,li,obj,obj1,obj2,trouve;
	
	trouve = 0;
	for (no=1;no<=panneau[panel].nb_noeud_contour;no++)
		{
		//beginning of verification that there are ropes all around this panel of netting
		deb_panel = no;
		if (no == panneau[panel].nb_noeud_contour)
			{
			fin_panel = 1;
			}
		else
			{
			fin_panel = no+1;
			}
		//printf("deb_panel %d fin_panel %d  ",deb_panel,fin_panel);	
		link1 = 0;	
		link2 = 0;	
		for (li=1;li<=Structure.nb_liaison;li++)
			{
			for (obj=1;obj<=Lien[li].nb_liaison;obj++)
				{
				//printf("li %d obj %d type %c struct %d extre %d\n",li,obj,Lien[li].type[obj],Lien[li].structure[obj],Lien[li].extremite[obj] );			
				if ((Lien[li].type[obj] == 'p') && (Lien[li].structure[obj] == panel) && (Lien[li].extremite[obj] == deb_panel))
					{
					link1 = li;
					}
				}
			}
		for (li=1;li<=Structure.nb_liaison;li++)
			{
			for (obj=1;obj<=Lien[li].nb_liaison;obj++)
				{
				//printf("li %d obj %d type %c struct %d extre %d\n",li,obj,Lien[li].type[obj],Lien[li].structure[obj],Lien[li].extremite[obj] );			
				if ((Lien[li].type[obj] == 'p') && (Lien[li].structure[obj] == panel) && (Lien[li].extremite[obj] == fin_panel))
					{
					link2 = li;
					}
				}
			}
		//printf("link1 %4d link2 %4d  ",link1,link2);			
		for (obj1=1;obj1<=Lien[link1].nb_liaison;obj1++)
			{
			if ((Lien[link1].type[obj1] == 'e') && (Lien[link1].structure[obj1] == cable))
				{
				//printf("typ1 %c struct %4d extr %4d \n",Lien[link1].type[obj1],Lien[link1].structure[obj1],Lien[link1].extremite[obj1]);			
				for (obj2=1;obj2<=Lien[link2].nb_liaison;obj2++)
					{
					if ((Lien[link2].type[obj2] == 'e') && (Lien[link2].structure[obj2] == cable))
						{
						trouve = 1;
						}
					}
				}
			}			
		}
	return trouve;
	}
	
int sewn_diamond_panel2cable2(int cable, int panel, int *corner1, int *corner2)
	{
	//return 1 if the cable n° cable is sewn to the diamond panel n° panel. 
	//corner1 is linked to extremity 1 of the cable.
	//corner2 is linked to extremity 2 of the cable.
	int no,deb_panel,fin_panel,link1,link2,li,obj,obj1,obj2,trouve;
	
	trouve = 0;
	*corner1 = 0;
	*corner2 = 0;
	for (no=1;no<=panneau[panel].nb_noeud_contour;no++)
		{
		//beginning of verification that there are ropes all around this panel of netting
		deb_panel = no;
		if (no == panneau[panel].nb_noeud_contour)
			{
			fin_panel = 1;
			}
		else
			{
			fin_panel = no+1;
			}
		//printf("deb_panel %d fin_panel %d  ",deb_panel,fin_panel);	
		link1 = 0;	
		link2 = 0;	
		for (li=1;li<=Structure.nb_liaison;li++)
			{
			for (obj=1;obj<=Lien[li].nb_liaison;obj++)
				{
				//printf("li %d obj %d type %c struct %d extre %d\n",li,obj,Lien[li].type[obj],Lien[li].structure[obj],Lien[li].extremite[obj] );			
				if ((Lien[li].type[obj] == 'p') && (Lien[li].structure[obj] == panel) && (Lien[li].extremite[obj] == deb_panel))
					{
					link1 = li;
					}
				}
			}
		for (li=1;li<=Structure.nb_liaison;li++)
			{
			for (obj=1;obj<=Lien[li].nb_liaison;obj++)
				{
				//printf("li %d obj %d type %c struct %d extre %d\n",li,obj,Lien[li].type[obj],Lien[li].structure[obj],Lien[li].extremite[obj] );			
				if ((Lien[li].type[obj] == 'p') && (Lien[li].structure[obj] == panel) && (Lien[li].extremite[obj] == fin_panel))
					{
					link2 = li;
					}
				}
			}
		//printf("link1 %4d link2 %4d  ",link1,link2);			
		for (obj1=1;obj1<=Lien[link1].nb_liaison;obj1++)
			{
			if ((Lien[link1].type[obj1] == 'e') && (Lien[link1].structure[obj1] == cable))
				{
				//printf("typ1 %c struct %4d extr %4d \n",Lien[link1].type[obj1],Lien[link1].structure[obj1],Lien[link1].extremite[obj1]);			
				for (obj2=1;obj2<=Lien[link2].nb_liaison;obj2++)
					{
					if ((Lien[link2].type[obj2] == 'e') && (Lien[link2].structure[obj2] == cable))
						{
						trouve = 1;
						}
					}
				}
			}			
		}

	link1 = 0;	
	link2 = 0;	
	for (li=1;li<=Structure.nb_liaison;li++)
		{
		for (obj=1;obj<=Lien[li].nb_liaison;obj++)
			{
			if ((Lien[li].type[obj] == 'e') && (Lien[li].structure[obj] == cable) && (Lien[li].extremite[obj] == 1))
				{
				link1 = li;
				}
			}
		}
	for (obj=1;obj<=Lien[link1].nb_liaison;obj++)
		{
		if ((Lien[link1].type[obj] == 'p') && (Lien[link1].structure[obj] == panel))
			{
			*corner1 = Lien[link1].extremite[obj];
			}
		}
	for (li=1;li<=Structure.nb_liaison;li++)
		{
		for (obj=1;obj<=Lien[li].nb_liaison;obj++)
			{
			if ((Lien[li].type[obj] == 'e') && (Lien[li].structure[obj] == cable) && (Lien[li].extremite[obj] == 2))
				{
				link2 = li;
				}
			}
		}
	for (obj=1;obj<=Lien[link2].nb_liaison;obj++)
		{
		if ((Lien[link2].type[obj] == 'p') && (Lien[link2].structure[obj] == panel))
			{
			*corner2 = Lien[link2].extremite[obj];
			}
		}
	//printf("panel %4d cable %4d corner1 %4d corner2 %4d trouve %4d\n",panel,cable,*corner1,*corner2, trouve);

	return trouve;
	}

