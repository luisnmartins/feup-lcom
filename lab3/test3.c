
#include "keyboard.h"

#include "timer_lab3.h"

//commit test

static unsigned int counter = 0;
unsigned long outbufass = 0;

int kbd_test_scan(unsigned short ass)
{


		int ipc_status, irq_set = keyboard_subscribe_int();
		message msg;
		int r;
		unsigned long  out_buf = 0;
		unsigned long out_buf2 = 0;
		unsigned int bytes_2=0;
		while (out_buf != ESC_CODE)
		{ /* You may want to use a different condition */
			/* Get a request message. */

			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
			{
				printf("driver_receive failed with: %d", r);
				continue;
			}
			if (is_ipc_notify(ipc_status))
			{ /* received notification */
				switch (_ENDPOINT_P(msg.m_source))
				{
				case HARDWARE: /* hardware interrupt notification */

					if (msg.NOTIFY_ARG & irq_set)
					{ /* subscribed interrupt */

						if (bytes_2 == 0)
						{
							if (ass == 0)
								out_buf = keyboard_test_int();
							else
							{
								while(1)
								{

									outbufass = 0;
									keyboardasm();
									out_buf = outbufass;
									if (outbufass != OUT_BUFF_ERR)
										break;
								}
								/*outbufass = 0;
								keyboardasm();
								out_buf = outbufass;*/


							}
							if (out_buf == OUT_BUF_2BYTES)
							{
								bytes_2 = 1;
								out_buf2 = out_buf << 8;
							} else
							{
								print_code(&out_buf);
							}
						} else if (bytes_2 == 1)
						{
							out_buf = keyboard_test_int();
							out_buf |= out_buf2;
							bytes_2 = 0;
							print_code(&out_buf);
						}


					}

					break;
				default:
					break; /* no other notifications expected: do nothing */
				}
			}
			else { /* received a standard message, not a notification */
				/* no standard messages expected: do nothing */
			}
		}

		printf("Program Finished\n");
		if (keyboard_unsubscribe_int() == 0)
		{
			printf("Unsubscribed\n");
			return 0;
		} else
		{
			return 1;
		}

		/* To be completed */
	}


int kbd_test_leds(unsigned short n, unsigned short *leds) {

	keyboard_subscribe_int();
	printf("Teclado subscrito\n");

	int ipc_status;
	int irq_set = timer_subscribe_int();

	int flag0 = 0, flag1 = 0, flag2 = 0;
	message msg;
	int r;
	unsigned long out_buf = 0, out_buf_bit_send = 0;
	int led1 = 0, led2 = 0, led3 = 0;
	int counter = 0;
	int i = 0;
	unsigned long data;
	sys_inb(KBD_OUT_BUF, &data);

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
						issue_cmd_kbd(ON_OFF_LEDS);
						data = keyboard_test_int();
						if(data != 0x9c)
							out_buf = data;

						} while (out_buf == RESEND || out_buf == ERROR);

						//printf("Outbuf: %x", out_buf);
						if (out_buf == ACK) {
							issue_cmd_kbd(BIT(leds[i]));
							out_buf_bit_send = keyboard_test_int();
							while (out_buf_bit_send == RESEND) {
								issue_cmd_kbd(BIT(leds[i]));
								out_buf_bit_send = keyboard_test_int();
							}
						} if (out_buf_bit_send == ERROR) {
							i--;
							continue;
						} else if (out_buf_bit_send == ACK) {
							if (leds[i] == 0) {
								print_led(leds[i], &flag0);
							} else if (leds[i] == 1) {
								print_led(leds[i], &flag1);
							} else if (leds[i] == 2) {
								print_led(leds[i], &flag2);
							}
						} else {

						}
						i++;
					}
					counter++;
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
	if ((timer_unsubscribe_int() == OK))
	{
		if(keyboard_unsubscribe_int() == OK)
			{printf("\nUnsubscribed");
			return 0;
			}
	}else {
			return 1;
		}

}




int kbd_test_timed_scan(unsigned short n) {
	int ipc_status, irq_set1 = keyboard_subscribe_int(), irq_set2 = timer_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0;
	unsigned long out_buf2 = 0;
	unsigned int bytes_2=0;
	unsigned int seg=0;
	static  unsigned int counter = 0;





	while ((out_buf != ESC_CODE) && (counter<= n*60))
	{ /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
		{
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status))
		{ /* received notification */
			switch (_ENDPOINT_P(msg.m_source))
			{
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set2)
				{

					counter++;

				}
				if(msg.NOTIFY_ARG & irq_set1)
				{
					if (bytes_2 == 0)
					{
						out_buf = keyboard_test_int();
						if (out_buf == OUT_BUF_2BYTES)
						{
							bytes_2 = 1;
							out_buf2 = out_buf << 8;
						} else
						{
							print_code(&out_buf);
						}
					} else if (bytes_2 == 1)
					{
						out_buf = keyboard_test_int();
						out_buf |= out_buf2;
						bytes_2 = 0;
						print_code(&out_buf);
					}
					counter=0;
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
		printf("\nUnsubscribed");
		return 0;
	}
}


