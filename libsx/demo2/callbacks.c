/* This file contains routines that are called when a button is pressed 
 * in your window or when things happen in a drawing area.
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



void pattern1(Widget w, void *data)   /* fill in a different pattern */
{
  int i,j;
  char *ptr;
  MyProgram *me = (MyProgram *)data;

  ptr = me->bitmap;

  for(i=0; i < me->bitmap_height; i++)
    for(j=0; j < me->bitmap_width; j++, ptr++)
     {
       if ((j%3) == 0)
	 *ptr = YELLOW;
       else if ((j%4) == 0)
	 *ptr = BLUE;
       else if ((j%4) == 0)
	 *ptr = GREEN;
     }

  /* since we changed things, we want them to be redisplayed, so.... */
  redisplay(NULL, me->win_width, me->win_height, me);
}


void pattern2(Widget w, void *data)
{
  int i,j;
  char *ptr;
  MyProgram *me = (MyProgram *)data;

  ptr = me->bitmap;

  for(i=0; i < me->bitmap_height; i++)
    for(j=0; j < me->bitmap_width; j++, ptr++)
     {
       if ((j%2) == 0)
	 *ptr = RED;
       if ((j%3) == 0)
	 *ptr = GREEN;
       if ((j%4) == 0)
	 *ptr = BLUE;
     }

  /* since we changed things, we want them to be redisplayed, so.... */
  redisplay(NULL, me->win_width, me->win_height, me);
}



/*
 * Here is where all redrawing will take place for your program. 
 * When the window needs to be redrawn, this function will be called.
 * When your program starts up for the first time, this function will 
 * be called and you should draw anything you need to draw in here.
 */
void redisplay(Widget w, int new_width, int new_height, void *data)
{
  MyProgram *me = data;
  int x, y;

  me->win_width  = new_width;
  me->win_height = new_height;

  ClearDrawArea();              /* start with a clean slate */

  SetColor(RED);
  DrawText("My Cool Program", (me->win_width/2)-50, 30); 

  /* x and y are the offsets into the drawing area of where we want the
   * bitmap to be drawn.  If you had a bitmap the same size as the 
   * drawing area, they'd be zero.  We want it to be centered, so we
   * calculate them appropriately.
   */
  x = (me->win_width  - me->bitmap_width) / 2;
  y = (me->win_height - me->bitmap_height) / 2;

  DrawImage(me->bitmap, x,y, me->bitmap_width, me->bitmap_height);
}




