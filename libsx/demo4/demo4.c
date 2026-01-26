/*
 * This demo program shows how to use bitmaps in your button widgets.
 * All that's been done is that I created several bitmaps using that
 * horrible X bitmap editor program, bitmap.  I saved those bitmaps
 * in files called thing1.h, thing2.h, etc.  They get #include'ed
 * here, and then we use them as the imagery for the button.
 *
 * Notice how when the button gets created we use NULL instead of a
 * text string.
 *
 * The program doesn't really do much with the buttons once they're
 * up, it just lets you click on them.  BTW, the bitmaps aren't
 * supposed to be anything in particular, it's just that I'm not much
 * of an artist.
 *
 *  Dominic Giampaolo
 *  dbg@sgi.com
 */
#include <stdio.h>
#include "libsx.h"

#include "thing1.h"
#include "thing2.h"
#include "thing3.h"
#include "thing4.h"




void quit(Widget w, void *junk)
{
  exit(0);
}


void thing1(Widget w, void *junk)
{
  printf("Thing 1\n");
}


void thing2(Widget w, void *junk)
{
  printf("Thing 2\n");
}



void thing3(Widget w, void *junk)
{
  printf("Thing 3\n");
}


void thing4(Widget w, void *junk)
{
  printf("Thing 4\n");
}



main(int argc, char **argv)
{
  Widget w[6];

  OpenDisplay(argc, argv);

  w[0] = MakeButton(NULL, thing1, NULL);
  w[1] = MakeButton(NULL, thing2, NULL);
  w[2] = MakeButton(NULL, thing3, NULL);
  w[3] = MakeButton(NULL, thing4, NULL);
  w[4] = MakeButton("Quit", quit, NULL);

  SetWidgetBitmap(w[0], thing1_bits, thing1_width, thing1_height);
  SetWidgetBitmap(w[1], thing2_bits, thing2_width, thing2_height);
  SetWidgetBitmap(w[2], thing3_bits, thing3_width, thing3_height);
  SetWidgetBitmap(w[3], thing4_bits, thing4_width, thing4_height);
  
  SetWidgetPos(w[1], PLACE_RIGHT, w[0], NO_CARE, NULL);
  SetWidgetPos(w[2], PLACE_RIGHT, w[1], NO_CARE, NULL);
  SetWidgetPos(w[3], PLACE_RIGHT, w[2], NO_CARE, NULL);
  SetWidgetPos(w[4], PLACE_RIGHT, w[3], NO_CARE, NULL);

  MainLoop();
}
