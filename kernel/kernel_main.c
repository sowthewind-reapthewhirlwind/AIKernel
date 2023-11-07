#include <stddef.h>
#include <stdint.h>

#include "lib/printk.h"

#include "boot/hardware_detect.h"

#include "drivers/drivers.h"
#include "drivers/block/ramdisk.h"
#include "drivers/serial/serial.h"

#include "fs/files.h"

#include "memory/memory.h"

#include "processes/idle_task.h"
#include "processes/process.h"
#include "processes/userspace.h"

#include "interrupts/interrupts.h"

#include "debug/panic.h"

/* Initrd hack */
#include "../userspace/initrd.h"

/* Homework 6 */
#include "version.h"

/* memory_kernel is the end of bss, so the address of the */
/* end of the kernel */
void kernel_main(uint32_t r0, uint32_t r1, uint32_t r2,
		uint32_t memory_kernel) {

	(void) r0;	/* Ignore boot method */

	/* Detect Hardware */
	hardware_detect((uint32_t *)r2);

	/* Setup Model-specific Variables based on harware revision */
	hardware_setup_vars();


	/*****************************/
	/* Initialize Serial Console */
	/*****************************/

	/* Serial console is most important so do that first */
	serial_init(SERIAL_UART_PL011);
	serial_printk("\n\n\nUsing pl011-uart\n");

	/************************/
	/* Boot messages!	*/
	/************************/

	printk("From bootloader: r0=%x r1=%x r2=%x\n",r0,r1,r2);

	/* Print boot message */
	printk("ECE531 OS\n");
	printk("Version %s\n\n",VERSION);

	/* Print model info */
	hardware_print_model(r1);

	/* Print command line */
	hardware_print_commandline();

	/******************************/
	/* Enable Interrupt Hardware  */
	/******************************/

	platform_irq_enable();

	/**************************/
	/* Init Device Drivers	  */
	/**************************/

	drivers_init_all();

	/**************************/
	/* Init Memory Hierarchy  */
	/**************************/

	memory_hierarchy_init(memory_kernel);

	/************************/
	/* Other init		*/
	/************************/

	/* Init the file descriptor table */
	fd_table_init();

	/* Initialize the ramdisk */
	ramdisk_init(initrd_image,sizeof(initrd_image));

	/* Mount the ramdisk */
	mount("/dev/ramdisk","/","romfs",0,NULL);

	/* Create idle task */
	create_idle_task();

	/* Enter our "init" process */
	start_userspace("/bin/shell");

	/* we should never get here */
	printk("Error starting init!\n");

	while(1) {

		/* Loop Forever */
		/* Should probably execute a wfi instruction */
		/* In theory only here for HZ until scheduler kicks in */
	}

}
