#include "mouse.h"

unsigned int mhook_id = 12;

typedef enum {
	INIT, DRAW, COMP
} state_t;
typedef enum {
	RDOW, RUP, TOLERANCE, VERT_LINE
} ev_type_t;



int mouse_subscribe_int() {
	int temp = mhook_id;

	if (sys_irqsetpolicy(MS_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mhook_id)
			!= OK) {
		printf("Can't send and define the policy");
		return -1;
	}

	if (sys_irqenable(&mhook_id) != OK) {
		printf("Can't enable the subscription");
		return -1;
	}

	return BIT(temp);
}

int mouse_unsubscribe_int() {

	if (sys_irqdisable(&mhook_id) != OK) {
		printf("Error executing sys_irqdisable");
		return 1;
	}
	if (sys_irqrmpolicy(&mhook_id) != OK) {
		printf(
				"Error executing sys_irqmpolicy - failure unsubscribing the previous subscription of the interrupt");
		return 1;
	}

	return 0;

}

unsigned long mouse_int_handler() {

	unsigned long data;
	unsigned int n = 0;
	unsigned long status;
	while (n <= 5) {
		sys_inb(STATUS_REG, &status);
		if ((status & OBF)) {
			sys_inb(MS_OUT_BUF, &data);

			return data;

		}
		tickdelay(micros_to_ticks(DELAY_US));
		n++;

	}

	return 1;

}

int issue_cmd_ms(unsigned long cmd) {

	unsigned long stat = 0;
	unsigned int n = 0;
	while (n <= 5) {
		sys_inb(STATUS_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 input buffer is not empty */
		if ((stat & IBF) == 0) {
			sys_outb(MS_OUT_BUF, cmd);
			//sys_outb(KBC_CMD_REG, cmd); /* no args command */
			return 0;
		}

		tickdelay(micros_to_ticks(DELAY_US));
		n++;
	}
	printf("Error trying to write in the input buffer\n");
	return -1;

}

int set_kbc_mouse() {
	unsigned long stat = 0;
	unsigned int n = 0;
	while (n <= 5) {

		sys_inb(STATUS_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 input buffer is not empty */
		if ((stat & IBF) == 0) {
			sys_outb(STATUS_REG, WRITE_B_MOUSE);
			//sys_outb(KBC_CMD_REG, cmd); /* no args command */
			return 0;
		}

		tickdelay(micros_to_ticks(DELAY_US));
		n++;
	}
	printf("Error trying to write in the input buffer\n");
	return -1;

}

void print_packet(int size_array, unsigned long *array) {
	int i = 0;
	int flag = 0;
	unsigned long byte1 = array[0];
	for (i; i < size_array; i++) {
		printf("B%d=0x%02x", i, array[i]);
		printf("  ");
	}
	int n = 0;
	for (n; n < 3; n++) {
		if (byte1 & BIT(n))
			flag = 1;
		else
			flag = 0;
		if (n == 0) {
			printf("LB=%d  ", flag);
		} else if (n == 2) {
			printf("MB=%d  ", flag);
		} else if (n == 1) {
			printf("RB=%d  ", flag);
		}

	}
	if ((byte1 & BIT(4)) && (array[1] != 0)) {

		printf("X=-%03d  ", compl2(array[1]));
	} else {
		printf("X=%04d  ", array[1]);
	}

	if ((byte1 & BIT(5)) && (array[2] != 0)) {
		printf("Y=-%03d   ", compl2(array[2]));
	} else {
		printf("Y=%04d   ", array[2]);
	}
	//byte1>>6;
	flag = 0;

	if (byte1 & BIT(6)) {
		flag = 1;
	}

	printf("XOV=0x%x  ", flag);

	flag = 0;

	if (byte1 & BIT(7)) {
		flag = 1;

	}
	printf("YOV=0x%x\n", flag);

}

long compl2(long nr) {
	nr ^= 0xFF;
	nr++;
	return nr;

}

void print_conf_byte1(unsigned long *conf_byte) {
	if (*conf_byte & BIT(0)) {
		printf("Right button is currently pressed\n");
	} else {
		printf("Right button is currently released\n");
	}
	if (*conf_byte & BIT(1)) {
		printf("Middle button is currently pressed\n");
	} else {
		printf("Middle button is currently released\n");
	}

	if (*conf_byte & BIT(2)) {
		printf("Left button is currently pressed\n");
	} else {
		printf("Left button is currently released\n");
	}
	if (*conf_byte & BIT(4)) {
		printf("Scaling= 2:1\n");
	} else {
		printf("Scaling= 1:1\n");
	}
	if (*conf_byte & BIT(5)) {
		printf("Data Reporting= Enabled\n");
	} else {
		printf("Data Reporting= Disabled\n");
	}
	if (*conf_byte & BIT(6)) {
		printf("Remote (polled) mode\n");
	} else {
		printf("Stream Mode\n");
	}

}

void check_hor_line(ev_type_t *evt,state_t *st) {
	//static state_t st = INIT; // initial state; keep state

	long y0;
	long yfinal;




	switch (*st) {
	case INIT:
		printf("entrouinit\n");
		if (*evt == RDOW)
			*st = DRAW;
		break;
	case DRAW:
		printf("entroudraw\n");
		if (*evt == TOLERANCE) {
			*st = DRAW;
		}else if (*evt == VERT_LINE)
		{
			*st = COMP;
		}
			// need to check if events VERT_LINE or HOR_TOLERANCE
	 else if (*evt == RUP)
		*st = INIT;
	break;
default:
	break;
	}
}
int is_vert(short length,short length_drawn)
{
	if(length_drawn >= length)
	{
		return 0;
	}else return 1;


}

/*int vert_line(short size,unsigned long *array)
{
	return 0;
}*/
