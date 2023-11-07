include ../../Makefile.inc
include ../Makefile_kernel.inc

INCLUDE = -I../include

all:	debug-armv7.a

### ARMV7

debug-armv7.a:	panic.armv7.o early_debug.armv7.o emergency_blink.armv7.o
	$(CROSS)$(AR) crs debug-armv7.a panic.armv7.o early_debug.armv7.o emergency_blink.armv7.o

panic.armv7.o:	panic.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o panic.armv7.o -c panic.c

early_debug.armv7.o:	early_debug.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o early_debug.armv7.o -c early_debug.c

emergency_blink.armv7.o:	emergency_blink.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o emergency_blink.armv7.o -c emergency_blink.c


clean:
	rm -f *~ *.o *.a
