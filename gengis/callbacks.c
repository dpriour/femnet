/* Gengis - Callbacks
 * callbacks.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <dirent.h>
#include "main.h"
#include "callbacks.h"
#include "gtk3_drawing.h"

/* Prototypes de fonctions internes */
void dfs_interconnection(int node, int *visited, int adjacency[MAX_POINTS][MAX_POINTS],
                         int *component, int *comp_size, int num_points);

/* ===== GESTION DES FICHIERS DISPONIBLES ===== */

#define MAX_FILE_MENU_ITEMS 20
static char available_files[MAX_FILE_MENU_ITEMS][256];
static int num_available_files = 0;

/* Callbacks pour charger des files spécifiques depuis le menu */
void load_file_0(Widget w, void *data) { if (num_available_files > 0) load_specific_file(available_files[0], (MyProgram*)data); }
void load_file_1(Widget w, void *data) { if (num_available_files > 1) load_specific_file(available_files[1], (MyProgram*)data); }
void load_file_2(Widget w, void *data) { if (num_available_files > 2) load_specific_file(available_files[2], (MyProgram*)data); }
void load_file_3(Widget w, void *data) { if (num_available_files > 3) load_specific_file(available_files[3], (MyProgram*)data); }
void load_file_4(Widget w, void *data) { if (num_available_files > 4) load_specific_file(available_files[4], (MyProgram*)data); }
void load_file_5(Widget w, void *data) { if (num_available_files > 5) load_specific_file(available_files[5], (MyProgram*)data); }
void load_file_6(Widget w, void *data) { if (num_available_files > 6) load_specific_file(available_files[6], (MyProgram*)data); }
void load_file_7(Widget w, void *data) { if (num_available_files > 7) load_specific_file(available_files[7], (MyProgram*)data); }
void load_file_8(Widget w, void *data) { if (num_available_files > 8) load_specific_file(available_files[8], (MyProgram*)data); }
void load_file_9(Widget w, void *data) { if (num_available_files > 9) load_specific_file(available_files[9], (MyProgram*)data); }
void load_file_10(Widget w, void *data) { if (num_available_files > 10) load_specific_file(available_files[10], (MyProgram*)data); }
void load_file_11(Widget w, void *data) { if (num_available_files > 11) load_specific_file(available_files[11], (MyProgram*)data); }
void load_file_12(Widget w, void *data) { if (num_available_files > 12) load_specific_file(available_files[12], (MyProgram*)data); }
void load_file_13(Widget w, void *data) { if (num_available_files > 13) load_specific_file(available_files[13], (MyProgram*)data); }
void load_file_14(Widget w, void *data) { if (num_available_files > 14) load_specific_file(available_files[14], (MyProgram*)data); }
void load_file_15(Widget w, void *data) { if (num_available_files > 15) load_specific_file(available_files[15], (MyProgram*)data); }
void load_file_16(Widget w, void *data) { if (num_available_files > 16) load_specific_file(available_files[16], (MyProgram*)data); }
void load_file_17(Widget w, void *data) { if (num_available_files > 17) load_specific_file(available_files[17], (MyProgram*)data); }
void load_file_18(Widget w, void *data) { if (num_available_files > 18) load_specific_file(available_files[18], (MyProgram*)data); }
void load_file_19(Widget w, void *data) { if (num_available_files > 19) load_specific_file(available_files[19], (MyProgram*)data); }

/* NOTE: file_callbacks n'est plus utilisé avec GTK 3 - commenté pour éviter warning */
/*
typedef void (*FileLoadCallback)(Widget, void*);
static FileLoadCallback file_callbacks[MAX_FILE_MENU_ITEMS] = {
    load_file_0, load_file_1, load_file_2, load_file_3, load_file_4,
    load_file_5, load_file_6, load_file_7, load_file_8, load_file_9,
    load_file_10, load_file_11, load_file_12, load_file_13, load_file_14,
    load_file_15, load_file_16, load_file_17, load_file_18, load_file_19
};
*/

/* Fonction pour créer le menu de chargement de files */
/* NOTE: Cette fonction n'est plus utilisée avec GTK 3 */
/* Le menu est maintenant créé dans gtk3_main.c */
int create_file_load_menu(Widget parent_menu, MyProgram *me)
{
    /* Stub pour compatibilité - ne fait rien avec GTK 3 */
    /* La création du menu de chargement est gérée dans gtk3_main.c */
    return 0;
}

/* ===== CALLBACKS POUR LES BOUTONS DE MENU ===== */

void mode_panel(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->current_mode = MODE_PANEL;
    me->current_poly = -1;
    me->temp_point = -1;
    printf("Mode: Creating panels\n");
    printf("Click to add vertices. Double-click to close panel.\n");
}

void mode_cable(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->current_mode = MODE_CABLE;
    me->current_poly = -1;
    me->temp_point = -1;
    printf("Mode: Creating cables\n");
    printf("Click on two points (existing or new) to create a cable.\n");
}

void mode_link(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->current_mode = MODE_LINK;
    me->current_poly = -1;
    me->temp_point = -1;
    printf("Mode: Creating links\n");
    printf("Click on two existing points to create a link.\n");
}

