/*prototypes de nrutil.c*/
float *vector(long nl, long nh);
float **matrix(long nrl, long nrh, long ncl, long nch);

/*prototypes de alloc.c*/
double **Malloc_double_tab(int nb_li, int nb_co);
double *Malloc_double(int nb);
float *Malloc_float(int nb);
int *Malloc_int(int nb);
struct commentaire *Malloc_commentaire(int nb);
double *Realloc_double(double *ff,int nb);
float *Realloc_float(float *ff,int nb);
int *Realloc_int(int *ff,int nb);
struct commentaire *Realloc_commentaire(struct commentaire *ff,int nb);

/*prototypes de animation2.c*/
void anim_rotation2(int code_video);
void animation_eigenvalue(int code_video);

/*prototypes deanimation.c*/
void animation();
void animation_video();

/*prototypes deanim_rotation2.c*/
void anim_rotation2(int code_video);

/*prototypes debase1.c*/
void base1(double angl1,int axeangl1,double angl2,int  axeangl2,int  nbcol,double *vect);

/*prototypes utilises par charger.c*/
int  ColorRGB(int r, int v, int b);
char *GetFile(char *_path);				/* pas de changement */


/*prototypes de charger.c*/
void charger_initial();
void charger_final();
void calcul_houle2();
void initialisation_min_max();
void initialisation_surface_front();
void changement_variable_catch();
void initialisation_color_side();
void initialisation_nb_color();
void initialisation_nb_ufils();
void initialisation_nb_vfils();
void initialisation_nb_Ufils_hexa();
void initialisation_nb_Vfils_hexa();
void ajout_symetrique(double decalx, double decaly, double decalz, int signx, int signy, int signz );
void recherche_symetrie();
void portrait();
void Genere_ps();
void initialisation_ps();
void initialisation_elongation();
void initialisation_couleur_tension_final();
void initialisation_couleur_tension_initial();
void initialisation_couleur_triangle();
void initialisation_orientation_triangle();
int appartient_triangle4(double um, double vm, double u1, double v1, double u2, double v2, double u3, double v3);
int segment_secant2(double a1, double b1, double a2, double b2, double x1, double yy1, double x2, double y2);
int segment_secant(double a1, double b1, double a2, double b2, double x1, double yy1, double x2, double y2);
void intersection_segment(double a1, double b1, double a2, double b2, double x1, double yy1, double x2, double y2, double *x,double *y);
void mesure_defaut_discretisation();
void produit_vect(float xx1, float yy1, float zz1, float xx2, float yy2, float zz2, float *xx3, float *yy3, float *zz3);
void produit_vect2(float vect_1[4], float vect_2[4], float *xx3, float *yy3, float *zz3);
void produit_vect3(float vect_1[4], float vect_2[4], float *vect_3);
void produit_vect3_double(double vect_1[4], double vect_2[4], double *vect_3);
void add_vect(float vect_1[4], float vect_2[4], float *vect_3);
void sou_vect(float vect_1[4], float vect_2[4], float *vect_3);
void add_vect_6(float vect_1[4], float vect_2[4], float *vect_3);
void add_vect_12(float vect_1[4], float vect_2[4], float *vect_3);
void produit_scal_vect(float scal, float vect_1[4], float *vect_2);
void produit_scal_vect_double(double scal, double vect_1[4], double *vect_2);
void produit_scal_vect_2(float scal1, float vect_1[4], float scal2, float vect_2[4], float *vect_3);
void produit_scal_vect_2_double(double scal1, double vect_1[4], double scal2, double vect_2[4], double *vect_3);
void produit_scal_vect_12(float scal, float vect_1[13], float *vect_2);
void produit_scal_vect_6(float scal, float vect_1[13], float *vect_2);
float produit_scal(float vect_1[4], float vect_2[4]);
double produit_scal_double(double vect_1[4], double vect_2[4]);
	
