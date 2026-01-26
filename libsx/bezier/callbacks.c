/* This file contains routines that manage the user interface.
 *
 *       This code (for what it's worth) is under the GNU copyleft.
 *
 *   Dominic Giampaolo
 *   dbg@sgi.com
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "libsx.h"    
#include "gfx.h"
#include "main.h"
#include "callbacks.h"
#include "bezier.h"

/*
 * Would you believe that posix doesn't actually require that M_PI_2 and
 * M_PI_4 be defined?  What a load of crap....
 */
#ifndef M_PI_2
#define M_PI_2          1.57079632679489661923
#endif
#ifndef M_PI_4
#define M_PI_4          0.78539816339744830962
#endif

/* internal prototypes */
void timeout(caddr_t data, XtIntervalId *id);
int  check_point(MyProgram *me, ushort x, ushort y);



/* Each of the following functions is tied to a given interface button.
 * They are called whenever the user clicks on something on the display, 
 * and happen independant of anything else that may be taking place on
 * the display.
 */


/* Just quit out of everything.
 */
void quit(Widget w, void *data)
{
  exit(0);
}


/* Cause the curve to be redrawn.  Not much to do here, this is basically
 * just a wrapper function for do_redisplay().
 */
void redraw_curve(Widget w, void *data)
{
  MyProgram *me = (MyProgram *)data;
  
  redisplay(NULL, me->width, me->height, me);
}


/* This resets the curve back to the original.
 */
void reset_curve(Widget w, void *data)
{
  MyProgram *me = (MyProgram *)data;
  
  me->pts[0].x = 0;      me->pts[0].y = 5000;
  me->pts[1].x = 2500;   me->pts[1].y = 7500;
  me->pts[2].x = 5000;   me->pts[2].y = 2500;
  me->pts[3].x = 7500;   me->pts[3].y = 5000;

  redisplay(NULL, me->width, me->height, me);
}


/* This starts the animation going.  It sets a flag and then calls the
 * timeout() routine.  timeout() does its business and then adds itself
 * as a time-out that will happen every so many milliseconds.
 */
void bez_anim(Widget w, void *data)
{
  MyProgram *me = (MyProgram *)data;
  
  if (me->remove_timeout == FALSE)  /* already doing it */
    return;
  me->remove_timeout = FALSE;

  ClearDrawArea();
  timeout((caddr_t)me, NULL);   /* start the ball rolling */
}


/* This unsets a flag that was set in bez_anim().  This makes the 
 * timeout() routine remove itself, and so the animation stops.
 */
void stop_anim(Widget w, void *data)
{
  MyProgram *me = (MyProgram *)data;
  
  if (me->remove_timeout == TRUE)  /* already stopped */
    return;  

  me->remove_timeout = TRUE;   /* makes the timeout function remove itself */
}


void time_out_adjust(Widget w, float new_val, void *data)
{
  char buff[80];
  MyProgram *me=data;

  me->timeout_val = new_val;

  sprintf(buff, "Timeout Val: %-6f    ", me->timeout_val);
  SetLabel(me->label_widget, buff);
}





/* These callbacks down here are the standard ones for the drawing area, 
 * and are where you'd implement your interface "policy".  By that, I mean
 * these functions and what they do determines how your program behaves 
 * and controls what the user will think of your program (i.e. this is
 * great or this is garbage).  You really should think out what you do
 * in these functions.  How do you want mouse clicks to work, what should
 * dragging operations behave like, etc.  These are all important issues
 * that get implemented in the next few functions and determine the look
 * and feel (oh oh, watch out for Apple's lawyers :^) of your application.
 */



/*
 * Here is where we redraw things when necessary.  It also re-maps the
 * view ports to reflect the new changes in the window size.
 */
void redisplay(Widget w, int new_width, int new_height, void *data)
{
  MyProgram *me = data;
  
  ClearDrawArea();                        /* start with a clean slate */

  me->width  = new_width;                 /* save new window size */
  me->height = new_height;


  /*
   * Setup the proper mapping from world coordinates (10000 x 10000) to
   * window coordinates (width x height)
   */
  SetView(0,0, 10000, 10000,  &me->world_view); 
  SetView(0,0, me->width, me->height, &me->view_port);
  MapView(&me->world_view, &me->view_port);

  SetColor(WHITE);

  /* draw the control points */
  FilledBox(me->pts[0].x, me->pts[0].y, 100, 100); 
  FilledBox(me->pts[1].x, me->pts[1].y, 100, 100); 
  FilledBox(me->pts[2].x, me->pts[2].y, 100, 100); 
  FilledBox(me->pts[3].x, me->pts[3].y, 100, 100); 

  bezier4(me->pts, 20);   /* draw the actual bezier curve */
}



#define NO_MB 0
#define MB_1  1
#define MB_2  2
#define MB_3  4
#define MB_4  8
#define MB_5  16
int mouse_button = 0;


void button_down(Widget w, int which_button, int x, int y, void *data)
{
  MyProgram *me=data;
  Vp2World(&x, &y);   /* convert from device to world coords */

  switch (which_button)
   {   
     case 1: mouse_button |= MB_1;    
             if (check_point(me, x, y))
	       me->mode = MODE_MOVING;
             break;

     case 2: mouse_button |= MB_2;
             break;
     
     case 3: mouse_button |= MB_3;
             break;
   }
}


