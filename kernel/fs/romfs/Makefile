include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	romfs-armv7.a

### ARMV7

romfs-armv7.a:	romfs.armv7.o
	$(CROSS)$(AR) crs romfs-armv7.a romfs.armv7.o

romfs.armv7.o:	romfs.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o romfs.armv7.o -c romfs.c

clean:
	rm -f *~ *.o *.a

