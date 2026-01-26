/* Gengis - Main GTK 3
 * Point d'entrée avec GTK 3 pour remplacer libsx
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <dirent.h>
#include "main.h"
#include "callbacks.h"
#include "gtk3_drawing.h"
#include <locale.h>

#define X_SIZE 800
#define Y_SIZE 600

/* Pointeur global vers MyProgram pour les callbacks GTK */
static MyProgram *global_me = NULL;

/* Widget global pour le drawing area (pour queue_draw) */
static GtkWidget *global_drawing_area = NULL;

/* =================================================================
 * FONCTIONS WRAPPER POUR LES CALLBACKS
 * ================================================================= */

/* Variable globale pour stocker la fenêtre principale */
static GtkWidget *g_main_window = NULL;

/* Structure pour passer les données au callback de réponse */
typedef struct {
    GtkWidget *dialog;
    GtkWidget *entry;
    char **result_ptr;
    char *default_value;
    gboolean done;
} DialogData;

/* Callback de réponse pour GetString - version sans gtk_dialog_run() */
static void on_getstring_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
    DialogData *data = (DialogData *)user_data;

    printf("DEBUG on_getstring_response: response_id=%d\n", response_id);
    fflush(stdout);

    if (response_id == GTK_RESPONSE_ACCEPT) {
        const char *text = gtk_entry_get_text(GTK_ENTRY(data->entry));
        printf("DEBUG on_getstring_response: User accepted, text='%s'\n",
               text ? text : "(null)");
        fflush(stdout);

        if (text && strlen(text) > 0) {
            *(data->result_ptr) = strdup(text);
        } else if (data->default_value) {
            *(data->result_ptr) = strdup(data->default_value);
        }
    } else {
        printf("DEBUG on_getstring_response: User cancelled\n");
        fflush(stdout);
        *(data->result_ptr) = NULL;
    }

    data->done = TRUE;
    gtk_widget_destroy(data->dialog);
}

/* Callback pour empêcher la fermeture du dialog par delete-event */
static gboolean on_dialog_delete_event(GtkWidget *widget, GdkEvent *event, gpointer user_data)
{
    DialogData *data = (DialogData *)user_data;
    printf("DEBUG on_dialog_delete_event: received\n");
    fflush(stdout);

    /* Traiter comme un Cancel */
    *(data->result_ptr) = NULL;
    data->done = TRUE;
    gtk_widget_destroy(widget);
    return TRUE;  /* TRUE = on a géré l'événement */
}

/* Fonction wrapper pour GetString - version avec event loop personnalisée */
char* GetString(char *prompt, char *default_value)
{
    GtkWidget *dialog, *content_area, *entry;
    char *result = NULL;
    DialogData data;

    printf("DEBUG GetString: Starting, prompt='%s', default='%s'\n",
           prompt ? prompt : "(null)",
           default_value ? default_value : "(null)");
    fflush(stdout);

    /* Créer un dialog simple */
    printf("DEBUG GetString: Creating dialog...\n");
    fflush(stdout);

    dialog = gtk_dialog_new_with_buttons(
        "Input Required",
        g_main_window ? GTK_WINDOW(g_main_window) : NULL,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "_Cancel", GTK_RESPONSE_CANCEL,
        "_OK", GTK_RESPONSE_ACCEPT,
        NULL);

    /* Obtenir l'area de contenu */
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_set_border_width(GTK_CONTAINER(content_area), 10);

    /* Ajouter le label */
    GtkWidget *label = gtk_label_new(prompt);
    gtk_box_pack_start(GTK_BOX(content_area), label, FALSE, FALSE, 5);

    /* Ajouter l'entry */
    entry = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(entry), 50);
    if (default_value) {
        gtk_entry_set_text(GTK_ENTRY(entry), default_value);
    }
    gtk_entry_set_activates_default(GTK_ENTRY(entry), TRUE);
    gtk_box_pack_start(GTK_BOX(content_area), entry, FALSE, FALSE, 5);

    /* Définir le bouton par défaut */
    gtk_dialog_set_default_response(GTK_DIALOG(dialog), GTK_RESPONSE_ACCEPT);

    /* Préparer la structure de données */
    data.dialog = dialog;
    data.entry = entry;
    data.result_ptr = &result;
    data.default_value = default_value;
    data.done = FALSE;

    /* Connecter les signaux */
    g_signal_connect(dialog, "response",
                     G_CALLBACK(on_getstring_response), &data);
    g_signal_connect(dialog, "delete-event",
                     G_CALLBACK(on_dialog_delete_event), &data);

    printf("DEBUG GetString: Showing dialog...\n");
    fflush(stdout);

    /* Montrer tous les widgets */
    gtk_widget_show_all(dialog);

    /* Focus sur l'entry */
    gtk_widget_grab_focus(entry);

    printf("DEBUG GetString: Entering event loop until dialog closes...\n");
    fflush(stdout);

    /* Attendre que le dialog soit fermé en traitant les événements manuellement */
    while (!data.done) {
        gtk_main_iteration();
    }

    printf("DEBUG GetString: Dialog closed, result=%p\n", (void*)result);
    fflush(stdout);

    return result;
}

