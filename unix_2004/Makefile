#MKLROOT = /opt/intel/composerxe-2011.3.174/mkl
#MKLROOT = /opt/intel/composer_xe_2011_sp1.6.233/mkl

CC = cc -O
#CFLAGS = -p
#CFLAGS = -tune ev5 -fast
CFLAGS =
# 
BIBOBJ =misezero4 miseajourPondFS resolution4 stockagec4  remonteb4 modification4 initialisation initialisation_pondFS allongement2 opening calculeffort_Zhan\
	transnoeud surf_filtree flexion2 fermeture2 libere_memoire pliage_triangle affectation_ze_rang\
	pliage_barre_pardiso2_3 pliage_barre_pardiso4 affectation_pardiso affectation_ia affectation\
	trouve_valeur modif_pardiso new_coor cut_triangle basic_bar_drag1 ballast_calcul2 deck_contact\
	pliage_triangle4 effortexterieurs pesanteur pesanteurelem traineecourant2 \
	flotteur2 flotteurelement2 tension tension_bar tension_constant_bar chargement_don tension_coulisses tension_winchs inner_surface\
	lectureDo4 ecriturestatique echangenoeuds sortie_texte_ecran sortie_texte_file\
	raideur_coulisses damping_element damping_triangle  damping_coulisse meridian\
	largeurmatrice fixationlaplusgrande serie largeurbande  chaineeff3 spheric_limit1\
	coordonnees4 effortsum effortmax efforttendance effortmean mouvementmax mouvementsum \
	mouvementtendance mouvementmean limitetronquee pression_interne limit_panels\
	nouvelleserie imprvectreel imprvectint imprmatrint4 modifraideur value_calculation\
	lectParam2 lecturesta etirement5 surglob2 rotation3 rotation4 base1 \
	base9 direct  nbmaille_triangle totalhydro2 compos trainee_front \
	rota1 eff1 effuv2 trainee_fil trainee_fil2 poidstriang pesanteurSurface imprmatreel3\
	etirement_hexa poidstri_hexa catch_hexa efflmn trouve_voisin filethydro4_sta surfacemouillee_sta calculeffort_sta\
	flotteursurf3 flotteursurf4 symetrie2 courantelem8 effort_trainee_elem_flottant efforttraineeelem efforttraineeelem_tab effortstructur fond\
	etat_convergence impresultat contact_coulisses traineevent1 catch2_volume recouvrement_x cage_volume ../lib_dp/alloc\
	nrutil jacobi jacobi_environ ran1 gasdev contact1 lecturespe lecturepre output_pressure\
	foamToFEMNET meshOF porousBaffleOF porousCellSetOF stlOF

OBJETS = $(BIBOBJ:=.o)
SOURCE = $(BIBOBJ:=.c)
INCLUDE = 4c19.h ../lib_dp/definition_lib.h
#OBJLIB  = ../lib_dp/librairy.o
#
all : unix
unix : unix.c libfil.flg
	cc $@.c libfil.a -L/usr/X11R6/lib/ -lm -o $@
#
libfil.flg : libfil.a
#	ranlib libfil.a
	touch -f $@
#
libfil.a : $(OBJETS) $(OBJLIB)
	ar rc libfil.a $(OBJETS) $(OBJLIB)
$(OBJETS) : $(INCLUDE)

clean:
	rm *.o
	rm libfil.a
	rm libfil.flg
#	rm *.data

# -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_gnu_thread.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -fopenmp -lpthread