void clear_all(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    int i;

    /* Sauvegarder l'état pour undo */
    save_state(me);

    me->num_points = 0;
    me->num_panels = 0;
    me->num_cables = 0;
    me->num_links = 0;
    me->current_poly = -1;
    me->temp_point = -1;

    for (i = 0; i < MAX_POINTS; i++) {
        me->points[i].used = FALSE;
    }

    printf("All cleared\n");
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void quit_program(Widget w, void *data)
{
    printf("Goodbye!\n");
    exit(0);
}

void set_view_plane(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    char *plane_str;
    int plane_value;

    plane_str = GetString("Choose view plane:\n1: Normal=X (window axes: Y,Z)\n2: Normal=Y (window axes: Z,X)\n3: Normal=Z (window axes: X,Y)", "3");

    if (!plane_str) {
        printf("Cancelled\n");
        return;
    }

    plane_value = atoi(plane_str);

    if (plane_value < 1 || plane_value > 3) {
        printf("Invalid value. Please enter 1, 2 or 3.\n");
        free(plane_str);
        return;
    }

    me->view_plane = plane_value;

    switch (plane_value) {
        case 1:
            printf("View plane set: Normal=X (window axes: Y,Z)\n");
            break;
        case 2:
            printf("View plane set: Normal=Y (window axes: Z,X)\n");
            break;
        case 3:
            printf("View plane set: Normal=Z (window axes: X,Y)\n");
            break;
    }

    free(plane_str);

    /* Redessiner */
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

/* ===== CALLBACKS POUR LES ÉVÉNEMENTS SOURIS ===== */

void button_down(Widget w, int button, int x, int y, void *data)
{
    MyProgram *me = (MyProgram *)data;
    int point_idx;

    /* Gérer le zoom avec la molette */
    if (button == 4) {  /* Molette vers le haut = Zoom In */
        me->zoom_factor *= 1.1;
        printf("Zoom: %.2fx\n", me->zoom_factor);
                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
        return;
    }
    if (button == 5) {  /* Molette vers le bas = Zoom Out */
        me->zoom_factor /= 1.1;
        if (me->zoom_factor < 0.1) me->zoom_factor = 0.1;
        printf("Zoom: %.2fx\n", me->zoom_factor);
                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
        return;
    }

    /* Gérer le panning avec bouton droit */
    if (button == 3) {  /* Bouton droit = Pan */
        me->is_panning = TRUE;
        me->last_mouse_x = x;
        me->last_mouse_y = y;
        printf("Pan mode enabled\n");
        return;
    }

    /* Bouton gauche (button == 1) pour les opérations normales */
    if (button != 1) return;

    switch (me->current_mode) {

    case MODE_MODIFY_UV:
        /* Détecter le côté de panele cliqué */
        {
            int wx, wy, wz;
            int i, j;
            int found = FALSE;
            int poly_idx = -1, edge_idx = -1;
            //double min_dist = 15.0;  /* tolérance de 15 pixels */
            Panel *poly1 = &me->panels[0];
            int p1_idx1 = poly1->points[0];
            int p2_idx1 = poly1->points[1];
                    double x1, y1, x2, y2, wx_2d, wy_2d;
                    switch (me->view_plane) {
                        case 1:  /* Normal=X, écran montre Y,Z */
                            x1 = me->points[p1_idx1].y;
                            y1 = me->points[p1_idx1].z;
                            x2 = me->points[p2_idx1].y;
                            y2 = me->points[p2_idx1].z;
                            break;
                        case 2:  /* Normal=Y, écran montre Z,X */
                            x1 = me->points[p1_idx1].z;
                            y1 = me->points[p1_idx1].x;
                            x2 = me->points[p2_idx1].z;
                            y2 = me->points[p2_idx1].x;
                            break;
                        case 3:  /* Normal=Z, écran montre X,Y */
                        default:
                            x1 = me->points[p1_idx1].x;
                            y1 = me->points[p1_idx1].y;
                            x2 = me->points[p2_idx1].x;
                            y2 = me->points[p2_idx1].y;
                            break;
                    }
            double min_dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            printf("min_dist %4.0lf\n",min_dist);

            screen_to_world(me, x, y, &wx, &wy, &wz);

            /* Chercher le côté le plus proche */
            for (i = 0; i < me->num_panels && !found; i++) {
                Panel *poly = &me->panels[i];
                for (j = 0; j < poly->num_points; j++) {
                    int p1_idx = poly->points[j];
                    int p2_idx = poly->points[(j+1) % poly->num_points];

                    /* Ne pas traiter le dernier côté si non fermé */
                    if (j == poly->num_points - 1 && !poly->closed) continue;

                    /* Extraire les bonnes coordonnées selon le plan de vue */

                    switch (me->view_plane) {
                        case 1:  /* Normal=X, écran montre Y,Z */
                            x1 = me->points[p1_idx].y;
                            y1 = me->points[p1_idx].z;
                            x2 = me->points[p2_idx].y;
                            y2 = me->points[p2_idx].z;
                            wx_2d = wy;
                            wy_2d = wz;
                            break;
                        case 2:  /* Normal=Y, écran montre Z,X */
                            x1 = me->points[p1_idx].z;
                            y1 = me->points[p1_idx].x;
                            x2 = me->points[p2_idx].z;
                            y2 = me->points[p2_idx].x;
                            wx_2d = wz;
                            wy_2d = wx;
                            break;
                        case 3:  /* Normal=Z, écran montre X,Y */
                        default:
                            x1 = me->points[p1_idx].x;
                            y1 = me->points[p1_idx].y;
                            x2 = me->points[p2_idx].x;
                            y2 = me->points[p2_idx].y;
                            wx_2d = wx;
                            wy_2d = wy;
                            break;
                    }
                    //double Nx,Ny;
                    //Nx = y2-y1;                    Ny = x1-x2;
                    double lN = sqrt((y2-y1)*(y2-y1) + (x1-x2)*(x1-x2));
                    double alpha = ((wx_2d-x1)*(x2-x1)+(wy_2d-y1)*(y2-y1)) / ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
                    double beta = ((wx_2d-x1)*(y2-y1)+(wy_2d-y1)*(x1-x2)) / ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
                    double dist = beta * lN;
		    printf("w %4.0lf %4.0lf xyz %4d %4d %4d x1y1 %4.0lf %4.0lf",wx_2d,wy_2d,me->points[p1_idx].x,me->points[p1_idx].y,me->points[p1_idx].z,x1,y1);
                    printf(" dist %6.2lf\n",dist);
                    if ((dist < min_dist) && (dist > 0.0) && (alpha >= 0.0) && (alpha <= 1.0))
                    {
                    min_dist = dist;
                    poly_idx = i;
                    edge_idx = j;
                    }
                }
            }

            if ((poly_idx != -1) && (edge_idx != -1)) {
                /* Stocker le côté sélectionné et mettre en évidence */
                me->selected_poly = poly_idx;
                me->selected_edge = edge_idx;

                /* Redessiner pour mettre en évidence */
                                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */

                /* Afficher la boîte de dialogue pour modifier u,v */
                int p1_idx = me->panels[poly_idx].points[edge_idx];
                int p2_idx = me->panels[poly_idx].points[(edge_idx+1) % me->panels[poly_idx].num_points];

                char prompt[512];
                char *values_str;
                double u1, v1, u2, v2, lu, lv;

                u1 = me->points[p1_idx].u;
                v1 = me->points[p1_idx].v;
                u2 = me->points[p2_idx].u;
                v2 = me->points[p2_idx].v;
                lu = u2 - u1;
                lv = v2 - v1;

                sprintf(prompt, "Edge of panel %d (points %d-%d)\n"
                               "u1=%.1f		v1=%.1f\n"
                               "u2=%.1f		v2=%.1f\n"
                               "lu=%.1f		lv=%.1f\n\n"
                               "Format: u1 v1 lu lv",
                        poly_idx+1, p1_idx+1, p2_idx+1, u1, v1, u2, v2, lu, lv);

                char default_val[128];
                sprintf(default_val, "%.1f		%.1f		%.1f		%.1f", u1, v1, lu, lv);

                values_str = GetString(prompt, default_val);
                if (values_str) {
                    double new_u1, new_v1, new_lu, new_lv;
                    if (sscanf(values_str, "%lf %lf %lf %lf", &new_u1, &new_v1, &new_lu, &new_lv) == 4) {
                        /* Calculer automatiquement u2 et v2 */
                        double new_u2 = new_u1 + new_lu;
                        double new_v2 = new_v1 + new_lv;

                        /* Sauvegarder pour undo */
                        save_state(me);

                        me->points[p1_idx].u = new_u1;
                        me->points[p1_idx].v = new_v1;
                        me->points[p2_idx].u = new_u2;
                        me->points[p2_idx].v = new_v2;

                        printf("UV modified: P%d(%.2f,%.2f) P%d(%.2f,%.2f) lu=%.2f lv=%.2f\n",
                               p1_idx+1, new_u1, new_v1, p2_idx+1, new_u2, new_v2, new_lu, new_lv);
                    } else {
                        printf("Invalid format\n");
                    }
                    free(values_str);
                }

                /* Désélectionner le côté */
                me->selected_poly = -1;
                me->selected_edge = -1;

                /* Redessiner */
                                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
            } else {
                printf("No edge found near click\n");
            }
        }
        break;


    case MODE_MODIFY_PANEL:
        /* Détecter le côté de panele cliqué */
        {
            int wx, wy, wz;
            int i, j;
            int found = FALSE;
            int poly_idx = -1, edge_idx = -1;
            Panel *poly1 = &me->panels[0];
            int p1_idx1 = poly1->points[0];
            int p2_idx1 = poly1->points[1];
                    double x1, y1, x2, y2, wx_2d, wy_2d;
                    switch (me->view_plane) {
                        case 1:  /* Normal=X, écran montre Y,Z */
                            x1 = me->points[p1_idx1].y;
                            y1 = me->points[p1_idx1].z;
                            x2 = me->points[p2_idx1].y;
                            y2 = me->points[p2_idx1].z;
                            break;
                        case 2:  /* Normal=Y, écran montre Z,X */
                            x1 = me->points[p1_idx1].z;
                            y1 = me->points[p1_idx1].x;
                            x2 = me->points[p2_idx1].z;
                            y2 = me->points[p2_idx1].x;
                            break;
                        case 3:  /* Normal=Z, écran montre X,Y */
                        default:
                            x1 = me->points[p1_idx1].x;
                            y1 = me->points[p1_idx1].y;
                            x2 = me->points[p2_idx1].x;
                            y2 = me->points[p2_idx1].y;
                            break;
                    }
            double min_dist = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
            printf("min_dist %4.0lf\n",min_dist);

            screen_to_world(me, x, y, &wx, &wy, &wz);

            /* Chercher le côté le plus proche */
            for (i = 0; i < me->num_panels && !found; i++) {
                Panel *poly = &me->panels[i];
                for (j = 0; j < poly->num_points; j++) {
                    int p1_idx = poly->points[j];
                    int p2_idx = poly->points[(j+1) % poly->num_points];

                    /* Ne pas traiter le dernier côté si non fermé */
                    if (j == poly->num_points - 1 && !poly->closed) continue;

                    /* Extraire les bonnes coordonnées selon le plan de vue */

                    switch (me->view_plane) {
                        case 1:  /* Normal=X, écran montre Y,Z */
                            x1 = me->points[p1_idx].y;
                            y1 = me->points[p1_idx].z;
                            x2 = me->points[p2_idx].y;
                            y2 = me->points[p2_idx].z;
                            wx_2d = wy;
                            wy_2d = wz;
                            break;
                        case 2:  /* Normal=Y, écran montre Z,X */
                            x1 = me->points[p1_idx].z;
                            y1 = me->points[p1_idx].x;
                            x2 = me->points[p2_idx].z;
                            y2 = me->points[p2_idx].x;
                            wx_2d = wz;
                            wy_2d = wx;
                            break;
                        case 3:  /* Normal=Z, écran montre X,Y */
                        default:
                            x1 = me->points[p1_idx].x;
                            y1 = me->points[p1_idx].y;
                            x2 = me->points[p2_idx].x;
                            y2 = me->points[p2_idx].y;
                            wx_2d = wx;
                            wy_2d = wy;
                            break;
                    }
                    double lN = sqrt((y2-y1)*(y2-y1) + (x1-x2)*(x1-x2));
                    double alpha = ((wx_2d-x1)*(x2-x1)+(wy_2d-y1)*(y2-y1)) / ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
                    double beta = ((wx_2d-x1)*(y2-y1)+(wy_2d-y1)*(x1-x2)) / ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
                    double dist = beta * lN;
		    printf("w %4.0lf %4.0lf xyz %4d %4d %4d x1y1 %4.0lf %4.0lf",wx_2d,wy_2d,me->points[p1_idx].x,me->points[p1_idx].y,me->points[p1_idx].z,x1,y1);
                    printf(" dist %6.2lf\n",dist);
                    if ((dist < min_dist) && (dist > 0.0) && (alpha >= 0.0) && (alpha <= 1.0))
                    {
                    min_dist = dist;
                    poly_idx = i;
                    edge_idx = j;
                    }
                }
            }

            if ((poly_idx != -1) && (edge_idx != -1)) {
                /* Stocker le côté sélectionné et mettre en évidence */
                me->selected_poly = poly_idx;
                me->selected_edge = edge_idx;

                /* Redessiner pour mettre en évidence */
                                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */

                /* Afficher la boîte de dialogue pour modifier u,v */
                int p1_idx = me->panels[poly_idx].points[edge_idx];
                //int p2_idx = me->panels[poly_idx].points[(edge_idx+1) % me->panels[poly_idx].num_points];

                char prompt[512];
                char *values_str;
		double T_stiffness;
		double C_stiffness;
		double MOS;
		double length;
		//double vol_mass;
		//double diameter;
		//double knot_size;
		//double cd;
		//double f;
		//double meshing_step;
		//int meshing_type;
		
                T_stiffness 	= me->panels[poly_idx].T_stiffness;
                C_stiffness 	= me->panels[poly_idx].C_stiffness;
                MOS		= me->panels[poly_idx].MOS;
                length		= me->panels[poly_idx].length;
                //vol_mass	= me->panels[poly_idx].vol_mass;
                //diameter	= me->panels[poly_idx].diameter;
                //knot_size	= me->panels[poly_idx].knot_size;
                //cd		= me->panels[poly_idx].cd;
                //f		= me->panels[poly_idx].f;
                //meshing_step	= me->panels[poly_idx].meshing_step;
                //meshing_type	= me->panels[poly_idx].meshing_type;
 
                sprintf(prompt, "panel %d \n"
                               "Traction stiffness=%.0f\n"
                               "Compression stiffness=%.0f\n"
                               "Mesh opening Stiffness=%.3f\n"
                               "Size length=%.3f",
                        poly_idx+1, T_stiffness, C_stiffness, MOS, length);

                char default_val[128];
                sprintf(default_val, "%.0f %.0f %.3f %.3f", T_stiffness, C_stiffness, MOS, length);

                values_str = GetString(prompt, default_val);
                if (values_str) {
                    double new_T_stiffness, new_C_stiffness, new_MOS, new_length;
                    if (sscanf(values_str, "%lf %lf %lf %lf", &new_T_stiffness, &new_C_stiffness, &new_MOS, &new_length) == 4) {

                        /* Sauvegarder pour undo */
                        save_state(me);

                        me->panels[poly_idx].T_stiffness = new_T_stiffness;
                        me->panels[poly_idx].C_stiffness = new_C_stiffness;
                        me->panels[poly_idx].MOS = new_MOS;
                        me->panels[poly_idx].length = new_length;

                        printf("Panel modified: P%d  T_stiffness=%.0f C_stiffness=%.0f  MOS=%.3f length=%.3f\n",
                               p1_idx+1, new_T_stiffness, new_C_stiffness, new_MOS, new_length);
                    } else {
                        printf("Invalid format\n");
                    }
                    free(values_str);
                }

                /* Désélectionner le côté */
                me->selected_poly = -1;
                me->selected_edge = -1;

                /* Redessiner */
                                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
            } else {
                printf("No edge found near click\n");
            }
        }
        break;


    case MODE_MODIFY_Z:
        /* Trouver le point cliqué et modifier sa coordonnée Z */
        {
            int point_idx = find_point(me, x, y, 10);
            if (point_idx != -1) {
                char prompt[256];
                char default_val[64];
                char *value_str;

                sprintf(prompt, "Modify Z coordinate of point %d\n"
                               "Current: x=%d y=%d z=%d\n\n"
                               "Enter new Z value:",
                        point_idx+1,
                        me->points[point_idx].x,
                        me->points[point_idx].y,
                        me->points[point_idx].z);

                sprintf(default_val, "%d", me->points[point_idx].z);

                value_str = GetString(prompt, default_val);
                if (value_str) {
                    int new_z;
                    if (sscanf(value_str, "%d", &new_z) == 1) {
                        /* Sauvegarder pour undo */
                        save_state(me);

                        me->points[point_idx].z = new_z;

                        printf("Z modified: Point %d: z=%d\n", point_idx+1, new_z);

                        /* Redessiner */
                                                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
                    } else {
                        printf("Invalid format\n");
                    }
                    free(value_str);
                }
            } else {
                printf("No point found near click\n");
            }
        }
        break;

    case MODE_ALIGN:
        /* Commencer la sélection rectangulaire */
        {
            me->selecting = TRUE;
            screen_to_world(me, x, y, &me->select_x1, &me->select_y1, &me->select_z1);
            me->select_x2 = me->select_x1;
            me->select_y2 = me->select_y1;
            me->select_z2 = me->select_z1;
            printf("Rectangle selection started\n");
        }
        break;

    case MODE_PANEL:
        /* Ajouter un point au panele en cours */
        if (me->current_poly == -1) {
            /* Démarrer un nouveau panele */
            if (me->num_panels >= MAX_PANELS) {
                printf("Maximum number of panels reached\n");
                return;
            }
            me->current_poly = me->num_panels;
            me->panels[me->current_poly].num_points = 0;
            me->panels[me->current_poly].closed = FALSE;
            me->panels[me->current_poly].type = 1;  /* Type par défaut */
            me->panels[me->current_poly].T_stiffness = 25000;  /* T_stiffness par défaut */
            me->panels[me->current_poly].C_stiffness = 0;  /* C_stiffness par défaut */
            me->panels[me->current_poly].MOS = 0;  /* MOS par défaut */
            me->panels[me->current_poly].length = 0.4;  /* length par défaut */
            me->panels[me->current_poly].vol_mass = 1025;  /* vol_mass par défaut */
            me->panels[me->current_poly].diameter = 0.002;  /* diameter par défaut */
            me->panels[me->current_poly].knot_size = 0.0;  /* knot_size par défaut */
            me->panels[me->current_poly].cd = 1.2;  /* cd par défaut */
            me->panels[me->current_poly].f = 0.08;  /* f par défaut */
            me->panels[me->current_poly].meshing_step = 10;  /* meshing_step par défaut */
            me->panels[me->current_poly].meshing_type = 2;  /* meshing_type par défaut */
            /* Initialiser les types des côtés à 1 par défaut */
            for (int k = 0; k < 50; k++) {
                me->panels[me->current_poly].edge_types[k] = 1;
            }
            me->num_panels++;
        }

        /* Vérifier si on clique près du premier point (fermer le panele) */
        if (me->panels[me->current_poly].num_points > 2) {
            //int first_pt = me->panels[me->current_poly].points[0];
            int last_pt = me->num_points - 1;
            int wx, wy, wz;
            int dx, dy;
            screen_to_world(me, x, y, &wx, &wy, &wz);

            /* Comparer les coordonnées selon le plan de vue */
            switch (me->view_plane) {
                case 1:  /* Normal=X, écran montre Y,Z */
                    dx = wy - me->points[last_pt].y;
                    dy = wz - me->points[last_pt].z;
                    break;
                case 2:  /* Normal=Y, écran montre Z,X */
                    dx = wz - me->points[last_pt].z;
                    dy = wx - me->points[last_pt].x;
                    break;
                case 3:  /* Normal=Z, écran montre X,Y */
                default:
                    dx = wx - me->points[last_pt].x;
                    dy = wy - me->points[last_pt].y;
                    break;
            }

	    //printf("poly.num_points %d ",me->panels[me->current_poly].num_points);
	    //printf("last_pt %d ",last_pt);
	    //printf("me->num_points %d \n",me->num_points);
	    //printf("wx wy wz = %d %d %d\n",wx,wy,wz);
	    //printf(" x  y  z = %d %d %d\n",me->points[last_pt-1].x,me->points[last_pt-1].y,me->points[last_pt-1].z);
            //if (sqrt(dx*dx + dy*dy) < 10) {
            //if (sqrt(dx*dx + dy*dy) == 0) {
            if ((dx == 0) && (dy == 0)) {
                /* Sauvegarder l'état pour undo */
                save_state(me);
                me->panels[me->current_poly].closed = TRUE;
                me->current_poly = -1;
                printf("Panel closed\n");
                                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
                me->current_mode = 0;

                return;
            }
        }

        /* Ajouter un nouveau point */
        add_point(me, x, y);
        point_idx = me->num_points - 1;
        me->panels[me->current_poly].points[me->panels[me->current_poly].num_points] = point_idx;
        me->panels[me->current_poly].num_points++;
	printf("me->num_points %d me->panels[me->current_poly].num_points %d\n",me->num_points,me->panels[me->current_poly].num_points);

        /* Redessiner */
                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
        break;

    case MODE_CABLE:
        /* Créer un cable entre deux points */
        if (me->temp_point == -1) {
            /* Premier point */
            point_idx = find_point(me, x, y, 1);
            if (point_idx == -1) {
                add_point(me, x, y);
                point_idx = me->num_points - 1;
            }
            me->temp_point = point_idx;
            printf("First point selected. Click for second point.\n");
        } else {
            /* Deuxième point */
            point_idx = find_point(me, x, y, 1);
            if (point_idx == -1) {
                add_point(me, x, y);
                point_idx = me->num_points - 1;
            }

            if (me->num_cables < MAX_CABLES) {
                /* Sauvegarder l'état pour undo */
                save_state(me);
                me->cables[me->num_cables].p1 = me->temp_point;
                me->cables[me->num_cables].p2 = point_idx;
                me->cables[me->num_cables].type = 1;  /* Type par défaut */
                me->num_cables++;
                printf("Cable created\n");
            }
            me->temp_point = -1;

            /* Redessiner */
                        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
        }
        break;

    case MODE_LINK:
        /* Créer un lien entre deux points existants */
        point_idx = find_closest_point(me, x, y);
        if (point_idx == -1) {
            printf("Click on an existing point xy %d %d \n", x, y);
            return;
        }

        if (me->temp_point == -1) {
            me->temp_point = point_idx;
            printf("First point selected. Click on another point.\n");
        } else {
            if (me->num_links < MAX_LINKS) {
                /* Sauvegarder l'état pour undo */
                save_state(me);
                me->links[me->num_links].p1 = me->temp_point;
                me->links[me->num_links].p2 = point_idx;
                me->num_links++;
                printf("Link created\n");
            }
            me->temp_point = -1;

            /* Redessiner */
                        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
        }
        break;
    }
}

void button_up(Widget w, int button, int x, int y, void *data)
{
    MyProgram *me = (MyProgram *)data;
    int i;

    /* Désactiver le panning quand on relâche le bouton droit */
    if (button == 3) {
        me->is_panning = FALSE;
        printf("Pan mode disabled\n");
        return;
    }

    /* Finaliser la sélection rectangulaire en mode alignement */
    if (button == 1 && me->current_mode == MODE_ALIGN && me->selecting) {
        me->selecting = FALSE;
        screen_to_world(me, x, y, &me->select_x2, &me->select_y2, &me->select_z2);

        /* Calculer les min/max du rectangle selon le plan de vue */
        int min1, max1, min2, max2;
        int coord1, coord2;

        switch (me->view_plane) {
            case 1:  /* Normal=X, écran montre Y,Z */
                min1 = (me->select_y1 < me->select_y2) ? me->select_y1 : me->select_y2;
                max1 = (me->select_y1 > me->select_y2) ? me->select_y1 : me->select_y2;
                min2 = (me->select_z1 < me->select_z2) ? me->select_z1 : me->select_z2;
                max2 = (me->select_z1 > me->select_z2) ? me->select_z1 : me->select_z2;

                /* Sélectionner les points dans le rectangle */
                me->num_selected = 0;
                for (i = 0; i < me->num_points; i++) {
                    if (me->points[i].used) {
                        coord1 = me->points[i].y;
                        coord2 = me->points[i].z;
                        if (coord1 >= min1 && coord1 <= max1 && coord2 >= min2 && coord2 <= max2) {
                            me->points[i].selected = TRUE;
                            me->num_selected++;
                        } else {
                            me->points[i].selected = FALSE;
                        }
                    }
                }
                break;

            case 2:  /* Normal=Y, écran montre Z,X */
                min1 = (me->select_z1 < me->select_z2) ? me->select_z1 : me->select_z2;
                max1 = (me->select_z1 > me->select_z2) ? me->select_z1 : me->select_z2;
                min2 = (me->select_x1 < me->select_x2) ? me->select_x1 : me->select_x2;
                max2 = (me->select_x1 > me->select_x2) ? me->select_x1 : me->select_x2;

                /* Sélectionner les points dans le rectangle */
                me->num_selected = 0;
                for (i = 0; i < me->num_points; i++) {
                    if (me->points[i].used) {
                        coord1 = me->points[i].z;
                        coord2 = me->points[i].x;
                        if (coord1 >= min1 && coord1 <= max1 && coord2 >= min2 && coord2 <= max2) {
                            me->points[i].selected = TRUE;
                            me->num_selected++;
                        } else {
                            me->points[i].selected = FALSE;
                        }
                    }
                }
                break;

            case 3:  /* Normal=Z, écran montre X,Y */
            default:
                min1 = (me->select_x1 < me->select_x2) ? me->select_x1 : me->select_x2;
                max1 = (me->select_x1 > me->select_x2) ? me->select_x1 : me->select_x2;
                min2 = (me->select_y1 < me->select_y2) ? me->select_y1 : me->select_y2;
                max2 = (me->select_y1 > me->select_y2) ? me->select_y1 : me->select_y2;

                /* Sélectionner les points dans le rectangle */
                me->num_selected = 0;
                for (i = 0; i < me->num_points; i++) {
                    if (me->points[i].used) {
                        coord1 = me->points[i].x;
                        coord2 = me->points[i].y;
                        if (coord1 >= min1 && coord1 <= max1 && coord2 >= min2 && coord2 <= max2) {
                            me->points[i].selected = TRUE;
                            me->num_selected++;
                        } else {
                            me->points[i].selected = FALSE;
                        }
                    }
                }
                break;
        }

        printf("%d points selected\n", me->num_selected);

        /* Redessiner */
                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
    }
}

void mouse_motion(Widget w, int x, int y, void *data)
{
    MyProgram *me = (MyProgram *)data;

    /* Si on est en train de panner, déplacer la vue */
    if (me->is_panning) {
        int dx = x - me->last_mouse_x;
        int dy = y - me->last_mouse_y;

        me->pan_x += dx;
        me->pan_y += dy;

        me->last_mouse_x = x;
        me->last_mouse_y = y;

        /* Redessiner */
                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
    }

    /* Si on est en train de sélectionner, mettre à jour le rectangle */
    if (me->selecting) {
        screen_to_world(me, x, y, &me->select_x2, &me->select_y2, &me->select_z2);

        /* Redessiner */
                /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
    }
}

/* ===== CALLBACK POUR LE REDESSIN ===== */

void redisplay(Widget w, int width, int height, void *data)
{
    MyProgram *me = (MyProgram *)data;

    me->draw_area_width = width;
    me->draw_area_height = height;

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

/* ===== FONCTIONS AUXILIAIRES ===== */

int find_point(MyProgram *me, int x, int y, int tolerance)
{
    int i;
    int wx, wy, wz;
    screen_to_world(me, x, y, &wx, &wy, &wz);

    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used) {
            int dx, dy;

            /* Comparer les coordonnées selon le plan de vue */
            switch (me->view_plane) {
                case 1:  /* Normal=X, écran montre Y,Z */
                    dx = wy - me->points[i].y;
                    dy = wz - me->points[i].z;
                    break;
                case 2:  /* Normal=Y, écran montre Z,X */
                    dx = wz - me->points[i].z;
                    dy = wx - me->points[i].x;
                    break;
                case 3:  /* Normal=Z, écran montre X,Y */
                default:
                    dx = wx - me->points[i].x;
                    dy = wy - me->points[i].y;
                    break;
            }

            if (sqrt(dx*dx + dy*dy) < tolerance) {
                return i;
            }
        }
    }
    return -1;
}

int find_closest_point(MyProgram *me, int x, int y)
{
    int i;
    int wx, wy, wz;
    int min_dist,dist;
    min_dist = 1000;
    int the_i;
    screen_to_world(me, x, y, &wx, &wy, &wz);

    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used) {
            int dx, dy;

            /* Comparer les coordonnées selon le plan de vue */
            switch (me->view_plane) {
                case 1:  /* Normal=X, écran montre Y,Z */
                    dx = wy - me->points[i].y;
                    dy = wz - me->points[i].z;
                    break;
                case 2:  /* Normal=Y, écran montre Z,X */
                    dx = wz - me->points[i].z;
                    dy = wx - me->points[i].x;
                    break;
                case 3:  /* Normal=Z, écran montre X,Y */
                default:
                    dx = wx - me->points[i].x;
                    dy = wy - me->points[i].y;
                    break;
            }
	    dist = sqrt(dx*dx + dy*dy);
            if (dist < min_dist) {
            	min_dist = dist;
            	the_i = i;
            }
        }
    }
    return the_i;
}