/* =================================================================
 * CALLBACKS POUR LES ÉVÉNEMENTS GTK
 * ================================================================= */

/* Callback de dessin GTK (remplace redisplay de libsx) */
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    MyProgram *me = (MyProgram *)data;

    /* Définir le contexte Cairo pour les fonctions de dessin */
    set_cairo_context(cr);

    /* Appeler la fonction de dessin existante */
    draw_everything(me);

    return FALSE;
}

/* Callback pour clic souris */
static gboolean on_button_press(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    MyProgram *me = (MyProgram *)data;

    /* Convertir les boutons GTK en format compatible libsx */
    int button = event->button;

    /* GTK utilise scroll events séparés, mais on garde cette structure */
    button_down(widget, button, (int)event->x, (int)event->y, me);

    gtk_widget_queue_draw(widget);
    return TRUE;
}

/* Callback pour relâchement souris */
static gboolean on_button_release(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    MyProgram *me = (MyProgram *)data;

    button_up(widget, event->button, (int)event->x, (int)event->y, me);

    gtk_widget_queue_draw(widget);
    return TRUE;
}

/* Callback pour mouvement souris */
static gboolean on_motion_notify(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
    MyProgram *me = (MyProgram *)data;

    mouse_motion(widget, (int)event->x, (int)event->y, me);

    gtk_widget_queue_draw(widget);
    return TRUE;
}

/* Callback pour molette souris (zoom) */
static gboolean on_scroll_event(GtkWidget *widget, GdkEventScroll *event, gpointer data)
{
    MyProgram *me = (MyProgram *)data;

    /* Simuler les boutons 4 et 5 de X11 utilisés par libsx */
    if (event->direction == GDK_SCROLL_UP) {
        button_down(widget, 4, (int)event->x, (int)event->y, me);
    } else if (event->direction == GDK_SCROLL_DOWN) {
        button_down(widget, 5, (int)event->x, (int)event->y, me);
    }

    gtk_widget_queue_draw(widget);
    return TRUE;
}

/* Callback pour touches clavier */
static gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    MyProgram *me = (MyProgram *)data;
    char key_str[32];

    /* Convertir la touche en string */
    if (event->keyval == GDK_KEY_z || event->keyval == GDK_KEY_Z) {
        /* Ctrl+Z pour undo */
        if (event->state & GDK_CONTROL_MASK) {
            key_str[0] = 'z';
            key_str[1] = '\0';
            key_pressed(widget, key_str, 0, me);
            gtk_widget_queue_draw(widget);
        }
    }

    return TRUE;
}

/* =================================================================
 * CALLBACKS POUR LES MENUS (WRAPPERS)
 * ================================================================= */

