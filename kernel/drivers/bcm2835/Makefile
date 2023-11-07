include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	bcm2835.armv7.a

bcm2835.armv7.a:	bcm2835_io.armv7.o
	$(CROSS)$(AR) crs bcm2835.armv7.a bcm2835_io.armv7.o

###

bcm2835_io.armv7.o:	bcm2835_io.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o bcm2835_io.armv7.o -c bcm2835_io.c

clean:
	rm -f *~ *.o *.a



