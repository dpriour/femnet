#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define DIM1  21000	// taille tableau we,ye > 3*NOMBRE_NOEUDS           //
#define DIM2  21000 	// taille tableau yb,wr >  NOMBRE_ELEMENTS & NOMBRE_SURFACES & NOMBRE_SURF_HEXA//
#define DIM3  1600	// taille tableau we,ye >= eca                      //

#define ARTICLE_TRACTRIX_2007 	0
//ARTICLE_TRACTRIX_2007 = 1 if the absissa of the tractrix meridian are pre-defined//

#if PRINCIPAL>0
#define CLASS	
#else
#define CLASS extern
#endif

#define REEL			float
#define REAL			double		//utilise dans triangle.c//

#define G 9.81                     // pesanteur  //
#define PI (4.0 * atan(1.0))
//#define RHO 1025.0		               	// masse volumique de l eau  de mer//
//#define RHO 1000.0//                   	// masse volumique de l eau  douce//
//#define RHO_AIR 1.208//                   	// masse volumique de l air  //

#define yb(zi,zj) (int)((Element[zi].extremite[(zj+2)/3])*3+zj-3*((zj+2)/3))			//node number of the extremity zj of element zi//
#define yc(zi,zj) (int)((Surface[zi].extremite[(zj+2)/3])*3+zj-3*((zj+2)/3))
#define yc_hexa(zi,zj) (int)((Surf_Hexa[zi].extremite[(zj+2)/3])*3+zj-3*((zj+2)/3))

#define NBMAXNOEUD		20000
#define NBMAXTRIANGLE		10000
#define NBMAXTRIHEXA		5000
#define NBMAXPANNEAU		200
#define NBMAXPANHEXA		200
#define NBMAXELEMENT		3300
#define NBMAXBARRE		8000
#define NBMAXTYPEBARRE		1900
#define NBMAXNOEUDCONTOUR	150
#define NBMAXNOEUDCOTE		1500
#define NBMAXNOEUDINTERIEUR	20000
#define NBMAXLIAISON		3000
#define NBMAXTYPENOEUD		50


#define TAG_NULL          0
#define TAG_STRING        1
#define TAG_INT           2
#define TAG_FLOAT         3
#define TAG_LABEL         4
#define TAG_WINDOW_LABEL  5
#define TAG_DONE          99

#define TAG_INIT    1
#define TAG_NOINIT  0


typedef struct MyProgram
	{
	int   win_width, win_height;
	}MyProgram;

typedef struct 	add_node_panel {
	int	*panel;	//no of the panel in which the node is added
	double  *U;		//coordinate in U meshes of the added node
	double  *V;		//coordinate in V meshes of the added node
	int	*type;		//type of the added node
	} 	ADD_NODE_PANEL;

typedef struct 	ball {
	int	nb;		//balls nb//
	double  *radius;	//table of radius of balls//
	double  *birth_time;	//birth time//
	int    *noeud;		//numeros du noeud de cette ball//
	double  *x;		//x position//
	double  *y;		//y position//
	double  *z;		//z position//
	double  *stiffness;	//N/m//
	int	*type;		//type of the ball one born//
	double  *ini_speed_x;	//m/s//
	double  *ini_speed_y;	//m/s//
	double  *ini_speed_z;	//m/s//
	int	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	} 	BALL;

typedef struct 	ballast {
	int	nb_cables;	//nb of cables in the ballast
	int	*cable;	//no of cable of the ballast
	double  *cable_volume;	//maximal volume of the ballast per cable
	double  volume;	//volume of the ballast
	double  speed;		//speed of variation of volume of the ballast
	int 	nb_times;	//nb of times for the dynamic
	double	*times;	//times table
	double	*volume_table;	//volume table
	double	altitude;	//if 0 : no record, if 1 : record in sta file. Defaut value is 0
	} 	BALLAST;

typedef struct Barre
	{
	int  noeud[3]; 			//indice des noeuds extremite//
	float longueur_repos;		//longueur au repos//
	float elongation;		//elongation//
	float longueur_tendue;		//longueur tendue//
	float tension;			//tension//
	float nrj;			//energie potentielle//
	float pro[3];			//proportion a la longueur du cable
	int  type;			//type de la barre (cable, element parent)
	int  netting2ropes_panel;	//in case of input netting2ropes. this value is the panel n°
	int  netting2ropes_uv;		//in case of input netting2ropes. if 1 this barre is along u, if 2 is along v 
	int flag_dessin;		//1 si dessine 0 si pas dessine//
	} BARRE;

typedef struct Barre_winch
	{
	int  noeud[3]; 							//indice des noeuds extremite//
	float longueur_repos;						//longueur au repos//
	float elongation;						//elongation//
	float longueur_tendue;                                          //longueur tendue//
	float tension;                                                  //tension//
	float nrj;                                                      //energie potentielle//
	float pro[3];							//proportion a la longueur de la barre//
	int  type; 							//type de la barre//
	} BARRE_WINCH;

typedef struct 	bottom
	{
	double 	coef_frottement;	//coef de frottement sur le fond des noeuds : effort horizontal / effort vertical//	
	double 	raideur;		//raideur a l enfoncement des noeuds (N/m)//
	double	drag;			//total drag on the bottom (N)//
	int	moving;			//if 1 the bottom is moving (for a trawl for example) by default is 0 (for a fish cage)//
	double	energy;			//power W//
	double	power;			//energy J//
	} 	BOTTOM;	

struct champ
	{
	int noeud1;			//premiere extremite //		
	int noeud2;			//seconde extremite //		
	int decimale;			//nb de decimale pour l affichage //
	double valeur;			//valeur //	
	char txt[156];			//intitule de la valeur affichee//
	};

CLASS struct champ *txt_distance;
CLASS struct champ *txt_effort;
CLASS struct champ *txt_tension;
CLASS struct champ *txt_tension_coulisse;
CLASS struct champ *txt_position;

typedef struct 	codend
	{
	int    	type;		 	//type of cod-end//
	double  nbr;			//nb of mesh around//
	double  nbl;			//nb of mesh along//
	double 	mf;			//full mesh size (m)//
	double 	mi;			//internal mesh size (m)//
	double 	stf;			//one twine stiffness (N)//
	int 	nbt;			//1 if single twine, 2 if double twine//
	double 	diam;			//dimaeter of 1 twine (m)//
	int 	sm;			//twine nb in each selvedge//
	double  wl;			//size of the window in nb of diamond mesh along//
	double  wr;			//size of the window in nb of diamond mesh around//
	double  distance;		//distance of the window to the codline in nb of diamond mesh//
	double  sql;			//size of the window in nb of squarre mesh along//
	double  sqr;			//size of the window in nb of squarre mesh around//
	double 	sqmf;			//full mesh size of the quarre mesh (m)//
	double 	rope_length;		//length of the rope m//
	double 	rope_diameter;		//diameter of the rope m//
	double 	rope_position;		//position of the rope to the codline in mesh//
	double 	rope_position2;		//position of the second rope to the codline in mesh//
	double 	rope_stf;		//stiffness of the rope N//
	} 	CODEND;


typedef struct 	commentaire
	{
	char texte[156];
	} 	COMMENTAIRE;


CLASS struct connect_panel_node
   	{
	int 	*panel;		//panel from which the node is linked//	
	int 	*node;		//node linked//	
	int 	*panel1;	//first  panel on which node is linked//	
	int 	*node1;		//first  node on which node is linked//	
	double 	*pro1;		//proportion of node1 in node coordinates//	
	int 	*panel2;	//second panel on which node is linked//	
	int 	*node2;		//second node on which node is linked//	
	double 	*pro2;		//proportion of node2 in node coordinates//	
   	}	Connect_panel_node;


typedef struct 	coulisse {
	int    	extremite[3];			//no des 2 points d extremites//
	int    	nb_noeud;		//nb de noeuds internes dans la coulisse en commencant par extremite 1//
	int    	*noeud;			//numeros des noeuds internes dans la coulisse en commencant par extremite 1//
	double  *longueur;		//distance entre noeuds en commencant par extremite 1//
	double 	raideur_traction;	//raideur en traction    (N) = section * module d elasticite//
	double 	raideur_compression;	//raideur en compression (N) = section * module d elasticite//
	double 	raideur_effective;	//raideur effective = raideur en traction (compression) si element est en traction (compression)//
	double 	wt;			//tension dans cet element (N)//
	double 	wtfinal;		//tension dans cet element (N) a l avant derniere iteration //
	double 	lgrepos;		//longueur avec tension = 0 N = somme des longueurs//
	double 	lgtendue;		//longueur sous tension//
	double 	diametrehydro;		//diametre hydrodynamique m^2//
	double 	rhocoulisse;		//masse volumique kg/m^3//
	double 	cdnormal;		//coef. de trainee normal//
	double 	ftangent;		//coef. de trainee tangent//
	int 	flag_maillage;		//1 si maille 0 si pas maille//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	int 	type_noeud;		//type des noeud a l interieur de la coulisse//
	double 	nrj;
	float 	rho;				//masse volumique//
	float 	elongation;
	} 	COULISSE;

typedef struct 	courant {
	double 	vitesse;	//amplitude (m/s)//
	double 	direction;	//direction dans le plan horizontal relativement a l axe X (deg.)//
	double 	*depth1;	//first depth//	
	double 	*depth2;	//second depth//			
	double 	*courant1;	//value for the first depth//			
	double 	*courant2;	//value for the second depth//			
	double 	*direction1;	//value for the first depth//			
	double 	*direction2;	//value for the second depth//			
	int 	nb_courant;	//nb of linear courant defined  by 2 depths, 2 courants and 2 directions//
	int 	nb_angle_speed_cd;	//speed and cd variable with angle
	double	*angle_speed_cd_alpha;	//first limit of angle for angle_speed_cd
	double	*angle_speed_cd_beta;	//second limit of angle for angle_speed_cd
	double	*angle_speed_cd_speed;	//speed curent for angle_speed_cd
	double	*angle_speed_cd_cd;	//cd for angle_speed_cd
	} 	COURANT;	

typedef struct 	deck {
	int	master_node;	//node at which the deck is linked
	double  x1;		//distance along x between the master node and the first  vertex
	double  y1;		//distance along x between the master node and the first  vertex
	double  z1;		//distance along z between the master node and the first  vertex
	double  x2;		//distance along x between the master node and the second vertex
	double  y2;		//distance along x between the master node and the second vertex
	double  z2;		//distance along z between the master node and the second vertex
	double  x3;		//distance along x between the master node and the third  vertex
	double  y3;		//distance along x between the master node and the third  vertex
	double  z3;		//distance along z between the master node and the third  vertex
	double  thickness;	//thickness of the deck (m)
	double  stiffness;	//stiffness of the deck (N/m)
	} 	DECK;

