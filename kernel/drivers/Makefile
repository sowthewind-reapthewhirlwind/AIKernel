include ../../Makefile.inc
include ../Makefile_kernel.inc

INCLUDE = -I../include

all:	drivers-armv7.a

#### ARMV7

drivers-armv7.a:	\
		drivers.armv7.o \
		bcm2835/bcm2835.armv7.a \
		block/block.armv7.a \
		console/console.armv7.a \
		gpio/gpio.armv7.a \
		led/led.armv7.a \
		serial/serial.armv7.a \
		timer/timer.armv7.a

	$(CROSS)$(AR) crsT drivers-armv7.a \
		drivers.armv7.o \
		bcm2835/bcm2835.armv7.a \
		block/block.armv7.a \
		console/console.armv7.a \
		gpio/gpio.armv7.a \
		led/led.armv7.a \
		serial/serial.armv7.a \
		timer/timer.armv7.a


drivers.armv7.o:	drivers.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o drivers.armv7.o -c drivers.c

bcm2835/bcm2835.armv7.a:	force_look
	cd bcm2835 && make

block/block.armv7.a:	force_look
	cd block && make

console/console.armv7.a:	force_look
	cd console && make

gpio/gpio.armv7.a:	force_look
	cd gpio && make

led/led.armv7.a:	force_look
	cd led && make

serial/serial.armv7.a:	force_look
	cd serial && make

timer/timer.armv7.a:	force_look
	cd timer && make

###

force_look:
	true


clean:
	rm -f *~ *.o *.a
	cd bcm2835 && make clean
	cd block && make clean
	cd console && make clean
	cd gpio && make clean
	cd led && make clean
	cd serial && make clean
	cd timer && make clean