/* Les callbacks de menu GTK n'utilisent pas Widget mais GtkWidget */
static void menu_save_file(GtkWidget *w, gpointer data)
{
    save_file(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_quit(GtkWidget *w, gpointer data)
{
    gtk_main_quit();
}

/* Wrapper pour load_specific_file */
static void menu_load_specific_file(GtkWidget *w, gpointer data)
{
    char *filename = (char *)data;
    load_specific_file(filename, global_me);
    gtk_widget_queue_draw(global_drawing_area);
}

/* Actions menu callbacks */
static void menu_mode_panel(GtkWidget *w, gpointer data)
{
    mode_panel(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_mode_cable(GtkWidget *w, gpointer data)
{
    mode_cable(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_mode_link(GtkWidget *w, gpointer data)
{
    mode_link(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_mode_modify_uv(GtkWidget *w, gpointer data)
{
    mode_modify_uv(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

//static void menu_mode_modify_panel(GtkWidget *w, gpointer data)
//{
    //mode_modify_panel(w, data);
    //gtk_widget_queue_draw(global_drawing_area);
//}

static void menu_set_view_plane(GtkWidget *w, gpointer data)
{
    set_view_plane(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_clear_all(GtkWidget *w, gpointer data)
{
    clear_all(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

/* Zoom menu callbacks */
static void menu_zoom_reset(GtkWidget *w, gpointer data)
{
    zoom_reset(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_zoom_pixel_m(GtkWidget *w, gpointer data)
{
    zoom_pixel_m(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

/* Alignment menu callbacks */
static void menu_mode_align(GtkWidget *w, gpointer data)
{
    mode_align(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_align_modify_x(GtkWidget *w, gpointer data)
{
    align_modify_x(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_align_modify_y(GtkWidget *w, gpointer data)
{
    align_modify_y(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_align_modify_z(GtkWidget *w, gpointer data)
{
    align_modify_z(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_align_modify_type(GtkWidget *w, gpointer data)
{
    align_modify_type(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

/* Display menu callbacks */
static void menu_toggle_points(GtkWidget *w, gpointer data)
{
    toggle_points(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_panels(GtkWidget *w, gpointer data)
{
    toggle_panels(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_cables(GtkWidget *w, gpointer data)
{
    toggle_cables(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_links(GtkWidget *w, gpointer data)
{
    toggle_links(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_axes(GtkWidget *w, gpointer data)
{
    toggle_axes(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

/* Numbers menu callbacks */
static void menu_toggle_point_numbers(GtkWidget *w, gpointer data)
{
    toggle_point_numbers(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_panel_numbers(GtkWidget *w, gpointer data)
{
    toggle_panel_numbers(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_cable_numbers(GtkWidget *w, gpointer data)
{
    toggle_cable_numbers(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_link_numbers(GtkWidget *w, gpointer data)
{
    toggle_link_numbers(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

/* Types menu callbacks */
static void menu_toggle_point_types(GtkWidget *w, gpointer data)
{
    toggle_point_types(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_panel_types(GtkWidget *w, gpointer data)
{
    toggle_panel_types(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_edge_types(GtkWidget *w, gpointer data)
{
    toggle_edge_types(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

static void menu_toggle_cable_types(GtkWidget *w, gpointer data)
{
    toggle_cable_types(w, data);
    gtk_widget_queue_draw(global_drawing_area);
}

/* =================================================================
 * CRÉATION DES MENUS
 * ================================================================= */

/* Créer le menu de chargement de fichiers */
static void create_load_file_submenu(GtkWidget *parent_menu, MyProgram *me)
{
    DIR *dir;
    struct dirent *entry;
    GtkWidget *item;

    /* Scanner le répertoire courant pour les fichiers .dat */
    dir = opendir(".");
    if (dir == NULL) return;

    while ((entry = readdir(dir)) != NULL) {
        int len = strlen(entry->d_name);
        if (len > 4 && strcmp(entry->d_name + len - 4, ".dat") == 0) {
            char *filename = strdup(entry->d_name);
            item = gtk_menu_item_new_with_label(filename);
            g_signal_connect(item, "activate",
                           G_CALLBACK(menu_load_specific_file), filename);
            gtk_menu_shell_append(GTK_MENU_SHELL(parent_menu), item);
        }
    }

    closedir(dir);
}

/* Créer la barre de menus complète */
static GtkWidget* create_menubar(MyProgram *me)
{
    GtkWidget *menubar, *menu, *submenu, *item;

    menubar = gtk_menu_bar_new();

    /* ===== Menu File ===== */
    item = gtk_menu_item_new_with_label("File");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);

    /* Save */
    item = gtk_menu_item_new_with_label("Save");
    g_signal_connect(item, "activate", G_CALLBACK(menu_save_file), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    /* Load file (submenu) */
    item = gtk_menu_item_new_with_label("Load file");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);
    submenu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), submenu);
    create_load_file_submenu(submenu, me);

    /* Quit */
    item = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(item, "activate", G_CALLBACK(menu_quit), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    /* ===== Menu Actions ===== */
    item = gtk_menu_item_new_with_label("Actions");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);

    item = gtk_menu_item_new_with_label("Create Panels");
    g_signal_connect(item, "activate", G_CALLBACK(menu_mode_panel), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Create Cables");
    g_signal_connect(item, "activate", G_CALLBACK(menu_mode_cable), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Create Links");
    g_signal_connect(item, "activate", G_CALLBACK(menu_mode_link), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Modify UV");
    g_signal_connect(item, "activate", G_CALLBACK(menu_mode_modify_uv), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    //item = gtk_menu_item_new_with_label("Modify panel");
    //g_signal_connect(item, "activate", G_CALLBACK(menu_mode_modify_panel), me);
    //gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("View Plane...");
    g_signal_connect(item, "activate", G_CALLBACK(menu_set_view_plane), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Clear All");
    g_signal_connect(item, "activate", G_CALLBACK(menu_clear_all), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    /* ===== Menu Zoom ===== */
    item = gtk_menu_item_new_with_label("Zoom");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);

    item = gtk_menu_item_new_with_label("Set Zoom...");
    g_signal_connect(item, "activate", G_CALLBACK(menu_zoom_reset), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Set Zoom pixel/m");
    g_signal_connect(item, "activate", G_CALLBACK(menu_zoom_pixel_m), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    /* ===== Menu Alignment ===== */
    item = gtk_menu_item_new_with_label("Alignment");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);

    item = gtk_menu_item_new_with_label("Alignment Mode");
    g_signal_connect(item, "activate", G_CALLBACK(menu_mode_align), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Modify X");
    g_signal_connect(item, "activate", G_CALLBACK(menu_align_modify_x), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Modify Y");
    g_signal_connect(item, "activate", G_CALLBACK(menu_align_modify_y), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Modify Z");
    g_signal_connect(item, "activate", G_CALLBACK(menu_align_modify_z), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    //item = gtk_menu_item_new_with_label("Modify Z");
    //g_signal_connect(item, "activate", G_CALLBACK(menu_mode_modify_z), me);
    //gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Modify Type");
    g_signal_connect(item, "activate", G_CALLBACK(menu_align_modify_type), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    /* ===== Menu Display ===== */
    item = gtk_menu_item_new_with_label("Display");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);

    item = gtk_menu_item_new_with_label("Points");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_points), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Panels");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_panels), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Cables");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_cables), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Interconnections");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_links), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Axes");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_axes), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    /* ===== Menu Numbers ===== */
    item = gtk_menu_item_new_with_label("Numbers");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);

    item = gtk_menu_item_new_with_label("Point Numbers");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_point_numbers), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Panel Numbers");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_panel_numbers), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Cable Numbers");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_cable_numbers), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Interconnection Numbers");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_link_numbers), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    /* ===== Menu Types ===== */
    item = gtk_menu_item_new_with_label("Types");
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), item);

    menu = gtk_menu_new();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(item), menu);

    item = gtk_menu_item_new_with_label("Point Types");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_point_types), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Panel Types");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_panel_types), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Edge Types");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_edge_types), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    item = gtk_menu_item_new_with_label("Cable Types");
    g_signal_connect(item, "activate", G_CALLBACK(menu_toggle_cable_types), me);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), item);

    return menubar;
}

/* =================================================================
 * CONFIGURATION DES ÉVÉNEMENTS
 * ================================================================= */

static void setup_events(GtkWidget *drawing_area, MyProgram *me)
{
    /* Activer les événements souris et clavier */
    gtk_widget_add_events(drawing_area,
        GDK_BUTTON_PRESS_MASK |
        GDK_BUTTON_RELEASE_MASK |
        GDK_POINTER_MOTION_MASK |
        GDK_SCROLL_MASK |
        GDK_KEY_PRESS_MASK);

    /* Connecter les signaux */
    g_signal_connect(drawing_area, "draw",
                    G_CALLBACK(on_draw_event), me);
    g_signal_connect(drawing_area, "button-press-event",
                    G_CALLBACK(on_button_press), me);
    g_signal_connect(drawing_area, "button-release-event",
                    G_CALLBACK(on_button_release), me);
    g_signal_connect(drawing_area, "motion-notify-event",
                    G_CALLBACK(on_motion_notify), me);
    g_signal_connect(drawing_area, "scroll-event",
                    G_CALLBACK(on_scroll_event), me);

    /* Permettre au drawing area de recevoir le focus clavier */
    gtk_widget_set_can_focus(drawing_area, TRUE);
    g_signal_connect(drawing_area, "key-press-event",
                    G_CALLBACK(on_key_press), me);
}

/* =================================================================
 * FONCTION MAIN
 * ================================================================= */

int main(int argc, char **argv)
{
    MyProgram mydata;
    GtkWidget *window, *vbox, *menubar, *drawing_area;
    int i;

    /* Initialisation des données (copié depuis main.c original) */
    mydata.num_points = 0;
    mydata.num_panels = 0;
    mydata.num_cables = 0;
    mydata.num_links = 0;
    //mydata.current_mode = MODE_PANEL;
    mydata.current_mode = 0;	//do nothing by default
    mydata.current_poly = -1;
    mydata.temp_point = -1;
    mydata.selected_poly = -1;
    mydata.selected_edge = -1;
    mydata.draw_area_width = X_SIZE;
    mydata.draw_area_height = Y_SIZE;
    mydata.zoom_factor = 1.0;
    mydata.zoom_pixel_m = 1.0;
    mydata.pan_x = 0;
    mydata.pan_y = 0;
    mydata.is_panning = FALSE;
    mydata.last_mouse_x = 0;
    mydata.last_mouse_y = 0;
    mydata.selecting = FALSE;
    mydata.select_x1 = mydata.select_y1 = 0;
    mydata.select_x2 = mydata.select_y2 = 0;
    mydata.num_selected = 0;
    mydata.undo_count = 0;
    strcpy(mydata.current_filename, "geometry.dat");

    mydata.show_points = TRUE;
    mydata.show_panels = TRUE;
    mydata.show_cables = TRUE;
    mydata.show_links = TRUE;
    mydata.show_axes = FALSE;

    mydata.show_point_numbers = FALSE;
    mydata.show_panel_numbers = FALSE;
    mydata.show_cable_numbers = FALSE;
    mydata.show_link_numbers = FALSE;

    mydata.show_point_types = FALSE;
    mydata.show_panel_types = FALSE;
    mydata.show_edge_types = FALSE;
    mydata.show_cable_types = FALSE;

    mydata.view_plane = 3;

    for (i = 0; i < MAX_POINTS; i++) {
        mydata.points[i].used = FALSE;
        mydata.points[i].selected = FALSE;
        mydata.points[i].type = 1;
    }

    /* Sauvegarder pointeur global */
    global_me = &mydata;

    /* Initialisation GTK */
    gtk_init(&argc, &argv);
    
    /* Forcer le point décimal */
    setlocale(LC_NUMERIC, "C");

    /* Créer la fenêtre principale */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Gengis");
    gtk_window_set_default_size(GTK_WINDOW(window), X_SIZE + 20, Y_SIZE + 60);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    /* Sauvegarder la fenêtre principale pour GetString */
    g_main_window = window;

    /* Créer layout vertical */
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    /* Créer et ajouter la barre de menus */
    menubar = create_menubar(&mydata);
    gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

    /* Créer le drawing area */
    drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, X_SIZE, Y_SIZE);
    gtk_box_pack_start(GTK_BOX(vbox), drawing_area, TRUE, TRUE, 0);

    /* Sauvegarder pointeur global */
    global_drawing_area = drawing_area;

    /* Configurer les événements */
    setup_events(drawing_area, &mydata);

    /* Afficher l'interface */
    gtk_widget_show_all(window);

    /* Donner le focus au drawing area */
    gtk_widget_grab_focus(drawing_area);

    /* Messages de démarrage */
    printf("Gengis démarré (GTK 3)\n");
    printf("Mode par défaut: Création de paneles\n");
    printf("Cliquez pour ajouter des points\n");
    printf("Utilisez la molette pour zoomer/dézoomer\n");

    /* Boucle principale GTK */
    gtk_main();

    return 0;
}
