/* This demo program shows you how to use the colormaps.  It's fairly
 * simple.
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

  mydata.cur_colormap = RAINBOW_1;

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
  int i;
  Widget w[5];

  if (OpenDisplay(argc, argv) == FALSE)
    return;

  w[0] = MakeButton("Next ColorMap", next_cmap, me);
  w[1] = MakeButton("Prev ColorMap", prev_cmap, me);
  w[2] = MakeButton("Quit!",         quit,    me);

  w[3] = MakeLabel("The ColorMap Demo");

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

  
  /* We are going to take over the colormap and install our own.
   * This will cause the colors in other windows to get wacked out, but
   * hey, that's the price you pay for nice smooth gradients. :-)
   * 
   * Also note that after we've called GetAllColors(), we can call
   * SetColorMap() as often as we like.
   */
  GetAllColors();
  SetColorMap(me->cur_colormap);


  /* Now we make the widget outlines and text visible even though we've 
   * taken over the colormap.  Otherwise they kind of become invisible.
   * This isn't the most foolproof way in the world to do this, but 
   * it works for most colormaps.
   */
  for(i=0; i < 4; i++)
   {
     SetFgColor(w[i], 255);
     SetBorderColor(w[i], 255);
   }
}



