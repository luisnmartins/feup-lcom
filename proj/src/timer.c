#include "i8254.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

unsigned int contador=0;
unsigned int hook_id = T0_IRQSET;

int timer_set_square(unsigned long timer, unsigned long freq) {

	unsigned long final;
	unsigned long conf;
	unsigned char div_lsb, div_msb;
	unsigned char timer_select, control_4first;
	if (timer_get_conf(timer, &conf) != 0) {
		return 1;
	}
	unsigned long div;
	div = TIMER_FREQ / freq;
	div_lsb = div;
	div_msb = div >> 8;
	final = conf & COPY_4LAST;
	if (timer == 0) {
		control_4first = COUNTER0_LSBMSB_CWORD;
		timer_select = TIMER_0;
	} else if (timer == 1) {
		control_4first = COUNTER1_LSBMSB_CWORD;
		timer_select = TIMER_1;

	} else if (timer == 2) {
		control_4first = COUNTER2_LSBMSB_CWORD;
		timer_select = TIMER_2;
	}

	final &= control_4first;
	if (sys_outb(TIMER_CTRL, final) != OK) {
		printf("Can't pass the control word to the TIMER CONTROL");
		return 1;
	}
	if (sys_outb(timer_select, div_lsb) != OK
			|| sys_outb(timer_select, div_msb) != OK) {
		printf("Can't pass the config to the TIMER");
		return 1;
	}

	printf("Time set with success!!\n");
	return 0;

	return 1;

}

int timer_subscribe_int() {

	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id) != OK) {
		printf("Can't send and define the policy");
		return -1;
	}

	if (sys_irqenable(&hook_id) != OK) {
		printf("Can't enable the subscription");
		return -1;
	}

	return BIT(T0_IRQSET);

}

int timer_unsubscribe_int() {

	if (sys_irqdisable(&hook_id) != OK) {
		printf("Error executing sys_irqdisable");
		return 1;
	}
	if (sys_irqrmpolicy(&hook_id) != OK) {
		printf(
				"Error executing sys_irqmpolicy - failure unsubscribing the previous subscription of the interrupt");
		return 1;
	}


	hook_id = T0_IRQSET;
	return 0;

}

void timer_int_handler(unsigned short *counter) {

	(*counter)++;

}

int timer_get_conf(unsigned long timer, unsigned char *st) {

	unsigned long read_info;
	unsigned char rbc_count, timer_select;


	if (timer == 0) {
		rbc_count = RBC_COUNT0;
		timer_select = TIMER_0;
	} else if (timer == 1) {
		rbc_count = RBC_COUNT1;
		timer_select = TIMER_1;
	} else if (timer == 2) {
		rbc_count = RBC_COUNT2;
		timer_select = TIMER_2;
	}

	printf("word : 0x%x\n", rbc_count);
	if (sys_outb(TIMER_CTRL, rbc_count) != 0) {
		printf("Can't pass the control word to the TIMER CONTROL");
		return 1;
	}
	if (sys_inb(timer_select, &read_info) != 0) {
		printf("Can't get the configuration of TIMER");
		return 1;
	}
	*st = (unsigned char) read_info;
	return 0;

}

int timer_display_conf(unsigned char conf) {

	int bcd = 0, null = 0, output = 0;
	unsigned char program_mode;

	printf("configuration: 0x%x\n", conf);
	if (conf & TIMER_BCD) {
		bcd = 1;
	}
	if (conf & BIT(6)) {
		null = 1;
	}
	if (conf & BIT(7)) {
		output = 1;
	}
	printf("BCD = %d\n", bcd);
	printf("Null Count = %d\n", null);
	printf("Output = %d\n", output);
	program_mode = conf >> 1;
	program_mode &= COPY_3LAST;
	printf("PROGRAM MODE: ");
	switch (program_mode) {
	case 0: {
		printf("INTERRUPT ON TERMINAL COUNT\n");
		break;
	}
	case 1: {
		printf("HARDWARE RETRIGGERABLE ONE-SHOT\n");
		break;
	}
	case 2: {
		printf("RATE GENERATOR\n");
		break;
	}
	case 3: {
		printf("SQUARE WAVE MODE\n");
		break;
	}
	case 4: {
		printf("SOFTWARE TRIGGERED STROBE\n");
		break;
	}
	case 5: {
		printf("HARDWARE TRIGGERED STROBE (RETRIGGERABLE)\n");
		break;
	}
	case 6: {
		printf("RATE GENERATOR\n");
		break;
	}
	case 7: {
		printf("SQUARE WAVE MODE\n");
		break;
	}
		defalut: {
			printf("No mode available\n");
			break;
		}
	}

	if (conf & TIMER_LSB_MSB) {
		printf("Type of Access = LSB followed by MSB\n");
		return 0;
	} else if (conf & TIMER_MSB) {
		printf("Type of Access = MSB\n");
		return 0;
	} else if (conf & TIMER_LSB) {
		printf("Type of Access = LSB\n");
		return 0;
	}

	return 1;

}

int timer_test_square(unsigned long freq) {

	if (freq <= 0) {
		printf("Invalid Frequency\n");
		return 1;
	}
	if (timer_set_square(TIMER_SEL0, freq) == 0) {

		return 0;
	} else
		return 1;
}

int timer_test_int(unsigned long time) {
	int ipc_status, irq_set = timer_subscribe_int();
	message msg;
	int r;
	if (time <= 0) {
		printf("Time not valid!");
		return 1;
	}
	while (contador <= (time * 60)) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */

					if (contador % 60 == 0 && contador >= 60) {

						printf("\nMessage on %d seconds", contador / 60);

					}
					timer_int_handler(&contador);

				}
				break;
			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}

	}

	if (timer_unsubscribe_int() != 0) {
		return 1;
	} else {
		printf("\nUnsubscribed");
		return 0;
	}

}
int timer_test_config(unsigned long timer) {

	if (timer != 0 && timer != 1 && timer != 2) {
		printf("Timer not valid. Please Try Again!!\n");
		return 1;
	}
	unsigned char var;
	if (timer_get_conf(timer, &var) == 0) {
		if (timer_display_conf(var) == 0)
			return 0;

	}
	return 1;
}
