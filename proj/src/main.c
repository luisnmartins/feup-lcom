#include <limits.h>
#include <string.h>
#include <errno.h>
#include "constants.h"
#include "video_gr.h"
#include "keyboard.h"
#include "graphics.h"
#include "timer.h"
#include "mouse.h"
#include "man_events.h"
#include <time.h>
//#include "pixmap.h"



int main()
{
	srand(time(NULL));
	sef_startup();
	sys_enable_iop(SELF);


	start_mode();
	start_variables_menu();


	int ipc_status;
	int irq_timer = timer_subscribe_int();
	int irq_kb = keyboard_subscribe_int();
	int irq_mouse = mouse_subscribe_int();
	if (irq_mouse == -1) {
			printf("Fail subscribing mouse");
			return 1;
		}
	if(set_stream_mode() == 1)
		return 1;
	message msg;
	int r;
	unsigned long out_buf = 0, out_buf2 = 0;
	unsigned long out_buf_mouse =0;
	unsigned short counter=0;
	unsigned short flag_outbuf=0;
	unsigned short flag_end=0;
	unsigned long packet_mouse[3];
	unsigned short counter_mouse =0;
	unsigned long status;

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
								if(timer_event_handler(counter) == 1)
								{
									flag_end =1 ;
									break;
								}


							}
							if(msg.NOTIFY_ARG & irq_kb)
							{

								if(receive_buffer(&out_buf, &out_buf2)==0)
								{

									if(keyboard_event_handler(out_buf) == 1)
									{
											printf("Terminou\n");
											flag_end = 1;
											break;
									}
								}
							}
							if (msg.NOTIFY_ARG & irq_mouse)
							{

								if(get_packets(&counter_mouse, packet_mouse, &out_buf_mouse) == 0)

									{
									mouse_event_handler(packet_mouse);
									//draw_screen();
									}
							}
							break;
						}

						}

						if(flag_end==1)
							break;
					}


			if(mouse_unsubscribe_int() != 0)
			{
				return 1;
			}
			out_buf = mouse_int_handler();

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
