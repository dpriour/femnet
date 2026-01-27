#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
/*
#ifdef PRINCIPAL
#define CLASS 	
#else
#define CLASS extern 
#endif
*/

#include "libsx.h"		/* should come first, defines libsx stuff  */
#include "../lib_dp/definition_lib.h"
//#include "4c19.h"
/*
typedef struct MyProgram
	{
	int   win_width, win_height;
	}MyProgram;
*/
#include "protos.h"

#define SORTIE_TEXTE_DISTANCE(X) 		(txt_distance		+(X)*sizeof(struct champ))
#define SORTIE_TEXTE_EFFORT(X) 			(txt_effort		+(X)*sizeof(struct champ))
#define SORTIE_TEXTE_TENSION(X) 		(txt_tension		+(X)*sizeof(struct champ))
#define SORTIE_TEXTE_TENSION_COULISSE(X) 	(txt_tension_coulisse	+(X)*sizeof(struct champ))
#define SORTIE_TEXTE_POSITION(X) 		(txt_position		+(X)*sizeof(struct champ))


#define REEL			float
#define REAL			double		/*utilise dans triangle.c*/

#include "variables.h"

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

/* define's */
#define X_SIZE 467		/* default draw area size, change as desired */
#define Y_SIZE 600

#include "const.h"

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
CLASS float pas_maille_x,pas_maille_y,profondeur_coupe_float,profondeur_coupe,temps_t_float,temps_t;
CLASS float minx,maxx,miny,maxy,minz,maxz,ecartmax; /*valeursmaximales des coordonnees sans rotation sans zoom*/
CLASS float cinx,caxx,ciny,caxy,cinz,caxz,ccartmax; /*valeursmaximales des coordonnees avec rotation sans zoom*/
CLASS float binx,baxx,biny,baxy,binz,baxz,bcartmax; /*valeursmaximales des coordonnees avec rotation avec zoom*/
CLASS Widget w[200];
CLASS int total2global[NBMAXNOEUD];
CLASS char fname[128];
CLASS char fname1[128];
CLASS char nom_fichier[MLEN];
CLASS float angle_x,angle_y,angle_z;
CLASS int profondeur[NBMAXTRIANGLE + NBMAXTRIANGLE + NBMAXELEMENT + NBMAXELEMENT + NBMAXNOEUD + NBMAXNOEUD];/*cote z du barycentre des surfaces des elements et des coulisses*/
/*CLASS float *h1x,*h2x,*h1y,*h2y,*h1z,*h2z;*/
CLASS float *temps;
CLASS int nbtemps,nb_animation,step_animation;
CLASS int no_eigenvalue,n_jacobi_result;
CLASS float scale_eigenvalue;
CLASS float ralenti_animation;
CLASS float depart_anim,fin_anim,depart_anim_sec,fin_anim_sec;
CLASS float elongationmin,elongationmax;		/*valeurs extremes des elongations de fils et elements*/
CLASS float repere[4][5];		/*coordonnees x y et z de l origine du repere et des 3 extremites des axes x y z*/
CLASS double surface_libre[4][5];	/*coordonnees x y et z des 4 coins de la SL*/
CLASS double surface_ballast[4][5];	/*coordonnees x y et z des 4 coins de la surface libre dans le 1er ballast*/
CLASS double surface_fond[4][5];		/*coordonnees x y et z des 4 coins de la surface du fond*/
CLASS double surface_front[4][5],surface_front_dessine[4][5];	/*coordonnees x y et z des 4 coins de la surface du front*/
CLASS double volume_value[4][9],volume_value_dessine[4][9];	/*coordonnees x y et z des 8 coins du volume value*/
CLASS double surface_inner[4][50],surface_inner_dessine[4][50];	
CLASS float *d_jacobi_result,**v_jacobi_result,**v_jacobi_rotati;

/*coordonnees x y et z du centre de lellipoide, du rayon axial d'un rayon radial et de second rayon radial*/
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
*/
//int GetValues_2(TagList *tags);