typedef struct 	element {
	int    	type;		 	//no du type de l element//
	int    	extremite[3];		//no des 2 points d extremites//
	int 	*noeud;			//indice noeud a l interieur de l element//
	int 	*barre;			//indice barre a l interieur de l element//
	double  *prop;			//position du noeud en proportion de la longueur du cable ds phobos
	int  	netting2ropes_panel;	//in case of input netting2ropes. this value is the panel n°
	int    	nb_nodes;		//nb of nodes in the cable WARNING probably not used//
	double  pro[3];			//position des 2 extremites en proportion de la longueur de l element de phobos WARNING probably not used//
	double 	diametremeca;		//diametre mecanique m^2//
	double 	raideur_traction;	//raideur en traction    (N) = section * module d elasticite//
	double 	raideur_compression;	//raideur en compression (N) = section * module d elasticite//
	double 	raideur_effective;	//raideur effective = raideur en traction (compression) si element est en traction (compression)//
	double 	wt;			//tension dans cet element (N)//
	double 	wtfinal;		//tension dans cet element (N) a l avant derniere iteration //
	double 	lgrepos;		//longueur avec tension = 0 N//
	double 	lgtendue;		//longueur sous tension//
	double 	lgwet;			//wetting length <= lgrepos//
	double 	diametrehydro;		//diametre hydrodynamique m//
	double 	rhoelement;		//masse volumique kg/m^3//
	double 	cdnormal;		//coef. de trainee normal//
	double 	ftangent;		//coef. de trainee tangent//
	int    	nb_barre;		//nb bar in the cable//
	int 	flag_maillage;		//dans phobos 1 si maille 0 si pas maille//
	int    	type_noeud;		//type of node in the cable//
	double	x1;			//coordonnee x de l extremite 1//
	double	y1;			//coordonnee y de l extremite 1//
	double	z1;			//coordonnee z de l extremite 1//
	double	x2;			//coordonnee x de l extremite 2//
	double	y2;			//coordonnee y de l extremite 2//
	double	z2;			//coordonnee z de l extremite 2//
	int    	noeud_trainee;
	double	haul_speed;		//hauling speed of the cable m/s//
	double	haul_beg_speed;		//hauling begin speed of the cable m/s//
	double	haul_end_speed;		//hauling end speed of the cable m/s//
	double	haul_bar_limit;		//hauling : minimal length of the actual bar m//
	double	haul_limit;		//hauling : minimal length of the cable m//
	double	haul_time;		//hauling : time at which the cable begins to reduce s//
	double	haul_beg_times;		//hauling : time at which the cable begins to reduce s//
	double	haul_end_times;		//hauling : time at which the cable ends to reduce s//
	double	haul_energy;		//hauling : energy required to haul this cable J//
	double 	EI_flexion;		//raideur a la flexion du cable em N.m.m//
	int	haul_extremity;		//hauling : extremity of the cable by which the cable is reduced//
	int	haul_bar;		//hauling : bar by which the cable is reduced, this bar changes during the progress//
	int	haul_node;		//hauling : node by which side the bar is reduced, this node changes during the progress//
	int	nb_times;		//in case of dynamic: nb of times//
	double	haul_mini,haul_maxi;	//in case of dynamic: minimal and maximal length of bars//
	double	*times;			//in case of dynamic: times table//
	double	*haul_v;		//in case of dynamic: hauling speed if >0 hauling if <0 shooting//
	double	*haul_d;		//in case of dynamic: hauling standad deviation of speed, in this case haul_v is the mean speed//
	int	*haul_ext;		//in case of dynamic: extremity of the cable by which the cable is hauled or shooted//
	int	*link_flexion;		//in case of 2 cables are connected//
	int	nb_link_flexion2;	//in case of 2 cables are connected : nb  link
	int	*link_flexion2;		//in case of 2 cables are connected : nb  2 element
	double	*angle_link_flexion2;	//in case of 2 cables are connected : angle between  2 elements
	int    	color;			//fonction de la tension//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//

	double  *lrepos;		//longueur repos dynamique//
	double 	*dtension;
	double 	*dlgtendue;
	double 	*dcontrainte;		//contrainte dynamique//

	double 	cable_drag;
	double 	nrj;
	double 	*dnrj;

	float symmetry_plan;			//value of the plan of symmetry for the plan//
	int lock;				/*0 there is no lock, 1 there is a lock: the length is not changed in the optimisation*/
	int lock2element;/**/			/*0 there is no lock2element, x != 0 there is a lock: the length is linked to the length of lock2element*/
	double 	optimization_length_maxi;	//if -1 no limit, if >=0 there is a limit in length of the cable
	double mass;				//mass of the element calculated with the initial length at rest, the diameter and the density
	int	constant_tension;		//1 if there is a constant tension in the bar element, 0 an usual bar element
	double 	tension_constant;		//value of the constant tension if any
	int 	nb_tab_drag_lift;		//nb of tabulated drag and lift coefficient fct of the angle between bar element and current, 0 if not
	int 	element_tab_drag_lift;		//element affected by tabulated drag and lift coefficient fct of the angle between bar element and current, 0 if not
	double 	*angle_tab_drag_lift;		//tabulation of the angle if nb_tab_drag_lift != 0
	double 	*drag_tab_drag_lift;		//tabulation of the drag coefficient if nb_tab_drag_lift != 0
	double 	*lift_tab_drag_lift;		//tabulation of the lift coefficient if nb_tab_drag_lift != 0
	double 	lcube;				//size of the cube which represents the volume of floatability of the element. It is centred on each extremity. 2*lcube³ = volume of element
	double 	pondFS[3];			//ponderation (>= 0.0 and <= 1.0) of drag force and floatability. pondFS = 0.0 if z-lcube/2 > mh. pondFS = 1.0 if z+lcube/2 < mh. otherwise pondFS = fabs(z-lcube/2)/lcube
	int	slider;				//the element belongs to the slider with this numero. if 0 this element dont belong to a slider
	int	nb_cable_contact;		//the element could have a contact with nb_cable_contact cables
	int	 *cable_contact;		//list of cables with potential contact
	int	cable2side;			//in case of input netting2ropes, side linked to this cable. if >0 cable and side in th same sens. If<0 opposite sens
	} 	ELEMENT;

typedef struct energy_bottom
	{
  	double step;		//square size (m)//
  	int  nb_square;	//nb of square//
  	int *nbx; 		//nb position along x (m)//
  	int *nby; 		//nb position along y (m)//
  	double *nrj;		//energy in square (J)//
	} ENERGY_BOTTOM;

typedef struct foot_print
	{
  	int  nb;		//nb of points along y axis//
  	double *y; 		//point position along y (m)//
  	double *z;		//point position along y (m)//
	} FOOT_PRINT;

typedef struct grid_drag
	{
  	int  nby;		//nb of cuts along y axis//
  	int  nbz; 		//nb of cuts along z axis//
  	double  pas; 		//step (m) along y and z//
  	double **tab;		//value of drag (N) per cell//
  	int nb_triangle;	//nb of triangles making door
  	int *vertex;		//vertex of triangle 3 for each triangle
  	int nb_type_point;	//number of type of nodes involv
  	int *type_point;	//type of node for the door
	} GRID_DRAG;

typedef struct 	houle {
	double 	hauteur;	//hauteur de la houle (m)//
       	double  hh1;            //hauteur de la houle (m) rampe comprise//
	double 	periode;	//periode (s)//
	double 	direction;	//direction dans le plasn horizontal relativement a l axe X (deg.)//
	double 	lambda;		//longueur d onde (m)//
	double 	omega;		//pulsation (rad/s)//
	double 	k;		//nombre d onde//
	double 	depth;		//profondeur du site (m)//
	float   Depth1;		//profondeur d eau en m > 0  attention probablement redondant avec depth//
// houle dans batz
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
	/*double X[1000][10000];
	double Y[1000][10000];
	double Z[1000][10000];
	double U[1000][10000];
	double V[1000][10000];
	double W[1000][10000];*/
double** X; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** Y; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** Z; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** U; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** V; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
double** W; // Pour déclarer notre tableau de tableau, on va créer un pointeur de pointeurs //
	int nb_trace; 		// nombre de trace de houle//
	int nb_point; 		// nombre de point de houle//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
//fin houle batz
	} 	HOULE;


typedef struct Inversion_triangles
	{
	int  nb_inversion_triangles;	//nb d inversions de triangles//
	int  *premier; 			//indice du premier triangle dans la numerotation globale//
	int  *second; 			//indice du second triangle dans la numerotation globale//
	} INVERSION_TRIANGLES;


typedef struct lien
	{
	int   nb_liaison;		//nb de noeud utilisant cette liaison//
	char *type; 			//types des structures liees//
	int  *structure; 		//indice des structures liees//
	int  *extremite; 		//indice des noeuds lies (numerotation locale)//
	int  *noeud; 			//indice des coins lies (numerotation totale)//
	double  angle_link_flexion2;	//in case of angle_link_flexion2 sum of the angle of embedment
	} LIEN;

typedef struct 	noeud {
	int    	type;		 	//no du type de noeud//
	int    	new_numero;		//renvoi le nouveau   numero de point apres renumerotation//
	int    	old_numero;		//renvoi le precedent numero de point apres renumerotation//
	double 	U,V;			//coordonnees filaires(meshes)//
	double 	u,v;			//coordonnees filaires(fils)//
	double 	x,y,z;			//coordonnees (m)//
	double	xcal,ycal,zcal;		//coordonnee cartesienne calculee (m)//
	double 	mx,my,mz;		//masses (kg)//
	double 	majx,majy,majz;		//masses ajoutees ses (kg)//
	double 	lonx,lony,lonz;		//longueurs du parralellepipede (m)//
	double 	lgwet;			//wet length (m) <= fabs(sz)//
	double 	imersion;		//imersion (m) = wf - mh <0 if under water//
	double 	cdx,cdy,cdz;		//coef de trainee//
	double 	fextx,fexty,fextz;	//Effort exterieur (N)//
	int    	senx,seny,senz;		//Sens de la limite des deplacement du noeud si >0 limite inferieure//
	double 	limx,limy,limz;		//Limite des deplacement du noeud (m)//
	int    	fixx,fixy,fixz;		//autorisation de deplacement 0 : libre, 1 : fixe//
	int    	symx,symy,symz;		//Symetrie si 1, sinon 0//
	double 	fhx,fhy,fhz;		//effort hydro sur le noeud (N)//
	int	flag_sta; 		//dans phobos: 1 si visite, 0 sinon//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	double	beg_times,end_times;	//in case of modification of the node in dynamic: times of the beginning of the modification and times of ending//
	double 	beg_vx,beg_vy,beg_vz;	//in case of modification of the node in dynamic: speed along x y z at the begining of the modification//
	double 	end_vx,end_vy,end_vz;	//in case of modification of the node in dynamic: speed along x y z at the end of the modification//
	int 	nb_times;		//in case of modification of the node in dynamic: nb of times//
	double 	*times;			//in case of modification of the node in dynamic: times table//
	double 	*speedx,*speedy,*speedz;//in case of modification of the node in dynamic: speed of the node at each times in x y and z components//
	double 	*speedm,*speedo,*speedd;//in case of modification of the node in dynamic: speed of the node at each times in amplitude orientation in XoY plane and standad deviation//
	int 	nb_times_fext;		//in case of modification of the node in dynamic: nb of times//
	double 	*times_fext;		//in case of modification of the node in dynamic: times table//
	//----in batz and temporis----//
	double 	inix,iniy,iniz;		//coordonnees sans rotation (m)//
	double 	*dx,*dy,*dz;		//coordonnees dynamique sans rotation (m)//
	double 	*ex,*ey,*ez;		//coordonnees dynamique (m)//
	double 	*hz;			//immersion sans rotation (m)//
	double 	*pz;			//pression sans rotation (Pa)//
	double 	*gx,*gy,*gz;		//immersion dynamique (m)//
	double  sx,sy,sz;
	double  fx,fy,fz;
	double  fxcal,fycal,fzcal;
	int     fmx,fmy,fmz;
	double  depx,depy,depz;
	int  	curvature_nb;		//nb of cases the curvature is assessed on this point
	double  curvature;		//curvature between two consecutives bar elements
	/////////////////////////////////////////////////////////////////////----in batz and temporis----//
	int	circular_speed;		//1 if this node has a circular speed, otherwise is 0
	double 	circular_normal[4];	//normal vector to the circle
	double	circular_center[4];	//center of the circle (m)
	double	circular_rev_speed;	//revolution speed of the node (turn/s)	
	int 	ballast;		//in case of ballast
	double 	volume_ballast;		//in case of ballast, water volume m³
	double 	precedent_ballast;	//in case of ballast, precedent water volume m³
	double 	speed_ballast;		//in case of ballast, speed of water volume m³/s
	double	vx,vy,vz;		//in case of determination of water speed per node in *.spe file
	double	OFx,OFy,OFz,OFsx,OFsy,OFsz;	//used by openfoam
	} 	NOEUD;

