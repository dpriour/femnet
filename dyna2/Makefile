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
	../unix_2004/misezero4 miseajourPondFS_dyna ../unix_2004/resolution4 ../unix_2004/stockagec4 ../unix_2004/remonteb4 ../unix_2004/modification4 ../unix_2004/initialisation ../unix_2004/allongement2 \
	../unix_2004/transnoeud ../unix_2004/surf_filtree ../unix_2004/libere_memoire ../unix_2004/trainee_fil deplacement\
	effortexterieurs_dyn ../unix_2004/pesanteur ../unix_2004/pesanteurelem ../unix_2004/traineecourant2 ../unix_2004/ballast_calcul2 ballast_calcul_dyna1 ballast_quantite_mouvement1 ballast_speed\
	../unix_2004/flotteur2 ../unix_2004/tension ../unix_2004/tension_bar ../unix_2004/chargement_don ../unix_2004/tension_coulisses\
	../unix_2004/lectureDo4 ../unix_2004/ecriturestatique ecriturestatique2 ../unix_2004/echangenoeuds ../unix_2004/inner_surface\
	../unix_2004/raideur_coulisses ../unix_2004/sortie_texte_ecran ../unix_2004/sortie_texte_file ../unix_2004/base9\
	../unix_2004/largeurmatrice ../unix_2004/fixationlaplusgrande ../unix_2004/serie ../unix_2004/largeurbande ../unix_2004/chaineeff3 \
	../unix_2004/coordonnees4 ../unix_2004/effortsum ../unix_2004/effortmax ../unix_2004/efforttendance ../unix_2004/effortmean ../unix_2004/mouvementmax ../unix_2004/mouvementsum\
	../unix_2004/mouvementtendance ../unix_2004/mouvementmean ../unix_2004/limitetronquee ../unix_2004/pression_interne\
	../unix_2004/nouvelleserie ../unix_2004/imprvectreel ../unix_2004/imprvectint ../unix_2004/imprmatrint4 ../unix_2004/modifraideur\
	../unix_2004/lectParam2 ../unix_2004/lecturesta ../unix_2004/rotation3 ../unix_2004/rotation4 ../unix_2004/base1\
	../unix_2004/direct ../unix_2004/nbmaille_triangle ../unix_2004/compos ../unix_2004/trainee_front ../unix_2004/initialisation_pondFS\
	../unix_2004/rota1 ../unix_2004/poidstriang ../unix_2004/pesanteurSurface ../unix_2004/imprmatreel3 ../unix_2004/contact1 ../unix_2004/affectation_ze_rang\
	../unix_2004/etirement_hexa ../unix_2004/poidstri_hexa ../unix_2004/catch_hexa ../unix_2004/efflmn ../unix_2004/eff1 ../unix_2004/effuv2\
	../unix_2004/flotteursurf3 ../unix_2004/flotteursurf4 ../unix_2004/symetrie2 ../unix_2004/effortstructur fond_dyn ../unix_2004/impresultat\
	../unix_2004/flexion2 ../unix_2004/fermeture2 ../unix_2004/pliage_triangle ../unix_2004/pliage_triangle4 ../unix_2004/traineevent1\
	../unix_2004/etat_convergence ../unix_2004/etirement5 ../unix_2004/surglob2 ../unix_2004/spheric_limit1 ../unix_2004/cut_triangle\
	../unix_2004/affectation ../unix_2004/new_coor ../unix_2004/trouve_valeur ../unix_2004/effort_trainee_elem_flottant ../unix_2004/basic_bar_drag1\
	../unix_2004/affectation_ia ../unix_2004/affectation_pardiso ../unix_2004/pliage_barre_pardiso2_2 ../unix_2004/pliage_barre_pardiso4\
	../unix_2004/cage_volume  ../lib_dp/alloc ../unix_2004/gasdev ../unix_2004/ran1  ../unix_2004/nrutil ../unix_2004/calculeffort_Zhan calculeffort_Zhan_dyna
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
