#include <minix/sysutil.h>
#include "keyboard.c"

//commit test

unsigned int hook_id = KB_IRQ;

int kbd_test_scan(unsigned short ass) {
	if (ass == 0) {
		int ipc_status, irq_set = keyboard_subscribe_int();
		message msg;
		int r;
		unsigned int acabou=0;
		while (acabou == 0)
		{ /* You may want to use a different condition */
			/* Get a request message. */

			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
				printf("driver_receive failed with: %d", r);
				continue;
			}
			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */

					if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

						{
							keyboard_test_int(acabou);

						}

					}
					break;
				default:
					break; /* no other notifications expected: do nothing */
				}
			} else { /* received a standard message, not a notification */
				/* no standard messages expected: do nothing */
			}
		}
		printf("Program Finish\n");
		keyboard_unsubscribe_int();
		printf("Unsubscribed\n");

		/* To be completed */
	}
int kbd_test_leds(unsigned short n, unsigned short *leds) {
    /* To be completed */
}
int kbd_test_timed_scan(unsigned short n) {
    /* To be completed */
}


