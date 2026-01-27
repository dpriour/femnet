#define PRINCIPAL 0
#include "phobos.h"

void filet_interne()
	{
	/*defini les triangles poses sur le contour, 
	calcule les coordonnees en nb de mailles des sommets des triangles. */
	int pa,col,mode;
	col=GetRGBColor(255,0,0);
	
	if (Structure.graphic == 1)
		{
		/*faire le maillage_coulisse si ce n est pas fait*/
		mode = GetMenuItemChecked(w[72]);
		if (mode == 0) maillage();
	
		if (col==-1) printf("Erreur de couleur \n");
		SetColor(col);
		}
	initialisation_par_default();
	for (pa=1;pa<=Structure.NbTypesurf;pa++)
		{ 
		if (panneau[pa].flag_filet == 0)
			{
			initialisation_par_default();
			if (panneau[pa].type_maillage != 4) 	initialisation_triangulation_interne(pa);
			initialisation_segment_interne(pa);
			if (panneau[pa].type_maillage != 4) 	triangulate("pQ",&in,&out,&vorout);
			/*Q pour quiet : sans commentaire*/
			if (panneau[pa].type_maillage != 4) 	mise_a_jour_triangulation_interne(pa);
			panneau[pa].flag_filet = 1;
			}
		}
	for (pa=1;pa<=Structure.NbTypesurf_hexa;pa++)
		{ 
		if (pan_hexa[pa].flag_filet == 0)
			{
			initialisation_par_default();
			initialisation_triangulation_interne_hexa(pa);
			initialisation_segment_interne_hexa(pa);
			triangulate("pQ",&in,&out,&vorout);
			/*Q pour quiet : sans commentaire*/
			mise_a_jour_triangulation_interne_hexa(pa);
			pan_hexa[pa].flag_filet = 1;
			}
		}
	liberer();
	inversions_des_triangles();
	if (Structure.graphic == 1)
		{
		SetMenuItemChecked(w[27],1);
		}
	}


void initialisation_par_default()
	{
	/*initialisation par defaut de in out et vorout*/
	in.pointlist 			= (REAL *) NULL;
	in.pointattributelist 		= (REAL *) NULL;
	in.pointmarkerlist 		= (int  *) NULL;
	in.trianglelist 		= (int  *) NULL;
	in.triangleattributelist 	= (REAL *) NULL;
	in.trianglearealist 		= (REAL *) NULL;
	in.neighborlist 		= (int  *) NULL;
	in.segmentlist	 		= (int  *) NULL;
	in.segmentmarkerlist	 	= (int  *) NULL;
	in.holelist	 		= (REAL *) NULL;
	in.regionlist	 		= (REAL *) NULL;
	in.edgelist		 	= (int  *) NULL;
	in.edgemarkerlist		= (int  *) NULL;
	in.normlist	 		= (REAL *) NULL;
	out.pointlist 			= (REAL *) NULL;
	out.pointattributelist 		= (REAL *) NULL;
	out.pointmarkerlist 		= (int  *) NULL;
	out.trianglelist 		= (int  *) NULL;
	out.triangleattributelist 	= (REAL *) NULL;
	out.trianglearealist 		= (REAL *) NULL;
	out.neighborlist 		= (int  *) NULL;
	out.segmentlist	 		= (int  *) NULL;
	out.segmentmarkerlist	 	= (int  *) NULL;
	out.holelist	 		= (REAL *) NULL;
	out.regionlist	 		= (REAL *) NULL;
	out.edgelist		 	= (int  *) NULL;
	out.edgemarkerlist		= (int  *) NULL;
	out.normlist	 		= (REAL *) NULL;
	vorout.pointlist 		= (REAL *) NULL;
	vorout.pointattributelist 	= (REAL *) NULL;
	vorout.pointmarkerlist 		= (int  *) NULL;
	vorout.trianglelist 		= (int  *) NULL;
	vorout.triangleattributelist 	= (REAL *) NULL;
	vorout.trianglearealist 	= (REAL *) NULL;
	vorout.neighborlist 		= (int  *) NULL;
	vorout.segmentlist	 	= (int  *) NULL;
	vorout.segmentmarkerlist	= (int  *) NULL;
	vorout.holelist	 		= (REAL *) NULL;
	vorout.regionlist	 	= (REAL *) NULL;
	vorout.edgelist		 	= (int  *) NULL;
	vorout.edgemarkerlist		= (int  *) NULL;
	vorout.normlist	 		= (REAL *) NULL;
	}

