CLASS FILE *fic_ps; 		/* handle du fichier Postscript */
CLASS int hauteur_police_ps; 
CLASS int largeur_police_ps; 
CLASS float epaisseur_trait_ps;
CLASS char mode_portrait;	/* PostScript : sortie paysage ou portrait */
CLASS char flag_ps; 		/* Sortie Postscript ? */
CLASS char flag_plain_color; 	/* couleur unie */
CLASS char flag_ortho_norm; 	/* flag : tracer dans un repere orthonorme */
CLASS int taille_police_x; 	/* sur l'ecran */
CLASS int taille_police_y; 	/* sur l'ecran */
CLASS int delta_caract_x;	/* offset graphique : nb de demi caractere horizontal */
CLASS int delta_caract_y;	/* offset graphique : nb de demi caractere vertical */
CLASS char flag_delta_carac;	/* flag : utilise dans les routines graphiques pour effectuer un decalage de delta_carac sur les 
				   coordonnees */
CLASS char ligne_motif[10][5]; /* definition des styles (motif) des traces de ligne */
CLASS float RESOLUTION_X_FEN; /* Largeur de la fenetre sur l'ecran */
CLASS float RESOLUTION_Y_FEN; /* Hauteur de la fenetre sur l'ecran */

CLASS float axe_x1; /* cadre de la position des axes dans le dessin */
CLASS float axe_x2;
CLASS float axe_y1;
CLASS float axe_y2;

CLASS FILE *f1;

CLASS struct Clip {float bas,haut,droite,gauche;}clip;
CLASS char flag_clip;
