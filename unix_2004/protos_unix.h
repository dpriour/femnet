/*prototypes de affectation.c*/
int affectation();

/*prototypes de affectation_ia.c*/
void affectation_ia();

/*prototypes de affectation_pardiso.c*/
int affectation_pardiso(double K, int l, int c);

/*prototypes de affectation_ze_rang.c*/
void affectation_ze_rang(int za, int zb, double val);

/*prototypes de alloc.c*/
double *Malloc_double(int nb);
float *Malloc_float(int nb);
int *Malloc_int(int nb);
struct commentaire *Malloc_commentaire(int nb);
double *Realloc_double(double *ff,int nb);
float *Realloc_float(float *ff,int nb);
int *Realloc_int(int *ff,int nb);
struct commentaire *Realloc_commentaire(struct commentaire *ff,int nb);
	

/*prototypes de allongement2.c*/
void allongement2(int elem);

/*prototypes de ballast_calcul2.c*/
void ballast_calcul2();

/*prototypes de base1.c*/
void base1(double angl1,int axeangl1,double angl2,int  axeangl2,int  nbcol,double *vect);

/*prototypes de base9.c*/
void base9(double angl1,int axeangl1,double angl2,int  axeangl2,int  nbcol,double (*mat)[10]);

/*prototypes de basic_bar_drag1.c*/
void basic_bar_drag1(double diam, double lgrepos, double cdnormal, double ftangent, double *ba, double *Vw, double *nt);

/*prototypes de calculeffort_sta.c*/
void calculeffort_sta(int notria,double VV[4],double UV[4]);

/*prototypes de calculeffort_Zhan.c*/
void filethydro4_sta_zhan();
void calculeffort_Zhan(int notria,double VV[4],double UV[4]);
double Solidity_diamond(int notria);

/*prototypes de cage_volume.c*/
double surface_triangle2_cage(double XX1, double YY1, double ZZ1, double XX2, double YY2, double ZZ2, double XX3, double YY3, double ZZ3);
int orientation_triangle_cage(int zh,int zi,int zj);
void surf_vol_elem_cage(int zh,int zi,int zj,double frontz, double *surfacefront,double *volumefront);
void extrema_direction_courant_cage_volume(double *minz,double *maxz, int nc);
void surface_volume_cage_volume(double frontz, double *surfacefront,double *volumefront, int nc);
void surface_cage_volume_volume(double frontz, double *surfacefront,double *volumefront, int nc);
float *cage_volume();
float *volume_cage();

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

/*prototypes de  catch2_volume.c*/
void extrema_direction_courant_catch2_volume(double *minx,double *maxx, int nc);
void surface_volume_catch2_volume(double frontx, double *surfacefront,double *volumefront, int nc);
double nouveau_front2_catch2_volume(double frx, double mix, double max, int nc);
void pression_prise2_catch2_volume(double frontx,int nc);
void catch2_volume();

/*prototypes de cage_volume.c*/
double surface_triangle2_cage(double XX1, double YY1, double ZZ1, double XX2, double YY2, double ZZ2, double XX3, double YY3, double ZZ3);
int orientation_triangle_cage(int zh,int zi,int zj);
void surf_vol_elem_cage(int zh,int zi,int zj,double frontz, double *surfacefront,double *volumefront);
void extrema_direction_courant_cage_volume(double *minz,double *maxz, int nc);
void surface_volume_cage_volume(double frontz, double *surfacefront,double *volumefront, int nc);
float* cage_volume();

/*prototypes de chaineeff3.c*/
void chaineeff3();

/*prototypes de chargement_don.c*/
void modif_materiau_elem(int num_elem_choisi, double raideur_traction_choisie, double raideur_compression_choisie, double masse_volumique_choisie, double diam_hydro_choisi, double coeff_trainee_normal_choisi, double coeff_trainee_tangent_choisi);
void charger(char *nomfichier);
int lecture_display_dyna(FILE *fic, char *chain);
int lecture_chaine(FILE *fic, char *chain);
int lecture_commentaire(FILE *fic, char *chain);

