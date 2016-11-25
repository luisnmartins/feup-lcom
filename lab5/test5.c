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

		return result;

	}
}

int test_square(unsigned short x, unsigned short y, unsigned short size,
		unsigned long color) {

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

	int ipc_status, irq_set = keyboard_subscribe_int();
	int irq_set2 = timer_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0;
	int i, a;
	void *video_mem_val = vg_init(0x105);


	float nr_int_total = delta/(time * 60);
	float v= nr_int_total;
	float nr_int_atual = 0;

	while (out_buf != ESC_CODE) {

		if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */

				if (msg.NOTIFY_ARG & irq_set) {
					out_buf = keyboard_int_handler();

						break;
				}

				if (msg.NOTIFY_ARG & irq_set2) {

					if(nr_int_atual > nr_int_total)
						break;

					if (hor == 0)
							yi += v;
						else
							xi += v;

					nr_int_atual++;

					memset(video_mem_val, 0, H_RES * V_RES * BITS_PER_PIXEL / 8);
					paint_xpm(xi, yi, xpm);

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

	/* To be completed */

}
