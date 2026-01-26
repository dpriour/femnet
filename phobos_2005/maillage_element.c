#define PRINCIPAL 0
#include "phobos.h"

void maillage_element()
	{
	int   el,co,nloc1,nloc2,nopan,maille,mode;
	char  pan;
		
	/*charger le fichier de donnees si ce n est pas fait*/
	mode = GetMenuItemChecked(w[1]);
	if (mode == 0) charger_phobos();
	for (el=1;el<=Structure.NbTypeelem;el++)
		{
		if(element[el].flag_maillage == 0)
			{
			if (element[el].nb_barre <= 0.0)
				{
				printf("ERREUR \n");
				printf("le nb de barre n est pas positif = %12d \n",element[el].nb_barre);
				printf("Element = %12d \n",el);
				exit(0);
				}
			co = 1;
			maille = liaison_maille_el(co,el,&pan,&nopan,&nloc1,&nloc2);			
			if (maille == 0)
				{
				maillage_element_libre(el);
				}
			if ((maille == 1) || (maille == 2))
				{
				maillage_element_panneau(el,nopan,nloc1,nloc2);
				}
			if ((maille == 3) || (maille == 4))
				{
				maillage_element_element(el,nopan,nloc1);
				}
			if ((maille == 5) || (maille == 6))
				{
				maillage_element_pan_hexa(el,nopan,nloc1,nloc2);
				}
			element[el].flag_maillage = 1;
			}
		}
	printf("Structure.nb_total = %4d \n",Structure.nb_total);
	
	SetMenuItemChecked(w[25],1);
	}

