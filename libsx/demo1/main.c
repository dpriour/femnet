/* This demo program just opens up a simple window and draws some things
 * into it.  It makes no pretensions about being sophisticated, but just
 * gets the job done.  You can use this as a framework for your own programs,
 * just follow the comments, and you should be able to extend it as
 * needed. 
 *
 * NOTE: 
 *   If you could care less about all the other stuff, and just want to write
 *   graphics code, simply edit the function redisplay() in callbacks.c and 
 *   modify it to your desires.  That is where all redrawing takes place.
 *
 *   Dominic Giampaolo
 *   dbg@sgi.com
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "libsx.h"             /* should come first, defines libsx stuff  */
#include "main.h"              /* where program specific stuff is defined */
#include "callbacks.h"         /* prototypes for callback functions       */


/* define's */
#define X_SIZE 300             /* default draw area size, change as desired */
#define Y_SIZE 300



void main(int argc, char **argv)
{
  MyProgram mydata;

  mydata.var1  = 1;                   /* do your initializations here */
  mydata.var2  = 2;
  mydata.flags = 0;

  init_display(argc, argv, &mydata);  /* setup the display */

  MainLoop();                         /* go right into the main loop */
}



/* This function sets up the display.  For any kind of a real program, 
 * you'll probably want to save the values returned by the MakeXXX calls
 * so that you have a way to refer to the display objects you have 
 * created (like if you have more than one drawing area, and want to
 * draw into both of them).
 */

void init_display(int argc, char **argv, MyProgram *me)
{
  Widget w[5];

  if (OpenDisplay(argc, argv) == FALSE)
    return;

  w[0] = MakeButton("Load",     load,     me);
  w[1] = MakeButton("Click Me", click_me, me);
  w[2] = MakeButton("Quit!",    quit,     me);

  w[3] = MakeLabel("This is a label");

  w[4] = MakeDrawArea(X_SIZE, Y_SIZE, redisplay, me);

  
  SetWidgetPos(w[1], PLACE_RIGHT, w[0], NO_CARE, NULL);
  SetWidgetPos(w[2], PLACE_RIGHT, w[1], NO_CARE, NULL);
  SetWidgetPos(w[3], PLACE_RIGHT, w[2], NO_CARE, NULL);
  SetWidgetPos(w[4], PLACE_UNDER, w[0], NO_CARE, NULL);
  

  /* This call actually causes the whole thing to be displayed on the
   * screen.  You have to call this function before doing any drawing
   * into the window.
   */
  ShowDisplay();

  
  /* Get standard (red, blue, green, yellow, black, white) colors for
   * drawing stuff.
   */
  GetStandardColors();
}




