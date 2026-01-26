/*
 * A color chooser.  The function GetColor() pops up a modal window
 * that lets a user interactively play with a color in either RGB or
 * HSV space and then returns the chosen value to your program.
 *
 * Written by Allen Martin (amartin@cs.wpi.edu)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libsx.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct {
  Widget creq_window;
  Widget red_label, red_string, red_scroll;
  Widget green_label, green_string, green_scroll;
  Widget blue_label, blue_string, blue_scroll;  

  int color;
  int rgb;
  float r, g, b;
  float h, s, v;
  int cancelled;
} CReqData;

#define BOX_WIDTH  85
#define BOX_HEIGHT 85

static void color_cancel(Widget w, CReqData *cdata);
static void color_ok(Widget w, CReqData *cdata);
static void color_string(Widget w, char *string, CReqData *cdata);
static void color_scroll(Widget w, float val, CReqData *cdata);
static void color_redisplay(Widget w, int width, int height, CReqData *cdata);
static void rgb_hsv(Widget w, CReqData *cdata);
static void rgb2hsv(float r, float g, float b, float *h, float *s, float *v);
static void hsv2rgb(float h, float s, float v, float *r, float *g, float *b);

/*
 * GetColor()
 */
int GetColor(unsigned char *r, unsigned char *g, unsigned char *b)
{
  CReqData cdata;
  Widget w[14];
  char cvalue[4];
  int width;
  
  /* initialize the color values */
  cdata.r = (float)*r; cdata.g = (float)*g; cdata.b = (float)*b;
  rgb2hsv(cdata.r, cdata.g, cdata.b, &cdata.h, &cdata.s, &cdata.v);

  cdata.rgb=TRUE;

  cdata.creq_window = MakeWindow("Color Requestor", SAME_DISPLAY,
				 EXCLUSIVE_WINDOW);

  w[0]  = MakeButton("RGB/HSV", (void *)rgb_hsv, &cdata);

  /* determine the width to make the string widgets with */
  width = TextWidth(GetWidgetFont(w[0]),  "88888");
  
  w[1]  = MakeLabel("R");
  sprintf(cvalue, "%d", *r);
  w[2]  = MakeStringEntry(cvalue, width, (void *)color_string, &cdata);
  w[3]  = MakeHorizScrollbar(250, (void *)color_scroll, &cdata);
  SetScrollbar(w[3], (float)*r, 255.0, 1.0);

  w[4]  = MakeLabel("G");
  sprintf(cvalue, "%d", *g);
  w[5]  = MakeStringEntry(cvalue, width, (void *)color_string, &cdata);
  w[6]  = MakeHorizScrollbar(250, (void *)color_scroll, &cdata);
  SetScrollbar(w[6], (float)*g, 255.0, 1.0);

  w[7]  = MakeLabel("B");
  sprintf(cvalue, "%d", *b);
  w[8]  = MakeStringEntry(cvalue, width, (void *)color_string, &cdata);
  w[9]  = MakeHorizScrollbar(250, (void *)color_scroll, &cdata);
  SetScrollbar(w[9], (float)*b, 255.0, 1.0);

  w[10] = MakeDrawArea(BOX_WIDTH, BOX_HEIGHT, (void *)color_redisplay, &cdata);
  w[11] = MakeButton("Ok", (void *)color_ok, &cdata);
  w[12] = MakeLabel("Please Edit the Color Above");
  w[13] = MakeButton("Cancel", (void *)color_cancel, &cdata);
  
  SetWidgetPos(w[1],  PLACE_UNDER, w[0], NO_CARE,     NULL);
  SetWidgetPos(w[2],  PLACE_UNDER, w[0], PLACE_RIGHT, w[1]);
  SetWidgetPos(w[3],  PLACE_UNDER, w[0], PLACE_RIGHT, w[2]);
  SetWidgetPos(w[4],  PLACE_UNDER, w[1], NO_CARE,     NULL);
  SetWidgetPos(w[5],  PLACE_UNDER, w[1], PLACE_RIGHT, w[4]);
  SetWidgetPos(w[6],  PLACE_UNDER, w[1], PLACE_RIGHT, w[5]);
  SetWidgetPos(w[7],  PLACE_UNDER, w[4], NO_CARE,     NULL);
  SetWidgetPos(w[8],  PLACE_UNDER, w[4], PLACE_RIGHT, w[7]);
  SetWidgetPos(w[9],  PLACE_UNDER, w[4], PLACE_RIGHT, w[8]);
  SetWidgetPos(w[10], PLACE_RIGHT, w[3], NO_CARE,     NULL);
  SetWidgetPos(w[11], PLACE_UNDER, w[7], NO_CARE,     NULL);
  SetWidgetPos(w[12], PLACE_UNDER, w[7], PLACE_RIGHT, w[11]);
  SetWidgetPos(w[13], PLACE_UNDER, w[7], PLACE_RIGHT, w[12]);

  /* save important widgets */
  cdata.red_label    = w[1];
  cdata.red_string   = w[2];
  cdata.red_scroll   = w[3];

  cdata.green_label  = w[4];
  cdata.green_string = w[5];
  cdata.green_scroll = w[6];

  cdata.blue_label   = w[7];
  cdata.blue_string  = w[8];
  cdata.blue_scroll  = w[9];

  ShowDisplay();

  /* allocate the custom color */
  cdata.color = GetPrivateColor();
  SetPrivateColor(cdata.color, cdata.r, cdata.g, cdata.b);
  SetDrawArea(w[10]);
  SetColor(cdata.color);

  MainLoop();
  
  SetCurrentWindow(ORIGINAL_WINDOW);

  /* check for cancel */
  if(cdata.cancelled)
    return(TRUE);

  *r = (unsigned char)cdata.r;
  *g = (unsigned char)cdata.g;
  *b = (unsigned char)cdata.b;

  return(FALSE);
}

