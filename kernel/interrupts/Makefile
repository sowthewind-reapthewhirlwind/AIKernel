include ../../Makefile.inc
include ../Makefile_kernel.inc

INCLUDE = -I../include

all:	interrupts-armv7.a

### ARMV7

interrupts-armv7.a:	gic-400.armv7.o interrupts.armv7.o irq_handler.armv7.o
	$(CROSS)$(AR) crs interrupts-armv7.a gic-400.armv7.o interrupts.armv7.o irq_handler.armv7.o

####

gic-400.armv7.o:	gic-400.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o gic-400.armv7.o -c gic-400.c

####

interrupts.armv7.o:	interrupts.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o interrupts.armv7.o -c interrupts.c

irq_handler.armv7.o:	irq_handler.s
	$(CROSS)as $(ASFLAGS_ARMV7) -o irq_handler.armv7.o irq_handler.s

###

clean:
	rm -f *~ *.o *.a
