include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	gpio.armv7.a

#### ARMV7

gpio.armv7.a:	gpio.armv7.o
	$(CROSS)$(AR) crs gpio.armv7.a gpio.armv7.o

gpio.armv7.o:	gpio.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o gpio.armv7.o -c gpio.c

####

clean:
	rm -f *~ *.o *.a