void initialisation_triangulation_interne(int pa)
	{
	/*defini les triangles poses sur les points interieurs du contour et des cotes*/
	int deb,no,nb_point;

	in.numberofpoints = panneau[pa].nb_noeud_interieur + panneau[pa].nb_noeud_contour + panneau[pa].nb_noeud_cote;
  	in.pointlist = (REAL *) malloc( in.numberofpoints * 2 * sizeof(REAL));
	if ( in.pointlist   == NULL)
		{
		printf(" in.pointlist  = NULL  \n" );
		exit(0);
		}
	in.pointmarkerlist 	= (int 		*) NULL;
	
	/*initialisation des points*/
	/*on commence par les points des coins*/
	nb_point = 0;
	for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
		{ 
		deb = panneau[pa].noeud_contour[no];
		in.pointlist[2*no-2 + 2*nb_point] = noeud[deb].u;
		in.pointlist[2*no-1 + 2*nb_point] = noeud[deb].v;
		/*
		printf("point %d   ", no);
		printf("u %lf  v %lf  \n", in.pointlist[2*no-2 + 2*nb_point],in.pointlist[2*no-1 + 2*nb_point]);
		*/
		}
		
	/*on continue avec les points sur les cotes*/
	nb_point = panneau[pa].nb_noeud_contour;
	for (no=1;no<=panneau[pa].nb_noeud_cote;no++)
		{ 
		deb = panneau[pa].noeud_cote[no];
		in.pointlist[2*no-2 + 2*nb_point] = noeud[deb].u;
		in.pointlist[2*no-1 + 2*nb_point] = noeud[deb].v;
		/*
		printf("point %d   ", no);
		printf("u %lf  v %lf  \n", in.pointlist[2*no-2 + 2*nb_point],in.pointlist[2*no-1 + 2*nb_point]);
		*/
		}
		
	/*on termine avec les points interieurs*/
	nb_point = panneau[pa].nb_noeud_contour + panneau[pa].nb_noeud_cote;
	for (no=1;no<=panneau[pa].nb_noeud_interieur;no++)
		{ 
		deb = panneau[pa].noeud_interieur[no];
		in.pointlist[2*no-2 + 2*nb_point] = noeud[deb].u;
		in.pointlist[2*no-1 + 2*nb_point] = noeud[deb].v;
		/*
		printf("point %d   ", no);
		printf("u %lf  v %lf  \n", in.pointlist[2*no-2 + 2*nb_point],in.pointlist[2*no-1 + 2*nb_point]);
		*/
		}
	}
	
void initialisation_triangulation_interne_hexa(int pa)
	{
	/*defini les triangles poses sur les points interieurs du contour et des cotes*/
	int deb,no,nb_point;

	in.numberofpoints = pan_hexa[pa].nb_noeud_interieur + pan_hexa[pa].nb_noeud_contour + pan_hexa[pa].nb_noeud_cote;
  	in.pointlist = (REAL *) malloc( in.numberofpoints * 2 * sizeof(REAL));
	if ( in.pointlist   == NULL)
		{
		printf(" in.pointlist  = NULL  \n" );
		exit(0);
		}
	in.pointmarkerlist 	= (int 		*) NULL;
	
	/*initialisation des points*/
	/*on commence par les points des coins*/
	nb_point = 0;
	for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
		{ 
		deb = pan_hexa[pa].noeud_contour[no];
		in.pointlist[2*no-2 + 2*nb_point] = noeud[deb].u;
		in.pointlist[2*no-1 + 2*nb_point] = noeud[deb].v;
		}
		
	/*on continue avec les points sur les cotes*/
	nb_point = pan_hexa[pa].nb_noeud_contour;
	for (no=1;no<=pan_hexa[pa].nb_noeud_cote;no++)
		{ 
		deb = pan_hexa[pa].noeud_cote[no];
		in.pointlist[2*no-2 + 2*nb_point] = noeud[deb].u;
		in.pointlist[2*no-1 + 2*nb_point] = noeud[deb].v;
		}
		
	/*on termine avec les points interieurs*/
	nb_point = pan_hexa[pa].nb_noeud_contour + pan_hexa[pa].nb_noeud_cote;
	for (no=1;no<=pan_hexa[pa].nb_noeud_interieur;no++)
		{ 
		deb = pan_hexa[pa].noeud_interieur[no];
		in.pointlist[2*no-2 + 2*nb_point] = noeud[deb].u;
		in.pointlist[2*no-1 + 2*nb_point] = noeud[deb].v;
		}
	}


