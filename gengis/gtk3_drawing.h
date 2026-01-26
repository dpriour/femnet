/* GTK 3 Drawing Layer - Header
 * Couche de compatibilité Cairo pour remplacer libsx
 */

#ifndef GTK3_DRAWING_H
#define GTK3_DRAWING_H

#include <gtk/gtk.h>

/* Définitions des couleurs (compatibles avec libsx) */
#define BLACK   0
#define RED     1
#define GREEN   2
#define BLUE    3
#define YELLOW  4
#define WHITE   5

/* Initialisation du contexte Cairo */
void set_cairo_context(cairo_t *cr);
cairo_t* get_cairo_context(void);

/* Fonctions de dessin (API compatible libsx) */
void SetColor(int color);
void SetDrawMode(int mode);  /* Ignoré avec Cairo, gardé pour compatibilité */
void ClearDrawArea(void);
void DrawLine(int x1, int y1, int x2, int y2);
void DrawPixel(int x, int y);
void DrawText(char *text, int x, int y);
void DrawFilledBox(int x, int y, int width, int height);
void DrawBox(int x, int y, int width, int height);

/* Fonctions pour GetStandardColors - compatibilité libsx */
void GetStandardColors(void);

/* Fonction de dialog pour GetString (définie dans gtk3_main.c) */
char* GetString(char *prompt, char *default_value);

#endif
