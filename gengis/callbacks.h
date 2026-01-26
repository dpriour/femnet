/* Geometry Editor - Prototypes des callbacks
 * callbacks.h
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "main.h"

/* Type générique pour Widget (compatible libsx et GTK) */
typedef void* Widget;

/* Callbacks pour les boutons */
void mode_panel(Widget w, void *data);
void mode_cable(Widget w, void *data);
void mode_link(Widget w, void *data);
void mode_align(Widget w, void *data);
void mode_modify_uv(Widget w, void *data);
void mode_modify_panel(Widget w, void *data);
void mode_modify_z(Widget w, void *data);
void clear_all(Widget w, void *data);
void quit_program(Widget w, void *data);
void set_view_plane(Widget w, void *data);

/* Callbacks pour l'alignement */
void align_modify_x(Widget w, void *data);
void align_modify_y(Widget w, void *data);
void align_modify_z(Widget w, void *data);
void align_modify_type(Widget w, void *data);

/* Callbacks pour le zoom */
void zoom_in(Widget w, void *data);
void zoom_out(Widget w, void *data);
void zoom_reset(Widget w, void *data);
void zoom_pixel_m(Widget w, void *data);

/* Callbacks pour l'affichage */
void toggle_points(Widget w, void *data);
void toggle_panels(Widget w, void *data);
void toggle_cables(Widget w, void *data);
void toggle_links(Widget w, void *data);
void toggle_axes(Widget w, void *data);

/* Callbacks pour l'affichage des numéros */
void toggle_point_numbers(Widget w, void *data);
void toggle_panel_numbers(Widget w, void *data);
void toggle_cable_numbers(Widget w, void *data);
void toggle_link_numbers(Widget w, void *data);

/* Callbacks pour l'affichage des types */
void toggle_point_types(Widget w, void *data);
void toggle_panel_types(Widget w, void *data);
void toggle_edge_types(Widget w, void *data);
void toggle_cable_types(Widget w, void *data);

/* Callbacks pour File */
void save_file(Widget w, void *data);
void load_file(Widget w, void *data);
void load_specific_file(char *filename, MyProgram *me);

/* Callbacks pour les événements souris */
void button_down(Widget w, int button, int x, int y, void *data);
void button_up(Widget w, int button, int x, int y, void *data);
void mouse_motion(Widget w, int x, int y, void *data);

/* Callback pour le redessin */
void redisplay(Widget w, int width, int height, void *data);

/* Fonctions auxiliaires */
int find_point(MyProgram *me, int x, int y, int tolerance);
int find_closest_point(MyProgram *me, int x, int y);
void add_point(MyProgram *me, int x, int y);
void draw_everything(MyProgram *me);

/* Fonctions de conversion de coordonnées */
void screen_to_world(MyProgram *me, int sx, int sy, int *wx, int *wy, int *wz);
void world_to_screen(MyProgram *me, int wx, int wy, int wz, int *sx, int *sy);

/* Fonctions pour undo (Ctrl+Z) */
void save_state(MyProgram *me);
void undo_action(MyProgram *me);
void key_pressed(Widget w, char *input, int up_or_down, void *data);

/* Fonction pour créer le menu de chargement de fichiers */
int create_file_load_menu(Widget parent_menu, MyProgram *me);

#endif
