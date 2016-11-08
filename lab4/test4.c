#include "test4.h"

int test_packet(unsigned short cnt) {

	int ipc_status, irq_set = mouse_subscribe_int();

	if (irq_set == -1) {
		printf("Fail subscribing mouse");
		return 1;
	}
	message msg;
	int r;
	int counter = 0;
	int n = 0;
	unsigned long out_buf = 0;
	unsigned long out_buf2 = 0;
	unsigned long packet[3];

	/*do
	 {
	 if (set_kbc_mouse() == -1) //set kbc to read mouse
	 return 1;

	 do{

	 issue_cmd_ms(STREAM_MODE);
	 out_buf = mouse_int_handler();

	 if ((out_buf & READ_KBC) == READ_KBC)
	 {
	 if(out_buf == ACK)
	 {
	 break;
	 }
	 else if( out_buf == NACK)
	 {
	 continue;
	 }
	 else if(out_buf == ERROR)
	 {
	 break;
	 }
	 }
	 else
	 {
	 out_buf = ERROR;
	 break;
	 }
	 }while(out_buf == NACK);

	 if(out_buf == ERROR)
	 {
	 continue;
	 }
	 else
	 break;

	 }while(out_buf == ERROR);*/

	do {
		if (set_kbc_mouse() == -1) //set kbc to read mouse
			return 1;

		issue_cmd_ms(ENABLE_STREAM);
		out_buf = mouse_int_handler();

	} while (out_buf != ACK);

	while (n < cnt) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					sys_inb(MS_OUT_BUF, &out_buf2);
					//mouse = (unsigned int) out_buf2;

					//printf("%x\n", mouse);

					if (counter == 2) {
						//printf("Ta aqui\n");
						packet[2] = out_buf2;
						counter = 0;
						n++;
						print_packet(3, packet);

					}

					if (counter == 1) {
						//printf("esta no counter1\n");
						packet[1] = out_buf2;
						counter++;
					}
					if (counter == 0) {
						//printf("counter 0");
						if (out_buf2 & BIT(3)) {
							//printf("BIT(3)\n");
							packet[0] = out_buf2;
							//printf("escreveu no pos 0\n");
							counter++;
							//printf("%d\n", counter);

						}
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
	do {
		if (set_kbc_mouse() == -1) //set kbc to read mouse
			return 1;

		issue_cmd_ms(DISABLE_STREAM);
		out_buf = mouse_int_handler();

	} while (out_buf != ACK);
	printf("Stream Disabled\n");
	//issue_cmd_ms(STREAM_MODE);
	out_buf = mouse_int_handler();

	if (mouse_unsubscribe_int() == 1)
		return 1;
	else
		return 0;
	return 0;
}

int test_async(unsigned short idle_time) {
	int ipc_status, irq_set1 = mouse_subscribe_int(), irq_set2 =
			timer_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0;
	static unsigned int counter_timer = 0;
	int counter = 0;
	int n = 0;
	unsigned long out_buf2 = 0;
	unsigned long packet[3];

	if ((irq_set1 == -1) || (irq_set2 == -1))
		return 1;

	do {
		if (set_kbc_mouse() == -1) //set kbc to read mouse
			return 1;

		issue_cmd_ms(ENABLE_STREAM);
		out_buf = mouse_int_handler();

	} while (out_buf != ACK);

	while (counter_timer <= idle_time * 60) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set2) {

					timer_int_handler(&counter_timer);

				}
				if (msg.NOTIFY_ARG & irq_set1) {
					sys_inb(MS_OUT_BUF, &out_buf2);
					//mouse = (unsigned int) out_buf2;

					//printf("%x\n", mouse);

					if (counter == 2) {
						//printf("Ta aqui\n");
						packet[2] = out_buf2;
						counter = 0;
						n++;
						print_packet(3, packet);

					}

					if (counter == 1) {
						//printf("esta no counter1\n");
						packet[1] = out_buf2;
						counter++;
					}
					if (counter == 0) {
						//printf("counter 0");
						if (out_buf2 & BIT(3)) {
							//printf("BIT(3)\n");
							packet[0] = out_buf2;
							//printf("escreveu no pos 0\n");
							counter++;
							//printf("%d\n", counter);

						}
					}
					counter_timer = 0;
				}

				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}
	do {
		if (set_kbc_mouse() == -1) //set kbc to read mouse
			return 1;

		issue_cmd_ms(DISABLE_STREAM);
		out_buf = mouse_int_handler();

	} while (out_buf != ACK);

	//issue_cmd_ms(STREAM_MODE);
	out_buf = mouse_int_handler();

	if ((mouse_unsubscribe_int() == 1) || (timer_unsubscribe_int() == 1))
		return 1;
	else
		return 0;

	return 0;
}

int test_config(void) {

	int ipc_status, irq_set = mouse_subscribe_int();
	message msg;
	int r;
	int counter = 0;
	int n = 0;
	unsigned long out_buf = 0;
	unsigned long out_buf2 = 0;
	int i = 0;

	if (irq_set == -1) {
		printf("Fail subscribing mouse");
		return 1;
	}
	do {
				if (set_kbc_mouse() == -1) //set kbc to read mouse
					return 1;

				issue_cmd_ms(ENABLE_STREAM);
				out_buf = mouse_int_handler();

			} while (out_buf != ACK);
	do {
		if (set_kbc_mouse() == -1) //set kbc to read mouse
			return 1;

		issue_cmd_ms(STATUS_REQUEST);
		out_buf = mouse_int_handler();

	} while (out_buf != ACK);


	for (i=0; i < 3; i++) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) {

					sys_inb(MS_OUT_BUF, &out_buf2);

					if (i == 0)
					{
						if (out_buf2 & BIT(7) & BIT(3))
						{
							printf("First configuration byte is not correct\n");
							return 1;
						}
						else
						{
							print_conf_byte1(&out_buf2);
						}
					}
					if (i == 1)
					{
						if (out_buf2 & CONF_BYTE2_ZEROS) {
							printf(
									"Second configuration byte is not correct\n");
							return 1;
						} else {
							printf("Resolution: %d counter per mm\n",
									pow(out_buf2, 2));
						}
					} else if (i == 2) {
						printf("Sample Rate: %d\n", out_buf2);
					}

				}
				break;
			default:
				break;
			}

		}
	}
	do {
			if (set_kbc_mouse() == -1) //set kbc to read mouse
				return 1;

			issue_cmd_ms(DISABLE_STREAM);
			out_buf = mouse_int_handler();

		} while (out_buf != ACK);

	out_buf = mouse_int_handler();

	if (mouse_unsubscribe_int() == 1)
		return 1;
	else
		return 0;

	return 0;
}

int test_gesture(short length) {
	/* To be completed ... */
}
