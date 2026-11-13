CC ?= cc
PKG_CONFIG ?= pkg-config
CPPFLAGS += $(shell $(PKG_CONFIG) --cflags gtk+-3.0) -DLINUX -DTRILIBRARY
CFLAGS ?= -O2 -g
CFLAGS += -std=gnu99 -Wno-incompatible-pointer-types -Wno-implicit-function-declaration
LDLIBS += $(shell $(PKG_CONFIG) --libs gtk+-3.0) -lm

SRCS=base1.c batz.c charger.c dessiner_ps.c dessiner_visualisation.c \
	dessiner_info_element.c dessiner_info_noeud.c fct_sx.c init_display.c \
	lecture_don.c lecturedo3.c lecturesta.c quitter.c redisplay.c rotation.c \
	qsort.c filet.c filet_hexa.c gfx_base.c postscript.c volume.c \
	interieur_triangle.c multireq.c commentaire.c checked_menu.c alloc.c \
	lecturedyn.c animation.c animation2.c anim_rotation2.c zoom.c \
	../static_2026/nrutil.c gtk3_compat.c
OBJS=$(SRCS:.c=.o)

.PHONY: all clean
all: batz

batz: $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) batz core
