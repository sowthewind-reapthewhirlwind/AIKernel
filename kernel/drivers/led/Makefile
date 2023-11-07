include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	led.armv7.a

### ARMV7

led.armv7.a:	led.armv7.o
	$(CROSS)$(AR) crs led.armv7.a led.armv7.o

led.armv7.o:	led.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o led.armv7.o -c led.c

####

clean:
	rm -f *~ *.o *.a

