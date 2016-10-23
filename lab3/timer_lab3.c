#include "timer_lab3.h"

unsigned int thook_id = TIMER0_IRQ;


int timer_subscribe_int() {

	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &thook_id) != OK) {
		printf("Can't send and define the policy");
		return -1;
	}

	if (sys_irqenable(&thook_id) != OK) {
		printf("Can't enable the subscription");
		return -1;
	}

	return BIT(TIMER0_IRQ);

}

int timer_unsubscribe_int() {

	if (sys_irqdisable(&thook_id) != OK) {
		printf("Error executing sys_irqdisable");
		return 1;
	}
	if (sys_irqrmpolicy(&thook_id) != OK) {
		printf(
				"Error executing sys_irqmpolicy - failure unsubscribing the previous subscription of the interrupt");
		return 1;
	}

	return 0;

}






