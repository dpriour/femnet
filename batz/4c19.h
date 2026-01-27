#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib_dp/definition_lib.h"
#include "../unix_2004/protos_unix.h"

//#include "filwin.h"

//#define RHO 1025                   /* masse volumique de l eau  */
/*#define yb(zi,zj) (int)((Element[zi].nop[(zj+2)/3])*3+zj-3*((zj+2)/3))*/
//#define yc(zi,zj) (int)((Surface[zi].nop[(zj+2)/3])*3+zj-3*((zj+2)/3))
//#define yc_hexa(zi,zj) (int)((Surf_Hexa[zi].nop[(zj+2)/3])*3+zj-3*((zj+2)/3))

/*
typedef double TCOO1[DIM1];   
typedef double TCOO2[DIM2];
typedef double TMKB[7],TMKB2[9],TMKB3[10],Tab1[4];
typedef int    TLARGE1[DIM1];
typedef int    TLARGE2[DIM2];
typedef double TMKK[65][65],TMKC[10][10];
*/
/* DIM2 est egal a NOMBRE_SURFACES + 1*/

/*
CLASS int    eca,nbiter,nbpas,nbopti,Nbmaxiterations,Periodeimpression,Diviseurhoule,largeur_matrice;
CLASS int    jlra,jlrb,jlrc,miseentension,lectsta,NbTypeNoeud,NbTypeelem,NbTypesurf,NbTypesurfHexa;
CLASS int    rang[5][DIM1],*colo,nb_col;
CLASS int    nbm,nbm1;
CLASS int    nb_fil[DIM2][3];
CLASS double RW,MW,RSUM,MSUM,RTEN,MTEN,lambda,hh1,tt,delt,nu,Seuilconvergence,Dureedynamique,Amolissement;
CLASS double Deplacement,k,omega,Depth1,Numtemps,Pascalcul,Passtockage,Debutstockage,Finstockage;
CLASS double X1,X2,X3,Y1,Y2,Y3,alpha,beta,iterationfin,precedent;
CLASS double nbmaille,nbmaillu1,nbmaillv1,nbmaillu2,nbmaillv2,alpha1,beta1,alpha2,prise,seuilprise,frontx,coef_frottement_sol,raidfond;
CLASS double mailleparpoint[DIM2][7];
CLASS double Relaxation,min_energy,max_energy,min_tension1,max_tension1,min_tension2,max_tension2,min_stress1,max_stress1,min_stress2,max_stress2;
TCOO1  wa,wasurf,waelem,wanoeud,wb,wf,wh,wv,mh,mvh,mgh,wf1,wf2,mvb,mgb,wfcodend;
TCOO2  wt,wtfinal,raideur;
*/



/*Tab1   fe,te,nbma;
TMKB   wd;
TMKB3  wae,ET,EN,ETuv,ENuv,Pe;
TMKC   we;
TMKB2  wd2;
TLARGE1 fixation,listeinter,fixa,whs,wl;
FILE   *f2;*/
