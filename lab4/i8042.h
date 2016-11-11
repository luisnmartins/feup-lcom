#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_
#include "i8254.h"


#define KB_IRQ 1    //Keyboard IRQ

#define STATUS_REG 0x64
#define KBD_OUT_BUF 0x60

#define OBF BIT(0)
#define IBF BIT(1)

#define ESC_CODE 0x81


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


// ------- RATO

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
#define CONF_FIRST_BYTE  BIT(7) & BIT(3)
#define RIGHT_BUTTON BIT(1)
#define MIDDLE_BUTTON BIT(2)
#define LEFT_BUTTON BIT(0)
#define SCALING BIT(4)
#define DATA_REPORT BIT(5)
#define MOUSE_MODE BIT(6)
#define SINAL_X BIT(4)
#define SINAL_Y BIT(5)
#define TOLERAN 5





#endif /* _LCOM_I8042_H */