void initialisation_segment_interne(int pa)
	{
	/*defini les triangles poses sur les points interieurs du contour et des cotes*/
	int deb,no,fin,co,nb_segment,numero_segment;
 
 	/*initialisation des segments*/
	in.numberofsegments = panneau[pa].nb_noeud_contour + panneau[pa].nb_noeud_cote;
  	in.segmentlist = (int *) malloc( in.numberofsegments * 2 * sizeof(int));
	if ( in.segmentlist   == NULL)
		{
		printf(" in.segmentlist  = NULL  \n" );
		exit(0);
		}

	numero_segment = 0; 				/*compteur qui suit le numero de segments*/
	for (no=1;no<=panneau[pa].nb_noeud_contour;no++)
		{ 
		deb = panneau[pa].suivant_contour[no];
		if (deb == 0) nb_segment = 1; 		/*pas de points intermediaires => 1 seul segment entre les points du contour*/
		if (deb != 0)				/*il y a des points intermediaires => plusieurs segments sur ce cote*/
			{
			co = no;
			do
				{
				co++;
				fin = panneau[pa].suivant_contour[co];
				}while((fin == 0) && (co != panneau[pa].nb_noeud_contour + 1));
			if (co != panneau[pa].nb_noeud_contour + 1) nb_segment = fin - deb + 1; 
			if (co == panneau[pa].nb_noeud_contour + 1) nb_segment = panneau[pa].nb_noeud_cote - deb + 2; 
			}
		/*printf("panneau[pa].suivant_contour[%d]   = %d  ",no, panneau[pa].suivant_contour[no]);
		printf("nb_segment   = %d  \n",nb_segment);*/

		for (co=1;co<=nb_segment;co++)
			{
			numero_segment++;
			if (co == 1) 
				{
				in.segmentlist[2*numero_segment-2] = no;
				/*
				printf("in.segmentlist-2[%d]   = %d  \n",2*numero_segment-2, in.segmentlist[2*numero_segment-2]);
				*/
				}
			if (co != 1)
				{
				in.segmentlist[2*numero_segment-2] = panneau[pa].nb_noeud_contour + panneau[pa].suivant_contour[no] + co - 2;
				/*
				printf("in.segmentlist-2[%d]   = %d  \n",2*numero_segment-2, in.segmentlist[2*numero_segment-2]);
				*/
				}
			if (co == nb_segment)
				{ 
				if (no == panneau[pa].nb_noeud_contour) in.segmentlist[2*numero_segment-1] = 1;
				if (no != panneau[pa].nb_noeud_contour) in.segmentlist[2*numero_segment-1] = no+1;
				/*
				printf("in.segmentlist-1[%d]   = %d  \n",2*numero_segment-1, in.segmentlist[2*numero_segment-1]);
				*/
				}
			if (co != nb_segment)
				{ 
				in.segmentlist[2*numero_segment-1] = panneau[pa].nb_noeud_contour + panneau[pa].suivant_contour[no] + co - 1;
				/*
				printf("in.segmentlist-1[%d]   = %d  \n",2*numero_segment-1, in.segmentlist[2*numero_segment-1]);
				*/
				}
			}
		}
	}

