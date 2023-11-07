include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	timer.armv7.a

#### ARMV7

timer.armv7.a:	sp804_timer.armv7.o
	$(CROSS)$(AR) crs timer.armv7.a sp804_timer.armv7.o

sp804_timer.armv7.o:	sp804_timer.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o sp804_timer.armv7.o -c sp804_timer.c

####

clean:
	rm -f *~ *.o *.a

