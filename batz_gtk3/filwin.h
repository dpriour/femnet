//#define DIM1  37033             // taille tableau we,ye > 3*NOMBRE_NOEUDS           //
//#define DIM2  25000            	// taille tableau yb,wr >  NOMBRE_ELEMENTS & NOMBRE_SURFACES & NOMBRE_SURF_HEXA //

/*
#ifdef PRINCIPAL
#define CLASS 	
#else
#define CLASS extern 
#endif
*/

/* struct 	ball {
	int    	nb;		//balls nb//
	double  *radius;	//table of radius of balls//
	double  *birth_time;	//birth time//
	int    	*noeud;		//numeros du noeud de cette ball//
	double  *x;		//x position//
	double  *y;		//y position//
	double  *z;		//z position//
	double  *stiffness;	//N/m//
	int    	*type;		//type of the ball one born//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	} 	;*/

/* struct 	element {
	int    	type;		 	//no du type de l element//
	int    	nop[3];
	double  pro[3];			//position des 2 extremites en proportion de la longueur de l element de phobos//
	double 	diametremeca;
	double 	raideur_traction;
	double 	raideur_compression;
	double 	tension;
	double 	*dtension;
	double 	lgrepos;
	double 	lgtendue;
	double 	*dlgtendue;
	double 	nrj;
	double 	*dnrj;
	double 	diametrehydro;
	double 	rhoelement;
	double 	cdnormal;
	double 	ftangent;
	int    	color;			//fonction de la tension//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	double	x1;			//coordonnee x de l extremite 1//
	double	y1;			//coordonnee y de l extremite 1//
	double	z1;			//coordonnee z de l extremite 1//
	double	x2;			//coordonnee x de l extremite 2//
	double	y2;			//coordonnee y de l extremite 2//
	double	z2;			//coordonnee z de l extremite 2//

	} ;*/
/*
 struct 	coulisse {
	int    	nop[3];			//no des 2 points d extremites//
	int    	nb_noeud;		//nb de noeuds internes dans la coulisse en commencant par extremite 1//
	int    	*noeud;			//numeros des noeuds internes dans la coulisse en commencant par extremite 1//
	double  *longueur;		//distance entre noeuds en commencant par extremite 1//
	double 	raideur_traction;	//raideur en traction    (N) = section * module d elasticite//
	double 	raideur_compression;	//raideur en compression (N) = section * module d elasticite//
	double 	raideur_effective;	//raideur effective = raideur en traction (compression) si element est en traction (compression)//
	double 	tension;		//tension dans cet element (N)//
	double 	lgrepos;		//longueur avec tension = 0 N = somme des longueurs//
	double 	lgtendue;		//longueur sous tension//
	double 	nrj;
	double 	diametrehydro;		//diametre hydrodynamique m^2//
	double 	rhocoulisse;		//masse volumique kg/m^3//
	double 	cdnormal;		//coef. de trainee normal//
	double 	ftangent;		//coef. de trainee tangent//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	} 	;*/

/* struct 	winch {
	int    	nop[3];			//no des 2 points d extremites//
	int    	nb_barre;		//nb de noeuds internes dans la coulisse en commencant par extremite 1//
	int    	type_noeud;		//type of node//
	int    	*noeud;			//numeros des noeuds internes dans la coulisse en commencant par extremite 1//
	int    	*exit;			//0 si le noeud est dans le treuil et 1 si il est sorti du treuil//
	double  *prop;			//proportion de la position du noeud relative a la longueur totale//
	double  *longueur;		//distance entre noeuds en commencant par extremite 1//
	double 	raideur_traction;	//raideur en traction    (N) = section * module d elasticite//
	double 	raideur_compression;	//raideur en compression (N) = section * module d elasticite//
	double 	raideur_effective;	//raideur effective = raideur en traction (compression) si element est en traction (compression)//
	double 	rho;			//density (kg/m3)//
	double 	wt;			//tension dans cet element (N)//
	double 	wtfinal;		//tension dans cet element (N) a l avant derniere iteration //
	double  adjust_force;		//force on the cable from the winch (N)//
	double 	longueur_repos;		//longueur avec tension = 0 N = somme des longueurs//
	double 	diam_hydro;		//diametre hydrodynamique m^2//
	double 	rhocoulisse;		//masse volumique kg/m^3//
	double 	cdnormal;		//coef. de trainee normal//
	double 	ftangent;		//coef. de trainee tangent//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	} 	;*/