/*prototypes de compos.c*/
void compos(double *V,double *u);

/*prototypes de contact1.c*/
void contact1();
int contact_base(double p1[4], double p2[4], double p3[4], double p4[4], int elem_12, int elem_34, double *fp1, double *fp2, double *fp3, double *fp4);

/*prototypes de contact_coulisses.c*/
void contact_coulisses();

/*prototypes de coordonnees4.c*/
void coordonnees4();

/*prototypes de courantelem8.c*/
void courantelem8();

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
	
/*prototypes de damping_coulisse.c*/
void damping_coulisse();

/*prototypes de damping_element.c*/
void damping_element();

/*prototypes de damping_triangle.c*/
void damping_triangle();

/*prototypes de deck_contact.c*/
void deck_contact();
void calc_alphaa_betaa(double vect_41[4], double vect_12[4], double vect_23[4], double *alphaa, double *betaa);

/*prototypes de direct.c*/
void direct();

/*prototypes de echangenoeuds.c*/
void echangenoeuds(int Noeudi,int Noeudj);

/*prototypes de ecriturestatique.c*/
int ecriturestatique(char *nomfichier);

/*prototypes de eff1.c*/
void eff1(int elem);
void eff_hexa1(int elem);

/*prototypes de efflmn.c*/
void efflmn(int elem,double *VV,double *LMN,double longueur_repos);

/*prototypes de effortexterieurs.c*/
void effortexterieurs();

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

/*prototypes de effort_trainee_elem_flottant.c*/
void effort_trainee_elem_flottant(int zg,int zh,int zi,double *V,double *nt,double mhh);	

/*prototypes de efforttraineeelem.c*/
void efforttraineeelem(int zg,int zh,int zi,double *V);	

/*prototypes de efforttraineeelem_tab.c*/
void efforttraineeelem_tab(int zg,int zh,int zi,double *V);

/*prototypes de effuv2.c*/
void effuv(int elem, double *VV, double *NM);

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

/*prototypes de filethydro4_sta.c*/
void filethydro4_sta();

/*prototypes de fixationlaplusgrande.c*/
int fixationlaplusgrande();

/*prototypes de flexion2.c*/
void flexion2();

/*prototypes de flotteur2.c*/
void flotteur2();

/*prototypes de flotteurelement2.c*/
void flotteurelement2();

/*prototypes de flotteursurf3.c*/
void flotteursurf3();

/*prototypes de flotteursurf4.c*/
void flotteursurf4();

/*prototypes de fond.c*/
void fond();

/*prototypes de foamToFEMNET.c*/
int foamToFEMNET(char *nomfichier);

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
void imprvectreel1(int nb, int dec, double *vect);
void imprvectreel2(int nb, int dec, int col, double *vect);

/*prototypes de initialisation.c*/
void initialisation();

/*prototypes de initialisation_pondFS.c*/
void initialisation_pondFS();

/*prototypes de inner_surface.c*/
void inner_surface();
void perimeter2(double frontx);
double mean_angle_2(double frt_x);
int recherche_symmetry();
void solve_linear_system(int nb_row, double **stiff, double *contr, double *result);

/*prototypes de jacobi.c*/
void jacobi(float **a, int n, float d[], float **v, int *nrot);

/*prototypes de jacobi_environ.c*/
void jacobi_environ();

/*prototypes de largeurbande.c*/
int largeurbande();

/*prototypes de largeurmatrice.c*/
int largeurmatrice();

/*prototypes de lectParam2.c*/
int lectParam2(char *nomfichier);

/*prototypes de lectureDo4.c*/
int lectureDo4(char *nomfichier);

/*prototypes de lecturesta.c*/
int lecturesta(char *nomfichier);