void initialisation_segment_interne_hexa(int pa)
	{
	/*defini les triangles poses sur les points interieurs du contour et des cotes*/
	int deb,no,fin,co,nb_segment,numero_segment;
 
 	/*initialisation des segments*/
	in.numberofsegments = pan_hexa[pa].nb_noeud_contour + pan_hexa[pa].nb_noeud_cote;
  	in.segmentlist = (int *) malloc( in.numberofsegments * 2 * sizeof(int));
	if ( in.segmentlist   == NULL)
		{
		printf(" in.segmentlist  = NULL  \n" );
		exit(0);
		}

	numero_segment = 0; 				/*compteur qui suit le numero de segments*/
	for (no=1;no<=pan_hexa[pa].nb_noeud_contour;no++)
		{ 
		deb = pan_hexa[pa].suivant_contour[no];
		if (deb == 0) nb_segment = 1; 		/*pas de points intermediaires => 1 seul segment entre les points du contour*/
		if (deb != 0)				/*il y a des points intermediaires => plusieurs segments sur ce cote*/
			{
			co = no;
			do
				{
				co++;
				fin = pan_hexa[pa].suivant_contour[co];
				}while((fin == 0) && (co != pan_hexa[pa].nb_noeud_contour + 1));
			if (co != pan_hexa[pa].nb_noeud_contour + 1) nb_segment = fin - deb + 1; 
			if (co == pan_hexa[pa].nb_noeud_contour + 1) nb_segment = pan_hexa[pa].nb_noeud_cote - deb + 2; 
			}

		for (co=1;co<=nb_segment;co++)
			{
			numero_segment++;
			if (co == 1) in.segmentlist[2*numero_segment-2] = no;
			if (co != 1)
				{
				in.segmentlist[2*numero_segment-2] = pan_hexa[pa].nb_noeud_contour + pan_hexa[pa].suivant_contour[no] + co
				- 2;
				}
			if (co == nb_segment)
				{ 
				if (no == pan_hexa[pa].nb_noeud_contour) in.segmentlist[2*numero_segment-1] = 1;
				if (no != pan_hexa[pa].nb_noeud_contour) in.segmentlist[2*numero_segment-1] = no+1;
				}
			if (co != nb_segment)
				{ 
				in.segmentlist[2*numero_segment-1] = pan_hexa[pa].nb_noeud_contour + pan_hexa[pa].suivant_contour[no] + co
				- 1;
				}
			}
		}
	}


void mise_a_jour_triangulation_interne(int pa)
	{
	/*defini les triangles poses sur les points interieurs du contour et des cotes*/
	int deb,no,fin;
	
	panneau[pa].nb_triangle_interieur = out.numberoftriangles;
	/*printf("  panneau : %4d ", pa);
	printf("  nb_triangle_interieur : %6d ", panneau[pa].nb_triangle_interieur);*/
	if ( panneau[pa].nb_triangle_interieur >= NBMAXNOEUDINTERIEUR)
		{
		printf(" NBMAXNOEUDINTERIEUR 1 trop petit %4d < %4d \n",NBMAXNOEUDINTERIEUR,panneau[pa].nb_triangle_interieur );
		exit(0);
		}
	/**********************************************/
  	panneau[pa].numero_triangle = (int *) malloc((1 + panneau[pa].nb_triangle_interieur) * sizeof(int));
	if (panneau[pa].numero_triangle    == NULL)
	      { 					       
	      printf(" panneau[pa].numero_triangle 1 = NULL  \n" );
	      exit(0);
	      }
	/**********************************************/
	for (deb=1;deb<=out.numberoftriangles;deb++)
		{ 
		Structure.nombreSurfaces++;
		if (Structure.nombreSurfaces >= NBMAXTRIANGLE)
			{
			printf(" NBMAXTRIANGLE trop petit %4d < %4d \n",NBMAXTRIANGLE,Structure.nombreSurfaces );
			exit(0);
			}
		/*le type de la surface est le numero du panneau*/
		surface[Structure.nombreSurfaces].type = pa;
		surface[Structure.nombreSurfaces].numerotation_locale = deb;
		panneau[pa].numero_triangle[deb] = Structure.nombreSurfaces;
		
		for (no=1;no<=out.numberofcorners;no++)
			{
			/*if ((deb == 1) && (no == 2)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 17;
			if ((deb == 2) && (no == 1)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 2;
			if ((deb == 6) && (no == 2)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 21;
			if ((deb ==15) && (no == 2)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 17;
			if ((deb ==28) && (no == 2)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 4;
			if ((deb ==29) && (no == 3)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 25;
			if ((deb == 3) && (no == 2)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 8;
			if ((deb == 4) && (no == 2)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 18;
			if ((deb ==24) && (no == 2)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 14;
			if ((deb ==26) && (no == 1)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 24;
			if ((deb ==30) && (no == 3)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 22;
			if ((deb ==31) && (no == 3)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 13;
			if ((deb ==18) && (no == 2)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 11;
			if ((deb ==18) && (no == 1)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 3;
			if ((deb ==18) && (no == 3)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 19;
			if ((deb ==21) && (no == 1)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 10;
			if ((deb ==21) && (no == 2)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 3;
			if ((deb ==21) && (no == 3)) out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1] = 19;*/
			fin = out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1];
			/*si 0<fin	                       <= panneau[pa].nb_noeud_contour   => fin appartient au contour    du panneau*/
			/*si 0<fin-panneau[pa].nb_noeud_contour<= panneau[pa].nb_noeud_cote      => fin appartient au cote       du panneau*/
			/*si 0<fin-panneau[pa].nb_noeud_cote   <= panneau[pa].nb_noeud_interieur => fin appartient a l interieur du panneau*/
			/*numero du sommet no dans la numerotation locale*/
			/*numero du sommet no dans la numerotation totale*/
			if (fin <= panneau[pa].nb_noeud_contour) 
				{
				if ( deb >= NBMAXNOEUDINTERIEUR)
					{
					printf(" NBMAXNOEUDINTERIEUR 2 trop petit %4d < %4d \n",NBMAXNOEUDINTERIEUR,deb );
					exit(0);
					}
				panneau[pa].triangle_interieur[deb][no]         = panneau[pa].noeud_contour[fin];
				surface[Structure.nombreSurfaces].extremite[no] = panneau[pa].noeud_contour[fin];
				}
			else
				{
				fin = fin - panneau[pa].nb_noeud_contour;
				if ((fin <=  panneau[pa].nb_noeud_cote)) 
					{
					if ( deb >= NBMAXNOEUDINTERIEUR)
						{
						printf(" NBMAXNOEUDINTERIEUR 3 trop petit %4d < %4d \n",NBMAXNOEUDINTERIEUR,deb );
						exit(0);
						}
					panneau[pa].triangle_interieur[deb][no]	= panneau[pa].noeud_cote[fin];
					surface[Structure.nombreSurfaces].extremite[no] 	= panneau[pa].noeud_cote[fin];
					}
				else
					{
					fin = fin - panneau[pa].nb_noeud_cote;
					if ( deb >= NBMAXNOEUDINTERIEUR)
						{
						printf(" NBMAXNOEUDINTERIEUR 4 trop petit %4d < %4d \n",NBMAXNOEUDINTERIEUR,deb );
						exit(0);
					}
					panneau[pa].triangle_interieur[deb][no]         = panneau[pa].noeud_interieur[fin];
					surface[Structure.nombreSurfaces].extremite[no] = panneau[pa].noeud_interieur[fin];
					}
				}
			}
		}
		//printf("Structure.nombreSurfaces = %8d \n", Structure.nombreSurfaces );
	}

