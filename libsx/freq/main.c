/*
 * This is an example program for use with the libsx library.  This
 * example shows how to implement a simple file requestor.  The main
 * window has two button widgets: a load button and a quit button.  The load
 * button will open a file requestor window where the user can select a
 * file from a scrollable list.  The program will block until the user
 * has selected a file or cancelled the load at which point the appropriate
 * action can be taken.
 *
 * -Allen Martin (amartin@wpi.wpi.edu)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsx.h"		/* gets us in the door with libsx          */
#include "freq.h"		/* file requestor header */

int init_display(int argc, char **argv, void *data);

/* callback protos */
void quit(Widget w, void *data);
void load(Widget w, void *data);

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

  w[0]  = MakeButton("Load",     load,   data);
  w[1]  = MakeButton("Quit!",    quit,   data);

  SetWidgetPos(w[1], PLACE_RIGHT, w[0], NO_CARE, NULL);

  ShowDisplay();
  
  GetStandardColors();

  return argc;
}

/*
 * load() - Callback function for the load button.  This just calls
 *          GetFile() to get a file name
 */
void load(Widget w, void *data)
{
  char *fname;
  
  fname = GetFile(NULL);
  if(fname)
    printf("The file \"%s\" was selected\n", fname);
  else
    printf("Load Cancelled\n");
}


/*
 * quit() - Callback funtion for the quit button.
 */
void quit(Widget w, void *data)
{
  exit(0);
}





