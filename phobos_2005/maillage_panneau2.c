#define PRINCIPAL 0
#include "phobos.h"
	
	/* 
	maillage des panneaux en creant des points sur les noeuds reels du filet
	
	ATTENTION : pour le maillage interne, il est possible de modifier le facteur de determination des
	noeuds trop proches du contour ou d un autre noeud - voir fact dans maillage_interne3 
	*/
	
void maillage_panneau2()
	{
	int   pa, mode ;

	/*faire le filet_contour si ce n est pas fait*/
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
			/* SI LE PAS DE MAILLAGE EST UN MULTIPLE DE LA LONGUEUR DE MAILLE, ON FAIT COINCIDER NOEUD REEL ET
			   NOEUD DE CALCUL, SINON ON MAILLE A "L'ANCIENNE"*/
			/*printf(" panneau[pa].longueur_repos= %12.6lf\n",panneau[pa].longueur_repos );*/
			if   ((panneau[pa].type_maillage != 1) && (panneau[pa].type_maillage != 2))
				{
				printf("le type de maillage du panneau %d doit etre 1 ou 2\n",pa );
				exit(0);
				}
			if   (panneau[pa].type_maillage == 1)
				{
				printf(" panneau = %d",pa );
				printf(" type maillage = %d",panneau[pa].type_maillage);
				printf(" maillage 1 \n");
				maillage_contour1(pa);
				maillage_interne2(pa);
				}	 
			if   (panneau[pa].type_maillage == 2)
				{
				printf(" panneau = %d",pa );
				printf(" type maillage = %d",panneau[pa].type_maillage);
				printf(" maillage 2 \n");
				maillage_contour2(pa);
				maillage_interne3(pa);
				}
			panneau[pa].flag_maillage = 1;
			}
		}
	printf("challlllllllut.nb_total = %4d \n",Structure.nb_total);
	SetMenuItemChecked(w[31],1);
	}
	
void maillage_contour_libre_filaire2(int pa, int co, int cp)
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
	deb = panneau[pa].noeud_contour[co];
	fin = panneau[pa].noeud_contour[cp];
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
	
	passe =  panneau[pa].pas_maillage / panneau[pa].longueur_repos;
	
	/* DETERMINATION DES POINTS EN U SUR LE COTE, NB_U NOMBRE DE POINTS EN U*/
	pt_u = 0 ; nb_u = 0 ;
	while ( (float) sens_u * (floor(udeb) + passe * sens_u * pt_u) <= sens_u * udeb )		/* ON SE PLACE BIEN PAR RAPPORT A L'EXTREMITE */
		{
		pt_u = pt_u + 1;
		}
	while  ( ( (float) sens_u * (floor(udeb) + sens_u * pt_u * passe ) < sens_u * ufin ) && ( fabs(sens_u *( ufin -  (floor(udeb) + sens_u * pt_u * passe))) >= fact*passe )) 	/* ON STOCKE LES POINTS TROUVES EN FILS U */
	    	{
	     	noeudcote_u[nb_u+1][1] = (float) floor(udeb) + sens_u * pt_u * passe ;
	     	noeudcote_u[nb_u+1][2] = equation_cote(2,noeudcote_u[nb_u+1][1],udeb,ufin,vdeb,vfin);
	     	pt_u++;
	     	nb_u++;
	     	if (nb_u >= 3*NBMAXNOEUDCOTE)
	     		{
			printf("Atttention nb_u %4d est >= a 3 * %4d \n",nb_u,NBMAXNOEUDCOTE);
			printf("Augmenter NBMAXNOEUDCOTE dans le *.h \n");
			exit(0);
	     		}
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
	     	if (nb_v >= 3*NBMAXNOEUDCOTE)
	     		{
			printf("Atttention nb_v %4d est > a 3 * NBMAXNOEUDCOTE %4d \n",nb_v,NBMAXNOEUDCOTE);
			printf("Augmenter NBMAXNOEUDCOTE dans le *.h \n");
			exit(0);
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
	panneau[pa].suivant_contour[co] = 0 ;
	for (zi = 1; zi <= cpt - 1 ; zi++)
		{
	        Structure.nb_total++;
		/*printf(" zi %4d Structure.nb_total %4d \n",zi,Structure.nb_total);*/
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
		panneau[pa].noeud_cote[panneau[pa].nb_noeud_cote] = Structure.nb_total;
		/*LGTENDUE CALCULEE ANTERIEUREMENT EN U ET V PERMET D'OBTENIR LA POSITION RELATIVE DU NOEUD / AUX EXTREMITES  */
		panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] = sqrt (  ( noeudcote_uv[zi][1] - udeb ) * ( noeudcote_uv[zi][1] - udeb )
									 + ( noeudcote_uv[zi][2] - vdeb ) * ( noeudcote_uv[zi][2] - vdeb ) ) 
								   / lg_tendue ; 
		noeud[Structure.nb_total].u = noeudcote_uv[zi][1] ;
		noeud[Structure.nb_total].v = noeudcote_uv[zi][2] ;
		noeud[Structure.nb_total].x = xdeb + panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] * (xfin-xdeb) ;
		noeud[Structure.nb_total].y = ydeb + panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] * (yfin-ydeb) ;
		noeud[Structure.nb_total].z = zdeb + panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] * (zfin-zdeb) ;
		noeud[Structure.nb_total].type = panneau[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].U = 0.5 * ( noeud[Structure.nb_total].u - noeud[Structure.nb_total].v ) ;
		noeud[Structure.nb_total].V = 0.5 * ( noeud[Structure.nb_total].u + noeud[Structure.nb_total].v ) ;
		printf("nb node on cote %d = %d Structure.nb_total %d mesh coordinates: u %lf v %lf twines coordinates:U %lf V %lf\n",co,cpt-1,Structure.nb_total ,noeud[Structure.nb_total].u,noeud[Structure.nb_total].v,noeud[Structure.nb_total].U,noeud[Structure.nb_total].V);		
		}
	}
	
