#define DIM1  20000	/* taille tableau we,ye > 3*NOMBRE_NOEUDS           */
#define DIM2  11000 	/* taille tableau yb,wr >  NOMBRE_ELEMENTS & NOMBRE_SURFACES & NOMBRE_SURF_HEXA*/
#define DIM3  1500	/* taille tableau we,ye >= eca                      */

#define ARTICLE_TRACTRIX_2007 	0
/*ARTICLE_TRACTRIX_2007 = 1 if the absissa of the tractrix
meridian are pre-defined*/

#if PRINCIPAL>0
#define CLASS	
#else
#define CLASS extern
#endif

#define G 9.81                     /* pesanteur  */
#define PI (4.0 * atan(1.0))
/*#define RHO 1025.0*/                   	/* masse volumique de l eau  de mer*/
/*#define RHO 1000.0*/                   	/* masse volumique de l eau  douce*/
/*#define RHO_AIR 1.208*/                   	/* masse volumique de l air  */
#define yb(zi,zj) (int)((Element[zi].extremite[(zj+2)/3])*3+zj-3*((zj+2)/3))			/*node number of the extremity zj of element zi*/
#define yc(zi,zj) (int)((Surface[zi].extremite[(zj+2)/3])*3+zj-3*((zj+2)/3))
#define yc_hexa(zi,zj) (int)((Surf_hexa[zi].extremite[(zj+2)/3])*3+zj-3*((zj+2)/3))

#define NBMAXNOEUD		20000
#define NBMAXTRIANGLE		5000
#define NBMAXTRIHEXA		5000
#define NBMAXPANNEAU		200
#define NBMAXPANHEXA		200
#define NBMAXELEMENT		2000	
#define NBMAXBARRE		5000
#define NBMAXTYPEBARRE		1900
#define NBMAXNOEUDCONTOUR	100
#define NBMAXNOEUDCOTE		100
#define NBMAXNOEUDINTERIEUR	20000
#define NBMAXLIAISON		1300
#define NBMAXTYPENOEUD		50

typedef struct 	ball {
	int    	nb;		/*balls nb*/
	double  *radius;	/*table of radius of balls*/
	double  *birth_time;	/*birth time*/
	int    	*noeud;		/*numeros du noeud de cette ball*/
	double  *x;		/*x position*/
	double  *y;		/*y position*/
	double  *z;		/*z position*/
	double  *stiffness;	/*N/m*/
	int    	*type;		/*type of the ball one born*/
	double  *ini_speed_x;	/*m/s*/
	double  *ini_speed_y;	/*m/s*/
	double  *ini_speed_z;	/*m/s*/
	} 	BALL;

typedef struct 	codend {
	int    	type;		 	/*type of cod-end*/
	double  nbr;			/*nb of mesh around*/
	double  nbl;			/*nb of mesh along*/
	double 	mf;			/*full mesh size (m)*/
	double 	mi;			/*internal mesh size (m)*/
	double 	stf;			/*one twine stiffness (N)*/
	int 	nbt;			/*1 if single twine, 2 if double twine*/
	double 	diam;			/*dimaeter of 1 twine (m)*/
	int 	sm;			/*twine nb in each selvedge*/
	double  wl;			/*size of the window in nb of diamond mesh along*/
	double  wr;			/*size of the window in nb of diamond mesh around*/
	double  distance;		/*distance of the window to the codline in nb of diamond mesh*/
	double  sql;			/*size of the window in nb of squarre mesh along*/
	double  sqr;			/*size of the window in nb of squarre mesh around*/
	double 	sqmf;			/*full mesh size of the quarre mesh (m)*/
	double 	rope_length;		/*length of the rope m*/
	double 	rope_diameter;		/*diameter of the rope m*/
	double 	rope_position;		/*position of the rope to the codline in mesh*/
	double 	rope_position2;		/*position of the second rope to the codline in mesh*/
	double 	rope_stf;		/*stiffness of the rope N*/
	} 	CODEND;

typedef struct Barre
	{
	int  noeud[3]; 							/*indice des noeuds extremite*/
	float longueur_repos;						/*longueur au repos*/
	float elongation;						/*elongation*/
	float longueur_tendue;                                           /*longueur tendue*/
	float tension;                                                  	/*tension*/
	float nrj;                                                       /*energie potentielle*/
	float pro[3];							/*proportion a la longueur de la barre*/
	int  type; 							/*type de la barre*/
	} BARRE;

typedef struct 	element {
	int    	type;		 	/*no du type de l element*/
	int    	extremite[3];		/*no des 2 points d extremites*/
	int 	*noeud;			/*indice noeud a l interieur de l element*/
	int 	*barre;			/*indice barre a l interieur de l element*/
	double  pro[3];			/*position des 2 extremites en proportion de la longueur de l element de phobos*/
	double 	diametremeca;		/*diametre mecanique m^2*/
	double 	raideur_traction;	/*raideur en traction    (N) = section * module d elasticite*/
	double 	raideur_compression;	/*raideur en compression (N) = section * module d elasticite*/
	double 	raideur_effective;	/*raideur effective = raideur en traction (compression) si element est en traction (compression)*/
	double 	wt;			/*tension dans cet element (N)*/
	double 	wtfinal;		/*tension dans cet element (N) a l avant derniere iteration */
	double 	lgrepos;		/*longueur avec tension = 0 N*/
	double 	lgtendue;		/*longueur sous tension*/
	double 	lgwet;			/*wetting length <= lgrepos*/
	double 	diametrehydro;		/*diametre hydrodynamique m*/
	double 	rhoelement;		/*masse volumique kg/m^3*/
	double 	cdnormal;		/*coef. de trainee normal*/
	double 	ftangent;		/*coef. de trainee tangent*/
	int    	nb_barre;		/*nb bar in the cable*/
	int 	flag_maillage;		/*dans phobos 1 si maille 0 si pas maille*/
	int    	type_noeud;		/*type of node in the cable*/
	double	x1;			/*coordonnee x de l extremite 1*/
	double	y1;			/*coordonnee x de l extremite 1*/
	double	z1;			/*coordonnee x de l extremite 1*/
	double	x2;			/*coordonnee x de l extremite 1*/
	double	y2;			/*coordonnee x de l extremite 1*/
	double	z2;			/*coordonnee x de l extremite 1*/
	int    	noeud_trainee;
	double	haul_speed;		/*hauling speed of the cable m/s*/
	double	haul_beg_speed;		/*hauling begin speed of the cable m/s*/
	double	haul_end_speed;		/*hauling end speed of the cable m/s*/
	double	haul_bar_limit;		/*hauling : minimal length of the actual bar m*/
	double	haul_limit;		/*hauling : minimal length of the cable m*/
	double	haul_time;		/*hauling : time at which the cable begins to reduce s*/
	double	haul_beg_times;		/*hauling : time at which the cable begins to reduce s*/
	double	haul_end_times;		/*hauling : time at which the cable ends to reduce s*/
	double	haul_energy;		/*hauling : energy required to haul this cable J*/
	double 	EI_flexion;		/*raideur a la flexion du cable em N.m.m*/
	int	haul_extremity;		/*hauling : extremity of the cable by which the cable is reduced*/
	int	haul_bar;		/*hauling : bar by which the cable is reduced, this bar changes during the progress*/
	int	haul_node;		/*hauling : node by which side the bar is reduced, this node changes during the progress*/
	int	nb_times;		/*in case of dynamic: nb of times*/
	double	haul_mini,haul_maxi;	/*in case of dynamic: minimal and maximal length of bars*/
	double	*times;			/*in case of dynamic: times table*/
	double	*haul_v;		/*in case of dynamic: hauling speed if >0 hauling if <0 shooting*/
	int	*haul_ext;		/*in case of dynamic: extremity of the cable by which the cable is hauled or shooted*/
	int	*link_flexion;		/*in case of 2 cables are connected*/
	} 	ELEMENT;