int liaison_maille_el(int neud,int elemen,char *structur,int *nostructur,int *debutsegm,int *finsegm)
	{
	/*
	neud       = debut du segment traite,
	elemen     = element traite,
	renvoie 1 si le noeud est lie par un lien a une structure deja maillee, sinon 0
	structur   = type de la structure maillee
	nostructur = numero de cette structure
	debutsegm  = numero dans la numerotation locale de la premiere extremite du segment maillee
	finsegm    = numero dans la numerotation locale de la derniere extremite du segment maillee
	*/
	
	int noeue,noliennoeud,noliennoeue,pa,el,noliendeb,nolienfin;
	int co,cp,deb,fin;
	
	/*neud = debut du cote, noeue : fin du cote dans la numerotation locale*/
	if (neud == 1) noeue = 2;
	if (neud == 2) noeue = 1;
	deb = element[elemen].extremite[neud];
	fin = element[elemen].extremite[noeue];
	noliennoeud = appartient_liaison(deb);
	noliennoeue = appartient_liaison(fin);
	
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		if (panneau[pa].flag_maillage == 1)
			{
			for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
				{
				/*co = debut du cote, cp : fin du cote dans la numeroattion locale*/
				if (co != panneau[pa].nb_noeud_contour) cp = co+1;
				if (co == panneau[pa].nb_noeud_contour) cp = 1;
				/*deb = debut du cote, fin : fin du cote dans la numerotation globale*/
				deb = panneau[pa].noeud_contour[co];
				fin = panneau[pa].noeud_contour[cp];
				noliendeb = appartient_liaison(deb);
				nolienfin = appartient_liaison(fin);
				if((noliendeb != 0) && (nolienfin != 0) && (noliendeb == noliennoeud) && (nolienfin == noliennoeue))
					{
					*structur = 'p';
					*nostructur = pa;
					*debutsegm = co;
					*finsegm = cp;
					return 1;
					}
				if((noliendeb != 0) && (nolienfin != 0) && (noliendeb == noliennoeue) && (nolienfin == noliennoeud))
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

	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{
		if (pan_hexa[pa].flag_maillage == 1)
			{
			for (co=1;co<=pan_hexa[pa].nb_noeud_contour;co++)
				{
				/*CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE*/
				if (co != pan_hexa[pa].nb_noeud_contour) cp = co+1;
				if (co == pan_hexa[pa].nb_noeud_contour) cp = 1;
				/*DEB = DEBUT DU COTE, FIN : FIN DU COTE DANS LA NUMEROTATION GLOBALE*/
				deb = pan_hexa[pa].noeud_contour[co];
				fin = pan_hexa[pa].noeud_contour[cp];
				noliendeb = appartient_liaison(deb);
				nolienfin = appartient_liaison(fin);
				/*printf("deb = %4d\n",deb);
				printf("fin = %4d\n",fin);*/
				
				if((noliendeb != 0) && (nolienfin != 0) && (noliendeb == noliennoeud) && (nolienfin == noliennoeue))
					{
					*structur = 'h';
					*nostructur = pa;
					*debutsegm = co;
					*finsegm = cp;
					return 5;
					}
				if((noliendeb != 0) && (nolienfin != 0) && (noliendeb == noliennoeue) && (nolienfin == noliennoeud))
					{
					*structur = 'h';
					*nostructur = pa;
					*debutsegm = cp;
					*finsegm = co;
					return 6;
					}
				}
			}
		}

	for (el=1;el<=Structure.NbTypeelem;el++)
		{
		if ((el != elemen) && (element[el].flag_maillage == 1))
			{
			deb = element[el].extremite[1];
			fin = element[el].extremite[2];
			noliendeb = appartient_liaison(deb);
			nolienfin = appartient_liaison(fin);
			if((noliendeb != 0) && (nolienfin != 0) && (noliendeb == noliennoeud) && (nolienfin == noliennoeue))
				{
				*structur = 'e';
				*nostructur = el;
				*debutsegm = 1;
				*finsegm = 2;
				return 3;
				}
			if((noliendeb != 0) && (nolienfin != 0) && (noliendeb == noliennoeue) && (nolienfin == noliennoeud))
				{
				*structur = 'e';
				*nostructur = el;
				*debutsegm = 2;
				*finsegm = 1;
				return 4;
				}
			}
		}
	*structur = ' ';
	*nostructur = 0;
	*debutsegm = 0;
	*finsegm = 0;
	return 0;
	}

void maillage_element_libre(int el)
	{
	int    zi, nb_coupe, deb, fin ;
	float  xdeb, xfin, ydeb, yfin, zdeb, zfin ;
	
	deb = element[el].extremite[1];
	fin = element[el].extremite[2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	nb_coupe = element[el].nb_barre;

	for (zi=1;zi<=nb_coupe - 1 ;zi++)
		{
		Structure.nb_barre++;
		if ( Structure.nb_barre>= NBMAXBARRE)
			{
			printf(" NBMAXBARRE trop petit %4d < %4d \n",NBMAXBARRE,Structure.nb_barre );
			exit(0);
			}
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		/*creation des barres*/
		if (zi == 1) barre[Structure.nb_barre].noeud[1] = deb;
		if (zi != 1) barre[Structure.nb_barre].noeud[1] = Structure.nb_total - 1;
		barre[Structure.nb_barre].noeud[2] = Structure.nb_total;
		/*Le no de type de la barre est le numero de l element*/
		barre[Structure.nb_barre].type = el;
		barre[Structure.nb_barre].netting2ropes_panel = 0;
		/*Creation d un noeud sur l element*/
		element[el].nb_nodes++;
		
		
		
		element[el].noeud[zi] = Structure.nb_total;
		//printf("element[%d].noeud[%d] = %4d nb_nodes %d\n",el,zi,element[el].noeud[zi],element[el].nb_nodes);
		/*Creation du noeud*/
		noeud[Structure.nb_total].x = xdeb + zi * (xfin-xdeb) / nb_coupe;
		noeud[Structure.nb_total].y = ydeb + zi * (yfin-ydeb) / nb_coupe;
		noeud[Structure.nb_total].z = zdeb + zi * (zfin-zdeb) / nb_coupe;
		barre[Structure.nb_barre].pro[1] = (float) (zi-1) / nb_coupe ;
		barre[Structure.nb_barre].pro[2] = (float)  zi    / nb_coupe ;
		element[el].prop[zi] =            (double)  zi    / nb_coupe  ;
		barre[Structure.nb_barre].longueur_repos = (float)  element[el].lgrepos * fabs(barre[Structure.nb_barre].pro[1]-barre[Structure.nb_barre].pro[2]);
		noeud[Structure.nb_total].type = element[el].type_noeud;
		}
	Structure.nb_barre++;
	if (Structure.nb_barre >= NBMAXBARRE)
		{
		printf(" NBMAXBARRE trop petit %4d < %4d \n",NBMAXBARRE,Structure.nb_barre );
		exit(0);
		}
	if (nb_coupe >  1) 
		{
		barre[Structure.nb_barre].noeud[1] = Structure.nb_total;
		barre[Structure.nb_barre].pro[1] = (float) (nb_coupe - 1) / nb_coupe ;
		}
	if (nb_coupe == 1) 
		{
		barre[Structure.nb_barre].noeud[1] = deb;
		barre[Structure.nb_barre].pro[1] = 0.0 ;
		}
	barre[Structure.nb_barre].noeud[2] = fin;
	barre[Structure.nb_barre].pro[2] = 1.0;
	barre[Structure.nb_barre].longueur_repos = (float)  element[el].lgrepos * fabs(barre[Structure.nb_barre].pro[1]-barre[Structure.nb_barre].pro[2]);
	barre[Structure.nb_barre].type = el;
	barre[Structure.nb_barre].netting2ropes_panel = 0;
	
	//printf(" Structure.nb_barre= %4d ",Structure.nb_barre);
	//printf(" Structure.nb_total= %4d \n",Structure.nb_total);

	/*type de barre*/
	/*if ( el >= NBMAXTYPEBARRE)
		{
		printf("NBMAXTYPEBARRE  trop petit %4d < %4d \n",NBMAXTYPEBARRE,el );
		exit(0);
		}
	TypeBarre[el].raideur_traction = element[el].raideur_traction;
	TypeBarre[el].raideur_compression = element[el].raideur_compression;
	TypeBarre[el].longueur_repos = element[el].lgrepos / nb_coupe;
	TypeBarre[el].diam_hydro = element[el].diametrehydro;
	TypeBarre[el].rho = element[el].rhoelement;
	TypeBarre[el].cdnormal = element[el].cdnormal;
	TypeBarre[el].ftangent = element[el].ftangent;*/
	}
	
void maillage_element_element(int el,int el2,int nlo1)
	{
	int    zi,nb_coupe,deb,fin,premier_loc,premier_cote,sens_cote,nb_lai;
	float  xdeb,xfin,ydeb,yfin,zdeb,zfin;
	
	deb = element[el2].extremite[1];
	fin = element[el2].extremite[2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	nb_coupe = element[el2].nb_barre;
	element[el].nb_barre = nb_coupe; 		/*Changement du nombre de barres sur l element el*/
	
	//printf("el %d el2 %d  nb_coupe %d\n",el,el2, nb_coupe);
	/**********************************************/
  	element[el].noeud = (int *) realloc(element[el].noeud, (1+ element[el].nb_barre) * sizeof(int));
	if (element[el].noeud    == NULL)
		{
		printf(" element[el].noeud 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	element[el].barre = (int *) realloc(element[el].barre, (1+ element[el].nb_barre) * sizeof(int));
	if (element[el].barre    == NULL)
		{
		printf(" element[el].barre 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	element[el].prop = (double *) realloc(element[el].prop, (1+ element[el].nb_barre) * sizeof(double));
	if (element[el].prop    == NULL)
		{
		printf(" element[el].prop 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	deb = element[el].extremite[1];
	fin = element[el].extremite[2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;

	if(nlo1 == 1)
		{
		premier_loc = 1;
		premier_cote = element[el2].noeud[premier_loc];
		sens_cote = +1;
		}
	if(nlo1 == 2)
		{
		premier_loc = nb_coupe - 1;
		premier_cote = element[el2].noeud[premier_loc];
		sens_cote = -1;
		}

	for (zi=1;zi<=nb_coupe -1 ;zi++)
		{
		Structure.nb_barre++;
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		/*creation des barres*/
		if (zi == 1)  barre[Structure.nb_barre].noeud[1] = deb ;
		if (zi != 1)  barre[Structure.nb_barre].noeud[1] = Structure.nb_total - 1; 
		barre[Structure.nb_barre].noeud[2] = Structure.nb_total;
		/*le no de type de la barre est le numero de l element*/
		barre[Structure.nb_barre].type = el;
		barre[Structure.nb_barre].netting2ropes_panel = 0;
		
		element[el].noeud[zi] = Structure.nb_total;
		printf("elemenu[%d].noeud[%d] = %4d \n",el,zi,element[el].noeud[zi]);
		noeud[Structure.nb_total].x      = xdeb + zi * (xfin-xdeb) / nb_coupe;
		noeud[Structure.nb_total].y      = ydeb + zi * (yfin-ydeb) / nb_coupe;
		noeud[Structure.nb_total].z      = zdeb + zi * (zfin-zdeb) / nb_coupe;
		barre[Structure.nb_barre].pro[1] = (float) (zi-1) / nb_coupe ;
		barre[Structure.nb_barre].pro[2] = (float)  zi    / nb_coupe ;
		element[el].prop[zi] =            (double)  zi    / nb_coupe ;
		barre[Structure.nb_barre].longueur_repos = (float)  element[el].lgrepos * fabs(barre[Structure.nb_barre].pro[1]-barre[Structure.nb_barre].pro[2]);
		noeud[Structure.nb_total].type   = element[el].type_noeud;
		
		nb_lai = appartient_liaison(premier_cote + sens_cote * (zi - 1));
		
		/*
		printf("premier_cote = %4d sens_cote =  %4d ens =  %4d\n",premier_cote,sens_cote,premier_cote + sens_cote * (zi - 1) );
		printf("element = %4d zi =  %4d nb_lai =  %4d\n",el,zi, nb_lai );
		*/
		
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
				printf("Lien[Structure.nb_Lien].noeud  1 = NULL  \n" );
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
			Lien[Structure.nb_lien].type[2] = 'e';
			Lien[Structure.nb_lien].structure[1] = el2;
			Lien[Structure.nb_lien].structure[2] = el ;
			Lien[Structure.nb_lien].extremite[1] = premier_loc + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].extremite[2] = zi;
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
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'e';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = el;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = zi;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		}
	Structure.nb_barre++;
	if ( Structure.nb_barre>= NBMAXBARRE)
		{
		printf(" NBMAXBARRE trop petit %4d < %4d \n",NBMAXBARRE,Structure.nb_barre );
		exit(0);
		}
	if (nb_coupe > 1)
		{
		barre[Structure.nb_barre].noeud[1] = Structure.nb_total;
		}
	else
		{
		barre[Structure.nb_barre].noeud[1] = deb;
		}	
	barre[Structure.nb_barre].noeud[2] = fin;
	barre[Structure.nb_barre].pro[1] = (float) ( nb_coupe - 1 ) / nb_coupe;;
	barre[Structure.nb_barre].pro[2] = 1.0;
	barre[Structure.nb_barre].longueur_repos = (float)  element[el].lgrepos * fabs(barre[Structure.nb_barre].pro[1]-barre[Structure.nb_barre].pro[2]);
	barre[Structure.nb_barre].type = el;
	barre[Structure.nb_barre].netting2ropes_panel = 0;
	
	printf(" el %4d ",el);
	printf(" Structure.nb_barre %4d ",Structure.nb_barre);
	printf(" extremites %4d %4d",barre[Structure.nb_barre].noeud[1],barre[Structure.nb_barre].noeud[2]);
	printf(" Structure.nb_total %4d \n",Structure.nb_total);
	
	
	/*type de barre*/
	/*if ( el >= NBMAXPANNEAU)
		{
		printf(" NBMAXPANNEAU trop petit %4d < %4d \n",NBMAXPANNEAU,el );
		exit(0);
		}
	TypeBarre[el].raideur_traction = element[el].raideur_traction;
	TypeBarre[el].raideur_compression = element[el].raideur_compression;
	TypeBarre[el].longueur_repos = element[el].lgrepos / nb_coupe;
	TypeBarre[el].diam_hydro = element[el].diametrehydro;
	TypeBarre[el].rho = element[el].rhoelement;
	TypeBarre[el].cdnormal = element[el].cdnormal;
	TypeBarre[el].ftangent = element[el].ftangent;*/
	}
	
void maillage_element_panneau(int el,int nopan,int nlo1,int nlo2)
	{
	int    zi,nb_coupe,deb,fin,premier_loc,premier_cote,sens_cote,nb_lai,nlo3;
	float  xdeb,xfin,ydeb,yfin,zdeb,zfin,ss;
	
	/* 
	   el : numero de l element
	nopan : numero du panneau auquel el est lie
	 nlo1 : numero de l extremite du panneau liee a l extremite 1 de el
	 nlo2 :     -   -      -       -   -      -   -     -       2  -  -
	Maillage d un element a partir d un panneau deja maille, auquel il est lie par les extremites 
	*/
	
	/* determination du nombre de coupes de l element el a partir du maillage du panneau nopan auquel il est lie */
	if (nlo1 + 1 == nlo2)
		{
		if(panneau[nopan].suivant_contour[nlo1] == 0)
			{
			/*pas de point de cote sur ce segment de contour*/
			nb_coupe = 1;
			}
		else
			{
			nlo3 = nlo2 - 1;
			do
				{
				nlo3 += 1;
				}
			while ((panneau[nopan].suivant_contour[nlo3] == 0) && (nlo3 != panneau[nopan].nb_noeud_contour));
			if (panneau[nopan].suivant_contour[nlo3] != 0)
				{
				nb_coupe = panneau[nopan].suivant_contour[nlo3] - panneau[nopan].suivant_contour[nlo1] + 1;
				}
			else
				{
				nb_coupe = panneau[nopan].nb_noeud_cote - panneau[nopan].suivant_contour[nlo1] + 2;
				}
			}
		}
	if (nlo1 - 1 == nlo2)
		{
		if(panneau[nopan].suivant_contour[nlo2] == 0)
			{
			/*pas de point de cote sur ce segment de contour*/
			nb_coupe = 1;
			}
		else
			{
			nlo3 = nlo1 - 1;
			do
				{
				nlo3 += 1;
				}
			while ((panneau[nopan].suivant_contour[nlo3] == 0) && (nlo3 != panneau[nopan].nb_noeud_contour));
			if (panneau[nopan].suivant_contour[nlo3] != 0)
				{
				nb_coupe = panneau[nopan].suivant_contour[nlo3] - panneau[nopan].suivant_contour[nlo2] + 1;
				}
			else
				{
				nb_coupe = panneau[nopan].nb_noeud_cote - panneau[nopan].suivant_contour[nlo2] + 2;
				}
			}
		}
	if ((nlo1 - 1 != nlo2) && (nlo1 + 1 != nlo2))
		{
		/*dans ce cas nlo1 et nlo2 sont 1 et panneau[nopan].nb_noeud_contour ou inversement*/
		if(panneau[nopan].suivant_contour[panneau[nopan].nb_noeud_contour] == 0)
			{
			/*pas de point de cote sur ce segment de contour*/
			nb_coupe = 1;
			}
		else
			{
			nb_coupe = panneau[nopan].nb_noeud_cote - panneau[nopan].suivant_contour[panneau[nopan].nb_noeud_contour] + 2;
			}
		}
	/*Changement du nombre de barres sur l element el*/
	element[el].nb_barre = nb_coupe; 		
	
	/**********************************************/
  	element[el].noeud = (int *) realloc(element[el].noeud, (1+ element[el].nb_barre) * sizeof(int));
	if (element[el].noeud    == NULL)
		{
		printf(" element[el].noeud 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	element[el].barre = (int *) realloc(element[el].barre, (1+ element[el].nb_barre) * sizeof(int));
	if (element[el].barre    == NULL)
		{
		printf(" element[el].barre 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	element[el].prop = (double *) realloc(element[el].prop, (1+ element[el].nb_barre) * sizeof(double));
	if (element[el].prop    == NULL)
		{
		printf(" element[el].prop 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	deb = element[el].extremite[1];
	fin = element[el].extremite[2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;

	/* determination du sens de maillage du panneau et initialisation en consequence du premier noeud de cote du panneau */
	if((nlo1 == nlo2-1) || ((nlo1 == panneau[nopan].nb_noeud_contour) && (nlo2 == 1)))
		{
		premier_loc = panneau[nopan].suivant_contour[nlo1];
		premier_cote = panneau[nopan].noeud_cote[panneau[nopan].suivant_contour[nlo1]];
		sens_cote = +1;
		}
	if((nlo2 == nlo1-1) || ((nlo2 == panneau[nopan].nb_noeud_contour) && (nlo1 == 1)))
		{
		premier_loc = panneau[nopan].suivant_contour[nlo2] + nb_coupe - 2;
		premier_cote = panneau[nopan].noeud_cote[panneau[nopan].suivant_contour[nlo2]] + nb_coupe - 2;
		sens_cote = -1;
		}
		
	for ( zi = 1 ; zi <= nb_coupe - 1 ; zi++ )
		{
		Structure.nb_barre++;
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		/*creation des barres*/
		if (zi == 1) barre[Structure.nb_barre].noeud[1] = deb ;
		if (zi != 1) barre[Structure.nb_barre].noeud[1] = Structure.nb_total - 1; 
		barre[Structure.nb_barre].noeud[2] = Structure.nb_total;
		/*le no de type de la barre est le numero de l element*/
		barre[Structure.nb_barre].type = el;
		barre[Structure.nb_barre].netting2ropes_panel = 0;
			
		/* ss vaut 0.0 si sens_cote vaut 1, 1.0 si sens_cote vaut -1 */
		ss = (float) 0.5 * fabs(sens_cote - 1.);
		element[el].noeud[zi]    = Structure.nb_total;
		printf("elemenv[%d].noeud[%d] = %4d\n",el,zi,element[el].noeud[zi]);
		noeud[Structure.nb_total].x = xdeb + (ss + sens_cote * panneau[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (xfin-xdeb) ;
		noeud[Structure.nb_total].y = ydeb + (ss + sens_cote * panneau[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (yfin-ydeb) ;
		noeud[Structure.nb_total].z = zdeb + (ss + sens_cote * panneau[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (zfin-zdeb) ;
		
		if ( sens_cote == 1 )
			{ /* On parcourt le cote du panneau dans le sens maillé donc */
		 	 barre[Structure.nb_barre].pro[2] = panneau[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)];
		 	 if ( zi == 1 ) { barre[Structure.nb_barre].pro[1] = 0.0 				    ; }		/* Pour la 1ère barre, on a 0.0 */
		 	 else           { barre[Structure.nb_barre].pro[1] = barre[Structure.nb_barre - 1].pro[2] ; }		/* Pour les autres barres, on s'appuie sur la barre precedente */
			}
		else
			{ /* On parcourt le cote de panneau dans le sens inverse maillé donc */
		 	 barre[Structure.nb_barre].pro[2] =  1. - panneau[nopan].prop_cote[premier_loc + sens_cote * (zi - 1) ];
		 	 if ( zi == 1 ) { barre[Structure.nb_barre].pro[1] = 0.0    			    ; }
		 	 else           { barre[Structure.nb_barre].pro[1] = barre[Structure.nb_barre - 1].pro[2] ; }
			}
		
		barre[Structure.nb_barre].longueur_repos = (float)  element[el].lgrepos * fabs(barre[Structure.nb_barre].pro[1]-barre[Structure.nb_barre].pro[2]);
		noeud[Structure.nb_total].type   =  element[el].type_noeud ;
		
		nb_lai = appartient_liaison( premier_cote + sens_cote * (zi - 1) ) ;
		
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
			Lien[Structure.nb_lien].type[2] = 'e';
			Lien[Structure.nb_lien].structure[1] = nopan;
			Lien[Structure.nb_lien].structure[2] = el ;
			Lien[Structure.nb_lien].extremite[1] = premier_loc + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].extremite[2] = zi;
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
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'e';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = el;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = zi;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		}
	Structure.nb_barre++;
	if ( Structure.nb_barre>= NBMAXBARRE)
		{
		printf(" NBMAXBARRE trop petit %4d < %4d \n",NBMAXBARRE,Structure.nb_barre );
		exit(0);
		}
	if (zi == 1)  barre[Structure.nb_barre].noeud[1] = deb ;
	else          barre[Structure.nb_barre].noeud[1] = Structure.nb_total;
	barre[Structure.nb_barre].noeud[2] = fin;
	if (zi == 1)  barre[Structure.nb_barre].noeud[1] = deb ;
	if (nb_coupe == 1 ) { barre[Structure.nb_barre].pro[1] = 0.0 ;}					/* Pour le cas d'une seule barre */
	else 		    { barre[Structure.nb_barre].pro[1] = barre[Structure.nb_barre - 1].pro[2] ;}	/* pour les autres, on s'appuie sur la barre précédente*/
	barre[Structure.nb_barre].pro[2] = 1.0;
	barre[Structure.nb_barre].longueur_repos = (float)  element[el].lgrepos * fabs(barre[Structure.nb_barre].pro[1]-barre[Structure.nb_barre].pro[2]);
	barre[Structure.nb_barre].type = el;
	barre[Structure.nb_barre].netting2ropes_panel = 0;
	
	//printf(" el= %4d ",el);
	//printf(" Structure.nb_barre= %4d ",Structure.nb_barre);
	//printf(" Structure.nb_total= %4d \n",Structure.nb_total);
	
	
	/*type de barre*/
	/*if ( el >= NBMAXPANNEAU)
		{
		printf(" NBMAXPANNEAU trop petit %4d < %4d \n",NBMAXPANNEAU,el );
		exit(0);
		}
	TypeBarre[el].raideur_traction = element[el].raideur_traction;
	TypeBarre[el].raideur_compression = element[el].raideur_compression;
	TypeBarre[el].longueur_repos = element[el].lgrepos / nb_coupe;
	TypeBarre[el].diam_hydro = element[el].diametrehydro;
	TypeBarre[el].rho = element[el].rhoelement;
	TypeBarre[el].cdnormal = element[el].cdnormal;
	TypeBarre[el].ftangent = element[el].ftangent;*/
	}
	
void maillage_element_pan_hexa(int el,int nopan,int nlo1,int nlo2)
	{
	int    zi,nb_coupe,deb,fin,premier_loc,premier_cote,sens_cote,nb_lai,nlo3;
	float  xdeb,xfin,ydeb,yfin,zdeb,zfin,ss;
	
	/* 
	   el : numero de l element
	nopan : numero du panneau auquel el est lie
	 nlo1 : numero de l extremite du panneau liee a l extremite 1 de el
	 nlo2 :     -   -      -       -   -      -   -     -       2  -  -
	Maillage d un element a partir d un panneau a maille hexagonale deja maille, auquel il est lie par les extremites 
	*/
	
	/* determination du nombre de coupes de l element el a partir du maillage du panneau nopan auquel il est lie */
	if (nlo1 + 1 == nlo2)
		{
		if(pan_hexa[nopan].suivant_contour[nlo1] == 0)
			{
			/*pas de point de cote sur ce segment de contour*/
			nb_coupe = 1;
			}
		else
			{
			nlo3 = nlo2 - 1;
			do
				{
				nlo3 += 1;
				}
			while ((pan_hexa[nopan].suivant_contour[nlo3] == 0) && (nlo3 != pan_hexa[nopan].nb_noeud_contour));
			if (pan_hexa[nopan].suivant_contour[nlo3] != 0)
				{
				nb_coupe = pan_hexa[nopan].suivant_contour[nlo3] - pan_hexa[nopan].suivant_contour[nlo1] + 1;
				}
			else
				{
				nb_coupe = pan_hexa[nopan].nb_noeud_cote - pan_hexa[nopan].suivant_contour[nlo1] + 2;
				}
			}
		}
	if (nlo1 - 1 == nlo2)
		{
		if(pan_hexa[nopan].suivant_contour[nlo2] == 0)
			{
			/*pas de point de cote sur ce segment de contour*/
			nb_coupe = 1;
			}
		else
			{
			nlo3 = nlo1 - 1;
			do
				{
				nlo3 += 1;
				}
			while ((pan_hexa[nopan].suivant_contour[nlo3] == 0) && (nlo3 != pan_hexa[nopan].nb_noeud_contour));
			if (pan_hexa[nopan].suivant_contour[nlo3] != 0)
				{
				nb_coupe = pan_hexa[nopan].suivant_contour[nlo3] - pan_hexa[nopan].suivant_contour[nlo2] + 1;
				}
			else
				{
				nb_coupe = pan_hexa[nopan].nb_noeud_cote - pan_hexa[nopan].suivant_contour[nlo2] + 2;
				}
			}
		}
	if ((nlo1 - 1 != nlo2) && (nlo1 + 1 != nlo2))
		{
		/*dans ce cas nlo1 et nlo2 sont 1 et pan_hexa[nopan].nb_noeud_contour ou inversement*/
		if(pan_hexa[nopan].suivant_contour[pan_hexa[nopan].nb_noeud_contour] == 0)
			{
			/*pas de point de cote sur ce segment de contour*/
			nb_coupe = 1;
			}
		else
			{
			nb_coupe = pan_hexa[nopan].nb_noeud_cote - pan_hexa[nopan].suivant_contour[pan_hexa[nopan].nb_noeud_contour] + 2;
			}
		}
	/*Changement du nombre de barres sur l element el*/
	element[el].nb_barre = nb_coupe; 		
	
	/**********************************************/
  	element[el].noeud = (int *) realloc(element[el].noeud, (1+ element[el].nb_barre) * sizeof(int));
	if (element[el].noeud    == NULL)
		{
		printf(" element[el].noeud 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	element[el].barre = (int *) realloc(element[el].barre, (1+ element[el].nb_barre) * sizeof(int));
	if (element[el].barre    == NULL)
		{
		printf(" element[el].barre 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
  	element[el].prop = (double *) realloc(element[el].prop, (1+ element[el].nb_barre) * sizeof(double));
	if (element[el].prop    == NULL)
		{
		printf(" element[el].prop 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	deb = element[el].extremite[1];
	fin = element[el].extremite[2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;

	/* determination du sens de maillage du panneau et initialisation en consequence du premier noeud de cote du panneau */
	if((nlo1 == nlo2-1) || ((nlo1 == pan_hexa[nopan].nb_noeud_contour) && (nlo2 == 1)))
		{
		premier_loc = pan_hexa[nopan].suivant_contour[nlo1];
		premier_cote = pan_hexa[nopan].noeud_cote[pan_hexa[nopan].suivant_contour[nlo1]];
		sens_cote = +1;
		}
	if((nlo2 == nlo1-1) || ((nlo2 == pan_hexa[nopan].nb_noeud_contour) && (nlo1 == 1)))
		{
		premier_loc = pan_hexa[nopan].suivant_contour[nlo2] + nb_coupe - 2;
		premier_cote = pan_hexa[nopan].noeud_cote[pan_hexa[nopan].suivant_contour[nlo2]] + nb_coupe - 2;
		sens_cote = -1;
		}
		
	for ( zi = 1 ; zi <= nb_coupe - 1 ; zi++ )
		{
		Structure.nb_barre++;
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		/*creation des barres*/
		if (zi == 1)  barre[Structure.nb_barre].noeud[1] = deb ;
		if (zi != 1) barre[Structure.nb_barre].noeud[1] = Structure.nb_total - 1; 
		barre[Structure.nb_barre].noeud[2] = Structure.nb_total;
		/*le no de type de la barre est le numero de l element*/
		barre[Structure.nb_barre].type = el;
		barre[Structure.nb_barre].netting2ropes_panel = 0;
			
		/* ss vaut 0.0 si sens_cote vaut 1, 1.0 si sens_cote vaut -1 */
		ss = (float) 0.5 * fabs(sens_cote - 1.);
		element[el].noeud[zi]    = Structure.nb_total;
		printf("elemenw[%d].noeud[%d] = %4d\n",el,zi,element[el].noeud[zi]);
		noeud[Structure.nb_total].x = xdeb + (ss + sens_cote * pan_hexa[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (xfin-xdeb) ;
		noeud[Structure.nb_total].y = ydeb + (ss + sens_cote * pan_hexa[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (yfin-ydeb) ;
		noeud[Structure.nb_total].z = zdeb + (ss + sens_cote * pan_hexa[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (zfin-zdeb) ;
		
		if ( sens_cote == 1 )
			{ /* On parcourt le cote du panneau dans le sens maillé donc */
		 	 barre[Structure.nb_barre].pro[2] = pan_hexa[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)];
		 	 if ( zi == 1 ) { barre[Structure.nb_barre].pro[1] = 0.0 				    ; }		/* Pour la 1ère barre, on a 0.0 */
		 	 else           { barre[Structure.nb_barre].pro[1] = barre[Structure.nb_barre - 1].pro[2] ; }		/* Pour les autres barres, on s'appuie sur la barre precedente */
			}
		else
			{ /* On parcourt le cote de panneau dans le sens inverse maillé donc */
		 	 barre[Structure.nb_barre].pro[2] =  1. - pan_hexa[nopan].prop_cote[premier_loc + sens_cote * (zi - 1) ];
		 	 if ( zi == 1 ) { barre[Structure.nb_barre].pro[1] = 0.0    			    ; }
		 	 else           { barre[Structure.nb_barre].pro[1] = barre[Structure.nb_barre - 1].pro[2] ; }
			}
		
		barre[Structure.nb_barre].longueur_repos = (float)  element[el].lgrepos * fabs(barre[Structure.nb_barre].pro[1]-barre[Structure.nb_barre].pro[2]);
		noeud[Structure.nb_total].type   =  element[el].type_noeud ;
		
		nb_lai = appartient_liaison( premier_cote + sens_cote * (zi - 1) ) ;
		
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
			Lien[Structure.nb_lien].type[1] = 'h';
			Lien[Structure.nb_lien].type[2] = 'e';
			Lien[Structure.nb_lien].structure[1] = nopan;
			Lien[Structure.nb_lien].structure[2] = el ;
			Lien[Structure.nb_lien].extremite[1] = premier_loc + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].extremite[2] = zi;
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
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'e';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = el;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = zi;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		}
	Structure.nb_barre++;
	if ( Structure.nb_barre>= NBMAXBARRE)
		{
		printf(" NBMAXBARRE trop petit %4d < %4d \n",NBMAXBARRE,Structure.nb_barre );
		exit(0);
		}
	if (zi == 1)  barre[Structure.nb_barre].noeud[1] = deb ;
	else          barre[Structure.nb_barre].noeud[1] = Structure.nb_total;
	barre[Structure.nb_barre].noeud[2] = fin;
	if (zi == 1)  barre[Structure.nb_barre].noeud[1] = deb ;
	if (nb_coupe == 1 ) { barre[Structure.nb_barre].pro[1] = 0.0 ;}					/* Pour le cas d'une seule barre */
	else 		    { barre[Structure.nb_barre].pro[1] = barre[Structure.nb_barre - 1].pro[2] ;}	/* pour les autres, on s'appuie sur la barre précédente*/
	barre[Structure.nb_barre].pro[2] = 1.0;
	barre[Structure.nb_barre].longueur_repos = (float)  element[el].lgrepos * fabs(barre[Structure.nb_barre].pro[1]-barre[Structure.nb_barre].pro[2]);
	barre[Structure.nb_barre].type = el;
	barre[Structure.nb_barre].netting2ropes_panel = 0;
	
	//printf(" el= %4d ",el);
	//printf(" Structure.nb_barre= %4d ",Structure.nb_barre);
	//printf(" Structure.nb_total= %4d \n",Structure.nb_total);
	
	/*type de barre*/
	/*if ( el >= NBMAXPANHEXA)
		{
		printf(" NBMAXPANHEXA trop petit %4d < %4d \n",NBMAXPANHEXA,el );
		exit(0);
		}
	TypeBarre[el].raideur_traction = element[el].raideur_traction;
	TypeBarre[el].raideur_compression = element[el].raideur_compression;
	TypeBarre[el].longueur_repos = element[el].lgrepos / nb_coupe;
	TypeBarre[el].diam_hydro = element[el].diametrehydro;
	TypeBarre[el].rho = element[el].rhoelement;
	TypeBarre[el].cdnormal = element[el].cdnormal;
	TypeBarre[el].ftangent = element[el].ftangent;*/
	}

void mise_a_jour_type_noeud(int cible, int source)
	{
	if ( cible >= NBMAXTYPENOEUD)
		{
		printf(" NBMAXTYPENOEUD trop petit %4d < %4d \n",NBMAXTYPENOEUD,cible );
		exit(0);
		}
	TypeNoeud[cible].mx = TypeNoeud[source].mx;
	TypeNoeud[cible].my = TypeNoeud[source].my;
	TypeNoeud[cible].mz = TypeNoeud[source].mz;
	TypeNoeud[cible].majx = TypeNoeud[source].majx;
	TypeNoeud[cible].majy = TypeNoeud[source].majy;
	TypeNoeud[cible].majz = TypeNoeud[source].majz;
	TypeNoeud[cible].lonx = TypeNoeud[source].lonx;
	TypeNoeud[cible].lony = TypeNoeud[source].lony;
	TypeNoeud[cible].lonz = TypeNoeud[source].lonz;
	TypeNoeud[cible].cdx = TypeNoeud[source].cdx;
	TypeNoeud[cible].cdy = TypeNoeud[source].cdy;
	TypeNoeud[cible].cdz = TypeNoeud[source].cdz;
	TypeNoeud[cible].fextx = TypeNoeud[source].fextx;
	TypeNoeud[cible].fexty = TypeNoeud[source].fexty;
	TypeNoeud[cible].fextz = TypeNoeud[source].fextz;
	TypeNoeud[cible].fixx = TypeNoeud[source].fixx;
	TypeNoeud[cible].fixy = TypeNoeud[source].fixy;
	TypeNoeud[cible].fixz = TypeNoeud[source].fixz;
	TypeNoeud[cible].limx = TypeNoeud[source].limx;
	TypeNoeud[cible].limy = TypeNoeud[source].limy;
	TypeNoeud[cible].limz = TypeNoeud[source].limz;
	TypeNoeud[cible].senx = TypeNoeud[source].senx;
	TypeNoeud[cible].seny = TypeNoeud[source].seny;
	TypeNoeud[cible].senz = TypeNoeud[source].senz;
	TypeNoeud[cible].symx = TypeNoeud[source].symx;
	TypeNoeud[cible].symy = TypeNoeud[source].symy;
	TypeNoeud[cible].symz = TypeNoeud[source].symz;
	}
