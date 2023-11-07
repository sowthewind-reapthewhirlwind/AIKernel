include Makefile.inc

all:	kernel/kernel7.img

kernel/kernel7.img:
	cd genromfs-0.5.2 && make
	cd userspace && make image
	cd kernel && make
	cd Drivers/Ethernet && make

clean:	
	cd genromfs-0.5.2 && make clean
	cd kernel && make clean
	cd userspace && make clean
	rm -f *~

submit:
	make clean
	tar -czvf hw6_submit.tar.gz genromfs-0.5.2 userspace kernel Makefile Makefile.inc README