void button_up(Widget w, int which_button, int x, int y, void *data)
{
  MyProgram *me=data;

  Vp2World(&x, &y);   /* convert from device to world coords */

  switch (which_button) 
   { 
     case 1: mouse_button &= ~MB_1;
             me->mode = MODE_NOTHING;

             redraw_curve(NULL, me);  /* so any screen turds are cleaned up */

	     break;
			    
     case 2: mouse_button &= ~MB_2;
             break;
			    
     case 3: mouse_button &= ~MB_3;
             break;
   }
}






/* Called when DrawingArea canvas have pointer motion events */
void process_motion(Widget w, int x, int y, void *data)
{
  static int oldx = 0, oldy = 0;
  Point old, cur;
  MyProgram *me=data;

  old.x = oldx;
  old.y = oldy;

  cur.x = x;
  cur.y = y;


  if ((me->mode & MODE_MOVING) == 0)
    return;

  if (me->cur_point == -1)
    return;

  Vp2World(&x, &y);   /* convert from device to world coords */


  SetColor(BLACK);              /* erase the old stuff */
  FilledBox(me->pts[me->cur_point].x,  me->pts[me->cur_point].y, 100, 100); 
  bezier4(me->pts, 20);


  if (x < 0)         /* keep things in bounds */
    x = 0;
  if (x > 10000)
    x = 10000;
  if (y < 0)
    y = 0;
  if (y > 10000)
    y = 10000;

  me->pts[me->cur_point].x = x;     me->pts[me->cur_point].y = y;

  SetColor(WHITE);                  /* redraw the new stuff */
  bezier4(me->pts, 20);

  FilledBox(me->pts[me->cur_point].x,  me->pts[me->cur_point].y, 100,100); 
}


/* Checks if a mouse click is near any control points.  Notice the slop
 * factor.  If we expected the user to click _exactly_ on the control
 * point, they'd get frustrated pretty quickly.  You generally need
 * some kind of slop factor like this.  It should also be parameterized
 * instead of hardcoded because on a different resolution screen, you'd 
 * want smaller or larger "slop" values.
 */
int check_point(MyProgram *me, ushort x, ushort y)
{
  int i;

  for(i=0; i < 4; i++)
   {
     if (x > me->pts[i].x-150 && x < me->pts[i].x+150)
	if (y > me->pts[i].y-150 && y < me->pts[i].y+150)
	 {
	   me->cur_point = i;
	   return TRUE;
	 }
   }

  return FALSE;
}


/* Here is where the animation takes place.  What happens is that we 
 * first check to see if we should stop animating and remove ourselves.
 * If so, we just call redraw_curve() and return.  Otherwise we check if 
 * we should erase the last frame, and if so, just erase the stuff by 
 * redrawing it in white and then adding ourselves to the time-out list 
 * once again.  Else, we are supposed to move things and redraw in black.
 * The updating of the control points should probably be in a separate 
 * function, but I'm lazy for now.  The ugliness that updates the control
 * points, moves them along a parametric curve that I stole from the Hill
 * graphics book.  It's a pretty neat curve (i.e. really twisty and curvy).
 * Anyway, after all that rigamarole, we just add ourselves to the timeout
 * chain again, and then return.
 * 
 * The thing that may not be immediately obvious is how this function 
 * gets called.  Well, lemme tellya.  The function AddTimeOut() sets
 * up a function (this one) to be called when a given amount of time
 * expires.  The code that actually calls this routine is part of the
 * X toolkit library, and isn't really visible.  The only other thing to
 * notice is that each time when we are done, we have to add ourselves 
 * again to the time-out list so that we will get called again in the
 * next few milliseconds (otherwise nothing would get called and the
 * animation would stop, which incidentally is how stop the animation).
 */

void timeout(caddr_t data, XtIntervalId *id)
{
  static double rad  = 0.0;
  MyProgram *me = (MyProgram *)data;

  if (me->remove_timeout == TRUE)
   {
     redraw_curve(NULL, me);
     return;
   }

  SetColor(BLACK);                   /* erase */
  bezier4(me->pts, 20);
  
 {                                   /* redraw */
   int size = 5000;
   double x,y, n = 6.0;
   
   rad += 0.01;
   
   me->pts[0].x = (size * (cos(n * rad)) * cos(rad)) + 5000;
   me->pts[0].y = (size * (cos((n-1) * rad)) * sin(rad)) + 5000;
   
   
   me->pts[1].x = (size * (cos(n * (rad + M_PI_2))) * cos(rad)) + 5000;
   me->pts[1].y = (size * (cos((n-1) * (rad + M_PI_2))) * sin(rad)) + 5000;
   
   me->pts[2].x = (size * (cos(n * (rad + M_PI_4))) * cos(rad)) + 5000;
   me->pts[2].y = (size * (cos((n-1) * (rad + M_PI_4))) * sin(rad)) + 5000;
   
   size /= 2;
   me->pts[3].x = (size * (cos(rad) + sin(8*rad))) + 5000;
   me->pts[3].y = ((size/2) * (2*sin(rad) + sin(7*rad))) + 5000;
   
   SetColor(WHITE);
   bezier4(me->pts, 20);
   
   if (me->remove_timeout == FALSE)
     AddTimeOut((me->timeout_val*1000), (GeneralCB)timeout, data);
 }

}


