#include <stdio.h>
#include "libsx.h"


void quit(Widget w, void *data)
{
  exit(0);
}


void draw_stuff(Widget w, int width, int height, void *data)
{
  ClearDrawArea();
  DrawLine(50,50, width-50, height-50);   /* just draw a diagonal line */
}
  


int main(int argc, char **argv)
{
  Widget w[2];


  argc = OpenDisplay(argc, argv);
  if (argc == 0)                   /* woops, couldn't get started */
    exit(5);
  
  /* could process our own command line options here. */
  
  w[0] = MakeButton("Quit", quit, NULL);
  w[1] = MakeDrawArea(800,500, draw_stuff, NULL);

  SetWidgetPos(w[1], PLACE_UNDER, w[0], NO_CARE, NULL);

  ShowDisplay();
  GetStandardColors();

  MainLoop();   /* off we go! */
}
