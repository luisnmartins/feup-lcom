#ifndef __MAN_EVENTS_H
#define __MAN_EVENTS_H


#include "graphics.h"




int keyboard_event_handler(unsigned long out_buf);
void timer_event_handler(unsigned short counter);
void mouse_event_handler(unsigned long *packet_mouse);
void game_start(int mode);










#endif /* __MAN_EVENTS_H */