typedef struct 	coulisse {
	int    	extremite[3];			/*no des 2 points d extremites*/
	int    	nb_noeud;		/*nb de noeuds internes dans la coulisse en commencant par extremite 1*/
	int    	*noeud;			/*numeros des noeuds internes dans la coulisse en commencant par extremite 1*/
	double  *longueur;		/*distance entre noeuds en commencant par extremite 1*/
	double 	raideur_traction;	/*raideur en traction    (N) = section * module d elasticite*/
	double 	raideur_compression;	/*raideur en compression (N) = section * module d elasticite*/
	double 	raideur_effective;	/*raideur effective = raideur en traction (compression) si element est en traction (compression)*/
	double 	wt;			/*tension dans cet element (N)*/
	double 	wtfinal;		/*tension dans cet element (N) a l avant derniere iteration */
	double 	lgrepos;		/*longueur avec tension = 0 N = somme des longueurs*/
	double 	lgtendue;		/*longueur sous tension*/
	double 	diametrehydro;		/*diametre hydrodynamique m^2*/
	double 	rhocoulisse;		/*masse volumique kg/m^3*/
	double 	cdnormal;		/*coef. de trainee normal*/
	double 	ftangent;		/*coef. de trainee tangent*/
	int 	flag_maillage;		/*1 si maille 0 si pas maille*/
	int 	type_noeud;		/*type des noeud a l interieur de la coulisse*/
	float 	nrj;
	float 	elongation;
	} 	COULISSE;

typedef struct Barre_winch
	{
	int  noeud[3]; 							/*indice des noeuds extremite*/
	float longueur_repos;						/*longueur au repos*/
	float elongation;						/*elongation*/
	float longueur_tendue;                                           /*longueur tendue*/
	float tension;                                                  	/*tension*/
	float nrj;                                                       /*energie potentielle*/
	float pro[3];							/*proportion a la longueur de la barre*/
	int  type; 							/*type de la barre*/
	} BARRE_WINCH;

typedef struct 	winch {
	int    	extremite[3];		/*no des 2 points d extremites*/
	int    	nb_barre;		/*nb de noeuds internes dans la coulisse en commencant par extremite 1*/
	int    	type_noeud;		/*type of node*/
	int    	*noeud;			/*numeros des noeuds internes dans la coulisse en commencant par extremite 1*/
	int 	*barre;			/*indice barre a l interieur de l element*/
	int    	*exit;			/*0 si le noeud est dans le treuil et 1 si il est sorti du treuil*/
	double  *prop;			/*proportion de la position du noeud relative a la longueur totale*/
	double  *longueur;		/*distance entre noeuds en commencant par extremite 1*/
	double 	raideur_traction;	/*raideur en traction    (N) = section * module d elasticite*/
	double 	raideur_compression;	/*raideur en compression (N) = section * module d elasticite*/
	double 	raideur_effective;	/*raideur effective = raideur en traction (compression) si element est en traction (compression)*/
	double 	rho;			/*density (kg/m3)*/
	double 	wt;			/*tension dans cet element (N)*/
	double 	wtfinal;		/*tension dans cet element (N) a l avant derniere iteration */
	double  adjust_force;		/*force on the cable from the winch (N)*/
	double 	longueur_repos;		/*longueur avec tension = 0 N = somme des longueurs*/
	double 	diam_hydro;		/*diametre hydrodynamique m^2*/
	double 	rhocoulisse;		/*masse volumique kg/m^3*/
	double 	cdnormal;		/*coef. de trainee normal*/
	double 	ftangent;		/*coef. de trainee tangent*/
	int flag_maillage;			/*1 si maille 0 si pas maille*/
	} 	WINCH;

typedef struct 	voisin {
	int exist;		/*0 si pas de voisin 1 si voisin*/
	int elem_voisin;	/*numero de l element voisin*/
	int sommet_oppose;	/*1 2 ou 3 = sommet oppose au voisin*/
	double U_oppose;	/*coordonnee filaire du sommet_oppose*/
	double V_oppose;	/*coordonnee filaire du sommet_oppose*/
	} 	VOISIN; 
	