/* struct surface {
	int    type;		 	//no du type de surface//
	int    nop[4];
	double lon[7];
	double diametremeca;
	double raideur_traction;
	double raideur_compression;
	double EI_flexion;		//raideur a la flexion des fils em N.m.m//
	double raideur_ouverture;
	double neutral_angle;		//angle au repos du panneau en rad//
	double tension1;
	double tension2;
	double nrj1;
	double nrj2;
	double nrj;
	double lgrepos;
	double mx;	//composante selon x du fil u//
	double my;
	double mz;
	double nx;	//composante selon x du fil v//
	double ny;
	double nz;
	double Nx;	//composante selon x de la normale normee au triangle//
	double Ny;
	double Nz;
	double defaut_disc;	//mesure du defaut de discretisation//
	double diametrehydro;
	double largeurnoeud;
	double rhosurface;
	double cdnormal;
	double ftangent;
  	float *g1_ux,*g2_ux,*g1_uy,*g2_uy,*g1_uz,*g2_uz;                     
  	float *f1_ux,*f2_ux,*f1_uy,*f2_uy;                     
  	float *g1_vx,*g2_vx,*g1_vy,*g2_vy,*g1_vz,*g2_vz;                     
  	float *f1_vx,*f2_vx,*f1_vy,*f2_vy;
	int    nb_ufils;
	int    nb_vfils;
	int    color_u;			//couleur en fonction de la tension//
	int    color_v;
	int    orientation;		//orientation de la surface 1 ou -1//
	int    color_side[4];
	int    flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	int    flag_dessin_u;		//fils u si 1 dessin sinon 0, par defaut 1//
	int    flag_dessin_v;		//fils v si 1 dessin sinon 0, par defaut 1//
	int    flag_dessin_triangle;		//triangle si 1 dessin sinon 0, par defaut 1//
	int    flag_dessin_orientation_xy;		//triangle si 1 dessin sinon 0, par defaut 1//
	double 	energy_pliage;		//energie potentielle liee au pliage de 2 triangles joints//
	double 	energy_ouverture;	//energie potentielle liee a l'ouverture des mailles//
	double 	energy_elastique;	//energie potentielle liee a l elongation des fils//
	double 	energy_contact;		//energie potentielle liee au contact entre les fils//
	int 	tarp;			//if 1 the panel is water proof like a tarp if 0 it is a netting//
	int     vertexU1,vertexV1,vertexU2,vertexV2;				//vertex from which the twines are drawn//	
	int     nU1,nU2,nV1,nV2;							//nb of twines drawn 2 for U and 2 for V//	
	double  beginU11,beginU12,beginU21,beginU22,beginV11,beginV12,beginV21,beginV22;//distance of the first twine to the vertex > 0 and < 1//
	double   stepU11, stepU12, stepU21, stepU22, stepV11, stepV12, stepV21, stepV22;//distance between the twine > begin and < 1//
	double max_exit_size;		//maximum of circle diameter passing trough meshes
	} ;*/