/*prototypes de lecturepre.c*/
int lecturepre(char *nomfichier);

/*prototypes de lecturespe.c*/
int lecturespe(char *nomfichier);

/*prototypes de libere_memoire.c*/
void libere_memoire();

/*prototypes de limitetronquee.c*/
void limitetronquee();

/*prototypes de limit_panels.c*/
void limit_panels();

/*prototypes de meridian.c*/
void meridian();
void curvilinear();
void meridian_x();
void meridian_y();
void meridian_z();

/*prototypes de meshOF.c*/
void meshOF();

/*prototypes de misezero4.c*/
void misezero4();

/*prototypes de miseajourPondFS.c*/
void miseajourPondFS();

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

/*prototypes de new_coor.c*/
int new_coor(int i, int zi, int zj, int zk, int zl);

/*prototypes de nouvelleserie.c*/
void nouvelleserie();

/*prototypes de nrutil.c*/
void nrerror(char error_text[]);
float *vector(long nl, long nh);
int *ivector(long nl, long nh);
unsigned char *cvector(long nl, long nh);
unsigned long *lvector(long nl, long nh);
double *dvector(long nl, long nh);
float **matrix(long nrl, long nrh, long ncl, long nch);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
int **imatrix(long nrl, long nrh, long ncl, long nch);
float **submatrix(float **a, long oldrl, long oldrh, long oldcl, long oldch,	long newrl, long newcl);
float **convert_matrix(float *a, long nrl, long nrh, long ncl, long nch);
float ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_vector(float *v, long nl, long nh);
void free_ivector(int *v, long nl, long nh);
void free_cvector(unsigned char *v, long nl, long nh);
void free_lvector(unsigned long *v, long nl, long nh);
void free_dvector(double *v, long nl, long nh);
void free_matrix(float **m, long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch);
void free_submatrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_convert_matrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch,	long ndl, long ndh);

/*prototypes de opening.c*/
void orientation_netting();
void opening_mesh();
void opening();
void opening_stripe();
double nb_maille_devant(int elem, double planx);

/*prototypes de output_pressure.c*/
void output_pressure(char *nomfichier);

/*prototypes de pathOF.c*/
int pathOF(char *nomfichier);

/*prototypes de pesanteur.c*/
void pesanteur();

/*prototypes de pesanteurSurface.c*/
void pesanteurSurface();

/*prototypes de pesanteurelem.c*/
void pesanteurelem();

/*prototypes de pliage_barre.c*/
void pliage_barre();

/*prototypes de pliage_barre2.c
int pliage_barre2();*/

/*prototypes de pliage_barre_pardiso.c*/
void pliage_barre_pardiso();

/*prototypes de pliage_barre_pardiso2_2.c*/
void pliage_barre_pardiso2_2();

/*prototypes de pliage_barre_pardiso2_3.c*/
void pliage_barre_pardiso2_3();

/*prototypes de pliage_barre_pardiso4.c*/
void pliage_barre_pardiso4();
void toto4(int bar1, int bar2, int zii, int zjj, int zkk, int znn);

/*prototypes de pliage_barre_link.c*/
void pliage_barre_link();

/*prototypes de pliage_barre3.c*/
void pliage_barre3();

/*prototypes de porousBaffleOF.c*/
void porousBaffleOF();

/*prototypes de porousCellSetOF.c*/
void porousCellSetOF();

/*prototypes de resolution_mkl_pardiso.c*/
void resolution_mkl_pardiso();

/*prototypes de realloc_pardiso.c*/
void realloc_pardiso();