typedef struct 	surface {
	int    	panneau;		/*no du panneau ou est situe ce triangle*/
	int    	type;		 	/*no du type de surface identique a panneau*/
	int    	extremite[4];		/*no des 3 points aux sommets*/
	int 	numerotation_locale; 	/*numero du triangle dans le panneau*/
	double 	U[4];			/*U[1] = lon[1] U[2] = lon[3] U[3] = lon[5] coordonnees des sommets en nombre de mailles selon U*/
	double 	V[4];			/*V[1] = lon[2] V[2] = lon[4] V[3] = lon[6] coordonnees des sommets en nombre de mailles selon V*/
	double 	lon[7];			/*attention redeondant avec U et V !!!! coordonnees filaires des 3 sommets dans le sens des diagonales aux mailles*/
	double 	nb_cote_u_ou_v;		/*nb de cotes de mailles u ou v dans ce triangle : nb cote u = nb cotev*/
	double 	diametremeca;		/*diametre mecanique m^2*/		
	double 	raideur_traction;	/*raideur en traction    (N) = section * module d elasticite*/
	double 	raideur_compression;	/*raideur en compression (N) = section * module d elasticite*/
	double 	EI_flexion;		/*raideur a la flexion des fils em N.m.m*/
	double 	raideur_ouverture;	/*raideur a l ouverture des maille em N.m/rad*/
	double 	neutral_angle;		/*angle au repos du panneau en rad*/
	double 	tension1;		/*tension dans les fils u (N)*/
	double 	tension2;		/*tension dans les fils v (N)*/
	double 	lgrepos;		/*longueur de la maille avec tension = 0 N*/
	double 	n[4];			/*n[1] = nx n[2] = ny n[3] = nz composante du cote de maille n*/
	double 	m[4];			/*m[1] = mx m[2] = my m[3] = mz composante du cote de maille m*/
	double 	nx;			/*ATTENTION: REDONDANT avcec nx et mx!!!!!!!!composante de la longueur du cote de maille u selon l axe x*/
	double 	ny;			/*composante de la longueur du cote de maille u selon l axe y*/
	double 	nz;			/*composante de la longueur du cote de maille u selon l axe z*/
	double 	mx;			/*composante de la longueur du cote de maille v selon l axe x*/
	double 	my;			/*composante de la longueur du cote de maille v selon l axe y*/
	double 	mz;			/*composante de la longueur du cote de maille v selon l axe z*/
	double 	Nx;			/*composante selon x de la normale normee au triangle*/
	double 	Ny;
	double 	Nz;
	double 	diametrehydro;		/*diametre hydrodynamique m*/
	double 	largeurnoeud;		/*largeur du noeud  m*/
	double 	rhosurface;		/*masse volumique kg/m^3*/
	double 	cdnormal;		/*coef. de trainee normal*/
	double 	ftangent;		/*coef. de trainee tangent*/
	double 	energy_pliage;		/*energie potentielle liee au pliage de 2 triangles joints*/
	double 	energy_ouverture;	/*energie potentielle liee a l'ouverture des mailles*/
	double 	nrj1;			/*energie potentielle du cote de maille m*/
	double 	nrj2;			/*energie potentielle du cote de maille n*/
	double 	energy_elastique;	/*energie potentielle liee a l elongation des fils*/
	double 	energy_contact;		/*energie potentielle liee au contact entre les fils*/
	double 	defaut_disc;		/*mesure du defaut de discretisation*/
	int 	tarp;			/*if 1 the panel is water proof like a tarp if 0 it is a netting*/	
	VOISIN	voisin_1;		/*info sur le voisin de surface oppose au sommet 1*/
	VOISIN	voisin_2;		/*info sur le voisin de surface oppose au sommet 2*/
	VOISIN	voisin_3;		/*info sur le voisin de surface oppose au sommet 3*/
	double current_reduction; 	/*ratio relatively to the upstream current*/
	double panel_drag; 		/*drag of each panel*/
	double diam_knot; 		/*diameter of the knot*/
	} 	SURFACE;

typedef struct 	surf_hexa {
	int    	type;		 							/*no du type de surface*/
	int    	extremite[4];								/*no des 3 points aux sommets*/
	double 	U[4];									/*attention redondant avec lon!!!!!!!!!coordonnees des sommets en nombre de mailles selon U*/
	double 	V[4];									/*attention redondant avec lon!!!!!!!!!coordonnees des sommets en nombre de mailles selon V*/
	double 	lon[7];									/*coordonnees filaires des 3 sommets dans le sens des diagonales aux mailles*/
	double 	nb_cote_l_m_ou_n;							/*nb de cotes de mailles l, m ou n dans ce triangle : nb cote l = nb cote m = nb cote n*/
	double 	diametremeca;								/*diametre mecanique m^2*/		
	double 	raideur_traction;							/*raideur en traction    (N) = section * module d elasticite*/
	double 	raideur_compression;							/*raideur en compression (N) = section * module d elasticite*/
	double 	raideur_traction_l,raideur_traction_m,raideur_traction_n;		/*raideur en traction des fils constituant le filet de ce panneau*/
	double 	raideur_compression_l,raideur_compression_m,raideur_compression_n;	/*raideur en compression des fils constituant le filet de ce panneau*/
	double 	tension1;								/*tension dans les fils l (N)*/
	double 	tension2;								/*tension dans les fils m (N)*/
	double 	tension3;								/*tension dans les fils n (N)*/
	double 	lo_repos,mo_repos,no_repos;						/*cote de maille l,m,n du filet de ce panneau*/
	double	lg_tendue1,lg_tendue2,lg_tendue3;					/*longueur du cote de maille l, m et n*/
	double 	l[4];									/*attention redondant avec lx ly et lz composante du cote de maille l*/
	double 	m[4];									/*composante du cote de maille m*/
	double 	n[4];									/*composante du cote de maille n*/
	double 	lx,ly,lz;								/*composante de la longueur du cote de maille l selon l axe x*/
	double 	mx,my,mz;								/*composante de la longueur du cote de maille m selon l axe x*/
	double 	nx,ny,nz;								/*composante de la longueur du cote de maille n selon l axe x*/
	double	nrj1,nrj2,nrj3;                               				/*energie potentielle du cote de maille l m et n*/
	double	nrj;									/*energie potentielle des 3 cotes de maille l m et n*/
	double 	diam_hydro_l,diam_hydro_m,diam_hydro_n;					/*diametre hydro des fils du filet de ce panneau*/
	double 	diametrehydro;								/*diametre hydrodynamique m*/
	double 	largeurnoeud;								/*largeur du noeud  m*/
	double 	rhosurface;								/*masse volumique kg/m^3*/
	double 	cdnormal;								/*coef. de trainee normal*/
	double 	ftangent;								/*coef. de trainee tangent*/
	int 	tarp;									/*if 1 the panel is water proof like a tarp if 0 it is a netting*/
	} 	SURFACE_HEXA;

typedef struct 	noeud {
	int    	type;		 	/*no du type de noeud*/
	int    	new_numero;		/*renvoi le nouveau   numero de point apres renumerotation*/
	int    	old_numero;		/*renvoi le precedent numero de point apres renumerotation*/
	double 	U,V;			/*coordonnees filaires(meshes)*/
	double 	u,v;			/*coordonnees filaires(fils)*/
	double 	x,y,z;			/*coordonnees (m)*/
	double	xcal,ycal,zcal;		/*coordonnee cartesienne calculee (m)*/
	double 	mx,my,mz;		/*masses (kg)*/
	double 	majx,majy,majz;		/*masses ajoutees ses (kg)*/
	double 	lonx,lony,lonz;		/*longueurs du parralellepipede (m)*/
	double 	lgwet;			/*wet length (m) <= fabs(sz)*/
	double 	imersion;		/*imersion (m) = wf - mh <0 if under water*/
	double 	cdx,cdy,cdz;		/*coef de trainee*/
	double 	fextx,fexty,fextz;	/*Effort exterieur (N)*/
	int    	senx,seny,senz;		/*Sens de la limite des deplacement du noeud si >0 limite inferieure*/
	double 	limx,limy,limz;		/*Limite des deplacement du noeud (m)*/
	int    	fixx,fixy,fixz;		/*autorisation de deplacement 0 : libre, 1 : fixe*/
	int    	symx,symy,symz;		/*Symetrie si 1, sinon 0*/
	double 	fhx,fhy,fhz;		/*effort hydro sur le noeud (N)*/
	int	flag_sta; 		/*dans phobos: 1 si visite, 0 sinon*/
	double	beg_times,end_times;	/*in case of modification of the node in dynamic: times of the beginning of the modification and times of ending*/
	double 	beg_vx,beg_vy,beg_vz;	/*in case of modification of the node in dynamic: speed along x y z at the begining of the modification*/
	double 	end_vx,end_vy,end_vz;	/*in case of modification of the node in dynamic: speed along x y z at the end of the modification*/
	int 	nb_times;		/*in case of modification of the node in dynamic: nb of times*/
	double 	*times;			/*in case of modification of the node in dynamic: times table*/
	double 	*speedx,*speedy,*speedz;/*in case of modification of the node in dynamic: speed of the node at each times*/
	} 	NOEUD; 
	
