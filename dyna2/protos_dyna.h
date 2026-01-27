/*prototypes de actualiser_deplacement_balls.c*/
void actualiser_deplacement_balls();

/*prototypes de actualiser_position.c*/
void actualiser_position(char *nomfichier);

/*prototypes de ballast_calcul_dyna1.c*/
void ballast_calcul_dyna1();

/*prototypes de ballast_quantite_mouvement1.c*/
void ballast_quantite_mouvement1();

/*prototypes de ballast_speed.c*/
void ballast_speed();

/*prototypes de ball_contact.c*/
//void ball_contact();

/*prototypes de ball_drag.c*/
//void ball_drag();

/*prototypes de ball_inertie.c*/
//void ball_inertie();

/*prototypes de ball_netting_contact.c*/
//void ball_netting_contact();

/*prototypes de ball_pesanteur.c*/
//void ball_pesanteur();

/*prototypes de calculeffort.c*/
void calculeffort(int notria,double VV[4],double UV[4]);

/*prototypes de calculeffortZhan_dyna.c*/
void calculeffort_zhan_dyna();

/*prototypes de creedynamique.c*/
int creedynamique(char *nomfichier);

/*prototypes de deplacement.c*/
void  deplacement(char *nomfichier);

/*prototypes de ecrituredynamique.c*/
int ecrituredynamique(char *nomfichier);

/*prototypes de ecriturehauling.c*/
int ecriturehauling(char *nomfichier);

/*prototypes de ecriturestatique2.c*/
int ecriturestatique2(char *nomfichier);
int ecriturestatique3(char *nomfichier);

/*prototypes de effortexterieurs_dyn.c*/
void effortexterieurs_dyn();

/*prototypes de energy_bottom2.c*/
void energy_bottom2();

/*prototypes de estime_position.c*/
void estime_position();

/*prototypes de filethydro3.c*/
void filethydro3();

/*prototypes de filethydro4.c*/
void filethydro4();

/*prototypes de flotteurelement_dyna2.c*/
void flotteurelement_dyna2();

/*prototypes de fond_dyn.c*/
void fond_dyn();

/*prototypes de gammah.c*/
void gammah();

/*prototypes de gammah2.c*/
void gammah2();

/*prototypes de hauling_cable.c*/
void hauling_cable();
int find_bar(double speed, int cable, int extremity);

/*prototypes de inertie_element2.c*/
void inertie_element2();

/*prototypes de inertie_noeud.c*/
void inertie_noeud();

/*prototypes de inertie_surface2.c*/
void inertie_surface2();

/*prototypes de initialisation_dynamique.c*/
void initialisation_dynamique(char *nomfichier);

/*prototypes de initialisation_hauling_cable.c*/
void initialisation_hauling_cable();

/*prototypes de libere_memoire_dyna.c*/
void libere_memoire_dyna();

/*prototypes de miseajourPondFS_dyna.c*/
void miseajourPondFS_dyna();

/*prototypes de surfacemouillee.c*/
void surfacemouillee(int notria,double S1);
double surfacemouillee2(int notria,double S1);

/*prototypes de trainee_element3_flottant.c*/
void trainee_element3_flottant();

/*prototypes de trainee_noeud.c*/
void trainee_noeud();
void trainee_noeud_base(int ni,double lonx,double lony,double lonz,double cdx,double cdy,double cdz,double demirhovit,double immersion);

/*prototypes de vitesseh.c*/
void vitesseh();

/*prototypes de vitesseh2.c*/
void vitesseh2();


/**********************************************************************/
/*unix_2004*/
/*prototypes de catch_hexa.c*/
double surface_triangle2(double XX1, double YY1, double ZZ1, double XX2, double YY2, double ZZ2, double XX3, double YY3, double ZZ3);
double longueur_segment2(double XX1, double YY1, double ZZ1, double XX2, double YY2, double ZZ2);
double rayon_maxi();
void extrema_direction_x(double *minx,double *maxx);
void extrema_direction_courant(double *minx,double *maxx);
void extrema_direction_courant_meridian(double *minx,double *maxx);
void extrema_direction_courant_curvilinear(double *minx,double *maxx);
void changement_variable_catch();
void changement_variable(int direction);
void changement_variable2(double teta);
int orientation_triangle(int zh,int zi,int zj);
int orientation_triangle_val(int zh,int zi,int zj);
void surf_vol_elem(int zh,int zi,int zj,double frontx, double *surfacefront,double *volumefront);
void surf_vol_elem2(int zh,int zi,int zj,double frontx, double *surfacefront,double *volumefront,double *mean_height);
void surface_volume(double frontx, double *surfacefront,double *volumefront);
void surface_volume2(double frontx, double *surfacefront,double *volumefront,double *volumefront_height);
double nouveau_front2(double frx, double mix, double max);
void pres_pris_elem2(int elem, double pression, double frontx);
void pres_pris_elem3(int elem, double pression, double frontx);
void pression_partielle(double AA[4], double BB[4], double CC[4], double presqsion, double frontx, double *FA, double *FB, double *FC);
void pression_partielle2(double AA[4], double BB[4], double CC[4], double pression, double frontx, double *FA, double *FB, double *FC, double **Kp);
void pression_totale(double AA[4], double BB[4], double CC[4], double pression, double *FA, double *FB, double *FC, double **Kp);
void pres_pris_elem2_hexa(int elem, double pression, double frontx);
double pression_statique(int elem, double frontx);
void pression_prise2(double frontx);
void pression_prise3(double frontx,double front_height);
void nb_mesh_front(double frontx);
void mesh_front(int elem, double frontx, int *zn, double *nb);
void catch_hexa();
void catch_hexa_old();