void maillage_contour_panneau2(int pa, int co, int cp,int pa2,int nlo1,int nlo2)
	{
	/*PA = NO DU PANNEAU, CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROTATION LOCALE*/
	/*PA2 = NO DU 2EM PANNEAU, NLO1 = DEBUT DU COTE, NLO2 : FIN DU COTE DANS LA NUMEROTATION LOCALE*/
	int    zi, nb_coupe, deb, fin, premier_cote, sens_cote, nb_lai, premier_loc, nlo3 ;
	float  xdeb, xfin, ydeb, yfin, zdeb, zfin, ss ;
	
	deb  = panneau[pa2].noeud_contour[nlo1];
	fin  = panneau[pa2].noeud_contour[nlo2];
	xdeb = noeud[deb].x;
	xfin = noeud[fin].x;
	ydeb = noeud[deb].y;
	yfin = noeud[fin].y;
	zdeb = noeud[deb].z;
	zfin = noeud[fin].z;
	
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
			/*PAS DE POINT DE COTE SUR CE SEGMENT DE CONTOUR*/
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
		premier_loc = panneau[pa2].suivant_contour[nlo1];
		premier_cote = panneau[pa2].noeud_cote[panneau[pa2].suivant_contour[nlo1]];
		sens_cote = +1;
		}
	if((nlo2 == nlo1-1) || ((nlo2 == panneau[pa2].nb_noeud_contour) && (nlo1 == 1)))
		{
		premier_loc = panneau[pa2].suivant_contour[nlo2] + nb_coupe - 2;
		premier_cote = panneau[pa2].noeud_cote[panneau[pa2].suivant_contour[nlo2]] + nb_coupe - 2;
		sens_cote = -1;
		}
	
	panneau[pa].suivant_contour[co] = 0 ;
	for ( zi = 1 ; zi <= nb_coupe -1 ; zi++ )
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
		/* SS PERMET D ETABLIR LA CORRESPONDANCE DES PROPORTIONS DE NOEUDS LIES SANS CONSIDERER DE IF...ELSE... 
		   NECESSAIRE POUR LE CAS OU LES COTES EN JEU NE SONT PAS 1MAILLES DANS LE MEME SENS!
		   SS VAUT 1. SI LES SENS DE MAILLAGE SONT OPPOSES , 0. SINON*/
		ss = (float) 0.5 * fabs(sens_cote - 1.);
		panneau[pa].noeud_cote[panneau[pa].nb_noeud_cote] = Structure.nb_total;
		panneau[pa].prop_cote[panneau[pa].nb_noeud_cote] = ss + sens_cote*panneau[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)];
		noeud[Structure.nb_total].x = xdeb + (ss + sens_cote*panneau[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (xfin-xdeb) ;
		noeud[Structure.nb_total].y = ydeb + (ss + sens_cote*panneau[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (yfin-ydeb) ;
		noeud[Structure.nb_total].z = zdeb + (ss + sens_cote*panneau[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (zfin-zdeb) ;
		noeud[Structure.nb_total].U = noeud[deb].U + (ss + sens_cote*panneau[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (noeud[fin].U-noeud[deb].U) ;
		noeud[Structure.nb_total].V = noeud[deb].V + (ss + sens_cote*panneau[pa2].prop_cote[premier_loc + sens_cote * (zi - 1)]) * (noeud[fin].V-noeud[deb].V) ;
		noeud[Structure.nb_total].type = panneau[pa].type_suivant_contour[co] ;
		noeud[Structure.nb_total].u = noeud[Structure.nb_total].U + noeud[Structure.nb_total].V ; 
		noeud[Structure.nb_total].v = noeud[Structure.nb_total].V - noeud[Structure.nb_total].U ; 
		}
	}

void maillage_contour2(int pa)
	{
	int   co, cp, nloc1, nloc2, nopan, maille;
	char  pan ;
	
	//printf("maillage_contour2 pa = %8d \n",pa);
	//printf("nb_noeud_contour = %8d \n",panneau[pa].nb_noeud_contour);/**/
	
	for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
		{
		/*CO = DEBUT DU COTE, CP : FIN DU COTE DANS LA NUMEROATTION LOCALE*/
		if (co != panneau[pa].nb_noeud_contour) cp = co+1;
		if (co == panneau[pa].nb_noeud_contour) cp = 1;
		
		maille = liaison_maille(co,pa,&pan,&nopan,&nloc1,&nloc2);
		/*
		co = DEBUT DU SEGMENT TRAITE,
		pa = PANNEAU TRAITE,
		RENVOIE 1 OU 2 SI LE NOEUD EST LIE PAR UN LIEN A UN PANNEAU DEJA MAILLE, SINON 0
		1 si meme sens, 2 sens inverse
		RENVOIE 3 OU 4 SI LE NOEUD EST LIE PAR UN LIEN A UN CABLE DEJA MAILLE, SINON 0
		3 meme sens 4 sens inverse
		pan = TYPE DE LA STRUCTURE MAILLEE 'p' ou 'e'
		nopan = NUMERO DE CETTE STRUCTURE
		nloc1 = NUMERO DANS LA NUMEROTATION LOCALE DE LA PREMIERE EXTREMITE DU SEGMENT MAILLEE
		nloc2 = NUMERO DANS LA NUMEROTATION LOCALE DE LA DERNIERE EXTREMITE DU SEGMENT MAILLEE
		*/
		
		
		//printf("pa %4d  ",pa);
		//printf("co %4d cp %4d ",co,cp);
		//printf("pan %4c nopan %4d ",pan,nopan);
		//printf("nloc1 %4d nloc2 %4d ",nloc1,nloc2);
		//printf("maille %4d \n",maille);
	
		if (maille == 0)
			{
			maillage_contour_libre_filaire2(pa, co, cp);
		 	}
		if ((maille == 1) || (maille == 2))
			{
			maillage_contour_panneau2(pa, co, cp, nopan, nloc1, nloc2);
			}
		if ((maille == 3) || (maille == 4))
			{
			//printf("maille element = %8d \n",nopan);/**/
			//maillage_contour_element(pa, co, cp, nopan, nloc1);
			maillage_contour_element2(pa, co, cp, nopan, nloc1);
			//exit(0);
			}
		}
	}
	
void maillage_interne3(int pa)
	{
	/*CREE LES POINTS A L INTERIEUR DU PANNEAU PA, EN SE BASANT SUR LES FILS*/
	
	int    li, nbU, nbV, co, sommet_1, sommet_2, sommet_3, tri ,trouve, distant,no;
	float  Uo, Vo, denominateur, coef_a, coef_b ;
	float  min_U, min_V, max_U, max_V ,fact, passe ;
	
	
			
	//printf("maillage interne du panneau %8d \n",pa);/**/
		
		
		
		
	/* FACTEUR DETERMINANT LA TOLERANCE DE PROXIMITE D UN NOEUD DU CONTOUR OU D UN NOEUD DU BORD*/
	/* DISTANCE DU NOEUD AU BORD OU A UN AUTRE NOEUD, INFERIEURE A (PAS DE MAILLAGE * FACT) */
	fact = 0.25 ;
	
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
	/*printf("nbU %8d nbV %8d \n",nbU,nbV);*/
	
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
		printf("Structure.nb_add_node_panel %4d \n",Structure.nb_add_node_panel);
		printf("pa %4d \n",pa);
		for (no=1;no<=Structure.nb_add_node_panel;no++)
			{
			if (Add_node_panel.panel[no] == pa)
				{
				printf("add node %d in panel %d coordinates %lf %lf with type %d\n",no,Add_node_panel.panel[no],Add_node_panel.U[no],Add_node_panel.V[no],Add_node_panel.type[no]);
				Uo = (float)  Add_node_panel.U[no];
				Vo = (float)  Add_node_panel.V[no];
				tri     = interieur_panneau_filaire2(Uo, Vo,  pa);
				printf("tri %4d \n",tri);
				if (tri != 0)
					{
					Structure.nb_total++;
					printf("Structure.nb_total %4d \n",Structure.nb_total);
					if (Structure.nb_total >= NBMAXNOEUD)
						{
						printf(" NBMAXNOEUD trop petit %4d < %4d \n",NBMAXNOEUD,Structure.nb_total );
						exit(0);
						}
					panneau[pa].nb_noeud_interieur = panneau[pa].nb_noeud_interieur + 1;
					printf("panneau[pa].nb_noeud_interieur %4d \n",panneau[pa].nb_noeud_interieur);
					/**********************************************/
					panneau[pa].noeud_interieur = (int *) realloc(panneau[pa].noeud_interieur, (1+ panneau[pa].nb_noeud_interieur) * sizeof(int));
					if (panneau[pa].noeud_interieur    == NULL)
						{
						printf(" panneau[pa].noeud_interieur 2 = NULL  \n" );
						exit(0);
						}
					/**********************************************/
					panneau[pa].noeud_interieur[panneau[pa].nb_noeud_interieur] = Structure.nb_total;
					printf("panneau[pa].noeud_interieur[panneau[pa].nb_noeud_interieur] %4d \n",panneau[pa].noeud_interieur[panneau[pa].nb_noeud_interieur]);
					noeud[Structure.nb_total].u = Uo;
					noeud[Structure.nb_total].v = Vo;
					noeud[Structure.nb_total].type = Add_node_panel.type[no];
				
					sommet_1 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]];
					sommet_2 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]];
					sommet_3 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]];
					printf("sommets %4d %4d %4d \n",sommet_1,sommet_2,sommet_3);
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
					//exit(0);
					}
				}
			}
		}
	//exit(0);
	passe = panneau[pa].pas_maillage / panneau[pa].longueur_repos;
	for (co=1;co<=nbV ;co++)
		{
		/*printf("	co %8d Structure.nb_total %8d \n",co,Structure.nb_total);*/
		for (li=1;li<=nbU ;li++)
			{
			/*printf("		li %8d \n",li);*/
			Uo =  floor(min_U) + passe * li ;
			Vo =  floor(min_V) + passe * co ;
			
			tri     = interieur_panneau_filaire2(Uo, Vo,  pa);
			trouve  = proche_contour_filaire(Uo, Vo,  pa, fact);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / CONTOUR */
			distant = proche_panneau_filaire(Uo, Vo, pa, fact);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / NOEUD */
			
			/*printf("co %8d li %8d tr %8d tr %8d di %8d UV %f %f\n",co,li,tri,trouve,distant,Uo,Vo);*/
		
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
	
void maillage_interne4(int pa)
	{
	/*CREE LES POINTS A L INTERIEUR DU PANNEAU PA, EN SE BASANT SUR LES MAILLES et avec un maillage différent selon U et V*/
	
	int    li, nbU, nbV, co, sommet_1, sommet_2, sommet_3, tri ,trouve, distant;
	float  Uo, Vo, MUo, MVo, denominateur, coef_a, coef_b ;
	float  min_U, min_V, max_U, max_V ,fact ;
	
	
			
	//printf("maillage interne du panneau le long des mailles %8d \n",pa);/**/
		
		
		
		
	/* FACTEUR DETERMINANT LA TOLERANCE DE PROXIMITE D UN NOEUD DU CONTOUR OU D UN NOEUD DU BORD*/
	/* DISTANCE DU NOEUD AU BORD OU A UN AUTRE NOEUD, INFERIEURE A (PAS DE MAILLAGE * FACT) */
	fact = 0.25 ;
	
	/*RECHERCHE DES POINTS EXTREMES*/
	min_U = noeud[panneau[pa].noeud_contour[1]].U;
	min_V = noeud[panneau[pa].noeud_contour[1]].V;
	max_U = noeud[panneau[pa].noeud_contour[1]].U;
	max_V = noeud[panneau[pa].noeud_contour[1]].V;
	for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
		{
		if (noeud[panneau[pa].noeud_contour[co]].U > max_U) max_U = noeud[panneau[pa].noeud_contour[co]].U;
		if (noeud[panneau[pa].noeud_contour[co]].U < min_U) min_U = noeud[panneau[pa].noeud_contour[co]].U;
		if (noeud[panneau[pa].noeud_contour[co]].V > max_V) max_V = noeud[panneau[pa].noeud_contour[co]].V;
		if (noeud[panneau[pa].noeud_contour[co]].V < min_V) min_V = noeud[panneau[pa].noeud_contour[co]].V;
		}
	//nbU = (int) ((max_U - min_U) / panneau[pa].pas_maillage * panneau[pa].longueur_repos);
	//nbV = (int) ((max_V - min_V) / panneau[pa].pas_maillage * panneau[pa].longueur_repos);
	nbU = (int) ((max_U - min_U) / panneau[pa].pas_U);
	nbV = (int) ((max_V - min_V) / panneau[pa].pas_V);
	printf("nbU %8d nbV %8d \n",nbU,nbV);/**/
	
	panneau[pa].nb_noeud_interieur = 0;
	/**********************************************/
  	panneau[pa].noeud_interieur = (int *) malloc(1 * sizeof(int));
	if (panneau[pa].noeud_interieur    == NULL)
		{
		printf(" panneau[pa].noeud_interieur 1 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	for (co=1;co<=nbV ;co++)
		{
		/*printf("	co %8d Structure.nb_total %8d \n",co,Structure.nb_total);*/
		for (li=1;li<=nbU ;li++)
			{
			/*printf("		li %8d \n",li);*/
			MUo =  floor(min_U) + panneau[pa].pas_U * li ;	/*coordonnées en mailles*/
			MVo =  floor(min_V) + panneau[pa].pas_V * co ;
			
			Uo =  MUo + MVo;	/*coordonnées en fils*/
			Vo = -MUo + MVo;
			
			
			tri     = interieur_panneau_filaire2(Uo, Vo,  pa);
			trouve  = proche_contour_filaire(Uo, Vo,  pa, fact);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / CONTOUR */
			distant = proche_panneau_filaire(Uo, Vo, pa, fact);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / NOEUD */
			
			printf("co %8d li %8d tri %8d tro %8d di %8d uv %f %f UV %f %f\n",co,li,tri,trouve,distant,Uo,Vo,MUo,MVo);/**/
		
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
	
void maillage_interne6(int pa)
	{
	/*CREE LES POINTS A L INTERIEUR DU PANNEAU PA, EN SE BASANT SUR LES FILS et avec un maillage différent selon u et v*/
	
	int    li, nbu, nbv, co, sommet_1, sommet_2, sommet_3, tri ,trouve, distant;
	float  Muo, Mvo, denominateur, coef_a, coef_b ;
	float  min_u, min_v, max_u, max_v ,fact ;
	
	
			
	//printf("maillage interne du panneau le long des fils %8d \n",pa);/**/
		
		
		
	/* FACTEUR DETERMINANT LA TOLERANCE DE PROXIMITE D UN NOEUD DU CONTOUR OU D UN NOEUD DU BORD*/
	/* DISTANCE DU NOEUD AU BORD OU A UN AUTRE NOEUD, INFERIEURE A (PAS DE MAILLAGE * FACT) */
	fact = 0.25 ;
	
	/*RECHERCHE DES POINTS EXTREMES*/
	min_u = noeud[panneau[pa].noeud_contour[1]].u;
	min_v = noeud[panneau[pa].noeud_contour[1]].v;
	max_u = noeud[panneau[pa].noeud_contour[1]].u;
	max_v = noeud[panneau[pa].noeud_contour[1]].v;
	for (co=1;co<=panneau[pa].nb_noeud_contour;co++)
		{
		if (noeud[panneau[pa].noeud_contour[co]].u > max_u) max_u = noeud[panneau[pa].noeud_contour[co]].u;
		if (noeud[panneau[pa].noeud_contour[co]].u < min_u) min_u = noeud[panneau[pa].noeud_contour[co]].u;
		if (noeud[panneau[pa].noeud_contour[co]].v > max_v) max_v = noeud[panneau[pa].noeud_contour[co]].v;
		if (noeud[panneau[pa].noeud_contour[co]].v < min_v) min_v = noeud[panneau[pa].noeud_contour[co]].v;
		}
	nbu = (int) ((max_u - min_u) / panneau[pa].pas_u);
	nbv = (int) ((max_v - min_v) / panneau[pa].pas_v);
	printf("nbu %8d nbv %8d \n",nbu,nbv);/**/
	printf("min_u %f max_u %f \n",min_u,max_u);/**/
	printf("min_v %f max_v %f \n",min_v,max_v);/**/
	
	panneau[pa].nb_noeud_interieur = 0;
	/**********************************************/
  	panneau[pa].noeud_interieur = (int *) malloc(1 * sizeof(int));
	if (panneau[pa].noeud_interieur    == NULL)
		{
		printf(" panneau[pa].noeud_interieur 1 = NULL  \n" );
		exit(0);
		}
	/**********************************************/
	
	for (co=1;co<=nbv ;co++)
		{
		//printf("	co %8d Structure.nb_total %8d ",co,Structure.nb_total);/**/
		for (li=1;li<=nbu ;li++)
			{
			//printf("		li %8d ",li);/**/
			Muo =  floor(min_u) + panneau[pa].pas_u * li ;	/*coordonnées en fils*/
			Mvo =  floor(min_v) + panneau[pa].pas_v * co ;
			
			tri     = interieur_panneau_filaire2(Muo, Mvo,  pa);
			trouve  = proche_contour_filaire(Muo, Mvo,  pa, fact);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / CONTOUR */
			distant = proche_panneau_filaire(Muo, Mvo, pa, fact);	/* FACT EST LE FACTEUR DE DISTANCE TOLEREE / NOEUD */
			
			//printf("co %8d li %8d tri %8d tro %8d di %8d uv %f %f\n",co,li,tri,trouve,distant,Muo,Mvo);/**/
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
				noeud[Structure.nb_total].u = Muo;
				noeud[Structure.nb_total].v = Mvo;
				noeud[Structure.nb_total].type = panneau[pa].type_noeud;
			
				sommet_1 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][1]];
				sommet_2 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][2]];
				sommet_3 = panneau[pa].noeud_contour[panneau[pa].triangle_contour[tri][3]];
				/*LE vECTEUR 1uOvO = COEF_A * 12 + COEF_B * 13*/
				denominateur = (((noeud[sommet_2].u - noeud[sommet_1].u) * (noeud[sommet_3].v - noeud[sommet_1].v)) 
					      - ((noeud[sommet_2].v - noeud[sommet_1].v) * (noeud[sommet_3].u - noeud[sommet_1].u))); 
				coef_a = (((Muo - noeud[sommet_1].u) * (noeud[sommet_3].v - noeud[sommet_1].v)) 
					- ((Mvo - noeud[sommet_1].v) * (noeud[sommet_3].u - noeud[sommet_1].u)))
					/ denominateur;
				coef_b = (((Muo - noeud[sommet_1].u) * (noeud[sommet_2].v - noeud[sommet_1].v)) 
					- ((Mvo - noeud[sommet_1].v) * (noeud[sommet_2].u - noeud[sommet_1].u)))
					/ (-denominateur);
				
   				noeud[Structure.nb_total].x = noeud[sommet_1].x + coef_a * (noeud[sommet_2].x - noeud[sommet_1].x) 
   						         		     + coef_b * (noeud[sommet_3].x - noeud[sommet_1].x);
   				noeud[Structure.nb_total].y = noeud[sommet_1].y + coef_a * (noeud[sommet_2].y - noeud[sommet_1].y)
   				 		         		     + coef_b * (noeud[sommet_3].y - noeud[sommet_1].y);
      				noeud[Structure.nb_total].z = noeud[sommet_1].z + coef_a * (noeud[sommet_2].z - noeud[sommet_1].z)
   				 		         		     + coef_b * (noeud[sommet_3].z - noeud[sommet_1].z);
				noeud[Structure.nb_total].U = (noeud[Structure.nb_total].u - noeud[Structure.nb_total].v) / 2.0;
   				noeud[Structure.nb_total].V = (noeud[Structure.nb_total].u + noeud[Structure.nb_total].v) / 2.0;
				
				//printf("sommets %8d %8d %8d \n",sommet_1,sommet_2,sommet_3);/**/
				//printf("sommet1 %f %f %f %f %f \n",noeud[sommet_1].u,noeud[sommet_1].v,noeud[sommet_1].x,noeud[sommet_1].y,noeud[sommet_1].z);/**/
				//printf("sommet2 %f %f %f %f %f \n",noeud[sommet_2].u,noeud[sommet_2].v,noeud[sommet_2].x,noeud[sommet_2].y,noeud[sommet_2].z);/**/
				//printf("sommet3 %f %f %f %f %f \n",noeud[sommet_3].u,noeud[sommet_3].v,noeud[sommet_3].x,noeud[sommet_3].y,noeud[sommet_3].z);/**/
				//printf("sommet %f %f %f %f %f \n",noeud[Structure.nb_total].u,noeud[Structure.nb_total].v,noeud[Structure.nb_total].x,noeud[Structure.nb_total].y,noeud[Structure.nb_total].z);/**/
		   				
				//exit(0);
				}
			}
		}
	}
	
float equation_cote(int inc, float val, float u1, float u2, float v1, float v2)
	{
	float u, v ;
	
	/* 
	U1,V1 (RESPT U2,V2) SONT LES COORDONNEES FILAIRES DE L EXTREMITE 1 (RESPT 2)
	ON SE DONNE VAL (U OU V SUR LA DROITE D EXTREMITE 12), DONC VAL EST SOIT LA COORDONNEE
	FILAIRE EN U,SOIT CELLE EN V, ET ON CHERCHE A CALCULER SOIT V, SOIT U A PARTIR DE L EQUATION DU COTE EN (U,V) :
	(U2-U1)*(V-V1)-(V2-V1)*(U-U1) = 0.0 ;
	*/
	 
	if ( inc == 1 ) 
		{
		/*on recherche U, connaissant V*/
	   	if ( v2 == v1 ) 
	   		{
	   		printf(" * equation_cote * v2=v1\n");
	   		exit(0);
	   		}
	   	else
	   	 	{
	   	  	u = ( u2 - u1 ) * ( val - v1 ) / ( v2 - v1 ) + u1 ;
	   	  	return u ; 
	   	 	}
	   	}
	if ( inc == 2 ) 
	   	{
		/*on recherche V, connaissant U*/
	   	if ( u2 == u1 ) 
	   		{
	   		printf(" * equation_cote * u2=u1\n");
	   		exit(0);
	   		}
	   	else 
	   	 	{
	   	  	v = ( v2 - v1 ) * ( val - u1 ) / ( u2 - u1 ) + v1 ;
	   	  	return v ; 
	   	 	}
	   	}
	}

