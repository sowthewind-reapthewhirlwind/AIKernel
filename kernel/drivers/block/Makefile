include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	block.armv7.a

### ARMV7

block.armv7.a:	ramdisk.armv7.o
	$(CROSS)$(AR) crus block.armv7.a ramdisk.armv7.o
	$(CROSS)$(RANLIB) block.armv7.a

ramdisk.armv7.o:	ramdisk.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o ramdisk.armv7.o -c ramdisk.c

clean:
	rm -f *~ *.o *.a



