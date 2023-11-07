include ../../Makefile.inc
include ../Makefile_kernel.inc

INCLUDE = -I../include

all:	time-armv7.a

### ARMV7

time-armv7.a:	time.armv7.o
	$(CROSS)$(AR) crs time-armv7.a time.armv7.o

time.armv7.o:	time.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o time.armv7.o -c time.c

###

clean:
	rm -f *~ *.o *.a
