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
 */

#include <stdio.h>
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
 *
 * Remember, the last argument to your callback is always a void pointer
 * to whatever data you specified when you created the widget.  You
 * must cast the pointer to be whatever type it really is.
 */


void quit(Widget w, void *data)
{
  /* Do any cleanup that is necessary for your program here */

  exit(0);
}



void button1(Widget w, void *data)
{
  printf("You clicked button #1\n");
}


void button2(Widget w, void *data)
{
  printf("You clicked button #2\n");
}




/*
 * The following functions are callbacks for the drawing area widgets.
 *
 * The only required callback is redisplay().  The others are optional
 * but have been setup to be used by init_display() in main.c.
 */


/* Here is where all redrawing will take place for your program. 
 * When the window needs to be redrawn, this function will be called.
 * When your program starts up for the first time, this function will 
 * be called and you should draw anything you need to draw in here.
 */
void redisplay(Widget w, int new_width, int new_height, void *data)
{
  MyProgram *me=data;

  ClearDrawArea();              /* start with a clean slate */
}



void button_down(Widget w, int which_button, int x, int y, void *data)
{
  printf("You clicked button %d at (%d,%d)\n", which_button, x,y);
}


void button_up(Widget w, int which_button, int x, int y, void *data)
{
  printf("You released button %d at (%d,%d)\n", which_button, x,y);
}




/*
 * The following function is called when keypresses happen in the drawing
 * area widget.
 *
 *  It is useful to know that the string returned to your program is
 * not necessarily a single ASCII character. You will get the usual
 * ASCII characters, including control characters (such as ^C or ^H).
 * But, the workstation's function keys will also be returned in a
 * string such as "F11" or "F23".  You will also get other longer
 * strings such as "Control_L", "Alt_R", or "Shift_L".  It is
 * important to understand that even if you just press the shift key to
 * get a capital letter, you will first receive the string "Shift_L"
 * or "Shift_R", then you will receive a capital letter (say, "H").
 * You should probably ignore the "Shift_L" or "Shift_R" messages (but
 * who knows, you may find some use for them).
 *
 * The argument, up_or_down, tells you whether the given key was pressed 
 * or released.  If the key was pressed down, up_or_down has a zero (0),
 * if the key was released, up_or_down contains a 1.
 *
 * NOTE WELL:
 *   The string that is returned to you can _NOT_ (I'll repeat that,
 *   can _NOT_) be modified by your program.  Got it?  Do _NOT_ modify
 *   the string.  If you want to munge with it, make a copy using
 *   strdup() or strcpy() into your own buffer space.
 */

void keypress(Widget w, char *input, int up_or_down, void *data)
{
  char *str;

  if (input == NULL)
    return;

  if (up_or_down == 0)
    str = "pressed";
  else
    str = "released";

  printf("You %s : <<%s>>\n", str, input);
}




/* Called when a DrawingArea gets mouse motion events.  The arguments
 * X and Y are the current position of the mouse in the window.
 *
 * NOTE: This routine should be _fast_ because *every* single time
 *       the mouse moves in the drawing area, this function is called. 
 *       So even if you are just moving the mouse across the drawing area,
 *       this routine is called. As it stands, it doesn't do anything.
 */
void motion(Widget w, int x, int y, void *data)
{
  static int oldx = 0, oldy = 0;

  oldx = x;
  oldy = y;

	DrawBox(x,y,10,10);

  /* Be careful what you do with the mouse movement events, they 
   * can make performance really bad if you don't process them fast
   */  
}


