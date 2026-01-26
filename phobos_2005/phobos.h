#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


#if PRINCIPAL>0
#define CLASS	
#else
#define CLASS extern
#endif

#include "libsx.h"		// should come first, defines libsx stuff  //
#include "../lib_dp/definition_lib.h"

#define REEL			float
#define REAL			double		//utilise dans triangle.c//
/*
typedef struct MyProgram
	{
	int   win_width, win_height;
	}MyProgram;
*/
#include "triangle.h"
#include "const.h"
#include "protos.h"


#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

// define's //
#define X_SIZE 480		// default draw area size, change as desired //
#define Y_SIZE 685
/*
#define NBMAXNOEUD		20000
#define NBMAXTRIANGLE		14000
#define NBMAXTRIHEXA		5000
#define NBMAXPANNEAU		1000
#define NBMAXPANHEXA		200
#define NBMAXELEMENT		20000	
#define NBMAXBARRE		5000
#define NBMAXTYPEBARRE		1900
#define NBMAXNOEUDCONTOUR	150
#define NBMAXNOEUDCOTE		200
#define NBMAXNOEUDINTERIEUR	20000
#define NBMAXLIAISON		1500
#define NBMAXTYPENOEUD		100
#define DIM1                    9000

#define G 9.81                     // pesanteur  //
#define PI (4.0 * atan(1.0))
#define RHO 1025		// masse volumique de l eau  //
*/
/*
CLASS float minx,maxx,miny,maxy,minz,maxz,ecartmax; //valeursmaximales des coordonnees//
CLASS float binx,baxx,biny,baxy,binz,baxz,bcartmax; //valeursmaximales des coordonnees dessinnees//*/
CLASS Widget w[200];
CLASS int total2global[NBMAXNOEUD],profondeur[NBMAXNOEUD],gris_interne,gris_externe;/*
CLASS char fname1[128],fname2[128],fname3[128];
CLASS char fname[128],oldfic[128],newfic[128];
CLASS float *h1x,*h2x,*h1y,*h2y,*g1x,*g2x,*g1y,*g2y;
*/

/**** variables globales ****/

//CLASS BALL			Ball;
//CLASS BARRE			barre[NBMAXBARRE],barre_old[NBMAXBARRE];
//CLASS BARRE_WINCH		barre_winch[NBMAXBARRE],barre_winch_old[NBMAXBARRE];
//CLASS BOTTOM			Bottom;
//CLASS COULISSE  		coulisse[NBMAXELEMENT], coulisse_old[NBMAXELEMENT];
//CLASS COURANT   		Courant;
//CLASS ELEMENT   		element[NBMAXELEMENT];
//CLASS HOULE     		Houle;
//CLASS INVERSION_TRIANGLES	inversion_triangles;
//CLASS LIEN			lien[NBMAXLIAISON];
//CLASS NOEUD     		noeud[NBMAXNOEUD],noeud_global[NBMAXNOEUD],noeud_old[NBMAXNOEUD],noeud_seam[NBMAXNOEUD];
//CLASS NUMERIQUE			Numerique;
//CLASS OPENING_ANGLE		Opening_angle;
//CLASS OPENING_MESH		Opening_mesh;
//CLASS OPENING_ANGLE_STRIPE	Opening_angle_stripe;
//CLASS ORDRE			ordre;
//CLASS PANNEAU			panneau[NBMAXPANNEAU];
//CLASS PANNEAU_HEXA		pan_hexa[NBMAXPANHEXA];
//CLASS PRISE     		Prise;
//CLASS SORTIE_TEXTE	  	Sortie_texte;
//CLASS SPHERE_ELEMENT		Sphere_element;
//CLASS STRUCTURE		structure, struct_old;
CLASS SURFACE			surface[NBMAXTRIANGLE],surface_old[NBMAXTRIANGLE];
//CLASS SURFACE_HEXA		surf_hexa[NBMAXTRIHEXA],surf_hexa_old[NBMAXTRIHEXA];
//CLASS TYPE_NOEUD_XYZ_SUPINF	type_noeud_XYZ_SUPINF;
//CLASS WINCH  			winch[NBMAXELEMENT];
/*
typedef struct {
	int  tag;
	char *label;
	void *data;
	int  init;
	} TagList;
*/
CLASS char triswitches[10];
CLASS struct triangulateio in;
CLASS struct triangulateio out;
CLASS struct triangulateio vorout;
/*
CLASS int Flag_Fichier_charge; 		// 1 si le fichier est charge 0 sinon //
CLASS int Flag_Fichier_charge_don; 	// 1 si le fichier est charge 0 sinon //
CLASS int Flag_Fichier_charge_mdg; 	// 1 si le fichier est charge 0 sinon //
CLASS int Flag_Fichier_charge_sta; 	// 1 si le fichier est charge 0 sinon //
CLASS int Flag_Fichier_cree; 		// 1 si le fichier est cree 0 sinon //
CLASS int Flag_Fichier_cree_sta; 	// 1 si le fichier est cree 0 sinon //
CLASS int Flag_Fichier_cree_mdg; 	// 1 si le fichier est cree 0 sinon //
CLASS int Flag_Mesh;    		// 1 si mesh est fait 0 sinon //
CLASS int periode_fils;    		//periode fils  //
*/