/*prototypes de checked_menu.c*/
void Checked_dessiner_contour_element();
void Checked_dessiner_contour_noeud();
void Checked_dessiner_afficher_houle();
void Checked_dessiner_contour_coulisse();
void Checked_dessiner_contour_winch();
void Checked_dessiner_contour_ball();
void Checked_dessiner_contour_triangle();
void Checked_dessiner_orientation_xy();
void Checked_dessiner_fils_u();
void Checked_dessiner_fils_v();
void Checked_dessiner_surface_front();
void Checked_dessiner_axes();
void Checked_dessiner_repere();
void Checked_dessiner_quadrillage();
void Checked_dessiner_surface_libre();
void Checked_dessiner_ballast_altitude();
void Checked_dessiner_cube_size();
/* debut modifdp du 4 mars 2010*/
void Checked_solidity_ratio();
void Checked_max_exit_size();
void Checked_flow_orientation();
/* fin modifdp du 4 mars 2010*/
void Checked_angle_fils();
void Checked_orientation_volume();
void Checked_volume_elementaire();
void Checked_surface_elementaire();
void Checked_defaut_discretisation();
void Checked_profondeur_barycentre();
void Checked_numero_element();
void Checked_type_element();
void Checked_commentaire();
void Checked_efforts_externes();
void Checked_eigen_values();
void Checked_deplacement();
void Checked_animation();
void Checked_animation_video();
void Checked_animation_eigenvalue();
void Checked_symmetry_no_symmetry();
void Checked_dessiner_afficher_houle();
void Checked_immersion();
void Checked_trajectoire();
void Checked_raideur_traction();
void Checked_raideur_compression();
void Checked_raideur_ouverture();
void Checked_tension();
void Checked_nrj();
void Checked_longueur_repos();
void Checked_longueur_tendue();
void Checked_masse_volumique();
void Checked_diametre();
void Checked_largeur_noeud();
void Checked_coefficient_cd();
void Checked_coefficient_f();
void Checked_section_element();
void Checked_volume_element();
void Checked_masse_element();
void Checked_masse_lineique();
void Checked_flottabilite();
void Checked_type_noeud();
void Checked_numero_noeud();
void Checked_masse_noeud();
void Checked_longueur_noeud();
void Checked_cd_noeud();
void Checked_effort_noeud();
void Checked_limite_noeud();
void Checked_sens_limite_noeud();
void Checked_deplacement_noeud();
void Checked_symmetrie_noeud();
void Checked_nb_mailles();


/*prototypes de commentaire.c*/
void commentaire();


/*prototypes utilises par dessiner_info_element.c*/
void Color(int c);
void Line(float x1,float y1,float x2, float y2);
void Text(float x,float y,char *str);
void Move_to(float x,float y);
void Line_to(float x,float y);
void Line_end();
void Surface_end();


