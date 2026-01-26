/*
 * -Allen Martin (amartin@wpi.wpi.edu)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsx.h"		/* gets us in the door with libsx */
#include "creq.h"		/* Color Requestor header */

int init_display(int argc, char **argv, void *data);

/* callback protos */
void cedit(Widget w, void *data);
void quit(Widget w, void *data);


void main(int argc, char **argv)
{
  argc = init_display(argc, argv, NULL);  /* setup the display */
  if (argc == 0)
    exit(0);

  MainLoop();                                /* go right into the main loop */
}


/* This function sets up the display.  For any kind of a real program, 
 * you'll probably want to save the values returned by the MakeXXX calls
 * so that you have a way to refer to the display objects you have 
 * created (like if you have more than one drawing area, and want to
 * draw into both of them).
 */
int init_display(int argc, char **argv, void *data)
{
  Widget w[2];

  argc = OpenDisplay(argc, argv);
  if (argc == FALSE)
    return argc;

  w[0]  = MakeButton("Edit",     cedit,  data);
  w[1]  = MakeButton("Quit!",    quit,   data);

  SetWidgetPos(w[1], PLACE_RIGHT, w[0], NO_CARE, NULL);

  ShowDisplay();
  
  GetStandardColors();

  return argc;
}

/*
 * cedit() - This is the Callback function for the edit button.  This
 *           simply calls GetColor() to get an RGB value
 */
void cedit(Widget w, void *data)
{
  unsigned char r=40,g=80,b=120;
  
  if(GetColor(&r,&g,&b))
    printf("Cancelled\n");
  else
    printf("Red=%d, Green=%d, Blue=%d\n", r, g, b);
}

/*
 * quit() - Callback function for the quit button
 */
void quit(Widget w, void *data)
{
  exit(0);
}






