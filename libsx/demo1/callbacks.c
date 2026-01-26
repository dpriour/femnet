/* This file contains callback routines that implement the logic of your
 * program.  The function init_display() in main.c built the display
 * and setup the connection between these functions and the user interface
 * elements.
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



/*  -- CALLBACK ROUTINES  --
 *
 * These functions are called when various things happen in your windows.
 * They should handle what happened and give feedback to the user.  Most
 * likely they will set options in your program (which is what the 
 * MyProgram data structure is for), and cause different things to happen, 
 * like loading and saving files, etc.
 */


void quit(Widget w, void *data)
{
  /* Do any cleanup that is necessary for your program here */

  exit(0);
}



void load(Widget w, void *data)
{
  char *string;

  string = GetString("\nEnter a filename to load\n", "untitled");

  if (string)
    printf("You entered the name: %s\n", string);
  else
    printf("You clicked the cancel button.\n");

}


void click_me(Widget w, void *data)
{
  MyProgram *me = (MyProgram *)data;
  int ans;

  ans = GetYesNo("\nAre you a weenie?\n\n");

  if (ans)
   {
     me->var1 = TRUE;
     printf("The user is a weenie.\n");
   }
  else
   {
     me->var2 = FALSE;
     printf("You are not a weenie.\n");
   }
}



/*
 * The following is the redisplay code for the drawing area widget.
 *
 * Each time it needs to be redisplayed (either because it the window
 * was resized or because it was obscured), this function gets called.
 */
void redisplay(Widget w, int width, int height, void *data)
{
  MyProgram *me=data;

  ClearDrawArea();              /* start with a clean slate */

  draw_stuff(width, height);
}


void draw_stuff(int width, int height)
{
  draw_lines(width, height);
  draw_random_lines();
  draw_points();
  draw_text(width, height);
}



void draw_lines(int width, int height)
{
  int i;
  
  SetColor(BLACK);             /* draw some pretty patterns */
  for(i=0; i < width; i+=5)
    DrawLine(0,i, i,height);

  SetColor(GREEN);
  for(i=0; i < width; i+=5)
    DrawLine(width,i, width-i,height);

}


void draw_random_lines(void)
{
  int i;
  XPoint xpts[50];

  srand(time(NULL) | 0x01);              /* seed the random number generator */

  for(i=0; i < 50; i++) 
    {
      xpts[i].x = (rand() % 75) + 75;    /* pick random vertices */
      xpts[i].y = (rand() % 75) + 75;
    }

  SetColor(RED);
  DrawPolyline(xpts, 50);                /* now draw all 50 of them in red */
}


void draw_points(void)
{
  int i, x,y;

  srand(time(NULL) | 0x01);              /* seed the random number generator */

  
  SetColor(BLUE);
  for(i=0; i < 100; i++)
    {
      x = (rand() % 75) + 150;           /* pick a random point */
      y = (rand() % 75) + 75;

      DrawPixel(x, y);                   /* now draw it on the screen */
    }
}


void draw_text(int width, int height)
{
  SetColor(BLACK);
  DrawText("My Cool Program", (width/2)-50, height/2); 
}