void mise_a_jour_triangulation_interne_hexa(int pa)
	{
	/*defini les triangles poses sur les points interieurs du contour et des cotes*/
	int deb,no,fin;
	
	pan_hexa[pa].nb_tri_hexa_interieur = out.numberoftriangles;
	printf("  pan_hexa : %4d ", pa);
	printf("  nb_tri_hexa_interieur : %6d ", pan_hexa[pa].nb_tri_hexa_interieur);
	if ( pan_hexa[pa].nb_tri_hexa_interieur >= NBMAXNOEUDINTERIEUR)
		{
		printf(" NBMAXNOEUDINTERIEUR 1 trop petit %4d < %4d \n",NBMAXNOEUDINTERIEUR,pan_hexa[pa].nb_tri_hexa_interieur );
		exit(0);
		}
	for (deb=1;deb<=out.numberoftriangles;deb++)
		{ 
		/*out.numberoftriangles = le nb de triangles trouves par la procedure triangle*/
		/*printf("deb = %8d \n", deb );*/
		Structure.nombreSurfHexa++;
		if (Structure.nombreSurfHexa >= NBMAXTRIHEXA)
			{
			printf(" NBMAXTRIHEXA trop petit %4d < %4d \n",NBMAXTRIHEXA,Structure.nombreSurfHexa );
			exit(0);
			}
		/*le type de la surface est le numero du panneau*/
		surf_hexa[Structure.nombreSurfHexa].type = pa;
		/*numberofcorners = le nb de sommet par triangle donc = 3*/
		for (no=1;no<=out.numberofcorners;no++)
			{
			fin = out.trianglelist[out.numberofcorners*deb-out.numberofcorners+no-1];
			/*printf("fin = %8d ", fin );*/
			/*si 0<fin	                        <= pan_hexa[pa].nb_noeud_contour   => fin appartient au contour    du panneau*/
			/*si 0<fin-pan_hexa[pa].nb_noeud_contour<= pan_hexa[pa].nb_noeud_cote      => fin appartient au cote       du panneau*/
			/*si 0<fin-pan_hexa[pa].nb_noeud_cote   <= pan_hexa[pa].nb_noeud_interieur => fin appartient a l interieur du panneau*/
			/*fin = numero du sommet no dans la numerotation locale au panneau*/
			/*a partir de fin on determine sa correspondance dans la numerotation totale*/
			if (fin <= pan_hexa[pa].nb_noeud_contour) 
				{
				/*fin decrit un point du contour*/
				if ( deb >= NBMAXNOEUDINTERIEUR)
					{
					printf(" NBMAXNOEUDINTERIEUR 2 trop petit %4d < %4d \n",NBMAXNOEUDINTERIEUR,deb );
					exit(0);
					}
				pan_hexa[pa].tri_hexa_interieur[deb][no]= pan_hexa[pa].noeud_contour[fin];
				surf_hexa[Structure.nombreSurfHexa].extremite[no] = pan_hexa[pa].noeud_contour[fin];
				}
			else
				{
				fin = fin - pan_hexa[pa].nb_noeud_contour;
				if ((fin <=  pan_hexa[pa].nb_noeud_cote)) 
					{
					/*fin decrit un point du cote*/
					if ( deb >= NBMAXNOEUDINTERIEUR)
						{
						printf(" NBMAXNOEUDINTERIEUR 3 trop petit %4d < %4d \n",NBMAXNOEUDINTERIEUR,deb );
						exit(0);
						}
					pan_hexa[pa].tri_hexa_interieur[deb][no]	= pan_hexa[pa].noeud_cote[fin];
					surf_hexa[Structure.nombreSurfHexa].extremite[no] 	= pan_hexa[pa].noeud_cote[fin];
					}
				else
					{
					/*fin decrit un point interieur*/
					fin = fin - pan_hexa[pa].nb_noeud_cote;
					if ( deb >= NBMAXNOEUDINTERIEUR)
						{
						printf(" NBMAXNOEUDINTERIEUR 4 trop petit %4d < %4d \n",NBMAXNOEUDINTERIEUR,deb );
						exit(0);
					}
					pan_hexa[pa].tri_hexa_interieur[deb][no]         = pan_hexa[pa].noeud_interieur[fin];
					surf_hexa[Structure.nombreSurfHexa].extremite[no] = pan_hexa[pa].noeud_interieur[fin];
					}
				}
			}
		}
		printf("Structure.nombreSurfHexa = %8d \n", Structure.nombreSurfHexa );
		/*for ( no = 1 ; no <= Structure.nombreSurfHexa ; no++ )
			{
			printf("triangle %4d : ", no );
			printf("sommets %4d  %4d  %4d\n",surf_hexa[no].extremite[1],surf_hexa[no].extremite[2],surf_hexa[no].extremite[3]);
			}*/
	}