typedef struct numerique {
	float Diviseur;			//raideur additionnelle en N//
	int Nbmaxiterations;		//nb max d iterations realisees dans unix//
	float Seuilconvergence;		//seuil de convergence en N//
	float Deplacement;		//deplacement maximal autorise en m//
	float Pascalcul;		//pas de calcul en dynamique en s//
	float Passtockage;		//pas de stockage en dynamique en s//
	float Debutstockage;		//debut du stockage en dynamique en s//
	float Finstockage;		//fin du stockage et du calculen dynamique en s//
	} NUMERIQUE;

typedef struct orientation_netting
	{
  	int  nb_panel;		//nb of diamond mesh panel involved//
  	int  *panel; 		//numero of the involved panels//
  	double  pas; 		//angle step to class the orientation relatively to the flow//
  	double **tab_mesh;	//nb of mesh per angle and per panel//
  	double **tab_netting;	//surface of netting per angle and per panel//
  	double **tab_drag;	//drag of netting per angle and per panel//
  	int nb_tab;		//nb ol class = (int) 90/pas//
	} ORIENTATION_NETTING;

typedef struct opening_angle
	{
  	int  nb_panel;		//nb of diamond mesh panel involved//
  	int  *panel; 		//numero of the involved panels//
  	double  pas; 		//angle step to class the angles//
  	double **tab;		//nb of mesh per angle and per panel//
  	int nb_tab;		//nb ol class = (int) 90/pas//
	} OPENING_ANGLE;

typedef struct opening_mesh
	{
  	int  nb_panel;		//nb of diamond mesh panel involved//
  	int  *panel; 		//numero of the involved panels//
  	double  pas; 		//surface step to class the surfaces//
  	double **tab;		//nb of mesh per surface and per panel//
  	int nb_tab;		//nb ol class of surfaces//
	} OPENING_MESH;

typedef struct opening_angle_stripe
	{
  	int  nb_panel;		//nb of diamond mesh panel involved//
  	int  *panel; 		//numero of the involved panels//
  	double  pas; 		//angle step to class the angles//
  	double **tab;		//nb of mesh per angle and per stripe//
  	int nb_tab;		//nb ol class = (int) 90/pas//
  	double  stripe_step; 	//step of stripe in m//
  	int  nb_stripe;		//nb of stripes front the front//
  	double  *fromx; 	//largest limit of the stripe//
  	double  *tox; 		//smallest limit of the stripe//
	} OPENING_ANGLE_STRIPE;

typedef struct optimization
   	{
   	int	type;		//type of optimization cf user guide in unix_2004//
	int 	nb_step;	//nb of step, default = 10//
	double 	prop;		//proportion of displacement relatively to the maximal size of the panel, default = 5%//
	double 	prop_max;		//proportion of displacement relatively to the maximal size of the panel, default = 5%//
	double 	prop_min;		//proportion of displacement relatively to the maximal size of the panel, default = 5%//
	double 	prop_multip;		//proportion of displacement relatively to the maximal size of the panel, default = 5%//
   	int	no;		//if type = 2 heigth of node no is constant//
   	double	pre;		//if type = 2 heigth of node no is constant at pre * 100 %//
   	int	node_type;	//if type = 2 heigth of node no is constant by modifying the exten forces on node_type//
   	int	constraint_direction;	//if 1 along x, if 2 along y, if 3 along z, //
   	int	constraint_node;	//node on which there is the constraint//
   	double	constraint_limit;	//the valui is respected at a distance of limit//
   	double	constraint_value;	//target value of the constraint//
   	int	constraint_type;	//up to now only 1 which is the forces on node type//
   	int	constraint_node_type;	//type of node which will be modify to reach the target//
   	double	constraint_max;		//max proportion of value of constraint_node_type//
   	double	constraint_min;		//min proportion of value of constraint_node_type//
   	double	constraint_ratio;	//ratio proportion of value of constraint_node_type//
	int 	nb_node;		//nb of nodes used in optimization 5//
	int 	*node;			//no of nodes used in optimization 5//
	int 	*dir;			//direction of nodes used in optimization 5//
	double 	*weighting;		//weighting of nodes used in optimization 5//
	int 	nb_element_bottom;	//nb of elements which must be in contact with the bottom//
	int 	*element_bottom;	//no of elements which must be in contact with the bottom//
	double	d_mesh;			//variation of mesh in order to calculate the gradient of objective, for optimization 7//
	double	d_obj;			//variation of objective in order to calculate the mesh step, for optimization 7//
	double	precis;			//precis on the mesh variation for findind the minimum of objective, for optimization 7//
   	double	constraint_surface_ceil;//constraint on the surface by a ceiling value //
   	}	OPTIMIZATION;

typedef struct ordre
	{
	char *type;
	int  *indice;
	} ORDRE;

typedef struct node_panel2ropes
	{
	double *U;
	double *V;
	int  *numero_total;
	int *side;
	int *cable;
	int * sens;
	double *prop_cable;
	} NODE_PANEL2ROPES;

typedef struct panneau
	{
	int nb_noeud_contour; 				//nb de noeuds du contour du panneau: corners//
	int nb_noeud_interieur; 			//nb de noeuds interieur au panneau//
	int nb_noeud_cote; 				//nb de noeuds des cotes du panneau//
	int *noeud_contour;				//liste ordonnee des indices des noeuds du contour: size nb_noeud_contour//
	int *suivant_contour;				//noeuds de cote qui suivent les noeuds du contour: size nb_noeud_contour//
	int *type_suivant_contour;			//type des noeuds de cote qui suivent les noeuds du contour: size nb_noeud_contour//
	int *noeud_cote;				//liste des indices des noeuds des cotes: size nb_noeud_cote//
	float *prop_cote;				//liste des positions relatives des noeuds des cotes / longueur du cote: size nb_noeud_cote//
	int *noeud_interieur;				//liste des indices des noeuds interieurs: size nb_noeud_interieur//
	int *numero_triangle;				//liste des indices des noeuds interieurs: size nb_triangle_interieur//
	int *side2cable;				//cable n°, in case this side is linked to the cable. If> 0 cable and side in the same sens. If<0 opposite sens//
	int nb_triangle_interieur; 			//nb de triangles interieurs//
	int triangle_interieur[NBMAXNOEUDINTERIEUR][4];	//sommets des triangles interieurs dans la numerotation totale//
	int nb_triangle_contour; 			//nb de triangles poses sur le contour//
	int triangle_contour[NBMAXNOEUDCONTOUR][4];	//sommets des triangles poses sur le contour dans la numerotation locale//
	float pas_maillage;				//pas du maillage des noeuds interieurs en m//
	float pas_U;					//pas du maillage des noeuds interieurs selon les mailles U en nb de mailles//
	float pas_V;					//pas du maillage des noeuds interieurs selon les mailles V en nb de mailles//
	float pas_u;					//pas du maillage des noeuds interieurs selon les cotes de mailles u en nb de mailles//
	float pas_v;					//pas du maillage des noeuds interieurs selon les cotes de mailles v en nb de mailles//
	int type_maillage;				//type du maillage//
	int flag_maillage;				//1 si maille 0 si pas maille//
	int flag_filet_contour;				//1 si la triangulation sur le contour    est calculee 0 sinon//
	int flag_filet;					//1 si la triangulation sur ts les points est calculee 0 sinon//
	int flag_dessin;				//1 si dessine 0 si pas dessine//
	float raideur_traction;				//raideur en traction des fils constituant le filet de ce panneau//
	float raideur_compression;			//raideur en compression des fils constituant le filet de ce panneau//
	float raideur_ouverture;			//raideur a l ouverture des mailles du filet de ce panneau//
	double EI_flexion;				//raideur a la flexion des fils em N.m.m//
	float longueur_repos;				//cote de maille du filet de ce panneau//
	float diam_hydro;				//diametre hydro des fils du filet de ce panneau//
	float diametremeca;				//diametre mecanique des fils du filet de ce panneau//
	float largeurnoeud;				//largeur des noeuds du filet de ce panneau//
	float rho;					//masse volumique des fils constituant le filet de ce panneau//
	float cdnormal;					//coef de trainee normale des fils constituant le filet de ce panneau//
	float ftangent;					//coef de trainee tangentielle des fils constituant le filet de ce panneau//
	double 	energy_pliage;				//energie potentielle liee au pliage de 2 triangles joints//
	double 	energy_ouverture;			//energie potentielle liee a l'ouverture des mailles//
	double 	energy_elastique;			//energie potentielle liee a l elongation des fils//
	double 	energy_contact;				//energie potentielle liee au contact entre les fils//
	double current_reduction; 			//ratio relatively to the upstream current//
	float surf_fils;				//surface de fils de ce panneau//
	double 	neutral_angle;				//angle au repos du panneau en rad//
	int type_noeud;					//type des noeud a l interieur du panneau//
	int tarp;					//if 1 the panel is water proof like a tarp if 0 it is a netting//
	int parallel[4];				/*define if the symmetry is along U (value 1), V (2), u (3) or v (4) if there is no symmetry (0) along X axis [1], Y [2] anz Z [3]*/
	double 	drag;					//total drag of the panel//
	double 	seam;					//seam size in mesh number//
	float symmetry_plan;	////			//value of the plan of symmetry for the plan//
	int *lock_U;					/*list of 0/1 of the same size of the nb of corner, if 0 there is no locking along U
							if 1 there is a locking along U*/
	int *lock_V;					/*list of 0/1 of the same size of the nb of corner, if 0 there is no locking along V
							if 1 there is a locking along V*/
	int netting_2_ropes_period;			//when a panel is transformed in ropes period along U & V of twines relatively to ropes							
	double netting_2_ropes_gap_U;			//when a panel is transformed in ropes gap (>=0.0 & <1.0) along U							
	double netting_2_ropes_gap_V;			//when a panel is transformed in ropes gap (>=0.0 & <1.0) along V							
	double netting_2_ropes_accuracy;		//when a panel is transformed in ropes accuracy on the position of new numeric nodes (in number of mesh side)							
	int netting_2_ropes_bar_nb;			//when a panel is transformed in ropes nb of bars per numeric rope							
	double min_exit_size;				//minimum of circle diameter passing trough meshes
	double max_exit_size;				//maximum of circle diameter passing trough meshes
	double mean_exit_size;				//mzan of circle diameter passing trough meshes
	double std_dev_exit_size;			//standard deciation of circle diameter passing trough meshes
	} PANNEAU;