/* struct surf_hexa {
	int    type;		 	//no du type de surface hexagonale//
	int    nop[4];
	double lon[7];
	double diametremeca;
	double 	raideur_traction_l,raideur_traction_m,raideur_traction_n;		//raideur en traction des fils constituant le filet de ce panneau//
	double 	raideur_compression_l,raideur_compression_m,raideur_compression_n;//raideur en compression des fils constituant le filet de ce panneau//
	double raideur_traction;
	double raideur_compression;
	double 	EI_flexion;		//raideur a la flexion des fils em N.m.m//
	double tension1;
	double tension2;
	double tension3;
	double nrj1;
	double nrj2;
	double nrj3;
	double nrj;
	double 	lo_repos,mo_repos,no_repos;		//cote de maille l,m,n du filet de ce panneau//
	double 	lx,ly,lz;			//composante de la longueur du cote de maille l selon l axe x//
	double 	mx,my,mz;			//composante de la longueur du cote de maille m selon l axe x//
	double 	nx,ny,nz;			//composante de la longueur du cote de maille n selon l axe x//
	double 	diam_hydro_l,diam_hydro_m,diam_hydro_n;	//diametre hydro des fils du filet de ce panneau//
	double diametrehydro;
	double largeurnoeud;
	double rhosurface;
	double cdnormal;
	double ftangent;
  	float *g1_Ux,*g2_Ux,*g1_Uy,*g2_Uy,*g1_Uz,*g2_Uz;                     
  	float *f1_Ux,*f2_Ux,*f1_Uy,*f2_Uy;                     
  	float *g1_Vx,*g2_Vx,*g1_Vy,*g2_Vy,*g1_Vz,*g2_Vz;                     
  	float *f1_Vx,*f2_Vx,*f1_Vy,*f2_Vy;
	int    nb_Ufils ;
	int    nb_Vfils ;
	int    color_l;			//couleur en fonction de la tension//
	int    color_m;
	int    color_n;
	int    orientation;		//orientation de la surface 1 ou -1//
	int    color_side[4];
	int    flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	} ;
*/
/* struct noeud {
	int    	type;		 	//no du type de noeud//
	int    	new_numero;		//renvoi le nouveau   numero de point apres renumerotation//
	int    	old_numero;		//renvoi le precedent numero de point apres renumerotation//
	double 	inix,iniy,iniz;		//coordonnees sans rotation (m)//
	double 	x,y,z;			//coordonnees (m)//
	double 	*dx,*dy,*dz;		//coordonnees dynamique sans rotation (m)//
	double 	*ex,*ey,*ez;		//coordonnees dynamique (m)//
	double 	*hz;			//immersion sans rotation (m)//
	double 	*gx,*gy,*gz;		//immersion dynamique (m)//
	double  mx,my,mz;
	double  majx,majy,majz;
	double  sx,sy,sz;
	double  cdx,cdy,cdz;
	double  fx,fy,fz;
	double  fxcal,fycal,fzcal;
	int     fmx,fmy,fmz;
	double  limx,limy,limz;
	int     fixx,fixy,fixz;
	int     symx,symy,symz;
	double  depx,depy,depz;
	int    flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	} ; */
	
/* struct houle {
	double lambda;
	double hh1;
	double hauteur;
	double periode;	
	double direction;
	double depth;		//profondeur du site (m)//
	//double 	**x,**y,**z;		coordonnees dynamique sans rotation (m)//
	//double 	**u,**v,**w;		coordonnees dynamique avec rotation (m)//
	//double 	**X,**Y,**Z;		coordonnees dynamique sans rotation (m)//
	//double 	**U,**V,**W;		coordonnees dynamique avec rotation (m)//
	double x[1000][1000];
	double y[1000][1000];
	double z[1000][1000];
	double u[1000][1000];
	double v[1000][1000];
	double w[1000][1000];
	//double X[1000][10000];
	double Y[1000][10000];
	double Z[1000][10000];
	double U[1000][10000];
	double V[1000][10000];
	double W[1000][10000];//
double** X; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** Y; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** Z; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** U; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** V; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** W; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
	int nb_trace; 		// nombre de trace de houle//
	int nb_point; 		// nombre de point de houle//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	} ;	*/

/* struct courant {
	double vitesse;	
	double direction;
	} ;	*/