void liberer()
	{
	/*libere les zones memoires attachees a in out et vorout*/
	if ( in.pointlist 		!= NULL) 	free(in.pointlist);
  	if ( in.pointattributelist 	!= NULL) 	free(in.pointattributelist);
  	if ( in.pointmarkerlist 	!= NULL) 	free(in.pointmarkerlist);
  	if ( in.trianglelist 		!= NULL) 	free(in.trianglelist);
  	if ( in.trianglearealist 	!= NULL) 	free(in.trianglearealist);
  	if ( in.neighborlist 		!= NULL) 	free(in.neighborlist);
  	if ( in.segmentlist 		!= NULL) 	free(in.segmentlist);
  	if ( in.segmentmarkerlist 	!= NULL) 	free(in.segmentmarkerlist);
  	if ( in.holelist 		!= NULL) 	free(in.holelist);
  	if ( in.regionlist 		!= NULL) 	free(in.regionlist);
  	if ( in.edgelist 		!= NULL) 	free(in.edgelist);
  	if ( in.edgemarkerlist 		!= NULL) 	free(in.edgemarkerlist);
  	if ( in.normlist 		!= NULL) 	free(in.normlist);
	if ( out.pointlist 		!= NULL) 	free(out.pointlist);
  	if ( out.pointattributelist 	!= NULL) 	free(out.pointattributelist);
  	if ( out.pointmarkerlist 	!= NULL) 	free(out.pointmarkerlist);
  	if ( out.trianglelist 		!= NULL) 	free(out.trianglelist);
  	if ( out.trianglearealist 	!= NULL) 	free(out.trianglearealist);
  	if ( out.neighborlist 		!= NULL) 	free(out.neighborlist);
  	if ( out.segmentlist 		!= NULL) 	free(out.segmentlist);
  	if ( out.segmentmarkerlist 	!= NULL) 	free(out.segmentmarkerlist);
  	if ( out.holelist 		!= NULL) 	free(out.holelist);
  	if ( out.regionlist 		!= NULL) 	free(out.regionlist);
  	if ( out.edgelist 		!= NULL) 	free(out.edgelist);
  	if ( out.edgemarkerlist 	!= NULL) 	free(out.edgemarkerlist);
  	if ( out.normlist 		!= NULL) 	free(out.normlist);
	if ( vorout.pointlist 			!= NULL) 	free(vorout.pointlist);
  	if ( vorout.pointattributelist 		!= NULL) 	free(vorout.pointattributelist);
  	if ( vorout.pointmarkerlist 		!= NULL) 	free(vorout.pointmarkerlist);
  	if ( vorout.trianglelist 		!= NULL) 	free(vorout.trianglelist);
  	if ( vorout.trianglearealist 		!= NULL) 	free(vorout.trianglearealist);
  	if ( vorout.neighborlist 		!= NULL) 	free(vorout.neighborlist);
  	if ( vorout.segmentlist 		!= NULL) 	free(vorout.segmentlist);
  	if ( vorout.segmentmarkerlist 		!= NULL) 	free(vorout.segmentmarkerlist);
  	if ( vorout.holelist 			!= NULL) 	free(vorout.holelist);
  	if ( vorout.regionlist 			!= NULL) 	free(vorout.regionlist);
  	if ( vorout.edgelist 			!= NULL) 	free(vorout.edgelist);
  	if ( vorout.edgemarkerlist 		!= NULL) 	free(vorout.edgemarkerlist);
  	if ( vorout.normlist 			!= NULL) 	free(vorout.normlist);
	}


