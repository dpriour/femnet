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
typedef void (*GeneralCB)(void *);
typedef void (*IOCallback)(void *, int *);
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
int GLOpenDisplay(int argc, char **argv, int *attributes);
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
void Gtk3RequestRedraw(void);
char *Gtk3GetFile(const char *initial_folder);
char *Gtk3GetFileFiltered(const char *initial_folder, const char *pattern);
char *Gtk3GetFinalFile(const char *initial_folder);
void SetWidgetPos(Widget w, int where1, Widget from1, int where2, Widget from2);
void SetWidgetGridPosition(Widget w, int column, int row, int width, int height);
void SetMenuItemChecked(Widget w, int state);
void SetWidgetSensitive(Widget w, int sensitive);
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
char *GetSaveFile(char *suggested_name, const char *initial_folder);
int SaveDrawAreaAsPdf(const char *path);
int SaveDrawAreaAsPng(const char *path);
int BeginDrawAreaPngFrame(void);
int EndDrawAreaPngFrame(const char *path);
Widget MakeWindow(char *name, char *display, int exclusive);
void SetCurrentWindow(Widget w);
void CloseWindow(void);
Widget MakeButton(char *label, ButtonCB cb, void *data);
Widget MakeLabel(char *text);
Widget MakeToggle(char *text, int state, Widget parent, ButtonCB cb, void *data);
void SetToggleState(Widget w, int state);
int GetToggleState(Widget w);
Widget MakeStringEntry(char *text, int width, StringCB cb, void *data);
void SetStringEntry(Widget w, char *text);
char *GetStringEntry(Widget w);
Widget MakeHorizScrollbar(int len, ScrollCB cb, void *data);
Widget MakeVertScrollbar(int len, ScrollCB cb, void *data);
void SetScrollbar(Widget w, float where, float max, float shown);
Widget MakeScrollList(char **list, int width, int height, ListCB cb, void *data);
void SetCurrentListItem(Widget w, int index);
int GetCurrentListItem(Widget w);
void ChangeScrollList(Widget w, char **list);
void SetWidgetFont(Widget w, XFont f);
XFont GetFont(char *name);
void FreeFont(XFont f);
void AttachEdge(Widget w, int edge, int to);
void SetFgColor(Widget w, int c);
void SetBgColor(Widget w, int c);
void SetBorderColor(Widget w, int c);
int GetFgColor(Widget w);
int GetBgColor(Widget w);
void DrawPixel(int x, int y);
void ScrollDrawArea(int dx, int dy, int x1, int y1, int x2, int y2);
void AddTimeOut(unsigned long interval, GeneralCB cb, void *data);
void AddReadCallback(int fd, IOCallback cb, void *data);
void AddWriteCallback(int fd, IOCallback cb, void *data);
void FreeStandardColors(void);
void SetWidgetBitmap(Widget w, char *data, int width, int height);
int GetPixel(int x, int y);

#endif
