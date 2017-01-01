#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include "constants.h"


/** @defgroup keyboard keyboard
 * @{
 *
 * Functions for using the keyboard
 */


/**
 * @brief subscribes and enables the keyboard interrupts
 * */
int keyboard_subscribe_int();
/**
 * @brief unsubscribes the keyboard interrupts
 * */
int keyboard_unsubscribe_int();
/**
 * @brief reads and return the output buffer of the keyboard
 * @return the output buffer of the keyboard,useful to check keys scancodes (assembly version is being used)
 *
 * */
unsigned long keyboard_int_handler();
/**
 * @brief checks if outbuf is of the E0, if the scan code of the key is of 2 bytes
 * @param out_buf to check
 * @param out_buf2 to save space for the 2 bytes
 * @return 1 if the scan code is of 2 bytes and the it hasn been handled,0 otherwise puting the full scan code in out_buff
 * */
int receive_buffer(unsigned long *out_buf, unsigned long *out_buf2);

/**
 * @brief issues a cmd to the keyboard buffer
 * @param cmd argument or command that is being written
 * @return 1 if it failed,0 otherwise
 * */
int issue_cmd_kbd(unsigned long cmd);

//void print_code(unsigned long *out_buf);
//void print_led(unsigned long leds_p, unsigned long flag);




#endif /* __KEYBOARD_H */