void add_point(MyProgram *me, int x, int y)
{
    int wx, wy, wz;

    if (me->num_points >= MAX_POINTS) {
        printf("Maximum number of points reached\n");
        return;
    }

    screen_to_world(me, x, y, &wx, &wy, &wz);
    me->points[me->num_points].x = wx;
    me->points[me->num_points].y = wy;
    me->points[me->num_points].z = wz;

    /* Initialiser u,v selon le plan de vue */
    switch (me->view_plane) {
        case 1:  /* Normal=X, écran montre Y,Z : u=Y, v=Z */
            me->points[me->num_points].u = (double)wy;
            me->points[me->num_points].v = (double)wz;
            break;
        case 2:  /* Normal=Y, écran montre Z,X : u=Z, v=X */
            me->points[me->num_points].u = (double)wz;
            me->points[me->num_points].v = (double)wx;
            break;
        case 3:  /* Normal=Z, écran montre X,Y : u=X, v=Y */
        default:
            me->points[me->num_points].u = (double)wx;
            me->points[me->num_points].v = (double)wy;
            break;
    }

    me->points[me->num_points].type = 1;        /* Type par défaut */
    me->points[me->num_points].selected = FALSE;
    me->points[me->num_points].used = TRUE;
    me->num_points++;
}

void draw_everything(MyProgram *me)
{
    int i, j;
    int sx1, sy1, sx2, sy2;

    /* Dessiner les axes selon le plan de vue */
    if (me->show_axes) {
        SetColor(BLACK);

        switch (me->view_plane) {
            case 1:  /* Normal=X, écran montre Y (horizontal) et Z (vertical) */
                /* Axe Y (horizontal) */
                world_to_screen(me, 0, -10000, 0, &sx1, &sy1);
                world_to_screen(me, 0, 10000, 0, &sx2, &sy2);
                DrawLine(sx1, sy1, sx2, sy2);
                world_to_screen(me, 0, 100, 0, &sx1, &sy1);
                DrawText("Y", sx1 + 10, sy1 + 5);

                /* Axe Z (vertical) */
                world_to_screen(me, 0, 0, -10000, &sx1, &sy1);
                world_to_screen(me, 0, 0, 10000, &sx2, &sy2);
                DrawLine(sx1, sy1, sx2, sy2);
                world_to_screen(me, 0, 0, 100, &sx1, &sy1);
                DrawText("Z", sx1 + 5, sy1 - 10);
                break;

            case 2:  /* Normal=Y, écran montre Z (horizontal) et X (vertical) */
                /* Axe Z (horizontal) */
                world_to_screen(me, 0, 0, -10000, &sx1, &sy1);
                world_to_screen(me, 0, 0, 10000, &sx2, &sy2);
                DrawLine(sx1, sy1, sx2, sy2);
                world_to_screen(me, 0, 0, 100, &sx1, &sy1);
                DrawText("Z", sx1 + 10, sy1 + 5);

                /* Axe X (vertical) */
                world_to_screen(me, -10000, 0, 0, &sx1, &sy1);
                world_to_screen(me, 10000, 0, 0, &sx2, &sy2);
                DrawLine(sx1, sy1, sx2, sy2);
                world_to_screen(me, 100, 0, 0, &sx1, &sy1);
                DrawText("X", sx1 + 5, sy1 - 10);
                break;

            case 3:  /* Normal=Z, écran montre X (horizontal) et Y (vertical) */
            default:
                /* Axe X (horizontal) */
                world_to_screen(me, -10000, 0, 0, &sx1, &sy1);
                world_to_screen(me, 10000, 0, 0, &sx2, &sy2);
                DrawLine(sx1, sy1, sx2, sy2);
                world_to_screen(me, 100, 0, 0, &sx1, &sy1);
                DrawText("X", sx1 + 10, sy1 + 5);

                /* Axe Y (vertical) */
                world_to_screen(me, 0, -10000, 0, &sx1, &sy1);
                world_to_screen(me, 0, 10000, 0, &sx2, &sy2);
                DrawLine(sx1, sy1, sx2, sy2);
                world_to_screen(me, 0, 100, 0, &sx1, &sy1);
                DrawText("Y", sx1 + 5, sy1 - 10);
                break;
        }

        /* Marquer l'origine */
        world_to_screen(me, 0, 0, 0, &sx1, &sy1);
        DrawLine(sx1-5, sy1, sx1+5, sy1);
        DrawLine(sx1, sy1-5, sx1, sy1+5);
        DrawText("0", sx1-10, sy1+15);
    }

    /* Dessiner les paneles EN PREMIER (en arrière-plan) */
    if (me->show_panels) {
        SetColor(BLUE);
        for (i = 0; i < me->num_panels; i++) {
            Panel *poly = &me->panels[i];
            for (j = 0; j < poly->num_points - 1; j++) {
                int p1 = poly->points[j];
                int p2 = poly->points[j+1];
                world_to_screen(me, me->points[p1].x, me->points[p1].y, me->points[p1].z, &sx1, &sy1);
                world_to_screen(me, me->points[p2].x, me->points[p2].y, me->points[p2].z, &sx2, &sy2);
                SetColor(BLUE);
                DrawLine(sx1, sy1, sx2, sy2);
            }
            /* Fermer le panele si nécessaire */
            if (poly->closed && poly->num_points > 0) {
                int p1 = poly->points[poly->num_points-1];
                int p2 = poly->points[0];
                world_to_screen(me, me->points[p1].x, me->points[p1].y, me->points[p1].z, &sx1, &sy1);
                world_to_screen(me, me->points[p2].x, me->points[p2].y, me->points[p2].z, &sx2, &sy2);
                SetColor(BLUE);
                DrawLine(sx1, sy1, sx2, sy2);
            }
        }
    }

    /* Mettre en évidence le côté sélectionné (mode UV) */
    if (me->selected_poly >= 0 && me->selected_edge >= 0) {
        Panel *poly = &me->panels[me->selected_poly];
        int edge_idx = me->selected_edge;
        int p1_idx, p2_idx;

        /* Déterminer les indices des points de ce côté */
        if (edge_idx < poly->num_points - 1) {
            p1_idx = poly->points[edge_idx];
            p2_idx = poly->points[edge_idx + 1];
        } else {
            /* Dernier côté (retour au début si fermé) */
            p1_idx = poly->points[poly->num_points - 1];
            p2_idx = poly->points[0];
        }

        /* Dessiner le côté sélectionné en rouge */
        SetColor(RED);
        world_to_screen(me, me->points[p1_idx].x, me->points[p1_idx].y, me->points[p1_idx].z, &sx1, &sy1);
        world_to_screen(me, me->points[p2_idx].x, me->points[p2_idx].y, me->points[p2_idx].z, &sx2, &sy2);
        DrawLine(sx1, sy1, sx2, sy2);

        /* Dessiner les extrémités en rouge (pixels uniques) */
        SetColor(RED);
        DrawPixel(sx1, sy1);
        DrawPixel(sx2, sy2);
    }

    /* Dessiner les cables */
    if (me->show_cables) {
        SetColor(GREEN);
        for (i = 0; i < me->num_cables; i++) {
            int p1 = me->cables[i].p1;
            int p2 = me->cables[i].p2;
            world_to_screen(me, me->points[p1].x, me->points[p1].y, me->points[p1].z, &sx1, &sy1);
            world_to_screen(me, me->points[p2].x, me->points[p2].y, me->points[p2].z, &sx2, &sy2);
            DrawLine(sx1, sy1, sx2, sy2);
        }
    }

    /* Dessiner les liens (en rouge pointillé) */
    if (me->show_links) {
        SetColor(RED);
        for (i = 0; i < me->num_links; i++) {
            int p1 = me->links[i].p1;
            int p2 = me->links[i].p2;
            int wx1 = me->points[p1].x;
            int wy1 = me->points[p1].y;
            int wz1 = me->points[p1].z;
            int wx2 = me->points[p2].x;
            int wy2 = me->points[p2].y;
            int wz2 = me->points[p2].z;
            int steps = 10;
            for (j = 0; j < steps; j += 2) {
                int wxa = wx1 + (wx2-wx1)*j/steps;
                int wya = wy1 + (wy2-wy1)*j/steps;
                int wza = wz1 + (wz2-wz1)*j/steps;
                int wxb = wx1 + (wx2-wx1)*(j+1)/steps;
                int wyb = wy1 + (wy2-wy1)*(j+1)/steps;
                int wzb = wz1 + (wz2-wz1)*(j+1)/steps;
                world_to_screen(me, wxa, wya, wza, &sx1, &sy1);
                world_to_screen(me, wxb, wyb, wzb, &sx2, &sy2);
                DrawLine(sx1, sy1, sx2, sy2);
            }
        }
    }

    /* Dessiner les numéros des points */
    if (me->show_point_numbers) {
        SetColor(BLACK);
        for (i = 0; i < me->num_points; i++) {
            if (me->points[i].used) {
                int sx, sy;
                char num_str[16];
                world_to_screen(me, me->points[i].x, me->points[i].y, me->points[i].z, &sx, &sy);
                sprintf(num_str, "%d", i+1);
                DrawText(num_str, sx + 8, sy - 8);
            }
        }
    }

    /* Dessiner les numéros des paneles */
    if (me->show_panel_numbers) {
        SetColor(BLUE);
        for (i = 0; i < me->num_panels; i++) {
            if (me->panels[i].num_points > 0) {
                /* Calculer le centre du panele */
                int center_x = 0, center_y = 0, center_z = 0;
                int sx, sy;
                char num_str[16];
                for (j = 0; j < me->panels[i].num_points; j++) {
                    int p_idx = me->panels[i].points[j];
                    center_x += me->points[p_idx].x;
                    center_y += me->points[p_idx].y;
                    center_z += me->points[p_idx].z;
                }
                center_x /= me->panels[i].num_points;
                center_y /= me->panels[i].num_points;
                center_z /= me->panels[i].num_points;
                world_to_screen(me, center_x, center_y, center_z, &sx, &sy);
                sprintf(num_str, "P%d", i+1);
                DrawText(num_str, sx, sy);
            }
        }
    }

    /* Dessiner les numéros des cables */
    if (me->show_cable_numbers) {
        SetColor(GREEN);
        for (i = 0; i < me->num_cables; i++) {
            /* Calculer le milieu du cable */
            int p1 = me->cables[i].p1;
            int p2 = me->cables[i].p2;
            int mid_x = (me->points[p1].x + me->points[p2].x) / 2;
            int mid_y = (me->points[p1].y + me->points[p2].y) / 2;
            int mid_z = (me->points[p1].z + me->points[p2].z) / 2;
            int sx, sy;
            char num_str[16];
            world_to_screen(me, mid_x, mid_y, mid_z, &sx, &sy);
            sprintf(num_str, "S%d", i+1);
            DrawText(num_str, sx, sy);
        }
    }

    /* Dessiner les numéros des interconnections (groupes de liens connectés) */
    if (me->show_link_numbers && me->num_links > 0) {
        int adjacency[MAX_POINTS][MAX_POINTS] = {{0}};
        int visited[MAX_POINTS] = {0};
        int components[MAX_LINKS][MAX_POINTS];
        int comp_sizes[MAX_LINKS] = {0};
        int num_components = 0;
        int k;

        /* Construire la matrice d'adjacence */
        for (i = 0; i < me->num_links; i++) {
            int p1 = me->links[i].p1;
            int p2 = me->links[i].p2;
            adjacency[p1][p2] = 1;
            adjacency[p2][p1] = 1;
        }

        /* Trouver les composantes connexes avec DFS */
        for (i = 0; i < me->num_points; i++) {
            if (me->points[i].used && !visited[i]) {
                int has_link = 0;
                /* Vérifier si ce nœud a au moins un lien */
                for (j = 0; j < me->num_points; j++) {
                    if (adjacency[i][j]) {
                        has_link = 1;
                        break;
                    }
                }

                if (has_link) {
                    comp_sizes[num_components] = 0;
                    dfs_interconnection(i, visited, adjacency, components[num_components],
                                      &comp_sizes[num_components], me->num_points);
                    num_components++;
                }
            }
        }

        /* Afficher le numéro de chaque interconnection */
        SetColor(RED);
        for (i = 0; i < num_components; i++) {
            /* Calculer le centre du groupe d'interconnection */
            int center_x = 0, center_y = 0, center_z = 0;
            int sx, sy;
            char num_str[16];

            for (k = 0; k < comp_sizes[i]; k++) {
                int p_idx = components[i][k];
                center_x += me->points[p_idx].x;
                center_y += me->points[p_idx].y;
                center_z += me->points[p_idx].z;
            }
            center_x /= comp_sizes[i];
            center_y /= comp_sizes[i];
            center_z /= comp_sizes[i];

            world_to_screen(me, center_x, center_y, center_z, &sx, &sy);
            sprintf(num_str, "I%d", i+1);
            DrawText(num_str, sx, sy);
        }
    }

    /* Dessiner les types des points */
    if (me->show_point_types) {
        SetColor(BLACK);
        for (i = 0; i < me->num_points; i++) {
            if (me->points[i].used) {
                int sx, sy;
                char type_str[16];
                world_to_screen(me, me->points[i].x, me->points[i].y, me->points[i].z, &sx, &sy);
                sprintf(type_str, "T%d", me->points[i].type);
                DrawText(type_str, sx + 8, sy + 8);
            }
        }
    }

    /* Dessiner les types des paneles */
    if (me->show_panel_types) {
        SetColor(BLUE);
        for (i = 0; i < me->num_panels; i++) {
            if (me->panels[i].num_points > 0) {
                /* Calculer le centre du panele */
                int center_x = 0, center_y = 0, center_z = 0;
                int sx, sy;
                char type_str[16];
                for (j = 0; j < me->panels[i].num_points; j++) {
                    int p_idx = me->panels[i].points[j];
                    center_x += me->points[p_idx].x;
                    center_y += me->points[p_idx].y;
                    center_z += me->points[p_idx].z;
                }
                center_x /= me->panels[i].num_points;
                center_y /= me->panels[i].num_points;
                center_z /= me->panels[i].num_points;
                world_to_screen(me, center_x, center_y, center_z, &sx, &sy);
                sprintf(type_str, "T%d", me->panels[i].type);
                DrawText(type_str, sx, sy + 15);
            }
        }
    }

    /* Dessiner les types des côtés des paneles */
    if (me->show_edge_types) {
        SetColor(BLUE);
        for (i = 0; i < me->num_panels; i++) {
            Panel *poly = &me->panels[i];
            /* Dessiner le type de chaque côté */
            for (j = 0; j < poly->num_points; j++) {
                int p1 = poly->points[j];
                int p2 = poly->points[(j+1) % poly->num_points];
                if (j == poly->num_points - 1 && !poly->closed) break;

                /* Calculer le milieu du côté */
                int mid_x = (me->points[p1].x + me->points[p2].x) / 2;
                int mid_y = (me->points[p1].y + me->points[p2].y) / 2;
                int mid_z = (me->points[p1].z + me->points[p2].z) / 2;
                int sx, sy;
                char type_str[16];
                world_to_screen(me, mid_x, mid_y, mid_z, &sx, &sy);
                sprintf(type_str, "T%d", poly->edge_types[j]);
                DrawText(type_str, sx, sy);
            }
        }
    }

    /* Dessiner les types des cables */
    if (me->show_cable_types) {
        SetColor(GREEN);
        for (i = 0; i < me->num_cables; i++) {
            /* Calculer le milieu du cable */
            int p1 = me->cables[i].p1;
            int p2 = me->cables[i].p2;
            int mid_x = (me->points[p1].x + me->points[p2].x) / 2;
            int mid_y = (me->points[p1].y + me->points[p2].y) / 2;
            int mid_z = (me->points[p1].z + me->points[p2].z) / 2;
            int sx, sy;
            char type_str[16];
            world_to_screen(me, mid_x, mid_y, mid_z, &sx, &sy);
            sprintf(type_str, "T%d", me->cables[i].type);
            DrawText(type_str, sx, sy + 15);
        }
    }

    /* Dessiner les points D'ABORD */
    if (me->show_points) {
        for (i = 0; i < me->num_points; i++) {
            if (me->points[i].used) {
                int sx, sy;
                world_to_screen(me, me->points[i].x, me->points[i].y, me->points[i].z, &sx, &sy);

                /* Couleur selon sélection */
                if (me->points[i].selected) {
                    SetColor(RED);
                } else {
                    SetColor(BLACK);
                }

                /* Dessiner un petit carré autour du point */
                int size = (int)(3 * me->zoom_factor);
                if (size < 2) size = 2;
                DrawLine(sx-size, sy-size, sx+size, sy-size);
                DrawLine(sx+size, sy-size, sx+size, sy+size);
                DrawLine(sx+size, sy+size, sx-size, sy+size);
                DrawLine(sx-size, sy+size, sx-size, sy-size);
            }
        }
    }

    /* Dessiner le rectangle de sélection en cours */
    if (me->selecting) {
        int sx1, sy1, sx2, sy2;
        world_to_screen(me, me->select_x1, me->select_y1, me->select_z1, &sx1, &sy1);
        world_to_screen(me, me->select_x2, me->select_y2, me->select_z2, &sx2, &sy2);

        SetColor(RED);
        DrawLine(sx1, sy1, sx2, sy1);
        DrawLine(sx2, sy1, sx2, sy2);
        DrawLine(sx2, sy2, sx1, sy2);
        DrawLine(sx1, sy2, sx1, sy1);
    }
}

