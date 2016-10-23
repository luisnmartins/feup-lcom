
#include "keyboard.h"

#include "timer_lab3.h"

//commit test

static unsigned int counter = 0;

int kbd_test_scan(unsigned short ass)
{
	if (ass == 0)
	{

		int ipc_status, irq_set = keyboard_subscribe_int();
		message msg;
		int r;
		int out_buf = 0;
		int out_buf2 = 0;
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

	printf("Program Finish\n");
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

}
    /* To be completed */
}





int kbd_test_timed_scan(unsigned short n) {
	int ipc_status, irq_set1 = keyboard_subscribe_int(), irq_set2 = timer_subscribe_int();
	message msg;
	int r;
	int out_buf = 0;
	int out_buf2 = 0;
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


