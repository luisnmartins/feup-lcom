#ifndef __MOUSE_H
#define __MOUSE_H


#include "constants.h"
#include <minix/sysutil.h>
#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>


/** @defgroup mouse mouse
 * @{
 *
 * Functions for using the mouse
 */

/**
 * @brief subscribes and enables the mouse interruts
 * @return the changed hook_id or -1 if it failed
 * */
int mouse_subscribe_int();
/**
 * @brief unsubscribes mouse interrupts
 * @return 1 if it failed,0 otherwise
 * */
int mouse_unsubscribe_int();
/**
 * @brief reads the out bufer of the mouse
 * @return the value of the buffer or -1 if it failed
 * */
unsigned long mouse_int_handler();
/**
 * @brief issues a command to the buffer of the mouse
 * @param cdm command or arguments issued
 * @return 0 if succeeds 1 otherwise
 * */
int issue_cmd_ms(unsigned long cmd);
/**
 *  @brief it reads and stores the packet of the mouse
 *  @param counter variable to know which element of the packet is being studied (a packet has 3)
 *  @param packet_mouse pointer to an array where the packets are stored
 *  @param out_buf_mouse a content to put on the packet
 *  @return 0 if the packet is complete, if packet_mouse has been filled, 1 otherwise
 * */
int get_packets(unsigned short *counter, unsigned long *packet_mouse, unsigned long *out_buf_mouse);
/**
 * @brief disables the stream mode of the mouse
 * */
int disable_stream_mode_end();
/**
 * @brief sets and enables the stream mode of the mouse
 * */
int set_stream_mode();
/**
 * @brief interprets and prints the contents of a mouse packet,and also store some of its values, like the movement in the x and y axis, the state of both mouse buttons(left and right)
 * @param size_array the size of the array packet (is always 3 )
 * @param array pointer to the first element of the packet array
 * @param x variable where is going to be stored the movement in the x axis of the mouse
 * @param y variable where is going to be stored the movement in the y axis of the mouse
 * @param lb variable where the state of the left mouse button is saved
 * @param rb variable where the state of the right mouse button is saved
 * @return 1 overflow is verified in any of the axiss
 * */
int print_packet(int size_array, unsigned long *array, long *x, long  *y, unsigned short *lb,unsigned short *rb) ;
/**
 * @brief gets a negative number in the complement for 2 mode a returns the absolute value of it
 * @brief nr the negative number in compl2
 * @return the absolute value
 * */
long compl2(long nr);

#endif /* __MOUSE_H */
