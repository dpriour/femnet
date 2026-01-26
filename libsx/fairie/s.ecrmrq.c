h02283
s 00103/00000/00000
d D 1.1 95/10/17 12:16:22 molagnon 1 0
c date and time created 95/10/17 12:16:22 by molagnon
e
u
U
f e 0
t
T
I 1
#include "../include/faixvg.h"
#define LMRQX 32
#define LMRQY 7
#define MRQCX 4
#define MRQCY 4

static unsigned long xmrq1t [] = 
{ 0x00000000, 0x7C000000, 0x7C000000, 0x7C000000, 0x7C000000, 0x7C000000, 0x00000000 };
static unsigned long xmrq2t [] = 
{ 0x00000000, 0x38000000, 0x7C000000, 0x7C000000, 0x7C000000, 0x38000000, 0x00000000 };
static unsigned long xmrq3t [] = 
{ 0x38000000, 0x6C000000, 0xC6000000, 0xC6000000, 0xC6000000, 0x6C000000, 0x38000000 };
static unsigned long xmrq4t [] = 
{ 0x00000000, 0x10000000, 0x10000000, 0x7C000000, 0x10000000, 0x10000000, 0x00000000 };
static unsigned long xmrq5t [] = 
{ 0x10000000, 0x38000000, 0x38000000, 0x7C000000, 0x7C000000, 0xFE000000, 0x00000000 };
static unsigned long xmrq6t [] = 
{ 0xFE000000, 0x7C000000, 0x7C000000, 0x38000000, 0x38000000, 0x10000000, 0x00000000 };
static unsigned long xmrq7t [] = 
{ 0x10000000, 0x54000000, 0x38000000, 0xFE000000, 0x38000000, 0x54000000, 0x10000000 };
static unsigned long xmrq8t [] = 
{ 0x00000000, 0x7C000000, 0x44000000, 0x44000000, 0x44000000, 0x7C000000, 0x00000000 };
static unsigned long xmrq9t [] = 
{ 0x00000000, 0x6C000000, 0x7C000000, 0x38000000, 0x7C000000, 0x6C000000, 0x00000000 };

zm_static (Smrq1, LMRQX, LMRQY, 1, xmrq1t);
zm_static (Smrq2, LMRQX, LMRQY, 1, xmrq2t);
zm_static (Smrq3, LMRQX, LMRQY, 1, xmrq3t);
zm_static (Smrq4, LMRQX, LMRQY, 1, xmrq4t);
zm_static (Smrq5, LMRQX, LMRQY, 1, xmrq5t);
zm_static (Smrq6, LMRQX, LMRQY, 1, xmrq6t);
zm_static (Smrq7, LMRQX, LMRQY, 1, xmrq7t);
zm_static (Smrq8, LMRQX, LMRQY, 1, xmrq8t);
zm_static (Smrq9, LMRQX, LMRQY, 1, xmrq9t);

void
ecrmrq_ (float *Pxpnt, float *Pypnt, int *Pkmrq)
                     
           

/*
 *      ecrmrq = ecriture d un marqueur 
 *      version %I% du %G%                                           */
     
{
    int jxpnt, jypnt;
    int lxpnt, lypnt;
    Zonmem   *PSmrq;
           
/* .... calcul des composantes du point ...................*/
/* le marqueur occupe le quart superieur gauche du pixrect */
/* il est centre sur le pixel 4,4 (dans le cadre 32, 7)    */

      jxpnt = (int) (xscl * (*Pxpnt)) + jxorg - MRQCX;
      jypnt = jyorg - (int) (yscl * (*Pypnt)) - MRQCY;

/* .... trace .............................................*/
  
      switch (*Pkmrq) {

      case (0):
        return;

      default:
      case (1):
        PSmrq = &Smrq1;
        break;

      case (2):
        PSmrq = &Smrq2;
        break;

      case (3):
        PSmrq = &Smrq3;
        break;

      case (4):
        PSmrq = &Smrq4;
        break;

      case (5):
        PSmrq = &Smrq5;
        break;

      case (6):
        PSmrq = &Smrq6;
        break;

      case (7):
        PSmrq = &Smrq7;
        break;

      case (8):
        PSmrq = &Smrq8;
        break;

      case (9):
        PSmrq = &Smrq9;
        break;

      }
      zm_col (PSmrq, 0, 0, LMRQX, LMRQY, kclr0, PSimg, jxpnt, jypnt);
}
E 1
