/*
 * A simple x window text viewer.  Written in frustration with using
 * Xless (which seems to ignore Xlib command line options like -fn).
 *
 *  Dominic Giampaolo
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libsx.h"
#include "../freq/freq.h"


typedef struct wininfo
{
  Widget window, text_widget, label_widget;
  int *num_windows;
  char *cur_path;
}WinInfo;


/*
 * Protos
 */
void make_text_viewer(char *fname, WinInfo *arg);



void error(char *str, char *pname)
{
  fprintf(stderr, "%s: %s", pname, str);
  exit(5);
}


void quit(Widget foo, void *arg)
{
  WinInfo *wi=(WinInfo *)arg;

  *(wi->num_windows) = *(wi->num_windows) - 1;

  SetCurrentWindow(XtParent(XtParent(foo)));
  CloseWindow();
  
  if (*(wi->num_windows) == 0)
    exit(0);
}


/*
 * Return the directory component of a string or NULL if it's in
 * the current directory.
 */
char *dirname(char *str)
{
  char *ptr, *tmp;

  ptr = strrchr(str, '/');
  if (ptr == NULL)
    return NULL;

  *ptr = '\0';
  tmp = strdup(str);

  *ptr = '/';

  return tmp;
}



/*
 * Open a new file in the same window.
 */
void new_file(Widget foo, void *arg)
{
  WinInfo *wi=(WinInfo *)arg;
  char *fname;

  fname = GetFile(wi->cur_path);
  if (fname)
   {
     SetTextWidgetText(wi->text_widget, fname, TRUE);
     SetLabel(wi->label_widget, fname);

     if (wi->cur_path)
       free(wi->cur_path);
     
     wi->cur_path = dirname(fname);
   }
}


void new_window(Widget foo, void *arg)
{
  WinInfo *wi=(WinInfo *)arg;
  WinInfo *new;
  char *fname;

  fname = GetFile(wi->cur_path);
  if (fname == NULL)
    return;

  new = (WinInfo *)calloc(sizeof(WinInfo), 1);
  if (new == NULL)
    return;

  new->num_windows = wi->num_windows;
  new->cur_path = dirname(fname);
  *(new->num_windows) = *(new->num_windows) + 1;
  
  new->window = MakeWindow("New Window", NULL, NONEXCLUSIVE_WINDOW);

  make_text_viewer(fname, new);
}



#define MAXLABEL  80

void make_text_viewer(char *fname, WinInfo *arg)
{
  Widget w[10];
  static char dummy_label[MAXLABEL];
  int i, width;
  XFont xf;

  for(i=0; i < MAXLABEL-1; i++)
    dummy_label[i] = ' ';
  dummy_label[i] = '\0';

  w[0] = MakeLabel(dummy_label);

  xf = GetWidgetFont(w[0]);
  if (xf != NULL)
    width = TextWidth(xf, dummy_label);
  else
    width = 600;

  w[1] = MakeTextWidget(fname, TRUE, FALSE, width, 500);
  w[2] = MakeButton("Quit", quit, arg);
  w[3] = MakeButton("New File", new_file, arg);
  w[4] = MakeButton("New Window", new_window, arg);
  
  
  SetWidgetPos(w[1], PLACE_UNDER, w[0], NO_CARE, NULL);
  SetWidgetPos(w[2], PLACE_UNDER, w[1], NO_CARE, NULL);
  SetWidgetPos(w[3], PLACE_UNDER, w[1], PLACE_RIGHT, w[2]);
  SetWidgetPos(w[4], PLACE_UNDER, w[1], PLACE_RIGHT, w[3]);
  
  AttachEdge(w[0], RIGHT_EDGE,  ATTACH_LEFT);
  AttachEdge(w[0], BOTTOM_EDGE, ATTACH_TOP);
  
  AttachEdge(w[1], LEFT_EDGE,   ATTACH_LEFT);
  AttachEdge(w[1], RIGHT_EDGE,  ATTACH_RIGHT);
  AttachEdge(w[1], TOP_EDGE,    ATTACH_TOP);
  AttachEdge(w[1], BOTTOM_EDGE, ATTACH_BOTTOM);
  
  AttachEdge(w[2], LEFT_EDGE,   ATTACH_LEFT);
  AttachEdge(w[2], RIGHT_EDGE,  ATTACH_LEFT);
  AttachEdge(w[2], TOP_EDGE,    ATTACH_BOTTOM);
  AttachEdge(w[2], BOTTOM_EDGE, ATTACH_BOTTOM);

  AttachEdge(w[3], LEFT_EDGE,   ATTACH_LEFT);
  AttachEdge(w[3], RIGHT_EDGE,  ATTACH_LEFT);
  AttachEdge(w[3], TOP_EDGE,    ATTACH_BOTTOM);
  AttachEdge(w[3], BOTTOM_EDGE, ATTACH_BOTTOM);

  AttachEdge(w[4], LEFT_EDGE,   ATTACH_LEFT);
  AttachEdge(w[4], RIGHT_EDGE,  ATTACH_LEFT);
  AttachEdge(w[4], TOP_EDGE,    ATTACH_BOTTOM);
  AttachEdge(w[4], BOTTOM_EDGE, ATTACH_BOTTOM);
  
  arg->text_widget  = w[1];
  arg->label_widget = w[0];

  ShowDisplay();

  SetLabel(w[0], fname);   /* set the real filename */
}



main(int argc, char **argv)
{
  int i,num_windows=0;
  Widget w[5];


  argc = OpenDisplay(argc, argv);
  if (argc == 0)
    error("Can't open display.", argv[0]);

  if (argc == 1)
    error("No files to view!\n", argv[0]);

  for(i=1; i < argc; i++)
   {
     WinInfo *wi;

     wi = (WinInfo *)calloc(sizeof(WinInfo), 1);
     if (wi == NULL)
       continue;
     
     wi->num_windows = &num_windows;
     wi->cur_path = dirname(argv[i]);
     
     num_windows++;
     if (i > 1)
       MakeWindow(argv[0], NULL, NONEXCLUSIVE_WINDOW);

     make_text_viewer(argv[i], wi);
   }

  MainLoop();
}