/*
 * rgb_hsv() - Callback for the RGB/HSV button
 */
static void rgb_hsv(Widget w, CReqData *cdata)
{
  char cvalue[4];
  
  cdata->rgb = !cdata->rgb;

  if(cdata->rgb)
    {
      SetLabel(cdata->red_label,   "R");
      SetLabel(cdata->green_label, "G");
      SetLabel(cdata->blue_label,  "B");

      sprintf(cvalue, "%d", (int)cdata->r);
      SetScrollbar(cdata->red_scroll, (float)cdata->r, 255.0, 1.0);
      SetStringEntry(cdata->red_string, cvalue);
      
      sprintf(cvalue, "%d", (int)cdata->g);
      SetScrollbar(cdata->green_scroll, (float)cdata->g, 255.0, 1.0);
      SetStringEntry(cdata->green_string, cvalue);
      
      sprintf(cvalue, "%d", (int)cdata->b);
      SetScrollbar(cdata->blue_scroll, (float)cdata->b, 255.0, 1.0);
      SetStringEntry(cdata->blue_string, cvalue);
    }

  else
    {
      SetLabel(cdata->red_label,   "H");
      SetLabel(cdata->green_label, "S");
      SetLabel(cdata->blue_label,  "V");

      sprintf(cvalue, "%d", (int)cdata->h);
      SetScrollbar(cdata->red_scroll, (float)cdata->h, 360.0, 1.0);
      SetStringEntry(cdata->red_string, cvalue);
      
      sprintf(cvalue, "%d", (int)cdata->s);
      SetScrollbar(cdata->green_scroll, (float)cdata->s, 100.0, 1.0);
      SetStringEntry(cdata->green_string, cvalue);
      
      sprintf(cvalue, "%d", (int)cdata->v);
      SetScrollbar(cdata->blue_scroll, (float)cdata->v, 255.0, 1.0);
      SetStringEntry(cdata->blue_string, cvalue);
    }
}

/*
 * color_ok() - Callback for color requestor OK button
 */
static void color_ok(Widget w, CReqData *cdata)
{
  cdata->cancelled = FALSE;
  SetCurrentWindow(cdata->creq_window);
  CloseWindow();
}

/*
 * color_cancel() - Callback for color requestor CANCEL button
 */
static void color_cancel(Widget w, CReqData *cdata)
{
  cdata->cancelled = TRUE;
  SetCurrentWindow(cdata->creq_window);
  CloseWindow();
}