/* struct 	prise {
	double 	volume;			//volume (m3)//
	double 	seuil;			//seuil (m3)//
	double 	cd;			//coef de trainee sur la prise//
	double 	front;			//position du front de la prise (m)//
	double 	diametre;		//diametre de la prise (m)//
	double 	epaisseur;		//distance du front a l extremite de la prise (m)//
	double 	radial_radius;		//radial radius of the ellipsoide inner surface (m)//
	double 	axial_radius;		//radial radius of the ellipsoide inner surface (m)//
	double 	distance_front;		//distance between the center of the ellipsoide and the front of the cod-end (m)//
	int	nb_point;		//nb of points in the perimeter of the front//
	double	*perimeter_y;		//y position of a point of the perimeter//
	double	*perimeter_z;		//z position of a point of the perimeter//
	double 	PR;			//prise en kg de poisson//
	double 	PE;			//perimetre tendu du cod-end//
	double 	TA;			//taille moyenne en kg des poisson//
	double 	RA;			//mesh opening stiffness N.m2//
	double 	Ox;			//x coordinate of the ellipsoide center//
	double 	Oy;			//y coordinate of the ellipsoide center//
	double 	Oz;			//z coordinate of the ellipsoide center//
	int 	nb_noeuds;		//nb de noeuds total de l'ellipsoide + le contour//
	int 	nb_noeuds_contour;	//nb de noeuds du contour de l'ellipsoide//
	double 	*xx,*yy,*zz;		//coordonnees des noeuds total de l'ellipsoide + le contour//
	double 	*xx_ini,*yy_ini,*zz_ini;//coordonnees des noeuds total de l'ellipsoide + le contour//
	int	nb_triangles;		//nb of triangles on the inner surface//
	int	*vertex_1;		//nb of vertex 1//
	int	*vertex_2;		//nb of vertex 2//
	int	*vertex_3;		//nb of vertex 3//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	double	catch_density;		//density of the catch when outside of water//
	} 	;	
*/
/*struct 	bottom {
	double 	coef_frottement;	//coef de frottement sur le fond des noeuds : effort horizontal / effort vertical//	
	double 	raideur;		//raideur a l enfoncement des noeuds (N/m)//
	} 	;	
	*/
/*struct champ
	{
	int noeud1;			//premiere extremite //		
	int noeud2;			//seconde extremite //		
	int decimale;			//nb de decimale pour l affichage //
	double valeur;			//valeur //	
	char txt[156];			//intitule de la valeur affichee//
	};*/
	
/*typedef struct 	commentaire {
	char texte[156];
	} 	COMMENTAIRE;	*/
	
