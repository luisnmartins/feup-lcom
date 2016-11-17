#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>

int keyboard_subscribe_int();
int keyboard_unsubscribe_int();
unsigned long keyboard_test_int();
int issue_cmd_kbd(unsigned long cmd);
void print_code(unsigned long *out_buf);
void print_led(unsigned long leds_p, unsigned long flag);




#endif /* __KEYBOARD_H */

