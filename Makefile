CC ?= cc
PKG_CONFIG ?= pkg-config
CPPFLAGS += $(shell $(PKG_CONFIG) --cflags gtk+-3.0) -DLINUX -DTRILIBRARY
CFLAGS ?= -O2 -g
CFLAGS += -std=gnu99 -Wno-incompatible-pointer-types -Wno-implicit-function-declaration
LDLIBS += $(shell $(PKG_CONFIG) --libs gtk+-3.0) -lm

SOURCES := $(filter-out phobos.c fct_sx.c multireq.c,$(wildcard *.c)) gtk3_compat.c
OBJECTS := $(SOURCES:.c=.o)

.PHONY: all clean
all: phobos

phobos: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) phobos core
