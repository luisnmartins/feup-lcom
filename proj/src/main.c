#include "i8042.h"
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "video_gr.h"
#include "keyboard.h"
#include "graphics.h"
#include "bitmap.h"
//#include "pixmap.h"

int main()
{
	sef_startup();

	start_mode();
	Bitmap* segmento = loadBitmap("/home/proj/res/images/segmento.bmp");
	drawBitmap(segmento,200,200,ALIGN_LEFT);

	int pos=0;

	//paint_xpm(200, 150, square_right);
	pos = paint_snake_hor(200, 200, 5, 1);
	move_snake(pos, 200, 1, 200);
	paint_xpm(200, 100, snapchat);
	paint_xpm(200, 300, maca);

	printf("aqui\n");


	int ipc_status;
			int irq_set2 = keyboard_subscribe_int();

			message msg;
			int r;
			unsigned long out_buf = 0;
			//out_buf = keyboard_int_handler();

			while (out_buf != ESC_CODE) { /* You may want to use a different condition */
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