/*prototypes de chaineeff3.c*/
void chaineeff3();

/*prototypes de chargement_don.c*/
void modif_materiau_elem(int num_elem_choisi, double raideur_traction_choisie, double raideur_compression_choisie, double masse_volumique_choisie, double diam_hydro_choisi, double coeff_trainee_normal_choisi, double coeff_trainee_tangent_choisi);
void charger(char *nomfichier);
int lecture_display_dyna(FILE *fic, char *chain);
int lecture_chaine(FILE *fic, char *chain);
int lecture_commentaire(FILE *fic, char *chain);

/*prototypes de coordonnees4.c*/
void coordonnees4();

/*prototypes de cut_triangle.c*/
int cut_triangle_plus_y(double y0, double y1, double z1, double y2, double z2, double y3, double z3, double *y4 ,double *z4, double *y5 ,double *z5, double *y6 ,double *z6, double *y7 ,double *z7, double *y8 ,double *z8, double *y9 ,double *z9);
int cut_triangle_moin_y(double y0, double y1, double z1, double y2, double z2, double y3, double z3, double *y4 ,double *z4, double *y5 ,double *z5, double *y6 ,double *z6, double *y7 ,double *z7, double *y8 ,double *z8, double *y9 ,double *z9);
int cut_triangle_plus_z(double z0, double y1, double z1, double y2, double z2, double y3, double z3, double *y4 ,double *z4, double *y5 ,double *z5, double *y6 ,double *z6, double *y7 ,double *z7, double *y8 ,double *z8, double *y9 ,double *z9);
int cut_triangle_moin_z(double z0, double y1, double z1, double y2, double z2, double y3, double z3, double *y4 ,double *z4, double *y5 ,double *z5, double *y6 ,double *z6, double *y7 ,double *z7, double *y8 ,double *z8, double *y9 ,double *z9);
int cut_segment_plus_y(double y0, double y1, double z1, double y2, double z2, double *y4 ,double *z4, double *y5 ,double *z5);
int cut_segment_moin_y(double y0, double y1, double z1, double y2, double z2, double *y4 ,double *z4, double *y5 ,double *z5);
int cut_segment_plus_z(double z0, double y1, double z1, double y2, double z2, double *y4 ,double *z4, double *y5 ,double *z5);
int cut_segment_moin_z(double z0, double y1, double z1, double y2, double z2, double *y4 ,double *z4, double *y5 ,double *z5);	
int cut_segment_plus_x(double x0, double x1, double y1, double x2, double y2, double *x4 ,double *y4, double *x5 ,double *y5);
int cut_segment_moin_x(double x0, double x1, double y1, double x2, double y2, double *x4 ,double *y4, double *x5 ,double *y5);
	
/*prototypes de direct.c*/
void direct();


/**********************************************************************/

/*prototypes de effortmax.c*/
double effortmax();

/*prototypes de effortmean.c*/
double effortmean();

/*prototypes de effortstructur.c*/
void effortstructur();

/*prototypes de effortsum.c*/
double effortsum();

/*prototypes de efforttendance.c*/
double efforttendance();

/*prototypes de effuv2.c*/
void effuv(int elem, double *VV, double *NM);

/*prototypes de etat_convergence.c*/
int etat_convergence();
double moyenne_convergence(int variable,int nb_pris, int periode);
double ecart_convergence(int variable,int nb_pris, int periode);

/*prototypes de etat_convergence.c*/
int etat_convergence();
double moyenne_convergence(int variable,int nb_pris, int periode);
double ecart_convergence(int variable,int nb_pris, int periode);

/*prototypes de etirement5.c*/
void etirement5();

/*prototypes de etirement_hexa.c*/
void etirement_hexa(int elem);
void calcul_lmn_hexa(int elem);
void calcul_lmn_iteratif(int elem);