/*
struct sortie_texte
	{
	int  nb_distance;			//nb de distance entre 2 points affichees//
	COMMENTAIRE *comment_distance;		//commentaires associes aux distances//
	int *noeud1_distance;			//premiere extremite de la distance//		
	int *noeud2_distance;			//seconde extremite de la distance//		
	int *decimale_distance;			//nb de decimale pour l affichage de la distance//
	double *valeur_distance;
			
	int  nb_effort;				//nb d effort selon un axe a un point affiches//
	COMMENTAIRE *comment_effort;		//commentaires associes aux distances//
	int *noeud_effort;			//premiere extremite de la distance//		
	int *axe_effort;			//seconde extremite de la distance//		
	int *decimale_effort;			//nb de decimale pour l affichage de la distance//
	double *valeur_effort;

	int  nb_tension;			//nb de tension dans un element affichees//
	COMMENTAIRE *comment_tension;		//commentaires associes aux distances//
	int *element_tension;			//premiere extremite de la distance//		
	int *element_extremite;			//premiere extremite de la distance//		
	int *decimale_tension;			//nb de decimale pour l affichage de la distance//
	double *valeur_tension;
	
	int  nb_tension_coulisse;		//nb de tension dans une coulisse affichees//
	COMMENTAIRE *comment_tension_coulisse;	//commentaires associes aux distances//
	int *coulisse_tension;			//premiere extremite de la distance//		
	int *coulisse_extremite;		//premiere extremite de la distance//		
	int *decimale_coulisse;			//nb de decimale pour l affichage de la distance//		
	double *valeur_tension_coulisse;
	
	int  nb_position;			//nb de position selon un axe a un point affichees//
	COMMENTAIRE *comment_position;		//commentaires associes aux distances//
	int *noeud_position;			//premiere extremite de la distance//		
	int *axe_position;			//seconde extremite de la distance//		
	int *decimale_position;			//nb de decimale pour l affichage de la distance//
	double *valeur_position;	
	
	int  nb_longueur;			//nb de longueur de barres affichees//
	COMMENTAIRE *comment_longueur;		//commentaires associes aux longueurs//
	int *element_longueur;			//numero de l element//		
	int *decimale_longueur;			//nb de decimale pour l affichage de la longueur//
	double *valeur_longueur;
	
	int  nb_longueur_cable;			//nb de longueur de cables affichees//
	COMMENTAIRE *comment_longueur_cable;	//commentaires associes aux longueurs//
	int *element_longueur_cable;		//numero du cable//		
	int *decimale_longueur_cable;		//nb de decimale pour l affichage de la longueur en m//
	double *valeur_longueur_cable;
	
	int  nb_energie_elong_diamond;		//nb d energies d elongation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_elong_diamond;	//commentaires associes aux energies//
	int *panneau_energie_elong;		//numero du panneau//		
	int *decimale_energie_elong;		//nb de decimale pour l affichage de l energie en J//
	double *valeur_energie_elong_diamond;
	
	int  nb_energie_fold_diamond;			//nb d energies d foldation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_fold_diamond;	//commentaires associes aux energies//
	int *panneau_energie_fold;			//numero du panneau//		
	int *decimale_energie_fold;			//nb de decimale pour l affichage de l energie en J//
	double *valeur_energie_fold_diamond;
	
	int  nb_energie_open_diamond;			//nb d energies d openation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_open_diamond;	//commentaires associes aux energies//
	int *panneau_energie_open;			//numero du panneau//		
	int *decimale_energie_open;			//nb de decimale pour l affichage de l energie en J//
	double *valeur_energie_open_diamond;
	
	int  nb_energie_contact_diamond;		//nb d energies d openation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_contact_diamond;	//commentaires associes aux energies//
	int *panneau_energie_contact;			//numero du panneau//		
	int *decimale_energie_contact;			//nb de decimale pour l affichage de l energie en J//
	double *valeur_energie_contact_diamond;
	
	int  nb_parametre;			//nb de position selon un axe a un point affichees//
	COMMENTAIRE *comment_parametre;		//commentaires associes aux distances//
	int *decimale_parametre;		//nb de decimale pour l affichage de la distance//
	double *valeur_parametre;
	
	int effort_structure;			//si 1 affiche l effort sur toute la structure (N) selon les axes X Y et Z//	
	int diametre_prise;			//si 1 affiche diametre_prise (m)//	
	int epaisseur_prise;			//si 1 affiche epaisseur_prise (m)//	
	int vitesse_courant;			//si 1 affiche vitesse_courant (m/s)//	
	int volume_capture;			//si 1 affiche volume_capture (m3)//	
	int surface_filtree;			//si 1 affiche surface_filtree (m2)//	

	double valeur_effort_structure[4];	//si 1 affiche l effort sur toute la structure (N) selon les axes X Y et Z//	
	double valeur_diametre_prise;		//si 1 affiche diametre_prise (m)//	
	double valeur_epaisseur_prise;		//si 1 affiche epaisseur_prise (m)//	
	double valeur_vitesse_courant;		//si 1 affiche vitesse_courant (m/s)//	
	double valeur_volume_capture;		//si 1 affiche volume_capture (m3)//	
	double valeur_surface_filtree;		//si 1 affiche surface_filtree (m2)//	
	double valeur_catch_drag;		//si 1 affiche la trainee sur la prise (N)//	
	double valeur_bottom_drag;		//si 1 affiche la trainee sur le fonf (N)//	
	double valeur_element_drag;		//si 1 affiche la trainee sur le fonf (N)//	
	double valeur_surface_drag;		//si 1 affiche la trainee sur le fonf (N)//	
	double valeur_node_drag;		//si 1 affiche la trainee sur le fonf (N)//	
	int volume_x;				//si 1 affiche le volume calcule selon l axe x (m3)//	
	int volume_y;				//si 1 affiche le volume calcule selon l axe y (m3)//	
	int volume_z;				//si 1 affiche le volume calcule selon l axe z (m3)//	
	int volume_0;				//si 1 affiche le volume calcule selon le courant (m3)//	
	int inner_surface;			//si 1 affiche les dimensions de l'ellipsoide de la surface interne de la prise (m)//	
	int inner_surface_triangulation;	//si 1 affiche les triangles de l'ellipsoide de la surface interne de la prise (m)//	
	int catch_drag;	   			//si 1 affiche the drag of the catch (N)//	
	int bottom_drag;	   		//si 1 affiche the drag on the bottom (N)//	
	int element_drag;	   		//si 1 affiche the drag on the bottom (N)//	
	int surface_drag;	   		//si 1 affiche the drag on the bottom (N)//	
	int node_drag;	   			//si 1 affiche the drag on the nodes (N)//	
	
	} ;
*/
/*struct sphere_element
   	{
	int 	*element;	//cable on which the sphere are//	
	int 	*nb;		//number of sphere//			
	double 	*diameter;	//diameter of the each sphere floats (m)//			
	double 	*floatability;		//floattability of each float (N)//			
   	}	Sphere_element;*/
   	
