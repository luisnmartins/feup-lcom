#include "i8042.h"
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "video_gr.h"
#include "keyboard.h"
#include "graphics.h"

//#include "pixmap.h"

int main()
{
	srand(time(NULL));
	sef_startup();

	start_mode();


	int ipc_status;
	int irq_set = timer_subscribe_int();
	int irq_set2 = keyboard_subscribe_int();
	message msg;
	int r;
	unsigned long out_buf = 0;
			//out_buf = keyboard_int_handler();

			while (1) { /* You may want to use a different condition */
					/* Get a request message. */

					if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
						printf("driver_receive failed with: %d", r);
						continue;
					}
					if (is_ipc_notify(ipc_status)) { /* received notification */
						switch (_ENDPOINT_P(msg.m_source)) {
						case HARDWARE: /* hardware interrupt notification */
							printf("a\n");
							if (msg.NOTIFY_ARG & irq_set2) {
								printf("b\n");
								out_buf = keyboard_int_handler();
								//paint_xpm(200, 500, maca);
							}
						}
					}
				}
				if (keyboard_unsubscribe_int() != 0) {
					return 1;
				}

				out_buf = keyboard_int_handler();


	vg_exit();

	return 0;
}