/*
#define TAG_NULL          0
#define TAG_STRING        1
#define TAG_INT           2
#define TAG_FLOAT         3
#define TAG_LABEL         4
#define TAG_WINDOW_LABEL  5
#define TAG_DONE          99

#define TAG_INIT    1
#define TAG_NOINIT  0

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

*/
/*
CLASS struct 	ball {
	int    	nb;		//balls nb
	double  *radius;	//table of radius of balls
	double  *birth_time;	//birth time
	int    	*noeud;		//numeros du noeud de cette ball
	double  *x;		//x position
	double  *y;		//y position
	double  *z;		//z position
	double  *stiffness;	//N/m
	int    	*type;		//type of the ball one born
	double  *ini_speed_x;	//m/s
	double  *ini_speed_y;	//m/s
	double  *ini_speed_z;	//m/s
	} 	Ball;

CLASS struct Noeud
	{
	REEL x;								//coordonnee cartesienne selon x//
	REEL y;								//coordonnee cartesienne selon y//
	REEL z;								//coordonnee cartesienne selon z//
	REEL xcal;							//coordonnee cartesienne calculee selon x//
	REEL ycal;							//coordonnee cartesienne calculee selon y//
	REEL zcal;							//coordonnee cartesienne calculee selon z//
	REEL U;								//coordonnee selon U en nb de maille pour les filets//
	REEL V;								//coordonnee selon V en nb de maille pour les filets//
	REEL u;								//coordonnee selon U en nb de maille pour les filets//
	REEL v;								//coordonnee selon V en nb de maille pour les filets//
	int flag_dessin;						//1 si dessine 0 si pas dessine//
	int type; 							//type du noeud//
	int flag_sta; 							//1 si visite, 0 sinon//
	} noeud[NBMAXNOEUD],noeud_global[NBMAXNOEUD],noeud_old[NBMAXNOEUD],noeud_seam[NBMAXNOEUD];

CLASS struct Barre
	{
	int  noeud[3]; 							//indice des noeuds extremite//
	REEL longueur_repos;						//longueur au repos//
	REEL elongation;						//elongation//
	REEL longueur_tendue;                                           //longueur tendue//
	REEL tension;                                                  	//tension//
	REEL nrj;                                                       //energie potentielle//
	int flag_dessin;						//1 si dessine 0 si pas dessine//
	REEL pro[3];							//proportion a la longueur de la barre//
	int  type; 							//type de la barre//
	} barre[NBMAXBARRE],barre_old[NBMAXBARRE];

CLASS struct Element
	{
	int    	type;		 	//no du type de l element//
	int    	extremite[3];		//no des 2 points d extremites//
	int 	*noeud;			//indice noeud a l interieur de l element//
	int 	*barre;			//indice barre a l interieur de l element//

	double  pro[3];			//position des 2 extremites en proportion de la longueur de l element de phobos//
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
	int	*haul_ext;		//in case of dynamic: extremity of the cable by which the cable is hauled or shooted//
	int	*link_flexion;		//in case of 2 cables are connected//
	int    	color;			//fonction de la tension//
	int    	flag_dessin;		//si 1 dessin sinon 0, par defaut 1//

	double  *lrepos;		//longueur repos dynamique//
	double 	*dtension;
	double 	*dlgtendue;
	double 	*dcontrainte;		//contrainte dynamique//

	double 	nrj;
	double 	*dnrj;

	float symmetry_plan;			//value of the plan of symmetry for the plan//
	} element[NBMAXELEMENT];

CLASS struct Barre_winch
	{
	int  noeud[3]; 							//indice des noeuds extremite//
	REEL longueur_repos;						//longueur au repos//
	REEL elongation;						//elongation//
	REEL longueur_tendue;                                           //longueur tendue//
	REEL tension;                                                  	//tension//
	REEL nrj;                                                       //energie potentielle//
	REEL pro[3];							//proportion a la longueur de la barre//
	int  type; 							//type de la barre//
	} barre_winch[NBMAXBARRE],barre_winch_old[NBMAXBARRE];

CLASS struct Winch
	{
	int nb_barre; 				//nb de barre dans l element//
	int extremite[3];			//indice des noeuds aux extremites//
	int *noeud;				//indice noeud a l interieur de l element//
	int *barre;				//indice barre a l interieur de l element//
	float raideur_traction;			//raideur en traction//
	float raideur_compression;		//raideur en compression//
	float longueur_repos;			//longueur au repos//
	float rho;				//masse volumique//
	float diam_hydro;			//diametre hydrodynamique//
	float cdnormal;				//coefficient de trainee//
	float ftangent;				//coefficient de trainee//
	float adjust_force;			//force on the cable from the winch (N)//
	int flag_maillage;			//1 si maille 0 si pas maille//
	int flag_dessin;			//1 si dessine 0 si pas dessine//
	int type_noeud;				//type des noeud a l interieur de l element//
	} winch[NBMAXELEMENT];

CLASS struct Coulisse
	{
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
	} coulisse[NBMAXELEMENT], coulisse_old[NBMAXELEMENT];

CLASS struct Triangle
	{
	int noeud[4]; 				//indice des sommets du triangle//
	int type; 				//numero du panneau//
	int numerotation_locale; 		//numero du triangle dans le panneau//
	REEL U[4];				//coordonnees des sommets en nombre de mailles selon U//
	REEL V[4];				//coordonnees des sommets en nombre de mailles selon V//
	REEL n[4];				//composante du cote de maille n//
	REEL m[4];				//composante du cote de maille m//
	REEL tension1;				//tension du cote de maille m//
	REEL tension2;				//tension du cote de maille n//
	REEL lg_tendue1;			//longueur du cote de maille m//
	REEL lg_tendue2;			//longueur du cote de maille n//
	REEL nrj1;                              //energie potentielle du cote de maille m//
	REEL nrj2;                              //energie potentielle du cote de maille n//
	REEL nrj;	
	REEL Nx;				//composante selon x de la normale normee au triangle//
	REEL Ny;
	REEL Nz;
	REEL defaut_disc;			//mesure du defaut de discretisation//
	REEL nb_cote_u_ou_v;			//nb de fils u ou v dans un triangle//	
	}triangle[NBMAXTRIANGLE],triangle_old[NBMAXTRIANGLE];

CLASS struct Tri_Hexa
	{
	int noeud[4]; 				//indice des sommets du triangle//
	int type; 				//indice des cotes du triangle//
	REEL U[4];				//coordonnees des sommets en nombre de mailles selon U//
	REEL V[4];				//coordonnees des sommets en nombre de mailles selon V//
	REEL l[4];				//composante du cote de maille l//
	REEL m[4];				//composante du cote de maille m//
	REEL n[4];				//composante du cote de maille n//
	REEL tension1;				//tension du cote de maille l//
	REEL tension2;				//tension du cote de maille m//
	REEL tension3;				//tension du cote de maille n//
	REEL lg_tendue1;			//longueur du cote de maille l//
	REEL lg_tendue2;			//longueur du cote de maille m//
	REEL lg_tendue3;			//longueur du cote de maille n//
	REEL nrj1;                               //energie potentielle du cote de maille l//
	REEL nrj2;                               //energie potentielle du cote de maille m//
	REEL nrj3;                               //energie potentielle du cote de maille n//
	REEL nrj;	
	REEL nb_cote_l_m_n;			//nb de fils u ou v dans un triangle//	
	}tri_hexa[NBMAXTRIHEXA],tri_hexa_old[NBMAXTRIHEXA];


CLASS struct Panneau
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
	int *numero_triangle;				//liste des indices des noeuds interieurs//
	int nb_triangle_interieur; 			//nb de triangles interieurs//
	int triangle_interieur[NBMAXNOEUDINTERIEUR][4];	//sommets des triangles interieurs dans la numerotation totale//
	int nb_triangle_contour; 			//nb de triangles poses sur le contour//
	int triangle_contour[NBMAXNOEUDCONTOUR][4];	//sommets des triangles poses sur le contour dans la numerotation locale//
	float pas_maillage;				//pas du maillage des noeuds interieurs//
	int type_maillage;				//type du maillage//
	int flag_maillage;				//1 si maille 0 si pas maille//
	int flag_filet_contour;				//1 si la triangulation sur le contour    est calculee 0 sinon//
	int flag_filet;					//1 si la triangulation sur ts les points est calculee 0 sinon//
	int flag_dessin;			//1 si dessine 0 si pas dessine//
	float raideur_traction;				//raideur en traction des fils constituant le filet de ce panneau//
	float raideur_compression;			//raideur en compression des fils constituant le filet de ce panneau//
	double 	EI_flexion;				//raideur a la flexion des fils em N.m.m//
	float raideur_ouverture;			//raideur a l ouverture des mailles du filet de ce panneau//
	double 	neutral_angle;				//angle au repos du panneau en rad//
	float longueur_repos;				//cote de maille du filet de ce panneau//
	float diam_hydro;				//diametre hydro des fils du filet de ce panneau//
	float largeurnoeud;				//largeur des noeuds du filet de ce panneau//
	float rho;					//masse volumique des fils constituant le filet de ce panneau//
	float cdnormal;					//coef de trainee normale des fils constituant le filet de ce panneau//
	float ftangent;					//coef de trainee tangentielle des fils constituant le filet de ce panneau//
	double 	energy_pliage;				//energie potentielle liee au pliage de 2 triangles joints//
	double 	energy_ouverture;			//energie potentielle liee a l'ouverture des mailles//
	double 	energy_elastique;			//energie potentielle liee a l elongation des fils//
	double 	energy_contact;				//energie potentielle liee au contact entre les fils//
	float surf_fils;				//surface de fils de ce panneau//
	int type_noeud;					//type des noeud a l interieur du panneau//
	double 	drag;					//total drag of the panel//
	double 	seam;					//seam size in mesh number//
	float symmetry_plan;	////			//value of the plan of symmetry for the plan//
	} panneau[NBMAXPANNEAU];


CLASS struct Pan_Hexa
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
	double 	drag;					//total drag of the panel//
	} pan_hexa[NBMAXPANHEXA];

CLASS struct Chalut
	{
	int nb_ordre_objet;             //nombre d'objets(panneau,element,coulisse,pan_hexa)//
	int nb_fils; 			//nombre de fils dans les triangles contour constituants le chalut//
	int T90_nb_fils; 			//nombre de fils dans les triangles contour constituants le chalut//
	int nb_panneau; 		//nombre de panneaux a maille losange constituants le chalut//
	int nb_pan_hexa; 		//nombre de panneaux a maille hexagonale constituants le chalut//
	int nb_element; 		//nombre de elements constituants le chalut//
	int nb_selvedges; 		//nombre de rallingues  constituants le chalut//
	int nb_winch; 			//nb of winches in the structure//
	int nb_coulisse; 		//nombre de coulisses constituants le chalut//
	int nb_liaison; 		//nombre de liaisons dans le chalut//
	int nb_lien; 			//nombre de liens dans le chalut >=  liaisons//
	int nb_total;			//nombre de noeuds dans la numerotation totale dans le chalut//
	int nb_global;			//nombre de noeuds dans la numerotation globale dans le chalut apres renumerotation//
	int nb_type_noeud;		//nombre de type de noeud dans le chalut//
	int nb_barre;			//nombre de barre dans le chalut//
	int nb_barre_winch;		//nombre de barre dans le chalut//
	int nb_barre_selvedges;		//nombre de barre dans le chalut//
	int nb_surface;			//nombre de surface dans le chalut//
	int nb_surf_hexa;		//nombre de surface a maille hexagonale dans le chalut//
	float surface_fils;		//surface de fils du chalut tel que maille//
	int orientation;		//orientation du dessin 1 (2,3) perpendiculaire a l axe x (y,z)//
	int version;			//version//
	int graphic;			//if 1 it is calculated with the graphic tool, if 2 or 3 it is calculated by the text tool//
	int drawing;			//0 (default) in colors, 1 in black//
 	char nomfichier1[100],nomfichier2[100];//files name//
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

	int nb_sphere_element;		//nb of sphere element cases//
	int nb_connect_panel_node;	//nb of nodes coordinates linked to two anaother node//
	} chalut,chalut_old;

CLASS struct sphere_element
   	{
	int 	*element;	//cable on which the sphere are//	
	int 	*nb;		//number of sphere//			
	double 	*diameter;	//diameter of the each sphere floats (m)//			
	double 	*floatability;		//floattability of each float (N)//			
   	}	Sphere_element;
   	

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
	


CLASS struct Point {
	float 	mx,my,mz;
	float 	majx,majy,majz;
	float 	lonx,lony,lonz;
	float 	cdx,cdy,cdz;
	float 	fextx,fexty,fextz;
	int   	fixx,fixy,fixz;
	float 	limx,limy,limz;
	int   	senx,seny,senz;
	int   	symx,symy,symz;
	} TypeNoeud[DIM1]; 
	
CLASS struct Lien
	{
	int  nb_liaison;		//nb de noeud utilisant cette liaison//
	char *type; 			//types des structures liees//
	int  *structure; 		//indice des structures liees//
	int  *extremite; 		//indice des noeuds lies (numerotation locale)//
	int  *noeud; 			//indice des coins lies (numerotation totale)//
	} lien[NBMAXLIAISON];

CLASS struct ordre
	{
	char *type;
	int  *indice;
	} ordre;
	
CLASS struct numerique {
	float DIVISEUR;			//raideur additionnelle en N//
	int Nbmaxiterations;		//nb max d iterations realisees dans unix//
	float Seuilconvergence;		//seuil de convergence en N//
	float Deplacement;		//deplacement maximal autorise en m//
	float Pascalcul;		//pas de calcul en dynamique en s//
	float Passtockage;		//pas de stockage en dynamique en s//
	float Debutstockage;		//debut du stockage en dynamique en s//
	float Finstockage;		//fin du stockage et du calculen dynamique en s//
	} Numerique;	

CLASS struct houle {
	float hauteur;			//hauteur de crete a creux en m//
	float periode;			//periode en s > 0//	
	float direction;		//direction dans XoY relativement a oX en degre//
	float Depth1;			//profondeur d eau en m > 0//
	} Houle;	

CLASS struct courant {
	float vitesse;			//amplitude de vitesse en m/s//
	float direction;		//direction dans XoY relativement a oX en degre//
	} Courant;

CLASS struct prise {
	float volume;			//volume de la prise en m3 ne tient pas compte des symetrie//
	float seuil;			//seuil sur ce volume en m3//
	float cd;			//coef de trainee sur la prise//
	float front;			//position du front en m//
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
	int 	dir_mesh_front;		////
	int	panels[3];		//the 2 panels where the limit is calculated//
	} Prise;	

CLASS struct fond {
	float raideur;			//raideur a l enfoncement en N/m//
	float coef_frottement;		//rapport effort horizontal sur vertical//
	} Fond;
	
CLASS struct opening_angle {
	int nb_panel;			//raideur a l enfoncement en N/m//
	int  *panel; 		//numero of the involved panels//
	double pas;			//raideur a l enfoncement en N/m//
	int nb_tab;			//raideur a l enfoncement en N/m//
	} Opening_angle;
	
CLASS struct opening_mesh {
	int nb_panel;			//raideur a l enfoncement en N/m//
	int  *panel; 		//numero of the involved panels//
	double pas;			//raideur a l enfoncement en N/m//
	int nb_tab;			//raideur a l enfoncement en N/m//
	} Opening_mesh;
	
CLASS struct opening_angle_stripe {
	int nb_panel;			//raideur a l enfoncement en N/m//
	int  *panel; 		//numero of the involved panels//
	double pas;			//raideur a l enfoncement en N/m//
	int nb_tab;			//raideur a l enfoncement en N/m//
  	double  stripe_step; 	//step of stripe in m//
	int nb_stripe;			//raideur a l enfoncement en N/m//
	} Opening_angle_stripe;
	
typedef struct 	commentaire {
	char texte[156];
	} 	COMMENTAIRE;

CLASS struct sortie_texte 
	{
	int  nb_distance;			//nb de distance entre 2 points affichees//
	COMMENTAIRE *comment_distance;		//commentaires associes aux distances//
	char *type_structure1_distance; 	//types des structures //
	int  *numero_structure1_distance; 	//indice des structures //
	int  *noeud1_distance;			//premiere extremite de la distance en numerotation locale//		
	char *type_structure2_distance; 	//types des structures //
	int  *numero_structure2_distance; 	//indice des structures //
	int  *noeud2_distance;			//seconde extremite de la distance//		
	int  *decimale_distance;		//nb de decimale pour l affichage de la distance//
	double  *valeur_distance;		//value of the distance//
			
	int  nb_effort;				//nb d effort selon un axe a un point affiches//
	COMMENTAIRE *comment_effort;		//commentaires associes aux distances//
	char *type_structure_effort; 		//types des structures //
	int  *numero_structure_effort; 		//indice des structures //
	int  *noeud_effort;			//noeud en numerotation locale//		
	int  *axe_effort;			//axe de l effort 1 : x, 2 : y et 3 : z//		
	int  *decimale_effort;			//nb de decimale pour l affichage //
	double  *valeur_effort;			//value of the effort//

	int  nb_tension_element;		//nb de tension dans un element affichees//
	COMMENTAIRE *comment_tension_element;	//commentaires associes aux distances//
	int *element_tension;			//premiere extremite de la distance//		
	int *element_extremite;			//premiere extremite de la distance//		
	int *decimale_tension_element;		//nb de decimale pour l affichage de la distance//
	double  *valeur_tension;		//value of the tension in the element//

	int  nb_tension_coulisse;		//nb de tension dans une coulisse affichees//
	COMMENTAIRE *comment_tension_coulisse;	//commentaires associes aux distances//
	int *coulisse_tension;			//premiere extremite de la distance//		
	int *coulisse_extremite;		//premiere extremite de la distance//		
	int *decimale_tension_coulisse;		//nb de decimale pour l affichage de la distance//
	double  *valeur_tension_coulisse;	//value of the tension in the coulisse//

	int  nb_position;			//nb de position selon un axe a un point affichees//
	COMMENTAIRE *comment_position;		//commentaires associes aux distances//
	char *type_structure_position; 		//types des structures //
	int  *numero_structure_position; 	//indice des structures //
	int  *noeud_position;			//noeud en numerotation locale//		
	int  *axe_position;			//axe de l effort 1 : x, 2 : y et 3 : z//		
	int *decimale_position;			//nb de decimale pour l affichage de la distance//
	double  *valeur_position;		//value of the position//
	
	int  nb_longueur_cable;			//nb de longueur de cables affichees//
	COMMENTAIRE *comment_longueur_cable;	//commentaires associes aux longueurs//
	int *element_longueur_cable;		//numero du cable//		
	int *decimale_longueur_cable;		//nb de decimale pour l affichage de la longueur en m//
	double *valeur_longueur_cable;		//valeur de la longueur en m//
	
	int  nb_energie_elong_diamond;		//nb d energies d elongation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_elong_diamond;	//commentaires associes aux energies//
	int *panneau_energie_elong;		//numero du panneau//		
	int *decimale_energie_elong;		//nb de decimale pour l affichage de l energie en J//
	
	int  nb_energie_fold_diamond;		//nb d energies d foldation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_fold_diamond;	//commentaires associes aux energies//
	int *panneau_energie_fold;		//numero du panneau//		
	int *decimale_energie_fold;		//nb de decimale pour l affichage de l energie en J//
	
	int  nb_energie_open_diamond;		//nb d energies d openation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_open_diamond;	//commentaires associes aux energies//
	int *panneau_energie_open;		//numero du panneau//		
	int *decimale_energie_open;		//nb de decimale pour l affichage de l energie en J//
	
	int  nb_energie_contact_diamond;		//nb d energies d openation par panneaux de filets losange affichees//
	COMMENTAIRE *comment_energie_contact_diamond;	//commentaires associes aux energies//
	int *panneau_energie_contact;		//numero du panneau//		
	int *decimale_energie_contact;		//nb de decimale pour l affichage de l energie en J//
	
	int  nb_parametre;			//nb de position selon un axe a un point affichees//
	COMMENTAIRE *comment_parametre;		//commentaires associes aux distances//
	int *decimale_parametre;		//nb de decimale pour l affichage de la distance//

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
	int panel_drag;				//if panel drag is reading (N)//	
	int inner_surface_triangulation;	//si 1 affiche les triangles de l'ellipsoide de la surface interne de la prise (m)//	
	int catch_drag;	   			//si 1 affiche the drag of the catch (N)//	
	int bottom_drag;	   		//si 1 affiche the drag on the bottom (N)//	
	int element_drag;	   		//si 1 affiche the drag on the bottom (N)//	
	int surface_drag;	   		//si 1 affiche the drag on the bottom (N)//	
	int node_drag;	   			//si 1 affiche the drag on the nodes (N)//	
	int meridian;	   			//si 1 affiche the drag on the nodes (N)//	
	int meridian_X;	   			//si 1 affiche the drag on the nodes (N)//	
	int meridian_Y;	   			//si 1 affiche the drag on the nodes (N)//	
	int meridian_Z;	   			//si 1 affiche the drag on the nodes (N)//	
	int curvilinear_codend_length;	   			//si 1 affiche the drag on the nodes (N)//	
	double valeur_catch_drag;	   	//si 1 affiche the drag of the catch (N)//	
	double valeur_bottom_drag;	   	//si 1 affiche the drag on the bottom (N)//	
	double valeur_element_drag;	   	//si 1 affiche the drag on the bottom (N)//	
	double valeur_surface_drag;	   	//si 1 affiche the drag on the bottom (N)//	
	double valeur_node_drag;	   	//si 1 affiche the drag on the nodes (N)//	
	double valeur_effort_structure[4];	   	//si 1 affiche the drag on the nodes (N)//	
	double valeur_diametre_prise;	   	//si 1 affiche the drag of the catch (N)//	
	double valeur_epaisseur_prise;	   	//si 1 affiche the drag of the catch (N)//	
	double valeur_volume_capture;	   	//si 1 affiche the drag of the catch (N)//	
	double valeur_vitesse_courant;	   	//si 1 affiche the drag of the catch (N)//	
	double valeur_surface_filtree;	   	//si 1 affiche the drag of the catch (N)//	

	
	}  Sortie_texte;

CLASS struct Inversion_triangles
	{
	int  nb_inversion_triangles;	//nb d inversions de triangles//
	int  *premier; 			//indice du premier triangle dans la numerotation globale//
	int  *second; 			//indice du second triangle dans la numerotation globale//
	} inversion_triangles;

CLASS struct Type_Noeud_XYZ_SUPINF
	{
	//9 code :
	//si 1 : limite SUP selon X	si 2 : limite INF selon X
	//si 3 : limite SUP selon Y	si 4 : limite INF selon Y
	//si 5 : limite SUP selon Z	si 6 : limite INF selon Z
	//si 7 : limite SUP selon X  et limite INF selon X
	//si 8 : limite SUP selon Y  et limite INF selon Y
	//si 9 : limite SUP selon Z  et limite INF selon Z
	//si 10 : limite SUP selon X  et limite INF selon X et limite SUP selon Y  et limite INF selon Y 
	//si 11 : limite SUP selon Y  et limite INF selon Y et limite SUP selon Z  et limite INF selon Z
	//si 12 : limite SUP selon Z  et limite INF selon Z et limite SUP selon X  et limite INF selon X
	//si 13 : limite SUP selon X  et limite INF selon X et limite SUP selon Y  et limite INF selon Y et limite SUP selon Z  et limite INF selon Z

	int code; 			//code//
	double limite; 		//limite de position des noeuds//
	double limite_basse1; 		//limite basse de position des noeuds//
	double limite_haute1; 		//limite haute de position des noeuds//
	double limite_basse2; 		//limite basse de position des noeuds//
	double limite_haute2; 		//limite haute de position des noeuds//
	double limite_basse3; 		//limite basse de position des noeuds//
	double limite_haute3; 		//limite haute de position des noeuds//
	double limite_basse4; 		//limite basse de position des noeuds//
	double limite_haute4; 		//limite haute de position des noeuds//
	double limite_basse5; 		//limite basse de position des noeuds//
	double limite_haute5; 		//limite haute de position des noeuds//
	double limite_basse6; 		//limite basse de position des noeuds//
	double limite_haute6; 		//limite haute de position des noeuds//
	int type; 			//type du noeud depassant la limite//
	} type_noeud_XYZ_SUPINF;

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

*/

