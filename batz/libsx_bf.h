#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "libsx.h"		/* should come first, defines libsx stuff  */
#include "../lib_dp/definition_lib.h"
//#include "4c19.h"

#if PRINCIPAL>0
#define CLASS	
#else
#define CLASS extern
#endif

#define REEL			float
#define REAL			double		/*utilise dans triangle.c*/

#include "variables.h"
#include "const.h"

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

/* define's */
#define X_SIZE 600		/* default draw area size, change as desired */
#define Y_SIZE 849

/*marge sur le graphique*/
//#define marge 0.05
/*
#define NBMAXNOEUD		DIM1
#define NBMAXTRIANGLE		DIM2
#define NBMAXELEMENT		DIM2	
#define NBMAXBARRE		DIM2
*/
CLASS int nb_local,nb_global,nb_type_noeud,nb_type_barre,backgroundcolor,gris_interne,gris_externe;
CLASS int nb_type_surface,nb_barre,nb_surface,nb_fils,periode_fils;
CLASS float pas_maille_x,pas_maille_y,profondeur_coupe_float,profondeur_coupe;
CLASS float minx,maxx,miny,maxy,minz,maxz,ecartmax; /*valeursmaximales des coordonnees sans rotation sans zoom*/
CLASS float cinx,caxx,ciny,caxy,cinz,caxz,ccartmax; /*valeursmaximales des coordonnees avec rotation sans zoom*/
CLASS float binx,baxx,biny,baxy,binz,baxz,bcartmax; /*valeursmaximales des coordonnees avec rotation avec zoom*/
CLASS Widget w[100];
CLASS int total2global[NBMAXNOEUD];
CLASS char fname[128];
CLASS char fname1[128];
CLASS char nom_fichier[MLEN];
CLASS float angle_x,angle_y,angle_z;
CLASS int profondeur[NBMAXTRIANGLE + NBMAXTRIANGLE + NBMAXELEMENT + NBMAXELEMENT];/*cote z du barycentre des surfaces des elements et des coulisses*/
/*CLASS float *h1x,*h2x,*h1y,*h2y,*h1z,*h2z;*/
CLASS float elongationmin,elongationmax;		/*valeurs extremes des elongations de fils et elements*/
CLASS float surface_libre[4][5];	/*coordonnees x y et z des 4 coins de la SL*/
CLASS float surface_fond[4][5];		/*coordonnees x y et z des 4 coins de la surface du fond*/
CLASS float surface_front[4][5],surface_front_dessine[4][5];	/*coordonnees x y et z des 4 coins de la surface du front*/

/*
typedef struct MyProgram
	{
	int   win_width, win_height;
	}MyProgram;*/
/*
typedef struct {
	int  tag;
	char *label;
	void *data;
	int  init;
	} TagList;
*/	
CLASS int Flag_Fichier_initial_charge; 	/* 1 si le fichier *.mdf est charge 0 sinon */
CLASS int Flag_Fichier_final_charge; 	/* 1 si le fichier *.sta est charge 0 sinon */

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
#define TAG_NOFLOAT  0
*/
//int GetValues_2(TagList 	*tags);