typedef struct Pan_Hexa
	{
	int nb_noeud_contour; 				//nb de noeuds du contour du panneau//
	int nb_noeud_interieur; 			//nb de noeuds interieur au panneau//
	int nb_noeud_cote; 				//nb de noeuds des cotes du panneau//
	int *noeud_contour;				//liste ordonnee des indices des noeuds du contour//
	int *suivant_contour;				//noeuds de cote qui suivent les noeuds du contour//
	int *type_suivant_contour;			//type des noeuds de cote qui suivent les noeuds du contour//
	int *noeud_cote;				//liste des indices des noeuds des cotes//
	float *prop_cote;				//liste des positions relatives des noeuds des cotes / longueur du cote//
	int *noeud_interieur;				//liste des indices des noeuds interieurs//
	int nb_tri_hexa_interieur; 			//nb de triangles interieurs//
	int tri_hexa_interieur[NBMAXNOEUDINTERIEUR][4];	//sommets des triangles interieurs dans la numerotation totale//
	int nb_tri_hexa_contour; 			//nb de triangles poses sur le contour//
	int tri_hexa_contour[NBMAXNOEUDCONTOUR][4];	//sommets des triangles poses sur le contour dans la numerotation locale//
	float pas_maillage;				//pas du maillage des noeuds interieurs//
	int type_maillage;				//type du maillage//
	int flag_maillage;				//1 si maille 0 si pas maille//
	int flag_filet_contour;				//1 si la triangulation sur le contour    est calculee 0 sinon//
	int flag_filet;					//1 si la triangulation sur ts les points est calculee 0 sinon//
	int flag_dessin;				//1 si dessine 0 si pas dessine//
	float raideur_traction_l,raideur_traction_m,raideur_traction_n;		//raideur en traction des fils constituant le filet de ce panneau//
	float raideur_compression_l,raideur_compression_m,raideur_compression_n;//raideur en compression des fils constituant le filet de ce panneau//
	float lo_repos,mo_repos,no_repos;		//cote de maille l,m,n du filet de ce panneau//
	float diam_hydro_l,diam_hydro_m,diam_hydro_n;	//diametre hydro des fils du filet de ce panneau//
	float rho;					//masse volumique des fils constituant le filet de ce panneau//
	float cdnormal;					//coef de trainee normale des fils constituant le filet de ce panneau//
	float ftangent;					//coef de trainee tangentielle des fils constituant le filet de ce panneau//
	float surf_fils;				//surface de fils de ce panneau//
	int type_noeud;					//type des noeud a l interieur du panneau//
	int tarp;					//if 1 the panel is water proof like a tarp if 0 it is a netting//
	double 	drag;					//total drag of the panel//
	} PANNEAU_HEXA;

CLASS struct Plan
	{
	int 	do_it;			//if 1 do the plan, if 0 dont//
	int 	direction;		//if 1 (2,3) along x (y,z)//
	int	nb_line;		//nb of lines for the plan//
	int	*panel;			//numero of the panel from which the line is drawn//
	int	*corner;		//numero of the panel from which the line is drawn//
	float	*limit;			//numero of the panel from which the line is drawn//
	int	nb_height;		//nb of heights for the plan//
	int	*panelh;		//numero of the panel from which the height is drawn//
	int	*corner1;		//numero of the panel from which the height is drawn//
	int	*corner2;		//numero of the panel from which the height is drawn//
	int	*directionh;		//numero of the panel from which the height is drawn//
	float	*position;		//numero of the panel from which the height is drawn//
	float	minx,maxx,miny,maxy;	//min max for the plan//
	int	nb_width;		//nb of heights for the plan//
	int	*panelw;		//numero of the panel from which the width is drawn//
	int	*corner3;		//numero of the panel from which the width is drawn//
	int	*corner4;		//numero of the panel from which the width is drawn//
	int	*directionw;		//numero of the panel from which the width is drawn//
	int	nb_widths;		//nb of heights for the plan//
	float	*positionw;		//numero of the panel from which the width is drawn//
	int	*panelws;		//numero of the panel from which the width symmetric is drawn//
	int	*corner3s;		//numero of the panel from which the width symmetric is drawn//
	int	*corner4s;		//numero of the panel from which the width symmetric is drawn//
	int	*directionws;		//numero of the panel from which the width symmetric is drawn//
	float	*positionws;		//numero of the panel from which the width symmetric is drawn//
	int	nb_cut;			//nb of panel cutting for the plan//
	int	*panelc;		//numero of the panel on which the cutting is drawn//
	int	*corner5;		//numero of the panel on which the cutting is drawn//
	int	nb_cable;		//nb of cables indicated on the plan//
	int	*cable;			//numero of the cable drawn//
	int	nb_trait_UV;		//nb of trait UV in panel//
	int	*panelt;		//numero of the panel on which the trait is drawn//
	float	*U1,*V1,*U2,*V2;	//coordinates in nb of meshes of the traits//
	int	nb_trait_UV_symmetry;	//nb of trait UV in panel//
	int	*panels;		//numero of the panel on which the trait is drawn//
	float	*R1,*S1,*R2,*S2;	//coordinates in nb of meshes of the traits//
	float	*symmetryt;		//coordinates in nb of meshes of the traits//
	int	nb_cable_diameter;	//nb of cables indicated on the plan with indication of diameter//
	int	*cabled;		//numero of the cable drawn//
	float	*cable_diameter;	//numero of the cable drawn//
	int	nb_cable_length;	//nb of cables indicated on the plan with indication of diameter//
	int	*cablel;		//numero of the cable drawn//
	float	*cable_length;		//numero of the cable drawn//
	int	nb_indication;		//nb of indications indicated on the plan//
	float	*X1,*Y1;		//position of the indication//
	float 	*indication; 		//indication//
	} plan;

typedef struct plan_cutting
   	{
   	int	nb_plan;		//if 0 no plan cutting, if 1 one plan cutting//
   	double	X0,Y0,Z0;		//point trough which the plan passes//
  	double	Xv,Yv,Zv;		//vector normal to the plan//
	int 	nb_nodes;		//nb of nodes in the plan cutting the netting//
	double 	*x,*y,*z,*alpha;	//position of the nodes and angle ,opening between twines in the surface following the node//
   	}	PLAN_CUTTING;

typedef struct 	prise {
	double 	volume;			//volume demande dans *.don(m3)//
	double 	volume_effectif;	//volume effectif (m3)//
	double 	seuil;			//seuil (m3)//
	double 	cd;			//coef de trainee sur la prise//
	double 	front;			//position du front de la prise (m)//
	double 	diametre;		//diametre de la prise (m)//
	double 	front_diameter;		//diametre au niveau du front (m)//
	double 	epaisseur;		//distance du front a l extremite de la prise (m)//
	double 	radial_radius;		//radial radius of the ellipsoide inner surface (m)//
	double 	axial_radius;		//radial radius of the ellipsoide inner surface (m)//
	double 	distance_front;		//distance between the center of the ellipsoide and the front of the cod-end (m)//
	int	nb_point;		//nb of points in the perimeter of the front//
	double	*perimeter_y;		//y position of a point of the perimeter//
	double	*perimeter_z;		//z position of a point of the perimeter//
	int	nb_panel_meridian;	//nb of panels used by the meridian//
	int	*panel_meridian;	//panels number used by the meridian//
	int	nb_point_meridian;	//nb of points in the meridian//
	double	*meridian_r;		//radius of the meridian//
	double	*meridian_x;		//x position of the meridian//
	double	*meridian_y;		//y position of the meridian//
	double	*meridian_z;		//z position of the meridian//
	int	nb_panel_curvilinear;	//nb of panels used by the curvilinear length of the cod end//
	int	*panel_curvilinear;	//panels number used by the curvilinear length of the cod end//
	int	nb_point_curvilinear;	//nb of points in the curvilinear length of the cod end//
	double	*curvilinear_r;		//radius of the curvilinear length of the cod end//
	double	*curvilinear_x;		//x position of the curvilinear length of the cod end//
	double 	PR;			//prise en kg de poisson//
	double 	PE;			//perimetre tendu du cod-end//
	double 	TA;			//taille moyenne en kg des poisson//
	double 	RA;                     //mesh opening stiffness N.m2//		
	double 	EI;			//mesh opening stiffness N.m2//
	double 	Ox;			//x coordinate of the ellipsoide center//
	double 	Oy;			//y coordinate of the ellipsoide center//
	double 	Oz;			//z coordinate of the ellipsoide center//
	double	*catch;			//catches//
	double 	max_volume;		//maximal volume available in the cod-end//
	double 	curvilinear_codend_length_total;	//curvilinear length of the cod end//
	double 	curvilinear_codend_length_occult;	//curvilinear length of the occulted part of the cod end//
	int	panels[3];		//the 2 panels where the limit is calculated//
	double 	limit_panels;		//limit between the 2 panels//	
	double 	nb_mesh_front;		//position of the front in nb of mesh//
	int	dir_mesh_front;		//direction along the position of the front in nb of mesh is calculated 1 : U and 2: V//
	int	nb_panel_catch2;	//nb of panels used by catch2//
	int	*panel_catch2;		//n° of panels used by catch2//
	double	drag;			//drag on the catch (N)//
	double	catch_dynamic;		//evolution of the catch in m3/s//
	double	catch_gravity;		//density of the catch when outside of water//
//----dans batz----//
	int 	nb_noeuds;		//nb de noeuds total de l'ellipsoide + le contour//
	int 	nb_noeuds_contour;	//nb de noeuds du contour de l'ellipsoide//
	double 	*xx,*yy,*zz;		//coordonnees des noeuds total de l'ellipsoide + le contour//
	double 	*xx_ini,*yy_ini,*zz_ini;//coordonnees des noeuds total de l'ellipsoide + le contour//
	int	nb_triangles;		//nb of triangles on the inner surface//
	int	*vertex_1;		//nb of vertex 1//
	int	*vertex_2;		//nb of vertex 2//
	int	*vertex_3;		//nb of vertex 3//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
//----dans batz----//
	int 	angle_tensions;		//if 1 calculation of mean angle between twines and mean tension in twines at the front
	double 	angle_twines;		//mean angle between twines at the front
	double 	tension_u,tension_v;	//mean tension in twines at the front
	} 	PRISE;	
   	
typedef struct recouvrement_x
   	{
	int 	*element1;	//element1//	
	int 	*element2;	//element2//	
	double 	*min;		//minimum distance along X axe between the nodes of element1 and element 2//	
	double 	*max;		//maximum distance along X axe between the nodes of element1 and element 2//			
	double 	*mean;		//mean distance along X axe between the nodes of element1 and element 2//			
	int 	*flag_limit;	//if 1 there is a limit used in nerzh//	
 	double 	*limit;		//if flag_limit is 1 there is a limit used in nerzh which is limit//	
   	}	RECOUVREMENT_X;

