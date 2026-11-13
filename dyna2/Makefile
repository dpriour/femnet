#MKLROOT = /opt/intel/composerxe-2011.3.174/mkl
#MKLROOT = /opt/intel/composer_xe_2011_sp1.6.233/mkl

CC = cc -O
#CFLAGS = -p
#CFLAGS = -tune ev5 -fast
CFLAGS = 
# 
BIBOBJ =flotteurelement_dyna2 ecrituredynamique ecriturehauling creedynamique filethydro3 filethydro4 surfacemouillee actualiser_deplacement_balls\
	calculeffort trainee_element3_flottant initialisation_dynamique inertie_noeud energy_bottom2\
	actualiser_position inertie_element2  libere_memoire_dyna\
	inertie_surface2 trainee_noeud vitesseh2 gammah2 surface3 estime_position  initialisation_hauling_cable hauling_cable\
	../static_2026/misezero4 miseajourPondFS_dyna ../static_2026/resolution4 ../static_2026/stockagec4 ../static_2026/remonteb4 ../static_2026/modification4 ../static_2026/initialisation ../static_2026/allongement2 \
	../static_2026/transnoeud ../static_2026/surf_filtree ../static_2026/libere_memoire ../static_2026/trainee_fil deplacement\
	effortexterieurs_dyn ../static_2026/pesanteur ../static_2026/pesanteurelem ../static_2026/traineecourant2 ../static_2026/ballast_calcul2 ballast_calcul_dyna1 ballast_quantite_mouvement1 ballast_speed\
	../static_2026/flotteur2 ../static_2026/tension ../static_2026/tension_bar ../static_2026/chargement_don ../static_2026/tension_coulisses\
	../static_2026/lectureDo4 ../static_2026/ecriturestatique ecriturestatique2 ../static_2026/echangenoeuds ../static_2026/inner_surface\
	../static_2026/raideur_coulisses ../static_2026/sortie_texte_ecran ../static_2026/sortie_texte_file ../static_2026/base9\
	../static_2026/largeurmatrice ../static_2026/fixationlaplusgrande ../static_2026/serie ../static_2026/largeurbande ../static_2026/chaineeff3 \
	../static_2026/coordonnees4 ../static_2026/effortsum ../static_2026/effortmax ../static_2026/efforttendance ../static_2026/effortmean ../static_2026/mouvementmax ../static_2026/mouvementsum\
	../static_2026/mouvementtendance ../static_2026/mouvementmean ../static_2026/limitetronquee ../static_2026/pression_interne\
	../static_2026/nouvelleserie ../static_2026/imprvectreel ../static_2026/imprvectint ../static_2026/imprmatrint4 ../static_2026/modifraideur\
	../static_2026/lectParam2 ../static_2026/lecturesta ../static_2026/rotation3 ../static_2026/rotation4 ../static_2026/base1\
	../static_2026/direct ../static_2026/nbmaille_triangle ../static_2026/compos ../static_2026/trainee_front ../static_2026/initialisation_pondFS\
	../static_2026/rota1 ../static_2026/poidstriang ../static_2026/pesanteurSurface ../static_2026/imprmatreel3 ../static_2026/contact1 ../static_2026/affectation_ze_rang\
	../static_2026/etirement_hexa ../static_2026/poidstri_hexa ../static_2026/catch_hexa ../static_2026/efflmn ../static_2026/eff1 ../static_2026/effuv2\
	../static_2026/flotteursurf3 ../static_2026/flotteursurf4 ../static_2026/symetrie2 ../static_2026/effortstructur fond_dyn ../static_2026/impresultat\
	../static_2026/flexion2 ../static_2026/fermeture2 ../static_2026/pliage_triangle ../static_2026/pliage_triangle4 ../static_2026/traineevent1\
	../static_2026/etat_convergence ../static_2026/etirement5 ../static_2026/surglob2 ../static_2026/spheric_limit1 ../static_2026/cut_triangle\
	../static_2026/affectation ../static_2026/new_coor ../static_2026/trouve_valeur ../static_2026/effort_trainee_elem_flottant ../static_2026/basic_bar_drag1\
	../static_2026/affectation_ia ../static_2026/affectation_pardiso ../static_2026/pliage_barre_pardiso2_2 ../static_2026/pliage_barre_pardiso4\
	../static_2026/cage_volume  ../lib_dp/alloc ../static_2026/gasdev ../static_2026/ran1  ../static_2026/nrutil ../static_2026/calculeffort_Zhan calculeffort_Zhan_dyna
#	ball_drag ball_netting_contact ball_pesanteur ball_contact ball_inertie
	
OBJETS = $(BIBOBJ:=.o)
SOURCE = $(BIBOBJ:=.c)
INCLUDE = 4c19.h ../lib_dp/definition_lib.h
#OBJLIB = ../lib_dp/librairy.o
#
all : dyna
dyna : dyna.c libfil.flg
	cc $@.c libfil.a -L/usr/X11R6/lib/ -lm -o $@
#	cc $@.c libfil.a -L/usr/X11R6/lib/ -lm -o $@ -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_gnu_thread.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -fopenmp -lpthread -fopenmp
#
libfil.flg : libfil.a
#	ranlib libfil.a
	touch -f $@
#
libfil.a : $(OBJETS)
	ar rc libfil.a $(OBJETS) $(OBJLIB)
$(OBJETS) : $(INCLUDE)

clean:
	rm *.o
	rm libfil.a
	rm libfil.flg
