#include "test4.h"

int test_packet(unsigned short cnt) {

	int ipc_status, irq_set = mouse_subscribe_int();
	if (irq_set == -1)
	{
		printf("Fail subscribing mouse");
		return 1;
	}
	message msg;
	int r;
	int counter = 0;
	int n = 0;
	unsigned long out_buf = 0;
	unsigned long packet[3];


	//do{
		out_buf = mouse_int_handler();
		sys_outb(STATUS_REG, WRITE_B_MOUSE);
		issue_cmd_ms(STREAM_MODE) ;
		out_buf = mouse_int_handler();
			do
			{
				sys_outb(STATUS_REG, WRITE_B_MOUSE);
				issue_cmd_ms(ENABLE_STREAM);
				out_buf = mouse_int_handler();
				if(out_buf == ERROR || out_buf == ACK)
				{
					break;
				}
			}
			while(out_buf == RESEND);

			out_buf = 0;

	while (n < cnt) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE:
				/* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) {
					/* subscribed interrupt */

					out_buf = mouse_int_handler();
					printf("%x,\n", out_buf);
					if (counter == 0) {
						printf("counter 0");
						if (out_buf & BIT(3)) {
							printf("BIT(3)\n");
							packet[0] = out_buf;
							counter++;

						} else
							continue;
					} else

						if (counter == 1) {
							packet[1] = out_buf;
							counter++;
						} else if (counter == 2) {
							printf("Ta aqui\n");
							packet[2] = out_buf;
							counter = 0;
							n++;
							print_packet(sizeof(packet), packet);

						}

				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else {

		}
	}
	sys_outb(STATUS_REG, WRITE_B_MOUSE);
	if(issue_cmd_ms(DISABLE_STREAM))
	{
		return 1;
	}
	//issue_cmd_ms(STREAM_MODE);
	if(mouse_unsubscribe_int() == 1)
		return 1;
	else
		return 0;

	return 0;
}


int test_async(unsigned short idle_time) {
    /* To be completed ... */
}

int test_config(void) {
    /* To be completed ... */
}

int test_gesture(short length) {
    /* To be completed ... */
}
