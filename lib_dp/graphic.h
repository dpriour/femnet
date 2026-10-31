#include <gtk/gtk.h> // <-- AJOUTEZ CETTE LIGNE ICI

typedef struct MyProgram
	{
	int   win_width, win_height;
	//Widget my_label;             // <-- Ajoutez cette ligne
	GtkWidget *my_label;  // <-- Remplacez 'Widget' par 'GtkWidget *'
	}MyProgram;


CLASS struct Plan
	{
	int 	do_it;			//if 1 do the plan, if 0 dont//
	int 	direction;		//if 1 (2,3) along x (y,z)//
	int	nb_line;		//nb of lines for the plan//
	int	*panel;			//numero of the panel from which the line is drawn//
	int	*corner;		//numero of the panel from which the line is drawn//
	float	*limit;			//numero of the panel from which the line is drawn//
	int	nb_height;		//nb of heights for the plan//
	int	*panelh;		//numero of the panel from which the height is drawn//
	int	*corner1;		//numero of the panel from which the height is drawn//
	int	*corner2;		//numero of the panel from which the height is drawn//
	int	*directionh;		//numero of the panel from which the height is drawn//
	float	*position;		//numero of the panel from which the height is drawn//
	float	minx,maxx,miny,maxy;	//min max for the plan//
	int	nb_width;		//nb of heights for the plan//
	int	*panelw;		//numero of the panel from which the width is drawn//
	int	*corner3;		//numero of the panel from which the width is drawn//
	int	*corner4;		//numero of the panel from which the width is drawn//
	int	*directionw;		//numero of the panel from which the width is drawn//
	int	nb_widths;		//nb of heights for the plan//
	float	*positionw;		//numero of the panel from which the width is drawn//
	int	*panelws;		//numero of the panel from which the width symmetric is drawn//
	int	*corner3s;		//numero of the panel from which the width symmetric is drawn//
	int	*corner4s;		//numero of the panel from which the width symmetric is drawn//
	int	*directionws;		//numero of the panel from which the width symmetric is drawn//
	float	*positionws;		//numero of the panel from which the width symmetric is drawn//
	int	nb_cut;			//nb of panel cutting for the plan//
	int	*panelc;		//numero of the panel on which the cutting is drawn//
	int	*corner5;		//numero of the panel on which the cutting is drawn//
	int	nb_cable;		//nb of cables indicated on the plan//
	int	*cable;			//numero of the cable drawn//
	int	nb_trait_UV;		//nb of trait UV in panel//
	int	*panelt;		//numero of the panel on which the trait is drawn//
	float	*U1,*V1,*U2,*V2;	//coordinates in nb of meshes of the traits//
	int	nb_trait_UV_symmetry;	//nb of trait UV in panel//
	int	*panels;		//numero of the panel on which the trait is drawn//
	float	*R1,*S1,*R2,*S2;	//coordinates in nb of meshes of the traits//
	float	*symmetryt;		//coordinates in nb of meshes of the traits//
	int	nb_cable_diameter;	//nb of cables indicated on the plan with indication of diameter//
	int	*cabled;		//numero of the cable drawn//
	float	*cable_diameter;	//numero of the cable drawn//
	int	nb_cable_length;	//nb of cables indicated on the plan with indication of diameter//
	int	*cablel;		//numero of the cable drawn//
	float	*cable_length;		//numero of the cable drawn//
	int	nb_indication;		//nb of indications indicated on the plan//
	float	*X1,*Y1;		//position of the indication//
	float 	*indication; 		//indication//
	} plan;


typedef struct {
	int  tag;
	char *label;
	void *data;
	int  init;
	} TagList;

int GetValues_2(TagList *tags);

//marge sur le graphique//
#define marge 0.05


CLASS FILE *fic_ps; 		// handle du fichier Postscript //
CLASS int hauteur_police_ps; 
CLASS int largeur_police_ps; 
CLASS float epaisseur_trait_ps;
CLASS char mode_portrait;	// PostScript : sortie paysage ou portrait //
CLASS char flag_ps; 		// Sortie Postscript ? //
CLASS char flag_ortho_norm; 	// flag : tracer dans un repere orthonorme //
CLASS int taille_police_x; 	// sur l'ecran //
CLASS int taille_police_y; 	// sur l'ecran //
CLASS int delta_caract_x;	// offset graphique : nb de demi caractere horizontal //
CLASS int delta_caract_y;	// offset graphique : nb de demi caractere vertical //
CLASS char flag_delta_carac;	// flag : utilise dans les routines graphiques pour effectuer un decalage de delta_carac sur les coordonnees //
CLASS char ligne_motif[10][5]; 	// definition des styles (motif) des traces de ligne //
CLASS float RESOLUTION_X_FEN; 	// Largeur de la fenetre sur l'ecran //
CLASS float RESOLUTION_Y_FEN; 	// Hauteur de la fenetre sur l'ecran //



