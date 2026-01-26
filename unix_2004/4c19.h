#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
#if PRINCIPAL>0
#define CLASS	
#else
#define CLASS extern
#endif
*/
/*Librairies Laspack*/
/*#include "/usr/X11R6/include/laspack/qmatrix.h"
#include "/usr/X11R6/include/laspack/errhandl.h"
#include "/usr/X11R6/include/laspack/itersolv.h"
#include "/usr/X11R6/include/laspack/vector.h"
#include "/usr/X11R6/include/laspack/operats.h"
#include "/usr/X11R6/include/laspack/rtc.h"*/

#include "../lib_dp/definition_lib.h"
#include "../lib_dp/protos_lib.h"
#include "protos_unix.h"



/**** variables globales ****/

//CLASS STRUCTURE  		Structure; 
//CLASS NOEUD     		Noeud[DIM1];//, TypeNoeud[DIM2];
//CLASS ELEMENT   		Element[DIM2],TypeElement[DIM2]; 

//CLASS COULISSE  		Coulisse[DIM2];
//CLASS WINCH  			Winch[DIM2];
//CLASS SURFACE   		Surface[DIM2],TypeSurface[DIM2]; 
//CLASS SURFACE_HEXA   		Surf_hexa[DIM2],TypeSurf_hexa[DIM2]; 
//CLASS HOULE     		Houle;
//CLASS COURANT   		Courant;
//CLASS VENT   			Vent;
//CLASS PRISE     		Prise;
//CLASS PRISE     		Catch2_length[5];
//CLASS PRISE     		Catch2_surface[5];
//CLASS PRISE     		Catch2_volume[5];
//CLASS PRISE     		Catch2_weight[5];
//CLASS PRISE     		Cage_volume[21];
//CLASS PRISE     		Volume_cage[21];
//CLASS SPHERIC_LIMIT     	Spheric_limit;
//CLASS BOTTOM	  		Bottom;
//CLASS SORTIE_TEXTE	  	Sortie_texte;
//CLASS CODEND			Codend;
//CLASS BALL			Ball;
//CLASS ORIENTATION_NETTING	Orientation_netting;
//CLASS OPENING_ANGLE		Opening_angle;
//CLASS OPENING_MESH		Opening_mesh;
//CLASS OPENING_ANGLE_STRIPE	Opening_angle_stripe;
//CLASS LIEN			Lien[NBMAXLIAISON];
//CLASS VALUE			Value;
//CLASS RECOUVREMENT_X		Recouvrement_x;
//CLASS VECTOR_TENSION_BAR	Vector_tension_bar;
//CLASS PLAN_CUTTING		Plan_cutting;

