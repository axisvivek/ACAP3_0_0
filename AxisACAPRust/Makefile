AXIS_USABLE_LIBS = UCLIBC GLIBC
include $(AXIS_TOP_DIR)/tools/build/rules/common.mak

PROGS     = axis_acapwith_rust

CFLAGS += -Wall -g -O2

all:	$(PROGS)

axis_acapwith_rust: launcher.o
	$(CC) $(LDFLAGS) launcher.c $(LIBS) $(LDLIBS) -o $@

clean:
	rm -f $(PROGS) *.o core
	rm -f *.tar