typedef struct 	houle {
	double 	hauteur;	/*hauteur de la houle (m)*/
       	double  hh1;            /*hauteur de la houle (m) rampe comprise*/
	double 	periode;	/*periode (s)*/
	double 	direction;	/*direction dans le plasn horizontal relativement a l axe X (deg.)*/
	double 	lambda;		/*longueur d onde (m)*/
	double 	omega;		/*pulsation (rad/s)*/
	double 	k;		/*nombre d onde*/
	double 	depth;		/*profondeur du site (m)*/
	float   Depth1;		/*profondeur d eau en m > 0  attention probablement redondant avec depth*/	
	} 	HOULE;	

typedef struct 	courant {
	double 	vitesse;	/*amplitude (m/s)*/
	double 	direction;	/*direction dans le plan horizontal relativement a l axe X (deg.)*/
	} 	COURANT;	

typedef struct 	vent {
	double 	vitesse;	/*amplitude (m/s)*/
	double 	direction;	/*direction dans le plan horizontal relativement a l axe X (deg.)*/
	} 	VENT;	

typedef struct 	prise {
	double 	volume;			/*volume demande dans *.don(m3)*/
	double 	volume_effectif;	/*volume effectif (m3)*/
	double 	seuil;			/*seuil (m3)*/
	double 	cd;			/*coef de trainee sur la prise*/
	double 	front;			/*position du front de la prise (m)*/
	double 	diametre;		/*diametre de la prise (m)*/
	double 	front_diameter;		/*diametre au niveau du front (m)*/
	double 	epaisseur;		/*distance du front a l extremite de la prise (m)*/
	double 	radial_radius;		/*radial radius of the ellipsoide inner surface (m)*/
	double 	axial_radius;		/*radial radius of the ellipsoide inner surface (m)*/
	double 	distance_front;		/*distance between the center of the ellipsoide and the front of the cod-end (m)*/
	int	nb_point;		/*nb of points in the perimeter of the front*/
	double	*perimeter_y;		/*y position of a point of the perimeter*/
	double	*perimeter_z;		/*z position of a point of the perimeter*/
	int	nb_panel_meridian;	/*nb of panels used by the meridian*/
	int	*panel_meridian;	/*panels number used by the meridian*/
	int	nb_point_meridian;	/*nb of points in the meridian*/
	double	*meridian_r;		/*radius of the meridian*/
	double	*meridian_x;		/*x position of the meridian*/
	double	*meridian_y;		/*y position of the meridian*/
	double	*meridian_z;		/*z position of the meridian*/
	int	nb_panel_curvilinear;	/*nb of panels used by the curvilinear length of the cod end*/
	int	*panel_curvilinear;	/*panels number used by the curvilinear length of the cod end*/
	int	nb_point_curvilinear;	/*nb of points in the curvilinear length of the cod end*/
	double	*curvilinear_r;		/*radius of the curvilinear length of the cod end*/
	double	*curvilinear_x;		/*x position of the curvilinear length of the cod end*/
	double 	PR;			/*prise en kg de poisson*/
	double 	PE;			/*perimetre tendu du cod-end*/
	double 	TA;			/*taille moyenne en kg des poisson*/
	double 	RA;                     /*mesh opening stiffness N.m2*/		
	double 	EI;			/*mesh opening stiffness N.m2*/
	double 	Ox;			/*x coordinate of the ellipsoide center*/
	double 	Oy;			/*y coordinate of the ellipsoide center*/
	double 	Oz;			/*z coordinate of the ellipsoide center*/
	double	*catch;			/*catches*/
	double 	max_volume;		/*maximal volume available in the cod-end*/
	double 	curvilinear_codend_length_total;	/*curvilinear length of the cod end*/
	double 	curvilinear_codend_length_occult;	/*curvilinear length of the occulted part of the cod end*/
	int	panels[3];		/*the 2 panels where the limit is calculated*/
	double 	limit_panels;		/*limit between the 2 panels*/	
	double 	nb_mesh_front;		/*position of the front in nb of mesh*/
	int	dir_mesh_front;		/*direction along the position of the front in nb of mesh is calculated 1 : U and 2: V*/
	int	nb_panel_catch2;	/*nb of panels used by catch2*/
	int	*panel_catch2;		/*n° of panels used by catch2*/
	double	drag;			/*drag on the catch (N)*/
	double	catch_dynamic;		/*evolution of the catch in m3/s*/
	double	catch_density;		/*density of the catch when outside of water*/
	} 	PRISE;	

typedef struct 	spheric_limit {
	double 	x;			/*x coordinate of the sphere centre*/	
	double 	y;			/*y coordinate of the sphere centre*/	
	double 	z;			/*z coordinate of the sphere centre*/	
	double 	radius;			/*radius of the sphere*/	
	double 	kc;			/*compression stiffness of the sphere*/	
	double 	kt;			/*traction    stiffness of the sphere*/	
	} 	SPHERIC_LIMIT;	
	
typedef struct 	bottom {
	double 	coef_frottement;	/*coef de frottement sur le fond des noeuds : effort horizontal / effort vertical*/	
	double 	raideur;		/*raideur a l enfoncement des noeuds (N/m)*/
	double	drag;			/*total drag on the bottom (N)*/
	double	moving;			/*if 1 the bottom is moving (for a trawl for example) by default is 0 (for a fish cage)*/
	} 	BOTTOM;	
	
typedef struct 	commentaire {
	char texte[156];
	} 	COMMENTAIRE;	
	
