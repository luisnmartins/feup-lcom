#include "i8254.h"
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

#define RBC_COUNT0 0xE2
#define RBC_COUNT1 0xE4
#define RBC_COUNT2 0xE8
#define COPY_4LAST 0x0F

unsigned int contador = 0;
unsigned int hook_id;


int timer_set_square(unsigned long timer, unsigned long freq) {

	unsigned long final;
	unsigned long conf;
	unsigned char div_lsb, div_msb;
	timer_get_conf(timer, &conf);
	unsigned long div;
	div = TIMER_FREQ / freq;
	div_lsb = div;
	div_msb = div >> 8;
	final = conf & COPY_4LAST;
	if (timer == 0)
	{
		final &= 0x3f;
		sys_outb(TIMER_CTRL, final);
		sys_outb(TIMER_0, div_lsb);
		sys_outb(TIMER_0, div_msb);
		printf("Time set with success!!\n");
		return 0;
	}
	else if (timer == 1)
	{
		final = final & 0x7f;
		sys_outb(TIMER_CTRL, final);
		sys_outb(TIMER_1, div_lsb);
		sys_outb(TIMER_1, div_msb);
		printf("Time set with success!!\n");
		return 0;

	}
	else if (timer == 2) {
		final = final & 0xbf;
		sys_outb(TIMER_CTRL, final);
		sys_outb(TIMER_2, div_lsb);
		sys_outb(TIMER_2, div_msb);
			printf("Time set with success!!\n");
			return 0;

	}

	return 1;

}

int timer_subscribe_int() {
	hook_id = 0;
	if (sys_irqsetpolicy(0, IRQ_REENABLE, &hook_id) < 0)
		return -1;
	else
		return hook_id;

}

int timer_unsubscribe_int() {
	sys_irqdisable(&hook_id);
	sys_irqrmpolicy(&hook_id);



}

void timer_int_handler() {

	contador++;


}

int timer_get_conf(unsigned long timer, unsigned char *st) {

	unsigned long read_info;
	if (timer == 0) {
		printf("palavra : 0x%x\n", RBC_COUNT0);
		if (sys_outb(TIMER_CTRL, RBC_COUNT0) == 0
				&& sys_inb(TIMER_0, &read_info) == 0)
			*st = (unsigned char) read_info;
		return 0;

	}
	if (timer == 1) {
		printf("palavra : 0x%x\n", RBC_COUNT1);
		if (sys_outb(TIMER_CTRL, RBC_COUNT1) == 0
				&& sys_inb(TIMER_1, &read_info) == 0)
			*st = (unsigned char) read_info;
		return 0;
	}
	if (timer == 2) {
		if (sys_outb(TIMER_CTRL, RBC_COUNT2) == 0
				&& sys_inb(TIMER_2, &read_info) == 0)
			*st = (unsigned char) read_info;
		return 0;
	}
	return 1;
}

int timer_display_conf(unsigned char conf) {

	int bcd = 0, null = 0, output = 0;

	printf("configuracao: 0x%x\n", conf);
	if (conf & BIT(0)) {
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
	if (conf & BIT(3)) {
		if (conf & BIT(2)) {
			if (conf & BIT(1)) {
				printf("Programmed Mode = SQUARE WAVE MODE\n");

			} else {
				printf("Programmed Mode = RATE GENERATOR\n");

			}
		} else {
			if (conf & BIT(1)) {
				printf(
						"Programmed Mode = HARDWARE TRIGGERED STROBE (RETRIGGERABLE)\n");

			} else {
				printf("Programmed Mode = SOFTWARE TRIGGERED STROBE\n");

			}
		}
	} else {
		if (conf & BIT(2)) {
			if (conf & BIT(1)) {
				printf("Programmed Mode = SQUARE WAVE MODE\n");

			} else {
				printf("Programmed Mode = RATE GENERATOR\n");

			}
		} else {
			if (conf & BIT(1)) {
				printf("Programmed Mode = HARDWARE RETRIGGERABLE ONE-SHOT\n");
			} else {
				printf("Programmed Mode = INTERRUPT ON TERMINAL COUNT\n");
			}
		}
	}

	if (conf & BIT(5)) {
		if (conf & BIT(4)) {
			printf("Type of Access = LSB followed by MSB\n");
			return 0;
		} else {
			printf("Type of Access = MSB\n");
			return 0;
		}
	} else {
		if (conf & BIT(4)) {
			printf("Type of Access = LSB\n");
			return 0;
		} else
			return 1;
	}

}

int timer_test_square(unsigned long freq) {

	if (timer_set_square(0, freq) == 0)
		return 0;
	else
		return 1;
}

int timer_test_int(unsigned long time) {
	int ipc_status, irq_set;
	message msg;
	int r;

	while (time > contador/60)
	{ /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source))
			{
			case HARDWARE: /* hardware interrupt notification */
				irq_set = timer_subscribe_int();
				if (msg.NOTIFY_ARG & irq_set) { /* subscribed interrupt */
					sys_irqenable(&hook_id);

					if (contador % 60 == 0)
					{
						printf("Message");
					}
					timer_int_handler();

			}
			break;
			default:
			break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}

	}
	timer_unsubscribe_int();
return 0;

}
int timer_test_config(unsigned long timer) {

	unsigned char var;
	if (timer_get_conf(timer, &var) == 0) {
		if (timer_display_conf(var) == 0)
			return 0;

	}
	return 1;
}