typedef struct 	slider {
	int		nb_bar;		//nb of bars in this slider
	int 		*barre;		//element belonging to this slider. the first bar defines the mechanical charateristics of the slider
	double 	diametremeca;		//diametre mecanique m^2//
	double 	raideur_traction;	//raideur en traction    (N) = section * module d elasticite//
	double 	raideur_compression;	//raideur en compression (N) = section * module d elasticite//
	double 	raideur_effective;	//raideur effective = raideur en traction (compression) si element est en traction (compression)//
	double 	wt;			//tension dans cet element (N)//
	double 	wtfinal;		//tension dans cet element (N) a l avant derniere iteration //
	double 	lgrepos;		//longueur avec tension = 0 N//
	double 	lgtendue;		//longueur sous tension//
	double 	diametrehydro;		//diametre hydrodynamique m//
	double 	rhoelement;		//masse volumique kg/m^3//
	double 	cdnormal;		//coef. de trainee normal//
	double 	ftangent;		//coef. de trainee tangent//
	int    	color;			//fonction de la tension//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	double 	nrj;
	double 	*dnrj;
	} 	SLIDER;

typedef struct sortie_texte
	{			
	int  nb_distance;			//nb de distance entre 2 points affichees//
	COMMENTAIRE *comment_distance;		//commentaires associes aux distances//
	int *noeud1_distance;			//premiere extremite de la distance en global//		
	int *noeud2_distance;			//seconde extremite de la distance en global//		
	int *decimale_distance;			//nb de decimale pour l affichage de la distance//
	char *type_structure1_distance; 	//types des structures //
	int  *numero_structure1_distance; 	//indice des structures //
	char *type_structure2_distance; 	//types des structures //
	int  *numero_structure2_distance; 	//indice des structures //
	double *valeur_distance;
			
	int  nb_effort;				//nb d effort selon un axe a un point affiches//
	COMMENTAIRE *comment_effort;		//commentaires associes aux distances//
	int *noeud_effort;			//premiere extremite de la distance en global//		
	int *axe_effort;			//seconde extremite de la distance//		
	int *decimale_effort;			//nb de decimale pour l affichage de la distance//
	char *type_structure_effort; 		//types des structures //
	int  *numero_structure_effort; 		//indice des structures //
	double *valeur_effort;

	int  nb_tension_element;		//nb de tension dans un element affichees//
	COMMENTAIRE *comment_tension_element;	//commentaires associes aux distances//
	int *element_tension;			//premiere extremite de la distance//		
	int *element_extremite;			//premiere extremite de la distance en local : 1 ou 2//		
	int *decimale_tension_element;		//nb de decimale pour l affichage de la distance//
	double *valeur_tension;

	int  nb_tension_coulisse;		//nb de tension dans une coulisse affichees//
	COMMENTAIRE *comment_tension_coulisse;	//commentaires associes aux distances//
	int *coulisse_tension;			//premiere extremite de la distance//		
	int *coulisse_extremite;		//premiere extremite de la distance//		
	int *decimale_tension_coulisse;		//nb de decimale pour l affichage de la distance//
	double *valeur_tension_coulisse;		

	int  nb_position;			//nb de position selon un axe a un point affichees//
	COMMENTAIRE *comment_position;		//commentaires associes aux distances//
	int *noeud_position;			//premiere extremite de la distance//		
	int *axe_position;			//seconde extremite de la distance//		
	int *decimale_position;			//nb de decimale pour l affichage de la distance//
	char *type_structure_position; 		//types des structures //
	int  *numero_structure_position; 	//indice des structures //
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
	double *valeur_longueur_cable;		//longueur en m//
	
	int  nb_energie_elong_diamond;		//nb d energies d elongation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_elong_diamond;	//commentaires associes aux energies//
	int *panneau_energie_elong;		//numero du panneau//		
	int *decimale_energie_elong;		//nb de decimale pour l affichage de l energie en J//
	double *valeur_energie_elong_diamond;
	
	int  nb_energie_fold_diamond;		//nb d energies d foldation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_fold_diamond;	//commentaires associes aux energies//
	int *panneau_energie_fold;		//numero du panneau//		
	int *decimale_energie_fold;		//nb de decimale pour l affichage de l energie en J//
	double *valeur_energie_fold_diamond;
	
	int  nb_energie_open_diamond;		//nb d energies d openation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_open_diamond;	//commentaires associes aux energies//
	int *panneau_energie_open;		//numero du panneau//		
	int *decimale_energie_open;		//nb de decimale pour l affichage de l energie en J//
	double *valeur_energie_open_diamond;
	
	int  nb_energie_contact_diamond;		//nb d energies d openation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_contact_diamond;	//commentaires associes aux energies//
	int *panneau_energie_contact;		//numero du panneau//		
	int *decimale_energie_contact;		//nb de decimale pour l affichage de l energie en J//
	double *valeur_energie_contact_diamond;
	
	int  nb_parametre;			//nb de position selon un axe a un point affichees//
	COMMENTAIRE *comment_parametre;		//commentaires associes aux distances//
	int *decimale_parametre;		//nb de decimale pour l affichage de la distance//
	double *valeur_parametre;

	int effort_structure;			//si 1 affiche l effort sur toute la structure (N) selon les axes X Y et Z//	
	int diametre_prise;			//si 1 affiche diametre_prise (m)//	
	int epaisseur_prise;			//si 1 affiche epaisseur_prise (m)//	
	int vitesse_courant;			//si 1 affiche vitesse_courant (m/s)//	
	int vitesse_vent;			//si 1 affiche vitesse_vent (m/s)//	
	int volume_capture;			//si 1 affiche volume_capture (m3)//	
	int surface_filtree;			//si 1 affiche surface_filtree (m2)//	
	int volume_x;				//si 1 affiche le volume calcule selon l axe x (m3)//	
	int volume_y;				//si 1 affiche le volume calcule selon l axe y (m3)//	
	int volume_z;				//si 1 affiche le volume calcule selon l axe z (m3)//	
	int volume_0;				//si 1 affiche le volume calcule selon le courant (m3)//	
	int inner_surface;			//si 1 affiche les dimensions de l'ellipsoide de la surface interne de la prise (m)//	
	int inner_surface_triangulation;	//si 1 trianguularise l'ellipsoide de la surface interne de la prise//	
	int meridian;				//si 1 affiche la meridian (m,m)//	
	int meridian_X;				//si 1 affiche la meridian (m,m)//	
	int meridian_Y;				//si 1 affiche la meridian (m,m)//	
	int meridian_Z;				//si 1 affiche la meridian (m,m)//	
	int curvilinear_codend_length;		//si 1 affiche la longueur curviligne du codend, de sa partie occultee et du rapport des 2//	
	int catch_drag;				//si 1 affiche the drag of the catch//	
	int bottom_drag;			//si 1 affiche the drag of the bottom//	
	int element_drag;			//si 1 affiche the drag of the bottom//	
	int surface_drag;			//si 1 affiche the drag of the bottom//	
	int node_drag;				//si 1 affiche the drag of the nodes//	
	int panel_drag;				//si 1 affiche the drag of the panels//	
	int cable_drag;				//si 1 affiche the drag of the cables//	
	int triangle_drag;			//si 1 affiche the drag of each triangle//	
	int bar_tension;			//only in dynamic, if 1 tension of bars in *.ten for each time step//	
	int diamond_tension;			//only in dynamic, if 1 tension of twines in *.ted for each time step//	

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

	
	} SORTIE_TEXTE;


typedef struct sphere_element
   	{
	int 	*element;	//cable on which the sphere are//	
	int 	*nb;		//number of sphere//			
	double 	*diameter;	//diameter of the each sphere floats (m)//			
	double 	*floatability;	//floattability of each float (N)//			
   	}	SPHERE_ELEMENT;

typedef struct 	spheric_limit {
	double 	x;			//x coordinate of the sphere centre//	
	double 	y;			//y coordinate of the sphere centre//	
	double 	z;			//z coordinate of the sphere centre//	
	double 	radius;			//radius of the sphere//	
	double 	kc;			//compression stiffness of the sphere//	
	double 	kt;			//traction    stiffness of the sphere//	
	} 	SPHERIC_LIMIT;	
	