/*prototypes de dessiner_info_element.c*/
void dessiner_contour_triangle_element();
void draw_contour_triangle_diamond(int pa);
void draw_contour_triangle_hexa(int pa);
void dessiner_orientation_volume();
void draw_orientation_volume_diamond(int pa);
void draw_orientation_volume_hexa(int pa);
void dessiner_surface_elementaire();
void draw_surface_elementaire_diamond(int pa);
void draw_surface_elementaire_hexa(int pa);
void dessiner_defaut_discretisation();
void draw_defaut_discretisation_diamond(int pa);
void dessiner_profondeur_barycentre();
void draw_profondeur_barycentre_diamond(int pa, int no);
void draw_profondeur_barycentre_hexa(int pa, int no);
void draw_profondeur_barycentre_element(int pa, int no);
void draw_profondeur_barycentre_coulisse(int pa, int no);
void draw_profondeur_barycentre_noeud(int pa, int no);
void dessiner_numero_element();
void draw_numero_element_diamond(int pa);
void draw_numero_element_hexa(int pa);
void draw_numero_element_barre(int pa);
void draw_numero_element_coulisse(int pa);
void dessiner_type_element();
void draw_type_element_diamond(int pa);
void draw_type_element_hexa(int pa);
void draw_type_element_barre(int pa);
void draw_type_element_coulisse(int pa);
void dessiner_raideur_traction();
void draw_raideur_traction_diamond(int pa);
void draw_raideur_traction_hexa(int pa);
void draw_raideur_traction_barre(int pa);
void draw_raideur_traction_coulisse(int pa);
void dessiner_raideur_compression();
void draw_raideur_compression_diamond(int pa);
void draw_raideur_compression_hexa(int pa);
void draw_raideur_compression_barre(int pa);
void draw_raideur_compression_coulisse(int pa);
void dessiner_raideur_ouverture();
void draw_raideur_ouverture_diamond(int pa);
void dessiner_tension();
void draw_tension_diamond(int pa);
void draw_tension_hexa(int pa);
void draw_tension_element(int pa);
void draw_tension_coulisse(int pa);
void dessiner_nrj();
void draw_nrj_diamond(int pa);
void draw_nrj_hexa(int pa);
void draw_nrj_element(int pa);
void draw_nrj_coulisse(int pa);
void dessiner_longueur_repos();
void draw_longueur_tendue_diamond(int pa);
void draw_longueur_tendue_hexa(int pa);
void draw_longueur_tendue_element(int pa);
void draw_longueur_repos_diamond(int pa);
void draw_longueur_repos_hexa(int pa);
void draw_longueur_repos_barre(int pa);
void draw_longueur_repos_coulisse(int pa);
void dessiner_longueur_tendue();
void draw_longueur_tendue_diamond(int pa);
void draw_longueur_tendue_hexa(int pa);
void draw_longueur_tendue_element(int pa);
void draw_longueur_tendue_coulisse(int pa);
void dessiner_masse_volumique();
void draw_masse_volumique_diamond(int pa);
void draw_masse_volumique_hexa(int pa);
void draw_masse_volumique_barre(int pa);
void draw_masse_volumique_coulisse(int pa);
void dessiner_diametre();
void draw_diametre_diamond(int pa);
void draw_diametre_hexa(int pa);
void draw_diametre_barre(int pa);
void draw_diametre_coulisse(int pa);
void dessiner_largeur_noeud();
void draw_largeur_noeud_diamond(int pa);
void dessiner_coefficient_cd();
void draw_coefficient_cd_diamond(int pa);
void draw_coefficient_cd_hexa(int pa);
void draw_coefficient_cd_barre(int pa);
void draw_coefficient_cd_coulisse(int pa);
void dessiner_coefficient_f();
void draw_coefficient_f_diamond(int pa);
void draw_coefficient_f_hexa(int pa);
void draw_coefficient_f_barre(int pa);
void draw_coefficient_f_coulisse(int pa);
void dessiner_section_element();
void draw_section_diamond(int pa);
void draw_section_hexa(int pa);
void draw_section_element(int pa);
void draw_section_coulisse(int pa);
void dessiner_volume_element();
void draw_volume_diamond(int pa);
void draw_volume_hexa(int pa);
void draw_volume_element(int pa);
void draw_volume_coulisse(int pa);
void dessiner_masse_element();
void draw_masse_diamond(int pa);
void draw_masse_hexa(int pa);
void draw_masse_element(int pa);
void draw_masse_coulisse(int pa);
void dessiner_masse_lineique();
void draw_masse_lineique_diamond(int pa);
void draw_masse_lineique_hexa(int pa);
void draw_masse_lineique_element(int pa);
void draw_masse_lineique_coulisse(int pa);
void dessiner_flottabilite();
void draw_flottabilite_diamond(int pa);
void draw_flottabilite_hexa(int pa);
void draw_flottabilite_element(int pa);
void draw_flottabilite_coulisse(int pa);
void dessiner_volume_elementaire();
void draw_volume_elementaire_diamond(int pa);
void draw_volume_elementaire_hexa(int pa);
void dessiner_orientation_xy_element();
void draw_orientation_xy_diamond(int pa);
void draw_orientation_xy_hexa(int pa);
void draw_longueur_repos_diamond(int pa);
void draw_longueur_tendue_coulisse(int pa);
void draw_volume_elementaire_diamond(int pa);
void draw_volume_elementaire_hexa(int pa);

/*prototypes de dessiner_info_noeud.c*/
void dessiner_type_noeud();
void draw_type_noeud_diamond(int pa);
void draw_type_noeud_hexa(int pa);
void draw_type_noeud_element(int pa);
void draw_type_noeud_coulisse(int pa);
void dessiner_numero_noeud();
void draw_numero_noeud_diamond(int pa);
void draw_numero_noeud_hexa(int pa);
void draw_numero_noeud_element(int pa);
void draw_numero_noeud_coulisse(int pa);
void dessiner_masse_noeud();
void draw_masse_noeud_diamond(int pa);
void draw_masse_noeud_hexa(int pa);
void draw_masse_noeud_element(int pa);
void draw_masse_noeud_coulisse(int pa);
void dessiner_longueur_noeud();
void draw_longueur_noeud_diamond(int pa);
void draw_longueur_noeud_hexa(int pa);
void draw_longueur_noeud_element(int pa);
void draw_longueur_noeud_coulisse(int pa);
void dessiner_cd_noeud();
void draw_cd_noeud_diamond(int pa);
void draw_cd_noeud_hexa(int pa);
void draw_cd_noeud_element(int pa);
void draw_cd_noeud_coulisse(int pa);
void dessiner_effort_noeud();
void draw_effort_noeud_diamond(int pa);
void draw_effort_noeud_hexa(int pa);
void draw_effort_noeud_element(int pa);
void draw_effort_noeud_coulisse(int pa);
void dessiner_limite_noeud();
void draw_limite_noeud_diamond(int pa);
void draw_limite_noeud_hexa(int pa);
void draw_limite_noeud_element(int pa);
void draw_limite_noeud_coulisse(int pa);
void dessiner_sens_limite_noeud();
void draw_sens_limite_noeud_diamond(int pa);
void draw_sens_limite_noeud_hexa(int pa);
void draw_sens_limite_noeud_element(int pa);
void draw_sens_limite_noeud_coulisse(int pa);
void dessiner_deplacement_noeud();
void draw_deplacement_noeud_diamond(int pa);
void draw_deplacement_noeud_hexa(int pa);
void draw_deplacement_noeud_element(int pa);
void draw_deplacement_noeud_coulisse(int pa);
void dessiner_symmetrie_noeud();
void draw_symmetrie_noeud_diamond(int pa);
void draw_symmetrie_noeud_hexa(int pa);
void draw_symmetrie_noeud_element(int pa);
void draw_symmetrie_noeud_coulisse(int pa);
void dessiner_nb_mailles();
void draw_nb_mailles_diamond(int paa);
void draw_nb_mailles_hexa(int paa);


