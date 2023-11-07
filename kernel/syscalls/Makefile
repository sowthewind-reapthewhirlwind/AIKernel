include ../../Makefile.inc
include ../Makefile_kernel.inc

INCLUDE = -I../include

all:	syscalls-armv7.a

### ARMV7

syscalls-armv7.a:	syscalls.armv7.o swi_handler.armv7.o exit.armv7.o \
		nanosleep.armv7.o sysinfo.armv7.o times.armv7.o uname.armv7.o
	$(CROSS)$(AR) crs syscalls-armv7.a \
			syscalls.armv7.o swi_handler.armv7.o exit.armv7.o \
		nanosleep.armv7.o sysinfo.armv7.o times.armv7.o uname.armv7.o



syscalls.armv7.o:	syscalls.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o syscalls.armv7.o -c syscalls.c

swi_handler.armv7.o:  swi_handler.s
	$(CROSS)as $(ASFLAGS_ARMV7) -o swi_handler.armv7.o swi_handler.s

exit.armv7.o:	exit.c ../include/syscalls/exit.h
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o exit.armv7.o -c exit.c

nanosleep.armv7.o:	nanosleep.c ../include/syscalls/nanosleep.h
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o nanosleep.armv7.o -c nanosleep.c

sysinfo.armv7.o:	sysinfo.c ../include/syscalls/sysinfo.h
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o sysinfo.armv7.o -c sysinfo.c

times.armv7.o:	times.c ../include/syscalls/times.h
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o times.armv7.o -c times.c

uname.armv7.o:	uname.c ../include/syscalls/uname.h ../date.h
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o uname.armv7.o -c uname.c

###

clean:
	rm -f *~ *.o *.a ../date.h

force_look:
	true

# Fix for compile on macos / zsh?
../date.h:	force_look
	/bin/echo -n "#define COMPILE_DATE \"" > ../date.h
	date | tr -d '\n' >> ../date.h
	/bin/echo "\"" >> ../date.h

#../date.h:	force_look
#	echo -n "#define COMPILE_DATE \"" > ../date.h
#	date | tr -d '\n' >> ../date.h
#	echo "\"" >> ../date.h