typedef struct panneau
	{
	int nb_noeud_contour; 				/*nb de noeuds du contour du panneau*/
	int nb_noeud_interieur; 			/*nb de noeuds interieur au panneau*/
	int nb_noeud_cote; 				/*nb de noeuds des cotes du panneau*/
	int *noeud_contour;				/*liste ordonnee des indices des noeuds du contour*/
	int *suivant_contour;				/*noeuds de cote qui suivent les noeuds du contour*/
	int *type_suivant_contour;			/*type des noeuds de cote qui suivent les noeuds du contour*/
	int *noeud_cote;				/*liste des indices des noeuds des cotes*/
	float *prop_cote;				/*liste des positions relatives des noeuds des cotes / longueur du cote*/
	int *noeud_interieur;				/*liste des indices des noeuds interieurs*/
	int *numero_triangle;				/*liste des indices des noeuds interieurs*/
	int nb_triangle_interieur; 			/*nb de triangles interieurs*/
	int triangle_interieur[NBMAXNOEUDINTERIEUR][4];	/*sommets des triangles interieurs dans la numerotation totale*/
	int nb_triangle_contour; 			/*nb de triangles poses sur le contour*/
	int triangle_contour[NBMAXNOEUDCONTOUR][4];	/*sommets des triangles poses sur le contour dans la numerotation locale*/
	float pas_maillage;				/*pas du maillage des noeuds interieurs*/
	int type_maillage;				/*type du maillage*/
	int flag_maillage;				/*1 si maille 0 si pas maille*/
	int flag_filet_contour;				/*1 si la triangulation sur le contour    est calculee 0 sinon*/
	int flag_filet;					/*1 si la triangulation sur ts les points est calculee 0 sinon*/
	float raideur_traction;				/*raideur en traction des fils constituant le filet de ce panneau*/
	float raideur_compression;			/*raideur en compression des fils constituant le filet de ce panneau*/
	float raideur_ouverture;			/*raideur a l ouverture des mailles du filet de ce panneau*/
	float EI_flexion;				/*raideur a la flexion des fils em N.m.m*/
	float longueur_repos;				/*cote de maille du filet de ce panneau*/
	float diam_hydro;				/*diametre hydro des fils du filet de ce panneau*/
	float largeurnoeud;				/*largeur des noeuds du filet de ce panneau*/
	float rho;					/*masse volumique des fils constituant le filet de ce panneau*/
	float cdnormal;					/*coef de trainee normale des fils constituant le filet de ce panneau*/
	float ftangent;					/*coef de trainee tangentielle des fils constituant le filet de ce panneau*/
	double 	energy_pliage;				/*energie potentielle liee au pliage de 2 triangles joints*/
	double 	energy_ouverture;			/*energie potentielle liee a l'ouverture des mailles*/
	double 	energy_elastique;			/*energie potentielle liee a l elongation des fils*/
	double 	energy_contact;				/*energie potentielle liee au contact entre les fils*/
	float surf_fils;				/*surface de fils de ce panneau*/
	double 	neutral_angle;				/*angle au repos du panneau en rad*/
	int type_noeud;					/*type des noeud a l interieur du panneau*/
	int tarp;					/*if 1 the panel is water proof like a tarp if 0 it is a netting*/
	int parallel[4];				/*define if the symmetry is along U (value 1), V (2), u (3) or v (4) 
							if there is no symmetry (0) along X axis [1], Y [2] anz Z [3]*/
	} PANNEAU;
	
typedef struct Pan_Hexa
	{
	int nb_noeud_contour; 				/*nb de noeuds du contour du panneau*/
	int nb_noeud_interieur; 			/*nb de noeuds interieur au panneau*/
	int nb_noeud_cote; 				/*nb de noeuds des cotes du panneau*/
	int *noeud_contour;				/*liste ordonnee des indices des noeuds du contour*/
	int *suivant_contour;				/*noeuds de cote qui suivent les noeuds du contour*/
	int *type_suivant_contour;			/*type des noeuds de cote qui suivent les noeuds du contour*/
	int *noeud_cote;				/*liste des indices des noeuds des cotes*/
	float *prop_cote;				/*liste des positions relatives des noeuds des cotes / longueur du cote*/
	int *noeud_interieur;				/*liste des indices des noeuds interieurs*/
	int nb_tri_hexa_interieur; 			/*nb de triangles interieurs*/
	int tri_hexa_interieur[NBMAXNOEUDINTERIEUR][4];	/*sommets des triangles interieurs dans la numerotation totale*/
	int nb_tri_hexa_contour; 			/*nb de triangles poses sur le contour*/
	int tri_hexa_contour[NBMAXNOEUDCONTOUR][4];	/*sommets des triangles poses sur le contour dans la numerotation locale*/
	float pas_maillage;				/*pas du maillage des noeuds interieurs*/
	int type_maillage;				/*type du maillage*/
	int flag_maillage;				/*1 si maille 0 si pas maille*/
	int flag_filet_contour;				/*1 si la triangulation sur le contour    est calculee 0 sinon*/
	int flag_filet;					/*1 si la triangulation sur ts les points est calculee 0 sinon*/
	float raideur_traction_l,raideur_traction_m,raideur_traction_n;		/*raideur en traction des fils constituant le filet de ce panneau*/
	float raideur_compression_l,raideur_compression_m,raideur_compression_n;/*raideur en compression des fils constituant le filet de ce panneau*/
	float lo_repos,mo_repos,no_repos;		/*cote de maille l,m,n du filet de ce panneau*/
	float diam_hydro_l,diam_hydro_m,diam_hydro_n;	/*diametre hydro des fils du filet de ce panneau*/
	float rho;					/*masse volumique des fils constituant le filet de ce panneau*/
	float cdnormal;					/*coef de trainee normale des fils constituant le filet de ce panneau*/
	float ftangent;					/*coef de trainee tangentielle des fils constituant le filet de ce panneau*/
	float surf_fils;				/*surface de fils de ce panneau*/
	int type_noeud;					/*type des noeud a l interieur du panneau*/
	int tarp;					/*if 1 the panel is water proof like a tarp if 0 it is a netting*/
	} PANNEAU_HEXA;

typedef struct lien
	{
	int   nb_liaison;		/*nb de noeud utilisant cette liaison*/
	char *type; 			/*types des structures liees*/
	int  *structure; 		/*indice des structures liees*/
	int  *extremite; 		/*indice des noeuds lies (numerotation locale)*/
	int  *noeud; 			/*indice des coins lies (numerotation totale)*/
	} LIEN;

