AXIS_USABLE_LIBS = UCLIBC GLIBC
include $(AXIS_TOP_DIR)/tools/build/rules/common.mak

PROGS     = axis_acapwith_rust

CFLAGS += -Wall -g -O2

PKGS = glib-2.0 gio-2.0 axparameter
CFLAGS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --cflags $(PKGS))
LDLIBS += $(shell PKG_CONFIG_PATH=$(PKG_CONFIG_PATH) pkg-config --libs $(PKGS))

all:	$(PROGS)

axis_acapwith_rust: launcher.o
	$(CC) $(LDFLAGS) launcher.c $(LIBS) $(LDLIBS) -o $@

clean:
	rm -f $(PROGS) *.o core
	rm -f *.tar