static void color_string(Widget w, char *string, CReqData *cdata)
{
  char cvalue[4];
  float val;
  
  val = atof(string);
  val = MAX(0, val);

  if(cdata->rgb)
    {
      /* range the value */
      val = MIN(255, val);
      
      sprintf(cvalue, "%d", (int)val);

      if(w==cdata->red_string)
	{
	  SetScrollbar(cdata->red_scroll, val, 255.0, 1.0);
	  SetStringEntry(cdata->red_string, cvalue);
	  cdata->r = val;
	}
      else if(w==cdata->green_string)
	{
	  SetScrollbar(cdata->green_scroll, val, 255.0, 1.0);
	  SetStringEntry(cdata->green_string, cvalue);
	  cdata->g = val;
	}
      else if(w==cdata->blue_string)
	{
	  SetScrollbar(cdata->blue_scroll, val, 255.0, 1.0);
	  SetStringEntry(cdata->blue_string, cvalue);
	  cdata->b = val;
	}

      rgb2hsv(cdata->r,  cdata->g,  cdata->b,
	      &cdata->h, &cdata->s, &cdata->v);
    }
  else
    {
      if(w==cdata->red_string)
	{
	  val = MIN(360, val);
	  sprintf(cvalue, "%d", (int)val);

	  SetScrollbar(cdata->red_scroll, val, 360.0, 1.0);
	  SetStringEntry(cdata->red_string, cvalue);
	  cdata->h = val;
	}
      else if(w==cdata->green_string)
	{
	  val = MIN(100, val);
	  sprintf(cvalue, "%d", (int)val);

	  SetScrollbar(cdata->green_scroll, val, 100.0, 1.0);
	  SetStringEntry(cdata->green_string, cvalue);
	  cdata->s = val;
	}
      else if(w==cdata->blue_string)
	{
	  val = MIN(255, val);
	  sprintf(cvalue, "%d", (int)val);

	  SetScrollbar(cdata->blue_scroll, val, 255.0, 1.0);
	  SetStringEntry(cdata->blue_string, cvalue);
	  cdata->v = val;
	}

      hsv2rgb(cdata->h,  cdata->s,  cdata->v,
	      &cdata->r, &cdata->g, &cdata->b);
    }      
  
  SetPrivateColor(cdata->color, (int)cdata->r, (int)cdata->g, (int)cdata->b);
}

static void color_scroll(Widget w, float val, CReqData *cdata)
{
  char cvalue[4];
  
  sprintf(cvalue, "%d", (int)val);

  if(cdata->rgb)
    {
      if(w==cdata->red_scroll)
	{
	  SetStringEntry(cdata->red_string, cvalue);
	  cdata->r = val;
	}
      else if(w==cdata->green_scroll)
	{
	  SetStringEntry(cdata->green_string, cvalue);
	  cdata->g = val;
	}
      else if(w==cdata->blue_scroll)
	{
	  SetStringEntry(cdata->blue_string, cvalue);
	  cdata->b = val;
	}

      rgb2hsv(cdata->r,  cdata->g,  cdata->b,
	      &cdata->h, &cdata->s, &cdata->v);
    }
  else
    {
      if(w==cdata->red_scroll)
	{
	  SetStringEntry(cdata->red_string, cvalue);
	  cdata->h = val;
	}
      else if(w==cdata->green_scroll)
	{
	  SetStringEntry(cdata->green_string, cvalue);
	  cdata->s = val;
	}
      else if(w==cdata->blue_scroll)
	{
	  SetStringEntry(cdata->blue_string, cvalue);
	  cdata->v = val;
	}

      hsv2rgb(cdata->h,  cdata->s,  cdata->v,
	      &cdata->r, &cdata->g, &cdata->b);
    }      

  SetPrivateColor(cdata->color, (int)cdata->r, (int)cdata->g, (int)cdata->b);
}
  

/*
 * color_redisplay() - Redisplay callback for the creq draw area
 */
static void color_redisplay(Widget w, int width, int height, CReqData *cdata)
{
  DrawFilledBox(0, 0, width, height);
}


static void rgb2hsv(float r, float g, float b, float *h, float *s, float *v)
{
  float   max = MAX(r,MAX(g,b));
  float   min = MIN(r,MIN(g,b));
  float   delta;
  
  *v = max;
  if (max != 0.0)
    *s = (max - min) / max;
  else
    *s = 0.0;
  
  if (*s == 0)
   {
     *h = 0;
   }
  else
   {
     delta = max - min;
     if (r == max) 
       *h = (g - b) / delta;
     else if (g == max)
       *h = 2 + (b - r) / delta;
     else if (b == max)
       *h = 4 + (r - g) / delta;
     *h *= 60;
     if (*h < 0.0)
       *h += 360;
   }

  *s *= 100.0;
}

static void hsv2rgb(float h, float _s, float v, float *r, float *g, float *b)
{
  int     i;
  float   f,p,q,t;
  float   s=_s;

  s /= 100.0;
  
  if (s == 0 && h == 0)
   {
     *r = *g = *b = v;
   }
  else
   {
     if (h >= 360.0)
       h = 0.0;
     h /= 60.0;
     
     i = h;
     f = h - i;
     p = v * (1 - s);
     q = v * (1 - (s * f));
     t = v * (1 - (s * (1 - f)));
     switch (i)
      {
	case 0: *r = v; *g = t; *b = p; break;
	case 1: *r = q; *g = v; *b = p; break;
	case 2: *r = p; *g = v; *b = t; break;
	case 3: *r = p; *g = q; *b = v; break;
	case 4: *r = t; *g = p; *b = v; break;
	case 5: *r = v; *g = p; *b = q; break;
      }
   }
}