typedef struct structure
   	{
	int 	 eigenvalues;		//if 1 the eigenvalues and eigen,vectors are calculated//
	int 	 orientation;		//orientation du dessin 1 (2,3) perpendiculaire a l axe x (y,z)//
	int 	 version; 		//version number of the *.don//
	int 	 nb_winch; 		//nb of winches in the structure//
	int 	 nb_liaison; 		//nombre de liaisons dans le chalut//
	int	 nb_sphere_element;	//nb of sphere element cases//
   	int	 NbTypeNoeud;
   	int	 nombreSurfaces;	//nombre de surface dans le chalut//
   	int	 nombreSurfHexa;	//nombre de surface a maille hexagonale dans le chalut//
   	int	 nombreCoulisses;	//nombre de coulisses constituants le chalut//
   	int	 NbTypeelem;
   	int	 NbTypesurf;
   	int	 NbTypesurf_hexa;

   	int      nombreNoeuds;
//  	int      nombreBalls;   n'a pas l'air de servir
  	int	 nombreElements;	//nombre de elements constituants le chalut// utilisé uniquement dans batz

   	double    diviseur;
   	int       lmn_calcules;		//= 1 si l m n des mailles hexagonales ont ete calcules sinon 0//
	int 	  nb_tarp_diamond;	//nb of tarps on diamond mesh panel//
	int 	  nb_tarp_hexa;		//nb of tarps on hexagonal mesh panel//
	int 	  nb_catch2_length;	//nb of catch, each catch for a determined panels//
	int 	  nb_catch2_surface;	//nb of catch, each catch for a determined panels//
	int 	  nb_catch2_volume;	//nb of catch, each catch for a determined panels//
	int 	  nb_catch2_weight;	//nb of catch, each catch for a determined panels//
	int 	  nb_cage_volume;	//nb of cage, each cage for a determined panels//
	double 	  element_drag;		//drag on elements (cables and bars)//
	double    surface_drag;		//drag on surface (netting)//
	double    node_drag;		//drag on node (floats, dead weights)//
	int 	  boat_no;		//node number of the boat for calculating the power spent by the boat//
	//double 	  element_drag2;	//drag on elements (cables and bars)//
	double 	  boat_energy;		//energy due to moving nodes//
	double 	  element_energy;	//energy on elements (cables and bars)//
	double    surface_energy;	//energy on surface (netting)//
	double    node_energy;		//energy on node (floats, dead weights)//
	double    haul_energy;		//energy in hauling//
	double 	  boat_power;		//power due to moving nodes//
	double 	  element_power;	//power on elements (cables and bars)//
	double    surface_power;	//power on surface (netting)//
	double    node_power;		//power on node (floats, dead weights)//
	double    haul_power;		//power in hauling//
	double    total_drag;		//drag on the whole structure//
	double	  filtered_surface;	//total filtered surface of the structure//
	int 	  nb_value;		//nb of linear value defined  by 2 depths and 2 values//
	int 	  nb_type_noeud_XYZ_SUPINF;	//nb modifications of node type//
	int 	  nb_recouvrement_x;	//nb of recouvrement_x between a element relatively to an another one//
	// debut modifdp du 12 mars 2010//	
	int 	  nb_vector_tension_bar;//nb of tension in bars//
	// fin modifdp du 12 mars 2010//	
	int 	  hydro_forces;		//if 1 the hydro forces are calculated//
	int 	  cut_plan_symmetry;	//if 1 (2, 3) the intersection of triangular elements of diamond meshes with symmetry plan X (Y, Z) is save (in nodes coordinates in m) with angles (radian) between twines//
	int 	  drag_forces_type;	//if 1 the hydro forces are calculated with morison, if 2 the hydro forces are calculated with zhan, if 3 the hydro forces are calculated with drop pressure//
	int 	  nb_hauling_cable;	//nb of hauling cables only used in dynamic//
	int 	  nb_hauling_cable2;	//nb of hauling cables only used in dynamic of type 2//
	int 	  nb_speed_type_node;	//nb of type node with speed//
	int 	  circular_speed_node;	//1 if a node has a circular speed, otherwise is 0
	int 	  type_solver;		//1: gauss, 2:pardiso//

	int	  drawing;		//0 default in colors, 1 in black//
	int 	  visible_symmetry; 	//1 default symmetry is visisble, à the symmetry is not visible//
	int       graphic;		//if 1 it is calculated with the graphic tool, if 2 it is calculated by the text tool//


	int       symetry;		//if 0 no sym, 1 symx, 2 symy, 4 symz, 3 symxy, 5 symxz, 6 symyz, 7 symxyz//
	char      nomfichier1[100],nomfichier2[100];	//files name//
	int       free_surface;		//1 if the free surface is displayed, 0 if not//

//----dans phobos----//

	int nb_ordre_objet;             //nombre d'objets(panneau,element,coulisse,pan_hexa)//
	int nb_node_panel2ropes;        //in case of input netting2ropes nb of nodes created in the panel//
	int nb_fils; 			//nombre de fils dans les triangles contour constituants le chalut//
	int T90_nb_fils; 		//nombre de fils dans les triangles contour selon l'axe T90//
	int nb_barre_winch; 		//nb of bars in winches in the structure//

	int nb_lien; 			//nombre de liens dans le chalut >=  liaisons//
	int nb_total;			//nombre de noeuds dans la numerotation totale dans le chalut//
	int nb_global;			//nombre de noeuds dans la numerotation globale dans le chalut apres renumerotation//
	int nb_barre;			//nombre de barre dans le chalut//
	int nb_barre_selvedges;		//nombre de barre dans le chalut//
	int nb_selvedges; 		//nombre de rallingues  constituants le chalut//

	float surface_fils;		//surface de fils du chalut tel que maille//

	int nb_catches;			//nb of catches calculated//
	double link_distance;		//distance used for automatic link between points//
	double add_x_pa;		//distance added along x axis for pannels from add_x_pa_no1 to add_x_pa_no2//
	int add_x_pa_no1;		//first panel to which is added add_x_pa//
	int add_x_pa_no2;		//last  panel to which is added add_x_pa//
	double add_y_pa;		//distance added along y axis for pannels from add_y_pa_no1 to add_y_pa_no2//
	int add_y_pa_no1;		//first panel to which is added add_y_pa//
	int add_y_pa_no2;		//last  panel to which is added add_y_pa//
	double add_z_pa;		//distance added along z axis for pannels from add_z_pa_no1 to add_z_pa_no2//
	int add_z_pa_no1;		//first panel to which is added add_z_pa//
	int add_z_pa_no2;		//last  panel to which is added add_z_pa//
	double add_x_el;		//distance added along x axis for elements from add_x_el_no1 to add_x_el_no2//
	int add_x_el_no1;		//first element to which is added add_x_el//
	int add_x_el_no2;		//last  element to which is added add_x_el//
	double add_y_el;		//distance added along y axis for elements from add_y_el_no1 to add_y_el_no2//
	int add_y_el_no1;		//first element to which is added add_y_el//
	int add_y_el_no2;		//last  element to which is added add_y_el//
	double add_z_el;		//distance added along z axis for elements from add_z_el_no1 to add_z_el_no2//
	int add_z_el_no1;		//first element to which is added add_z_el//
	int add_z_el_no2;		//last  element to which is added add_z_el//
	double rot_el_xxo;		//x component of the center around which the elements from rot_z_el_no1 to rot_z_el_no2 are rotated//
	double rot_el_yyo;		//y component of the center around which the elements from rot_z_el_no1 to rot_z_el_no2 are rotated//
	double rot_el_zzo;		//z component of the center around which the elements from rot_z_el_no1 to rot_z_el_no2 are rotated//
	double rot_el_teta;		//rotation angle the elements from rot_z_el_no1 to rot_z_el_no2 are rotated//
	int rot_el_no1;			//first element rotated//
	int rot_el_no2;			//last  element rotated//
	double rot_pa_xxo;		//x component of the center around which the panels from rot_z_el_no1 to rot_z_el_no2 are rotated//
	double rot_pa_yyo;		//y component of the center around which the panels from rot_z_el_no1 to rot_z_el_no2 are rotated//
	double rot_pa_zzo;		//z component of the center around which the panels from rot_z_el_no1 to rot_z_el_no2 are rotated//
	double rot_pa_teta;		//rotation angle the panels from rot_z_el_no1 to rot_z_el_no2 are rotated//
	int rot_pa_no1;			//first panels rotated//
	int rot_pa_no2;			//last  panels rotated//

	double add_cage_diam;
	double add_cage_xxo;
	double add_cage_yyo;
	int add_cage_nsegment;
	double add_cage_dist_ann;
	double add_cage_haut_ann;
	int add_number_cage;
	double add_hauteur_filet_elev;
	double add_taille_maille_elev;

	double add_filet_pred_diam;
	double add_diam_lest;
	double add_filet_pred_xxo;
	double add_filet_pred_yyo;
	int add_filet_pred_nsegment;
	double add_hauteur_filet_pred;
	double add_taille_maille_pred;

	int nb_connect_panel_node;	//nb of nodes coordinates linked to two anaother node//
//----dans phobos----//
	int nb_ratio_drag_panel;	//nb of case of modification of the panel drag in dynamic
	double 	*times_drag_panel;	//in case of modification of the panel drag in dynamic: ratio of all the panels at each times
	double 	*ratio_drag_panel;	//in case of modification of the panel drag in dynamic: ratio of all the panels at each times
	double ratio_num_temp;		//ratio of K[i][i] < num_temps relatively to the nb of DOF
	int convergence_parameters;	//if 1 the convergence parameters are defined if 0 they are defined in ~/hexa/unix_2004/param.txt
	int total1,total2;		//if total1 & total2 are != 0 they are link in the same global node
	int delta_h1;			//if 1 the size of the structure along X Y and Z is stored in tmp file
	double delta_h2;  		//if delta_h1 == 1 the height of the structure is delta_h2
	int Delta_h_v;			//if 1, 2 distances betwwen nodes is stored in file tmp
	int Delta_h1;			//if delta_h_v = 1, first  node of the first  distance
	int Delta_h2;			//if delta_h_v = 1, second node of the first  distance
	int Delta_h3;			//if delta_h_v = 1, first  node of the second distance
	int Delta_h4;			//if delta_h_v = 1, second node of the second distance
	int curvature;			//if 1 the curvature of the elements is stored in *.cuv file
	int hauling_cable4_tension;	//if 1 the tension in cables hauled are recorded in *.hwt file
	int nb_ballast;		//nb of ballasts
	int nb_deck;		//nb of decks
	int ballast_altitude;		//if 0 : no record, if 1 : record in sta file. Defaut value is 0
	double x_g,y_g,z_g,total_mass;			//position of gravity center and total mass, the default value of total mass is 0, if -1 that means that the total mass, its position, the total floatability and its position are calculated and stored in sta file
	double x_p,y_p,z_p,total_volume_floatability;	//position of floatability center and total volume of flatability
	int netting_volume_calculation;		//if 1 volume inside nettings behind a plane normal to X axis is calculated
	double front_netting_volume;			//position of the plane along X axis behind which the nettings volume is calculated
	int speed_type_node;		//default value is 0, if 4 the speed afor few coordinates are given in *.fos, this file is read at each time step
 	int screen;			//default value is 1, 1 is for classic output
 	int nb_slider;			//nb of sliders 
 	int nb_cable_contact;			//nb of couple of cables which could be in contact 
 	int nb_fixed_components;		//nb of fixed components
 	int *list_fixed_node;			//list of fixed node
 	int *list_fixed_axe;			//list of axe (x, y, or z) of fixed node
 	double *effort_fixed_components;	//force on fixed components
 	int wave_model;			//default is 1. 1: Airy finite depth, 2: Stokes 2d order finite depth, 3: Stokes 3d order infinite depth
 	int stiffness_matrix;			//default is 0. If 1 there is record of the stiffness matrix in *.sti
 	int nrj;				//default is 0. If 1 there is record of the energy per time step in *.nrj
 	int haul;				//default is 0. If 1 there is record of the length of bars per time step in *.haul
 	int nb_add_node_panel;			//nb of numeric nodes created in diamond panel: use  input add_node_panel 2 14.0 15.0 3
 	int openfoam;				//default is 0. 1: there will have a use of openfoam, 2: openfoam has created a water speed file, 3: open has created a pressure file
 	int pressure_file;			//default is 0. 1: there will have a use of openfoam, 2: openfoam has created a water speed file, 3: open has created a pressure file
 	char pathOFc[200];  		//path for openfoam	
 	int rigOF;			//used by openfoam
 	int paraview;			//default is 0. 1: the files vtk are created in order to be used by paraview
 	int exit_size_diamond_panel;	//default is 0. 1: assess min max mean std_dev of exit size per diamond panel. Exit size is the diameter of the maximal circle passing trough meshes per diamond panel
 	int mean_XYZ_desequilibrium;	//default is 0. 1: display at each iteration mean desequilibrium along X, Y and Z (N)
 	} 	STRUCTURE;

   
typedef struct 	voisin {
	int exist;		//0 si pas de voisin 1 si voisin//
	int elem_voisin;	//numero de l element voisin//
	int sommet_oppose;	//1 2 ou 3 = sommet oppose au voisin//
	double U_oppose;	//coordonnee filaire du sommet_oppose//
	double V_oppose;	//coordonnee filaire du sommet_oppose//
	} 	VOISIN; 


