#include <stddef.h>
#include <stdint.h>

#include "lib/printk.h"

#include "drivers/drivers.h"
#include "drivers/led/led.h"
#include "drivers/timer/timer.h"
#include "drivers/serial/serial.h"
#include "drivers/pmu/arm-pmu.h"

void drivers_init_all(void) {

	/**************************/
	/* Device Drivers	  */
	/**************************/

	/* Set up ACT LED */
	led_init();

	/* Set up timer */
	timer_init();

	serial_enable_interrupts();


}
