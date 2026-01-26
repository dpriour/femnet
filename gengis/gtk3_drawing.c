/* GTK 3 Drawing Layer - Implementation
 * Wrappers Cairo pour remplacer les fonctions de dessin libsx
 */

#include "gtk3_drawing.h"
#include <string.h>

/* Variables globales pour le contexte Cairo */
static cairo_t *current_cairo_ctx = NULL;
static GdkRGBA current_color = {0.0, 0.0, 0.0, 1.0};  /* Noir par défaut */

/* Palette de couleurs standard */
static GdkRGBA color_palette[] = {
    {0.0, 0.0, 0.0, 1.0},  /* BLACK */
    {1.0, 0.0, 0.0, 1.0},  /* RED */
    {0.0, 1.0, 0.0, 1.0},  /* GREEN */
    {0.0, 0.0, 1.0, 1.0},  /* BLUE */
    {1.0, 1.0, 0.0, 1.0},  /* YELLOW */
    {1.0, 1.0, 1.0, 1.0}   /* WHITE */
};

/* Initialiser le contexte Cairo pour le dessin */
void set_cairo_context(cairo_t *cr)
{
    current_cairo_ctx = cr;

    if (cr != NULL) {
        /* Configurer le contexte Cairo */
        cairo_set_line_width(cr, 1.0);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);

        /* Appliquer la couleur courante */
        gdk_cairo_set_source_rgba(cr, &current_color);
    }
}

/* Obtenir le contexte Cairo courant */
cairo_t* get_cairo_context(void)
{
    return current_cairo_ctx;
}

/* Définir la couleur de dessin */
void SetColor(int color)
{
    if (color >= 0 && color <= WHITE) {
        current_color = color_palette[color];

        if (current_cairo_ctx) {
            gdk_cairo_set_source_rgba(current_cairo_ctx, &current_color);
        }
    }
}

/* SetDrawMode - ignoré avec Cairo (gardé pour compatibilité) */
void SetDrawMode(int mode)
{
    /* Cairo gère automatiquement les modes de dessin */
    /* Cette fonction ne fait rien mais existe pour compatibilité avec libsx */
}

/* Effacer la zone de dessin (fond blanc) */
void ClearDrawArea(void)
{
    if (!current_cairo_ctx) return;

    /* Sauvegarder la couleur courante */
    GdkRGBA saved_color = current_color;

    /* Remplir avec du blanc */
    cairo_set_source_rgb(current_cairo_ctx, 1.0, 1.0, 1.0);
    cairo_paint(current_cairo_ctx);

    /* Restaurer la couleur courante */
    current_color = saved_color;
    gdk_cairo_set_source_rgba(current_cairo_ctx, &current_color);
}

/* Dessiner une ligne */
void DrawLine(int x1, int y1, int x2, int y2)
{
    if (!current_cairo_ctx) return;

    cairo_move_to(current_cairo_ctx, x1 + 0.5, y1 + 0.5);
    cairo_line_to(current_cairo_ctx, x2 + 0.5, y2 + 0.5);
    cairo_stroke(current_cairo_ctx);
}

/* Dessiner un pixel */
void DrawPixel(int x, int y)
{
    if (!current_cairo_ctx) return;

    cairo_rectangle(current_cairo_ctx, x, y, 1.0, 1.0);
    cairo_fill(current_cairo_ctx);
}

/* Dessiner du texte */
void DrawText(char *text, int x, int y)
{
    if (!current_cairo_ctx || !text) return;

    /* Configurer la police */
    cairo_select_font_face(current_cairo_ctx, "Sans",
                          CAIRO_FONT_SLANT_NORMAL,
                          CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(current_cairo_ctx, 12.0);

    /* Dessiner le texte */
    cairo_move_to(current_cairo_ctx, x, y);
    cairo_show_text(current_cairo_ctx, text);
}

/* Dessiner un rectangle rempli */
void DrawFilledBox(int x, int y, int width, int height)
{
    if (!current_cairo_ctx) return;

    cairo_rectangle(current_cairo_ctx, x, y, width, height);
    cairo_fill(current_cairo_ctx);
}

/* Dessiner un rectangle (contour uniquement) */
void DrawBox(int x, int y, int width, int height)
{
    if (!current_cairo_ctx) return;

    cairo_rectangle(current_cairo_ctx, x + 0.5, y + 0.5, width, height);
    cairo_stroke(current_cairo_ctx);
}

/* GetStandardColors - compatibilité libsx (ne fait rien avec GTK) */
void GetStandardColors(void)
{
    /* Les couleurs sont déjà définies dans color_palette */
    /* Cette fonction existe uniquement pour compatibilité avec libsx */
}