void inversions_des_triangles()
	{
	/*inverse les triangles definis dans l input du *.don*/
	int inv,prem,seco,pann,p1,p2,p3,s1,s2,s3,no,tri_prem,tri_seco;
	
	printf("inversions_des_triangles\n");
	
	for (inv=1; inv<=inversion_triangles.nb_inversion_triangles; inv++)
		{
		prem = inversion_triangles.premier[inv];
		seco = inversion_triangles.second[inv];
		if ((surface[prem].type != surface[seco].type) || (prem > Structure.nombreSurfaces)  || (prem < 1) || (seco > Structure.nombreSurfaces)  || (seco < 1))
			{
			printf("la %d eme inversions_des_triangles entre %d et %d n'inverse pas des triangles du meme panneau\n",inv,prem,seco);
			printf("la %d eme inversions_des_triangles entre %d et %d n'inverse pas des triangles\n",inv,prem,seco);
			}
		else
			{
			/*recherche du numero du triangle interieur au panneau*/
			pann = surface[prem].type;		/*panneau dans lequel sont les 2 triangles*/
			for (no=1; no<=panneau[pann].nb_triangle_interieur; no++)
				{
				if (panneau[pann].numero_triangle[no] == prem)
					{
					tri_prem = no;
					}
				if (panneau[pann].numero_triangle[no] == seco)
					{
					tri_seco = no;
					}
				}
			printf("tri_prem %5d tri_seco %5d \n",tri_prem,tri_seco);
		
		
			/*sommets du premier triangle*/
			p1 = surface[prem].extremite[1];	p2 = surface[prem].extremite[2];	p3 = surface[prem].extremite[3];
			/*sommets du second triangle*/
			s1 = surface[seco].extremite[1];	s2 = surface[seco].extremite[2];	s3 = surface[seco].extremite[3];
			printf("p1 p3 %5d %5d %5d s1 s3 %5d %5d %5d \n",p1,p2,p3,s1,s2,s3);
			if ((p1 != s1) && (p1 != s2) && (p1 != s3))
				{		
				if ((p2 != s1) && (p2 != s2) && (p2 != s3))
					{
					printf("la %d eme inversions_des_triangles entre %d et %d n'inverse pas des triangles jointifs\n",inv,prem,seco);
					}
				if ((p3 != s1) && (p3 != s2) && (p3 != s3))
					{
					printf("la %d eme inversions_des_triangles entre %d et %d n'inverse pas des triangles jointifs\n",inv,prem,seco);
					}
				if ((p2 == s3) && (p3 == s2))
					{
					printf("p1 a\n");
					surface[prem].extremite[1] = p1;	surface[prem].extremite[2] = s1;	surface[prem].extremite[3] = p3;
					surface[seco].extremite[1] = p1;	surface[seco].extremite[2] = p2;	surface[seco].extremite[3] = s1;
					}
				if ((p2 == s2) && (p3 == s1))
					{
					printf("p1 b\n");
					surface[prem].extremite[1] = p1;	surface[prem].extremite[2] = s3;	surface[prem].extremite[3] = p3;
					surface[seco].extremite[1] = p1;	surface[seco].extremite[2] = p2;	surface[seco].extremite[3] = s3;
					}
				if ((p2 == s1) && (p3 == s3))
					{
					printf("p1 c\n");
					surface[prem].extremite[1] = p1;	surface[prem].extremite[2] = s2;	surface[prem].extremite[3] = p3;
					surface[seco].extremite[1] = p1;	surface[seco].extremite[2] = p2;	surface[seco].extremite[3] = s2;
					}
				}
			if ((p2 != s1) && (p2 != s2) && (p2 != s3))
				{		
				if ((p3 != s1) && (p3 != s2) && (p3 != s3))
					{
					printf("la %d eme inversions_des_triangles entre %d et %d n'inverse pas des triangles jointifs\n",inv,prem,seco);
					}
				if ((p1 != s1) && (p1 != s2) && (p1 != s3))
					{
					printf("la %d eme inversions_des_triangles entre %d et %d n'inverse pas des triangles jointifs\n",inv,prem,seco);
					}
				if ((p3 == s3) && (p1 == s2))
					{
					printf("p2 d\n");
					surface[prem].extremite[1] = p2;	surface[prem].extremite[2] = s1;	surface[prem].extremite[3] = p1;
					surface[seco].extremite[1] = p2;	surface[seco].extremite[2] = p3;	surface[seco].extremite[3] = s1;
					}
				if ((p3 == s2) && (p1 == s1))
					{
					printf("p2 e\n");
					surface[prem].extremite[1] = p2;	surface[prem].extremite[2] = s3;	surface[prem].extremite[3] = p1;
					surface[seco].extremite[1] = p2;	surface[seco].extremite[2] = p3;	surface[seco].extremite[3] = s3;
					}
				if ((p3 == s1) && (p1 == s3))
					{
					printf("p2 f\n");
					surface[prem].extremite[1] = p2;	surface[prem].extremite[2] = s2;	surface[prem].extremite[3] = p1;
					surface[seco].extremite[1] = p2;	surface[seco].extremite[2] = p3;	surface[seco].extremite[3] = s2;
					}
				}
			if ((p3 != s1) && (p3 != s2) && (p3 != s3))
				{		
				if ((p1 != s1) && (p1 != s2) && (p1 != s3))
					{
					printf("la %d eme inversions_des_triangles entre %d et %d n'inverse pas des triangles jointifs\n",inv,prem,seco);
					}
				if ((p2 != s1) && (p2 != s2) && (p2 != s3))
					{
					printf("la %d eme inversions_des_triangles entre %d et %d n'inverse pas des triangles jointifs\n",inv,prem,seco);
					}
				if ((p1 == s3) && (p2 == s2))
					{
					printf("p3 g\n");
					surface[prem].extremite[1] = p3;	surface[prem].extremite[2] = s1;	surface[prem].extremite[3] = p2;
					surface[seco].extremite[1] = p3;	surface[seco].extremite[2] = p1;	surface[seco].extremite[3] = s1;
					}
				if ((p1 == s2) && (p2 == s1))
					{
					printf("p3 h\n");
					surface[prem].extremite[1] = p3;	surface[prem].extremite[2] = s3;	surface[prem].extremite[3] = p2;
					surface[seco].extremite[1] = p3;	surface[seco].extremite[2] = p1;	surface[seco].extremite[3] = s3;
					}
				if ((p1 == s1) && (p2 == s3))
					{
					printf("p3 i\n");
					surface[prem].extremite[1] = p3;	surface[prem].extremite[2] = s2;	surface[prem].extremite[3] = p2;
					surface[seco].extremite[1] = p3;	surface[seco].extremite[2] = p1;	surface[seco].extremite[3] = s2;
					}
				}
			panneau[pann].triangle_interieur[tri_prem][1] = surface[prem].extremite[1];
			panneau[pann].triangle_interieur[tri_prem][2] = surface[prem].extremite[2];
			panneau[pann].triangle_interieur[tri_prem][3] = surface[prem].extremite[3];
			panneau[pann].triangle_interieur[tri_seco][1] = surface[seco].extremite[1];
			panneau[pann].triangle_interieur[tri_seco][2] = surface[seco].extremite[2];
			panneau[pann].triangle_interieur[tri_seco][3] = surface[seco].extremite[3];

			}
		}
	}