typedef struct sortie_texte
	{			
	int  nb_distance;			/*nb de distance entre 2 points affichees*/
	COMMENTAIRE *comment_distance;		/*commentaires associes aux distances*/
	int *noeud1_distance;			/*premiere extremite de la distance en global*/		
	int *noeud2_distance;			/*seconde extremite de la distance en global*/		
	int *decimale_distance;			/*nb de decimale pour l affichage de la distance*/
	char *type_structure1_distance; 	/*types des structures */
	int  *numero_structure1_distance; 	/*indice des structures */
	char *type_structure2_distance; 	/*types des structures */
	int  *numero_structure2_distance; 	/*indice des structures */
			
	int  nb_effort;				/*nb d effort selon un axe a un point affiches*/
	COMMENTAIRE *comment_effort;		/*commentaires associes aux distances*/
	int *noeud_effort;			/*premiere extremite de la distance en global*/		
	int *axe_effort;			/*seconde extremite de la distance*/		
	int *decimale_effort;			/*nb de decimale pour l affichage de la distance*/
	char *type_structure_effort; 		/*types des structures */
	int  *numero_structure_effort; 		/*indice des structures */

	int  nb_tension_element;		/*nb de tension dans un element affichees*/
	COMMENTAIRE *comment_tension_element;	/*commentaires associes aux distances*/
	int *element_tension;			/*premiere extremite de la distance*/		
	int *element_extremite;			/*premiere extremite de la distance en local : 1 ou 2*/		
	int *decimale_tension_element;		/*nb de decimale pour l affichage de la distance*/

	int  nb_tension_coulisse;		/*nb de tension dans une coulisse affichees*/
	COMMENTAIRE *comment_tension_coulisse;	/*commentaires associes aux distances*/
	int *coulisse_tension;			/*premiere extremite de la distance*/		
	int *coulisse_extremite;		/*premiere extremite de la distance*/		
	int *decimale_tension_coulisse;			/*nb de decimale pour l affichage de la distance*/		

	int  nb_position;			/*nb de position selon un axe a un point affichees*/
	COMMENTAIRE *comment_position;		/*commentaires associes aux distances*/
	int *noeud_position;			/*premiere extremite de la distance*/		
	int *axe_position;			/*seconde extremite de la distance*/		
	int *decimale_position;			/*nb de decimale pour l affichage de la distance*/
	char *type_structure_position; 		/*types des structures */
	int  *numero_structure_position; 	/*indice des structures */
		
	int  nb_longueur;			/*nb de longueur de barres affichees*/
	COMMENTAIRE *comment_longueur;		/*commentaires associes aux longueurs*/
	int *element_longueur;			/*numero de l element*/		
	int *decimale_longueur;			/*nb de decimale pour l affichage de la longueur*/
	
	int  nb_longueur_cable;			/*nb de longueur de cables affichees*/
	COMMENTAIRE *comment_longueur_cable;	/*commentaires associes aux longueurs*/
	int *element_longueur_cable;		/*numero du cable*/		
	int *decimale_longueur_cable;		/*nb de decimale pour l affichage de la longueur en m*/
	double *valeur_longueur_cable;		/*longueur en m*/
	
	int  nb_energie_elong_diamond;		/*nb d energies d elongation par panneaux de filets losange affichees*/
	COMMENTAIRE *comment_energie_elong_diamond;	/*commentaires associes aux energies*/
	int *panneau_energie_elong;		/*numero du panneau*/		
	int *decimale_energie_elong;		/*nb de decimale pour l affichage de l energie en J*/
	
	int  nb_energie_fold_diamond;		/*nb d energies d foldation par panneaux de filets losange affichees*/
	COMMENTAIRE *comment_energie_fold_diamond;	/*commentaires associes aux energies*/
	int *panneau_energie_fold;		/*numero du panneau*/		
	int *decimale_energie_fold;		/*nb de decimale pour l affichage de l energie en J*/
	
	int  nb_energie_open_diamond;		/*nb d energies d openation par panneaux de filets losange affichees*/
	COMMENTAIRE *comment_energie_open_diamond;	/*commentaires associes aux energies*/
	int *panneau_energie_open;		/*numero du panneau*/		
	int *decimale_energie_open;		/*nb de decimale pour l affichage de l energie en J*/
	
	int  nb_energie_contact_diamond;		/*nb d energies d openation par panneaux de filets losange affichees*/
	COMMENTAIRE *comment_energie_contact_diamond;	/*commentaires associes aux energies*/
	int *panneau_energie_contact;		/*numero du panneau*/		
	int *decimale_energie_contact;		/*nb de decimale pour l affichage de l energie en J*/
	
	int  nb_parametre;			/*nb de position selon un axe a un point affichees*/
	COMMENTAIRE *comment_parametre;		/*commentaires associes aux distances*/
	int *decimale_parametre;		/*nb de decimale pour l affichage de la distance*/

	int effort_structure;			/*si 1 affiche l effort sur toute la structure (N) selon les axes X Y et Z*/	
	int diametre_prise;			/*si 1 affiche diametre_prise (m)*/	
	int epaisseur_prise;			/*si 1 affiche epaisseur_prise (m)*/	
	int vitesse_courant;			/*si 1 affiche vitesse_courant (m/s)*/	
	int vitesse_vent;			/*si 1 affiche vitesse_vent (m/s)*/	
	int volume_capture;			/*si 1 affiche volume_capture (m3)*/	
	int surface_filtree;			/*si 1 affiche surface_filtree (m2)*/	
	int volume_x;				/*si 1 affiche le volume calcule selon l axe x (m3)*/	
	int volume_y;				/*si 1 affiche le volume calcule selon l axe y (m3)*/	
	int volume_z;				/*si 1 affiche le volume calcule selon l axe z (m3)*/	
	int volume_0;				/*si 1 affiche le volume calcule selon le courant (m3)*/	
	int inner_surface;			/*si 1 affiche les dimensions de l'ellipsoide de la surface interne de la prise (m)*/	
	int inner_surface_triangulation;	/*si 1 trianguularise l'ellipsoide de la surface interne de la prise*/	
	int meridian;				/*si 1 affiche la meridian (m,m)*/	
	int meridian_X;				/*si 1 affiche la meridian (m,m)*/	
	int meridian_Y;				/*si 1 affiche la meridian (m,m)*/	
	int meridian_Z;				/*si 1 affiche la meridian (m,m)*/	
	int curvilinear_codend_length;		/*si 1 affiche la longueur curviligne du codend, de sa partie occultee et du rapport des 2*/	
	int catch_drag;				/*si 1 affiche the drag of the catch*/	
	int bottom_drag;			/*si 1 affiche the drag of the bottom*/	
	int element_drag;			/*si 1 affiche the drag of the bottom*/	
	int surface_drag;			/*si 1 affiche the drag of the bottom*/	
	int node_drag;				/*si 1 affiche the drag of the nodes*/	
	int panel_drag;				/*si 1 affiche the drag of the panels*/	
	
	} SORTIE_TEXTE;

typedef struct Inversion_triangles
	{
	int  nb_inversion_triangles;	/*nb d inversions de triangles*/
	int  *premier; 			/*indice du premier triangle dans la numerotation globale*/
	int  *second; 			/*indice du second triangle dans la numerotation globale*/
	} INVERSION_TRIANGLES;

typedef struct opening_angle
	{
  	int  nb_panel;		/*nb of diamond mesh panel involved*/
  	int  *panel; 		/*numero of the involved panels*/
  	double  pas; 		/*angle step to class the angles*/
  	double **tab;		/*nb of mesh per angle and per panel*/
  	int nb_tab;		/*nb ol class = (int) 90/pas*/
	} OPENING_ANGLE;

