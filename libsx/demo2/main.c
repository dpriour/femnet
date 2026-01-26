/* This demo program shows how to display a Raster Image (i.e. bitmap). 
 * It allocates a small bitmap, fills it in with some data, and then draws
 * it centered in the drawing area. 
 *
 * You should notice that I've modified the main.h file so that we can
 * store information about the bitmap there instead of having all kinds
 * of ugly global variables.
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

/* internal prototype */
void fill_in_bitmap(MyProgram *me);



void main(int argc, char **argv)
{
  MyProgram mydata;

  mydata.bitmap = (char *)malloc(100*100);  /* a 100x100 bitmap */
  if (mydata.bitmap == NULL)
   {
     fprintf(stderr, "Fooey, no memory for bitmap.\n");
     exit(10);
   }
  mydata.bitmap_width   = 100;
  mydata.bitmap_height  = 100;

  init_display(argc, argv, &mydata);  /* setup the display */

  fill_in_bitmap(&mydata);            /* put some stuff in the bitmap */

  MainLoop();                         /* go right into the main loop */
}



/* This function sets up the display.  For any kind of a real program, 
 * you'll probably want to save the values returned by the MakeXXX calls
 * so that you have a way to refer to the display widgets you have 
 * created (like if you have more than one drawing area, and want to
 * draw into both of them).
 */

void init_display(int argc, char **argv, MyProgram *me)
{
  Widget w[5];

  if (OpenDisplay(argc, argv) == FALSE)
    return;

  w[0] = MakeButton("Pattern #1", pattern1, me);
  w[1] = MakeButton("Pattern #2", pattern2, me);
  w[2] = MakeButton("Quit!",      quit,     me);

  w[3] = MakeLabel("Bitmap demo program");

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
   * drawing stuff.  Check libsx.h for more info. 
   */
  GetStandardColors();


 /* If you wanted to get all the colors in the colormap, you'd do the
  * following :
  *
  *    GetAllColors();
  *    SetColorMap(GREY_SCALE_1);
  *
  * You can wait to do it till later if you want.  There's no need 
  * to do it here if you don't need to (because it wacks out the
  * colormap).  Check libsx.h for other colormap types you can 
  * ask for (like RAINBOW_{1,2} or GREY_SCALE_{1,2}).
  */
}



/*
 * Put some junk in the bitmap so it's a little interesting.
 */
void fill_in_bitmap(MyProgram *me)
{
  int i,j;
  char *ptr = me->bitmap;

  for(i=0; i < me->bitmap_height; i++)
    for(j=0; j < me->bitmap_width; j++, ptr++)
     {
       *ptr = rand();
     }
}