/*prototypes de fermeture2.c*/
void fermeture2();

/*prototypes de fixationlaplusgrande.c*/
int fixationlaplusgrande();

/*prototypes de flexion2.c*/
void flexion2();

/*prototypes de flotteur2.c*/
void flotteur2();

/*prototypes de flotteursurf3.c*/
void flotteursurf3();

/*prototypes de impresultat.c*/
void impr_effort(int noe);
void impr_effort2(int noe, int axe, int nb_decim);
void impr_tension(int noe);
void impr_tension2(int noe, int nb_decim);
void impr_tension2_coulisse(int noe, int nb_decim);
void impr_position(int noe);
void impr_position2(int noe, int axe, int nb_decim);
void impr_distance(int noe1, int noe2);
void impr_distance_brut(int noe1, int noe2);
void impr_distance_brut2(int noe1, int noe2, int nb_decim);

/*prototypes de imprmatreel3.c*/
void imprmatreel3(int ncol1, int ncol2, int nlig1, int  nlig2, double *mat, int dimcol);

/*prototypes de imprmatrint4.c*/
void imprmatrint4(int ncol1,int ncol2,int nlig1,int  nlig2,int *mat,int dimcol);

/*prototypes de imprvectint.c*/
void imprvectint(int nb,int *vect);

/*prototypes de imprvectreel.c*/
void imprvectreel(int nb, double *vect);

/*prototypes de initialisation.c*/
void initialisation();

/*prototypes de inner_surface.c*/
void inner_surface();
void perimeter2(double frontx);
double mean_angle_2(double frt_x);
int recherche_symmetry();
void solve_linear_system(int nb_row, double **stiff, double *contr, double *result);

/*prototypes de largeurbande.c*/
int largeurbande();

/*prototypes de largeurmatrice.c*/
int largeurmatrice();

/*prototypes de lectParam2.c*/
int lectParam2();

/*prototypes de lectureDo4.c*/
int lectureDo4(char *nomfichier);


/*prototypes de lecturesta.c*/
int lecturesta(char *nomfichier);

/*prototypes de libere_memoire.c*/
void libere_memoire();

/*prototypes de limitetronquee.c*/
void limitetronquee();

/*prototypes de meridian.c*/
void meridian();

/*prototypes de misezero4.c*/
void misezero4();

/*prototypes de modification4.c*/
void modification4();

/*prototypes de modifraideur.c*/
int modifraideur();

/*prototypes de mouvementmax.c*/
double mouvementmax();

/*prototypes de mouvementmean.c*/
double mouvementmean();

/*prototypes de mouvementsum.c*/
double mouvementsum();

/*prototypes de mouvementtendance.c*/
double mouvementtendance();

/*prototypes de nbmaille_triangle.c*/
void nbmaille_triangle();

/*prototypes de nouvelleserie.c*/
void nouvelleserie();

/*prototypes de pesanteur.c*/
void pesanteur();

/*prototypes de pesanteurSurface.c*/
void pesanteurSurface();

/*prototypes de pesanteurelem.c*/
void pesanteurelem();

/*prototypes de pliage_barre.c*/
void pliage_barre();

