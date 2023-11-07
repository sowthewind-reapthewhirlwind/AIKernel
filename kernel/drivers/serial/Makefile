include ../../../Makefile.inc
include ../../Makefile_kernel.inc

INCLUDE = -I../../include

all:	serial.armv7.a

#### ARMV7

serial.armv7.a:	pl011_uart.armv7.o mini_uart.armv7.o serial.armv7.o
	$(CROSS)$(AR) crs serial.armv7.a pl011_uart.armv7.o mini_uart.armv7.o serial.armv7.o

pl011_uart.armv7.o:	pl011_uart.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o pl011_uart.armv7.o -c pl011_uart.c

mini_uart.armv7.o:	mini_uart.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o mini_uart.armv7.o -c mini_uart.c

serial.armv7.o:	serial.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o serial.armv7.o -c serial.c

clean:
	rm -f *~ *.o *.a
