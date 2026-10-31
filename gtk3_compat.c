#include "phobos.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

int WHITE=0, BLACK=1, RED=2, GREEN=3, BLUE=4, YELLOW=5;
static GtkWidget *window, *vbox, *menubar, *area;
static GtkWidget *current_menu;
static cairo_t *cr;
static GdkRGBA palette[512];
static int colors=6, active_color=1, line_width=1;
static RedisplayCB redisplay_cb;
static void *redisplay_data;
static MouseButtonCB down_cb,up_cb;
static void *drawing_data;
static MotionCB motion_cb;

static void menu_activate(GtkMenuItem *item, gpointer data) {
    ButtonCB cb=(ButtonCB)g_object_get_data(G_OBJECT(item),"phobos-callback");
    if(cb) cb(GTK_WIDGET(item),g_object_get_data(G_OBJECT(item),"phobos-data"));
    if(area) gtk_widget_queue_draw(area);
}
static gboolean draw_cb(GtkWidget *widget,cairo_t *context,gpointer data) {
    cr=context;
    if(redisplay_cb) { GtkAllocation a; gtk_widget_get_allocation(widget,&a); redisplay_cb(widget,a.width,a.height,redisplay_data); }
    cr=NULL; return FALSE;
}
int Gtk3DrawingIsActive(void){return cr!=NULL;}
int SaveDrawAreaAsPng(const char *path){
    GtkAllocation a;
    cairo_surface_t *surface;
    cairo_status_t status;
    if(!area||!redisplay_cb||!path||!*path)return 0;
    gtk_widget_get_allocation(area,&a);
    if(a.width<=0||a.height<=0)return 0;
    surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,a.width,a.height);
    status=cairo_surface_status(surface);
    if(status!=CAIRO_STATUS_SUCCESS){cairo_surface_destroy(surface);return 0;}
    cr=cairo_create(surface);
    redisplay_cb(area,a.width,a.height,redisplay_data);
    status=cairo_status(cr);
    cairo_destroy(cr);
    cr=NULL;
    if(status==CAIRO_STATUS_SUCCESS)status=cairo_surface_status(surface);
    if(status==CAIRO_STATUS_SUCCESS)status=cairo_surface_write_to_png(surface,path);
    cairo_surface_destroy(surface);
    return status==CAIRO_STATUS_SUCCESS;
}
static gboolean mouse_cb(GtkWidget *w,GdkEventButton *e,gpointer data) {
    MouseButtonCB cb=e->type==GDK_BUTTON_PRESS?down_cb:up_cb;
    if(cb) cb(w,(int)e->button,(int)e->x,(int)e->y,drawing_data);
    gtk_widget_queue_draw(w);
    return TRUE;
}
static gboolean motion_event(GtkWidget *w,GdkEventMotion *e,gpointer data) {
    if(motion_cb) motion_cb(w,(int)e->x,(int)e->y,drawing_data);
    return TRUE;
}
static gboolean scroll_event(GtkWidget *w,GdkEventScroll *e,gpointer data) {
    GtkAllocation a;
    double dy=0.0,factor,anchor_x,anchor_y,new_width,new_height;
    if(e->direction==GDK_SCROLL_UP) dy=-1.0;
    else if(e->direction==GDK_SCROLL_DOWN) dy=1.0;
    else if(e->direction==GDK_SCROLL_SMOOTH) dy=e->delta_y;
    else return FALSE;
    if(dy==0.0) return TRUE;

    gtk_widget_get_allocation(w,&a);
    if(a.width<=0||a.height<=0||baxx<=binx||baxy<=biny) return TRUE;
    factor=exp(dy*0.20);
    if(factor<0.2) factor=0.2;
    if(factor>5.0) factor=5.0;
    anchor_x=binx+(e->x/a.width)*(baxx-binx);
    anchor_y=baxy+(e->y/a.height)*(biny-baxy);
    new_width=(baxx-binx)*factor;
    new_height=(biny-baxy)*factor;
    binx=anchor_x-(e->x/a.width)*new_width;
    baxx=binx+new_width;
    baxy=anchor_y-(e->y/a.height)*new_height;
    biny=baxy+new_height;
    bcartmax=(new_width>new_height)?new_width:new_height;
    gtk_widget_queue_draw(w);
    (void)data;
    return TRUE;
}
int OpenDisplay(int argc,char **argv) {
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL); gtk_window_set_title(GTK_WINDOW(window),"Phobos");
    gtk_window_set_default_size(GTK_WINDOW(window),1000,850);
    gtk_window_set_resizable(GTK_WINDOW(window),TRUE);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0); gtk_container_add(GTK_CONTAINER(window),vbox);
    menubar=gtk_menu_bar_new(); gtk_box_pack_start(GTK_BOX(vbox),menubar,FALSE,FALSE,0);
    return TRUE;
}
void MainLoop(void){gtk_main();}
void ShowDisplay(void){gtk_widget_show_all(window);}
void SyncDisplay(void){while(gtk_events_pending()) gtk_main_iteration();}
Widget MakeMenu(char *name){
    GtkWidget *root=gtk_menu_item_new_with_label(name),*menu=gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(root),menu); gtk_menu_shell_append(GTK_MENU_SHELL(menubar),root); current_menu=menu; return root;
}
Widget MakeMenuItem(Widget menu,char *name,ButtonCB cb,void *data){
    GtkWidget *submenu=GTK_IS_MENU_ITEM(menu)?gtk_menu_item_get_submenu(GTK_MENU_ITEM(menu)):NULL;
    GtkWidget *item=gtk_menu_item_new_with_label(name);
    gtk_menu_shell_append(GTK_MENU_SHELL(submenu?submenu:current_menu),item);
    g_object_set_data(G_OBJECT(item),"phobos-callback",(gpointer)cb);
    g_object_set_data(G_OBJECT(item),"phobos-data",data);
    g_object_set_data_full(G_OBJECT(item),"phobos-label",g_strdup(name),g_free);
    if(cb) g_signal_connect(item,"activate",G_CALLBACK(menu_activate),NULL);
    return item;
}
Widget MakeDrawArea(int width,int height,RedisplayCB cb,void *data){
    area=gtk_drawing_area_new();
    /* Keep a practical minimum while allowing the GTK window to shrink/grow. */
    gtk_widget_set_size_request(area,320,240);
    gtk_widget_set_hexpand(area,TRUE); gtk_widget_set_vexpand(area,TRUE);
    redisplay_cb=cb; redisplay_data=data; drawing_data=data;
    g_signal_connect(area,"draw",G_CALLBACK(draw_cb),NULL);
    gtk_widget_add_events(area,GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK|GDK_POINTER_MOTION_MASK);
    g_signal_connect(area,"button-press-event",G_CALLBACK(mouse_cb),NULL);
    g_signal_connect(area,"button-release-event",G_CALLBACK(mouse_cb),NULL);
    g_signal_connect(area,"motion-notify-event",G_CALLBACK(motion_event),NULL);
    gtk_box_pack_start(GTK_BOX(vbox),area,TRUE,TRUE,0); return area;
}
void SetButtonDownCB(Widget w,MouseButtonCB cb){down_cb=cb;}
void SetButtonUpCB(Widget w,MouseButtonCB cb){up_cb=cb;}
void SetMouseMotionCB(Widget w,MotionCB cb){motion_cb=cb;}
void SetMouseWheelCB(Widget w){gtk_widget_add_events(w,GDK_SCROLL_MASK|GDK_SMOOTH_SCROLL_MASK);g_signal_connect(w,"scroll-event",G_CALLBACK(scroll_event),NULL);}
void SetWidgetPos(Widget w,int p1,Widget from1,int p2,Widget from2){(void)w;(void)p1;(void)from1;(void)p2;(void)from2;}
void SetMenuItemChecked(Widget w,int state){if(w){const char *label=g_object_get_data(G_OBJECT(w),"phobos-label");g_object_set_data(G_OBJECT(w),"phobos-checked",GINT_TO_POINTER(state!=0));if(label&&GTK_IS_MENU_ITEM(w)){char *marked=state?g_strconcat("✓  ",label,NULL):g_strdup(label);gtk_menu_item_set_label(GTK_MENU_ITEM(w),marked);g_free(marked);}}}
int GetMenuItemChecked(Widget w){return w?GPOINTER_TO_INT(g_object_get_data(G_OBJECT(w),"phobos-checked")):0;}
void GetStandardColors(void){palette[0]=(GdkRGBA){1,1,1,1};palette[1]=(GdkRGBA){0,0,0,1};palette[2]=(GdkRGBA){1,0,0,1};palette[3]=(GdkRGBA){0,1,0,1};palette[4]=(GdkRGBA){0,0,1,1};palette[5]=(GdkRGBA){1,1,0,1};}
int GetRGBColor(int r,int g,int b){if(colors>=512)return BLACK; palette[colors]=(GdkRGBA){r/255.0,g/255.0,b/255.0,1};return colors++;}
void SetColor(int c){active_color=(c>=0&&c<colors)?c:BLACK;}
void SetLineWidth(int width){line_width=width>0?width:1;}
static void source(void){gdk_cairo_set_source_rgba(cr,&palette[active_color]);cairo_set_line_width(cr,line_width);}
void DrawLine(int x1,int y1,int x2,int y2){if(!cr)return;source();cairo_move_to(cr,x1,y1);cairo_line_to(cr,x2,y2);cairo_stroke(cr);}
void DrawPolyline(XPoint*p,int n){if(!cr||!p||n<2)return;source();cairo_move_to(cr,p[0].x,p[0].y);for(int i=1;i<n;i++)cairo_line_to(cr,p[i].x,p[i].y);cairo_stroke(cr);}
void DrawFilledPolygon(XPoint*p,int n){if(!cr||!p||n<3)return;source();cairo_move_to(cr,p[0].x,p[0].y);for(int i=1;i<n;i++)cairo_line_to(cr,p[i].x,p[i].y);cairo_close_path(cr);cairo_fill(cr);}
void DrawFilledBox(int x,int y,int w,int h){if(!cr)return;source();cairo_rectangle(cr,x,y,w,h);cairo_fill(cr);}
void DrawBox(int x,int y,int w,int h){if(!cr)return;source();cairo_rectangle(cr,x,y,w,h);cairo_stroke(cr);}
void DrawText(char*t,int x,int y){if(!cr||!t)return;source();cairo_move_to(cr,x,y);cairo_show_text(cr,t);}
void DrawArc(int x,int y,int w,int h,int a,int b){if(!cr)return;source();cairo_save(cr);cairo_translate(cr,x+w/2.0,y+h/2.0);cairo_scale(cr,w/2.0,h/2.0);cairo_arc(cr,0,0,1,a*M_PI/180.0,(a+b)*M_PI/180.0);cairo_restore(cr);cairo_stroke(cr);}
void DrawFilledArc(int x,int y,int w,int h,int a,int b){if(!cr)return;source();cairo_save(cr);cairo_translate(cr,x+w/2.0,y+h/2.0);cairo_scale(cr,w/2.0,h/2.0);cairo_arc(cr,0,0,1,a*M_PI/180.0,(a+b)*M_PI/180.0);cairo_restore(cr);cairo_fill(cr);}
void ClearDrawArea(void){if(cr){cairo_save(cr);cairo_set_source_rgb(cr,1,1,1);cairo_paint(cr);cairo_restore(cr);}}
void SetDrawArea(Widget w){(void)w;}
void GetDrawAreaSize(int*w,int*h){GtkAllocation a;if(area){gtk_widget_get_allocation(area,&a);if(w)*w=a.width;if(h)*h=a.height;}}
void SetDrawMode(int mode){(void)mode;}
void SetDrawMotif(char*m,int n){(void)m;(void)n;}
void Beep(void){gdk_display_beep(gdk_display_get_default());}
void SetWidgetState(Widget w,int s){if(w)gtk_widget_set_sensitive(w,s);}
int GetWidgetState(Widget w){return gtk_widget_get_sensitive(w);}
void SetLabel(Widget w,char*t){if(GTK_IS_LABEL(w))gtk_label_set_text(GTK_LABEL(w),t);else if(GTK_IS_MENU_ITEM(w))gtk_menu_item_set_label(GTK_MENU_ITEM(w),t);}
char *GetString(char*p,char*d){(void)p;(void)d;return NULL;}
int GetYesNo(char*q){(void)q;return 0;}
char *GetFile(char *path){static char selected[4096];GtkWidget*d=gtk_file_chooser_dialog_new("Choisir un fichier",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,"Annuler",GTK_RESPONSE_CANCEL,"Ouvrir",GTK_RESPONSE_ACCEPT,NULL);if(path)gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(d),path);selected[0]='\0';if(gtk_dialog_run(GTK_DIALOG(d))==GTK_RESPONSE_ACCEPT){char *filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(d));if(filename){g_strlcpy(selected,filename,sizeof(selected));g_free(filename);}}gtk_widget_destroy(d);return selected;}
char *GetDonFile(char *path){static char selected[4096];GtkWidget*d=gtk_file_chooser_dialog_new("Choisir un fichier .don",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,"Annuler",GTK_RESPONSE_CANCEL,"Ouvrir",GTK_RESPONSE_ACCEPT,NULL);GtkFileFilter*filter=gtk_file_filter_new();gtk_file_filter_set_name(filter,"Fichiers .don");gtk_file_filter_add_pattern(filter,"*.don");gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(d),filter);if(path)gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(d),path);selected[0]='\0';if(gtk_dialog_run(GTK_DIALOG(d))==GTK_RESPONSE_ACCEPT){char *filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(d));if(filename){g_strlcpy(selected,filename,sizeof(selected));g_free(filename);}}gtk_widget_destroy(d);return selected;}
char *GetStaFile(char *path){static char selected[4096];GtkWidget*d=gtk_file_chooser_dialog_new("Choisir un fichier .sta",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,"Annuler",GTK_RESPONSE_CANCEL,"Ouvrir",GTK_RESPONSE_ACCEPT,NULL);GtkFileFilter*filter=gtk_file_filter_new();gtk_file_filter_set_name(filter,"Fichiers .sta");gtk_file_filter_add_pattern(filter,"*.sta");gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(d),filter);if(path)gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(d),path);selected[0]='\0';if(gtk_dialog_run(GTK_DIALOG(d))==GTK_RESPONSE_ACCEPT){char *filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(d));if(filename){g_strlcpy(selected,filename,sizeof(selected));g_free(filename);}}gtk_widget_destroy(d);return selected;}
char *GetSavePngFile(char *suggested_name){static char selected[4096];GtkWidget*d=gtk_file_chooser_dialog_new("Enregistrer le dessin PNG",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_SAVE,"Annuler",GTK_RESPONSE_CANCEL,"Enregistrer",GTK_RESPONSE_ACCEPT,NULL);GtkFileFilter*filter=gtk_file_filter_new();gtk_file_filter_set_name(filter,"Images PNG");gtk_file_filter_add_pattern(filter,"*.png");gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(d),filter);gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(d),TRUE);if(suggested_name&&*suggested_name)gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(d),suggested_name);selected[0]='\0';if(gtk_dialog_run(GTK_DIALOG(d))==GTK_RESPONSE_ACCEPT){char *filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(d));if(filename){g_strlcpy(selected,filename,sizeof(selected));g_free(filename);}}gtk_widget_destroy(d);return selected;}
void edit(Widget w,void *data){GtkWidget*d,*spin;int value;d=gtk_dialog_new_with_buttons("Période des fils",GTK_WINDOW(window),GTK_DIALOG_MODAL,"Annuler",GTK_RESPONSE_CANCEL,"Valider",GTK_RESPONSE_ACCEPT,NULL);spin=gtk_spin_button_new_with_range(1,100000,1);value=periode_fils>0?periode_fils:1;gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin),value);gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(d))),spin);gtk_widget_show_all(d);if(gtk_dialog_run(GTK_DIALOG(d))==GTK_RESPONSE_ACCEPT){periode_fils=(int)gtk_spin_button_get_value(GTK_SPIN_BUTTON(spin));initialisation_nb_fils();fils_contour_calculer();axe_T90_calculer();}gtk_widget_destroy(d);(void)w;(void)data;}
