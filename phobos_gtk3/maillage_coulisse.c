#define PRINCIPAL 0
#include "phobos.h"

void maillage_coulisse()
	{
	int   li,no,co,cq,cp,nloc1,nloc2,nopan,maille,nolienpa,mode1,mode2;
	char  pan;
	
	
	/*faire le maillage panneau et des elements si ce n est pas fait
	le maillage ce fait alors avec maillage_panneau1 par defaut*/
	mode1 = GetMenuItemChecked(w[26]);	/*flag = 1 si maillage_panneau1 fait*/
	mode2 = GetMenuItemChecked(w[31]);	/*flag = 1 si maillage_panneau2 fait*/
	/*if ((mode1 == 0) && (mode2 == 0)) maillage_panneau2();*/
	
	for (co=1;co<=Structure.nombreCoulisses;co++)
		{
		if(coulisse[co].flag_maillage == 0)
			{
			if (coulisse[co].nb_noeud < 0)
				{
				printf("ERREUR \n");
				printf("le nb de noeud doit etre >= 0 = %12d \n",coulisse[co].nb_noeud);
				printf("Coulisse = %12d \n",co);
				exit(0);
				}
			cq = 1;
			cp = 2;
			/*
			recherche si la coulisse est liee a une structure deja maille
			sinon maille = 0
			si oui maille = 1 a 8
			cq est lextremite 1 de la coulisse co
			pan est le type de structure deja maillee : e pour element, h pour panneau hexa ...
			nopan est le numero de la structure
			nloc1 est le noeud lie a cq et nloc2 est lie a l extremite 2 de la coulisse co
			*/
			maille = liaison_maille_co(cq,co,&pan,&nopan,&nloc1,&nloc2);
			
			/*
			printf("maille = %d \n",maille);
			printf("cq = %d \n",cq);
			printf("co = %d \n",co);
			printf("pan = %c \n",pan);
			printf("nopan = %d \n",nopan);
			printf("nloc1 = %d \n",nloc1);
			printf("nloc2 = %d \n",nloc2);
			*/
			

			if (maille == 0)
				{
				maillage_coulisse_libre(co);
				}
			if ((maille == 1) || (maille == 2))
				{
				maillage_coulisse_panneau(co,nopan,nloc1,nloc2);
				}
			if ((maille == 3) || (maille == 4))
				{
				maillage_coulisse_coulisse(co,nopan,nloc1);
				}
			if ((maille == 5) || (maille == 6))
				{
				maillage_coulisse_element(co,nopan,nloc1);
				}
			if ((maille == 7) || (maille == 8))
				{
				maillage_coulisse_pan_hexa(co,nopan,nloc1,nloc2);
				}
			coulisse[co].flag_maillage = 1;
			}
		}
	printf("Structure.nb_total = %4d \n",Structure.nb_total);
	
	SetMenuItemChecked(w[71],1);
	}

