#define PRINCIPAL 0
#include "phobos.h"


void maillage()
	{
	int i,mode,el, pa,co;
	char tonom[200];
	FILE *f3;
	if (Structure.graphic == 1)
		{
		/*charger le fichier de donnees si ce n est pas fait*/
		mode = GetMenuItemChecked(w[5]);
		if (mode == 0) filet_contour();
		}

	for (el=1;el<=Structure.NbTypeelem;el++)
		{
		element[el].nb_nodes = 0;
		//printf("el %4d nb_nodes %4d\n",el,element[el].nb_nodes);		
		}
	for (i=1;i<=Structure.nb_ordre_objet;i++)
		{ 
 	        if (ordre.type[i] == 'e') maillage_element2(ordre.indice[i]);
	        if (ordre.type[i] == 'p') maillage_panneau(ordre.indice[i]);	
	        if (ordre.type[i] == 'h') maillage_pan_hexa2(ordre.indice[i]);	
		if (ordre.type[i] == 'c') maillage_coulisse2(ordre.indice[i]);
		if (ordre.type[i] == 'w') maillage_winch1(ordre.indice[i]);
		printf("maillage.c fct maillage maillage de %c indice = %12d terminé\n",ordre.type[i],ordre.indice[i]);/**/
		}

		
	for (pa=1;pa<=Structure.NbTypesurf;pa++)	
		{
		//printf("panneau[%d].nb_noeud_contour %4d \n",pa,panneau[pa].nb_noeud_contour );
		for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
			{
			//printf("panneau[%d].noeud_contour[%d]  %4d ",pa,co,panneau[pa].noeud_contour[co]);
			//printf("panneau[%d].suivant_contour[%d]  %4d\n",pa,co,panneau[pa].suivant_contour[co]);
			//printf("panneau[%d].type_suivant_contour[%d]  %4d \n",pa,co,panneau[pa].type_suivant_contour[co]);
			}
		//printf("panneau[%d].nb_noeud_cote %4d \n",pa,panneau[pa].nb_noeud_cote );
		for (co=1;co<=panneau[pa].nb_noeud_cote;co++)
			{
			//printf("panneau[%d].noeud_cote[%d]  %4d ",pa,co,panneau[pa].noeud_cote[co]);
			//printf("panneau[%d].prop_cote[%d]  %f \n",pa,co,panneau[pa].prop_cote[co]);
			}
		}
	//exit(0);


	if (Structure.nb_type_noeud_XYZ_SUPINF > 0)	changement_de_type_noeud();
	
	strcpy(tonom,fname1);
 	strcat(tonom,".des");
	f3 = fopen(tonom,"w");

  	if (f3 == NULL) 
  		{ 
  		printf("creer_fichier_des: impossible d ouvrir le fichier %s\n",tonom);
  	  	exit(0);
  		}


	for (pa=1;pa<=Structure.NbTypesurf;pa++)	fprintf(f3,"pa %3d : %d\n",pa,panneau[pa].flag_dessin);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)	fprintf(f3,"he %3d : 1\n",pa);	fprintf(f3,"\n");
	//for (pa=1;pa<=Structure.NbTypeelem;pa++)	fprintf(f3,"el %3d : 1\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.NbTypeelem;pa++)	fprintf(f3,"el %3d : %d\n",pa,element[pa].flag_dessin);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.nombreCoulisses;pa++)	fprintf(f3,"co %3d : 1\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.nb_winch;pa++)	fprintf(f3,"wi %3d : 1\n",pa);	fprintf(f3,"\n");
	for (pa=1;pa<=Structure.nb_barre;pa++)	fprintf(f3,"ba %3d : 1\n",pa);	fprintf(f3,"\n"); //NOMBRE_ELEMENTS
	for (pa=1;pa<=Structure.nb_total;pa++)	fprintf(f3,"pt %3d : 1\n",pa); //NOMBRE_NOEUDS
	fclose(f3);
	
	for (el=1;el<=Structure.NbTypeelem;el++)
		{
		//printf("el %4d nb_barre %4d\n",el,element[el].nb_barre);
		}
	printf("Structure.nb_total = %4d \n",Structure.nb_total);
	printf("bar number = %d\n", Structure.nb_barre);
	//exit(0);

	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[72],1);
		}
	}	

