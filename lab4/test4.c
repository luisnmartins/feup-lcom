#include "test4.h"
#include "mouse.h"

typedef enum {
	INIT, DRAW, COMP
} state_t;
typedef enum {
	RDOW, RUP, TOLERANCE, VERT_LINE
} ev_type_t;

state_t st = INIT;



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


	do {
		if (set_kbc_mouse() == -1) //set kbc to read mouse
			return 1;

		issue_cmd_ms(DISABLE_STREAM);
		out_buf = mouse_int_handler();

	} while (out_buf != ACK);
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

					if (counter == 0) {

						if (out_buf2 & BIT(3)) {

							packet[0] = out_buf2;

						} else
							continue;
					} else if (counter == 1) {

						packet[1] = out_buf2;

					} else if (counter == 2) {

						packet[2] = out_buf2;

						print_packet(3, packet);
						counter = 0;
						n++;
						continue;

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

		issue_cmd_ms(DISABLE_STREAM);
		out_buf = mouse_int_handler();

	} while (out_buf != ACK);
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

					if (counter == 0) {

						if (out_buf2 & BIT(3)) {

							packet[0] = out_buf2;

						} else
							continue;
					} else if (counter == 1) {

						packet[1] = out_buf2;

					} else if (counter == 2) {

						packet[2] = out_buf2;

						print_packet(3, packet);
						counter = 0;
						n++;
						continue;

					}

					counter++;
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

	for (i = 0; i < 3; i++) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set) {

					sys_inb(MS_OUT_BUF, &out_buf2);

					if (i == 0) {
						if (out_buf2 & BIT(7) & BIT(3)) {
							printf("First configuration byte is not correct\n");
							return 1;
						} else {
							print_conf_byte1(&out_buf2);
						}
					}
					if (i == 1) {
						if (out_buf2 & CONF_BYTE2_ZEROS) {
							printf(
									"Second configuration byte is not correct\n");
							return 1;
						} else {
							printf("Resolution: %d counter per mm\n", 1<<out_buf2);
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
	int ipc_status, irq_set = mouse_subscribe_int();
	ev_type_t tipo;
	if (irq_set == -1) {
		printf("Fail subscribing mouse");
		return 1;
	}
	message msg;
	int r;
	int counter = 0;
	int flag = 0;
	short length_drawn;
	int length_sign ;
	if (length < 0)
		length_sign = 1;
	else
		length_sign = 0;

	unsigned long previous_deltay = 0;

	unsigned long out_buf = 0;
	unsigned long out_buf2 = 0;
	unsigned long packet[3];
	unsigned long equal_bits;
	unsigned long abs_value;
	unsigned long equal_bits1;

	do {
		if (set_kbc_mouse() == -1) //set kbc to read mouse
			return 1;

		issue_cmd_ms(ENABLE_STREAM);
		out_buf = mouse_int_handler();

	} while (out_buf != ACK);
	out_buf = mouse_int_handler();
	while (st != COMP) { /* You may want to use a different condition */
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

					if (counter == 0) {

						if (out_buf2 & BIT(3)) {

							packet[0] = out_buf2;

							counter++;

						} else
							continue;
					} else if (counter == 1) {

						packet[1] = out_buf2;
						counter++;
					} else if (counter == 2) {

						packet[2] = out_buf2;
						counter = 0;

						print_packet(3, packet);
						flag++;

						if (flag != 1)
						{

						equal_bits = packet[0];
						equal_bits1 = packet[0];
						equal_bits1 &= BIT(4);
						equal_bits &= BIT(5);
						equal_bits = equal_bits>>5;
						equal_bits1 = equal_bits1 >> 4;
						printf("%d,   %d\n", equal_bits, equal_bits1);
						if(equal_bits != 0)
							abs_value = compl2(packet[2]);
						else abs_value = packet[2];
						printf("%d\n",length_sign );

						if(equal_bits  == length_sign && packet[1] != 0 && packet[2] != 0 && (equal_bits == equal_bits1) )
						{
							length_drawn += abs_value;


						}else
						{
							length_drawn = 0;
							abs_value = 0;



						}

						if (packet[0] & BIT(1)) {
							tipo = RDOW;
							check_hor_line(&tipo,&st);
							printf("passou aqui\n");
							//roda dfa
						} else {
							tipo = RUP;
							check_hor_line(&tipo,&st);
							//roda DFA
						}
						if ((is_vert(abs(length),length_drawn) != 0))  {

							tipo = TOLERANCE;

							check_hor_line(&tipo,&st);

							//roda dfa;
						} else if (is_vert(length,length_drawn) == 0) {
							//printf("sinais iguais");
							tipo = VERT_LINE;
							check_hor_line(&tipo,&st);
							// roda dfa;
						}


					}}


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
	{
		printf("out\n");
		return 0;
	}
	return 0;
}

/*int is_vert(short length,unsigned long byte2)
{
	if (byte2 == length)
		return 0;
	else return 1;
}*/
