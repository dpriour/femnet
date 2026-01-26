#define PRINCIPAL 0
#include "4c19.h"

/* Lecture du fichier .mdh */

int lectureDo4(char *nomfichier)
	{
	int n,zi;
  	char 	*pr,*buffer;
  	char 	t1[256],tonom[200];
	char 	chaine[] = "                                               ";
  	int 	tmp,i,j,k,n_ligne,p_colonne,tmp_winch,tmp_i1,tmp_i2,tmp_i3,tmp_i4,tmp_i5,itmp;
  	int	trouve,cable,bar_mini,no_bar,inter,panel;
	double	tmp_d1,tmp_d2,mini,pro1,pro2;
  	FILE 	*f1;

  	strcpy(tonom,nomfichier);
        j=strlen(tonom);
        while ((tonom[j])!='.' && j>0) j--;
        if (tonom[j]=='.') tonom[j]=0;

  	strcat(tonom,".mdg");

  	printf(" \n");
  	printf("%s %s \n","file ",tonom);

  	f1 = fopen(tonom,"r");
  	if (f1 == NULL) 
  		{
    		printf(" \n");
    		printf("%s %s %s \n","file ",tonom," don't exist ?");
    		exit(0);
  		} 
	Structure.version = 1;
	lecture_chaine(f1,chaine);		
	i = strlen(chaine);
	//printf("chain: %s  ",chaine);
	//printf("longueur chaine = %d\n",i);/**/
	
	if (strcmp(chaine,"version_2") == 0)
		{
		Structure.version = 2;
		}
  	
  	
  	
  	buffer = fgets(t1,256,f1);  /* t1 contient la premiere ligne du fichier .mdh*/
  	buffer = fgets(t1,256,f1);  /* t1 contient la seconde ligne du fichier .mdh*/
  	buffer = fgets(t1,256,f1);  /* t1 contient la troisieme ligne du fichier .mdh*/
  	buffer = fgets(t1,256,f1);  /* t1 contient la quatrieme ligne du fichier .mdh*/


  	/* noeuds ***********************************************************/
  	itmp = fscanf(f1,"%d\n",&NOMBRE_NOEUDS); 
  	if (3*NOMBRE_NOEUDS > DIM1)
  		{
    		printf("%s %d \n","Attention : DIM1 dans filwin.h est trop petit, l augmenter jusqu a",3*NOMBRE_NOEUDS+1);
    		exit(0);
  		}

  	i = NOMBRE_NOEUDS;
  	printf("%s %d %s \n","reading ",i," nodes");

       	n_ligne = 1+3*NOMBRE_NOEUDS;
       	p_colonne = 2*DIM3;
       	
       	xze_modif = (double *) malloc (n_ligne * p_colonne * sizeof(double));
       	if (xze_modif	== NULL){printf("xze_modif	= NULL \n" );exit(0);}
	ze_modif = (double **) malloc (n_ligne * sizeof(double *));
	if (ze_modif	== NULL){printf("ze_modif	= NULL \n" );exit(0);}
  	cze_modif = xze_modif;
  	for (i=0;i<n_ligne;i++)
  		{
  		ze_modif[i] = cze_modif;
  		cze_modif += p_colonne;
		}
  	for (i=0;i<n_ligne;i++)
  		{
  		for (j=0;j<p_colonne;j++)
  			{
  			ze_modif[i][j] = 0.0;
  			}
  		}
	
       	xze_contact = (double *) malloc (n_ligne * p_colonne * sizeof(double));
       	if (xze_contact	== NULL){printf("xze_contact	= NULL \n" );exit(0);}
	ze_contact = (double **) malloc (n_ligne * sizeof(double *));
	if (ze_contact	== NULL){printf("ze_contact	= NULL \n" );exit(0);}
  	cze_contact = xze_contact;
  	for (i=0;i<n_ligne;i++)
  		{
  		ze_contact[i] = cze_contact;
  		cze_contact += p_colonne;
		}
  	for (i=0;i<n_ligne;i++)
  		{
  		for (j=0;j<p_colonne;j++)
  			{
  			ze_contact[i][j] = 0.0;
  			}
  		}

	if (Structure.type_solver == 1)
	{
	       	xze = (double *) malloc (n_ligne * p_colonne * sizeof(double));
       		if (xze	== NULL){printf("xze	= NULL \n" );exit(0);}
		ze = (double **) malloc (n_ligne * sizeof(double *));
		if (ze	== NULL){printf("ze	= NULL \n" );exit(0);}
  		cze = xze;
  		for (i=0;i<n_ligne;i++)
  		{
  			ze[i] = cze;
  			cze += p_colonne;
		}
  		for (i=0;i<n_ligne;i++)
  		{
  			for (j=0;j<p_colonne;j++)
  			{
  				ze[i][j] = 0.0;
  			}
  		}
	}
	else if (Structure.type_solver == 2)
	{
		n = 3*NOMBRE_NOEUDS;
		ia = (int*) malloc((n+1)*sizeof(int));
		if (ia	== NULL){printf("ia	= NULL \n" );exit(0);}

/*	       	a = (double *) malloc (9*NOMBRE_NOEUDS*NOMBRE_NOEUDS * sizeof(double));
       		if (a	== NULL){printf("a	= NULL \n" );exit(0);}

	       	ka = (int *) malloc (9*NOMBRE_NOEUDS*NOMBRE_NOEUDS * sizeof(int));
       		if (ka	== NULL){printf("ka	= NULL \n" );exit(0);}

	       	ja = (int *) malloc (9*NOMBRE_NOEUDS*NOMBRE_NOEUDS * sizeof(int));
       		if (ja	== NULL){printf("ja	= NULL \n" );exit(0);}*/

		A = (double *) malloc (9*NOMBRE_NOEUDS*NOMBRE_NOEUDS * sizeof(double));
		if (A	== NULL){printf("A = NULL \n" );exit(0);}

		P = (int *) malloc (9*NOMBRE_NOEUDS*NOMBRE_NOEUDS * sizeof(int));
		if (P	== NULL){printf("P = NULL \n" );exit(0);}

		for (i=0; i<9*NOMBRE_NOEUDS*NOMBRE_NOEUDS ; i++)
		{
/*			a[i] = 0.0;
			ka[i] = 0;
			ja[i] = 0;*/
			P[i] = -1;
			A[i] = 0.0;
		}
		for (i=0; i<n; i++){ia[i] = 0;}
		Nnonnul = 0;
	}

  	buffer = fgets(t1,256,f1); 
  	for (i=1;i<=NOMBRE_NOEUDS;i++)
  		{
		itmp = fscanf(f1,"%d %lf %lf %lf %d %d ",&tmp,&Noeud[i].x,&Noeud[i].y,&Noeud[i].z,&Noeud[i].new_numero,&Noeud[i].type);
    		buffer = fgets(t1,256,f1); 
    		/*printf("%d %lf %lf %lf \n",i,Noeud[i].x,Noeud[i].y,Noeud[i].z);*/
  		}
  	/*Noeud[i].x, Noeud[i].y,Noeud[i].z sont les coordonnees cartesiennes des noeuds */
  	/* Noeud[i].type est le numero de reference du noeud i. */


	for (i=1;i<=NOMBRE_NOEUDS;i++)
	  	{
		Noeud[i].mx   = TypeNoeud[Noeud[i].type].mx;   /* Masse du noeud i */
		Noeud[i].my   = TypeNoeud[Noeud[i].type].my;
		Noeud[i].mz   = TypeNoeud[Noeud[i].type].mz;
		Noeud[i].majx = TypeNoeud[Noeud[i].type].majx; /* Masse ajoutee du noeud i : n'intervient qu'en dynamique*/
		Noeud[i].majy = TypeNoeud[Noeud[i].type].majy;
		Noeud[i].majz = TypeNoeud[Noeud[i].type].majz;
		Noeud[i].lonx   = TypeNoeud[Noeud[i].type].lonx;   /* Longueur selon x du noeud i */
		Noeud[i].lony   = TypeNoeud[Noeud[i].type].lony;
		Noeud[i].lonz   = TypeNoeud[Noeud[i].type].lonz;
		Noeud[i].cdx  = TypeNoeud[Noeud[i].type].cdx;  /* Coefficient de trainee selon x du noeud i */
		Noeud[i].cdy  = TypeNoeud[Noeud[i].type].cdy;
		Noeud[i].cdz  = TypeNoeud[Noeud[i].type].cdz;
		Noeud[i].fextx   = TypeNoeud[Noeud[i].type].fextx;   /* Effort exterieur selon x du noeud i */
		Noeud[i].fexty   = TypeNoeud[Noeud[i].type].fexty;
		Noeud[i].fextz   = TypeNoeud[Noeud[i].type].fextz;		
		Noeud[i].fixx = TypeNoeud[Noeud[i].type].fixx; /* Deplacement selon x du noeud i : Fixe ou Libre */
		Noeud[i].fixy = TypeNoeud[Noeud[i].type].fixy;
		Noeud[i].fixz = TypeNoeud[Noeud[i].type].fixz;
		Noeud[i].limx = TypeNoeud[Noeud[i].type].limx; /* Limite du deplacement selon x du noeud i  */
		Noeud[i].limy = TypeNoeud[Noeud[i].type].limy;
		Noeud[i].limz = TypeNoeud[Noeud[i].type].limz;
		Noeud[i].senx  = TypeNoeud[Noeud[i].type].senx;  /*Sens de la Limite du deplacement selon x du noeud i */
		Noeud[i].seny  = TypeNoeud[Noeud[i].type].seny;
		Noeud[i].senz  = TypeNoeud[Noeud[i].type].senz;
		Noeud[i].symx = TypeNoeud[Noeud[i].type].symx; /* =1 si Le noeud i appartient au plan de symetrie YOZ, 0 sinon*/
		Noeud[i].symy = TypeNoeud[Noeud[i].type].symy; /* =1 si Le noeud i appartient au plan de symetrie XOZ, 0 sinon*/
		Noeud[i].symz = TypeNoeud[Noeud[i].type].symz; /* =1 si Le noeud i appartient au plan de symetrie XOY, 0 sinon*/
	  	}

	for (zi = 1 ; zi<= NOMBRE_NOEUDS ; zi++) 
  		{
  		Noeud[zi].curvature = -1.0;
  		Noeud[zi].curvature_nb = 0;
		Noeud[zi].circular_speed = 0;
  		}

	if (Sortie_texte.effort_structure == 1)
		{
		printf("effort_structurf = %d \n",Sortie_texte.effort_structure);
   		Structure.nb_fixed_components = 0;
   		Structure.list_fixed_node = (int *) Malloc_int(1);
   		Structure.list_fixed_axe = (int *) Malloc_int(1);
   		Structure.effort_fixed_components = (double *) Malloc_double(1);
		//numbering
		for ( zi = 1 ; zi <= NOMBRE_NOEUDS ; zi++ )
			{ 
			if ( Noeud[zi].fixx == 1)	Structure.nb_fixed_components++;	/*effort selon X */
			if ( Noeud[zi].fixy == 1)	Structure.nb_fixed_components++;	/*effort selon Y */
			if ( Noeud[zi].fixz == 1)	Structure.nb_fixed_components++;	/*effort selon Z */
			}
		printf("Structure.nb_fixed_components = %d \n",Structure.nb_fixed_components);
   		Structure.list_fixed_node = (int *) Malloc_int(1+Structure.nb_fixed_components);
   		Structure.list_fixed_axe = (int *) Malloc_int(1+Structure.nb_fixed_components);
   		Structure.effort_fixed_components = (double *) Malloc_double(1+Structure.nb_fixed_components);
   		Structure.nb_fixed_components = 0;
		//affectation
   		Structure.nb_fixed_components = 0;
		for ( zi = 1 ; zi <= NOMBRE_NOEUDS ; zi++ )
			{ 
			/*effort selon X */
			if ( Noeud[zi].fixx == 1)
				{
				Structure.nb_fixed_components++;
				Structure.list_fixed_node[Structure.nb_fixed_components] = zi;
				Structure.list_fixed_axe[Structure.nb_fixed_components] = 1;
				}
			/*effort selon Y */
			if ( Noeud[zi].fixy   == 1)
				{
				Structure.nb_fixed_components++;
				Structure.list_fixed_node[Structure.nb_fixed_components] = zi;
				Structure.list_fixed_axe[Structure.nb_fixed_components] = 2;
				}
			/*effort selon Z */
			if ( Noeud[zi].fixz   == 1)
				{
				Structure.nb_fixed_components++;
				Structure.list_fixed_node[Structure.nb_fixed_components] = zi;
				Structure.list_fixed_axe[Structure.nb_fixed_components] = 3;
				}
			}
		}








  	/* éléments ***********************************************************/
	for (i=1;i<=Structure.NbTypeelem;i++)
		{
		TypeElement[i].nb_barre = 0; /*default value, will be actualized later*/
		TypeElement[i].noeud =		(int *) Malloc_int(2 + TypeElement[i].nb_barre);
		TypeElement[i].barre =		(int *) Malloc_int(1 + TypeElement[i].nb_barre);
		TypeElement[i].netting2ropes_panel = 0;		
		}
  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	itmp = fscanf(f1,"%d",&NOMBRE_ELEMENTS);
  	if (NOMBRE_ELEMENTS > DIM2)
  		{
    		printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",NOMBRE_ELEMENTS+1);
    		exit(0);
  		}
	
  	i = NOMBRE_ELEMENTS;
  	printf("%s %d %s \n","reading ",i," bars");

  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	/* Element[i].extremite[1] et Element[i].extremite[2] sont les numeros du noeud i, extremites des bouts. */
  	/* Element[i].type est le numero de type( ie de reference) du noeud i. */
  	/* Element[i].pro[1] et Element[i].pro[2] sont les positions des extremites de l element par rapport aux extremites du bout qui le contient*/
  	for (i=1;i<=NOMBRE_ELEMENTS;i++)
  		{ 
    		/*itmp = fscanf(f1,"%d %d %d %lf %lf %d %lf",&tmp,&Element[i].extremite[1],&Element[i].extremite[2],&Element[i].pro[1],&Element[i].pro[2],&Element[i].type,&Element[i].lgrepos);*/
    		itmp = fscanf(f1,"%d %d %d %lf %lf %d",&tmp,&Element[i].extremite[1],&Element[i].extremite[2],&Element[i].pro[1],&Element[i].pro[2],&Element[i].type);
    		buffer = fgets(t1,256,f1); 
    		/*do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');*/
		/*printf("Element[%d].lgrepos = %lf \n",i,Element[i].lgrepos);*/
		printf("bar i  %d extremities %d %d pro %lf %lf type %d\n",i,Element[i].extremite[1],Element[i].extremite[2],Element[i].pro[1],Element[i].pro[2],Element[i].type);
		Element[i].netting2ropes_panel = 0;	//default value: this bar element belongs to a cable not a panel
		if (Element[i].type < 0)
			{
			panel = abs(Element[i].type);
			Element[i].netting2ropes_panel = panel;	//this bar element belongs to panel
			Structure.NbTypeelem = Structure.NbTypeelem + 1;
			cable = Structure.NbTypeelem;
			printf("Structure.NbTypeelem %d \n",Structure.NbTypeelem);
			TypeElement[cable].netting2ropes_panel = panel;
			TypeElement[cable].nb_barre = 1;
			TypeElement[cable].noeud = (int *) Malloc_int(1 + TypeElement[cable].nb_barre);
			TypeElement[cable].barre = (int *) Malloc_int(1 + TypeElement[cable].nb_barre);
			TypeElement[cable].barre[TypeElement[cable].nb_barre] = i;
			TypeElement[cable].noeud[1] = Element[i].extremite[1];
			TypeElement[cable].noeud[2] = Element[i].extremite[2];
			}
		else
			{
			cable = Element[i].type;
			TypeElement[cable].nb_barre = TypeElement[cable].nb_barre + 1;
			TypeElement[cable].noeud = Realloc_int   (TypeElement[cable].noeud,2 + TypeElement[cable].nb_barre);
			TypeElement[cable].barre = Realloc_int   (TypeElement[cable].barre,1 + TypeElement[cable].nb_barre);
			TypeElement[cable].barre[TypeElement[cable].nb_barre] = i;
			if (TypeElement[cable].nb_barre == 1)
				{
				TypeElement[cable].noeud[1] = Element[i].extremite[1];
				TypeElement[cable].noeud[2] = Element[i].extremite[2];
				}
			else
				{
				trouve = 0;
			  	for (j=1;j<=TypeElement[cable].nb_barre;j++)
			  		{
			  		if (Element[i].extremite[1] == TypeElement[cable].noeud[j]) trouve = 2;
			  		if (Element[i].extremite[2] == TypeElement[cable].noeud[j]) trouve = 1;
			  		}
				TypeElement[cable].noeud[TypeElement[cable].nb_barre+1] = Element[i].extremite[trouve];
				}
			}
 		}

		
 	/*sorting bars of cable begining with extremity 1 of the cable (pro = 0.0)*/
	for (cable=1;cable<=Structure.NbTypeelem;cable++)
		{
		if (TypeElement[cable].netting2ropes_panel != 0)
			{
		  	for (i=1;i<=TypeElement[cable].nb_barre;i++)
		  		{
			 	mini = 1.0;
			 	bar_mini = 0;
			  	for (j=i;j<=TypeElement[cable].nb_barre;j++)
			  		{
			  		no_bar = TypeElement[cable].barre[j];
			  		pro1 = Element[no_bar].pro[1];
			  		pro2 = Element[no_bar].pro[2];
			  		if (pro1 < mini)
			  			{
			  			mini = pro1;
			  			bar_mini = j;
			  			}
			  		if (pro2 < mini)
			  			{
			  			mini = pro2;
			  			bar_mini = j;
			  			}
			  		}
			  	inter = TypeElement[cable].barre[i];
			  	TypeElement[cable].barre[i] = TypeElement[cable].barre[bar_mini];
			  	TypeElement[cable].barre[bar_mini] = inter;
		  		}
		  	}
	 	}
	for (cable=1;cable<=Structure.NbTypeelem;cable++)
		{
		if (TypeElement[cable].netting2ropes_panel != 0)
			{
		  	for (i=1;i<=TypeElement[cable].nb_barre;i++)
		  		{
		  		no_bar = TypeElement[cable].barre[i];
		  		pro1 = Element[no_bar].pro[1];
		  		pro2 = Element[no_bar].pro[2];
		  		if (pro1 < pro2)
		  			{
		  			TypeElement[cable].noeud[i  ] = Element[no_bar].extremite[1];
		  			TypeElement[cable].noeud[i+1] = Element[no_bar].extremite[2];
		  			}
		  		else
		  			{
		  			TypeElement[cable].noeud[i  ] = Element[no_bar].extremite[2];
		  			TypeElement[cable].noeud[i+1] = Element[no_bar].extremite[1];
		  			}
		  		}
		  	}
	  	}

	for (i=1;i<=NOMBRE_ELEMENTS;i++)
	  	{ 
		if (Element[i].netting2ropes_panel == 0)
			{
			Element[i].raideur_traction    = TypeElement[Element[i].type].raideur_traction;
			Element[i].lgrepos             = TypeElement[Element[i].type].lgrepos;/**/
			Element[i].diametremeca        = TypeElement[Element[i].type].diametremeca;
			Element[i].raideur_compression = TypeElement[Element[i].type].raideur_compression;
			Element[i].rhoelement          = TypeElement[Element[i].type].rhoelement;
			Element[i].diametrehydro       = TypeElement[Element[i].type].diametrehydro;
			Element[i].cdnormal            = TypeElement[Element[i].type].cdnormal;
			Element[i].ftangent            = TypeElement[Element[i].type].ftangent;
			Element[i].EI_flexion          = TypeElement[Element[i].type].EI_flexion;
			}
		else
			{
			panel = Element[i].netting2ropes_panel;
			Element[i].raideur_traction    = panneau[panel].raideur_traction * panneau[panel].netting_2_ropes_period;
			Element[i].lgrepos             = panneau[panel].longueur_repos * panneau[panel].netting_2_ropes_period / panneau[panel].netting_2_ropes_bar_nb;
			Element[i].diametremeca        = panneau[panel].diam_hydro * sqrt(panneau[panel].netting_2_ropes_period);
			Element[i].raideur_compression = panneau[panel].raideur_compression * panneau[panel].netting_2_ropes_period;
			Element[i].rhoelement          = panneau[panel].rho;
			Element[i].diametrehydro       = panneau[panel].diam_hydro * sqrt(panneau[panel].netting_2_ropes_period);
			Element[i].cdnormal            = panneau[panel].cdnormal * sqrt(panneau[panel].netting_2_ropes_period);
			Element[i].ftangent            = panneau[panel].ftangent * sqrt(panneau[panel].netting_2_ropes_period);
			Element[i].EI_flexion          = 0.0;
			}
		printf("Element[%d].lgrepos %lf\n",i,Element[i].lgrepos);
	  	}


  	/* coulisses ***********************************************************/
  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	itmp = fscanf(f1,"%d",&NOMBRE_COULISSES);
  	if (NOMBRE_COULISSES > DIM2)
  		{
    		printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",NOMBRE_COULISSES+1);
    		exit(0);
  		}
	
  	i = NOMBRE_COULISSES;
  	printf("%s %d %s \n","reading ",i," coulisses");

  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	/* Coulisse[i].extremite[1] et Coulisse[i].extremite[2] sont les numeros du noeud i, extremites des coulisses. */
  	for (i=1;i<=NOMBRE_COULISSES;i++)
  		{ 
    		itmp = fscanf(f1,"%d %d %d %d ",&tmp,&Coulisse[i].extremite[1],&Coulisse[i].extremite[2],&Coulisse[i].nb_noeud);
       		/**********************************************/
       		/*ici il y a +3 pour avoir suffisament de place pour mettre les extremites pour serie.c*/
       		Coulisse[i].noeud = (int *) malloc((3 + Coulisse[i].nb_noeud) * sizeof(int));
       		if (Coulisse[i].noeud    == NULL)
               		{
               		printf("Coulisse[i].noeud  1 = NULL  \n" );
               		exit(0);
               		}
       		/**********************************************/
		/*ici il ya une longueur de plus que de noeud interieurs plus le zero = +2*/
       		Coulisse[i].longueur = (double *) malloc((2 + Coulisse[i].nb_noeud) * sizeof(double));
       		if (Coulisse[i].longueur    == NULL)
               		{
               		printf("Coulisse[i].longueur  1 = NULL  \n" );
               		exit(0);
               		}
       		/**********************************************/
    		/*buffer = fgets(t1,256,f1); */
  		for (j=1;j<=Coulisse[i].nb_noeud;j++)
  			{ 
    			itmp = fscanf(f1,"%d  ",&Coulisse[i].noeud[j]);
    			}
    		/*buffer = fgets(t1,256,f1); */ 
 		}


  	for (i=1;i<=NOMBRE_COULISSES;i++)
  		{ 
  		printf("coulisse %d   nb noeud %d \n",i,Coulisse[i].nb_noeud);
  		for (j=1;j<=Coulisse[i].nb_noeud;j++)
  			{ 
  			printf(" %d ",Coulisse[i].noeud[j]);
    			}
  		printf(" \n");
 		}


  	/* surfaces ***********************************************************/
  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	itmp = fscanf(f1,"%d",&NOMBRE_SURFACES);
    	//printf("NOMBRE_SURFACES %d \n",NOMBRE_SURFACES);
  	if (NOMBRE_SURFACES > DIM2)
  		{
    		printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",NOMBRE_SURFACES+1);
    		exit(0);
  		}
	
  	i = NOMBRE_SURFACES;
  	printf("%s %d %s \n","reading ",i," diamond netting triangles");

  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	/* Surface[i].extremite[1], Surface[i].extremite[2], Surface[i].extremite[3] sont les trois numeros des noeuds formant le ieme triangle*/
  	/* Surface[i].lon[1], Surface[i].lon[2] sont les coordonnes filaires du 1er sommet du triangle i*/
  	/* Surface[i].lon[3], Surface[i].lon[4] sont les coordonnes filaires du 2nd sommet du triangle i*/
  	/* Surface[i].lon[5], Surface[i].lon[6] sont les coordonnes filaires du 3ieme sommet du triangle i*/
  	/* Surface[i].type est le numero du type du triangle, appele surface, i */
  	for (i=1;i<=NOMBRE_SURFACES;i++)
  		{ 
    		itmp = fscanf(f1,"%d %d %d %d %lf %lf %lf %lf %lf %lf %d",
       		&tmp,&Surface[i].extremite[1],&Surface[i].extremite[2],&Surface[i].extremite[3],
       		&Surface[i].lon[1],&Surface[i].lon[2],&Surface[i].lon[3],&Surface[i].lon[4],&Surface[i].lon[5],&Surface[i].lon[6],&Surface[i].type);
    		do  pr=fgets(t1,256,f1);
    		while (pr == NULL || *pr =='\n');
  		}

	for (i=1;i<=NOMBRE_SURFACES;i++)
	  	{ 
		Surface[i].raideur_traction    = panneau[Surface[i].type].raideur_traction;
		Surface[i].raideur_compression = panneau[Surface[i].type].raideur_compression;
		Surface[i].raideur_ouverture   = panneau[Surface[i].type].raideur_ouverture;
		Surface[i].neutral_angle       = panneau[Surface[i].type].neutral_angle;
		Surface[i].EI_flexion          = panneau[Surface[i].type].EI_flexion;
		Surface[i].lgrepos             = panneau[Surface[i].type].longueur_repos;
		Surface[i].diametremeca        = panneau[Surface[i].type].diametremeca;
		Surface[i].rhosurface          = panneau[Surface[i].type].rho;
		Surface[i].diametrehydro       = panneau[Surface[i].type].diam_hydro;
		Surface[i].largeurnoeud        = panneau[Surface[i].type].largeurnoeud;
		Surface[i].cdnormal            = panneau[Surface[i].type].cdnormal;
		Surface[i].ftangent            = panneau[Surface[i].type].ftangent;
		Surface[i].tarp                = panneau[Surface[i].type].tarp;
	  	}




  	/* surfaces hexagonales*************************************************/
  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	itmp = fscanf(f1,"%d",&NOMBRE_SURF_HEXA);
  	if (NOMBRE_SURF_HEXA > DIM2)
  		{
    		printf("%s %d \n","Attention : DIM2 dans filwin.h est trop petit, l augmenter jusqu a",NOMBRE_SURF_HEXA+1);
    		exit(0);
  		}
	
  	i = NOMBRE_SURF_HEXA;
  	printf("%s %d %s \n","reading ",i," hexagonal triangles netting");

  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	/* Surf_Hexa[i].extremite[1], Surf_Hexa[i].extremite[2], Surf_Hexa[i].extremite[3] sont les trois numeros des noeuds formant le ieme triangle*/
  	/* Surf_Hexa[i].lon[1], Surf_Hexa[i].lon[2] sont les coordonnes filaires du 1er sommet du triangle i*/
  	/* Surf_Hexa[i].lon[3], Surf_Hexa[i].lon[4] sont les coordonnes filaires du 2nd sommet du triangle i*/
  	/* Surf_Hexa[i].lon[5], Surf_Hexa[i].lon[6] sont les coordonnes filaires du 3ieme sommet du triangle i*/
  	/* Surf_Hexa[i].type est le numero du type du triangle, appele surface, i */
  	for (i=1;i<=NOMBRE_SURF_HEXA;i++)
  		{ 
    		itmp = fscanf(f1,"%d %d %d %d %lf %lf %lf %lf %lf %lf %d",
       		&tmp,&Surf_Hexa[i].extremite[1],&Surf_Hexa[i].extremite[2],&Surf_Hexa[i].extremite[3],
       		&Surf_Hexa[i].lon[1],&Surf_Hexa[i].lon[2],&Surf_Hexa[i].lon[3],&Surf_Hexa[i].lon[4],&Surf_Hexa[i].lon[5],&Surf_Hexa[i].lon[6],&Surf_Hexa[i].type);
    		do  pr=fgets(t1,256,f1);
    		while (pr == NULL || *pr =='\n');
  		}
    		
  	/*les fils l m n des mailles hexagonales n ont pas encore ete calcules*/
  	Structure.lmn_calcules = 0;
	 for (i=1;i<=NOMBRE_SURF_HEXA;i++)
	    	{ 
		Surf_Hexa[i].raideur_traction_l    	= TypeSurfHexa[Surf_Hexa[i].type].raideur_traction_l;
		Surf_Hexa[i].raideur_traction_m    	= TypeSurfHexa[Surf_Hexa[i].type].raideur_traction_m;
		Surf_Hexa[i].raideur_traction_n    	= TypeSurfHexa[Surf_Hexa[i].type].raideur_traction_n;
		Surf_Hexa[i].raideur_compression_l 	= TypeSurfHexa[Surf_Hexa[i].type].raideur_compression_l;
		Surf_Hexa[i].raideur_compression_m 	= TypeSurfHexa[Surf_Hexa[i].type].raideur_compression_m;
		Surf_Hexa[i].raideur_compression_n 	= TypeSurfHexa[Surf_Hexa[i].type].raideur_compression_n;
		Surf_Hexa[i].lo_repos            	= TypeSurfHexa[Surf_Hexa[i].type].lo_repos;
		Surf_Hexa[i].mo_repos            	= TypeSurfHexa[Surf_Hexa[i].type].mo_repos;
		Surf_Hexa[i].no_repos            	= TypeSurfHexa[Surf_Hexa[i].type].no_repos;
		Surf_Hexa[i].diametremeca        	= TypeSurfHexa[Surf_Hexa[i].type].diametremeca;
		Surf_Hexa[i].rhosurface          	= TypeSurfHexa[Surf_Hexa[i].type].rhosurface;
		Surf_Hexa[i].diam_hydro_l       	= TypeSurfHexa[Surf_Hexa[i].type].diam_hydro_l;
		Surf_Hexa[i].diam_hydro_m       	= TypeSurfHexa[Surf_Hexa[i].type].diam_hydro_m;
		Surf_Hexa[i].diam_hydro_n       	= TypeSurfHexa[Surf_Hexa[i].type].diam_hydro_n;
		Surf_Hexa[i].cdnormal            	= TypeSurfHexa[Surf_Hexa[i].type].cdnormal;
		Surf_Hexa[i].ftangent            	= TypeSurfHexa[Surf_Hexa[i].type].ftangent;
		Surf_Hexa[i].tarp	            	= TypeSurfHexa[Surf_Hexa[i].type].tarp;
	    	}

if (Structure.version == 1)
	{
	NOMBRE_WINCHS = 0;
	}
if ((Structure.version >= 2) || (Ball.nb >= 1))
	{
  	/* winch ***********************************************************/
  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	itmp = fscanf(f1,"%d",&tmp_winch);
  	printf("%s %d %s \n","reading ",tmp_winch," winch bars");

  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
	NOMBRE_WINCHS = 0;
	tmp_i5 = 0;		/*first winch*/

	for (i=1;i<=tmp_winch;i++)
  		{ 
    		itmp = fscanf(f1,"%d %d %d %lf %lf %d",&tmp_i1,&tmp_i2,&tmp_i3,&tmp_d1,&tmp_d2,&tmp_i4);	buffer = fgets(t1,256,f1); 
		printf("tmp_i1 %3d tmp_i2 %3d tmp_i3 %3d tmp_d1 %7.3lf tmp_d2 %7.3lf tmp_i4 %3d tmp_i5 %3d\n",tmp_i1,tmp_i2,tmp_i3,tmp_d1,tmp_d2,tmp_i4,tmp_i5);
		/*
		*/
		
		if (tmp_i4 != tmp_i5)
			{
			/*new winch*/
			tmp_i5 = tmp_i4;
			Winch[tmp_i4].nb_barre = 1;
			/*Winch[tmp_i4].noeud = (int    *) Malloc_int   (3 + Winch[tmp_i4].nb_barre);*/
			/**********************************************/
			Winch[tmp_i4].noeud= (int *) malloc((3 + Winch[tmp_i4].nb_barre) * sizeof(int));
			if ( Winch[tmp_i4].noeud   == NULL)
				{
				printf("Winch[tmp_i4].noeud  1 = NULL  \n" );
				exit(0);
				}
			/**********************************************/
			Winch[tmp_i4].prop  = (double *) Malloc_double(3 + Winch[tmp_i4].nb_barre);
			Winch[tmp_i4].noeud[Winch[tmp_i4].nb_barre    ] = tmp_i2;
			Winch[tmp_i4].noeud[Winch[tmp_i4].nb_barre + 1] = tmp_i3;
			Winch[tmp_i4].prop [Winch[tmp_i4].nb_barre    ] = tmp_d1;
			Winch[tmp_i4].prop [Winch[tmp_i4].nb_barre + 1] = tmp_d2;
			Winch[tmp_i4].extremite[1] = tmp_i2;
			Winch[tmp_i4].extremite[2] = tmp_i3;
			NOMBRE_WINCHS = NOMBRE_WINCHS + 1;
			}
		else
			{
			Winch[tmp_i4].nb_barre = Winch[tmp_i4].nb_barre + 1;
			Winch[tmp_i4].noeud = Realloc_int   (Winch[tmp_i4].noeud,3 + Winch[tmp_i4].nb_barre);
			Winch[tmp_i4].prop  = Realloc_double(Winch[tmp_i4].prop ,3 + Winch[tmp_i4].nb_barre);
			Winch[tmp_i4].noeud[Winch[tmp_i4].nb_barre    ] = tmp_i2;
			Winch[tmp_i4].noeud[Winch[tmp_i4].nb_barre + 1] = tmp_i3;
			Winch[tmp_i4].prop [Winch[tmp_i4].nb_barre    ] = tmp_d1;
			Winch[tmp_i4].prop [Winch[tmp_i4].nb_barre + 1] = tmp_d2;
			Winch[tmp_i4].extremite[2] = tmp_i3;
			}
		}
	/*for (i=1;i<=NOMBRE_WINCHS;i++)
  		{ 
		printf("i %3d extremities %3d %3d\n",i,Winch[i].extremite[1],Winch[i].extremite[2]);
		for (j=1;j<=Winch[i].nb_barre+1;j++)
  			{
			printf("j %3d noeud %3d prop %lf\n",j,Winch[i].noeud[j],Winch[i].prop[j]);
			}
		}*/
	}
if (Ball.nb >= 1)
	{
  	printf("here we are \n");
  	/* balls ***********************************************************/
  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	itmp = fscanf(f1,"%d",&Ball.nb);
	/*Ball.noeud =		(int *) Malloc_int(1 + Ball.nb);*/
	/**********************************************/
	Ball.noeud= (int *) malloc((1 + Ball.nb) * sizeof(int));
	if (Ball.noeud    == NULL)
		{
		printf("Ball.noeud  1 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	/*Ball.type = 		(int *) Malloc_int(1 + Ball.nb);*/
	/**********************************************/
	Ball.type= (int *) malloc((1 + Ball.nb) * sizeof(int));
	if (Ball.type    == NULL)
		{
		printf("Ball.type  1 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	Ball.birth_time = 	(double *) Malloc_double(1 + Ball.nb);
	Ball.stiffness = 	(double *) Malloc_double(1 + Ball.nb);
	Ball.radius = 		(double *) Malloc_double(1 + Ball.nb);
	Ball.ini_speed_x = 	(double *) Malloc_double(1 + Ball.nb);
	Ball.ini_speed_y = 	(double *) Malloc_double(1 + Ball.nb);
	Ball.ini_speed_z = 	(double *) Malloc_double(1 + Ball.nb);
	
  	i = Ball.nb;
  	printf("%s %d %s \n","reading ",i," balls");

  	do  pr=fgets(t1,256,f1); while (pr == NULL || *pr =='\n');
  	for (i=1;i<=Ball.nb;i++)
  		{ 
    		/*1   89 0.0000000 100.0000000 0.1300000     2 */
    		itmp = fscanf(f1,"%d %d %lf %lf %lf %d %lf %lf %lf",&tmp,&Ball.noeud[i],&Ball.birth_time[i],&Ball.stiffness[i],&Ball.radius[i],&Ball.type[i],&Ball.ini_speed_x[i],&Ball.ini_speed_y[i],&Ball.ini_speed_z[i]);
    		buffer = fgets(t1,256,f1); 
		printf("Ball %d tmp %d noeud %d birth_time %lf stiffness %lf radius %lf type %d speed %lf %lf %lf  ",i,tmp,Ball.noeud[i],Ball.birth_time[i],Ball.stiffness[i],Ball.radius[i],Ball.type[i],Ball.ini_speed_x[i],Ball.ini_speed_y[i],Ball.ini_speed_z[i]);/**/
		printf("position %lf %lf %lf\n",Noeud[Ball.noeud[i]].x,Noeud[Ball.noeud[i]].y,Noeud[Ball.noeud[i]].z);/**/
 		}
 	}

  	fclose(f1);



 	return 0;
	}	