/****************************************************************************/		
void maillage_winch1(int el)
	{
	int   co,nloc1,nloc2,nopan,maille,mode;
	char  pan;
		
	if(winch[el].flag_maillage == 0)
		{
		if (winch[el].nb_barre <= 0.0)
			{
			printf("ERREUR 1\n");
			printf("le nb de barre n est pas positif = %12d \n",winch[el].nb_barre);
			printf("Element = %12d \n",el);
			exit(0);
			}
		maillage_winch_libre(el);
		winch[el].flag_maillage = 1;
		}


	/*printf("Structure.nb_total = %4d \n",Structure.nb_total);*/
	
	}


		
/****************************************************************************/		
void maillage_element2(int el)
	{
	int   co,cp,nloc1,nloc2,nopan,maille,mode;
	char  pan;
		
	/*if(element[el].flag_maillage == 1)
		{
		printf("WARNING maillage_element2  le maillage de l'element %12d est deja fait\n",el);
		}*/
	
	if(element[el].flag_maillage == 0)
		{
		if (element[el].nb_barre <= 0.0)
			{
			printf("ERREUR 2\n");
			printf("le nb de barre de l'element %d n est pas positif = %12d \n",el,element[el].nb_barre);
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
	/*printf("Structure.nb_total = %4d \n",Structure.nb_total);*/
	
	//do the list of barre per element
	
	//printf("Structure.nb_barre = %4d ",Structure.nb_barre);
	//printf("el = %4d \n",el);
	for (co=1;co<=Structure.nb_barre;co++)	
		{
		//printf("bar %4d ",co);
		//printf("cable %4d ",barre[co].type);
		//printf("bar nodes %4d %4d ",barre[co].noeud[1],barre[co].noeud[2]);
		//printf("bar pro %4.2f %4.2f\n",barre[co].pro[1],barre[co].pro[2]);	
		}
	//printf("extremity element %4d %4d ",element[el].extremite[1],element[el].extremite[2]);
	//printf("element nb_bar %4d\n",element[el].nb_barre);
	for (cp=1;cp<=element[el].nb_barre-1;cp++)	
		{	
		//printf("node %4d ",element[el].noeud[cp]);
		//printf("bar %4d\n",element[el].barre[cp]);
		}

	//exit(0);
	}


		
/******************************************************************************/
void maillage_panneau(int pa)
	{
	if(panneau[pa].flag_maillage == 1)
		{
		printf("WARNING \n");
		printf("le maillage du panneau %12d est deja fait",pa);
		}
		
	if (panneau[pa].flag_maillage == 0)
		{
		if (panneau[pa].pas_maillage <= 0.0)
			{
			printf("ERREUR 3\n");
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
		/* SI LE PAS DE MAILLAGE EST UN MULTIPLE DE LA LONGUEUR DE MAILLE, ON FAIT COINCIDER NOEUD REEL ET
		NOEUD DE CALCUL, SINON ON MAILLE A "L'ANCIENNE"*/
		//printf(" panneau = %d",pa );
		//printf(" panneau[pa].longueur_repos= %.3g",panneau[pa].longueur_repos );/**/
		//printf(" nb_noeud_contour = %8d ",panneau[pa].nb_noeud_contour);/**/
		//printf(" maillage.c panneau[%d].type_maillage = %d\n",pa,panneau[pa].type_maillage);
		if   ((panneau[pa].type_maillage != 1) && (panneau[pa].type_maillage != 2) && (panneau[pa].type_maillage != 3) && (panneau[pa].type_maillage != 4))
			{
			printf("Type meshing of panel %d is %d but it must be 1, 2, 3 or 4\n",pa, panneau[pa].type_maillage);
			exit(0);
			}
		if   (panneau[pa].type_maillage == 1)
			{
			/*printf(" type maillage = %d",panneau[pa].type_maillage);
			printf(" maillage 1 \n");*/
			maillage_contour1(pa);
			maillage_interne2(pa);
			}	 
		if   (panneau[pa].type_maillage == 2)
			{
			//printf(" type maillage = %d \n",panneau[pa].type_maillage);
			//printf(" maillage 2 \n");/**/
			maillage_contour2(pa);
			if ((panneau[pa].pas_U == 0.0) && (panneau[pa].pas_u == 0.0))
				{
				maillage_interne3(pa);	/*nodes created along twines uniform*/
				}
			if (panneau[pa].pas_U != 0.0)
				{
				maillage_interne4(pa);	/*nodes created along meshes not uniform*/
				}
			if (panneau[pa].pas_u != 0.0)
				{
				maillage_interne6(pa);	/*nodes created along twines not uniform*/
				}
			}
		if   (panneau[pa].type_maillage == 3)
			{
			//printf(" type maillage = %d \n",panneau[pa].type_maillage);
			//printf("In this case the twines are modelled by bars elements in a rectangular panel\n");/**/
			maillage_interne5(pa);	/*bars elements created along twines*/
			}
		if   (panneau[pa].type_maillage == 4)
			{
			//printf(" type maillage = %d \n",panneau[pa].type_maillage);
			//printf("In this case the twines are modelled by bars elements\n");/**/
			//maillage_interne5(pa);	/*bars elements created along twines*/
			meshing_netting_2_ropes3(pa);
			}
		panneau[pa].flag_maillage = 1;
		}
	
	//printf("panneau %d Structure.nb_total = %4d \n",pa,Structure.nb_total);

	}

/***********************************************************************************************/	
void maillage_pan_hexa2(int pa)
	{
	double X1,X2,X3,Y1,Y2,Y3,U1,U2,U3,V1,V2,V3,longueur_repos,UX,UY,VX,VY,D;
	 
	if(pan_hexa[pa].flag_maillage == 1)
		{
		printf("WARNING \n");
		printf("le maillage du panneau_hexa %12d est deja fait",pa);
		}
	
	if (pan_hexa[pa].flag_maillage == 0)
		{
		if (pan_hexa[pa].pas_maillage <= 0.0)
			{
			printf("ERREUR 4\n");
			printf("le pas du maillage n est pas positif = %12.2f \n",pan_hexa[pa].pas_maillage);
			printf("pan_hexa = %12d \n",pa);
			exit(0);
			}
		pan_hexa[pa].nb_noeud_cote = 0;
		/**********************************************/
  		pan_hexa[pa].noeud_cote = (int *) malloc(1 * sizeof(int));
		if (pan_hexa[pa].noeud_cote    == NULL)
			{
			printf(" pan_hexa[pa].noeud_cote 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		pan_hexa[pa].prop_cote = (float *) malloc(1 * sizeof(float));
		if (pan_hexa[pa].prop_cote    == NULL)
			{
			printf(" pan_hexa[pa].prop_cote 1 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		/* Calcul de la longueur_repos pour se ramener au cas des mailles losanges pour le maillage */
		if (Structure.orientation == 1)
			{
			X1 = noeud[pan_hexa[pa].noeud_contour[1]].y; Y1 = noeud[pan_hexa[pa].noeud_contour[1]].z;
			X2 = noeud[pan_hexa[pa].noeud_contour[2]].y; Y2 = noeud[pan_hexa[pa].noeud_contour[2]].z;
			X3 = noeud[pan_hexa[pa].noeud_contour[3]].y; Y3 = noeud[pan_hexa[pa].noeud_contour[3]].z;
			}
		if (Structure.orientation == 2)
			{
			X1 = noeud[pan_hexa[pa].noeud_contour[1]].z; Y1 = noeud[pan_hexa[pa].noeud_contour[1]].x;
			X2 = noeud[pan_hexa[pa].noeud_contour[2]].z; Y2 = noeud[pan_hexa[pa].noeud_contour[2]].x;
			X3 = noeud[pan_hexa[pa].noeud_contour[3]].z; Y3 = noeud[pan_hexa[pa].noeud_contour[3]].x;
			}
		if (Structure.orientation == 3)
			{
			X1 = noeud[pan_hexa[pa].noeud_contour[1]].x; Y1 = noeud[pan_hexa[pa].noeud_contour[1]].y;
			X2 = noeud[pan_hexa[pa].noeud_contour[2]].x; Y2 = noeud[pan_hexa[pa].noeud_contour[2]].y;
			X3 = noeud[pan_hexa[pa].noeud_contour[3]].x; Y3 = noeud[pan_hexa[pa].noeud_contour[3]].y;
			}
			
		U3 = noeud[pan_hexa[pa].noeud_contour[3]].U; V3 = noeud[pan_hexa[pa].noeud_contour[3]].V;
		U1 = noeud[pan_hexa[pa].noeud_contour[1]].U; V1 = noeud[pan_hexa[pa].noeud_contour[1]].V;
		U2 = noeud[pan_hexa[pa].noeud_contour[2]].U; V2 = noeud[pan_hexa[pa].noeud_contour[2]].V;

		/*calcul d une longueur au repos pour estimer la pas de maillage: ATTENTION A REVOIR!!*/
		D=(U2-U1)*(V3-V1)-(U3-U1)*(V2-V1);
		UX=((X2-X1)*(V3-V1)-(X3-X1)*(V2-V1))/D;
		UY=((Y2-Y1)*(V3-V1)-(Y3-Y1)*(V2-V1))/D;
		VX=((X2-X1)*(U3-U1)-(X3-X1)*(U2-U1))/D;
		VY=((Y2-Y1)*(U3-U1)-(Y3-Y1)*(U2-U1))/D;
			
		longueur_repos=0.5*sqrt((UX+VX)*(UX+VX) + (UY+VY)*(UY+VY));
		/*longueur_repos= 0.023;
		printf("D UX UY VX VY : %lf %lf %lf %lf %lf \n",D,UX,UY,VX,VY);*/
		printf("longueur_repos = %lf\n",longueur_repos);
			
		/* SI LE PAS DE MAILLAGE EST UN MULTIPLE DE LA LONGUEUR DE MAILLE, ON FAIT COINCIDER NOEUD REEL ET
		 NOEUD DE CALCUL, SINON ON MAILLE A "L'ANCIENNE"*/
			
		if   ((pan_hexa[pa].type_maillage < 1) || (pan_hexa[pa].type_maillage > 3))
			{
			printf("le type de maillage du pan_hexa %d doit etre entre 1 et 3\n",pa );
			exit(0);
			}
		if   (pan_hexa[pa].type_maillage == 1)
			{
			printf(" pan_hexa = %d",pa );
			printf(" type maillage = %d",pan_hexa[pa].type_maillage);
			printf(" maillage 1 \n");
			mail_hexa_contour1(pa,longueur_repos);
			mail_hexa_interne2(pa,longueur_repos);
			}	 
		if   (pan_hexa[pa].type_maillage == 2)
			{
			printf(" pan_hexa = %d",pa );
			printf(" type maillage = %d",pan_hexa[pa].type_maillage);
			printf(" maillage 2 \n");
			mail_hexa_contour2(pa,longueur_repos);
			mail_hexa_interne3(pa,longueur_repos);
			}
		if   (pan_hexa[pa].type_maillage == 3)
			{
			printf(" pan_hexa = %d",pa );
			printf(" type maillage = %d",pan_hexa[pa].type_maillage);
			printf(" maillage 3 \n");
			maillage_pan_hexa_en_element(pa);
			pan_hexa[pa].flag_filet = 1;
			}
		pan_hexa[pa].flag_maillage = 1;
		}
	
	printf("pan_hexa %d Structure.nb_total = %4d \n",pa,Structure.nb_total);
	}
	
/*******************************************************************************************************/
void maillage_coulisse2(int co)
	{
	int   li,no,cq,cp,nloc1,nloc2,nopan,maille,nolienpa,mode1,mode2;
	char  pan;
	
	if(coulisse[co].flag_maillage == 1)
		{
		printf("WARNING \n");
		printf("le maillage de la coulisse %12d est deja fait",co);
		}
	
	if(coulisse[co].flag_maillage == 0)
		{
		if (coulisse[co].nb_noeud < 0)
			{
			printf("ERREUR 5\n");
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
		
	printf("coulisse %d Structure.nb_total = %4d \n",co,Structure.nb_total);
	

	}


void changement_de_type_noeud()
	{
	int   li,no,cq,cp,nloc1,nloc2,nopan,maille,nolienpa,mode1,mode2,zi;
	double ba1,ba2,ba3,ha1,ha2,ha3;
	char  pan;



	for (zi=1;zi<=Structure.nb_type_noeud_XYZ_SUPINF;zi++)	
		{
		ba1 = type_noeud_XYZ_SUPINF.limite_basse1[zi];
		ba2 = type_noeud_XYZ_SUPINF.limite_basse2[zi];
		ba3 = type_noeud_XYZ_SUPINF.limite_basse3[zi];
		ha1 = type_noeud_XYZ_SUPINF.limite_haute1[zi];
		ha2 = type_noeud_XYZ_SUPINF.limite_haute2[zi];
		ha3 = type_noeud_XYZ_SUPINF.limite_haute3[zi];
		if (type_noeud_XYZ_SUPINF.code[zi] == 1)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].z > type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].y > type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].x > type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 2)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].z < type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].y < type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].x < type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 3)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].x > type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].z > type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].y > type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 4)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].x < type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].z < type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].y < type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 5)
			{
			printf("Structure.orientation %d \n", Structure.orientation);		
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].y > type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].x > type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].z > type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 6)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].y < type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].x < type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].z < type_noeud_XYZ_SUPINF.limite[zi]))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 7)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].z > ba1) && (noeud[no].z < ha1))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].y > ba1) && (noeud[no].y < ha1))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].x > ba1) && (noeud[no].x < ha1))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 8)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].x > ba1) && (noeud[no].x < ha1))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].z > ba1) && (noeud[no].z < ha1))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].y > ba1) && (noeud[no].y < ha1))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 9)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].y > ba1) && (noeud[no].y < ha1))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].x > ba1) && (noeud[no].x < ha1))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].z > ba1) && (noeud[no].z < ha1))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 10)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].z > ba1) && (noeud[no].z < ha1) && (noeud[no].x > ba2) && (noeud[no].x < ha2))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].y > ba1) && (noeud[no].y < ha1) && (noeud[no].z > ba2) && (noeud[no].z < ha2))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].x > ba1) && (noeud[no].x < ha1) && (noeud[no].y > ba2) && (noeud[no].y < ha2))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 11)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].x > ba1) && (noeud[no].x < ha1) && (noeud[no].y > ba2) && (noeud[no].y < ha2))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].z > ba1) && (noeud[no].z < ha1) && (noeud[no].x < ba2) && (noeud[no].x > ha2))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].y > ba1) && (noeud[no].y < ha1) && (noeud[no].z > ba2) && (noeud[no].z < ha2))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 12)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].y > ba1) && (noeud[no].y < ha1) && (noeud[no].z > ba2) && (noeud[no].z < ha2))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].x > ba1) && (noeud[no].x < ha1) && (noeud[no].y > ba2) && (noeud[no].y < ha2))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].z > ba1) && (noeud[no].z < ha1) && (noeud[no].x > ba2) && (noeud[no].x < ha2))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		if (type_noeud_XYZ_SUPINF.code[zi] == 13)
			{
			for (no=1;no<=Structure.nb_total;no++)	
				{
				if ((Structure.orientation == 1) && (noeud[no].z > ba1) && (noeud[no].z < ha1) && (noeud[no].x > ba2) && (noeud[no].x < ha2) && (noeud[no].y > ba3) && (noeud[no].y < ha3))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 2) && (noeud[no].y > ba1) && (noeud[no].y < ha1) && (noeud[no].z > ba2) && (noeud[no].z < ha2) && (noeud[no].x > ba3) && (noeud[no].x < ha3))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				if ((Structure.orientation == 3) && (noeud[no].x > ba1) && (noeud[no].x < ha1) && (noeud[no].y > ba2) && (noeud[no].y < ha2) && (noeud[no].z > ba3) && (noeud[no].z < ha3))	noeud[no].type = type_noeud_XYZ_SUPINF.type[zi];
				}
			}
		}
	}
	
	
	
	

