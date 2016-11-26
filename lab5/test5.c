#include "timer.h"
#include "keyboard.h"
#include "i8042.h"
#include "i8254.h"
#include "timer.h"
#include "lmlib.h"
#include "vbe.h"
#include "video_gr.h"
#include  <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <inttypes.h>
//#include "pixmap.h" // defines  pic1, pic2, etc

static unsigned int counter = 0;
void *test_init(unsigned short mode, unsigned short delay) {

	int ipc_status, irq_set = timer_subscribe_int();
	message msg;
	int a;
	if (delay <= 0) {
		printf("Time not valid!");
		return NULL;
	}


	vbe_mode_info_t v1;
	vbe_get_mode_info(0x105,&v1);

	void *result = vg_init(mode);
	while (counter <= (delay * 60)) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((a = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", a);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) {
					timer_int_handler(&counter);

				}
			}
		}
	}

	if (timer_unsubscribe_int() != 0) {
		return NULL;
	} else {
		if (vg_exit() != 0)

			return NULL;
		printf("Physical Adress: 0x%02x",v1.PhysBasePtr);
		return result;

	}
}

int test_square(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color) {


	vbe_mode_info_t v1;
	vbe_get_mode_info(0x105,&v1);

	unsigned hres = v1.XResolution;
	unsigned vres = v1.YResolution;
	unsigned bitspixel = v1.BitsPerPixel;


	if(x+size >= hres || y+size >= vres)
	{
		printf("Not valid\n");
		return 1;
	}



	int ipc_status, irq_set = keyboard_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0;
	int i, a;

	vg_init(0x105);

	for (i = 0; i < size; i++) {
		for (a = 0; a < size; a++) {
			paintPixel(x + a, y + i, color);
		}

	}
	while (out_buf != ESC_CODE) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) {
					out_buf = keyboard_int_handler();
				}
			}
		}
	}
	if (keyboard_unsubscribe_int() != 0) {
		return 1;
	}
	out_buf = keyboard_int_handler();

	if (vg_exit() != 0)
		return 1;

	return 0;

}

int test_line(unsigned short xi, unsigned short yi, unsigned short xf,
		unsigned short yf, unsigned long color) {


	vbe_mode_info_t v1;
	vbe_get_mode_info(0x105,&v1);

	unsigned hres = v1.XResolution;
	unsigned vres = v1.YResolution;
	unsigned bitspixel = v1.BitsPerPixel;


	if(xi >= hres || xf>=hres || yf>=vres || yi >= vres)
	{
		printf("Not valid\n");
		return 1;
	}






	int ipc_status, irq_set = keyboard_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0;
	int i, a;

	vg_init(0x105);

	make_line(xi, xf, yi, yf, color);

	while (out_buf != ESC_CODE) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) {
					out_buf = keyboard_int_handler();
				}
			}
		}
	}
	if (keyboard_unsubscribe_int() != 0) {
		return 1;
	}
	out_buf = keyboard_int_handler();

	if (vg_exit() != 0)
		return 1;

	return 0;

}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {

	int ipc_status, irq_set = keyboard_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0;
	int b, a;
	int largura, altura;

	vg_init(0x105);

	paint_xpm(xi, yi, xpm);

	while (out_buf != ESC_CODE) { /* You may want to use a different condition */
		/* Get a request message. */

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) {
					out_buf = keyboard_int_handler();
				}
			}
		}
	}
	if (keyboard_unsubscribe_int() != 0) {
		return 1;
	}
	out_buf = keyboard_int_handler();

	if (vg_exit() != 0)
		return 1;

	return 0;

}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	vbe_mode_info_t v1;
	vbe_get_mode_info(0x105,&v1);

	unsigned hres = v1.XResolution;
	unsigned vres = v1.YResolution;
	unsigned bitspixel = v1.BitsPerPixel;


	if(abs(xi) >= hres || abs(yi) >= vres)
	{
		printf("Not valid\n");
		return 1;
	}
	else if(hor == 0)
	{
		if(yi+delta >= vres)
		{
			printf("Not valid\n");
				return 1;}
	}
	else
	{
		if(xi+delta >= hres)
		{		printf("Not valid\n");
						return 1;
		}
	}



	int ipc_status, irq_set = keyboard_subscribe_int();
	int irq_set2 = timer_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0;
	int i, a;
	void *video_mem_val = vg_init(0x105);
	int flag=0;
	unsigned short xant, yant;

	float nr_int_total = (float)delta/(time * 60);
	float v= nr_int_total;
	int contador=0;

	while (out_buf != ESC_CODE) {

			if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
			}
			if (is_ipc_notify(ipc_status)) { /* received notification */
				switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE: /* hardware interrupt notification */

					if (msg.NOTIFY_ARG & irq_set)
					{
						out_buf = keyboard_int_handler();

					}

				if (msg.NOTIFY_ARG & irq_set2) {

					if(flag == 0)
						{
							if(contador> time*60)
								flag = 1;

							if (hor == 0)
									yi += v;
							else
									xi += v;

							contador++;


							paint_black_xpm(xant, yant, xpm);

							if (xi >= hres || yi >= vres)
							{
								flag= 1;
								continue;
							}
							if(paint_xpm(xi, yi, xpm) == 1)
								break;
							else
							{
								xant = xi;
								yant = yi;
							}
						}
					}
				}
			}
	}


	if (timer_unsubscribe_int() != 0) {
		return 1;
	}
	if (keyboard_unsubscribe_int() != 0) {
		return 1;
	}
	out_buf = keyboard_int_handler();

	if (vg_exit() != 0)
		return 1;

	return 0;
}


int test_controller() {

	VbeInfoBlock conf;

	vbe_read_block_info(&conf);

	printf ("VBE controller information\n");



	if(conf.Capabilities[0] && BIT(0) == 0)
	{
		printf("DAC is fixed width,with 6 bits per primary color\n");
	}
	else
	{
		printf("DAC width is switchable to 8 bits per primary color\n");
	}
	if(conf.Capabilities[0] && BIT(1) == 0)
	{
		printf("Controller is VGA compatible\n");
	}
	else
	{
		printf("Controller is not VGA compatible\n");
	}
	if(conf.Capabilities[0] && BIT(2) == 0)
	{
		printf("Normal RAMDAC operation\n");

	}else
	{
		printf("When programming large blocks of information to the RAMDAC,use the blank bit in Function 09h\n");
	}

	printf("VBE version: %u\n",conf.VbeVersion);
	printf("Total memory:%d KB\n" ,conf.TotalMemory);


	short *modes = conf.VideoModePtr;
	int aux = (int)modes;
	int most_significant = aux >> 16  & (0xF0000);
	aux = (int) modes;
	int least_significant = aux && 0x0000FFFF;

	aux = most_significant + least_significant;

	modes =(short*) aux;
	printf("Modes: ");
	while(*modes != -1)
	{
		printf("%u\t",*modes);
	}


	return 0;

}