int liaison_maille_co(int neud,int couliss,char *structur,int *nostructur,int *debutsegm,int *finsegm)
	{
	/*
	neud       	= debut du segment traite,
	couliss     	= coulisse traitee,
	renvoie de 1 a 8 si le noeud est lie par un lien a une structure deja maillee, sinon 0
	structur   	= type de la structure maillee
	nostructur 	= numero de cette structure
	debutsegm  	= numero dans la numerotation locale de la premiere extremite du segment maillee
	finsegm    	= numero dans la numerotation locale de la derniere extremite du segment maillee
	*/
	
	int noeue,noliennoeud,noliennoeue,pa,co,li,noliendeb,nolienfin;
	int el,cq,cp,deb,fin;
	
	/*neud = debut du cote, noeue : fin du cote dans la numerotation locale*/
	if (neud == 1) noeue = 2;
	if (neud == 2) noeue = 1;
	
	deb = coulisse[couliss].extremite[neud];
	fin = coulisse[couliss].extremite[noeue];
	noliennoeud = appartient_liaison(deb);
	noliennoeue = appartient_liaison(fin);
      
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{
		if (panneau[pa].flag_maillage == 1)
			{
			for (cq=1;cq<=panneau[pa].nb_noeud_contour;cq++)
				{
				/*cq = debut du cote, cp : fin du cote dans la numeroattion locale*/
				if (cq != panneau[pa].nb_noeud_contour) cp = cq+1;
				if (cq == panneau[pa].nb_noeud_contour) cp = 1;
				/*deb = debut du cote, fin : fin du cote dans la numerotation globale*/
				deb = panneau[pa].noeud_contour[cq];
				fin = panneau[pa].noeud_contour[cp];
				noliendeb = appartient_liaison(deb);
				nolienfin = appartient_liaison(fin);
				if((noliendeb != 0) && (noliendeb == noliennoeud) && (nolienfin == noliennoeue))
					{
					*structur = 'p';
					*nostructur = pa;
					*debutsegm = cq;
					*finsegm = cp;
					return 1;
					}
				if((noliendeb != 0) && (noliendeb == noliennoeue) && (nolienfin == noliennoeud))
					{
					*structur = 'p';
					*nostructur = pa;
					*debutsegm = cp;
					*finsegm = cq;
					return 2;
					}
				}
			}
		}
	
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{
		if (pan_hexa[pa].flag_maillage == 1)
			{
			for (cq=1;cq<=pan_hexa[pa].nb_noeud_contour;cq++)
				{
				/*cq = debut du cote, cp : fin du cote dans la numeroattion locale*/
				if (cq != pan_hexa[pa].nb_noeud_contour) cp = cq+1;
				if (cq == pan_hexa[pa].nb_noeud_contour) cp = 1;
				/*deb = debut du cote, fin : fin du cote dans la numerotation globale*/
				deb = pan_hexa[pa].noeud_contour[cq];
				fin = pan_hexa[pa].noeud_contour[cp];
				noliendeb = appartient_liaison(deb);
				nolienfin = appartient_liaison(fin);
				if((noliendeb != 0) && (noliendeb == noliennoeud) && (nolienfin == noliennoeue))
					{
					*structur = 'h';
					*nostructur = pa;
					*debutsegm = cq;
					*finsegm = cp;
					return 7;
					}
				if((noliendeb != 0) && (noliendeb == noliennoeue) && (nolienfin == noliennoeud))
					{
					*structur = 'h';
					*nostructur = pa;
					*debutsegm = cp;
					*finsegm = cq;
					return 8;
					}
				}
			}
		}

	for (co=1;co<=Structure.nombreCoulisses;co++)
		{
		if ((co != couliss) && (coulisse[co].flag_maillage == 1))
			{
			deb = coulisse[co].extremite[1];
			fin = coulisse[co].extremite[2];
			noliendeb = appartient_liaison(deb);
			nolienfin = appartient_liaison(fin);
			if((noliendeb != 0) && (noliendeb == noliennoeud) && (nolienfin == noliennoeue))
				{
				*structur = 'c';
				*nostructur = co;
				*debutsegm = 1;
				*finsegm = 2;
				return 3;
				}
			if((noliendeb != 0) && (noliendeb == noliennoeue) && (nolienfin == noliennoeud))
				{
				*structur = 'c';
				*nostructur = co;
				*debutsegm = 2;
				*finsegm = 1;
				return 4;
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
			
			if((noliendeb != 0) && (noliendeb == noliennoeud) && (nolienfin == noliennoeue))
				{
				*structur = 'e';
				*nostructur = el;
				*debutsegm = 1;
				*finsegm = 2;
				return 5;
				}
			if((noliendeb != 0) && (noliendeb == noliennoeue) && (nolienfin == noliennoeud))
				{
				*structur = 'e';
				*nostructur = el;
				*debutsegm = 2;
				*finsegm = 1;
				return 6;
				}
			}
		}
	*structur = ' ';
	*nostructur = 0;
	*debutsegm = 0;
	*finsegm = 0;
	return 0;
	}


void maillage_coulisse_libre(int co)
	{
	/*maillage de la coulisse co connaissant le nombre de noeud totaux = coulisse[co].nb_noeud*/
	
	int    zi, nb_coupe, deb, fin ;
	float  xdeb, xfin, ydeb, yfin, zdeb, zfin ;
	
	deb = coulisse[co].extremite[1];
	fin = coulisse[co].extremite[2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	if (coulisse[co].nb_noeud < 0)
		{
		printf("coulisse[%4d].nb_noeud trop petit = %4d < 2 \n",co,coulisse[co].nb_noeud );
		exit(0);
		}
	/**********************************************/
  	coulisse[co].noeud = (int *) malloc((1 + coulisse[co].nb_noeud) * sizeof(int));
	if (coulisse[co].noeud    == NULL)
		{
		printf("coulisse[co].noeud  1 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	for (zi=1;zi<=coulisse[co].nb_noeud ;zi++)
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		/*creation des noeuds de la coulisse*/
		coulisse[co].noeud[zi] = Structure.nb_total;
		/*Creation du noeud*/
		noeud[Structure.nb_total].x = xdeb + zi * (xfin-xdeb) / (coulisse[co].nb_noeud+1);
		noeud[Structure.nb_total].y = ydeb + zi * (yfin-ydeb) / (coulisse[co].nb_noeud+1);
		noeud[Structure.nb_total].z = zdeb + zi * (zfin-zdeb) / (coulisse[co].nb_noeud+1);
		noeud[Structure.nb_total].type = coulisse[co].type_noeud;
		}
	}


void maillage_coulisse_coulisse(int co,int co2,int nlo1)
	{
	/*
	maillage de la coulisse co liee a la coulisse co2 qui est deja maillee
	si nlo1 est = 1 les extremites 1 des 2 coulisses sont lie, de meme pour les extremite 2
	si nlo1 est = 2 l extremite 1 d une coulisse est lie a l extremite 2 de l autre coulisse
	*/
	
	int    zi,nb_coupe,deb,fin,premier_loc,premier_cote,sens_cote,nb_lai;
	float  xdeb,xfin,ydeb,yfin,zdeb,zfin;
	
	nb_coupe = coulisse[co2].nb_noeud + 1;
	coulisse[co].nb_noeud = nb_coupe - 1; 		/*Changement du nombre de noeud sur la coulisse co*/
	
	/**********************************************/
  	coulisse[co].noeud = (int *) realloc(coulisse[co].noeud, (1+ coulisse[co].nb_noeud) * sizeof(int));
	if (coulisse[co].noeud    == NULL)
		{
		printf(" coulisse[co].noeud 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	deb = coulisse[co].extremite[1];
	fin = coulisse[co].extremite[2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;

	if(nlo1 == 1)
		{
		premier_loc = 1;
		premier_cote = coulisse[co2].noeud[premier_loc];
		sens_cote = +1;
		}
	if(nlo1 == 2)
		{
		premier_loc = nb_coupe + 1;
		premier_cote = coulisse[co2].noeud[premier_loc];
		sens_cote = -1;
		}

	for (zi=1;zi<=nb_coupe - 1 ;zi++)
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		
		coulisse[co].noeud[zi] = Structure.nb_total;
		noeud[Structure.nb_total].x      = xdeb + zi * (xfin-xdeb) / nb_coupe;
		noeud[Structure.nb_total].y      = ydeb + zi * (yfin-ydeb) / nb_coupe;
		noeud[Structure.nb_total].z      = zdeb + zi * (zfin-zdeb) / nb_coupe;
		noeud[Structure.nb_total].type   = coulisse[co].type_noeud;
		
		nb_lai = appartient_liaison(premier_cote + sens_cote * (zi - 1));
		
		/*
		printf("premier_cote = %4d sens_cote =  %4d ens =  %4d\n",premier_cote,sens_cote,premier_cote + sens_cote * (zi - 1) );
		printf("coulisse = %4d zi =  %4d nb_lai =  %4d\n",co,zi, nb_lai );
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
			Lien[Structure.nb_lien].type[1] = 'c';
			Lien[Structure.nb_lien].type[2] = 'c';
			Lien[Structure.nb_lien].structure[1] = co2;
			Lien[Structure.nb_lien].structure[2] = co ;
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
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'c';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = co;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = zi;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		}
	printf(" Structure.nb_total= %4d ",Structure.nb_total);
	}
	
void maillage_coulisse_element(int co,int el2,int nlo1)
	{
	/*
	maillage de la coulisse co liee a l element el2 qui est deja maille
	si nlo1 est = 1 les extremites 1 de la coulisse et de l element sont lies, de meme pour les extremite 2
	si nlo1 est = 2 l extremite 1 de la coulisse est lie a l extremite 2 de l element et inversement
	*/
	
	int    zi,nb_coupe,deb,fin,premier_loc,premier_cote,sens_cote,nb_lai,nb_point;
	float  xdeb,xfin,ydeb,yfin,zdeb,zfin,nb_segment,inter;
	
	/*on commence par maille la coulisse*/
	maillage_coulisse_libre(co);
	
	/*on verifie que le nb de barre de l element est > au nb de barre de la coulisse*/
	if(element[el2].nb_barre < coulisse[co].nb_noeud + 1)
		{
		printf(" le nombre de barre de l element %4d est trop faible  \n",el2 );
		printf(" l augmenter au moins jusqu a %4d   \n",coulisse[co].nb_noeud + 1 );
		exit(0);
		}

	/*calcul du nombre de barre de le element correspondant a une barre de la coulisse
	autrement dit tout les nb_segment noeuds de l element sont lies aux noeuds de la coulisse*/
	nb_segment = (float) element[el2].nb_barre / ((float)coulisse[co].nb_noeud + 1.0);
		
	/*premier_cote : debut de l element et sens_cote : sens */
	if(nlo1 == 1)
		{
		premier_loc = 1;
		premier_cote = element[el2].noeud[premier_loc];
		sens_cote = +1;
		}
	if(nlo1 == 2)
		{
		premier_loc = element[el2].nb_barre - 1;
		premier_cote = element[el2].noeud[premier_loc];
		sens_cote = -1;
		}
	/*
	printf("nlo1  %4d   \n",nlo1 );
	printf("premier_loc  %4d   \n", premier_loc);
	printf("premier_cote  %4d   \n", premier_cote);
	printf("sens_cote  %4d   \n", sens_cote);
	*/

	/*relie chaque noeud interieur de la coulisse a un noeud de l element*/
	for (zi=1;zi<= coulisse[co].nb_noeud ;zi++)
		{
		/*noeud de depart du lien*/
		deb = coulisse[co].noeud[zi];
		
		/*inter = (float) (zi * nb_segment);
		printf("(float) (zi * nb_segment)  = %f   ", inter);
		inter = rintf((float) (zi * nb_segment));
		printf("rintf((float) (zi * nb_segment))  = %f   \n", inter);*/
		
		nb_point = (int) rintf((float) (zi * nb_segment));
		
		fin = premier_cote + sens_cote * (nb_point - 1);
		nb_lai = appartient_liaison(fin);
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
			Lien[Structure.nb_lien].type[2] = 'c';
			Lien[Structure.nb_lien].structure[1] = el2;
			Lien[Structure.nb_lien].structure[2] = co ;
			Lien[Structure.nb_lien].extremite[1] = nb_point;	/*numerotation locale a l element*/
			Lien[Structure.nb_lien].extremite[2] = zi;		/*numerotation locale a la coulisse*/
			Lien[Structure.nb_lien].noeud[1] = fin;		/*numerotation totale*/
			Lien[Structure.nb_lien].noeud[2] = deb;		/*numerotation totale*/
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
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'c';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = co;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = zi;		/*numerotation locale a la coulisse*/
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = deb;		/*numerotation totale*/
			}
		}
	printf(" Structure.nb_total= %4d ",Structure.nb_total);
	}
	




void maillage_coulisse_element_old(int co,int el2,int nlo1)
	{
	/*
	maillage de la coulisse co liee a l element el2 qui est deja maille
	si nlo1 est = 1 les extremites 1 de la coulisse et de l element sont lies, de meme pour les extremite 2
	si nlo1 est = 2 l extremite 1 de la coulisse est lie a l extremite 2 de l element et inversement
	*/
	
	int    zi,nb_coupe,deb,fin,premier_loc,premier_cote,sens_cote,nb_lai;
	float  xdeb,xfin,ydeb,yfin,zdeb,zfin;
	
	nb_coupe = element[el2].nb_barre;
	coulisse[co].nb_noeud = nb_coupe - 1; 		/*Changement du nombre de noeud sur la coulisse co*/
	
	/**********************************************/
  	coulisse[co].noeud = (int *) realloc(coulisse[co].noeud, (1+ coulisse[co].nb_noeud) * sizeof(int));
	if (coulisse[co].noeud    == NULL)
		{
		printf(" coulisse[co].noeud 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	deb = coulisse[co].extremite[1];
	fin = coulisse[co].extremite[2];
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
		premier_loc = nb_coupe + 1;
		premier_cote = element[el2].noeud[premier_loc];
		sens_cote = -1;
		}

	for (zi=1;zi<=nb_coupe - 1 ;zi++)
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		
		coulisse[co].noeud[zi] = Structure.nb_total;
		noeud[Structure.nb_total].x      = xdeb + zi * (xfin-xdeb) / nb_coupe;
		noeud[Structure.nb_total].y      = ydeb + zi * (yfin-ydeb) / nb_coupe;
		noeud[Structure.nb_total].z      = zdeb + zi * (zfin-zdeb) / nb_coupe;
		noeud[Structure.nb_total].type   = coulisse[co].type_noeud;
		
		nb_lai = appartient_liaison(premier_cote + sens_cote * (zi - 1));
		
		printf("premier_cote = %4d sens_cote =  %4d ens =  %4d\n",premier_cote,sens_cote,premier_cote + sens_cote * (zi - 1) );
		printf("coulisse = %4d zi =  %4d nb_lai =  %4d\n",co,zi, nb_lai );
		
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
				printf("lien[Structure.nb_lien].noeud  1 = NULL  \n" );
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
			Lien[Structure.nb_lien].type[2] = 'c';
			Lien[Structure.nb_lien].structure[1] = el2;
			Lien[Structure.nb_lien].structure[2] = co ;
			Lien[Structure.nb_lien].extremite[1] = sens_cote * (zi - 1);		/*numerotation locale a l element*/
			Lien[Structure.nb_lien].extremite[2] = zi;					/*numerotation locale a la coulisse*/
			Lien[Structure.nb_lien].noeud[1] = premier_cote + sens_cote * (zi - 1); 	/*numerotation totale*/
			Lien[Structure.nb_lien].noeud[2] = Structure.nb_total; 			/*numerotation totale*/
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
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'c';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = co;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = zi;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		}
	printf(" Structure.nb_total= %4d ",Structure.nb_total);
	}
	
void maillage_coulisse_panneau(int co,int nopan,int nlo1,int nlo2)
	{
	int    zi,nb_coupe,deb,fin,premier_loc,premier_cote,sens_cote,nb_lai,nlo3;
	float  xdeb,xfin,ydeb,yfin,zdeb,zfin,ss;
	
	/* 
	co : numero de la coulisse
	nopan : numero du panneau auquel co est lie
	nlo1 : numero de l extremite du panneau liee a l extremite 1 de co
	nlo2 :     -   -      -       -   -      -   -     -       2  -  -
	Maillage d une coulisse a partir d un panneau deja maille, auquel il est lie par les extremites 
	*/
	
	/* determination du nombre de coupes de la coulisse co a partir du maillage du panneau nopan auquel il est lie */
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
				/*printf("nlo3 = %4d ",nlo3);
				printf("panneau[nopan].suivant_contour[nlo3] = %4d \n",panneau[nopan].suivant_contour[nlo3]);*/
				}
			while ((panneau[nopan].suivant_contour[nlo3] == 0) && (nlo3 != panneau[nopan].nb_noeud_contour));
			if (panneau[nopan].suivant_contour[nlo3] != 0)
				{
				nb_coupe = panneau[nopan].suivant_contour[nlo3] - panneau[nopan].suivant_contour[nlo2] + 1;
				}
			else
				{
				/*modifie le 26/3/98
				nb_coupe = panneau[nopan].nb_noeud_cote - panneau[nopan].suivant_contour[nlo1] + 2;*/
				nb_coupe = panneau[nopan].nb_noeud_cote - panneau[nopan].suivant_contour[nlo2] + 2;
				/*printf("panneau[nopan].nb_noeud_cote = %4d ",panneau[nopan].nb_noeud_cote);
				printf("panneau[nopan].suivant_contour[nlo1] = %4d \n",panneau[nopan].suivant_contour[nlo1]);*/
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
	/*Changement du nombre de noeuds interne sur la coulisse co*/
	coulisse[co].nb_noeud = nb_coupe + 1; 		
	
	/**********************************************/
  	coulisse[co].noeud = (int *) realloc(coulisse[co].noeud, (1+ coulisse[co].nb_noeud) * sizeof(int));
	if (coulisse[co].noeud    == NULL)
		{
		printf(" coulisse[co].noeud 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	deb = coulisse[co].extremite[1];
	fin = coulisse[co].extremite[2];
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
		
	coulisse[co].noeud[1] = deb;
	for ( zi = 1 ; zi <= nb_coupe - 1 ; zi++ )
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
			
		/* ss vaut 0.0 si sens_cote vaut 1, 1.0 si sens_cote vaut -1 */
		ss = (float) 0.5 * fabs(sens_cote - 1.);
		coulisse[co].noeud[zi]    = Structure.nb_total;
		noeud[Structure.nb_total].x = xdeb + (ss + sens_cote * panneau[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (xfin-xdeb) ;
		noeud[Structure.nb_total].y = ydeb + (ss + sens_cote * panneau[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (yfin-ydeb) ;
		noeud[Structure.nb_total].z = zdeb + (ss + sens_cote * panneau[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (zfin-zdeb) ;
		
		noeud[Structure.nb_total].type   =  coulisse[co].type_noeud ;
		
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
			Lien[Structure.nb_lien].type[2] = 'c';
			Lien[Structure.nb_lien].structure[1] = nopan;
			Lien[Structure.nb_lien].structure[2] = co ;
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
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'c';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = co;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = zi;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		}
	coulisse[co].noeud[coulisse[co].nb_noeud] = fin;
	printf(" Structure.nb_total= %4d ",Structure.nb_total);
	}
	
void maillage_coulisse_pan_hexa(int co,int nopan,int nlo1,int nlo2)
	{
	int    zi,nb_coupe,deb,fin,premier_loc,premier_cote,sens_cote,nb_lai,nlo3;
	float  xdeb,xfin,ydeb,yfin,zdeb,zfin,ss;
	
	/* 
	co : numero de la coulisse
	nopan : numero du panneau auquel co est lie
	nlo1 : numero de l extremite du panneau liee a l extremite 1 de co
	nlo2 :     -   -      -       -   -      -   -     -       2  -  -
	Maillage d une coulisse a partir d un panneau a maille hexagonale deja maille, auquel il est lie par les extremites 
	*/
	
	
	/* determination du nombre de coupes de la coulisse co a partir du maillage du panneau nopan auquel il est lie */
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
				/*printf("nlo3 = %4d ",nlo3);
				printf("pan_hexa[nopan].suivant_contour[nlo3] = %4d \n",pan_hexa[nopan].suivant_contour[nlo3]);*/
				}
			while ((pan_hexa[nopan].suivant_contour[nlo3] == 0) && (nlo3 != pan_hexa[nopan].nb_noeud_contour));
			if (pan_hexa[nopan].suivant_contour[nlo3] != 0)
				{
				nb_coupe = pan_hexa[nopan].suivant_contour[nlo3] - pan_hexa[nopan].suivant_contour[nlo2] + 1;
				}
			else
				{
				/*modifie le 26/3/98
				nb_coupe = pan_hexa[nopan].nb_noeud_cote - pan_hexa[nopan].suivant_contour[nlo1] + 2;*/
				nb_coupe = pan_hexa[nopan].nb_noeud_cote - pan_hexa[nopan].suivant_contour[nlo2] + 2;
				/*printf("pan_hexa[nopan].nb_noeud_cote = %4d ",pan_hexa[nopan].nb_noeud_cote);
				printf("pan_hexa[nopan].suivant_contour[nlo1] = %4d \n",pan_hexa[nopan].suivant_contour[nlo1]);*/
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
	/*Changement du nombre de noeuds interne sur la coulisse co*/
	coulisse[co].nb_noeud = nb_coupe + 1; 		
	
	/**********************************************/
  	coulisse[co].noeud = (int *) realloc(coulisse[co].noeud, (1+ coulisse[co].nb_noeud) * sizeof(int));
	if (coulisse[co].noeud    == NULL)
		{
		printf(" coulisse[co].noeud 2 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	deb = coulisse[co].extremite[1];
	fin = coulisse[co].extremite[2];
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
		
	coulisse[co].noeud[1] = deb;
	for ( zi = 1 ; zi <= nb_coupe - 1 ; zi++ )
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
			
		/* ss vaut 0.0 si sens_cote vaut 1, 1.0 si sens_cote vaut -1 */
		ss = (float) 0.5 * fabs(sens_cote - 1.);
		coulisse[co].noeud[zi]    = Structure.nb_total;
		noeud[Structure.nb_total].x = xdeb + (ss + sens_cote * pan_hexa[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (xfin-xdeb) ;
		noeud[Structure.nb_total].y = ydeb + (ss + sens_cote * pan_hexa[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (yfin-ydeb) ;
		noeud[Structure.nb_total].z = zdeb + (ss + sens_cote * pan_hexa[nopan].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (zfin-zdeb) ;
		
		noeud[Structure.nb_total].type   =  coulisse[co].type_noeud ;
		
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
			Lien[Structure.nb_lien].type[2] = 'c';
			Lien[Structure.nb_lien].structure[1] = nopan;
			Lien[Structure.nb_lien].structure[2] = co ;
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
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'c';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = co;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = zi;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		}
	coulisse[co].noeud[coulisse[co].nb_noeud] = fin;
	printf(" Structure.nb_total= %4d ",Structure.nb_total);
	}
	