/*prototypes utilises par dessiner_ps.c*/
void ColorRGB_ps(int r, int v, int b);


/*prototypes de dessiner_ps.c*/
void dessiner();
void dessiner2();
int Clip3(float *xx1,float *yy1,float *xx2,float *yy2);
void EffaceTriangle(int icolor, double dx1, double dy1, double dx2, double dy2, double dx3, double dy3);
void EffaceQuadrangle(int icolor, double dx1, double dy1, double dx2, double dy2, double dx3, double dy3, double dx4, double dy4);
void TraceSegment(int icolor, double dx1, double dy1, double dx2, double dy2);
void EcritText(int icolor, double dx, double dy, char *chaine, double decalage_y);

/*prototypes de dessiner_visualisation.c*/
void dessiner_contour_winch();
void draw_contour_winch(int pa);
void dessiner_contour_ball();
void draw_contour_ball(int pa);
void dessiner_contour_coulisse();
void draw_contour_coulisse(int pa);
void dessiner_contour_element();
void dessiner_contour_element2();
void dessiner_contour_element3();
void draw_contour_element3(int pa);
void draw_contour_noeud(int pa);
void draw_efforts_externes(int pa);
void draw_eigen_values(int pa);
void dessiner_contour_noeud();
void dessiner_afficher_houle();
void dessiner_angle_fils();
void draw_angle_fils(int pa);
/* debut modifdp du 4 mars 2010*/
void draw_solidity_ratio(int pa);
void draw_max_exit_size(int pa);
void draw_flow_orientation(int pa);
/* fin modifdp du 4 mars 2010*/
void dessiner_efforts_externes();
void dessiner_eigen_values();
void dessiner_immersion();
void draw_immersion_element(int pa);
void draw_immersion_surface(int pa);
void dessiner_trajectoire();
void draw_trajectoire_element(int pa);
void draw_trajectoire_surface(int pa);
void dessiner_deplacement();
void draw_deplacement_diamond(int pa);
void draw_deplacement_hexa(int pa);
void draw_deplacement_element(int pa);
void draw_deplacement_coulisse(int pa);
void dessiner_commentaire();
void dessiner_fils_u();
void draw_fils_u(int pa);
void draw_fils_u_hexa(int pa);
void draw_fils_v_hexa(int pa);
void dessiner_fils_v();
void draw_fils_v(int pa);
void trace_fil_hexa(float a1, float b1, float a2, float b2, float x1, float y1, float x2, float y2, float x3, float y3);
void pointille(float x1, float y1, float x2, float y2);
void dessiner_fils_uv();
void draw_fils_uv_hexa(int pa);
void dessiner_fils_u_initial();
void dessiner_fils_v_initial();
void dessiner_fils_uv_initial();
void dessiner_surface_libre();
void dessiner_ballast_altitude();
void dessiner_cube_size();
void dessiner_surface_front();
void dessiner_axes();
void dessiner_repere();
void dessiner_quadrillage();
void draw_twines(int pa, float ua, float xa, float ya, float ub, float xb, float yb, float uc, float xc, float yc);
void draw_twines_color(int color, int pa, float ua, float xa, float ya, float ub, float xb, float yb, float uc, float xc, float yc);
void draw_segment_color(int color, double x1m, double y1m, double x2m, double y2m);
void white_triangle_diamond(int pa);
void white_triangle_hexa(int pa);


/*prototypes de filet.c*/
void fils_contour_calculer();
void  hachu4_u(int pa, float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui);
void  hachu4_v(int pa, float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui);
void dessiner_quadrillage();

