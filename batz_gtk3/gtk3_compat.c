#include "batz.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cairo-pdf.h>

	/*
0 : invisible
1 : black
2 : blue
3 : red
4 : green
5 : yellow
	*/
//int WHITE=0, BLACK=1, RED=2, GREEN=3, BLUE=4, YELLOW=5;
int WHITE=0, BLACK=1, BLUE=2, RED=3, GREEN=4, YELLOW=5;
static GtkWidget *window, *vbox, *menubar, *area, *grid;
static GtkWidget *current_menu;
static cairo_t *cr;
static cairo_surface_t *png_frame_surface;
static GdkRGBA palette[512];
static int colors=6, active_color=1, line_width=1;
static RedisplayCB redisplay_cb;
static void *redisplay_data;
static MouseButtonCB down_cb,up_cb;
static void *drawing_data;
static MotionCB motion_cb;
static GtkWidget *dialog_window;
static GtkWidget *current_parent;
static GtkWidget *last_entry;
static GtkWidget *last_list;
static int default_fg=1,default_bg=0;
static int next_widget_row;
static GtkWidget *pack_widget(GtkWidget *w);

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
void Gtk3RequestRedraw(void){if(area)gtk_widget_queue_draw(area);}
char *Gtk3GetFileFiltered(const char *initial_folder, const char *pattern){
    static char selected[4096];
    char *resolved_folder=NULL;
    GtkWidget *dialog=gtk_file_chooser_dialog_new("Sélectionner un fichier",window?GTK_WINDOW(window):NULL,
        GTK_FILE_CHOOSER_ACTION_OPEN,"Annuler",GTK_RESPONSE_CANCEL,"Ouvrir",GTK_RESPONSE_ACCEPT,NULL);
    if(pattern&&*pattern){
        GtkFileFilter *filter=gtk_file_filter_new();
        gtk_file_filter_set_name(filter,pattern);
        gtk_file_filter_add_pattern(filter,pattern);
        gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog),filter);
        gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog),filter);
    }
    selected[0]='\0';
    if(initial_folder&&*initial_folder){
        if(g_file_test(initial_folder,G_FILE_TEST_IS_DIR)) resolved_folder=g_strdup(initial_folder);
        else if(g_file_test("data_2001",G_FILE_TEST_IS_DIR)) resolved_folder=g_strdup("data_2001");
        else if(g_file_test("../data_2001",G_FILE_TEST_IS_DIR)) resolved_folder=g_strdup("../data_2001");
        if(resolved_folder){gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),resolved_folder);g_free(resolved_folder);}
    }
    if(gtk_dialog_run(GTK_DIALOG(dialog))==GTK_RESPONSE_ACCEPT){
        char *filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if(filename){g_strlcpy(selected,filename,sizeof(selected));g_free(filename);}
    }
    gtk_widget_destroy(dialog);
    return selected;
}
char *Gtk3GetFile(const char *initial_folder){
    return Gtk3GetFileFiltered(initial_folder,NULL);
}
char *Gtk3GetFinalFile(const char *initial_folder){
    static char selected[4096];
    char *resolved_folder=NULL;
    GtkWidget *dialog=gtk_file_chooser_dialog_new("Sélectionner un fichier",window?GTK_WINDOW(window):NULL,
        GTK_FILE_CHOOSER_ACTION_OPEN,"Annuler",GTK_RESPONSE_CANCEL,"Ouvrir",GTK_RESPONSE_ACCEPT,NULL);
    GtkFileFilter *filter=gtk_file_filter_new();
    gtk_file_filter_set_name(filter,"*.sta, *.dyn");
    gtk_file_filter_add_pattern(filter,"*.sta");
    gtk_file_filter_add_pattern(filter,"*.dyn");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog),filter);
    gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog),filter);
    selected[0]='\0';
    if(initial_folder&&*initial_folder){
        if(g_file_test(initial_folder,G_FILE_TEST_IS_DIR)) resolved_folder=g_strdup(initial_folder);
        else if(g_file_test("data_2001",G_FILE_TEST_IS_DIR)) resolved_folder=g_strdup("data_2001");
        else if(g_file_test("../data_2001",G_FILE_TEST_IS_DIR)) resolved_folder=g_strdup("../data_2001");
        if(resolved_folder)gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog),resolved_folder);
    }
    g_free(resolved_folder);
    if(gtk_dialog_run(GTK_DIALOG(dialog))==GTK_RESPONSE_ACCEPT){
        char *filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        if(filename){g_strlcpy(selected,filename,sizeof(selected));g_free(filename);}
    }
    gtk_widget_destroy(dialog);
    return selected;
}
int SaveDrawAreaAsPdf(const char *path){
    GtkAllocation a;
    cairo_surface_t *surface;
    cairo_status_t status;
    if(!area||!redisplay_cb||!path||!*path)return 0;
    gtk_widget_get_allocation(area,&a);
    if(a.width<=0||a.height<=0)return 0;
    surface=cairo_pdf_surface_create(path,a.width,a.height);
    status=cairo_surface_status(surface);
    if(status!=CAIRO_STATUS_SUCCESS){cairo_surface_destroy(surface);return 0;}
    cr=cairo_create(surface);
    redisplay_cb(area,a.width,a.height,redisplay_data);
    cairo_show_page(cr);
    status=cairo_status(cr);
    cairo_destroy(cr);
    cr=NULL;
    if(status==CAIRO_STATUS_SUCCESS)status=cairo_surface_status(surface);
    cairo_surface_destroy(surface);
    return status==CAIRO_STATUS_SUCCESS;
}
int SaveDrawAreaAsPng(const char *path){
    GtkAllocation a;
    cairo_surface_t *surface;
    cairo_t *context;
    cairo_status_t status;
    if(!area||!redisplay_cb||!path||!*path)return 0;
    gtk_widget_get_allocation(area,&a);
    if(a.width<=0||a.height<=0)return 0;
    surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,a.width,a.height);
    status=cairo_surface_status(surface);
    if(status!=CAIRO_STATUS_SUCCESS){cairo_surface_destroy(surface);return 0;}
    context=cairo_create(surface);
    cr=context;
    redisplay_cb(area,a.width,a.height,redisplay_data);
    status=cairo_status(context);
    cr=NULL;
    cairo_destroy(context);
    if(status==CAIRO_STATUS_SUCCESS){
        cairo_surface_flush(surface);
        status=cairo_surface_write_to_png(surface,path);
    }
    cairo_surface_destroy(surface);
    return status==CAIRO_STATUS_SUCCESS;
}
int BeginDrawAreaPngFrame(void){
    GtkAllocation a;
    if(!area||cr||png_frame_surface)return 0;
    gtk_widget_get_allocation(area,&a);
    if(a.width<=0||a.height<=0)return 0;
    png_frame_surface=cairo_image_surface_create(CAIRO_FORMAT_ARGB32,a.width,a.height);
    if(cairo_surface_status(png_frame_surface)!=CAIRO_STATUS_SUCCESS){cairo_surface_destroy(png_frame_surface);png_frame_surface=NULL;return 0;}
    cr=cairo_create(png_frame_surface);
    if(cairo_status(cr)!=CAIRO_STATUS_SUCCESS){cairo_destroy(cr);cr=NULL;cairo_surface_destroy(png_frame_surface);png_frame_surface=NULL;return 0;}
    return 1;
}
int EndDrawAreaPngFrame(const char *path){
    cairo_status_t status;
    if(!cr||!png_frame_surface||!path||!*path)return 0;
    status=cairo_status(cr);
    cairo_destroy(cr);
    cr=NULL;
    if(status==CAIRO_STATUS_SUCCESS){
        cairo_surface_flush(png_frame_surface);
        status=cairo_surface_write_to_png(png_frame_surface,path);
    }
    cairo_surface_destroy(png_frame_surface);
    png_frame_surface=NULL;
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
    gtk_init(&argc,&argv);
    setlocale(LC_NUMERIC, "C");
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL); gtk_window_set_title(GTK_WINDOW(window),"Batz");
    gtk_window_set_default_size(GTK_WINDOW(window),1000,850);
    gtk_window_set_resizable(GTK_WINDOW(window),TRUE);
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    vbox=gtk_box_new(GTK_ORIENTATION_VERTICAL,0); gtk_container_add(GTK_CONTAINER(window),vbox);
    menubar=gtk_menu_bar_new(); gtk_box_pack_start(GTK_BOX(vbox),menubar,FALSE,FALSE,0);
    grid=gtk_grid_new(); gtk_grid_set_row_spacing(GTK_GRID(grid),4); gtk_grid_set_column_spacing(GTK_GRID(grid),4);
    gtk_box_pack_start(GTK_BOX(vbox),grid,TRUE,TRUE,0); current_parent=grid; next_widget_row=0;
    return TRUE;
}
void MainLoop(void){gtk_main();}
void ShowDisplay(void){if(window)gtk_widget_show_all(window);if(dialog_window)gtk_widget_show_all(dialog_window);}
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
    gtk_widget_add_events(area,GDK_BUTTON_PRESS_MASK|GDK_BUTTON_RELEASE_MASK|GDK_POINTER_MOTION_MASK|GDK_SCROLL_MASK|GDK_SMOOTH_SCROLL_MASK);
    g_signal_connect(area,"button-press-event",G_CALLBACK(mouse_cb),NULL);
    g_signal_connect(area,"button-release-event",G_CALLBACK(mouse_cb),NULL);
    g_signal_connect(area,"motion-notify-event",G_CALLBACK(motion_event),NULL);
    SetMouseWheelCB(area);
    pack_widget(area); gtk_widget_set_hexpand(area,TRUE); gtk_widget_set_vexpand(area,TRUE); return area;
}
void SetButtonDownCB(Widget w,MouseButtonCB cb){down_cb=cb;}
void SetButtonUpCB(Widget w,MouseButtonCB cb){up_cb=cb;}
void SetMouseMotionCB(Widget w,MotionCB cb){motion_cb=cb;}
void SetMouseWheelCB(Widget w){gtk_widget_add_events(w,GDK_SCROLL_MASK|GDK_SMOOTH_SCROLL_MASK);g_signal_connect(w,"scroll-event",G_CALLBACK(scroll_event),NULL);}
void SetWidgetPos(Widget w,int p1,Widget from1,int p2,Widget from2){
    int x,y;
    if(!w||!GTK_IS_WIDGET(w)||current_parent!=grid||gtk_widget_get_parent(w)!=grid)return;
    x=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(w),"batz-grid-x"));
    y=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(w),"batz-grid-y"));
    if(from1&&GTK_IS_WIDGET(from1)&&gtk_widget_get_parent(from1)==grid){
        int fx=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(from1),"batz-grid-x"));
        int fy=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(from1),"batz-grid-y"));
        if(p1==PLACE_RIGHT){x=fx+1;y=fy;}
        else if(p1==PLACE_UNDER){x=fx;y=fy+1;}
    }
    if(from2&&GTK_IS_WIDGET(from2)&&gtk_widget_get_parent(from2)==grid){
        int fx=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(from2),"batz-grid-x"));
        int fy=GPOINTER_TO_INT(g_object_get_data(G_OBJECT(from2),"batz-grid-y"));
        if(p2==PLACE_UNDER){x=fx;y=fy+1;}
        else if(p2==PLACE_RIGHT){x=fx+1;y=fy;}
    }
    /* Removing the only container reference would destroy the widget. */
    g_object_ref(w);
    gtk_container_remove(GTK_CONTAINER(grid),w);
    gtk_grid_attach(GTK_GRID(grid),w,x,y,1,1);
    g_object_set_data(G_OBJECT(w),"batz-grid-x",GINT_TO_POINTER(x));
    g_object_set_data(G_OBJECT(w),"batz-grid-y",GINT_TO_POINTER(y));
    g_object_unref(w);
}
void SetWidgetGridPosition(Widget w,int column,int row,int width,int height){
    if(!w||!GTK_IS_WIDGET(w)||current_parent!=grid||gtk_widget_get_parent(w)!=grid||width<1||height<1)return;
    g_object_ref(w);
    gtk_container_remove(GTK_CONTAINER(grid),w);
    gtk_grid_attach(GTK_GRID(grid),w,column,row,width,height);
    g_object_set_data(G_OBJECT(w),"batz-grid-x",GINT_TO_POINTER(column));
    g_object_set_data(G_OBJECT(w),"batz-grid-y",GINT_TO_POINTER(row));
    g_object_unref(w);
}
void SetMenuItemChecked(Widget w,int state){if(w){const char *label=g_object_get_data(G_OBJECT(w),"phobos-label");g_object_set_data(G_OBJECT(w),"phobos-checked",GINT_TO_POINTER(state!=0));if(label&&GTK_IS_MENU_ITEM(w)){char *marked=state?g_strconcat("✓  ",label,NULL):g_strdup(label);gtk_menu_item_set_label(GTK_MENU_ITEM(w),marked);g_free(marked);}}}
void SetWidgetSensitive(Widget w,int sensitive){if(w)gtk_widget_set_sensitive(GTK_WIDGET(w),sensitive!=0);}
int GetMenuItemChecked(Widget w){return w?GPOINTER_TO_INT(g_object_get_data(G_OBJECT(w),"phobos-checked")):0;}
//void GetStandardColors(void){palette[0]=(GdkRGBA){1,1,1,1};palette[1]=(GdkRGBA){0,0,0,1};palette[2]=(GdkRGBA){1,0,0,1};palette[3]=(GdkRGBA){0,1,0,1};palette[4]=(GdkRGBA){0,0,1,1};palette[5]=(GdkRGBA){1,1,0,1};}
void GetStandardColors(void){palette[0]=(GdkRGBA){1,1,1,1};palette[1]=(GdkRGBA){0,0,0,1};palette[2]=(GdkRGBA){0,0,1,1};palette[3]=(GdkRGBA){1,0,0,1};palette[4]=(GdkRGBA){0,1,0,1};palette[5]=(GdkRGBA){1,1,0,1};}
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
void SetWidgetState(Widget w,int s){gtk_widget_set_sensitive(w,s);}
int GetWidgetState(Widget w){return gtk_widget_get_sensitive(w);}
void SetLabel(Widget w,char*t){if(GTK_IS_LABEL(w))gtk_label_set_text(GTK_LABEL(w),t);else if(GTK_IS_MENU_ITEM(w))gtk_menu_item_set_label(GTK_MENU_ITEM(w),t);}
char *GetString(char*p,char*d){static char answer[4096];GtkWidget*dialog,*entry;dialog=gtk_dialog_new_with_buttons(p?p:"Saisie",window?GTK_WINDOW(window):NULL,GTK_DIALOG_MODAL,"Annuler",GTK_RESPONSE_CANCEL,"Valider",GTK_RESPONSE_ACCEPT,NULL);entry=gtk_entry_new();if(d)gtk_entry_set_text(GTK_ENTRY(entry),d);gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog))),entry);gtk_widget_show_all(dialog);answer[0]='\0';if(gtk_dialog_run(GTK_DIALOG(dialog))==GTK_RESPONSE_ACCEPT)g_strlcpy(answer,gtk_entry_get_text(GTK_ENTRY(entry)),sizeof(answer));gtk_widget_destroy(dialog);return answer;}
int GetYesNo(char*q){GtkWidget*dialog=gtk_message_dialog_new(window?GTK_WINDOW(window):NULL,GTK_DIALOG_MODAL,GTK_MESSAGE_QUESTION,GTK_BUTTONS_YES_NO,"%s",q?q:"");int response=gtk_dialog_run(GTK_DIALOG(dialog));gtk_widget_destroy(dialog);return response==GTK_RESPONSE_YES;}
char *GetSaveFile(char *suggested_name, const char *initial_folder){static char selected[4096];GtkWidget*d=gtk_file_chooser_dialog_new("Enregistrer le dessin",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_SAVE,"Annuler",GTK_RESPONSE_CANCEL,"Enregistrer",GTK_RESPONSE_ACCEPT,NULL);gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(d),TRUE);if(initial_folder&&*initial_folder)gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(d),initial_folder);if(suggested_name&&*suggested_name)gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(d),suggested_name);selected[0]='\0';if(gtk_dialog_run(GTK_DIALOG(d))==GTK_RESPONSE_ACCEPT){char *filename=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(d));if(filename){g_strlcpy(selected,filename,sizeof(selected));g_free(filename);}}gtk_widget_destroy(d);return selected;}
int GLOpenDisplay(int argc,char **argv,int *attributes){(void)attributes;return OpenDisplay(argc,argv);}
Widget MakeWindow(char *name,char *display,int exclusive){GtkWidget*d; (void)display;(void)exclusive;d=gtk_window_new(GTK_WINDOW_TOPLEVEL);gtk_window_set_title(GTK_WINDOW(d),name?name:"batz");gtk_window_set_default_size(GTK_WINDOW(d),760,560);GtkWidget*b=gtk_box_new(GTK_ORIENTATION_VERTICAL,4);gtk_container_add(GTK_CONTAINER(d),b);dialog_window=d;current_parent=b;return d;}
void SetCurrentWindow(Widget w){if(w==NULL){current_parent=grid?grid:vbox;dialog_window=NULL;}else{dialog_window=w;current_parent=gtk_bin_get_child(GTK_BIN(w));}}
void CloseWindow(void){if(dialog_window)gtk_widget_destroy(dialog_window);dialog_window=NULL;current_parent=vbox;if(gtk_main_level()>0)gtk_main_quit();}
static GtkWidget *pack_widget(GtkWidget*w){if(current_parent==grid){gtk_grid_attach(GTK_GRID(grid),w,0,next_widget_row++,1,1);g_object_set_data(G_OBJECT(w),"batz-grid-x",GINT_TO_POINTER(0));g_object_set_data(G_OBJECT(w),"batz-grid-y",GINT_TO_POINTER(next_widget_row-1));}else if(current_parent&&GTK_IS_BOX(current_parent))gtk_box_pack_start(GTK_BOX(current_parent),w,FALSE,FALSE,2);return w;}
static void button_event(GtkWidget*w,gpointer p){ButtonCB cb=(ButtonCB)g_object_get_data(G_OBJECT(w),"batz-cb");if(cb)cb(w,g_object_get_data(G_OBJECT(w),"batz-data"));}
Widget MakeButton(char *label,ButtonCB cb,void*data){GtkWidget*w=gtk_button_new_with_label(label?label:"");g_object_set_data(G_OBJECT(w),"batz-cb",(gpointer)cb);g_object_set_data(G_OBJECT(w),"batz-data",data);if(cb)g_signal_connect(w,"clicked",G_CALLBACK(button_event),NULL);return pack_widget(w);}
Widget MakeLabel(char*text){return pack_widget(gtk_label_new(text?text:""));}
static void toggle_event(GtkWidget*w,gpointer p){ButtonCB cb=(ButtonCB)g_object_get_data(G_OBJECT(w),"batz-cb");if(cb)cb(w,g_object_get_data(G_OBJECT(w),"batz-data"));}
Widget MakeToggle(char*t,int state,Widget parent,ButtonCB cb,void*d){GtkWidget*w=gtk_check_button_new_with_label(t?t:"");(void)parent;gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(w),state);g_object_set_data(G_OBJECT(w),"batz-cb",(gpointer)cb);g_object_set_data(G_OBJECT(w),"batz-data",d);if(cb)g_signal_connect(w,"toggled",G_CALLBACK(toggle_event),NULL);return pack_widget(w);}
void SetToggleState(Widget w,int s){gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(w),s);}
int GetToggleState(Widget w){return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w));}
static void entry_event(GtkWidget*w,gpointer p){StringCB cb=(StringCB)g_object_get_data(G_OBJECT(w),"batz-cb");if(cb)cb(w,(char*)gtk_entry_get_text(GTK_ENTRY(w)),g_object_get_data(G_OBJECT(w),"batz-data"));}
Widget MakeStringEntry(char*t,int width,StringCB cb,void*d){GtkWidget*w=gtk_entry_new();if(t)gtk_entry_set_text(GTK_ENTRY(w),t);gtk_entry_set_width_chars(GTK_ENTRY(w),width>0?width/8:20);g_object_set_data(G_OBJECT(w),"batz-cb",(gpointer)cb);g_object_set_data(G_OBJECT(w),"batz-data",d);if(cb)g_signal_connect(w,"activate",G_CALLBACK(entry_event),NULL);last_entry=w;return pack_widget(w);}
void SetStringEntry(Widget w,char*t){gtk_entry_set_text(GTK_ENTRY(w),t?t:"");}
char*GetStringEntry(Widget w){return (char*)gtk_entry_get_text(GTK_ENTRY(w));}
static void scale_event(GtkRange*r,gpointer p){ScrollCB cb=(ScrollCB)g_object_get_data(G_OBJECT(r),"batz-cb");if(cb)cb(GTK_WIDGET(r),(float)gtk_range_get_value(r),g_object_get_data(G_OBJECT(r),"batz-data"));}
static Widget make_scale(int orientation,int len,ScrollCB cb,void*d){GtkWidget*w=gtk_scale_new_with_range(orientation,0,1,.01);gtk_widget_set_size_request(w,orientation==GTK_ORIENTATION_HORIZONTAL?len:-1,orientation==GTK_ORIENTATION_VERTICAL?-1:24);if(orientation==GTK_ORIENTATION_VERTICAL)gtk_widget_set_vexpand(w,TRUE);gtk_scale_set_draw_value(GTK_SCALE(w),FALSE);g_object_set_data(G_OBJECT(w),"batz-cb",(gpointer)cb);g_object_set_data(G_OBJECT(w),"batz-data",d);g_signal_connect(w,"value-changed",G_CALLBACK(scale_event),NULL);return pack_widget(w);}
Widget MakeHorizScrollbar(int n,ScrollCB cb,void*d){return make_scale(GTK_ORIENTATION_HORIZONTAL,n,cb,d);}
Widget MakeVertScrollbar(int n,ScrollCB cb,void*d){return make_scale(GTK_ORIENTATION_VERTICAL,n,cb,d);}
void SetScrollbar(Widget w,float where,float max,float shown){gtk_range_set_range(GTK_RANGE(w),0,max);gtk_range_set_value(GTK_RANGE(w),where);(void)shown;}
static void list_event(GtkListBox*b,GtkListBoxRow*r,gpointer d){ListCB cb=(ListCB)g_object_get_data(G_OBJECT(b),"batz-cb");if(cb&&r){GtkWidget*l=gtk_bin_get_child(GTK_BIN(r));cb(GTK_WIDGET(b),(char*)gtk_label_get_text(GTK_LABEL(l)),gtk_list_box_row_get_index(r),g_object_get_data(G_OBJECT(b),"batz-data"));}}
Widget MakeScrollList(char**items,int width,int height,ListCB cb,void*d){GtkWidget*sc=gtk_scrolled_window_new(NULL,NULL),*b=gtk_list_box_new();gtk_container_add(GTK_CONTAINER(sc),b);gtk_widget_set_size_request(sc,width,height);g_object_set_data(G_OBJECT(b),"batz-cb",(gpointer)cb);g_object_set_data(G_OBJECT(b),"batz-data",d);if(items)for(int i=0;items[i];i++)gtk_container_add(GTK_CONTAINER(b),gtk_label_new(items[i]));g_signal_connect(b,"row-selected",G_CALLBACK(list_event),NULL);last_list=b;pack_widget(sc);return b;}
void SetCurrentListItem(Widget w,int i){GtkListBoxRow*r=gtk_list_box_get_row_at_index(GTK_LIST_BOX(w),i);if(r)gtk_list_box_select_row(GTK_LIST_BOX(w),r);}
int GetCurrentListItem(Widget w){GtkListBoxRow*r=gtk_list_box_get_selected_row(GTK_LIST_BOX(w));return r?gtk_list_box_row_get_index(r):-1;}
void ChangeScrollList(Widget w,char**items){GList*rows=gtk_container_get_children(GTK_CONTAINER(w));for(GList*p=rows;p;p=p->next)gtk_widget_destroy(GTK_WIDGET(p->data));g_list_free(rows);if(items)for(int i=0;items[i];i++)gtk_container_add(GTK_CONTAINER(w),gtk_label_new(items[i]));gtk_widget_show_all(w);}
void SetWidgetFont(Widget w,XFont f){if(w&&f)gtk_widget_override_font(w,f);}
XFont GetFont(char*n){return pango_font_description_from_string(n?n:"Sans 10");}
void FreeFont(XFont f){if(f)pango_font_description_free(f);}
void AttachEdge(Widget w,int edge,int to){(void)w;(void)edge;(void)to;}
void SetFgColor(Widget w,int c){(void)w;default_fg=c;} void SetBgColor(Widget w,int c){(void)w;default_bg=c;} void SetBorderColor(Widget w,int c){(void)w;(void)c;}
int GetFgColor(Widget w){(void)w;return default_fg;} int GetBgColor(Widget w){(void)w;return default_bg;}
void DrawPixel(int x,int y){DrawLine(x,y,x,y);} int GetPixel(int x,int y){(void)x;(void)y;return BLACK;}
void ScrollDrawArea(int dx,int dy,int x1,int y1,int x2,int y2){(void)dx;(void)dy;(void)x1;(void)y1;(void)x2;(void)y2;if(area)gtk_widget_queue_draw(area);}
void AddTimeOut(unsigned long ms,GeneralCB cb,void*d){if(cb)g_timeout_add(ms,(GSourceFunc)cb,d);}
void AddReadCallback(int fd,IOCallback cb,void*d){(void)fd;(void)cb;(void)d;} void AddWriteCallback(int fd,IOCallback cb,void*d){(void)fd;(void)cb;(void)d;}
void FreeStandardColors(void){} void SetWidgetBitmap(Widget w,char*d,int x,int y){(void)w;(void)d;(void)x;(void)y;}
