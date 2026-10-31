#ifndef PHOBOS_GTK3_LIBSX_COMPAT_H
#define PHOBOS_GTK3_LIBSX_COMPAT_H

/* Minimal source compatibility layer: the implementation is GTK3/Cairo. */
#include <gtk/gtk.h>
#include <locale.h> // 1. N'oubliez pas d'inclure cette bibliothèque
#include <X11/Xlib.h>

typedef GtkWidget *Widget;
typedef void (*ButtonCB)(Widget, void *);
typedef void (*RedisplayCB)(Widget, int, int, void *);
typedef void (*MouseButtonCB)(Widget, int, int, int, void *);
typedef void (*MotionCB)(Widget, int, int, void *);
typedef void (*StringCB)(Widget, char *, void *);
typedef void (*ScrollCB)(Widget, float, void *);
typedef void (*ListCB)(Widget, char *, int, void *);
typedef PangoFontDescription *XFont;

#define SAME_DISPLAY NULL
#define NONEXCLUSIVE_WINDOW 0
#define EXCLUSIVE_WINDOW 1
#define ORIGINAL_WINDOW NULL
#define NO_CARE 0
#define PLACE_RIGHT 1
#define PLACE_UNDER 2
#define LEFT_EDGE 0
#define RIGHT_EDGE 1
#define TOP_EDGE 2
#define BOTTOM_EDGE 3
#define ATTACH_LEFT 0
#define ATTACH_RIGHT 1
#define ATTACH_TOP 2
#define ATTACH_BOTTOM 3
#define SANE_XOR 0x7f

extern int WHITE, BLACK, RED, GREEN, BLUE, YELLOW;
int OpenDisplay(int argc, char **argv);
void MainLoop(void);
void ShowDisplay(void);
void SyncDisplay(void);
Widget MakeMenu(char *name);
Widget MakeMenuItem(Widget menu, char *name, ButtonCB callback, void *data);
Widget MakeDrawArea(int width, int height, RedisplayCB callback, void *data);
void SetButtonDownCB(Widget w, MouseButtonCB cb);
void SetButtonUpCB(Widget w, MouseButtonCB cb);
void SetMouseMotionCB(Widget w, MotionCB cb);
void SetMouseWheelCB(Widget w);
int Gtk3DrawingIsActive(void);
void SetWidgetPos(Widget w, int where1, Widget from1, int where2, Widget from2);
void SetMenuItemChecked(Widget w, int state);
int GetMenuItemChecked(Widget w);
void SetColor(int color);
void SetLineWidth(int width);
int GetRGBColor(int r, int g, int b);
void GetStandardColors(void);
void DrawLine(int x1,int y1,int x2,int y2);
void DrawPolyline(XPoint *points,int n);
void DrawFilledPolygon(XPoint *points,int n);
void DrawFilledBox(int x,int y,int width,int height);
void DrawBox(int x,int y,int width,int height);
void DrawText(char *text,int x,int y);
void DrawArc(int x,int y,int width,int height,int angle1,int angle2);
void DrawFilledArc(int x,int y,int width,int height,int angle1,int angle2);
void ClearDrawArea(void);
void SetDrawArea(Widget w);
void GetDrawAreaSize(int *w,int *h);
void SetDrawMode(int mode);
void SetDrawMotif(char *motif,int count);
void SetLineWidth(int width);
void Beep(void);
void SetWidgetState(Widget w,int state);
int GetWidgetState(Widget w);
void SetLabel(Widget w,char *text);
char *GetString(char *prompt,char *default_value);
int GetYesNo(char *question);
char *GetFile(char *path);
char *GetDonFile(char *path);
char *GetStaFile(char *path);
char *GetSavePngFile(char *suggested_name);
int SaveDrawAreaAsPng(const char *path);

#endif
