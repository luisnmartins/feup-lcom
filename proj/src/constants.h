#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include "i8254.h"

//-------------- GRAPHICS

//#define H_RES             1280
//#define V_RES		  1024
//#define BITS_PER_PIXEL	  16
//#define SCREEN_SIZE  H_RES*V_RES*BITS_PER_PIXEL/8
#define HORIZONTAL_PAINT 0
#define VERTICAL_PAINT 1


// -------------- KEYB0ARD

#define KB_IRQ 1    //Keyboard IRQ

#define STATUS_REG 0x64
#define KBD_OUT_BUF 0x60

#define OBF BIT(0)
#define IBF BIT(1)

#define ESC_CODE 0x81
#define UP_ARROW 0xE048
#define DOWN_ARROW 0xE050
#define LEFT_ARROW 0xE04B
#define RIGHT_ARROW 0xE04D
#define A_KEY 0x9E
#define W_KEY 0x91
#define S_KEY 0x9F
#define D_KEY 0xA0
#define ENTER  0x001C
#define CTRL_MAKE 0x1D
#define CTRL_BREAK 0x9D
#define SHIFT_MAKE 0x36
#define SHIFT_BREAK 0xB6


#define NBIT(n) (0xFF^BIT(n))

#define OUT_BUF_2BYTES 0xE0
#define DELAY_US 20000

#define PAR_ERR BIT(7)
#define TO_ERR BIT(6)


#define ON_OFF_LEDS 0xED
#define KBC_CMD_REG 0x64
#define ACK 0xFA
#define RESEND 0xFE
#define ERROR 0xFC


// ------- MOUSE

#define MS_OUT_BUF 0x60		//mouse out_buf
#define MS_IRQ 12   //Mouse IRQ
#define AUX BIT(5) //out_buf is mouse information
#define WRITE_B_MOUSE 0xD4 //commands the KBC to forward its argument to the mouse
#define STREAM_MODE 0xEA //set mouse with stream mode
#define DISABLE_STREAM 0xF5
#define ENABLE_STREAM 0xF4
#define NACK 0xFE
#define STATUS_REQUEST 0xE9
#define CONF_BYTE2_ZEROS BIT(7) & BIT(6) & BIT(5) & BIT(4) & BIT(3) & BIT(2)
#define READ_KBC 0x20


#define VERIFY_PACKET BIT(3)
#define VERIFY_EMPTY_BUF BIT(5)
#define CONF_FIRST_BYTE  BIT(7) & BIT(3)
#define RIGHT_BUTTON BIT(1)
#define MIDDLE_BUTTON BIT(2)
#define LEFT_BUTTON BIT(0)
#define SCALING BIT(4)
#define DATA_REPORT BIT(5)
#define MOUSE_MODE BIT(6)
#define SINAL_X BIT(4)
#define SINAL_Y BIT(5)
#define X_OVF BIT(6)
#define Y_OVF BIT(7)
#define TOLERAN 5



//--------------- MENU CONSTANTS

#define SQUARE_HEIGHT 59
#define SQUARE_WIDTH 101

// ---- SINGLE PLAYER AND MOUSE + SNAKE

#define FIRST_ELEMENT 341
#define SECOND_ELEMENT 591
#define THIRD_ELEMENT 838

#define BODY_HEIGHT 491
#define HEAD_HEIGHT 707

// ------ MULTIPLAYER

#define FIRST_ELEMENT_M 336
#define SECOND_ELEMENT_M 584
#define THIRD_ELEMENT_M 834


#define BODY_HEIGHT_M 638


// ---------- RTC

#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_REG_A 0xA
#define RTC_REG_B 0xB
#define BINARY_MODE BIT(2)
#define RTC_UIP BIT(7)
#define RTC_SEC_REG 0x00
#define RTC_MIN_REG 0x02
#define RTC_H_REG 0x04
#define RTC_DAY_REG 0x07
#define RTC_MON_REG 0x08
#define RTC_YEAR_REG 0x09


#endif /* _CONSTANTS_H */
