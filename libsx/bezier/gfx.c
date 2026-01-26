/* This file implements functions which operate on a world coordinate space.
 * The code is entirely integer based for speedier operation.
 * 
 * The dimensions of the world are 16,384 x 16,384 (x 16,384).  This is 
 * changeable via #define's.  I use 16,384 as a world size because it 
 * works easily in decimal to simulate floating point numbers and it isn't
 * so large that you have to worry about overflow.
 * 
 * These routines work use the lower level X routines in libsx.
 *
 */
#include <stdio.h>
#include "gfx.h"
#include "libsx.h"

#define ushort unsigned short        /* serious hack... */

#define SCALE        16384
#define SCALE_SHIFT  14

static int sx = SCALE,        /* scale       */
           sy = SCALE;

static int tx = 0,            /* translation */
           ty = 0;

static int cur_color = 1;



/* Set a view, either world or viewport coords.
 *   le == left   edge of view
 *   te == top    edge of view
 *   re == right  edge of view
 *   be == bottom edge of view 
 */
void SetView(int le, int te, int re, int be, Rectangle *r)
{
  if (r == NULL)
    return;

  r->left_edge = le;
  r->top_edge  = te;
  r->width     = re;     /* really right edge  */
  r->height    = be;     /* really bottom edge */
}


/* Maps ww onto vp for all subsequent drawing operations.
 * Since we use integers, we have to multiply by SCALE so as not to lose
 * precision (otherwise most everything here would be zero).
 */
void MapView(Rectangle *ww, Rectangle *vp)
{
  sx = ((vp->width  - vp->left_edge) << SCALE_SHIFT) / 
        (ww->width  - ww->left_edge);
  sy = ((vp->height - vp->top_edge)  << SCALE_SHIFT) / 
        (ww->height - ww->top_edge);

  if (sx == 0)
    sx = 1;      /* just in case, to avoid division by zero */
  if (sy == 0)
    sy = 1;      /* just in case, to avoid division by zero */

  tx = ((vp->left_edge * ww->width) - (ww->left_edge * vp->width));
  tx = (tx) / (ww->width - ww->left_edge);

  ty = ((vp->top_edge * ww->height) - (ww->top_edge * vp->height));
  ty = (ty) / (ww->height - ww->top_edge);
}


void Vp2World(int *x, int *y) /* convert from a mouse click to world coords */
{
  *x = ((*x - tx) << SCALE_SHIFT) / sx;
  *y = ((*y - ty) << SCALE_SHIFT) / sy;
}


static ushort cur_x, cur_y;   /* these are in viewport coords */

void MoveTo(ushort x, ushort y)
{
  cur_x = (((int)x * sx) >> SCALE_SHIFT) + tx;
  cur_y = (((int)y * sy) >> SCALE_SHIFT) + ty;
}


void LineTo(ushort x, ushort y)
{
  int rx2, ry2;

  rx2 = (((int)x * sx) >> SCALE_SHIFT) + tx;
  ry2 = (((int)y * sy) >> SCALE_SHIFT) + ty;

  DrawLine(cur_x, cur_y, rx2, ry2);

  cur_x = rx2;
  cur_y = ry2;
}


void PutPoint(ushort x1, ushort y1)
{
  int rx1, ry1;  /* real x1,y1 */
  
  rx1 = (((int)x1 * sx) >> SCALE_SHIFT) + tx;
  ry1 = (((int)y1 * sy) >> SCALE_SHIFT) + ty;

  DrawPixel(rx1, ry1);

  cur_x = rx1;
  cur_y = ry1;
}


void Line(ushort x1, ushort y1, ushort x2, ushort y2)
{
  int rx1, ry1, rx2, ry2;  /* real x1,y1, etc... */
  
  rx1 = (((int)x1 * sx) >> SCALE_SHIFT) + tx;
  ry1 = (((int)y1 * sy) >> SCALE_SHIFT) + ty;

  rx2 = (((int)x2 * sx) >> SCALE_SHIFT) + tx;
  ry2 = (((int)y2 * sy) >> SCALE_SHIFT) + ty;

  DrawLine(rx1, ry1, rx2, ry2);

  cur_x = rx2;
  cur_y = ry2;
}


void PutBox(ushort x1, ushort y1, ushort x2, ushort y2)
{
  int rx1, ry1, rx2, ry2;  /* real x1,y1, etc... */
  
  rx1 = (((int)x1 * sx) >> SCALE_SHIFT) + tx;
  ry1 = (((int)y1 * sy) >> SCALE_SHIFT) + ty;

  rx2 = (((int)x2 * sx) >> SCALE_SHIFT);
  ry2 = (((int)y2 * sy) >> SCALE_SHIFT);

  DrawBox(rx1, ry1, rx2, ry2);

  cur_x = rx1;
  cur_y = ry1;
}

void FilledBox(ushort x1, ushort y1, ushort x2, ushort y2)
{
  int rx1, ry1, rx2, ry2;  /* real x1,y1, etc... */

  rx1 = (((int)x1 * sx) >> SCALE_SHIFT) + tx;
  ry1 = (((int)y1 * sy) >> SCALE_SHIFT) + ty;

  rx2 = (((int)x2 * sx) >> SCALE_SHIFT);
  ry2 = (((int)y2 * sy) >> SCALE_SHIFT);

  DrawFilledBox(rx1, ry1, rx2, ry2);

  cur_x = rx1;
  cur_y = ry1;
}