/*prototypes de pliage_triangle.c*/
void produit_vect(double xx1, double yy1, double zz1, double xx2, double yy2, double zz2, double *xx3, double *yy3, double *zz3);
void produit_vect2(double vect_1[4], double vect_2[4], double *xx3, double *yy3, double *zz3);
void produit_vect3(double vect_1[4], double vect_2[4], double *vect_3);
void add_vect(double vect_1[4], double vect_2[4], double *vect_3);
void substract_vect(double vect_1[4], double vect_2[4], double *vect_3);
void add_vect_6(double vect_1[4], double vect_2[4], double *vect_3);
void add_vect_12(double vect_1[4], double vect_2[4], double *vect_3);
double produit_scal(double vect_1[4], double vect_2[4]);
void produit_scal_vect(double scal, double vect_1[4], double *vect_2);
void add_scal_vect_1(double double_1, double vect_1[4], double *vect);
void add_scal_vect_2(double double_1, double vect_1[4], double double_2, double vect_2[4], double *vect);
void add_scal_vect_3(double double_1, double vect_1[4], double double_2, double vect_2[4], double double_3, double vect_3[4], double *vect);
void add_scal_vect_4(double double_1, double vect_1[4], double double_2, double vect_2[4], double double_3, double vect_3[4], double double_4, double vect_4[4], double *vect);
void add_scal_vect_5(double double_1, double vect_1[4], double double_2, double vect_2[4], double double_3, double vect_3[4], double double_4, double vect_4[4], double double_5, double vect_5[4], double *vect);
void produit_scal_vect_6(double scal, double vect_1[13], double *vect_2);
void produit_scal_vect_12(double scal, double vect_1[13], double *vect_2);
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

/*prototypes de recouvrement_x.c*/
int recouvrement_x(int element1, int element2, double *min, double *max, double *mean);

/*prototypes de remonteb4.c*/
void remonteb4();

/*prototypes de resolution_gradient.c*/
void resolution_gradient();

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

/*prototypes de spheric_limit1.c*/
void spheric_limit1();

/*prototypes de stockagec4.c*/
void stockagec4();

/*prototypes de stlOF.c*/
void stlOF();

/*prototypes de surf_filtree.c*/
double surf_filtree();
double surf_filtree_direction(int direction);

/*prototypes de surfacemouillee_sta.c*/
double surfacemouillee_sta(int notria,double S1);

/*prototypes de surglob2.c*/
void surglob2();

/*prototypes de symetrie2.c*/
void symetrie2();

/*prototypes de tension.c*/
void tension();

/*prototypes de tension_bar.c*/
void tension_bar();

/*prototypes de tension_constant_bar.c*/
void tension_constant_bar();

/*prototypes de tension_coulisses.c*/
void tension_coulisses();

/*prototypes de tension_winchs.c*/
void tension_winchs();

/*prototypes de totalhydro2.c*/
void totalhydro2();
void drag_normal_twine(double VV[4], double uu[4], int elem, double *FN, double **KN);
void drag_tangent_twine(double VV[4], double uu[4], int elem, double *FT, double **KT);

/*prototypes de trainee_fil.c*/
void trainee_fil(int elem, double *VV, double *tfuv);

/*prototypes de trainee_fil2.c*/
void trainee_fil2(int elem, double VV[4], double *tfuv);

/*prototypes de trainee_front.c*/
void trainee_front();

/*prototypes de traineecourant2.c*/
void traineecourant2();

/*prototypes de traineevent1.c*/
void traineevent1();

/*prototypes de transnoeud.c*/
void transnoeud();

/*prototypes de trouve_valeur.c*/
void trouve_valeur(int l, int c);

/*prototypes de trouve_voisin.c*/
void trouve_voisin();
int trouver2(int elem1, int sommet1, int *elem2, int *sommet2, double *U2, double *V2);

/*prototypes de value_calculation.c*/
double value_calculation3(double lim_Y, int sens_lim_Y);
double value_calculation2();
double value_calculation();
double value_calculation_triangle(double min_depth, double min_value, double max_depth, double max_value, double XX1, double XX2, double XX3, double YY1, double YY2, double YY3, double ZZ1, double ZZ2, double ZZ3, double sgn);


