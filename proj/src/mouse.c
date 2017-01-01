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

	mhook_id = 12;

	return 0;

}

unsigned long mouse_int_handler() {

	unsigned long data;
	unsigned int n = 0;
	unsigned long status;
	while (n <= 5) {
		printf("LER DO MOUSE\n");
		sys_inb(STATUS_REG, &status);
		if ((status & OBF)) {
			sys_inb(MS_OUT_BUF, &data);

			return data;

		}
		n++;

	}
	//printf("Error reading from out buffer\n");
	return -1;

}

int issue_cmd_ms(unsigned long cmd) {

	unsigned long stat = 0;
	unsigned int n = 0;
	while (n <= 5) {
		if (set_kbc_mouse() == -1) //set kbc to read mouse
					return -1;
		sys_inb(STATUS_REG, &stat); /* assuming it returns OK */
		/* loop while 8042 input buffer is not empty */

		if ((stat & IBF) == 0) {
			sys_outb(MS_OUT_BUF, cmd);
			sys_outb(KBC_CMD_REG, cmd); /* no args command */
			return 0;
		}

		//tickdelay(micros_to_ticks(DELAY_US));
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

		//tickdelay(micros_to_ticks(DELAY_US));
		n++;
	}
	printf("Error trying to write in the input buffer\n");
	return -1;

}


int get_packets(unsigned short *counter, unsigned long *packet_mouse, unsigned long *out_buf_mouse)
{

	printf("GET PACKETS\n");
	(*out_buf_mouse) = mouse_int_handler();
	if((*out_buf_mouse) == -1)
	{
			(*counter) = 0;
			return 1;
	}
	if ((*counter) == 0)
	{
		if ((*out_buf_mouse) & VERIFY_PACKET)
		{

			packet_mouse[0] = (*out_buf_mouse);

		} else return 1;

	}
	else if ((*counter) == 1)
	{

		packet_mouse[1] = (*out_buf_mouse);

	}
	else if ((*counter) == 2)
	{
		packet_mouse[2] = (*out_buf_mouse);
		printf("ACABOU LEITURA\n");
		(*counter) = 0;
		return 0;
	}
	(*counter)++;
	printf("COUNTER MOUSE: %d\n", (*counter));
	return 1;




}

int set_stream_mode()
{
	int send_ct=0;
	unsigned long out_buf = 0;

	do {

			issue_cmd_ms(DISABLE_STREAM);
			out_buf = mouse_int_handler();
			send_ct++;

		} while ((out_buf != ACK) && send_ct<5);
		if(send_ct>= 5)
		{
			printf("Error sending Disable command");
			return 1;
		}
		send_ct=0;
		do {


			issue_cmd_ms(ENABLE_STREAM);
			out_buf = mouse_int_handler();
			send_ct++;

		} while ((out_buf != ACK) && send_ct<5);

		if(send_ct>= 5)
		{
			printf("Error sending Enable command");
			return 1;
		}
}


int disable_stream_mode_end()
{
		int send_ct=0;
		unsigned long out_buf = 0;
		do {

			issue_cmd_ms(DISABLE_STREAM);
			out_buf = mouse_int_handler();
			send_ct++;

		} while ((out_buf != ACK) && send_ct<5);
		if(send_ct>= 5)
		{
			printf("Error sending Disable command");
			return 1;
		}

		printf("Stream Disabled\n");

		send_ct=0;

		do {

			issue_cmd_ms(STREAM_MODE);
			out_buf = mouse_int_handler();
			send_ct++;

		} while (out_buf != ACK && send_ct<5);
		if(send_ct>= 5)
			{
				printf("Error sending set stream command");
				return 1;
			}

		printf("Stream mode set");

		out_buf = mouse_int_handler();
}


int print_packet(int size_array, unsigned long *array, long *x, long  *y, unsigned short *lb,unsigned short *rb) {
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
			(*lb) = flag;
		} else if (n == 2) {
			printf("MB=%d  ", flag);
		} else if (n == 1) {
			printf("RB=%d  ", flag);
			(*rb) = flag;
		}

	}
	if ((byte1 & SINAL_X) && (array[1] != 0)) {

		printf("X=-%03d  ", compl2(array[1]));
		(*x) = -compl2(array[1]);
	} else {
		printf("X=%04d  ", array[1]);
		(*x) = array[1];
	}

	if ((byte1 & SINAL_Y) && (array[2] != 0)) {
		printf("Y=-%03d   ", compl2(array[2]));
		(*y) = -compl2(array[2]);
	} else {
		printf("Y=%04d   ", array[2]);
		(*y) = array[2];
	}
	//byte1>>6;
	flag = 0;

	if (byte1 & X_OVF) {
		flag = 1;
		return 1;
	}

	printf("XOV=0x%x  ", flag);

	flag = 0;

	if (byte1 & Y_OVF) {
		flag = 1;
		return 1;

	}
	printf("YOV=0x%x\n", flag);
	return 0;

}

long compl2(long nr) {
	nr ^= 0xFF;
	nr++;
	return nr;

}