typedef struct 	surface {
	int    	panneau;		//no du panneau ou est situe ce triangle//
	int    	type;		 	//no du type de surface identique a panneau auquel appartient ce triangle//
	int    	extremite[4];		//no des 3 points aux sommets//
	int 	numerotation_locale; 	//numero du triangle dans le panneau//
	double 	U[4];			//U[1] = lon[1] U[2] = lon[3] U[3] = lon[5] coordonnees des sommets en nombre de mailles selon U//
	double 	V[4];			//V[1] = lon[2] V[2] = lon[4] V[3] = lon[6] coordonnees des sommets en nombre de mailles selon V//
	double 	lon[7];		//attention redeondant avec U et V !!!! coordonnees filaires des 3 sommets dans le sens des diagonales aux mailles//
	double 	nb_cote_u_ou_v;	//nb de cotes de mailles u ou v dans ce triangle : nb cote u = nb cotev//
	double 	diametremeca;		//diametre mecanique m^2//		
	double 	raideur_traction;	//raideur en traction    (N) = section * module d elasticite//
	double 	raideur_compression;	//raideur en compression (N) = section * module d elasticite//
	double 	EI_flexion;		//raideur a la flexion des fils em N.m.m//
	double 	raideur_ouverture;	//raideur a l ouverture des maille em N.m/rad//
	double 	neutral_angle;		//angle au repos du panneau en rad//
	double 	tension1;		//tension dans les fils u (N)//
	double 	tension2;		//tension dans les fils v (N)//
	double 	lgrepos;		//longueur de la maille avec tension = 0 N//
	double 	lg_tendue1;		//longueur du cote de maille m//
	double 	lg_tendue2;		//longueur du cote de maille n//
	double 	N[4];			//normal to the surface length = 1//
	double 	n[4];			//n[1] = nx n[2] = ny n[3] = nz composante du cote de maille n//
	double 	m[4];			//m[1] = mx m[2] = my m[3] = mz composante du cote de maille m//
	double 	nx;			//ATTENTION: REDONDANT avcec nx et mx!!!!!!!!composante de la longueur du cote de maille u selon l axe x//
	double 	ny;			//composante de la longueur du cote de maille u selon l axe y//
	double 	nz;			//composante de la longueur du cote de maille u selon l axe z//
	double 	mx;			//composante de la longueur du cote de maille v selon l axe x//
	double 	my;			//composante de la longueur du cote de maille v selon l axe y//
	double 	mz;			//composante de la longueur du cote de maille v selon l axe z//
	double 	Nx;			//composante selon x de la normale normee au triangle//
	double 	Ny;
	double 	Nz;
	double 	diametrehydro;		//diametre hydrodynamique m//
	double 	largeurnoeud;		//largeur du noeud  m//
	double 	rhosurface;		//masse volumique kg/m^3//
	double 	cdnormal;		//coef. de trainee normal//
	double 	ftangent;		//coef. de trainee tangent//
	double 	energy_pliage;		//energie potentielle liee au pliage de 2 triangles joints//
	double 	energy_ouverture;	//energie potentielle liee a l'ouverture des mailles//
	double  nrj;
	double 	nrj1;			//energie potentielle du cote de maille m//
	double 	nrj2;			//energie potentielle du cote de maille n//
	double 	energy_elastique;	//energie potentielle liee a l elongation des fils//
	double 	energy_contact;		//energie potentielle liee au contact entre les fils//
	double 	defaut_disc;		//mesure du defaut de discretisation//
	int 	tarp;			//if 1 the panel is water proof like a tarp if 0 it is a netting//	
	VOISIN	voisin_1;		//info sur le voisin de surface oppose au sommet 1//
	VOISIN	voisin_2;		//info sur le voisin de surface oppose au sommet 2//
	VOISIN	voisin_3;		//info sur le voisin de surface oppose au sommet 3//
	double current_reduction; 	//ratio relatively to the upstream current//
	double panel_drag; 		//drag of the surface//
	double panel_dragxyz; 		//hydrodynamic drag norm of the surface//
	double diam_knot; 		//diameter of the knot//
//----dans batz et temporis----//
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

	int     vertexU1,vertexV1,vertexU2,vertexV2;				//vertex from which the twines are drawn//	
	int     nU1,nU2,nV1,nV2;							//nb of twines drawn 2 for U and 2 for V//	
	double  beginU11,beginU12,beginU21,beginU22,beginV11,beginV12,beginV21,beginV22;//distance of the first twine to the vertex > 0 and < 1//
	double   stepU11, stepU12, stepU21, stepU22, stepV11, stepV12, stepV21, stepV22;//distance between the twine > begin and < 1//
//----dans batz et temporis----//
	double 	lcube;				//size of the cube which represents the volume of floatability of the surface. It is centred on each extremity. 3*lcube³ = volume of surface
	double 	pondFS[4];			//ponderation (>= 0.0 and <= 1.0) of drag force and floatability. pondFS = 0.0 if z-lcube/2 > mh. pondFS = 1.0 if z+lcube/2 < mh. otherwise pondFS = fabs(z-lcube/2)/lcube
	double	EI;				//in case of the twine has beam behavior, EI is the flexion rigidity of twine
	double	alpha0;				//in case of the twine has beam behavior, alpha0 is the neutral angle between twines at knot
	int	nbbar;				//in case of the twine has beam behavior, nbbar is the number of bar elements per half twine
	double pressure_n;			//presure normal to the traiangular surface
	double pressure_t1;			//presure tangent to the traiangular surface along ?
	double pressure_t2;			//presure tangent to the traiangular surface along ?
	double min_exit_size;			//minimum of circle diameter passing trough meshes
	double max_exit_size;			//maximum of circle diameter passing trough meshes
	double mean_exit_size;			//mzan of circle diameter passing trough meshes
	double std_dev_exit_size;		//standard deciation of circle diameter passing trough meshes
	} 	SURFACE;

typedef struct 	surf_hexa {
	int    	type;		 							//no du type de surface//
	int    	extremite[4];								//no des 3 points aux sommets//
	double 	U[4];									//attention redondant avec lon!!!!!!!!!coordonnees des sommets en nombre de mailles selon U//
	double 	V[4];									//attention redondant avec lon!!!!!!!!!coordonnees des sommets en nombre de mailles selon V//
	double 	lon[7];									//coordonnees filaires des 3 sommets dans le sens des diagonales aux mailles//
	double 	nb_cote_l_m_ou_n;							//nb de cotes de mailles l, m ou n dans ce triangle : nb cote l = nb cote m = nb cote n//
	double 	diametremeca;								//diametre mecanique m^2//		
	double 	raideur_traction;							//raideur en traction    (N) = section * module d elasticite//
	double 	raideur_compression;							//raideur en compression (N) = section * module d elasticite//
	double 	raideur_traction_l,raideur_traction_m,raideur_traction_n;		//raideur en traction des fils constituant le filet de ce panneau//
	double 	raideur_compression_l,raideur_compression_m,raideur_compression_n;	//raideur en compression des fils constituant le filet de ce panneau//
	double 	EI_flexion;		//raideur a la flexion des fils em N.m.m//
	double 	tension1;								//tension dans les fils l (N)//
	double 	tension2;								//tension dans les fils m (N)//
	double 	tension3;								//tension dans les fils n (N)//
	double 	lo_repos,mo_repos,no_repos;						//cote de maille l,m,n du filet de ce panneau//
	double	lg_tendue1,lg_tendue2,lg_tendue3;					//longueur du cote de maille l, m et n//
	double 	l[4];									//attention redondant avec lx ly et lz composante du cote de maille l//
	double 	m[4];									//composante du cote de maille m//
	double 	n[4];									//composante du cote de maille n//
	double 	lx,ly,lz;								//composante de la longueur du cote de maille l selon l axe x//
	double 	mx,my,mz;								//composante de la longueur du cote de maille m selon l axe x//
	double 	nx,ny,nz;								//composante de la longueur du cote de maille n selon l axe x//
	double	nrj1,nrj2,nrj3;                               				//energie potentielle du cote de maille l m et n//
	double	nrj;									//energie potentielle des 3 cotes de maille l m et n//
	double 	diam_hydro_l,diam_hydro_m,diam_hydro_n;					//diametre hydro des fils du filet de ce panneau//
	double 	diametrehydro;								//diametre hydrodynamique m//
	double 	largeurnoeud;								//largeur du noeud  m//
	double 	rhosurface;								//masse volumique kg/m^3//
	double 	cdnormal;								//coef. de trainee normal//
	double 	ftangent;								//coef. de trainee tangent//
	int 	tarp;									//if 1 the panel is water proof like a tarp if 0 it is a netting//
//----dans batz et temporis----//
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
//----dans batz et temporis----//
	} 	SURFACE_HEXA;


typedef struct two_parameters
   	{
   	int	pa1;		//first panel//
   	int	pa2;		//second panel//
   	int	no1;		//first corner//
   	int	no2;		//second second//
   	int	co1;		//first direction//
   	int	co2;		//second direction//
   	double	pl1;		//first plage//
   	double	pl2;		//second plage//
   	double	st1;		//first step//
   	double	st2;		//second step//
   	int	code;		//code 0 no two_parameters 1: two_parameters//
   	int	vect1;		//place of the first  point in vect of parameters//
   	int	vect2;		//place of the second point in vect of parameters//
   	}	TWO_PARAMETERS;
   	
typedef struct Type_Noeud_XYZ_SUPINF
	{
	/*9 code :
	si 1 : limite SUP selon X	si 2 : limite INF selon X
	si 3 : limite SUP selon Y	si 4 : limite INF selon Y
	si 5 : limite SUP selon Z	si 6 : limite INF selon Z
	si 7 : limite SUP selon X  et limite INF selon X
	si 8 : limite SUP selon X  et limite INF selon X
	si 9 : limite SUP selon X  et limite INF selon X
	si 10 : limite SUP selon X  et limite INF selon X et limite SUP selon Y  et limite INF selon Y 
	si 11 : limite SUP selon Y  et limite INF selon Y et limite SUP selon Z  et limite INF selon Z
	si 12 : limite SUP selon Z  et limite INF selon Z et limite SUP selon X  et limite INF selon X
	si 13 : limite SUP selon X  et limite INF selon X et limite SUP selon Y  et limite INF selon Y et limite SUP selon Z  et limite INF selon Z
	*/
	int *code; 			//code//
	double *limite; 		//limite de position des noeud			code =  1 à  6//
	double *limite_basse1; 	//limite basse de position des noeud		code =  7 à 13//
	double *limite_haute1; 	//limite haute de position des noeud		code =  7 à 13//
	double *limite_basse2; 	//limite basse de position des noeuds		code = 10 à 13//
	double *limite_haute2; 	//limite haute de position des noeuds		code = 10 à 13//
	double *limite_basse3; 	//limite basse de position des noeuds		code = 13//
	double *limite_haute3; 	//limite haute de position des noeuds		code = 13//
	int *type; 			//type du noeud depassant la limite//
	} TYPE_NOEUD_XYZ_SUPINF;

   	
typedef struct value
   	{
	double 	*depth1;	//first depth//	
	double 	*depth2;	//second depth//			
	double 	*value1;	//value for the first depth//			
	double 	*value2;	//value for the second depth//			
   	}	VALUE;

// debut modifdp du 12 mars 2010//	
typedef struct vector_tension_bar
   	{
	int 	*bar;	//element1//	
   	}	VECTOR_TENSION_BAR;
// fin modifdp du 12 mars 2010//	

typedef struct 	vent {
	double 	vitesse;	//amplitude (m/s)//
	double 	direction;	//direction dans le plan horizontal relativement a l axe X (deg.)//
	} 	VENT;	

typedef struct 	winch {
	int    	extremite[3];		//no des 2 points d extremites//
	int    	nb_barre;		//nb de noeuds internes dans la coulisse en commencant par extremite 1//
	int    	type_noeud;		//type of node//
	int    	*noeud;			//numeros des noeuds internes dans la coulisse en commencant par extremite 1//
	int 	*barre;			//indice barre a l interieur de l element//
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
	int 	flag_maillage;			//1 si maille 0 si pas maille//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//
	} 	WINCH;

