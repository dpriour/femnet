#define PRINCIPAL 0
#include "phobos.h"
	
	/* 
	maillage des panneaux a maille hexagonale en creant des points sur les noeuds reels du filet.
	ATTENTION : pour le maillage interne, il est possible de modifier le facteur de determination des
	noeuds trop proches du contour ou d un autre noeud - voir fact dans mail_hexa_interne3 
	*/
	
void maillage_pan_hexa()
	{
	int   pa,mode,deb ;
	double X1,X2,X3,Y1,Y2,Y3,U1,U2,U3,V1,V2,V3,longueur_repos,UX,UY,VX,VY,D; 
	
	/*faire le filet_contour si ce n est pas fait*/
	mode = GetMenuItemChecked(w[5]);
	if (mode == 0) filet_contour();
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{
		if (pan_hexa[pa].flag_maillage == 0)
			{
			if (pan_hexa[pa].pas_maillage <= 0.0)
				{
				printf("ERREUR \n");
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
			
			deb = 0;
			do
				{
				/*on cherche 3 noeuds consecutifs non alignes cad tel que D != 0*/
				U1 = noeud[pan_hexa[pa].noeud_contour[deb+1]].U; V1 = noeud[pan_hexa[pa].noeud_contour[deb+1]].V;
				U2 = noeud[pan_hexa[pa].noeud_contour[deb+2]].U; V2 = noeud[pan_hexa[pa].noeud_contour[deb+2]].V;
				U3 = noeud[pan_hexa[pa].noeud_contour[deb+3]].U; V3 = noeud[pan_hexa[pa].noeud_contour[deb+3]].V;

				/*calcul d une longueur au repos pour estimer la pas de maillage: ATTENTION A REVOIR!!*/
				/*D est en fait la surface du triangle 1 2 3 exprimee en nb de maille ... a un facteur pres !!*/
				D=(U2-U1)*(V3-V1)-(U3-U1)*(V2-V1);
				
				deb++;
				}
			while ((D == 0.0) && (deb+3 <= pan_hexa[pa].nb_noeud_contour));
			
			if (D==0.0)
				{
				printf("Argh ! pas possible de trouver 3 trouver 3 noeuds consecutifs non alignes \n");
				printf("dans le panneau =  %d \n",pa);
				exit(0);
				}
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
		}
	printf("Structure.nb_total = %4d \n",Structure.nb_total);
	SetMenuItemChecked(w[72],1);
	}

void mail_hexa_contour1(int pa,double longueur_repos)
	{
	int   co, cp, nloc1, nloc2, nopan, maille;
	char  pan ;
	
	for (co=1;co<=pan_hexa[pa].nb_noeud_contour;co++)
		{
		/*CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROATTION LOCALE*/
		if (co != pan_hexa[pa].nb_noeud_contour) cp = co+1;
		if (co == pan_hexa[pa].nb_noeud_contour) cp = 1;
		
		/*
		recherche si le panneau hexa est lie a une structure deja maille
		sinon maille = 0
		si oui maille = 1 a 4
		co est l extremite du cote du panneau hexa
		pan est le type de structure deja maillee : e pour element, h pour panneau hexa ...
		nopan est le numero de la structure
		nloc1 est le noeud lie a cq et nloc2 est lie a l extremite 2 de la coulisse co
		*/
		maille = liaison_maille_hexa(co,pa,&pan,&nopan,&nloc1,&nloc2);
		
		printf("maille = %d \n",maille);
		printf("co = %d \n",co);
		printf("pa = %d \n",pa);
		printf("pan = %c \n",pan);
		printf("nopan = %d \n",nopan);
		printf("nloc1 = %d \n",nloc1);
		printf("nloc2 = %d \n",nloc2);
		
		if (maille == 0)
			{
			mail_hexa_contour_libre_filaire(pa, co, cp, longueur_repos);
		 	}
		if ((maille == 1) || (maille == 2))
			{
			mail_hexa_contour_pan_hexa(pa, co, cp, nopan, nloc1, nloc2);
			}
		if ((maille == 3) || (maille == 4))
			{
			mail_hexa_contour_element(pa, co, cp, nopan, nloc1);
			}
		}
	}

void mail_hexa_interne2(int pa,double longueur_repos)
	{
	/*CREE LES POINTS A L INTERIEUR DU PAN_HEXA PA, EN SE BASANT SUR LES FILS*/
	
	int   li, nbU, nbV, co, sommet_1, sommet_2, sommet_3, tri ,trouve, distant;
	float Uo, Vo, denominateur, coef_a, coef_b ;
	float min_U, min_V, max_U ,max_V ,fact ;
			
	/* FACTEUR DETERMINANT LA TOLERANCE DE PROXIMITE D UN NOEUD DU CONTOUR OU D UN NOEUD DU BORD*/
	/* DISTANCE DU NOEUD AU BORD OU A UN AUTRE NOEUD, INFERIEURE A (PAS DE MAILLAGE * FACT) */
	fact = 0.5 ;
	
	/*RECHERCHE DES POINTS EXTREMES*/
	min_U = noeud[pan_hexa[pa].noeud_contour[1]].u;
	min_V = noeud[pan_hexa[pa].noeud_contour[1]].v;
	max_U = noeud[pan_hexa[pa].noeud_contour[1]].u;
	max_V = noeud[pan_hexa[pa].noeud_contour[1]].v;
	for (co=1;co<=pan_hexa[pa].nb_noeud_contour;co++)
		{
		if (noeud[pan_hexa[pa].noeud_contour[co]].u > max_U) max_U = noeud[pan_hexa[pa].noeud_contour[co]].u;
		if (noeud[pan_hexa[pa].noeud_contour[co]].u < min_U) min_U = noeud[pan_hexa[pa].noeud_contour[co]].u;
		if (noeud[pan_hexa[pa].noeud_contour[co]].v > max_V) max_V = noeud[pan_hexa[pa].noeud_contour[co]].v;
		if (noeud[pan_hexa[pa].noeud_contour[co]].v < min_V) min_V = noeud[pan_hexa[pa].noeud_contour[co]].v;
		}
	nbU = (int) ((max_U - min_U) / pan_hexa[pa].pas_maillage * longueur_repos);
	nbV = (int) ((max_V - min_V) / pan_hexa[pa].pas_maillage * longueur_repos);
	pan_hexa[pa].nb_noeud_interieur = 0;
	
	/**********************************************/
  	pan_hexa[pa].noeud_interieur = (int *) malloc(1 * sizeof(int));
	if (pan_hexa[pa].noeud_interieur    == NULL)
		{
		printf(" pan_hexa[pa].noeud_interieur 1 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	for (co=1;co<=nbV - 1;co++)
		{
		for (li=1;li<=nbU - 1;li++)
			{
			Uo = min_U + li * (max_U-min_U) / nbU;
			Vo = min_V + co * (max_V-min_V) / nbV;
			tri = interieur_pan_hexa_filaire(Uo, Vo,  pa);
			trouve = proche_contour_filaire_hexa(Uo, Vo,  pa, fact, longueur_repos);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / CONTOUR */
			distant = proche_pan_hexa_filaire(Uo, Vo, pa, fact, longueur_repos);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / NOEUD */
			
			if ((tri != 0) && (trouve != 0) && (distant != 0))
				{
				Structure.nb_total++;
				if (Structure.nb_total >= NBMAXNOEUD)
					{
					printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
					exit(0);
					}
				pan_hexa[pa].nb_noeud_interieur = pan_hexa[pa].nb_noeud_interieur + 1;
				/**********************************************/
  				pan_hexa[pa].noeud_interieur = (int *) realloc(pan_hexa[pa].noeud_interieur, (1+ pan_hexa[pa].nb_noeud_interieur) * sizeof(int));
				if (pan_hexa[pa].noeud_interieur    == NULL)
					{
					printf(" pan_hexa[pa].noeud_interieur 2 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				pan_hexa[pa].noeud_interieur[pan_hexa[pa].nb_noeud_interieur] = Structure.nb_total;
				noeud[Structure.nb_total].u = Uo;
				noeud[Structure.nb_total].v = Vo;
				noeud[Structure.nb_total].type = pan_hexa[pa].type_noeud;
			
				sommet_1 = pan_hexa[pa].noeud_contour[pan_hexa[pa].tri_hexa_contour[tri][1]];
				sommet_2 = pan_hexa[pa].noeud_contour[pan_hexa[pa].tri_hexa_contour[tri][2]];
				sommet_3 = pan_hexa[pa].noeud_contour[pan_hexa[pa].tri_hexa_contour[tri][3]];
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

void mail_hexa_contour2(int pa,double longueur_repos)
	{
	int   co, cp, nloc1, nloc2, nopan, maille;
	char  pan ;
	
	for (co=1;co<=pan_hexa[pa].nb_noeud_contour;co++)
		{
		/*CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROATTION LOCALE*/
		if (co != pan_hexa[pa].nb_noeud_contour) cp = co+1;
		if (co == pan_hexa[pa].nb_noeud_contour) cp = 1;
		
		/*
		recherche si le panneau hexa est lie a une structure deja maille
		sinon maille = 0
		si oui maille = 1 a 4
		co est l extremite du cote du panneau hexa
		pan est le type de structure deja maillee : e pour element, h pour panneau hexa ...
		nopan est le numero de la structure
		nloc1 est le noeud lie a cq et nloc2 est lie a l extremite 2 de la coulisse co
		*/
		maille = liaison_maille_hexa(co,pa,&pan,&nopan,&nloc1,&nloc2);
		
		printf("maille = %d \n",maille);
		printf("co = %d \n",co);
		printf("pa = %d \n",pa);
		printf("pan = %c \n",pan);
		printf("nopan = %d \n",nopan);
		printf("nloc1 = %d \n",nloc1);
		printf("nloc2 = %d \n",nloc2);
		
		
		if (maille == 0)
			{
			mail_hexa_contour_libre_filaire2(pa, co, cp, longueur_repos);
		 	}
		if ((maille == 1) || (maille == 2))
			{
			mail_hexa_contour_pan_hexa2(pa, co, cp, nopan, nloc1, nloc2);
			}
		if ((maille == 3) || (maille == 4))
			{
			mail_hexa_contour_element(pa, co, cp, nopan, nloc1);
			}
		}
	}
	
void mail_hexa_interne3(int pa,double longueur_repos)
	{
	/*CREE LES POINTS A L INTERIEUR DU PANNEAU PA, EN SE BASANT SUR LES FILS*/
	
	int    li ,nbU, nbV, co, sommet_1, sommet_2, sommet_3, tri ,trouve, distant;
	float  Uo, Vo, denominateur, coef_a, coef_b ;
	float  min_U, min_V, max_U, max_V ,fact, passe ;
			
	/* FACTEUR DETERMINANT LA TOLERANCE DE PROXIMITE D UN NOEUD DU CONTOUR OU D UN NOEUD DU BORD*/
	/* DISTANCE DU NOEUD AU BORD OU A UN AUTRE NOEUD, INFERIEURE A (PAS DE MAILLAGE * FACT) */
	fact = 0.25 ;
	
	/*RECHERCHE DES POINTS EXTREMES*/
	min_U = noeud[pan_hexa[pa].noeud_contour[1]].u;
	min_V = noeud[pan_hexa[pa].noeud_contour[1]].v;
	max_U = noeud[pan_hexa[pa].noeud_contour[1]].u;
	max_V = noeud[pan_hexa[pa].noeud_contour[1]].v;
	for (co=1;co<=pan_hexa[pa].nb_noeud_contour;co++)
		{
		if (noeud[pan_hexa[pa].noeud_contour[co]].u > max_U) max_U = noeud[pan_hexa[pa].noeud_contour[co]].u;
		if (noeud[pan_hexa[pa].noeud_contour[co]].u < min_U) min_U = noeud[pan_hexa[pa].noeud_contour[co]].u;
		if (noeud[pan_hexa[pa].noeud_contour[co]].v > max_V) max_V = noeud[pan_hexa[pa].noeud_contour[co]].v;
		if (noeud[pan_hexa[pa].noeud_contour[co]].v < min_V) min_V = noeud[pan_hexa[pa].noeud_contour[co]].v;
		}
	nbU = (int) ((max_U - min_U) / pan_hexa[pa].pas_maillage * longueur_repos);
	nbV = (int) ((max_V - min_V) / pan_hexa[pa].pas_maillage * longueur_repos);
	
	pan_hexa[pa].nb_noeud_interieur = 0;
	/**********************************************/
  	pan_hexa[pa].noeud_interieur = (int *) malloc(1 * sizeof(int));
	if (pan_hexa[pa].noeud_interieur    == NULL)
		{
		printf(" pan_hexa[pa].noeud_interieur 1 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	passe = pan_hexa[pa].pas_maillage / longueur_repos;
	for (co=1;co<=nbV ;co++)
		{
		for (li=1;li<=nbU ;li++)
			{
				 Uo =  floor(min_U) + passe * li ;
				 Vo =  floor(min_V) + passe * co ;
			
			tri     = interieur_pan_hexa_filaire(Uo, Vo,  pa);
			trouve  = proche_contour_filaire_hexa(Uo, Vo,  pa, fact, longueur_repos);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / CONTOUR */
			distant = proche_pan_hexa_filaire(Uo, Vo, pa, fact, longueur_repos);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / NOEUD */
			
			if ((tri != 0) && (trouve != 0) && (distant != 0))
				{
				Structure.nb_total++;
				
				if (Structure.nb_total >= NBMAXNOEUD)
					{
					printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
					exit(0);
					}
				pan_hexa[pa].nb_noeud_interieur = pan_hexa[pa].nb_noeud_interieur + 1;
				/**********************************************/
  				pan_hexa[pa].noeud_interieur = (int *) realloc(pan_hexa[pa].noeud_interieur, (1+ pan_hexa[pa].nb_noeud_interieur) * sizeof(int));
				if (pan_hexa[pa].noeud_interieur    == NULL)
					{
					printf(" pan_hexa[pa].noeud_interieur 2 = NULL  \n" );
					exit(0);
					}
				/**********************************************/
				pan_hexa[pa].noeud_interieur[pan_hexa[pa].nb_noeud_interieur] = Structure.nb_total;
				noeud[Structure.nb_total].u = Uo;
				noeud[Structure.nb_total].v = Vo;
				noeud[Structure.nb_total].type = pan_hexa[pa].type_noeud;
			
				sommet_1 = pan_hexa[pa].noeud_contour[pan_hexa[pa].tri_hexa_contour[tri][1]];
				sommet_2 = pan_hexa[pa].noeud_contour[pan_hexa[pa].tri_hexa_contour[tri][2]];
				sommet_3 = pan_hexa[pa].noeud_contour[pan_hexa[pa].tri_hexa_contour[tri][3]];
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
	
int liaison_maille_hexa(int neud,int pannea,char *structur,int *nostructur,int *debutsegm,int *finsegm)
	{
	/*
	NEUD = DEBUT DU SEGMENT TRAITE,
	PANNEA = PANNEAU TRAITE,
	RENVOIE 1 SI LE NOEUD EST LIE PAR UN LIEN A UNE STRUCTURE DEJA MAILLEE, SINON 0
	STRUCTUR = TYPE DE LA STRUCTURE MAILLEE
	NOSTRUCTUR = NUMERO DE CETTE STRUCTURE
	DEBUTSEGM = NUMERO DANS LA NUMEROTATION LOCALE DE LA PREMIERE EXTREMITE DU SEGMENT MAILLEE
	FINSEGM = NUMERO DANS LA NUMEROTATION LOCALE DE LA DERNIERE EXTREMITE DU SEGMENT MAILLEE
	*/
	
	int noeue, noliennoeud, noliennoeue, pa, el, noliendeb, nolienfin ;
	int co, cp, deb, fin ;
	
	/*NEUD = DEBUT DU COTE, NOEUE : FIN DU COTE DANS LA NUMEROTATION LOCALE*/
	if (neud != pan_hexa[pannea].nb_noeud_contour) noeue = neud+1;
	if (neud == pan_hexa[pannea].nb_noeud_contour) noeue = 1;
	
	deb = pan_hexa[pannea].noeud_contour[neud];
	fin = pan_hexa[pannea].noeud_contour[noeue];
	noliennoeud = appartient_liaison(deb);
	noliennoeue = appartient_liaison(fin);
	
	if ((noliennoeud != 0) && (noliennoeue != 0))
		{
		for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
			{
			if ((pa != pannea) && (pan_hexa[pa].flag_maillage == 1))
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
					if((noliendeb == noliennoeud) && (nolienfin == noliennoeue))
						{
						*structur = 'h';
						*nostructur = pa;
						*debutsegm = co;
						*finsegm = cp;
						return 1;
						}
					if((noliendeb == noliennoeue) && (nolienfin == noliennoeud))
						{
						*structur = 'h';
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

void mail_hexa_contour_libre_filaire(int pa, int co, int cp,double longueur_repos)
	{
	/*
	PA = NO DU PANNEAU, CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE
	EN SE BASANT SUR LES COORDONNEES FILAIRES
	*/
	int    zi, nb_coupe, deb, fin;
	float  xdeb, xfin, ydeb, yfin, zdeb, zfin ;
	float  lg_tendue ;
	
	deb  = pan_hexa[pa].noeud_contour[co];
	fin  = pan_hexa[pa].noeud_contour[cp];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	lg_tendue = sqrt(((noeud[fin].u-noeud[deb].u) * (noeud[fin].u-noeud[deb].u)) + ((noeud[fin].v-noeud[deb].v) * (noeud[fin].v-noeud[deb].v)));
	nb_coupe = (int) (lg_tendue / pan_hexa[pa].pas_maillage * longueur_repos);
	
	pan_hexa[pa].suivant_contour[co] = 0 ;
	
	for (zi=1;zi<=nb_coupe -1 ;zi++)
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		pan_hexa[pa].nb_noeud_cote++;
		
		/**********************************************/
  		pan_hexa[pa].noeud_cote = (int *) realloc(pan_hexa[pa].noeud_cote, (1+ pan_hexa[pa].nb_noeud_cote) * sizeof(int));
		if (pan_hexa[pa].noeud_cote    == NULL)
			{
			printf(" pan_hexa[pa].noeud_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		pan_hexa[pa].prop_cote = (float *) realloc(pan_hexa[pa].prop_cote, (1+ pan_hexa[pa].nb_noeud_cote) * sizeof(float));
		if (pan_hexa[pa].prop_cote    == NULL)
			{
			printf(" pan_hexa[pa].prop_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		if (zi == 1)
			{
			pan_hexa[pa].suivant_contour[co] = pan_hexa[pa].nb_noeud_cote;
			}
		pan_hexa[pa].noeud_cote[pan_hexa[pa].nb_noeud_cote] = Structure.nb_total;
		pan_hexa[pa].prop_cote[pan_hexa[pa].nb_noeud_cote] = (float) zi / nb_coupe;
		noeud[Structure.nb_total].x = xdeb + zi * (xfin-xdeb) / nb_coupe;
		noeud[Structure.nb_total].y = ydeb + zi * (yfin-ydeb) / nb_coupe;
		noeud[Structure.nb_total].z = zdeb + zi * (zfin-zdeb) / nb_coupe;
		noeud[Structure.nb_total].type = pan_hexa[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].U = noeud[deb].U + zi * (noeud[fin].U-noeud[deb].U) / nb_coupe;
		noeud[Structure.nb_total].V = noeud[deb].V + zi * (noeud[fin].V-noeud[deb].V) / nb_coupe;
		noeud[Structure.nb_total].u = noeud[Structure.nb_total].U + noeud[Structure.nb_total].V; 
		noeud[Structure.nb_total].v = noeud[Structure.nb_total].V - noeud[Structure.nb_total].U; 
		}
	}
		
void mail_hexa_contour_pan_hexa(int pa, int co, int cp,int pa2,int nlo1,int nlo2)
	{
	/*
	PA = NO DU PANNEAU, CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE
	PA2 = NO DU 2EM PANNEAU, NLO1 = DEBUT DU COTE, NLO2 : FIN DU COTE DANS LA NUMEROTATION LOCALE
	*/
	int   zi, nb_coupe, deb, fin, premier_cote, sens_cote, nb_lai, premier_loc, nlo3 ;
	float xdeb, xfin, ydeb, yfin, zdeb, zfin, ss ;
	
	deb  = pan_hexa[pa2].noeud_contour[nlo1];
	fin  = pan_hexa[pa2].noeud_contour[nlo2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	
	/*CALCUL DE NB_COUPE*/
	if (nlo1 + 1 == nlo2)
		{
		if(pan_hexa[pa2].suivant_contour[nlo1] == 0)
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
			while ((pan_hexa[pa2].suivant_contour[nlo3] == 0) && (nlo3 != pan_hexa[pa2].nb_noeud_contour));
			if (pan_hexa[pa2].suivant_contour[nlo3] != 0)
				{
				nb_coupe = pan_hexa[pa2].suivant_contour[nlo3] - pan_hexa[pa2].suivant_contour[nlo1] + 1;
				}
			else
				{
				nb_coupe = pan_hexa[pa2].nb_noeud_cote - pan_hexa[pa2].suivant_contour[nlo1] + 2;
				}
			}
		}
	if (nlo1 - 1 == nlo2)
		{
		if(pan_hexa[pa2].suivant_contour[nlo2] == 0)
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
			while ((pan_hexa[pa2].suivant_contour[nlo3] == 0) && (nlo3 != pan_hexa[pa2].nb_noeud_contour));
			if (pan_hexa[pa2].suivant_contour[nlo3] != 0)
				{
				nb_coupe = pan_hexa[pa2].suivant_contour[nlo3] - pan_hexa[pa2].suivant_contour[nlo2] + 1;
				}
			else
				{
				nb_coupe = pan_hexa[pa2].nb_noeud_cote - pan_hexa[pa2].suivant_contour[nlo2] + 2;
				}
			}
		}
	if ((nlo1 - 1 != nlo2) && (nlo1 + 1 != nlo2))
		{
		/*DANS CE CAS NLO1 ET NLO2 SONT 1 ET PANNEAU[PA2].NB_NOEUD_CONTOUR OU INVERSEMENT*/
		if(pan_hexa[pa2].suivant_contour[pan_hexa[pa2].nb_noeud_contour] == 0)
			{
			/*pas de point de cote sur ce segment de contour*/
			nb_coupe = 1;
			}
		else
			{
			nb_coupe = pan_hexa[pa2].nb_noeud_cote - pan_hexa[pa2].suivant_contour[pan_hexa[pa2].nb_noeud_contour] + 2;
			}
		}
	
	deb  = pan_hexa[pa].noeud_contour[co];
	fin  = pan_hexa[pa].noeud_contour[cp];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	
	if((nlo1 == nlo2-1) || ((nlo1 == pan_hexa[pa2].nb_noeud_contour) && (nlo2 == 1)))
		{
		premier_loc  = pan_hexa[pa2].suivant_contour[nlo1];
		premier_cote = pan_hexa[pa2].noeud_cote[pan_hexa[pa2].suivant_contour[nlo1]];
		sens_cote = +1;
		}
	if((nlo2 == nlo1-1) || ((nlo2 == pan_hexa[pa2].nb_noeud_contour) && (nlo1 == 1)))
		{
		premier_loc  = pan_hexa[pa2].suivant_contour[nlo2] + nb_coupe - 2;
		premier_cote = pan_hexa[pa2].noeud_cote[pan_hexa[pa2].suivant_contour[nlo2]] + nb_coupe - 2;
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
		pan_hexa[pa].nb_noeud_cote++;
		
		/**********************************************/
  		pan_hexa[pa].noeud_cote = (int *) realloc(pan_hexa[pa].noeud_cote, (1 + pan_hexa[pa].nb_noeud_cote) * sizeof(int));
		if (pan_hexa[pa].noeud_cote    == NULL)
			{
			printf(" pan_hexa[pa].noeud_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		pan_hexa[pa].prop_cote = (float *) realloc(pan_hexa[pa].prop_cote, (1 + pan_hexa[pa].nb_noeud_cote) * sizeof(float));
		if (pan_hexa[pa].prop_cote    == NULL)
			{
			printf(" pan_hexa[pa].prop_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		if (zi ==1)
			{
			pan_hexa[pa].suivant_contour[co] = pan_hexa[pa].nb_noeud_cote;
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
			Lien[Structure.nb_lien].type[1] = 'h';
			Lien[Structure.nb_lien].type[2] = 'h';
			Lien[Structure.nb_lien].structure[1] = pa2;
			Lien[Structure.nb_lien].structure[2] = pa ;
			Lien[Structure.nb_lien].extremite[1] = premier_loc + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].extremite[2] = pan_hexa[pa].nb_noeud_cote;
			Lien[Structure.nb_lien].noeud[1] = premier_cote + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].noeud[2] = Structure.nb_total;
			}
		if (nb_lai != 0)
			{		
			Lien[nb_lai].nb_liaison++;
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'h';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = pa;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = pan_hexa[pa].nb_noeud_cote;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		ss = 0.5 * ( fabs( sens_cote - 1. ) );
		pan_hexa[pa].noeud_cote[pan_hexa[pa].nb_noeud_cote] = Structure.nb_total;
		pan_hexa[pa].prop_cote[pan_hexa[pa].nb_noeud_cote] = (float) ( ss + sens_cote ) * zi /nb_coupe;
		noeud[Structure.nb_total].x = xdeb + zi * (xfin-xdeb) /nb_coupe;
		noeud[Structure.nb_total].y = ydeb + zi * (yfin-ydeb) /nb_coupe;
		noeud[Structure.nb_total].z = zdeb + zi * (zfin-zdeb) /nb_coupe;
		noeud[Structure.nb_total].U = noeud[deb].U +zi * (noeud[fin].U-noeud[deb].U)/nb_coupe ;
		noeud[Structure.nb_total].V = noeud[deb].V +zi * (noeud[fin].V-noeud[deb].V)/nb_coupe  ;
		noeud[Structure.nb_total].type = pan_hexa[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].u = noeud[Structure.nb_total].U + noeud[Structure.nb_total].V; 
		noeud[Structure.nb_total].v = noeud[Structure.nb_total].V - noeud[Structure.nb_total].U; 
		}
	}

void mail_hexa_contour_element(int pa,int co,int cp,int noele,int nloc)
	{
	/*
	PA = NO DU PANNEAU, CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE
	NOELE = NO DE L ELEMENT, NLOC = DEBUT DE L ELEMENT CORRESPONDANT A CO
	*/
	
	int   zi, nb_coupe, deb, fin, premier_cote, sens_cote, nb_lai, premier_loc ;
	float xdeb, xfin, ydeb, yfin, zdeb, zfin ;
	
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
	
	deb  = pan_hexa[pa].noeud_contour[co];
	fin  = pan_hexa[pa].noeud_contour[cp];
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
		pan_hexa[pa].nb_noeud_cote++;
		
		/**********************************************/
  		pan_hexa[pa].noeud_cote = (int *) realloc(pan_hexa[pa].noeud_cote, (1+ pan_hexa[pa].nb_noeud_cote) * sizeof(int));
		if (pan_hexa[pa].noeud_cote    == NULL)
			{
			printf(" pan_hexa[pa].noeud_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		pan_hexa[pa].prop_cote = (float *) realloc(pan_hexa[pa].prop_cote, (1+ pan_hexa[pa].nb_noeud_cote) * sizeof(float));
		if (pan_hexa[pa].prop_cote    == NULL)
			{
			printf(" pan_hexa[pa].prop_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		if (zi ==1)
			{
			pan_hexa[pa].suivant_contour[co] = pan_hexa[pa].nb_noeud_cote;
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
			Lien[Structure.nb_lien].type[2] = 'h';
			Lien[Structure.nb_lien].structure[1] = noele;
			Lien[Structure.nb_lien].structure[2] = pa ;
			Lien[Structure.nb_lien].extremite[1] = premier_loc + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].extremite[2] = pan_hexa[pa].nb_noeud_cote;
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
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'h';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = pa;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = pan_hexa[pa].nb_noeud_cote;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		pan_hexa[pa].noeud_cote[pan_hexa[pa].nb_noeud_cote] = Structure.nb_total;
		noeud[Structure.nb_total].x = xdeb + zi * (xfin-xdeb) / nb_coupe;
		noeud[Structure.nb_total].y = ydeb + zi * (yfin-ydeb) / nb_coupe;
		noeud[Structure.nb_total].z = zdeb + zi * (zfin-zdeb) / nb_coupe;
		noeud[Structure.nb_total].U = noeud[deb].U + zi * (noeud[fin].U-noeud[deb].U) / nb_coupe;
		noeud[Structure.nb_total].V = noeud[deb].V + zi * (noeud[fin].V-noeud[deb].V) / nb_coupe;
		noeud[Structure.nb_total].type = pan_hexa[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].u = noeud[Structure.nb_total].U + noeud[Structure.nb_total].V; 
		noeud[Structure.nb_total].v = noeud[Structure.nb_total].V - noeud[Structure.nb_total].U; 
		}
	}

void mail_hexa_contour_libre_filaire2(int pa, int co, int cp,double longueur_repos)
	{
	/*
	PA = NO DU PANNEAU, CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE
	EN SE BASANT SUR LES COORDONNEES FILAIRES
	*/
	int    i, zi, deb, fin, nb_u, nb_v, pt_u, pt_v, sens_u, sens_v, pointu, pointv, cpt;
	float  xdeb, xfin, ydeb, yfin, zdeb, zfin, udeb, ufin, vdeb, vfin, passe, fact;
	float  lg_tendue ;
	float  noeudcote_u[3*NBMAXNOEUDCOTE][3], noeudcote_v[3*NBMAXNOEUDCOTE][3], noeudcote_uv[3*NBMAXNOEUDCOTE][3] ;
	
	fact = 0.6;
	/* AFFECTATIONS DES VARIABLES COURANTES */
	deb = pan_hexa[pa].noeud_contour[co];
	fin = pan_hexa[pa].noeud_contour[cp];
	xdeb = noeud[deb].x ; xfin = noeud[fin].x ;
	ydeb = noeud[deb].y ; yfin = noeud[fin].y ;
	zdeb = noeud[deb].z ; zfin = noeud[fin].z ;
	udeb = noeud[deb].u ; ufin = noeud[fin].u ;
	vdeb = noeud[deb].v ; vfin = noeud[fin].v ;
	lg_tendue = sqrt(((noeud[fin].u-noeud[deb].u) * (noeud[fin].u-noeud[deb].u)) + ((noeud[fin].v-noeud[deb].v) * (noeud[fin].v-noeud[deb].v)));

	/* LOCALISATION DES POINTS EN FILS U ET EN FILS V SUR LE COTE*/
	/* DETERMINATION DES SENS DE CROISSANCE DE U ET V SUR LE COTE */
	if ( udeb <= ufin ) sens_u =  1 ;
		else        sens_u = -1 ;
	if ( vdeb <= vfin ) sens_v =  1 ;
		else        sens_v = -1 ;
	
	passe =  pan_hexa[pa].pas_maillage / longueur_repos;
	
	/* DETERMINATION DES POINTS EN U SUR LE COTE, NB_U NOMBRE DE POINTS EN U*/
	pt_u = 0 ; nb_u = 0 ;
	while ( (float) sens_u * (floor(udeb) + passe * sens_u * pt_u) <= sens_u * udeb )		/* ON SE PLACE BIEN PAR RAPPORT A L'EXTREMITE */
		{
		pt_u = pt_u + 1;
		}
	while  ( ( (float) sens_u * (floor(udeb) + sens_u * pt_u * passe ) < sens_u * ufin ) && ( fabs(sens_u *( ufin -  (floor(udeb) + sens_u * pt_u * passe))) >= fact*passe )) 		/* ON STOCKE LES POINTS TROUVES EN FILS U */
	    	{
	     	noeudcote_u[nb_u+1][1] = (float) floor(udeb) + sens_u * pt_u * passe ;
	     	noeudcote_u[nb_u+1][2] = equation_cote(2,noeudcote_u[nb_u+1][1],udeb,ufin,vdeb,vfin);
	     	pt_u++;
	     	nb_u++;
	    	}

	/* DETERMINATION DES POINTS EN V SUR LE COTE, NB_V NOMBRE DE POINTS EN V */
	pt_v = 0 ; nb_v = 0 ;
	while ( (float) sens_v * (floor(vdeb) + passe * sens_v * pt_v) <= sens_v * vdeb )
		{
		pt_v = pt_v + 1;
		}
	while ( ( (float) sens_v * (floor(vdeb) + sens_v * pt_v * passe ) < sens_v * vfin ) && ( fabs(sens_v *( vfin -  (floor(vdeb) + sens_v * pt_v * passe))) >= fact*passe )) 	
	    	{
	     	noeudcote_v[nb_v+1][2] = (float) floor(vdeb) + sens_v * pt_v * passe ;
	     	noeudcote_v[nb_v+1][1] = equation_cote(1,noeudcote_v[nb_v+1][2],udeb,ufin,vdeb,vfin);
	     	pt_v++;
	     	nb_v++;
	    	}

	/* TRI ET RANGEMENT DE CES NOEUDS DU COTE, CPT : COMPTEUR DU NOMBRE DE "VRAIS" NOEUDS POSES SUR LE COTE */
   	/* 
   	CET ALGO DE TRI COMPARE UN "NOEUD EN U" A UN "NOEUD EN V" JUSQU A LA FIN D UN DES 2 TABLEAUX DES NOEUDS,
   	ET DECIDE QU ILS SONT IDENTIQUES  S ILS NE SONT NI INFERIEUR (EN U OU V) NI SUPERIEUR (EN U OU V), L UN A 
   	L AUTRE. POINTU ET POINTV DESIGNENT LES INDICES COURANT DES TABLEAUX, RESPT EN U ET V.
   	SI UN NOEUD EST TROP PRES DU PRECEDENT, ON L IGNORE!
   	*/
   	
        noeudcote_uv[0][1] = udeb ;
	noeudcote_uv[0][2] = vdeb ;
	pointu = 1 ; pointv = 1 ; cpt = 1 ; 
	while ( ( pointu <= nb_u ) && ( pointv <= nb_v ) )
		{
		if ( ( sens_u * ( noeudcote_u[pointu][1] - noeudcote_v[pointv][1] ) < -0.001 ) || 		/* LE POINT EN FIL U EST AVANT LE POINT EN FIL V */
	     	( sens_v * ( noeudcote_u[pointu][2] - noeudcote_v[pointv][2] ) < -0.001 )   )
	     		{
	      		if ( ( fabs(noeudcote_u[pointu][1] - noeudcote_uv[cpt-1][1]) < 0.5*passe) )
	            		{
	             		pointu++;
	            		}
	      		else
	      	    		{ 
	      			noeudcote_uv[cpt][1] = noeudcote_u[pointu][1] ; 
	      			noeudcote_uv[cpt][2] = noeudcote_u[pointu][2] ;
	      			pointu++;
	      			cpt++;
	      	    		}
	     		}
	 	else  
	 		{
	 		if ( ( sens_u * ( noeudcote_v[pointv][1] - noeudcote_u[pointu][1] ) < -0.001 ) || 	/* LE POINT EN FIL V EST AVANT LE POINT EN FIL U */
	             	( sens_v * ( noeudcote_v[pointv][2] - noeudcote_u[pointu][2] ) < -0.001 )   )
	           		{
	            		if ( ( fabs(noeudcote_v[pointv][2] - noeudcote_uv[cpt-1][2]) < 0.5*passe) )
	            			{
	            	 		pointv++;
	            			}
	            		else 
	            			{
	            	 		noeudcote_uv[cpt][1] = noeudcote_v[pointv][1] ; 
	            	 		noeudcote_uv[cpt][2] = noeudcote_v[pointv][2] ;
	            	 		pointv++;
	            	 		cpt++;
	            			}
	           		}
			else       
		   		{
	            		noeudcote_uv[cpt][1] = noeudcote_v[pointv][1] ;					/* LE POINT EN FIL V EST EGAL AU POINT EN FIL U */
	            		noeudcote_uv[cpt][2] = noeudcote_v[pointv][2] ;					/* CAR AUCUN DES DEUX CAS PRECEDENTS */
	            		pointv++;
	            		pointu++;
	            		cpt++;
		   		}
			}
		}
	/* RESTE LES POINTS SOIT DANS NOEUDCOTE_U SOIT DANS NOEUDCOTE_V ( SOIT POINTU = NB_U SOIT POINTV = NB_V EN SORTIE DU TRI) */
	for ( i = pointu ; i <= nb_u ; i++ )
	   	{
	      	if ( ( fabs(noeudcote_u[i][1] - noeudcote_uv[cpt-1][1]) < 0.5*passe) || ( fabs(noeudcote_u[i][1] - ufin) < 0.5*passe ) )
	      		{
	      		}
	      	else
	        	{
	          	noeudcote_uv[cpt][1] = noeudcote_u[i][1] ;
	          	noeudcote_uv[cpt][2] = noeudcote_u[i][2] ;
	          	cpt++;  
	        	}
	     	}
	for ( i = pointv ; i <= nb_v; i++ )
	     	{
	      	if ( ( fabs(noeudcote_v[i][2] - noeudcote_uv[cpt-1][2]) < 0.5*passe) || ( fabs(noeudcote_v[i][2] - vfin) < 0.5*passe ) )
	      		{
	      		}
	      	else
	        	{
	         	noeudcote_uv[cpt][1] = noeudcote_v[i][1] ;
	         	noeudcote_uv[cpt][2] = noeudcote_v[i][2] ;
	         	cpt++;  
	        	}
	     	}

	/* CREATION DES NOEUDS */
	/* ON CONNAIT LE NOMBRE DE NOEUDS A CREER SUR LE COTE (CPT - 1) AINSI QUE SES COORDONNEES FILAIRES U ET V*/
	/* ON INITIALISE DONC TOUT CE QUI DOIT L ETRE POUR CHAQUE NOEUD POSE SUR CE COTE*/
	pan_hexa[pa].suivant_contour[co] = 0 ;
	for (zi = 1; zi <= cpt - 1 ; zi++)
		{
	        Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		pan_hexa[pa].nb_noeud_cote++;
		
		/**********************************************/
  		pan_hexa[pa].noeud_cote = (int *) realloc(pan_hexa[pa].noeud_cote, (1+ pan_hexa[pa].nb_noeud_cote) * sizeof(int));
		if (pan_hexa[pa].noeud_cote    == NULL)
			{
			printf(" pan_hexa[pa].noeud_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		pan_hexa[pa].prop_cote = (float *) realloc(pan_hexa[pa].prop_cote, (1+ pan_hexa[pa].nb_noeud_cote) * sizeof(float));
		if (pan_hexa[pa].prop_cote    == NULL)
			{
			printf(" pan_hexa[pa].prop_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		if (zi ==1)
			{
			pan_hexa[pa].suivant_contour[co] = pan_hexa[pa].nb_noeud_cote;
			}
		pan_hexa[pa].noeud_cote[pan_hexa[pa].nb_noeud_cote] = Structure.nb_total;
		/*LGTENDUE CALCULEE ANTERIEUREMENT EN U ET V PERMET D'OBTENIR LA POSITION RELATIVE DU NOEUD / AUX EXTREMITES  */
		pan_hexa[pa].prop_cote[pan_hexa[pa].nb_noeud_cote] = sqrt (  ( noeudcote_uv[zi][1] - udeb ) * ( noeudcote_uv[zi][1] - udeb )
									 + ( noeudcote_uv[zi][2] - vdeb ) * ( noeudcote_uv[zi][2] - vdeb ) ) 
								   / lg_tendue ; 
		noeud[Structure.nb_total].u = noeudcote_uv[zi][1] ;
		noeud[Structure.nb_total].v = noeudcote_uv[zi][2] ;
		noeud[Structure.nb_total].x = xdeb + pan_hexa[pa].prop_cote[pan_hexa[pa].nb_noeud_cote] * (xfin-xdeb) ;
		noeud[Structure.nb_total].y = ydeb + pan_hexa[pa].prop_cote[pan_hexa[pa].nb_noeud_cote] * (yfin-ydeb) ;
		noeud[Structure.nb_total].z = zdeb + pan_hexa[pa].prop_cote[pan_hexa[pa].nb_noeud_cote] * (zfin-zdeb) ;
		noeud[Structure.nb_total].type = pan_hexa[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].U = 0.5 * ( noeud[Structure.nb_total].u - noeud[Structure.nb_total].v ) ;
		noeud[Structure.nb_total].V = 0.5 * ( noeud[Structure.nb_total].u + noeud[Structure.nb_total].v ) ;
		}
	}
	
void mail_hexa_contour_pan_hexa2(int pa, int co, int cp,int pa2,int nlo1,int nlo2)
	{
	/*PA = NO DU PANNEAU, CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE*/
	/*PA2 = NO DU 2EM PANNEAU, NLO1 = DEBUT DU COTE, NLO2 : FIN DU COTE DANS LA NUMEROTATION LOCALE*/
	int    zi, nb_coupe, deb, fin, premier_cote, sens_cote, nb_lai, premier_loc, nlo3 ;
	float  xdeb, xfin, ydeb, yfin, zdeb, zfin, ss ;
	
	deb  = pan_hexa[pa2].noeud_contour[nlo1];
	fin  = pan_hexa[pa2].noeud_contour[nlo2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	
	/*CALCUL DE NB_COUPE*/
	if (nlo1 + 1 == nlo2)
		{
		if(pan_hexa[pa2].suivant_contour[nlo1] == 0)
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
			while ((pan_hexa[pa2].suivant_contour[nlo3] == 0) && (nlo3 != pan_hexa[pa2].nb_noeud_contour));
			if (pan_hexa[pa2].suivant_contour[nlo3] != 0)
				{
				nb_coupe = pan_hexa[pa2].suivant_contour[nlo3] - pan_hexa[pa2].suivant_contour[nlo1] + 1;
				}
			else
				{
				nb_coupe = pan_hexa[pa2].nb_noeud_cote - pan_hexa[pa2].suivant_contour[nlo1] + 2;
				}
			}
		}
	if (nlo1 - 1 == nlo2)
		{
		if(pan_hexa[pa2].suivant_contour[nlo2] == 0)
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
			while ((pan_hexa[pa2].suivant_contour[nlo3] == 0) && (nlo3 != pan_hexa[pa2].nb_noeud_contour));
			if (pan_hexa[pa2].suivant_contour[nlo3] != 0)
				{
				nb_coupe = pan_hexa[pa2].suivant_contour[nlo3] - pan_hexa[pa2].suivant_contour[nlo2] + 1;
				}
			else
				{
				nb_coupe = pan_hexa[pa2].nb_noeud_cote - pan_hexa[pa2].suivant_contour[nlo2] + 2;
				}
			}
		}
	if ((nlo1 - 1 != nlo2) && (nlo1 + 1 != nlo2))
		{
		/*DANS CE CAS NLO1 ET NLO2 SONT 1 ET PANNEAU[PA2].NB_NOEUD_CONTOUR OU INVERSEMENT*/
		if(pan_hexa[pa2].suivant_contour[pan_hexa[pa2].nb_noeud_contour] == 0)
			{
			/*PAS DE POINT DE COTE SUR CE SEGMENT DE CONTOUR*/
			nb_coupe = 1;
			}
		else
			{
			nb_coupe = pan_hexa[pa2].nb_noeud_cote - pan_hexa[pa2].suivant_contour[pan_hexa[pa2].nb_noeud_contour] + 2;
			}
		}
	
	deb  = pan_hexa[pa].noeud_contour[co];
	fin  = pan_hexa[pa].noeud_contour[cp];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	
	if((nlo1 == nlo2-1) || ((nlo1 == pan_hexa[pa2].nb_noeud_contour) && (nlo2 == 1)))
		{
		premier_loc = pan_hexa[pa2].suivant_contour[nlo1];
		premier_cote = pan_hexa[pa2].noeud_cote[pan_hexa[pa2].suivant_contour[nlo1]];
		sens_cote = +1;
		}
	if((nlo2 == nlo1-1) || ((nlo2 == pan_hexa[pa2].nb_noeud_contour) && (nlo1 == 1)))
		{
		premier_loc = pan_hexa[pa2].suivant_contour[nlo2] + nb_coupe - 2;
		premier_cote = pan_hexa[pa2].noeud_cote[pan_hexa[pa2].suivant_contour[nlo2]] + nb_coupe - 2;
		sens_cote = -1;
		}
	
	pan_hexa[pa].suivant_contour[co] = 0 ;
	for ( zi = 1 ; zi <= nb_coupe -1 ; zi++ )
		{
		Structure.nb_total++;
		if (Structure.nb_total >= NBMAXNOEUD)
			{
			printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
			exit(0);
			}
		pan_hexa[pa].nb_noeud_cote++;
		
		/**********************************************/
  		pan_hexa[pa].noeud_cote = (int *) realloc(pan_hexa[pa].noeud_cote, (1 + pan_hexa[pa].nb_noeud_cote) * sizeof(int));
		if (pan_hexa[pa].noeud_cote    == NULL)
			{
			printf(" pan_hexa[pa].noeud_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
  		pan_hexa[pa].prop_cote = (float *) realloc(pan_hexa[pa].prop_cote, (1 + pan_hexa[pa].nb_noeud_cote) * sizeof(float));
		if (pan_hexa[pa].prop_cote    == NULL)
			{
			printf(" pan_hexa[pa].prop_cote 2 = NULL  \n" );
			exit(0);
			}
		/**********************************************/
		if (zi ==1)
			{
			pan_hexa[pa].suivant_contour[co] = pan_hexa[pa].nb_noeud_cote;
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
			Lien[Structure.nb_lien].type[1] = 'h';
			Lien[Structure.nb_lien].type[2] = 'h';
			Lien[Structure.nb_lien].structure[1] = pa2;
			Lien[Structure.nb_lien].structure[2] = pa ;
			Lien[Structure.nb_lien].extremite[1] = premier_loc + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].extremite[2] = pan_hexa[pa].nb_noeud_cote;
			Lien[Structure.nb_lien].noeud[1] = premier_cote + sens_cote * (zi - 1);
			Lien[Structure.nb_lien].noeud[2] = Structure.nb_total;
			}
		if (nb_lai != 0)
			{		
			Lien[nb_lai].nb_liaison++;
			Lien[nb_lai].type     [Lien[nb_lai].nb_liaison] = 'h';
			Lien[nb_lai].structure[Lien[nb_lai].nb_liaison] = pa;
			Lien[nb_lai].extremite[Lien[nb_lai].nb_liaison] = pan_hexa[pa].nb_noeud_cote;
			Lien[nb_lai].noeud    [Lien[nb_lai].nb_liaison] = Structure.nb_total;
			}
		/* SS PERMET D ETABLIR LA CORRESPONDANCE DES PROPORTIONS DE NOEUDS LIES SANS CONSIDERER DE IF...ELSE... 
		   NECESSAIRE POUR LE CAS OU LES COTES EN JEU NE SONT PAS 1MAILLES DANS LE MEME SENS!
		   SS VAUT 1. SI LES SENS DE MAILLAGE SONT OPPOSES , 0. SINON*/
		ss = (float) 0.5 * fabs(sens_cote - 1.);
		pan_hexa[pa].noeud_cote[pan_hexa[pa].nb_noeud_cote] = Structure.nb_total;
		pan_hexa[pa].prop_cote[pan_hexa[pa].nb_noeud_cote] = ss + sens_cote*pan_hexa[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)];
		noeud[Structure.nb_total].x = xdeb + (ss + sens_cote*pan_hexa[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (xfin-xdeb) ;
		noeud[Structure.nb_total].y = ydeb + (ss + sens_cote*pan_hexa[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (yfin-ydeb) ;
		noeud[Structure.nb_total].z = zdeb + (ss + sens_cote*pan_hexa[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (zfin-zdeb) ;
		noeud[Structure.nb_total].U = noeud[deb].U + (ss + sens_cote*pan_hexa[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (noeud[fin].U-noeud[deb].U) ;
		noeud[Structure.nb_total].V = noeud[deb].V + (ss + sens_cote*pan_hexa[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (noeud[fin].V-noeud[deb].V) ;
		noeud[Structure.nb_total].type = pan_hexa[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].u = noeud[Structure.nb_total].U + noeud[Structure.nb_total].V ; 
		noeud[Structure.nb_total].v = noeud[Structure.nb_total].V - noeud[Structure.nb_total].U ; 
		}
	}

int interieur_pan_hexa_filaire(float UU, float VV, int no_pa)
	{
	float  S, S_ref, U1, U2, U3, V1, V2, V3 ;
	int    trouve, sommet_1, sommet_2, sommet_3, no_tri ;
	
	/*RECHERCHE SI LE NOEUD DE COORDONNEES FILAIRE UU ET VV EST A L INTERIEUR DU CONTOUR  DU PANNEAU NO_PA
	SI A L INTERIEUR DU CONTOUR RETURN = NUMERO DU TRIANGLE CONTOUR OU EST SITUE LE POINT
	SI A L EXTERIEUR DU CONTOUR RETURN = 0
	*/
	trouve = 0;	/*LE TRIANGLE OU EST LE NOEUD N EST PAS TROUVE POUR L INSTANT*/

	for (no_tri=1;no_tri<=pan_hexa[no_pa].nb_tri_hexa_contour;no_tri++)
		{
		sommet_1 = pan_hexa[no_pa].noeud_contour[pan_hexa[no_pa].tri_hexa_contour[no_tri][1]];
		sommet_2 = pan_hexa[no_pa].noeud_contour[pan_hexa[no_pa].tri_hexa_contour[no_tri][2]];
		sommet_3 = pan_hexa[no_pa].noeud_contour[pan_hexa[no_pa].tri_hexa_contour[no_tri][3]];
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
		if ((S / S_ref > 0.999) && (S / S_ref < 1.001))
			{
			/*LE NOEUD Structure.NB_TOTAL EST A L INTERIEUR DU CONTOUR*/
			trouve = no_tri;
			break;
			}
		}
	return trouve;
	}
	
	
int proche_contour_filaire_hexa(float UU, float VV, int no_pa, float fact,double longueur_repos)
	{
	float  S, U1, U2, U3, V1, V2, V3, A, B, C, p, ha, ac, ab ,s2;
	int    trouve, no, deb, fin ;
	
	/*RECHERCHE DES NOEUDS TROP PROCHE DES SEGMENTS DU CONTOUR DU PANNEAU NO_PA
	SI TROP PROCHE DU CONTOUR TROUVE = 0
	SI LOIN DU CONTOUR TROUVE = 1
	LA RECHERCHE SE FAIT SUR LES COORDONNEES FILAIRES DES NOEUDS*/
	trouve = 1;
	for (no=1;no<=pan_hexa[no_pa].nb_noeud_contour;no++)
		{
		deb = pan_hexa[no_pa].noeud_contour[no];
		if (no != pan_hexa[no_pa].nb_noeud_contour) fin = pan_hexa[no_pa].noeud_contour[no + 1];
		if (no == pan_hexa[no_pa].nb_noeud_contour) fin = pan_hexa[no_pa].noeud_contour[1];
		
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
    		/*S = sqrt(p*(p-A)*(p-B)*(p-C));*/
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
			if (ha < pan_hexa[no_pa].pas_maillage / longueur_repos * fact)
				{
				trouve = 0;
				break;
				}
			}
		}
	return trouve;
	}
	
	
int proche_pan_hexa_filaire(float UU, float VV, int no_pa, float fact,double longueur_repos)
	{
	float  U1, V1, distance ;
	int    trouve, no, deb;
	
	/*
	RECHERCHE DES NOEUDS TROP PROCHE DES NOEUDS DU CONTOUR DU PANNEAU NO_PA
	SI TROP PROCHE DU CONTOUR TROUVE = 0
	SI LOIN DU CONTOUR TROUVE = 1
	*/
	trouve = 1;
	for (no=1;no<=pan_hexa[no_pa].nb_noeud_contour;no++)
		{
		deb = pan_hexa[no_pa].noeud_contour[no];
		
		/*COORDONNEES DU NOEUD DU CONTOUR TRAITE*/
		U1 = noeud[deb].u;
		V1 = noeud[deb].v;
				
		/*DISTANCE ENTRE LES POINTS*/
		distance = sqrt((U1-UU) * (U1-UU) + (V1-VV) * (V1-VV));
		
		/*RECHERCHE SI LA DISTANCE  EST INFERIEUR AU PAS_MAILLAGE * FACT DANS CE CAS LE NOEUD 
		EST TROP PROCHE DU CONTOUR*/
		if (distance < pan_hexa[no_pa].pas_maillage / longueur_repos * fact)
			{
			trouve = 0;
			break;
			}
		}
	return trouve;
	}
	
	
void maillage_pan_hexa_en_element(int pa)
	{
	int    um,vm,zi, nb_coupe, deb, fin, zu , zv, pre, sec, tro,minu,maxu,minv,maxv;
	float  xdeb, xfin, ydeb, yfin, zdeb, zfin ;
	float u1,u2,u3,v1,v2,v3,x1,x2,x3,y1,y2,y3,z1,z2,z3,denom,ru,rv,alpha,beta;
	float xm,ym,zm,vect_ux,vect_vx,vect_uy,vect_vy,vect_uz,vect_vz;
	float a1,a2,b1,b2,c1;
	
	/*
	int no_triangle,no_tri_hexa,cote,deb,fin,deb_total,fin_total,no_pa;
	int inside,inside1,inside2,int_temp;
	float xd,yd;
	*/
	
	if (pan_hexa[pa].nb_noeud_contour != 4)
		{
		printf(" Ce type de maillage %d ne convient que pour les contours a 4 noeuds\n",pan_hexa[pa].type_maillage);
		exit(0);
		}
	
	pre = pan_hexa[pa].noeud_contour[1];
	sec = pan_hexa[pa].noeud_contour[2];
	tro = pan_hexa[pa].noeud_contour[3];
		
	u1 = (float) noeud[pre].U;	v1 = (float) noeud[pre].V;
	u2 = (float) noeud[sec].U;	v2 = (float) noeud[sec].V;
	u3 = (float) noeud[tro].U;	v3 = (float) noeud[tro].V;
	
	x1 = noeud[pre].x;	y1 = noeud[pre].y;	z1 = noeud[pre].z;
	x2 = noeud[sec].x;	y2 = noeud[sec].y;	z2 = noeud[sec].z;
	x3 = noeud[tro].x;	y3 = noeud[tro].y;	z3 = noeud[tro].z;
		
	denom = (u3-u1)*(v2-v1) - (u2-u1)*(v3-v1);
	
	/* precautions en cas de denominateur nul*/
	if (fabs(denom) <= 0.00001)
	       	{
		printf(" denom = 0\n");
		exit(0);
	       	} 
	
       	/*calcul des vecteur elementaires cartesiens de cote de maille vect_u et vect_v*/

       	ru = u1+1.0;
       	rv = v1+0.0;

       	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
       	beta  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;
	     	
      	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
      	vect_ux = alpha * ( x2 - x1 )+ beta * ( x3 - x1 );
      	vect_uy = alpha * ( y2 - y1 )+ beta * ( y3 - y1 );
      	vect_uz = alpha * ( z2 - z1 )+ beta * ( z3 - z1 );

     	ru = u1+0.0;
     	rv = v1+1.0;

     	alpha =   ( (rv-v1)*(u3-u1) - (ru-u1)*(v3-v1) ) / denom;
     	beta  =   ( (ru-u1)*(v2-v1) - (rv-v1)*(u2-u1) ) / denom;

     	/* determination des coordonnees cartesiennes du sommet courant proche d une position d equilibre */
     	vect_vx = alpha * ( x2 - x1 )+ beta * ( x3 - x1 );
     	vect_vy = alpha * ( y2 - y1 )+ beta * ( y3 - y1 );
     	vect_vz = alpha * ( z2 - z1 )+ beta * ( z3 - z1 );

	minu = (int) floor(u1);		maxu = (int) ceil(u1);
	minv = (int) floor(v1);		maxv = (int) ceil(v1);
	
       	if (minu>u2) minu = (int) floor(u2);  if (maxu<u2) maxu = (int) ceil(u2);
       	if (minu>u3) minu = (int) floor(u3);  if (maxu<u3) maxu = (int) ceil(u3);
       	if (minv>v2) minv = (int) floor(v2);  if (maxv<v2) maxv = (int) ceil(v2);
       	if (minv>v3) minv = (int) floor(v3);  if (maxv<v3) maxv = (int) ceil(v3);
      	printf("minu= %d, maxu = %d   ",minu,maxu);
      	printf("minv= %d, maxv = %d \n",minv,maxv);
	
   	/*creation des barres*/
       	for (um=minu;um<maxu;um++)
               	{ 
               	for (vm=minv;vm<maxv;vm++)
        	       	{
        	       	/*printf("um   : %8d ,vm  :  %8d ",um,vm);*/
        	       	/* determination des coefficients alpha et beta definis tels que 1m = alpha*12 + beta*13 */
        	       	alpha =   ( (vm-v1)*(u3-u1) - (um-u1)*(v3-v1) ) / denom;
        	       	beta  =   ( (um-u1)*(v2-v1) - (vm-v1)*(u2-u1) ) / denom;
        	       	/*printf("alpha= %f,beta = %f ",alpha,beta);*/
        	      
        	       	/* determination des coordonnees cartesiennes de l origine de la maille proche d une position d equilibre */
        	       	xm = alpha * ( x2 - x1 )+ beta * ( x3 - x1 ) + x1;
        	       	ym = alpha * ( y2 - y1 )+ beta * ( y3 - y1 ) + y1;			       
        	       	zm = alpha * ( z2 - z1 )+ beta * ( z3 - z1 ) + z1;
        	       	
        	       	
        	       	if ((um!=minu) || (vm!=minv))
        	       		{
        	       		a1 = xm +vect_ux*0.0/6.0 +vect_vx*0.0/2.0;
        	       		b1 = ym +vect_uy*0.0/6.0 +vect_vy*0.0/2.0;
        	       		c1 = zm +vect_uz*0.0/6.0 +vect_vz*0.0/2.0;
				Structure.nb_total++;
				noeud[Structure.nb_total].x = a1;
				noeud[Structure.nb_total].y = b1;
				noeud[Structure.nb_total].z = c1;
				noeud[Structure.nb_total].type = pan_hexa[pa].type_noeud;
				if ((um==minu) || (vm==minv))	noeud[Structure.nb_total].type = 1;

        	       		}			       
        	       
        	       	if ((um==maxu-1) && (vm!=minv))
        	       		{
        	       		a1 = xm +vect_ux*6.0/6.0 +vect_vx*0.0/2.0;
        	       		b1 = ym +vect_uy*6.0/6.0 +vect_vy*0.0/2.0;
        	       		c1 = zm +vect_uz*6.0/6.0 +vect_vz*0.0/2.0;
				Structure.nb_total++;
				noeud[Structure.nb_total].x = a1;
				noeud[Structure.nb_total].y = b1;
				noeud[Structure.nb_total].z = c1;
				noeud[Structure.nb_total].type = 1;
        	       		}			       
        	       
        	       	if ((um!=minu) && (vm==maxv-1))
        	       		{
        	       		a1 = xm +vect_ux*0.0/6.0 +vect_vx*2.0/2.0;
        	       		b1 = ym +vect_uy*0.0/6.0 +vect_vy*2.0/2.0;
        	       		c1 = zm +vect_uz*0.0/6.0 +vect_vz*2.0/2.0;
				Structure.nb_total++;
				noeud[Structure.nb_total].x = a1;
				noeud[Structure.nb_total].y = b1;
				noeud[Structure.nb_total].z = c1;
				noeud[Structure.nb_total].type = 1;
        	       		}			       
        	       
        	       	a1 = xm +vect_ux*1.0/6.0 +vect_vx*1.0/2.0;
        	       	b1 = ym +vect_uy*1.0/6.0 +vect_vy*1.0/2.0;
        	       	c1 = zm +vect_uz*1.0/6.0 +vect_vz*1.0/2.0;
			Structure.nb_total++;
			noeud[Structure.nb_total].x = a1;
			noeud[Structure.nb_total].y = b1;
			noeud[Structure.nb_total].z = c1;
			noeud[Structure.nb_total].type = pan_hexa[pa].type_noeud;
        	       
        	       	a1 = xm +vect_ux*3.0/6.0 +vect_vx*1.0/2.0;
        	       	b1 = ym +vect_uy*3.0/6.0 +vect_vy*1.0/2.0;
        	       	c1 = zm +vect_uz*3.0/6.0 +vect_vz*1.0/2.0;
			Structure.nb_total++;
			noeud[Structure.nb_total].x = a1;
			noeud[Structure.nb_total].y = b1;
			noeud[Structure.nb_total].z = c1;
			noeud[Structure.nb_total].type = pan_hexa[pa].type_noeud;
        	       
        	       	a1 = xm +vect_ux*4.0/6.0 +vect_vx*0.0/2.0;
        	       	b1 = ym +vect_uy*4.0/6.0 +vect_vy*0.0/2.0;
        	       	c1 = zm +vect_uz*4.0/6.0 +vect_vz*0.0/2.0;
			Structure.nb_total++;
			noeud[Structure.nb_total].x = a1;
			noeud[Structure.nb_total].y = b1;
			noeud[Structure.nb_total].z = c1;
			noeud[Structure.nb_total].type = pan_hexa[pa].type_noeud;
			if (vm==minv)	noeud[Structure.nb_total].type = 1;
			
        	       	if (vm==maxv-1)
        	       		{
        	       		a1 = xm +vect_ux*4.0/6.0 +vect_vx*2.0/2.0;
        	       		b1 = ym +vect_uy*4.0/6.0 +vect_vy*2.0/2.0;
        	       		c1 = zm +vect_uz*4.0/6.0 +vect_vz*2.0/2.0;
				Structure.nb_total++;
				noeud[Structure.nb_total].x = a1;
				noeud[Structure.nb_total].y = b1;
				noeud[Structure.nb_total].z = c1;
				noeud[Structure.nb_total].type = 1;
        	       		}			       
        	       
        	       	}
               	}
	if (Structure.nb_total >= NBMAXNOEUD)
		{
		printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
		exit(0);
		}
	tri();      	
               	
   	/*creation des barres*/
       	for (um=minu;um<maxu;um++)
               	{ 
               	for (vm=minv;vm<maxv;vm++)
        	       	{
        	       	/*fils l*/
			Structure.nb_barre++;
        	       	barre[Structure.nb_barre].noeud[1] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 1 + 0 * (maxv - minv)];
        	       	barre[Structure.nb_barre].noeud[2] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 1 * (maxv - minv)];
			barre[Structure.nb_barre].type = 1;
			barre[Structure.nb_barre].netting2ropes_panel = 0;
			barre[Structure.nb_barre].pro[1] = 0.0 ;
			barre[Structure.nb_barre].pro[2] = 1.0 ;
			barre[Structure.nb_barre].longueur_repos = pan_hexa[pa].lo_repos ;
			
			Structure.nb_barre++;
        	       	barre[Structure.nb_barre].noeud[1] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 2 * (maxv - minv)];
        	       	barre[Structure.nb_barre].noeud[2] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 3 + 3 * (maxv - minv)];
			barre[Structure.nb_barre].type = 1;
			barre[Structure.nb_barre].netting2ropes_panel = 0;
			barre[Structure.nb_barre].pro[1] = 0.0 ;
			barre[Structure.nb_barre].pro[2] = 1.0 ;
			barre[Structure.nb_barre].longueur_repos = pan_hexa[pa].lo_repos ;
        	       	}
               	}
       	for (um=minu;um<maxu;um++)
               	{ 
               	for (vm=minv;vm<maxv;vm++)
        	       	{
        	       	/*fils n*/
			Structure.nb_barre++;
        	       	barre[Structure.nb_barre].noeud[1] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 1 * (maxv - minv)];
        	       	barre[Structure.nb_barre].noeud[2] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 0 * (maxv - minv)];
			barre[Structure.nb_barre].type = 3;
			barre[Structure.nb_barre].netting2ropes_panel = 0;
			barre[Structure.nb_barre].pro[1] = 0.0 ;
			barre[Structure.nb_barre].pro[2] = 1.0 ;
			barre[Structure.nb_barre].longueur_repos = pan_hexa[pa].no_repos ;

			Structure.nb_barre++;
        	       	barre[Structure.nb_barre].noeud[1] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 2 * (maxv - minv)];
        	       	barre[Structure.nb_barre].noeud[2] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 3 * (maxv - minv)];
			barre[Structure.nb_barre].type = 3;
			barre[Structure.nb_barre].netting2ropes_panel = 0;
			barre[Structure.nb_barre].pro[1] = 0.0 ;
			barre[Structure.nb_barre].pro[2] = 1.0 ;
			barre[Structure.nb_barre].longueur_repos = pan_hexa[pa].no_repos ;
        	       	}
               	}
       	for (um=minu;um<maxu;um++)
               	{ 
               	for (vm=minv;vm<maxv;vm++)
        	       	{
        	       	/*fils m*/
			Structure.nb_barre++;
        	       	barre[Structure.nb_barre].noeud[1] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 1 * (maxv - minv)];
        	       	barre[Structure.nb_barre].noeud[2] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 2 * (maxv - minv)];
			barre[Structure.nb_barre].type = 2;
			barre[Structure.nb_barre].netting2ropes_panel = 0;
			barre[Structure.nb_barre].pro[1] = 0.0 ;
			barre[Structure.nb_barre].pro[2] = 1.0 ;
			barre[Structure.nb_barre].longueur_repos = pan_hexa[pa].mo_repos ;
        	       	}
               	}
       	for (um=minu;um<maxu;um++)
               	{ 
               	for (vm=minv;vm<=maxv-1;vm++)
        	       	{
        	       	/*fils m*/
			Structure.nb_barre++;
        	       	barre[Structure.nb_barre].noeud[1] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 3 * (maxv - minv)];
        	       	barre[Structure.nb_barre].noeud[2] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 3 + 4 * (maxv - minv)];
			barre[Structure.nb_barre].type = 2;
			barre[Structure.nb_barre].netting2ropes_panel = 0;
			barre[Structure.nb_barre].pro[1] = 0.0 ;
			barre[Structure.nb_barre].pro[2] = 1.0 ;
			barre[Structure.nb_barre].longueur_repos = pan_hexa[pa].mo_repos ;
        	       	}
               	}
       	for (um=minu;um<maxu;um++)
               	{ 
               	for (vm=maxv;vm<=maxv;vm++)
        	       	{
        	       	/*fils m
			Structure.nb_barre++;
        	       	barre[Structure.nb_barre].noeud[1] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 2 + 3 * (maxv - minv)];
        	       	barre[Structure.nb_barre].noeud[2] = profondeur[um * ((maxv-minv) * 4 + 2) + vm + 3 + 4 * (maxv - minv)];
			barre[Structure.nb_barre].type = 2;
			barre[Structure.nb_barre].netting2ropes_panel = 0;
			barre[Structure.nb_barre].pro[1] = 0.0 ;
			barre[Structure.nb_barre].pro[2] = 1.0 ;
			barre[Structure.nb_barre].longueur_repos = pan_hexa[pa].mo_repos ;*/
        	       	}
               	}
	printf(" Structure.nb_barre = %4d \n",Structure.nb_barre );
	if ( Structure.nb_barre>= NBMAXBARRE)
		{
		printf(" NBMAXBARRE trop petit %4d < %4d \n",NBMAXBARRE,Structure.nb_barre );
		exit(0);
		}
	/*TypeBarre[1].raideur_traction = 	pan_hexa[pa].raideur_traction_l;
	TypeBarre[1].raideur_compression = 	pan_hexa[pa].raideur_compression_l;
	TypeBarre[1].longueur_repos = 		pan_hexa[pa].lo_repos;
	TypeBarre[1].diam_hydro = 		pan_hexa[pa].diam_hydro_l;
	TypeBarre[1].rho = 			pan_hexa[pa].rho;
	TypeBarre[1].cdnormal = 		pan_hexa[pa].cdnormal;
	TypeBarre[1].ftangent = 		pan_hexa[pa].ftangent;

	TypeBarre[2].raideur_traction = 	pan_hexa[pa].raideur_traction_m;
	TypeBarre[2].raideur_compression = 	pan_hexa[pa].raideur_compression_m;
	TypeBarre[2].longueur_repos = 		pan_hexa[pa].mo_repos;
	TypeBarre[2].diam_hydro = 		pan_hexa[pa].diam_hydro_m;
	TypeBarre[2].rho = 			pan_hexa[pa].rho;
	TypeBarre[2].cdnormal = 		pan_hexa[pa].cdnormal;
	TypeBarre[2].ftangent = 		pan_hexa[pa].ftangent;

	TypeBarre[3].raideur_traction = 	pan_hexa[pa].raideur_traction_n;
	TypeBarre[3].raideur_compression = 	pan_hexa[pa].raideur_compression_n;
	TypeBarre[3].longueur_repos = 		pan_hexa[pa].no_repos;
	TypeBarre[3].diam_hydro = 		pan_hexa[pa].diam_hydro_n;
	TypeBarre[3].rho = 			pan_hexa[pa].rho;
	TypeBarre[3].cdnormal = 		pan_hexa[pa].cdnormal;
	TypeBarre[3].ftangent = 		pan_hexa[pa].ftangent;*/
	}
	
