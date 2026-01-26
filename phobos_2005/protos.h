/*prototypes de alloc.c*/
double *Malloc_double(int nb);
float *Malloc_float(int nb);
int *Malloc_int(int nb);
struct commentaire *Malloc_commentaire(int nb);
double *Realloc_double(double *ff,int nb);
float *Realloc_float(float *ff,int nb);
int *Realloc_int(int *ff,int nb);
struct commentaire *Realloc_commentaire(struct commentaire *ff,int nb);
	

/*prototypes de fct_sx.c*/
char *GetFile(char *_path);				



/*prototypes de chargement_don.c*/
void modif_materiau_elem(int num_elem_choisi, double raideur_traction_choisie, double raideur_compression_choisie, double masse_volumique_choisie, double diam_hydro_choisi, double coeff_trainee_normal_choisi, double coeff_trainee_tangent_choisi);
void charger_phobos();
void charger(char *nomfichier);
void initialisation_nb();
void initialisation_seam();
void automatic_linking();
void initialisation_nb_fils();
void initialisation_lien();
void initialisation_min_max();
void creer_fichier_phobos();
void creer_fichier_speed_file();
void creer_fichier();
void Genere_ps();
void initialisation_ps();
void lire_fichier_sta();
int lecture_chaine(FILE *fic, char *chain);
int lecture_commentaire(FILE *fic, char *chain);
void lecture_des();
int seam_coordinates(int pa, int no, double U1, double U2, double U3, double U4, double V1, double V2, double V3, double V4);
void homot_file(char *source_file, char *target_file, double homot_ratio);
void produit_vect(double xx1, double yy1, double zz1, double xx2, double yy2, double zz2, double *xx3, double *yy3, double *zz3);
void produit_vect2(double vect_1[4], double vect_2[4], double *xx3, double *yy3, double *zz3);
void produit_vect3(double vect_1[4], double vect_2[4], double *vect_3);
void add_vect(double vect_1[4], double vect_2[4], double *vect_3);
void add_vect_6(double vect_1[4], double vect_2[4], double *vect_3);
void add_vect_12(double vect_1[4], double vect_2[4], double *vect_3);
void produit_scal_vect(double scal, double vect_1[4], double *vect_2);
void produit_scal_vect_12(double scal, double vect_1[13], double *vect_2);
void produit_scal_vect_6(double scal, double vect_1[13], double *vect_2);
double produit_scal(double vect_1[4], double vect_2[4]);
void base1(double angl1,int axeangl1,double angl2,int  axeangl2,int  nbcol,double *vect);
	
			
	



