#include "keyboard.h"
#include "timer.h"
#include "i8042.h"

//commit test

static unsigned int counter = 0;
unsigned long outbufass = 0;
unsigned long statusandobf = 0;

int kbd_test_scan(unsigned short ass) {

	int ipc_status, irq_set = keyboard_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0;
	unsigned long out_buf2 = 0;
	unsigned int bytes_2 = 0;
	while (out_buf != ESC_CODE) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					if (bytes_2 == 0) {
						if (ass == 0)
						{
							out_buf = keyboard_int_handler();

						}
						else {
							do {
								keyboardasm();
							} while (statusandobf == 0);
							readoutbuf();
							out_buf = outbufass;

						}
						if (out_buf == OUT_BUF_2BYTES) {
							bytes_2 = 1;
							out_buf2 = out_buf << 8;
						} else {
							print_code(&out_buf);
						}
					} else if (bytes_2 == 1) {
						out_buf = keyboard_int_handler();
						out_buf |= out_buf2;
						bytes_2 = 0;
						print_code(&out_buf);
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

	printf("Program Finished\n");
	if (keyboard_unsubscribe_int() == 0) {
		out_buf = keyboard_int_handler();    //to clean the out buffer after unsubscribed it
		printf("Unsubscribed\n");
		return 0;
	} else {
		return 1;
	}


}

int kbd_test_leds(unsigned short n, unsigned short *leds) {

	keyboard_subscribe_int();

	int ipc_status;
	int irq_set = timer_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0, out_buf_bit_send = 0;
	unsigned long leds_set = 0;
	int counter = 0;
	int i = 0;
	int nr = 0;
	unsigned long data;
	//sys_inb(KBD_OUT_BUF, &data);

	while (counter < n * 60) {
		//printf("esta no while");
		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) {

					if (counter % 60 == 0) {
						do {
							if(issue_cmd_kbd(ON_OFF_LEDS) == -1)
							{
								return 1;
							}
							data = keyboard_int_handler();
							if(data == 1)
								return 1;
							if (data != 0x9c)
								out_buf = data;

						} while (out_buf == RESEND || out_buf == ERROR);

						if (out_buf == ACK) {
						do {

								leds_set ^= BIT(leds[i]);
								if(issue_cmd_kbd(leds_set) == -1)
									return 1;

								out_buf_bit_send = keyboard_int_handler();
								if(out_buf_bit_send == 1)
									return 1;
								if (out_buf_bit_send == RESEND){
									leds_set ^= BIT(leds[i]);
								}
								nr++;
							}
							while((out_buf_bit_send == RESEND) && nr<=5);

							if (out_buf_bit_send == ACK) {
								print_led(leds[i], leds_set);
							}

							if (out_buf_bit_send == ERROR) {
								leds_set ^= BIT(leds[i]);
								i--;
								continue;
							}
						}

						i++;
					}
					counter++;
				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		}
	}

	if ((timer_unsubscribe_int() != 0) && (keyboard_unsubscribe_int() != 0)) {
			return 1;
		} else {
			out_buf = keyboard_int_handler();  //to clean the out buffer after unsubscribed it
			if(out_buf == 1)
				return 1;
			printf("\nUnsubscribed");
			return 0;
		}
}

int kbd_test_timed_scan(unsigned short n) {
	int ipc_status, irq_set1 = keyboard_subscribe_int(), irq_set2 = timer_subscribe_int();
	if((irq_set1 == -1) ||(irq_set2 == -1))
		return 1;
	message msg;
	int r;
	unsigned long out_buf = 0;
	unsigned long out_buf2 = 0;
	unsigned int bytes_2 = 0;
	static unsigned int counter = 0;

	while ((out_buf != ESC_CODE) && (counter <= n * 60)) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set2) {

					timer_int_handler(&counter);

				}
				if (msg.NOTIFY_ARG & irq_set1) {
					if (bytes_2 == 0) {
						out_buf = keyboard_int_handler();

						if (out_buf == OUT_BUF_2BYTES) {
							bytes_2 = 1;
							out_buf2 = out_buf << 8;
						} else {
							print_code(&out_buf);
						}
					} else if (bytes_2 == 1) {
						out_buf = keyboard_int_handler();

						out_buf |= out_buf2;
						bytes_2 = 0;
						print_code(&out_buf);
					}
					counter = 0;
				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}

	}

	if ((timer_unsubscribe_int() != 0) && (keyboard_unsubscribe_int() != 0)) {
		return 1;
	} else {
		out_buf = keyboard_int_handler();  //to clean the out buffer after unsubscribed it

		printf("\nUnsubscribed");
		return 0;
	}
}