typedef struct opening_mesh
	{
  	int  nb_panel;		/*nb of diamond mesh panel involved*/
  	int  *panel; 		/*numero of the involved panels*/
  	double  pas; 		/*surface step to class the surfaces*/
  	double **tab;		/*nb of mesh per surface and per panel*/
  	int nb_tab;		/*nb ol class of surfaces*/
	} OPENING_MESH;

typedef struct opening_angle_stripe
	{
  	int  nb_panel;		/*nb of diamond mesh panel involved*/
  	int  *panel; 		/*numero of the involved panels*/
  	double  pas; 		/*angle step to class the angles*/
  	double **tab;		/*nb of mesh per angle and per stripe*/
  	int nb_tab;		/*nb ol class = (int) 90/pas*/
  	double  stripe_step; 	/*step of stripe in m*/
  	int  nb_stripe;		/*nb of stripes front the front*/
  	double  *fromx; 	/*largest limit of the stripe*/
  	double  *tox; 		/*smallest limit of the stripe*/
	} OPENING_ANGLE_STRIPE;

typedef struct Type_Noeud_XYZ_SUPINF
	{
	/*9 code :
	si 1 : limite SUP selon X	si 2 : limite INF selon X
	si 3 : limite SUP selon Y	si 4 : limite INF selon Y
	si 5 : limite SUP selon Z	si 6 : limite INF selon Z
	si 7 : limite SUP selon X  et limite INF selon X
	si 8 : limite SUP selon X  et limite INF selon X
	si 9 : limite SUP selon X  et limite INF selon X
	*/
	int code; 			/*code*/
	double limite; 		/*limite de position des noeud*/
	double limite_basse; 	/*limite basse de position des noeud*/
	double limite_haute; 	/*limite haute de position des noeud*/
	int type; 			/*type du noeud depassant la limite*/
	} TYPE_NOEUD_XYZ_SUPINF;

typedef struct chalut
	{
	int nb_ordre_objet;             /*nombre d'objets(panneau,element,coulisse,pan_hexa)*/
	int nb_fils; 			/*nombre de fils dans les triangles contour constituants le chalut*/
	int T90_nb_fils; 		/*nombre de fils dans les triangles contour selon l'axe T90*/
	int nb_panneau; 		/*nombre de panneaux a maille losange constituants le chalut*/
	int nb_pan_hexa; 		/*nombre de panneaux a maille hexagonale constituants le chalut*/
	int nb_element; 		/*nombre de elements constituants le chalut*/
	int nb_winch; 			/*nb of winches in the structure*/
	int nb_barre_winch; 		/*nb of bars in winches in the structure*/
	int nb_coulisse; 		/*nombre de coulisses constituants le chalut*/
	int nb_liaison; 		/*nombre de liaisons dans le chalut*/
	int nb_lien; 			/*nombre de liens dans le chalut >=  liaisons*/
	int nb_total;			/*nombre de noeuds dans la numerotation totale dans le chalut*/
	int nb_global;			/*nombre de noeuds dans la numerotation globale dans le chalut apres renumerotation*/
	int nb_type_noeud;		/*nombre de type de noeud dans le chalut*/
	int nb_barre;			/*nombre de barre dans le chalut*/
	int nb_surface;			/*nombre de surface dans le chalut*/
	int nb_surf_hexa;		/*nombre de surface a maille hexagonale dans le chalut*/
	float surface_fils;		/*surface de fils du chalut tel que maille*/
	int orientation;		/*orientation du dessin 1 (2,3) perpendiculaire a l axe x (y,z)*/
	int nb_catches;			/*nb of catches calculated*/
	int version;			/*version*/
	double link_distance;		/*distance used for automatic link between points*/
	int nb_sphere_element;		/*nb of sphere element cases*/
	} CHALUT;

typedef struct filiere
   	{
	int 	  orientation;		/*orientation du dessin 1 (2,3) perpendiculaire a l axe x (y,z)*/
   	int       nombrePoints;
   	int       nombreNoeuds;
   	int       nombreBalls;
   	int	  nombreElements;
	int 	  nb_winch; 		/*nb of winches in the structure*/
	int 	  version; 		/*version number of the *.don*/
   	int	  nombreCoulisses;
   	int	  nombreSurfaces;
   	int	  nombreSurfHexa;
   	int	  NbTypeNoeud;
   	int	  NbTypeelem;
   	int	  NbTypesurf;
   	int	  NbTypesurf_hexa;
	int 	  nb_liaison; 		/*nombre de liaisons dans le chalut*/
   	double    diviseur;
   	int       lmn_calcules;		/*= 1 si l m n des mailles hexagonales ont ete calcules sinon 0*/
	int 	  nb_tarp_diamond;	/*nb of tarps on diamond mesh panel*/
	int 	  nb_tarp_hexa;		/*nb of tarps on hexagonal mesh panel*/
	int 	  nb_catch2_length;	/*nb of catch, each catch for a determined panels*/
	int 	  nb_catch2_surface;	/*nb of catch, each catch for a determined panels*/
	int 	  nb_catch2_volume;	/*nb of catch, each catch for a determined panels*/
	int 	  nb_catch2_weight;	/*nb of catch, each catch for a determined panels*/
	int 	  nb_cage_volume;	/*nb of cage, each cage for a determined panels*/
	double 	  element_drag;		/*drag on elements (cables and bars)*/
	double    surface_drag;		/*drag on surface (netting)*/
	double    node_drag;		/*drag on node (floats, dead weights)*/
	double    total_drag;		/*drag on the whole structure*/
	double	  filtered_surface;	/*total filtered surface of the structure*/
	int 	  nb_value;		/*nb of linear value defined  by 2 depths and 2 values*/
	int 	  nb_recouvrement_x;	/*nb of recouvrement_x between a element relatively to an another one*/
	/* debut modifdp du 12 mars 2010*/	
	int 	  nb_vector_tension_bar;/*nb of tension in bars*/
	/* fin modifdp du 12 mars 2010*/	
	int 	  hydro_forces;		/*if 1 the hydro forces are calculated*/
	int 	  cut_plan_symmetry;	/*if 1 (2, 3) the intersection of triangular elements of diamond meshes with symmetry plan X (Y, Z) is save (in nodes coordinates in m) with angles (radian) between twines*/
	int 	  drag_forces_type;	/*if 1 the hydro forces are calculated with morison, if 2 the hydro forces are calculated with zhan, if 3 the hydro forces are calculated with drop pressure*/
	int 	  nb_hauling_cable;	/*nb of hauling cables only used in dynamic*/
	int 	  nb_hauling_cable2;	/*nb of hauling cables only used in dynamic of type 2*/
	int 	  nb_speed_type_node;	/*nb of type node with speed*/
	int 	  type_solver;		/*1: gauss, 2:pardiso*/
   	} 	FILIERE;