/*prototypes de pliage_triangle.c*/
void produit_vect(double xx1, double yy1, double zz1, double xx2, double yy2, double zz2, double *xx3, double *yy3, double *zz3);
void produit_vect2(double vect_1[4], double vect_2[4], double *xx3, double *yy3, double *zz3);
void produit_vect3(double vect_1[4], double vect_2[4], double *vect_3);
double produit_scal(double vect_1[4], double vect_2[4]);
int trouver(int elem1, int sommet1, int *elem2, int *sommet2, double *U2, double *V2);
int trouver_sym(int elem1, int sommet1);
void diff_nx_vector(double v_vect[5], double d_vect[3], double *d_nx_vect);
void diff_ny_vector(double v_vect[5], double d_vect[3], double *d_ny_vect);
void diff_nz_vector(double v_vect[5], double d_vect[3], double *d_nz_vect);
void diff_mx_vector(double v_vect[5], double d_vect[3], double *d_mx_vect);
void diff_my_vector(double v_vect[5], double d_vect[3], double *d_my_vect);
void diff_mz_vector(double v_vect[5], double d_vect[3], double *d_mz_vect);
void diff_ps_vector(double v_vect[5], double d_vect[3], double coord_vect[13], double *d_ps_vect);
void diff_nn_vector(double v_vect[5], double d_vect[3], double n_vect[4], double *d_nn_vect);
void diff_mm_vector(double v_vect[5], double d_vect[3], double m_vect[4], double *d_mm_vect);
void diff_Alph_vector(double Alph, double seui, double v_vect[5], double d_vect[3], double n_vect[4], double m_vect[4], double *d_al_vect);
void diff_coef_vector(double hhh, double Alph, double seui, double nnn, double mmm, double v_vect[5], double d_al_vect[13], double d_nn_vect[13], double d_mm_vect[13], double *d_co_vect);
void diff_fx1_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fx1_vect);
void diff_fy1_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fy1_vect);
void diff_fz1_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fz1_vect);
void diff_fx2_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fx2_vect);
void diff_fy2_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fy2_vect);
void diff_fz2_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fz2_vect);
void diff_fx3_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fx3_vect);
void diff_fy3_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fy3_vect);
void diff_fz3_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fz3_vect);
void diff_fx4_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fx4_vect);
void diff_fy4_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fy4_vect);
void diff_fz4_vector( double coe, double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_ps_vect[13], double d_co_vect[13], double d_nn_vect[13], double d_nx_vect[13], double d_ny_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_my_vect[13], double d_mz_vect[13], double *d_fz4_vect);
void diff_alphax1_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nx_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_ps_vect[13], double *d_alphax1_vect);
void diff_alphay1_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_ny_vect[13], double d_mm_vect[13], double d_my_vect[13], double d_ps_vect[13], double *d_alphay1_vect);
void diff_alphaz1_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mz_vect[13], double d_ps_vect[13], double *d_alphaz1_vect);
void diff_alphax2_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nx_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_ps_vect[13], double *d_alphax2_vect);
void diff_alphay2_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_ny_vect[13], double d_mm_vect[13], double d_my_vect[13], double d_ps_vect[13], double *d_alphay2_vect);
void diff_alphaz2_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mz_vect[13], double d_ps_vect[13], double *d_alphaz2_vect);
void diff_alphax3_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nx_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_ps_vect[13], double *d_alphax3_vect);
void diff_alphay3_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_ny_vect[13], double d_mm_vect[13], double d_my_vect[13], double d_ps_vect[13], double *d_alphay3_vect);
void diff_alphaz3_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mz_vect[13], double d_ps_vect[13], double *d_alphaz3_vect);
void diff_alphax4_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nx_vect[13], double d_mm_vect[13], double d_mx_vect[13], double d_ps_vect[13], double *d_alphax4_vect);
void diff_alphay4_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_ny_vect[13], double d_mm_vect[13], double d_my_vect[13], double d_ps_vect[13], double *d_alphay4_vect);
void diff_alphaz4_vector( double alph, double d_alpha[13], double d_vect[3], double v_vect[5], double n_vect[3], double m_vect[3], double d_nn_vect[13], double d_nz_vect[13], double d_mm_vect[13], double d_mz_vect[13], double d_ps_vect[13], double *d_alphaz4_vect);

/*prototypes de pliage_triangle4.c*/
void pliage_triangle4();

/*prototypes de poidstri_hexa.c*/
void poidstri_hexa(int elem);

/*prototypes de poidstriang.c*/
void poidstriang(int elem);

/*prototypes de pression_interne.c*/
void pression_interne(int elem);

/*prototypes de raideur_coulisses.c*/
void raideur_coulisses();

/*prototypes de remonteb4.c*/
void remonteb4();

/*prototypes de resolution4.c*/
void resolution4();

/*prototypes de rota1.c*/
void rota1(double *VV,double *NM);

/*prototypes de rotation3.c*/
void rotation3(int zh,int zi,int zj);

/*prototypes de rotation4.c*/
void rotation4(int zh, int zi, int zj, double *angle3, double *angle2);

/*prototypes de serie.c*/
void serie();

/*prototypes de sortie_texte_ecran.c*/
void sortie_texte_ecran();

/*prototypes de sortie_texte_file.c*/
void sortie_texte_file(char *nomfichier);

/*prototypes de stockagec4.c*/
void stockagec4();

/*prototypes de surf_filtree.c*/
double surf_filtree();
double surf_filtree_direction(int direction);

/*prototypes de surglob2.c*/
void surglob2();

/*prototypes de surface3.c*/
void surface3();

/*prototypes de symetrie2.c*/
void symetrie2();

/*prototypes de tension.c*/
void tension();

/*prototypes de tension_bar.c*/
void tension_bar();

/*prototypes de tension_coulisses.c*/
void tension_coulisses();

/*prototypes de trainee_fil.c*actua/
void trainee_fil(int elem, double *VV, double *tfuv);

/*prototypes de trainee_front.c*/
void trainee_front();

/*prototypes de traineecourant2.c*/
void traineecourant2();

/*prototypes de traineevent1.c*/
void traineevent1();

/*prototypes de transnoeud.c*/
void transnoeud();

/*prototypes de contact_coulisses.c*/
void contact_coulisses();


