#include <limits.h>
#include <string.h>
#include <errno.h>
#include "video_gr.h"
#include "keyboard.h"
#include "graphics.h"
#include "timer.h"
#include "constants.h"
#include "man_events.h"
#include <time.h>
//#include "pixmap.h"



int main()
{
	srand(time(NULL));
	sef_startup();

	start_mode();


	int ipc_status;
	int irq_timer = timer_subscribe_int();
	int irq_kb = keyboard_subscribe_int();
	//int irq_mouse = mouse_subscribre_int();
	message msg;
	int r;
	unsigned long out_buf = 0, out_buf2 = 0;
	unsigned short counter=0;
	unsigned short flag_outbuf=0;
	unsigned short flag_end=0;

	while (1) { /* You may want to use a different condition */
					/* Get a request message. */

					if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
						printf("driver_receive failed with: %d", r);
						continue;
					}
					if (is_ipc_notify(ipc_status)) { /* received notification */
						switch (_ENDPOINT_P(msg.m_source)) {
						case HARDWARE: /* hardware interrupt notification */
							if (msg.NOTIFY_ARG & irq_timer)
							{
								printf("interrupt timer\n");
								timer_int_handler(&counter);
								timer_event_handler(counter);

							}
							if(msg.NOTIFY_ARG & irq_kb)
							{
								out_buf = keyboard_int_handler();
								if(out_buf == OUT_BUF_2BYTES)
								{
									out_buf2 = out_buf<<8;
									flag_outbuf = 1;
									continue;
								}
								if(flag_outbuf == 1)
								{
									out_buf |= out_buf2;
									out_buf2 = 0;
								}
								if(keyboard_event_handler(out_buf) == 1)
								{
									printf("Terminou\n");
									flag_end = 1;
									break;
								}

							}
							break;
						}
						if(flag_end==1)
							break;
					}
				}



				if (keyboard_unsubscribe_int() != 0) {
					return 1;
				}

				out_buf = keyboard_int_handler();

				if (timer_unsubscribe_int() != 0) {
									return 1;
				}

	vg_exit();

	return 0;
}