/* ===== FONCTIONS DE CONVERSION DE COORDONNÉES ===== */

void screen_to_world(MyProgram *me, int sx, int sy, int *wx, int *wy, int *wz)
{
    /* Convertir les coordonnées écran en coordonnées monde (avec zoom et pan) */
    /* en fonction du plan de vue actuel */
    int screen_to_world_x = (int)((sx - me->pan_x) / me->zoom_factor);
    int screen_to_world_y = (int)((sy - me->pan_y) / me->zoom_factor);

    switch (me->view_plane) {
        case 1:  /* Normal=X, écran montre Y (horizontal) et Z (vertical) */
            *wx = 0;  /* La coordonnée X reste inchangée, sera mise à jour par l'appelant si nécessaire */
            *wy = screen_to_world_x;
            *wz = screen_to_world_y;
            break;
        case 2:  /* Normal=Y, écran montre Z (horizontal) et X (vertical) */
            *wx = screen_to_world_y;
            *wy = 0;  /* La coordonnée Y reste inchangée, sera mise à jour par l'appelant si nécessaire */
            *wz = screen_to_world_x;
            break;
        case 3:  /* Normal=Z, écran montre X (horizontal) et Y (vertical) */
        default:
            *wx = screen_to_world_x;
            *wy = screen_to_world_y;
            *wz = 0;  /* La coordonnée Z reste inchangée, sera mise à jour par l'appelant si nécessaire */
            break;
    }
}

