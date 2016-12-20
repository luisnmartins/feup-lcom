#ifndef __MOUSE_H
#define __MOUSE_H


#include "constants.h"
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>



int mouse_subscribe_int();
int mouse_unsubscribe_int();
unsigned long mouse_int_handler();
int issue_cmd_ms(unsigned long cmd);
int get_packets(unsigned short *counter, unsigned long *packet_mouse, unsigned long out_buf_mouse);
int disable_stream_mode_end();
int set_stream_mode();
int print_packet(int size_array, unsigned long *array, long *x, long  *y, unsigned short *lb) ;
long compl2(long nr);
void print_conf_byte1(unsigned long *conf_byte);
int is_vert(short length,short length_drawn);
//int vert_line(short size,unsigned long *array)

#endif /* __MOUSE_H */