/*
struct value
   	{
	double 	*depth1;	//first depth//	
	double 	*depth2;	//second depth//			
	double 	*value1;	//value for the first depth//			
	double 	*value2;	//value for the second depth//			
   	}	Value;*/
   	
/*struct filiere devenu structure
   {
   int       nombrePoints;
   int	     nombreElements;
   int	     nombreCoulisses;
   int	     nombreSurfaces;
   int	     nombreSurfHexa;
   int 	     nb_winch; 				//nb of winches in the structure//
   int 	     version; 				//version number of the *.don//
   int 	     drawing; 				//0 default in colors, 1 in black//
   int 	     visible_symmetry; 			//1 default symmetry is visisble, à the symmetry is not visible//
   double    diviseur;
   int       graphic;				//if 1 it is calculated with the graphic tool, if 2 it is calculated by the text tool//
   int       nb_sphere_element;			//nb of element with spheric floats//
   int       symetry;				//if 0 no sym, 1 symx, 2 symy, 4 symz, 3 symxy, 5 symxz, 6 symyz, 7 symxyz//
   char      nomfichier1[100],nomfichier2[100];	//files name//
   int	     nb_value;				//nb of linear value//
   int       free_surface;			//1 if the free surface is displayed, 0 if not//
   };
*/

/*
int    	flag_dessin_axes;		//si 1 dessin sinon 0, par defaut 1//
int    	flag_dessin_quadrillage;		//si 1 dessin sinon 0, par defaut 1//
int    	flag_dessin_commentaires;		//si 1 dessin sinon 0, par defaut 1//
int    	flag_dessin_efforts_externes;		//si 1 dessin sinon 0, par defaut 1//
int    	flag_dessin_deplacement;		//si 1 dessin sinon 0, par defaut 1//
int    	flag_dessin_trajectoire;		//si 1 dessin sinon 0, par defaut 1//
int    	flag_dessin_immersion;		//si 1 dessin sinon 0, par defaut 1//
*/

//*** declaration de variables globales ***//
/*
CLASS struct Structure   	Structure; 
CLASS struct noeud     		Noeud[DIM1],TypeNoeud[DIM1];
CLASS struct element   		Element[DIM2],TypeElement[DIM2]; 
CLASS struct winch   		Winch[DIM2]; 
CLASS struct ball   		Ball; 
CLASS struct coulisse   	Coulisse[DIM2]; 
CLASS struct surface   		Surface[DIM2],TypeSurface[DIM2];
CLASS struct surf_hexa 		Surf_Hexa[DIM2],TypeSurfHexa[DIM2]; 
CLASS struct houle     		Houle;
CLASS struct courant   		Courant;
CLASS struct prise     		Prise;
CLASS struct bottom	  	Bottom;
CLASS struct sphere_element	Sphere_element;
CLASS struct sortie_texte	Sortie_texte;
CLASS struct value		Value;
*/

//*** declaration de variables globales ***//
/*
CLASS struct champ *txt_distance;
CLASS struct champ *txt_effort;
CLASS struct champ *txt_tension;
CLASS struct champ *txt_tension_coulisse;
CLASS struct champ *txt_position;


// "define" //
#define NOMBRE_ELEMENTS 	Structure.nombreElements
#define NOMBRE_COULISSES 	Structure.nombreCoulisses
#define NOMBRE_POINTS   	Structure.nombrePoints
#define NOMBRE_SURFACES 	Structure.nombreSurfaces
#define NOMBRE_SURF_HEXA 	Structure.nombreSurfHexa
#define NOMBRE_WINCHS 		Structure.nb_winch
#define DIVISEUR        	Structure.diviseur*/