void world_to_screen(MyProgram *me, int wx, int wy, int wz, int *sx, int *sy)
{
    /* Convertir les coordonnées monde en coordonnées écran (avec zoom et pan) */
    /* en fonction du plan de vue actuel */
    int world_x, world_y;

    switch (me->view_plane) {
        case 1:  /* Normal=X, écran montre Y (horizontal) et Z (vertical) */
            world_x = wy;
            world_y = wz;
            break;
        case 2:  /* Normal=Y, écran montre Z (horizontal) et X (vertical) */
            world_x = wz;
            world_y = wx;
            break;
        case 3:  /* Normal=Z, écran montre X (horizontal) et Y (vertical) */
        default:
            world_x = wx;
            world_y = wy;
            break;
    }

    *sx = (int)(world_x * me->zoom_factor + me->pan_x);
    *sy = (int)(world_y * me->zoom_factor + me->pan_y);
}

/* ===== CALLBACKS POUR LE ZOOM ===== */

void zoom_in(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->zoom_factor *= 1.2;
    printf("Zoom: %.2fx\n", me->zoom_factor);
    
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void zoom_out(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->zoom_factor /= 1.2;
    if (me->zoom_factor < 0.1) me->zoom_factor = 0.1;
    printf("Zoom: %.2fx\n", me->zoom_factor);
    
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void zoom_reset(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    char *zoom_str;
    float new_zoom;

    /* Demander à l'utilisateur le niveau de zoom désiré */
    zoom_str = GetString("Desired zoom level (e.g.: 1.0 for 100%, 1.5 for 150%):", "1.0");
    if (!zoom_str) {
        printf("Zoom reset cancelled\n");
        return;
    }

    new_zoom = atof(zoom_str);

    /* Vérifier que le zoom est dans une plage raisonnable */
    if (new_zoom < 0.1) new_zoom = 0.1;
    if (new_zoom > 10.0) new_zoom = 10.0;

    me->zoom_factor = new_zoom;
    me->pan_x = 0;
    me->pan_y = 0;
    printf("Zoom set to %.2fx\n", me->zoom_factor);

    free(zoom_str);

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void zoom_pixel_m(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    char *zoom_str;
    float new_zoom;

    /* Demander à l'utilisateur le niveau de zoom désiré */
    zoom_str = GetString("Desired pixel/m:", "1.0");
    if (!zoom_str) {
        printf("Zoom reset cancelled\n");
        return;
    }

    new_zoom = atof(zoom_str);

    /* Vérifier que le zoom est dans une plage raisonnable */
    if (new_zoom < 0.0) new_zoom = fabs(new_zoom);
 
    me->zoom_pixel_m = new_zoom;
    printf(" %.2f pixel/m\n", me->zoom_pixel_m);

    free(zoom_str);

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

/* ===== CALLBACKS POUR L'AFFICHAGE ===== */

void toggle_points(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_points = !me->show_points;
    printf("Point display: %s\n", me->show_points ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_panels(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_panels = !me->show_panels;
    printf("Panel display: %s\n", me->show_panels ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_cables(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_cables = !me->show_cables;
    printf("Cable display: %s\n", me->show_cables ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_links(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_links = !me->show_links;
    printf("Interconnection display: %s\n", me->show_links ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_axes(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_axes = !me->show_axes;
    printf("Axes display: %s\n", me->show_axes ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

/* ===== CALLBACKS POUR L'AFFICHAGE DES NUMÉROS ===== */

void toggle_point_numbers(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_point_numbers = !me->show_point_numbers;
    printf("Point numbers display: %s\n", me->show_point_numbers ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_panel_numbers(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_panel_numbers = !me->show_panel_numbers;
    printf("Panel numbers display: %s\n", me->show_panel_numbers ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_cable_numbers(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_cable_numbers = !me->show_cable_numbers;
    printf("Cable numbers display: %s\n", me->show_cable_numbers ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_link_numbers(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_link_numbers = !me->show_link_numbers;
    printf("Interconnection numbers display: %s\n", me->show_link_numbers ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

/* ===== CALLBACKS POUR L'AFFICHAGE DES TYPES ===== */

void toggle_point_types(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_point_types = !me->show_point_types;
    printf("Affichage des types de points: %s\n", me->show_point_types ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_panel_types(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_panel_types = !me->show_panel_types;
    printf("Affichage des types de paneles: %s\n", me->show_panel_types ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_edge_types(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_edge_types = !me->show_edge_types;
    printf("Edge types display: %s\n", me->show_edge_types ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void toggle_cable_types(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->show_cable_types = !me->show_cable_types;
    printf("Cable types display: %s\n", me->show_cable_types ? "ON" : "OFF");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

/* ===== CALLBACKS POUR FILE (SAVE/LOAD) ===== */

/* Fonction auxiliaire pour DFS (parcours en profondeur) */
void dfs_interconnection(int node, int *visited, int adjacency[MAX_POINTS][MAX_POINTS],
                         int *component, int *comp_size, int num_points)
{
    int i;
    visited[node] = 1;
    component[(*comp_size)++] = node;

    for (i = 0; i < num_points; i++) {
        if (adjacency[node][i] && !visited[i]) {
            dfs_interconnection(i, visited, adjacency, component, comp_size, num_points);
        }
    }
}

void save_file(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    char *filename;
    FILE *fp;
    int i, j;

    filename = GetString("Filename to save:", me->current_filename);

    if (!filename) {
        printf("Save cancelled\n");
        return;
    }

    fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: cannot open file %s\n", filename);
        free(filename);
        return;
    }

    /* Sauvegarder le plan de vue */
    fprintf(fp, "VIEW_PLANE %d\n", me->view_plane);

    /* Sauvegarder les points */
    fprintf(fp, "POINTS %d\n", me->num_points);
    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used) {
            fprintf(fp, "%d %d %d %d %.6f %.6f\n", me->points[i].x, me->points[i].y, me->points[i].z, me->points[i].type,
                    me->points[i].u, me->points[i].v);
        }
    }

    /* Sauvegarder les paneles */
    fprintf(fp, "PANELS %d\n", me->num_panels);
    for (i = 0; i < me->num_panels; i++) {
        fprintf(fp, "%d %d %d", me->panels[i].num_points, me->panels[i].closed, me->panels[i].type);
        /* Sauvegarder les indices des points (numérotation à partir de 1) */
        for (j = 0; j < me->panels[i].num_points; j++) {
            fprintf(fp, " %d", me->panels[i].points[j] + 1);
        }
        /* Sauvegarder les types des côtés */
        for (j = 0; j < me->panels[i].num_points; j++) {
            fprintf(fp, " %d", me->panels[i].edge_types[j]);
        }
        fprintf(fp, "\n");
    }

    /* Sauvegarder les cables */
    fprintf(fp, "CABLES %d\n", me->num_cables);
    for (i = 0; i < me->num_cables; i++) {
        fprintf(fp, "%d %d %d\n", me->cables[i].p1 + 1, me->cables[i].p2 + 1, me->cables[i].type);
    }

    /* Trouver et sauvegarder les interconnections (composantes connexes) */
    if (me->num_links > 0) {
        /* Allouer dynamiquement pour éviter stack overflow */
        int (*adjacency)[MAX_POINTS] = calloc(MAX_POINTS, sizeof(int[MAX_POINTS]));
        int *visited = calloc(MAX_POINTS, sizeof(int));
        int (*components)[MAX_POINTS] = calloc(MAX_LINKS, sizeof(int[MAX_POINTS]));
        int comp_sizes[MAX_LINKS] = {0};
        int num_components = 0;

        if (!adjacency || !visited || !components) {
            printf("Error: memory allocation failed\n");
            if (adjacency) free(adjacency);
            if (visited) free(visited);
            if (components) free(components);
            fclose(fp);
            free(filename);
            return;
        }

        /* Construire la matrice d'adjacence */
        for (i = 0; i < me->num_links; i++) {
            int p1 = me->links[i].p1;
            int p2 = me->links[i].p2;
            adjacency[p1][p2] = 1;
            adjacency[p2][p1] = 1;
        }

        /* Trouver les composantes connexes avec DFS */
        for (i = 0; i < me->num_points; i++) {
            if (me->points[i].used && !visited[i]) {
                int has_link = 0;
                /* Vérifier si ce nœud a au moins un lien */
                for (j = 0; j < me->num_points; j++) {
                    if (adjacency[i][j]) {
                        has_link = 1;
                        break;
                    }
                }

                if (has_link) {
                    comp_sizes[num_components] = 0;
                    dfs_interconnection(i, visited, adjacency, components[num_components],
                                      &comp_sizes[num_components], me->num_points);
                    num_components++;
                }
            }
        }

        /* Sauvegarder au format INTERCONNECTIONS (numérotation à partir de 1) */
        fprintf(fp, "INTERCONNECTIONS %d\n", num_components);
        for (i = 0; i < num_components; i++) {
            fprintf(fp, "%d", comp_sizes[i]);
            for (j = 0; j < comp_sizes[i]; j++) {
                fprintf(fp, " %d", components[i][j] + 1);
            }
            fprintf(fp, "\n");
        }

        /* Libérer la mémoire */
        free(adjacency);
        free(visited);
        free(components);
    } else {
        fprintf(fp, "INTERCONNECTIONS 0\n");
    }

    fclose(fp);

    /* Créer et sauvegarder le fichier .don associé */
    {
        char don_filename[512];
        char *dot;
        FILE *fp_don;

        /* Copier le nom de fichier et remplacer l'extension par .don */
        strncpy(don_filename, filename, sizeof(don_filename) - 1);
        don_filename[sizeof(don_filename) - 1] = '\0';

        dot = strrchr(don_filename, '.');
        if (dot != NULL) {
            strcpy(dot, ".don");
        } else {
            strcat(don_filename, ".don");
        }

        /* Ouvrir et écrire dans le fichier .don */
        fp_don = fopen(don_filename, "w");
        if (fp_don) {
            int panel_num, node_num, pt_idx;

            fprintf(fp_don, "design in the plane normal to axis: %d\n\n", me->view_plane);
            fprintf(fp_don, "panels number: %d\n\n", me->num_panels);
	    printf("me->zoom_pixel_m=%f\n", me->zoom_pixel_m);
            /* Écrire les informations pour chaque panele */
            for (panel_num = 0; panel_num < me->num_panels; panel_num++) {
                fprintf(fp_don, "Panel: %d\n", panel_num + 1);
                fprintf(fp_don, "number of nodes around: %d\n", me->panels[panel_num].num_points);
                fprintf(fp_don, "nodes of the contour no x y z U V type and following type:\n");

                /* Écrire les informations de chaque point du panele */
                for (node_num = 0; node_num < me->panels[panel_num].num_points; node_num++) {
                    pt_idx = me->panels[panel_num].points[node_num];
                    fprintf(fp_don, "%d    %f    %f    %f    %f    %f    %d    %d\n",
                            node_num + 1,
                            (double)(me->points[pt_idx].x/me->zoom_pixel_m),
                            (double)(me->points[pt_idx].y/me->zoom_pixel_m),
                            (double)(me->points[pt_idx].z/me->zoom_pixel_m),
                            me->points[pt_idx].u,
                            me->points[pt_idx].v,
                            me->points[pt_idx].type,
                            me->panels[panel_num].edge_types[node_num]);
                }

                /* Écrire les paramètres physiques du panneau */
                fprintf(fp_don, "Traction stiffness (N):            25000.000000\n");
                fprintf(fp_don, "Compression stiffness (N):        1.000000\n");
                fprintf(fp_don, "Mesh opening stiffness (N.m/rad):    0.000000\n");
                fprintf(fp_don, "Unstretched length (m):            0.400000\n");
                fprintf(fp_don, "Volumic mass (kg/m3):            1025.000000\n");
                fprintf(fp_don, "Hydrodynamic diameter (m):        0.002800\n");
                fprintf(fp_don, "Knot size (m):                0.000000\n");
                fprintf(fp_don, "Normal Cd:                1.200000\n");
                fprintf(fp_don, "Tangential Cd:                0.080000\n");
                fprintf(fp_don, "Meshing step (m):            3.000000\n");
                fprintf(fp_don, "Type of internal nodes:            %d\n", me->panels[panel_num].type);
                fprintf(fp_don, "Meshing type:                2\n\n");
            }

            /* Écrire les informations sur les panneaux hexagonaux et les câbles */
            fprintf(fp_don, "hexagonal panels number: 0\n\n");
            fprintf(fp_don, "Cables number: %d\n\n", me->num_cables);

            /* Écrire les informations pour chaque cable (câble) */
            for (i = 0; i < me->num_cables; i++) {
                int p1_idx = me->cables[i].p1;
                int p2_idx = me->cables[i].p2;

                fprintf(fp_don, "Cable: %d\n", i + 1);
                fprintf(fp_don, "Extremities no x y z type:\n");
                fprintf(fp_don, "1  %f  %f  %f  %d\n",
                        (double)(me->points[p1_idx].x/me->zoom_pixel_m),
                        (double)(me->points[p1_idx].y/me->zoom_pixel_m),
                        (double)(me->points[p1_idx].z/me->zoom_pixel_m),
                        me->points[p1_idx].type);
                fprintf(fp_don, "2  %f  %f  %f  %d\n",
                        (double)(me->points[p2_idx].x/me->zoom_pixel_m),
                        (double)(me->points[p2_idx].y/me->zoom_pixel_m),
                        (double)(me->points[p2_idx].z/me->zoom_pixel_m),
                        me->points[p2_idx].type);
                fprintf(fp_don, "Traction stiffness (N):        62000000.000000\n");
                fprintf(fp_don, "Compression stiffness (N):    1.000000\n");
                fprintf(fp_don, "Unstretched length (m):        200.000000\n");
                fprintf(fp_don, "Volumic mass (kg/m3):        4800.000000\n");
                fprintf(fp_don, "Hydrodynamic diameter (m):    0.026000\n");
                fprintf(fp_don, "Normal Cd:            1.800000\n");
                fprintf(fp_don, "Tangential Cd:            0.080000\n");
                fprintf(fp_don, "Bars number:            9\n");
                fprintf(fp_don, "Type of internal nodes:        %d\n\n", me->cables[i].type);
            }

            /* Calculer le nombre d'interconnections (composantes connexes) */
            int num_interconnections = 0;
            if (me->num_links > 0) {
                int (*adjacency)[MAX_POINTS] = calloc(MAX_POINTS, sizeof(int[MAX_POINTS]));
                int *visited = calloc(MAX_POINTS, sizeof(int));
                int (*components)[MAX_POINTS] = calloc(MAX_LINKS, sizeof(int[MAX_POINTS]));
                int comp_sizes[MAX_LINKS] = {0};

                if (!adjacency || !visited || !components) {
                    printf("Error: memory allocation failed in .don file generation\n");
                    if (adjacency) free(adjacency);
                    if (visited) free(visited);
                    if (components) free(components);
                    goto skip_don_interconnections;
                }

                /* Construire la matrice d'adjacence */
                for (i = 0; i < me->num_links; i++) {
                    int p1 = me->links[i].p1;
                    int p2 = me->links[i].p2;
                    adjacency[p1][p2] = 1;
                    adjacency[p2][p1] = 1;
                }

                /* Trouver les composantes connexes avec DFS */
                for (i = 0; i < me->num_points; i++) {
                    if (me->points[i].used && !visited[i]) {
                        int has_link = 0;
                        /* Vérifier si ce nœud a au moins un lien */
                        for (j = 0; j < me->num_points; j++) {
                            if (adjacency[i][j]) {
                                has_link = 1;
                                break;
                            }
                        }

                        if (has_link) {
                            comp_sizes[num_interconnections] = 0;
                            dfs_interconnection(i, visited, adjacency, components[num_interconnections],
                                              &comp_sizes[num_interconnections], me->num_points);
                            num_interconnections++;
                        }
                    }
                }

                /* Libérer la mémoire */
                free(adjacency);
                free(visited);
                free(components);
            }

skip_don_interconnections:
            /* Écrire les informations sur les câbles coulissants et les liens */
            fprintf(fp_don, "Sliding cables number: 0\n\n");
            fprintf(fp_don, "links number: %d\n", num_interconnections);

            /* Écrire les détails de chaque interconnexion */
            if (num_interconnections > 0) {
                int (*adjacency)[MAX_POINTS] = calloc(MAX_POINTS, sizeof(int[MAX_POINTS]));
                int *visited = calloc(MAX_POINTS, sizeof(int));
                int (*components)[MAX_POINTS] = calloc(MAX_LINKS, sizeof(int[MAX_POINTS]));
                int comp_sizes[MAX_LINKS] = {0};
                int interco_num = 0;

                if (!adjacency || !visited || !components) {
                    printf("Error: memory allocation failed in .don interconnection details\n");
                    if (adjacency) free(adjacency);
                    if (visited) free(visited);
                    if (components) free(components);
                    goto skip_don_details;
                }

                /* Reconstruire la matrice d'adjacence et les composantes */
                for (i = 0; i < me->num_links; i++) {
                    int p1 = me->links[i].p1;
                    int p2 = me->links[i].p2;
                    adjacency[p1][p2] = 1;
                    adjacency[p2][p1] = 1;
                }

                for (i = 0; i < me->num_points; i++) {
                    if (me->points[i].used && !visited[i]) {
                        int has_link = 0;
                        for (j = 0; j < me->num_points; j++) {
                            if (adjacency[i][j]) {
                                has_link = 1;
                                break;
                            }
                        }

                        if (has_link) {
                            comp_sizes[interco_num] = 0;
                            dfs_interconnection(i, visited, adjacency, components[interco_num],
                                              &comp_sizes[interco_num], me->num_points);

                            /* Écrire les détails de cette interconnexion */
                            fprintf(fp_don, "nb_pt :%d    ", comp_sizes[interco_num]);

                            /* Pour chaque point de l'interconnexion */
                            for (j = 0; j < comp_sizes[interco_num]; j++) {
                                int pt_idx = components[interco_num][j];

                                /* Chercher le point dans les cables */
                                int seg_num, found_in_cable = 0;
                                for (seg_num = 0; seg_num < me->num_cables; seg_num++) {
                                    if (me->cables[seg_num].p1 == pt_idx) {
                                        fprintf(fp_don, "el: %d    nd: 1    ", seg_num + 1);
                                        found_in_cable = 1;
                                        break;
                                    } else if (me->cables[seg_num].p2 == pt_idx) {
                                        fprintf(fp_don, "el: %d    nd: 2    ", seg_num + 1);
                                        found_in_cable = 1;
                                        break;
                                    }
                                }

                                /* Si pas trouvé dans les cables, chercher dans les paneles */
                                if (!found_in_cable) {
                                    int poly_num, node_num;
                                    for (poly_num = 0; poly_num < me->num_panels; poly_num++) {
                                        for (node_num = 0; node_num < me->panels[poly_num].num_points; node_num++) {
                                            if (me->panels[poly_num].points[node_num] == pt_idx) {
                                                fprintf(fp_don, "pa: %d    nd: %d    ", poly_num + 1, node_num + 1);
                                                goto next_point;
                                            }
                                        }
                                    }
                                }
                                next_point:;
                            }

                            fprintf(fp_don, "\n");
                            interco_num++;
                        }
                    }
                }

                /* Libérer la mémoire */
                free(adjacency);
                free(visited);
                free(components);
            }

skip_don_details:
            /* Écrire l'ordre de maillage */
            fprintf(fp_don, "\nMeshing order:\n");

            /* Écrire tous les paneles */
            for (i = 0; i < me->num_panels; i++) {
                fprintf(fp_don, "pa:    %d  ", i + 1);
            }
            if (me->num_panels > 0) {
                fprintf(fp_don, "\n");
            }

            /* Écrire tous les cables */
            for (i = 0; i < me->num_cables; i++) {
                fprintf(fp_don, "el:     %d ", i + 1);
            }
            if (me->num_cables > 0) {
                fprintf(fp_don, "\n");
            }

            /* Calculer le nombre maximum de types de nœuds */
            int max_node_type = 0;
            for (i = 0; i < me->num_points; i++) {
                if (me->points[i].used && me->points[i].type > max_node_type) {
                    max_node_type = me->points[i].type;
                }
            }

            /* Écrire le nombre de types de nœuds */
            fprintf(fp_don, "\nNumber of types of nodes: %d\n\n", max_node_type);

            /* Écrire les informations pour chaque type de nœud */
            for (i = 1; i <= max_node_type; i++) {
                fprintf(fp_don, "No du type :            %d\n", i);
                fprintf(fp_don, "Mass X,Y,Z (kg):        0.000000  0.000000  0.000000\n");
                fprintf(fp_don, "Added mass X,Y,Z (kg):        0.000000  0.000000  0.000000\n");
                fprintf(fp_don, "Length X,Y,Z (m):        0.000000  0.000000  0.000000\n");
                fprintf(fp_don, "Drag coefficient X,Y,Z:        1.200000  1.200000  1.200000\n");
                fprintf(fp_don, "External forces X,Y,Z (N):    0.000000  0.000000  0.000000\n");
                fprintf(fp_don, "Displacement X,Y,Z:        1  1  1\n");
                fprintf(fp_don, "Limits X,Y,Z (m):        0.000000  0.000000  0.000000\n");
                fprintf(fp_don, "Limits sens X,Y,Z:        0  0  0\n");
                fprintf(fp_don, "Symetry X,Y,Z:            0  0  0\n\n");
            }

            /* Écrire l'environnement numérique et les paramètres */
            fprintf(fp_don, "NUMERIC ENVIRONMENT\n");
            fprintf(fp_don, "Divisor (s):                        0.000050\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Convergence threshold (N):                0.0100000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Displacement limit for each iteration (m):        10.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Maximal number of iterations:                10000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Dynamic: Time step (s):                    0.100000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Dynamic: Record time step (s):                0.200000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Dynamic: Beginning time of record (s):            0.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Dynamic: End time of record and calculation (s):    0.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "METEO/OCEANIC ENVIRONMENT\n");
            fprintf(fp_don, "Current direction (deg):                0.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Current speed (m/s):                    2.058000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Wave period (s):                    10.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Wave height (m):                    0.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Wave direction relatively X (deg):            0.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Depth (m):                        2000.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "CATCH DESCRIPTION\n");
            fprintf(fp_don, "Volume (m3):                        0.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Accuracy on this volume:                0.000010\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Drag coefficient on this volume:            1.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "BOTTOM SEA ENVIRONMENT\n");
            fprintf(fp_don, "Wearing coefficient on the bottom:            0.500000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Stiffness of the insertion in the sea bottom (N/m):    5000000.000000\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "TEXT OUTPUT\n");
            fprintf(fp_don, "Distances number         :    0\n");
            fprintf(fp_don, "Forces number             :    0\n");
            fprintf(fp_don, "Tensions number         :    0\n");
            fprintf(fp_don, "Sliding tensions number     :    0\n");
            fprintf(fp_don, "Positions number         :    0\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "Structure forces display         : 1\n");
            fprintf(fp_don, "Catch diameter display             : 1\n");
            fprintf(fp_don, "Catch thickness display             : 1\n");
            fprintf(fp_don, "Catch volume display             : 1\n");
            fprintf(fp_don, "Filtrated surface display         : 1\n");
            fprintf(fp_don, "Speed display                 : 1\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "\n");
            fprintf(fp_don, "input Auto_convergence\n");
            fprintf(fp_don, "input convergence_parameters 1 10 100000000000\n");
            fprintf(fp_don, "input link 0.5\n");

            fclose(fp_don);
            printf("DON file saved: %s\n", don_filename);
        } else {
            printf("Warning: could not create DON file %s\n", don_filename);
        }
    }

    /* Sauvegarder le nom du fichier sauvegardé */
    strncpy(me->current_filename, filename, sizeof(me->current_filename) - 1);
    me->current_filename[sizeof(me->current_filename) - 1] = '\0';

    printf("File saved: %s\n", filename);

    /* Libérer la mémoire allouée par GetString */
    free(filename);
}

/* Fonction auxiliaire pour charger un fichier spécifique */
void load_specific_file(char *filename, MyProgram *me)
{
    FILE *fp;
    char line[256];
    int i, j, n;

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Error: cannot open file %s\n", filename);
        return;
    }

    /* Effacer les données actuelles */
    me->num_points = 0;
    me->num_panels = 0;
    me->num_cables = 0;
    me->num_links = 0;
    for (i = 0; i < MAX_POINTS; i++) {
        me->points[i].used = FALSE;
    }

    /* Charger le plan de vue (si présent, sinon garder la valeur actuelle) */
    if (fgets(line, sizeof(line), fp)) {
        int view_plane_val;
        if (sscanf(line, "VIEW_PLANE %d", &view_plane_val) == 1) {
            me->view_plane = view_plane_val;
            /* Lire la ligne suivante pour les POINTS */
            fgets(line, sizeof(line), fp);
        }
        /* Sinon, la ligne actuelle devrait être "POINTS ..." */
    }

    /* Charger les points */
    if (sscanf(line, "POINTS %d", &n) == 1) {
        me->num_points = n;
        for (i = 0; i < n; i++) {
            if (fgets(line, sizeof(line), fp)) {
                int type = 1; /* valeur par défaut */
                int z = 0;    /* valeur par défaut */
                double u, v;
                int num_read = sscanf(line, "%d %d %d %d %lf %lf",
                                     &me->points[i].x, &me->points[i].y, &z, &type, &u, &v);
                if (num_read >= 2) {
                    me->points[i].z = (num_read >= 3) ? z : 0;
                    me->points[i].type = (num_read >= 4) ? type : 1;
                    me->points[i].used = TRUE;
                    me->points[i].selected = FALSE;
                    /* Si u,v sont présents, les utiliser, sinon défaut selon plan de vue */
                    if (num_read >= 6) {
                        me->points[i].u = u;
                        me->points[i].v = v;
                    } else {
                        /* Initialiser u,v selon le plan de vue */
                        switch (me->view_plane) {
                            case 1:  /* Normal=X : u=Y, v=Z */
                                me->points[i].u = (double)me->points[i].y;
                                me->points[i].v = (double)me->points[i].z;
                                break;
                            case 2:  /* Normal=Y : u=Z, v=X */
                                me->points[i].u = (double)me->points[i].z;
                                me->points[i].v = (double)me->points[i].x;
                                break;
                            case 3:  /* Normal=Z : u=X, v=Y */
                            default:
                                me->points[i].u = (double)me->points[i].x;
                                me->points[i].v = (double)me->points[i].y;
                                break;
                        }
                    }
                }
            }
        }
    }

    /* Charger les paneles */
    if (fgets(line, sizeof(line), fp) && sscanf(line, "PANELS %d", &n) == 1) {
        me->num_panels = n;
        for (i = 0; i < n; i++) {
            if (fgets(line, sizeof(line), fp)) {
                char *ptr = line;
                int num_pts, closed, poly_type = 1;  /* type par défaut = 1 */
                int k;

                /* Essayer de lire avec le type (nouveau format) */
                if (sscanf(ptr, "%d %d %d", &num_pts, &closed, &poly_type) >= 2) {
                    me->panels[i].num_points = num_pts;
                    me->panels[i].closed = closed;
                    me->panels[i].type = poly_type;
                }

                /* Avancer le pointeur après les trois premiers entiers */
                ptr = strchr(ptr, ' ');
                if (ptr) ptr = strchr(ptr+1, ' ');
                if (ptr) ptr = strchr(ptr+1, ' ');

                /* Lire les indices des points (numérotation à partir de 1 dans le fichier) */
                for (j = 0; j < num_pts && ptr; j++) {
                    int pt_idx;
                    sscanf(ptr, "%d", &pt_idx);
                    me->panels[i].points[j] = pt_idx - 1;
                    ptr = strchr(ptr+1, ' ');
                }

                /* Lire les types des côtés (si présents, sinon défaut = 1) */
                for (k = 0; k < num_pts; k++) {
                    if (ptr) {
                        int edge_type;
                        sscanf(ptr, "%d", &edge_type);
                        me->panels[i].edge_types[k] = edge_type;
                        ptr = strchr(ptr+1, ' ');
                    } else {
                        me->panels[i].edge_types[k] = 1;  /* défaut */
                    }
                }
            }
        }
    }

    /* Charger les cables */
    if (fgets(line, sizeof(line), fp) && sscanf(line, "CABLES %d", &n) == 1) {
        me->num_cables = n;
        for (i = 0; i < n; i++) {
            if (fgets(line, sizeof(line), fp)) {
                int p1, p2, seg_type = 1;  /* type par défaut = 1 */
                /* Essayer de lire avec le type (nouveau format), sinon ancien format */
                /* Numérotation à partir de 1 dans le fichier */
                if (sscanf(line, "%d %d %d", &p1, &p2, &seg_type) >= 2) {
                    me->cables[i].p1 = p1 - 1;
                    me->cables[i].p2 = p2 - 1;
                    me->cables[i].type = seg_type;
                }
            }
        }
    }

    /* Charger les interconnections (nouveau format) ou les liens (ancien format) */
    if (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "INTERCONNECTIONS %d", &n) == 1) {
            /* Nouveau format: INTERCONNECTIONS (numérotation à partir de 1 dans le fichier) */
            me->num_links = 0;
            for (i = 0; i < n; i++) {
                if (fgets(line, sizeof(line), fp)) {
                    char *ptr = line;
                    int num_nodes, nodes[MAX_POINTS];
                    int k;

                    /* Lire le nombre de nœuds */
                    sscanf(ptr, "%d", &num_nodes);
                    ptr = strchr(ptr, ' ');

                    /* Lire tous les nœuds de cette interconnection */
                    for (j = 0; j < num_nodes && ptr; j++) {
                        sscanf(ptr, "%d", &nodes[j]);
                        nodes[j]--;  /* Convertir de 1-based à 0-based */
                        ptr = strchr(ptr+1, ' ');
                    }

                    /* Reconstruire les liens entre nœuds consécutifs */
                    for (k = 0; k < num_nodes - 1; k++) {
                        if (me->num_links < MAX_LINKS) {
                            me->links[me->num_links].p1 = nodes[k];
                            me->links[me->num_links].p2 = nodes[k+1];
                            me->num_links++;
                        }
                    }
                }
            }
        } else if (sscanf(line, "LINKS %d", &n) == 1) {
            /* Ancien format: LINKS (compatibilité) - numérotation à partir de 1 dans le fichier */
            me->num_links = n;
            for (i = 0; i < n; i++) {
                if (fgets(line, sizeof(line), fp)) {
                    int p1, p2;
                    sscanf(line, "%d %d", &p1, &p2);
                    me->links[i].p1 = p1 - 1;
                    me->links[i].p2 = p2 - 1;
                }
            }
        }
    }

    fclose(fp);

    /* Sauvegarder le nom du fichier chargé */
    strncpy(me->current_filename, filename, sizeof(me->current_filename) - 1);
    me->current_filename[sizeof(me->current_filename) - 1] = '\0';

    printf("File loaded: %s\n", filename);
    printf("  Points: %d, Panels: %d, Cables: %d, Links: %d\n",
           me->num_points, me->num_panels, me->num_cables, me->num_links);

    /* Redessiner */
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void load_file(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    char *filename;
    DIR *dir;
    struct dirent *entry;
    char prompt[1024];
    char file_list[768];

    /* Scanner le répertoire pour les files .dat */
    file_list[0] = '\0';
    dir = opendir(".");
    if (dir) {
        strcat(file_list, "Available files:\n");
        while ((entry = readdir(dir)) != NULL) {
            if (strstr(entry->d_name, ".dat") != NULL) {
                if (strlen(file_list) < 700) {  /* Éviter débordement */
                    strcat(file_list, "  - ");
                    strcat(file_list, entry->d_name);
                    strcat(file_list, "\n");
                }
            }
        }
        closedir(dir);
    }

    /* Créer le prompt avec la liste */
    if (strlen(file_list) > 0) {
        snprintf(prompt, sizeof(prompt), "%s\nFilename to load:", file_list);
    } else {
        snprintf(prompt, sizeof(prompt), "Filename to load:");
    }

    filename = GetString(prompt, me->current_filename);
    if (!filename) {
        printf("Load cancelled\n");
        return;
    }

    /* Utiliser la fonction auxiliaire pour charger le fichier */
    load_specific_file(filename, me);
    free(filename);
}

/* ===== MODE ALIGNEMENT ===== */

void mode_modify_uv(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->current_mode = MODE_MODIFY_UV;
    me->current_poly = -1;
    me->temp_point = -1;
    me->selecting = FALSE;
    me->num_selected = 0;
    me->selected_poly = -1;
    me->selected_edge = -1;

    printf("Mode: Modify UV - Click on a panel edge\n");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void mode_modify_panel(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->current_mode = MODE_MODIFY_PANEL;
    me->current_poly = -1;
    me->temp_point = -1;
    me->selecting = FALSE;
    me->num_selected = 0;
    me->selected_poly = -1;
    me->selected_edge = -1;

    printf("Mode: Modify UV - Click on a panel edge\n");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void mode_modify_z(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->current_mode = MODE_MODIFY_Z;
    me->current_poly = -1;
    me->temp_point = -1;
    me->selecting = FALSE;
    me->num_selected = 0;
    me->selected_poly = -1;
    me->selected_edge = -1;

    printf("Mode: Modify Z - Click on a point\n");

        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void mode_align(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    me->current_mode = MODE_ALIGN;
    me->current_poly = -1;
    me->temp_point = -1;
    me->selecting = FALSE;
    me->num_selected = 0;

    /* Désélectionner tous les points */
    int i;
    for (i = 0; i < me->num_points; i++) {
        me->points[i].selected = FALSE;
    }
    
    printf("Mode: Alignment\n");
    printf("Draw a rectangle to select points\n");
    
    /* Redessiner pour enlever les sélections */
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

/* ===== CALLBACKS POUR L'ALIGNEMENT ===== */

void align_modify_x(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    char *value_str;
    char prompt[256];
    int new_x, i;
    double sum = 0.0, mean = 0.0, variance = 0.0, stddev = 0.0;

    if (me->num_selected == 0) {
        printf("No point selected\n");
        return;
    }

    /* Sauvegarder l'état pour undo */
    save_state(me);

    /* Calculer la moyenne */
    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            sum += me->points[i].x;
        }
    }
    mean = sum / me->num_selected;

    /* Calculer l'écart-type */
    sum = 0.0;
    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            double diff = me->points[i].x - mean;
            sum += diff * diff;
        }
    }
    variance = sum / me->num_selected;
    stddev = sqrt(variance);

    /* Afficher les statistiques */
    printf("X Statistics: Mean=%.2f, StdDev=%.2f (%d points)\n",
           mean, stddev, me->num_selected);

    /* Créer le prompt avec les statistiques */
    sprintf(prompt, "Current X: Mean=%.1f, StdDev=%.1f\nNew X coordinate:",
            mean, stddev);

    char default_val[128];
    sprintf(default_val, "%.0lf", mean);

    value_str = GetString(prompt, default_val);

    //value_str = GetString(prompt, "109");
    if (!value_str) {
        printf("Modification cancelled\n");
        return;
    }

    new_x = atoi(value_str);

    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            me->points[i].x = new_x;
        }
    }

    printf("%d points aligned on X=%d\n", me->num_selected, new_x);

    free(value_str);

    /* Redessiner */
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void align_modify_y(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    char *value_str;
    char prompt[256];
    int new_y, i;
    double sum = 0.0, mean = 0.0, variance = 0.0, stddev = 0.0;

    if (me->num_selected == 0) {
        printf("No point selected\n");
        return;
    }

    /* Sauvegarder l'état pour undo */
    save_state(me);

    /* Calculer la moyenne */
    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            sum += me->points[i].y;
        }
    }
    mean = sum / me->num_selected;

    /* Calculer l'écart-type */
    sum = 0.0;
    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            double diff = me->points[i].y - mean;
            sum += diff * diff;
        }
    }
    variance = sum / me->num_selected;
    stddev = sqrt(variance);

    /* Afficher les statistiques */
    printf("Y Statistics: Mean=%.2f, StdDev=%.2f (%d points)\n",
           mean, stddev, me->num_selected);

    /* Créer le prompt avec les statistiques */
    sprintf(prompt, "Current Y: Mean=%.1f, StdDev=%.1f\nNew Y coordinate:",
            mean, stddev);

    char default_val[128];
    sprintf(default_val, "%.0lf", mean);

    value_str = GetString(prompt, default_val);
    //value_str = GetString(prompt, "100");
    if (!value_str) {
        printf("Modification cancelled\n");
        return;
    }

    new_y = atoi(value_str);

    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            me->points[i].y = new_y;
        }
    }

    printf("%d points aligned on Y=%d\n", me->num_selected, new_y);

    free(value_str);

    /* Redessiner */
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void align_modify_z(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    char *value_str;
    char prompt[256];
    int new_z, i;
    double sum = 0.0, mean = 0.0, variance = 0.0, stddev = 0.0;

    if (me->num_selected == 0) {
        printf("No point selected\n");
        return;
    }

    /* Sauvegarder l'état pour undo */
    save_state(me);

    /* Calculer la moyenne */
    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            sum += me->points[i].z;
        }
    }
    mean = sum / me->num_selected;

    /* Calculer l'écart-type */
    sum = 0.0;
    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            double diff = me->points[i].z - mean;
            sum += diff * diff;
        }
    }
    variance = sum / me->num_selected;
    stddev = sqrt(variance);

    /* Afficher les statistiques */
    printf("Z Statistics: Mean=%.2f, StdDev=%.2f (%d points)\n",
           mean, stddev, me->num_selected);

    /* Créer le prompt avec les statistiques */
    sprintf(prompt, "Current Z: Mean=%.1f, StdDev=%.1f\nNew Z coordinate:",
            mean, stddev);

    char default_val[128];
    sprintf(default_val, "%.0lf", mean);

    value_str = GetString(prompt, default_val);
    //value_str = GetString(prompt, "100");
    if (!value_str) {
        printf("Modification cancelled\n");
        return;
    }

    new_z = atoi(value_str);

    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            me->points[i].z = new_z;
        }
    }

    printf("%d points aligned on Z=%d\n", me->num_selected, new_z);

    free(value_str);

    /* Redessiner */
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void align_modify_type(Widget w, void *data)
{
    MyProgram *me = (MyProgram *)data;
    char *value_str;
    int new_type, i, j;
    int num_points_changed = 0;
    int num_panels_changed = 0;
    int num_edges_changed = 0;
    int num_cables_changed = 0;

    if (me->num_selected == 0) {
        printf("No point selected\n");
        return;
    }

    /* Sauvegarder l'état pour undo */
    save_state(me);

    value_str = GetString("New type (selected points/panels/edges/cables):", "1");
    if (!value_str) {
        printf("Modification cancelled\n");
        return;
    }

    new_type = atoi(value_str);

    /* Modifier le type des points selected */
    for (i = 0; i < me->num_points; i++) {
        if (me->points[i].used && me->points[i].selected) {
            me->points[i].type = new_type;
            num_points_changed++;
        }
    }

    /* Modifier le type des paneles si tous leurs points sont sélectionnés */
    for (i = 0; i < me->num_panels; i++) {
        int all_selected = 1;
        if (me->panels[i].num_points == 0) continue;

        /* Vérifier si tous les points du panele sont sélectionnés */
        for (j = 0; j < me->panels[i].num_points; j++) {
            int p_idx = me->panels[i].points[j];
            if (!me->points[p_idx].selected) {
                all_selected = 0;
                break;
            }
        }

        if (all_selected) {
            me->panels[i].type = new_type;
            num_panels_changed++;
        }
    }

    /* Modifier le type des côtés des paneles si les deux extrémités sont sélectionnées */
    for (i = 0; i < me->num_panels; i++) {
        for (j = 0; j < me->panels[i].num_points; j++) {
            int p1 = me->panels[i].points[j];
            int p2 = me->panels[i].points[(j+1) % me->panels[i].num_points];

            /* Si c'est le dernier côté d'un panele non fermé, on ne le traite pas */
            if (j == me->panels[i].num_points - 1 && !me->panels[i].closed) {
                continue;
            }

            /* Si les deux extrémités du côté sont sélectionnées */
            if (me->points[p1].selected && me->points[p2].selected) {
                me->panels[i].edge_types[j] = new_type;
                num_edges_changed++;
            }
        }
    }

    /* Modifier le type des cables si les deux extrémités sont sélectionnées */
    for (i = 0; i < me->num_cables; i++) {
        int p1 = me->cables[i].p1;
        int p2 = me->cables[i].p2;

        if (me->points[p1].selected && me->points[p2].selected) {
            me->cables[i].type = new_type;
            num_cables_changed++;
        }
    }

    printf("Type %d applied: %d points, %d panels, %d edges, %d cables\n",
           new_type, num_points_changed, num_panels_changed,
           num_edges_changed, num_cables_changed);

    free(value_str);

    /* Redessiner */
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

/* ===== FONCTIONS POUR UNDO (Ctrl+Z) ===== */

void save_state(MyProgram *me)
{
    int i;

    /* Si le stack est plein, décaler tous les états vers le bas */
    if (me->undo_count >= MAX_UNDO) {
        for (i = 0; i < MAX_UNDO - 1; i++) {
            me->undo_stack[i] = me->undo_stack[i + 1];
        }
        me->undo_count = MAX_UNDO - 1;
    }

    /* Sauvegarder l'état actuel au sommet du stack */
    UndoState *state = &me->undo_stack[me->undo_count];

    /* Copier tous les points */
    for (i = 0; i < MAX_POINTS; i++) {
        state->points[i] = me->points[i];
    }
    state->num_points = me->num_points;

    /* Copier tous les paneles */
    for (i = 0; i < MAX_PANELS; i++) {
        state->panels[i] = me->panels[i];
    }
    state->num_panels = me->num_panels;

    /* Copier tous les cables */
    for (i = 0; i < MAX_CABLES; i++) {
        state->cables[i] = me->cables[i];
    }
    state->num_cables = me->num_cables;

    /* Copier tous les liens */
    for (i = 0; i < MAX_LINKS; i++) {
        state->links[i] = me->links[i];
    }
    state->num_links = me->num_links;

    me->undo_count++;
}

void undo_action(MyProgram *me)
{
    int i;

    if (me->undo_count == 0) {
        printf("No action to undo\n");
        return;
    }

    /* Récupérer le dernier état sauvegardé */
    me->undo_count--;
    UndoState *state = &me->undo_stack[me->undo_count];

    /* Restaurer tous les points */
    for (i = 0; i < MAX_POINTS; i++) {
        me->points[i] = state->points[i];
    }
    me->num_points = state->num_points;

    /* Restaurer tous les paneles */
    for (i = 0; i < MAX_PANELS; i++) {
        me->panels[i] = state->panels[i];
    }
    me->num_panels = state->num_panels;

    /* Restaurer tous les cables */
    for (i = 0; i < MAX_CABLES; i++) {
        me->cables[i] = state->cables[i];
    }
    me->num_cables = state->num_cables;

    /* Restaurer tous les liens */
    for (i = 0; i < MAX_LINKS; i++) {
        me->links[i] = state->links[i];
    }
    me->num_links = state->num_links;

    printf("Action undone (Ctrl+Z)\n");

    /* Redessiner */
        /* Redraw handled by gtk_widget_queue_draw in gtk3_main.c */
}

void key_pressed(Widget w, char *input, int up_or_down, void *data)
{
    MyProgram *me = (MyProgram *)data;

    /* up_or_down: 0 = key down, 1 = key up */
    if (up_or_down != 0) return;  /* Ne traiter que les appuis */

    /* Détecter Ctrl+Z */
    if (input && (input[0] == 26 || input[0] == 'z'-'a'+1)) {  /* ASCII 26 = Ctrl+Z */
        undo_action(me);
    }
}
