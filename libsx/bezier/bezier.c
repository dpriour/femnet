/* this file contains a routine to implement drawing a bezier
 * curve based on 4 control points 
 *
 *  dominic giampaolo
 *  dbg@sgi.com
 */
#include "gfx.h"
#include "libsx.h"
#include "bezier.h"

void bezier4(Point *p, int num_steps)
{
  double t, t_sq, t_cb, incr;
  double r1, r2, r3, r4;
  ushort curve_x, curve_y;

  incr = 1.0 / (double)num_steps;

  MoveTo(p[0].x, p[0].y);

  for(t=incr; t <= 1.01; t += incr)
   {
     t_sq = t * t;
     t_cb = t * t_sq;

     r1 = (1 - 3*t + 3*t_sq -   t_cb)*(double)p[0].x;
     r2 = (    3*t - 6*t_sq + 3*t_cb)*(double)p[1].x;
     r3 = (          3*t_sq - 3*t_cb)*(double)p[2].x;
     r4 = (                     t_cb)*(double)p[3].x;
     curve_x = (ushort)(r1 + r2 + r3 + r4);

     r1 = (1 - 3*t + 3*t_sq -   t_cb)*(double)p[0].y;
     r2 = (    3*t - 6*t_sq + 3*t_cb)*(double)p[1].y;
     r3 = (          3*t_sq - 3*t_cb)*(double)p[2].y;
     r4 = (                     t_cb)*(double)p[3].y;
     curve_y = (ushort)(r1 + r2 + r3 + r4);

     LineTo(curve_x, curve_y);
   }
}
