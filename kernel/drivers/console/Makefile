include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	console.armv7.a

#### ARMv7

console.armv7.a:	console_io.armv7.o
	$(CROSS)$(AR) crus console.armv7.a console_io.armv7.o
	$(CROSS)$(RANLIB) console.armv7.a

console_io.armv7.o:	console_io.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o console_io.armv7.o -c console_io.c


####

clean:
	rm -f *~ *.o *.a
