/* This file contains callback routines that drive the display.
 *
 * If you add a function to this file, you should also add a function 
 * prototype for it to the callbacks.h file (unless it is an internal 
 * function, then you should just add it down below where it says 
 * "internal prototypes").
 *
 *              --  This code is under the GNU copyleft  --
 *
 *   Dominic Giampaolo
 *   dbg@sgi.com
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "libsx.h"
#include "main.h"
#include "callbacks.h"




void quit(Widget w, void *data)
{
  /* Do any cleanup that is necessary for your program here */

  exit(0);
}



void next_cmap(Widget w, void *data)
{
  MyProgram *me = (MyProgram *)data;

  me->cur_colormap++;
  if (me->cur_colormap > 3)
    me->cur_colormap = 0;

  SetColorMap(me->cur_colormap);
}


void prev_cmap(Widget w, void *data)
{
  MyProgram *me = (MyProgram *)data;
  
  me->cur_colormap--;
  if (me->cur_colormap < 0)
    me->cur_colormap = 3;

  SetColorMap(me->cur_colormap);
}



/* Here is where all redrawing will take place for your program. 
 * When the window needs to be redrawn, this function will be called.
 * When your program starts up for the first time, this function will 
 * be called and you should draw anything you need to draw in here.
 */

void redisplay(Widget w, int width, int height, void *data)
{
  MyProgram *me=data;
  int i;
  
  ClearDrawArea();                   /* start with a clean slate */

  for(i=0; i < width; i++)           /* draw some pretty patterns */
   {
     SetColor(i);          /* this will step through the gradient of colors */
     DrawLine(0,i, i,height);
   }

  for(i=0; i < width; i++)
   {
     SetColor(i);   
    DrawLine(width,i, width-i,height);
   }

  SetColor(RED);
  DrawText("My Cool Program", (width/2)-50, height/2); 
}




