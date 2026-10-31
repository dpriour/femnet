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

#include "gtk3_compat.h"  /* GTK3/Cairo compatibility declarations */
#include "../lib_dp/definition_lib.h"
#include "../lib_dp/graphic.h"

#define REEL			float
#define REAL			double		//utilise dans triangle.c//

#include "triangle.h"
#include "const.h"
#include "protos.h"


#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

// define's //
#define X_SIZE 1000		// default draw area size, change as desired //
#define Y_SIZE 1300

CLASS Widget w[200];
CLASS int total2global[NBMAXNOEUD],profondeur[NBMAXNOEUD],gris_interne,gris_externe;
CLASS int *colo,nb_col;

/**** variables globales ****/

CLASS SURFACE			surface[NBMAXTRIANGLE],surface_old[NBMAXTRIANGLE];
CLASS char triswitches[10];
CLASS struct triangulateio in;
CLASS struct triangulateio out;
CLASS struct triangulateio vorout;

