include ../../Makefile.inc
include ../Makefile_kernel.inc

INCLUDE = -I../include

all:	processes-armv7.a

### ARMV7

processes-armv7.a:	process.armv7.o exec.armv7.o \
		idle_task.armv7.o scheduler.armv7.o userspace.armv7.o \
		vfork.armv7.o waitpid.armv7.o waitqueue.armv7.o
	$(CROSS)$(AR) crs processes-armv7.a \
			process.armv7.o exec.armv7.o \
			idle_task.armv7.o scheduler.armv7.o userspace.armv7.o \
			vfork.armv7.o waitpid.armv7.o waitqueue.armv7.o


exec.armv7.o:	exec.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o exec.armv7.o -c exec.c

idle_task.armv7.o:	idle_task.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o idle_task.armv7.o -c idle_task.c

process.armv7.o:	process.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o process.armv7.o -c process.c

scheduler.armv7.o:	scheduler.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o scheduler.armv7.o -c scheduler.c

userspace.armv7.o:	userspace.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o userspace.armv7.o -c userspace.c

vfork.armv7.o:	vfork.c
	$(CROSS)$(CC) $(CFLAGS_ARM1176) $(INCLUDE) -o vfork.armv7.o -c vfork.c

waitpid.armv7.o:	waitpid.c
	$(CROSS)$(CC) $(CFLAGS_ARM1176) $(INCLUDE) -o waitpid.armv7.o -c waitpid.c

waitqueue.armv7.o:	waitqueue.c
	$(CROSS)$(CC) $(CFLAGS_ARM1176) $(INCLUDE) -o waitqueue.armv7.o -c waitqueue.c

###

clean:
	rm -f *~ *.o *.a
