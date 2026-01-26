/* Geometry Editor - Programme de création de paneles et cables
 * main.h - Définitions et structures de données
 */

#ifndef MAIN_H
#define MAIN_H

#define MAX_POINTS 1000
#define MAX_PANELS 100
#define MAX_CABLES 100
#define MAX_LINKS 200

#define MODE_PANEL   1
#define MODE_CABLE   2
#define MODE_LINK      3
#define MODE_ALIGN     4
#define MODE_MODIFY_UV 5
#define MODE_MODIFY_Z  6
#define MODE_MODIFY_PANEL  7

#define MAX_UNDO 10  /* Nombre maximum d'actions annulables */

#ifndef TRUE
#define TRUE  1
#define FALSE 0
#endif

/* Structure pour un point */
typedef struct {
    int x, y, z;
    int type;         /* type du point (par défaut 1) */
    int used;
    int selected;     /* 1 si sélectionné */
    double u, v;      /* coordonnées en mailles (par défaut = x, y) */
} Point;

/* Structure pour un panele */
typedef struct {
    int points[50];      /* indices des points */
    int num_points;
    int closed;
    int type;            /* type du panele (par défaut 1) */
    int edge_types[50];  /* type de chaque côté du panele (par défaut 1) */
    double T_stiffness;
    double C_stiffness;
    double MOS;
    double length;
    double vol_mass;
    double diameter;
    double knot_size;
    double cd;
    double f;
    double meshing_step;
    int meshing_type;
} Panel;

/* Structure pour un cable */
typedef struct {
    int p1, p2;          /* indices des deux points */
    int type;            /* type du cable (par défaut 1) */
} Cable;

/* Structure pour un lien */
typedef struct {
    int p1, p2;          /* indices des deux points liés */
} Link;

/* Structure pour sauvegarder un état (undo) */
typedef struct {
    Point points[MAX_POINTS];
    int num_points;
    Panel panels[MAX_PANELS];
    int num_panels;
    Cable cables[MAX_CABLES];
    int num_cables;
    Link links[MAX_LINKS];
    int num_links;
} UndoState;

/* Structure principale du programme */
typedef struct {
    Point points[MAX_POINTS];
    int num_points;

    Panel panels[MAX_PANELS];
    int num_panels;

    Cable cables[MAX_CABLES];
    int num_cables;

    Link links[MAX_LINKS];
    int num_links;

    int current_mode;     /* MODE_PANEL, MODE_CABLE, MODE_LINK */
    int current_poly;     /* panele en cours de création */
    int temp_point;       /* point temporaire pour cable/lien */

    /* Pour le mode modification UV */
    int selected_poly;    /* panele dont un côté est sélectionné (-1 si aucun) */
    int selected_edge;    /* index du côté sélectionné (-1 si aucun) */

    int draw_area_width;
    int draw_area_height;

    /* Zoom et pan */
    float zoom_factor;    /* facteur de zoom (1.0 = normal) */
    int pan_x, pan_y;     /* décalage pour le pan */
    float zoom_pixel_m;    /* ratio pixel per m */

    /* État du panning */
    int is_panning;       /* 1 si en train de panner */
    int last_mouse_x;     /* dernière position x de la souris */
    int last_mouse_y;     /* dernière position y de la souris */

    /* Sélection rectangulaire pour alignement */
    int selecting;        /* 1 si en train de sélectionner */
    int select_x1, select_y1, select_z1;  /* coin de départ */
    int select_x2, select_y2, select_z2;  /* coin actuel */
    int num_selected;     /* nombre de points sélectionnés */

    /* Historique pour undo (Ctrl+Z) */
    UndoState undo_stack[MAX_UNDO];
    int undo_count;       /* nombre d'états sauvegardés */

    /* Fichier en cours */
    char current_filename[256];  /* nom du fichier chargé/sauvegardé */

    /* Contrôle de l'affichage */
    int show_points;          /* 1 pour afficher les points */
    int show_panels;        /* 1 pour afficher les paneles */
    int show_cables;        /* 1 pour afficher les cables */
    int show_links;           /* 1 pour afficher les interconnections */
    int show_axes;            /* 1 pour afficher les axes */

    /* Contrôle de l'affichage des numéros */
    int show_point_numbers;   /* 1 pour afficher les numéros des points */
    int show_panel_numbers; /* 1 pour afficher les numéros des paneles */
    int show_cable_numbers; /* 1 pour afficher les numéros des cables */
    int show_link_numbers;    /* 1 pour afficher les numéros des interconnections */

    /* Contrôle de l'affichage des types */
    int show_point_types;     /* 1 pour afficher les types des points */
    int show_panel_types;   /* 1 pour afficher les types des paneles */
    int show_edge_types;      /* 1 pour afficher les types des côtés des paneles */
    int show_cable_types;   /* 1 pour afficher les types des cables */

    /* Plan de vue (projection) */
    int view_plane;           /* 1: normal=X (YZ), 2: normal=Y (ZX), 3: normal=Z (XY) */
} MyProgram;

/* Prototypes - init_display n'est plus nécessaire avec GTK 3 */
/* La fonction main() est maintenant dans gtk3_main.c */

#endif