// "define" //
#define NOMBRE_BALLS   		Structure.nombreBalls
#define NOMBRE_COULISSES 	Structure.nombreCoulisses
#define DIVISEUR        	Structure.diviseur
#define NOMBRE_ELEMENTS 	Structure.nombreElements
#define NOMBRE_NOEUDS   	Structure.nombreNoeuds
#define NOMBRE_SURFACES 	Structure.nombreSurfaces
#define NOMBRE_SURF_HEXA 	Structure.nombreSurfHexa
#define NOMBRE_WINCHS 		Structure.nb_winch


typedef double TCOO1[DIM1];   
typedef double TCOO2[DIM2];
typedef double TMKB[7],TMKB3[10],Tab1[4];
typedef double TMK2[DIM1][2*DIM3];
typedef int    TLARGE1[DIM1];
typedef int    TLARGE2[DIM2];
typedef double TMKK[65][65],TMKC[10][10];



//------dans Batz------//

CLASS int    	flag_dessin_axes;		//si 1 dessin sinon 0, par defaut 1//
CLASS int    	flag_dessin_quadrillage;	//si 1 dessin sinon 0, par defaut 1//
CLASS int    	flag_dessin_commentaires;	//si 1 dessin sinon 0, par defaut 1//
CLASS int    	flag_dessin_efforts_externes;	//si 1 dessin sinon 0, par defaut 1//
CLASS int    	flag_dessin_deplacement;	//si 1 dessin sinon 0, par defaut 1//
CLASS int    	flag_dessin_trajectoire;	//si 1 dessin sinon 0, par defaut 1//
CLASS int    	flag_dessin_immersion;		//si 1 dessin sinon 0, par defaut 1//
 

//*** declaration de variables globales par ordre alphabétique ***//


CLASS struct add_node_panel   		Add_node_panel; 
CLASS struct ball   			Ball; 
CLASS struct ballast   		Ballast[6]; 
CLASS struct deck   		Deck[60]; 
CLASS struct bottom	  		Bottom;
CLASS struct codend			Codend;
CLASS struct coulisse   		Coulisse[DIM2], coulisse[NBMAXELEMENT], coulisse_old[NBMAXELEMENT];
CLASS struct slider   			Slider[DIM2];
CLASS struct courant   		Courant;
CLASS struct element   		Element[DIM2],TypeElement[DIM2],element_init[NBMAXELEMENT], element[NBMAXELEMENT]; 
CLASS struct houle     		Houle;
CLASS struct lien			Lien[NBMAXLIAISON];
CLASS struct noeud     		Noeud[DIM1],TypeNoeud[DIM1],noeud_init[NBMAXNOEUD], noeud[NBMAXNOEUD],noeud_global[NBMAXNOEUD],noeud_old[NBMAXNOEUD],noeud_seam[NBMAXNOEUD];
CLASS struct orientation_netting	Orientation_netting;
CLASS struct grid_drag			Grid_drag;
CLASS struct energy_bottom		Energy_bottom;
CLASS struct foot_print		Foot_print;
CLASS struct opening_angle		Opening_angle;
CLASS struct opening_mesh		Opening_mesh;
CLASS struct opening_angle_stripe	Opening_angle_stripe;
CLASS struct plan_cutting		Plan_cutting;
CLASS struct prise     		Prise, Catch2_length[5], Catch2_surface[5], Catch2_volume[5];
CLASS struct prise     		Catch2_weight[5], Cage_volume[21], Volume_cage[21];
CLASS struct recouvrement_x		Recouvrement_x;
CLASS struct sortie_texte		Sortie_texte;
CLASS struct sphere_element		Sphere_element;
CLASS struct spheric_limit    	Spheric_limit;
CLASS struct structure 		Structure, structure, struct_old; 
CLASS struct surface   		Surface[DIM2],TypeSurface[DIM2];
CLASS struct surf_hexa 		Surf_Hexa[DIM2],TypeSurfHexa[DIM2], surf_hexa[NBMAXTRIHEXA],surf_hexa_old[NBMAXTRIHEXA]; 
CLASS struct value			Value;
CLASS struct vector_tension_bar	Vector_tension_bar;
CLASS struct vent   			Vent;
CLASS struct winch   			Winch[DIM2], winch[NBMAXELEMENT]; 

CLASS BARRE				barre[NBMAXBARRE],barre_old[NBMAXBARRE];
CLASS BARRE_WINCH			barre_winch[NBMAXBARRE],barre_winch_old[NBMAXBARRE];
CLASS INVERSION_TRIANGLES		inversion_triangles;
CLASS NUMERIQUE				Numerique;
CLASS ORDRE				ordre;
CLASS NODE_PANEL2ROPES			node_panel2ropes;
CLASS PANNEAU				panneau[NBMAXPANNEAU],panneau_init[NBMAXPANNEAU];
CLASS PANNEAU_HEXA			pan_hexa[NBMAXPANHEXA];
CLASS TYPE_NOEUD_XYZ_SUPINF		type_noeud_XYZ_SUPINF;



CLASS int    eca,nbiter,nbpas,nbopti,Nbmaxiterations,Periodeimpression,Diviseurhoule,largeur_matrice, Auto_convergence;
CLASS int    jlra,jlrb,jlrc,miseentension,lectsta,NbTypeNoeud,NbTypeelem,NbTypesurf,NbTypesurfHexa;
CLASS int    rang[5][DIM1],*colo,nb_col,KLL,KUU;
CLASS int    nb_u_tension,nb_v_tension,nb_pt_aval;
CLASS int    Nnonnul, find_link;
CLASS int    nbm,nbm1;
CLASS int    nb_fil[DIM2][3];
CLASS double RW,MW,RSUM,MSUM,RTEN,MTEN,lambda,hh1,tt,delt,nu,Seuilconvergence,Dureedynamique,Amolissement, RMEAN,MMEAN,Relaxation,RHO_AIR,RHO;
CLASS double mean_desequilibrium_X,mean_desequilibrium_Y,mean_desequilibrium_Z;
CLASS double Deplacement,k,omega,Depth1,Numtemps,Pascalcul,Passtockage,Debutstockage,Finstockage,Nextstockage, Numtemps_relax, deltat;
CLASS double X1,X2,X3,Y1,Y2,Y3,alpha,betaa,iterationfin,precedent;
CLASS double nbmaille,nbmaillu1,nbmaillv1,nbmaillu2,nbmaillv2,alpha1,beta1,alpha2,prise,seuilprise,frontx,coef_frottement_sol,raidfond;
CLASS double mailleparpoint[DIM2][7], bag,frontz;
CLASS double wg[7][7],NT[7],etat_converg[1001][5];
CLASS double Relaxation,min_energy,max_energy,min_tension1,max_tension1,min_tension2,max_tension2,min_stress1,max_stress1,min_stress2,max_stress2;
CLASS double double_temp,amplitude_value_calculation;
CLASS double valeur,min_exit_diameter,max_exit_diameter;
CLASS double SM;   /*surface mouillee d'un element triangulaire*/

//TCOO1  wa,wasurf,waelem,wanoeud,wb,wf,wh,wv,mh,mvh,mgh,wf1,wf2,mvb, mvb1, mgb,wfcodend, waemodif,waecontact;
CLASS double wa[DIM1],wasurf[DIM1],waelem[DIM1],wanoeud[DIM1],wb[DIM1],wf[DIM1],wh[DIM1],wv[DIM1],mh[DIM1],mvh[DIM1],mgh[DIM1],wf1[DIM1],wf2[DIM1],mvb[DIM1], mvb1[DIM1], mgb[DIM1],wfcodend[DIM1], waemodif[DIM1],waecontact[DIM1];
//TCOO2  wt,wtfinal,raideur;
CLASS double wt[DIM2],wtfinal[DIM2],raideur[DIM2];
CLASS Tab1   ne,te;
CLASS TMKB   wd;
CLASS TMKB3  wae,ET,EN,ETuv,ENuv,ETu_ou_v,ENu_ou_v,ETlmn,ENlmn,Pe;
CLASS TMKC   kcontact,kmodif,we;
CLASS int *ia, *ja, *ka, *P;
CLASS double **ze,*xze,*cze,**ze_modif,*xze_modif,*cze_modif,**ze_contact,*xze_contact,*cze_contact, *a, *A;
CLASS TLARGE1 fixation,fixa,whs,wl;

CLASS FILE   *file1, *file2;

CLASS float minx,maxx,miny,maxy,minz,maxz,ecartmax; //valeursmaximales des coordonnees//
CLASS float binx,baxx,biny,baxy,binz,baxz,bcartmax; //valeursmaximales des coordonnees dessinnees//
//CLASS Widget w[100];
//CLASS int total2global[NBMAXNOEUD],profondeur[NBMAXNOEUD];
CLASS char fname1[128],fname2[128],fname3[128];
CLASS char fname[128],oldfic[128],newfic[128];
CLASS float *h1x,*h2x,*h1y,*h2y,*g1x,*g2x,*g1y,*g2y;



typedef struct {
	int  tag;
	char *label;
	void *data;
	int  init;
	} TagList;

CLASS int Flag_Fichier_charge; 		// 1 si le fichier est charge 0 sinon //
CLASS int Flag_Fichier_charge_don; 	// 1 si le fichier est charge 0 sinon //
CLASS int Flag_Fichier_charge_mdg; 	// 1 si le fichier est charge 0 sinon //
CLASS int Flag_Fichier_charge_sta; 	// 1 si le fichier est charge 0 sinon //
CLASS int Flag_Fichier_cree; 		// 1 si le fichier est cree 0 sinon //
CLASS int Flag_Fichier_cree_sta; 	// 1 si le fichier est cree 0 sinon //
CLASS int Flag_Fichier_cree_mdg; 	// 1 si le fichier est cree 0 sinon //
CLASS int Flag_Mesh;    		// 1 si mesh est fait 0 sinon //
CLASS int periode_fils;    		//periode fils  //


int GetValues_2(TagList *tags);

//marge sur le graphique//
#define marge 0.05


CLASS FILE *fic_ps; 		// handle du fichier Postscript //
CLASS int hauteur_police_ps; 
CLASS int largeur_police_ps; 
CLASS float epaisseur_trait_ps;
CLASS char mode_portrait;	// PostScript : sortie paysage ou portrait //
CLASS char flag_ps; 		// Sortie Postscript ? //
CLASS char flag_ortho_norm; 	// flag : tracer dans un repere orthonorme //
CLASS int taille_police_x; 	// sur l'ecran //
CLASS int taille_police_y; 	// sur l'ecran //
CLASS int delta_caract_x;	// offset graphique : nb de demi caractere horizontal //
CLASS int delta_caract_y;	// offset graphique : nb de demi caractere vertical //
CLASS char flag_delta_carac;	// flag : utilise dans les routines graphiques pour effectuer un decalage de delta_carac sur les coordonnees //
CLASS char ligne_motif[10][5]; 	// definition des styles (motif) des traces de ligne //
CLASS float RESOLUTION_X_FEN; 	// Largeur de la fenetre sur l'ecran //
CLASS float RESOLUTION_Y_FEN; 	// Hauteur de la fenetre sur l'ecran //



