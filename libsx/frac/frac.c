/* this program draw 2-d fractal mountains.  It generates them using
 * a random midpoint displacement algorithim. 
 * 
 * it generates several screenfulls of mountains and scrolls them to try
 * and be interesting.
 *
 * This code is pretty mungy, but works
 * d.b.g. late summer 1990
 * dbg@sgi.com
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libsx.h"


/*
 * Unfortunately some machines like Sun's don't have RAND_MAX defined
 * where it should be (can you say "Please be ANSI compliant?"), so
 * we will #define it if it isn't.
 */
#ifndef RAND_MAX
#define RAND_MAX  0x7fff
#endif


/* forward declaration */
int   fracline(int a, int b);
void  quit(Widget w, void *junk);
void  anim(Widget w, void *data);
void  draw_stuff(Widget w, int width, int height, void *junk);
void  set_scroll_val(Widget w, float val, void *junk);
void  set_timeout_val(Widget w, float val, void *junk);


int max_random = RAND_MAX;


#define MAX 2048

int line[MAX];              /* this is our global fractal "line" */
double rug = 0.6;           /* ruggedness factor of the "terrain" */


int width,height,where;
int scroll_amount=8;
int timeout=250;
int remove_timeout=FALSE;


main(int argc, char **argv)
{
  int a, b;
  Widget w[10];

  if (OpenDisplay(argc, argv) == 0)
    exit(0);
  
  w[0] = MakeButton("Quit", quit, NULL);
  w[1] = MakeDrawArea(500, 500, draw_stuff, NULL);
  w[2] = MakeButton("  Animate  ", anim, NULL);
  w[3] = MakeHorizScrollbar(100, set_scroll_val, NULL);
  w[4] = MakeHorizScrollbar(150,set_timeout_val,NULL); 
  w[5] = MakeLabel("Scroll Amount:");
  w[6] = MakeLabel("Timeout Val:");

  SetWidgetPos(w[1], PLACE_UNDER, w[0], NO_CARE, NULL);
  SetWidgetPos(w[2], PLACE_RIGHT, w[0], NO_CARE, NULL);
  SetWidgetPos(w[5], PLACE_RIGHT, w[2], NO_CARE, NULL);
  SetWidgetPos(w[3], PLACE_RIGHT, w[5], NO_CARE, NULL);
  SetWidgetPos(w[6], PLACE_RIGHT, w[3], NO_CARE, NULL);
  SetWidgetPos(w[4], PLACE_RIGHT, w[6], NO_CARE, NULL);

  SetScrollbar(w[3], (float)scroll_amount, 32.0, 1.0);
  SetScrollbar(w[4], (float)timeout, 500.0, 10.0);


  ShowDisplay();
  GetStandardColors();


  
  /* initialize */
  srand((getpid()*time(NULL)) | 0x01); 

  a = 0; b = MAX - 1;
  line[a] = line[b] = (rand() % 200) + 100;
  
  fracline(a, b);    /* actually generate the fractal line. */
  
  MainLoop();
} /* end of main */




void  quit(Widget w, void *junk)
{
  exit(0);
}




void  set_scroll_val(Widget w, float val, void *junk)
{
  scroll_amount = (int)val + 1;
}


void  set_timeout_val(Widget w, float val, void *junk)
{
  timeout = (int)val;
}


void  draw_stuff(Widget w, int nwidth, int nheight, void *junk)
{
  int i,x;

  width  = nwidth;
  height = nheight;

  ClearDrawArea();

  SetColor(BLACK);
  for(i=1; i < width; i++)
    DrawLine(i-1, line[i-1], i, line[i]);

  where = i;
}



/* void do_anim(void *data, XtIntervalId *foo)  */
void do_anim(void *data) 
{
  int i;
  
  ScrollDrawArea(scroll_amount, 0, 0,0, width, height);
  
  SetColor(BLACK);
  for(i=0; i < scroll_amount; i++)
   {
     DrawLine(width-scroll_amount+i-1, line[(where+i-1)%MAX],
	      width-scroll_amount+i,   line[(where+i)  %MAX]);
   }
  where += i;
  
  if (remove_timeout == FALSE)
    AddTimeOut(timeout, do_anim, NULL);
  else
    remove_timeout = FALSE;
}


void anim(Widget w, void *data)
{
  static int toggle=0;

  toggle ^= 1;
  if (toggle)
   {
     SetLabel(w, "Stop Anim");
     AddTimeOut(timeout, do_anim, NULL); 
   }
  else
   {
     remove_timeout = TRUE;
     SetLabel(w, "  Animate  ");
   }
}



/* This is the "random midpoint displacement algorithim"  It hasn't been
 * optimized, and I don't know why I used all the temporary variables....
 */

fracline(int a, int b)
{
  int mid;
  double temp, temp1, temp2;
  
  if ( (b - a) > 1){
    mid = (a + b) / 2;
    
    temp1 = (line[a] + line[b])/2;
    temp = (double)(b - a);
    
    temp2 = (double)rand() / (double)max_random;
    temp2 = (temp2 * 2.0) - 1.0;
    
    line[mid] = (int)(temp1 + (temp2 * temp * rug));
    
    if (line[mid] < 0)
      line[mid] = 0;
    else if (line[mid] > 500)
      line[mid] = 500;
    
    fracline(a, mid);
    fracline(mid, b);
  }
}