/*prototypes de chargement_mdgsta.c*/
void charger_mdgsta();
void creer_fichier_sta();
void noeud_element();
void noeud_panneau();
int appartient_triangle(int noe,int typ,int notri);
void position_interieur_triangle(double um,double vm,double u1,double v1,double u2,double v2,double u3,double v3, double *alpha,double *beta);
int position_interieur_triangle2(double um,double vm,double u1,double v1,double u2,double v2,double u3,double v3, double *alpha,double *beta);
int appartient_triangle_contour(double um,double vm,int typ);
int appartient_triangle2(int noe,int typ);
int appartient_triangle3(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
int segment_secant(double a1, double b1, double a2, double b2, double x1, double y1, double x2, double y2);
void intersection_segment(double a1, double b1, double a2, double b2, double x1, double y1, double x2, double y2, double *x,double *y);
int intersection_segment2(double a1, double b1, double a2, double b2, double x1, double y1, double x2, double y2, double *alpha,double *beta);
void distance_segment_point(double a1, double b1, double a2, double b2, double x1, double y1, double *alpha,double *beta);
int appartient_tri_hexa2(int noe,int typ);
void ecriture_sta(FILE *f3);
void nothing();

/*prototypes de lire_fichier_mdhsta.c*/
void lire_fichier_mdgsta();
void mesure_defaut_discretisation();


/*prototypes de chargement_sta.c*/
void charger_sta();


/*prototypes de dessiner_axes.c*/
void dessiner_axes();
int Clip3(float *xx1,float *yy1,float *xx2,float *yy2);



/*prototypes de gfx_base.c*/
void Move_to(float x,float y);
void Line_to(float x,float y);
void Surface_end();
void Color(int c);
void Text(float,float,char *);
void Line(float,float,float,float);




/*prototypes de dessiner_ps.c*/
void dessiner();
void dessiner_contour_hexa();
void dessiner_contour_panneau();
void dessiner_contour_panel_cutting();
void dessiner_contour_element();
void dessiner_contour_winch();
void dessiner_contour_coulisse();
void dessiner_contour_balls();
void dessiner_liaison();
void dessiner_angle_flexion_cable();
void dessiner_lie();
void dessiner_numero_hexa();
void dessiner_numero_panneau();
void dessiner_numero_element();
void dessiner_numero_coulisse();
void dessiner_numero_barre();
void dessiner_order_liaison();
void dessiner_numero_liaison();
void dessiner_ordre_maillage();
void dessiner_numero_total();
void dessiner_numerotation_type();
void dessiner_valeur_masse();
void dessiner_valeur_longueur();
void dessiner_valeur_cd();
void dessiner_valeur_effort_exterieur();
void dessiner_valeur_fixation();
void dessiner_valeur_limite();
void dessiner_valeur_sens_limite();
void dessiner_valeur_symetrie();
void dessiner_nb_mailles();
void dessiner_nb_cotes_mailles();
void dessiner_longueur_cotes();
void dessiner_panel_cutting();
void dessiner_numero_global();
void dessiner_numero_local();
void dessiner_numero_interieur();
void dessiner_numero_coin();
void dessiner_raideur_traction();
void dessiner_raideur_compression();
void dessiner_raideur_ouverture();
void dessiner_longueur_repos();
void dessiner_bar_length();
void dessiner_masse_volumique();
void dessiner_diametre();
void dessiner_largeur_noeud();
void dessiner_coefficient_cd();
void dessiner_coefficient_f();
void dessiner_panel_drag();
void dessiner_longueur_maillage();
void dessiner_type_maillage();
void dessiner_section_element();
void dessiner_volume_element();
void dessiner_masse_element();
void dessiner_masse_lineique();
void dessiner_flottabilite();
void dessiner_EI_flexion_cable();
void dessiner_courant();
void dessiner_Prise_volume();
void dessiner_frottement_fond();
void dessiner_surface_fils();
void filet_interne_dessiner();
void internal_bar_dessiner();
void orientation_uv_dessiner();
void orientation_UV_dessiner();
void orientation_xy_dessiner();
void dessiner_filet_interne(int no_pa);
void dessiner_orientation_uv(int no_pa);
void dessiner_orientation_UV(int no_pa);
void dessiner_orientation_xy(int no_pa);
void filet_contour_dessiner();
void fils_contour_dessiner();
void UV_Vectors_dessiner();
void dessiner_filet_contour_hexa(int no_pa);
void dessiner_filet_contour(int no_pa);
void dessiner_fils_contour();
void dessiner_UV_Vectors();
void dessiner_axe_T90();
void axe_T90_dessiner();
void trace_fil_hexa(float a1, float b1, float a2, float b2, float x1, float y1, float x2, float y2, float x3, float y3);
void dessiner_numerotation_triangle_contour();
void dessiner_numerotation_triangle_interieur();
void dessiner_longueur_tendue();
void dessiner_tension();
void dessiner_nrj();
void dessiner_defaut_discretisation();
void dessiner_numerotation_globale();
void draw_segment_color(int color, double x1m, double y1m, double x2m, double y2m);
void TraceSegment(int icolor, double dx1, double dy1, double dx2, double dy2);

/*prototypes de Checked_menu.c*/
void Checked_dessiner_contour_hexa();
void Checked_dessiner_contour_panneau();
void Checked_dessiner_contour_panel_cutting();
void Checked_dessiner_contour_element();
void Checked_dessiner_contour_winch();
void Checked_dessiner_contour_coulisse();
void Checked_dessiner_contour_balls();
void Checked_dessiner_liaison();
void Checked_angle_flexion_cable();
void Checked_dessiner_lie();
void Checked_numerotation_hexa();
void Checked_numerotation_panneau();
void Checked_numerotation_element();
void Checked_numerotation_coulisse();
void Checked_numerotation_barre();
void Checked_numerotation_liaison();
void Checked_order_liaison();
void Checked_ordre_maillage();
void Checked_numerotation_total();
void Checked_numerotation_global();
void Checked_numerotation_local();
void Checked_numerotation_interieur();
void Checked_numerotation_coin();
void Checked_valeur_masse();
void Checked_valeur_longueur();
void Checked_valeur_cd();
void Checked_valeur_effort_exterieur();
void Checked_valeur_fixation();
void Checked_valeur_limite();
void Checked_valeur_sens_limite();
void Checked_valeur_symetrie();
void Checked_nb_mailles();
void Checked_nb_cotes_mailles();
void Checked_longueur_cotes();
void Checked_panel_cutting();
void Checked_courant();
void Checked_prise();
void Checked_frottement_fond();
void Checked_surface_fils();
void Checked_numerotation_type();
void Checked_numerotation_triangle_contour();
void Checked_numerotation_triangle_interieur();
void Checked_raideur_traction();
void Checked_raideur_compression();
void Checked_raideur_ouverture();
void Checked_twines_nb();
void Checked_longueur_repos();
void Checked_bar_length();
void Checked_masse_volumique();
void Checked_diametre();
void Checked_largeur_noeud();
void Checked_coefficient_cd();
void Checked_coefficient_f();
void Checked_panel_drag();
void Checked_longueur_maillage();
void Checked_type_maillage();
void Checked_section_element();
void Checked_volume_element();
void Checked_masse_element();
void Checked_masse_lineique();
void Checked_flottabilite();
void Checked_filet_interne();
void Checked_internal_bar();
void Checked_orientation_uv();
void Checked_orientation_UV();
void Checked_orientation_xy();
void Checked_filet_contour();
void Checked_fils_contour();
void Checked_UV_Vectors();
void Checked_axe_T90();
void Checked_dessiner_axes();
void Checked_longueur_tendue();
void Checked_tension();
void Checked_numerotation_globale();
void Checked_nrj();
void Checked_defaut_discretisation();
void Checked_EI_flexion_cable();

/*prototypes de elongation.c*/
void elongation();



/*prototypes de filet.c*/
void filet_contour();
void triangulation_contour(int pa);
void triangul_hexa_contour(int pa);
void fils_contour_calculer();
void axe_T90_calculer();
void  hachu3(float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui);
void  hachu4(float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui);


/*prototypes de filet_interne.c*/
void filet_interne();
void initialisation_par_default();
void initialisation_triangulation_interne(int pa);
void initialisation_triangulation_interne_hexa(int pa);
void initialisation_segment_interne(int pa);
void initialisation_segment_interne_hexa(int pa);
void mise_a_jour_triangulation_interne(int pa);
void mise_a_jour_triangulation_interne_hexa(int pa);
void liberer();
void inversions_des_triangles();


/*prototypes de init_display.c*/
void init_display(int argc, char **argv, MyProgram *me);



/*prototypes de maillage.c*/
void maillage();
void maillage_winch1(int el);
void maillage_panneau();
void maillage_element2(int el);
void maillage_pan_hexa2();
void maillage_coulisse2();
void changement_de_type_noeud();

/*prototypes de maillage_coulisse.c*/
void maillage_coulisse();
int liaison_maille_co(int neud,int couliss,char *structur,int *nostructur,int *debutsegm,int *finsegm);
void maillage_coulisse_libre(int co);
void maillage_coulisse_coulisse(int co,int co2,int nlo1);
void maillage_coulisse_element(int co,int el2,int nlo1);
void maillage_coulisse_element_old(int co,int el2,int nlo1);
void maillage_coulisse_panneau(int co,int nopan,int nlo1,int nlo2);
void maillage_coulisse_pan_hexa(int co,int nopan,int nlo1,int nlo2);



/*prototypes de maillage_element.c*/
void maillage_element();
int liaison_maille_el(int neud,int elemen,char *structur,int *nostructur,int *debutsegm,int *finsegm);
void maillage_element_libre(int el);
void maillage_element_element(int el,int el2,int nlo1);
void maillage_element_panneau(int el,int nopan,int nlo1,int nlo2);
void maillage_element_pan_hexa(int el,int nopan,int nlo1,int nlo2);
void mise_a_jour_type_noeud(int cible, int source);


/*prototypes de maillage_winch.c*/
void maillage_winch_libre(int el);



/*prototypes de maillage_pan_hexa.c*/
void maillage_pan_hexa();
void mail_hexa_contour1(int pa,double longueur_repos);
void mail_hexa_interne2(int pa,double longueur_repos);
void mail_hexa_contour2(int pa,double longueur_repos);
void mail_hexa_interne3(int pa,double longueur_repos);
int liaison_maille_hexa(int neud,int pannea,char *structur,int *nostructur,int *debutsegm,int *finsegm);
void mail_hexa_contour_libre_filaire(int pa, int co, int cp,double longueur_repos);
void mail_hexa_contour_pan_hexa(int pa, int co, int cp,int pa2,int nlo1,int nlo2);
void mail_hexa_contour_element(int pa,int co,int cp,int noele,int nloc);
void mail_hexa_contour_libre_filaire2(int pa, int co, int cp,double longueur_repos);
void mail_hexa_contour_pan_hexa2(int pa, int co, int cp,int pa2,int nlo1,int nlo2);
int interieur_pan_hexa_filaire(float UU, float VV, int no_pa);
int proche_contour_filaire_hexa(float UU, float VV, int no_pa, float fact,double longueur_repos);
int proche_pan_hexa_filaire(float UU, float VV, int no_pa, float fact,double longueur_repos);
void maillage_pan_hexa_en_element(int el);





/*prototypes de maillage_panneau1.c*/	
void maillage_panneau1();
int appartient_liaison(int no_noeud);
int appartient_barre(int no_noeud);
int appartient_numero_element(int no_noeud);
int appartient_type_element(int no_noeud);
int liaison_maille(int neud,int pannea,char *structur,int *nostructur,int *debutsegm,int *finsegm);
void maillage_contour_libre_filaire(int pa, int co, int cp);
void maillage_contour_panneau(int pa, int co, int cp,int pa2,int nlo1,int nlo2);
void maillage_contour_element(int pa,int co,int cp,int noele,int nloc);
void maillage_contour_element2(int pa,int co,int cp,int noele,int nloc);
void maillage_contour1(int pa);
float surface_triangle(float X1, float Y1, float X2, float Y2, float X3, float Y3 );
void maillage_interne2(int pa);
void maillage_interne5(int pa);
int interieur_panneau_filaire(float UU, float VV, int no_pa);
int interieur_panneau_filaire2(float UU, float VV, int no_pa);
int interieur_panneau_filaire3(double UU, double VV, int no_pa, double *alpha, double *beta);
int proche_contour_filaire(float UU, float VV, int no_pa, float fact);
int proche_panneau_filaire(float UU, float VV, int no_pa, float fact);
int sewn_diamond_panel2cable(int cable, int panel);
int sewn_diamond_panel2cable2(int cable, int panel, int *corner1, int *corner2);






/*prototypes de maillage_panneau2.c*/	
void maillage_panneau2();
void maillage_contour_libre_filaire2(int pa, int co, int cp);
void maillage_contour_panneau2(int pa, int co, int cp,int pa2,int nlo1,int nlo2);
void maillage_contour2(int pa);
void maillage_interne3(int pa);
void maillage_interne4(int pa);
void maillage_interne6(int pa);
float equation_cote(int inc, float val, float u1, float u2, float v1, float v2);

/*prototypes de maillage_seam.c*/	
void maillage_seam();


/*prototypes de meshing_netting_2_ropes2.c*/
int verification_ropes_around_panel2(int pa);
void create_side2cable(int pa);
void first_node_created(int pa);
int number_of_cuts(int pan, double extrem1_u, double extrem1_v, double extrem2_u, double extrem2_v, int *cut_t, int *cut_s, double *cut_a, double *cut_b, int *cut_c);
int side_neighbor(int pan, double pt1x, double pt1y, double pt2x, double pt2y);
int is_node_close_side(int pan, double *extrem_u, double *extrem_v);
int is_node_close_side2(int pan, int side, double ptu, double ptv);
int is_node_close_another_one2(int pan, double ptu, double ptv);
int bar_creation2(int pan, int pt1, int pt2, double cut_a);
int case1(int pan, int tri, double ptu, double ptv);
int case2(int pan, int cut_s , double cut_b , double *extrem_u, double *extrem_v);
void sorting_node_per_element_around_panel(int pan);
void bar_creation_per_element_around_panel(int pan);


/*prototypes de meshing_netting_2_ropes3.c*/
void meshing_netting_2_ropes3(int pa);

/*prototypes de multireq.c*/	
void edit(Widget w, void *data);



/*prototypes de nbmaille_triangle3.c*/	
void nb_maille_total();
void nbmaille_triangle(int pa);
void nbmaille_tri_hexa(int pa);



/*prototypes de numerotation.c*/	
void numerotation_globale();
int noeud_reference_liaison(int no_liaison);


/*prototypes de numerotation_balls.c*/	
void numerotation_balls();



/*prototypes de postscript.c*/	
void Chk_ps_open();
void Chk_ps_close();
void Text_ps(float x,float y, char *s);
void Line_ps(float x1,float y1,float x2,float y2);
void Move_to_ps (float x1,float y1);
void Line_to_ps (float x1,float y1);
void Line_end_ps ();
void Surface_end_ps ();
void Circle_ps (float x1,float y1,float r);
void Color_ps(int c);
void ColorRGB_ps(int r, int v, int b);
void Motif_ps(char d[],int n);
void Size_font_ps(int coef);
void Line_larg_ps(int n);
void Rectangle_plein_ps(float x1,float y1, float x2,float y2);
char *Date();


/*prototypes de qsort.c*/	
void tri();

/*prototypes de quitter.c*/	
void quitter(Widget w, void *data);



/*prototypes de redisplay.c*/	
void redisplay(Widget w, int new_width, int new_height, void *data);



/*prototypes de zoom.c*/
void add_link();	
void button_down(Widget w, int which_button, int x, int y, void *data);
void button_up(Widget w, int which_button, int x, int y, void *data);
void motion(Widget w, int x, int y, void *data);
