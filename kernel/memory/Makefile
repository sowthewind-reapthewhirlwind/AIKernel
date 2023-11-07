include ../../Makefile.inc
include ../Makefile_kernel.inc

INCLUDE = -I../include

all:	memory-armv7.a

### ARMV7

memory-armv7.a:	memory.armv7.o armv7-mmu.o
	$(CROSS)$(AR) crs memory-armv7.a memory.armv7.o armv7-mmu.o

armv7-mmu.o:	armv7-mmu.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o armv7-mmu.o -c armv7-mmu.c

memory.armv7.o:	memory.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o memory.armv7.o -c memory.c

###

clean:
	rm -f *~ *.o *.a