typedef struct optimization
   	{
   	int	type;		/*type of optimization cf user guide in unix_2004*/
	int 	nb_step;	/*nb of step, default = 10*/
	double 	prop;		/*proportion of displacement relatively to the maximal size of the panel, default = 5%*/
	double 	prop_max;		/*proportion of displacement relatively to the maximal size of the panel, default = 5%*/
	double 	prop_min;		/*proportion of displacement relatively to the maximal size of the panel, default = 5%*/
	double 	prop_multip;		/*proportion of displacement relatively to the maximal size of the panel, default = 5%*/
   	int	no;		/*if type = 2 heigth of node no is constant*/
   	double	pre;		/*if type = 2 heigth of node no is constant at pre * 100 %*/
   	int	node_type;	/*if type = 2 heigth of node no is constant by modifying the exten forces on node_type*/
   	int	constraint_direction;	/*if 1 along x, if 2 along y, if 3 along z, */
   	int	constraint_node;	/*node on which there is the constraint*/
   	double	constraint_limit;	/*the valui is respected at a distance of limit*/
   	double	constraint_value;	/*target value of the constraint*/
   	int	constraint_type;	/*up to now only 1 which is the forces on node type*/
   	int	constraint_node_type;	/*type of node which will be modify to reach the target*/
   	double	constraint_max;		/*max proportion of value of constraint_node_type*/
   	double	constraint_min;		/*min proportion of value of constraint_node_type*/
   	double	constraint_ratio;	/*ratio proportion of value of constraint_node_type*/
	int 	nb_node;		/*nb of nodes used in optimization 5*/
	int 	*node;			/*no of nodes used in optimization 5*/
	int 	*dir;			/*direction of nodes used in optimization 5*/
	double 	*weighting;		/*weighting of nodes used in optimization 5*/
	int 	nb_element_bottom;	/*nb of elements which must be in contact with the bottom*/
	int 	*element_bottom;	/*no of elements which must be in contact with the bottom*/
	double	d_mesh;			/*variation of mesh in order to calculate the gradient of objective, for optimization 7*/
	double	d_obj;			/*variation of objective in order to calculate the mesh step, for optimization 7*/
	double	precis;			/*precis on the mesh variation for findind the minimum of objective, for optimization 7*/
   	double	constraint_surface_ceil;/*constraint on the surface by a ceiling value */
   	}	OPTIMIZATION;
   	
typedef struct plan_cutting
   	{
   	int	nb_plan;		/*if 0 no plan cutting, if 1 one plan cutting*/
   	double	X0,Y0,Z0;		/*point trough which the plan passes*/
  	double	Xv,Yv,Zv;		/*vector normal to the plan*/
	int 	nb_nodes;		/*nb of nodes in the plan cutting the netting*/
	double 	*x,*y,*z,*alpha;	/*position of the nodes and angle ,opening between twines in the surface following the node*/
   	}	PLAN_CUTTING;
   	
typedef struct sphere_element
   	{
	int 	*element;	/*cable on which the sphere are*/	
	int 	*nb;		/*number of sphere*/			
	double 	*diameter;	/*diameter of the each sphere floats (m)*/			
	double 	*floatability;	/*floattability of each float (N)*/			
   	}	SPHERE_ELEMENT;
   	
typedef struct value
   	{
	double 	*depth1;	/*first depth*/	
	double 	*depth2;	/*second depth*/			
	double 	*value1;	/*value for the first depth*/			
	double 	*value2;	/*value for the second depth*/			
   	}	VALUE;
   	
typedef struct recouvrement_x
   	{
	int 	*element1;	/*element1*/	
	int 	*element2;	/*element2*/	
	double 	*min;		/*minimum distance along X axe between the nodes of element1 and element 2*/	
	double 	*max;		/*maximum distance along X axe between the nodes of element1 and element 2*/			
	double 	*mean;		/*mean distance along X axe between the nodes of element1 and element 2*/			
	int 	*flag_limit;	/*if 1 there is a limit used in nerzh*/	
 	double 	*limit;		/*if flag_limit is 1 there is a limit used in nerzh which is limit*/	
   	}	RECOUVREMENT_X;
   	
/* debut modifdp du 12 mars 2010*/	
typedef struct vector_tension_bar
   	{
	int 	*bar;	/*element1*/	
   	}	VECTOR_TENSION_BAR;
/* fin modifdp du 12 mars 2010*/	
   	
typedef struct two_parameters
   	{
   	int	pa1;		/*first panel*/
   	int	pa2;		/*second panel*/
   	int	no1;		/*first corner*/
   	int	no2;		/*second second*/
   	int	co1;		/*first direction*/
   	int	co2;		/*second direction*/
   	double	pl1;		/*first plage*/
   	double	pl2;		/*second plage*/
   	double	st1;		/*first step*/
   	double	st2;		/*second step*/
   	int	code;		/*code 0 no two_parameters 1: two_parameters*/
   	int	vect1;		/*place of the first  point in vect of parameters*/
   	int	vect2;		/*place of the second point in vect of parameters*/
   	}	TWO_PARAMETERS;
   	
typedef struct ordre
	{
	char *type;
	int  *indice;
	} ORDRE;
	
typedef struct numerique {
	float DIVISEUR;			/*raideur additionnelle en N*/
	int Nbmaxiterations;		/*nb max d iterations realisees dans unix*/
	float Seuilconvergence;		/*seuil de convergence en N*/
	float Deplacement;		/*deplacement maximal autorise en m*/
	float Pascalcul;		/*pas de calcul en dynamique en s*/
	float Passtockage;		/*pas de stockage en dynamique en s*/
	float Debutstockage;		/*debut du stockage en dynamique en s*/
	float Finstockage;		/*fin du stockage et du calculen dynamique en s*/
	} NUMERIQUE;
	
/* "define" */
#define NOMBRE_BALLS   		Filiere.nombreBalls
#define NOMBRE_NOEUDS   	Filiere.nombreNoeuds
#define NOMBRE_ELEMENTS 	Filiere.nombreElements
#define NOMBRE_WINCHS 		Filiere.nb_winch
#define NOMBRE_COULISSES 	Filiere.nombreCoulisses
#define NOMBRE_SURFACES 	Filiere.nombreSurfaces
#define NOMBRE_SURF_HEXA 	Filiere.nombreSurfHexa

typedef double TCOO1[DIM1];   
typedef double TCOO2[DIM2];
typedef double TMKB[7],TMKB3[10],Tab1[4];
typedef double TMK2[DIM1][2*DIM3];
typedef int    TLARGE1[DIM1];
typedef int    TLARGE2[DIM2];
typedef double TMKK[65][65],TMKC[10][10];

