#ifndef __MOUSE_H
#define __MOUSE_H


#include "i8042.h"
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>



int mouse_subscribe_int();
int mouse_unsubscribe_int();
unsigned long mouse_int_handler();
int issue_cmd_ms(unsigned long cmd);
void print_packet(int size_array, unsigned long *array);
long compl2(long nr);
void print_conf_byte1(unsigned long *conf_byte);

//int vert_line(short size,unsigned long *array)

#endif /* __MOUSE_H */
