include ../../Makefile.inc
include ../Makefile_kernel.inc

INCLUDE = -I../include

all:	lib-armv7.a

### ARMV7

lib-armv7.a:	memcpy.armv7.o memory_benchmark.armv7.o memset.armv7.o printk.armv7.o string.armv7.o
	$(CROSS)$(AR) crs lib-armv7.a memcpy.armv7.o memory_benchmark.armv7.o memset.armv7.o \
		printk.armv7.o string.armv7.o

memcpy.armv7.o:	memcpy.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o memcpy.armv7.o -c memcpy.c

memory_benchmark.armv7.o:	memory_benchmark.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o memory_benchmark.armv7.o -c memory_benchmark.c

memset.armv7.o:	memset.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o memset.armv7.o -c memset.c

printk.armv7.o:	printk.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o printk.armv7.o -c printk.c

string.armv7.o:	string.c
	$(CROSS)$(CC) $(CFLAGS_ARMV7) $(INCLUDE) -o string.armv7.o -c string.c

###

clean:
	rm -f *~ *.o *.a