/*prototypes de filet_hexa.c*/
void fils_contour_hexa();
void  hachu_hexa_u(int pa, float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui);
void  hachu_hexa_v(int pa, float vh[],float uh1[],float uh2[],float nh,float Uh,float Ui);

/*prototypes degfx_base.c*/
int ColorRGB(int r, int v, int b);
void Color(int c);
void Line(float xx1,float yy1,float xx2, float yy2);
void Move_to (float x,float y);
void Line_to (float x,float y);
void Line_end ();
void Surface_end();
void Circle (float x,float y,float r);
void Text(float x,float y,char *str);
void Motif(int m);
void Size_font(int coef);
void Line_larg(int n);
void Rectangle_plein(float x,float y, float l, float h);
int ClipSegment(float *XX1,float *YY1,float *XX2,float *YY2);
void ClipArea();
void TraceClip();



/*prototypes de init_display.c*/
void init_display(int argc, char **argv, MyProgram *me);
void init_display_text(int argc, char **argv, MyProgram *me);

/*prototypes de interieur_triangle.c*/
int interieur_triangle(double xx1, double xx2, double xx3, double yy1, double yy2, double yy3);
double surface_triangle(double x1, double y1, double x2, double y2, double x3, double y3);

/*prototypes delecturedo3.c*/
int lectureDo3(char *nomfichier);

/*prototypes de animation.c*/
void animation();
void animation_video();

/*prototypes de animation2.c*/
void animation2(int code_video);

/*prototypes de lecture_don.c*/
void modif_materiau_elem(int num_elem_choisi, double raideur_traction_choisie, double raideur_compression_choisie, double masse_volumique_choisie, double diam_hydro_choisi, double coeff_trainee_normal_choisi, double coeff_trainee_tangent_choisi);
void lecture_don(char *nomfichier);
void lecture_des();
void lecture_des2(char *nomfichier);
int lecture_chaine(FILE *fic, char *chain);
int lecture_commentaire(FILE *fic, char *chain);

/*prototypes delecturedyn.c*/
int lecturedyn(char *nomfichier);


/*prototypes de lecturedo3.c*/
int lectureDo3(char *nomfichier);

/*prototypes de lecturesta.c*/
int lecturesta(char *nomfichier);


/*prototypes de lecturedyn.c*/
int lecturedyn(char *nomfichier);


/*prototypes de multireq.c*/
int GetValues_2(TagList *tags);
void edit(Widget w, void *data);
void edit_echelle(Widget w, void *data);
void edit_coupe(Widget w, void *data);
void edit_coupe2(Widget ww, float val, void *junk);
void edit_temps1(Widget ww, float val, void *junk);
void Entry_Temps(Widget ww, char *string, void *junk);
void edit_animation(Widget w, void *data);
void edit_nb_animation(Widget w, void *data);
void edit_eigenvalues(Widget w, void *data);


/*prototypes de postscript.c*/
void Chk_ps_open();
void Chk_ps_close();
void Text_ps(float x,float y, char *s);
void Line_ps(float xx1,float yy1,float xx2,float yy2);
void Move_to_ps (float x1,float y1);
void Line_to_ps (float x1,float y1);
void Line_end_ps ();
void Surface_end_ps ();
void Circle_ps (float xx1,float yy1,float r);
void Color_ps(int c);
void ColorRGB_ps(int r, int v, int b);
void Motif_ps(char d[],int n);
void Size_font_ps(int coef);
void Line_larg_ps(int n);
void Rectangle_plein_ps(float xx1,float yy1, float xx2,float yy2);
char *Date();

/*prototypes deqsort.c*/
void swapfloat(float *ttab1,float *ttab2);
void swapint(int *ttab1,int *ttab2);
void quicksort(float a[],int m, int n);
void tri();


/*prototypes de quitter.c*/
void quitter();

/*prototypes de redisplay.c*/
void redisplay(Widget ww, int new_width, int new_height, void *data);






/*prototypes de rotation.c*/
void Rotation_X(Widget ww, float val, void *junk);
void Rotation_Y(Widget ww, float val, void *junk);
void Entry_Rotation_X(Widget ww, char *string, void *junk);
void Entry_Rotation_Y(Widget ww, char *string, void *junk);
void rotation();
void rotation_fils();


/*prototypes de volume.c*/
int orientation_triangle(int elem);
void surface_volume(int elem, double frontx, double *surfacefront,double *volumefront);
double surface_triangle2(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);





/*prototypes de zoom.c*/
void button_down(Widget ww, int which_button, int x, int y, void *data);
void button_up(Widget ww, int which_button, int x, int y, void *data);



/*prototypes de coupe.c*/
void cedit(Widget w, void *data);
void GetCoupe();
