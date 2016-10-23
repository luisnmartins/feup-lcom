#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

int keyboard_subscribe_int();
int keyboard_unsubscribe_int();
int keyboard_test_int();
void print_code(unsigned long *out_buf);




#endif /* __KEYBOARD_H */
